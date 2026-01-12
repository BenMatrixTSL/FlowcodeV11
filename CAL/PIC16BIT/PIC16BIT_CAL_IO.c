// CRC: 5D982BB222882C54AB4AFF20A1590FC484D3178BD0D2510D0F5A64A7853221CAE2C33FABBE4F69A6659399D51781B7B916F8D538056A8D1637947D276E0FE9699A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF547925710CB1C9F051109A2A28A424432296AE398E14B41FF3F8587C8843B92CDD6B17028E41EAB3E2771A3B6B84BEBAAEF8B9C1FF74ECED7B14C0879C23ABA293BFDBD528274C25FACEB025FFF8B820174BD08A0F0502EBA549D34A0D5AD11F36ADABD6E2EA5C45256B464465EB7DE492FDAAF5FD9222558EC447A7A7C3AA69E9E27863BF8B478B1
// REVISION: 1.0
// GUID: AEFB1CEB-9016-472A-A9A6-75E037BA47E3
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\PIC16BIT_CAL_IO.c
/*********************************************************************
 *                  Flowcode CAL IO File
 *
 * File: PIC16BIT_CAL_IO.c
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
 * 270912 | ST | Changed from 8bit to 16bit to allow full port access
 *
 *
 */

#include "PIC16BIT_CAL_IO.h"

void FC_CAL_Port_Out__x (volatile unsigned int* PORT, MX_UINT16 OutMask, MX_UINT16 OutValue)
{
	*PORT = (*PORT & ~OutMask) | (OutValue & OutMask);
}


void FC_CAL_Port_Out_DDR__x (volatile unsigned int* PORT, volatile unsigned int* DDR, MX_UINT16 OutMask, MX_UINT16 OutValue)
{
	*DDR &= (~OutMask);
	*PORT = (*PORT & ~OutMask) | (OutValue & OutMask);
}


MX_UINT16 FC_CAL_Port_In__x (volatile unsigned int* PORT, MX_UINT16 InMask, MX_UINT8 Shift)
{
	return (*PORT & InMask) >> Shift;
}


MX_UINT16 FC_CAL_Port_In_DDR__x (volatile unsigned int* PORT, volatile unsigned int* DDR, MX_UINT16 InMask, MX_UINT8 Shift)
{
	*DDR |= InMask;
	return (*PORT & InMask) >> Shift;
}
