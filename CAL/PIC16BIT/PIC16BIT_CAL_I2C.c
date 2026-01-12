// CRC: 5D982BB222882C54AB4AFF20A1590FC484D3178BD0D2510D0F5A64A7853221CAE2C33FABBE4F69A6659399D51781B7B9FAE5D3E402C32CC04ABA32A404641158F3C76BAD8EEF9A81C5BD6FC7FBC82BBEEAB3A14A2A013993711B8143522C2B69417AB4CCDCA5CF90AD633EAD1005C88DA1E994E8F962379A1A43050764A6D5D2FB0A86A9262D33DE92D3B16C61E06CBF9453BD3865BEA8FC770F7308D717B43404E4E7B06660D0EC15E4E834F41915C4B9E670B98ED97111549D34A0D5AD11F377C4C6DC9CB40069C74E90637F1EE8148645CB606C1E817EACA9CE2DF1EA8436E42CFE37638C9748
// REVISION: 2.0
// GUID: 30D6EA9C-37DA-48CF-A047-E5AA1F247330
// DATE: 20\01\2023
// DIR: CAL\PIC16BIT\PIC16BIT_CAL_I2C.c
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
MX_UINT16 MX_I2C_TIMEOUT_X;

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

#if (!defined I2C1CON)
	#if (defined I2C1CON1)
		#define I2C1CON     I2C1CON1
		#define I2C1CONbits I2C1CON1bits
	#endif
#endif

#if (!defined I2C2CON)
	#if (defined I2C2CON1)
		#define I2C2CON     I2C2CON1
		#define I2C2CONbits I2C2CON1bits
	#endif
#endif

//If software channel is enabled then define bit delay.
#if (MX_I2C_CHANNEL_X == 0)
  #ifndef MX_I2C_SW_DEL
	#define MX_I2C_SW_DEL
	#define MX_I2C_SW_BAUD	((500000 / MX_I2C_BAUD_X)-1)

	#if (MX_I2C_SW_BAUD < 1)
		#define MX_I2C_DELAY	delay_us(1);
	#else
		#define MX_I2C_DELAY	delay_us(MX_I2C_SW_BAUD);
	#endif
  #endif
#else
  #define MX_I2C_HW_BAUD	((MX_CLK_SPEED / MX_CLKS_PER_INST) / MX_I2C_BAUD_X) - 2

  //Check for rollover
  #if MX_I2C_HW_BAUD > 511
  	#undef MX_I2C_HW_BAUD
  	#define MX_I2C_HW_BAUD 511
  #endif
#endif


