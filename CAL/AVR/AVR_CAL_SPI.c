// CRC: 77485F5F6A861F9125D47827B4DE492656C5431E478E8046055FD2257F64F1F306F4274FDFAD3D87C5F8E545EDBF5F889A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF551260109AC61BDEE431FE094D47B11FCA5C8E90C8E4F4BC57E8FA24A798451DAF6DAFCBA8F5A3F8CE4FE8FE3C3EEBBC5AEEDE3059C350C84F48AEAE122E5A4A4831CB35BEE6E539427068CF31B49094311DA6271DD1D7342549D34A0D5AD11F39606BD9CC0F39E47823F0F8CB9F9DACCCBB1EEB53A37FE8DA00A18B8526AEFB14B8DFBE9D4D641FD
// REVISION: 1.0
// GUID: 770FCE29-94DA-4DCF-8091-DFDADF564FBB
// DATE: 08\08\2022
// DIR: CAL\AVR\AVR_CAL_SPI.c
/*********************************************************************
 *                  Flowcode CAL SPI File
 *
 * File: AVR_CAL_SPI.c
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
 * 190911 | BR | Created
 * 020312 | BR | Updated to v5.1 CAL Schema
 * 220512 | BR | Added XMEGA functionality
 * 200712 | BR | Added new macro to configure prescaler on the fly
 * 090812 | ST | Fixed initial clock polarity setting
 * 090812 | ST | Added comments to explain the BMODE settings and Master_Byte function
 * 140912 | BR | Chaned prescaler function to tie in with the FAT component
 * 210613 | BR | Bug fix defines mod for HW SPI Prescaler - also related mods to init
 * 030713 | LM | Standard API calls
 * 220118 | LM | Add transaction functions
 *
 */


//When using hardware SPI channels override port and pin conns with FCD conn definitions
//Only overwrite CS pin defines when using SPI in slave mode on a hardware channel
//Also sort out postscale and prescale options for hardware channels

#define MX_SPI_REF_X			CAL_APPEND(MX_SPI_REF, MX_SPI_NUM)
#define MX_SPI_CHANNEL_X		CAL_APPEND(MX_SPI_CHANNEL_, MX_SPI_NUM)
#define MX_SPI_MOSI_PIN_X		CAL_APPEND(MX_SPI_MOSI_PIN_, MX_SPI_NUM)
#define MX_SPI_MOSI_PORT_X		CAL_APPEND(MX_SPI_MOSI_PORT_, MX_SPI_NUM)
#define MX_SPI_MOSI_TRIS_X		CAL_APPEND(MX_SPI_MOSI_TRIS_, MX_SPI_NUM)
#define MX_SPI_MISO_PIN_X		CAL_APPEND(MX_SPI_MISO_PIN_, MX_SPI_NUM)
#define MX_SPI_MISO_PORT_X		CAL_APPEND(MX_SPI_MISO_PORT_, MX_SPI_NUM)
#define MX_SPI_MISO_TRIS_X		CAL_APPEND(MX_SPI_MISO_TRIS_, MX_SPI_NUM)
#define MX_SPI_SCK_PIN_X		CAL_APPEND(MX_SPI_SCK_PIN_, MX_SPI_NUM)
#define MX_SPI_SCK_PORT_X		CAL_APPEND(MX_SPI_SCK_PORT_, MX_SPI_NUM)
#define MX_SPI_SCK_TRIS_X		CAL_APPEND(MX_SPI_SCK_TRIS_, MX_SPI_NUM)
#define MX_SPI_CS_PIN_X			CAL_APPEND(MX_SPI_CS_PIN_, MX_SPI_NUM)
#define MX_SPI_CS_PORT_X		CAL_APPEND(MX_SPI_CS_PORT_, MX_SPI_NUM)
#define MX_SPI_CS_TRIS_X		CAL_APPEND(MX_SPI_CS_TRIS_, MX_SPI_NUM)
#define MX_SPI_BMODE_X			CAL_APPEND(MX_SPI_BMODE_, MX_SPI_NUM)
#define MX_SPI_PR_SCALE_X		CAL_APPEND(MX_SPI_PR_SCALE_, MX_SPI_NUM)
#define MX_SPI_PO_SCALE_X		CAL_APPEND(MX_SPI_PO_SCALE_, MX_SPI_NUM)
#define MX_SPI_INT_X			CAL_APPEND(MX_SPI_INT_, MX_SPI_NUM)
#define MX_SPI_SLAVE_X			CAL_APPEND(MX_SPI_SLAVE_, MX_SPI_NUM)


