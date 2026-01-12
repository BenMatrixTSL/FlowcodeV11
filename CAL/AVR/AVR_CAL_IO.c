// CRC: 77485F5F6A861F9125D47827B4DE492656C5431E478E8046055FD2257F64F1F3839C2618FDDE2E5B47BDCC5F9C10ADC19A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF50A729AB05BE28625EF47FA25E25AE2AB1471F3DDD8AB19412A016B2A6DC1C018C06D8566BE72DF2A33070DAE1C3ED8CA753F5DC664E2B21AA27126D8D405E7C051E0AFD7FAD6FA95B58550D43A64BCCBAA793FFE9575D57E549D34A0D5AD11F33C98CC4ECAE7BA0855F80E1DE84F575D42CAD7AABAE62BB7BFDF2E6001B9426D00C9FC801055D429
// REVISION: 1.0
// GUID: 5E04D3D0-DAFB-48FF-853C-9F34B1E169D3
// DATE: 08\08\2022
// DIR: CAL\AVR\AVR_CAL_IO.c
/*********************************************************************
 *                  Flowcode CAL IO File
 *
 * File: AVR_CAL_IO.c
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
 * 010911 | SK | Created
 * 050911 | BR | Added 10F and 12F compatible I/O functions
 * 020312 | BR | Updated to v5.1 CAL Schema
 *
 */

#include "AVR_CAL_IO.h"

static void FC_CAL_Port_Out__x (volatile char* PORT, MX_UINT8 OutMask, MX_UINT8 OutValue)
{
	*PORT = (*PORT & ~OutMask) | (OutValue & OutMask);
}


static void FC_CAL_Port_Out_DDR__x (volatile char* PORT, volatile char* DDR, MX_UINT8 OutMask, MX_UINT8 OutValue)
{
	*DDR |= OutMask;
	*PORT = (*PORT & ~OutMask) | (OutValue & OutMask);
}


static MX_UINT8 FC_CAL_Port_In__x (volatile char* PIN, MX_UINT8 InMask, MX_UINT8 Shift)
{
	return (*PIN & InMask) >> Shift;
}


static MX_UINT8 FC_CAL_Port_In_DDR__x (volatile char* PIN, volatile char* DDR, MX_UINT8 InMask, MX_UINT8 Shift)
{
	*DDR &= (~InMask);
	return (*PIN & InMask) >> Shift;
}


static MX_UINT8 FC_CAL_Bit_In__x(volatile char* Port, MX_UINT8 Pin)
{
	#ifdef MX_XMEGA

		//PORT*.IN register always 4 bytes after PORT*.OUT register
		//Confirmed Devices - ATXMEGA A

		*Port++;
		*Port++;
		*Port++;
		*Port++;
		return test_bit(*Port, Pin);

	#else

		//PIN* register always 2 bytes in front of PORT* register
		//Confirmed Devices - ATMEGA324P, ATTINY2313, AT90CAN

		*Port--;
		*Port--;
		return test_bit(*Port, Pin);

	#endif
}
