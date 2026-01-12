// CRC: AE5753800093D2B889297C6B876B6A21749C10AFA09C3FCE4A5F65B0FF76818F298EE8C9FC6B4135A3C7E653C47A3E7E9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5AA3B9850131E3C9EDFF2E1715AA92C3E6E8C07ACAC1CDED29DD97E134AAA8DABFC172D2A6B176D85A6F189CF963FAA3831F6B5922CAEB3BF210FF227180F0E25A46FB4B55F1588F2CB4C929983F98E84E5AD4A7DE3D9775C549D34A0D5AD11F3F3728E78861C5148C2C8CAB80BAECB5BB62C503BEC181E3907369D99911C23D5D43797C197BFDEC5
// REVISION: 1.0
// GUID: A8BECC2B-E773-4F02-A655-A06C0F4A0676
// DATE: 08\08\2022
// DIR: CAL\ARM\ARM_CAL_ADC.c
/*********************************************************************
 *                  Flowcode CAL ADC File
 *
 * File: ARM_CAL_ADC.c
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
 * 060911 | BR | Created
 * 200911 | BR | Updated to include all ADC type files
 * 050312 | BR | Updated to v5.1 CAL Schema
 * 171212 | BR | Moved the code to begin the sample to allow for more optimised ADC readings
 * 030713 | LM | Standard API calls
 * 240414 | LM | Additions to support Touch via ADC
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


/* ADC Type 1 Supported Devices ************************************************************
// AT90SAMS7 Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_1

	char current_channel;

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		current_channel = Channel;

		AT91F_ADC_CfgTimings(AT91C_BASE_ADC, MCKMHz, (Conv_Speed + 1), 50, T_Charge * 1000);
		AT91F_ADC_EnableChannel(AT91C_BASE_ADC, (1 << Channel));

		AT91F_ADC_StartConversion(AT91C_BASE_ADC);				//begin next conversion
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		while(!(AT91F_ADC_GetStatus(AT91C_BASE_ADC) & (1 << current_channel)));

		if (Sample_Mode)
			iRetVal = AT91F_ADC_GetLastConvertedData(AT91C_BASE_ADC);		//10-bit ADC
		else
			iRetVal = AT91F_ADC_GetLastConvertedData(AT91C_BASE_ADC) >> 2;	//8-bit ADC

		AT91F_ADC_StartConversion(AT91C_BASE_ADC);				//begin next conversion

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		AT91F_ADC_DisableChannel(AT91C_BASE_ADC, (1 << current_channel));
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif

