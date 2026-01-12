// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BE51709219B24776899D8775E8924234175E2BB879229DC221599C110569B5B7A99A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5EEF2B8CBCD466BE5A2E3A454CEFD5F3A12EEC636DE5FCE0BEEAF9382F2FBFF4B67605F30B58C3C408F0CCF2D08C2F18EDEF40CC200B06FCE979C8F4B338862BC240E5F36F4B2BFB95718654573363A600C6F71DB1518FDEB549D34A0D5AD11F331961C1FAB67FB8C9269620B92A5ABBDC6C0EDFC73DEA11C79849CDE32E3BB2BC44AB45AA6BFFC2C
// REVISION: 1.0
// GUID: 01370F46-1953-4638-AF61-8D96F35B9284
// DATE: 08\08\2022
// DIR: CAL\STARM\STARM_CAL_CLOCKS.c
/*********************************************************************
 *                  Flowcode CAL CLOCKS File
 *
 * File: STARM_CAL_CLOCKS.c
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
 * 121016 | LM | Created

 *
 */

#if RCC_AHB_PRE < 2
	#define RCC_AHB_PRE_DIVX RCC_SYSCLK_DIV1
#elif RCC_AHB_PRE < 4
	#define RCC_AHB_PRE_DIVX RCC_SYSCLK_DIV2
#elif RCC_AHB_PRE < 8
	#define RCC_AHB_PRE_DIVX RCC_SYSCLK_DIV4
#elif RCC_AHB_PRE < 16
	#define RCC_AHB_PRE_DIVX RCC_SYSCLK_DIV8
#elif RCC_AHB_PRE < 32
	#define RCC_AHB_PRE_DIVX RCC_SYSCLK_DIV16
#elif RCC_AHB_PRE < 64
	#define RCC_AHB_PRE_DIVX RCC_SYSCLK_DIV32
#elif RCC_AHB_PRE < 128
	#define RCC_AHB_PRE_DIVX RCC_SYSCLK_DIV64
#elif RCC_AHB_PRE < 256
	#define RCC_AHB_PRE_DIVX RCC_SYSCLK_DIV128
#elif RCC_AHB_PRE < 512
	#define RCC_AHB_PRE_DIVX RCC_SYSCLK_DIV256
#else
	#define RCC_AHB_PRE_DIVX RCC_SYSCLK_DIV512
#endif

#if RCC_APB1_PRE < 2
	#define RCC_APB1_PRE_DIVX RCC_HCLK_DIV1
#elif RCC_APB1_PRE < 4
	#define RCC_APB1_PRE_DIVX RCC_HCLK_DIV2
#elif RCC_APB1_PRE < 8
	#define RCC_APB1_PRE_DIVX RCC_HCLK_DIV4
#elif RCC_APB1_PRE < 16
	#define RCC_APB1_PRE_DIVX RCC_HCLK_DIV8
#else
	#define RCC_APB1_PRE_DIVX RCC_HCLK_DIV16
#endif

#if RCC_APB2_PRE < 2
	#define RCC_APB2_PRE_DIVX RCC_HCLK_DIV1
#elif RCC_APB2_PRE < 4
	#define RCC_APB2_PRE_DIVX RCC_HCLK_DIV2
#elif RCC_APB2_PRE < 8
	#define RCC_APB2_PRE_DIVX RCC_HCLK_DIV4
#elif RCC_APB2_PRE < 16
	#define RCC_APB2_PRE_DIVX RCC_HCLK_DIV8
#else
	#define RCC_APB2_PRE_DIVX RCC_HCLK_DIV16
#endif

#if defined(RCC_PLL_MUL)
#if RCC_PLL_MUL > 15
	#define RCC_PLL_MULX RCC_PLL_MUL16
#elif RCC_PLL_MUL > 14
	#define RCC_PLL_MULX RCC_PLL_MUL15
#elif RCC_PLL_MUL > 13
	#define RCC_PLL_MULX RCC_PLL_MUL14
#elif RCC_PLL_MUL > 12
	#define RCC_PLL_MULX RCC_PLL_MUL13
#elif RCC_PLL_MUL > 11
	#define RCC_PLL_MULX RCC_PLL_MUL12
#elif RCC_PLL_MUL > 10
	#define RCC_PLL_MULX RCC_PLL_MUL11
