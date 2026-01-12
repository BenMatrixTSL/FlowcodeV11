// CRC: AE5753800093D2B889297C6B876B6A21749C10AFA09C3FCE4A5F65B0FF76818F780D0B864F5D1F680368647E196A8AAC5FC36BB60D5779D524F8CD3FDC3D2E447800D711032B6231711B8143522C2B698938310A325BEFED72B83EB4C9B635C4EBFE7695C1292471455840074B8BB17683626EA46999313724ECE28FC503A0EF378139E38E93943CDFB5609686129188D93C0EA4C39EEE78D18C38503B0CA1EEAF34E37E2D836EB1549D34A0D5AD11F3D2C301AADFA65E4FCFEAACDAD2150962A0458B232D3A80B168F76F09E69EFC60247D7D36043FD9DE
// REVISION: 3.0
// GUID: AF982365-FC17-4740-8275-4928400D4BF8
// DATE: 29\09\2023
// DIR: CAL\ARM\ARM_CAL_I2C.c
/*********************************************************************
 *                  Flowcode CAL I2C File
 *
 * File: ARM_CAL_I2C.c
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
 * 050312 | BR | Updated to v5.1 CAL Schema
 * 030713 | LM | Standard API calls
 * 260914 | LM | Changes to Slave macro API
 * 220118 | LM | Addition of transaction functions
 *
 */




//When using hardware I2C channels override port and pin conns with FCD conn definitions
#ifdef MX_I2C_REF1
	#if MX_I2C_CHANNEL_1 > 0
		#undef MX_I2C_SDA_PIN_1
		#undef MX_I2C_SDA_PORT_1
		#undef MX_I2C_SDA_TRIS_1
		#undef MX_I2C_SCL_PIN_1
		#undef MX_I2C_SCL_PORT_1
		#undef MX_I2C_SCL_TRIS_1
	#endif
	#if MX_I2C_CHANNEL_1 == 1
		#define MX_I2C_SDA_PIN_1		MX_I2C_1_SDA_PIN
		#define MX_I2C_SDA_PORT_1		MX_I2C_1_SDA_PORT
		#define MX_I2C_SDA_TRIS_1		MX_I2C_1_SDA_TRIS
		#define MX_I2C_SCL_PIN_1		MX_I2C_1_SCL_PIN
		#define MX_I2C_SCL_PORT_1		MX_I2C_1_SCL_PORT
		#define MX_I2C_SCL_TRIS_1		MX_I2C_1_SCL_TRIS
	#endif
	#if MX_I2C_CHANNEL_1 == 2
		#define MX_I2C_SDA_PIN_1		MX_I2C_2_SDA_PIN
		#define MX_I2C_SDA_PORT_1		MX_I2C_2_SDA_PORT
		#define MX_I2C_SDA_TRIS_1		MX_I2C_2_SDA_TRIS
		#define MX_I2C_SCL_PIN_1		MX_I2C_2_SCL_PIN
		#define MX_I2C_SCL_PORT_1		MX_I2C_2_SCL_PORT
		#define MX_I2C_SCL_TRIS_1		MX_I2C_2_SCL_TRIS
	#endif
	#if MX_I2C_CHANNEL_1 == 3
		#define MX_I2C_SDA_PIN_1		MX_I2C_3_SDA_PIN
		#define MX_I2C_SDA_PORT_1		MX_I2C_3_SDA_PORT
		#define MX_I2C_SDA_TRIS_1		MX_I2C_3_SDA_TRIS
		#define MX_I2C_SCL_PIN_1		MX_I2C_3_SCL_PIN
		#define MX_I2C_SCL_PORT_1		MX_I2C_3_SCL_PORT
		#define MX_I2C_SCL_TRIS_1		MX_I2C_3_SCL_TRIS
	#endif
	#if MX_I2C_CHANNEL_1 == 4
		#define MX_I2C_SDA_PIN_1		MX_I2C_4_SDA_PIN
		#define MX_I2C_SDA_PORT_1		MX_I2C_4_SDA_PORT
		#define MX_I2C_SDA_TRIS_1		MX_I2C_4_SDA_TRIS
		#define MX_I2C_SCL_PIN_1		MX_I2C_4_SCL_PIN
		#define MX_I2C_SCL_PORT_1		MX_I2C_4_SCL_PORT
		#define MX_I2C_SCL_TRIS_1		MX_I2C_4_SCL_TRIS
	#endif
