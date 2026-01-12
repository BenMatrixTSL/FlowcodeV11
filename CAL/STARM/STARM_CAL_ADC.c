// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BE32EDF69067A133BBE6AB16F4A0496FD1186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF55A511C7E37D1DEAEFCF51200FF745350317E981B2772BCA577DEA2E05E59F4A7406E948489D4E57C344C05A318972110C2D83516871D323E5F53EBE6FF5E6557E0CF0B44255A38AAF21683EA05DCB2EDA72BDA3A5A4AAF70549D34A0D5AD11F39D2FA68650DD736FCAE265D498F931BF0034F2086BB9472B84C37E21E8DB1164AF575DDB9223ACD6
// REVISION: 1.0
// GUID: F0238A3A-46F7-49D4-8D24-218367C65E26
// DATE: 08\08\2022
// DIR: CAL\STARM\STARM_CAL_ADC.c
/*********************************************************************
 *                  Flowcode CAL ADC File
 *
 * File: STARM_CAL_ADC.c
 *
 * (c) 2016 Matrix TSL.
 * http://www.matrixtsl.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
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
 * 060911 | BR | Created
 * 210911 | BR | Updated to include all ADC type files
 * 020312 | BR | Updated to v5.1 CAL Schema
 * 230512 | BR | Added XMEGA functionality
 * 171212 | BR | Moved the code to begin the sample to allow for more optimised ADC readings
 * 030713 | LM | Standard API calls
 * 240414 | LM | Additions to support Touch via ADC
 * 170914 | LM | Additions to support Touch via ADC (some types now actually work!)
 * 011216 | LM | ST ARM updates and fixes
 */


//ADC Function Prototypes
CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge));
CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode));
CALFUNCTION(void, FC_CAL_ADC_Disable_, (void));



/* ADC handler declaration */
ADC_HandleTypeDef		MX_ADC_HANDLE;
ADC_ChannelConfTypeDef	MX_ADC_CH_CONF;
GPIO_InitTypeDef		MX_GPIO_INIT_STRUCT;

uint32_t MX_TEMP_MODER, MX_TEMP_OTYPER, MX_TEMP_OSPEEDR, MX_TEMP_PUPDR, MX_TEMP_AFRH, MX_TEMP_AFRL;

GPIO_TypeDef*	MX_ADC_PORT_X = GPIOA;
uint32_t		MX_ADC_PIN_X = 0;


