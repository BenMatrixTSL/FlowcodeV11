// CRC: A6459004C43C0517DC6DFC5681C2AD698104299A14C9E1875427A2F7EF4303D9CFD76A29863CD488DE50EA9D9C0AC8D1A3155482ED3F9ACED4A499F07D178F0C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5CDE115BF92B5901691A2605B6BC0BB6FCCBFF72817CF9A10826EF55B18775473C97E9E83A8F29B3E8E9B582A607A914F5211D7975DD32FC3B73BADC3EE9C7A2DA8F42818F9F07D34ABEDE18E121FF394D81183AD4EBFEAAA549D34A0D5AD11F33E31F078F52BB9663A981CE72EBFFFE0BAC17A1D161CA437C1E0961D1CF9D810AE94354B8E74C3BA
// REVISION: 1.0
// GUID: D3E00438-D926-4F33-A15B-D554F4E7ED71
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\PIC32BIT_CAL_RTC.c
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
// 32MX5XX/6XX7XX Family
// *******************************************************************************************/

#ifdef MX_RTC_TYPE_1


	CALFUNCTION(void, FC_CAL_RTC_Init_, (void))
	{
		RTCCONbits.ON = 0;						//Disable RTCC

		//Enable RTCC Register Writes.
		//assume interrupts are disabled
		//assume the DMA controller is suspended
		//assume the device is locked
		//starting critical sequence
		SYSKEY = 0xaa996655; 					//Write first unlock key to SYSKEY
		SYSKEY = 0x556699aa; 					//Write second unlock key to SYSKEY
		RTCCONbits.RTCWREN = 1;  				//Enable RTC Register Writes
		//end critical sequence
		//re-enable interrupts
		//re-enable the DMA controller

		RTCCONbits.RTCCLKSEL = MX_RTC_CLOCK;	//Setup clock - Internal / External
		RTCCONbits.RTCCLKON = 1;				//RTC Clock Is Running
		RTCCONbits.ON = 1;						//Enable RTCC
	}


	//Write Functions

	CALFUNCTION(void, FC_CAL_RTC_SetSec_, (MX_UINT8 Data))
	{
		RTCTIME &= 0xFFFF0000;
		RTCTIME |= Data << 8;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetMin_, (MX_UINT8 Data))
	{
		RTCTIME &= 0xFF00FF00;
		RTCTIME |= (unsigned long) Data << 16;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetHour_, (MX_UINT8 Data))
	{
		RTCTIME &= 0x00FFFF00;
		RTCTIME |= (unsigned long) Data << 24;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetWeekDay_, (MX_UINT8 Data))
	{
		RTCDATE &= 0xFFFFFF00;
		RTCDATE |= Data;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetDay_, (MX_UINT8 Data))
	{
		RTCDATE &= 0xFFFF00FF;
		RTCDATE |= Data << 8;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetMonth_, (MX_UINT8 Data))
	{
		RTCDATE &= 0xFF00FFFF;
		RTCDATE |= (unsigned long) Data << 16;
	}

	CALFUNCTION(void, FC_CAL_RTC_SetYear_, (MX_UINT8 Data))
	{
		RTCDATE &= 0x00FFFFFF;
		RTCDATE |= (unsigned long) Data << 24;
	}


	//Read Functions

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetSec_, (void))
	{
		MX_UINT8 retval;
		retval = RTCTIME >> 8;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetMin_, (void))
	{
		MX_UINT8 retval;
		retval = (unsigned long) RTCTIME >> 16;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetHour_, (void))
	{
		MX_UINT8 retval;
		retval = (unsigned long) RTCTIME >> 24;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetWeekDay_, (void))
	{
		MX_UINT8 retval;
		retval = RTCDATE;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetDay_, (void))
	{
		MX_UINT8 retval;
		retval = RTCDATE >> 8;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetMonth_, (void))
	{
		MX_UINT8 retval;
		retval = (unsigned long) RTCDATE >> 16;
		return (retval);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetYear_, (void))
	{
		MX_UINT8 retval;
		retval = (unsigned long) RTCDATE >> 24;
		return (retval);
	}


#endif



