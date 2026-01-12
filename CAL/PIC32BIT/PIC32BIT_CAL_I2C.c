// CRC: A6459004C43C0517DC6DFC5681C2AD698104299A14C9E1875427A2F7EF4303D9CFD76A29863CD488DE50EA9D9C0AC8D1FAE5D3E402C32CC04ABA32A404641158F3C76BAD8EEF9A81C5BD6FC7FBC82BBEEAB3A14A2A013993711B8143522C2B6940BFFB513FF76BE6DDC42BA0CC69CD6CBC5EEB23B16A1DF7423CE02CE07989A2EFCC8AFFEABC4FEDFEEB7DE169ACA7FFD8D86CB23072556D7767A3A1A4EDE80432BB7E8EAEBF5398941598F07780284ED4FBD53EB795428B549D34A0D5AD11F3D60917B61D9A6F98D9102E2CC50B0BB02D2164F516035FDF07369D99911C23D5D43797C197BFDEC5
// REVISION: 2.0
// GUID: A7674516-2E55-4BCD-BE84-D4310FB85365
// DATE: 20\01\2023
// DIR: CAL\PIC32BIT\PIC32BIT_CAL_I2C.c
/*********************************************************************
 *                  Flowcode CAL I2C File
 *
 * File: PIC16BIT_CAL_I2C.c
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
 * 230911 | BR | Created
 * 020312 | BR | Updated to v5.1 CAL Schema
 * 040912 | BR | Minor mod to switch I2C registers based on dsPIC30F target definition
 * 030713 | LM | Standard API calls
 * 280813 | LM | Removed unused defines
 * 071013 | LM | fix for single I2C channel
 * 071013 | LM | Fixed Baud Rate Generator value
 * 260914 | LM | Changes to Slave macro API
 * 021014 | LM | Implemented Slave functionality
 * 220118 | LM | Addition of transaction functions
 *
 */



#define MX_I2C_CHANNEL_X		CAL_APPEND(MX_I2C_CHANNEL_, MX_I2C_NUM)
#define MX_I2C_SDA_PIN_X		CAL_APPEND(MX_I2C_SDA_PIN_, MX_I2C_NUM)
#define MX_I2C_SDA_PORT_X		CAL_APPEND(MX_I2C_SDA_PORT_, MX_I2C_NUM)
#define MX_I2C_SDA_TRIS_X		CAL_APPEND(MX_I2C_SDA_TRIS_, MX_I2C_NUM)
#define MX_I2C_SCL_PIN_X		CAL_APPEND(MX_I2C_SCL_PIN_, MX_I2C_NUM)
#define MX_I2C_SCL_PORT_X		CAL_APPEND(MX_I2C_SCL_PORT_, MX_I2C_NUM)
#define MX_I2C_SCL_TRIS_X		CAL_APPEND(MX_I2C_SCL_TRIS_, MX_I2C_NUM)
#define MX_I2C_BMODE_X			CAL_APPEND(MX_I2C_BMODE_, MX_I2C_NUM)
#define MX_I2C_BAUD_X			CAL_APPEND(MX_I2C_BAUD_, MX_I2C_NUM)
#define MX_I2C_INT_X			CAL_APPEND(MX_I2C_INT_, MX_I2C_NUM)
#define MX_I2C_STOPDEL_X		CAL_APPEND(MX_I2C_STOPDEL_, MX_I2C_NUM)
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
MX_UINT32 MX_I2C_TIMEOUT_X;

//Ensure I2C1CON registers are defined correctly
#if (defined _I2CADD)
	#define I2C1RCV			I2CRCV
	#define I2C1TRN			I2CTRN
	#define I2C1BRG			I2CBRG
	#define I2C1CON			I2CCON
	#define I2C1STAT		I2CSTAT
	#define I2C1ADD			I2CADD
	#define I2C1RCVbits		I2CRCVbits
	#define I2C1TRNbits		I2CTRNbits
	#define I2C1BRGbits		I2CBRGbits
	#define I2C1CONbits		I2CCONbits
	#define I2C1STATbits	I2CSTATbits
	#define I2C1ADDbits		I2CADDbits
