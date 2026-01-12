// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B81C1D9B46CD5A2250B072AE94224B49131FB11C427988058F6166CF704E625A4D8940AE31AE32EB4A0C3CAEE8E7DA698771D83523AF90E24FF15F29FDE4D07706C245DCC8C720B4FEAE02B915E931018772CD34FEE61541F24A60D227D3EED77DA0A31C062904F3DBAA7D0FC8818805F6769768EEE47B519671F5C97C30BD3CA3AA1D7F7DCF288256549D34A0D5AD11F36E220A89B9164139B5B19C23CDCEBE61E0C4B0753902A026ADE7F62E1D9AF28DE7B6485568F872D0
// REVISION: 3.0
// GUID: 85F665AC-116A-4A6D-94EE-B05B1F6B26D8
// DATE: 29\05\2025
// DIR: CAL\PIC\PIC_CAL_EEPROM.c
/*********************************************************************
 *                  Flowcode CAL EEPROM File
 *
 * File: PIC_CAL_EEPROM.c
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
 * 010513 | LM | V6 EEPROM CAL standardised API to 16 bit data word size
 * 240517 | BR | Added Type 4 for new 18F devices
 * 300517 | LM | Additional mods to support 16F18 (compiles but untested)
 */


#ifndef _INTCON_GIE_POSITION
  #ifdef _INTCON0_GIE_POSITION
    #define INTCON INTCON0
    #define INTCONbits INTCON0bits
  #endif
#endif


