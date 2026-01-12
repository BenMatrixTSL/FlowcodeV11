// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A0A335F5682D6F7FC85627147D5EF8444BB958AA1671ED06F0AE265CA116CDFB2F7800D711032B6231711B8143522C2B698DE3976514C8F3774F263794D68CF301EE80B65CFE504A04CAFC4AC423D765AC94ADFE7B8A641D756529854CBE610836785B7D18D9B61CF477B150B5ACCD158629AB5665F50A66E5DD2634E1F3B901E9A00E5CB17BBF7080549D34A0D5AD11F31A983974339BF6D5DCC9ACFFE37BE017827443896A6CB2C26DAE80F1ED87A78E40144AF09ADB914F
// REVISION: 2.0
// GUID: E3D41CD4-1A8C-4A66-91B6-BE1955B2FFDA
// DATE: 10\05\2023
// DIR: CAL\ESP\ESP_CAL_BT_SPP.c
/*********************************************************************
 *                  Flowcode CAL BT SPP File
 *
 * File: ESP_CAL_BT_SPP.c
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
 * 271120 | BR | Created
 *
 */

#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp_bt_device.h"
#include "esp_spp_api.h"

#define SPP_TAG "BT_SPP"
#define SPP_SERVER_NAME "SPP_SERVER"

//Receive Buffer Details
MX_UINT8 ESP32_BT_RXBUF[BT_RX_BUF_SZ];
MX_UINT16 ESP32_BT_RXBUFSTART = 0;
MX_UINT16 ESP32_BT_RXBUFEND = 0;
MX_UINT16 ESP32_BT_RXIDX;

//Verbose Debug Output
#if BT_DEBUG & 1
  #define BT_LOGI2 ESP_LOGI
  #define BT_LOGI3 ESP_LOGI
  #define BT_LOGI4 ESP_LOGI
#else
  #define BT_LOGI2(A,B)
  #define BT_LOGI3(A,B,C)
  #define BT_LOGI4(A,B,C,D)
#endif

#if BT_DEBUG & 2
  #define BT_LOGE3 ESP_LOGE
  #define BT_LOGE4 ESP_LOGE
#else
  #define BT_LOGE3(A,B,C)
  #define BT_LOGE4(A,B,C,D)
#endif



MX_UINT16 ESP32_BT_SPP_RX_GetNumberBytes()
{
    MX_UINT16 FCR_RETVAL;

    if (ESP32_BT_RXBUFEND > ESP32_BT_RXBUFSTART)
    {
        FCR_RETVAL = ESP32_BT_RXBUFEND - ESP32_BT_RXBUFSTART;
    }
    else
    {
        if (ESP32_BT_RXBUFEND < ESP32_BT_RXBUFSTART)
        {
            FCR_RETVAL = (BT_RX_BUF_SZ - ESP32_BT_RXBUFSTART) + ESP32_BT_RXBUFEND;
        }
        else
        {
            FCR_RETVAL = 0;
        }
    }
    return (FCR_RETVAL);
}


MX_UINT8 ESP32_BT_SPP_RX_PutByte(MX_UINT8 FCL_DATA)
{
    MX_UINT16 FCL_TEMP;
    MX_UINT8 FCR_RETVAL = 0;

    FCL_TEMP = ESP32_BT_RXBUFEND + 1;

    if (FCL_TEMP >= BT_RX_BUF_SZ)
    {
        FCL_TEMP = 0;
    }

    if (FCL_TEMP != ESP32_BT_RXBUFSTART)
    {
        ESP32_BT_RXBUF[ESP32_BT_RXBUFEND] = FCL_DATA;
        ESP32_BT_RXBUFEND = FCL_TEMP;
        FCR_RETVAL = 1;
    }

    return (FCR_RETVAL);
}


