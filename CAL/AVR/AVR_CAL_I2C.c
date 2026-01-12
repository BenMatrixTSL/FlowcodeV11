// CRC: 77485F5F6A861F9125D47827B4DE492656C5431E478E8046055FD2257F64F1F3780D0B864F5D1F680368647E196A8AACF3C76BAD8EEF9A81C5BD6FC7FBC82BBEEAB3A14A2A013993711B8143522C2B6999D3E085021898637E964335588759B61AE65B7489FBA412C10B7462A9E4317969B69B54612A1DB87D304D81521A8F4A2203ED1071DE40DE3BE89FFFBB274E58019EC102BBD8B2CFF5362E8EEF546271E5AD4A7DE3D9775C549D34A0D5AD11F3750C7BFC721322207A75005491EA02BA6C6A859502C0084B61112B2378F6127E5D3A7ED706D09BBA
// REVISION: 2.0
// GUID: 1836954B-9943-4026-B850-E149BA2F53F5
// DATE: 20\01\2023
// DIR: CAL\AVR\AVR_CAL_I2C.c
/*********************************************************************
 *                  Flowcode CAL I2C File
 *
 * File: AVR_CAL_I2C.c
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
 * 230512 | BR | Added XMEGA functionality
 * 030713 | LM | Standard API calls
 * 050913 | LM | Removed unwanted defines
 * 260914 | LM | Changes to Slave macro API
 * 020415 | LM | Added support for Slave
 * 260416 | LM | Added use of TWI Prescaler for bit rate
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

//If software channel is enabled then define bit delay.
#if defined(MX_USI) || (MX_I2C_CHANNEL_X == 0)
  #ifndef MX_I2C_SW_DEL
	#define MX_I2C_SW_BAUD	((500000 / MX_I2C_BAUD_X)-1)

	#if (MX_I2C_SW_BAUD < 1)
		#define MX_I2C_DELAY	delay_us(1);
	#else
		#define MX_I2C_DELAY	delay_us(MX_I2C_SW_BAUD);
	#endif
  #endif
#endif

//If XMEGA then work out the peripheral order
#ifdef MX_XMEGA
	#ifdef TWIC
		#define MX_I2C_CH1_DEF			TWIC
	#endif
	#ifdef TWID
		#define MX_I2C_CH2_DEF			TWID
		#ifdef TWIE
			#define MX_I2C_CH3_DEF		TWIE
		#endif
		#ifdef TWIF
			#define MX_I2C_CH4_DEF		TWIF
		#endif
	#else
		#ifdef TWIE
			#define MX_I2C_CH2_DEF		TWIE
		#endif
	#endif

	#define MX_I2C_START_X				CAL_APPEND(MX_I2C_START_, MX_I2C_NUM)
	#define MX_I2C_ADDR_X				CAL_APPEND(MX_I2C_ADDR_, MX_I2C_NUM)

	MX_UINT8	MX_I2C_ADDR_X = 0;
	MX_UINT8	MX_I2C_START_X = 0;
#endif


CALFUNCTION(void, FC_CAL_I2C_Master_Init_, (void))
{

	#if (MX_I2C_CHANNEL_X == 0)															//Use Master I2C Software
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Configure SDA as Input
		FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Configure SCL as Input
	#else
		#ifndef MX_MI2C
			#error "This chip does not have Master I2C capability"
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 1)													//Use Master I2C Hardware 1
		#ifndef MX_I2C_1
			#error "This chip does not have I2C1 capability"
		#else
			#ifndef MX_XMEGA
			  #ifdef MX_USI
				FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Configure SDA as Input
				FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Configure SCL as Input
				USICR = (1 << USIWM1);
			  #else
				#if ((((MX_CLK_SPEED / MX_I2C_BAUD_X)-16)/2) < 255)
					// Prescaler 1
				TWBR = (((MX_CLK_SPEED / MX_I2C_BAUD_X)-16)/2);
				TWSR = 0;
				#elif ((((MX_CLK_SPEED / MX_I2C_BAUD_X)-16)/8) < 255)
					// Prescaler 4
					TWBR = (((MX_CLK_SPEED / MX_I2C_BAUD_X)-16)/8);
					TWSR = 1;
				#elif ((((MX_CLK_SPEED / MX_I2C_BAUD_X)-16)/32) < 255)
					// Prescaler 16
					TWBR = (((MX_CLK_SPEED / MX_I2C_BAUD_X)-16)/32);
					TWSR = 2;
				#else
					// Prescaler 64
					TWBR = (((MX_CLK_SPEED / MX_I2C_BAUD_X)-16)/128);
					TWSR = 3;
				#endif
			  #endif
			#else
				MX_I2C_CH1_DEF.MASTER.BAUD = MX_I2C_BAUD_X;
				MX_I2C_CH1_DEF.MASTER.CTRLA = (1 << TWI_MASTER_ENABLE_bp);
				MX_I2C_CH1_DEF.MASTER.STATUS = 0x01;							//Idle State
				//#error "ATXMEGA devices are not supported in I2C hardware mode"
			#endif
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)													//Use Master I2C Hardware 2
		#ifndef MX_I2C_2
			#error "This chip does not have I2C2 capability"
		#else
			#ifndef MX_XMEGA
			#else
				MX_I2C_CH2_DEF.MASTER.BAUD = MX_I2C_BAUD_X;
				MX_I2C_CH2_DEF.MASTER.CTRLA = (1 << TWI_MASTER_ENABLE_bp);
				MX_I2C_CH2_DEF.MASTER.STATUS = 0x01;							//Idle State
				//#error "ATXMEGA devices are not supported in I2C hardware mode"
			#endif
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 3)													//Use Master I2C Hardware 3
		#ifndef MX_I2C_3
			#error "This chip does not have I2C3 capability"
		#else
			#ifndef MX_XMEGA
			#else
				MX_I2C_CH3_DEF.MASTER.BAUD = MX_I2C_BAUD_X;
				MX_I2C_CH3_DEF.MASTER.CTRLA = (1 << TWI_MASTER_ENABLE_bp);
				MX_I2C_CH3_DEF.MASTER.STATUS = 0x01;							//Idle State
				//#error "ATXMEGA devices are not supported in I2C hardware mode"
			#endif
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 4)													//Use Master I2C Hardware 4
		#ifndef MX_I2C_4
			#error "This chip does not have I2C4 capability"
		#else
			#ifndef MX_XMEGA
			#else
				MX_I2C_CH4_DEF.MASTER.BAUD = MX_I2C_BAUD_X;
				MX_I2C_CH4_DEF.MASTER.CTRLA = (1 << TWI_MASTER_ENABLE_bp);
				MX_I2C_CH4_DEF.MASTER.STATUS = 0x01;							//Idle State
				//#error "ATXMEGA devices are not supported in I2C hardware mode"
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

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1
		#ifndef MX_XMEGA
		  #ifdef MX_USI
			USICR = (0 << USIWM1);
		  #else
			TWSR = 0;
		  #endif
		#else
			MX_I2C_CH1_DEF.MASTER.CTRLA = (0 << TWI_MASTER_ENABLE_bp);
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)												//Use Master I2C Hardware 2
		#ifndef MX_XMEGA
		#else
			MX_I2C_CH2_DEF.MASTER.CTRLA = (0 << TWI_MASTER_ENABLE_bp);
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 3)												//Use Master I2C Hardware 3
		#ifndef MX_XMEGA
		#else
			MX_I2C_CH3_DEF.MASTER.CTRLA = (0 << TWI_MASTER_ENABLE_bp);
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 4)												//Use Master I2C Hardware 4
		#ifndef MX_XMEGA
		#else
			MX_I2C_CH4_DEF.MASTER.CTRLA = (0 << TWI_MASTER_ENABLE_bp);
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

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1
		#ifndef MX_XMEGA
		  #ifdef MX_USI
			USIDR = 0xff;
			MX_I2C_DELAY;
			FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Make Sure SCL is Set
			MX_I2C_DELAY;
			USIDR = 0x00;
			MX_I2C_DELAY;
			FC_CAL_Bit_Low_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Make Sure SCL is Clear
			MX_I2C_DELAY;
			USISR = 0x80;
		  #else
			TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);	//Clear TWI interrupt and initiate start condition
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while((TWCR & (1 << TWINT)) == 0 && MX_I2C_TIMEOUT_X--);					//Wait for confirmation
		  #endif
		#else
			MX_I2C_START_X = 1;
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)
		MX_I2C_START_X = 1;
	#endif

	#if (MX_I2C_CHANNEL_X == 3)
		MX_I2C_START_X = 1;
	#endif

	#if (MX_I2C_CHANNEL_X == 4)
		MX_I2C_START_X = 1;
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
		//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR
	#endif

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1
		#ifndef MX_XMEGA
		  #ifdef MX_USI
			USIDR = 0xff;
			MX_I2C_DELAY;
			FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Make Sure SCL is Set
			MX_I2C_DELAY;
			USIDR = 0x00;
			MX_I2C_DELAY;
			FC_CAL_Bit_Low_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Make Sure SCL is Clear
			MX_I2C_DELAY;
			USISR = 0x80;
		  #else
			TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);	//Clear TWI interrupt and initiate start condition
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while((TWCR & (1 << TWINT)) == 0 && MX_I2C_TIMEOUT_X--);					//Wait for confirmation
		  #endif
		#else
			MX_I2C_START_X = 1;
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)												//Use Master I2C Hardware 2
		MX_I2C_START_X = 1;
	#endif

	#if (MX_I2C_CHANNEL_X == 3)												//Use Master I2C Hardware 3
		MX_I2C_START_X = 1;
	#endif

	#if (MX_I2C_CHANNEL_X == 4)												//Use Master I2C Hardware 4
		MX_I2C_START_X = 1;
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
		#ifndef MX_XMEGA
		  #ifdef MX_USI
			USIDR = 0x00;
			MX_I2C_DELAY;
			FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Make Sure SCL is Set
			MX_I2C_DELAY;
			USIDR = 0xff;
		  #else
			TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);					//Clear TWI interrupt and initiate stop condition
		  #endif
		#else
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)												//Use Master I2C Hardware 2
	#endif

	#if (MX_I2C_CHANNEL_X == 3)												//Use Master I2C Hardware 3
	#endif

	#if (MX_I2C_CHANNEL_X == 4)												//Use Master I2C Hardware 4
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
			//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR
		}
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);			//Set SDA High
		MX_I2C_DELAY;
		FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);			//Set SCL High
		MX_I2C_DELAY;
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);
		if (FC_CAL_Bit_In(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X))								//Get the Status Bit
			local_ack = 1;
		//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR
		FC_CAL_Bit_Low_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);			//Set SCL Low
		//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR
		return (local_ack);													//0 = Ack received : 1 = Ack not received
	#endif

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1
		#ifndef MX_XMEGA
		  #ifdef MX_USI
			unsigned char i;
			USIDR = Data;
			for (i = 0; i < 8; i++)
			{
				MX_I2C_DELAY;
				USICR = (1 << USIWM1) | (1 << USITC);
				MX_I2C_DELAY;
				USICR = (1 << USIWM1) | (1 << USITC) | (1 << USICLK);
			}
			USIDR = 0xff;
			MX_I2C_DELAY;
			USICR = (1 << USIWM1) | (1 << USITC);
			MX_I2C_DELAY;
			i = 0;
			FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);	//Set SDA High
			if (FC_CAL_Bit_In(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X))						//Get the Status Bit
				i = 1;
			FC_CAL_Bit_High_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Configure SDA as Output
			USICR = (1 << USIWM1) | (1 << USITC);
			return (i);
		  #else
			TWDR = Data;
			delay_us(10);							//Delay here to overcome potential TWI AVR hardware bug
			TWCR = (1 << TWINT) | (1 << TWEN);
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while((TWCR & (1 << TWINT)) == 0 && MX_I2C_TIMEOUT_X--);
			if(((TWSR & 0xf8) == 0x18) || ((TWSR & 0xf8) == 0x28) || ((TWSR & 0xf8) == 0x40) || ((TWSR & 0xf8) == 0x50))
				return(0);
			else
				return(1);
		  #endif
		#else
			if (MX_I2C_START_X)
				MX_I2C_CH1_DEF.MASTER.ADDR = Data;
			else
				MX_I2C_CH1_DEF.MASTER.DATA = Data;

			MX_I2C_START_X = 0;
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(!(MX_I2C_CH1_DEF.MASTER.STATUS & TWI_MASTER_WIF_bm) && MX_I2C_TIMEOUT_X--);
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)												//Use Master I2C Hardware 2
		#ifndef MX_XMEGA
		#else
			if (MX_I2C_START_X)
				MX_I2C_CH2_DEF.MASTER.ADDR = Data;
			else
				MX_I2C_CH2_DEF.MASTER.DATA = Data;

			MX_I2C_START_X = 0;
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(!(MX_I2C_CH2_DEF.MASTER.STATUS & TWI_MASTER_WIF_bm) && MX_I2C_TIMEOUT_X--);
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 3)												//Use Master I2C Hardware 3
		#ifndef MX_XMEGA
		#else
			if (MX_I2C_START_X)
				MX_I2C_CH3_DEF.MASTER.ADDR = Data;
			else
				MX_I2C_CH3_DEF.MASTER.DATA = Data;

			MX_I2C_START_X = 0;
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(!(MX_I2C_CH3_DEF.MASTER.STATUS & TWI_MASTER_WIF_bm) && MX_I2C_TIMEOUT_X--);
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 4)												//Use Master I2C Hardware 4
		#ifndef MX_XMEGA
		#else
			if (MX_I2C_START_X)
				MX_I2C_CH4_DEF.MASTER.ADDR = Data;
			else
				MX_I2C_CH4_DEF.MASTER.DATA = Data;

			MX_I2C_START_X = 0;
			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(!(MX_I2C_CH4_DEF.MASTER.STATUS & TWI_MASTER_WIF_bm) && MX_I2C_TIMEOUT_X--);
		#endif
	#endif

  return 0;
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
		//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR
		return (Data);
	#endif

	#if (MX_I2C_CHANNEL_X == 1)						//Use Master I2C Hardware 1
		#ifndef MX_XMEGA
		  #ifdef MX_USI
			unsigned char i, data;
			USIDR = 0xff;
			for (i = 0; i < 8; i++)
			{
				MX_I2C_DELAY;
				USICR = (1 << USIWM1) | (1 << USITC);
				MX_I2C_DELAY;
				USICR = (1 << USIWM1) | (1 << USITC) | (1 << USICLK);
			}
			data = USIDR;
			if(Last)
				USIDR = 0xff;
			else
				USIDR = 0x00;
			MX_I2C_DELAY;
			USICR = (1 << USIWM1) | (1 << USITC);
			MX_I2C_DELAY;
			USICR = (1 << USIWM1) | (1 << USITC);
			return(data);
		  #else
			if (Last)
				TWCR = (1 << TWINT) | (1 << TWEN);					//Read data with Nack
			else
				TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);	//Read data with Ack

			MX_I2C_TIMEOUT_X = 0xFFFF;
			while((TWCR & (1 << TWINT)) == 0 && MX_I2C_TIMEOUT_X--);
			return(TWDR);
		  #endif
		#else
			if (Last)
				set_bit (MX_I2C_CH1_DEF.MASTER.CTRLC, TWI_MASTER_ACKACT_bp);	//Read data with Nack
			else
				clear_bit (MX_I2C_CH1_DEF.MASTER.CTRLC, TWI_MASTER_ACKACT_bp);	//Read data with Ack

			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(!(MX_I2C_CH1_DEF.MASTER.STATUS & TWI_MASTER_RIF_bm) && MX_I2C_TIMEOUT_X--);
			return MX_I2C_CH1_DEF.MASTER.DATA;
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)						//Use Master I2C Hardware 2
		#ifndef MX_XMEGA
		#else
			if (Last)
				set_bit (MX_I2C_CH2_DEF.MASTER.CTRLC, TWI_MASTER_ACKACT_bp);	//Read data with Nack
			else
				clear_bit (MX_I2C_CH2_DEF.MASTER.CTRLC, TWI_MASTER_ACKACT_bp);	//Read data with Ack

			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(!(MX_I2C_CH2_DEF.MASTER.STATUS & TWI_MASTER_RIF_bm) && MX_I2C_TIMEOUT_X--);
			return MX_I2C_CH2_DEF.MASTER.DATA;
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 3)						//Use Master I2C Hardware 3
		#ifndef MX_XMEGA
		#else
			if (Last)
				set_bit (MX_I2C_CH3_DEF.MASTER.CTRLC, TWI_MASTER_ACKACT_bp);	//Read data with Nack
			else
				clear_bit (MX_I2C_CH3_DEF.MASTER.CTRLC, TWI_MASTER_ACKACT_bp);	//Read data with Ack

			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(!(MX_I2C_CH3_DEF.MASTER.STATUS & TWI_MASTER_RIF_bm) && MX_I2C_TIMEOUT_X--);
			return MX_I2C_CH3_DEF.MASTER.DATA;
		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 4)						//Use Master I2C Hardware 4
		#ifndef MX_XMEGA
		#else
			if (Last)
				set_bit (MX_I2C_CH4_DEF.MASTER.CTRLC, TWI_MASTER_ACKACT_bp);	//Read data with Nack
			else
				clear_bit (MX_I2C_CH4_DEF.MASTER.CTRLC, TWI_MASTER_ACKACT_bp);	//Read data with Ack

			MX_I2C_TIMEOUT_X = 0xFFFF;
			while(!(MX_I2C_CH4_DEF.MASTER.STATUS & TWI_MASTER_RIF_bm) && MX_I2C_TIMEOUT_X--);
			return MX_I2C_CH4_DEF.MASTER.DATA;
		#endif
	#endif

  return 0;
}



/*********************************************
Slave_Init()
	MX_UINT8 Address
		Only supports 7 bit addressing, bits 7..1
		LSB is ignored
	MX_UINT8 Mask
		For devices that support a mask
		A bit set in the mask will cause a compare
		Hence for an exact address match,
		mask should be set to 0xFE (or 0xFF)

Detailed explanation:
	AVR:
	TWAMR – TWI (Slave) Address Mask Register
	Each of the bits in TWAMR can mask (disable)
	the corresponding address bits in the TWAR.
	If the mask bit is set to one then the
	address match logic ignores the compare
	between the incoming address bit
	and the corresponding bit in TWAR
	(i.e. a set bit forces a match for that bit)

	PIC:
	A zero bit in the SSPMSK register has the
	effect of making the corresponding bit
	of the received address a “don’t care”

	The I2C Slave API is based on the PIC,
	hence for AVR we invert the Mask internally

Control registers for info:
	Address/Data Shift Register (TWDR)
	Bit Rate Register (TWBR)
	Address Register (TWAR)
	Status Register (TWSR)
	Control Register (TWCR)
*********************************************/
CALFUNCTION(void, FC_CAL_I2C_Slave_Init_, (MX_UINT8 Address, MX_UINT8 Mask))
{
	#if (MX_I2C_CHANNEL_X == 1)
		#ifndef MX_I2C_1
			#error "This chip does not have hardware I2C capability"
		#else
			#ifndef MX_XMEGA
				#ifdef MX_USI

				#else
					TWBR = (((MX_CLK_SPEED / MX_I2C_BAUD_X)-16)/2);
					// load the slave address, clear TWGCE
					TWAR = Address & 0xFE;
					#ifdef TWAMR
						// load the Mask, if the device has one
						TWAMR = ~Mask;
					#endif
					// enable the TWI, set TWEA to enable the ack of the slave address
					TWCR = (1<<TWEA)|(1<<TWEN);
				#endif
			#else
				#warning "Slave I2C not yet supported on ATXMEGA devices"
			#endif
		#endif
	#endif
}

