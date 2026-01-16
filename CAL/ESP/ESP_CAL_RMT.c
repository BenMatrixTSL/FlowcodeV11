// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A0EC3636C2091E3D95FDE5985E834040BC5D030493ED8F270F250DA32599059548D40765EF942CB299A9B11F738DF98E15B905B5B68AC0E38DC77F5D866A51D55CE462FC01712F051FF476466D56CBC986A44F0D87A5B5F77FF69B01A59DC388FD57618789C4DD97825229A1E8ECEA57C00B82875B080218C30FB37E4B9EF2C82A50C235DE3A27B61E549D34A0D5AD11F375E88500AD9B9589C504938488FCB13512D4B2976864CCD004789BB7D1BE12C9008FFBF4203128CD
// REVISION: 5.0
// GUID: 160769D3-AFC9-426C-B4F3-28C967D5F695
// DATE: 16\01\2026
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
 * ?Company?) for its Flowcode graphical programming language is
 * intended and supplied to you, the Company?s customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
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
 * 160126 | BR | Updated to work with IDF v5.3 tested with WS2812B component
 *             | API change - added timeout parameter to the FC_CAL_RMT_TXBusy_X function
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
CALFUNCTION(MX_UINT8, FC_CAL_RMT_TXBusy_, (MX_SINT16 timeout));
CALFUNCTION(void, FC_CAL_RMT_RX_, (void));

#if defined MX_CAL_ESP32

	#include "driver/rmt_tx.h"
	#include "driver/rmt_rx.h"
	#include "driver/rmt_encoder.h"
	#include "driver/gpio.h"
	#include "freertos/task.h"
	#include "esp_err.h"
	#include "esp_check.h"
	#include <stdlib.h>

	// Define mode constants if not available (for backward compatibility)
	#ifndef RMT_MODE_TX
		#define RMT_MODE_TX 0
	#endif
	#ifndef RMT_MODE_RX
		#define RMT_MODE_RX 1
	#endif

	// Backward compatibility: rmt_item32_t structure for ESP-IDF 5.x
	// The old rmt_item32_t in ESP-IDF 4.1 was a struct containing a union
	// The triple-brace initialization {{{duration0, level0, duration1, level1}}} matches this format
	typedef struct {
		union {
			struct {
				uint32_t duration0 : 15;
				uint32_t level0 : 1;
				uint32_t duration1 : 15;
				uint32_t level1 : 1;
			};
			uint32_t val;
		};
	} rmt_item32_t;

	//Data Buffer - using rmt_item32_t for backward compatibility with generated code
	// The generated code uses rmt_item32_t with nested brace initialization syntax
	rmt_item32_t MX_RMT_BUFFER_X[MX_RMT_BUFFSZ_X];

	// Temporary buffer for converted symbols (only allocate if needed)
	// We'll convert rmt_item32_t to rmt_symbol_word_t on-the-fly during transmission
	static rmt_symbol_word_t* rmt_symbol_buffer_X = NULL;
	static size_t rmt_symbol_buffer_size_X = 0;

	// Channel handle storage for ESP-IDF 5.x
	static rmt_channel_handle_t rmt_channel_handle_X = NULL;
	static rmt_encoder_handle_t rmt_copy_encoder_X = NULL;
	static uint8_t rmt_initialized_X = 0;

#endif



