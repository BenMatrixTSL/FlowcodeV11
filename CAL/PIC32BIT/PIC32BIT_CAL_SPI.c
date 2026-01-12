// CRC: A6459004C43C0517DC6DFC5681C2AD698104299A14C9E1875427A2F7EF4303D9CFD76A29863CD488DE50EA9D9C0AC8D162C5EB630D1FECDDCBEF1BA7CAEA61529A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF57BBE0552F45ABACCEB7694B50B9F2CEA38F6F216FC462CC374752247DC4A8650886BC6122699E279E3FD2A9B520FCA62A855C782C84E4D898ACC637BEC8BCC2F7AEB038F52C8F61064FB6511252792F79AD75B158F43CD60549D34A0D5AD11F37BEC7342D161E7CA300BD3F7A1321EB341C268744ECC3770BCC7899FCA2DDCC03543C1004297ACD4
// REVISION: 1.0
// GUID: F5E98872-8257-4E6E-9471-35649561F0B4
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\PIC32BIT_CAL_SPI.c
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


//Setup Definitions
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
#define MX_SPI_REMAPPABLE_SCK_X		CAL_APPEND(MX_SPI_REMAPPABLE_SCK_, MX_SPI_NUM)
#define MX_SPI_MISO_RPINR_X			CAL_APPEND(MX_SPI_MISO_RPINR_, MX_SPI_NUM)
#define MX_SPI_MISO_RP_X			CAL_APPEND(MX_SPI_MISO_RP_, MX_SPI_NUM)
#define MX_SPI_MOSI_RPOR_X			CAL_APPEND(MX_SPI_MOSI_RPOR_, MX_SPI_NUM)
#define MX_SPI_MOSI_SDO_X			CAL_APPEND(MX_SPI_MOSI_SDO_, MX_SPI_NUM)
#define MX_SPI_CLK_RPOR_X			CAL_APPEND(MX_SPI_CLK_RPOR_, MX_SPI_NUM)
#define MX_SPI_CLK_SCK_X			CAL_APPEND(MX_SPI_CLK_SCK_, MX_SPI_NUM)



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