#if defined(MX_EE_TYPE1) || defined(MX_EE_TYPE2) || defined(MX_EE_TYPE3) || defined(MX_EE_TYPE4)

	#ifdef _NVMCON1_WR_POSN

		MX_UINT16 FC_CAL_EE_Read (MX_UINT16 Address)
		{
			MX_UINT16 data = 0;

			#ifdef MX_EE

				#if defined _NVMCON1_NVMREG_POSN
					NVMCON1bits.NVMREG = 0;					//EEPROM Access
				#elif defined _NVMCON1_NVMREGS_POSN
					NVMCON1bits.NVMREGS = 1;				//EEPROM Access
				#endif

				NVMADRL = Address & 0xff;

				#if (MX_EE_SIZE > 256)
					NVMADRH = (Address & 0xff00) >> 8;
				#endif

				#if defined (MX_EE_TYPE4)					//EE Memory starts at address 0xF000
					NVMADRH |= 0xF0;
				#endif

				NVMCON1bits.RD = 1;
				#if defined _NVMDAT_NVMDAT0_POSN
					data = NVMDAT;
				#elif defined _NVMDATL_NVMDAT0_POSN
					data = NVMDATL;
				#elif defined _NVMDATL_NVMDATL0_POSN
					data = NVMDATL;
				#endif

				#if defined _NVMCON1_NVMREG_POSN
					NVMCON1bits.NVMREG = 2;					//FLASH Access
				#elif defined _NVMCON1_NVMREGS_POSN
					NVMCON1bits.NVMREGS = 0;				//FLASH Access
				#endif

			#else
				#error "Chip does not have EEPROM memory"
			#endif
			return (data);
		}

		void FC_CAL_EE_Write (MX_UINT16 Address, MX_UINT16 Data)
		{
			#ifdef MX_EE

				char bInterruptsEnabled;

				//wait for previous EE writes to complete...
				while (ts_bit(NVMCON1, WR));

				#if defined _NVMCON1_NVMREG_POSN
					NVMCON1bits.NVMREG = 0;					//EEPROM Access
				#elif defined _NVMCON1_NVMREGS_POSN
					NVMCON1bits.NVMREGS = 1;				//EEPROM Access
				#endif

				NVMADRL = Address & 0xff;

				#if (MX_EE_SIZE > 256)
					NVMADRH = (Address & 0xff00) >> 8;
				#endif

				#if defined (MX_EE_TYPE4)					//EE Memory starts at address 0xF000
					NVMADRH |= 0xF0;
				#endif

				#if defined _NVMDAT_NVMDAT0_POSN
					NVMDAT = Data;
				#elif defined _NVMDATL_NVMDAT0_POSN
					NVMDATL = Data;
				#elif defined _NVMDATL_NVMDATL0_POSN
					NVMDATL = Data;
				#endif

				NVMCON1bits.WREN = 1;

				bInterruptsEnabled = ts_bit(INTCON, GIE);
				cr_bit(INTCON, GIE);			//Disable Interrupts

				NVMCON2 = 0x55;
				NVMCON2 = 0xAA;

				NVMCON1bits.WR = 1;

				while (ts_bit(NVMCON1, WR));		//wait for EE write to complete...

				if (bInterruptsEnabled)
					st_bit(INTCON, GIE);		//Re-enable Interrupts

				NVMCON1bits.WREN = 0;

				#if defined _NVMCON1_NVMREG_POSN
					NVMCON1bits.NVMREG = 2;					//FLASH Access
				#elif defined _NVMCON1_NVMREGS_POSN
					NVMCON1bits.NVMREGS = 0;				//FLASH Access
				#endif

			#else
				#error "Chip does not have EEPROM memory"
			#endif
		}

	#else


		MX_UINT16 FC_CAL_EE_Read (MX_UINT16 Address)
		{
			MX_UINT16 data = 0;

			#ifdef MX_EE

				EEADR = Address & 0xff;
				#if (MX_EE_SIZE > 256)
					EEADRH = (Address & 0xff00) >> 8;
				#endif
				#ifdef MX_EE_TYPE2
					cr_bit(EECON1, EEPGD);
				#endif
				#ifdef MX_EE_TYPE3
					cr_bit(EECON1, EEPGD);
					cr_bit(EECON1, CFGS);
				#endif
				st_bit(EECON1, RD);
				data = EEDATA;

			#else
				#error "Chip does not have EEPROM memory"
			#endif
			return (data);
		}

		void FC_CAL_EE_Write (MX_UINT16 Address, MX_UINT16 Data)
		{
			#ifdef MX_EE

				char bInterruptsEnabled;
				//wait for previous EE writes to complete...
				while (ts_bit(EECON1, WR));
				EEADR = Address & 0xff;
				#if (MX_EE_SIZE > 256)
					EEADRH = (Address & 0xff00) >> 8;
				#endif
				EEDATA = Data;
				#ifdef MX_EE_TYPE2
					cr_bit(EECON1, EEPGD);
				#endif
				#ifdef MX_EE_TYPE3
					cr_bit(EECON1, EEPGD);
					cr_bit(EECON1, CFGS);
				#endif
				st_bit(EECON1, WREN);
				bInterruptsEnabled = ts_bit(INTCON, GIE);
				cr_bit(INTCON, GIE);			//Disable Interrupts
				EECON2 = 0x55;
				EECON2 = 0xAA;
				st_bit(EECON1, WR);
				while (ts_bit(EECON1, WR));	//wait for EE write to complete...
				if (bInterruptsEnabled)
					st_bit(INTCON, GIE);		//Re-enable Interrupts
				cr_bit(EECON1, WREN);

			#else
				#error "Chip does not have EEPROM memory"
			#endif
		}

	#endif

#endif



#ifdef MX_EE_TYPE5			//SAF type Flash EE memory

	#warning "Be sure to enable the Storage Area Flash (SAF) in the device configuration settings"

	MX_UINT16 FC_CAL_EE_Read (MX_UINT16 Address)
	{
		NVMADRH = MX_EE_Flash_Address >> 8;
		NVMADRL = MX_EE_Flash_Address + Address;
		NVMCON1bits.NVMREGS = 0;
		NVMCON1bits.RD = 1;

		while (NVMCON1bits.RD == 1)
		{
		}

		//NOP();  // NOPs may be required for latency at high frequencies
		//NOP();

		return NVMDATL;		//Data is stored in lower 8-bits, upper 6 bits are currently unused
	}

	void FC_CAL_EE_Write (MX_UINT16 Address, MX_UINT16 Data)
	{
		char bInterruptsEnabled;

		//Create 32 byte RAM image
		int FlashRowData[32];
		for (int i =0;i<32;i++)
		{
			FlashRowData[i]= FC_CAL_EE_Read((Address & 0xE0) + i);			//Read address 0-31, 32-63, 64-95, 96-127
		}

		//  int Err = 0;
		NVMCON1bits.WRERR = 0;

		bInterruptsEnabled = ts_bit(INTCON, GIE);
		INTCONbits.GIE = 0;     // Disable interrupts

		//Update required value
		FlashRowData[Address & 0x1F] = Data;

		//Erase Row - 32 instruction words
		NVMADRH = MX_EE_Flash_Address >> 8;
		NVMADRL = MX_EE_Flash_Address + (Address & 0xE0);

		NVMCON1bits.NVMREGS = 0;
		NVMCON1bits.FREE = 1;
		NVMCON1bits.WREN = 1;
		NVMCON2 = 0x55;
		NVMCON2 = 0xAA;
		NVMCON1bits.WR = 1;

		// Wait for write to complete
		while (NVMCON1bits.WR == 1)
		{
		}

		NVMCON1bits.WREN = 0;

		//Write Row - 32 instruction words including new data byte value
		for (int i=0; i<32; i++)
		{
			NVMADRH = MX_EE_Flash_Address >> 8;
			NVMADRL = MX_EE_Flash_Address + (Address & 0xE0) + i;
			NVMDATL = FlashRowData[i];
			NVMCON1bits.NVMREGS = 0;
			NVMCON1bits.WREN = 1;
			NVMCON2 = 0x55;
			NVMCON2 = 0xAA;
			NVMCON1bits.WR = 1;
			// Wait for write to complete
			while (NVMCON1bits.WR == 1)
			{
			}

			NVMCON1bits.WREN = 0;
		}

		if (bInterruptsEnabled)
			INTCONbits.GIE = 1;   // restore interrupt enable

	}

