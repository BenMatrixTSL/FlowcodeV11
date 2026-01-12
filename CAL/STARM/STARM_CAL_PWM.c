// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BE710E9ED9BA6E2533B656C080141B6EDA186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5C0763D185536B2A76F72F8A5A9A3A413415DE53552CAF1220A0A5BE875464DD8570BD57DDC4A847F0CBEB86EFFBEC97D4FE6B71C4F9C0AC17A75AFD46C54640EE3EEC4FEDCF74B2D46BD2FB67EC3B7869A6DA71FF9458762549D34A0D5AD11F3C340C2E9047014A70034608B88982798374D9EA12DAECB35A8B2FE2536E6C50FEBD31FED13C8BAD2
// REVISION: 1.0
// GUID: 1AAC85CC-CC2E-4A1E-97A0-3026C76B9DE3
// DATE: 08\08\2022
// DIR: CAL\STARM\STARM_CAL_PWM.c
/*********************************************************************
 *                  Flowcode CAL UART File
 *
 * File: STARM_CAL_UART.c
 *
 * (c) 2016 Matrix Multimedia Ltd.
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
 * 141116 | SK | Created
 */



#ifndef MX_HAL_PWM_MODULE_INCLUDED
	#define MX_HAL_PWM_MODULE_INCLUDED
#endif

//Dynamic function naming based on defines and index number
#define MX_PWM_PIN_X		CAL_APPEND(MX_PWM_PIN_, MX_PWM_NUM)
#define MX_PWM_TYPE_X		CAL_APPEND(MX_PWM_TYPE_, MX_PWM_NUM)
#define MX_PWM_PORT_X		CAL_APPEND(MX_PWM_PORT_, MX_PWM_NUM)
#define MX_PWM_TRIS_X		CAL_APPEND(MX_PWM_TRIS_, MX_PWM_NUM)
#define MX_PWM_CHANNEL_X	CAL_APPEND(MX_PWM_CHANNEL_, MX_PWM_NUM)

#define MX_PWM_AF_X			CAL_APPEND(MX_PWM_AF_, MX_PWM_NUM)
#define MX_PWM_NAME_X		CAL_APPEND(MX_PWM_NAME_, MX_PWM_NUM)
#define MX_PWM_CLOCK_X		CAL_APPEND(MX_PWM_CLOCK_, MX_PWM_NUM)
#define MX_PWM_NUMBER_X		CAL_APPEND(MX_PWM_NUMBER_, MX_PWM_NUM)

#define MX_TIM_HANDLE_X		CAL_APPEND(MX_TIM_HANDLE_, MX_PWM_NUM)
#define MX_CONFIG_OC_X		CAL_APPEND(MX_CONFIG_OC_, MX_PWM_NUM)

