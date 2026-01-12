// CRC: F9C65A77A483DDF22B438B7FEB8E3C81451B6760FECB07508D29EE770BB95F4719A8F996960012782EE617D4262733209A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF54BB992562D02866D44822913C2D21CEE85865EDAEC687EFE54D504863DDF89ECAA1903BE86B43A552F102A9FEAA52ABAA2B7C8C4C10361372E76F3E3A37A28C461952E44112C748DA24D1B7A6F7059770329886B163E05AC549D34A0D5AD11F3F2B4A9627FB6E29EF0CC6D1C77A68C20807879A43E9890A7E4565E63FDA312627DD474674123A97D
// REVISION: 1.0
// GUID: 3F2E719D-38E7-42B6-A38D-3E31C8A50575
// DATE: 08\08\2022
// DIR: CAL\PICO\PICO_CAL_ICD2.c
/*********************************************************************
 *                  Flowcode CAL ICD2 File
 *
 * File: PICO_CAL_ICD2.c
 *
 * (c) 2016-2021 Matrix TSL
 * http://www.matrixtsl.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
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
 * 200721 | LM | PICO version
 *
 *
 */

#include "hardware/watchdog.h"

	//ICD Clock Port Defines
	#if (ICD_CLK_PORT == 0)
	  #define ICD_CLK_PIN_TRIS 0
	  #define ICD_CLK_PIN_PORT 0
	#endif

	//ICD Data Port Defines
	#if (ICD_DATA_PORT == 0)
	  #define ICD_DATA_PIN_TRIS 0
	  #define ICD_DATA_PIN_PORT 0
	#endif

	#ifndef ICD_CLK_PIN_TRIS
	  #warning "Error: no definition for the ICD clock pin"
	#endif

	#ifndef ICD_DATA_PIN_TRIS
	  #warning "Error: no definition for the ICD data pin"
	#endif


	// set_bit(ICD_CLK_PIN_TRIS, ICD_CLK_PIN)
	// set clock as input
	#define ICD_CLK_IN		FC_CAL_Bit_In_DDR(ICD_CLK_PIN_PORT, ICD_CLK_PIN_TRIS, ICD_CLK_PIN)

	// test_bit(ICD_CLK_PIN_PORT, ICD_CLK_PIN)
	// test the Clock pin
	#define ICD_CLK_READ	(FC_CAL_Bit_In(ICD_CLK_PIN_PORT, ICD_CLK_PIN))

	// set_bit(ICD_DATA_PIN_TRIS, ICD_DATA_PIN)
	// set data as input
	#define ICD_DATA_IN		FC_CAL_Bit_In_DDR(ICD_DATA_PIN_PORT, ICD_DATA_PIN_TRIS, ICD_DATA_PIN)

	// test_bit(ICD_DATA_PIN_PORT, ICD_DATA_PIN)
	// read test data pin
	#define ICD_DATA_READ	(FC_CAL_Bit_In(ICD_DATA_PIN_PORT, ICD_DATA_PIN))

	// clear_bit(ICD_DATA_PIN_TRIS, ICD_DATA_PIN)
	// set data as output (always followed by _LOW or _HIGH hence not required)
	#define ICD_DATA_OUT

	// clear_bit(ICD_DATA_PIN_PORT, ICD_DATA_PIN)
	// set data pin low (and sets as output)
	#define ICD_DATA_LOW	FC_CAL_Bit_Low_DDR(ICD_DATA_PIN_PORT, ICD_DATA_PIN_TRIS, ICD_DATA_PIN)

	// set_bit(ICD_DATA_PIN_PORT,ICD_DATA_PIN)
	// set data pin high (and sets as output)
	#define ICD_DATA_HIGH	FC_CAL_Bit_High_DDR(ICD_DATA_PIN_PORT, ICD_DATA_PIN_TRIS, ICD_DATA_PIN)

	// wait_clock(1<<ICD_CLK_PIN, 0)
	#define WAIT_CLOCK_HIGH			wait_clock(1, 0)
	// wait_clock(0, 0)
	#define WAIT_CLOCK_LOW			wait_clock(0, 0)
	// wait_clock(0, 1)
	#define WAIT_CLOCK_LOW_TIMEOUT	wait_clock(0, 1)
	// wait_clock(1<<ICD_CLK_PIN, 1)
	#define WAIT_CLOCK_HIGH_TIMEOUT	wait_clock(1, 1)
	// wait_data(0)
	#define WAIT_DATA_LOW			wait_data(0)
	// wait_data(1<<ICD_DATA_PIN)
	#define WAIT_DATA_HIGH			wait_data(1)

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
	MX_UINT8 dbg_mode = 0x00;
	MX_UINT8 icd_stack_ptr = 0x00;
	MX_UINT8 ICD_Interrupt_Enable = 0;
	MX_UINT16 ICD_TIMEOUT = 10000;

	//ICD Functions
	void MARKER(MX_SINT16 block_id);
	void PUSH(MX_UINT8 macro_id);
	void POP();
	MX_UINT8 icd_byte_tx(MX_UINT8 data);
	MX_UINT8 icd_byte_rx(void);
	MX_UINT8 wait_clock(MX_UINT8 state, MX_UINT8 timeout_inc);
	MX_UINT8 wait_data(MX_UINT8 state);
	MX_UINT8 read_register(MX_UINT16 address);
	void write_register(MX_UINT16 address, MX_UINT8 data);
	void rst_dev(void);


	#define FC_MARKER(x)		{ if (ICD_Interrupt_Enable == 0)	{ ICD_Interrupt_Enable = 1; MARKER(x); ICD_Interrupt_Enable = 0; } }
	#define ICD_PUSH(x)			{ if (ICD_Interrupt_Enable == 0)	{ ICD_Interrupt_Enable = 1; PUSH(x); ICD_Interrupt_Enable = 0; } }
	#define ICD_POP()			{ if (ICD_Interrupt_Enable == 0)	{ ICD_Interrupt_Enable = 1; POP(); ICD_Interrupt_Enable = 0; } }


	//#warning "'Possible sw stack corruption' messages can safely be ignored for 'MARKER', 'PUSH' and 'POP' ICD functions";


	//ICD Marker Functions - Called at the start of every Flowcode block when ICD is enabled.
	void MARKER(MX_SINT16 block_id)
	{
		MX_UINT8 int_store;

		//if (ICD_Interrupt_Enable == 0)
		//{
//			int_store = INTCON;									//Store interrupt register
//	?		INTCON = 0;											//Disable all interrupts

			MX_UINT8 dbg_hold = 0;
			MX_UINT8 icd_cmd;
			MX_UINT16 address;
			MX_UINT8 idx;
			MX_UINT8 tempdata = 0;

			ICD_CLK_IN;					//Clock is an input
			ICD_DATA_OUT;				//Data is an output
			ICD_DATA_LOW;				//Data is default low

			if(ICD_CLK_READ)				//Test to see if clock input is 1
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
					ICD_DATA_IN;		//Data is an input target stopped

					if (dbg_hold & 0x08)
					{
						WAIT_CLOCK_HIGH;							//Wait indefinitely for the next clock
						WAIT_CLOCK_LOW;								//Wait indefinitely for the next clock
						WAIT_CLOCK_HIGH;							//Wait indefinitely for the next clock
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
								ICD_DATA_OUT;				//Data is an output
								ICD_DATA_HIGH;				//Data is high
								WAIT_CLOCK_LOW_TIMEOUT;
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
								case ICD_RD_EE:					//Read Contents Of EEPROM Command
									address = icd_byte_rx();
									address = address | (icd_byte_rx() << 8);
									icd_byte_tx(eeprom_read(address));
									break;

								case ICD_WR_EE:					//Write Byte to EEPROM Command
									address = icd_byte_rx();
									address = address | (icd_byte_rx() << 8);
									tempdata = icd_byte_rx();
									eeprom_write(address, tempdata);
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
				ICD_DATA_OUT;				//Data line as output
				ICD_DATA_LOW;				//Data output low
			}

//	???		INTCON = int_store;										//Restore all interrupts
		//}
	}



	void PUSH(MX_UINT8 macro_id)
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
	MX_UINT8 icd_byte_tx(MX_UINT8 data)
	{
		MX_UINT8 count, mask;

		ICD_CLK_IN;				//Clock line as input

		ICD_DATA_OUT;			//Data line as output
		ICD_DATA_LOW;			//Data is 0 RTS

		if (WAIT_CLOCK_LOW)								//Wait here for receive to start from host
			return 255;

		for(count=0; count<8; count++)
		{
			mask = data & 0x01;								//Prepare data
			if (mask)										//Write data onto data line
			{
				ICD_DATA_HIGH;
			}
			else
			{
				ICD_DATA_LOW;
			}
			data = data >> 1;
			if (WAIT_CLOCK_HIGH_TIMEOUT)				//Wait for clock to go high
				return 254;
			if (WAIT_CLOCK_LOW_TIMEOUT)							//Wait for clock to go low
				return 253;
		}

		ICD_DATA_IN;			//Data line as input end of byte
		if (WAIT_DATA_LOW)									//Wait for byte acknowledge
				return 252;
		if (WAIT_CLOCK_HIGH_TIMEOUT)					//Wait for byte acknowledge end
				return 251;

		return 0;											//Success!
	}



	//ICD receive byte Function - Collects a bit banged serial data byte.
	MX_UINT8 icd_byte_rx(void)
	{
		MX_UINT8 data = 0;
		MX_UINT8 count;

		ICD_DATA_IN;			//Data line as input
		ICD_CLK_IN;				//Clock line as input

		WAIT_CLOCK_LOW;									//Wait here for transmit to start from host

		for(count=0; count<8; count++)						//Receive Byte
		{
			data = data >> 1;
			if (WAIT_CLOCK_LOW_TIMEOUT)							//Wait for clock to go low
			{
				return 0;
			}
			if (ICD_DATA_READ) 	//Read incoming data on data pin
				data = data | 0x80;

			if (WAIT_CLOCK_HIGH_TIMEOUT)				//Wait for clock to go high
			{
				return 0;
			}
		}

		if (WAIT_DATA_HIGH)						//Wait for data to go high
		{
			return 0;
		}

		if (WAIT_CLOCK_LOW_TIMEOUT)								//Wait for clock to go low
		{
			return 0;
		}

		ICD_DATA_OUT;			//ICD data is an output
		ICD_DATA_LOW;			//ICD data 0 send Ack

		if (WAIT_CLOCK_HIGH_TIMEOUT)					//Wait for clock to go high
		{
			return 0;
		}

		ICD_DATA_IN;			//ICD data clear ack

		return(data);
	}


	MX_UINT8 wait_clock(MX_UINT8 state, MX_UINT8 timeout_inc)
	{
		MX_UINT16 timeout = 0;

		while ((ICD_CLK_READ != state) && (timeout < ICD_TIMEOUT))	//Wait for clk
		{
			// might need a delay here for ARM?
			timeout = timeout +  timeout_inc;		//Increment time out
		}

		if (timeout == ICD_TIMEOUT)					//Has the routine timed out
			return 1;
		return 0;
	}


	MX_UINT8 wait_data(MX_UINT8 state)
	{
		MX_UINT16 timeout = 0;
		while ((ICD_DATA_READ != state) && (timeout < ICD_TIMEOUT))	//Wait for data
		{
			// might need a delay here for ARM?
			timeout = timeout +  1;					//Increment time out
		}

		if (timeout == ICD_TIMEOUT)					//Has the routine timed out
			return 1;
		return 0;
	}


	MX_UINT8 read_register(MX_UINT16 address)
	{
		MX_UINT32 dp = 0x20000000 + address;
		return *(MX_UINT8*)dp;
	}


	void write_register(MX_UINT16 address, MX_UINT8 data)
	{
		MX_UINT32 dp = 0x20000000 + address;
		*(MX_UINT8*)dp = data;
	}


	void rst_dev()
	{
		// Software Reset
		watchdog_reboot(0,0,0);
	}

//End of ICD functionality
