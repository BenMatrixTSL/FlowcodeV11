// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A08F697C51B7B990AE29C105FC2E0A2C3C77BB3095D8F4AC8569D42B3D56D757768940AE31AE32EB4A0C3CAEE8E7DA69874D7E08E6029882EB548F219A82DC2CE743D500A24E3E614EAE1288FC5DF8CDAC03A20A986E6BD55C32729370A0E6AAEFB75C270774DE11268C480AF10FC5DEF63EC2D50167A431274069AB3BE8FF7FC4CB011AE44E4E45FD549D34A0D5AD11F31A7A8D8BDF9DC30EBC353F8271527D4FE2DEE65D0E5F72EDAE50ACE3D7DDA2D28E9421B336835453
// REVISION: 7.0
// GUID: 63D1329F-A0AE-4642-A0EB-5E43C724AA7A
// DATE: 06\08\2025
// DIR: CAL\ESP\ESP_CAL_File.c

/*********************************************************************
 *                  Flowcode CAL File System Access File
 *
 * File: RPI_CAL_Socket.c
 *
 * (c) 2018 Matrix TSL
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
 * 281022 | BR | Created
 *
 */


#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"

#define MOUNT_POINT 		"/sdcard"
#define MOUNT_POINTSLASH 	MOUNT_POINT"/"

#define MX_FILE_COUNT_X     		CAL_APPEND(MX_FILE_COUNT_, MX_FILE_NUM)
#define MX_FILE_MAX_FREQUENCY_X  	CAL_APPEND(MX_FILE_MAX_FREQUENCY_, MX_FILE_NUM)
#define MX_FILE_SD_MODE_X     		CAL_APPEND(MX_FILE_SD_MODE_, MX_FILE_NUM)
#define MX_FILE_SD_REMAPPABLE_X		CAL_APPEND(MX_FILE_SD_REMAPPABLE_, MX_FILE_NUM)
#define MX_FILE_SD_CLK_X			CAL_APPEND(MX_FILE_SD_CLK_, MX_FILE_NUM)
#define MX_FILE_SD_CMD_X			CAL_APPEND(MX_FILE_SD_CMD_, MX_FILE_NUM)
#define MX_FILE_SD_D0_X				CAL_APPEND(MX_FILE_SD_D0_, MX_FILE_NUM)
#define MX_FILE_SD_D1_X				CAL_APPEND(MX_FILE_SD_D1_, MX_FILE_NUM)
#define MX_FILE_SD_D2_X				CAL_APPEND(MX_FILE_SD_D2_, MX_FILE_NUM)
#define MX_FILE_SD_D3_X				CAL_APPEND(MX_FILE_SD_D3_, MX_FILE_NUM)
#define MX_FILE_BUFF_SIZE_X     	CAL_APPEND(MX_FILE_BUFF_SIZE_, MX_FILE_NUM)
#define MX_FILE_DIR_SIZE_X     		CAL_APPEND(MX_FILE_DIR_SIZE_, MX_FILE_NUM)



//Unique variable names
#define MX_FILE_IDX_X     	CAL_APPEND(MX_FILE_IDX_, MX_FILE_NUM)
#define MX_FILE_FP_X     	CAL_APPEND(MX_FILE_FP_, MX_FILE_NUM)
#define MX_FILE_ST_X     	CAL_APPEND(MX_FILE_ST_, MX_FILE_NUM)
#define MX_FILE_INIT_X     	CAL_APPEND(MX_FILE_INIT_, MX_FILE_NUM)
#define MX_FILE_RW_X     	CAL_APPEND(MX_FILE_RW_, MX_FILE_NUM)


unsigned char MX_FILE_IDX_X = 0;										//File Index
unsigned char MX_FILE_INIT_X[MX_FILE_COUNT_X] = {0};					//Initialise status
unsigned char MX_FILE_RW_X[MX_FILE_COUNT_X] = {1};						//Read (0) / write (1) mode
struct stat MX_FILE_ST_X[MX_FILE_COUNT_X];								//File Status
FILE * MX_FILE_FP_X[MX_FILE_COUNT_X] = {NULL};							//File Handle
char MX_FILE_DIR_X[MX_FILE_COUNT_X][MX_FILE_DIR_SIZE_X] = {0};			//Directory
char MX_FILE_OPEN_X[MX_FILE_COUNT_X] = {0};


unsigned char MX_FILE_ReadBuffer[MX_FILE_BUFF_SIZE_X] = {0};
unsigned int MX_FILE_ReadIndex = 0;
unsigned int MX_FILE_ReadTotal = 0;