/*
//Interrupt Definitions
#if (MX_UART_INT_X == 1)

	#ifndef MX_UART_INT_DEFS
	#define MX_UART_INT_DEFS

		#define MX_UART_INT_CH1_FUNC
		#define MX_UART_INT_CH2_FUNC
		#define MX_UART_INT_FUNC_END

		#define MX_UART_INT_CH1_DET		ts_bit(pir1, RCIF) && ts_bit(pie1, RCIE)
		#define MX_UART_INT_CH2_DET		ts_bit(MX_UART2_PIR, RC2IF) && ts_bit(MX_UART2_PIE, RC2IE)

		#define MX_UART_INT_CH1_EN		st_bit (pie1, RCIE)
		#define MX_UART_INT_CH2_EN		st_bit (MX_UART2_PIE, RC2IE)

		#define MX_UART_INT_CH1_DIS		cr_bit (pie1, RCIE)
		#define MX_UART_INT_CH2_DIS		cr_bit (MX_UART2_PIE, RC2IE)

		#define MX_UART_INT_CH1_CLR		cr_bit (pir1, RCIF)
		#define MX_UART_INT_CH2_CLR		cr_bit (MX_UART2_PIR, RC2IF)

	#endif
#endif
*/

	//Special case for BL0061 ARM EB2 Board - Remap Flowcode Pins to Actual Port Pins
	#ifdef MX_BL0061_PINMAP
		#undef MX_PWM_PIN_X
		#undef MX_PWM_PORT_X
		#if (MX_PWM_CHANNEL_X == 1)
			#define MX_PWM_PIN_X (8)
			#define MX_PWM_PORT_X GPIOA
		#elif (MX_PWM_CHANNEL_X == 2)
			#define MX_PWM_PIN_X (9)
			#define MX_PWM_PORT_X GPIOA
		#elif (MX_PWM_CHANNEL_X == 3)
			#define MX_PWM_PIN_X (10)
			#define MX_PWM_PORT_X GPIOA
		#elif (MX_PWM_CHANNEL_X == 4)
			#define MX_PWM_PIN_X (11)
			#define MX_PWM_PORT_X GPIOA
		#elif (MX_PWM_CHANNEL_X == 5)
			#define MX_PWM_PIN_X (5)
			#define MX_PWM_PORT_X GPIOA
		#elif (MX_PWM_CHANNEL_X == 6)
			#define MX_PWM_PIN_X (3)
			#define MX_PWM_PORT_X GPIOB
		#elif (MX_PWM_CHANNEL_X == 7)
			#define MX_PWM_PIN_X (10)
			#define MX_PWM_PORT_X GPIOB
		#elif (MX_PWM_CHANNEL_X == 8)
			#define MX_PWM_PIN_X (6)
			#define MX_PWM_PORT_X GPIOA
		#elif (MX_PWM_CHANNEL_X == 9)
			#define MX_PWM_PIN_X (7)
			#define MX_PWM_PORT_X GPIOA
		#elif (MX_PWM_CHANNEL_X == 10)
			#define MX_PWM_PIN_X (0)
			#define MX_PWM_PORT_X GPIOB
		#elif (MX_PWM_CHANNEL_X == 11)
			#define MX_PWM_PIN_X (1)
			#define MX_PWM_PORT_X GPIOB
		#elif (MX_PWM_CHANNEL_X == 12)
			#define MX_PWM_PIN_X (6)
			#define MX_PWM_PORT_X GPIOB
		#elif (MX_PWM_CHANNEL_X == 13)
			#define MX_PWM_PIN_X (7)
			#define MX_PWM_PORT_X GPIOB
		#elif (MX_PWM_CHANNEL_X == 14)
			#define MX_PWM_PIN_X (8)
			#define MX_PWM_PORT_X GPIOB
		#elif (MX_PWM_CHANNEL_X == 15)
			#define MX_PWM_PIN_X (9)
			#define MX_PWM_PORT_X GPIOB
		#elif (MX_PWM_CHANNEL_X == 16)
			#define MX_PWM_PIN_X (0)
			#define MX_PWM_PORT_X GPIOA
		#elif (MX_PWM_CHANNEL_X == 17)
			#define MX_PWM_PIN_X (1)
			#define MX_PWM_PORT_X GPIOA
		#elif (MX_PWM_CHANNEL_X == 18)
			#define MX_PWM_PIN_X (2)
			#define MX_PWM_PORT_X GPIOA
		#elif (MX_PWM_CHANNEL_X == 19)
			#define MX_PWM_PIN_X (3)
			#define MX_PWM_PORT_X GPIOA
		#elif (MX_PWM_CHANNEL_X == 20)
			#define MX_PWM_PIN_X (6)
			#define MX_PWM_PORT_X GPIOC
		#elif (MX_PWM_CHANNEL_X == 21)
			#define MX_PWM_PIN_X (7)
			#define MX_PWM_PORT_X GPIOC
		#elif (MX_PWM_CHANNEL_X == 22)
			#define MX_PWM_PIN_X (8)
			#define MX_PWM_PORT_X GPIOC
		#elif (MX_PWM_CHANNEL_X == 23)
			#define MX_PWM_PIN_X (9)
			#define MX_PWM_PORT_X GPIOC
		#elif (MX_PWM_CHANNEL_X == 24)
			#define MX_PWM_PIN_X (14)
			#define MX_PWM_PORT_X GPIOB
		#elif (MX_PWM_CHANNEL_X == 25)
			#define MX_PWM_PIN_X (15)
			#define MX_PWM_PORT_X GPIOB
		#endif
	#endif


CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 FCL_PERIOD, MX_UINT16 FCL_PRESCALER));
CALFUNCTION(void, FC_CAL_PWM_Disable_, (void));
CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 FCL_DUTY));
CALFUNCTION(void, FC_CAL_PWM_Enable_, (void));
CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 FCL_DUTY));


//Create PWM Structures
TIM_HandleTypeDef	MX_TIM_HANDLE_X;
TIM_OC_InitTypeDef	MX_CONFIG_OC_X;