// Returns I2C status byte
// Bit 0 = 1 Indicates address/data byte available in the buffer to read
// Bit 5 = 1 Indicates that the last byte received or transmitted was data (else address)
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_Status_, (void))
{
	MX_UINT8 status = 0;
	#if (MX_I2C_CHANNEL_X == 1)
		#ifndef MX_I2C_1
			#error "This chip does not have hardware I2C capability"
		#else
			#ifndef MX_XMEGA
				#ifdef MX_USI

				#else
					if (TWCR & (1<<TWINT))
					{
						switch (TWSR & 0xF8)
						{
							//  Status Codes for Slave Transmitter Mode (Address)
							case 0xA8:	// Own SLA+R has been received; ACK has been returned
							case 0xB0:	// Arbitration lost in SLA+R/W as Master; own SLA+R has been received; ACK has been returned
								status = 1;
								break;
							//  Status Codes for Slave Receiver Mode (Address)
							case 0x60:	// Own SLA+W has been received; ACK has been returned
							case 0x68:	// Arbitration lost in SLA+R/W as Master; own SLA+W has been received; ACK has been returned
							case 0x70:	// General call address has been received; ACK has been returned
							case 0x78:	// Arbitration lost in SLA+R/W as Master; General call address has been received; ACK has been returned
								status = 1;
								break;
							//  Status Codes for Slave Receiver Mode Data Byte
							case 0x80:	// Previously  addressed  with  own SLA+W; data has been received; ACK has been returned
							case 0x88:	// Previously  addressed  with  own SLA+W; data has been received; NOT ACK has been returned
							case 0x90:	// Previously addressed with general  call;  data  has  been  received; ACK has been returned
							case 0x98:	// Previously addressed with general call; data has been received; NOT ACK has been returned
								status = 0x21;
								break;
							//  Status Codes for Slave Transmitter Mode Data Byte
							case 0xB8:	// Data byte in TWDR has been transmitted; ACK has been received
							case 0xC0:	// Data byte in TWDR has been transmitted; NOT ACK has been received
							case 0xC8:	// Last data byte in TWDR has been transmitted  (TWEA  =  “0”);  ACK has been received
								status = 0x21;
								break;
							case 0xF8:
							case 0:
							case 0xA0:	// A  STOP  condition  or  repeated START condition has been received while still addressed as Slave
								TWCR = (1<<TWEA)|(1<<TWEN)|(1<<TWINT);
								break;
							default:
								break;
						}
					}
				#endif
			#else
				//#warning "Slave I2C not yet supported on ATXMEGA devices"
			#endif
		#endif
	#endif
	return status;
}

