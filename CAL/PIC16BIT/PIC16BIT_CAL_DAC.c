// CRC: 5D982BB222882C54AB4AFF20A1590FC484D3178BD0D2510D0F5A64A7853221CAE2C33FABBE4F69A6659399D51781B7B9FD3192051E68C560235B68789FD7E5A59A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF55DFF7B7998B715470E9A076743DE34BCA605D3F80D6C16191079F372B96988FB1A8ED134E200093D404399E185A24E65DEF165D4AB73BC46CEA875AF343AC398674F0475047BC491433AD6E140BD9FF09368807D9AC6CCC2549D34A0D5AD11F3BFE154ED374B5486FFA66492112989B5708C5037F2DBA6FCE00AF8598B7CA62D1079227E43D7E189
// REVISION: 1.0
// GUID: C9DF0D99-3D0D-4A6A-9139-E773BD59EE54
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\PIC16BIT_CAL_DAC.c
/*********************************************************************
 *                  Flowcode CAL DAC File
 *
 * File: PIC16BIT_CAL_DAC.c
 *
 * (c) 2016 Matrix Multimedia Ltd.
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
 * 310516 | BR | Created
 */


#define MX_DAC_CHANNEL_X		CAL_APPEND(MX_DAC_CHANNEL_, MX_DAC_NUM)
#define MX_DAC_VREF_X			CAL_APPEND(MX_DAC_VREF_, MX_DAC_NUM)


CALFUNCTION(void, FC_CAL_DAC_Enable_, (void));
CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output));
CALFUNCTION(void, FC_CAL_DAC_Disable_, (void));



// DAC Type 1 Supported Devices ************************************************************
// 33FJx6GSx0x
// Up to 1 channel
// *******************************************************************************************/

#ifdef MX_DAC_TYPE_1

	CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
	{
		CMPCON1 = 0x0100;						//Setup DAC to be an output

		#if (MX_DAC_VREF_X > 0)					//Setup +Ve Vref
			CMPCON1 = CMPCON1 | Vref;
		#endif

		CMPCON1 = CMPCON1 | 0x8000;				//Enable DAC Module
	}


	CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output))
	{
		CMPDAC1 = Output;
	}


	CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
	{
		CMPCON1 = 0;
	}

#endif



// DAC Type 2 Supported Devices ************************************************************
// 33FJxxxMC804
// Up to 2 channels
// *******************************************************************************************/

#ifdef MX_DAC_TYPE_2

  #if (MX_DAC_CHANNEL_X == 1)

	CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
	{
		DAC1CON = 0x8005;						//Enable DAC Module - divide input clock by 6
		DAC1STAT = DAC1STAT | 0x8000;			//Enable Left DAC Channel - Note DACLP and DACLN are both active
	}


	CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output))
	{
		DAC1LDAT = Output;
	}


	CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
	{
		DAC1STAT = DAC1STAT & 0x00FF;
	}

  #endif

  #if (MX_DAC_CHANNEL_X == 2)

	CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
	{
		DAC1CON = 0x8005;						//Enable DAC Module - divide input clock by 6
		DAC1STAT = DAC1STAT | 0x0080;			//Enable Right DAC Channel - Note DACRP and DACRN are both active
	}


	CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output))
	{
		DAC1RDAT = Output;
	}


	CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
	{
		DAC1STAT = DAC1STAT & 0xFF00;
	}

  #endif

#endif


