// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A0478F634975A712457CCBE7D4DA9E6C8317B470248A3E565D848C9455C852E4568940AE31AE32EB4A0C3CAEE8E7DA6987701755DACCBBAD92E358C3573EFFEA993C714E85A4D0A19AE795E48CBBC2BBB19CB0CBF3F66A86D935161DDC827F45B8C5D1AF141BA12F79F6034EE04ED219A9C6EFB67D07065A59E495F16A8437A73B73E43143A8C96C84549D34A0D5AD11F3890E87E6702502CA18B7E3F35A1F6D5F6970B6A5560D69C87C7C0C9FABE651313F9A05C84301D1C0
// REVISION: 7.0
// GUID: 7DBB402F-DCAE-4422-AECA-736BAF57E606
// DATE: 28\04\2025
// DIR: CAL\ESP\ESP_CAL_UART.c
/*********************************************************************
 *                  Flowcode CAL UART File
 *
 * File: ESP_CAL_UART.c
 *
 * (c) 2018 Matrix TSL.
 * http://www.matrixtsl.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
 * 'Company') for its Flowcode graphical programming language is
 * intended and supplied to you, the Company's customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN 'AS IS' CONDITION. NO WARRANTIES,
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
 *
 */

#include "driver/uart.h"

#ifndef MX_UART_SW_DEFS
	#define MX_UART_SW_DEFS

	#define INST_COUNT	25			//----Need to test with other clock speeds----//

	//Work out number of nops for software baud rate
	#define MX_OVERHEAD				(MX_CLK_SPEED / INST_COUNT)
	#define SW_OFFSET				(1000000 / MX_OVERHEAD)

#endif

#define MX_RECEIVE_DELAY 	(MX_CLK_SPEED / 1000000)


//Dynamic function naming based on defines and index number
#define MX_UART_CHANNEL_X	CAL_APPEND(MX_UART_CHANNEL_, MX_UART_NUM)
#define MX_UART_TX_EN_X		CAL_APPEND(MX_UART_UseTX_, MX_UART_NUM)
#define MX_UART_TX_PIN_X	CAL_APPEND(MX_UART_TX_PIN_, MX_UART_NUM)
#define MX_UART_TX_PORT_X	CAL_APPEND(MX_UART_TX_PORT_, MX_UART_NUM)
#define MX_UART_TX_TRIS_X	CAL_APPEND(MX_UART_TX_TRIS_, MX_UART_NUM)
#define MX_UART_RX_EN_X		CAL_APPEND(MX_UART_UseRX_, MX_UART_NUM)
#define MX_UART_RX_PIN_X	CAL_APPEND(MX_UART_RX_PIN_, MX_UART_NUM)
#define MX_UART_RX_PORT_X	CAL_APPEND(MX_UART_RX_PORT_, MX_UART_NUM)
#define MX_UART_RX_TRIS_X	CAL_APPEND(MX_UART_RX_TRIS_, MX_UART_NUM)
#define MX_UART_FLOWEN_X	CAL_APPEND(MX_UART_FLOWEN_, MX_UART_NUM)
#define MX_UART_CTS_PIN_X	CAL_APPEND(MX_UART_CTS_PIN_, MX_UART_NUM)
#define MX_UART_CTS_PORT_X	CAL_APPEND(MX_UART_CTS_PORT_, MX_UART_NUM)
#define MX_UART_CTS_TRIS_X	CAL_APPEND(MX_UART_CTS_TRIS_, MX_UART_NUM)
#define MX_UART_RTS_PIN_X	CAL_APPEND(MX_UART_RTS_PIN_, MX_UART_NUM)
#define MX_UART_RTS_PORT_X	CAL_APPEND(MX_UART_RTS_PORT_, MX_UART_NUM)
#define MX_UART_RTS_TRIS_X	CAL_APPEND(MX_UART_RTS_TRIS_, MX_UART_NUM)
#define MX_UART_DBITS_X		CAL_APPEND(MX_UART_DBITS_, MX_UART_NUM)
#define MX_UART_RETURN_X	CAL_APPEND(MX_UART_RETURN_, MX_UART_NUM)
#define MX_UART_ECHO_X		CAL_APPEND(MX_UART_ECHO_, MX_UART_NUM)
#define MX_UART_INT_X		CAL_APPEND(MX_UART_INT_, MX_UART_NUM)
#define MX_UART_BAUD_X		CAL_APPEND(MX_UART_BAUD_, MX_UART_NUM)
#define MX_UART_CONF_X		CAL_APPEND(uart_config_, MX_UART_NUM)

