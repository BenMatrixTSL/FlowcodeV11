// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BE2FC147DD578D22BE796589A9E29B61C0186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF527431C11047852D5C8461630D46557B204BC6D13B1607ED9D03C62EE9304F7DAA6C13D1A301A573775182D7B0957EEBD0E61DF89BA16433926650D0F2DC34A7A1C3C63738F79AF2C7EEC4FB2D5E492F8EFA62DE588905CEC549D34A0D5AD11F31B16651A9599190DCBA355B1DDCC71A1787A37186E3BB9C9E4565E63FDA312627DD474674123A97D
// REVISION: 1.0
// GUID: DF6F3D07-155F-4A2D-9C51-568611AFE3FA
// DATE: 08\08\2022
// DIR: CAL\STARM\STARM_CAL_DAC.c
/*********************************************************************
 *                  Flowcode CAL DAC File
 *
 * File: PIC16BIT_CAL_DAC.c
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
 * 310516 | BR | Created
 */


#define MX_DAC_CHANNEL_X		CAL_APPEND(MX_DAC_CHANNEL_, MX_DAC_NUM)
#define MX_DAC_VREF_X			CAL_APPEND(MX_DAC_VREF_, MX_DAC_NUM)


CALFUNCTION(void, FC_CAL_DAC_Enable_, (void));
CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output));
CALFUNCTION(void, FC_CAL_DAC_Disable_, (void));

/* DAC handler declaration */
DAC_HandleTypeDef		MX_DAC_HANDLE;
DAC_ChannelConfTypeDef	MX_DAC_CH_CONF;


// DAC Type 1 Supported Devices ************************************************************
// STM32F0 STM32F4 STM32F7
// Up to 2 channels
// CHANNEL 1 = DAC1_1 with buffer option (disabled)
// CHANNEL 2 = DAC1_2 with buffer option (disabled)
// *******************************************************************************************/

#ifdef MX_DAC_TYPE_1

  #if (MX_DAC_CHANNEL_X == 1)

	CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
	{
		GPIO_InitTypeDef		MX_GPIO_INIT_STRUCT;

#if defined(STM32F4) || defined(STM32F7)
		__HAL_RCC_DAC_CLK_ENABLE();
#else
		__HAL_RCC_DAC1_CLK_ENABLE();
#endif
		
		MX_GPIO_INIT_STRUCT.Pin = GPIO_PIN_4;
		MX_GPIO_INIT_STRUCT.Mode = GPIO_MODE_ANALOG;
		MX_GPIO_INIT_STRUCT.Pull = GPIO_NOPULL;
		MX_GPIO_INIT_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &MX_GPIO_INIT_STRUCT);
		
#if defined(STM32F4) || defined(STM32F7)
		MX_DAC_HANDLE.Instance = DAC;
#else
		MX_DAC_HANDLE.Instance = DAC1;
#endif
		HAL_DAC_Init(&MX_DAC_HANDLE);

		MX_DAC_CH_CONF.DAC_Trigger = DAC_TRIGGER_NONE;
		MX_DAC_CH_CONF.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
		HAL_DAC_ConfigChannel(&MX_DAC_HANDLE, &MX_DAC_CH_CONF, DAC_CHANNEL_1);
	}


	CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output))
	{
#if defined(STM32F4) || defined(STM32F7)
		MX_DAC_HANDLE.Instance = DAC;
#else
		MX_DAC_HANDLE.Instance = DAC1;
#endif
		HAL_DAC_SetValue(&MX_DAC_HANDLE, DAC_CHANNEL_1, DAC_ALIGN_12B_R, Output);
		HAL_DAC_Start(&MX_DAC_HANDLE, DAC_CHANNEL_1);
	}


	CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
	{
		GPIO_InitTypeDef		MX_GPIO_INIT_STRUCT;
		
		MX_GPIO_INIT_STRUCT.Pin = GPIO_PIN_4;
		MX_GPIO_INIT_STRUCT.Mode = GPIO_MODE_INPUT;
		MX_GPIO_INIT_STRUCT.Pull = GPIO_NOPULL;
		MX_GPIO_INIT_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &MX_GPIO_INIT_STRUCT);
	}

  #endif

  #if (MX_DAC_CHANNEL_X == 2)

	CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
	{
		GPIO_InitTypeDef		MX_GPIO_INIT_STRUCT;
		
#if defined(STM32F4) || defined(STM32F7)
		__HAL_RCC_DAC_CLK_ENABLE();
#else
		__HAL_RCC_DAC1_CLK_ENABLE();
#endif
		
		MX_GPIO_INIT_STRUCT.Pin = GPIO_PIN_5;
		MX_GPIO_INIT_STRUCT.Mode = GPIO_MODE_ANALOG;
		MX_GPIO_INIT_STRUCT.Pull = GPIO_NOPULL;
		MX_GPIO_INIT_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &MX_GPIO_INIT_STRUCT);

