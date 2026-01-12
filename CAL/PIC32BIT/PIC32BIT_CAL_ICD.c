// CRC: A6459004C43C0517DC6DFC5681C2AD698104299A14C9E1875427A2F7EF4303D9CFD76A29863CD488DE50EA9D9C0AC8D11943CB6EFE8CD218370B0AACA18BB2D79A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5F6CC40EFEDD46E1C2C9201818FE36F942DDD1B42B08E21222A6FE0E853C3B6B546E019F9F5A30186E8C1C754A0BC1072298417C60E76D5D0285CEB79AD6FBF521A0FF1933BA18FDFC282FACF741A6D2374BD08A0F0502EBA549D34A0D5AD11F350440B7B758AB4B433A4C507C2341F76E7BB8EA59AFD6C3561112B2378F6127E5D3A7ED706D09BBA
// REVISION: 1.0
// GUID: F8CF946C-BA53-46C5-A985-1F4A5FD0849D
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\PIC32BIT_CAL_ICD.c
/*********************************************************************
 *                  Flowcode CAL ICD File
 *
 * File: PIC_CAL_ICD.c
 *
 * (c) 2011 Matrix Multimedia Ltd.
 * http://www.matrixmultimedia.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix Multimedia Ltd (the
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
 * 010911 | BR | Created
 *
 *
 *
 */


	//ICD Clock Port Defines
	#if (ICD_CLK_PORT == 0)
		#define ICD_CLK_PIN_TRIS TRISA
		#define ICD_CLK_PIN_PORT PORTA
	#endif
	#if (ICD_CLK_PORT == 1)
		#define ICD_CLK_PIN_TRIS TRISB
		#define ICD_CLK_PIN_PORT PORTB
	#endif
	#if (ICD_CLK_PORT == 2)
		#define ICD_CLK_PIN_TRIS TRISC
		#define ICD_CLK_PIN_PORT PORTC
	#endif
	#if (ICD_CLK_PORT == 3)
		#define ICD_CLK_PIN_TRIS TRISD
		#define ICD_CLK_PIN_PORT PORTD
	#endif
	#if (ICD_CLK_PORT == 4)
		#define ICD_CLK_PIN_TRIS TRISE
		#define ICD_CLK_PIN_PORT PORTE
	#endif
	#if (ICD_CLK_PORT == 5)
		#define ICD_CLK_PIN_TRIS TRISF
		#define ICD_CLK_PIN_PORT PORTF
	#endif
	#if (ICD_CLK_PORT == 6)
		#define ICD_CLK_PIN_TRIS TRISG
		#define ICD_CLK_PIN_PORT PORTG
	#endif

	//ICD Data Port Defines
	#if (ICD_DATA_PORT == 0)
		#define ICD_DATA_PIN_TRIS TRISA
		#define ICD_DATA_PIN_PORT PORTA
	#endif
	#if (ICD_DATA_PORT == 1)
		#define ICD_DATA_PIN_TRIS TRISB
		#define ICD_DATA_PIN_PORT PORTB
	#endif
	#if (ICD_DATA_PORT == 2)
		#define ICD_DATA_PIN_TRIS TRISC
		#define ICD_DATA_PIN_PORT PORTC
	#endif
	#if (ICD_DATA_PORT == 3)
		#define ICD_DATA_PIN_TRIS TRISD
		#define ICD_DATA_PIN_PORT PORTD
	#endif
	#if (ICD_DATA_PORT == 4)
		#define ICD_DATA_PIN_TRIS TRISE
		#define ICD_DATA_PIN_PORT PORTE
	#endif
	#if (ICD_DATA_PORT == 5)
		#define ICD_DATA_PIN_TRIS TRISF
		#define ICD_DATA_PIN_PORT PORTF
	#endif
	#if (ICD_DATA_PORT == 6)
		#define ICD_DATA_PIN_TRIS TRISG
		#define ICD_DATA_PIN_PORT PORTG
	#endif

	#ifndef ICD_CLK_PIN_TRIS
	  #warning "Error: no definition for the ICD clock pin"
	#endif

	#ifndef ICD_DATA_PIN_TRIS
	  #warning "Error: no definition for the ICD data pin"
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
		unsigned int tempdata = 0;
	#endif

	//ICD Global Variables
	unsigned char dbg_mode = 0x00;
	unsigned char icd_stack_ptr = 0x00;
	unsigned char ICD_Interrupt_Enable = 0;
	unsigned int ICD_TIMEOUT = 0xFFFF;

	//ICD Functions
	void MARKER(signed int block_id);
	void PUSH(char macro_id);
	void POP();
	char icd_byte_tx(char data);
	char icd_byte_rx(void);
	char wait_clock(char state, char timeout_inc);
	char wait_data(char state);
	char read_register(unsigned long address);
	void write_register(unsigned long address, char data);
	void rst_dev(void);

	#define FC_MARKER(x)		{ if (ICD_Interrupt_Enable == 0)	{ ICD_Interrupt_Enable = 1; MARKER(x); ICD_Interrupt_Enable = 0; } }
	#define ICD_PUSH(x)			{ if (ICD_Interrupt_Enable == 0)	{ ICD_Interrupt_Enable = 1; PUSH(x); ICD_Interrupt_Enable = 0; } }
	#define ICD_POP()			{ if (ICD_Interrupt_Enable == 0)	{ ICD_Interrupt_Enable = 1; POP(); ICD_Interrupt_Enable = 0; } }


	//ICD Marker Functions - Called at the start of every Flowcode block when ICD is enabled.
	void MARKER(signed int block_id)
	{
		//if (ICD_Interrupt_Enable == 0)
		//{
			__asm__ volatile("disi #0x3FFF");			//Disable interrupts

			unsigned char dbg_hold = 0;
			unsigned char icd_cmd;
			unsigned long address;
			unsigned char idx;

			set_bit(ICD_CLK_PIN_TRIS, ICD_CLK_PIN);					//Clock is an input
			clear_bit(ICD_DATA_PIN_TRIS, ICD_DATA_PIN);				//Data is an output
			set_bit(ICD_DATA_PIN_PORT, ICD_DATA_PIN);				//Data is default low	****** inverted

			if(test_bit(ICD_CLK_PIN_PORT, ICD_CLK_PIN))				//Test to see if clock input is 1
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
						if(block_id == *(brk_pnt + idx)) dbg_hold = dbg_hold | 0x02;		//if(block_id == brk_pnt[idx]) dbg_hold = dbg_hold | 0x02;
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
					set_bit(ICD_DATA_PIN_TRIS, ICD_DATA_PIN);		//Data is an input target stopped

					if (dbg_hold & 0x08)
					{
						delay_us(250);								//Wait for pins to settle after reset
						delay_us(250);								//Wait for pins to settle after reset
						wait_clock(1<<ICD_CLK_PIN, 0);				//Wait indefinitely for the next clock
						wait_clock(0, 0);							//Wait indefinitely for the next clock
						wait_clock(1<<ICD_CLK_PIN, 0);				//Wait indefinitely for the next clock
						icd_byte_tx(dbg_mode);						//Send current ICD mode
						icd_byte_tx(block_id);						//Send block ID
						icd_byte_tx(block_id>>8);

					}
					else
					{
						if (wait_clock(1<<ICD_CLK_PIN, 1))			//Wait for clock to go high
							return;
						if (wait_clock(0, 0))						//Wait for clock to go low
							return;
						if (wait_clock(1<<ICD_CLK_PIN, 0))			//Wait for clock to go high
							return;

						if (icd_byte_tx(dbg_mode)) dbg_hold = 0;	//Send current ICD mode
						if (icd_byte_tx(block_id)) dbg_hold = 0;	//Send block ID
						if (icd_byte_tx(block_id>>8)) dbg_hold = 0;
					}

					while(dbg_hold)
					{
						icd_cmd = icd_byte_rx();							//Receive command byte

						__asm__ volatile("disi #0x3FFF");					//Ensure interrupts remain disabled while waiting

						switch(icd_cmd)
						{
							case ICD_START:									//Start Command

								dbg_hold = 0;								//Start the target running
								clear_bit(ICD_DATA_PIN_TRIS, ICD_DATA_PIN);				//Data is an output
								set_bit(ICD_DATA_PIN_PORT, ICD_DATA_PIN);				//Data is default low	**** inverted
								wait_clock(0, 1);
								break;

							case ICD_SETBP:						//Set Breakpoint Command

								address = icd_byte_rx();					//Receive BP ID
								address = address | (icd_byte_rx() << 8);
								idx=0;										//Initialise BP counter
								while(idx < ICD_NUM_BPS && *(brk_pnt + idx) != -1)	//Scan for empty BP slot           //while(idx < ICD_NUM_BPS && brk_pnt[idx] != -1)	//Scan for empty BP slot
									idx = idx + 1;

								if (idx == ICD_NUM_BPS)						//If breakpoint command list full
									icd_byte_tx(255);						//Let the ICD know
								else
								{
									*(brk_pnt + idx) = address;					//Else assign the BP ID to the BP list				//brk_pnt[idx] = address;
									icd_byte_tx(0);							//Transmit an acknowledge
								}
								break;

							case ICD_CLRBP:						//Clear Breakpoint Command

								address = icd_byte_rx();
								address = address | (icd_byte_rx() << 8);
								idx=0;										//Initialise BP counter
								while(idx < ICD_NUM_BPS && *(brk_pnt + idx) != address)	//Scan for slot containing BP				//while(idx < ICD_NUM_BPS && brk_pnt[idx] != address)
									idx = idx + 1;

								if (idx == ICD_NUM_BPS)						//If breakpoint not in the list
									icd_byte_tx(255);						//Let the ICD know
								else
								{
									*(brk_pnt + idx) = -1;						//Else clear the BP ID from the BP list					//brk_pnt[idx] = -1;
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
                				address = address | 0xa0000000;
								icd_byte_tx(read_register(address));		//&address//Transmit the register value
								break;

							case ICD_WR_RAM:					//Write Byte Of RAM Command

								address = icd_byte_rx();
								address = address | (icd_byte_rx() << 8);
                				address = address | 0xa0000000;
								write_register(address, icd_byte_rx());
								break;

							case ICD_DIS_BPS:					//Clear all breakpoints

								idx=0;	//init BP counter
								while (idx < ICD_NUM_BPS)
								{
									*(brk_pnt + idx) = -1;											//brk_pnt[idx] = -1;
									idx = idx + 1;
								}
								break;

							#ifdef MX_EE						//Is EEPROM Available?

								case ICD_RD_EE:					//Read Contents Of EEPROM Command

									address = icd_byte_rx();
									address = address | (icd_byte_rx() << 8);
									if (address < (MX_EE_SIZE / 2))
									{
										TBLPAG = __builtin_tblpage(&eeprom);      // eeprom page
										address = __builtin_tbloffset(&eeprom) + address;
										icd_byte_tx(__builtin_tblrdl(address));
									}
									else
									{
										icd_byte_tx(0);
									}
									break;

								case ICD_WR_EE:					//Write Byte to EEPROM Command

									address = icd_byte_rx();
									address = address | (icd_byte_rx() << 8);
									tempdata = icd_byte_rx();

									if (address < (MX_EE_SIZE / 2))
									{
										NVMCON = 0x4004;            // set up to write 1 word

										TBLPAG = __builtin_tblpage(&eeprom);
										address = __builtin_tbloffset(&eeprom) + address;

										__builtin_tblwtl(address,tempdata);    // prepare data in write latch

										 //asm volatile ("disi #6");    // disable irqs for 6 instructions
										 //Interrupts already temporarily disabled.

										 __builtin_write_NVM();        // unlock and write

										while(NVMCONbits.WR);        // wait while busy
									}
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
									icd_byte_tx(*(icd_stack + idx));											//icd_byte_tx(icd_stack[idx]);
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
				clear_bit(ICD_DATA_PIN_TRIS,ICD_DATA_PIN);				//Data line as output
				set_bit(ICD_DATA_PIN_PORT,ICD_DATA_PIN);				//Data output low	**** inverted
			}
			__asm__ volatile("disi #0x0001");						//Restore all interrupts
		//}
	}


	void PUSH(char macro_id)
	{
		//if (ICD_Interrupt_Enable == 0)
		//{
			//note: there is no specific stack overflow test here (there will be at the PC end though)
			if (icd_stack_ptr < ICD_STACK_SIZE)
			{
				*(icd_stack + icd_stack_ptr) = macro_id;			//Assign macro ID				//icd_stack[icd_stack_ptr] = macro_id;
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

		set_bit(ICD_CLK_PIN_TRIS,ICD_CLK_PIN);				//Clock line as input
		clear_bit(ICD_DATA_PIN_TRIS,ICD_DATA_PIN);			//Data line as output
		set_bit(ICD_DATA_PIN_PORT,ICD_DATA_PIN);			//Data is 0 RTS		**** inverted

		if (wait_clock(0, 1))								//Wait for clock to go low
			return 255;

		for(count=0; count<8; count++)
		{
			mask = data & 0x01;								//Prepare data
			if(mask)										//Write data onto data line
				clear_bit(ICD_DATA_PIN_PORT,ICD_DATA_PIN);			// **** inverted
			else
				set_bit(ICD_DATA_PIN_PORT,ICD_DATA_PIN);			// **** inverted
			data = data >> 1;
			if (wait_clock(1<<ICD_CLK_PIN, 1))				//Wait for clock to go high
				return 254;
			if (wait_clock(0, 1))							//Wait for clock to go low
				return 253;
		}

		set_bit(ICD_DATA_PIN_TRIS,ICD_DATA_PIN);			//Data line as input end of byte
		if (wait_data(0))									//Wait for byte acknowledge
				return 252;
		if (wait_clock(1<<ICD_CLK_PIN, 1))					//Wait for byte acknowledge end
				return 251;
		return 0;											//Success!
	}



	//ICD receive byte Function - Collects a bit banged serial data byte.
	char icd_byte_rx(void)
	{
		unsigned char data = 0;
		unsigned char count;

		set_bit(ICD_DATA_PIN_TRIS,ICD_DATA_PIN);			//Data line as input
		set_bit(ICD_CLK_PIN_TRIS,ICD_CLK_PIN);				//Clock line as input
		for(count=0; count<8; count++)						//Receive Byte
		{
			data = data >> 1;
			if (wait_clock(0, 1))							//Wait for clock to go low
				return 0;

			if (test_bit(ICD_DATA_PIN_PORT,ICD_DATA_PIN) == 0) 		//Read incoming data on data pin	**** inverted
				data = data | 0x80;

			if (wait_clock(1<<ICD_CLK_PIN, 1))				//Wait for clock to go high
				return 0;
		}

		if (wait_data(1<<ICD_DATA_PIN))						//Wait for data to go high
			return 0;

		if (wait_clock(0, 1))								//Wait for clock to go low
			return 0;

		clear_bit(ICD_DATA_PIN_TRIS, ICD_DATA_PIN);			//ICD data is an output
		set_bit(ICD_DATA_PIN_PORT, ICD_DATA_PIN);			//ICD data 0 send Ack		**** inverted

		if (wait_clock(1<<ICD_CLK_PIN, 1))					//Wait for clock to go high
			return 0;

		set_bit(ICD_DATA_PIN_TRIS, ICD_DATA_PIN);			//ICD data clear ack
		return(data);
	}


	char wait_clock(char state, char timeout_inc)
	{
		unsigned int timeout = 0;
		unsigned char tout2 = 0;

		while ((test_bit(ICD_CLK_PIN_PORT,ICD_CLK_PIN) != state) && (timeout < ICD_TIMEOUT))	//Wait for clk
		{
			tout2 = tout2 + timeout_inc;
			if (tout2 == 0)
			{
				timeout = timeout +  timeout_inc;				//Increment time out
			}
			delay_us(1);
		}

		if (timeout == ICD_TIMEOUT)							//Has the routine timed out
			return 1;
		return 0;
	}


	char wait_data(char state)
	{
		unsigned int timeout = 0;
		unsigned char tout2 = 0;

		while ((test_bit(ICD_DATA_PIN_PORT, ICD_DATA_PIN) == state) && (timeout < ICD_TIMEOUT))	//Wait for data		**** inverted
		{
			tout2 = tout2 + 1;
			if (tout2 == 0)
			{
				timeout = timeout +  1;							//Increment time out
			}
			delay_us(1);
		}

		if (timeout == ICD_TIMEOUT)							//Has the routine timed out
			return 1;
		return 0;
	}


	char read_register(unsigned long address)
	{
		char RetVal;

		volatile char* register_ptr = (char*)address;

		RetVal = *register_ptr;

		return RetVal;
	}


	void write_register(unsigned long address, char data)
	{
		volatile char* register_ptr = (char*)address;

		*register_ptr = data;
	}


	void rst_dev()
	{
		unsigned int resdummy;

		// Perform device reset
		// The system unlock sequence must be performed before the SWRST bit can be written.
		// Refer to Section 6. “Oscillator” (DS61112) in the “PIC32 Family Reference Manual” for details.
		// -> Execute  the  system  unlock  sequence  by  writing  the  Key  values  of
		// 0xAA996655  and 0x556699AA to the SYSKEY register.

		SYSKEY = 0x00000000;
		SYSKEY = 0xAA996655;
		SYSKEY = 0x556699AA;

		RSWRSTbits.SWRST = 1;

		resdummy = RSWRST;

		while(1);
	}


//End of ICD functionality

