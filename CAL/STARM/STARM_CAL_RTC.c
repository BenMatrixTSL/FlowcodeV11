// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BE89A4AB1A5D05A2BA21B6A2F7A077260E186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF59207DC5361ECD88D0C69D152534353040D8485471006CF701144FE29C263156D97F5ECB8E89E60B6E6FC79B7E644083A74A3E7C07C744B4C59EDF61EB618678E29B8A91A393B98B1E0B5E7E57D28E60DB6330F903D737808549D34A0D5AD11F3835DA68BDFB243A3F138E746C0D252EE5B19386C0025AD68C1E0961D1CF9D810AE94354B8E74C3BA
// REVISION: 1.0
// GUID: 8B95D65F-E4AA-4D0B-8B6E-3985FABC9D4B
// DATE: 08\08\2022
// DIR: CAL\STARM\STARM_CAL_RTC.c
/*********************************************************************
 *                  Flowcode CAL RTCC File
 *
 * File: STARM_CAL_RTC.c
 *
 * (c) 2020 Matrix TSL
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
 * 200120 | LM | Created
 */

/***
	Note: All functions expect values in BCD format

	FCD addition:

    <rtcc type='1'>
    	<clock>
    	    <option name='40 kHz internal RC (LSI RC)' value='0' />
    	    <option name='32.768 kHz external crystal (LSE crystal)' value='1' />
    	</clock>
    </rtcc>

***/

CALFUNCTION(void, FC_CAL_RTC_Init_, (void));

CALFUNCTION(void, FC_CAL_RTC_SetSec_, (MX_UINT8 Data));
CALFUNCTION(void, FC_CAL_RTC_SetMin_, (MX_UINT8 Data));
CALFUNCTION(void, FC_CAL_RTC_SetHour_, (MX_UINT8 Data));
CALFUNCTION(void, FC_CAL_RTC_SetWeekDay_, (MX_UINT8 Data));
CALFUNCTION(void, FC_CAL_RTC_SetDay_, (MX_UINT8 Data));
CALFUNCTION(void, FC_CAL_RTC_SetMonth_, (MX_UINT8 Data));
CALFUNCTION(void, FC_CAL_RTC_SetYear_, (MX_UINT8 Data));

CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetSec_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetMin_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetHour_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetWeekDay_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetDay_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetMonth_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetYear_, (void));


#if defined (STM32F4)
	#ifndef	RTC_TR_HU_Pos
		#define	RTC_TR_HU_Pos	(16U)
	#endif
	#ifndef	RTC_TR_SU_Pos
		#define	RTC_TR_SU_Pos	(0U)
	#endif
	#ifndef	RTC_TR_MNU_Pos
		#define	RTC_TR_MNU_Pos	(8U)
	#endif
	#ifndef	RTC_DR_WDU_Pos
		#define	RTC_DR_WDU_Pos	(13U)
	#endif
	#ifndef	RTC_DR_DU_Pos
		#define	RTC_DR_DU_Pos	(0U)
	#endif
	#ifndef	RTC_DR_MU_Pos
		#define	RTC_DR_MU_Pos	(8U)
	#endif
	#ifndef	RTC_DR_YU_Pos
		#define	RTC_DR_YU_Pos	(16U)
	#endif
#endif


	#define MX_RTC_SET_INIT()	{RTC->ISR |= RTC_ISR_INIT; while (!(RTC->ISR & RTC_ISR_INITF));}
	#define MX_RTC_CLR_INIT()	{RTC->ISR &= ~(RTC_ISR_INIT);}
	#define MX_RTC_WAIT_RSF()	{RTC->ISR &= ~(RTC_ISR_RSF); while (!(RTC->ISR & RTC_ISR_RSF));}


#if defined (STM32F303x8) || defined (STM32F303xC) || defined (STM32F303xE)

	CALFUNCTION(void, FC_CAL_RTC_Init_, (void))
	{
		#if (MX_RTC_CLOCK == 0)
			// 40 kHz low speed internal RC (LSI RC)
			SET_BIT(PWR->CR, PWR_CR_DBP);
			__HAL_RCC_LSI_ENABLE();
			__HAL_RCC_RTC_ENABLE();
			RCC->BDCR = (RCC_BDCR_RTCEN | RCC_BDCR_RTCSEL_LSI);
			RTC->WPR = 0xCAU;
			RTC->WPR = 0x53U;			
			MX_RTC_SET_INIT();
			RTC->PRER = 0x63018F;	// Prescalers for 40kHz
			MX_RTC_CLR_INIT();
			
		#elif (MX_RTC_CLOCK == 1)
			// 32.768 kHz low speed external crystal (LSE crystal)
			SET_BIT(PWR->CR, PWR_CR_DBP);
			__HAL_RCC_LSE_CONFIG(RCC_LSE_ON);
			__HAL_RCC_RTC_ENABLE();
			RCC->BDCR = (RCC_BDCR_RTCEN | RCC_BDCR_RTCSEL_LSE | RCC_BDCR_LSEON);
			RTC->WPR = 0xCAU;
			RTC->WPR = 0x53U;			
			MX_RTC_SET_INIT();
			RTC->PRER = 0x7F00FF;	// Prescalers for 32.768kHz
			MX_RTC_CLR_INIT();
			
		#else
			#warning "Unknown RTC clock source selection"
		#endif
	}

