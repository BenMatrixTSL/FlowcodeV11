// CRC: 34358081B117C27F7D8358E612878F8E5F343B66182D417818220CB9C07676CFF9C2DD0568DE6D72532BD20CD051BCC69A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF553C1241817FF9D94AF1544850DD4A831F281FFB7457FFDBAD953523820156617410A766AC01F08F531D500F584AA44E2EC8DFA61E15F6D29CBE748A353177B6738B947A675A86888B9C6075CA226687522A61D2BBA84C14E549D34A0D5AD11F31B100C7D0B0A4D98DFADD99F8C745EB3C6DD1A8ED9C9EDB46C38C782664ADBC14BD5B47FBC6A6D19
// REVISION: 1.0
// GUID: C9B19AAB-7FE1-41B4-9F77-3C1FB3E1D593
// DATE: 08\08\2022
// DIR: CAL\RPI\RPI_CAL_ICD2.c
/*********************************************************************
 *                  Flowcode RPI ICD File
 *
 * File: RPI_CAL_ICD.c
 *
 * (c) 2011-2018 Matrix TSL
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
 * 070218 | LM | Created from PIC
 *
 *
 */

 #include <stdlib.h>

// #define MX_ICD_DEBUG
// #define MX_ICD_DEBUG_CMD
// #define MX_ICD_DEBUG_HALT_FLAG  21
// #define MX_ICD_DEBUG_RX_FLAG  20
// #define MX_ICD_DEBUG_TX_FLAG  12

// Now for some pin mangling for BL0036 :O) ...
#if   (ICD_CLK_PORT == PORTA)
	#if   (ICD_CLK_PIN == 0)
		#define MX_ICD_CLK_GPIO	MX_PORTA0_GPIO
	#elif (ICD_CLK_PIN == 1)
		#define MX_ICD_CLK_GPIO	MX_PORTA1_GPIO
	#elif (ICD_CLK_PIN == 2)
		#define MX_ICD_CLK_GPIO	MX_PORTA2_GPIO
	#elif (ICD_CLK_PIN == 3)
		#define MX_ICD_CLK_GPIO	MX_PORTA3_GPIO
	#elif (ICD_CLK_PIN == 4)
		#define MX_ICD_CLK_GPIO	MX_PORTA4_GPIO
	#elif (ICD_CLK_PIN == 5)
		#define MX_ICD_CLK_GPIO	MX_PORTA5_GPIO
	#endif
#elif (ICD_CLK_PORT == PORTB)
	#if   (ICD_CLK_PIN == 0)
		#define MX_ICD_CLK_GPIO	MX_PORTB0_GPIO
	#elif (ICD_CLK_PIN == 1)
		#define MX_ICD_CLK_GPIO	MX_PORTB1_GPIO
	#elif (ICD_CLK_PIN == 2)
		#define MX_ICD_CLK_GPIO	MX_PORTB2_GPIO
	#elif (ICD_CLK_PIN == 3)
		#define MX_ICD_CLK_GPIO	MX_PORTB3_GPIO
	#elif (ICD_CLK_PIN == 4)
		#define MX_ICD_CLK_GPIO	MX_PORTB4_GPIO
	#elif (ICD_CLK_PIN == 5)
		#define MX_ICD_CLK_GPIO	MX_PORTB5_GPIO
	#elif (ICD_CLK_PIN == 6)
		#define MX_ICD_CLK_GPIO	MX_PORTB6_GPIO
	#elif (ICD_CLK_PIN == 7)
		#define MX_ICD_CLK_GPIO	MX_PORTB7_GPIO
	#endif
#elif (ICD_CLK_PORT == PORTC)
	#if   (ICD_CLK_PIN == 0)
		#define MX_ICD_CLK_GPIO	MX_PORTC0_GPIO
	#elif (ICD_CLK_PIN == 1)
		#define MX_ICD_CLK_GPIO	MX_PORTC1_GPIO
	#elif (ICD_CLK_PIN == 2)
		#define MX_ICD_CLK_GPIO	MX_PORTC2_GPIO
	#elif (ICD_CLK_PIN == 3)
		#define MX_ICD_CLK_GPIO	MX_PORTC3_GPIO
	#elif (ICD_CLK_PIN == 4)
		#define MX_ICD_CLK_GPIO	MX_PORTC4_GPIO
	#elif (ICD_CLK_PIN == 5)
		#define MX_ICD_CLK_GPIO	MX_PORTC5_GPIO
	#elif (ICD_CLK_PIN == 6)
		#define MX_ICD_CLK_GPIO	MX_PORTC6_GPIO
	#elif (ICD_CLK_PIN == 7)
		#define MX_ICD_CLK_GPIO	MX_PORTC7_GPIO
	#endif
