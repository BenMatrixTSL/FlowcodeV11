// CRC: F9C65A77A483DDF22B438B7FEB8E3C81451B6760FECB07508D29EE770BB95F47D736E221269B259DD111497F7C88964F9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5E53DF9A560BC5092C25E48F09DE5CFB93E0EA93C1C447A6466C71715354ED55C988F65966A354D0F2E2D0E8F6F78E762EAEA72E86F5807714B590DAF0861EFC0BA88C299C2CE1C5D3102D85AF6CB821301F4F23EDD068422549D34A0D5AD11F3E99EBE1455672D03D91F1F3CA4659DC2F5BA1923B4CB8A56B828D9FAEE7A88865484BB54CD7ADC26
// REVISION: 1.0
// GUID: 0FFF894A-F94F-4D75-8614-0C237E140016
// DATE: 08\08\2022
// DIR: CAL\PICO\PICO_CAL_ADC.c

/*********************************************************************
 *                  Flowcode CAL ADC File
 *
 * File: PICO_CAL_ADC.c
 *
 * (c) 2021 Matrix TSL.
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
 * 280521 | LM | Created
 *
 */


#include "hardware/adc.h"

//ADC Function Prototypes
CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge));
CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode));
CALFUNCTION(void, FC_CAL_ADC_Disable_, (void));

#ifdef MX_ADC_TOUCH
	#warning "ADC Touch not currently available on RP2040 devices"
	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel);
#endif


// ADC Type 1 Supported Devices ************************************************************
// RP2040
// *******************************************************************************************/

#ifdef MX_ADC_TYPE_1

	// ADC mode mask. Bit set when channel is initialised as ADC
	MX_UINT32 MX_ADC_INIT_FLAGS = 0;

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		// nb. Conv_Speed, Vref, T_Charge NOT USED
		MX_UINT32 Mask = 1ul << (Channel);
		if (0 == MX_ADC_INIT_FLAGS)
		{
			// First enable initialises ADC
			adc_init();
		}
		if (!(MX_ADC_INIT_FLAGS & Mask))
		{
			// This channel not yet intialised
			adc_gpio_init(Channel + 26);
			MX_ADC_INIT_FLAGS |= Mask;
		}
		// Select this channel
		adc_select_input(Channel);
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 Sample = adc_read();
		if (0 == Sample_Mode)
		{
			// Convert to 8 bit
			Sample = Sample >> 4;
		}
		return (Sample);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		// Do nothing? As it's called too often?
	}

#endif

