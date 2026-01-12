// CRC: AE5753800093D2B889297C6B876B6A21749C10AFA09C3FCE4A5F65B0FF76818F06F4274FDFAD3D87C5F8E545EDBF5F889A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5145603A7C180594AB174F5A2894DF8F1694B47468C92D6FF44AEDC3221DC781AE93EAE62ABE7FA0F93110EE34CBEA4A030956E686F40CECDEEC5148B44F002E103BBA10F783C5D87D38255A80EA8A428C6C3DA1732690348549D34A0D5AD11F33AFEEE7461EAD8C3FA764AFDB8DEC1A083AB6903D889079368F76F09E69EFC60247D7D36043FD9DE
// REVISION: 1.0
// GUID: 4B572772-B403-443A-BA6B-B85CF408B789
// DATE: 08\08\2022
// DIR: CAL\ARM\ARM_CAL_SPI.c
/*********************************************************************
 *                  Flowcode CAL SPI File
 *
 * File: PIC_CAL_SPI.c
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
 * 150911 | BR | Updated variables with typedef alternatives
 * 050312 | BR | Updated to v5.1 CAL Schema
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


//Setup Definitions
#ifdef MX_SPI_REF_X
	#if MX_SPI_CHANNEL_X > 0
		//Compatible Setting
		#if MX_SPI_PR_SCALE_X == 4
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0x08
		#endif
		#if MX_SPI_PR_SCALE_X == 6
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0x0C
		#endif
		#if MX_SPI_PR_SCALE_X == 12
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0x18
		#endif
		#if MX_SPI_PR_SCALE_X == 16
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0x20
		#endif
		#if MX_SPI_PR_SCALE_X == 24
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0x30
		#endif
		#if MX_SPI_PR_SCALE_X == 48
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X	0x60
		#endif
	#endif
#endif


#define MX_PRESCALE_VAR_X		CAL_APPEND(prescale_, MX_SPI_NUM)

MX_UINT8 MX_PRESCALE_VAR_X = (MX_SPI_PR_SCALE_X / 4) - 1;


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



CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Init_, (void))
{
	MX_UINT8 retVal = 1;

	FC_CAL_Bit_High_DDR (MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_TRIS_X, MX_SPI_MOSI_PIN_X);		// MOSI pin is default high
	FC_CAL_Bit_In_DDR   (MX_SPI_MISO_PORT_X, MX_SPI_MISO_TRIS_X, MX_SPI_MISO_PIN_X);		// MISO pin is a input

	#if (MX_SPI_BMODE_X & 0x02)
		FC_CAL_Bit_High_DDR (MX_SPI_SCK_PORT_X, MX_SPI_SCK_TRIS_X, MX_SPI_SCK_PIN_X);		// Clock pin is default high
	#else
		FC_CAL_Bit_Low_DDR  (MX_SPI_SCK_PORT_X, MX_SPI_SCK_TRIS_X, MX_SPI_SCK_PIN_X);		// Clock pin is default low
	#endif

	#if (MX_SPI_CHANNEL_X == 1)
	 //#ifndef MX_SPI_1
	 //	#error "SPI channel 1 not available on this device"
	 //#else
		AT91F_SPI_CfgPMC();
		AT91F_PIO_CfgPeriph( AT91C_BASE_PIOA, (unsigned int)AT91C_PA12_MISO | (unsigned int)AT91C_PA13_MOSI | (unsigned int)AT91C_PA14_SPCK, 0);
		AT91F_SPI_Reset(AT91C_BASE_SPI);
		AT91F_SPI_Enable(AT91C_BASE_SPI);
		AT91F_SPI_CfgMode(AT91C_BASE_SPI, 0xc0000013);
		AT91F_SPI_CfgCs(AT91C_BASE_SPI, 0, (MX_SPI_PR_SCALE_X << 8) | (MX_SPI_BMODE_X & 0x01) | (MX_SPI_BMODE_X & 0x02));

	 //#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
	 //#ifndef MX_SPI_2
	 //	#error "SPI channel 2 not available on this device"
	 //#else
		//ARM only has 1 SPI channel
   	 //#endif
  	#endif
	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_Master_Uninit_, (void))
{
	#if (MX_SPI_CHANNEL_X == 1)
		AT91F_SPI_Disable(AT91C_BASE_SPI);
		AT91F_PIO_CfgInput( AT91C_BASE_PIOA, (unsigned int)AT91C_PA12_MISO | (unsigned int)AT91C_PA13_MOSI | (unsigned int)AT91C_PA14_SPCK);
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		//ARM only has 1 SPI channel
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
		AT91F_SPI_PutChar(AT91C_BASE_SPI, DataOut, 0);				// Send outgoing byte
		while((AT91C_BASE_SPI->SPI_SR & AT91C_SPI_TXEMPTY) == 0);	// Wait for the transmit buffer to empty
		retVal = AT91F_SPI_GetChar(AT91C_BASE_SPI);					// Read the data
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		//ARM only has 1 SPI channel
	#endif

	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_SetPrescaler_, (MX_UINT8 Prescaler))
{
	MX_PRESCALE_VAR_X = Prescaler;

	#if (MX_SPI_CHANNEL_X > 0)
		if (Prescaler == 0)				//1:4
			MX_PRESCALE_VAR_X = 0x08;
		if (Prescaler == 1)				//1:6
			MX_PRESCALE_VAR_X = 0x0C;
		if (Prescaler == 2)				//1:12
			MX_PRESCALE_VAR_X = 0x18;
		if (Prescaler == 3)				//1:16
			MX_PRESCALE_VAR_X = 0x20;
		if (Prescaler == 4)				//1:24
			MX_PRESCALE_VAR_X = 0x30;
		if (Prescaler == 5)				//1:48
			MX_PRESCALE_VAR_X = 0x60;
	#endif

	#if (MX_SPI_CHANNEL_X == 1)
	 	AT91F_SPI_CfgCs(AT91C_BASE_SPI, 0, (MX_PRESCALE_VAR_X << 8) | (MX_SPI_BMODE_X & 0x01) | (MX_SPI_BMODE_X & 0x02));
	#endif
}




CALFUNCTION(void, FC_CAL_SPI_Slave_Init_, (void))
{

}

CALFUNCTION(void, FC_CAL_SPI_Slave_Uninit_, (void))
{

}

CALFUNCTION(void, FC_CAL_SPI_Slave_SetTxData_, (MX_UINT8 Data))
{

}

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Slave_GetRxData_, (void))
{
	return(0);
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