CALFUNCTION(void, FC_CAL_I2C_Master_Init_, (void))
{

	#if (MX_I2C_CHANNEL_X == 0)															//Use Master I2C Software
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Configure SDA as Input
		FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Configure SCL as Input
	#endif

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1
		#ifndef MX_I2C_1
			#error "This chip does not have I2C channel 1 defined"
		#else
		  #ifdef MX_I2C_SLEW												//Slew Rate Control
			if (MX_I2C_BMODE_X & 0x01)
				I2C1CONbits.DISSLW = 0;										//Slew Rate Control Enabled
			else
				I2C1CONbits.DISSLW = 1;										//Slew Rate Control Disabled
		  #else
		  	I2C1CONbits.DISSLW = 1;											//Slew Rate Control Disabled
		  #endif
		  #ifdef MX_I2C_SMBUS												//SMBus Control
			if (MX_I2C_BMODE_X & 0x02)
				I2C1CONbits.SMEN = 1;										//Enable SMBus specific inputs
			else
				I2C1CONbits.SMEN = 0;										//Disable SMBus specific inputs
		  #else
		  	I2C1CONbits.SMEN = 0;											//Disable SMBus specific inputs
		  #endif
			I2C1CONbits.I2CEN = 1;											//Enable I2C Peripheral
			I2C1BRG = MX_I2C_HW_BAUD;										//Set the Baud Rate
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)												//Use Master I2C Hardware 2
		#ifndef MX_I2C_2
			#error "This chip does not have I2C channel 2 defined"
		#else
		  #ifdef MX_I2C_SLEW												//Slew Rate Control
			if (MX_I2C_BMODE_X & 0x01)
				I2C2CONbits.DISSLW = 0;										//Slew Rate Control Enabled
			else
				I2C2CONbits.DISSLW = 1;										//Slew Rate Control Disabled
		  #else
		  	I2C2CONbits.DISSLW = 1;											//Slew Rate Control Disabled
		  #endif
		  #ifdef MX_I2C_SMBUS												//SMBus Control
			if (MX_I2C_BMODE_X & 0x02)
				I2C2CONbits.SMEN = 1;										//Enable SMBus specific inputs
			else
				I2C2CONbits.SMEN = 0;										//Disable SMBus specific inputs
		  #else
		  	I2C2CONbits.SMEN = 0;											//Disable SMBus specific inputs
		  #endif
			I2C2CONbits.I2CEN = 1;											//Enable I2C Peripheral
			I2C2BRG = MX_I2C_HW_BAUD;										//Set the Baud Rate
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 3)												//Use Master I2C Hardware 3
		#ifndef MX_I2C_3
			#error "This chip does not have I2C channel 3 defined"
		#else
		  #ifdef MX_I2C_SLEW												//Slew Rate Control
			if (MX_I2C_BMODE_X & 0x01)
				I2C3CONbits.DISSLW = 0;										//Slew Rate Control Enabled
			else
				I2C3CONbits.DISSLW = 1;										//Slew Rate Control Disabled
		  #else
		  	I2C3CONbits.DISSLW = 1;											//Slew Rate Control Disabled
		  #endif
		  #ifdef MX_I2C_SMBUS												//SMBus Control
			if (MX_I2C_BMODE_X & 0x02)
				I2C3CONbits.SMEN = 1;										//Enable SMBus specific inputs
			else
				I2C3CONbits.SMEN = 0;										//Disable SMBus specific inputs
		  #else
		  	I2C3CONbits.SMEN = 0;											//Disable SMBus specific inputs
		  #endif
			I2C3CONbits.I2CEN = 1;											//Enable I2C Peripheral
			I2C3BRG = MX_I2C_HW_BAUD;										//Set the Baud Rate
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 4)												//Use Master I2C Hardware 4
		#ifndef MX_I2C_4
			#error "This chip does not have I2C channel 4 defined"
		#else
		  #ifdef MX_I2C_SLEW												//Slew Rate Control
			if (MX_I2C_BMODE_X & 0x01)
				I2C4CONbits.DISSLW = 0;										//Slew Rate Control Enabled
			else
				I2C4CONbits.DISSLW = 1;										//Slew Rate Control Disabled
		  #else
		  	I2C4CONbits.DISSLW = 1;											//Slew Rate Control Disabled
		  #endif
		  #ifdef MX_I2C_SMBUS												//SMBus Control
			if (MX_I2C_BMODE_X & 0x02)
				I2C4CONbits.SMEN = 1;										//Enable SMBus specific inputs
			else
				I2C4CONbits.SMEN = 0;										//Disable SMBus specific inputs
		  #else
		  	I2C4CONbits.SMEN = 0;											//Disable SMBus specific inputs
		  #endif
			I2C4CONbits.I2CEN = 1;											//Enable I2C Peripheral
			I2C4BRG = MX_I2C_HW_BAUD;										//Set the Baud Rate
		#endif
	#endif
}

