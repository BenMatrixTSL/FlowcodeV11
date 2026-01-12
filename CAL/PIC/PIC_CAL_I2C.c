// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B8780D0B864F5D1F680368647E196A8AACEA68E2929511E6E27D52A876A9F220FA562AF2F62E9AB6760C3CAEE8E7DA6987DE3F57CDBA3A75ED618FE9E6D8BAA9A87668C33C7D0D76AF9CB24CE08F8B3A6208E90FACA779D500822923DC1AB94DA057834014FAB126860197DC63678D55DF5E1DCE6D459C3CFBAC0A36EDE6FFF9B2636F7A56F194CD15549D34A0D5AD11F30D22ADDCB073812F2DE26A97C9D202459AB2FADFBA6617B461112B2378F6127E5D3A7ED706D09BBA
// REVISION: 6.0
// GUID: 51FF44D1-6796-4E76-97BD-E923529881BA
// DATE: 19\09\2025
// DIR: CAL\PIC\PIC_CAL_I2C.c
/*********************************************************************
 *                  Flowcode CAL I2C File
 *
 * File: PIC_CAL_I2C.c
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
 * 021211 | BR | Converted to new dynamic defines mechanism
 * 310512 | BR | Minor bug fix when using SW I2C on a device with no I2C peripheral
 * 120912 | BR | Minor bug fix to remove a bug with remappable I2C channel 2
 * 120912 | BR | Minor bug fix to remove a bug with register SSP2CON
 * 090413 | LM | removed I2C HW port overrides, all come from CAL component for V6
 * 140613 | BR | Minor mod to error message to say not available or not supported
 * 020713 | LM | Standard API calls
 * 260914 | LM | Implemented Slave functionality
 * 260416 | LM | Updates for XC8
 * 220118 | LM | Addition of transaction functions
 * 120925 | BR | Added new I2CxCON0 style peripheral support
 */



#define MX_I2C_CHANNEL_X		CAL_APPEND(MX_I2C_CHANNEL_, MX_I2C_NUM)
#define MX_I2C_SDA_PIN_X		CAL_APPEND(MX_I2C_SDA_PIN_, MX_I2C_NUM)
#define MX_I2C_SDA_PORT_X		CAL_APPEND(MX_I2C_SDA_PORT_, MX_I2C_NUM)
#define MX_I2C_SDA_TRIS_X		CAL_APPEND(MX_I2C_SDA_TRIS_, MX_I2C_NUM)
#define MX_I2C_SDA_ODC_X		CAL_APPEND(MX_I2C_SDA_ODC_, MX_I2C_NUM)
#define MX_I2C_SCL_PIN_X		CAL_APPEND(MX_I2C_SCL_PIN_, MX_I2C_NUM)
#define MX_I2C_SCL_PORT_X		CAL_APPEND(MX_I2C_SCL_PORT_, MX_I2C_NUM)
#define MX_I2C_SCL_TRIS_X		CAL_APPEND(MX_I2C_SCL_TRIS_, MX_I2C_NUM)
#define MX_I2C_SCL_ODC_X		CAL_APPEND(MX_I2C_SCL_ODC_, MX_I2C_NUM)
#define MX_I2C_BMODE_X			CAL_APPEND(MX_I2C_BMODE_, MX_I2C_NUM)
#define MX_I2C_BAUD_X			CAL_APPEND(MX_I2C_BAUD_, MX_I2C_NUM)
#define MX_I2C_INT_X			CAL_APPEND(MX_I2C_INT_, MX_I2C_NUM)
#define MX_I2C_STOPDEL_X		CAL_APPEND(MX_I2C_STOPDEL_, MX_I2C_NUM)
#define MX_I2C_REMAPPABLE_X		CAL_APPEND(MX_I2C_REMAPPABLE_, MX_I2C_NUM)
#define MX_I2C_SDA_RPOR_X		CAL_APPEND(MX_I2C_SDA_RPOR_, MX_I2C_NUM)
#define MX_I2C_SDA_X			CAL_APPEND(MX_I2C_SDA_, MX_I2C_NUM)
#define MX_I2C_SCL_RPOR_X		CAL_APPEND(MX_I2C_SCL_RPOR_, MX_I2C_NUM)
#define MX_I2C_SCL_X			CAL_APPEND(MX_I2C_SCL_, MX_I2C_NUM)
#define MX_I2C_SDA_RPINR_X		CAL_APPEND(MX_I2C_SDA_RPINR_, MX_I2C_NUM)
#define MX_I2C_SDA_RP_X			CAL_APPEND(MX_I2C_SDA_RP_, MX_I2C_NUM)
#define MX_I2C_SCL_RPINR_X		CAL_APPEND(MX_I2C_SCL_RPINR_, MX_I2C_NUM)
#define MX_I2C_SCL_RP_X			CAL_APPEND(MX_I2C_SCL_RP_, MX_I2C_NUM)
#define MX_I2C_CLKSTRCH_X		CAL_APPEND(MX_I2C_CLOCKSTRETCHING_, MX_I2C_NUM)


//Function Prototypes
CALFUNCTION(void, FC_CAL_I2C_Master_Init_, (void));
CALFUNCTION(void, FC_CAL_I2C_Master_Uninit_, (void));
CALFUNCTION(void, FC_CAL_I2C_Master_Start_, (void));
CALFUNCTION(void, FC_CAL_I2C_Master_Restart_, (void));
CALFUNCTION(void, FC_CAL_I2C_Master_Stop_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Master_TxByte_, (MX_UINT8 Data));
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Master_RxByte_, (MX_UINT8 Last));

CALFUNCTION(void, FC_CAL_I2C_Slave_Init_, (MX_UINT8 Address, MX_UINT8 Mask));
CALFUNCTION(void, FC_CAL_I2C_Slave_Uninit_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_TxByte_, (MX_UINT8 Data));
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_RxByte_, (MX_UINT8 Last));
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_Status_, (void));