#endif
#ifdef MX_I2C_REF2
	#if MX_I2C_CHANNEL_2 > 0
		#undef MX_I2C_SDA_PIN_2
		#undef MX_I2C_SDA_PORT_2
		#undef MX_I2C_SDA_TRIS_2
		#undef MX_I2C_SCL_PIN_2
		#undef MX_I2C_SCL_PORT_2
		#undef MX_I2C_SCL_TRIS_2
	#endif
	#if MX_I2C_CHANNEL_2 == 1
		#define MX_I2C_SDA_PIN_2		MX_I2C_1_SDA_PIN
		#define MX_I2C_SDA_PORT_2		MX_I2C_1_SDA_PORT
		#define MX_I2C_SDA_TRIS_2		MX_I2C_1_SDA_TRIS
		#define MX_I2C_SCL_PIN_2		MX_I2C_1_SCL_PIN
		#define MX_I2C_SCL_PORT_2		MX_I2C_1_SCL_PORT
		#define MX_I2C_SCL_TRIS_2		MX_I2C_1_SCL_TRIS
	#endif
	#if MX_I2C_CHANNEL_2 == 2
		#define MX_I2C_SDA_PIN_2		MX_I2C_2_SDA_PIN
		#define MX_I2C_SDA_PORT_2		MX_I2C_2_SDA_PORT
		#define MX_I2C_SDA_TRIS_2		MX_I2C_2_SDA_TRIS
		#define MX_I2C_SCL_PIN_2		MX_I2C_2_SCL_PIN
		#define MX_I2C_SCL_PORT_2		MX_I2C_2_SCL_PORT
		#define MX_I2C_SCL_TRIS_2		MX_I2C_2_SCL_TRIS
	#endif
	#if MX_I2C_CHANNEL_2 == 3
		#define MX_I2C_SDA_PIN_2		MX_I2C_3_SDA_PIN
		#define MX_I2C_SDA_PORT_2		MX_I2C_3_SDA_PORT
		#define MX_I2C_SDA_TRIS_2		MX_I2C_3_SDA_TRIS
		#define MX_I2C_SCL_PIN_2		MX_I2C_3_SCL_PIN
		#define MX_I2C_SCL_PORT_2		MX_I2C_3_SCL_PORT
		#define MX_I2C_SCL_TRIS_2		MX_I2C_3_SCL_TRIS
	#endif
	#if MX_I2C_CHANNEL_2 == 4
		#define MX_I2C_SDA_PIN_2		MX_I2C_4_SDA_PIN
		#define MX_I2C_SDA_PORT_2		MX_I2C_4_SDA_PORT
		#define MX_I2C_SDA_TRIS_2		MX_I2C_4_SDA_TRIS
		#define MX_I2C_SCL_PIN_2		MX_I2C_4_SCL_PIN
		#define MX_I2C_SCL_PORT_2		MX_I2C_4_SCL_PORT
		#define MX_I2C_SCL_TRIS_2		MX_I2C_4_SCL_TRIS
	#endif
