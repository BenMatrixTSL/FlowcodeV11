// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A0298EE8C9FC6B4135A3C7E653C47A3E7E2E5E803813867B467E404F6188BF6473EE9C40F438F233A5A9B11F738DF98E156DA03D7DC51B7E32073F424834EDD335D44D8362AFB3EA14A67EBF8A447D857875AB7F0C240CA5A620394E67F4665BF519EE712C6DCA7E5701F2A8F6B9AA7C82D2A1042278990451B13A63D6467E264A3C812A96556EBB62549D34A0D5AD11F383D0027892EF6C4CC6352C70EE5A551B8397F7D355301E49072F880DBB6DFDD32544F23D1CC1FCAE
// REVISION: 9.0
// GUID: A3DAB360-833F-4DB0-87AF-FEC4D8C732BB
// DATE: 11\11\2026
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
 * 061126 | MW | IDF v5: Enable only creates the ADC unit if not already open, Disable clears the handle.
 *               Fixes abort "adc1 is already in use" when Enable is called per sample (adc_base GetAverageInt/Byte).
 * 061126 | MW | IDF v5: Sample returns factory calibrated counts (adc_cali line/curve fitting, eFuse data).
 *               Raw adc_oneshot_read on ESP32 read ~0.16 V low (0.956 V on pin gave 986 instead of 1186).
 *               Calibrated mV is scaled back to counts against MX_ADC_CAL_VDD_MV so ratiometric components still work.
 *               If no calibration data is available the raw reading is returned as before.
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
	#include "esp_adc/adc_cali.h"						//Factory calibration (fix: raw reads were ~0.16 V low)
	#include "esp_adc/adc_cali_scheme.h"
	#include "soc/soc_caps.h"

	#ifndef MX_ADC_CAL_VDD_MV
		#define MX_ADC_CAL_VDD_MV	3300					//Supply in mV that calibrated readings are scaled against
	#endif
	#define MX_ADC_CAL_MAX_COUNT	((1 << SOC_ADC_RTC_MAX_BITWIDTH) - 1)

	#define MX_ADC_EN
	#define MX_ADC_DIS
	#define MX_ADC_INIT(A,B)

	adc_oneshot_unit_handle_t adc_handle = NULL;
	MX_UINT8 adc_unit_open = 0;						//0 = no unit open, 1 = ADC1, 2 = ADC2 (fix: Enable may be called repeatedly, e.g. adc_base GetAverage)
	adc_cali_handle_t adc_cali_handle = NULL;		//Calibration for the open unit, NULL = not available, use raw

	//Create factory calibration for the unit just opened, leaves handle NULL if the chip has no calibration data
	void FC_CAL_ADC_CaliCreate(adc_unit_t unit)
	{
		adc_cali_handle = NULL;
	#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
		adc_cali_curve_fitting_config_t cali_config = {
			.unit_id = unit,
		#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 1, 0)
			.chan = 0,
		#endif
			.atten = ADC_ATTEN_DB_11,
			.bitwidth = ADC_BITWIDTH_DEFAULT
		};
		if (adc_cali_create_scheme_curve_fitting(&cali_config, &adc_cali_handle) != ESP_OK)
			adc_cali_handle = NULL;
	#elif ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
		adc_cali_line_fitting_config_t cali_config = {
			.unit_id = unit,
			.atten = ADC_ATTEN_DB_11,
			.bitwidth = ADC_BITWIDTH_DEFAULT
		};
		if (adc_cali_create_scheme_line_fitting(&cali_config, &adc_cali_handle) != ESP_OK)
			adc_cali_handle = NULL;
	#endif
	}

	void FC_CAL_ADC_CaliDelete(void)
	{
		if (adc_cali_handle != NULL)
		{
	#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
			adc_cali_delete_scheme_curve_fitting(adc_cali_handle);
	#elif ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
			adc_cali_delete_scheme_line_fitting(adc_cali_handle);
	#endif
			adc_cali_handle = NULL;
		}
	}

	// ADC Type 1 Supported Devices IDF 5.x *******************************************************
	// ESP32
	// *******************************************************************************************/
	#ifdef MX_ADC_TYPE_1

		#define MX_ADC_CHA_X		CAL_APPEND(MX_ADC_CHA_, MX_ADC_NUM)

		MX_UINT8 MX_ADC_CHA_X = 1;

		CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
		{
			MX_UINT8 unit = (Channel < 32) ? 1 : 2;

			if ((adc_handle != NULL) && (adc_unit_open != unit))	//Other ADC unit open - close it first
			{
				FC_CAL_ADC_CaliDelete();
				ESP_ERROR_CHECK(adc_oneshot_del_unit(adc_handle));
				adc_handle = NULL;
				adc_unit_open = 0;
			}

			if (Channel < 32)								//ADC1
			{
				if (adc_handle == NULL)						//Only create the unit if not already open
				{
					adc_oneshot_unit_init_cfg_t init_config1 = {
							.unit_id = ADC_UNIT_1,
							.ulp_mode = ADC_ULP_MODE_DISABLE
					};
					ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc_handle));
					adc_unit_open = 1;
					FC_CAL_ADC_CaliCreate(ADC_UNIT_1);
				}
			}
			else											//ADC2
			{
				Channel = Channel - 32;                    //ADC 2 restart from 32 @ index 0
				if (adc_handle == NULL)						//Only create the unit if not already open
				{
					adc_oneshot_unit_init_cfg_t init_config1 = {
							.unit_id = ADC_UNIT_2,
							.ulp_mode = ADC_ULP_MODE_DISABLE
					};
					ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc_handle));
					adc_unit_open = 2;
					FC_CAL_ADC_CaliCreate(ADC_UNIT_2);
				}
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

			if (adc_cali_handle != NULL)				//Apply factory calibration, return counts against MX_ADC_CAL_VDD_MV
			{
				int mV = 0;
				if (adc_cali_raw_to_voltage(adc_cali_handle, Sample, &mV) == ESP_OK)
				{
					Sample = (int)(((int32_t)mV * MX_ADC_CAL_MAX_COUNT + (MX_ADC_CAL_VDD_MV / 2)) / MX_ADC_CAL_VDD_MV);
					if (Sample > MX_ADC_CAL_MAX_COUNT) Sample = MX_ADC_CAL_MAX_COUNT;
					if (Sample < 0) Sample = 0;
				}
			}

			if (Sample_Mode == 0)
			{
				Sample = Sample >> 4;						//Reduce to 8-bit sample
			}

			return ((MX_UINT16) Sample);
		}

		CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
		{
			if (adc_handle != NULL)							//Only delete if a unit is open
			{
				FC_CAL_ADC_CaliDelete();
				ESP_ERROR_CHECK(adc_oneshot_del_unit(adc_handle));
				adc_handle = NULL;
				adc_unit_open = 0;
			}
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