MX_UINT16 ESP32_BT_SPP_RX_GetByte()
{
    MX_UINT16 FCL_TEMP;
    MX_UINT16 FCR_RETVAL = 255;

    if (ESP32_BT_RXBUFSTART != ESP32_BT_RXBUFEND)
    {
        FCR_RETVAL = ESP32_BT_RXBUF[ESP32_BT_RXBUFSTART];
        FCL_TEMP = ESP32_BT_RXBUFSTART + 1;

        if (FCL_TEMP >= BT_RX_BUF_SZ)
        {
            FCL_TEMP = 0;
        }

        ESP32_BT_RXBUFSTART = FCL_TEMP;
    }

    return (FCR_RETVAL);
}


uint32_t BT_SPP_Handle = 0;

static const esp_spp_mode_t esp_spp_mode = ESP_SPP_MODE_CB;

static const esp_spp_sec_t sec_mask = ESP_SPP_SEC_AUTHENTICATE;
static const esp_spp_role_t role_slave = ESP_SPP_ROLE_SLAVE;

static void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param)
{
    switch (event) {
    case ESP_SPP_INIT_EVT:
        BT_LOGI2(SPP_TAG, "ESP_SPP_INIT_EVT");
        esp_bt_dev_set_device_name( BT_DEV_NAME );
        esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
        esp_spp_start_srv(sec_mask,role_slave, 0, SPP_SERVER_NAME);
        break;
    case ESP_SPP_DISCOVERY_COMP_EVT:
        BT_LOGI2(SPP_TAG, "ESP_SPP_DISCOVERY_COMP_EVT");
        break;
    case ESP_SPP_OPEN_EVT:
        BT_LOGI2(SPP_TAG, "ESP_SPP_OPEN_EVT");

        BT_SPP_Handle = param->srv_open.handle;

        break;
    case ESP_SPP_CLOSE_EVT:
        BT_LOGI2(SPP_TAG, "ESP_SPP_CLOSE_EVT");

        BT_SPP_Handle = 0;

        break;
    case ESP_SPP_START_EVT:
        BT_LOGI2(SPP_TAG, "ESP_SPP_START_EVT");

        //BT_SPP_Handle = param->srv_open.handle;

        break;
    case ESP_SPP_CL_INIT_EVT:
        BT_LOGI2(SPP_TAG, "ESP_SPP_CL_INIT_EVT");
        break;
    case ESP_SPP_DATA_IND_EVT:

    	BT_SPP_Handle = param->srv_open.handle;

        BT_LOGI4(SPP_TAG, "ESP_SPP_DATA_IND_EVT len=%d handle=%d", param->data_ind.len, param->data_ind.handle);

        //Data received - Add to CB a byte at a time
        for (ESP32_BT_RXIDX = 0; ESP32_BT_RXIDX < param->data_ind.len; ESP32_BT_RXIDX++)
        {
			ESP32_BT_SPP_RX_PutByte( param->data_ind.data[ESP32_BT_RXIDX] ) ;
		}

		//Interrupts enabled - call user macro
		#if BT_RX_INT_EN == 1
		    BT_RX_INT_MACRO();
		#endif

        break;
    case ESP_SPP_CONG_EVT:
        BT_LOGI2(SPP_TAG, "ESP_SPP_CONG_EVT");
        break;
    case ESP_SPP_WRITE_EVT:
        BT_LOGI2(SPP_TAG, "ESP_SPP_WRITE_EVT");
        break;
    case ESP_SPP_SRV_OPEN_EVT:

    	BT_SPP_Handle = param->srv_open.handle;

        BT_LOGI2(SPP_TAG, "ESP_SPP_SRV_OPEN_EVT");
        break;
    default:
        break;
    }
}