#if defined(STM32F4) || defined(STM32F7)
		MX_DAC_HANDLE.Instance = DAC;
#else
		MX_DAC_HANDLE.Instance = DAC1;
#endif	
		HAL_DAC_Init(&MX_DAC_HANDLE);

		MX_DAC_CH_CONF.DAC_Trigger = DAC_TRIGGER_NONE;
		MX_DAC_CH_CONF.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
		HAL_DAC_ConfigChannel(&MX_DAC_HANDLE, &MX_DAC_CH_CONF, DAC_CHANNEL_2);
	}


	CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output))
	{
#if defined(STM32F4) || defined(STM32F7)
		MX_DAC_HANDLE.Instance = DAC;
#else
		MX_DAC_HANDLE.Instance = DAC1;
#endif
		HAL_DAC_SetValue(&MX_DAC_HANDLE, DAC_CHANNEL_2, DAC_ALIGN_12B_R, Output);
		HAL_DAC_Start(&MX_DAC_HANDLE, DAC_CHANNEL_2);
	}


	CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
	{
		GPIO_InitTypeDef		MX_GPIO_INIT_STRUCT;
		
		MX_GPIO_INIT_STRUCT.Pin = GPIO_PIN_5;
		MX_GPIO_INIT_STRUCT.Mode = GPIO_MODE_INPUT;
		MX_GPIO_INIT_STRUCT.Pull = GPIO_NOPULL;
		MX_GPIO_INIT_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &MX_GPIO_INIT_STRUCT);
	}

  #endif
  
#endif


// DAC Type 3 Supported Devices ************************************************************
// STM32F3
// Up to 3 channels
// CHANNEL 1 = DAC1_1 with buffer option (disabled)
// CHANNEL 2 = DAC1_2 with switch option (enabled)
// CHANNEL 3 = DAC2_1 with switch option (enaled)
// *******************************************************************************************/

