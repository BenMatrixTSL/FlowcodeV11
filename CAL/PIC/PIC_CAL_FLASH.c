// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B867A9E646346A0E58656E0C7CA00928D09A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF524932A49FE66F4B58B781DBC581E2B8305DFA73B215499A86739DED14638F0291905D7DBDFD29F9AB852FA43BEF6064CBB4EB62AC05DB85FB4C1760B84D63F3A7A70645FC0A1ABE7B1265FC4F3AC8DB72C2D21A7CF10EADA549D34A0D5AD11F3BB9200D7D30D7ABD5F5EB38CBDFEC37ACA3827E98B5A163442BD2180FD7CFFB0161DC776D051D9AD
// REVISION: 1.0
// GUID: 18E650A8-5C27-4CE6-AD30-AB8B086B6528
// DATE: 08\08\2022
// DIR: CAL\PIC\PIC_CAL_FLASH.c
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
 * 010911 | BR | Created
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

		void MX_FLASH_ReadInstruction (MX_UINT32 Address, MX_UINT16 *Data)
		{
			MxConv.AsLong = Address;

			MX_UINT8 lo = MxConv.AsByte[0];
			MX_UINT8 hi = MxConv.AsByte[1];

			#asm

				BANKSEL NVMADRL ; Select Bank for NVMCON registers
				MOVLW MX_FLASH_ReadInstruction@lo ;
				MOVWF NVMADRL ; Store LSB of address
				MOVLW MX_FLASH_ReadInstruction@hi ;
				MOVWF NVMADRH ; Store MSB of address

				BCF NVMCON1,6 ; Do not select Configuration Space
				BSF NVMCON1,0 ; Initiate read
				MOVF NVMDATL,W ; Get LSB of word
				MOVWF MX_FLASH_ReadInstruction@lo ; Store in user location
				MOVF NVMDATH,W ; Get MSB of word
				MOVWF MX_FLASH_ReadInstruction@hi ; Store in user location

			#endasm


			MxConv.AsByte[0] = lo;
			MxConv.AsByte[1] = hi;
			Data[0] = MxConv.AsInt[0];

		}

		void MX_FLASH_WriteInstruction (MX_UINT32 Address, MX_UINT16 *Data)
		{

		}

		void MX_FLASH_WriteInstructionRow (MX_UINT32 Address, MX_UINT16 *Data)
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

		void MX_FLASH_ReadInstruction (MX_UINT32 Address, MX_UINT16 *Data)
		{

		}

		void MX_FLASH_WriteInstruction (MX_UINT32 Address, MX_UINT16 *Data)
		{

		}

		void MX_FLASH_WriteInstructionRow (MX_UINT32 Address, MX_UINT16 *Data)
		{

		}

	#endif		//#if (MX_FLASH_TYPE == 2)



	//Generic read routine - let the compiler do the work.
	char ReadFlash(long address)
	{
		char a;
		#if defined (_PIC_H_)				//10F / 12F /16F
			#if defined(__FLASHTYPE)
				a = FLASH_READ(address);
			#else
				#error "Sorry your selected target chip does not have Flash read capabilities";
			#endif
		#else								//18F
			_LOAD_TBLPTR(address);
			asm("TBLRD*+");
			a = TABLAT;
		#endif
		return a;
	}


#endif		//#define MX_FLASH_CAL_LAYER