CALFUNCTION(MX_UINT8, FC_CAL_I2C_Transaction_Init_,   (MX_UINT8 SlaveAddress));
CALFUNCTION(MX_UINT16, FC_CAL_I2C_Transaction_Read_,   (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length));
CALFUNCTION(MX_UINT16, FC_CAL_I2C_Transaction_Write_,  (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length));
CALFUNCTION(void,     FC_CAL_I2C_Transaction_Uninit_, (void));

//I2C Timeout - Avoids any blocking delays
#define MX_I2C_TIMEOUT_X		CAL_APPEND(MX_I2C_TIMEOUT_, MX_I2C_NUM)
MX_UINT16 MX_I2C_TIMEOUT_X;


#if (MX_I2C_CHANNEL_X > 0)

	//Ensure SSPCON register is defined correctly
	#ifndef _SSPCON_SSPM0_SIZE
	  #ifdef _SSPCON1_SSPM0_SIZE
		#define SSPCON	SSPCON1
		#define SSPCONbits	SSPCON1bits
	  #else
		#ifdef _SSP1CON1_SSPM0_SIZE
			#define SSPCON	SSP1CON1
			#define SSPCONbits	SSP1CON1bits
		#endif
	  #endif
	#endif


	#ifdef _I2C1CON0_EN_POSN		//New devices have I2CxCON0 register
	#else
		//Ensure SSPIF register is defined correctly
		#ifndef _PIR1_SSPIF_POSITION
		  #ifdef _PIR1_SSP1IF_POSITION
			#define SSPIF_PIR PIR1
			#define SSPIF	SSP1IF
		  #else
			#ifdef _PIR3_SSP1IF_POSN
			  #define SSPIF_PIR PIR3
			  #define SSPIF	SSP1IF
			#else
			  #error "I2C does not have the SSPIF defined on this chip - does your chip support this feature?"
			#endif
		  #endif
		#else
		  #define SSPIF_PIR PIR1
		#endif
	#endif


	//Ensure SSPCON1 register is defined correctly
	#ifndef _SSPCON1_SSPM0_SIZE
	  #ifdef _SSP1CON1_SSPM0_SIZE
		#define SSPCON1	SSP1CON1
	  #endif
	#endif


	//Ensure SSPCON2 register is defined correctly
	#ifdef _I2C1CON0_EN_POSN		//New devices have I2CxCON0 register
	#else
		#ifndef _SSPCON2_SEN_SIZE
		  #ifdef _SSP1CON2_SEN_SIZE
			#define SSPCON2	SSP1CON2
		  #endif
		  #ifndef SSPCON2
			#warning "I2C Master Mode may not be available on your current target device, switch to software mode."
		  #endif
		#endif
	#endif


	//Ensure SSPCON3 register is defined correctly
	#ifndef _SSPCON3_DHEN_SIZE
	  #ifdef _SSP1CON3_DHEN_SIZE
		#define SSPCON3	SSP1CON3
	  #endif
	#endif


	//Ensure SSPSTAT register is defined correctly
	#ifndef _SSPSTAT_BF_POSN
	  #ifdef _SSP1STAT_BF_POSN
		#define SSPSTAT	SSP1STAT

		#ifdef _SSP1STAT_R_nW_POSN
			#define SSPSTAT_R_NOT_W R_nW
		#else
			#define SSPSTAT_R_NOT_W R_NOT_W
		#endif

	  #endif
	#else

		#ifdef _SSPSTAT_R_nW_POSN
			#define SSPSTAT_R_NOT_W R_nW
		#else
			#define SSPSTAT_R_NOT_W R_NOT_W
		#endif

	#endif


	//Ensure SSPADD register is defined correctly
	#ifndef _SSPADD_SSPADD_POSN
	  #ifdef _SSP1ADD_SSPADD_POSN
		#define SSPADD	SSP1ADD
	  #endif
	#endif


	//Ensure SSPBUFF register is defined correctly
	#ifndef _SSPBUF_SSPBUF_POSN
	  #ifdef _SSP1BUF_SSPBUF_POSN
		#define SSPBUF	SSP1BUF
	  #endif
	#endif


	//Ensure SSPMSK register is defined correctly
	#ifndef _SSPMSK_MSK0_POSN
	  #ifdef _SSP1MSK_MSK0_POSN
		#define SSPMSK	SSP1MSK
	  #endif
	#endif


	#ifdef _SSP2STAT_R_nW_POSN
		#define SSP2STAT_R_NOT_W R_nW
	#else
		#define SSP2STAT_R_NOT_W R_NOT_W
	#endif

	// 16F1827
// SSP2 Interrupt Flag Register Detection
#if (MX_I2C_CHANNEL_X > 1)
	#ifdef _I2C1CON0_EN_POSN		//New devices have I2CxCON0 register
	#else
		#ifndef _PIR1_SSP2IF_POSITION
		  #ifdef _PIR2_SSP2IF_POSITION
			#define SSP2PIRP	PIR2
		  #else
			#ifdef _PIR3_SSP2IF_POSN
			  #define SSP2PIRP	PIR3
			#else
			  #ifdef _PIR4_SSP2IF_POSN
				#define SSP2PIRP	PIR4
			  #else
				#error "I2C Channel 2 does not have the SSP2IF defined on this chip - does your chip support this feature?"
			  #endif
			#endif
		  #endif
		#else
		  #define SSP2PIRP	PIR1
		#endif
	#endif
#endif

	#if (MX_I2C_CHANNEL_X > 1)

		#ifndef SSP2CON
			#define SSP2CON SSP2CON1
		#endif

	#endif

  #define MX_I2C_HW_BAUD	((MX_CLK_SPEED / 4) / MX_I2C_BAUD_X) - 1

  //Check for rollover
  #if MX_I2C_HW_BAUD > 255
  	#undef MX_I2C_HW_BAUD
  	#define MX_I2C_HW_BAUD 255
  #endif