#endif


#if (MX_I2C_CHANNEL_X == 0)
  #ifndef MX_I2C_SW_DEL
	#define MX_I2C_SW_DEL
	#define MX_I2C_SW_BAUD	(500000 / MX_I2C_BAUD_X)

	#if (MX_I2C_SW_BAUD < 1)
		#define MX_I2C_DELAY	delay_us(1);
	#else
		#define MX_I2C_DELAY	delay_us(MX_I2C_SW_BAUD);
	#endif

  #endif
#else

  #ifdef MX_UART_BAUD_DIV
    #define MX_I2C_HW_BAUD_X	((((1.0f/ (MX_I2C_BAUD_X)) - (0.104f/1000000.0f)) * MX_CLK_SPEED) - 2 )
  #else
    #define MX_I2C_HW_BAUD_X	((((1.0f/ (2.0f * MX_I2C_BAUD_X)) - (0.104f/1000000.0f)) * MX_CLK_SPEED) - 2 )
  #endif

  //Check for rollover
  //#if MX_I2C_HW_BAUD > 511
  //	#undef MX_I2C_HW_BAUD
  //	#define MX_I2C_HW_BAUD 511
  //#endif
#endif


CALFUNCTION(void, FC_CAL_I2C_Master_Init_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)					//Use Master I2C Software														//Use Master I2C Software
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Configure SDA as Input
		FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Configure SCL as Input
	#endif

	#if (MX_I2C_CHANNEL_X == 1)					//Use Master I2C Hardware CH1
		#ifdef MX_I2C_SLEW						//Slew Rate Control
			if (MX_I2C_BMODE_X & 0x01)
			  	I2C1CONbits.DISSLW = 0;
			else
			  	I2C1CONbits.DISSLW = 1;
		#else
			I2C1CONbits.DISSLW = 1;
		#endif

		#ifdef MX_I2C_SMBUS					//SMBus Control
			if (MX_I2C_BMODE_X & 0x02)
		 		I2C1CONbits.SMEN = 1;
			else
		  		I2C1CONbits.SMEN = 0;
		#else
			I2C1CONbits.SMEN = 1;
		#endif

		I2C1BRG = MX_I2C_HW_BAUD_X;
		I2C1CONbits.ON = 1;
	#endif

	#if (MX_I2C_CHANNEL_X == 2)					//Use Master I2C Hardware CH2
		#ifdef MX_I2C_SLEW						//Slew Rate Control
			if (MX_I2C_BMODE_X & 0x01)
				I2C2CONbits.DISSLW = 0;
			else
				I2C2CONbits.DISSLW = 1;
		#else
			I2C2CONbits.DISSLW = 1;
		#endif

		#ifdef MX_I2C_SMBUS					//SMBus Control
			if (MX_I2C_BMODE_X & 0x02)
				I2C2CONbits.SMEN = 1;
			else
				I2C2CONbits.SMEN = 0;
		#else
			I2C2CONbits.SMEN = 1;
		#endif

		I2C2BRG = MX_I2C_HW_BAUD_X;
		I2C2CONbits.ON = 1;
	#endif

	#if (MX_I2C_CHANNEL_X == 3)					//Use Master I2C Hardware CH2
		#ifdef MX_I2C_SLEW						//Slew Rate Control
			if (MX_I2C_BMODE_X & 0x01)
				I2C3CONbits.DISSLW = 0;
			else
				I2C3CONbits.DISSLW = 1;
		#else
			I2C3CONbits.DISSLW = 1;
		#endif

		#ifdef MX_I2C_SMBUS					//SMBus Control
			if (MX_I2C_BMODE_X & 0x02)
				I2C3CONbits.SMEN = 1;
			else
				I2C3CONbits.SMEN = 0;
		#else
			I2C3CONbits.SMEN = 1;
		#endif

		I2C3BRG = MX_I2C_HW_BAUD_X;
		I2C3CONbits.ON = 1;
	#endif

	#if (MX_I2C_CHANNEL_X == 4)					//Use Master I2C Hardware CH2
		#ifdef MX_I2C_SLEW						//Slew Rate Control
			if (MX_I2C_BMODE_X & 0x01)
				I2C4CONbits.DISSLW = 0;
			else
				I2C4CONbits.DISSLW = 1;
		#else
			I2C4CONbits.DISSLW = 1;
		#endif

		#ifdef MX_I2C_SMBUS					//SMBus Control
			if (MX_I2C_BMODE_X & 0x02)
				I2C4CONbits.SMEN = 1;
			else
				I2C4CONbits.SMEN = 0;
		#else
			I2C4CONbits.SMEN = 1;
		#endif

		I2C4BRG = MX_I2C_HW_BAUD_X;
		I2C4CONbits.ON = 1;
	#endif

	#if (MX_I2C_CHANNEL_X == 5)					//Use Master I2C Hardware CH2
		#ifdef MX_I2C_SLEW						//Slew Rate Control
			if (MX_I2C_BMODE_X & 0x01)
				I2C5CONbits.DISSLW = 0;
			else
				I2C5CONbits.DISSLW = 1;
		#else
			I2C5CONbits.DISSLW = 1;
		#endif

		#ifdef MX_I2C_SMBUS					//SMBus Control
			if (MX_I2C_BMODE_X & 0x02)
				I2C5CONbits.SMEN = 1;
			else
				I2C5CONbits.SMEN = 0;
		#else
			I2C5CONbits.SMEN = 1;
		#endif

		I2C5BRG = MX_I2C_HW_BAUD_X;
		I2C5CONbits.ON = 1;
	#endif

}

