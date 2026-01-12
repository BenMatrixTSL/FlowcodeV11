// CRC: 5D982BB222882C54AB4AFF20A1590FC484D3178BD0D2510D0F5A64A7853221CAE2C33FABBE4F69A6659399D51781B7B9E1B9F0352D8791541263048FFE416A47186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5C0D3FCD3FAA3356B70A8038FD14C42E30FD5AAA6DC0C51FC32285DA02A6608D935C55BE11165C1EADADD32F59D1F9FA564F256CC587344169F57F6E8FDDDD86434E781E90C35DCB3965964CD2B671ABFAD01D95B5C2AC90D549D34A0D5AD11F3B6D7C13C8B3640F28FBF3CE21628B1D8E7B0DE98C9CDA769A7E0A38DADB65FFF85A60D01A8F5E6C8
// REVISION: 1.0
// GUID: 0A78549D-93F3-48E9-8638-94AC2215E081
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\PIC16BIT_CAL_FLASH.c
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
 * 300320 | BR | Added new functions to work with FlashCAL and FlashEEs
 */


#ifndef MX_FLASH_CAL_LAYER
	#define MX_FLASH_CAL_LAYER


	#if (MX_FLASH_TYPE == 1)

		MX_Union32 MxConv;

		#define MX_FLASH_ERASE_AUX		0x400A
		#define MX_FLASH_ERASE_PRI		0x400D
		#define MX_FLASH_ERASE_PAGE		0x4003
		#define MX_FLASH_PROG_WORD		0x4001
		#define MX_FLASH_PROG_ROW		0x4002

		void MX_FLASH_EraseAll (MX_BOOL Aux)
		{
			if (Aux)
			{
				NVMCON = MX_FLASH_ERASE_AUX;		//Aux Flash
			}
			else
			{
				NVMCON = MX_FLASH_ERASE_PRI;		//Primary Flash
			}
			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}

		void MX_FLASH_ErasePage (MX_UINT32 Address)
		{
			MxConv.AsLong = Address;
			NVMADR = MxConv.AsInt[0];
			NVMADRU = MxConv.AsInt[1];
			NVMCON = MX_FLASH_ERASE_PAGE;
			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}

		void MX_FLASH_ReadInstruction (MX_UINT32 Address, MX_UINT32 *Data)
		{
			MX_UINT16 addr16;
			MxConv.AsLong = Address;
			addr16 = MxConv.AsInt[0];
			TBLPAG = MxConv.AsInt[1];
			MxConv.AsInt[0] = __builtin_tblrdl(addr16);
			MxConv.AsInt[1] = __builtin_tblrdh(addr16);
			Data[0] = MxConv.AsLong;
		}

		void MX_FLASH_WriteInstruction (MX_UINT32 Address, MX_UINT32 *Data)
		{
			TBLPAG = 0xFA;
			MxConv.AsLong = Address;
			NVMADR = MxConv.AsInt[0];
			NVMADRU = MxConv.AsInt[1];
			NVMCON = MX_FLASH_PROG_WORD;

			for (MX_UINT8 i=0; i<MX_FLASH_MIN_WRITE_SIZE; i++)
			{
				MxConv.AsLong = Data[i];
				__builtin_tblwtl(i * 2, MxConv.AsInt[0]);
				__builtin_tblwth(i * 2, MxConv.AsInt[1]);
			}

			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}

