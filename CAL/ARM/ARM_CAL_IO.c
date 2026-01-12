// CRC: AE5753800093D2B889297C6B876B6A21749C10AFA09C3FCE4A5F65B0FF76818F839C2618FDDE2E5B47BDCC5F9C10ADC19A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF565318245517BB169996477DFDB201D12AAD0212CA55CD8337D2A2F669E08D16F6FBB4576D8DCE60832C962D6A73536D1F041CEC83DC7DDDA305EC477B3138E3AE6843C978B5A80E297EBA07325807C7D9AD75B158F43CD60549D34A0D5AD11F38BBADB03BEACEDC67792491E4BEEEECB0A37B6F83881749CB54CBE7FC75FC27ACB6057F59853FD1A
// REVISION: 1.0
// GUID: FF367F89-BFEA-4B77-AE07-1A025AC708A3
// DATE: 08\08\2022
// DIR: CAL\ARM\ARM_CAL_IO.c
/*********************************************************************
 *                  Flowcode CAL IO File
 *
 * File: PIC_CAL_IO.c
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
 * 160911 | BR | Created
 * 050312 | BR | Updated to v5.1 CAL Schema
 */

#include "ARM_CAL_IO.h"


void FC_CAL_Port_Out__x (MX_UINT8* Port, MX_UINT8 OutMask, MX_UINT8 OutValue)
{
	*Port = (*Port & ~OutMask) | (OutValue & OutMask);
}


void FC_CAL_Port_Out_DDR__x (MX_UINT8* Port, MX_UINT8* Tris, MX_UINT8 OutMask, MX_UINT8 OutValue)
{
	//*Tris = *Tris & (~OutMask);
	*Port = (*Port & ~OutMask) | (OutValue & OutMask);
}


MX_UINT8 FC_CAL_Port_In__x (MX_UINT8* Port, MX_UINT8 InMask, MX_UINT8 Shift)
{
	return (*Port & InMask) >> Shift;
}


MX_UINT8 FC_CAL_Port_In_DDR__x (MX_UINT8* Port, MX_UINT8* Tris, MX_UINT8 InMask, MX_UINT8 Shift)
{
	//*Tris = *Tris | InMask;
	return (*Port & InMask) >> Shift;
}