#elif RCC_PLL_MUL > 9
	#define RCC_PLL_MULX RCC_PLL_MUL10
#elif RCC_PLL_MUL > 8
	#define RCC_PLL_MULX RCC_PLL_MUL9
#elif RCC_PLL_MUL > 7
	#define RCC_PLL_MULX RCC_PLL_MUL8
#elif RCC_PLL_MUL > 6
	#define RCC_PLL_MULX RCC_PLL_MUL7
#elif RCC_PLL_MUL > 5
	#define RCC_PLL_MULX RCC_PLL_MUL6
#elif RCC_PLL_MUL > 4
	#define RCC_PLL_MULX RCC_PLL_MUL5
#elif RCC_PLL_MUL > 3
	#define RCC_PLL_MULX RCC_PLL_MUL4
#elif RCC_PLL_MUL > 2
	#define RCC_PLL_MULX RCC_PLL_MUL3
#else
	#define RCC_PLL_MULX RCC_PLL_MUL2
#endif
#endif

#if defined(RCC_PRE_DIV)
	#if RCC_PRE_DIV > 15
		#define RCC_PRE_DIVX RCC_PREDIV_DIV16
	#elif RCC_PRE_DIV > 14
		#define RCC_PRE_DIVX RCC_PREDIV_DIV15
	#elif RCC_PRE_DIV > 13
		#define RCC_PRE_DIVX RCC_PREDIV_DIV14
	#elif RCC_PRE_DIV > 12
		#define RCC_PRE_DIVX RCC_PREDIV_DIV13
	#elif RCC_PRE_DIV > 11
		#define RCC_PRE_DIVX RCC_PREDIV_DIV12
	#elif RCC_PRE_DIV > 10
		#define RCC_PRE_DIVX RCC_PREDIV_DIV11
	#elif RCC_PRE_DIV > 9
		#define RCC_PRE_DIVX RCC_PREDIV_DIV10
	#elif RCC_PRE_DIV > 8
		#define RCC_PRE_DIVX RCC_PREDIV_DIV9
	#elif RCC_PRE_DIV > 7
		#define RCC_PRE_DIVX RCC_PREDIV_DIV8
	#elif RCC_PRE_DIV > 6
		#define RCC_PRE_DIVX RCC_PREDIV_DIV7
	#elif RCC_PRE_DIV > 5
		#define RCC_PRE_DIVX RCC_PREDIV_DIV6
	#elif RCC_PRE_DIV > 4
		#define RCC_PRE_DIVX RCC_PREDIV_DIV5
	#elif RCC_PRE_DIV > 3
		#define RCC_PRE_DIVX RCC_PREDIV_DIV4
	#elif RCC_PRE_DIV > 2
		#define RCC_PRE_DIVX RCC_PREDIV_DIV3
	#elif RCC_PRE_DIV > 1
		#define RCC_PRE_DIVX RCC_PREDIV_DIV2
	#else
		#define RCC_PRE_DIVX RCC_PREDIV_DIV1
	#endif
#elif defined(RCC_HSE_DIV)
	#if RCC_HSE_DIV > 15
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV16
	#elif RCC_HSE_DIV > 14
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV15
	#elif RCC_HSE_DIV > 13
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV14
	#elif RCC_HSE_DIV > 12
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV13
	#elif RCC_HSE_DIV > 11
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV12
	#elif RCC_HSE_DIV > 10
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV11
	#elif RCC_HSE_DIV > 9
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV10
	#elif RCC_HSE_DIV > 8
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV9
	#elif RCC_HSE_DIV > 7
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV8
	#elif RCC_HSE_DIV > 6
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV7
	#elif RCC_HSE_DIV > 5
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV6
	#elif RCC_HSE_DIV > 4
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV5
	#elif RCC_HSE_DIV > 3
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV4
	#elif RCC_HSE_DIV > 2
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV3
	#elif RCC_HSE_DIV > 1
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV2
	#else
		#define RCC_PRE_DIVX RCC_HSE_PREDIV_DIV1
	#endif
#endif
	
#if   (FLASH_LTNC > 7) && (defined FLASH_LATENCY_8)
	#define FLASH_LATENCY_X FLASH_LATENCY_8
#elif (FLASH_LTNC > 6) && (defined FLASH_LATENCY_7)
	#define FLASH_LATENCY_X FLASH_LATENCY_7