CALFUNCTION(void, FC_CAL_I2C_Master_Uninit_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)															//Use Master I2C Software
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Configure SDA as Input
		FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Configure SCL as Input
	#endif

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1
		I2C1CON = 0;														//Disable SSP
	#endif

	#if (MX_I2C_CHANNEL_X == 2)												//Use Master I2C Hardware 2
		I2C2CON = 0;														//Disable SSP
	#endif

	#if (MX_I2C_CHANNEL_X == 3)												//Use Master I2C Hardware 3
		I2C3CON = 0;														//Disable SSP
	#endif

	#if (MX_I2C_CHANNEL_X == 4)												//Use Master I2C Hardware 4
		I2C4CON = 0;														//Disable SSP
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

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1
		I2C1CONbits.SEN = 1;												//Initiate start condition
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C1CONbits.SEN == 1 && MX_I2C_TIMEOUT_X--);										//Wait for start bit to be generated
	#endif

	#if (MX_I2C_CHANNEL_X == 2)												//Use Master I2C Hardware 2
		I2C2CONbits.SEN = 1;												//Initiate start condition
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C2CONbits.SEN == 1 && MX_I2C_TIMEOUT_X--);										//Wait for start bit to be generated
	#endif

	#if (MX_I2C_CHANNEL_X == 3)												//Use Master I2C Hardware 3
		I2C3CONbits.SEN = 1;												//Initiate start condition
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C3CONbits.SEN == 1 && MX_I2C_TIMEOUT_X--);										//Wait for start bit to be generated
	#endif

	#if (MX_I2C_CHANNEL_X == 4)												//Use Master I2C Hardware 4
		I2C4CONbits.SEN = 1;												//Initiate start condition
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C4CONbits.SEN == 1 && MX_I2C_TIMEOUT_X--);										//Wait for start bit to be generated
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

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1
		I2C1CONbits.RSEN = 1;												//Initiate restart condition
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C1CONbits.RSEN == 1 && MX_I2C_TIMEOUT_X--);										//Wait for restart bit to be generated
	#endif

	#if (MX_I2C_CHANNEL_X == 2)												//Use Master I2C Hardware 2
		I2C2CONbits.RSEN = 1;												//Initiate restart condition
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C2CONbits.RSEN == 1 && MX_I2C_TIMEOUT_X--);										//Wait for restart bit to be generated
	#endif

	#if (MX_I2C_CHANNEL_X == 3)												//Use Master I2C Hardware 3
		I2C3CONbits.RSEN = 1;												//Initiate restart condition
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C3CONbits.RSEN == 1 && MX_I2C_TIMEOUT_X--);										//Wait for restart bit to be generated
	#endif

	#if (MX_I2C_CHANNEL_X == 4)												//Use Master I2C Hardware 4
		I2C4CONbits.RSEN = 1;												//Initiate restart condition
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C4CONbits.RSEN == 1 && MX_I2C_TIMEOUT_X--);										//Wait for restart bit to be generated
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

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1
		I2C1CONbits.PEN = 1;												//Initiate stop condition
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C1CONbits.PEN == 1 && MX_I2C_TIMEOUT_X--);										//Wait for stop bit to be generated
	#endif

	#if (MX_I2C_CHANNEL_X == 2)												//Use Master I2C Hardware 2
		I2C2CONbits.PEN = 1;												//Initiate stop condition
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C2CONbits.PEN == 1 && MX_I2C_TIMEOUT_X--);										//Wait for stop bit to be generated
	#endif

	#if (MX_I2C_CHANNEL_X == 3)												//Use Master I2C Hardware 3
		I2C3CONbits.PEN = 1;												//Initiate stop condition
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C3CONbits.PEN == 1 && MX_I2C_TIMEOUT_X--);										//Wait for stop bit to be generated
	#endif

	#if (MX_I2C_CHANNEL_X == 4)												//Use Master I2C Hardware 4
		I2C4CONbits.PEN = 1;												//Initiate stop condition
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C4CONbits.PEN == 1 && MX_I2C_TIMEOUT_X--);										//Wait for stop bit to be generated
	#endif

	#if (MX_I2C_STOPDEL_X == 1)
		delay_ms(10);														//Wait before reusing the I2C BUS
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
		if (FC_CAL_Bit_In(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X))		//Get the Status Bit
			local_ack = 1;
		//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR
		FC_CAL_Bit_Low_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);			//Set SCL Low
		//MX_I2C_DELAY;																	//Removed 050613 - BR
		return (local_ack);													//0 = Ack received : 1 = Ack not received
	#endif

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1
		I2C1TRN = Data;														//Send byte
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C1STATbits.TRSTAT == 1 && MX_I2C_TIMEOUT_X--);									//Wait for data byte to be sent
		if(I2C1STATbits.ACKSTAT == 1)										//Check Acknowledgement
			return (1);														//No Acknowledgement
		else return (0);													//Acknowledgement received
	#endif

	#if (MX_I2C_CHANNEL_X == 2)												//Use Master I2C Hardware 2
		I2C2TRN = Data;														//Send byte
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C2STATbits.TRSTAT == 1 && MX_I2C_TIMEOUT_X--);									//Wait for data byte to be sent
		if(I2C2STATbits.ACKSTAT == 1)										//Check Acknowledgement
			return (1);														//No Acknowledgement
		else return (0);													//Acknowledgement received
	#endif

	#if (MX_I2C_CHANNEL_X == 3)												//Use Master I2C Hardware 3
		I2C3TRN = Data;														//Send byte
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C3STATbits.TRSTAT == 1 && MX_I2C_TIMEOUT_X--);									//Wait for data byte to be sent
		if(I2C3STATbits.ACKSTAT == 1)										//Check Acknowledgement
			return (1);														//No Acknowledgement
		else return (0);													//Acknowledgement received
	#endif

	#if (MX_I2C_CHANNEL_X == 4)												//Use Master I2C Hardware 4
		I2C4TRN = Data;														//Send byte
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C4STATbits.TRSTAT == 1 && MX_I2C_TIMEOUT_X--);									//Wait for data byte to be sent
		if(I2C4STATbits.ACKSTAT == 1)										//Check Acknowledgement
			return (1);														//No Acknowledgement
		else return (0);													//Acknowledgement received
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

	#if (MX_I2C_CHANNEL_X == 1)						//Use Master I2C Hardware 1
		I2C1CONbits.RCEN = 1;						//Initiate Read
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C1CONbits.RCEN == 1 && MX_I2C_TIMEOUT_X--);				//Wait for data read
		if (Last)
			I2C1CONbits.ACKDT = 1;					//Send Nack
		else I2C1CONbits.ACKDT = 0;					//Send Ack
		I2C1CONbits.ACKEN = 1;						//Initiate Nack
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C1CONbits.ACKEN && MX_I2C_TIMEOUT_X--);					//Wait for data read
		return(I2C1RCV);							//Store incoming data
	#endif

	#if (MX_I2C_CHANNEL_X == 2)						//Use Master I2C Hardware 2
		I2C2CONbits.RCEN = 1;						//Initiate Read
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C2CONbits.RCEN == 1 && MX_I2C_TIMEOUT_X--);				//Wait for data read
		if (Last)
			I2C2CONbits.ACKDT = 1;					//Send Nack
		else I2C2CONbits.ACKDT = 0;					//Send Ack
		I2C2CONbits.ACKEN = 1;						//Initiate Nack
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C2CONbits.ACKEN && MX_I2C_TIMEOUT_X--);					//Wait for data read
		return(I2C2RCV);							//Store incoming data
	#endif

	#if (MX_I2C_CHANNEL_X == 3)						//Use Master I2C Hardware 3
		I2C3CONbits.RCEN = 1;						//Initiate Read
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C3CONbits.RCEN == 1 && MX_I2C_TIMEOUT_X--);				//Wait for data read
		if (Last)
			I2C3CONbits.ACKDT = 1;					//Send Nack
		else I2C3CONbits.ACKDT = 0;					//Send Ack
		I2C3CONbits.ACKEN = 1;						//Initiate Nack
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C3CONbits.ACKEN && MX_I2C_TIMEOUT_X--);					//Wait for data read
		return(I2C3RCV);							//Store incoming data
	#endif

	#if (MX_I2C_CHANNEL_X == 4)						//Use Master I2C Hardware 4
		I2C4CONbits.RCEN = 1;						//Initiate Read
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C4CONbits.RCEN == 1 && MX_I2C_TIMEOUT_X--);				//Wait for data read
		if (Last)
			I2C4CONbits.ACKDT = 1;					//Send Nack
		else I2C4CONbits.ACKDT = 0;					//Send Ack
		I2C4CONbits.ACKEN = 1;						//Initiate Nack
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while(I2C4CONbits.ACKEN && MX_I2C_TIMEOUT_X--);					//Wait for data read
		return(I2C4RCV);							//Store incoming data
	#endif
}


