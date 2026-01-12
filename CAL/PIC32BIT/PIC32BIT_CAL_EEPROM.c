// CRC: A6459004C43C0517DC6DFC5681C2AD698104299A14C9E1875427A2F7EF4303D9CFD76A29863CD488DE50EA9D9C0AC8D1628F5CA2F725AA35EBE7AEDEF0F5C47ADD04A5F8AD9BEEB1823278EF8F2BA19C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF58E7B81F9000533EE8795A534CFC1FAFAB7AC0C13E1653FEAFF4A7C1268BAE699D9A5CCD516157F52143216C1DD610B3FBE12614F65A924740125BC7A15571F673030809FA91E5D3CD5092F32C17DF8BE66EEC95E95BEF4E2549D34A0D5AD11F347196A997876052DD110FEEF0A58F3360C58AF24453D2ED7E7373FB746EF938F8DC82FEBD146BBA9
// REVISION: 1.0
// GUID: FBFA3BF9-9507-4A41-962F-5703AA740403
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\PIC32BIT_CAL_EEPROM.c
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