#ifdef MX_DAC_TYPE_3

  #if (MX_DAC_CHANNEL_X == 1)

	CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
	{
		GPIO_InitTypeDef		MX_GPIO_INIT_STRUCT;

		__HAL_RCC_DAC1_CLK_ENABLE();
		
		MX_GPIO_INIT_STRUCT.Pin = GPIO_PIN_4;
		MX_GPIO_INIT_STRUCT.Mode = GPIO_MODE_ANALOG;
		MX_GPIO_INIT_STRUCT.Pull = GPIO_NOPULL;
		MX_GPIO_INIT_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &MX_GPIO_INIT_STRUCT);
		
		MX_DAC_HANDLE.Instance = DAC1;
		HAL_DAC_Init(&MX_DAC_HANDLE);

		MX_DAC_CH_CONF.DAC_Trigger = DAC_TRIGGER_NONE;
		MX_DAC_CH_CONF.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
		HAL_DAC_ConfigChannel(&MX_DAC_HANDLE, &MX_DAC_CH_CONF, DAC_CHANNEL_1);
	}


	CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output))
	{
		MX_DAC_HANDLE.Instance = DAC1;
		HAL_DAC_SetValue(&MX_DAC_HANDLE, DAC_CHANNEL_1, DAC_ALIGN_12B_R, Output);
		HAL_DAC_Start(&MX_DAC_HANDLE, DAC_CHANNEL_1);
	}


	CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
	{
		GPIO_InitTypeDef		MX_GPIO_INIT_STRUCT;
		
		MX_GPIO_INIT_STRUCT.Pin = GPIO_PIN_4;
		MX_GPIO_INIT_STRUCT.Mode = GPIO_MODE_INPUT;
		MX_GPIO_INIT_STRUCT.Pull = GPIO_NOPULL;
		MX_GPIO_INIT_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &MX_GPIO_INIT_STRUCT);
	}

  #endif

  #if (MX_DAC_CHANNEL_X == 2)

	CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
	{
		GPIO_InitTypeDef		MX_GPIO_INIT_STRUCT;
		
		__HAL_RCC_DAC1_CLK_ENABLE();
		
		MX_GPIO_INIT_STRUCT.Pin = GPIO_PIN_5;
		MX_GPIO_INIT_STRUCT.Mode = GPIO_MODE_ANALOG;
		MX_GPIO_INIT_STRUCT.Pull = GPIO_NOPULL;
		MX_GPIO_INIT_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &MX_GPIO_INIT_STRUCT);

		MX_DAC_HANDLE.Instance = DAC1;		
		HAL_DAC_Init(&MX_DAC_HANDLE);

		MX_DAC_CH_CONF.DAC_Trigger = DAC_TRIGGER_NONE;
		MX_DAC_CH_CONF.DAC_OutputSwitch = DAC_OUTPUTSWITCH_ENABLE;
		HAL_DAC_ConfigChannel(&MX_DAC_HANDLE, &MX_DAC_CH_CONF, DAC_CHANNEL_2);
	}


	CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output))
	{
		MX_DAC_HANDLE.Instance = DAC1;
		HAL_DAC_SetValue(&MX_DAC_HANDLE, DAC_CHANNEL_2, DAC_ALIGN_12B_R, Output);
		HAL_DAC_Start(&MX_DAC_HANDLE, DAC_CHANNEL_2);
	}


	CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
	{
		GPIO_InitTypeDef		MX_GPIO_INIT_STRUCT;
		
		MX_GPIO_INIT_STRUCT.Pin = GPIO_PIN_5;
		MX_GPIO_INIT_STRUCT.Mode = GPIO_MODE_INPUT;
		MX_GPIO_INIT_STRUCT.Pull = GPIO_NOPULL;
		MX_GPIO_INIT_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &MX_GPIO_INIT_STRUCT);
	}

  #endif

  #if (MX_DAC_CHANNEL_X == 3)

	CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
	{
		GPIO_InitTypeDef		MX_GPIO_INIT_STRUCT;
		
		__HAL_RCC_DAC2_CLK_ENABLE();
		
		MX_GPIO_INIT_STRUCT.Pin = GPIO_PIN_6;
		MX_GPIO_INIT_STRUCT.Mode = GPIO_MODE_ANALOG;
		MX_GPIO_INIT_STRUCT.Pull = GPIO_NOPULL;
		MX_GPIO_INIT_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &MX_GPIO_INIT_STRUCT);

		MX_DAC_HANDLE.Instance = DAC2;		
		HAL_DAC_Init(&MX_DAC_HANDLE);

		MX_DAC_CH_CONF.DAC_Trigger = DAC_TRIGGER_NONE;
		MX_DAC_CH_CONF.DAC_OutputSwitch = DAC_OUTPUTSWITCH_ENABLE;
		HAL_DAC_ConfigChannel(&MX_DAC_HANDLE, &MX_DAC_CH_CONF, DAC_CHANNEL_1);
	}


	CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output))
	{
		MX_DAC_HANDLE.Instance = DAC2;
		HAL_DAC_SetValue(&MX_DAC_HANDLE, DAC_CHANNEL_1, DAC_ALIGN_12B_R, Output);
		HAL_DAC_Start(&MX_DAC_HANDLE, DAC_CHANNEL_1);
	}


	CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
	{
		GPIO_InitTypeDef		MX_GPIO_INIT_STRUCT;
		
		MX_GPIO_INIT_STRUCT.Pin = GPIO_PIN_6;
		MX_GPIO_INIT_STRUCT.Mode = GPIO_MODE_INPUT;
		MX_GPIO_INIT_STRUCT.Pull = GPIO_NOPULL;
		MX_GPIO_INIT_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &MX_GPIO_INIT_STRUCT);
		
		__HAL_RCC_DAC2_CLK_DISABLE();
	}

  #endif
  
#endif