#else

  #ifndef MX_I2C_SW_DEL
	#define MX_I2C_SW_DEL
	#define MX_I2C_SW_BAUD	((500000 / MX_I2C_BAUD_X)-1)

	#if (MX_I2C_SW_BAUD < 1)
		#define MX_I2C_DELAY	delay_us(1);
	#else
		#define MX_I2C_DELAY	delay_us(MX_I2C_SW_BAUD);
	#endif

  #endif

#endif


CALFUNCTION(void, FC_CAL_I2C_Master_Init_, (void))
{
	#if (MX_I2C_REMAPPABLE_X == 1)
		MX_I2C_SDA_RPINR_X = MX_I2C_SDA_RP_X;		//Data Input Remap
		MX_I2C_SDA_RPOR_X = MX_I2C_SDA_X;			//Data Output Remap
		MX_I2C_SCL_RPOR_X = MX_I2C_SCL_X;			//Clock Output Remap
		MX_I2C_SCL_RPINR_X = MX_I2C_SCL_RP_X;		//Clock Input Remap
	#endif

	FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Configure SDA as Input
	FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Configure SCL as Input

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1
		#ifndef MX_MI2C
			#error "This chip does not have Master I2C capability or Flowcode does not currently support it"
		#else

			#ifndef MX_I2C_1
				#error "This chip does not have Master I2C channel 1"
			#endif

			#ifdef _I2C1CON0_EN_POSN		//New devices have I2CxCON0 register

				//Pins must be configured as open drain only
				MX_I2C_SDA_ODC_X |= (1 << MX_I2C_SDA_PIN_X);
				MX_I2C_SCL_ODC_X |= (1 << MX_I2C_SCL_PIN_X);

				//Pins must be configured as outputs - default pull up
				FC_CAL_Bit_High_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);
				FC_CAL_Bit_High_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);

				I2C1CON0bits.MODE = 4;											//Setup I2C into Master Mode - 7-bit address
  				I2C1CON1bits.ACKCNT=1; 											//1 => I2CxCNT == 0 => Not Acknowledge (NACK) copied to SDA output
    			I2C1CON1bits.ACKDT=0; 											//0 => I2CxCNT != 0 => Acknowledge (ACK) copied to SDA output
				I2C1CLK = 0x03;													//Use MFINTOSC 500KHz

				#if (MX_I2C_BAUD_X > 100000)
					I2C1CON2bits.FME = 1;										//500KHz/4 = 125KHz
				#else
					I2C1CON2bits.FME = 0;										//500KHz/5 = 100KHz
				#endif

				I2C1CON2bits.ABD = 0;											//Address buffer disable
				I2C1CON0bits.EN=1;												//Enable I2C

			#else							//Standard MSSP configuration

				#if (MX_I2C_BMODE_X & 0x01)
					cr_bit (SSPSTAT,SMP);										//Slew Rate Control Enabled
				#else
					st_bit (SSPSTAT,SMP);										//Slew Rate Control Disabled
				#endif

				#if (MX_I2C_BMODE_X & 0x02)
					st_bit (SSPSTAT,CKE);										//Enable SMBus specific inputs
				#else
					cr_bit (SSPSTAT,CKE);										//Disable SMBus specific inputs
				#endif

				SSPCON = 0x28;													//Setup I2C into Master Mode
				SSPADD = MX_I2C_HW_BAUD;										//Set the Baud Rate
				SSPCON2 = 0x00;													//Clear the control bits
				st_bit(INTCON, GIE);

			#endif
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)												//Use Master I2C Hardware 2
		#ifndef MX_MI2C
			#error "This chip does not have Master I2C capability or Flowcode does not currently support it"
		#else

			#ifndef MX_I2C_2
				#error "This chip does not have Master I2C channel 2"
			#endif

			#ifdef _I2C2CON0_EN_POSN		//New devices have I2CxCON0 register

				//Pins must be configured as open drain only
				MX_I2C_SDA_ODC_X |= (1 << MX_I2C_SDA_PIN_X);
				MX_I2C_SCL_ODC_X |= (1 << MX_I2C_SCL_PIN_X);

				//Pins must be configured as outputs - default pull up
				FC_CAL_Bit_High_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);
				FC_CAL_Bit_High_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);

				I2C2CON0bits.MODE = 4;											//Setup I2C into Master Mode - 7-bit address
  				I2C2CON1bits.ACKCNT=1; 											//1 => I2CxCNT == 0 => Not Acknowledge (NACK) copied to SDA output
    			I2C2CON1bits.ACKDT=0; 											//0 => I2CxCNT != 0 => Acknowledge (ACK) copied to SDA output
				I2C2CLK = 0x03;													//Use MFINTOSC 500KHz

				#if (MX_I2C_BAUD_X > 100000)
					I2C2CON2bits.FME = 1;										//500KHz/4 = 125KHz
				#else
					I2C2CON2bits.FME = 0;										//500KHz/5 = 100KHz
				#endif

				I2C2CON2bits.ABD = 0;											//Address buffer disable
				I2C2CON0bits.EN=1;												//Enable I2C

			#else							//Standard MSSP configuration

				#if (MX_I2C_BMODE_X & 0x01)
					cr_bit (SSP2STAT,SMP);										//Slew Rate Control Enabled
				#else
					st_bit (SSP2STAT,SMP);										//Slew Rate Control Disabled
				#endif

				#if (MX_I2C_BMODE_X & 0x02)
					st_bit (SSP2STAT,CKE);										//Enable SMBus specific inputs
				#else
					cr_bit (SSP2STAT,CKE);										//Disable SMBus specific inputs
				#endif

				SSP2CON = 0x28;													//Setup I2C into Master Mode
				SSP2ADD = MX_I2C_HW_BAUD;										//Set the Baud Rate
				SSP2CON2 = 0x00;												//Clear the control bits
				st_bit(INTCON, GIE);

			#endif
		#endif
	#endif


}


