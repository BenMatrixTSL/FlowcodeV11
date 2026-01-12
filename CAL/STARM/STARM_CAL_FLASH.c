// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BEB932B8128C287EB94CE9FB8F0BCEE23720C9826029F8C62A16EFA57B72031C2D9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF539529BDBBF47A79840D34BD5B41EC97E9BAF15A8658DB4E56570B9EDB46E3DB42FAC9632688CCE144FD35389838B7DDCB15BB28390342B174A1D47EB0026070957811BA061C9C8246D58A5CEC617F3212BCAEA307BD0F4A3549D34A0D5AD11F306EFC5373E0A3AA354A2391BB95408354854280D4C6C0E0F76AD1A7DB9B9D5F43F565616D7803A54
// REVISION: 1.0
// GUID: 66F53943-F5F1-4474-A3EC-D2921E2ACD4B
// DATE: 08\08\2022
// DIR: CAL\STARM\STARM_CAL_FLASH.c
/*********************************************************************
 *                  Flowcode CAL Flash File
 *
 * File: STARM_CAL_FLASH.c
 *
 * (c) 2020 Matrix TSL
 * http://www.matrixtsl.com
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
 * 020120 | LM | Created
 *
 *
 *
 */


#ifndef MX_FLASH_CAL_LAYER
	#define MX_FLASH_CAL_LAYER

	#if defined (STM32F373xC)

		MX_BOOL MX_FLASH_Ready(void)
		{
			// If still busy after 5 seconds return false
			MX_UINT32 start = HAL_GetTick();
			while (FLASH->SR & (FLASH_SR_BSY))
			{
				if ((HAL_GetTick() - start) > 5000)
					return 0;
			}
			// Clear the End of Operation flag if set
			if (FLASH->SR & (FLASH_SR_EOP))
				FLASH->SR = (FLASH_SR_EOP);
			return 1;
		}
		
		MX_BOOL MX_FLASH_Unlock(void)
		{
			if (FLASH->CR & (FLASH_CR_LOCK))
			{
				// For program and erase operations on the Flash memory, the internal RC oscillator (HSI) must be ON.
				__HAL_RCC_HSI_ENABLE() ;
				// Unlocking sequence written to the FLASH_KEYR register to open the access to the FLASH_CR register. 
				FLASH->KEYR = 0x45670123;
				FLASH->KEYR = 0xCDEF89AB;
				if (FLASH->CR & (FLASH_CR_LOCK))
					return 0;
			}
			return 1;
		}
		
		void MX_FLASH_EraseAll(MX_BOOL Aux)
		{
			// We'll not allow this for now!
		}

		void MX_FLASH_ErasePage(MX_UINT32 Address)
		{
			// Flash memory is organised as 128 pages of 2Kbyte
			// Flash area starts at 0x0800 0000, page 0, which ends at 0x0800 07ff
			// Check that the Flash is not locked, unlock if it is
			if (MX_FLASH_Unlock())
			{
				if (MX_FLASH_Ready())
				{
					// Set the PER bit in the FLASH_CR register
					FLASH->CR &= ~(FLASH_CR_PG);
					FLASH->CR |= (FLASH_CR_PER);
					// Program the FLASH_AR register to select a page to erase
					FLASH->AR = Address & 0x0ffff800;
					// Set the STRT bit in the FLASH_CR register
					// The software should start checking if the BSY bit equals ‘0’ at least one CPU cycle after setting the STRT bit.
					FLASH->CR |= (FLASH_CR_STRT);
				}
			}
		}
		
		void MX_FLASH_WriteU16(MX_UINT32 Address, MX_UINT16 Data)
		{
			// Write one half word of data
			if (MX_FLASH_Unlock())
			{
				if (MX_FLASH_Ready())
				{
					FLASH->CR &= ~(FLASH_CR_PER);
					FLASH->CR |= (FLASH_CR_PG);
					*(__IO uint16_t*)Address = Data;
				}
			}
		}
		
		void MX_FLASH_WriteByteArray(MX_UINT32 Address, MX_UINT8 *Data, MX_UINT32 Size)
		{
			// This assumes that the Flash destination address is UINT16 aligned, i.e. starts on an even address
			MX_UINT32 x = 0;
			MX_UINT16 w = 0;

			while (x < Size)
			{
			  if (Address & 1)
			  {
				w |= (Data[x] << 8);
				MX_FLASH_WriteU16(Address & 0xfffffffe, w);
				w = 0;
			  }
			  else
			  {
				w = Data[x];
			  }
			  Address++;
			  x++;
			}
			// flush any remaining byte
			if (Address & 1)
			{
				MX_FLASH_WriteU16(Address & 0xfffffffe, w);
			}
		}
		
		void MX_FLASH_ReadInstruction (MX_UINT32 Address, MX_UINT32 *Data)
		{

		}

		void MX_FLASH_WriteInstruction (MX_UINT32 Address, MX_UINT32 *Data)
		{

		}

		void MX_FLASH_WriteInstructionRow8 (MX_UINT32 Address, MX_UINT8 *Data)
		{

		}

		void MX_FLASH_WriteInstructionRow16 (MX_UINT32 Address, MX_UINT16 *Data)
		{
			MX_FLASH_WriteU16(Address, *Data);
		}

		void MX_FLASH_WriteInstructionRow (MX_UINT32 Address, MX_UINT32 *Data)
		{

		}

	// END OF #if defined (STM32F373xC)
	
	#elif 0 // more devices here ...

	#else
		#warning "No Flash support for selected target device"
	#endif

#endif		//#define MX_FLASH_CAL_LAYER

