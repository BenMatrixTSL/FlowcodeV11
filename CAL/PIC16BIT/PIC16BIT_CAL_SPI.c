// CRC: 5D982BB222882C54AB4AFF20A1590FC484D3178BD0D2510D0F5A64A7853221CAE2C33FABBE4F69A6659399D51781B7B962C5EB630D1FECDDCBEF1BA7CAEA61529A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF52132E60E2F83633AAEE42AECC2716E8F9B97968B46850D05B11FABA7FA747DEB8AF9254373EFEEC10C402CEF61DDF0938EEB578029F1ABDC8F22D5FB9CB3F24C123F9263CE2D18A76A9D8191DDEE02994236C4BB413250AA549D34A0D5AD11F3D80C5D7DEE0EA1E77BA796A6972DDEA75386E3E6C330420D1EF3C8BA6D793B2D3FD0D9AB4C2F44A0
// REVISION: 1.0
// GUID: 3021E4EA-0FB8-43C3-A3EB-86D3A1E52F2F
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\PIC16BIT_CAL_SPI.c
/*********************************************************************
 *                  Flowcode CAL SPI File
 *
 * File: PIC16BIT_CAL_SPI.c
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
 * 090911 | BR | Created
 * 050312 | BR | Updated to v5.1 CAL Schema
 * 200712 | BR | Added new macro to configure prescaler on the fly
 * 090812 | ST | Fixed initial clock polarity setting
 * 090812 | ST | Added comments to explain the BMODE settings and Master_Byte function
 * 170812 | BR | Removed unneeded #endif statements
 * 070912 | BR | Changed Remappable Functionality to be loaded from FCD
 * 110912 | BR | Added minor mod for SPI channel 2,3 and 4 for MX_SPICON devices
 * 140912 | BR | Chaned prescaler function to tie in with the FAT component
 * 181012 | LM | Dummy read to clear flags
 * 210613 | BR | Bug fix defines mod for HW SPI Prescaler - also related mods to init
 * 030713 | LM | Standard API calls
 * 280813 | LM | Removed MX_SPI_x define checks
 * 011214 | LM | dsPIC Manual: The SMP bit must be set only after setting the MSTEN bit.
 * 220118 | LM | Add transaction functions
 *
 */



//When using hardware SPI channels override port and pin conns with FCD conn definitions
//Only overwrite CS pin defines when using SPI in slave mode on a hardware channel
//Also sort out postscale and prescale options for hardware channels