#endif
#ifdef MX_I2C_REF3
	#if MX_I2C_CHANNEL_3 > 0
		#undef MX_I2C_SDA_PIN_3
		#undef MX_I2C_SDA_PORT_3
		#undef MX_I2C_SDA_TRIS_3
		#undef MX_I2C_SCL_PIN_3
		#undef MX_I2C_SCL_PORT_3
		#undef MX_I2C_SCL_TRIS_3
	#endif
	#if MX_I2C_CHANNEL_3 == 1
		#define MX_I2C_SDA_PIN_3		MX_I2C_1_SDA_PIN
		#define MX_I2C_SDA_PORT_3		MX_I2C_1_SDA_PORT
		#define MX_I2C_SDA_TRIS_3		MX_I2C_1_SDA_TRIS
		#define MX_I2C_SCL_PIN_3		MX_I2C_1_SCL_PIN
		#define MX_I2C_SCL_PORT_3		MX_I2C_1_SCL_PORT
		#define MX_I2C_SCL_TRIS_3		MX_I2C_1_SCL_TRIS
	#endif
	#if MX_I2C_CHANNEL_3 == 2
		#define MX_I2C_SDA_PIN_3		MX_I2C_2_SDA_PIN
		#define MX_I2C_SDA_PORT_3		MX_I2C_2_SDA_PORT
		#define MX_I2C_SDA_TRIS_3		MX_I2C_2_SDA_TRIS
		#define MX_I2C_SCL_PIN_3		MX_I2C_2_SCL_PIN
		#define MX_I2C_SCL_PORT_3		MX_I2C_2_SCL_PORT
		#define MX_I2C_SCL_TRIS_3		MX_I2C_2_SCL_TRIS
	#endif
	#if MX_I2C_CHANNEL_3 == 3
		#define MX_I2C_SDA_PIN_3		MX_I2C_3_SDA_PIN
		#define MX_I2C_SDA_PORT_3		MX_I2C_3_SDA_PORT
		#define MX_I2C_SDA_TRIS_3		MX_I2C_3_SDA_TRIS
		#define MX_I2C_SCL_PIN_3		MX_I2C_3_SCL_PIN
		#define MX_I2C_SCL_PORT_3		MX_I2C_3_SCL_PORT
		#define MX_I2C_SCL_TRIS_3		MX_I2C_3_SCL_TRIS
	#endif
	#if MX_I2C_CHANNEL_3 == 4
		#define MX_I2C_SDA_PIN_3		MX_I2C_4_SDA_PIN
		#define MX_I2C_SDA_PORT_3		MX_I2C_4_SDA_PORT
		#define MX_I2C_SDA_TRIS_3		MX_I2C_4_SDA_TRIS
		#define MX_I2C_SCL_PIN_3		MX_I2C_4_SCL_PIN
		#define MX_I2C_SCL_PORT_3		MX_I2C_4_SCL_PORT
		#define MX_I2C_SCL_TRIS_3		MX_I2C_4_SCL_TRIS
	#endif
#endif
#ifdef MX_I2C_REF4
	#if MX_I2C_CHANNEL_4 > 0
		#undef MX_I2C_SDA_PIN_4
		#undef MX_I2C_SDA_PORT_4
		#undef MX_I2C_SDA_TRIS_4
		#undef MX_I2C_SCL_PIN_4
		#undef MX_I2C_SCL_PORT_4
		#undef MX_I2C_SCL_TRIS_4
	#endif
	#if MX_I2C_CHANNEL_4 == 1
		#define MX_I2C_SDA_PIN_4		MX_I2C_1_SDA_PIN
		#define MX_I2C_SDA_PORT_4		MX_I2C_1_SDA_PORT
		#define MX_I2C_SDA_TRIS_4		MX_I2C_1_SDA_TRIS
		#define MX_I2C_SCL_PIN_4		MX_I2C_1_SCL_PIN
		#define MX_I2C_SCL_PORT_4		MX_I2C_1_SCL_PORT
		#define MX_I2C_SCL_TRIS_4		MX_I2C_1_SCL_TRIS
	#endif
	#if MX_I2C_CHANNEL_4 == 2
		#define MX_I2C_SDA_PIN_4		MX_I2C_2_SDA_PIN
		#define MX_I2C_SDA_PORT_4		MX_I2C_2_SDA_PORT
		#define MX_I2C_SDA_TRIS_4		MX_I2C_2_SDA_TRIS
		#define MX_I2C_SCL_PIN_4		MX_I2C_2_SCL_PIN
		#define MX_I2C_SCL_PORT_4		MX_I2C_2_SCL_PORT
		#define MX_I2C_SCL_TRIS_4		MX_I2C_2_SCL_TRIS
	#endif
	#if MX_I2C_CHANNEL_4 == 3
		#define MX_I2C_SDA_PIN_4		MX_I2C_3_SDA_PIN
		#define MX_I2C_SDA_PORT_4		MX_I2C_3_SDA_PORT
		#define MX_I2C_SDA_TRIS_4		MX_I2C_3_SDA_TRIS
		#define MX_I2C_SCL_PIN_4		MX_I2C_3_SCL_PIN
		#define MX_I2C_SCL_PORT_4		MX_I2C_3_SCL_PORT
		#define MX_I2C_SCL_TRIS_4		MX_I2C_3_SCL_TRIS
	#endif
	#if MX_I2C_CHANNEL_4 == 4
		#define MX_I2C_SDA_PIN_4		MX_I2C_4_SDA_PIN
		#define MX_I2C_SDA_PORT_4		MX_I2C_4_SDA_PORT
		#define MX_I2C_SDA_TRIS_4		MX_I2C_4_SDA_TRIS
		#define MX_I2C_SCL_PIN_4		MX_I2C_4_SCL_PIN
		#define MX_I2C_SCL_PORT_4		MX_I2C_4_SCL_PORT
		#define MX_I2C_SCL_TRIS_4		MX_I2C_4_SCL_TRIS
	#endif
