// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A0F9C2DD0568DE6D72532BD20CD051BCC69A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF587AE616E88FE7F510EB0AF2E02C5B9BF23B81689E1110144A14D219375E6C9196A97687E0B2DFABD3BDE3210FEBA472168F349FF0489B228B9F60F1D1E1DF86CB4AC288B9877373BDE7F0A5773FFE2D3F93C85EB19451B75549D34A0D5AD11F30733849047E00CA0E57228E443ABA8BAAA869FE65CB18B5414E084950FA5CC8F5270B55B262AFD36
// REVISION: 1.0
// GUID: 876868D8-FE33-47D5-8510-D363E9A89F39
// DATE: 08\08\2022
// DIR: CAL\ESP\ESP_CAL_ICD2.c
/*********************************************************************
 *                  Flowcode CAL ICD2 File
 *
 * File: ESP_CAL_ICD2.c
 *
 * (c) 2018 Matrix TSL.
 * http://www.matrixtsl.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
 * “Company”) for its Flowcode graphical programming language is
 * intended and supplied to you, the Company’s customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Changelog:
 *
 *  date  | by | description
 * -------+----+-----------------------------------------------------
 * 250718 | BR | Created
 *
 */


	//ICD Clock Port Defines

	#ifdef MX_BL0058_PINMAP
		#define ICD_ALT_CLK_PIN		12				//Hard coded to PortA pin 6 / IO12
		#define ICD_ALT_DATA_PIN	13				//Hard coded to PortA pin 7 / IO13
	#else
		#if (ICD_CLK_PORT == 0)
		  #define ICD_ALT_CLK_PIN	ICD_CLK_PIN
		#endif
		#if (ICD_CLK_PORT == 1)
		  #define ICD_ALT_CLK_PIN	ICD_CLK_PIN + 32
		#endif

		//ICD Data Port Defines
		#if (ICD_DATA_PORT == 0)
		  #define ICD_ALT_DATA_PIN	ICD_DATA_PIN
		#endif
		#if (ICD_DATA_PORT == 1)
		  #define ICD_ALT_DATA_PIN	ICD_DATA_PIN + 32
		#endif
	#endif

	//ICD Global Defines
	#define ICD_START	  0x80
	#define ICD_SETBP	  0x81
	#define ICD_CLRBP	  0x82
	#define ICD_EN_IBP	  0x83
	#define ICD_DIS_IBP	  0x84
	#define ICD_EN_SBP	  0x85
	#define ICD_DIS_SBP	  0x86
	#define ICD_RD_RAM	  0x87
	#define ICD_WR_RAM	  0x88
	#define ICD_GET_ID    0x8C
	#define ICD_GET_STACK 0x8D
	#define ICD_DIS_BPS	  0x8B
	#define ICD_RESET	  0x8E

	#ifdef MX_EE					//If EEPROM
		#define ICD_RD_EE	  0x89
		#define ICD_WR_EE	  0x8A
	#endif

	//ICD Global Variables
	unsigned char dbg_mode = 0x00;
	unsigned char icd_stack_ptr = 0x00;
	unsigned char ICD_Interrupt_Enable = 0;
	unsigned int ICD_TIMEOUT = 10000;

	//ICD Functions
	void MARKER(signed int block_id);
	void PUSH(char macro_id);
	void POP();
	char icd_byte_tx(char data);
	char icd_byte_rx(void);
	char wait_clock(char state, char timeout_inc);
	char wait_data(char state);
	char read_register(unsigned int address);
	void write_register(unsigned int address, char data);
	void rst_dev(void);

	#define FC_MARKER(x)		{ if (ICD_Interrupt_Enable == 0)	{ ICD_Interrupt_Enable = 1; MARKER(x); ICD_Interrupt_Enable = 0; } }
	#define ICD_PUSH(x)			{ if (ICD_Interrupt_Enable == 0)	{ ICD_Interrupt_Enable = 1; PUSH(x); ICD_Interrupt_Enable = 0; } }
	#define ICD_POP()			{ if (ICD_Interrupt_Enable == 0)	{ ICD_Interrupt_Enable = 1; POP(); ICD_Interrupt_Enable = 0; } }


	//ICD Marker Functions - Called at the start of every Flowcode block when ICD is enabled.
	void MARKER(signed int block_id)
	{
		//if (ICD_Interrupt_Enable == 0)
		//{
			portDISABLE_INTERRUPTS();						//Disable all interrupts


			unsigned char dbg_hold = 0;
			unsigned char icd_cmd;
			unsigned int address;
			unsigned char idx;
			char tempdata = 0;

			gpio_set_direction(ICD_ALT_CLK_PIN, GPIO_MODE_INPUT);			//Clock is an input
			gpio_set_direction(ICD_ALT_DATA_PIN, GPIO_MODE_OUTPUT);			//Data is an output
			gpio_set_level(ICD_ALT_DATA_PIN, 0);		//Data is default low

			if(gpio_get_level(ICD_ALT_CLK_PIN))			//Test to see if clock input is 1
				dbg_mode = dbg_mode | 0x04;					//Enable ICD Pause
			else
				dbg_mode = dbg_mode & 0xFB;					//Disable ICD Pause

			if(dbg_mode)									//Is ICD Active?
			{
				if(dbg_mode & 0x01) dbg_hold = 0x01;		//Test for Single Step operation
				if(dbg_mode & 0x02)							//Test for Breakpoint operation and match
				{
					for(idx=0; idx<ICD_NUM_BPS; idx++)
					{
						if(block_id == brk_pnt[idx]) dbg_hold = dbg_hold | 0x02;
					}
				}

				if(dbg_mode & 0x04) 								//Test for Flowcode triggered operation
					dbg_hold = dbg_hold | 0x04;

				if(dbg_mode & 0x08) 								//Test for initial stop condition
				{
					dbg_hold = dbg_hold | 0x08;						//Place target into infinite wait mode
					dbg_mode = dbg_mode & 0xF7;						//Disable infinite wait mode for next iteration.
				}

				if(dbg_hold)										//Enter Debug mode
				{
					gpio_set_direction(ICD_ALT_DATA_PIN, GPIO_MODE_INPUT);		//Data is an input target stopped

					if (dbg_hold & 0x08)
					{
						wait_clock(1, 0);				//Wait indefinitely for the next clock
						wait_clock(0, 0);							//Wait indefinitely for the next clock
						wait_clock(1, 0);				//Wait indefinitely for the next clock

						icd_byte_tx(dbg_mode);						//Send current ICD mode
						icd_byte_tx(block_id);						//Send block ID
						icd_byte_tx(block_id>>8);
					}
					else
					{
						if (wait_clock(1, 1))			//Wait for clock to go high
							return;
						if (wait_clock(0, 1))						//Wait for clock to go low
							return;
						if (wait_clock(1, 1))			//Wait for clock to go high
							return;

						if (icd_byte_tx(dbg_mode)) dbg_hold = 0;	//Send current ICD mode
						if (icd_byte_tx(block_id)) dbg_hold = 0;	//Send block ID
						if (icd_byte_tx(block_id>>8)) dbg_hold = 0;
					}

					while(dbg_hold)
					{
						icd_cmd = icd_byte_rx();				//Receive command byte

						switch(icd_cmd)
						{
							case ICD_START:									//Start Command

								dbg_hold = 0;								//Start the target running
								gpio_set_direction(ICD_ALT_DATA_PIN, GPIO_MODE_OUTPUT);		//Data is an output
								gpio_set_level(ICD_ALT_DATA_PIN, 0);	//Data is default low
								wait_clock(0, 1);
								break;

							case ICD_SETBP:						//Set Breakpoint Command

								address = icd_byte_rx();					//Receive BP ID
								address = address | (icd_byte_rx() << 8);
								idx=0;										//Initialise BP counter
								while(idx < ICD_NUM_BPS && brk_pnt[idx] != -1)	//Scan for empty BP slot
									idx = idx + 1;

								if (idx == ICD_NUM_BPS)						//If breakpoint command list full
									icd_byte_tx(255);						//Let the ICD know
								else
								{
									brk_pnt[idx] = address;					//Else assign the BP ID to the BP list
									icd_byte_tx(0);							//Transmit an acknowledge
								}
								break;

							case ICD_CLRBP:						//Clear Breakpoint Command

								address = icd_byte_rx();
								address = address | (icd_byte_rx() << 8);
								idx=0;										//Initialise BP counter
								while(idx < ICD_NUM_BPS && brk_pnt[idx] != address)	//Scan for slot containing BP
									idx = idx + 1;

								if (idx == ICD_NUM_BPS)						//If breakpoint not in the list
									icd_byte_tx(255);						//Let the ICD know
								else
								{
									brk_pnt[idx] = -1;						//Else clear the BP ID from the BP list
									icd_byte_tx(0);							//Transmit an acknowledge
								}
								break;

							case ICD_EN_IBP:					//Enable indexed breakpoints Command

								dbg_mode = dbg_mode | 0x02;					//Enable indexed breakpoints
								break;

							case ICD_DIS_IBP:					//Disable indexed breakpoints Command

								dbg_mode = dbg_mode & 0xFD;					//Disable indexed breakpoints
								break;

							case ICD_EN_SBP:					//Enable step breakpoint Command

								dbg_mode = dbg_mode | 0x01;					//Enable step breakpoint
								break;

							case ICD_DIS_SBP:					//Disable step breakpoint Command

								dbg_mode = dbg_mode & 0xFE;					//Disable step breakpoint
								break;

							case ICD_RD_RAM:					//Read Byte Of RAM Command

								address = icd_byte_rx();
								address = address | (icd_byte_rx() << 8);
								icd_byte_tx(read_register(address));		//&address//Transmit the register value
								break;

							case ICD_WR_RAM:					//Write Byte Of RAM Command

								address = icd_byte_rx();
								address = address | (icd_byte_rx() << 8);
								write_register(address, icd_byte_rx());
								break;

							case ICD_DIS_BPS:					//Clear all breakpoints

								idx=0;	//init BP counter
								while (idx < ICD_NUM_BPS)
								{
									brk_pnt[idx] = -1;
									idx = idx + 1;
								}
								break;



							#ifdef MX_EE						//Is EEPROM Available?

								case ICD_RD_EE:					//Read Contents Of EEPROM Command

									address = icd_byte_rx();
									address = address | (icd_byte_rx() << 8);

									#ifdef EEWE
										while (test_bit(EECR, EEWE));
									#else
										while (test_bit(EECR, EEPE));
									#endif

									icd_byte_tx(eeprom_read_byte((unsigned char *)address));


								case ICD_WR_EE:					//Write Byte to EEPROM Command

									address = icd_byte_rx();
									address = address | (icd_byte_rx() << 8);
									tempdata = icd_byte_rx();

									#ifdef EEWE
										while (test_bit(EECR, EEWE));
									#else
										while (test_bit(EECR, EEPE));
									#endif

										eeprom_write_byte((unsigned char *)address, tempdata);
									break;
							#endif								//End of EEPROM code

							case ICD_GET_ID:
								icd_byte_tx(ICD_ID0);
								icd_byte_tx(ICD_ID1);
								icd_byte_tx(ICD_ID2);
								icd_byte_tx(ICD_ID3);
								icd_byte_tx(ICD_ID4);
								icd_byte_tx(ICD_ID5);
								icd_byte_tx(ICD_ID6);
								icd_byte_tx(ICD_ID7);
								break;

							case ICD_GET_STACK:
								icd_byte_tx(ICD_STACK_SIZE+1);		//+1 because the PPP firmware does not expect the stack pointer return as well
								icd_byte_tx(icd_stack_ptr);
								for (idx=0; idx<ICD_STACK_SIZE; idx++)
								{
									icd_byte_tx(icd_stack[idx]);
								}
								break;

							case ICD_RESET:
								rst_dev();
								break;

							default:
								break;
						}
					}
				}
				gpio_set_direction(ICD_ALT_DATA_PIN, GPIO_MODE_OUTPUT);				//Data line as output
				gpio_set_level(ICD_ALT_DATA_PIN, 0);			//Data output low
			}

			portENABLE_INTERRUPTS();							//Restore all interrupts
		//}
	}


	void PUSH (char macro_id)
	{
		//if (ICD_Interrupt_Enable == 0)
		//{
			//note: there is no specific stack overflow test here (there will be at the PC end though)
			if (icd_stack_ptr < ICD_STACK_SIZE)
			{
				icd_stack[icd_stack_ptr] = macro_id;			//Assign macro ID
			}
			icd_stack_ptr++;									//Move to next layer of stack
		//}
	}


	void POP()
	{
		//if (ICD_Interrupt_Enable == 0)
		//{
			//note: there is no specific stack underflow test here (there will be at the PC end though)
			icd_stack_ptr--;
		//}
	}


	//ICD transmit byte Function - Bit bangs out a data byte.
	char icd_byte_tx(char data)
	{
		char count, mask;

		gpio_set_direction(ICD_ALT_CLK_PIN, GPIO_MODE_INPUT);					//Clock line as input
		gpio_set_direction(ICD_ALT_DATA_PIN, GPIO_MODE_OUTPUT);				//Data line as output
		gpio_set_level(ICD_ALT_DATA_PIN, 0);				//Data is 0 RTS

		if (wait_clock(0, 1))								//Wait for clock to go low
			return 255;

		for(count=0; count<8; count++)
		{
			mask = data & 0x01;						//Prepare data
			if(mask)								//Write data onto data line
				gpio_set_level(ICD_ALT_DATA_PIN, 1);
			else
				gpio_set_level(ICD_ALT_DATA_PIN, 0);
			data = data >> 1;
			if (wait_clock(1, 1))				//Wait for clock to go high
				return 254;
			if (wait_clock(0, 1))							//Wait for clock to go low
				return 253;
		}

		gpio_set_direction(ICD_ALT_DATA_PIN, GPIO_MODE_INPUT);				//Data line as input end of byte
		if (wait_data(0))									//Wait for byte acknowledge
				return 252;
		if (wait_clock(1, 1))					//Wait for byte acknowledge end
				return 251;
		return 0;									//Success!
	}



	//ICD receive byte Function - Collects a bit banged serial data byte.
	char icd_byte_rx(void)
	{
		unsigned char data = 0;
		unsigned char count;

		gpio_set_direction(ICD_ALT_DATA_PIN, GPIO_MODE_INPUT);			//Data line as input
		gpio_set_direction(ICD_ALT_CLK_PIN, GPIO_MODE_INPUT);				//Clock line as input
		for(count=0; count<8; count++)					//Receive Byte
		{
			data = data >> 1;
			if (wait_clock(0, 1))						//Wait for clock to go low
				return 0;

			if (gpio_get_level(ICD_ALT_DATA_PIN)) 	//Read incoming data on data pin
				data = data | 0x80;

			if (wait_clock(1, 1))			//Wait for clock to go high
				return 0;
		}

		if (wait_data(1))					//Wait for data to go high
			return 0;

		if (wait_clock(0, 1))							//Wait for clock to go low
			return 0;

		gpio_set_direction(ICD_ALT_DATA_PIN, GPIO_MODE_OUTPUT);			//ICD data is an output
		gpio_set_level(ICD_ALT_DATA_PIN, 0);		//ICD data 0 send Ack

		if (wait_clock(1, 1))				//Wait for clock to go high
			return 0;

		gpio_set_direction(ICD_ALT_DATA_PIN, GPIO_MODE_INPUT);			//ICD data clear ack
		return(data);
	}


	char wait_clock(char state, char timeout_inc)
	{
		unsigned int timeout = 0;

		while ((gpio_get_level(ICD_ALT_CLK_PIN) != state) && (timeout < ICD_TIMEOUT))	//Wait for clk
			timeout = timeout +  timeout_inc;		//Increment time out

		if (timeout == ICD_TIMEOUT)					//Has the routine timed out
			return 1;
		return 0;
	}


	char wait_data(char state)
	{
		unsigned int timeout = 0;
		while ((gpio_get_level(ICD_ALT_DATA_PIN) != state) && (timeout < ICD_TIMEOUT))	//Wait for data		**** inverted
			timeout = timeout +  1;					//Increment time out

		if (timeout == ICD_TIMEOUT)					//Has the routine timed out
			return 1;
		return 0;
	}


	char read_register(unsigned int address)
	{
		char RetVal;

		volatile char* register_ptr = (char*)address;

		RetVal = *register_ptr;

		return RetVal;
	}


	void write_register(unsigned int address, char data)
	{
		volatile char* register_ptr = (char*)address;

		*register_ptr = data;
	}


	void rst_dev()
	{
		esp_restart();
	}


//End of ICD functionality