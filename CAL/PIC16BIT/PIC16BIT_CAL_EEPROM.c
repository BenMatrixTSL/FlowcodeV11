// CRC: 5D982BB222882C54AB4AFF20A1590FC484D3178BD0D2510D0F5A64A7853221CAE2C33FABBE4F69A6659399D51781B7B9628F5CA2F725AA35EBE7AEDEF0F5C47ADD04A5F8AD9BEEB1823278EF8F2BA19C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5E5D0E8290D3F694B9CA51002AB67DE183DC3C86CF371938185EDE1367CDB513CF4E985C5AB3B6DB3396109FF9BAEDC659FD71AEEE9CE9A62825BA59AC2328CA19BD9264EFB93CE4C4CA0D2540B8FF235B278EB02C7778B88549D34A0D5AD11F3DC444865BB244D64F9646E575531F0D03FF01DC44737F57808DB0CC5B99E58558FAE3087E8A87EE9
// REVISION: 1.0
// GUID: 4CD3F83D-7277-4805-9EDB-6382F73BACD0
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\PIC16BIT_CAL_EEPROM.c
/*********************************************************************
 *                  Flowcode CAL EEPROM File
 *
 * File: PIC16BIT_CAL_EEPROM.c
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
 * 210911 | BR | Created
 * 020312 | BR | Updated to v5.1 CAL Schema
 */



//EEPROM Function Prototypes
MX_UINT16 FC_CAL_EE_Read (MX_UINT16 Address);
void FC_CAL_EE_Write (MX_UINT16 Address, MX_UINT16 Data);


//EEPROM memory define
#ifdef MX_EE
	unsigned int __attribute__ ((space(eedata))) eeprom;        // eeprom storage base
#endif



MX_UINT16 FC_CAL_EE_Read (MX_UINT16 Address)
{
	#ifdef MX_EE

		MX_UINT16 offset;
		MX_UINT16 Data;

		if (Address < (MX_EE_SIZE / 2))
		{
			Address <<= 1;								// word align address
			TBLPAG = __builtin_tblpage(&eeprom);      	// eeprom page
			offset = __builtin_tbloffset(&eeprom) + Address;
			Data = __builtin_tblrdl(offset);
			return(Data);
		}
		return 0;

	#else
		#error "Chip does not have EEPROM memory"
	#endif
}

void FC_CAL_EE_Write (MX_UINT16 Address, MX_UINT16 Data)
{
	#ifdef MX_EE

		#ifdef MX_EE_TYPE2								//Mod 28/08/14 to try and fix an issue on 24FV32KA304 Family

			MX_UINT16 offset;

			if (Address < (MX_EE_SIZE / 2))
			{
				//Calculate address
				Address <<= 1;							// word align address

				NVMCON = 0x4044;            			// Erase 1 word
				TBLPAG = __builtin_tblpage(&eeprom);
				offset = __builtin_tbloffset(&eeprom) + Address;
				__builtin_tblwtl(offset, 0);    		// prepare data in write latch

				asm volatile ("disi #6");    			// disable irqs for 6 instructions
				__builtin_write_NVM();        			// unlock and write
				while(NVMCONbits.WR);        			// wait while busy

				NVMCON = 0x4004;            			// set up to write 1 word
				__builtin_tblwtl(offset, Data);    		// prepare data in write latch
				 asm volatile ("disi #6");    			// disable irqs for 6 instructions
				 __builtin_write_NVM();        			// unlock and write
				while(NVMCONbits.WR);        			// wait while busy
			}

		#else

			MX_UINT16 offset;

			if (Address < (MX_EE_SIZE / 2))
			{
				//Calculate address
				Address <<= 1;							// word align address

				TBLPAG = __builtin_tblpage(&eeprom);
				offset = __builtin_tbloffset(&eeprom) + Address;

				NVMADR = offset;

				NVMCON = 0x4044;            			// Erase 1 word
				asm volatile ("disi #6");    			// disable irqs for 6 instructions
				__builtin_write_NVM();        			// unlock and write
				while(NVMCONbits.WR);        			// wait while busy
				NVMCON = 0x4004;            			// set up to write 1 word
				__builtin_tblwtl(offset, Data);    		// prepare data in write latch
				 asm volatile ("disi #6");    			// disable irqs for 6 instructions
				 __builtin_write_NVM();        			// unlock and write
				while(NVMCONbits.WR);        			// wait while busy
			}

		#endif

	#else
		#error "Chip does not have EEPROM memory"
	#endif
}