CALFUNCTION(MX_UINT8, FC_CAL_FILE_CloseFile_, ());


const char mount_point[] = MOUNT_POINT;
sdmmc_card_t *card;


CALFUNCTION(MX_UINT8, FC_CAL_FILE_Initialise_, ())
{
    esp_err_t ret;

    // Options for mounting the filesystem.
    // If format_if_mount_failed is set to true, SD card will be partitioned and
    // formatted in case when mounting fails.
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = MX_FILE_COUNT_X,
        .allocation_unit_size = 16 * 1024
    };

	// Use settings defined above to initialize SD card and mount FAT filesystem.
    // Note: esp_vfs_fat_sdmmc/sdspi_mount is all-in-one convenience functions.
    // Please check its source code and implement error recovery when developing
    // production applications.

    // By default, SD card frequency is initialized to SDMMC_FREQ_DEFAULT (20MHz)
    // For setting a specific frequency, use host.max_freq_khz (range 400kHz - 40MHz for SDMMC)
    // Example: for fixed frequency of 10MHz, use host.max_freq_khz = 10000;
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();

    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

    // Set bus width to use:
#if (MX_FILE_SD_MODE_X == 4)
    slot_config.width = 4;
#else
    slot_config.width = 1;
#endif

    // On chips where the GPIOs used for SD card can be configured, set them in
    // the slot_config structure:
#if (MX_FILE_SD_REMAPPABLE_X == 1)
    slot_config.clk = MX_FILE_SD_CLK_X;
    slot_config.cmd = MX_FILE_SD_CMD_X;
    slot_config.d0 = MX_FILE_SD_D0_X;
#if (MX_FILE_SD_MODE_X == 4)
    slot_config.d1 = MX_FILE_SD_D1_X;
    slot_config.d2 = MX_FILE_SD_D2_X;
    slot_config.d3 = MX_FILE_SD_D3_X;
#endif  // #if (MX_FILE_SD_MODE_X == 4)
#endif  // CONFIG_SOC_SDMMC_USE_GPIO_MATRIX

    // Enable internal pullups on enabled pins. The internal pullups
    // are insufficient however, please make sure 10k external pullups are
    // connected on the bus. This is for debug / example purpose only.
    slot_config.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;

    ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL)
		{
			return (254);		//Failed to mount filesystem
        }
		else
		{
            return (255);		//Failed to initialize the card
        }
    }

	return (0);					//OK
}


CALFUNCTION(void, FC_CAL_FILE_Uninitialise_, ())
{
 	// All done, unmount partition and disable SDMMC peripheral

 #if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)	// enable functionality present in IDF v5.0
    esp_vfs_fat_sdcard_unmount(mount_point, card);
 #else
 	esp_vfs_fat_sdmmc_unmount();
 #endif

}


CALFUNCTION(MX_UINT8, FC_CAL_FILE_OpenFile_, (MX_STRING FCL_FILENAME, unsigned int length))
{
	unsigned char FCL_FILEPATH[256];

	if (MX_FILE_INIT_X[MX_FILE_IDX_X] == 0)
	{
		FCI_CONCATENATE(MOUNT_POINTSLASH, MX_FILE_DIR_SIZE_X, "", 0, MX_FILE_DIR_X[MX_FILE_IDX_X], MX_FILE_DIR_SIZE_X);
		MX_FILE_INIT_X[MX_FILE_IDX_X] = 1;
	}

	//Combine filename with current directory
	FCI_CONCATENATE(MX_FILE_DIR_X[MX_FILE_IDX_X], MX_FILE_DIR_SIZE_X, FCL_FILENAME, length, FCL_FILEPATH, MX_FILE_DIR_SIZE_X);
	//ESP_LOGI(TAG, "Reading file: %s", (char *) FCL_FILEPATH);

	if (MX_FILE_OPEN_X[MX_FILE_IDX_X])
		CALFUNCTION(, FC_CAL_FILE_CloseFile_, ());

	//Open file for in read mode - ensure we don't create new files
	MX_FILE_FP_X[MX_FILE_IDX_X] = fopen (FCL_FILEPATH, "r");

	//if file not found and creation error
	if (MX_FILE_FP_X[MX_FILE_IDX_X] == NULL)
	{
		MX_FILE_OPEN_X[MX_FILE_IDX_X] = 0;

        //ESP_LOGE(TAG, "Failed to open file for reading");
		return 1;
	}

	//Close file reference
	fclose(MX_FILE_FP_X[MX_FILE_IDX_X]);

	//Open file for append and reading
	MX_FILE_FP_X[MX_FILE_IDX_X] = fopen (FCL_FILEPATH, "a+");

	MX_FILE_OPEN_X[MX_FILE_IDX_X] = 1;

	//Flag file pointer is at the EOF
	MX_FILE_RW_X[MX_FILE_IDX_X] = 1;

	//File opened correctly
	return 0;
}


