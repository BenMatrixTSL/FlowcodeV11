// CRC: 5D982BB222882C54AB4AFF20A1590FC484D3178BD0D2510D0F5A64A7853221CAE2C33FABBE4F69A6659399D51781B7B9A3155482ED3F9ACED4A499F07D178F0C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF596E879B66FFDEDC88249E365E42B073C2503F12F1CBE68666C5FF208F33A6A3CC8C1AA26AA74F676AB5F4C636F753AF3DE17534A588E48E284FBAFEFE0009F5A0886037C790CE03C1AFC1B8D48D73712A1B93B6F26A46D89549D34A0D5AD11F379D3C0A087712381D64EA048CAF87321AC98F396ACE9C6E327FDDD94B8F81F9CD157EA94462C8AB8
// REVISION: 1.0
// GUID: 7F248B6E-C0E4-43D9-80E6-2BF6B879F9D6
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\PIC16BIT_CAL_RTC.c
/*********************************************************************
 *                  Flowcode CAL RTCC File
 *
 * File: PIC16BIT_CAL_RTC.c
 *
 * (c) 2017 Matrix Multimedia Ltd.
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
 * 080517 | BR | Created
 */


CALFUNCTION(void, FC_CAL_RTC_Init_, (void));

CALFUNCTION(void, FC_CAL_RTC_SetSec_, (MX_UINT8 Data));
CALFUNCTION(void, FC_CAL_RTC_SetMin_, (MX_UINT8 Data));
CALFUNCTION(void, FC_CAL_RTC_SetHour_, (MX_UINT8 Data));
CALFUNCTION(void, FC_CAL_RTC_SetWeekDay_, (MX_UINT8 Data));
CALFUNCTION(void, FC_CAL_RTC_SetDay_, (MX_UINT8 Data));
CALFUNCTION(void, FC_CAL_RTC_SetMonth_, (MX_UINT8 Data));
CALFUNCTION(void, FC_CAL_RTC_SetYear_, (MX_UINT8 Data));

CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetSec_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetMin_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetHour_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetWeekDay_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetDay_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetMonth_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetYear_, (void));



// RTC Type 1 Supported Devices ************************************************************
// 24FJ128GA310 Family
// *******************************************************************************************/

#ifdef MX_RTC_TYPE_1


	CALFUNCTION(void, FC_CAL_RTC_Init_, (void))
	{
		RCFGCAL = 0;							//Disable RTCC

		//Enable RTCC Register Writes.
		asm volatile ("disi	#5");
		asm volatile ("mov #0x55, w7");			// write 0x55 and 0xAA to
		asm volatile ("mov w7, _NVMKEY"); 		//  NVMKEY to disable
		asm volatile ("mov #0xAA, w8");			// 	write protection
		asm volatile ("mov w8, _NVMKEY");
		asm volatile ("bset _RCFGCAL, #13");	// set the RTCWREN bit
		asm volatile ("nop");
		asm volatile ("nop");

		#ifdef _RTCPWC_RTCLK_POSITION 			//Not all devices have a configurable clock
			RTCPWCbits.RTCLK = MX_RTC_CLOCK;	//Set the RTCC Clock
		#endif

		RCFGCALbits.RTCEN = 1;					//Enable RTCC
	}


	//Write Functions

	CALFUNCTION(void, FC_CAL_RTC_SetSec_, (MX_UINT8 Data))
	{
		unsigned int val;

		RCFGCALbits.RTCPTR = 0;		//Min/Sec Selection
		val = RTCVAL;

		val &= 0xFF00;				//Clear Month Bits
		val |= Data;				//Assign Data Bits

		RCFGCALbits.RTCPTR = 0;		//Min/Sec Selection
		RTCVAL = val;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetMin_, (MX_UINT8 Data))
	{
		unsigned int val;

		RCFGCALbits.RTCPTR = 0;		//Min/Sec Selection
		val = RTCVAL;

		val &= 0x00FF;				//Clear Month Bits
		val |= Data << 8;			//Assign Data Bits

		RCFGCALbits.RTCPTR = 0;		//Min/Sec Selection
		RTCVAL = val;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetHour_, (MX_UINT8 Data))
	{
		unsigned int val;

		RCFGCALbits.RTCPTR = 1;		//Weekday/Hour Selection
		val = RTCVAL;

		val &= 0xFF00;				//Clear Month Bits
		val |= Data;				//Assign Data Bits

		RCFGCALbits.RTCPTR = 1;		//Weekday/Hour Selection
		RTCVAL = val;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetWeekDay_, (MX_UINT8 Data))
	{
		unsigned int val;

		RCFGCALbits.RTCPTR = 1;		//Weekday/Hour Selection
		val = RTCVAL;

		val &= 0x00FF;				//Clear Month Bits
		val |= Data << 8;			//Assign Data Bits

		RCFGCALbits.RTCPTR = 1;		//Weekday/Hour Selection
		RTCVAL = val;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetDay_, (MX_UINT8 Data))
	{
		unsigned int val;

		RCFGCALbits.RTCPTR = 2;		//Month/Day Selection
		val = RTCVAL;

		val &= 0xFF00;				//Clear Month Bits
		val |= Data;				//Assign Data Bits

		RCFGCALbits.RTCPTR = 2;		//Month/Day Selection
		RTCVAL = val;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetMonth_, (MX_UINT8 Data))
	{
		unsigned int val;

		RCFGCALbits.RTCPTR = 2;		//Month/Day Selection
		val = RTCVAL;

		val &= 0x00FF;				//Clear Month Bits
		val |= Data << 8;			//Assign Data Bits

		RCFGCALbits.RTCPTR = 2;		//Month/Day Selection
		RTCVAL = val;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetYear_, (MX_UINT8 Data))
	{
		unsigned int val;

		RCFGCALbits.RTCPTR = 3;		//Year Selection
		val = RTCVAL;

		val &= 0xFF00;				//Clear Month Bits
		val |= Data;				//Assign Data Bits

		RCFGCALbits.RTCPTR = 3;		//Year Selection
		RTCVAL = val;
	}


	//Read Functions

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetSec_, (void))
	{
		MX_UINT8 retval;
		RCFGCALbits.RTCPTR = 0;		//Min/Sec Selection
		retval = RTCVAL;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetMin_, (void))
	{
		MX_UINT8 retval;
		RCFGCALbits.RTCPTR = 0;		//Min/Sec Selection
		retval = RTCVAL >> 8;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetHour_, (void))
	{
		MX_UINT8 retval;
		RCFGCALbits.RTCPTR = 1;		//Weekday/Hour Selection
		retval = RTCVAL;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetWeekDay_, (void))
	{
		MX_UINT8 retval;
		RCFGCALbits.RTCPTR = 1;		//Weekday/Hour Selection
		retval = RTCVAL >> 8;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetDay_, (void))
	{
		MX_UINT8 retval;
		RCFGCALbits.RTCPTR = 2;		//Month/Day Selection
		retval = RTCVAL;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetMonth_, (void))
	{
		MX_UINT8 retval;
		RCFGCALbits.RTCPTR = 2;		//Month/Day Selection
		retval = RTCVAL >> 8;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetYear_, (void))
	{
		MX_UINT8 retval;
		RCFGCALbits.RTCPTR = 3;		//Year Selection
		retval = RTCVAL;
		return (retval);
	}