#define MX_SPI_REF_X				CAL_APPEND(MX_SPI_REF, MX_SPI_NUM)
#define MX_SPI_CHANNEL_X			CAL_APPEND(MX_SPI_CHANNEL_, MX_SPI_NUM)
#define MX_SPI_MOSI_PIN_X			CAL_APPEND(MX_SPI_MOSI_PIN_, MX_SPI_NUM)
#define MX_SPI_MOSI_PORT_X			CAL_APPEND(MX_SPI_MOSI_PORT_, MX_SPI_NUM)
#define MX_SPI_MOSI_TRIS_X			CAL_APPEND(MX_SPI_MOSI_TRIS_, MX_SPI_NUM)
#define MX_SPI_MISO_PIN_X			CAL_APPEND(MX_SPI_MISO_PIN_, MX_SPI_NUM)
#define MX_SPI_MISO_PORT_X			CAL_APPEND(MX_SPI_MISO_PORT_, MX_SPI_NUM)
#define MX_SPI_MISO_TRIS_X			CAL_APPEND(MX_SPI_MISO_TRIS_, MX_SPI_NUM)
#define MX_SPI_SCK_PIN_X			CAL_APPEND(MX_SPI_SCK_PIN_, MX_SPI_NUM)
#define MX_SPI_SCK_PORT_X			CAL_APPEND(MX_SPI_SCK_PORT_, MX_SPI_NUM)
#define MX_SPI_SCK_TRIS_X			CAL_APPEND(MX_SPI_SCK_TRIS_, MX_SPI_NUM)
#define MX_SPI_CS_PIN_X				CAL_APPEND(MX_SPI_CS_PIN_, MX_SPI_NUM)
#define MX_SPI_CS_PORT_X			CAL_APPEND(MX_SPI_CS_PORT_, MX_SPI_NUM)
#define MX_SPI_CS_TRIS_X			CAL_APPEND(MX_SPI_CS_TRIS_, MX_SPI_NUM)
#define MX_SPI_BMODE_X				CAL_APPEND(MX_SPI_BMODE_, MX_SPI_NUM)
#define MX_SPI_PR_SCALE_X			CAL_APPEND(MX_SPI_PR_SCALE_, MX_SPI_NUM)
#define MX_SPI_PO_SCALE_X			CAL_APPEND(MX_SPI_PO_SCALE_, MX_SPI_NUM)
#define MX_SPI_INT_X				CAL_APPEND(MX_SPI_INT_, MX_SPI_NUM)
#define MX_SPI_REMAPPABLE_X			CAL_APPEND(MX_SPI_REMAPPABLE_, MX_SPI_NUM)
#define MX_SPI_MISO_RPINR_X			CAL_APPEND(MX_SPI_MISO_RPINR_, MX_SPI_NUM)
#define MX_SPI_MISO_RP_X			CAL_APPEND(MX_SPI_MISO_RP_, MX_SPI_NUM)
#define MX_SPI_MOSI_RPOR_X			CAL_APPEND(MX_SPI_MOSI_RPOR_, MX_SPI_NUM)
#define MX_SPI_MOSI_SDO_X			CAL_APPEND(MX_SPI_MOSI_SDO_, MX_SPI_NUM)
#define MX_SPI_CLK_RPOR_X			CAL_APPEND(MX_SPI_CLK_RPOR_, MX_SPI_NUM)
#define MX_SPI_CLK_SCK_X			CAL_APPEND(MX_SPI_CLK_SCK_, MX_SPI_NUM)
#define MX_SPI_CLK_RPINR_X			CAL_APPEND(MX_SPI_CLK_RPINR_, MX_SPI_NUM)
#define MX_SPI_CLK_RP_X				CAL_APPEND(MX_SPI_CLK_RP_, MX_SPI_NUM)
#define MX_SPI_USESS_X				CAL_APPEND(MX_SPI_USESS_, MX_SPI_NUM)
#define MX_SPI_SS_RPINR_X			CAL_APPEND(MX_SPI_SS_RPINR_, MX_SPI_NUM)
#define MX_SPI_SS_RP_X				CAL_APPEND(MX_SPI_SS_RP_, MX_SPI_NUM)
#define MX_SPI_SLAVE_X				CAL_APPEND(MX_SPI_SLAVE_, MX_SPI_NUM)
#define MX_SPI_SS_ALT_X				CAL_APPEND(MX_SPI_SS_ALT_, MX_SPI_NUM)
#define MX_SPI_SS_REG_X				CAL_APPEND(MX_SPI_SS_REG_, MX_SPI_NUM)
#define MX_SPI_SS_MSK_X				CAL_APPEND(MX_SPI_SS_MSK_, MX_SPI_NUM)
#define MX_SPI_SS_PIN_X				CAL_APPEND(MX_SPI_SS_PIN_, MX_SPI_NUM)
#define MX_SPI_SS_PORT_X			CAL_APPEND(MX_SPI_SS_PORT_, MX_SPI_NUM)
#define MX_SPI_SS_TRIS_X			CAL_APPEND(MX_SPI_SS_TRIS_, MX_SPI_NUM)

//Setup Definitions
#ifdef MX_SPI_REF_X
	#if MX_SPI_CHANNEL_X > 0
		#if MX_SPI_PR_SCALE_X == 2
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b11011
		#endif
		#if MX_SPI_PR_SCALE_X == 4
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b11110
		#endif
		#if MX_SPI_PR_SCALE_X == 6
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b01011
		#endif
		#if MX_SPI_PR_SCALE_X == 8
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b00011
		#endif
		#if MX_SPI_PR_SCALE_X == 12
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b10110
		#endif
		#if MX_SPI_PR_SCALE_X == 16
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b11101
		#endif
		#if MX_SPI_PR_SCALE_X == 20
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b01110
		#endif
		#if MX_SPI_PR_SCALE_X == 24
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b01010
		#endif
		#if MX_SPI_PR_SCALE_X == 28
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b00110
		#endif
		#if MX_SPI_PR_SCALE_X == 32
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b11001
		#endif
		#if MX_SPI_PR_SCALE_X == 48
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b10101
		#endif
		#if MX_SPI_PR_SCALE_X == 64
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b11100
		#endif
		#if MX_SPI_PR_SCALE_X == 128
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b11000
		#endif
		#if MX_SPI_PR_SCALE_X == 192
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b10100
		#endif
		#if MX_SPI_PR_SCALE_X == 256
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b10000
		#endif
		#if MX_SPI_PR_SCALE_X == 512
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0b00000
		#endif
	#endif