// No Tx on GPS
#if (MX_UART_TX_EN_X)
	#define MX_UART_TX_X	(MX_UART_TX_PORT_X + MX_UART_TX_PIN_X)
#else
	#define MX_UART_TX_X	UART_PIN_NO_CHANGE
#endif

#if (MX_UART_RX_EN_X)
	#define MX_UART_RX_X	(MX_UART_RX_PORT_X + MX_UART_RX_PIN_X)
#else
	#define MX_UART_RX_X	UART_PIN_NO_CHANGE
#endif

#define UART_Delay_CAL		CAL_APPEND(FC_CAL_UART_Delay_, MX_UART_NUM)
#define UART_HalfDelay_CAL	CAL_APPEND(FC_CAL_UART_HalfDelay_, MX_UART_NUM)
#define UART_Send			CAL_APPEND(FC_CAL_UART_Send_, MX_UART_NUM)
#define UART_Uninit			CAL_APPEND(FC_CAL_UART_Uninit_, MX_UART_NUM)


#if (MX_UART_CHANNEL_X == 0)

	#define MX_SOFT_BAUD_X (1000000 / MX_UART_BAUD_X) - SW_OFFSET

	#if (MX_SOFT_BAUD_X < 1)
		#error "Software UART Baud Rate Not Available At This Clock Speed"
	#endif

#endif


#define portTICK_PERIOD_US (1)


//Component Definitions
#define UART_STATUS_LOOP	0
#define UART_STATUS_TIMEOUT	1
#define UART_STATUS_RXBYTE	2

#if   (MX_UART_CHANNEL_X == 1)&&((MX_UART_INT_X == 1)|| defined (MX_UART0_INT))
	static void uart0_interrupt_task(void);
	static QueueHandle_t uart0_queue;
	static MX_UINT8 uart0_interrupt_enabled = 1;
	static void uart0_event_task(void *pvParameters)
	{
		uart_event_t event;
		MX_UINT16 i;
		while(1) {
			if(xQueueReceive(uart0_queue, (void * )&event, portMAX_DELAY)) {
				switch(event.type) {
					case UART_DATA:
						if (uart0_interrupt_enabled) {for (i=0;i<event.size;i++) { uart0_interrupt_task(); }}
						break;
					default:
						break;
				}
			}
		}
		vTaskDelete(NULL);
	}
#elif (MX_UART_CHANNEL_X == 2)&&((MX_UART_INT_X == 1)|| defined (MX_UART1_INT))
	static void uart1_interrupt_task(void);
	static QueueHandle_t uart1_queue;
	static MX_UINT8 uart1_interrupt_enabled = 1;
	static void uart1_event_task(void *pvParameters)
	{
		uart_event_t event;
		MX_UINT16 i;
		while(1) {
			if(xQueueReceive(uart1_queue, (void * )&event, portMAX_DELAY)) {
				switch(event.type) {
					case UART_DATA:
						if (uart1_interrupt_enabled) {for (i=0;i<event.size;i++) { uart1_interrupt_task(); }}
						break;
					default:
						break;
				}
			}
		}
		vTaskDelete(NULL);
	}
#elif (MX_UART_CHANNEL_X == 3)&&((MX_UART_INT_X == 1)|| defined (MX_UART2_INT))
	static void uart2_interrupt_task(void);
	static QueueHandle_t uart2_queue;
	static MX_UINT8 uart2_interrupt_enabled = 1;
	static void uart2_event_task(void *pvParameters)
	{
		uart_event_t event;
		MX_UINT16 i;
		while(1) {
			if(xQueueReceive(uart2_queue, (void * )&event, portMAX_DELAY)) {
				switch(event.type) {
					case UART_DATA:
						if (uart2_interrupt_enabled) {for (i=0;i<event.size;i++) { uart2_interrupt_task(); }}
						break;
					default:
						break;
				}
			}
		}
		vTaskDelete(NULL);
	}
#endif


