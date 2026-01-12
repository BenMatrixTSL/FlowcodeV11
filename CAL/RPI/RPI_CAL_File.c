// CRC: 34358081B117C27F7D8358E612878F8E5F343B66182D417818220CB9C07676CF8F697C51B7B990AE29C105FC2E0A2C3C6F44F738C9EB354C3CEBADA1DDEF2ADDB496F86072B20B50711B8143522C2B69A0686589D073F5E83AD1FF82E77889B5F548B263276E8E1D86D7F1E9F164AD734DB114699E7334907037D43448A2959CD51011A9C077DCE47C51E5DF8A1A614B587690218102C2FB5D804719E061EE8818073F469CF6CF40549D34A0D5AD11F32DD599E6DA06401B146C5050D934BD7B44E6A915E58423CA5D2E1919BC6D834D57C406BC4A49D3F1
// REVISION: 6.0
// GUID: 8944A1CE-13E0-4F82-B538-CBB6EA85907D
// DATE: 27\09\2023
// DIR: CAL\RPI\RPI_CAL_File.c

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
 * �Company�) for its Flowcode graphical programming language is
 * intended and supplied to you, the Company�s customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
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


#include <stdio.h>
#include <stdlib.h>



#define MX_FILE_COUNT_X     CAL_APPEND(MX_FILE_COUNT_, MX_FILE_NUM)
#define MX_FILE_ROOT_X     	CAL_APPEND(MX_FILE_ROOT_, MX_FILE_NUM)


//Unique variable names
#define MX_FILE_IDX_X     	CAL_APPEND(MX_FILE_IDX_, MX_FILE_NUM)
#define MX_FILE_FP_X     	CAL_APPEND(MX_FILE_FP_, MX_FILE_NUM)
#define MX_FILE_ST_X     	CAL_APPEND(MX_FILE_ST_, MX_FILE_NUM)
#define MX_FILE_INIT_X     	CAL_APPEND(MX_FILE_INIT_, MX_FILE_NUM)


unsigned char MX_FILE_IDX_X = 0;							//File Index
unsigned char MX_FILE_INIT_X[MX_FILE_COUNT_X] = {0};		//Initialise status
struct stat MX_FILE_ST_X[MX_FILE_COUNT_X];					//File Status
FILE * MX_FILE_FP_X[MX_FILE_COUNT_X];						//File Handle
unsigned char * MX_FILE_DIR_X[MX_FILE_COUNT_X][256] = {0};	//Directory


CALFUNCTION(MX_UINT8, FC_CAL_FILE_OpenFile_, (MX_CHAR *FCL_FILENAME, unsigned int length))
{
	unsigned char * FCL_FILEPATH[256];

	if (MX_FILE_INIT_X[MX_FILE_IDX_X] == 0)
	{
		FCI_CONCATENATE(MX_FILE_ROOT_X, 256, "", 0, MX_FILE_DIR_X[MX_FILE_IDX_X], 256);
		MX_FILE_INIT_X[MX_FILE_IDX_X] = 1;
	}

	//Combine filename with current directory
	FCI_CONCATENATE(MX_FILE_DIR_X[MX_FILE_IDX_X], 256, FCL_FILENAME, 256, FCL_FILEPATH, 256);

	//Get file stats
	stat(FCL_FILEPATH, &MX_FILE_ST_X[MX_FILE_IDX_X]);

	//Open file for reading and appending
	MX_FILE_FP_X[MX_FILE_IDX_X] = fopen (FCL_FILEPATH, "a+");
	//MX_FILE_FP_X[MX_FILE_IDX_X] = fopen (FCL_FILEPATH, "r");

	//if file not found and creation error
	if (MX_FILE_FP_X[MX_FILE_IDX_X] == NULL)
		return 1;

	//Not needed
	//lseek(MX_FILE_FP_X, 0, SEEK_SET);

	//File opened correctly
	return 0;
}


CALFUNCTION(MX_UINT8, FC_CAL_FILE_CloseFile_, ())
{
	//Close file reference
	fclose(MX_FILE_FP_X[MX_FILE_IDX_X]);

	//File closed correctly
	return 0;
}