CALFUNCTION(void, FC_CAL_I2C_Master_Uninit_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)																//Use Master I2C Software
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);			//Configure SDA as Input
		FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);			//Configure SCL as Input
	#endif

	#if (MX_I2C_CHANNEL_X == 1)			//Use Master I2C Hardware 1
		#ifdef _I2C1CON0_EN_POSN		//New devices have I2CxCON0 register

			//Disable open drain only
			MX_I2C_SDA_ODC_X &= ~(1 << MX_I2C_SDA_PIN_X);
			MX_I2C_SCL_ODC_X &= ~(1 << MX_I2C_SCL_PIN_X);

			I2C1CON0 = 0x0;				//Disable I2C
		#else
			cr_bit(SSPCON, SSPEN);		//Disable SSP
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)			//Use Master I2C Hardware 2
		#ifdef _I2C2CON0_EN_POSN		//New devices have I2CxCON0 register

			//Disable open drain only
			MX_I2C_SDA_ODC_X &= ~(1 << MX_I2C_SDA_PIN_X);
			MX_I2C_SCL_ODC_X &= ~(1 << MX_I2C_SCL_PIN_X);

			I2C2CON0 = 0x0;				//Disable I2C
		#else
			cr_bit(SSP2CON, SSPEN);		//Disable SSP
		#endif
	#endif
}


CALFUNCTION(void, FC_CAL_I2C_Master_Start_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)															//Use Master I2C Software

		FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Make Sure SCL is Set
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Make Sure SDA is Set
		MX_I2C_DELAY;																	//Small Delay
		FC_CAL_Bit_Low_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Clear SDA
		MX_I2C_DELAY;																	//Small Delay
		FC_CAL_Bit_Low_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Clear SCL
		//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR

	#endif

	#if (MX_I2C_CHANNEL_X == 1)													//Use Master I2C Hardware 1

		#ifdef _I2C1CON0_EN_POSN												//New devices have I2CxCON0 register

			MX_I2C_TIMEOUT_X = 0xFFFF;
			while (ts_bit(I2C1STAT0,BFRE) && MX_I2C_TIMEOUT_X--);				//Wait for bus to be free
			MX_I2C_TIMEOUT_X = 0xFFFF;
			st_bit(I2C1CON0,S);													//Initiate start condition
			while(ts_bit(I2C1CON0,S) && MX_I2C_TIMEOUT_X--);					//Wait for start bit to be generated

		#else

			cr_bit(SSPIF_PIR, SSPIF);											//Clear SSP interrupt flag
			st_bit(SSPCON2,SEN);												//Initiate start condition
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(SSPCON2,SEN) && MX_I2C_TIMEOUT_X--);					//Wait for start bit to be generated

		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)													//Use Master I2C Hardware 2
		#ifdef _I2C2CON0_EN_POSN												//New devices have I2CxCON0 register

			MX_I2C_TIMEOUT_X = 0xFFFF;
			while (ts_bit(I2C2STAT0,BFRE) && MX_I2C_TIMEOUT_X--);				//Wait for bus to be free
			MX_I2C_TIMEOUT_X = 0xFFFF;
			st_bit(I2C2CON0,S);													//Initiate start condition
			while(ts_bit(I2C2CON0,S) && MX_I2C_TIMEOUT_X--);					//Wait for start bit to be generated

		#else

			cr_bit(SSP2PIRP, SSP2IF);											//Clear SSP interrupt flag
			st_bit(SSP2CON2,SEN);												//Initiate start condition
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(SSP2CON2,SEN) && MX_I2C_TIMEOUT_X--);					//Wait for start bit to be generated

		#endif
	#endif
}


CALFUNCTION(void, FC_CAL_I2C_Master_Restart_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)															//Use Master I2C Software

		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Set SDA High
		MX_I2C_DELAY;
		FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Set SCL High
		MX_I2C_DELAY;
		FC_CAL_Bit_Low_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Set SDA Low
		MX_I2C_DELAY;
		FC_CAL_Bit_Low_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Set SCL Low
		//MX_I2C_DELAY;																	//Removed 050613 - BR

	#endif

	#if (MX_I2C_CHANNEL_X == 1)													//Use Master I2C Hardware 1
		#ifdef _I2C1CON0_EN_POSN												//New devices have I2CxCON0 register

			MX_I2C_TIMEOUT_X = 0xFFFF;
			st_bit(I2C1CON0,S);													//Initiate start condition
			while(ts_bit(I2C1CON0,S) && MX_I2C_TIMEOUT_X--);					//Wait for start bit to be generated

		#else

			cr_bit(SSPIF_PIR, SSPIF);											//Clear SSP interrupt flag
			st_bit(SSPCON2,RSEN);												//Initiate restart condition
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(SSPCON2,RSEN) && MX_I2C_TIMEOUT_X--);					//Wait for restart bit to be generated

		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)													//Use Master I2C Hardware 2
		#ifdef _I2C2CON0_EN_POSN												//New devices have I2CxCON0 register

			MX_I2C_TIMEOUT_X = 0xFFFF;
			st_bit(I2C2CON0,S);													//Initiate start condition
			while(ts_bit(I2C2CON0,S) && MX_I2C_TIMEOUT_X--);					//Wait for start bit to be generated

		#else

			cr_bit(SSP2PIRP, SSP2IF);											//Clear SSP interrupt flag
			st_bit(SSP2CON2,RSEN);												//Initiate restart condition
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(SSP2CON2,RSEN) && MX_I2C_TIMEOUT_X--);					//Wait for restart bit to be generated

		#endif
	#endif
}