#ifndef MX_UART_INT_DEFS
#define MX_UART_INT_DEFS

	#define MX_UART_INT_CH1_FUNC	void uart0_interrupt_task()	{
	#define MX_UART_INT_CH2_FUNC	void uart1_interrupt_task()	{
	#define MX_UART_INT_CH3_FUNC	void uart2_interrupt_task()	{
	#define MX_UART_INT_CH4_FUNC	void uart3_interrupt_task()	{
	#define MX_UART_INT_FUNC_END	}

	#define MX_UART_INT_CH1_DET		(1)
	#define MX_UART_INT_CH2_DET		(1)
	#define MX_UART_INT_CH3_DET		(1)
	#define MX_UART_INT_CH4_DET		(1)

	#define MX_UART_INT_CH1_EN
	#define MX_UART_INT_CH2_EN
	#define MX_UART_INT_CH3_EN
	#define MX_UART_INT_CH4_EN

	#define MX_UART_INT_CH1_DIS
	#define MX_UART_INT_CH2_DIS
	#define MX_UART_INT_CH3_DIS
	#define MX_UART_INT_CH4_DIS

	#define MX_UART_INT_CH1_CLR
	#define MX_UART_INT_CH2_CLR
	#define MX_UART_INT_CH3_CLR
	#define MX_UART_INT_CH4_CLR
	#define MX_UART_INT_CH5_CLR
	#define MX_UART_INT_CH6_CLR
	#define MX_UART_INT_CH7_CLR
	#define MX_UART_INT_CH8_CLR

#endif


//Function Prototypes
CALFUNCTION(void, FC_CAL_UART_Init_, (void));
CALFUNCTION(void, FC_CAL_UART_Uninit_, (void));
CALFUNCTION(void, FC_CAL_UART_Send_, (MX_UINT16 nChar));
CALFUNCTION(MX_SINT16, FC_CAL_UART_Receive_, (MX_UINT8 nTimeout));
CALFUNCTION(void, FC_CAL_UART_Delay_, (void));
CALFUNCTION(void, FC_CAL_UART_HalfDelay_, (void));
CALFUNCTION(void, FC_CAL_UART_UpdateBaud_, (MX_UINT8 new_baud));


#define BUF_SIZE (256)


/* Data Bits
UART_DATA_5_BITS = 0x0,    //word length: 5bits
UART_DATA_6_BITS = 0x1,    //word length: 6bits
UART_DATA_7_BITS = 0x2,    //word length: 7bits
UART_DATA_8_BITS = 0x3,    //word length: 8bits
*/





