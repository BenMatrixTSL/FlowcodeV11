// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A01C1D9B46CD5A2250B072AE94224B49139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF56B0D26F68FE8477CAC1EB4CB0B1B71D3DAD96D65020CF8B9A5CED3AD36C1A0D5EDACB5667BA69C9F5A9695DB191C0D2EA6FF9FBC9CDACF154749F12F6C770339FC043F282182CDB48709C713D67DF10F502990E2AF2DF044549D34A0D5AD11F36FF0D61B8552A1C50BF1CA9EDA09D85A76199A75424B78E927A8E1A814A6FBB04A61C0D2CB77CF29
// REVISION: 1.0
// GUID: 7F9CCE7D-48D5-4516-87BE-ACFAC2B1571F
// DATE: 08\08\2022
// DIR: CAL\ESP\ESP_CAL_EEPROM.c
/*********************************************************************
 *                  Flowcode CAL EEPROM File
 *
 * File: ESP_CAL_EEPROM.c
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
 * 260521 | BR | Created
 */

#include "nvs_flash.h"
#include "nvs.h"


MX_UINT8 initialised = 0;
nvs_handle_t my_handle;
esp_err_t err;
MX_STRING EEaddrStr[8];

void FC_CAL_EE_Init ()
{
    // Initialize NVS
    err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );

	err = nvs_open("storage", NVS_READWRITE, &my_handle);

	/*
    if (err != ESP_OK)
    {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    }
    else
    {
        printf("Done\n");
	}
	*/

	initialised = 1;
}

MX_UINT16 FC_CAL_EE_Read (MX_UINT16 Address)
{
	if (initialised == 0)
		FC_CAL_EE_Init();

	MX_UINT16 EEdata = 0;
	FCI_TOSTRU16(Address, EEaddrStr, 8);

    err = nvs_get_u16(my_handle, EEaddrStr, &EEdata);

	return (EEdata);
}

void FC_CAL_EE_Write (MX_UINT16 Address, MX_UINT16 Data)
{
	if (initialised == 0)
		FC_CAL_EE_Init();

	FCI_TOSTRU16(Address, EEaddrStr, 8);

    err = nvs_set_u16(my_handle, EEaddrStr, Data);
    err = nvs_commit(my_handle);
}