#elif defined (STM32F4)

	CALFUNCTION(void, FC_CAL_RTC_Init_, (void))
	{
		#if (MX_RTC_CLOCK == 0)
			// 32 kHz low speed internal RC (LSI RC)
			SET_BIT(PWR->CR, PWR_CR_DBP);
			__HAL_RCC_LSI_ENABLE();
			__HAL_RCC_RTC_ENABLE();
			RTC->WPR = 0xCAU;
			RTC->WPR = 0x53U;			
			MX_RTC_SET_INIT();
			RTC->PRER = 0x63013F;	// Prescalers for 32kHz
			MX_RTC_CLR_INIT();
			
		#elif (MX_RTC_CLOCK == 1)
			// 32.768 kHz low speed external crystal (LSE crystal)
			SET_BIT(PWR->CR, PWR_CR_DBP);
			__HAL_RCC_LSE_CONFIG(RCC_LSE_ON);
			__HAL_RCC_RTC_ENABLE();
			RTC->WPR = 0xCAU;
			RTC->WPR = 0x53U;			
			MX_RTC_SET_INIT();
			RTC->PRER = 0x7F00FF;	// Prescalers for 32.768kHz
			MX_RTC_CLR_INIT();
			
		#else
			#warning "Unknown RTC clock source selection"
		#endif
	}

#endif

	// Write Functions
	
	CALFUNCTION(void, FC_CAL_RTC_SetSec_, (MX_UINT8 Data))
	{
		MX_RTC_SET_INIT();
		RTC->TR = (RTC->TR & ~(RTC_TR_ST | RTC_TR_SU)) | (Data << RTC_TR_SU_Pos);
		MX_RTC_CLR_INIT();
		MX_RTC_WAIT_RSF();
	}

	CALFUNCTION(void, FC_CAL_RTC_SetMin_, (MX_UINT8 Data))
	{
		MX_RTC_SET_INIT();
		RTC->TR = (RTC->TR & ~(RTC_TR_MNT | RTC_TR_MNU)) | (Data << RTC_TR_MNU_Pos);
		MX_RTC_CLR_INIT();
		MX_RTC_WAIT_RSF();
	}

	CALFUNCTION(void, FC_CAL_RTC_SetHour_, (MX_UINT8 Data))
	{
		MX_RTC_SET_INIT();
		RTC->TR = (RTC->TR & ~(RTC_TR_HT | RTC_TR_HU)) | (Data << RTC_TR_HU_Pos);
		MX_RTC_CLR_INIT();
		MX_RTC_WAIT_RSF();
	}

	CALFUNCTION(void, FC_CAL_RTC_SetWeekDay_, (MX_UINT8 Data))
	{
		// nb. 0 not allowed. 1=Monday 7=Sunday
		Data &= 7;
		if (Data == 0) Data = 1;

		MX_RTC_SET_INIT();
		RTC->TR = (RTC->TR & ~(RTC_DR_WDU)) | (Data << RTC_DR_WDU_Pos);
		MX_RTC_CLR_INIT();
		MX_RTC_WAIT_RSF();
	}

	CALFUNCTION(void, FC_CAL_RTC_SetDay_, (MX_UINT8 Data))
	{
		MX_RTC_SET_INIT();
		RTC->DR = (RTC->DR & ~(RTC_DR_DT | RTC_DR_DU)) | (Data << RTC_DR_DU_Pos);
		MX_RTC_CLR_INIT();
		MX_RTC_WAIT_RSF();
	}

	CALFUNCTION(void, FC_CAL_RTC_SetMonth_, (MX_UINT8 Data))
	{
		MX_RTC_SET_INIT();
		RTC->DR = (RTC->DR & ~(RTC_DR_MT | RTC_DR_MU)) | (Data << RTC_DR_MU_Pos);
		MX_RTC_CLR_INIT();
		MX_RTC_WAIT_RSF();
	}

	CALFUNCTION(void, FC_CAL_RTC_SetYear_, (MX_UINT8 Data))
	{
		MX_RTC_SET_INIT();
		RTC->DR = (RTC->DR & ~(RTC_DR_YT | RTC_DR_YU)) | (Data << RTC_DR_YU_Pos);
		MX_RTC_CLR_INIT();
		MX_RTC_WAIT_RSF();
	}


	// Read Functions

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetSec_, (void))
	{
		return ((RTC->TR & (RTC_TR_ST | RTC_TR_SU)) >> RTC_TR_SU_Pos);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetMin_, (void))
	{
		return ((RTC->TR & (RTC_TR_MNT | RTC_TR_MNU)) >> RTC_TR_MNU_Pos);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetHour_, (void))
	{
		return ((RTC->TR & (RTC_TR_HT | RTC_TR_HU)) >> RTC_TR_HU_Pos);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetWeekDay_, (void))
	{
		return ((RTC->DR & (RTC_DR_WDU)) >> RTC_DR_WDU_Pos);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetDay_, (void))
	{
		return ((RTC->DR & (RTC_DR_DT | RTC_DR_DU)) >> RTC_DR_DU_Pos);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetMonth_, (void))
	{
		return ((RTC->DR & (RTC_DR_MT | RTC_DR_MU)) >> RTC_DR_MU_Pos);
	}

	CALFUNCTION(MX_UINT8, FC_CAL_RTC_GetYear_, (void))
	{
		return ((RTC->DR & (RTC_DR_YT | RTC_DR_YU)) >> RTC_DR_YU_Pos);
	}