//Peripheral Functions
CALFUNCTION(void, FC_CAL_UART_Init_, (void))
{
	#if (MX_UART_CHANNEL_X == 0)

		//#error "Software UART channels not currently supported due to lack of microsecond delays!"

		#if (MX_UART_RX_EN_X == 1)
			GET_PORT_PIN (MX_UART_RX_PORT_X, MX_UART_RX_PIN_X);			// Receive pin is a input
		#endif
		#if (MX_UART_TX_EN_X == 1)
			SET_PORT_PIN (MX_UART_TX_PORT_X, MX_UART_TX_PIN_X, 1);		// Transmit pin is default high
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 1)

		#warning "UART channel 1 is used for the debug output, it might be better to use the debug output component or another UART channel."

		#if (MX_UART_DBITS_X == 9)
			#error "Sorry the ESP32 only supports 7 or 8 bit UART packets"
		#endif

		uart_config_t MX_UART_CONF_X = {
			.baud_rate = MX_UART_BAUD_X,
			.data_bits = (MX_UART_DBITS_X - 5),
			.parity    = UART_PARITY_DISABLE,
			.stop_bits = UART_STOP_BITS_1,
			.flow_ctrl = UART_HW_FLOWCTRL_DISABLE
		};

		uart_param_config(UART_NUM_0, &MX_UART_CONF_X);

		#warning "UART channel 1 has remappable functionality but can break programming functionality! Disabled by default in the Flowcode ESP CAL."

		//uart_set_pin(UART_NUM_0, MX_UART_TX_X, MX_UART_RX_X, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);						//TX Pin, RX Pin, RTS Pin, CTS Pin
		uart_set_pin(UART_NUM_0, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);			//DO Not Touch Debug/Programming Pins!

		#if ((MX_UART_INT_X == 1)|| defined (MX_UART0_INT))
			uart_driver_install(UART_NUM_0, BUF_SIZE, 0, 20, &uart0_queue, 0);
			xTaskCreate(uart0_event_task, "uart0_event_task", 2048, NULL, 12, NULL);
		#else
			uart_driver_install(UART_NUM_0, BUF_SIZE, 0, 0, NULL, 0);
		#endif

	#endif

	#if (MX_UART_CHANNEL_X == 2)

		#if (MX_UART_DBITS_X == 9)
			#error "Sorry the ESP32 only supports 7 or 8 bit UART packets"
		#endif

		uart_config_t MX_UART_CONF_X = {
			.baud_rate = MX_UART_BAUD_X,
			.data_bits = (MX_UART_DBITS_X - 5),
			.parity    = UART_PARITY_DISABLE,
			.stop_bits = UART_STOP_BITS_1,
			.flow_ctrl = UART_HW_FLOWCTRL_DISABLE
		};

		uart_param_config(UART_NUM_1, &MX_UART_CONF_X);
		uart_set_pin(UART_NUM_1, MX_UART_2_TX_RPOR, MX_UART_2_RX_RP, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);					//TX Pin, RX Pin, RTS Pin, CTS Pin

		#if ((MX_UART_INT_X == 1)|| defined (MX_UART1_INT))
			uart_driver_install(UART_NUM_1, BUF_SIZE, 0, 20, &uart1_queue, 0);
			xTaskCreate(uart1_event_task, "uart1_event_task", 2048, NULL, 12, NULL);
		#else
			uart_driver_install(UART_NUM_1, BUF_SIZE, 0, 0, NULL, 0);
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 3)

		#if (MX_UART_DBITS_X == 9)
			#error "Sorry the ESP32 only supports 7 or 8 bit UART packets"
		#endif

		uart_config_t MX_UART_CONF_X = {
			.baud_rate = MX_UART_BAUD_X,
			.data_bits = (MX_UART_DBITS_X - 5),
			.parity    = UART_PARITY_DISABLE,
			.stop_bits = UART_STOP_BITS_1,
			.flow_ctrl = UART_HW_FLOWCTRL_DISABLE
		};

		uart_param_config(UART_NUM_2, &MX_UART_CONF_X);

		#ifdef MX_BL6390_PINMAP
			uart_set_pin(UART_NUM_2, 2, 1, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);					//TX Pin, RX Pin, RTS Pin, CTS Pin
		#else
			uart_set_pin(UART_NUM_2, MX_UART_3_TX_RPOR, MX_UART_3_RX_RP, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);					//TX Pin, RX Pin, RTS Pin, CTS Pin
		#endif


		#if ((MX_UART_INT_X == 1)|| defined (MX_UART2_INT))
			uart_driver_install(UART_NUM_2, BUF_SIZE, 0, 20, &uart2_queue, 0);
			xTaskCreate(uart2_event_task, "uart2_event_task", 2048, NULL, 12, NULL);
		#else
			uart_driver_install(UART_NUM_2, BUF_SIZE, 0, 0, NULL, 0);
		#endif
  	#endif

	#if (MX_UART_FLOWEN_X == 1)											// Flowcontrol enabled?
		GET_PORT_PIN (MX_UART_CTS_PORT_X, MX_UART_CTS_PIN_X);			// CTS pin is a input
		#if (MX_UART_INT_X == 1)
			SET_PORT_PIN (MX_UART_RTS_PORT_X, MX_UART_RTS_PIN_X, 0);	// RTS is ready to accept data
		#else
			SET_PORT_PIN (MX_UART_RTS_PORT_X, MX_UART_RTS_PIN_X, 1);	// RTS not ready to accept data
		#endif
	#endif
}


CALFUNCTION(void, FC_CAL_UART_Uninit_, (void))
{
	#if (MX_UART_CHANNEL_X == 0)
		#if (MX_UART_RX_EN_X == 1)
			GET_PORT_PIN (MX_UART_RX_PORT_X, MX_UART_RX_PIN_X);			// Receive pin is a input
		#endif
		#if (MX_UART_TX_EN_X == 1)
			GET_PORT_PIN (MX_UART_TX_PORT_X, MX_UART_TX_PIN_X);			// Transmit pin is a input
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 1)

	#endif

	#if (MX_UART_CHANNEL_X == 2)

   	#endif

	#if (MX_UART_CHANNEL_X == 3)

   	#endif

	#if (MX_UART_FLOWEN_X == 1)											// Flowcontrol enabled?
		GET_PORT_PIN (MX_UART_CTS_PORT_X, MX_UART_CTS_PIN_X);			// CTS pin is a input
		GET_PORT_PIN (MX_UART_RTS_PORT_X, MX_UART_RTS_PIN_X);			// RTS pin is a input
  	#endif
}


