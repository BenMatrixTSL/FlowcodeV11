// CRC: 34358081B117C27F7D8358E612878F8E5F343B66182D417818220CB9C07676CF298EE8C9FC6B4135A3C7E653C47A3E7E9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5C1116D9679C1E8382E06F955B954A30147D436B77B14445EC65D1AD217D19D2CB2B3E008ED20CA287EA1A1539909AD04FCE2D3179289F4A426B862A00B504D833F31227621ED3490A34406538B38326787C81DE5F77A6D66549D34A0D5AD11F3E6C247DE5994D3A3B2763EF705BEFE1EC306C3CD4558F18F393652584481258577A9EBB6374D41DE
// REVISION: 1.0
// GUID: CBD1691A-D5AB-432F-8A04-1176BA2DE763
// DATE: 08\08\2022
// DIR: CAL\RPI\RPI_CAL_ADC.c
/*********************************************************************
 *                  Flowcode CAL ADC File
 *
 * File: RPI_CAL_ADC.c
 *
 * (c) 2018 Matrix TSL.
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
 * 160418 | LM | Created as a template file
 */



//ADC Function Prototypes
CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge));
CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode));
CALFUNCTION(void, FC_CAL_ADC_Disable_, ());

#ifdef MX_ADC_SCAN
  CALFUNCTION(void, FC_CAL_ADC_ScanEnable_, (MX_UINT8 Channel, MX_UINT8 Enable));
#endif

#ifdef MX_ADC_TOUCH
	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel));
#endif


//#ifdef MX_ADC_TYPE_1
/*******************************************************************************************
* ADC Type 1
*******************************************************************************************/
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
	}


	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		return 0;
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
//#endif