CALFUNCTION(void, FC_CAL_I2C_Master_Stop_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)															//Use Master I2C Software
		FC_CAL_Bit_Low_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Set SCL Low
		FC_CAL_Bit_Low_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Set SDA Low
		MX_I2C_DELAY;
		FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Set SCL High
		MX_I2C_DELAY;
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Set SDA High
	#endif

	#if (MX_I2C_CHANNEL_X == 1)													//Use Master I2C Hardware 1
		#ifdef _I2C1CON0_EN_POSN												//New devices have I2CxCON0 register

			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(I2C1STAT0,MMA) && MX_I2C_TIMEOUT_X--);					//Wait for stop bit to be generated

		#else

			cr_bit(SSPIF_PIR,SSPIF);											//Clear SSP interrupt flag
			st_bit(SSPCON2,PEN);												//Initiate stop condition
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(SSPCON2,PEN) && MX_I2C_TIMEOUT_X--);					//Wait for stop bit to be generated

		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)													//Use Master I2C Hardware 2
		#ifdef _I2C2CON0_EN_POSN												//New devices have I2CxCON0 register

			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(I2C2STAT0,MMA) && MX_I2C_TIMEOUT_X--);					//Wait for stop bit to be generated

		#else

			cr_bit(SSP2PIRP,SSP2IF);											//Clear SSP interrupt flag
			st_bit(SSP2CON2,PEN);												//Initiate stop condition
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(SSP2CON2,PEN) && MX_I2C_TIMEOUT_X--);					//Wait for stop bit to be generated

		#endif
	#endif

	#if (MX_I2C_STOPDEL_X == 1)
	  delay_ms(10);																//Wait before reusing the I2C BUS -  avoids lockup problem exibited on some older PICs
	#endif
}


CALFUNCTION(MX_UINT8, FC_CAL_I2C_Master_TxByte_, (MX_UINT8 Data))
{
	#if (MX_I2C_CHANNEL_X == 0)												//Use Master I2C Software
		MX_UINT8 bit_mask;
		MX_UINT8 local_ack = 0;
		for(bit_mask=0x80;bit_mask;bit_mask=bit_mask>>1)
		{
			if(Data & bit_mask)
			{
				FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);	//Set SDA High
			}
			else
			{
				FC_CAL_Bit_Low_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);	//Set SDA Low
			}
			MX_I2C_DELAY;
			FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Set SCL High
			MX_I2C_DELAY;

			#if (MX_I2C_CLKSTRCH_X == 1)
			    MX_I2C_TIMEOUT_X = 0xFFFF;
				while (FC_CAL_Bit_In(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X) == 0 && MX_I2C_TIMEOUT_X--);		//Wait for the clock to go high - Clock stretching.
			#endif

			FC_CAL_Bit_Low_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Set SCL Low
			//MX_I2C_DELAY;																	//Removed 050613 - BR
		}
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);			//Set SDA High
		MX_I2C_DELAY;
		FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);			//Set SCL High
		MX_I2C_DELAY;
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);
		if (FC_CAL_Bit_In(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X))								//Get the Status Bit
			local_ack = 1;
		//MX_I2C_DELAY;																		//Small Delay //Removed 050613 - BR
		FC_CAL_Bit_Low_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);			//Set SCL Low
		//MX_I2C_DELAY;																		//Removed 050613 - BR
		return (local_ack);																	//0 = Ack received : 1 = Ack not received
	#endif

	#if (MX_I2C_CHANNEL_X == 1)													//Use Master I2C Hardware 1
		#ifdef _I2C1CON0_EN_POSN												//New devices have I2CxCON0 register

			I2C1TXB = Data;														//Send byte
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(I2C1STAT1,TXBE) == 0 && MX_I2C_TIMEOUT_X--);			//Wait for control bit to be sent
			if (I2C1CON1bits.ACKSTAT)
				return (1);														//No Acknowledgement
			else return (0);													//Acknowledgement received

		#else

			cr_bit(SSPIF_PIR,SSPIF);											//Clear SSP interrupt flag
			SSPBUF = Data;														//Send byte
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(SSPIF_PIR,SSPIF) == 0 && MX_I2C_TIMEOUT_X--);			//Wait for control bit to be sent
			if(ts_bit(SSPCON2,ACKSTAT))											//Check Acknowledgement
				return (1);														//No Acknowledgement
			else return (0);													//Acknowledgement received

		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)													//Use Master I2C Hardware 2
		#ifdef _I2C1CON0_EN_POSN												//New devices have I2CxCON0 register

			I2C2TXB = Data;														//Send byte
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(I2C2STAT1,TXBE) == 0 && MX_I2C_TIMEOUT_X--);			//Wait for control bit to be sent
			if (I2C2CON1bits.ACKSTAT)
				return (1);														//No Acknowledgement
			else return (0);													//Acknowledgement received

		#else

			cr_bit(SSP2PIRP,SSP2IF);												//Clear SSP interrupt flag
			SSP2BUF=Data;														//Send byte
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(SSP2PIRP,SSP2IF) == 0 && MX_I2C_TIMEOUT_X--);					//Wait for control bit to be sent
			if(ts_bit(SSP2CON2,ACKSTAT))										//Check Acknowledgement
				return (1);														//No Acknowledgement
			else return (0);													//Acknowledgement received

		#endif
	#endif
}