void esp_bt_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param)
{
    switch (event) {
    case ESP_BT_GAP_AUTH_CMPL_EVT:{
        if (param->auth_cmpl.stat == ESP_BT_STATUS_SUCCESS) {
            BT_LOGI3(SPP_TAG, "authentication success: %s", param->auth_cmpl.device_name);
            esp_log_buffer_hex(SPP_TAG, param->auth_cmpl.bda, ESP_BD_ADDR_LEN);
        } else {
            BT_LOGE3(SPP_TAG, "authentication failed, status:%d", param->auth_cmpl.stat);
        }
        break;
    }
    case ESP_BT_GAP_PIN_REQ_EVT:{
        BT_LOGI3(SPP_TAG, "ESP_BT_GAP_PIN_REQ_EVT min_16_digit:%d", param->pin_req.min_16_digit);
        if (param->pin_req.min_16_digit) {
            BT_LOGI2(SPP_TAG, "Input pin code: 0000 0000 0000 0000");
            esp_bt_pin_code_t pin_code = {0};
            esp_bt_gap_pin_reply(param->pin_req.bda, true, 16, pin_code);
        } else {
            BT_LOGI2(SPP_TAG, "Input pin code: 1234");
            esp_bt_pin_code_t pin_code;
            pin_code[0] = '1';
            pin_code[1] = '2';
            pin_code[2] = '3';
            pin_code[3] = '4';
            esp_bt_gap_pin_reply(param->pin_req.bda, true, 4, pin_code);
        }
        break;
    }

#if (CONFIG_BT_SSP_ENABLED == true)
    case ESP_BT_GAP_CFM_REQ_EVT:
        BT_LOGI3(SPP_TAG, "ESP_BT_GAP_CFM_REQ_EVT Please compare the numeric value: %d", param->cfm_req.num_val);
        esp_bt_gap_ssp_confirm_reply(param->cfm_req.bda, true);
        break;
    case ESP_BT_GAP_KEY_NOTIF_EVT:
        BT_LOGI3(SPP_TAG, "ESP_BT_GAP_KEY_NOTIF_EVT passkey:%d", param->key_notif.passkey);
        break;
    case ESP_BT_GAP_KEY_REQ_EVT:
        BT_LOGI2(SPP_TAG, "ESP_BT_GAP_KEY_REQ_EVT Please enter passkey!");
        break;
#endif

    default: {
        BT_LOGI3(SPP_TAG, "event: %d", event);
        break;
    }
    }
    return;
}


void BT_SPP_init()
{
	esp_err_t ret;
	ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    if ((ret = esp_bt_controller_init(&bt_cfg)) != ESP_OK) {
        BT_LOGE4(SPP_TAG, "%s initialize controller failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT)) != ESP_OK) {
        BT_LOGE4(SPP_TAG, "%s enable controller failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bluedroid_init()) != ESP_OK) {
        BT_LOGE4(SPP_TAG, "%s initialize bluedroid failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bluedroid_enable()) != ESP_OK) {
        BT_LOGE4(SPP_TAG, "%s enable bluedroid failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bt_gap_register_callback(esp_bt_gap_cb)) != ESP_OK) {
        BT_LOGE4(SPP_TAG, "%s gap register failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_spp_register_callback(esp_spp_cb)) != ESP_OK) {
        BT_LOGE4(SPP_TAG, "%s spp register failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_spp_init(esp_spp_mode)) != ESP_OK) {
        BT_LOGE4(SPP_TAG, "%s spp init failed: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

#if (CONFIG_BT_SSP_ENABLED == true)
    /* Set default parameters for Secure Simple Pairing */
    esp_bt_sp_param_t param_type = ESP_BT_SP_IOCAP_MODE;
    esp_bt_io_cap_t iocap = ESP_BT_IO_CAP_IO;
    esp_bt_gap_set_security_param(param_type, &iocap, sizeof(uint8_t));
#endif

    /*
     * Set default parameters for Legacy Pairing
     * Use variable pin, input pin code when pairing
     */
    esp_bt_pin_type_t pin_type = ESP_BT_PIN_TYPE_VARIABLE;
    esp_bt_pin_code_t pin_code;
    esp_bt_gap_set_pin(pin_type, 0, pin_code);
}


void BT_SPP_deinit()
{
	esp_spp_deinit();
}


void ESP32_BT_SPP_SetName (MX_CHAR * name)
{
	esp_bt_dev_set_device_name(name);
}


void ESP32_BT_SPP_TX_PutBytes (MX_UINT8 * data, MX_UINT16 length)
{
	if (BT_SPP_Handle)
	{
		esp_spp_write(BT_SPP_Handle, length, data);
	}
}


MX_UINT8 ESP32_BT_SPP_CheckConnection ()
{
	if (BT_SPP_Handle)
	{
		return 1;
	}
	return 0;
}