#elif (ICD_CLK_PORT == PORTD)
	#if   (ICD_CLK_PIN == 0)
		#define MX_ICD_CLK_GPIO	MX_PORTD0_GPIO
	#elif (ICD_CLK_PIN == 1)
		#define MX_ICD_CLK_GPIO	MX_PORTD1_GPIO
	#elif (ICD_CLK_PIN == 2)
		#define MX_ICD_CLK_GPIO	MX_PORTD2_GPIO
	#elif (ICD_CLK_PIN == 3)
		#define MX_ICD_CLK_GPIO	MX_PORTD3_GPIO
	#elif (ICD_CLK_PIN == 4)
		#define MX_ICD_CLK_GPIO	MX_PORTD4_GPIO
	#elif (ICD_CLK_PIN == 5)
		#define MX_ICD_CLK_GPIO	MX_PORTD5_GPIO
	#endif
#endif
#ifndef MX_ICD_CLK_GPIO
	// Nothing defined for that Port/Pin
	// Or we have GPIO numbers anyway (Port G)
	#define MX_ICD_CLK_GPIO ICD_CLK_PIN
#endif

#if   (ICD_DATA_PORT == PORTA)
	#if   (ICD_DATA_PIN == 0)
		#define MX_ICD_DATA_GPIO	MX_PORTA0_GPIO
	#elif (ICD_DATA_PIN == 1)
		#define MX_ICD_DATA_GPIO	MX_PORTA1_GPIO
	#elif (ICD_DATA_PIN == 2)
		#define MX_ICD_DATA_GPIO	MX_PORTA2_GPIO
	#elif (ICD_DATA_PIN == 3)
		#define MX_ICD_DATA_GPIO	MX_PORTA3_GPIO
	#elif (ICD_DATA_PIN == 4)
		#define MX_ICD_DATA_GPIO	MX_PORTA4_GPIO
	#elif (ICD_DATA_PIN == 5)
		#define MX_ICD_DATA_GPIO	MX_PORTA5_GPIO
	#endif
#elif (ICD_DATA_PORT == PORTB)
	#if   (ICD_DATA_PIN == 0)
		#define MX_ICD_DATA_GPIO	MX_PORTB0_GPIO
	#elif (ICD_DATA_PIN == 1)
		#define MX_ICD_DATA_GPIO	MX_PORTB1_GPIO
	#elif (ICD_DATA_PIN == 2)
		#define MX_ICD_DATA_GPIO	MX_PORTB2_GPIO
	#elif (ICD_DATA_PIN == 3)
		#define MX_ICD_DATA_GPIO	MX_PORTB3_GPIO
	#elif (ICD_DATA_PIN == 4)
		#define MX_ICD_DATA_GPIO	MX_PORTB4_GPIO
	#elif (ICD_DATA_PIN == 5)
		#define MX_ICD_DATA_GPIO	MX_PORTB5_GPIO
	#elif (ICD_DATA_PIN == 6)
		#define MX_ICD_DATA_GPIO	MX_PORTB6_GPIO
	#elif (ICD_DATA_PIN == 7)
		#define MX_ICD_DATA_GPIO	MX_PORTB7_GPIO
	#endif