CALFUNCTION(MX_UINT8, FC_CAL_FILE_CloseFile_, ())
{
	//Close file reference
	if (MX_FILE_OPEN_X[MX_FILE_IDX_X])
		fclose(MX_FILE_FP_X[MX_FILE_IDX_X]);

	MX_FILE_OPEN_X[MX_FILE_IDX_X] = 0;

	MX_FILE_ReadIndex = 0;
	MX_FILE_ReadTotal = 0;

	//File closed correctly
	return 0;
}



CALFUNCTION(MX_UINT8, FC_CAL_FILE_CreateFile_, (MX_STRING *FCL_FILENAME, unsigned int length))
{
	unsigned char * FCL_FILEPATH[256];

	if (MX_FILE_INIT_X[MX_FILE_IDX_X] == 0)
	{
		FCI_CONCATENATE(MOUNT_POINTSLASH, MX_FILE_DIR_SIZE_X, "", 0, MX_FILE_DIR_X[MX_FILE_IDX_X], MX_FILE_DIR_SIZE_X);
		MX_FILE_INIT_X[MX_FILE_IDX_X] = 1;
	}

	//Combine filename with current directory
	FCI_CONCATENATE(MX_FILE_DIR_X[MX_FILE_IDX_X], MX_FILE_DIR_SIZE_X, FCL_FILENAME, length, FCL_FILEPATH, MX_FILE_DIR_SIZE_X);
	//ESP_LOGI(TAG, "Reading file: %s", (char *) FCL_FILEPATH);

	//Open file for append and reading - also create new file
	MX_FILE_FP_X[MX_FILE_IDX_X] = fopen (FCL_FILEPATH, "a+");

	//Flag file pointer is at the EOF
	MX_FILE_RW_X[MX_FILE_IDX_X] = 1;

	//File opened correctly
	return 0;
}



CALFUNCTION(MX_UINT8, FC_CAL_FILE_DeleteFile_, (MX_CHAR *FCL_FILENAME, unsigned int length))
{
	unsigned char * FCL_FILEPATH[256];

	if (MX_FILE_INIT_X[MX_FILE_IDX_X] == 0)
	{
		FCI_CONCATENATE(MOUNT_POINTSLASH, MX_FILE_DIR_SIZE_X, "", 0, MX_FILE_DIR_X[MX_FILE_IDX_X], MX_FILE_DIR_SIZE_X);
		MX_FILE_INIT_X[MX_FILE_IDX_X] = 1;
	}

	//Combine filename with current directory
	FCI_CONCATENATE(MX_FILE_DIR_X[MX_FILE_IDX_X], MX_FILE_DIR_SIZE_X, FCL_FILENAME, length, FCL_FILEPATH, MX_FILE_DIR_SIZE_X);

	//Delete file
	return remove(FCL_FILEPATH);
}


CALFUNCTION(MX_UINT32, FC_CAL_FILE_ReadFileSize_, ())
{
	//Return file size in bytes
	return MX_FILE_ST_X[MX_FILE_IDX_X].st_size;
}


CALFUNCTION(MX_UINT8, FC_CAL_FILE_AppendByteToFile_, (MX_UINT8 FCL_BYTE))
{
	//Append a character to the end of the file
	return fputc(FCL_BYTE, MX_FILE_FP_X[MX_FILE_IDX_X]);
}


CALFUNCTION(MX_UINT8, FC_CAL_FILE_AppendStringToFile_, (MX_STRING *FCL_STR, unsigned int stlength))
{
	//Append a string to the end of the file
	return fputs(FCL_STR, MX_FILE_FP_X[MX_FILE_IDX_X]);
}


CALFUNCTION(MX_UINT8, FC_CAL_FILE_ReadByteFromFile_, ())
{
	if (MX_FILE_RW_X[MX_FILE_IDX_X])
	{
		//Seek to the start of the file
		fseek(MX_FILE_FP_X[MX_FILE_IDX_X], 0, SEEK_SET);
		MX_FILE_RW_X[MX_FILE_IDX_X] = 0;
	}

	if (MX_FILE_ReadIndex >= MX_FILE_ReadTotal)
	{
		//Return an array of bytes from the file into the local buffer
		MX_FILE_ReadTotal = fread(MX_FILE_ReadBuffer, 1, MX_FILE_BUFF_SIZE_X, MX_FILE_FP_X[MX_FILE_IDX_X]);
		MX_FILE_ReadIndex = 0;
	}

	if (MX_FILE_ReadIndex < MX_FILE_ReadTotal)
	{
		return MX_FILE_ReadBuffer[MX_FILE_ReadIndex++];
	}
	else
	{
		return 0;		//EOF?
	}

}