#endif


#define MX_PRESCALE_VAR_X		CAL_APPEND(prescale_, MX_SPI_NUM)

MX_UINT16 MX_PRESCALE_VAR_X = MX_SPI_PR_SCALE_X;


//Function Prototypes
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Init_, (void));
CALFUNCTION(void, FC_CAL_SPI_Master_Uninit_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Byte_, (MX_UINT8 DataOut));
CALFUNCTION(void, FC_CAL_SPI_SetPrescaler_, (MX_UINT8 Prescaler));

CALFUNCTION(void, FC_CAL_SPI_Slave_Init_, (void));
CALFUNCTION(void, FC_CAL_SPI_Slave_Uninit_, (void));
CALFUNCTION(void, FC_CAL_SPI_Slave_SetTxData_, (MX_UINT8 Data));
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Slave_GetRxData_, (void));

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_Init_,   (void));
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_,   (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length));
CALFUNCTION(void,     FC_CAL_SPI_Transaction_Uninit_, (void));


#ifdef MX_SPI1CON
	#define SPI1CON1		SPI1CON
	#define SPI1CON1bits	SPI1CONbits
	#define SPI2CON1		SPI2CON
	#define SPI2CON1bits	SPI2CONbits
	#define SPI3CON1		SPI3CON
	#define SPI3CON1bits	SPI3CONbits
	#define SPI4CON1		SPI4CON
	#define SPI4CON1bits	SPI4CONbits
#endif



