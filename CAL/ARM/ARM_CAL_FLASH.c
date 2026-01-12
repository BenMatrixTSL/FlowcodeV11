// CRC: AE5753800093D2B889297C6B876B6A21749C10AFA09C3FCE4A5F65B0FF76818F67A9E646346A0E58656E0C7CA00928D09A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5CB2087346CD69362C3006B792B1B2499171244022B891D61218801E7D8AA161434150D15F988B2DF3937DDF6E3A3C621E47C0DCDDAE0169907D06FB5AC9CC3E267E381CC670A761A7D8783176816EB6963486621A8D93CD1549D34A0D5AD11F3E60EF9886A3B8320A2C6334C323505203F7F209D62E32C4A6CFC63B583D3C0065E5746CE888A1719
// REVISION: 1.0
// GUID: F5F5CF17-0F14-47B2-A610-F2DAA711CE13
// DATE: 08\08\2022
// DIR: CAL\ARM\ARM_CAL_FLASH.c
/*********************************************************************
 *                  Flowcode CAL Flash File
 *
 * File: ARM_CAL_Flash.c
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
 * 020412 | BR | Created
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
		char* ByteAddr;
		ByteAddr = (char*)(address);
		return(*ByteAddr);
	}


#endif		//#define MX_FLASH_CAL_LAYER