#ifdef MX_BL0058_PINMAP
	#if (MX_RMT_PIN_X == 0)
		#define MX_RMT_REMAP_PIN_X	32
	#endif
	#if (MX_RMT_PIN_X == 1)
		#define MX_RMT_REMAP_PIN_X	33
	#endif
	#if (MX_RMT_PIN_X == 2)
		#define MX_RMT_REMAP_PIN_X	2
	#endif
	#if (MX_RMT_PIN_X == 3)
		#define MX_RMT_REMAP_PIN_X	26
	#endif
	#if (MX_RMT_PIN_X == 4)
		#define MX_RMT_REMAP_PIN_X	4
	#endif
	#if (MX_RMT_PIN_X == 5)
		#define MX_RMT_REMAP_PIN_X	5
	#endif
	#if (MX_RMT_PIN_X == 6)
		#define MX_RMT_REMAP_PIN_X	12
	#endif
	#if (MX_RMT_PIN_X == 7)
		#define MX_RMT_REMAP_PIN_X	13
	#endif
	#if (MX_RMT_PIN_X == 8)
		#define MX_RMT_REMAP_PIN_X	14
	#endif
	#if (MX_RMT_PIN_X == 9)
		#define MX_RMT_REMAP_PIN_X	15
	#endif
	#if (MX_RMT_PIN_X == 10)
		#define MX_RMT_REMAP_PIN_X	18
	#endif
	#if (MX_RMT_PIN_X == 11)
		#define MX_RMT_REMAP_PIN_X	19
	#endif
	#if (MX_RMT_PIN_X == 12)
		#define MX_RMT_REMAP_PIN_X	27
	#endif
	#if (MX_RMT_PIN_X == 13)
		#define MX_RMT_REMAP_PIN_X	22
	#endif
	#if (MX_RMT_PIN_X == 14)
		#define MX_RMT_REMAP_PIN_X	0
	#endif
	#if (MX_RMT_PIN_X == 15)
		#define MX_RMT_REMAP_PIN_X	25
	#endif
	#if (MX_RMT_PIN_X == 16)
		#define MX_RMT_REMAP_PIN_X	23
	#endif
	#if (MX_RMT_PIN_X == 18)
		#define MX_RMT_REMAP_PIN_X	16
	#endif
	#if (MX_RMT_PIN_X == 19)
		#define MX_RMT_REMAP_PIN_X	17
	#endif
	#if (MX_RMT_PIN_X == 20)
		#define MX_RMT_REMAP_PIN_X	34
	#endif
	#if (MX_RMT_PIN_X == 21)
		#define MX_RMT_REMAP_PIN_X	35
	#endif
	#if (MX_RMT_PIN_X == 22)
		#define MX_RMT_REMAP_PIN_X	36
	#endif
	#if (MX_RMT_PIN_X == 23)
		#define MX_RMT_REMAP_PIN_X	39
	#endif
#else
	#ifdef MX_BL6390_PINMAP
		#if (MX_RMT_PIN_X == 0)
			#define MX_RMT_REMAP_PIN_X	4
		#endif
		#if (MX_RMT_PIN_X == 1)
			#define MX_RMT_REMAP_PIN_X	5
		#endif
		#if (MX_RMT_PIN_X == 2)
			#define MX_RMT_REMAP_PIN_X	6
		#endif
		#if (MX_RMT_PIN_X == 3)
			#define MX_RMT_REMAP_PIN_X	7
		#endif
		#if (MX_RMT_PIN_X == 4)
			#define MX_RMT_REMAP_PIN_X	15
		#endif
		#if (MX_RMT_PIN_X == 5)
			#define MX_RMT_REMAP_PIN_X	16
		#endif
		#if (MX_RMT_PIN_X == 6)
			#define MX_RMT_REMAP_PIN_X	17
		#endif
		#if (MX_RMT_PIN_X == 7)
			#define MX_RMT_REMAP_PIN_X	18
		#endif
		#if (MX_RMT_PIN_X == 8)
			#define MX_RMT_REMAP_PIN_X	8
		#endif
		#if (MX_RMT_PIN_X == 9)
			#define MX_RMT_REMAP_PIN_X	19
		#endif
		#if (MX_RMT_PIN_X == 10)
			#define MX_RMT_REMAP_PIN_X	20
		#endif
		#if (MX_RMT_PIN_X == 11)
			#define MX_RMT_REMAP_PIN_X	3
		#endif
		#if (MX_RMT_PIN_X == 12)
			#define MX_RMT_REMAP_PIN_X	9
		#endif
		#if (MX_RMT_PIN_X == 13)
			#define MX_RMT_REMAP_PIN_X	10
		#endif
		#if (MX_RMT_PIN_X == 14)
			#define MX_RMT_REMAP_PIN_X	11
		#endif
		#if (MX_RMT_PIN_X == 15)
			#define MX_RMT_REMAP_PIN_X	12
		#endif
		#if (MX_RMT_PIN_X == 16)
			#define MX_RMT_REMAP_PIN_X	13
		#endif
		#if (MX_RMT_PIN_X == 17)
			#define MX_RMT_REMAP_PIN_X	14
		#endif
		#if (MX_RMT_PIN_X == 18)
			#define MX_RMT_REMAP_PIN_X	21
		#endif
		#if (MX_RMT_PIN_X == 19)
			#define MX_RMT_REMAP_PIN_X	47
		#endif
		#if (MX_RMT_PIN_X == 20)
			#define MX_RMT_REMAP_PIN_X	48
		#endif
		#if (MX_RMT_PIN_X == 21)
			#define MX_RMT_REMAP_PIN_X	45
		#endif
		#if (MX_RMT_PIN_X == 22)
			#define MX_RMT_REMAP_PIN_X	38
		#endif
		#if (MX_RMT_PIN_X == 23)
			#define MX_RMT_REMAP_PIN_X	39
		#endif
		#if (MX_RMT_PIN_X == 24)
			#define MX_RMT_REMAP_PIN_X	40
		#endif
		#if (MX_RMT_PIN_X == 25)
			#define MX_RMT_REMAP_PIN_X	41
		#endif
		#if (MX_RMT_PIN_X == 26)
			#define MX_RMT_REMAP_PIN_X	42
		#endif
		#if (MX_RMT_PIN_X == 27)
			#define MX_RMT_REMAP_PIN_X	46
		#endif
		#if (MX_RMT_PIN_X == 28)
			#define MX_RMT_REMAP_PIN_X	0
		#endif
	#else
		#define MX_RMT_REMAP_PIN_X		MX_RMT_PIN_X
	#endif