#elif (ICD_DATA_PORT == PORTC)
	#if   (ICD_DATA_PIN == 0)
		#define MX_ICD_DATA_GPIO	MX_PORTC0_GPIO
	#elif (ICD_DATA_PIN == 1)
		#define MX_ICD_DATA_GPIO	MX_PORTC1_GPIO
	#elif (ICD_DATA_PIN == 2)
		#define MX_ICD_DATA_GPIO	MX_PORTC2_GPIO
	#elif (ICD_DATA_PIN == 3)
		#define MX_ICD_DATA_GPIO	MX_PORTC3_GPIO
	#elif (ICD_DATA_PIN == 4)
		#define MX_ICD_DATA_GPIO	MX_PORTC4_GPIO
	#elif (ICD_DATA_PIN == 5)
		#define MX_ICD_DATA_GPIO	MX_PORTC5_GPIO
	#elif (ICD_DATA_PIN == 6)
		#define MX_ICD_DATA_GPIO	MX_PORTC6_GPIO
	#elif (ICD_DATA_PIN == 7)
		#define MX_ICD_DATA_GPIO	MX_PORTC7_GPIO
	#endif
#elif (ICD_DATA_PORT == PORTD)
	#if   (ICD_DATA_PIN == 0)
		#define MX_ICD_DATA_GPIO	MX_PORTD0_GPIO
	#elif (ICD_DATA_PIN == 1)
		#define MX_ICD_DATA_GPIO	MX_PORTD1_GPIO
	#elif (ICD_DATA_PIN == 2)
		#define MX_ICD_DATA_GPIO	MX_PORTD2_GPIO
	#elif (ICD_DATA_PIN == 3)
		#define MX_ICD_DATA_GPIO	MX_PORTD3_GPIO
	#elif (ICD_DATA_PIN == 4)
		#define MX_ICD_DATA_GPIO	MX_PORTD4_GPIO
	#elif (ICD_DATA_PIN == 5)
		#define MX_ICD_DATA_GPIO	MX_PORTD5_GPIO
	#endif
#endif
#ifndef MX_ICD_DATA_GPIO
	// Nothing defined for that Port/Pin
	// Or we have GPIO numbers anyway (Port G)
	#define MX_ICD_DATA_GPIO ICD_DATA_PIN
#endif