// Slave functionality

// nb. Not all processors support a Mask (e.g. dsPIC30F)
CALFUNCTION(void, FC_CAL_I2C_Slave_Init_, (MX_UINT8 Address, MX_UINT8 Mask))
{
	#if (MX_I2C_CHANNEL_X == 1)
		I2C1CON = 0b1000000001000000;
		I2C1ADD = (MX_UINT16)Address >> 1;
		#ifdef I2C1MSK
		I2C1MSK = (MX_UINT16)Mask >> 1;
		#endif
		#ifdef _SI2C1IF
		IFS1bits.SI2C1IF = 0;
		#else
		IFS0bits.SI2CIF = 0;
		#endif
	#endif
	#if (MX_I2C_CHANNEL_X == 2)
		I2C2CON = 0b1000000001000000;
		I2C2ADD = (MX_UINT16)Address >> 1;
		I2C2MSK = (MX_UINT16)Mask >> 1;
		IFS3bits.SI2C2IF = 0;
	#endif
	#if (MX_I2C_CHANNEL_X == 3)
		I2C3CON = 0b1000000001000000;
		I2C3ADD = (MX_UINT16)Address >> 1;
		I2C3MSK = (MX_UINT16)Mask >> 1;
		IFS5bits.SI2C3IF = 0;
	#endif
	#if (MX_I2C_CHANNEL_X == 4)
		I2C4CON = 0b1000000001000000;
		I2C4ADD = (MX_UINT16)Address >> 1;
		I2C4MSK = (MX_UINT16)Mask >> 1;
		IFS7bits.SI2C4IF = 0;
	#endif
}