CALFUNCTION(MX_UINT8, FC_CAL_I2C_Master_RxByte_, (MX_UINT8 Last))
{
	#if (MX_I2C_CHANNEL_X == 0)												//Use Master I2C Software
		MX_UINT8 bit_mask;
		MX_UINT8 Data = 0;
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);			//Set SDA High
		MX_I2C_DELAY;
		for(bit_mask=0x80;bit_mask;bit_mask=bit_mask>>1)
		{
			FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Set SCL High
			MX_I2C_DELAY;

			#if (MX_I2C_CLKSTRCH_X == 1)
			    MX_I2C_TIMEOUT_X = 0xFFFF;
				while (FC_CAL_Bit_In(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X) == 0 && MX_I2C_TIMEOUT_X--);		//Wait for the clock to go high - Clock stretching.
			#endif

			FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);
			if(FC_CAL_Bit_In(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X))	//Read Incoming Bit
				Data = Data | bit_mask;														//Add data to variable
			FC_CAL_Bit_Low_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Set SCL Low
			MX_I2C_DELAY;																	//Small Delay
		}
		if (Last)																		//Acknowledge?
		{
			FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);	//Send Nack
		}
		else
		{
			FC_CAL_Bit_Low_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);	//Send Ack
		}
		MX_I2C_DELAY;
		FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Set SCL High
		MX_I2C_DELAY;
		FC_CAL_Bit_Low_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Set SCL Low
		//MX_I2C_DELAY;																	//Removed 050613 - BR
		return (Data);
	#endif

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1
		#ifdef _I2C1CON0_EN_POSN											//New devices have I2CxCON0 register

			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(I2C1STAT1,RXBF) == 0 && MX_I2C_TIMEOUT_X--);		//Wait for data read
			return (I2C1RXB);												//Store incoming data

		#else

			cr_bit(SSPIF_PIR,SSPIF);										//Clear SSP interrupt flag
			st_bit(SSPCON2,RCEN);											//Initiate Read
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(SSPIF_PIR,SSPIF) == 0 && MX_I2C_TIMEOUT_X--);		//Wait for data read
			if (Last)
				st_bit(SSPCON2,ACKDT);										//Send Nack
			else cr_bit(SSPCON2,ACKDT);										//Send Ack
			st_bit(SSPCON2,ACKEN);											//Initiate Nack
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(SSPCON2,ACKEN) && MX_I2C_TIMEOUT_X--);				//Wait for data read
			return(SSPBUF);													//Store incoming data

		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)												//Use Master I2C Hardware 2
		#ifdef _I2C1CON0_EN_POSN											//New devices have I2CxCON0 register

			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(I2C2STAT1,RXBF) == 0 && MX_I2C_TIMEOUT_X--);		//Wait for data read
			return (I2C2RXB);												//Store incoming data

		#else

			cr_bit(SSP2PIRP,SSP2IF);										//Clear SSP interrupt flag
			st_bit(SSP2CON2,RCEN);											//Initiate Read
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(SSP2PIRP,SSP2IF) == 0 && MX_I2C_TIMEOUT_X--);		//Wait for data read
			if (Last)
				st_bit(SSP2CON2,ACKDT);										//Send Nack
			else cr_bit(SSP2CON2,ACKDT);									//Send Ack
			st_bit(SSP2CON2,ACKEN);											//Initiate Nack
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(ts_bit(SSP2CON2,ACKEN) && MX_I2C_TIMEOUT_X--);			//Wait for data read
			return(SSP2BUF);												//Store incoming data

		#endif
	#endif
}



/*********************************************
Slave functions, only support 7 bit addressing
*********************************************/

CALFUNCTION(void, FC_CAL_I2C_Slave_Init_, (MX_UINT8 Address, MX_UINT8 Mask))
{
	#if (MX_I2C_REMAPPABLE_X == 1)
		MX_I2C_SDA_RPINR_X = MX_I2C_SDA_RP_X;		//Data Input Remap
		MX_I2C_SDA_RPOR_X = MX_I2C_SDA_X;			//Data Output Remap
		MX_I2C_SCL_RPINR_X = MX_I2C_SCL_RP_X;		//Clock Input Remap
	#endif

	#if (MX_I2C_CHANNEL_X == 1)
		#ifdef _I2C1CON0_EN_POSN		//New devices have I2CxCON0 register
		#else

			#if (MX_I2C_BMODE_X & 0x01)
				cr_bit(SSPSTAT, SMP);	// Slew Rate Control Enabled
			#else
				st_bit(SSPSTAT, SMP);	// Slew Rate Control Disabled
			#endif
			SSPCON = 0x36;				// SSPEN=1, CKP=1, SSPM<3:0>=0110  = I2C Slave mode, 7-bit address
			SSPCON2 = 1;				// SEN=1 Clock stretching is enabled
			#ifdef SSPCON3
				SSPCON3 = 3;			// set AHEN and DHEN
			#endif
			#ifdef SSPMSK
				SSPMSK = Mask;
			#endif
			SSPADD = Address;

		#endif
	#endif
	#if (MX_I2C_CHANNEL_X == 2)
		#ifdef _I2C1CON0_EN_POSN		//New devices have I2CxCON0 register
		#else

			#if (MX_I2C_BMODE_X & 0x01)
				cr_bit(SSP2STAT, SMP);	// Slew Rate Control Enabled
			#else
				st_bit(SSP2STAT, SMP);	// Slew Rate Control Disabled
			#endif
			SSP2CON1 = 0x36;			// SSPEN=1, CKP=1, SSPM<3:0>=0110  = I2C Slave mode, 7-bit address
			SSP2CON2 = 1;				// SEN=1 Clock stretching is enabled
			#ifdef SSPCON3
				SSP2CON3 = 3;			// set AHEN and DHEN
			#endif
			#ifdef SSPMSK
				SSP2MSK = Mask;
			#endif
			SSP2ADD = Address;

		#endif
	#endif
}

// Returns I2C status byte (SSPSTAT = SMP CKE D/A P S R/W UA BF)
// Bit 0 = 1 Indicates address/data byte available in the buffer to read
// Bit 5 = 1 Indicates that the last byte received or transmitted was data (else address)
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_Status_, (void))
{
	#if (MX_I2C_CHANNEL_X == 1)
		#ifdef _I2C1CON0_EN_POSN		//New devices have I2CxCON0 register
		#else
			return SSPSTAT;
		#endif
	#elif (MX_I2C_CHANNEL_X == 2)
		#ifdef _I2C1CON0_EN_POSN		//New devices have I2CxCON0 register
		#else
			return SSP2STAT;
		#endif
	#endif

	return 0;
}

// Disables the I2C peripheral
CALFUNCTION(void, FC_CAL_I2C_Slave_Uninit_, (void))
{
	#if (MX_I2C_CHANNEL_X == 1)
		#ifdef _I2C1CON0_EN_POSN		//New devices have I2CxCON0 register
		#else
			cr_bit(SSPCON, SSPEN);
		#endif
	#endif
	#if (MX_I2C_CHANNEL_X == 2)
		#ifdef _I2C1CON0_EN_POSN		//New devices have I2CxCON0 register
		#else
			cr_bit(SSP2CON1, SSPEN);
		#endif
	#endif
}

