// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B8F9C2DD0568DE6D72532BD20CD051BCC69A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF568EF3C86207F539885134A2156F2DEEFCA1A65F02BE777B9A97A134C93601B58CA7D72E835FE004994A63E190EFED2D8F294882B89B581C050ED66A8BDC3E761D4019840D93070EB6CA7F40963EFC893D79B4145C7715DF8549D34A0D5AD11F328D90B0EE5F39BFAC90ADD8209FE002038C7F98BBD676823EC447A7A7C3AA69E9E27863BF8B478B1
// REVISION: 1.0
// GUID: 42D02E52-8183-4734-BB69-21ECA443AA65
// DATE: 08\08\2022
// DIR: CAL\PIC\PIC_CAL_ICD2.c
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
 * copyright laws. All rights are reserved. Any use in vioportion
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
		#if defined (_PORTA_RA0_POSN) || defined (_PORTA_RA1_POSN) || defined (_PORTA_RA2_POSN) || defined (_PORTA_RA3_POSN) || defined (_PORTA_RA4_POSN) || defined (_PORTA_RA5_POSN) || defined (_PORTA_RA6_POSN) || defined (_PORTA_RA7_POSN)
			#define ICD_CLK_PIN_TRIS TRISA
			#define ICD_CLK_PIN_PORT PORTA
		#endif
		#if defined (_GPIO_GP0_POSN) || defined (_GPIO_GP1_POSN) || defined (_GPIO_GP2_POSN) || defined (_GPIO_GP3_POSN)
			#define ICD_CLK_PIN_PORT GPIO
			#ifdef TRISGPIO
				#define ICD_CLK_PIN_TRIS TRISGPIO
			#endif
			#ifdef TRISIO
				#define ICD_CLK_PIN_TRIS TRISIO
			#endif
			#ifdef TRIS
				#define ICD_CLK_PIN_TRIS TRIS
			#endif
		#endif
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
		#ifdef _PORTA_RA0_POSN
			#define ICD_DATA_PIN_TRIS TRISA
			#define ICD_DATA_PIN_PORT PORTA
		#endif
		#ifdef GPIO
			#define ICD_DATA_PIN_PORT GPIO
			#ifdef TRISGPIO
				#define ICD_DATA_PIN_TRIS TRISGpio
			#endif
			#ifdef TRISIO
				#define ICD_DATA_PIN_TRIS TRISIO
			#endif
			#ifdef TRIS
				#define ICD_DATA_PIN_TRIS TRIS
			#endif
		#endif
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
	#endif

	//ICD Global Variables
	unsigned char dbg_mode = 0x00;
	unsigned char icd_stack_ptr = 0x00;
	unsigned char ICD_Interrupt_Enable = 0;
	unsigned int ICD_TIMEOUT = 1000;

	//ICD Functions
	void MARKER(signed int block_id);
	void PUSH(char macro_id);
	void POP();
	unsigned char icd_byte_tx(char data);
	unsigned char icd_byte_rx(void);
	unsigned char wait_clock(char state, char timeout_inc);
	unsigned char wait_data(char state);
	char read_register(unsigned int address);
	void write_register(unsigned int address, char data);
	void rst_dev(void);


	#define FC_MARKER(x)		{ if (ICD_Interrupt_Enable == 0)	{ ICD_Interrupt_Enable = 1; MARKER(x); ICD_Interrupt_Enable = 0; } }
	#define ICD_PUSH(x)			{ if (ICD_Interrupt_Enable == 0)	{ ICD_Interrupt_Enable = 1; PUSH(x); ICD_Interrupt_Enable = 0; } }
	#define ICD_POP()			{ if (ICD_Interrupt_Enable == 0)	{ ICD_Interrupt_Enable = 1; POP(); ICD_Interrupt_Enable = 0; } }


	//#warning "'Possible sw stack corruption' messages can safely be ignored for 'MARKER', 'PUSH' and 'POP' ICD functions";


	//ICD Marker Functions - Called at the start of every Flowcode block when ICD is enabled.
	void MARKER(signed int block_id)
	{
		unsigned char int_store;


		//if (ICD_Interrupt_Enable == 0)
		//{
			int_store = INTCON;									//Store interrupt register
			INTCON = 0;											//Disable all interrupts

			unsigned char dbg_hold = 0;
			unsigned char icd_cmd;
			unsigned int address;
			unsigned char idx;
			char tempdata = 0;

			set_bit(ICD_CLK_PIN_TRIS, ICD_CLK_PIN);					//Clock is an input
			clear_bit(ICD_DATA_PIN_TRIS, ICD_DATA_PIN);				//Data is an output
			clear_bit(ICD_DATA_PIN_PORT, ICD_DATA_PIN);				//Data is default low

			if(test_bit(ICD_CLK_PIN_PORT, ICD_CLK_PIN))				//Test to see if clock input is 1
			{
				dbg_mode = dbg_mode | 0x04;							//Enable ICD Pause
			}
			else
			{
				dbg_mode = dbg_mode & 0xFB;							//Disable ICD Pause
			}

			if(dbg_mode)											//Is ICD Active?
			{
				if(dbg_mode & 0x01)
				{
					dbg_hold = 0x01;								//Test for Single Step operation
				}
				if(dbg_mode & 0x02)									//Test for Breakpoint operation and match
				{
					for(idx=0; idx<ICD_NUM_BPS; idx++)
					{
						if(block_id == *(brk_pnt + idx))
						{
							dbg_hold = dbg_hold | 0x02;				//if(block_id == brk_pnt[idx]) dbg_hold = dbg_hold | 0x02;
						}
					}
				}

				if(dbg_mode & 0x04) 								//Test for Flowcode triggered operation
				{
					dbg_hold = dbg_hold | 0x04;
				}

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
						icd_cmd = icd_byte_rx();					//Receive command byte
						switch(icd_cmd)
						{
							case ICD_START:									//Start Command

								dbg_hold = 0;								//Start the target running
								clear_bit(ICD_DATA_PIN_TRIS, ICD_DATA_PIN);				//Data is an output
								set_bit(ICD_DATA_PIN_PORT, ICD_DATA_PIN);				//Data is high
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
									*(brk_pnt + idx) = -1;											//brk_pnt[idx] = -1;
									idx = idx + 1;
								}
								break;

							#ifdef MX_EE						//Is EEPROM Available?
								#ifdef _BOOSTC
									#ifndef MX_ICD_EEADR
										#ifdef EEADR
											#define MX_ICD_EEADR eeadr
										#endif
									#endif
									#ifndef MX_ICD_EEADR
										#ifdef EEADRL
											#define MX_ICD_EEADR eeadrl
										#endif
									#endif
									#ifndef MX_ICD_EEDATA
										#ifdef EEDATA
											#define MX_ICD_EEDATA eedata
										#endif
									#endif
									#ifndef MX_ICD_EEDATA
										#ifdef EEDATAL
											#define MX_ICD_EEDATA eedatal
										#endif
									#endif
								#endif

								case ICD_RD_EE:					//Read Contents Of EEPROM Command

									address = icd_byte_rx();
									address = address | (icd_byte_rx() << 8);

									#ifdef _BOOSTC
										MX_ICD_EEADR = address & 0xff;
										#if (MX_EE_SIZE > 256)
											eeadrh = (address & 0xff00) >> 8;
										#endif
										#ifdef MX_EE_TYPE2
											cr_bit(eecon1, EEPGD);
										#endif
										#ifdef MX_EE_TYPE3
											cr_bit(eecon1, EEPGD);
											cr_bit(eecon1, CFGS);
										#endif
											st_bit(eecon1, RD);

										icd_byte_tx(MX_ICD_EEDATA);
									#endif
									#ifdef HI_TECH_C
										icd_byte_tx(eeprom_read(address));
									#endif
									#ifdef ALTCAL_XC8
										icd_byte_tx(eeprom_read(address));
									#endif
									break;

								case ICD_WR_EE:					//Write Byte to EEPROM Command

									address = icd_byte_rx();
									address = address | (icd_byte_rx() << 8);
									tempdata = icd_byte_rx();

									#ifdef _BOOSTC
										while (ts_bit(eecon1, WR));				//wait for previous EE writes to complete...

										#if (MX_EE_SIZE > 256)
											eeadrh = (address & 0xff00) >> 8;
										#endif

										MX_ICD_EEADR = address & 0xff;
										MX_ICD_EEDATA = tempdata;

										#ifdef MX_EE_TYPE2
											cr_bit(eecon1, EEPGD);
										#endif
										#ifdef MX_EE_TYPE3
											cr_bit(eecon1, EEPGD);
											cr_bit(eecon1, CFGS);
										#endif

										st_bit(eecon1, WREN);
										eecon2 = 0x55;
										eecon2 = 0xAA;
										st_bit(eecon1, WR);
										while (ts_bit(eecon1, WR));				//wait for EE write to complete...
									#endif
									#ifdef HI_TECH_C
										eeprom_write(address, tempdata);
									#endif
									#ifdef ALTCAL_XC8
										eeprom_write(address, tempdata);
									#endif

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
				clear_bit(ICD_DATA_PIN_PORT,ICD_DATA_PIN);				//Data output low
			}

			INTCON = int_store;										//Restore all interrupts
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
			icd_stack_ptr++;
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
		clear_bit(ICD_DATA_PIN_PORT,ICD_DATA_PIN);			//Data is 0 RTS

		if (wait_clock(0, 0))								//Wait here for receive to start from host
			return 255;

		for(count=0; count<8; count++)
		{
			mask = data & 0x01;								//Prepare data
			if(mask)										//Write data onto data line
				set_bit(ICD_DATA_PIN_PORT,ICD_DATA_PIN);
			else
				clear_bit(ICD_DATA_PIN_PORT,ICD_DATA_PIN);
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

		wait_clock(0, 0);									//Wait here for transmit to start from host

		for(count=0; count<8; count++)						//Receive Byte
		{
			data = data >> 1;
			if (wait_clock(0, 1))							//Wait for clock to go low
			{
				return 0;
			}
			if (test_bit(ICD_DATA_PIN_PORT,ICD_DATA_PIN)) 	//Read incoming data on data pin
				data = data | 0x80;

			if (wait_clock(1<<ICD_CLK_PIN, 1))				//Wait for clock to go high
			{
				return 0;
			}
		}

		if (wait_data(1<<ICD_DATA_PIN))						//Wait for data to go high
		{
			return 0;
		}

		if (wait_clock(0, 1))								//Wait for clock to go low
		{
			return 0;
		}

		clear_bit(ICD_DATA_PIN_TRIS, ICD_DATA_PIN);			//ICD data is an output
		clear_bit(ICD_DATA_PIN_PORT, ICD_DATA_PIN);			//ICD data 0 send Ack

		if (wait_clock(1<<ICD_CLK_PIN, 1))					//Wait for clock to go high
		{
			return 0;
		}

		//set_bit(ICD_DATA_PIN_TRIS, ICD_DATA_PIN);			//ICD data clear ack

		return(data);
	}


	char wait_clock(char state, char timeout_inc)
	{
		unsigned int timeout = 0;

		while ((test_bit(ICD_CLK_PIN_PORT,ICD_CLK_PIN) != state) && (timeout < ICD_TIMEOUT))	//Wait for clk
			timeout = timeout +  timeout_inc;		//Increment time out

		if (timeout == ICD_TIMEOUT)					//Has the routine timed out
			return 1;
		return 0;
	}


	char wait_data(char state)
	{
		unsigned int timeout = 0;
		while ((test_bit(ICD_DATA_PIN_PORT, ICD_DATA_PIN) != state) && (timeout < ICD_TIMEOUT))	//Wait for data
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
		//Disable all interrupts
		INTCON = 0;
		#ifdef _PIE1_TMR1IE_POSN
			PIE1 = 0x00;
		#endif
		#ifdef _PIE2_LVDIE_POSN
			PIE2 = 0x00;
		#endif

		//Reset all port pins back to inputs
		#ifdef _PORTA_RA0_POSN
			TRISA = 0xff;
			PORTA = 0x00;
		#endif
		#ifdef GPIO | gpio
			GPIO = 0x00;
			#ifdef TRISGPIO | trisgpio
				TRISGPIO = 0xff;
			#endif
			#ifdef TRISIO | trisio
				TRISIO = 0xff;
			#endif
			#ifdef TRIS | tris
				TRIS = 0xff;
			#endif
		#endif
		#ifdef _PORTB_RB0_POSN
			TRISB = 0xff;
			PORTB = 0x00;
		#endif
		#ifdef _PORTC_RC0_POSN
			TRISC = 0xff;
			PORTC = 0x00;
		#endif
		#ifdef _PORTD_RD0_POSN
			TRISD = 0xff;
			PORTD = 0x00;
		#endif
		#ifdef _PORTE_RE0_POSN
			#ifdef _TRISE_TRISE0_POSN	//Some devices have a PORTE pin for MCLR but no TRISE register
				TRISE = 0xff;
			#endif
			PORTE = 0x00;
		#endif
		#ifdef _PORTF_RF0_POSN
			TRISF = 0xff;
			PORTF = 0x00;
		#endif

		//Software Reset
		INTCON=0;			//Disable Interrupts
		#ifdef _OPTION_REG_PSA_POSN
			OPTION_REG=8;		//Enable watchdog timer with 1:1 prescale
		#endif
		#ifdef _T0CON_PSA_POSN
			T0CON=8;
		#endif

		//Rollback EB006v7 has issues with this!!
		//#ifdef _WDTCON_SWDTEN_POSN
		//	WDTCON = 0x01;		//Enable watchdog timer with 1:1 prescale
		//#endif

		RESET();			//Supported on some devices

		while(1) ;   		//Wait forever for watchdog reset
	}

//End of ICD functionality