// I2C is disabled via this function
CALFUNCTION(void, FC_CAL_I2C_Slave_Uninit_, (void))
{
	#if (MX_I2C_CHANNEL_X == 1)
		I2C1CON = 0;
	#endif
	#if (MX_I2C_CHANNEL_X == 2)
		I2C2CON = 0;
	#endif
	#if (MX_I2C_CHANNEL_X == 3)
		I2C3CON = 0;
	#endif
	#if (MX_I2C_CHANNEL_X == 4)
		I2C4CON = 0;
	#endif
}

// Data is sent and Ack/Nak from Master is returned
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_TxByte_, (MX_UINT8 Data))
{
	#if (MX_I2C_CHANNEL_X == 1)
		#ifdef _SI2C1IF
		IFS1bits.SI2C1IF = 0;
		#else
		IFS0bits.SI2CIF = 0;
		#endif
		I2C1TRN = Data;
		I2C1CONbits.SCLREL = 1;
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while ((I2C1CONbits.SCLREL)&&(I2C1STATbits.S) && MX_I2C_TIMEOUT_X--);
		#ifdef _SI2C1IF
		IFS1bits.SI2C1IF = 0;
		#else
		IFS0bits.SI2CIF = 0;
		#endif
		return ((I2C1STATbits.ACKSTAT) || (!I2C1STATbits.S))?1:0;
	#endif
	#if (MX_I2C_CHANNEL_X == 2)
		IFS3bits.SI2C2IF = 0;
		I2C2TRN = Data;
		I2C2CONbits.SCLREL = 1;
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while ((I2C2CONbits.SCLREL)&&(I2C2STATbits.S) && MX_I2C_TIMEOUT_X--);
		IFS3bits.SI2C2IF = 0;
		return ((I2C2STATbits.ACKSTAT) || (!I2C2STATbits.S))?1:0;
	#endif
	#if (MX_I2C_CHANNEL_X == 3)
		IFS5bits.SI2C3IF = 0;
		I2C3TRN = Data;
		I2C3CONbits.SCLREL = 1;
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while ((I2C3CONbits.SCLREL)&&(I2C3STATbits.S) && MX_I2C_TIMEOUT_X--);
		IFS5bits.SI2C3IF = 0;
		return ((I2C3STATbits.ACKSTAT) || (!I2C3STATbits.S))?1:0;
	#endif
	#if (MX_I2C_CHANNEL_X == 4)
		IFS7bits.SI2C4IF = 0;
		I2C4TRN = Data;
		I2C4CONbits.SCLREL = 1;
		MX_I2C_TIMEOUT_X = 0xFFFF;
		while ((I2C4CONbits.SCLREL)&&(I2C4STATbits.S) && MX_I2C_TIMEOUT_X--);
		IFS7bits.SI2C4IF = 0;
		return ((I2C4STATbits.ACKSTAT) || (!I2C4TATbits.S))?1:0;
	#endif
}

