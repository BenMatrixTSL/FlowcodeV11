// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B806F4274FDFAD3D87C5F8E545EDBF5F88B0AB1886C55FCE0EEB6878BF9700E2F3FD2D54CA74B4B4EB0C3CAEE8E7DA6987372D781EDD272894B5FD966CB65DB7004020B8C0A2E716078707F7EFA0CB6FB0047E8E5CE028052B999C3F2FEE9CA4615A404F9584EA45BF137FF0FD118564CC7791A2F1A49B197D96AD999D8C1D3DEA63A24DFCC62ECA1B549D34A0D5AD11F3B1C975D35A3F524A38BD56EECDB40F386147F29EBA927A21ADE7F62E1D9AF28DE7B6485568F872D0
// REVISION: 2.0
// GUID: D2711759-93A0-44B7-9206-AE13E1845EE6
// DATE: 28\03\2025
// DIR: CAL\PIC\PIC_CAL_SPI.c
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
 * 011211 | BR | Converted to new dynamic defines mechanism
 * 200712 | BR | Added new macro to configure prescaler on the fly
 * 080812 | ST | Fixed undefines typo
 * 090812 | ST | Fixed initial clock polarity setting
 * 090812 | ST | Added comments to explain the BMODE settings and Master_Byte function
 * 140912 | BR | Chaned prescaler function to tie in with the FAT component
 * 171212 | BR | Bug fix - added undefine to allow more then 1 instance of the SPI CAL
 * 090413 | LM | Port definitions from SPI CAL component
 * 210613 | BR | Bug fix defines mod for HW SPI Prescaler - also related mods to init
 * 030713 | LM | Standard API calls
 * 250713 | LM | Upper case register name typo fix
 * 260416 | LM | Updates for XC8
 * 220118 | LM | Add transaction functions
 *
 */


//When using hardware SPI channels override port and pin conns with FCD conn definitions
//Only overwrite CS pin defines when using SPI in slave mode on a hardware channel
//Also sort out postscale and prescale options for hardware channels


//Channel Abstraction
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
#define MX_SPI_SS_PIN_X				CAL_APPEND(MX_SPI_SS_PIN_, MX_SPI_NUM)
#define MX_SPI_SS_PORT_X			CAL_APPEND(MX_SPI_SS_PORT_, MX_SPI_NUM)
#define MX_SPI_SS_TRIS_X			CAL_APPEND(MX_SPI_SS_TRIS_, MX_SPI_NUM)
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


//Only Software Channels Require the Prescale Variable
#if (MX_SPI_CHANNEL_X == 0)
	#define MX_PRESCALE_VAR_X		CAL_APPEND(prescale_, MX_SPI_NUM)

	#ifdef _SPI1CON0_EN_POSN		//New devices have SPIxCON0
		MX_UINT8 MX_PRESCALE_VAR_X = MX_SPI_PR_SCALE_X;
	#else
		MX_UINT8 MX_PRESCALE_VAR_X = (MX_SPI_PR_SCALE_X / 4) - 1;
	#endif
#endif


//Function Prototypes
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Init_, (void));
CALFUNCTION(void, FC_CAL_SPI_Master_Uninit_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Byte_, (MX_UINT8 DataOut));
CALFUNCTION(void, FC_CAL_SPI_SetPrescaler_, (MX_UINT8 Prescaler));

CALFUNCTION(void, FC_CAL_SPI_Slave_Init_, (void));
CALFUNCTION(void, FC_CAL_SPI_Slave_Uninit_, (void));
CALFUNCTION(void, FC_CAL_SPI_Slave_TxByte_, (MX_UINT8 Data));
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Slave_RxByte_, (void));

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_Init_,   (void));
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_,   (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length));
CALFUNCTION(void,     FC_CAL_SPI_Transaction_Uninit_, (void));



#if (MX_SPI_CHANNEL_X > 0)
	#ifdef _SPI1CON0_EN_POSN		//New devices have SPIxCON0
		//Don't refactor prescaler value on newer devices, baud register can take value directly.
	#else
		#if (MX_SPI_PR_SCALE_X == 4)
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X 0
		#endif
		#if (MX_SPI_PR_SCALE_X == 16)
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X 1
		#endif
		#if (MX_SPI_PR_SCALE_X == 64)
			#undef MX_SPI_PR_SCALE_X
			#define MX_SPI_PR_SCALE_X 2
		#endif
	#endif
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