#elif (FLASH_LTNC > 5) && (defined FLASH_LATENCY_6)
	#define FLASH_LATENCY_X FLASH_LATENCY_6
#elif (FLASH_LTNC > 4) && (defined FLASH_LATENCY_5)
	#define FLASH_LATENCY_X FLASH_LATENCY_5
#elif (FLASH_LTNC > 3) && (defined FLASH_LATENCY_4)
	#define FLASH_LATENCY_X FLASH_LATENCY_4
#elif (FLASH_LTNC > 2) && (defined FLASH_LATENCY_3)
	#define FLASH_LATENCY_X FLASH_LATENCY_3
#elif (FLASH_LTNC > 1) && (defined FLASH_LATENCY_2)
	#define FLASH_LATENCY_X FLASH_LATENCY_2
#elif (FLASH_LTNC > 0) && (defined FLASH_LATENCY_1)
	#define FLASH_LATENCY_X FLASH_LATENCY_1
#else
	#define FLASH_LATENCY_X FLASH_LATENCY_0
#endif
	
	
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void Error_Handler()
{
}

void SystemClocksSetup(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();
  
	/* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
#if defined PWR_REGULATOR_VOLTAGE_SCALE1
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
#endif

	if(RCC_OSC_TYPE)
	{	
	#if defined RCC_OSCILLATORTYPE_HSI48
		if(RCC_OSC_TYPE == 2)
		{
			/* Enable HSI48 Oscillator */
			RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
			RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
		}
	#endif
		if(RCC_OSC_TYPE & 1)
		{
		/* Enable HSE Oscillator */
		RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;

		/* Bypass HSI Oscillator drive for external oscillator */		
			if(RCC_OSC_TYPE == 3)
		{
			RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
		} else {
			RCC_OscInitStruct.HSEState = RCC_HSE_ON;
		}
		}
	} else {
		/* Enable HSI Oscillator */
		RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
		RCC_OscInitStruct.HSIState = RCC_HSI_ON;
		RCC_OscInitStruct.HSICalibrationValue = 0x10;
	}

	if(RCC_PLL_SRC)
	{
		RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
		if(RCC_PLL_SRC == 0x02)
		{
			RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
		}
		
#ifdef RCC_PLLSOURCE_HSI
		if(RCC_PLL_SRC == 0x01)
		{
			RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
		}
#endif

#ifdef RCC_PLLSOURCE_HSI48
		if(RCC_PLL_SRC == 0x03)
		{
			RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI48;
		}
#endif
	}

#if defined(STM32F2) || defined(STM32F4) || defined(STM32F7)
#ifdef RCC_PLLM
	RCC_OscInitStruct.PLL.PLLM = RCC_PLLM;
#endif
#ifdef RCC_PLLN
	RCC_OscInitStruct.PLL.PLLN = RCC_PLLN;
#endif
#ifdef RCC_PLLP
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP;
#endif
#ifdef RCC_PLLQ
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ;
#endif
#ifdef RCC_PLLR
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR;
#endif
#elif defined(STM32F0)
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MULX;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PRE_DIVX;
#elif defined(STM32F3)
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MULX;
	#if defined(RCC_PRE_DIV)
		RCC_OscInitStruct.PLL.PREDIV = RCC_PRE_DIVX;
	#elif defined(RCC_HSE_DIV)
		RCC_OscInitStruct.HSEPredivValue = RCC_PRE_DIVX;
	#endif
#endif	

	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

#ifdef CLK_OVRDRV
	/* activate the OverDrive to reach the 180 Mhz Frequency */
	if(HAL_PWREx_ActivateOverDrive() != HAL_OK)
	{
		Error_Handler();
	}
#endif
  
	switch(RCC_SYSCLK_SRC)
	{
		case 1:
				RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
				break;
				
		case 2:
				RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
				break;
#ifdef RCC_OSCILLATORTYPE_HSI48
		case 3:
				RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
				break;
#endif
		
		default:
				RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;		
	}		

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
	clocks dividers */
#ifdef RCC_CLOCKTYPE_PCLK2	// not available for F0
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
#else
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
#endif

	RCC_ClkInitStruct.AHBCLKDivider = RCC_AHB_PRE_DIVX;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_PRE_DIVX;
#ifdef RCC_CLOCKTYPE_PCLK2	// not available for F0
	RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_PRE_DIVX;
#endif

	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_X) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}