// When Last is true a Nak is sent, otherwise if Last = 0 then Ack is sent
// Not all processors support software Ack/Nak by the Slave,
// for some, such as dsPIC30F, the I2C peripheral hardware sends the Ack
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_RxByte_, (MX_UINT8 Last))
{
	#if (MX_I2C_CHANNEL_X == 1)
		MX_UINT8 Data;
		Data = I2C1RCV;
		#ifdef _SI2C1IF
		IFS1bits.SI2C1IF = 0;
		#ifdef _R_NOT_W
		if ((I2C1STATbits.D_NOT_A)&&(!I2C1STATbits.R_NOT_W))
		#else
		if ((I2C1STATbits.D_A)&&(!I2C1STATbits.R_W))
		#endif
		{
			// writing data to slave
			I2C1CONbits.ACKDT = Last?1:0;
			if (!Last)
			{
				I2C1CONbits.SCLREL = 1;
				MX_I2C_TIMEOUT_X = 0xFFFF;
				while (I2C1CONbits.SCLREL && MX_I2C_TIMEOUT_X--);
			}
		}
		I2C1CONbits.SCLREL = 1;
		#else
		// for dsPIC30F the Ack has already been sent to the Master
		IFS0bits.SI2CIF = 0;
		I2C1CONbits.SCLREL = 1;
		#endif
		return Data;
	#endif
	#if (MX_I2C_CHANNEL_X == 2)
		MX_UINT8 Data;
		Data = I2C2RCV;
		IFS3bits.SI2C2IF = 0;
		#ifdef _R_NOT_W
		if ((I2C2STATbits.D_NOT_A)&&(!I2C2STATbits.R_NOT_W))
		#else
		if ((I2C2STATbits.D_A)&&(!I2C2STATbits.R_W))
		#endif
		{
			// writing data to slave
			I2C2CONbits.ACKDT = Last?1:0;
			if (!Last)
			{
				I2C2CONbits.SCLREL = 1;
				MX_I2C_TIMEOUT_X = 0xFFFF;
				while (I2C2CONbits.SCLREL && MX_I2C_TIMEOUT_X--);
			}
		}
		I2C2CONbits.SCLREL = 1;
		return Data;
	#endif
	#if (MX_I2C_CHANNEL_X == 3)
		MX_UINT8 Data;
		Data = I2C3RCV;
		IFS5bits.SI2C3IF = 0;
		if ((I2C3STATbits.D_A)&&(!I2C3STATbits.R_W))
		{
			// writing data to slave
			I2C3CONbits.ACKDT = Last?1:0;
			if (!Last)
			{
				I2C3CONbits.SCLREL = 1;
				MX_I2C_TIMEOUT_X = 0xFFFF;
				while (I2C3CONbits.SCLREL && MX_I2C_TIMEOUT_X--);
			}
		}
		I2C3CONbits.SCLREL = 1;
		return Data;
	#endif
	#if (MX_I2C_CHANNEL_X == 4)
		MX_UINT8 Data;
		Data = I2C4RCV;
		IFS7bits.SI2C4IF = 0;
		if ((I2C4STATbits.D_A)&&(!I2C4STATbits.R_W))
		{
			// writing data to slave
			I2C4CONbits.ACKDT = Last?1:0;
			if (!Last)
			{
				I2C4CONbits.SCLREL = 1;
				MX_I2C_TIMEOUT_X = 0xFFFF;
				while (I2C4CONbits.SCLREL && MX_I2C_TIMEOUT_X--);
			}
		}
		I2C4CONbits.SCLREL = 1;
		return Data;
	#endif
}