CALFUNCTION(MX_UINT8, FC_CAL_FILE_DeleteFile_, (MX_CHAR *FCL_FILENAME, unsigned int length))
{
	unsigned char * FCL_FILEPATH[256];

	if (MX_FILE_INIT_X[MX_FILE_IDX_X] == 0)
	{
		FCI_CONCATENATE(MX_FILE_ROOT_X, 256, "", 0, MX_FILE_DIR_X[MX_FILE_IDX_X], 256);
		MX_FILE_INIT_X[MX_FILE_IDX_X] = 1;
	}

	//Combine filename with current directory
	FCI_CONCATENATE(MX_FILE_DIR_X[MX_FILE_IDX_X], 256, FCL_FILENAME, 256, FCL_FILEPATH, 256);

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


CALFUNCTION(MX_UINT8, FC_CAL_FILE_AppendStringToFile_, (MX_UINT8 *FCL_STR, unsigned int length))
{
	//Append a string to the end of the file
	return fputs(FCL_STR, MX_FILE_FP_X[MX_FILE_IDX_X]);
}


CALFUNCTION(MX_UINT8, FC_CAL_FILE_ReadByteFromFile_, ())
{
	//Return a character from the file
	return fgetc(MX_FILE_FP_X[MX_FILE_IDX_X]);
}


CALFUNCTION(MX_UINT8, FC_CAL_FILE_ReadByteFromIndex_, (MX_UINT32 FCL_ADDRESS))
{
	//Seek to the correct byte in the file
	lseek(MX_FILE_FP_X, FCL_ADDRESS, SEEK_SET);

	//Return a character from the file
	return fgetc(MX_FILE_FP_X[MX_FILE_IDX_X]);
}


CALFUNCTION(void, FC_CAL_FILE_ReadStringFromFile_, (MX_UINT16 NumBytes, MX_UINT8 EndChar, MX_UINT8 * FCL_STR, MX_UINT16 length))
{
	//Return a character from the file
	fgets(FCL_STR, NumBytes, MX_FILE_FP_X[MX_FILE_IDX_X]);
}


CALFUNCTION(MX_UINT8, FC_CAL_FILE_SetFileIndex_, (MX_UINT8 FCL_Index))
{
	//Set the file index allowing access to multiple files at once
	if (FCL_Index < MX_FILE_COUNT_X)
		MX_FILE_IDX_X = FCL_Index;
}


CALFUNCTION(MX_UINT8, FC_CAL_FILE_OpenFolder_, (MX_UINT8 *FCL_STR, unsigned int length))
{
	if (MX_FILE_INIT_X[MX_FILE_IDX_X] == 0)
	{
		FCI_CONCATENATE(MX_FILE_ROOT_X, 256, "", 0, MX_FILE_DIR_X[MX_FILE_IDX_X], 256);
		MX_FILE_INIT_X[MX_FILE_IDX_X] = 1;
	}

	if (FCI_COMPARE(FCL_STR, length, "root", 4, 1) == 0)
	{
		FCI_CONCATENATE(MX_FILE_ROOT_X, 256, "", 0, MX_FILE_DIR_X[MX_FILE_IDX_X], 256);
		MX_FILE_INIT_X[MX_FILE_IDX_X] = 1;
	}
	else
	{
		//Combine folder with current directory
		FCI_CONCATENATE(MX_FILE_DIR_X[MX_FILE_IDX_X], 256, FCL_STR, 256, MX_FILE_DIR_X[MX_FILE_IDX_X], 256);

		MX_UINT16 len = FCI_GETLENGTH(FCL_STR, 256);
		if (FCL_STR[len - 1] != '/')
		{
			//Combine folder with current directory
			FCI_CONCATENATE(MX_FILE_DIR_X[MX_FILE_IDX_X], 256, "/", 1, MX_FILE_DIR_X[MX_FILE_IDX_X], 256);
		}
	}

	return 0;
}