//Bus Mode - Bit0=CKP=CPOL, Bit1=CKE=!CPHA, Bit2=CSMP
//CKP=CPOL - Clock Polarity - Idle State of the clock 0=0, 1=1
//CKE=CPHA - Clock Phase - Clock Edge 0=leading edge, 1=trailing edge
//CSMP - Input Data Bit Sample Phase
//CRAT - SPI Clock Rate 0=1/4, 1=1/16, 2=1/64

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

	#if (MX_SPI_REMAPPABLE_X == 1)
		MX_SPI_MISO_RPINR_X = MX_SPI_MISO_RP_X;
		MX_SPI_MOSI_RPOR_X = MX_SPI_MOSI_SDO_X;
		MX_SPI_CLK_RPOR_X = MX_SPI_CLK_SCK_X;			//For some reason the SPI clock is not included in the remap on PIC32
	#endif

	#if (MX_SPI_CHANNEL_X == 1)

		SPI1CON1 = MX_SPI_PR_SCALE_X & 0x1F;					//Assign Clock Prescalers
		SPI1CON1bits.MSTEN = 1;									//master mode
		SPI1CON1bits.CKP = MX_SPI_BMODE_X & 0x01;				//Assign Clock Polarity
		SPI1CON1bits.CKE = (MX_SPI_BMODE_X & 0x02) >> 1;		//Assign Clock Phase
		SPI1CON1bits.SMP = (MX_SPI_BMODE_X & 0x04) >> 2;		//Assign Input Data Phase

		#ifdef SPI1STATL
			SPI1STATLbits.SPIROV = 0;							//clear unread data flag
			SPI1CON1bits.SPIEN = 1;								//enable SPI peripheral
		#else
			SPI1STATbits.SPIROV = 0;							//clear unread data flag
			SPI1STATbits.SPIEN = 1;								//enable SPI peripheral
		#endif

	#endif

	#if (MX_SPI_CHANNEL_X == 2)

		SPI2CON1 = MX_SPI_PR_SCALE_X & 0x1F;					//Assign Clock Prescalers
		SPI2CON1bits.MSTEN = 1;									//master mode
		SPI2CON1bits.CKP = MX_SPI_BMODE_X & 0x01;				//Assign Clock Polarity
		SPI2CON1bits.CKE = (MX_SPI_BMODE_X & 0x02) >> 1;		//Assign Clock Phase
		SPI2CON1bits.SMP = (MX_SPI_BMODE_X & 0x04) >> 2;		//Assign Input Data Phase

		#ifdef SPI2STATL
			SPI2STATLbits.SPIROV = 0;							//clear unread data flag
			SPI2CON1bits.SPIEN = 1;								//enable SPI peripheral
		#else
			SPI2STATbits.SPIROV = 0;							//clear unread data flag
			SPI2STATbits.SPIEN = 1;								//enable SPI peripheral
		#endif

	#endif

	#if (MX_SPI_CHANNEL_X == 3)

		SPI3CON1 = MX_SPI_PR_SCALE_X & 0x1F;					//Assign Clock Prescalers
		SPI3CON1bits.MSTEN = 1;									//master mode
		SPI3CON1bits.CKP = MX_SPI_BMODE_X & 0x01;				//Assign Clock Polarity
		SPI3CON1bits.CKE = (MX_SPI_BMODE_X & 0x02) >> 1;		//Assign Clock Phase
		SPI3CON1bits.SMP = (MX_SPI_BMODE_X & 0x04) >> 2;		//Assign Input Data Phase

		#ifdef SPI3STATL
			SPI3STATLbits.SPIROV = 0;							//clear unread data flag
			SPI3CON1bits.SPIEN = 1;								//enable SPI peripheral
		#else
			SPI3STATbits.SPIROV = 0;							//clear unread data flag
			SPI3STATbits.SPIEN = 1;								//enable SPI peripheral
		#endif

	#endif

	#if (MX_SPI_CHANNEL_X == 4)

		SPI4CON1 = MX_SPI_PR_SCALE_X & 0x1F;					//Assign Clock Prescalers
		SPI4CON1bits.MSTEN = 1;									//master mode
		SPI4CON1bits.CKP = MX_SPI_BMODE_X & 0x01;				//Assign Clock Polarity
		SPI4CON1bits.CKE = (MX_SPI_BMODE_X & 0x02) >> 1;		//Assign Clock Phase
		SPI4CON1bits.SMP = (MX_SPI_BMODE_X & 0x04) >> 2;		//Assign Input Data Phase

		#ifdef SPI4STATL
			SPI4STATLbits.SPIROV = 0;							//clear unread data flag
			SPI4CON1bits.SPIEN = 1;								//enable SPI peripheral
		#else
			SPI4STATbits.SPIROV = 0;							//clear unread data flag
			SPI4STATbits.SPIEN = 1;								//enable SPI peripheral
		#endif

	#endif
	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_Master_Uninit_, (void))
{
	#if (MX_SPI_CHANNEL_X == 1)
		#ifdef SPI1STATL
			SPI1CON1bits.SPIEN = 0;								//disable SPI peripheral
		#else
			SPI1STATbits.SPIEN = 0;								//disable SPI peripheral
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		#ifdef SPI2STATL
			SPI2CON1bits.SPIEN = 0;								//disable SPI peripheral
		#else
			SPI2STATbits.SPIEN = 0;								//disable SPI peripheral
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 3)
		#ifdef SPI3STATL
			SPI3CON1bits.SPIEN = 0;								//disable SPI peripheral
		#else
			SPI3STATbits.SPIEN = 0;								//disable SPI peripheral
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 4)
		#ifdef SPI4STATL
			SPI4CON1bits.SPIEN = 0;								//disable SPI peripheral
		#else
			SPI4STATbits.SPIEN = 0;								//disable SPI peripheral
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

		MX_UINT8 idx;
		MX_UINT16 i;
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
			#if ((MX_SPI_BMODE_X & 0x02) == 0x02)									//CKE = 1; (mode 0 or 2)
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

		#ifdef SPI1BUFL
			retVal = SPI1BUFL;						// dummy read to clear flags
			SPI1BUFL = DataOut;						//send outgoing byte
		#else
			retVal = SPI1BUF;						// dummy read to clear flags
			SPI1BUF = DataOut;						//send outgoing byte
		#endif

		#ifdef SPI1STATL
			while (SPI1STATLbits.SPIRBF == 0);		//wait until data has been sent
		#else
			while (SPI1STATbits.SPIRBF == 0);		//wait until data has been sent
		#endif

		#ifdef SPI1BUFL
			retVal = SPI1BUFL;						//receive the byte
		#else
			retVal = SPI1BUF;						//receive the byte
		#endif

	#endif

	#if (MX_SPI_CHANNEL_X == 2)

		#ifdef SPI2BUFL
			retVal = SPI2BUFL;						// dummy read to clear flags
			SPI2BUFL = DataOut;						//send outgoing byte
		#else
			retVal = SPI2BUF;						// dummy read to clear flags
			SPI2BUF = DataOut;						//send outgoing byte
		#endif

		#ifdef SPI2STATL
			while (SPI2STATLbits.SPIRBF == 0);		//wait until data has been sent
		#else
			while (SPI2STATbits.SPIRBF == 0);		//wait until data has been sent
		#endif

		#ifdef SPI2BUFL
			retVal = SPI2BUFL;						//receive the byte
		#else
			retVal = SPI2BUF;						//receive the byte
		#endif

	#endif

	#if (MX_SPI_CHANNEL_X == 3)

		#ifdef SPI3BUFL
			retVal = SPI3BUFL;					// dummy read to clear flags
			SPI3BUFL = DataOut;					//send outgoing byte
		#else
			retVal = SPI3BUF;					// dummy read to clear flags
			SPI3BUF = DataOut;					//send outgoing byte
		#endif

		#ifdef SPI3STATL
			while (SPI3STATLbits.SPIRBF == 0);		//wait until data has been sent
		#else
			while (SPI3STATbits.SPIRBF == 0);		//wait until data has been sent
		#endif

		#ifdef SPI3BUFL
			retVal = SPI3BUFL;						//receive the byte
		#else
			retVal = SPI3BUF;						//receive the byte
		#endif

	#endif

	#if (MX_SPI_CHANNEL_X == 4)

		#ifdef SPI4BUFL
			retVal = SPI4BUFL;					// dummy read to clear flags
			SPI4BUFL = DataOut;					//send outgoing byte
		#else
			retVal = SPI4BUF;					// dummy read to clear flags
			SPI4BUF = DataOut;					//send outgoing byte
		#endif

		#ifdef SPI4STATL
			while (SPI4STATLbits.SPIRBF == 0);		//wait until data has been sent
		#else
			while (SPI4STATbits.SPIRBF == 0);		//wait until data has been sent
		#endif

		#ifdef SPI4BUFL
			retVal = SPI4BUFL;						//receive the byte
		#else
			retVal = SPI4BUF;						//receive the byte
		#endif

	#endif

	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_SetPrescaler_, (MX_UINT8 Prescaler))
{
	MX_PRESCALE_VAR_X = Prescaler;

	#if (MX_SPI_CHANNEL_X > 0)
		if (Prescaler == 0)					//1:2
			MX_PRESCALE_VAR_X = 0b11011;
		else if (Prescaler == 1)			//1:4
			MX_PRESCALE_VAR_X = 0b11110;
		else if (Prescaler == 2)			//1:6
			MX_PRESCALE_VAR_X = 0b01011;
		else if (Prescaler == 3)			//1:8
			MX_PRESCALE_VAR_X = 0b00011;
		else if (Prescaler == 4)			//1:12
			MX_PRESCALE_VAR_X = 0b10110;
		else if (Prescaler == 5)			//1:16
			MX_PRESCALE_VAR_X = 0b11101;
		else if (Prescaler == 6)			//1:20
			MX_PRESCALE_VAR_X = 0b01110;
		else if (Prescaler == 7)			//1:24
			MX_PRESCALE_VAR_X = 0b01010;
		else if (Prescaler == 8)			//1:28
			MX_PRESCALE_VAR_X = 0b00110;
		else if (Prescaler == 9)			//1:32
			MX_PRESCALE_VAR_X = 0b11001;
		else if (Prescaler == 10)			//1:48
			MX_PRESCALE_VAR_X = 0b10101;
		else if (Prescaler == 11)			//1:64
			MX_PRESCALE_VAR_X = 0b11100;
		else if (Prescaler == 12)			//1:128
			MX_PRESCALE_VAR_X = 0b11000;
		else if (Prescaler == 13)			//1:192
			MX_PRESCALE_VAR_X = 0b10100;
		else if (Prescaler == 14)			//1:256
			MX_PRESCALE_VAR_X = 0b10000;
		else if (Prescaler == 15)			//1:512
			MX_PRESCALE_VAR_X = 0b00000;
	#endif

	#if (MX_SPI_CHANNEL_X == 1)

		#ifdef SPI1STATL
			SPI1CON1bits.SPIEN = 0;								//Disable SPI peripheral
		#else
			SPI1STATbits.SPIEN = 0;								//Disable SPI peripheral
		#endif

		SPI1CON1 = SPI1CON1 & 0xFFE0;
		SPI1CON1 = SPI1CON1 | (MX_PRESCALE_VAR_X & 0x1F);		//Assign Clock Prescalers

		#ifdef SPI1STATL
			SPI1CON1bits.SPIEN = 1;								//Re-enable SPI peripheral
		#else
			SPI1STATbits.SPIEN = 1;								//Re-enable SPI peripheral
		#endif

	#endif

	#if (MX_SPI_CHANNEL_X == 2)

		#ifdef SPI2STATL
			SPI2CON1bits.SPIEN = 0;								//Disable SPI peripheral
		#else
			SPI2STATbits.SPIEN = 0;								//Disable SPI peripheral
		#endif

		SPI2CON1 = SPI2CON1 & 0xFFE0;
		SPI2CON1 = SPI2CON1 | (MX_PRESCALE_VAR_X & 0x1F);		//Assign Clock Prescalers

		#ifdef SPI2STATL
			SPI2CON1bits.SPIEN = 1;								//Re-enable SPI peripheral
		#else
			SPI2STATbits.SPIEN = 1;								//Re-enable SPI peripheral
		#endif

	#endif

	#if (MX_SPI_CHANNEL_X == 3)

		#ifdef SPI3STATL
			SPI3CON1bits.SPIEN = 0;								//Disable SPI peripheral
		#else
			SPI3STATbits.SPIEN = 0;								//Disable SPI peripheral
		#endif

		SPI3CON1 = SPI3CON1 & 0xFFE0;
		SPI3CON1 = SPI3CON1 | (MX_PRESCALE_VAR_X & 0x1F);		//Assign Clock Prescalers

		#ifdef SPI3STATL
			SPI3CON1bits.SPIEN = 1;								//Re-enable SPI peripheral
		#else
			SPI3STATbits.SPIEN = 1;								//Re-enable SPI peripheral
		#endif

	#endif

	#if (MX_SPI_CHANNEL_X == 4)

		#ifdef SPI4STATL
			SPI4CON1bits.SPIEN = 0;								//Disable SPI peripheral
		#else
			SPI4STATbits.SPIEN = 0;								//Disable SPI peripheral
		#endif

		SPI4CON1 = SPI4CON1 & 0xFFE0;
		SPI4CON1 = SPI4CON1 | (MX_PRESCALE_VAR_X & 0x1F);		//Assign Clock Prescalers

		#ifdef SPI4STATL
			SPI4CON1bits.SPIEN = 1;								//Re-enable SPI peripheral
		#else
			SPI4STATbits.SPIEN = 1;								//Re-enable SPI peripheral
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

	#if (MX_SPI_REMAPPABLE_X == 1)									//Remappable I/O
		MX_SPI_MISO_RPINR_X = MX_SPI_MISO_RP_X;						//Data In
		MX_SPI_MOSI_RPOR_X = MX_SPI_MOSI_SDO_X;						//Data Out
		MX_SPI_CLK_RPINR_X = MX_SPI_CLK_RP_X;						//Clock In
		#if (MX_SPI_USESS_X == 1)
			MX_SPI_SS_RPINR_X = MX_SPI_SS_RP_X;						//SS In
		#endif
	#endif

	#if (MX_SPI_SS_ALT_X == 1)										//Alt SS Pin
		MX_SPI_SS_REG_X |= MX_SPI_SS_MSK_X;							//Enable alternate SS pin
	#endif

	#if (MX_SPI_CHANNEL_X == 1)

		SPI1CON1bits.MSTEN = 0;									//Slave mode
		SPI1CON1bits.CKP = MX_SPI_BMODE_X & 0x01;				//Assign Clock Polarity
		SPI1CON1bits.CKE = (MX_SPI_BMODE_X & 0x02) >> 1;		//Assign Clock Phase
		SPI1CON1bits.SMP = (MX_SPI_BMODE_X & 0x04) >> 2;		//Assign Input Data Phase

		#ifdef SPI1BUFL
			SPI1BUFL = 0;										//Clear outgoing byte
		#else
			SPI1BUF = 0;										//Clear outgoing byte
		#endif

		#if (MX_SPI_USESS_X == 1)
			SPI1CON1bits.SSEN = 1;								//Assign Slave Mode - Use SS Pin - Active Low
		#else
			SPI1CON1bits.SSEN = 0;								//Assign Slave Mode - No SS Pin
		#endif

		#ifdef SPI1STATL
			SPI1STATLbits.SPIROV = 0;							//clear unread data flag
			SPI1CON1bits.SPIEN = 1;								//enable SPI peripheral
		#else
			SPI1STATbits.SPIROV = 0;							//clear unread data flag
			SPI1STATbits.SPIEN = 1;								//enable SPI peripheral
		#endif

	#endif

	#if (MX_SPI_CHANNEL_X == 2)

		SPI2CON1bits.MSTEN = 0;									//Slave mode
		SPI2CON1bits.CKP = MX_SPI_BMODE_X & 0x01;				//Assign Clock Polarity
		SPI2CON1bits.CKE = (MX_SPI_BMODE_X & 0x02) >> 1;		//Assign Clock Phase
		SPI2CON1bits.SMP = (MX_SPI_BMODE_X & 0x04) >> 2;		//Assign Input Data Phase

		#ifdef SPI2BUFL
			SPI2BUFL = 0;										//Clear outgoing byte
		#else
			SPI2BUF = 0;										//Clear outgoing byte
		#endif

		#if (MX_SPI_USESS_X == 1)
			SPI2CON1bits.SSEN = 1;								//Assign Slave Mode - Use SS Pin - Active Low
		#else
			SPI2CON1bits.SSEN = 0;								//Assign Slave Mode - No SS Pin
		#endif

		#ifdef SPI2STATL
			SPI2STATLbits.SPIROV = 0;							//clear unread data flag
			SPI2CON1bits.SPIEN = 1;								//enable SPI peripheral
		#else
			SPI2STATbits.SPIROV = 0;							//clear unread data flag
			SPI2STATbits.SPIEN = 1;								//enable SPI peripheral
		#endif

	#endif

	#if (MX_SPI_CHANNEL_X == 3)

		SPI3CON1bits.MSTEN = 0;									//Slave mode
		SPI3CON1bits.CKP = MX_SPI_BMODE_X & 0x01;				//Assign Clock Polarity
		SPI3CON1bits.CKE = (MX_SPI_BMODE_X & 0x02) >> 1;		//Assign Clock Phase
		SPI3CON1bits.SMP = (MX_SPI_BMODE_X & 0x04) >> 2;		//Assign Input Data Phase

		#ifdef SPI3BUFL
			SPI3BUFL = 0;										//Clear outgoing byte
		#else
			SPI3BUF = 0;										//Clear outgoing byte
		#endif

		#if (MX_SPI_USESS_X == 1)
			SPI3CON1bits.SSEN = 1;								//Assign Slave Mode - Use SS Pin - Active Low
		#else
			SPI3CON1bits.SSEN = 0;								//Assign Slave Mode - No SS Pin
		#endif

		#ifdef SPI3STATL
			SPI3STATLbits.SPIROV = 0;							//clear unread data flag
			SPI3CON1bits.SPIEN = 1;								//enable SPI peripheral
		#else
			SPI3STATbits.SPIROV = 0;							//clear unread data flag
			SPI3STATbits.SPIEN = 1;								//enable SPI peripheral
		#endif

	#endif

	#if (MX_SPI_CHANNEL_X == 4)

		SPI4CON1bits.MSTEN = 0;									//Slave mode
		SPI4CON1bits.CKP = MX_SPI_BMODE_X & 0x01;				//Assign Clock Polarity
		SPI4CON1bits.CKE = (MX_SPI_BMODE_X & 0x02) >> 1;		//Assign Clock Phase
		SPI4CON1bits.SMP = (MX_SPI_BMODE_X & 0x04) >> 2;		//Assign Input Data Phase

		#ifdef SPI4BUFL
			SPI4BUFL = 0;										//Clear outgoing byte
		#else
			SPI4BUF = 0;										//Clear outgoing byte
		#endif

		#if (MX_SPI_USESS_X == 1)
			SPI4CON1bits.SSEN = 1;								//Assign Slave Mode - Use SS Pin - Active Low
		#else
			SPI4CON1bits.SSEN = 0;								//Assign Slave Mode - No SS Pin
		#endif

		#ifdef SPI4STATL
			SPI4STATLbits.SPIROV = 0;							//clear unread data flag
			SPI4CON1bits.SPIEN = 1;								//enable SPI peripheral
		#else
			SPI4STATbits.SPIROV = 0;							//clear unread data flag
			SPI4STATbits.SPIEN = 1;								//enable SPI peripheral
		#endif

	#endif

}