// Loads the Data byte into the shift buffer and releases SCL ready for sending
// Returns Master Ack/Nak (0=Ack=More, 1=Nak=Last)
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_TxByte_, (MX_UINT8 Data))
{
	#if (MX_I2C_CHANNEL_X == 1)
		#ifdef _I2C1CON0_EN_POSN		//New devices have I2CxCON0 register
			return 0;
		#else
			cr_bit(SSPIF_PIR, SSPIF);					// clear SSPIF
			SSPBUF = Data;							// load the data to send
			st_bit(SSPCON, CKP);					// release SCL
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while (ts_bit(SSPIF_PIR, SSPIF)==0 && MX_I2C_TIMEOUT_X--);			// wait for SSPIF to go high before we read the Ack
			cr_bit(SSPIF_PIR, SSPIF);					// clear SSPIF
			return ts_bit(SSPCON2, ACKSTAT)?1:0;	// return ACKSTAT
		#endif
	#elif (MX_I2C_CHANNEL_X == 2)
		#ifdef _I2C1CON0_EN_POSN		//New devices have I2CxCON0 register
			return 0;
		#else
			cr_bit(SSP2PIRP, SSP2IF);					// clear SSPIF
			SSP2BUF = Data;							// load the data to send
			st_bit(SSP2CON1, CKP);					// release SCL
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while (ts_bit(SSP2PIRP, SSP2IF)==0 && MX_I2C_TIMEOUT_X--);		// wait for SSPIF to go high before we read the Ack
			cr_bit(SSP2PIRP, SSP2IF);					// clear SSPIF
			return ts_bit(SSP2CON2, ACKSTAT)?1:0;	// return ACKSTAT
		#endif
	#else
		return 0;
	#endif
}

// Returns the byte from the shift buffer
// and sends Ack or Nak (0=Ack=More, 1=Nak=Last)
// nb. First check FC_CAL_I2C_Slave_Status() & 1
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_RxByte_, (MX_UINT8 Last))
{
	#if (MX_I2C_CHANNEL_X == 1)
		MX_UINT8 Data;

		#ifdef _I2C1CON0_EN_POSN		//New devices have I2CxCON0 register
		#else

			Data = SSPBUF;
			if (ts_bit(SSPSTAT, SSPSTAT_R_NOT_W))
			{
				#ifdef SSPCON3
					// It's a read from Slave by Master
					if (ts_bit(SSPCON3, AHEN))
					{
						Last ? st_bit(SSPCON2, ACKDT) : cr_bit(SSPCON2, ACKDT);	// Ack or Nak
						st_bit(SSPCON1, CKP);									// release SCL
						MX_I2C_TIMEOUT_X = 0xFFFF;
						while (ts_bit(SSPCON1, CKP) && MX_I2C_TIMEOUT_X--);							// wait for CKP to go low again indicating that the Ack has been sent
					}
				#endif
			}
			else
			{
				// It's a write from Master to Slave
				Last ? st_bit(SSPCON2, ACKDT) : cr_bit(SSPCON2, ACKDT);	// Ack or Nak
				st_bit(SSPCON, CKP);									// release SCL
				if (0 == Last)
				{
					MX_I2C_TIMEOUT_X = 0xFFFF;
					while (ts_bit(SSPCON, CKP) && MX_I2C_TIMEOUT_X--);						// wait for CKP to go low again indicating that the Ack has been sent
					st_bit(SSPCON, CKP);								// release SCL (again)
				}
			}

		#endif

		return Data;			// return the received data

	#elif (MX_I2C_CHANNEL_X == 2)
		MX_UINT8 Data;

		#ifdef _I2C1CON0_EN_POSN		//New devices have I2CxCON0 register
		#else
			Data = SSP2BUF;
			if (ts_bit(SSP2STAT, SSP2STAT_R_NOT_W))
			{
				#ifdef SSP2CON3
				// It's a read from Slave by Master
				if (ts_bit(SSP2CON3, AHEN))
				{
					Last ? st_bit(SSP2CON2, ACKDT) : cr_bit(SSP2CON2, ACKDT);	// Ack or Nak
					st_bit(SSP2CON1, CKP);									// release SCL
					MX_I2C_TIMEOUT_X = 0xFFFF;
					while (ts_bit(SSP2CON1, CKP) && MX_I2C_TIMEOUT_X--);							// wait for CKP to go low again indicating that the Ack has been sent
				}
				#endif
			}
			else
			{
				// It's a write from Master to Slave
				Last ? st_bit(SSP2CON2, ACKDT) : cr_bit(SSP2CON2, ACKDT);	// Ack or Nak
				st_bit(SSP2CON1, CKP);									// release SCL
				if (0 == Last)
				{
					MX_I2C_TIMEOUT_X = 0xFFFF;
					while (ts_bit(SSP2CON1, CKP) && MX_I2C_TIMEOUT_X--);						// wait for CKP to go low again indicating that the Ack has been sent
					st_bit(SSP2CON1, CKP);								// release SCL (again)
				}
			}
		#endif

		return Data;			// return the received data
	#else
		return 0;
	#endif
}




/**************************************************
	Master Transaction functions
**************************************************/

#define MX_I2C_ADDRESS_X		CAL_APPEND(MX_I2C_ADDRESS_, MX_I2C_NUM)
#define MX_I2C_INIT_X			CAL_APPEND(MX_I2C_INIT_, MX_I2C_NUM)

MX_UINT8 MX_I2C_ADDRESS_X;
MX_UINT8 MX_I2C_INIT_X = 0;


CALFUNCTION(MX_UINT8, FC_CAL_I2C_Transaction_Init_,   (MX_UINT8 SlaveAddress))
{
	MX_I2C_ADDRESS_X = SlaveAddress;

	if (MX_I2C_INIT_X == 0)
	{
		MX_I2C_INIT_X = 1;
		CALFUNCTION(, FC_CAL_I2C_Master_Init_, ());
	}

	return 1;	// Success
}