//Ensure registers are defined correctly
#ifndef SSPCON_SSPM0_POSN
  #ifdef _SSPCON1_SSPM0_POSN
	#define SSPCON	SSPCON1
	#define SSPCONbits	SSPCON1bits
  #else
	#ifdef _SSP1CON1_SSPM0_POSN
		#define SSPCON	SSP1CON1
		#define SSPCONbits	SSP1CON1bits
	#endif
  #endif
#endif

#ifndef _SSP2CON_CKP_POSN
	#ifdef _SSP2CON1_CKP_POSN
		#define SSP2CON	SSP2CON1
	#endif
#endif


#ifndef _SSPBUF_SSPBUF_POSN
  #ifdef _SSP1BUF_SSPBUF_POSN
	#define SSPBUF	SSP1BUF
  #endif
#endif

#ifndef _SSPSTAT_BF_POSN
	#ifdef _SSP1STAT_BF_POSN
		#define SSPSTAT SSP1STAT
	#endif
#endif



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
		MX_SPI_MISO_RPINR_X = MX_SPI_MISO_RP_X;						//Data In
		MX_SPI_MOSI_RPOR_X = MX_SPI_MOSI_SDO_X;						//Data Out
		MX_SPI_CLK_RPOR_X = MX_SPI_CLK_SCK_X;						//Clock Out
	#endif

	#if (MX_SPI_CHANNEL_X == 1)
		#ifdef _SPI1CON0_EN_POSN		//New devices have SPIxCON0
			SPI1BAUD = MX_SPI_PR_SCALE_X;							//Assign Clock Prescaler
			ld_bit(SPI1CON1, CKP, (MX_SPI_BMODE_X & 0x01));			//Assign Clock Polarity
			ld_bit(SPI1CON1, CKE, (MX_SPI_BMODE_X & 0x02));			//Assign Clock Phase
			ld_bit(SPI1CON1, SMP, (MX_SPI_BMODE_X & 0x04));			//Assign Input Data Phase
			st_bit(SPI1CON0, MST);									//Assign Master Mode
			st_bit(SPI1CON2, TXR);									//Transmit uses FIFO buffer
			st_bit(SPI1CON2, RXR);									//Receive uses FIFO buffer
			st_bit(SPI1CON0, EN);									//Activate SPI Peripheral
		#else
			SSPCON    		 = MX_SPI_PR_SCALE_X & 0x03;			//Assign Clock Prescaler
			ld_bit(SSPCON, CKP, (MX_SPI_BMODE_X & 0x01));			//Assign Clock Polarity
			ld_bit(SSPSTAT, CKE, (MX_SPI_BMODE_X & 0x02));			//Assign Clock Phase
			ld_bit(SSPSTAT, SMP, (MX_SPI_BMODE_X & 0x04));			//Assign Input Data Phase
			st_bit(SSPCON, SSPEN);									//Activate SPI Peripheral
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		#ifdef _SPI2CON0_EN_POSN		//New devices have SPIxCON0
			SPI2BAUD = MX_SPI_PR_SCALE_X;							//Assign Clock Prescaler
			ld_bit(SPI2CON1, CKP, (MX_SPI_BMODE_X & 0x01));			//Assign Clock Polarity
			ld_bit(SPI2CON1, CKE, (MX_SPI_BMODE_X & 0x02));			//Assign Clock Phase
			ld_bit(SPI2CON1, SMP, (MX_SPI_BMODE_X & 0x04));			//Assign Input Data Phase
			st_bit(SPI2CON0, MST);									//Assign Master Mode
			st_bit(SPI2CON2, TXR);									//Transmit uses FIFO buffer
			st_bit(SPI2CON2, RXR);									//Receive uses FIFO buffer
			st_bit(SPI2CON0, EN);									//Activate SPI Peripheral
		#else
			SSP2CON    		 = MX_SPI_PR_SCALE_X & 0x03;			//Assign Clock Prescaler
			ld_bit(SSP2CON, CKP, (MX_SPI_BMODE_X & 0x01));			//Assign Clock Polarity
			ld_bit(SSP2STAT, CKE, (MX_SPI_BMODE_X & 0x02));			//Assign Clock Phase
			ld_bit(SSP2STAT, SMP, (MX_SPI_BMODE_X & 0x04));			//Assign Input Data Phase
			st_bit(SSP2CON, SSPEN);									//Activate SPI Peripheral
		#endif
	#endif
	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_Master_Uninit_, (void))
{
	#if (MX_SPI_CHANNEL_X == 1)
		#ifdef _SPI1CON0_EN_POSN		//New devices have SPIxCON0
			SPI1CON0 = 0;
		#else
			SSPCON = 0;
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		#ifdef _SPI2CON0_EN_POSN		//New devices have SPIxCON0
			SPI2CON0 = 0;
		#else
			SSP2CON = 0;
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
		#ifdef _SPI1CON0_EN_POSN		//New devices have SPIxCON0
			SPI1TCNTL = 1;    					// Set for 1 byte at a time
			SPI1TXB = DataOut;					//Send outgoing byte
			while ((SPI1STATUS & 0x20) == 0);	//Wait until TXBUF is empty
			retVal = SPI1RXB;					//Collect incoming byte
		#else
			SSPBUF = DataOut;					//Send outgoing byte
			while ((SSPSTAT & 0x01) == 0);		//Wait until SSPBUF is empty
			retVal = SSPBUF;					//Collect incoming byte
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		#ifdef _SPI2CON0_EN_POSN		//New devices have SPIxCON0
			SPI2TCNTL = 1;    					// Set for 1 byte at a time
			SPI2TXB = DataOut;					//Send outgoing byte
			while ((SPI2STATUS & 0x20) == 0);	//Wait until TXBUF is empty
			retVal = SPI2RXB;					//Collect incoming byte
		#else
			SSP2BUF = DataOut;					//Send outgoing byte
			while ((SSP2STAT & 0x01) == 0);		//Wait until SSPBUF is empty
			retVal = SSP2BUF;					//Collect incoming byte
		#endif
	#endif

	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_SetPrescaler_, (MX_UINT8 Prescaler))
{
	//Old Devices
	//0 = Fosc/4
	//1 = Fosc/16
	//2 = Fosc/64

	//New Devices - New devices have SPIxCON0 - e.g. PIC18FxxK42
	//0 = Fosc
	//1 = Fosc / 2
	//2 = Fosc / 3
	//255 = Fosc / 256

	#if (MX_SPI_CHANNEL_X == 0)
		MX_PRESCALE_VAR_X = Prescaler;
	#endif

	#if (MX_SPI_CHANNEL_X == 1)
		#ifdef _SPI1CON0_EN_POSN		//New devices have SPIxCON0
			SPI1BAUD = Prescaler;									//Use Prescaler Value Directly
		#else
			cr_bit(SSPCON, SSPEN);									//Deactivate SPI Peripheral
			SSPCON = SSPCON & 0xFC;
			SSPCON = SSPCON | (Prescaler & 0x03);					//Assign Clock Prescaler
			st_bit(SSPCON, SSPEN);									//Activate SPI Peripheral
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		#ifdef _SPI1CON0_EN_POSN		//New devices have SPIxCON0
			SPI2BAUD = Prescaler;									//Use Prescaler Value Directly
		#else
			cr_bit(SSP2CON, SSPEN);									//Deactivate SPI Peripheral
			SSP2CON = SSP2CON & 0xFC;
			SSP2CON = SSP2CON | (Prescaler & 0x03);					//Assign Clock Prescaler
			st_bit(SSP2CON, SSPEN);									//Activate SPI Peripheral
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
		#ifdef _SPI1CON0_EN_POSN		//New devices have SPIxCON0
			ld_bit(SPICON, CKP, (MX_SPI_BMODE_X & 0x01));			//Assign Clock Polarity
			ld_bit(SPICON, CKE, (MX_SPI_BMODE_X & 0x02));			//Assign Clock Phase
			ld_bit(SPICON, SMP, (MX_SPI_BMODE_X & 0x04));			//Assign Input Data Phase

			#if (MX_SPI_USESS_X == 1)
				SPICONbits.SSPM = 4;								//Assign Slave Mode - Use SS Pin - Active Low
			#else
				SPICONbits.SSPM = 5;								//Assign Slave Mode - No SS Pin
			#endif

			SSPBUF = 0;
			st_bit(SPICON, EN);									//Activate SPI Peripheral
		#else
			ld_bit(SSPCON, CKP, (MX_SPI_BMODE_X & 0x01));			//Assign Clock Polarity
			ld_bit(SSPSTAT, CKE, (MX_SPI_BMODE_X & 0x02));			//Assign Clock Phase
			ld_bit(SSPSTAT, SMP, (MX_SPI_BMODE_X & 0x04));			//Assign Input Data Phase

			#if (MX_SPI_USESS_X == 1)
				SSPCON = (SSPCON & 0xF0) | 4;						//Assign Slave Mode - Use SS Pin - Active Low
			#else
				SSPCON = (SSPCON & 0xF0) | 5;						//Assign Slave Mode - No SS Pin
			#endif

			SSPBUF = 0;
			st_bit(SSPCON, SSPEN);									//Activate SPI Peripheral
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		#ifdef _SPI2CON0_EN_POSN		//New devices have SPIxCON0
			ld_bit(SPI2CON1, CKP, (MX_SPI_BMODE_X & 0x01));			//Assign Clock Polarity
			ld_bit(SPI2CON1, CKE, (MX_SPI_BMODE_X & 0x02));			//Assign Clock Phase
			ld_bit(SPI2CON1, SMP, (MX_SPI_BMODE_X & 0x04));			//Assign Input Data Phase

			#if (MX_SPI_USESS_X == 1)
				SPI2CON1bits.SSPM = 4;								//Assign Slave Mode - Use SS Pin - Active Low
			#else
				SPI2CON1bits.SSPM = 5;								//Assign Slave Mode - No SS Pin
			#endif

			SSP2BUF = 0;
			st_bit(SPI2CON0, EN);									//Activate SPI Peripheral
		#else
			ld_bit(SSP2CON1, CKP, (MX_SPI_BMODE_X & 0x01));			//Assign Clock Polarity
			ld_bit(SSP2STAT, CKE, (MX_SPI_BMODE_X & 0x02));			//Assign Clock Phase
			ld_bit(SSP2STAT, SMP, (MX_SPI_BMODE_X & 0x04));			//Assign Input Data Phase

			#if (MX_SPI_USESS_X == 1)
				SSP2CON1bits.SSPM = 4;								//Assign Slave Mode - Use SS Pin - Active Low
			#else
				SSP2CON1bits.SSPM = 5;								//Assign Slave Mode - No SS Pin
			#endif

			SSP2BUF = 0;
			st_bit(SSP2CON1, SSPEN);									//Activate SPI Peripheral
		#endif
	#endif

}

CALFUNCTION(void, FC_CAL_SPI_Slave_Uninit_, (void))
{
	#if (MX_SPI_CHANNEL_X == 1)
		#ifdef _SPI1CON0_EN_POSN		//New devices have SPIxCON0
			SPI1CON0 = 0;
		#else
			SSPCON = 0;
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		#ifdef _SPI2CON0_EN_POSN		//New devices have SPIxCON0
			SPI2CON0 = 0;
		#else
			SSP2CON1 = 0;
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
		SSPBUF = Data;						//Specify outgoing byte
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		SSP2BUF = Data;						//Specify outgoing byte
	#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Slave_RxByte_, (void))
{
	MX_UINT8 retVal = 0;

	#if (MX_SPI_CHANNEL_X == 1)
		retVal = SSPBUF;					//Collect incoming byte
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		retVal = SSP2BUF;					//Collect incoming byte
	#endif

	return(retVal);
}


#endif			//Slave End



#undef MX_SPI_PR_SCALE_X