CALFUNCTION(void, FC_CAL_PWM_Enable_, (void))
{
	GPIO_InitTypeDef GPIO_InitStruct;
	MX_UINT16 pwm_chan;

	MX_PWM_CLOCK_X();

// Timer config
	MX_TIM_HANDLE_X.Instance = MX_PWM_NAME_X;

//	MX_TIM_HANDLE_X.Init.Prescaler = 1;
	MX_TIM_HANDLE_X.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	MX_TIM_HANDLE_X.Init.CounterMode = TIM_COUNTERMODE_UP;
	MX_TIM_HANDLE_X.Init.RepetitionCounter = 0;

	HAL_TIM_PWM_Init(&MX_TIM_HANDLE_X);
	HAL_TIM_Base_Start(&MX_TIM_HANDLE_X);

// GPIO initialization
	GPIO_InitStruct.Pin = (1 << MX_PWM_PIN_X);
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = MX_PWM_AF_X;
	HAL_GPIO_Init(MX_PWM_PORT_X, &GPIO_InitStruct);

// PWM channel config
	MX_CONFIG_OC_X.OCMode = TIM_OCMODE_PWM1;
	MX_CONFIG_OC_X.OCIdleState = TIM_OCIDLESTATE_SET;
	MX_CONFIG_OC_X.Pulse = 0;
	MX_CONFIG_OC_X.OCPolarity = TIM_OCPOLARITY_HIGH;
	MX_CONFIG_OC_X.OCFastMode = TIM_OCFAST_ENABLE;

#if (MX_PWM_NUMBER_X == 1)
	pwm_chan = TIM_CHANNEL_1;
#elif (MX_PWM_NUMBER_X == 2)
	pwm_chan = TIM_CHANNEL_2;
#elif (MX_PWM_NUMBER_X == 3)
	pwm_chan = TIM_CHANNEL_3;
#elif (MX_PWM_NUMBER_X == 4)
	pwm_chan = TIM_CHANNEL_4;
#endif

	HAL_TIM_PWM_ConfigChannel(&MX_TIM_HANDLE_X, &MX_CONFIG_OC_X, pwm_chan);
	HAL_TIM_PWM_Start(&MX_TIM_HANDLE_X, pwm_chan);
}

CALFUNCTION(void, FC_CAL_PWM_Disable_, (void))
{
	GPIO_InitTypeDef GPIO_InitStruct;
	MX_UINT16 pwm_chan;

#if (MX_PWM_NUMBER_X == 1)
	pwm_chan = TIM_CHANNEL_1;
#elif (MX_PWM_NUMBER_X == 2)
	pwm_chan = TIM_CHANNEL_2;
#elif (MX_PWM_NUMBER_X == 3)
	pwm_chan = TIM_CHANNEL_3;
#elif (MX_PWM_NUMBER_X == 4)
	pwm_chan = TIM_CHANNEL_4;
#endif

	// GPIO revert to input
	GPIO_InitStruct.Pin = (1 << MX_PWM_PIN_X);
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(MX_PWM_PORT_X, &GPIO_InitStruct);
	//
	HAL_TIM_PWM_Stop(&MX_TIM_HANDLE_X, pwm_chan);
}

CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 FCL_PERIOD, MX_UINT16 FCL_PRESCALER))
{
	MX_TIM_HANDLE_X.Instance = MX_PWM_NAME_X;

	MX_TIM_HANDLE_X.Init.Period = FCL_PERIOD;
	MX_TIM_HANDLE_X.Init.Prescaler = FCL_PRESCALER -1;
	HAL_TIM_PWM_Init(&MX_TIM_HANDLE_X);
	HAL_TIM_Base_Start(&MX_TIM_HANDLE_X);
}

CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 FCL_DUTY))
{
	MX_UINT16 pwm_chan;

#if (MX_PWM_NUMBER_X == 1)
	pwm_chan = TIM_CHANNEL_1;
#elif (MX_PWM_NUMBER_X == 2)
	pwm_chan = TIM_CHANNEL_2;
#elif (MX_PWM_NUMBER_X == 3)
	pwm_chan = TIM_CHANNEL_3;
#elif (MX_PWM_NUMBER_X == 4)
	pwm_chan = TIM_CHANNEL_4;
#endif

	MX_CONFIG_OC_X.Pulse = FCL_DUTY;

	HAL_TIM_PWM_ConfigChannel(&MX_TIM_HANDLE_X, &MX_CONFIG_OC_X, pwm_chan);
	HAL_TIM_PWM_Start(&MX_TIM_HANDLE_X, pwm_chan);
}

CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 FCL_DUTY))
{
	MX_UINT16 pwm_chan;

	MX_CONFIG_OC_X.Pulse = FCL_DUTY;

#if (MX_PWM_NUMBER_X == 1)
	pwm_chan = TIM_CHANNEL_1;
#elif (MX_PWM_NUMBER_X == 2)
	pwm_chan = TIM_CHANNEL_2;
#elif (MX_PWM_NUMBER_X == 3)
	pwm_chan = TIM_CHANNEL_3;
#elif (MX_PWM_NUMBER_X == 4)
	pwm_chan = TIM_CHANNEL_4;
#endif

	HAL_TIM_PWM_ConfigChannel(&MX_TIM_HANDLE_X, &MX_CONFIG_OC_X, pwm_chan);
	HAL_TIM_PWM_Start(&MX_TIM_HANDLE_X, pwm_chan);
}

