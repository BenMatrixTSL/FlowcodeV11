// CRC: 77485F5F6A861F9125D47827B4DE492656C5431E478E8046055FD2257F64F1F31C1D9B46CD5A2250B072AE94224B49139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5B7C04C68C6FC9D1216CC3EE380C46910D07E019F113F8613B26D3016FA3916D73FAE0237BDBB7A5AFA174E99AB4066BC061E33B4EBD940F58BE12546E5B6D6C603BFD9D041AF3ADCED881A4E33B3B4A3A053822A9B71577C549D34A0D5AD11F3B4CF625E8EC9AB7BFD5136B1566C4A1390B00780892C4DDC072F880DBB6DFDD32544F23D1CC1FCAE
// REVISION: 1.0
// GUID: 0E12AC62-B59A-4A42-9156-4AE36665AEDB
// DATE: 08\08\2022
// DIR: CAL\AVR\AVR_CAL_EEPROM.c
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
 * 010513 | LM | V6 EEPROM CAL standardised API to 16 bit data word size
 */



#ifdef MX_XMEGA

	#define NVM_EXEC()	asm("push r30"      "\n\t"	\
							"push r31"      "\n\t"	\
							"push r16"      "\n\t"	\
							"push r18"      "\n\t"	\
							"ldi r30, 0xCB" "\n\t"	\
							"ldi r31, 0x01" "\n\t"	\
							"ldi r16, 0xD8" "\n\t"	\
							"ldi r18, 0x01" "\n\t"	\
							"out 0x34, r16" "\n\t"	\
							"st Z, r18"	    "\n\t"	\
							"pop r18"       "\n\t"	\
							"pop r16"       "\n\t"	\
							"pop r31"       "\n\t"	\
							"pop r30"       "\n\t"	\
							)

	void EEPROM_WaitForNVM( void )
	{
		do {
			/* Block execution while waiting for the NVM to be ready. */
		} while ((NVM.STATUS & NVM_NVMBUSY_bm) == NVM_NVMBUSY_bm);
	}

	void EEPROM_FlushBuffer( void )
	{
		/* Wait until NVM is not busy. */
		EEPROM_WaitForNVM();

		/* Flush EEPROM page buffer if necessary. */
		if ((NVM.STATUS & NVM_EELOAD_bm) != 0) {
			NVM.CMD = NVM_CMD_ERASE_EEPROM_BUFFER_gc;
			NVM_EXEC();
		}
	}

#endif



MX_UINT16 FC_CAL_EE_Read (MX_UINT16 Address)
{
	#ifdef MX_EE

		#ifndef MX_XMEGA

			MX_UINT16 Data = 0;

			#ifdef EEWE
				while (test_bit(EECR, EEWE));
			#else
				while (test_bit(EECR, EEPE));
			#endif

			Data = eeprom_read_byte((unsigned char *)Address);
			return (Data);

		#else

			EEPROM_WaitForNVM();	//Wait until NVM is not busy

			//Set address to read from
			NVM.ADDR0 = Address & 0xFF;
			NVM.ADDR1 = (Address >> 8) & 0x1F;
			NVM.ADDR2 = 0x00;

			//Issue EEPROM Read command
			NVM.CMD = NVM_CMD_READ_EEPROM_gc;
			NVM_EXEC();

			return NVM.DATA0;

		#endif

	#else
		#error "Chip does not have EEPROM memory"
	#endif

	return (0);
}

void FC_CAL_EE_Write (MX_UINT16 Address, MX_UINT16 Data)
{
	#ifdef MX_EE

		#ifndef MX_XMEGA

			#ifdef EEWE
				while (test_bit(EECR, EEWE));
			#else
				while (test_bit(EECR, EEPE));
			#endif

			cli();
			eeprom_write_byte((unsigned char *)Address, (MX_UINT8)Data);
			sei();

		#else

			EEPROM_FlushBuffer();
			NVM.CMD = NVM_CMD_LOAD_EEPROM_BUFFER_gc;

			//Set address to write to
			NVM.ADDR0 = Address & 0xFF;
			NVM.ADDR1 = (Address >> 8) & 0x1F;
			NVM.ADDR2 = 0x00;

			//Load data to write, which triggers the loading of EEPROM page buffer
			NVM.DATA0 = Data;

			//Issue EEPROM Atomic Write (Erase&Write) command. Load command, write the protection signature and execute command.
			NVM.CMD = NVM_CMD_ERASE_WRITE_EEPROM_PAGE_gc;
			NVM_EXEC();

		#endif

	#else
		#error "Chip does not have EEPROM memory"
	#endif
}