//Setup Definitions
#ifdef MX_SPI_REF_X
	#if MX_SPI_CHANNEL_X > 0
		#if MX_SPI_PR_SCALE_X == 4
			#define MX_SPI_PR_SCALE_HW	0
		#endif
		#if MX_SPI_PR_SCALE_X == 16
			#define MX_SPI_PR_SCALE_HW	1
		#endif
		#if MX_SPI_PR_SCALE_X == 64
			#define MX_SPI_PR_SCALE_HW	2
		#endif
		#if MX_SPI_PR_SCALE_X == 128
			#define MX_SPI_PR_SCALE_HW	3
		#endif
		#if MX_SPI_PR_SCALE_X == 2
			#define MX_SPI_PR_SCALE_HW	4
		#endif
		#if MX_SPI_PR_SCALE_X == 8
			#define MX_SPI_PR_SCALE_HW	5
		#endif
		#if MX_SPI_PR_SCALE_X == 32
			#define MX_SPI_PR_SCALE_HW	6
		#endif
	#endif
#endif


#define MX_PRESCALE_VAR_X		CAL_APPEND(prescale_, MX_SPI_NUM)

MX_UINT8 MX_PRESCALE_VAR_X = (MX_SPI_PR_SCALE_X / 2) - 1;


//Master Function Prototypes
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Init_, (void));
CALFUNCTION(void, FC_CAL_SPI_Master_Uninit_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Byte_, (MX_UINT8 DataOut));
CALFUNCTION(void, FC_CAL_SPI_SetPrescaler_, (MX_UINT8 Prescaler));

//Master Transaction Function Prototypes
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_Init_,   (void));
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_,   (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length));
CALFUNCTION(void,     FC_CAL_SPI_Transaction_Uninit_, (void));

//Slave Function Prototypes
CALFUNCTION(void, FC_CAL_SPI_Slave_Init_, (void));
CALFUNCTION(void, FC_CAL_SPI_Slave_Uninit_, (void));
CALFUNCTION(void, FC_CAL_SPI_Slave_TxByte_, (MX_UINT8 Data));
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Slave_RxByte_, (void));


//Bus Mode - Bit0=CKP=CPOL, Bit1=CKE=!CPHA, Bit2=CSMP
//CKP=CPOL - Clock Polarity - Idle State of the clock 0=0, 1=1
//CKE=CPHA - Clock Phase - Clock Edge 0=leading edge, 1=trailing edge
//CSMP - Input Data Bit Sample Phase

// There are 4 SPI clock modes as follows:
//
// SPI Mode | CKP (CPOL) | CKE (CPHA) | BMODE | Explanation
//----------+------------+--------------------+------------------------------------------------
//  1 (0,1) |  0   (0)   |  0   (1)   | xx00  | idle low;  data out on falling/trailing edge
//  3 (1,1) |  1   (1)   |  0   (1)   | xx01  | idle high; data out on rising/trailing edge
//  0 (0,0) |  0   (0)   |  1   (0)   | xx10  | idle low;  data out on rising/leading edge
//  2 (1,0) |  1   (1)   |  1   (0)   | xx11  | idle high; data out on falling/leading edge
//----------+------------+---------------------------------------------------------------------
//
// So:
//     BMODE & 0x01 = CKP =  CPOL
//     BMODE & 0x02 = CKE = !CPHA