#ifdef MX_ADC_TYPE_1
/*******************************************************************************************
* ADC Type 1 Supported Devices  STM32F2, STM32F4
*******************************************************************************************/
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			case 0:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 0; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_0; break;
			case 1:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 1; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_1; break;
			case 2:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 2; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_2; break;
			case 3:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 3; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_3; break;
			case 4:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 4; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_4; break;
			case 5:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 5; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_5; break;
			case 6:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 6; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_6; break;
			case 7:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 7; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_7; break;
			case 8:  MX_ADC_PORT_X = GPIOB; MX_ADC_PIN_X = 0; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_8; break;
			case 9:  MX_ADC_PORT_X = GPIOB; MX_ADC_PIN_X = 1; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_9; break;
			case 10: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 0; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_10; break;
			case 11: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 1; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_11; break;
			case 12: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 2; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_12; break;
			case 13: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 3; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_13; break;
			case 14: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 4; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_14; break;
			case 15: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 5; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_15; break;
		}

		/*##-1- Configure the ADC peripheral #######################################*/

		#if (MX_ADC_NUM == 1)
			__HAL_RCC_ADC1_CLK_ENABLE();
			MX_ADC_HANDLE.Instance = ADC1;
		#endif

		#if (MX_ADC_NUM == 2)
			__HAL_RCC_ADC2_CLK_ENABLE();
			MX_ADC_HANDLE.Instance = ADC2;
		#endif

		#if (MX_ADC_NUM == 3)
			__HAL_RCC_ADC3_CLK_ENABLE();
			MX_ADC_HANDLE.Instance = ADC3;
		#endif

		if (Conv_Speed == 2)
			MX_ADC_HANDLE.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
		else if (Conv_Speed == 4)
			MX_ADC_HANDLE.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
		else if (Conv_Speed == 6)
			MX_ADC_HANDLE.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV6;
		else
			MX_ADC_HANDLE.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;

		MX_ADC_HANDLE.Init.Resolution = ADC_RESOLUTION_12B;
		MX_ADC_HANDLE.Init.ScanConvMode = DISABLE;
		MX_ADC_HANDLE.Init.ContinuousConvMode = DISABLE;
		MX_ADC_HANDLE.Init.DiscontinuousConvMode = DISABLE;
		MX_ADC_HANDLE.Init.NbrOfDiscConversion = 0;
		MX_ADC_HANDLE.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
		MX_ADC_HANDLE.Init.ExternalTrigConv = ADC_SOFTWARE_START;
		MX_ADC_HANDLE.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		MX_ADC_HANDLE.Init.NbrOfConversion = 1;
		MX_ADC_HANDLE.Init.DMAContinuousRequests = DISABLE;
		MX_ADC_HANDLE.Init.EOCSelection = ENABLE;

		/*##-2- Configure ADC regular channel ######################################*/
		MX_ADC_CH_CONF.Rank = 1;
		MX_ADC_CH_CONF.Offset = 0;
		if (T_Charge > 144)
		MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_480CYCLES;
		else if (T_Charge > 112)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_144CYCLES;
		else if (T_Charge > 84)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_112CYCLES;
		else if (T_Charge > 56)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_84CYCLES;
		else if (T_Charge > 28)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_56CYCLES;
		else if (T_Charge > 15)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_28CYCLES;
		else if (T_Charge > 3)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_15CYCLES;
		else
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_3CYCLES;

		// ##-2- Save current GPIO ##########################################
		MX_TEMP_MODER = MX_ADC_PORT_X->MODER;
		MX_TEMP_OTYPER = MX_ADC_PORT_X->OTYPER;
		MX_TEMP_OSPEEDR = MX_ADC_PORT_X->OSPEEDR;
		MX_TEMP_PUPDR = MX_ADC_PORT_X->PUPDR;
		MX_TEMP_AFRH = MX_ADC_PORT_X->AFR[0];
		MX_TEMP_AFRL = MX_ADC_PORT_X->AFR[1];

		// ##-2- Configure peripheral GPIO ##########################################
		MX_GPIO_INIT_STRUCT.Pin = 1 << MX_ADC_PIN_X;
		MX_GPIO_INIT_STRUCT.Mode = GPIO_MODE_ANALOG;
		MX_GPIO_INIT_STRUCT.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(MX_ADC_PORT_X, &MX_GPIO_INIT_STRUCT);

		HAL_ADC_Init(&MX_ADC_HANDLE);
	}


	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal = 0;

		if (HAL_ADC_ConfigChannel(&MX_ADC_HANDLE, &MX_ADC_CH_CONF) == HAL_OK)
		{
			if (HAL_ADC_Start(&MX_ADC_HANDLE) == HAL_OK)
			{
				if (HAL_ADC_PollForConversion(&MX_ADC_HANDLE, 100) == HAL_OK)
				{
					iRetVal = HAL_ADC_GetValue(&MX_ADC_HANDLE);
					if(!Sample_Mode)
						iRetVal >>= 4;
				}
			}
		}
		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{

		MX_GPIO_INIT_STRUCT.Pin = 1 << MX_ADC_PIN_X;
		MX_GPIO_INIT_STRUCT.Mode = (MX_TEMP_MODER >> (MX_ADC_PIN_X << 1)) & 0x03;
		MX_GPIO_INIT_STRUCT.Mode |= (((MX_TEMP_OTYPER >> MX_ADC_PIN_X) & 0x01) << 2);
		MX_GPIO_INIT_STRUCT.Speed |= (MX_TEMP_OSPEEDR >> (MX_ADC_PIN_X << 1)) & 0x03;
		MX_GPIO_INIT_STRUCT.Pull = (MX_TEMP_PUPDR >> (MX_ADC_PIN_X << 1)) & 0x03;

		if(MX_ADC_PIN_X > 0x07)
		{
			MX_ADC_PIN_X -= 7;
			MX_GPIO_INIT_STRUCT.Alternate = (MX_TEMP_AFRH >> (MX_ADC_PIN_X << 2)) & 0x0f;
		} else {
			MX_GPIO_INIT_STRUCT.Alternate = (MX_TEMP_AFRL >> (MX_ADC_PIN_X << 2)) & 0x0f;
		}

		HAL_GPIO_Init(MX_ADC_PORT_X, &MX_GPIO_INIT_STRUCT);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	#endif // MX_ADC_TOUCH


#elif defined MX_ADC_TYPE_2
/*******************************************************************************************
* ADC Type 2 Supported Devices  STM32F0
*******************************************************************************************/
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			case 0:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 0; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_0; break;
			case 1:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 1; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_1; break;
			case 2:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 2; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_2; break;
			case 3:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 3; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_3; break;
			case 4:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 4; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_4; break;
			case 5:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 5; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_5; break;
			case 6:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 6; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_6; break;
			case 7:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 7; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_7; break;
			case 8:  MX_ADC_PORT_X = GPIOB; MX_ADC_PIN_X = 0; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_8; break;
			case 9:  MX_ADC_PORT_X = GPIOB; MX_ADC_PIN_X = 1; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_9; break;
			case 10: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 0; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_10; break;
			case 11: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 1; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_11; break;
			case 12: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 2; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_12; break;
			case 13: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 3; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_13; break;
			case 14: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 4; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_14; break;
			case 15: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 5; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_15; break;
		}

		/*##-1- Configure the ADC peripheral #######################################*/

		#if (MX_ADC_NUM == 1)
			__HAL_RCC_ADC1_CLK_ENABLE();
			MX_ADC_HANDLE.Instance = ADC1;
		#endif

		#if (MX_ADC_NUM == 2)
			__HAL_RCC_ADC2_CLK_ENABLE();
			MX_ADC_HANDLE.Instance = ADC2;
		#endif

		#if (MX_ADC_NUM == 3)
			__HAL_RCC_ADC3_CLK_ENABLE();
			MX_ADC_HANDLE.Instance = ADC3;
		#endif

		if (Conv_Speed == 2)
			MX_ADC_HANDLE.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
		else // if (Conv_Speed == 4)
			MX_ADC_HANDLE.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;

		MX_ADC_HANDLE.Init.Resolution = ADC_RESOLUTION_12B;
		MX_ADC_HANDLE.Init.ScanConvMode = DISABLE;
		MX_ADC_HANDLE.Init.ContinuousConvMode = DISABLE;
		MX_ADC_HANDLE.Init.DiscontinuousConvMode = DISABLE;
		MX_ADC_HANDLE.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
		MX_ADC_HANDLE.Init.ExternalTrigConv = ADC_SOFTWARE_START;
		MX_ADC_HANDLE.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		MX_ADC_HANDLE.Init.DMAContinuousRequests = DISABLE;
		MX_ADC_HANDLE.Init.EOCSelection = ENABLE;
		MX_ADC_HANDLE.Init.LowPowerAutoWait = DISABLE;
		MX_ADC_HANDLE.Init.LowPowerAutoPowerOff = DISABLE;
		MX_ADC_HANDLE.Init.Overrun = ADC_OVR_DATA_PRESERVED;

		/*##-2- Configure ADC regular channel ######################################*/
		MX_ADC_CH_CONF.Rank = ADC_RANK_CHANNEL_NUMBER;
		if (T_Charge > 71)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
		else if (T_Charge > 55)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;
		else if (T_Charge > 41)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
		else if (T_Charge > 28)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_41CYCLES_5;
		else if (T_Charge > 13)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;
		else if (T_Charge > 7)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
		else if (T_Charge > 1)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
		else
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;

		// ##-2- Save current GPIO ##########################################
		MX_TEMP_MODER = MX_ADC_PORT_X->MODER;
		MX_TEMP_OTYPER = MX_ADC_PORT_X->OTYPER;
		MX_TEMP_OSPEEDR = MX_ADC_PORT_X->OSPEEDR;
		MX_TEMP_PUPDR = MX_ADC_PORT_X->PUPDR;
		MX_TEMP_AFRH = MX_ADC_PORT_X->AFR[0];
		MX_TEMP_AFRL = MX_ADC_PORT_X->AFR[1];

		// ##-2- Configure peripheral GPIO ##########################################
		MX_GPIO_INIT_STRUCT.Pin = 1 << MX_ADC_PIN_X;
		MX_GPIO_INIT_STRUCT.Mode = GPIO_MODE_ANALOG;
		MX_GPIO_INIT_STRUCT.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(MX_ADC_PORT_X, &MX_GPIO_INIT_STRUCT);

		HAL_ADC_Init(&MX_ADC_HANDLE);
	}


	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal = 0;

		if (HAL_ADC_ConfigChannel(&MX_ADC_HANDLE, &MX_ADC_CH_CONF) == HAL_OK)
		{
			if (HAL_ADC_Start(&MX_ADC_HANDLE) == HAL_OK)
			{
				if (HAL_ADC_PollForConversion(&MX_ADC_HANDLE, 100) == HAL_OK)
				{
		iRetVal = HAL_ADC_GetValue(&MX_ADC_HANDLE);
		if(!Sample_Mode)
			iRetVal >>= 4;
				}
			}
		}
		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{

		MX_GPIO_INIT_STRUCT.Pin = 1 << MX_ADC_PIN_X;
		MX_GPIO_INIT_STRUCT.Mode = (MX_TEMP_MODER >> (MX_ADC_PIN_X << 1)) & 0x03;
		MX_GPIO_INIT_STRUCT.Mode |= (((MX_TEMP_OTYPER >> MX_ADC_PIN_X) & 0x01) << 2);
		MX_GPIO_INIT_STRUCT.Speed |= (MX_TEMP_OSPEEDR >> (MX_ADC_PIN_X << 1)) & 0x03;
		MX_GPIO_INIT_STRUCT.Pull = (MX_TEMP_PUPDR >> (MX_ADC_PIN_X << 1)) & 0x03;

		if(MX_ADC_PIN_X > 0x07)
		{
			MX_ADC_PIN_X -= 7;
			MX_GPIO_INIT_STRUCT.Alternate = (MX_TEMP_AFRH >> (MX_ADC_PIN_X << 2)) & 0x0f;
		} else {
			MX_GPIO_INIT_STRUCT.Alternate = (MX_TEMP_AFRL >> (MX_ADC_PIN_X << 2)) & 0x0f;
		}

		HAL_GPIO_Init(MX_ADC_PORT_X, &MX_GPIO_INIT_STRUCT);

		MX_ADC_CH_CONF.Rank = ADC_RANK_NONE;
		HAL_ADC_ConfigChannel(&MX_ADC_HANDLE, &MX_ADC_CH_CONF);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	#endif // MX_ADC_TOUCH

#elif defined MX_ADC_TYPE_3
/*******************************************************************************************
* ADC Type 3 Supported Devices  STM32F3
*******************************************************************************************/
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			case 1:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 0; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_1; break;
			case 2:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 1; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_2; break;
			case 3:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 2; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_3; break;
			case 4:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 3; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_4; break;
			case 5:  MX_ADC_PORT_X = GPIOF; MX_ADC_PIN_X = 4; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_5; break;
			case 6:  MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 0; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_6; break;
			case 7:  MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 1; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_7; break;
			case 8:  MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 2; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_8; break;
			case 9:  MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 3; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_9; break;
			//case 10: MX_ADC_PORT_X = GPIOF; MX_ADC_PIN_X = 2; break;
			case 11:  MX_ADC_PORT_X = GPIOB; MX_ADC_PIN_X = 0; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_11; break;
			case 12:  MX_ADC_PORT_X = GPIOB; MX_ADC_PIN_X = 1; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_12; break;
			case 13:  MX_ADC_PORT_X = GPIOB; MX_ADC_PIN_X = 13; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_13; break;
			//case 14:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 3; break;
			//case 15:  MX_ADC_PORT_X = GPIOF; MX_ADC_PIN_X = 4; break;
			//default:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 0; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_0; break;
		}

		/*##-1- Configure the ADC peripheral #######################################*/

		#if (MX_ADC_NUM == 1)
			__HAL_RCC_ADC1_CLK_ENABLE();
			MX_ADC_HANDLE.Instance = ADC1;
		#endif

		#if (MX_ADC_NUM == 2)
			__HAL_RCC_ADC2_CLK_ENABLE();
			MX_ADC_HANDLE.Instance = ADC2;
		#endif

		#if (MX_ADC_NUM == 3)
			__HAL_RCC_ADC3_CLK_ENABLE();
			MX_ADC_HANDLE.Instance = ADC3;
		#endif

		if(Conv_Speed == 1)
			MX_ADC_HANDLE.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV1;
		else if (Conv_Speed == 2)
			MX_ADC_HANDLE.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
		else
			MX_ADC_HANDLE.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;

		MX_ADC_HANDLE.Init.Resolution = ADC_RESOLUTION_12B;
		MX_ADC_HANDLE.Init.ScanConvMode = DISABLE;
		MX_ADC_HANDLE.Init.ContinuousConvMode = DISABLE;
		MX_ADC_HANDLE.Init.DiscontinuousConvMode = DISABLE;
		MX_ADC_HANDLE.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
		MX_ADC_HANDLE.Init.ExternalTrigConv = ADC_SOFTWARE_START;
		MX_ADC_HANDLE.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		MX_ADC_HANDLE.Init.DMAContinuousRequests = DISABLE;
		MX_ADC_HANDLE.Init.EOCSelection = ENABLE;
		MX_ADC_HANDLE.Init.LowPowerAutoWait = DISABLE;
		// MX_ADC_HANDLE.Init.LowPowerAutoPowerOff = DISABLE;
		MX_ADC_HANDLE.Init.Overrun = ADC_OVR_DATA_PRESERVED;

		/*##-2- Configure ADC regular channel ######################################*/
		MX_ADC_CH_CONF.Rank = ADC_REGULAR_RANK_1;

		if (T_Charge > 300)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_601CYCLES_5;
		else if (T_Charge > 120)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_181CYCLES_5;
		else if (T_Charge > 40)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_61CYCLES_5;
		else if (T_Charge > 13)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_19CYCLES_5;
		else if (T_Charge > 5)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
		else if (T_Charge > 2)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_4CYCLES_5;
		else if (T_Charge > 1)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
		else
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;

  		// ##-2- Save current GPIO ##########################################
		MX_TEMP_MODER = MX_ADC_PORT_X->MODER;
		MX_TEMP_OTYPER = MX_ADC_PORT_X->OTYPER;
		MX_TEMP_OSPEEDR = MX_ADC_PORT_X->OSPEEDR;
		MX_TEMP_PUPDR = MX_ADC_PORT_X->PUPDR;
		MX_TEMP_AFRH = MX_ADC_PORT_X->AFR[0];
		MX_TEMP_AFRL = MX_ADC_PORT_X->AFR[1];

		// ##-2- Configure peripheral GPIO ##########################################
		MX_GPIO_INIT_STRUCT.Pin = 1 << MX_ADC_PIN_X;
		MX_GPIO_INIT_STRUCT.Mode = GPIO_MODE_ANALOG;
		MX_GPIO_INIT_STRUCT.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(MX_ADC_PORT_X, &MX_GPIO_INIT_STRUCT);

		HAL_ADC_Init(&MX_ADC_HANDLE);
	}


	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal = 0;

		if (HAL_ADC_ConfigChannel(&MX_ADC_HANDLE, &MX_ADC_CH_CONF) == HAL_OK)
		{
			if (HAL_ADC_Start(&MX_ADC_HANDLE) == HAL_OK)
			{
				if (HAL_ADC_PollForConversion(&MX_ADC_HANDLE, 100) == HAL_OK)
				{
					iRetVal = HAL_ADC_GetValue(&MX_ADC_HANDLE);
					if(!Sample_Mode)
						iRetVal >>= 4;
				}
			}
		}
		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{

		MX_GPIO_INIT_STRUCT.Pin = 1 << MX_ADC_PIN_X;
		MX_GPIO_INIT_STRUCT.Mode = (MX_TEMP_MODER >> (MX_ADC_PIN_X << 1)) & 0x03;
		MX_GPIO_INIT_STRUCT.Mode |= (((MX_TEMP_OTYPER >> MX_ADC_PIN_X) & 0x01) << 2);
		MX_GPIO_INIT_STRUCT.Speed |= (MX_TEMP_OSPEEDR >> (MX_ADC_PIN_X << 1)) & 0x03;
		MX_GPIO_INIT_STRUCT.Pull = (MX_TEMP_PUPDR >> (MX_ADC_PIN_X << 1)) & 0x03;

		if(MX_ADC_PIN_X > 0x07)
		{
			MX_ADC_PIN_X -= 7;
			MX_GPIO_INIT_STRUCT.Alternate = (MX_TEMP_AFRH >> (MX_ADC_PIN_X << 2)) & 0x0f;
		} else {
			MX_GPIO_INIT_STRUCT.Alternate = (MX_TEMP_AFRL >> (MX_ADC_PIN_X << 2)) & 0x0f;
		}

		HAL_GPIO_Init(MX_ADC_PORT_X, &MX_GPIO_INIT_STRUCT);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	#endif // MX_ADC_TOUCH


#elif defined MX_ADC_TYPE_4
/*******************************************************************************************
* ADC Type 4 Supported Devices  STM32F1
*******************************************************************************************/
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			case 0:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 0; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_0; break;
			case 1:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 1; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_1; break;
			case 2:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 2; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_2; break;
			case 3:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 3; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_3; break;
			case 4:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 4; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_4; break;
			case 5:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 5; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_5; break;
			case 6:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 6; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_6; break;
			case 7:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 7; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_7; break;
			case 8:  MX_ADC_PORT_X = GPIOB; MX_ADC_PIN_X = 0; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_8; break;
			case 9:  MX_ADC_PORT_X = GPIOB; MX_ADC_PIN_X = 1; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_9; break;
			case 10: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 0; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_10; break;
			case 11: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 1; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_11; break;
			case 12: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 2; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_12; break;
			case 13: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 3; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_13; break;
			case 14: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 4; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_14; break;
			case 15: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 5; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_15; break;
		}

		/*##-1- Configure the ADC peripheral #######################################*/

		#if (MX_ADC_NUM == 1)
			__HAL_RCC_ADC1_CLK_ENABLE();
			MX_ADC_HANDLE.Instance = ADC1;
		#endif

		#if (MX_ADC_NUM == 2)
			__HAL_RCC_ADC2_CLK_ENABLE();
			MX_ADC_HANDLE.Instance = ADC2;
		#endif

		#if (MX_ADC_NUM == 3)
			__HAL_RCC_ADC3_CLK_ENABLE();
			MX_ADC_HANDLE.Instance = ADC3;
		#endif

		// MX_ADC_HANDLE.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;	// ?
		// MX_ADC_HANDLE.Init.Resolution = ADC_RESOLUTION_12B;
		MX_ADC_HANDLE.Init.ScanConvMode = DISABLE;
		MX_ADC_HANDLE.Init.ContinuousConvMode = DISABLE;
		MX_ADC_HANDLE.Init.DiscontinuousConvMode = DISABLE;
		// MX_ADC_HANDLE.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
		MX_ADC_HANDLE.Init.ExternalTrigConv = ADC_SOFTWARE_START;
		MX_ADC_HANDLE.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		// MX_ADC_HANDLE.Init.DMAContinuousRequests = DISABLE;
		// MX_ADC_HANDLE.Init.EOCSelection = ENABLE;
		// MX_ADC_HANDLE.Init.LowPowerAutoWait = DISABLE;
		// MX_ADC_HANDLE.Init.LowPowerAutoPowerOff = DISABLE;
		// MX_ADC_HANDLE.Init.Overrun = ADC_OVR_DATA_PRESERVED;			// ?

		/*##-2- Configure ADC regular channel ######################################*/
		MX_ADC_CH_CONF.Rank = 1;	// ADC_RANK_CHANNEL_NUMBER;

		if (T_Charge > 71)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
		else if (T_Charge > 55)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;
		else if (T_Charge > 41)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
		else if (T_Charge > 28)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_41CYCLES_5;
		else if (T_Charge > 13)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;
		else if (T_Charge > 7)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
		else if (T_Charge > 1)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
		else
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;

  		// ##-2- Save current GPIO ##########################################
		/*******************************************
		MX_TEMP_MODER = MX_ADC_PORT_X->MODER;
		MX_TEMP_OTYPER = MX_ADC_PORT_X->OTYPER;
		MX_TEMP_OSPEEDR = MX_ADC_PORT_X->OSPEEDR;
		MX_TEMP_PUPDR = MX_ADC_PORT_X->PUPDR;
		MX_TEMP_AFRH = MX_ADC_PORT_X->AFR[0];
		MX_TEMP_AFRL = MX_ADC_PORT_X->AFR[1];
		*******************************************/

		// ##-2- Configure peripheral GPIO ##########################################
		MX_GPIO_INIT_STRUCT.Pin = 1 << MX_ADC_PIN_X;
		MX_GPIO_INIT_STRUCT.Mode = GPIO_MODE_ANALOG;
		MX_GPIO_INIT_STRUCT.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(MX_ADC_PORT_X, &MX_GPIO_INIT_STRUCT);

		HAL_ADC_Init(&MX_ADC_HANDLE);
	}


	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal = 0;

		if (HAL_ADC_ConfigChannel(&MX_ADC_HANDLE, &MX_ADC_CH_CONF) == HAL_OK)
		{
			if (HAL_ADC_Start(&MX_ADC_HANDLE) == HAL_OK)
			{
				if (HAL_ADC_PollForConversion(&MX_ADC_HANDLE, 100) == HAL_OK)
				{
					iRetVal = HAL_ADC_GetValue(&MX_ADC_HANDLE);
					if(!Sample_Mode)
						iRetVal >>= 4;
				}
			}
		}
		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		/*******************************************
		MX_GPIO_INIT_STRUCT.Pin = 1 << MX_ADC_PIN_X;
		MX_GPIO_INIT_STRUCT.Mode = (MX_TEMP_MODER >> (MX_ADC_PIN_X << 1)) & 0x03;
		MX_GPIO_INIT_STRUCT.Mode |= (((MX_TEMP_OTYPER >> MX_ADC_PIN_X) & 0x01) << 2);
		MX_GPIO_INIT_STRUCT.Speed |= (MX_TEMP_OSPEEDR >> (MX_ADC_PIN_X << 1)) & 0x03;
		MX_GPIO_INIT_STRUCT.Pull = (MX_TEMP_PUPDR >> (MX_ADC_PIN_X << 1)) & 0x03;

		if(MX_ADC_PIN_X > 0x07)
		{
			MX_ADC_PIN_X -= 7;
			MX_GPIO_INIT_STRUCT.Alternate = (MX_TEMP_AFRH >> (MX_ADC_PIN_X << 2)) & 0x0f;
		} else {
			MX_GPIO_INIT_STRUCT.Alternate = (MX_TEMP_AFRL >> (MX_ADC_PIN_X << 2)) & 0x0f;
		}

		HAL_GPIO_Init(MX_ADC_PORT_X, &MX_GPIO_INIT_STRUCT);
		*******************************************/
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	#endif // MX_ADC_TOUCH