#define MX_ICD_DELAY FCI_DELAYBYTE_US(10)

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
			//int_store = INTCON;									//Store interrupt register
			//INTCON = 0;											//Disable all interrupts

			unsigned char dbg_hold = 0;
			unsigned char icd_cmd;
			unsigned int address;
			unsigned int page;
			unsigned char idx;
			char tempdata = 0;

			#ifdef MX_ICD_DEBUG
				printf("MARKER %d\r\n", block_id);
			#endif

			MX_GPIO_IN(MX_ICD_CLK_GPIO);							//Clock is an input
			MX_GPIO_IN(MX_ICD_DATA_GPIO);
			MX_GPIO_OUT(MX_ICD_DATA_GPIO);							//Data is an output
			MX_GPIO_CLR(MX_ICD_DATA_GPIO);							//Data is default low

			if(MX_GPIO_GET(MX_ICD_CLK_GPIO))						//Test to see if clock input is 1
			{
				dbg_mode = dbg_mode | 0x04;							//Enable ICD Pause
			#ifdef MX_ICD_DEBUG_HALT_FLAG
				MX_GPIO_OUT(MX_ICD_DEBUG_HALT_FLAG);
				MX_GPIO_SET(MX_ICD_DEBUG_HALT_FLAG);
			#endif
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
					#ifdef MX_ICD_DEBUG
						printf("\tHOLD %02x, mode %02x\r\n", dbg_hold, dbg_mode);
					#endif
					MX_GPIO_IN(MX_ICD_DATA_GPIO);					//Data is an input target stopped

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
						if (wait_clock(0, 0))						//Wait for clock to go low
							return;
						if (wait_clock(1, 0))			//Wait for clock to go high
							return;

						if (icd_byte_tx(dbg_mode)) dbg_hold = 0;	//Send current ICD mode
						if (icd_byte_tx(block_id)) dbg_hold = 0;	//Send block ID
						if (icd_byte_tx(block_id>>8)) dbg_hold = 0;
					}

					while(dbg_hold)
					{
						icd_cmd = icd_byte_rx();					//Receive command byte
						#ifdef  MX_ICD_DEBUG
							#ifdef MX_ICD_DEBUG_CMD
								if (icd_cmd) printf("\tcmd=%02x\r\n", icd_cmd);
							#endif
						#endif
						switch(icd_cmd)
						{
							case ICD_START:									//Start Command
								dbg_hold = 0;								//Start the target running
								MX_GPIO_OUT(MX_ICD_DATA_GPIO);				//Data is an output
								// MX_GPIO_SET(MX_ICD_DATA_GPIO);				//Data is high
								// Looks like this should be low!
								MX_GPIO_CLR(MX_ICD_DATA_GPIO);
								wait_clock(0, 1);
								#ifdef MX_ICD_DEBUG
									printf("\tICD_START\r\n");
								#endif
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
								#ifdef MX_ICD_DEBUG
									printf("\tICD_SETBP\r\n");
								#endif
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
								#ifdef MX_ICD_DEBUG
									printf("\tICD_CLRBP\r\n");
								#endif
								break;

							case ICD_EN_IBP:					//Enable indexed breakpoints Command

								dbg_mode = dbg_mode | 0x02;					//Enable indexed breakpoints
								#ifdef MX_ICD_DEBUG
									printf("\tICD_EN_IBP\r\n");
								#endif
								break;

							case ICD_DIS_IBP:					//Disable indexed breakpoints Command

								dbg_mode = dbg_mode & 0xFD;					//Disable indexed breakpoints
								#ifdef MX_ICD_DEBUG
									printf("\tICD_DIS_IBP\r\n");
								#endif
								break;

							case ICD_EN_SBP:					//Enable step breakpoint Command

								dbg_mode = dbg_mode | 0x01;					//Enable step breakpoint
								#ifdef MX_ICD_DEBUG
									printf("\tICD_EN_SBP\r\n");
								#endif
								break;

							case ICD_DIS_SBP:					//Disable step breakpoint Command

								dbg_mode = dbg_mode & 0xFE;					//Disable step breakpoint
								#ifdef MX_ICD_DEBUG
									printf("\tICD_DIS_SBP\r\n");
								#endif
								break;

							case ICD_RD_RAM:					//Read Byte Of RAM Command

								address = icd_byte_rx();
								address = address | (icd_byte_rx() << 8);
								// Memory address adjustment due to two byte protocol limit
								// Also assumes initialised .data segment variables are in the same page as .bss un-initialised variables
								page = (unsigned int)&gpio & 0x0FFFF0000;
								address += page;
								if ((address & 0x8000) == 0)
								{
									if (((unsigned int)&gpio & 0x8000) != 0)
									{
										// Address assumed to be in the next 64K page
										address += 0x10000;
									}
								}
								else
								{
									if (((unsigned int)&gpio & 0x8000) == 0)
									{
										// Address assumed to be in the previous 64K page
										address -= 0x10000;
									}
								}
								unsigned char value = read_register(address);
								icd_byte_tx(value);
								#ifdef MX_ICD_DEBUG
									printf("\tICD_RD_RAM %08x = %02x\r\n", address, value);
								#endif
								break;

							case ICD_WR_RAM:					//Write Byte Of RAM Command

								address = icd_byte_rx();
								address = address | (icd_byte_rx() << 8);
								// Memory address adjustment due to two byte protocol limit
								// Also assumes initialised .data segment variables are in the same page as .bss un-initialised variables
								page = (unsigned int)&gpio & 0x0FFFF0000;
								address += page;
								if ((address & 0x8000) == 0)
								{
									if (((unsigned int)&gpio & 0x8000) != 0)
									{
										// Address assumed to be in the next 64K page
										address += 0x10000;
									}
								}
								else
								{
									if (((unsigned int)&gpio & 0x8000) == 0)
									{
										// Address assumed to be in the previous 64K page
										address -= 0x10000;
									}
								}
								write_register(address, icd_byte_rx());
								#ifdef MX_ICD_DEBUG
									printf("\tICD_WR_RAM %08x\r\n", address);
								#endif
								break;

							case ICD_DIS_BPS:					//Clear all breakpoints

								idx=0;	//init BP counter
								while (idx < ICD_NUM_BPS)
								{
									*(brk_pnt + idx) = -1;											//brk_pnt[idx] = -1;
									idx = idx + 1;
								}
								#ifdef MX_ICD_DEBUG
									printf("\tICD_DIS_BPS\r\n");
								#endif
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
								#ifdef  MX_ICD_DEBUG
									printf("\tICD_GET_ID\r\n");
								#endif
								break;

							case ICD_GET_STACK:
								icd_byte_tx(ICD_STACK_SIZE+1);		//+1 because the PPP firmware does not expect the stack pointer return as well
								icd_byte_tx(icd_stack_ptr);
								for (idx=0; idx<ICD_STACK_SIZE; idx++)
								{
									icd_byte_tx(*(icd_stack + idx));											//icd_byte_tx(icd_stack[idx]);
								}
								#ifdef  MX_ICD_DEBUG
									printf("\tICD_GET_STACK\r\n");
								#endif
								break;

							case ICD_RESET:
								#ifdef  MX_ICD_DEBUG
									printf("\tICD_RESET\r\n");
								#endif
								if (dbg_mode != 0)
								{
									// Ignore initial (all?) reset commands
								#ifdef  MX_ICD_DEBUG
									printf("\tBye!\r\n");
									FCI_DELAYINT_S(2);
								#endif
									exit(0);
								}
								
								break;

							default:
								break;
						}
					}
				}
				MX_GPIO_OUT(MX_ICD_DATA_GPIO);				//Data line as output
				MX_GPIO_CLR(MX_ICD_DATA_GPIO);				//Data output low
			}
	#ifdef MX_ICD_DEBUG_HALT_FLAG
		MX_GPIO_CLR(MX_ICD_DEBUG_HALT_FLAG);
	#endif

			// INTCON = int_store;										//Restore all interrupts
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
	unsigned char icd_byte_tx(char data)
	{
		char count, mask;
		#ifdef MX_ICD_DEBUG_TX_FLAG
			MX_GPIO_OUT(MX_ICD_DEBUG_TX_FLAG);
			MX_GPIO_SET(MX_ICD_DEBUG_TX_FLAG);
		#endif
		FC_CAL_GPIO_GET_DDR(MX_ICD_CLK_GPIO);				//Clock line as input
															//Data line as output
		FC_CAL_GPIO_CLR_DDR(MX_ICD_DATA_GPIO);				//Data is 0 RTS

		if (wait_clock(0, 0))								//Wait here for receive to start from host
		{
			#ifdef MX_ICD_DEBUG_TX_FLAG
				MX_GPIO_CLR(MX_ICD_DEBUG_TX_FLAG);
			#endif
			return 255;
		}

		for(count=0; count<8; count++)
		{
			FC_CAL_GPIO_PUT(MX_ICD_DATA_GPIO, (data & 1));
			data = data >> 1;
			if (wait_clock(1, 1))				//Wait for clock to go high
			{
			#ifdef MX_ICD_DEBUG_TX_FLAG
				MX_GPIO_CLR(MX_ICD_DEBUG_TX_FLAG);
			#endif
				return 254;
			}
			if (wait_clock(0, 1))							//Wait for clock to go low
			{
			#ifdef MX_ICD_DEBUG_TX_FLAG
				MX_GPIO_CLR(MX_ICD_DEBUG_TX_FLAG);
			#endif
				return 253;
		}
		}

		FC_CAL_GPIO_GET_DDR(MX_ICD_DATA_GPIO);			//Data line as input end of byte
		if (wait_data(0))									//Wait for byte acknowledge
		{
			#ifdef MX_ICD_DEBUG_TX_FLAG
				MX_GPIO_CLR(MX_ICD_DEBUG_TX_FLAG);
			#endif
				return 252;
		}
		if (wait_clock(1, 1))					//Wait for byte acknowledge end
		{
			#ifdef MX_ICD_DEBUG_TX_FLAG
				MX_GPIO_CLR(MX_ICD_DEBUG_TX_FLAG);
			#endif
				return 251;
		}
		#ifdef MX_ICD_DEBUG_TX_FLAG
			MX_GPIO_CLR(MX_ICD_DEBUG_TX_FLAG);
		#endif
		return 0;											//Success!
	}



	//ICD receive byte Function - Collects a bit banged serial data byte.
	unsigned char icd_byte_rx(void)
	{
		unsigned char data = 0;
		unsigned char count;
		#ifdef MX_ICD_DEBUG_RX_FLAG
			MX_GPIO_OUT(MX_ICD_DEBUG_RX_FLAG);
			MX_GPIO_SET(MX_ICD_DEBUG_RX_FLAG);
		#endif
		FC_CAL_GPIO_GET_DDR(MX_ICD_DATA_GPIO);				//Data line as input
		FC_CAL_GPIO_GET_DDR(MX_ICD_CLK_GPIO);				//Clock line as input

		wait_clock(0, 0);									//Wait here for transmit to start from host

		for(count=0; count<8; count++)						//Receive Byte
		{
			data = data >> 1;
			if (wait_clock(0, 1))							//Wait for clock to go low
			{
				#ifdef MX_ICD_DEBUG_RX_FLAG
					MX_GPIO_CLR(MX_ICD_DEBUG_RX_FLAG);
				#endif
				return 0;
			}
			if (FC_CAL_GPIO_GET(MX_ICD_DATA_GPIO)) 	//Read incoming data on data pin
				data = data | 0x80;

			if (wait_clock(1, 1))				//Wait for clock to go high
			{
				#ifdef MX_ICD_DEBUG_RX_FLAG
					MX_GPIO_CLR(MX_ICD_DEBUG_RX_FLAG);
				#endif
				return 0;
			}
		}

		if (wait_data(1))						//Wait for data to go high
		{
			#ifdef MX_ICD_DEBUG_RX_FLAG
				MX_GPIO_CLR(MX_ICD_DEBUG_RX_FLAG);
			#endif
			return 0;
		}

		if (wait_clock(0, 1))								//Wait for clock to go low
		{
			#ifdef MX_ICD_DEBUG_RX_FLAG
				MX_GPIO_CLR(MX_ICD_DEBUG_RX_FLAG);
			#endif
			return 0;
		}

															//ICD data is an output
		FC_CAL_GPIO_CLR_DDR(MX_ICD_DATA_GPIO);				//ICD data 0 send Ack

		if (wait_clock(1, 1))					//Wait for clock to go high
		{
			#ifdef MX_ICD_DEBUG_RX_FLAG
				MX_GPIO_CLR(MX_ICD_DEBUG_RX_FLAG);
			#endif
			return 0;
		}

		FC_CAL_GPIO_GET_DDR(MX_ICD_DATA_GPIO);			//ICD data clear ack
		#ifdef MX_ICD_DEBUG_RX_FLAG
			MX_GPIO_CLR(MX_ICD_DEBUG_RX_FLAG);
		#endif
		return(data);
	}


	unsigned char wait_clock(char state, char timeout_inc)
	{
		unsigned int timeout = 0;
		if (state)
		{
			// wait for high
			while ((!FC_CAL_GPIO_GET(MX_ICD_CLK_GPIO)) && (timeout < ICD_TIMEOUT))
			{
				MX_ICD_DELAY;
				timeout = timeout +  timeout_inc;		//Increment time out
			}
		}
		else
		{
			// wait for low
			while ((FC_CAL_GPIO_GET(MX_ICD_CLK_GPIO)) && (timeout < ICD_TIMEOUT))
			{
				MX_ICD_DELAY;
				timeout = timeout +  timeout_inc;		//Increment time out
			}
		}
		if (timeout >= ICD_TIMEOUT)					//Has the routine timed out
			return 1;
		return 0;
	}


	unsigned char wait_data(char state)
	{
		unsigned int timeout = 0;
		if (state)
		{
			// wait for high
			while ((!FC_CAL_GPIO_GET(MX_ICD_DATA_GPIO)) && (timeout < ICD_TIMEOUT))
			{
				MX_ICD_DELAY;
				++timeout;		//Increment time out
			}
		}
		else
		{
			// wait for low
			while ((FC_CAL_GPIO_GET(MX_ICD_DATA_GPIO)) && (timeout < ICD_TIMEOUT))
			{
				MX_ICD_DELAY;
				++timeout;		//Increment time out
			}
		}
		if (timeout >= ICD_TIMEOUT)					//Has the routine timed out
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
		// Not something we want to do on a Raspberry Pi!
	}

#ifdef MX_ICD_DEBUG
	#undef MX_ICD_DEBUG
#endif

