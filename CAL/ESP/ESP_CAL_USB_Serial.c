// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A01CCAA1F64DCE9D54FCE71B97CFC36836EAB9DC0344E07D5326A66CC0150DD556B6336C11BE63C7B23E6A7110B5081D39796EDD611F6757020C3CAEE8E7DA698717AEC8DEA3E94A26D5551A8C932F95295A74BA5858CEB6B2FC6B44983F207D2FC772EDF2C2ADBA2F259EE6410350CF61ACC09A8C56EFC78E404DCC1194350755B329AD74E31A3E088870B4F6FCE361038E938B6AA73A9466549D34A0D5AD11F37BA1E22E3BD6FBA2AE42A364CE938ECC8EAF1ED57043375C7BE859FCFFBFD79E33DBA559DB338738
// REVISION: 2.0
// GUID: 73076598-9D0F-4FB3-A92E-1C7892627F14
// DATE: 11\07\2025
// DIR: CAL\ESP\ESP_CAL_USB_Serial.c

/*********************************************************************
 *              Flowcode CAL USB Serial CDC Comms
 *
 * File: ESP_CAL_USB_Serial.c
 *
 * (c) 2025 Matrix TSL
 * http://www.matrixTSL.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
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
 * 100725 | BR | Created
 *
 */


#define MX_USB_SERIAL_ENUM_TOUTEN_X     	CAL_APPEND(MX_USB_SERIAL_ENUM_TOUTEN_, MX_USB_SERIAL_NUM)
#define MX_USB_SERIAL_ENUM_TOUT_X     		CAL_APPEND(MX_USB_SERIAL_ENUM_TOUT_, MX_USB_SERIAL_NUM)
#define MX_USB_SERIAL_ENUM_RETURN_X     	CAL_APPEND(MX_USB_SERIAL_ENUM_RETURN_, MX_USB_SERIAL_NUM)



#include <stdint.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "tinyusb.h"
#include "tusb_cdc_acm.h"



static const char *TAG = "example";
static uint8_t buf[CONFIG_TINYUSB_CDC_RX_BUFSIZE + 1];

void tinyusb_cdc_rx_callback(int itf, cdcacm_event_t *event)
{
    /* initialization */
    size_t rx_size = 0;

    /* read */
    esp_err_t ret = tinyusb_cdcacm_read(itf, buf, CONFIG_TINYUSB_CDC_RX_BUFSIZE, &rx_size);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Data from channel %d:", itf);
        ESP_LOG_BUFFER_HEXDUMP(TAG, buf, rx_size, ESP_LOG_INFO);
    } else {
        ESP_LOGE(TAG, "Read error");
    }

    /* write back */
    tinyusb_cdcacm_write_queue(itf, buf, rx_size);
    tinyusb_cdcacm_write_flush(itf, 0);
}

void tinyusb_cdc_line_state_changed_callback(int itf, cdcacm_event_t *event)
{
    int dtr = event->line_state_changed_data.dtr;
    int rts = event->line_state_changed_data.rts;
    ESP_LOGI(TAG, "Line state changed on channel %d: DTR:%d, RTS:%d", itf, dtr, rts);
}


CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_Initialise_, ())
{

    ESP_LOGI(TAG, "USB initialization");
    const tinyusb_config_t tusb_cfg = {
        .device_descriptor = NULL,
        .string_descriptor = NULL,
        .external_phy = false,
        .configuration_descriptor = NULL,
    };

    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));

    tinyusb_config_cdcacm_t acm_cfg = {
        .usb_dev = TINYUSB_USBDEV_0,
        .cdc_port = TINYUSB_CDC_ACM_0,
        .rx_unread_buf_sz = 64,
        .callback_rx = &tinyusb_cdc_rx_callback, // the first way to register a callback
        .callback_rx_wanted_char = NULL,
        .callback_line_state_changed = NULL,
        .callback_line_coding_changed = NULL
    };

    ESP_ERROR_CHECK(tusb_cdc_acm_init(&acm_cfg));
    /* the second way to register a callback */
    ESP_ERROR_CHECK(tinyusb_cdcacm_register_callback(
                        TINYUSB_CDC_ACM_0,
                        CDC_EVENT_LINE_STATE_CHANGED,
                        &tinyusb_cdc_line_state_changed_callback));

	#if (CONFIG_TINYUSB_CDC_COUNT > 1)
		acm_cfg.cdc_port = TINYUSB_CDC_ACM_1;
		ESP_ERROR_CHECK(tusb_cdc_acm_init(&acm_cfg));
		ESP_ERROR_CHECK(tinyusb_cdcacm_register_callback(
							TINYUSB_CDC_ACM_1,
							CDC_EVENT_LINE_STATE_CHANGED,
							&tinyusb_cdc_line_state_changed_callback));
	#endif

    ESP_LOGI(TAG, "USB initialization DONE");
	return 0;

}


CALFUNCTION(MX_UINT16, FC_CAL_USB_Serial_ReadByte_, (MX_UINT8 timeout_ms))
{
	MX_UINT16 retval = 255;
	MX_UINT8 inner = 0;

	if (MX_USB_SERIAL_ENUM_RETURN_X)
		retval = 512;

	if (timeout_ms == 0)
	{
		timeout_ms = 1;
		inner = 98;
	}

	return retval;
}


CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendByte_, (MX_UINT8 FCL_DATA))
{
	buf[0] = FCL_DATA;

    tinyusb_cdcacm_write_queue(TINYUSB_CDC_ACM_0, buf, 1);
    tinyusb_cdcacm_write_flush(TINYUSB_CDC_ACM_0, 0);

  	return (0);
}



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendByteArray_, (MX_UINT8 *FCL_DATA, MX_UINT16 FCLsz_DATA, MX_UINT8 FCL_NUMBYTES))
{

    tinyusb_cdcacm_write_queue(TINYUSB_CDC_ACM_0, FCL_DATA, FCL_NUMBYTES);
    tinyusb_cdcacm_write_flush(TINYUSB_CDC_ACM_0, 0);

	return (0);
}




CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendString_, (MX_CHAR *FCL_DATA, MX_UINT16 FCLsz_DATA))
{

  	MX_UINT8 FCL_LENGTH;

	FCL_LENGTH = FCI_GETLENGTH(FCL_DATA, FCLsz_DATA);

	tinyusb_cdcacm_write_queue(TINYUSB_CDC_ACM_0, FCL_DATA, FCL_LENGTH);
    tinyusb_cdcacm_write_flush(TINYUSB_CDC_ACM_0, 0);

    return (0);
}