CALFUNCTION(MX_UINT16, FC_CAL_I2C_Transaction_Read_,   (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length))
{
	MX_UINT8 fail = 0;

	if (Length > Size) return 0;

	#if (MX_I2C_CHANNEL_X == 1)						//Use Master I2C Hardware 1
		#ifdef _I2C1CON0_EN_POSN					//New devices have I2CxCON0 register
			I2C1STAT1bits.CLRBF = 1;
			I2C1ADB1 = ((MX_I2C_ADDRESS_X<<1)|1); 	//I2C address, read
			I2C1CNTL = Length; 						//Number of bytes excluding address
			I2C1CNTH = Length>>8;
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)						//Use Master I2C Hardware 2
		#ifdef _I2C2CON0_EN_POSN					//New devices have I2CxCON0 register
			I2C2STAT1bits.CLRBF = 1;
			I2C2ADB1 = ((MX_I2C_ADDRESS_X<<1)|1); 	//I2C address, read
			I2C2CNTL = Length; 						//Number of bytes excluding address
			I2C2CNTH = Length>>8;
		#endif
	#endif

	MX_UINT16 n = 0;
	CALFUNCTION( , FC_CAL_I2C_Master_Start_, ());

	#if (MX_I2C_CHANNEL_X == 1)						//Use Master I2C Hardware 1
		#ifdef _I2C1CON0_EN_POSN					//New devices have I2CxCON0 register
			I2C1CON0bits.RSEN=0; 					// Disable restart mode now restart condition has completed: note the order in which this is cleared is important
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)						//Use Master I2C Hardware 2
		#ifdef _I2C2CON0_EN_POSN					//New devices have I2CxCON0 register
			I2C2CON0bits.RSEN=0; 					// Disable restart mode now restart condition has completed: note the order in which this is cleared is important
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X > 0)					//Use Master I2C Hardware
		#ifdef _I2C1CON0_EN_POSN					//New devices have I2CxCON0 register
		#else
			if ( CALFUNCTION( , FC_CAL_I2C_Master_TxByte_, ((MX_I2C_ADDRESS_X<<1)|1)))
				return 0;
		#endif
	#else
		if ( CALFUNCTION( , FC_CAL_I2C_Master_TxByte_, ((MX_I2C_ADDRESS_X<<1)|1)))
			return 0;
	#endif

	while (n < Length)
	{
		Buffer[n] = CALFUNCTION(, FC_CAL_I2C_Master_RxByte_, ((n+1==Length)?1:0));
		++n;
	}

	CALFUNCTION( , FC_CAL_I2C_Master_Stop_, ());

	if (fail)
		return 0;

	return n;
}


CALFUNCTION(MX_UINT16, FC_CAL_I2C_Transaction_Write_,  (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length))
{
	MX_UINT8 sendStop = 1;
	MX_UINT16 fail = 0;
	if (Length & 0x8000)
	{
		Length = Length & 0x7FFF;
		sendStop = 0;
	}
	if (Length > Size) return 0;

	#if (MX_I2C_CHANNEL_X == 1)					//Use Master I2C Hardware 1
		#ifdef _I2C1CON0_EN_POSN				//New devices have I2CxCON0 register
			I2C1STAT1bits.CLRBF = 1;
			I2C1ADB1 = (MX_I2C_ADDRESS_X<<1); 	//I2C address, write
			I2C1CNTL = Length; 					//Number of bytes excluding address
			I2C1CNTH = Length>>8;

			if (sendStop == 0)
				 I2C1CON0bits.RSEN=1; 			// Enable restart mode: note the order in which this is set is important
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)					//Use Master I2C Hardware 2
		#ifdef _I2C2CON0_EN_POSN				//New devices have I2CxCON0 register
			I2C2STAT1bits.CLRBF = 1;
			I2C2ADB1 = (MX_I2C_ADDRESS_X<<1); 	//I2C address, write
			I2C2CNTL = Length; 					//Number of bytes excluding address
			I2C2CNTH = Length>>8;

			if (sendStop == 0)
				 I2C2CON0bits.RSEN=1; 			// Enable restart mode: note the order in which this is set is important
		#endif
	#endif

	MX_UINT16 n = 0;
	CALFUNCTION( , FC_CAL_I2C_Master_Start_, ());

	#if (MX_I2C_CHANNEL_X > 0)					//Use Master I2C Hardware
		#ifdef _I2C1CON0_EN_POSN					//New devices have I2CxCON0 register
		#else
			if ( CALFUNCTION( , FC_CAL_I2C_Master_TxByte_, (MX_I2C_ADDRESS_X<<1)))
				return 0;
		#endif
	#else
		if ( CALFUNCTION( , FC_CAL_I2C_Master_TxByte_, (MX_I2C_ADDRESS_X<<1)))
			return 0;
	#endif

	while (n < Length)
	{
		if ( CALFUNCTION( , FC_CAL_I2C_Master_TxByte_, (Buffer[n])))
			fail = n+1;
		++n;
	}

	if (sendStop)
		CALFUNCTION( , FC_CAL_I2C_Master_Stop_, ());

	#if (MX_I2C_CHANNEL_X == 1)					//Use Master I2C Hardware 1
		#ifdef _I2C1CON0_EN_POSN				//New devices have I2CxCON0 register
			else
			{
				MX_I2C_TIMEOUT_X = 0xFFFF;
				while(ts_bit(I2C1CON0,MDR) == 0 && MX_I2C_TIMEOUT_X--);			//Wait for master to be ready to accept more
			}
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)					//Use Master I2C Hardware 2
		#ifdef _I2C2CON0_EN_POSN				//New devices have I2CxCON0 register
			else
			{
				MX_I2C_TIMEOUT_X = 0xFFFF;
				while(ts_bit(I2C1CON0,MDR) == 0 && MX_I2C_TIMEOUT_X--);			//Wait for master to be ready to accept more
			}
		#endif
	#endif

	if (fail)
		return (fail-1);

	return n;
}


CALFUNCTION(void,     FC_CAL_I2C_Transaction_Uninit_, (void))
{
	CALFUNCTION(, FC_CAL_I2C_Master_Uninit_, ());
}
