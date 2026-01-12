// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BEBC498017453FC42375FFFCA09E4CC8D9186EF292F6E67B0826724E02FB1A5213F3C76BAD8EEF9A81C5BD6FC7FBC82BBEEAB3A14A2A013993711B8143522C2B69B4A52D0051DB9CC505B156E6D9B6E240970D2ACE12D7CCA83F32982CE01095F4E3B96DE0A63654988AAF8FE11F8718275A03929D6B9D052C8FDB81183BD8A4F1649E9E54A88109462A65D919BDB65BD4A61930F97993E62D549D34A0D5AD11F3C3451EEFFB383385D7645225E17125E0B9CACC7D85C9A90942BD2180FD7CFFB0161DC776D051D9AD
// REVISION: 2.0
// GUID: 1ABE1988-D184-40C0-932D-C3D1319151B2
// DATE: 20\01\2023
// DIR: CAL\STARM\STARM_CAL_I2C.c
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
 * 220118 | LM | Add transaction functions
 * 060219 | LM | Add hardware support
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

#if (MX_I2C_CHANNEL_X > 0)
	#define MX_I2C_X				CAL_APPEND(I2C, MX_I2C_NUM)					// I2C Name - eg I2C1
	#define MX_I2C_CLOCK_X     		CAL_APPEND(MX_I2C_CLOCK_, MX_I2C_NUM)		// I2C Clock Config - eg __HAL_RCC_SPI1_CLK_ENABLE
	#define MX_I2C_HANDLE_X			CAL_APPEND(MX_I2C_HANDLE_, MX_I2C_NUM)		// I2C instance structure handle
	#define MX_I2C_SCL_AF_X			CAL_APPEND(MX_I2C_SCL_AF_, MX_I2C_NUM)		// I2C SCL Alt
	#define MX_I2C_SDA_AF_X			CAL_APPEND(MX_I2C_SDA_AF_, MX_I2C_NUM)		// I2C SDA Alt
	I2C_HandleTypeDef MX_I2C_HANDLE_X;											// Create I2C Structure
#else
	//I2C Timeout - Avoids any blocking delays
	#define MX_I2C_TIMEOUT_X		CAL_APPEND(MX_I2C_TIMEOUT_, MX_I2C_NUM)
	MX_UINT16 MX_I2C_TIMEOUT_X;
#endif

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
#endif