CALFUNCTION(void, FC_CAL_SPI_Slave_Uninit_, (void))
{
	#if (MX_SPI_CHANNEL_X == 1)
		#ifdef SPI1STATL
			SPI1CON1bits.SPIEN = 0;								//disable SPI peripheral
		#else
			SPI1STATbits.SPIEN = 0;								//disable SPI peripheral
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		#ifdef SPI2STATL
			SPI2CON1bits.SPIEN = 0;								//disable SPI peripheral
		#else
			SPI2STATbits.SPIEN = 0;								//disable SPI peripheral
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 3)
		#ifdef SPI3STATL
			SPI3CON1bits.SPIEN = 0;								//disable SPI peripheral
		#else
			SPI3STATbits.SPIEN = 0;								//disable SPI peripheral
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 4)
		#ifdef SPI4STATL
			SPI4CON1bits.SPIEN = 0;								//disable SPI peripheral
		#else
			SPI4STATbits.SPIEN = 0;								//disable SPI peripheral
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
		#ifdef SPI1BUFL
			SPI1BUFL = Data;				//Specify outgoing byte
		#else
			SPI1BUF = Data;					//Specify outgoing byte
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		#ifdef SPI2BUFL
			SPI2BUFL = Data;				//Specify outgoing byte
		#else
			SPI2BUF = Data;					//Specify outgoing byte
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 3)
		#ifdef SPI3BUFL
			SPI3BUFL = Data;				//Specify outgoing byte
		#else
			SPI3BUF = Data;					//Specify outgoing byte
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 4)
		#ifdef SPI4BUFL
			SPI4BUFL = Data;				//Specify outgoing byte
		#else
			SPI4BUF = Data;					//Specify outgoing byte
		#endif
	#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Slave_RxByte_, (void))
{
	MX_UINT8 retVal = 0;

	#if (MX_SPI_CHANNEL_X == 1)
		#ifdef SPI1BUFL
			retVal = SPI1BUFL;				//Collect incoming byte
		#else
			retVal = SPI1BUF;				//Collect incoming byte
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		#ifdef SPI2BUFL
			retVal = SPI2BUFL;				//Collect incoming byte
		#else
			retVal = SPI2BUF;				//Collect incoming byte
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 3)
		#ifdef SPI3BUFL
			retVal = SPI3BUFL;				//Collect incoming byte
		#else
			retVal = SPI3BUF;				//Collect incoming byte
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 4)
		#ifdef SPI4BUFL
			retVal = SPI4BUFL;				//Collect incoming byte
		#else
			retVal = SPI4BUF;				//Collect incoming byte
		#endif
	#endif

	return(retVal);
}


#endif			//Slave End


#undef MX_SPI_PR_SCALE_X