/*
		void MX_FLASH_WriteInstructionRow16 (MX_UINT32 Address, MX_UINT16 *Data)
		{
			NVMCON = MX_FLASH_PROG_ROW;
			TBLPAG = 0xFA;
			MxConv.AsLong = Address;
			NVMADR = MxConv.AsInt[0];
			NVMADRU = MxConv.AsInt[1];
			for(MX_UINT16 i=0; i<MX_FLASH_ROW_SIZE; i++)
			{
				__builtin_tblwtl((i * 2), Data[i]);
				__builtin_tblwth((i * 2), 0);
			}
			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}
*/

		void MX_FLASH_WriteInstructionRow (MX_UINT32 Address, MX_UINT32 *Data)
		{
			NVMCON = MX_FLASH_PROG_ROW;
			TBLPAG = 0xFA;
			MxConv.AsLong = Address;
			NVMADR = MxConv.AsInt[0];
			NVMADRU = MxConv.AsInt[1];
			for(MX_UINT16 i=0; i<MX_FLASH_ROW_SIZE; i++)
			{
				MxConv.AsLong = Data[i];
				__builtin_tblwtl((i * 2), MxConv.AsInt[0]);
				__builtin_tblwth((i * 2), MxConv.AsInt[1]);
			}
			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}

	#endif		//#if (MX_FLASH_TYPE == 1)


	#if (MX_FLASH_TYPE == 2)

		MX_Union32 MxConv;

		#define MX_FLASH_ERASE_AUX		0x404D
		#define MX_FLASH_ERASE_PRI		0x404F
		#define MX_FLASH_ERASE_PAGE		0x4042
		#define MX_FLASH_PROG_WORD		0x4003
		#define MX_FLASH_PROG_ROW		0x4001


		void MX_FLASH_EraseAll (MX_BOOL Aux)
		{
			if (Aux)
			{
			}
			else
			{
			}
			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}

		void MX_FLASH_ErasePage (MX_UINT32 Address)
		{
			MxConv.AsLong = Address;
			NVMCON = MX_FLASH_ERASE_PAGE;
			TBLPAG = MxConv.AsInt[1];
			__builtin_tblwtl(MxConv.AsInt[0], 0x0000);
			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}

		void MX_FLASH_ReadInstruction (MX_UINT32 Address, MX_UINT32 *Data)
		{
			MX_UINT16 addr16;
			MxConv.AsLong = Address;
			addr16 = MxConv.AsInt[0];
			TBLPAG = MxConv.AsInt[1];
			MxConv.AsInt[0] = __builtin_tblrdl(addr16);
			MxConv.AsInt[1] = __builtin_tblrdh(addr16);
			Data[0] = MxConv.AsLong;
		}

		void MX_FLASH_WriteInstruction (MX_UINT32 Address, MX_UINT32 *Data)
		{
			MX_UINT16 addr16;
			MxConv.AsLong = Address;
			TBLPAG = MxConv.AsInt[1];
			addr16 = MxConv.AsInt[0];
			NVMCON = MX_FLASH_PROG_WORD;

			for (MX_UINT8 i=0; i<MX_FLASH_MIN_WRITE_SIZE; i++)
			{
				MxConv.AsLong = Data[i];
				__builtin_tblwtl(i * 2, MxConv.AsInt[0]);
				__builtin_tblwth(i * 2, MxConv.AsInt[1]);
			}

			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}

/*
		void MX_FLASH_WriteInstructionRow16 (MX_UINT32 Address, MX_UINT16 *Data)
		{
			MX_UINT16 addr16;
			NVMCON = MX_FLASH_PROG_ROW;
			MxConv.AsLong = Address;
			TBLPAG = MxConv.AsInt[1];
			addr16 = MxConv.AsInt[0];
			for(MX_UINT16 i=0; i<MX_FLASH_ROW_SIZE; i++)
			{
				__builtin_tblwtl(addr16 + (i * 2), Data[i]);
				__builtin_tblwth(addr16 + (i * 2), 0);
			}
			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}
*/

		void MX_FLASH_WriteInstructionRow (MX_UINT32 Address, MX_UINT32 *Data)
		{
			MX_UINT16 addr16;
			NVMCON = MX_FLASH_PROG_ROW;
			MxConv.AsLong = Address;
			TBLPAG = MxConv.AsInt[1];
			addr16 = MxConv.AsInt[0];
			for(MX_UINT16 i=0; i<MX_FLASH_ROW_SIZE; i++)
			{
				MxConv.AsLong = Data[i];
				__builtin_tblwtl(addr16 + (i * 2), MxConv.AsInt[0]);
				__builtin_tblwth(addr16 + (i * 2), MxConv.AsInt[1]);
			}
			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}

	#endif		//#if (MX_FLASH_TYPE == 2)



	#if (MX_FLASH_TYPE == 3)

		MX_Union32 MxConv;

		#define MX_FLASH_ERASE_AUX
		#define MX_FLASH_ERASE_PRI		0x404F
		#define MX_FLASH_ERASE_PAGE		0x4042
		#define MX_FLASH_PROG_WORD		0x4003
		#define MX_FLASH_PROG_ROW		0x4001

		void MX_FLASH_EraseAll (MX_BOOL Aux)
		{
			if (Aux)
			{
				//Not available on this device
			}
			else
			{

			}
			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}

		void MX_FLASH_ErasePage (MX_UINT32 Address)
		{
			MxConv.AsLong = Address;
			NVMCON = MX_FLASH_ERASE_PAGE;
			NVMADR = MxConv.AsInt[0];
			NVMADRU = MxConv.AsInt[1];
			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}

		void MX_FLASH_ReadInstruction (MX_UINT32 Address, MX_UINT32 *Data)
		{
			MX_UINT16 addr16;
			MxConv.AsLong = Address;
			addr16 = MxConv.AsInt[0];
			TBLPAG = MxConv.AsInt[1];
			MxConv.AsInt[0] = __builtin_tblrdl(addr16);
			MxConv.AsInt[1] = __builtin_tblrdh(addr16);
			Data[0] = MxConv.AsLong;
		}

		void MX_FLASH_WriteInstruction (MX_UINT32 Address, MX_UINT32 *Data)
		{
			MX_UINT16 addr16;
			MxConv.AsLong = Address;

			NVMADR = MxConv.AsInt[0];
			NVMADRU = MxConv.AsInt[1];
			NVMCON = MX_FLASH_PROG_WORD;

			for (MX_UINT8 i=0; i<MX_FLASH_MIN_WRITE_SIZE; i++)
			{
				MxConv.AsLong = Data[i];
				__builtin_tblwtl(i * 2, MxConv.AsInt[0]);
				__builtin_tblwth(i * 2, MxConv.AsInt[1]);
			}
		}