#if (MX_SPI_SLAVE_X != 1)	//Master Start

	#if (MX_SPI_CHANNEL_X > 0)
		//SPI Hardware Channel CS Warning
		#warning "Important user information. Please read."
		#warning "Hardware SPI may cause a lockup in your program if Hardware SS Pin is left as an input!";
		#warning "Suggest using the SS pin as the CS pin to ensure no lockup."
		#warning "SS pin must be set to an output or pulled high before initialising the SPI."
		#warning "Refer to the device datasheet for the SPI hardware SS pin.";
	#endif


	CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Init_, (void))
	{
		MX_UINT8 retVal = 1;

		FC_CAL_Bit_High_DDR (MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_TRIS_X, MX_SPI_MOSI_PIN_X);		// MOSI pin is default high
		FC_CAL_Bit_In_DDR   (MX_SPI_MISO_PORT_X, MX_SPI_MISO_TRIS_X, MX_SPI_MISO_PIN_X);		// MISO pin is a input

		#if (MX_SPI_BMODE_X & 0x01)
			FC_CAL_Bit_High_DDR (MX_SPI_SCK_PORT_X, MX_SPI_SCK_TRIS_X, MX_SPI_SCK_PIN_X);		// Clock pin is default high
		#else
			FC_CAL_Bit_Low_DDR  (MX_SPI_SCK_PORT_X, MX_SPI_SCK_TRIS_X, MX_SPI_SCK_PIN_X);		// Clock pin is default low
		#endif

		#if (MX_SPI_CHANNEL_X == 1)
		 //#ifndef MX_SPI_1
		 //	#error "SPI channel 1 not available on this device"
		 //#else
			#ifndef MX_XMEGA
			  #ifdef MX_USI
				USICR = (1 << USIWM0);
			  #else
				MX_UINT8 SPIConfig = 0;

				SPIConfig  = (1 << SPE);
				SPIConfig |= (1 << MSTR);
				SPIConfig |= (MX_SPI_PR_SCALE_HW & 0x07);
				#if (MX_SPI_BMODE_X & 0x01)							//Assign Clock Polarity
					SPIConfig |= (1 << CPOL);
				#endif
				#if ((MX_SPI_BMODE_X & 0x02) == 0)					//Assign Clock Phase
					SPIConfig |= (1 << CPHA);
				#endif
				SPCR = SPIConfig;									//Pass config settings to SPI register
			  #endif
			#else
				MX_UINT8 SPIConfig = 0;
				SPIConfig  = (1 << SPI_ENABLE_bp);
				SPIConfig |= (1 << SPI_MASTER_bp);
				SPIConfig |= (MX_SPI_PR_SCALE_HW & 0x03);
				SPIConfig |= ((MX_SPI_PR_SCALE_HW << 5) & 0x80);
				#if (MX_SPI_BMODE_X & 0x01)							//Assign Clock Polarity
					SPIConfig |= (1 << SPI_MODE0_bp);
				#endif
				#if ((MX_SPI_BMODE_X & 0x02) == 0)					//Assign Clock Phase
					SPIConfig |= (1 << SPI_MODE1_bp);
				#endif
				SPIC.CTRL = SPIConfig;
			#endif
		 //#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 2)
		 //#ifndef MX_SPI_2
		 //	#error "SPI channel 2 not available on this device"
		 //#else
			#ifndef MX_XMEGA
			#else
				MX_UINT8 SPIConfig = 0;
				SPIConfig  = (1 << SPI_ENABLE_bp);
				SPIConfig |= (1 << SPI_MASTER_bp);
				SPIConfig |= (MX_SPI_PR_SCALE_HW & 0x03);
				SPIConfig |= ((MX_SPI_PR_SCALE_HW << 5) & 0x80);
				#if (MX_SPI_BMODE_X & 0x01)							//Assign Clock Polarity
					SPIConfig |= (1 << SPI_MODE0_bp);
				#endif
				#if ((MX_SPI_BMODE_X & 0x02) == 0)					//Assign Clock Phase
					SPIConfig |= (1 << SPI_MODE1_bp);
				#endif
				SPID.CTRL = SPIConfig;
			#endif
		 //#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 3)
		 //#ifndef MX_SPI_3
		 //	#error "SPI channel 3 not available on this device"
		 //#else
			#ifndef MX_XMEGA
			#else
				MX_UINT8 SPIConfig = 0;
				SPIConfig  = (1 << SPI_ENABLE_bp);
				SPIConfig |= (1 << SPI_MASTER_bp);
				SPIConfig |= (MX_SPI_PR_SCALE_HW & 0x03);
				SPIConfig |= ((MX_SPI_PR_SCALE_HW << 5) & 0x80);
				#if (MX_SPI_BMODE_X & 0x01)							//Assign Clock Polarity
					SPIConfig |= (1 << SPI_MODE0_bp);
				#endif
				#if ((MX_SPI_BMODE_X & 0x02) == 0)					//Assign Clock Phase
					SPIConfig |= (1 << SPI_MODE1_bp);
				#endif
				SPIE.CTRL = SPIConfig;
			#endif
		 //#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 4)
		 //#ifndef MX_SPI_4
		 //	#error "SPI channel 4 not available on this device"
		 //#else
			#ifndef MX_XMEGA
			#else
				MX_UINT8 SPIConfig = 0;
				SPIConfig  = (1 << SPI_ENABLE_bp);
				SPIConfig |= (1 << SPI_MASTER_bp);
				SPIConfig |= (MX_SPI_PR_SCALE_HW & 0x03);
				SPIConfig |= ((MX_SPI_PR_SCALE_HW << 5) & 0x80);
				#if (MX_SPI_BMODE_X & 0x01)							//Assign Clock Polarity
					SPIConfig |= (1 << SPI_MODE0_bp);
				#endif
				#if ((MX_SPI_BMODE_X & 0x02) == 0)					//Assign Clock Phase
					SPIConfig |= (1 << SPI_MODE1_bp);
				#endif
				SPIF.CTRL = SPIConfig;
			#endif
		 //#endif
		#endif
		return (retVal);
	}


	CALFUNCTION(void, FC_CAL_SPI_Master_Uninit_, (void))
	{
		#if (MX_SPI_CHANNEL_X == 1)
			#ifndef MX_XMEGA
			  #ifdef MX_USI
				USICR = 0;
			  #else
				clear_bit(SPCR, SPE);
			  #endif
			#else
				clear_bit(SPIC.CTRL, SPI_ENABLE_bp);
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 2)
			#ifndef MX_XMEGA
			#else
				clear_bit(SPID.CTRL, SPI_ENABLE_bp);
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 3)
			#ifndef MX_XMEGA
			#else
				clear_bit(SPIE.CTRL, SPI_ENABLE_bp);
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 4)
			#ifndef MX_XMEGA
			#else
				clear_bit(SPIF.CTRL, SPI_ENABLE_bp);
			#endif
		#endif

		//Reset Pins to Inputs
		FC_CAL_Bit_In_DDR (MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_TRIS_X, MX_SPI_MOSI_PIN_X);
		FC_CAL_Bit_In_DDR (MX_SPI_MISO_PORT_X, MX_SPI_MISO_TRIS_X, MX_SPI_MISO_PIN_X);
		FC_CAL_Bit_In_DDR (MX_SPI_SCK_PORT_X, MX_SPI_SCK_TRIS_X, MX_SPI_SCK_PIN_X);
	}


	CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Byte_, (MX_UINT8 DataOut))
	{
		MX_UINT8 retVal = 0;

		#if (MX_SPI_CHANNEL_X == 0)

			MX_UINT8 idx, i;
			for (idx = 0; idx < 8; idx++)
			{
				retVal = retVal << 1;

				//If mode 1 or 3, switch the clock
				#if ((MX_SPI_BMODE_X & 0x02) == 0x00)									//CKE = 0; (mode 1 or 3) Set SCK active before data
					#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
						FC_CAL_Bit_High(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X);			//CKP = 0; (mode 1)
					#else
						FC_CAL_Bit_Low(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X);			//CKP = 1; (mode 3)
					#endif
				#endif

				//Data setup
				if (DataOut & 0x80)														//Test Data bit
					FC_CAL_Bit_High(MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_PIN_X);				//Set SDO bit
				else
					FC_CAL_Bit_Low (MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_PIN_X);				//Clear SDO bit

				//Clock delay
				for (i=0; i<MX_PRESCALE_VAR_X; i++)
					nop();

				//Switch clock - high for modes 0 and 3; low for modes 1 and 2
				#if ((MX_SPI_BMODE_X & 0x02) == 0x02)									//CKE = 1; (mode 0 or 2)
					#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
						FC_CAL_Bit_High(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X);			//CKP = 0; (mode 0)
					#else
						FC_CAL_Bit_Low(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X);			//CKP = 1; (mode 2)
					#endif
				#else
					#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
						FC_CAL_Bit_Low(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X);			//CKP = 0; (mode 1)
					#else
						FC_CAL_Bit_High(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X);			//CKP = 1; (mode 3)
					#endif
				#endif

				//Sample at middle of data output?
				#if ((MX_SPI_BMODE_X & 0x04) == 0)										//Sample at the middle of period
					if(FC_CAL_Bit_In(MX_SPI_MISO_PORT_X, MX_SPI_MISO_PIN_X))
						retVal = retVal | 0x01;
					else
						retVal = retVal & 0xFE;
				#endif

				//Clock delay
				for (i=0; i<MX_PRESCALE_VAR_X; i++)
					nop();

				//If mode 0 or 2, switch the clock
				#if ((MX_SPI_BMODE_X & 0x02) == 0x02)									//CKE = 1; (mode 0 or 2)																//CKE = 0; Set SCK idle after data
					#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
						FC_CAL_Bit_Low(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X);			//CKP = 0; (mode 0)
					#else
						FC_CAL_Bit_High(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X);			//CKP = 1; (mode 2)
					#endif
				#endif

				//Sample at end of data output?
				#if ((MX_SPI_BMODE_X & 0x04) == 0x04)									//Sample at the end of period
					if(FC_CAL_Bit_In(MX_SPI_MISO_PORT_X, MX_SPI_MISO_PIN_X))
						retVal = retVal | 0x01;
					else
						retVal = retVal & 0xFE;
				#endif

				DataOut = DataOut << 1;							//Move to next data bit
			}
		#endif

		#if (MX_SPI_CHANNEL_X == 1)
			#ifndef MX_XMEGA
			  #ifdef MX_USI
				unsigned int i;
				USISR = 0;
				USIDR = DataOut;
				for (i = 0; i < 8; i++)
				{
					USICR = (1 << USIWM0) | (1 << USITC);
					delay_us(1);
					USICR = (1 << USIWM0) | (1 << USITC) | (1 << USICLK);
					delay_us(1);
				}
				retVal = USIDR;
			  #else
				retVal = SPSR;							//Clear SPIF
				SPDR = DataOut;							//send data byte
				while ((SPSR & (1 << SPIF)) == 0);		//wait until sspbuf is empty
				retVal = SPDR;							//receive the Char
			  #endif
			#else
				SPIC.DATA = DataOut;								//send data byte
				while ((SPIC.STATUS & (1 << SPI_IF_bp)) == 0);		//wait until sspbuf is empty
				retVal = SPIC.DATA;									//receive the Char
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 2)
			#ifndef MX_XMEGA
			#else
				SPID.DATA = DataOut;								//send data byte
				while ((SPID.STATUS & (1 << SPI_IF_bp)) == 0);		//wait until sspbuf is empty
				retVal = SPID.DATA;									//receive the Char
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 3)
			#ifndef MX_XMEGA
			#else
				SPIE.DATA = DataOut;								//send data byte
				while ((SPIE.STATUS & (1 << SPI_IF_bp)) == 0);		//wait until sspbuf is empty
				retVal = SPIE.DATA;									//receive the Char
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 4)
			#ifndef MX_XMEGA
			#else
				SPIF.DATA = DataOut;								//send data byte
				while ((SPIF.STATUS & (1 << SPI_IF_bp)) == 0);		//wait until sspbuf is empty
				retVal = SPIF.DATA;									//receive the Char
			#endif
		#endif

		return (retVal);
	}


	CALFUNCTION(void, FC_CAL_SPI_SetPrescaler_, (MX_UINT8 Prescaler))
	{
		MX_PRESCALE_VAR_X = Prescaler;
		MX_UINT8 SPIConfig = 0;

		#if (MX_SPI_CHANNEL_X > 0)
			if (Prescaler == 0)			//1:2
				MX_PRESCALE_VAR_X =	4;
			if (Prescaler == 1)			//1:4
				MX_PRESCALE_VAR_X =	0;
			if (Prescaler == 2)			//1:8
				MX_PRESCALE_VAR_X =	5;
			if (Prescaler == 3)			//1:16
				MX_PRESCALE_VAR_X =	1;
			if (Prescaler == 4)			//1:32
				MX_PRESCALE_VAR_X =	6;
			if (Prescaler == 5)			//1:64
				MX_PRESCALE_VAR_X =	2;
			if (Prescaler == 6)			//1:128
				MX_PRESCALE_VAR_X =	7;
			if (Prescaler == 7)			//1:256
				MX_PRESCALE_VAR_X =	3;
		#endif

		#if (MX_SPI_CHANNEL_X == 1)
			#ifndef MX_XMEGA
			  #ifndef MX_USI
				SPIConfig = SPCR;
				SPIConfig &= 0xF8;
				SPIConfig |= (MX_PRESCALE_VAR_X & 0x07);
				SPCR = SPIConfig;
			  #endif
			#else
				SPIConfig = SPIC.CTRL;
				SPIConfig &= 0x7C;
				SPIConfig |= (MX_PRESCALE_VAR_X & 0x03);
				SPIConfig |= ((MX_PRESCALE_VAR_X << 5) & 0x80);
				SPIC.CTRL = SPIConfig;
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 2)
			#ifndef MX_XMEGA
			#else
				SPIConfig = SPID.CTRL;
				SPIConfig &= 0x7C;
				SPIConfig |= (MX_PRESCALE_VAR_X & 0x03);
				SPIConfig |= ((MX_PRESCALE_VAR_X << 5) & 0x80);
				SPID.CTRL = SPIConfig;
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 3)
			#ifndef MX_XMEGA
			#else
				SPIConfig = SPIE.CTRL;
				SPIConfig &= 0x7C;
				SPIConfig |= (MX_PRESCALE_VAR_X & 0x03);
				SPIConfig |= ((MX_PRESCALE_VAR_X << 5) & 0x80);
				SPIE.CTRL = SPIConfig;
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 4)
			#ifndef MX_XMEGA
			#else
				SPIConfig = SPIF.CTRL;
				SPIConfig &= 0x7C;
				SPIConfig |= (MX_PRESCALE_VAR_X & 0x03);
				SPIConfig |= ((MX_PRESCALE_VAR_X << 5) & 0x80);
				SPIF.CTRL = SPIConfig;
			#endif
		#endif
	}


	/**************************************************
		SPI Master Transaction based functions
	**************************************************/

	CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_Init_,   (void))
	{
		CALFUNCTION(, FC_CAL_SPI_Master_Init_, ());
		return 1;	// Success
	}

	CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_,   (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length))
	{
		if (Length > Size) return 0;
		MX_UINT16 n = 0;
		while (n < Length)
		{
			Buffer[n] = CALFUNCTION(, FC_CAL_SPI_Master_Byte_, (Buffer[n]));
			++n;
		}
		return 1;		// Success
	}

	CALFUNCTION(void, FC_CAL_SPI_Transaction_Uninit_, (void))
	{
		CALFUNCTION(, FC_CAL_SPI_Master_Uninit_, ());
	}