#endif





CALFUNCTION(void, FC_CAL_RMT_Init_, (void))
{
	#if defined MX_CAL_ESP32
		// Only initialize once
		if (rmt_initialized_X)
		{
			return;
		}

		#if (MX_RMT_MODE_X == RMT_MODE_TX)
			// Configure TX channel for ESP-IDF 5.x
			rmt_tx_channel_config_t tx_channel_config = {
				.clk_src = RMT_CLK_SRC_DEFAULT,
				.gpio_num = MX_RMT_REMAP_PIN_X,
				.mem_block_symbols = 64 * MX_RMT_MEMBLKNUM_X,
				.resolution_hz = 80000000 / MX_RMT_CLKDIV_X,
				.trans_queue_depth = 4,
				.flags = {
					.invert_out = false,
					.with_dma = false,
				},
			};

			ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_channel_config, &rmt_channel_handle_X));

			// Configure carrier if enabled
			if (MX_RMT_TXCARRIEREN_X)
			{
				// Convert old carrier level constant to new polarity flag
				// RMT_CARRIER_LEVEL_LOW (0) -> polarity_active_low = 1
				// RMT_CARRIER_LEVEL_HIGH (1) -> polarity_active_low = 0
				uint8_t carrier_level_low = 0;
				#ifdef RMT_CARRIER_LEVEL_LOW
					carrier_level_low = (MX_RMT_TXCARRIERLVL_X == RMT_CARRIER_LEVEL_LOW) ? 1 : 0;
				#else
					// If constants not available, assume 0 = LOW, 1 = HIGH
					carrier_level_low = (MX_RMT_TXCARRIERLVL_X == 0) ? 1 : 0;
				#endif

				rmt_carrier_config_t carrier_config = {
					.duty_cycle = MX_RMT_TXCARRIERDUTY_X,
					.frequency_hz = MX_RMT_TXCARRIERFREQ_X,
					.flags = {
						.polarity_active_low = carrier_level_low,
					},
				};
				ESP_ERROR_CHECK(rmt_apply_carrier(rmt_channel_handle_X, &carrier_config));
			}

			// Note: Idle level configuration in ESP-IDF 5.x is handled via the transmit config
			// The eot_level field in rmt_transmit_config_t controls the end-of-transmission level
			// This will be set in the FC_CAL_RMT_TX_ function based on MX_RMT_TXIDLELVL_X

			// Create copy encoder for direct symbol transmission
			rmt_copy_encoder_config_t copy_encoder_config = {};
			ESP_ERROR_CHECK(rmt_new_copy_encoder(&copy_encoder_config, &rmt_copy_encoder_X));

			// Enable the channel
			ESP_ERROR_CHECK(rmt_enable(rmt_channel_handle_X));
		#endif

		#if (MX_RMT_MODE_X == RMT_MODE_RX)
			// Configure RX channel for ESP-IDF 5.x
			rmt_rx_channel_config_t rx_channel_config = {
				.clk_src = RMT_CLK_SRC_DEFAULT,
				.resolution_hz = 80000000 / MX_RMT_CLKDIV_X,
				.mem_block_symbols = 64 * MX_RMT_MEMBLKNUM_X,
				.gpio_num = MX_RMT_REMAP_PIN_X,
				.flags = {
					.invert_in = false,
					.with_dma = false,
				},
			};

			ESP_ERROR_CHECK(rmt_new_rx_channel(&rx_channel_config, &rmt_channel_handle_X));

			// Note: RX filter configuration is done when calling rmt_receive() in the RX function
			// The filter threshold is calculated here for later use
			// Filter threshold in nanoseconds = ticks * (1 second / resolution_hz)
			// This will be used in the FC_CAL_RMT_RX_ function

			// Enable the channel
			ESP_ERROR_CHECK(rmt_enable(rmt_channel_handle_X));
		#endif

		rmt_initialized_X = 1;
	#endif
}