/*
		void MX_FLASH_WriteInstructionRow16 (MX_UINT32 Address, MX_UINT16 *Data)
		{
			MX_UINT16 addr16;
			NVMCON = MX_FLASH_PROG_ROW;
			MxConv.AsLong = Address;
			NVMADR = MxConv.AsInt[0];
			NVMADRU = MxConv.AsInt[1];
			for(MX_UINT16 i=0; i<MX_FLASH_ROW_SIZE; i++)
			{
				__builtin_tblwtl((i * 2), Data[i]);
				__builtin_tblwth((i * 2), 0);
			}
			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}
*/

		void MX_FLASH_WriteInstructionRow (MX_UINT32 Address, MX_UINT32 *Data)
		{
			MX_UINT16 addr16;
			NVMCON = MX_FLASH_PROG_ROW;
			MxConv.AsLong = Address;
			NVMADR = MxConv.AsInt[0];
			NVMADRU = MxConv.AsInt[1];
			for(MX_UINT16 i=0; i<MX_FLASH_ROW_SIZE; i++)
			{
				MxConv.AsLong = Data[i];
				__builtin_tblwtl((i * 2), MxConv.AsInt[0]);
				__builtin_tblwth((i * 2), MxConv.AsInt[1]);
			}
			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}

	#endif		//#if (MX_FLASH_TYPE == 3)



	#if (MX_FLASH_TYPE == 4)

		MX_Union32 MxConv;

		#define MX_FLASH_ERASE_AUX
		#define MX_FLASH_ERASE_PRI
		#define MX_FLASH_ERASE_PAGE		0x4041
		#define MX_FLASH_PROG_WORD
		#define MX_FLASH_PROG_ROW		0x4001

		void MX_FLASH_EraseAll (MX_BOOL Aux)
		{
			//Not available on this device
		}

		void MX_FLASH_ErasePage (MX_UINT32 Address)
		{
			MxConv.AsLong = Address;
			NVMCON = MX_FLASH_ERASE_PAGE;
			NVMADR = MxConv.AsInt[0];
			NVMADRU = MxConv.AsInt[1];
			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}

		void MX_FLASH_ReadInstruction (MX_UINT32 Address, MX_UINT32 *Data)
		{
			MX_UINT16 addr16;
			MxConv.AsLong = Address;
			addr16 = MxConv.AsInt[0];
			TBLPAG = MxConv.AsInt[1];
			MxConv.AsInt[0] = __builtin_tblrdl(addr16);
			MxConv.AsInt[1] = __builtin_tblrdh(addr16);
			Data[0] = MxConv.AsLong;
		}

		void MX_FLASH_WriteInstruction (MX_UINT32 Address, MX_UINT32 *Data)
		{
			//Not available on this device
		}

/*
		void MX_FLASH_WriteInstructionRow16 (MX_UINT32 Address, MX_UINT16 *Data)
		{
			MX_UINT16 addr16;
			NVMCON = MX_FLASH_PROG_ROW;
			MxConv.AsLong = Address;
			NVMADR = MxConv.AsInt[0];
			NVMADRU = MxConv.AsInt[1];
			for(MX_UINT16 i=0; i<MX_FLASH_ROW_SIZE; i++)
			{
				__builtin_tblwtl((i * 2), Data[i]);
				__builtin_tblwth((i * 2), 0);
			}
			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}
*/

		void MX_FLASH_WriteInstructionRow (MX_UINT32 Address, MX_UINT32 *Data)
		{
			MX_UINT16 addr16;
			NVMCON = MX_FLASH_PROG_ROW;
			MxConv.AsLong = Address;
			NVMADR = MxConv.AsInt[0];
			NVMADRU = MxConv.AsInt[1];
			for(MX_UINT16 i=0; i<MX_FLASH_ROW_SIZE; i++)
			{
				MxConv.AsLong = Data[i];
				__builtin_tblwtl((i * 2), MxConv.AsInt[0]);
				__builtin_tblwth((i * 2), MxConv.AsInt[1]);
			}
			__builtin_disi(5);
			__builtin_write_NVM();
			while(NVMCONbits.WR == 1);
		}

	#endif		//#if (MX_FLASH_TYPE == 4)



	//Generic read routine - let the compiler do the work.
	char ReadFlash(long address)
	{
		char a;
		volatile char* register_ptr = (char*)address;
		a = *register_ptr;
		return a;
	}


#endif		//#define MX_FLASH_CAL_LAYER