// Disables the I2C peripheral
CALFUNCTION(void, FC_CAL_I2C_Slave_Uninit_, (void))
{
	#if (MX_I2C_CHANNEL_X == 1)
		#ifndef MX_I2C_1
			#error "This chip does not have hardware I2C capability"
		#else
			#ifndef MX_XMEGA
				#ifdef MX_USI

				#else
					TWCR = 0;
				#endif
			#else
				//#warning "Slave I2C not yet supported on ATXMEGA devices"
			#endif
		#endif
	#endif
}

// Loads the Data byte into the shift buffer and releases SCL ready for sending
// Returns Master Ack/Nak (0=Ack=More, 1=Nak=Last)
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_TxByte_, (MX_UINT8 Data))
{
	MX_UINT8 Result = 1;	// default to Nak

	#if (MX_I2C_CHANNEL_X == 1)
		#ifndef MX_I2C_1
			#error "This chip does not have hardware I2C capability"
		#else
			#ifndef MX_XMEGA
				#ifdef MX_USI

				#else
					TWDR = Data;		// load the data
					delay_us(10);
					TWCR |= 1<<TWINT;	// kick TWINT
					MX_I2C_TIMEOUT_X = 0xFFFF;
					while (!(TWCR & (1<<TWINT)) && MX_I2C_TIMEOUT_X--);
					switch (TWSR & 0xF8)
					{
						case 0xA8:	// Own SLA+R has been received; ACK has been returned
						case 0xB0:	// Arbitration lost in SLA+R/W as Master; own SLA+R has been received; ACK has been returned
						case 0xB8:	// Data byte in TWDR has been transmitted; ACK has been received
						case 0xC8:	// Last data byte in TWDR has been transmitted (TWEA  =  “0”); ACK has been received
							Result = 0;
							break;
						case 0xC0:	// Data byte in TWDR has been transmitted; NOT ACK has been received
						default:
							break;
					}
					TWCR |= 1<<TWINT;	// kick TWINT
				#endif
			#else
				//#warning "Slave I2C not yet supported on ATXMEGA devices"
			#endif
		#endif
	#endif

	return Result;
}

// Returns the byte from the shift buffer
// and sends Ack or Nak (0=Ack=More, 1=Nak=Last)
// nb. First check FC_CAL_I2C_Slave_Status() & 1
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_RxByte_, (MX_UINT8 Last))
{
	MX_UINT8 Data = 0;
	#if (MX_I2C_CHANNEL_X == 1)
		#ifndef MX_I2C_1
			#error "This chip does not have hardware I2C capability"
		#else
			#ifndef MX_XMEGA
				#ifdef MX_USI

				#else
					Data = TWDR;
					if ((MX_UINT8)(TWSR & 0xF8) < 0xA0)
					{
						// Slave Receiver Mode
						if (Last)
						{
							// Send Nak
							TWCR = (1<<TWINT)|(1<<TWEN);
						}
						else
						{
							// Send Ack
							TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
						}
					}
				#endif
			#else
				//#warning "Slave I2C not yet supported on ATXMEGA devices"
			#endif
		#endif
	#endif
	return Data;			// return the received data
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