CALFUNCTION(void, FC_CAL_I2C_Master_Init_, (void))
{

	#if (MX_I2C_CHANNEL_X == 0)															//Use Master I2C Software
		FC_CAL_Bit_In_DDR(MX_I2C_SDA_PORT_X, MX_I2C_SDA_TRIS_X, MX_I2C_SDA_PIN_X);		//Configure SDA as Input
		FC_CAL_Bit_In_DDR(MX_I2C_SCL_PORT_X, MX_I2C_SCL_TRIS_X, MX_I2C_SCL_PIN_X);		//Configure SCL as Input
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

		#if (MX_I2C_CHANNEL_X == 0)
			CALFUNCTION(, FC_CAL_I2C_Master_Init_, ());
			return 1;	// Success
		#else
			GPIO_InitTypeDef  GPIO_InitStruct;

			#if (MX_I2C_CHANNEL_X == 1)
				__HAL_RCC_I2C1_CLK_ENABLE();
				MX_I2C_HANDLE_X.Instance = I2C1;
			#elif (MX_I2C_CHANNEL_X == 2)
				__HAL_RCC_I2C2_CLK_ENABLE();
				MX_I2C_HANDLE_X.Instance = I2C2;
			#endif

			#if defined (__STM32F0xx_HAL_I2C_H)
				RCC_PeriphCLKInitTypeDef PeriphClkInit;
				PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
				PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
				HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
			#endif

			//Special case for BL0061 ARM EB2 Board - Remap Flowcode Pins to Actual Port Pins
			#ifdef MX_BL0061_PINMAP
				#undef MX_I2C_SCL_PIN_X
				#undef MX_I2C_SDA_PIN_X
				#undef MX_I2C_SCL_PORT_X
				#undef MX_I2C_SDA_PORT_X

				#if MX_I2C_CHANNEL_X == 1
					#define MX_I2C_SCL_PIN_X (6)
					#define MX_I2C_SDA_PIN_X (7)
					#define MX_I2C_SCL_PORT_X GPIOB
					#define MX_I2C_SDA_PORT_X GPIOB
				#endif
			#endif

			/* I2C SCL GPIO pin configuration  */
			GPIO_InitStruct.Pin       = 1 << MX_I2C_SCL_PIN_X;
			GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
			GPIO_InitStruct.Pull      = GPIO_PULLUP;
			GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
			GPIO_InitStruct.Alternate = MX_I2C_SCL_AF_X;
			HAL_GPIO_Init(MX_I2C_SCL_PORT_X, &GPIO_InitStruct);

			/* I2C SDA GPIO pin configuration  */
			GPIO_InitStruct.Pin 	  = 1 << MX_I2C_SDA_PIN_X;
			GPIO_InitStruct.Alternate = MX_I2C_SDA_AF_X;
			HAL_GPIO_Init(MX_I2C_SDA_PORT_X, &GPIO_InitStruct);

			#if defined (__STM32F0xx_HAL_I2C_H)
				// This code currently assumes fI2CCLK is HSI (the default)
				#if (MX_I2C_BAUD_X < 300000)
					// 100K
					MX_I2C_HANDLE_X.Init.Timing = (0x01U << I2C_TIMINGR_PRESC_Pos)
													|(0x04U << I2C_TIMINGR_SCLDEL_Pos)
													|(0x02U << I2C_TIMINGR_SDADEL_Pos)
													|(0x0FU << I2C_TIMINGR_SCLH_Pos)
													|(0x13U << I2C_TIMINGR_SCLL_Pos);
				#elif (MX_I2C_BAUD_X < 500000)
					// 400K
					MX_I2C_HANDLE_X.Init.Timing = 0x00901A53;
				#else
					// 500K (max at HSI)
					MX_I2C_HANDLE_X.Init.Timing = (0x00U << I2C_TIMINGR_PRESC_Pos)
													|(0x00U << I2C_TIMINGR_SCLDEL_Pos)
													|(0x00U << I2C_TIMINGR_SDADEL_Pos)
													|(0x03U << I2C_TIMINGR_SCLH_Pos)
													|(0x06U << I2C_TIMINGR_SCLL_Pos);
				#endif

			#elif defined (__STM32F4xx_HAL_I2C_H)
				MX_I2C_HANDLE_X.Init.ClockSpeed = MX_I2C_BAUD_X;
				MX_I2C_HANDLE_X.Init.DutyCycle = I2C_DUTYCYCLE_2;

			#else
				// This needs further work ...
				MX_I2C_HANDLE_X.Init.Timing = 0x70777F7F;
			#endif

			MX_I2C_HANDLE_X.Init.OwnAddress1 = 0;
			MX_I2C_HANDLE_X.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
			MX_I2C_HANDLE_X.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
			MX_I2C_HANDLE_X.Init.OwnAddress2 = 0;
			#if 0 // Which device?
				MX_I2C_HANDLE_X.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
			#endif
			MX_I2C_HANDLE_X.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
			MX_I2C_HANDLE_X.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
			if (HAL_I2C_Init(&MX_I2C_HANDLE_X) == HAL_OK)
				return 1;	// Success
			else
				return 0;	// Fail
		#endif
	}
}

CALFUNCTION(MX_UINT16, FC_CAL_I2C_Transaction_Read_,   (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length))
{
	if (Length > Size) return 0;
	MX_UINT16 n = 0;
	#if (MX_I2C_CHANNEL_X == 0)
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
	#else
		if (HAL_I2C_Master_Receive(&MX_I2C_HANDLE_X, (MX_I2C_ADDRESS_X<<1), Buffer, Length, 200) == HAL_OK)
			return Length;
		else
			return 0;
	#endif

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
	#if (MX_I2C_CHANNEL_X == 0)
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
	#else
		HAL_StatusTypeDef ErrorCode = HAL_I2C_Master_Transmit(&MX_I2C_HANDLE_X, (MX_I2C_ADDRESS_X<<1), Buffer, Length, 2000);
		if (ErrorCode == HAL_OK)
			return Length;
		else
			return 0;
	#endif
	return n;
}

CALFUNCTION(void,     FC_CAL_I2C_Transaction_Uninit_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)
		CALFUNCTION(, FC_CAL_I2C_Master_Uninit_, ());
	#else
		HAL_I2C_DeInit(&MX_I2C_HANDLE_X);
	#endif
}