#endif


// RTC Type 2 Supported Devices ************************************************************
// 24FJ256GA412 Family
// *******************************************************************************************/

#ifdef MX_RTC_TYPE_2


	CALFUNCTION(void, FC_CAL_RTC_Init_, (void))
	{
		RTCCON1Lbits.RTCEN = 0;					//Disable RTCC

		//Enable RTCC Register Writes.
		asm volatile ("DISI #6");
		asm volatile ("MOV #NVMKEY, W1");
		asm volatile ("MOV #0x55, W2");
		asm volatile ("MOV W2, [W1]");
		asm volatile ("MOV #0xAA, W3");
		asm volatile ("MOV W3, [W1]");
		//asm volatile ("BCLR RTCCON1L, #WRLOCK");
		RTCCON1Lbits.WRLOCK = 0;
		asm volatile ("nop");
		asm volatile ("nop");

		RTCCON2Lbits.CLKSEL = MX_RTC_CLOCK;		//Set the RTCC Clock
		RTCCON2Lbits.PS = MX_RTC_PRESCALER;		//Set the RTCC Prescaler
		RTCCON2Lbits.FDIV = MX_RTC_FRACDIV;		//Set the RTCC Fractional Divider
		RTCCON2H = MX_RTC_DIVIDER;				//Set the RTCC Clock Divider 16-bit Value

		RTCCON1Lbits.RTCEN = 1;					//Enable RTCC
	}


	//Write Functions

	CALFUNCTION(void, FC_CAL_RTC_SetSec_, (MX_UINT8 Data))
	{
		TIMEL &= 0x00FF;
		TIMEL |= Data << 8;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetMin_, (MX_UINT8 Data))
	{
		TIMEH &= 0xFF00;
		TIMEH |= Data;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetHour_, (MX_UINT8 Data))
	{
		TIMEH &= 0x00FF;
		TIMEH |= Data << 8;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetWeekDay_, (MX_UINT8 Data))
	{
		DATEL &= 0xFF00;
		DATEL |= Data;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetDay_, (MX_UINT8 Data))
	{
		DATEL &= 0x00FF;
		DATEL |= Data << 8;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetMonth_, (MX_UINT8 Data))
	{
		DATEH &= 0xFF00;
		DATEH |= Data;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetYear_, (MX_UINT8 Data))
	{
		DATEH &= 0x00FF;
		DATEH |= Data << 8;
	}


	//Read Functions

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetSec_, (void))
	{
		MX_UINT8 retval;
		retval = TIMEL >> 8;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetMin_, (void))
	{
		MX_UINT8 retval;
		retval = TIMEH;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetHour_, (void))
	{
		MX_UINT8 retval;
		retval = TIMEH >> 8;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetWeekDay_, (void))
	{
		MX_UINT8 retval;
		retval = DATEL;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetDay_, (void))
	{
		MX_UINT8 retval;
		retval = DATEL >> 8;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetMonth_, (void))
	{
		MX_UINT8 retval;
		retval = DATEH;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetYear_, (void))
	{
		MX_UINT8 retval;
		retval = DATEH >> 8;
		return (retval);
	}


#endif



