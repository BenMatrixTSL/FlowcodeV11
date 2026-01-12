// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A08F72C7C616BF79FDECDF1017F97793DB9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF506BFBED0B9DBA5A998955FA10C3D8361F7F70008CFED0F4DEF73572DFF2DA9E7867977D73B6394DCB0C96F64B73A16A65FD93E4D20B69993039AD86E3567E8DFFD5335CDC9D7414A1C36D0672F8303C9F4596136F1D69FF9549D34A0D5AD11F3EAB7657E42DF688DBB83F199123C90AE7B8EB51F385295B518D34502288D3DAB5F5FD00D1D4C038A
// REVISION: 1.0
// GUID: 45ADA36C-BDCD-4FCD-AAEE-288D31152F7E
// DATE: 08\08\2022
// DIR: CAL\ESP\ESP_CAL_DAC.c
/*********************************************************************
 *                  Flowcode CAL DAC File
 *
 * File: ESP_CAL_DAC.c
 *
 * (c) 2020 Matrix TSL.
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
 * 310720 | LM | Created
 */

#include <driver/dac.h>

#define MX_DAC_CHANNEL_X		CAL_APPEND(MX_DAC_CHANNEL_, MX_DAC_NUM)
#define MX_DAC_VREF_X			CAL_APPEND(MX_DAC_VREF_, MX_DAC_NUM)

CALFUNCTION(void, FC_CAL_DAC_Enable_, (void));
CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output));
CALFUNCTION(void, FC_CAL_DAC_Disable_, (void));

#ifdef MX_DAC_TYPE_1

	CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
	{
		#if (MX_DAC_CHANNEL_X == 1)
			dac_output_enable(DAC_CHANNEL_1);
		#endif

		#if (MX_DAC_CHANNEL_X == 2)
			dac_output_enable(DAC_CHANNEL_2);
		#endif
	}

	CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output))
	{
		#if (MX_DAC_CHANNEL_X == 1)
			dac_output_voltage(DAC_CHANNEL_1, Output);
		#endif

		#if (MX_DAC_CHANNEL_X == 2)
			dac_output_voltage(DAC_CHANNEL_2, Output);
		#endif
	}

	CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
	{
		#if (MX_DAC_CHANNEL_X == 1)
			dac_output_disable(DAC_CHANNEL_1);
		#endif

		#if (MX_DAC_CHANNEL_X == 2)
			dac_output_disable(DAC_CHANNEL_2);
		#endif
	}

#endif