#endif

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


//If software channel is enabled then define bit delay.
#if (MX_I2C_CHANNEL_X == 0)
  #ifndef MX_I2C_SW_DEL
	#define MX_I2C_SW_BAUD	((500000 / MX_I2C_BAUD_X)-1)

	#if (MX_I2C_SW_BAUD < 1)
		#define MX_I2C_DELAY	delay_us(1);
	#else
		#define MX_I2C_DELAY	delay_us(MX_I2C_SW_BAUD);
	#endif

  #endif

	//I2C Timeout - Avoids any blocking delays
	#define MX_I2C_TIMEOUT_X		CAL_APPEND(MX_I2C_TIMEOUT_, MX_I2C_NUM)
	MX_UINT16 MX_I2C_TIMEOUT_X;

#endif


CALFUNCTION(void, FC_CAL_I2C_Master_Init_, (void))
{

	#if (MX_I2C_CHANNEL_X == 0)															//Use Master I2C Software
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Configure SDA as Input
		FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Configure SCL as Input
	#endif

	#if (MX_I2C_CHANNEL_X == 1)															//Use Master I2C Hardware 1
		#error "ARM does not support I2C in this mode - SW implementation only"
	#endif

	#if (MX_I2C_CHANNEL_X == 2)															//Use Master I2C Hardware 2
		#error "ARM does not support I2C in this mode - SW implementation only"
	#endif

	#if (MX_I2C_CHANNEL_X == 3)															//Use Master I2C Hardware 3
		#error "ARM does not support I2C in this mode - SW implementation only"
	#endif

	#if (MX_I2C_CHANNEL_X == 4)															//Use Master I2C Hardware 4
		#error "ARM does not support I2C in this mode - SW implementation only"
	#endif
}

CALFUNCTION(void, FC_CAL_I2C_Master_Uninit_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)															//Use Master I2C Software
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Configure SDA as Input
		FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Configure SCL as Input
	#endif

	#if (MX_I2C_CHANNEL_X == 1)															//Use Master I2C Hardware 1
		//ARM does not support I2C in this mode - SW only
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

	#if (MX_I2C_CHANNEL_X == 1)															//Use Master I2C Hardware 1
		//ARM does not support I2C in this mode - SW only
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

	#if (MX_I2C_CHANNEL_X == 1)															//Use Master I2C Hardware 1
		//ARM does not support I2C in this mode - SW only
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

	#if (MX_I2C_CHANNEL_X == 1)															//Use Master I2C Hardware 1
		//ARM does not support I2C in this mode - SW only
	#endif

	#if (MX_I2C_STOPDEL_X == 1)
  	  delay_ms(10);		//Wait before reusing the I2C BUS -  avoids lockup problem exibited on some PICs
	#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_I2C_Master_TxByte_, (MX_UINT8 Data))
{
	#if (MX_I2C_CHANNEL_X == 0)															//Use Master I2C Software
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
		if (FC_CAL_Bit_In(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X))		//Get the Status Bit
			local_ack = 1;
		//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR
		FC_CAL_Bit_Low_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);			//Set SCL Low
		//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR
		return (local_ack);													//0 = Ack received : 1 = Ack not received
	#endif

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1
		//ARM does not support I2C in this mode - SW only
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
			MX_I2C_DELAY;
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
		//ARM does not support I2C in this mode - SW only
	#endif
}




//Slave functions currently not implemented
CALFUNCTION(void, FC_CAL_I2C_Slave_Init_, (MX_UINT8 Address, MX_UINT8 Mask))
{

}

CALFUNCTION(void, FC_CAL_I2C_Slave_Uninit_, (void))
{

}

CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_TxByte_, (MX_UINT8 Data))
{
	return (0);
}

CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_RxByte_, (MX_UINT8 Last))
{
	return (0);
}

CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_Status_, (void))
{
	return (0);
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
