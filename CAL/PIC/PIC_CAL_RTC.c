// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B8AFFCE948852155731B40F11264BDA1C19A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5344CC6E59C8D8E617E0741DDECFB0B08FB980C72B0465952FEC73EF747CB37EA6216865A6485619419C4454CCAC6FFE4A13C49364EB7656EAC34482F33F516328938C71085069B189668AFFD2383ED5D2BCAEA307BD0F4A3549D34A0D5AD11F3172025C8F3E170AC936839889923933C8B43B7DB322A51A7FA0264F21FD71235929CCCA4409E3163
// REVISION: 1.0
// GUID: BE42FA34-85FF-45A7-9BFC-32BD893DF0E9
// DATE: 08\08\2022
// DIR: CAL\PIC\PIC_CAL_RTC.c
/*********************************************************************
 *                  Flowcode CAL RTCC File
 *
 * File: PIC_CAL_RTC.c
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
// 18F46J11 Family
// *******************************************************************************************/

#ifdef MX_RTC_TYPE_1


	CALFUNCTION(void, FC_CAL_RTC_Init_, (void))
	{
		RTCCFGbits.RTCEN = 0;					//Disable RTCC

		//Enable RTCC Register Writes.
		EECON2 = 0b01010101;
		EECON2 = 0b10101010;
		RTCCFGbits.RTCWREN = 1;

		RTCCFGbits.RTCEN = 1;					//Enable RTCC
	}


	//Write Functions

	CALFUNCTION(void, FC_CAL_RTC_SetSec_, (MX_UINT8 Data))
	{
		RTCCFG &= 0xFC;				//Min/Sec Selection
		RTCVALL = Data;				//Assign Data Bits
	}

	CALFUNCTION(void, FC_CAL_RTC_SetMin_, (MX_UINT8 Data))
	{
		RTCCFG &= 0xFC;				//Min/Sec Selection
		RTCVALH = Data;				//Assign Data Bits
	}

	CALFUNCTION(void, FC_CAL_RTC_SetHour_, (MX_UINT8 Data))
	{
		RTCCFG &= 0xFC;				//Weekday/Hour Selection
		RTCCFG |= 0x01;
		RTCVALL = Data;				//Assign Data Bits
	}

	CALFUNCTION(void, FC_CAL_RTC_SetWeekDay_, (MX_UINT8 Data))
	{
		RTCCFG &= 0xFC;				//Weekday/Hour Selection
		RTCCFG |= 0x01;
		RTCVALH = Data;				//Assign Data Bits
	}

	CALFUNCTION(void, FC_CAL_RTC_SetDay_, (MX_UINT8 Data))
	{
		RTCCFG &= 0xFC;				//Month/Day Selection
		RTCCFG |= 0x02;
		RTCVALL = Data;				//Assign Data Bits
	}

	CALFUNCTION(void, FC_CAL_RTC_SetMonth_, (MX_UINT8 Data))
	{
		RTCCFG &= 0xFC;				//Month/Day Selection
		RTCCFG |= 0x02;
		RTCVALH = Data;				//Assign Data Bits
	}

	CALFUNCTION(void, FC_CAL_RTC_SetYear_, (MX_UINT8 Data))
	{
		RTCCFG &= 0xFC;				//Year Selection
		RTCCFG |= 0x03;
		RTCVALL = Data;				//Assign Data Bits
	}


	//Read Functions

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetSec_, (void))
	{
		RTCCFG &= 0xFC;				//Min/Sec Selection
		return (RTCVALL);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetMin_, (void))
	{
		RTCCFG &= 0xFC;				//Min/Sec Selection
		return (RTCVALH);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetHour_, (void))
	{
		RTCCFG &= 0xFC;				//Weekday/Hour Selection
		RTCCFG |= 0x01;
		return (RTCVALL);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetWeekDay_, (void))
	{
		RTCCFG &= 0xFC;				//Weekday/Hour Selection
		RTCCFG |= 0x01;
		return (RTCVALH);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetDay_, (void))
	{
		RTCCFG &= 0xFC;				//Month/Day Selection
		RTCCFG |= 0x02;
		return (RTCVALL);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetMonth_, (void))
	{
		RTCCFG &= 0xFC;				//Month/Day Selection
		RTCCFG |= 0x02;
		return (RTCVALH);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetYear_, (void))
	{
		RTCCFG &= 0xFC;				//Year Selection
		RTCCFG |= 0x03;
		return (RTCVALL);
	}


#endif


