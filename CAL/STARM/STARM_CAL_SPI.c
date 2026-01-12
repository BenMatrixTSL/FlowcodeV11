// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BE8AD878454316ED2644D152CF69231675186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5F3EBA38888ED5A684AB4E09F4E26C9B83857235436EFC5A7546BB342F60FAD5F1E797651BEB4FA24514C69F523159A567B5CF7487210CC7D10392D50B55B6B9C9DFFC633C164E2302A8FE7A3F31B12A3D578BA18CE050E81549D34A0D5AD11F35F5CB9667DFC77846FBFB159E2761D51BC976AC7618D6832FC0E9FB60DFEAB887A64FF5F89231504
// REVISION: 1.0
// GUID: 5C92AB4A-5FF7-4D19-9915-59AFFAE53D7E
// DATE: 08\08\2022
// DIR: CAL\STARM\STARM_CAL_SPI.c
/*********************************************************************
 *                  Flowcode CAL SPI File
 *
 * File: STARM_CAL_SPI.c
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
 * 290316 | BR | Created
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

#define MX_SPI_HANDLE_X			CAL_APPEND(MX_SPI_HANDLE_, MX_SPI_NUM)		//SPI instance structure handle

#define MX_SPI_CLOCK_X     		CAL_APPEND(MX_SPI_CLOCK_, MX_SPI_NUM)		//SPI Clock Config - eg __HAL_RCC_SPI1_CLK_ENABLE

#define MX_SPI_X				CAL_APPEND(MX_SPI_NAME_, MX_SPI_NUM)		//SPI Name - eg SPI1
#define MX_SPI_MOSI_AF_X		CAL_APPEND(MX_SPI_MOSI_AF_, MX_SPI_NUM)		//SPI Alt Function Name - eg GPIO_AF5_SPI1
#define MX_SPI_MISO_AF_X		CAL_APPEND(MX_SPI_MISO_AF_, MX_SPI_NUM)		//SPI Alt Function Name - eg GPIO_AF5_SPI1
#define MX_SPI_CLK_AF_X			CAL_APPEND(MX_SPI_CLK_AF_, MX_SPI_NUM)		//SPI Alt Function Name - eg GPIO_AF5_SPI1

#define MX_PRESCALE_VAR_X		CAL_APPEND(MX_PRESCALE_VAR_, MX_SPI_NUM)

MX_UINT8 MX_PRESCALE_VAR_X = (MX_SPI_PR_SCALE_X / 2) - 1;


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


//Create SPI Structure
SPI_HandleTypeDef MX_SPI_HANDLE_X;


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
	GPIO_InitTypeDef  GPIO_InitStruct;

	#if (MX_SPI_CHANNEL_X == 0)
		FC_CAL_Bit_High_DDR (MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_TRIS_X, MX_SPI_MOSI_PIN_X);		// MOSI pin is default high
		FC_CAL_Bit_In_DDR   (MX_SPI_MISO_PORT_X, MX_SPI_MISO_TRIS_X, MX_SPI_MISO_PIN_X);		// MISO pin is a input

		#if (MX_SPI_BMODE_X & 0x01)
			FC_CAL_Bit_High_DDR (MX_SPI_SCK_PORT_X, MX_SPI_SCK_TRIS_X, MX_SPI_SCK_PIN_X);		// Clock pin is default high
		#else
			FC_CAL_Bit_Low_DDR  (MX_SPI_SCK_PORT_X, MX_SPI_SCK_TRIS_X, MX_SPI_SCK_PIN_X);		// Clock pin is default low
		#endif
	#endif

	#if (MX_SPI_CHANNEL_X > 0)
		/* Enable SPI clock */
		MX_SPI_CLOCK_X();

		/* Set the SPI parameters */
		MX_SPI_HANDLE_X.Instance               = MX_SPI_X;

	#if	(MX_SPI_PR_SCALE_X < 3)
		MX_SPI_HANDLE_X.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	#elif (MX_SPI_PR_SCALE_X < 6)
		MX_SPI_HANDLE_X.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	#elif (MX_SPI_PR_SCALE_X < 12)
		MX_SPI_HANDLE_X.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	#elif (MX_SPI_PR_SCALE_X < 24)
		MX_SPI_HANDLE_X.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	#elif (MX_SPI_PR_SCALE_X < 48)
		MX_SPI_HANDLE_X.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
	#elif (MX_SPI_PR_SCALE_X < 96)
		MX_SPI_HANDLE_X.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	#elif (MX_SPI_PR_SCALE_X < 192)
		MX_SPI_HANDLE_X.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
	#else
		MX_SPI_HANDLE_X.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	#endif

		MX_SPI_HANDLE_X.Init.Direction         = SPI_DIRECTION_2LINES;

	#if (MX_SPI_BMODE_X & 0x02)
		MX_SPI_HANDLE_X.Init.CLKPhase          = SPI_PHASE_2EDGE;
	#else
		MX_SPI_HANDLE_X.Init.CLKPhase          = SPI_PHASE_1EDGE;
	#endif

	#if (MX_SPI_BMODE_X & 0x01)
		MX_SPI_HANDLE_X.Init.CLKPolarity       = SPI_POLARITY_HIGH;
	#else
		MX_SPI_HANDLE_X.Init.CLKPolarity       = SPI_POLARITY_LOW;
	#endif

		MX_SPI_HANDLE_X.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
		MX_SPI_HANDLE_X.Init.CRCPolynomial     = 7;
		MX_SPI_HANDLE_X.Init.DataSize          = SPI_DATASIZE_8BIT;
		MX_SPI_HANDLE_X.Init.FirstBit          = SPI_FIRSTBIT_MSB;
		MX_SPI_HANDLE_X.Init.NSS               = SPI_NSS_SOFT;
		MX_SPI_HANDLE_X.Init.TIMode            = SPI_TIMODE_DISABLE;
		MX_SPI_HANDLE_X.Init.Mode 			 = SPI_MODE_MASTER;

		HAL_SPI_Init(&MX_SPI_HANDLE_X);

		//Special case for BL0061 ARM EB2 Board - Remap Flowcode Pins to Actual Port Pins
		#ifdef MX_BL0061_PINMAP
			#undef MX_SPI_SCK_PIN_X
			#undef MX_SPI_MISO_PIN_X
			#undef MX_SPI_MOSI_PIN_X
			#undef MX_SPI_SCK_PORT_X
			#undef MX_SPI_MISO_PORT_X
			#undef MX_SPI_MOSI_PORT_X

			#if MX_SPI_CHANNEL_X == 1
				#define MX_SPI_SCK_PIN_X (5)
				#define MX_SPI_MISO_PIN_X (6)
				#define MX_SPI_MOSI_PIN_X (7)
				#define MX_SPI_SCK_PORT_X GPIOA
				#define MX_SPI_MISO_PORT_X GPIOA
				#define MX_SPI_MOSI_PORT_X GPIOA
			#endif
			#if MX_SPI_CHANNEL_X == 2
				#define MX_SPI_SCK_PIN_X (13)
				#define MX_SPI_MISO_PIN_X (14)
				#define MX_SPI_MOSI_PIN_X (15)
				#define MX_SPI_SCK_PORT_X GPIOB
				#define MX_SPI_MISO_PORT_X GPIOB
				#define MX_SPI_MOSI_PORT_X GPIOB
			#endif
			#if MX_SPI_CHANNEL_X == 3
				#define MX_SPI_SCK_PIN_X (10)
				#define MX_SPI_MISO_PIN_X (11)
				#define MX_SPI_MOSI_PIN_X (12)
				#define MX_SPI_SCK_PORT_X GPIOC
				#define MX_SPI_MISO_PORT_X GPIOC
				#define MX_SPI_MOSI_PORT_X GPIOC
			#endif
		#endif

		/* SPI SCK GPIO pin configuration  */
		GPIO_InitStruct.Pin       = 1 << MX_SPI_SCK_PIN_X;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_PULLUP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = MX_SPI_CLK_AF_X;

		HAL_GPIO_Init(MX_SPI_SCK_PORT_X, &GPIO_InitStruct);

		/* SPI MISO GPIO pin configuration  */
		GPIO_InitStruct.Pin 	  = 1 << MX_SPI_MISO_PIN_X;
		GPIO_InitStruct.Alternate = MX_SPI_MISO_AF_X;

		HAL_GPIO_Init(MX_SPI_MISO_PORT_X, &GPIO_InitStruct);

		/* SPI MOSI GPIO pin configuration  */
		GPIO_InitStruct.Pin		  = 1 << MX_SPI_MOSI_PIN_X;
		GPIO_InitStruct.Alternate = MX_SPI_MOSI_AF_X;

		HAL_GPIO_Init(MX_SPI_MOSI_PORT_X, &GPIO_InitStruct);
	#endif
	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_Master_Uninit_, (void))
{
	#if (MX_SPI_CHANNEL_X > 0)
		GPIO_InitTypeDef  GPIO_InitStruct;

		GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull      = GPIO_NOPULL;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;

		// SPI SCK GPIO pin configuration
		GPIO_InitStruct.Pin       = 1 << MX_SPI_SCK_PIN_X;
		HAL_GPIO_Init(MX_SPI_SCK_PORT_X, &GPIO_InitStruct);

		// SPI MISO GPIO pin configuration
		GPIO_InitStruct.Pin 	  = 1 << MX_SPI_MISO_PIN_X;
		HAL_GPIO_Init(MX_SPI_MISO_PORT_X, &GPIO_InitStruct);

		// SPI MOSI GPIO pin configuration
		GPIO_InitStruct.Pin		  = 1 << MX_SPI_MOSI_PIN_X;
		HAL_GPIO_Init(MX_SPI_MOSI_PORT_X, &GPIO_InitStruct);
	#else
		//Reset Pins to Inputs
		FC_CAL_Bit_In_DDR (MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_TRIS_X, MX_SPI_MOSI_PIN_X);
		FC_CAL_Bit_In_DDR (MX_SPI_MISO_PORT_X, MX_SPI_MISO_TRIS_X, MX_SPI_MISO_PIN_X);
		FC_CAL_Bit_In_DDR (MX_SPI_SCK_PORT_X, MX_SPI_SCK_TRIS_X, MX_SPI_SCK_PIN_X);
	#endif
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
			FCI_DELAYBYTE_US(MX_PRESCALE_VAR_X);

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
			FCI_DELAYBYTE_US(MX_PRESCALE_VAR_X);

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

	#if (MX_SPI_CHANNEL_X > 0)
		HAL_SPI_TransmitReceive(&MX_SPI_HANDLE_X, &DataOut, &retVal, 1, 10);
	#endif

	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_SetPrescaler_, (MX_UINT8 Prescaler))
{
	MX_PRESCALE_VAR_X = Prescaler;

	#if (MX_SPI_CHANNEL_X > 0)

	#endif
}




//Not currently implemented

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
