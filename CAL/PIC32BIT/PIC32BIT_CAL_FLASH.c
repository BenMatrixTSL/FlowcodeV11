// CRC: A6459004C43C0517DC6DFC5681C2AD698104299A14C9E1875427A2F7EF4303D9CFD76A29863CD488DE50EA9D9C0AC8D1E1B9F0352D8791541263048FFE416A47186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5B058713D60CCCF713A3BA5BFA9FCD4B22A6A5BFD6DB9FC2300337FD96E2CC6CC62042919E9B9BBDFDAAE029D24E77CF0130680AB9B3A9AFA8D9DE113222BC427C71BAF08C4D89C2B32382AF3A359C4954581113083D8814E549D34A0D5AD11F3F82F43111AE82F9175D215DA59E281C68573B70DE21EEA806DAE80F1ED87A78E40144AF09ADB914F
// REVISION: 1.0
// GUID: 032AD16E-E31D-4A0F-87DD-CD9E3A0D96A9
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\PIC32BIT_CAL_FLASH.c
/*********************************************************************
 *                  Flowcode CAL Flash File
 *
 * File: PIC_CAL_Flash.c
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
 * 050912 | BR | Created
 *
 *
 *
 */



#ifndef MX_FLASH_CAL_LAYER
	#define MX_FLASH_CAL_LAYER


	#if (MX_FLASH_TYPE == 1)

		MX_Union32 MxConv;

		void MX_FLASH_EraseAll (MX_BOOL Aux)
		{

		}

		void MX_FLASH_ErasePage (MX_UINT32 Address)
		{

		}

		void MX_FLASH_ReadInstruction (MX_UINT32 Address, MX_UINT32 *Data)
		{

		}

		void MX_FLASH_WriteInstruction (MX_UINT32 Address, MX_UINT32 *Data)
		{

		}

		void MX_FLASH_WriteInstructionRow (MX_UINT32 Address, MX_UINT32 *Data)
		{

		}

	#endif		//#if (MX_FLASH_TYPE == 1)


	#if (MX_FLASH_TYPE == 2)

		MX_Union32 MxConv;

		void MX_FLASH_EraseAll (MX_BOOL Aux)
		{

		}

		void MX_FLASH_ErasePage (MX_UINT32 Address)
		{

		}

		void MX_FLASH_ReadInstruction (MX_UINT32 Address, MX_UINT32 *Data)
		{

		}

		void MX_FLASH_WriteInstruction (MX_UINT32 Address, MX_UINT32 *Data)
		{

		}

		void MX_FLASH_WriteInstructionRow (MX_UINT32 Address, MX_UINT32 *Data)
		{

		}

	#endif		//#if (MX_FLASH_TYPE == 2)




	//Generic read routine - let the compiler do the work.
	char ReadFlash(long address)
	{
		char a;
		volatile char* register_ptr = (char*)address;
		a = *register_ptr;
		return a;
	}



#endif		//#define MX_FLASH_CAL_LAYER






