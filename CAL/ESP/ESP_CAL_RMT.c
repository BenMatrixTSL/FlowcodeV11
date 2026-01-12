// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A0EC3636C2091E3D95FDE5985E834040BCD99CBA6AE3D0D6B4AEE753DFFD532AF527C0D65860C3044B711B8143522C2B696889B9906FE47288C77F5D866A51D55CE462FC01712F051FF476466D56CBC986A44F0D87A5B5F77FF69B01A59DC388FD57618789C4DD97825229A1E8ECEA57C00B82875B080218C30FB37E4B9EF2C82A50C235DE3A27B61E549D34A0D5AD11F3E703DF51C8143710714FB4D00BCBA05299BD67B5FEE875D96CFC63B583D3C0065E5746CE888A1719
// REVISION: 3.0
// GUID: 160769D3-AFC9-426C-B4F3-28C967D5F695
// DATE: 13\02\2023
// DIR: CAL\ESP\ESP_CAL_RMT.c
/*********************************************************************
 *                  Flowcode CAL RMT File
 *
 * File: ESP_CAL_RMT.c
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
 * 061120 | BR | Created
 */


#define MX_RMT_CHANNEL_X		MX_RMT_NUM
#define MX_RMT_MODE_X			CAL_APPEND(MX_RMT_MODE_, MX_RMT_NUM)
#define MX_RMT_PIN_X			CAL_APPEND(MX_RMT_PIN_, MX_RMT_NUM)
#define MX_RMT_MEMBLKNUM_X		CAL_APPEND(MX_RMT_MEMBLKNUM_, MX_RMT_NUM)
#define MX_RMT_CLKDIV_X			CAL_APPEND(MX_RMT_CLKDIV_, MX_RMT_NUM)

#define MX_RMT_TXLOOPEN_X		CAL_APPEND(MX_RMT_TXLOOPEN_, MX_RMT_NUM)
#define MX_RMT_TXCARRIEREN_X	CAL_APPEND(MX_RMT_TXCARRIEREN_, MX_RMT_NUM)
#define MX_RMT_TXCARRIERFREQ_X  CAL_APPEND(MX_RMT_TXCARRIERFREQ_, MX_RMT_NUM)
#define MX_RMT_TXCARRIERDUTY_X	CAL_APPEND(MX_RMT_TXCARRIERDUTY_, MX_RMT_NUM)
#define MX_RMT_TXCARRIERLVL_X	CAL_APPEND(MX_RMT_TXCARRIERLVL_, MX_RMT_NUM)
#define MX_RMT_TXIDLEEN_X		CAL_APPEND(MX_RMT_TXIDLEEN_, MX_RMT_NUM)
#define MX_RMT_TXIDLELVL_X		CAL_APPEND(MX_RMT_TXIDLELVL_, MX_RMT_NUM)

#define MX_RMT_RXFILTEREN_X		CAL_APPEND(MX_RMT_RXFILTEREN_, MX_RMT_NUM)
#define MX_RMT_RXFILTERTICKS_X	CAL_APPEND(MX_RMT_RXFILTERTICKS_, MX_RMT_NUM)
#define MX_RMT_IDLETHRESH_X		CAL_APPEND(MX_RMT_IDLETHRESH_, MX_RMT_NUM)

#define MX_RMT_BUFFER_X			CAL_APPEND(MX_RMT_Buffer_, MX_RMT_NUM)
#define MX_RMT_BUFFSZ_X			CAL_APPEND(MX_RMT_BUFFSZ_, MX_RMT_NUM)



//Function Prototypes
CALFUNCTION(void, FC_CAL_RMT_Init_, (void));
CALFUNCTION(void, FC_CAL_RMT_WriteData_, (MX_UINT32 address, MX_UINT32 val));
CALFUNCTION(MX_UINT32, FC_CAL_RMT_ReadData_, (MX_UINT32 address));
CALFUNCTION(void, FC_CAL_RMT_TX_, (MX_UINT8 waitWhileComplete));
CALFUNCTION(MX_UINT8, FC_CAL_RMT_TXBusy_, (void));
CALFUNCTION(void, FC_CAL_RMT_RX_, (void));

#if defined MX_CAL_ESP32

	#include "driver/rmt.h"

	//Data Buffer
	rmt_item32_t MX_RMT_BUFFER_X[MX_RMT_BUFFSZ_X];

#endif


CALFUNCTION(void, FC_CAL_RMT_Init_, (void))
{
	#if defined MX_CAL_ESP32
		rmt_config_t config;
		config.rmt_mode = MX_RMT_MODE_X;
		config.channel = MX_RMT_CHANNEL_X;
		config.gpio_num = MX_RMT_PIN_X;
		config.mem_block_num = MX_RMT_MEMBLKNUM_X;

		#if (MX_RMT_MODE_X == RMT_MODE_TX)
			config.tx_config.loop_en = MX_RMT_TXLOOPEN_X;
			config.tx_config.carrier_en = MX_RMT_TXCARRIEREN_X;
			config.tx_config.carrier_freq_hz = MX_RMT_TXCARRIERFREQ_X;
			config.tx_config.carrier_duty_percent = MX_RMT_TXCARRIERDUTY_X;
			config.tx_config.carrier_level = MX_RMT_TXCARRIERLVL_X;
			config.tx_config.idle_output_en = MX_RMT_TXIDLEEN_X;
			config.tx_config.idle_level = MX_RMT_TXIDLELVL_X;
		#endif

		#if (MX_RMT_MODE_X == RMT_MODE_RX)
			config.rx_config.filter_en = MX_RMT_RXFILTEREN_X;
			config.rx_config.filter_ticks_thresh = MX_RMT_RXFILTERTICKS_X;
			config.rx_config.idle_threshold = 0;
		#endif

		config.clk_div = MX_RMT_CLKDIV_X;

		ESP_ERROR_CHECK(rmt_config(&config));
		ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));
	#endif
}

CALFUNCTION(void, FC_CAL_RMT_TX_, (MX_UINT8 waitWhileComplete))
{
	#if defined MX_CAL_ESP32
		ESP_ERROR_CHECK(rmt_write_items(MX_RMT_CHANNEL_X, MX_RMT_BUFFER_X, MX_RMT_BUFFSZ_X, false));
		//ESP_ERROR_CHECK(rmt_wait_tx_done(MX_RMT_CHANNEL_X, 100));

		if (waitWhileComplete)
		{
			uint32_t status;
			do
			{
				rmt_get_status(MX_RMT_CHANNEL_X, &status);
			}
			while (status & 0x1000000);
		}

	#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_RMT_TXBusy_, (void))
{
	MX_UINT8 ret = 0;
	#if defined MX_CAL_ESP32
		uint32_t status;

		rmt_get_status(MX_RMT_CHANNEL_X, &status);

		if (status & 0x1000000)
		{
			ret = 1;
		}
	#endif
	return ret;
}

CALFUNCTION(void, FC_CAL_RMT_RX_, (void))
{
	#if defined MX_CAL_ESP32

	#endif
}