CALFUNCTION(MX_UINT16, FC_CAL_FILE_ReadByteArrayFromFile_, (MX_UINT8 *Data, MX_UINT16 stLength, MX_UINT16 Length))
{
	MX_UINT16 idx;
	for (idx = 0; idx < Length; idx++)
	{
		Data[idx] = CALFUNCTION(, FC_CAL_FILE_ReadByteFromFile_, ());
	}
	return Length;
}


CALFUNCTION(MX_UINT8, FC_CAL_FILE_ReadByteFromIndex_, (MX_UINT32 FCL_ADDRESS))
{
	//Seek to the correct byte in the file
	fseek(MX_FILE_FP_X[MX_FILE_IDX_X], FCL_ADDRESS, SEEK_SET);
	MX_FILE_RW_X[MX_FILE_IDX_X] = 0;

	//Flag that we have moved and need to refill the buffer if doing a burst read
	MX_FILE_ReadIndex = MX_FILE_ReadTotal;

	//Return a character from the file
	return fgetc(MX_FILE_FP_X[MX_FILE_IDX_X]);
}


CALFUNCTION(void, FC_CAL_FILE_ReadStringFromFile_, (MX_UINT16 NumBytes, MX_UINT8 EndChar, MX_STRING * FCL_STR, MX_UINT16 length))
{
	if (MX_FILE_RW_X[MX_FILE_IDX_X])
	{
		//Seek to the start of the file
		fseek(MX_FILE_FP_X[MX_FILE_IDX_X], 0, SEEK_SET);
		MX_FILE_RW_X[MX_FILE_IDX_X] = 0;

		//Flag that we have moved and need to refill the buffer if doing a burst read
		MX_FILE_ReadIndex = MX_FILE_ReadTotal;
	}

	//Return a character from the file
	fgets(FCL_STR, NumBytes, MX_FILE_FP_X[MX_FILE_IDX_X]);
}


CALFUNCTION(MX_UINT8, FC_CAL_FILE_SetFileIndex_, (MX_UINT8 FCL_Index))
{
	//Set the file index allowing access to multiple files at once
	if (FCL_Index < MX_FILE_COUNT_X)
		MX_FILE_IDX_X = FCL_Index;

	return 0;
}


CALFUNCTION(MX_UINT8, FC_CAL_FILE_OpenFolder_, (MX_STRING *FCL_STR, unsigned int length))
{
	if (MX_FILE_INIT_X[MX_FILE_IDX_X] == 0)
	{
		FCI_CONCATENATE(MOUNT_POINTSLASH, MX_FILE_DIR_SIZE_X, "", 0, MX_FILE_DIR_X[MX_FILE_IDX_X], MX_FILE_DIR_SIZE_X);
		MX_FILE_INIT_X[MX_FILE_IDX_X] = 1;
	}

	if (FCI_COMPARE(FCL_STR, length, "root", 4, 1) == 0)
	{
		FCI_CONCATENATE(MOUNT_POINTSLASH, MX_FILE_DIR_SIZE_X, "", 0, MX_FILE_DIR_X[MX_FILE_IDX_X], MX_FILE_DIR_SIZE_X);
		MX_FILE_INIT_X[MX_FILE_IDX_X] = 1;
	}
	else
	{
		//Combine folder with current directory
		FCI_CONCATENATE(MX_FILE_DIR_X[MX_FILE_IDX_X], MX_FILE_DIR_SIZE_X, FCL_STR, length, MX_FILE_DIR_X[MX_FILE_IDX_X], MX_FILE_DIR_SIZE_X);

		MX_UINT16 len = FCI_GETLENGTH(FCL_STR, length);
		if (FCL_STR[len - 1] != '/')
		{
			//Combine folder with current directory
			FCI_CONCATENATE(MX_FILE_DIR_X[MX_FILE_IDX_X], MX_FILE_DIR_SIZE_X, "/", 1, MX_FILE_DIR_X[MX_FILE_IDX_X], MX_FILE_DIR_SIZE_X);
		}
	}

	return 0;
}