#endif

#ifdef MX_EE_TYPE6			//DFM type Flash EE memory

	MX_UINT16 FC_CAL_EE_Read (MX_UINT16 Address)
	{
		MX_UINT8 retVal;

		NVMCON0bits.NVMEN = 1;

		NVMADRU = MX_EE_DFM_Address >> 16;
		NVMADRH = MX_EE_DFM_Address >> 8;
		NVMADRL = MX_EE_DFM_Address + Address;
		NVMCON1bits.RD = 1;

		//while (NVMCON1bits.RD == 1)
		//{
		//}

		retVal = NVMDATL;			//Data is stored in lower 8-bits, upper 6 bits are currently unused
		NVMCON0bits.NVMEN = 0;
		return retVal;
	}

	void FC_CAL_EE_Write (MX_UINT16 Address, MX_UINT16 Data)
	{
		char bInterruptsEnabled;

		//Erase Row - 32 instruction words
		NVMADRU = MX_EE_DFM_Address >> 16;
		NVMADRH = MX_EE_DFM_Address >> 8;
		NVMADRL = MX_EE_DFM_Address + Address;

		NVMDATL = Data;
		NVMCON0bits.NVMEN = 1;

		bInterruptsEnabled = ts_bit(INTCON, GIE);
		INTCONbits.GIE = 0;     // Disable interrupts

		NVMCON2 = 0x55;
		NVMCON2 = 0xAA;
		NVMCON1bits.WR = 1;

		// Wait for write to complete
		while (NVMCON1bits.WR == 1)
		{
		}

		NVMCON0bits.NVMEN = 0;

		if (bInterruptsEnabled)
			INTCONbits.GIE = 1;   // restore interrupt enable

	}

#endif

#ifdef MX_EE_TYPE7 // Q series NVM

MX_UINT16 FC_CAL_EE_Read(MX_UINT16 Address)
{
    NVMADR = Address;                  // Set EEPROM address (0–255)
    NVMCON1bits.NVMCMD = 0b000;        // Byte Read command
    NVMCON0bits.GO = 1;                // Start read operation
    while (NVMCON0bits.GO);            // Wait for GO to clear
    return NVMDATL;                    // Return 8-bit data (zero-extended)
}

void FC_CAL_EE_Write(MX_UINT16 Address, MX_UINT16 Data)
{
   
    INTCON0bits.GIE = 0;  // Disable global interrupts completely
    // Setup write
    NVMADR = Address;
    NVMDATL = (MX_UINT8)(Data & 0xFF);
    NVMCON1bits.NVMCMD = 0b011;       // Byte Write command

    // Unlock sequence
    NVMLOCK = 0x55;
    NVMLOCK = 0xAA;
    NVMCON0bits.GO = 1;               // Start write

    while (NVMCON0bits.GO);           // Wait until complete

    NVMCON1bits.NVMCMD = 0;           // Clear command
    INTCON0bits.GIE = 1; 			  // Re-enable global interrupts
}

#endif