CALFUNCTION(void, FC_CAL_UART_Send_, (MX_UINT16 nChar))
{
	#if (MX_UART_TX_EN_X == 1)

		#if (MX_UART_FLOWEN_X == 1)
			while (GET_PORT_PIN(MX_UART_CTS_PORT_X, MX_UART_CTS_PIN_X) != 0);		// Wait until CTS is low
		#endif

		#if (MX_UART_CHANNEL_X == 0)
			MX_UINT8 idx;
			SET_PORT_PIN(MX_UART_TX_PORT_X, MX_UART_TX_PIN_X, 0);					// Send Start bit
			UART_Delay_CAL();
			for (idx = 0; idx < MX_UART_DBITS_X; idx++)
			{
				if (nChar & 0x01)													// Mask off data bit
					SET_PORT_PIN(MX_UART_TX_PORT_X, MX_UART_TX_PIN_X, 1);
				else
					SET_PORT_PIN(MX_UART_TX_PORT_X, MX_UART_TX_PIN_X, 0);
				UART_Delay_CAL();
				nChar = nChar >> 1;													// Move to next data bit
			}
			SET_PORT_PIN(MX_UART_TX_PORT_X, MX_UART_TX_PIN_X, 1);					// Send Stop bit
			UART_Delay_CAL();
		#endif

		#if (MX_UART_CHANNEL_X == 1)
			char cChar = nChar;
			uart_write_bytes(UART_NUM_0, (const char *) &cChar, 1);

		#endif

		#if (MX_UART_CHANNEL_X == 2)
			char cChar = nChar;
			uart_write_bytes(UART_NUM_1, (const char *) &cChar, 1);

		#endif

		#if (MX_UART_CHANNEL_X == 3)
			char cChar = nChar;
			uart_write_bytes(UART_NUM_2, (const char *) &cChar, 1);

		#endif

	#endif
}




CALFUNCTION(MX_SINT16, FC_CAL_UART_Receive_, (MX_UINT8 nTimeout))
{
	#if (MX_UART_RETURN_X == 1)
		MX_UINT16 retVal = 512;
	#else
		MX_UINT8 retVal = 255;
	#endif

	#if (MX_UART_RX_EN_X == 1)

		#if (MX_UART_CHANNEL_X > 0)

			int len = 0;
			uint8_t data[2];

			#if (MX_UART_CHANNEL_X == 1)
				len = uart_read_bytes(UART_NUM_0, data, 1, nTimeout / portTICK_PERIOD_MS);
			#endif

			#if (MX_UART_CHANNEL_X == 2)
				len = uart_read_bytes(UART_NUM_1, data, 1, nTimeout / portTICK_PERIOD_MS);
			#endif

			#if (MX_UART_CHANNEL_X == 3)
				len = uart_read_bytes(UART_NUM_2, data, 1, nTimeout / portTICK_PERIOD_MS);
			#endif

			if (len > 0)
			{
				retVal = data[0];
			}

		#else

			MX_UINT8 delay1 = 0;
			MX_UINT8 regcheck = 0;
			MX_UINT8 bWaitForever = 0;
			MX_UINT8 rxStatus = UART_STATUS_LOOP;
			MX_UINT16 delaycnt;

		  #if (MX_UART_CHANNEL_X == 0)
			MX_UINT8 idx;
		  #else
			MX_UINT8 dummy = 0;
		  #endif

			if (nTimeout == 255)
				bWaitForever = 1;

			#if (MX_UART_FLOWEN_X == 1)
				#if (MX_UART_INT_X == 0)
					SET_PORT_PIN (MX_UART_RTS_PORT_X, MX_UART_RTS_PIN_X, 0);			// Ready to accept data
				#endif
			#endif

			while (rxStatus == UART_STATUS_LOOP)
			{
				if (bWaitForever == 0)
				{
					if (nTimeout == 0)							//don't wait forever, so do timeout thing...
					{
						rxStatus = UART_STATUS_TIMEOUT;
					}
					else
					{
						for (delaycnt = 0; delaycnt < MX_RECEIVE_DELAY; delaycnt++);	//Delay without calling delay function
						delay1 = delay1 + 1;
						if(delay1 == 100)
						{
							nTimeout = nTimeout - 1;
							delay1 = 0;
						}
					}
				}

				#if (MX_UART_CHANNEL_X == 0)
					regcheck = GET_PORT_PIN(MX_UART_RX_PORT_X, MX_UART_RX_PIN_X);	//Test for start bit
					if (regcheck == 0)
						rxStatus = UART_STATUS_RXBYTE;
				#endif
			}

			if (rxStatus == UART_STATUS_RXBYTE)
			{
				#if (MX_UART_CHANNEL_X == 0)

					retVal = 0;
					UART_HalfDelay_CAL();
					UART_Delay_CAL();

					for (idx = 0; idx < MX_UART_DBITS_X; idx++)
					{
						if ( GET_PORT_PIN(MX_UART_RX_PORT_X, MX_UART_RX_PIN_X) )
							retVal = retVal | (0x01 << idx);

						UART_Delay_CAL();
					}

				#endif
			}

		#endif

		#if (MX_UART_ECHO_X == 1)
			UART_Send(retVal);
		#endif

		#if (MX_UART_FLOWEN_X == 1)
			#if (MX_UART_INT_X == 0)
				SET_PORT_PIN(MX_UART_RTS_PORT_X, MX_UART_RTS_PIN_X, 1);		//not ready to accept data
			#endif
		#endif

	#endif

	return (retVal);
}