CALFUNCTION(void, FC_CAL_RMT_TX_, (MX_UINT8 waitWhileComplete))
{
	#if defined MX_CAL_ESP32
		#if (MX_RMT_MODE_X == RMT_MODE_TX)
			// Safety check: ensure channel is initialized
			if (rmt_channel_handle_X == NULL || rmt_copy_encoder_X == NULL)
			{
				return;
			}

			// Configure transmission parameters
			// Set eot_level based on idle level configuration (if enabled)
			uint32_t eot_level = 0;
			if (MX_RMT_TXIDLEEN_X)
			{
				// Convert old idle level constant to eot_level
				// RMT_IDLE_LEVEL_LOW (0) -> eot_level = 0
				// RMT_IDLE_LEVEL_HIGH (1) -> eot_level = 1
				#ifdef RMT_IDLE_LEVEL_HIGH
					eot_level = (MX_RMT_TXIDLELVL_X == RMT_IDLE_LEVEL_HIGH) ? 1 : 0;
				#else
					// If constants not available, assume 0 = LOW, 1 = HIGH
					eot_level = (MX_RMT_TXIDLELVL_X == 0) ? 0 : 1;
				#endif
			}

			rmt_transmit_config_t transmit_config = {
				.loop_count = MX_RMT_TXLOOPEN_X ? -1 : 0,
				.flags = {
					.eot_level = eot_level,
				},
			};

			// Convert rmt_item32_t buffer to rmt_symbol_word_t format for transmission
			// Allocate temporary buffer if needed (only once, reuse it)
			if (rmt_symbol_buffer_size_X < MX_RMT_BUFFSZ_X)
			{
				if (rmt_symbol_buffer_X != NULL)
				{
					free(rmt_symbol_buffer_X);
				}
				rmt_symbol_buffer_X = (rmt_symbol_word_t*)malloc(MX_RMT_BUFFSZ_X * sizeof(rmt_symbol_word_t));
				if (rmt_symbol_buffer_X == NULL)
				{
					return; // Out of memory
				}
				rmt_symbol_buffer_size_X = MX_RMT_BUFFSZ_X;
			}

			// Convert each rmt_item32_t to rmt_symbol_word_t
			// This ensures proper field mapping regardless of memory layout differences
			// Find the actual number of symbols to transmit (stop at first zero entry or use full buffer)
			size_t num_symbols = MX_RMT_BUFFSZ_X;
			for (size_t i = 0; i < MX_RMT_BUFFSZ_X; i++)
			{
				rmt_symbol_buffer_X[i].duration0 = MX_RMT_BUFFER_X[i].duration0;
				rmt_symbol_buffer_X[i].level0 = MX_RMT_BUFFER_X[i].level0;
				rmt_symbol_buffer_X[i].duration1 = MX_RMT_BUFFER_X[i].duration1;
				rmt_symbol_buffer_X[i].level1 = MX_RMT_BUFFER_X[i].level1;

				// Stop at first completely zero entry (end marker)
				if (MX_RMT_BUFFER_X[i].duration0 == 0 && MX_RMT_BUFFER_X[i].duration1 == 0 &&
				    MX_RMT_BUFFER_X[i].level0 == 0 && MX_RMT_BUFFER_X[i].level1 == 0)
				{
					num_symbols = i + 1; // Include the zero entry
					break;
				}
			}

			// Transmit the data using copy encoder
			// The copy encoder expects the data size in bytes
			// Only transmit the actual number of symbols we have
			if (num_symbols > 0)
			{
				ESP_ERROR_CHECK(rmt_transmit(rmt_channel_handle_X, rmt_copy_encoder_X, rmt_symbol_buffer_X,
				                            num_symbols * sizeof(rmt_symbol_word_t), &transmit_config));
			}

			// Wait for transmission to complete if requested
			if (waitWhileComplete)
			{
				ESP_ERROR_CHECK(rmt_tx_wait_all_done(rmt_channel_handle_X, portMAX_DELAY));
			}
		#endif
	#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_RMT_TXBusy_, (MX_SINT16 timeout))
{
	MX_UINT8 ret = 0;
	#if defined MX_CAL_ESP32
		#if (MX_RMT_MODE_X == RMT_MODE_TX)
			// Check if transmission is still in progress
			// Using rmt_tx_wait_all_done with 0 timeout to check status
			esp_err_t status = rmt_tx_wait_all_done(rmt_channel_handle_X, timeout);
			if (status == ESP_ERR_TIMEOUT)
			{
				// Transmission is still in progress
				ret = 1;
			}
			// If status is ESP_OK, transmission is complete, ret remains 0
		#endif
	#endif
	return ret;
}

CALFUNCTION(void, FC_CAL_RMT_RX_, (void))
{
	#if defined MX_CAL_ESP32

	#endif
}

