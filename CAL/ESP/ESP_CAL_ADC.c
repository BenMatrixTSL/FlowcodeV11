// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A0298EE8C9FC6B4135A3C7E653C47A3E7E0F49ACC266A9D3D79B14CAE55A2DB626ABB24D739BCDFCC30C3CAEE8E7DA69871498BB485154219A073F424834EDD335D44D8362AFB3EA14A67EBF8A447D857875AB7F0C240CA5A620394E67F4665BF519EE712C6DCA7E5701F2A8F6B9AA7C82D2A1042278990451B13A63D6467E264A3C812A96556EBB62549D34A0D5AD11F366CD4E344B91B50C597BAB6CD1F04EB379ED40D293571EA6B64C1696A7E966BD4B005A56FBFB0362
// REVISION: 8.0
// GUID: A3DAB360-833F-4DB0-87AF-FEC4D8C732BB
// DATE: 27\06\2025
// DIR: CAL\ESP\ESP_CAL_ADC.c
/*********************************************************************
 *                  Flowcode CAL ADC File
 *
 * File: ESP_CAL_ADC.c
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
 * 250718 | BR | Created
 * 110423 | BR | Added support for IDF v5.0
 * 151024 | BR | Fixed a problem with 8-bit ADC reads
 * 260625 | MW | Fixed a problem with IDF v5.0 ADC2channels was causing a reset.
 */


//ADC Function Prototypes
CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge));
CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode));
CALFUNCTION(void, FC_CAL_ADC_Disable_, (void));


#ifdef MX_ADC_TOUCH
	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel);
#endif



#if defined(MX_ADC_CHANNEL_32) || defined(MX_ADC_CHANNEL_33) || defined(MX_ADC_CHANNEL_34) || defined(MX_ADC_CHANNEL_35) || defined(MX_ADC_CHANNEL_36) || defined(MX_ADC_CHANNEL_37) || defined(MX_ADC_CHANNEL_38) || defined(MX_ADC_CHANNEL_39) || defined(MX_ADC_CHANNEL_40) || defined(MX_ADC_CHANNEL_41)
	#warning "ADC channels 32 and greater require the use of ADC peripheral 2 which is not available when WIFI or BT is enabled"
#endif




//IDF code for ADC has changed so modify code to suit version
#include "esp_idf_version.h"


#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)	// enable functionality present in IDF v5.0

	#include "esp_adc/adc_oneshot.h"

	#define MX_ADC_EN
	#define MX_ADC_DIS
	#define MX_ADC_INIT(A,B)

	adc_oneshot_unit_handle_t adc_handle;

	// ADC Type 1 Supported Devices IDF 5.x *******************************************************
	// ESP32
	// *******************************************************************************************/
	#ifdef MX_ADC_TYPE_1

		#define MX_ADC_CHA_X		CAL_APPEND(MX_ADC_CHA_, MX_ADC_NUM)

		MX_UINT8 MX_ADC_CHA_X = 1;

		CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
		{
			if (Channel < 32)								//ADC1
			{
				adc_oneshot_unit_init_cfg_t init_config1 = {
						.unit_id = ADC_UNIT_1,
						.ulp_mode = ADC_ULP_MODE_DISABLE
				};
				ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc_handle));
			}
			else											//ADC2
			{
				Channel = Channel - 32;                    //ADC 2 restart from 32 @ index 0
				adc_oneshot_unit_init_cfg_t init_config1 = {
						.unit_id = ADC_UNIT_2,
						.ulp_mode = ADC_ULP_MODE_DISABLE
				};
				ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc_handle));
			}

			adc_oneshot_chan_cfg_t config =
			{
				.bitwidth = ADC_BITWIDTH_DEFAULT,
				.atten = ADC_ATTEN_DB_11   //.atten = 3-Vref
			};
			ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, Channel, &config));			
			MX_ADC_CHA_X = Channel;
		}

		CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
		{
			int Sample = 0;
			ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, MX_ADC_CHA_X, &Sample));

			if (Sample_Mode == 0)
			{
				Sample = Sample >> 4;						//Reduce to 8-bit sample
			}

			return ((MX_UINT16) Sample);
		}

		CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
		{
			ESP_ERROR_CHECK(adc_oneshot_del_unit(adc_handle));
		}

		#ifdef MX_ADC_TOUCH
			#warning "ADC Touch not currently available on ESP32 devices"
		#endif

	#endif

#else

	#include "driver/adc.h"

	#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 4, 0)		// enable functionality present in IDF v4.4

		#define MX_ADC_EN		adc_power_acquire
		#define MX_ADC_DIS		adc_power_release
		#define MX_ADC_INIT(A,B)

	#else													//Original IDF v4.1

		#define MX_ADC_EN			adc_power_on
		#define MX_ADC_DIS			adc_power_off
		#define MX_ADC_INIT(A,B)	adc_gpio_init(A,B)

	#endif


	// ADC Type 1 Supported Devices IDF 4.x *******************************************************
	// ESP32
	// *******************************************************************************************/
	#ifdef MX_ADC_TYPE_1

		#define MX_ADC_PER_X		CAL_APPEND(MX_ADC_PER_, MX_ADC_NUM)
		#define MX_ADC_CHA_X		CAL_APPEND(MX_ADC_CHA_, MX_ADC_NUM)

		MX_UINT8 MX_ADC_PER_X = 1;
		MX_UINT8 MX_ADC_CHA_X = 1;

		CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
		{
			MX_ADC_EN();									//Power up ADC module

			if (Channel < 32)								//ADC1
			{
				MX_ADC_PER_X = 1;							//Set ADC Peripheral

				adc1_config_width(ADC_WIDTH_BIT_12);		//12-bit Samples 0-4095 - 0:9-bit / 1:10-bit / 2:11-bit / 3:12-bit
				adc1_config_channel_atten(Channel, 3-Vref);	//Attenuation 1.1V Max Input - 0:1/1 / 1:1/2.5 / 2:1/6 / 3:1/11 (Default)
				MX_ADC_INIT(1, Channel);					//Initialise ADC pad
			}
			else if (Channel < 64)							//ADC2
			{
				MX_ADC_PER_X = 2;							//Set ADC Peripheral 2
				Channel = Channel - 32;						//ADC 2 restart from 32 @ index 0
				adc2_config_channel_atten(Channel, 3-Vref);	//Attenuation 1.1V Max Input - 0:1/1 / 1:1/2.5 / 2:1/6 / 3:1/11 (Default)
				MX_ADC_INIT(2, Channel);					//Initialise ADC pad
			}
			
			MX_ADC_CHA_X = Channel;
		}

		CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
		{
			MX_SINT16 Sample = 0;

			if (MX_ADC_PER_X == 1)							//ADC1
			{
				Sample = adc1_get_raw(MX_ADC_CHA_X);
			}
			else if (MX_ADC_PER_X == 2)						//ADC2
			{
				adc2_get_raw(MX_ADC_CHA_X, ADC_WIDTH_BIT_12, &Sample);
			}

			if (Sample_Mode == 0)
			{
				Sample = Sample >> 4;						//Reduce to 8-bit sample
			}

			return (Sample);
		}

		CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
		{

			MX_ADC_DIS();									//Power down ADC module

		}

		#ifdef MX_ADC_TOUCH
			#warning "ADC Touch not currently available on ESP32 devices"
		#endif

	#endif

#endif