CALFUNCTION(void, FC_CAL_UART_Delay_, (void))
{
  #if (MX_UART_CHANNEL_X == 0)

	MX_UINT16 delay = MX_SOFT_BAUD_X;

	while (delay > 255)
	{
		delay_us(255);
		delay = delay - 255;
	}
	delay_us(delay);

  #endif
}

CALFUNCTION(void, FC_CAL_UART_HalfDelay_, (void))
{
  #if (MX_UART_CHANNEL_X == 0)

	MX_UINT16 delay = (MX_SOFT_BAUD_X) >> 1;

	while (delay > 255)
	{
		delay_us(255);
		delay = delay - 255;
	}
	delay_us(delay);

  #endif
}


CALFUNCTION(void, FC_CAL_UART_UpdateBaud_, (MX_UINT8 new_baud))
{
	//Baud Rates - Function compatible with hardware mode only
	/*
	0 - 1200
	1 - 2400
	2 - 4800
	3 - 9600
	4 - 19200
	5 - 38400
	6 - 57600
	7 - 115200
	8 - 250000
	*/

	unsigned long new_Baud = 9600;

	if (new_baud > 8)
		return;

	if (new_baud == 0)
		new_Baud = 1200;
	else if (new_baud == 1)
		new_Baud = 2400;
	else if (new_baud == 2)
		new_Baud = 4800;
	else if (new_baud == 3)
		new_Baud = 9600;
	else if (new_baud == 4)
		new_Baud = 19200;
	else if (new_baud == 5)
		new_Baud = 38400;
	else if (new_baud == 6)
		new_Baud = 57600;
	else if (new_baud == 7)
		new_Baud = 115200;
	else if (new_baud == 8)
		new_Baud = 250000;

	uart_config_t MX_UART_CONF_X = {
		.baud_rate = new_Baud,
		.data_bits = (MX_UART_DBITS_X - 5),
		.parity    = UART_PARITY_DISABLE,
		.stop_bits = UART_STOP_BITS_1,
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE
	};

	UART_Uninit();

	#if (MX_UART_CHANNEL_X == 1)

		uart_param_config(UART_NUM_0, &MX_UART_CONF_X);
		/**
		uart_set_pin(UART_NUM_0, MX_UART_TX_X, MX_UART_RX_X, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);			//TX Pin, RX Pin, RTS Pin, CTS Pin
		uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH1_EN;
		#else
			MX_UART_INT_CH1_DIS;
		#endif
		**/
	#endif

	#if (MX_UART_CHANNEL_X == 2)

		uart_param_config(UART_NUM_1, &MX_UART_CONF_X);
		/**
		uart_set_pin(UART_NUM_1, MX_UART_TX_X, MX_UART_RX_X, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);			//TX Pin, RX Pin, RTS Pin, CTS Pin
		uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0);

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH2_EN;
		#else
			MX_UART_INT_CH2_DIS;
		#endif
		**/
	#endif

	#if (MX_UART_CHANNEL_X == 3)

		uart_param_config(UART_NUM_2, &MX_UART_CONF_X);
		/**
		uart_set_pin(UART_NUM_2, MX_UART_TX_X, MX_UART_RX_X, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);			//TX Pin, RX Pin, RTS Pin, CTS Pin
		uart_driver_install(UART_NUM_2, BUF_SIZE * 2, 0, 0, NULL, 0);

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH3_EN;
		#else
			MX_UART_INT_CH3_DIS;
		#endif
		**/
  	#endif

}