#if (MX_SPI_CHANNEL_X == 0)
	MX_UINT8 MX_PRESCALE_VAR_X = MX_SPI_PR_SCALE_X;
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

		#if (MX_SPI_REMAPPABLE_SCK_X != 1)					//1 == No Clock Available
			MX_SPI_CLK_RPOR_X = MX_SPI_CLK_SCK_X;			//For some reason the SPI clock is not included in the remap on PIC32MX and PIC32MZ but is there on PIC32MM
		#endif

	#endif

	#if (MX_SPI_CHANNEL_X == 1)

		if (MX_SPI_BMODE_X & 0x01)		//Clock Polarity
			SPI1CONbits.CKP = 1;
		else
			SPI1CONbits.CKP = 0;

		if (MX_SPI_BMODE_X & 0x02)		//Clock Edge
			SPI1CONbits.CKE = 1;
		else
			SPI1CONbits.CKE = 0;

		if (MX_SPI_BMODE_X & 0x04)		//Sample Phase
			SPI1CONbits.SMP = 1;
		else
			SPI1CONbits.SMP = 0;

		SPI1BRG = MX_SPI_PR_SCALE_X;	//Set Baud Rate
		SPI1CONbits.MSTEN = 1;			//Master Mode
		SPI1STATbits.SPIROV = 0;
		SPI1CONbits.ON = 1;				//SPI On

	#endif

	#if (MX_SPI_CHANNEL_X == 2)

		if (MX_SPI_BMODE_X & 0x01)		//Clock Polarity
			SPI2CONbits.CKP = 1;
		else
			SPI2CONbits.CKP = 0;

		if (MX_SPI_BMODE_X & 0x02)		//Clock Edge
			SPI2CONbits.CKE = 1;
		else
			SPI2CONbits.CKE = 0;

		if (MX_SPI_BMODE_X & 0x04)		//Sample Phase
			SPI2CONbits.SMP = 1;
		else
			SPI2CONbits.SMP = 0;

		SPI2BRG = MX_SPI_PR_SCALE_X;	//Set Baud Rate
		SPI2CONbits.MSTEN = 1;			//Master Mode
		SPI2STATbits.SPIROV = 0;
		SPI2CONbits.ON = 1;				//SPI On

	#endif

	#if (MX_SPI_CHANNEL_X == 3)

		if (MX_SPI_BMODE_X & 0x01)		//Clock Polarity
			SPI3CONbits.CKP = 1;
		else
			SPI3CONbits.CKP = 0;

		if (MX_SPI_BMODE_X & 0x02)		//Clock Edge
			SPI3CONbits.CKE = 1;
		else
			SPI3CONbits.CKE = 0;

		if (MX_SPI_BMODE_X & 0x04)		//Sample Phase
			SPI3CONbits.SMP = 1;
		else
			SPI3CONbits.SMP = 0;

		SPI3BRG = MX_SPI_PR_SCALE_X;	//Set Baud Rate
		SPI3CONbits.MSTEN = 1;			//Master Mode
		SPI3STATbits.SPIROV = 0;
		SPI3CONbits.ON = 1;				//SPI On

	#endif

	#if (MX_SPI_CHANNEL_X == 4)

		if (MX_SPI_BMODE_X & 0x01)		//Clock Polarity
			SPI4CONbits.CKP = 1;
		else
			SPI4CONbits.CKP = 0;

		if (MX_SPI_BMODE_X & 0x02)		//Clock Edge
			SPI4CONbits.CKE = 1;
		else
			SPI4CONbits.CKE = 0;

		if (MX_SPI_BMODE_X & 0x04)		//Sample Phase
			SPI4CONbits.SMP = 1;
		else
			SPI4CONbits.SMP = 0;

		SPI4BRG = MX_SPI_PR_SCALE_X;	//Set Baud Rate
		SPI4CONbits.MSTEN = 1;			//Master Mode
		SPI4STATbits.SPIROV = 0;
		SPI4CONbits.ON = 1;				//SPI On

	#endif

	#if (MX_SPI_CHANNEL_X == 5)

		if (MX_SPI_BMODE_X & 0x01)		//Clock Polarity
			SPI5CONbits.CKP = 1;
		else
			SPI5CONbits.CKP = 0;

		if (MX_SPI_BMODE_X & 0x02)		//Clock Edge
			SPI5CONbits.CKE = 1;
		else
			SPI5CONbits.CKE = 0;

		if (MX_SPI_BMODE_X & 0x04)		//Sample Phase
			SPI5CONbits.SMP = 1;
		else
			SPI5CONbits.SMP = 0;

		SPI5BRG = MX_SPI_PR_SCALE_X;	//Set Baud Rate
		SPI5CONbits.MSTEN = 1;			//Master Mode
		SPI5STATbits.SPIROV = 0;
		SPI5CONbits.ON = 1;				//SPI On

	#endif

	#if (MX_SPI_CHANNEL_X == 6)

		if (MX_SPI_BMODE_X & 0x01)		//Clock Polarity
			SPI6CONbits.CKP = 1;
		else
			SPI6CONbits.CKP = 0;

		if (MX_SPI_BMODE_X & 0x02)		//Clock Edge
			SPI6CONbits.CKE = 1;
		else
			SPI6CONbits.CKE = 0;

		if (MX_SPI_BMODE_X & 0x04)		//Sample Phase
			SPI6CONbits.SMP = 1;
		else
			SPI6CONbits.SMP = 0;

		SPI6BRG = MX_SPI_PR_SCALE_X;	//Set Baud Rate
		SPI6CONbits.MSTEN = 1;			//Master Mode
		SPI6STATbits.SPIROV = 0;
		SPI6CONbits.ON = 1;				//SPI On

	#endif
	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_Master_Uninit_, (void))
{
	#if (MX_SPI_CHANNEL_X == 1)
		SPI1CONbits.ON = 0;			//SPI Off
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		SPI2CONbits.ON = 0;			//SPI Off
	#endif

	#if (MX_SPI_CHANNEL_X == 3)
		SPI3CONbits.ON = 0;			//SPI Off
	#endif

	#if (MX_SPI_CHANNEL_X == 4)
		SPI4CONbits.ON = 0;			//SPI Off
	#endif

	#if (MX_SPI_CHANNEL_X == 5)
		SPI5CONbits.ON = 0;			//SPI Off
	#endif

	#if (MX_SPI_CHANNEL_X == 6)
		SPI6CONbits.ON = 0;			//SPI Off
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

		MX_UINT8 i, idx;
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
				if( FC_CAL_Bit_In(MX_SPI_MISO_PORT_X, MX_SPI_MISO_PIN_X) )
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
				if( FC_CAL_Bit_In(MX_SPI_MISO_PORT_X, MX_SPI_MISO_PIN_X) )
					retVal = retVal | 0x01;
				else
					retVal = retVal & 0xFE;
			#endif

			DataOut = DataOut << 1;							//Move to next data bit
		}
    #endif

	#if (MX_SPI_CHANNEL_X == 1)
		retVal = SPI1BUF;
		SPI1BUF = DataOut;
		while((SPI1STAT & 0x01) == 0);
		retVal = SPI1BUF;
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		retVal = SPI2BUF;
		SPI2BUF = DataOut;
		while((SPI2STAT & 0x01) == 0);
		retVal = SPI2BUF;
	#endif

	#if (MX_SPI_CHANNEL_X == 3)
		retVal = SPI3BUF;
		SPI3BUF = DataOut;
		while((SPI3STAT & 0x01) == 0);
		retVal = SPI3BUF;
	#endif

	#if (MX_SPI_CHANNEL_X == 4)
		retVal = SPI4BUF;
		SPI4BUF = DataOut;
		while((SPI4STAT & 0x01) == 0);
		retVal = SPI4BUF;
	#endif

	#if (MX_SPI_CHANNEL_X == 5)
		retVal = SPI5BUF;
		SPI5BUF = DataOut;
		while((SPI5STAT & 0x01) == 0);
		retVal = SPI5BUF;
	#endif

	#if (MX_SPI_CHANNEL_X == 6)
		retVal = SPI6BUF;
		SPI6BUF = DataOut;
		while((SPI6STAT & 0x01) == 0);
		retVal = SPI6BUF;
	#endif

	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_SetPrescaler_, (MX_UINT8 Prescaler))
{
	#if (MX_SPI_CHANNEL_X == 0)
		MX_PRESCALE_VAR_X = Prescaler;
	#endif

	#if (MX_SPI_CHANNEL_X == 1)
		SPI1BRG = Prescaler;
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		SPI2BRG = Prescaler;
	#endif

	#if (MX_SPI_CHANNEL_X == 3)
		SPI3BRG = Prescaler;
	#endif

	#if (MX_SPI_CHANNEL_X == 4)
		SPI4BRG = Prescaler;
	#endif

	#if (MX_SPI_CHANNEL_X == 5)
		SPI5BRG = Prescaler;
	#endif

	#if (MX_SPI_CHANNEL_X == 6)
		SPI6BRG = Prescaler;
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


#undef MX_SPI_PR_SCALE_X