// Returns the status of the I2C Slave
// This is used to poll for a received matching address.
// Bit 0 = 1 Indicates address/data byte available in the buffer to read
// Bit 2 = 1 Indicates a Read, else 0 indicates a Write
// Bit 3 = 1 Indicates Start bit detected
// Bit 4 = 1 Indicates Stop bit detected
// Bit 5 = 1 Indicates that the last byte received (or transmitted?) was data (else address)
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_Status_, (void))
{
	#if (MX_I2C_CHANNEL_X == 1)
		MX_UINT8 Status = 0;
		#ifdef _SI2C1IF
		if (IFS1bits.SI2C1IF) Status |= 1;
		#else
		if (IFS0bits.SI2CIF) Status |= 1;
		#endif
		#ifdef _R_NOT_W
		if (I2C1STATbits.R_NOT_W) Status |= 4;
		#else
		if (I2C1STATbits.R_W) Status |= 4;
		#endif
		if (I2C1STATbits.S) Status |= 8;
		if (I2C1STATbits.P) Status |= 0x10;
		#ifdef _D_NOT_A
		if (I2C1STATbits.D_NOT_A) Status |= 0x20;
		#else
		if (I2C1STATbits.D_A) Status |= 0x20;
		#endif
		return (Status);
	#endif
	#if (MX_I2C_CHANNEL_X == 2)
		MX_UINT8 Status = 0;
		if (IFS3bits.SI2C2IF) Status |= 1;
		#ifdef _R_NOT_W
		if (I2C2STATbits.R_NOT_W) Status |= 4;
		#else
		if (I2C2STATbits.R_W) Status |= 4;
		#endif
		if (I2C2STATbits.S) Status |= 8;
		if (I2C2STATbits.P) Status |= 0x10;
		#ifdef _D_NOT_A
		if (I2C2STATbits.D_NOT_A) Status |= 0x20;
		#else
		if (I2C2STATbits.D_A) Status |= 0x20;
		#endif
		return (Status);
	#endif
	#if (MX_I2C_CHANNEL_X == 3)
		MX_UINT8 Status = 0;
		if (IFS5bits.SI2C3IF) Status |= 1;
		if (I2C3STATbits.R_W) Status |= 4;
		if (I2C3STATbits.S) Status |= 8;
		if (I2C3STATbits.P) Status |= 0x10;
		if (I2C3STATbits.D_A) Status |= 0x20;
		return (Status);
	#endif
	#if (MX_I2C_CHANNEL_X == 4)
		MX_UINT8 Status = 0;
		if (IFS7bits.SI2C4IF) Status |= 1;
		if (I2C4STATbits.R_W) Status |= 4;
		if (I2C4STATbits.S) Status |= 8;
		if (I2C4STATbits.P) Status |= 0x10;
		if (I2C4STATbits.D_A) Status |= 0x20;
		return (Status);
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
