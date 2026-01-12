// CRC: A6459004C43C0517DC6DFC5681C2AD698104299A14C9E1875427A2F7EF4303D9CFD76A29863CD488DE50EA9D9C0AC8D116F8D538056A8D1637947D276E0FE9699A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF56EB68BAB820251E605A03D58F1A86F876ACBAF3B5C8A7993DD769C5BD87D3B67B2C39DD612F45734A44EE8D195FFFC76B65046F1E0F3D990767D266FB17B75C7A886990F7A1C6ECFF22617CE1A45FF2C87C81DE5F77A6D66549D34A0D5AD11F33036ACB5A7F2458C9B3F04E8CF94DE166BAEC97B254F3CD50C9FBA1F01A7E45B08B65E7F68830DD9
// REVISION: 1.0
// GUID: 7C5FB745-D60D-4B8D-8DC2-333647370562
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\PIC32BIT_CAL_IO.c
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

#include "PIC32BIT_CAL_IO.h"

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