#endif		//End of Master



#if (MX_SPI_SLAVE_X == 1)		//Slave Start

	CALFUNCTION(void, FC_CAL_SPI_Slave_Init_, (void))
	{
		FC_CAL_Bit_High_DDR (MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_TRIS_X, MX_SPI_MOSI_PIN_X);		// MOSI pin is default high
		FC_CAL_Bit_In_DDR   (MX_SPI_MISO_PORT_X, MX_SPI_MISO_TRIS_X, MX_SPI_MISO_PIN_X);		// MISO pin is a input
		FC_CAL_Bit_In_DDR   (MX_SPI_SCK_PORT_X, MX_SPI_SCK_TRIS_X, MX_SPI_SCK_PIN_X);			// Clock pin is a input
		#if (MX_SPI_USESS_X == 1)
			FC_CAL_Bit_In_DDR   (MX_SPI_SS_PORT_X, MX_SPI_SS_TRIS_X, MX_SPI_SS_PIN_X);			// SS pin is a input
		#endif

		#if (MX_SPI_CHANNEL_X == 1)
			#ifndef MX_XMEGA
			  #ifdef MX_USI
				#error "AVR Devices with USI based SPI peripherals are not currently supported by SPI Slave functionality."
			  #else
				MX_UINT8 SPIConfig = 0;

				SPIConfig  = (1 << SPE);
				#if (MX_SPI_BMODE_X & 0x01)							//Assign Clock Polarity
					SPIConfig |= (1 << CPOL);
				#endif
				#if ((MX_SPI_BMODE_X & 0x02) == 0)					//Assign Clock Phase
					SPIConfig |= (1 << CPHA);
				#endif
				SPCR = SPIConfig;									//Pass config settings to SPI register
			  #endif
			#else
				MX_UINT8 SPIConfig = 0;
				SPIConfig  = (1 << SPI_ENABLE_bp);
				#if (MX_SPI_BMODE_X & 0x01)							//Assign Clock Polarity
					SPIConfig |= (1 << SPI_MODE0_bp);
				#endif
				#if ((MX_SPI_BMODE_X & 0x02) == 0)					//Assign Clock Phase
					SPIConfig |= (1 << SPI_MODE1_bp);
				#endif
				SPIC.CTRL = SPIConfig;
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 2)
			#ifndef MX_XMEGA
			#else
				MX_UINT8 SPIConfig = 0;
				SPIConfig  = (1 << SPI_ENABLE_bp);
				#if (MX_SPI_BMODE_X & 0x01)							//Assign Clock Polarity
					SPIConfig |= (1 << SPI_MODE0_bp);
				#endif
				#if ((MX_SPI_BMODE_X & 0x02) == 0)					//Assign Clock Phase
					SPIConfig |= (1 << SPI_MODE1_bp);
				#endif
				SPID.CTRL = SPIConfig;
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 3)
			#ifndef MX_XMEGA
			#else
				MX_UINT8 SPIConfig = 0;
				SPIConfig  = (1 << SPI_ENABLE_bp);
				#if (MX_SPI_BMODE_X & 0x01)							//Assign Clock Polarity
					SPIConfig |= (1 << SPI_MODE0_bp);
				#endif
				#if ((MX_SPI_BMODE_X & 0x02) == 0)					//Assign Clock Phase
					SPIConfig |= (1 << SPI_MODE1_bp);
				#endif
				SPIE.CTRL = SPIConfig;
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 4)
			#ifndef MX_XMEGA
			#else
				MX_UINT8 SPIConfig = 0;
				SPIConfig  = (1 << SPI_ENABLE_bp);
				#if (MX_SPI_BMODE_X & 0x01)							//Assign Clock Polarity
					SPIConfig |= (1 << SPI_MODE0_bp);
				#endif
				#if ((MX_SPI_BMODE_X & 0x02) == 0)					//Assign Clock Phase
					SPIConfig |= (1 << SPI_MODE1_bp);
				#endif
				SPIF.CTRL = SPIConfig;
			#endif
		#endif
	}

	CALFUNCTION(void, FC_CAL_SPI_Slave_Uninit_, (void))
	{
		#if (MX_SPI_CHANNEL_X == 1)
			#ifndef MX_XMEGA
			  #ifdef MX_USI
				USICR = 0;
			  #else
				clear_bit(SPCR, SPE);
			  #endif
			#else
				clear_bit(SPIC.CTRL, SPI_ENABLE_bp);
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 2)
			#ifndef MX_XMEGA
			#else
				clear_bit(SPID.CTRL, SPI_ENABLE_bp);
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 3)
			#ifndef MX_XMEGA
			#else
				clear_bit(SPIE.CTRL, SPI_ENABLE_bp);
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 4)
			#ifndef MX_XMEGA
			#else
				clear_bit(SPIF.CTRL, SPI_ENABLE_bp);
			#endif
		#endif

		//Reset Pins to Inputs
		FC_CAL_Bit_In_DDR (MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_TRIS_X, MX_SPI_MOSI_PIN_X);
		FC_CAL_Bit_In_DDR (MX_SPI_MISO_PORT_X, MX_SPI_MISO_TRIS_X, MX_SPI_MISO_PIN_X);
		FC_CAL_Bit_In_DDR (MX_SPI_SCK_PORT_X, MX_SPI_SCK_TRIS_X, MX_SPI_SCK_PIN_X);
	}

	CALFUNCTION(void, FC_CAL_SPI_Slave_TxByte_, (MX_UINT8 Data))
	{
		#if (MX_SPI_CHANNEL_X == 1)
			#ifndef MX_XMEGA
			  #ifdef MX_USI
			  #else
				SPDR = Data;									//send data byte
			  #endif
			#else
				SPIC.DATA = Data;								//send data byte
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 2)
			#ifndef MX_XMEGA
			#else
				SPID.DATA = Data;								//send data byte
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 3)
			#ifndef MX_XMEGA
			#else
				SPIE.DATA = Data;								//send data byte
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 4)
			#ifndef MX_XMEGA
			#else
				SPIF.DATA = Data;								//send data byte
			#endif
		#endif

	}

	CALFUNCTION(MX_UINT8, FC_CAL_SPI_Slave_RxByte_, (void))
	{
		MX_UINT8 retVal;

		#if (MX_SPI_CHANNEL_X == 1)
			#ifndef MX_XMEGA
			  #ifdef MX_USI
			  #else
				retVal = SPDR;										//receive the Char
			  #endif
			#else
				retVal = SPIC.DATA;									//receive the Char
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 2)
			#ifndef MX_XMEGA
			#else
				retVal = SPID.DATA;									//receive the Char
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 3)
			#ifndef MX_XMEGA
			#else
				retVal = SPIE.DATA;									//receive the Char
			#endif
		#endif

		#if (MX_SPI_CHANNEL_X == 4)
			#ifndef MX_XMEGA
			#else
				retVal = SPIF.DATA;									//receive the Char
			#endif
		#endif

		return(retVal);
	}

#endif			//Slave End


#undef MX_SPI_PR_SCALE_HW