CALFUNCTION(void, FC_CAL_I2C_Master_Uninit_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)															//Use Master I2C Software
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Configure SDA as Input
		FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Configure SCL as Input
	#endif

	#if (MX_I2C_CHANNEL_X == 1)		//Use Master I2C Hardware CH1
		I2C1CONbits.ON = 0;
	#endif

	#if (MX_I2C_CHANNEL_X == 2)		//Use Master I2C Hardware CH2
		I2C2CONbits.ON = 0;
	#endif

	#if (MX_I2C_CHANNEL_X == 3)		//Use Master I2C Hardware CH2
		I2C3CONbits.ON = 0;
	#endif

	#if (MX_I2C_CHANNEL_X == 4)		//Use Master I2C Hardware CH2
		I2C4CONbits.ON = 0;
	#endif

	#if (MX_I2C_CHANNEL_X == 5)		//Use Master I2C Hardware CH2
		I2C5CONbits.ON = 0;
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

	#if (MX_I2C_CHANNEL_X == 1)		//Use Master I2C Hardware CH1
		I2C1CONbits.SEN = 1;		//Initiate Start Condition
		MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C1CONbits.SEN != 0) && MX_I2C_TIMEOUT_X--);		//Wait for Start to complete
        #ifdef MX_MZ_MODE
        	delay_us(10);
        #endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)		//Use Master I2C Hardware CH2
		I2C2CONbits.SEN = 1;		//Initiate Start Condition
		MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C2CONbits.SEN != 0) && MX_I2C_TIMEOUT_X--);		//Wait for Start to complete
        #ifdef MX_MZ_MODE
        	delay_us(10);
        #endif
	#endif

	#if (MX_I2C_CHANNEL_X == 3)		//Use Master I2C Hardware CH2
		I2C3CONbits.SEN = 1;		//Initiate Start Condition
		MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C3CONbits.SEN != 0) && MX_I2C_TIMEOUT_X--);		//Wait for Start to complete
        #ifdef MX_MZ_MODE
        	delay_us(10);
        #endif
	#endif

	#if (MX_I2C_CHANNEL_X == 4)		//Use Master I2C Hardware CH2
		I2C4CONbits.SEN = 1;		//Initiate Start Condition
		MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C4CONbits.SEN != 0) && MX_I2C_TIMEOUT_X--);		//Wait for Start to complete
        #ifdef MX_MZ_MODE
        	delay_us(10);
        #endif
	#endif

	#if (MX_I2C_CHANNEL_X == 5)		//Use Master I2C Hardware CH2
		I2C5CONbits.SEN = 1;		//Initiate Start Condition
		MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C5CONbits.SEN != 0) && MX_I2C_TIMEOUT_X--);		//Wait for Start to complete
        #ifdef MX_MZ_MODE
        	delay_us(10);
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

	#if (MX_I2C_CHANNEL_X == 1)		//Use Master I2C Hardware CH1
		I2C1CONbits.RSEN = 1;		//Initiate Restart Condition
		MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C1CONbits.RSEN != 0) && MX_I2C_TIMEOUT_X--);		//Wait for Restart to complete
        #ifdef MX_MZ_MODE
        	delay_us(10);
        #endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)		//Use Master I2C Hardware CH2
		I2C2CONbits.RSEN = 1;		//Initiate Restart Condition
		MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C2CONbits.RSEN != 0) && MX_I2C_TIMEOUT_X--);		//Wait for Restart to complete
        #ifdef MX_MZ_MODE
        	delay_us(10);
        #endif
	#endif

	#if (MX_I2C_CHANNEL_X == 3)		//Use Master I2C Hardware CH2
		I2C3CONbits.RSEN = 1;		//Initiate Restart Condition
		MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C3CONbits.RSEN != 0) && MX_I2C_TIMEOUT_X--);		//Wait for Restart to complete
        #ifdef MX_MZ_MODE
        	delay_us(10);
        #endif
	#endif

	#if (MX_I2C_CHANNEL_X == 4)		//Use Master I2C Hardware CH2
		I2C4CONbits.RSEN = 1;		//Initiate Restart Condition
		MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C4CONbits.RSEN != 0) && MX_I2C_TIMEOUT_X--);		//Wait for Restart to complete
        #ifdef MX_MZ_MODE
        	delay_us(10);
        #endif
	#endif

	#if (MX_I2C_CHANNEL_X == 5)		//Use Master I2C Hardware CH2
		I2C5CONbits.RSEN = 1;		//Initiate Restart Condition
		MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C5CONbits.RSEN != 0) && MX_I2C_TIMEOUT_X--);		//Wait for Restart to complete
        #ifdef MX_MZ_MODE
        	delay_us(10);
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

	#if (MX_I2C_CHANNEL_X == 1)		//Use Master I2C Hardware CH1
		I2C1CONbits.PEN = 1;		//Initiate Stop Condition
		MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C1CONbits.PEN != 0) && MX_I2C_TIMEOUT_X--);		//Wait for Start to complete
        #ifdef MX_MZ_MODE
        	delay_us(10);
        #endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)		//Use Master I2C Hardware CH2
		I2C2CONbits.PEN = 1;		//Initiate Stop Condition
		MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C2CONbits.PEN != 0) && MX_I2C_TIMEOUT_X--);		//Wait for Start to complete
        #ifdef MX_MZ_MODE
        	delay_us(10);
        #endif
	#endif

	#if (MX_I2C_CHANNEL_X == 3)		//Use Master I2C Hardware CH2
		I2C3CONbits.PEN = 1;		//Initiate Stop Condition
		MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C3CONbits.PEN != 0) && MX_I2C_TIMEOUT_X--);		//Wait for Start to complete
        #ifdef MX_MZ_MODE
        	delay_us(10);
        #endif
	#endif

	#if (MX_I2C_CHANNEL_X == 4)		//Use Master I2C Hardware CH2
		I2C4CONbits.PEN = 1;		//Initiate Stop Condition
		MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C4CONbits.PEN != 0) && MX_I2C_TIMEOUT_X--);		//Wait for Start to complete
        #ifdef MX_MZ_MODE
        	delay_us(10);
        #endif
	#endif

	#if (MX_I2C_CHANNEL_X == 5)		//Use Master I2C Hardware CH2
		I2C5CONbits.PEN = 1;		//Initiate Stop Condition
		MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C5CONbits.PEN != 0) && MX_I2C_TIMEOUT_X--);		//Wait for Start to complete
        #ifdef MX_MZ_MODE
        	delay_us(10);
        #endif
	#endif

	#if (MX_I2C_STOPDEL_X == 1)
  	  delay_ms(10);		//Wait before reusing the I2C BUS -  avoids lockup problem exibited on some PICs
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
				MX_I2C_TIMEOUT_X = 0xFFFFFF;
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
		if (FC_CAL_Bit_In(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X))		//Get the Status Bit
			local_ack = 1;
		//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR
		FC_CAL_Bit_Low_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);			//Set SCL Low
		//MX_I2C_DELAY;																	//Removed 050613 - BR
		return (local_ack);													//0 = Ack received : 1 = Ack not received
	#endif

	#if (MX_I2C_CHANNEL_X == 1)
		if (I2C1STATbits.I2COV)		//Check for receive overflow
			return (1);
		if (I2C1STATbits.IWCOL)		//Check for transmit overflow
			return (1);

		I2C1TRN = Data;				//Send byte

        MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C1STATbits.TBF) && MX_I2C_TIMEOUT_X--);	//Check for transmit busy

        MX_I2C_TIMEOUT_X = 0xFFFFFF;
		while((I2C1STATbits.TRSTAT) && MX_I2C_TIMEOUT_X--);	//Wait for data byte to be sent

		if(I2C1STATbits.ACKSTAT)		//Check Acknowledgement
			return (1);					//No Acknowledgement
		else return (0);				//Acknowledgement OK
	#endif

	#if (MX_I2C_CHANNEL_X == 2)
		if (I2C2STATbits.I2COV)		//Check for receive overflow
			return (1);
		if (I2C2STATbits.IWCOL)		//Check for transmit overflow
			return (1);

		I2C2TRN = Data;				//Send byte

        MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C2STATbits.TBF) && MX_I2C_TIMEOUT_X--);	//Check for transmit busy

        MX_I2C_TIMEOUT_X = 0xFFFFFF;
		while((I2C2STATbits.TRSTAT) && MX_I2C_TIMEOUT_X--);	//Wait for data byte to be sent

		if(I2C2STATbits.ACKSTAT)		//Check Acknowledgement
			return (1);					//No Acknowledgement
		else return (0);				//Acknowledgement OK
	#endif

	#if (MX_I2C_CHANNEL_X == 3)
		if (I2C3STATbits.I2COV)		//Check for receive overflow
			return (1);
		if (I2C3STATbits.IWCOL)		//Check for transmit overflow
			return (1);

		I2C3TRN = Data;				//Send byte

        MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C3STATbits.TBF) && MX_I2C_TIMEOUT_X--);	//Check for transmit busy

        MX_I2C_TIMEOUT_X = 0xFFFFFF;
		while((I2C3STATbits.TRSTAT) && MX_I2C_TIMEOUT_X--);	//Wait for data byte to be sent

		if(I2C3STATbits.ACKSTAT)		//Check Acknowledgement
			return (1);					//No Acknowledgement
		else return (0);				//Acknowledgement OK
	#endif

	#if (MX_I2C_CHANNEL_X == 4)
		if (I2C4STATbits.I2COV)		//Check for receive overflow
			return (1);
		if (I2C4STATbits.IWCOL)		//Check for transmit overflow
			return (1);

		I2C4TRN = Data;				//Send byte

        MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C4STATbits.TBF) && MX_I2C_TIMEOUT_X--);	//Check for transmit busy

        MX_I2C_TIMEOUT_X = 0xFFFFFF;
		while((I2C4STATbits.TRSTAT) && MX_I2C_TIMEOUT_X--);	//Wait for data byte to be sent

		if(I2C4STATbits.ACKSTAT)		//Check Acknowledgement
			return (1);					//No Acknowledgement
		else return (0);				//Acknowledgement OK
	#endif

	#if (MX_I2C_CHANNEL_X == 5)
		if (I2C5STATbits.I2COV)		//Check for receive overflow
			return (1);
		if (I2C5STATbits.IWCOL)		//Check for transmit overflow
			return (1);

		I2C5TRN = Data;				//Send byte

        MX_I2C_TIMEOUT_X = 0xFFFFFF;
        while((I2C5STATbits.TBF) && MX_I2C_TIMEOUT_X--);	//Check for transmit busy

        MX_I2C_TIMEOUT_X = 0xFFFFFF;
		while((I2C5STATbits.TRSTAT) && MX_I2C_TIMEOUT_X--);	//Wait for data byte to be sent

		if(I2C5STATbits.ACKSTAT)		//Check Acknowledgement
			return (1);					//No Acknowledgement
		else return (0);				//Acknowledgement OK
	#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_I2C_Master_RxByte_, (MX_UINT8 Last))
{
	#if (MX_I2C_CHANNEL_X == 0)												//Use Master I2C Software
		unsigned char bit_mask;
		unsigned char Data = 0;
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);			//Set SDA High
		MX_I2C_DELAY;
		for(bit_mask=0x80;bit_mask;bit_mask=bit_mask>>1)
		{
			FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Set SCL High
			MX_I2C_DELAY;

			#if (MX_I2C_CLKSTRCH_X == 1)
				MX_I2C_TIMEOUT_X = 0xFFFFFF;
				while (FC_CAL_Bit_In(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X) == 0 && MX_I2C_TIMEOUT_X--);		//Wait for the clock to go high - Clock stretching.
			#endif

			FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);
			if(FC_CAL_Bit_In(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X))	//Read Incoming Bit
				Data = Data | bit_mask;														//Add data to variable
			FC_CAL_Bit_Low_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Set SCL Low
			MX_I2C_DELAY;																	//BR
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

	#if (MX_I2C_CHANNEL_X == 1)						//Use Master I2C Hardware
		I2C1CONbits.RCEN = 1;

		MX_I2C_TIMEOUT_X = 0xFFFFFF;
		while((I2C1CONbits.RCEN) && MX_I2C_TIMEOUT_X--);	//Wait for data read

		if (Last)
			I2C1CONbits.ACKDT = 1;		//Send Nack
		else
			I2C1CONbits.ACKDT = 0;		//Send Ack

		I2C1CONbits.ACKEN = 1;			//Initiate Ack/Nack

		MX_I2C_TIMEOUT_X = 0xFFFFFF;
		while((I2C1CONbits.ACKEN) && MX_I2C_TIMEOUT_X--);		//Wait for data read

		return(I2C1RCV);				//Store incoming data
	#endif

	#if (MX_I2C_CHANNEL_X == 2)						//Use Master I2C Hardware
		I2C2CONbits.RCEN = 1;

		MX_I2C_TIMEOUT_X = 0xFFFFFF;
		while((I2C2CONbits.RCEN) && MX_I2C_TIMEOUT_X--);	//Wait for data read

		if (Last)
			I2C2CONbits.ACKDT = 1;		//Send Nack
		else
			I2C2CONbits.ACKDT = 0;		//Send Ack

		I2C2CONbits.ACKEN = 1;			//Initiate Ack/Nack

		MX_I2C_TIMEOUT_X = 0xFFFFFF;
		while((I2C2CONbits.ACKEN) && MX_I2C_TIMEOUT_X--);		//Wait for data read

		return(I2C2RCV);				//Store incoming data
	#endif

	#if (MX_I2C_CHANNEL_X == 3)						//Use Master I2C Hardware
		I2C3CONbits.RCEN = 1;

		MX_I2C_TIMEOUT_X = 0xFFFFFF;
		while((I2C3CONbits.RCEN) && MX_I2C_TIMEOUT_X--);	//Wait for data read

		if (Last)
			I2C3CONbits.ACKDT = 1;		//Send Nack
		else
			I2C3CONbits.ACKDT = 0;		//Send Ack

		I2C3CONbits.ACKEN = 1;			//Initiate Ack/Nack

		MX_I2C_TIMEOUT_X = 0xFFFFFF;
		while((I2C3CONbits.ACKEN) && MX_I2C_TIMEOUT_X--);		//Wait for data read

		return(I2C3RCV);				//Store incoming data
	#endif

	#if (MX_I2C_CHANNEL_X == 4)						//Use Master I2C Hardware
		I2C4CONbits.RCEN = 1;

		MX_I2C_TIMEOUT_X = 0xFFFFFF;
		while((I2C4CONbits.RCEN) && MX_I2C_TIMEOUT_X--);	//Wait for data read

		if (Last)
			I2C4CONbits.ACKDT = 1;		//Send Nack
		else
			I2C4CONbits.ACKDT = 0;		//Send Ack

		I2C4CONbits.ACKEN = 1;			//Initiate Ack/Nack

		MX_I2C_TIMEOUT_X = 0xFFFFFF;
		while((I2C4CONbits.ACKEN) && MX_I2C_TIMEOUT_X--);		//Wait for data read

		return(I2C4RCV);				//Store incoming data
	#endif

	#if (MX_I2C_CHANNEL_X == 5)						//Use Master I2C Hardware
		I2C5CONbits.RCEN = 1;

		MX_I2C_TIMEOUT_X = 0xFFFFFF;
		while((I2C5CONbits.RCEN) && MX_I2C_TIMEOUT_X--);	//Wait for data read

		if (Last)
			I2C5CONbits.ACKDT = 1;		//Send Nack
		else
			I2C5CONbits.ACKDT = 0;		//Send Ack

		I2C5CONbits.ACKEN = 1;			//Initiate Ack/Nack

		MX_I2C_TIMEOUT_X = 0xFFFFFF;
		while((I2C5CONbits.ACKEN) && MX_I2C_TIMEOUT_X--);		//Wait for data read

		return(I2C5RCV);				//Store incoming data
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
	if (Length > Size) return 0;
	MX_UINT16 n = 0;
	CALFUNCTION( , FC_CAL_I2C_Master_Start_, ());
	if ( CALFUNCTION( , FC_CAL_I2C_Master_TxByte_, ((MX_I2C_ADDRESS_X<<1)|1)))
		return 0;
	while (n < Length)
	{
		Buffer[n] = CALFUNCTION(, FC_CAL_I2C_Master_RxByte_, ((n+1==Length)?1:0));
		++n;
	}
	CALFUNCTION( , FC_CAL_I2C_Master_Stop_, ());
	return n;
}

CALFUNCTION(MX_UINT16, FC_CAL_I2C_Transaction_Write_,  (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length))
{
	MX_UINT8 sendStop = 1;
	if (Length & 0x8000)
	{
		Length = Length & 0x7FFF;
		sendStop = 0;
	}
	if (Length > Size) return 0;
	MX_UINT16 n = 0;
	CALFUNCTION( , FC_CAL_I2C_Master_Start_, ());
	if ( CALFUNCTION( , FC_CAL_I2C_Master_TxByte_, (MX_I2C_ADDRESS_X<<1)))
					return 0;
	while (n < Length)
	{
		if ( CALFUNCTION( , FC_CAL_I2C_Master_TxByte_, (Buffer[n])))
			break;
		++n;
	}
	if (sendStop)
		CALFUNCTION( , FC_CAL_I2C_Master_Stop_, ());
	return n;
}

CALFUNCTION(void,     FC_CAL_I2C_Transaction_Uninit_, (void))
{
	CALFUNCTION(, FC_CAL_I2C_Master_Uninit_, ());
}