#elif defined MX_ADC_TYPE_5
/*******************************************************************************************
* ADC Type 5 Supported Devices  STM32F7
*******************************************************************************************/
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			case 0:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 0; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_0; break;
			case 1:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 1; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_1; break;
			case 2:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 2; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_2; break;
			case 3:  MX_ADC_PORT_X = GPIOA; MX_ADC_PIN_X = 3; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_3; break;
			case 4:  MX_ADC_PORT_X = GPIOF; MX_ADC_PIN_X = 6; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_4; break;
			case 5:  MX_ADC_PORT_X = GPIOF; MX_ADC_PIN_X = 7; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_5; break;
			case 6:  MX_ADC_PORT_X = GPIOF; MX_ADC_PIN_X = 8; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_6; break;
			case 7:  MX_ADC_PORT_X = GPIOF; MX_ADC_PIN_X = 9; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_7; break;
			case 8:  MX_ADC_PORT_X = GPIOF; MX_ADC_PIN_X = 10; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_8; break;
			case 9:  MX_ADC_PORT_X = GPIOF; MX_ADC_PIN_X = 3; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_9; break;
			case 10: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 0; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_10; break;
			case 11: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 1; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_11; break;
			case 12: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 2; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_12; break;
			case 13: MX_ADC_PORT_X = GPIOC; MX_ADC_PIN_X = 3; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_12; break;
			case 14: MX_ADC_PORT_X = GPIOF; MX_ADC_PIN_X = 4; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_14; break;
			case 15: MX_ADC_PORT_X = GPIOF; MX_ADC_PIN_X = 5; MX_ADC_CH_CONF.Channel = ADC_CHANNEL_15; break;
		}

		/*##-1- Configure the ADC peripheral #######################################*/

		#if (MX_ADC_NUM == 1)
			__HAL_RCC_ADC1_CLK_ENABLE();
			MX_ADC_HANDLE.Instance = ADC1;
		#endif

		#if (MX_ADC_NUM == 2)
			__HAL_RCC_ADC2_CLK_ENABLE();
			MX_ADC_HANDLE.Instance = ADC2;
		#endif

		#if (MX_ADC_NUM == 3)
			__HAL_RCC_ADC3_CLK_ENABLE();
			MX_ADC_HANDLE.Instance = ADC3;
		#endif

		if (Conv_Speed == 2)
			MX_ADC_HANDLE.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
		else if (Conv_Speed == 4)
			MX_ADC_HANDLE.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
		else if (Conv_Speed == 6)
			MX_ADC_HANDLE.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV6;
		else
			MX_ADC_HANDLE.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;

		MX_ADC_HANDLE.Init.Resolution = ADC_RESOLUTION_12B;
		MX_ADC_HANDLE.Init.ScanConvMode = DISABLE;
		MX_ADC_HANDLE.Init.ContinuousConvMode = DISABLE;
		MX_ADC_HANDLE.Init.DiscontinuousConvMode = DISABLE;
		MX_ADC_HANDLE.Init.NbrOfDiscConversion = 0;
		MX_ADC_HANDLE.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
		MX_ADC_HANDLE.Init.ExternalTrigConv = ADC_SOFTWARE_START;
		MX_ADC_HANDLE.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		MX_ADC_HANDLE.Init.NbrOfConversion = 1;
		MX_ADC_HANDLE.Init.DMAContinuousRequests = DISABLE;
		MX_ADC_HANDLE.Init.EOCSelection = ENABLE;

		/*##-2- Configure ADC regular channel ######################################*/
		MX_ADC_CH_CONF.Rank = 1;
		MX_ADC_CH_CONF.Offset = 0;
		if (T_Charge > 144)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_480CYCLES;
		else if (T_Charge > 112)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_144CYCLES;
		else if (T_Charge > 84)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_112CYCLES;
		else if (T_Charge > 56)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_84CYCLES;
		else if (T_Charge > 28)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_56CYCLES;
		else if (T_Charge > 15)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_28CYCLES;
		else if (T_Charge > 3)
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_15CYCLES;
		else
			MX_ADC_CH_CONF.SamplingTime = ADC_SAMPLETIME_3CYCLES;

		// ##-2- Save current GPIO ##########################################
		MX_TEMP_MODER = MX_ADC_PORT_X->MODER;
		MX_TEMP_OTYPER = MX_ADC_PORT_X->OTYPER;
		MX_TEMP_OSPEEDR = MX_ADC_PORT_X->OSPEEDR;
		MX_TEMP_PUPDR = MX_ADC_PORT_X->PUPDR;
		MX_TEMP_AFRH = MX_ADC_PORT_X->AFR[0];
		MX_TEMP_AFRL = MX_ADC_PORT_X->AFR[1];

		// ##-2- Configure peripheral GPIO ##########################################
		MX_GPIO_INIT_STRUCT.Pin = 1 << MX_ADC_PIN_X;
		MX_GPIO_INIT_STRUCT.Mode = GPIO_MODE_ANALOG;
		MX_GPIO_INIT_STRUCT.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(MX_ADC_PORT_X, &MX_GPIO_INIT_STRUCT);

		HAL_ADC_Init(&MX_ADC_HANDLE);
	}


	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal = 0;

		if (HAL_ADC_ConfigChannel(&MX_ADC_HANDLE, &MX_ADC_CH_CONF) == HAL_OK)
		{
			if (HAL_ADC_Start(&MX_ADC_HANDLE) == HAL_OK)
			{
				if (HAL_ADC_PollForConversion(&MX_ADC_HANDLE, 100) == HAL_OK)
				{
					iRetVal = HAL_ADC_GetValue(&MX_ADC_HANDLE);
					if(!Sample_Mode)
						iRetVal >>= 4;
				}
			}
		}
		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{

		MX_GPIO_INIT_STRUCT.Pin = 1 << MX_ADC_PIN_X;
		MX_GPIO_INIT_STRUCT.Mode = (MX_TEMP_MODER >> (MX_ADC_PIN_X << 1)) & 0x03;
		MX_GPIO_INIT_STRUCT.Mode |= (((MX_TEMP_OTYPER >> MX_ADC_PIN_X) & 0x01) << 2);
		MX_GPIO_INIT_STRUCT.Speed |= (MX_TEMP_OSPEEDR >> (MX_ADC_PIN_X << 1)) & 0x03;
		MX_GPIO_INIT_STRUCT.Pull = (MX_TEMP_PUPDR >> (MX_ADC_PIN_X << 1)) & 0x03;

		if(MX_ADC_PIN_X > 0x07)
		{
			MX_ADC_PIN_X -= 7;
			MX_GPIO_INIT_STRUCT.Alternate = (MX_TEMP_AFRH >> (MX_ADC_PIN_X << 2)) & 0x0f;
		} else {
			MX_GPIO_INIT_STRUCT.Alternate = (MX_TEMP_AFRL >> (MX_ADC_PIN_X << 2)) & 0x0f;
		}

		HAL_GPIO_Init(MX_ADC_PORT_X, &MX_GPIO_INIT_STRUCT);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	#endif // MX_ADC_TOUCH
#endif

