// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A012C52A9A458B17900EC8DB8A0EB203070AA5E8A2F812169EA82655AA92B9A6C44889EC98FBA75DB2D8DA408700E5719BDC7C31995637CCFDB345944F8F63A8B4F69065F02D721CD44F1380303175D54B9BF1F081D0E533CCC056E096A2CD5EB06EB9418C92B909ECBBF0D2127CB22A037E072B5D5B02F7B8206708C9AB9FAE2ACF73F1E08F47AFD2549D34A0D5AD11F37C6B136EDD8BE9FB03AEBF4AC1E9C85CD41D3D89F1ADCDA13D04CF7CD5577C5FE9D77FAA9053C2CE
// REVISION: 9.0
// GUID: 44BDA123-11CC-4362-8F91-DDD8658F5D98
// DATE: 09\10\2024
// DIR: CAL\ESP\ESP_CAL_Delay.c
/*********************************************************************
 *                  Flowcode CAL Delays File
 *
 * File: ESP_CAL_Delay.c
 *
 * (c) 2018 Matrix TSL.
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
 * 130718 | BR | Created
 * 071020 | LM | ESP timer interrupts added
 * 120624 | BR | ESP timer interrupts support moved from timer.h to gptimer.h
 */



void Wdt_Delay_S(MX_UINT8 delay);
void Wdt_Delay_Ms(MX_UINT8 delay);

void Wdt_DelayInt_S(MX_UINT16 delay);
void Wdt_DelayInt_Ms(MX_UINT16 delay);


// Delay by bytes
#define FCI_DELAYBYTE_S(count)     	delay_s((count))
#define FCI_DELAYBYTE_MS(count)    	delay_ms((count))
#define FCI_DELAYBYTE_US(count)    	delay_us((count))

#define FCI_DELAYINT_S(count)     	delay_s((count))
#define FCI_DELAYINT_MS(count)    	delay_ms((count))
#define FCI_DELAYINT_US(count)    	delay_us((count))

// With watchdog timer
#define FCI_DELAYBYTEWDT_S(count)	delay_s((count))
#define FCI_DELAYBYTEWDT_MS(count)	delay_ms((count))
#define FCI_DELAYBYTEWDT_US(count)	delay_us((count))

#define FCI_DELAYINTWDT_S(count)	delay_s((count))
#define FCI_DELAYINTWDT_MS(count)	delay_ms((count))
#define FCI_DELAYINTWDT_US(count)	delay_us((count))


//ms delays below 10ms are reported to be only lasting several uS and so we use the uS function

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)	// enable functionality present in IDF v5.0
	#define MX_US_FUNCTION	esp_rom_delay_us
#else												//Original IDF v4.1
	#define MX_US_FUNCTION	ets_delay_us
#endif


#define delay_us(x)					MX_US_FUNCTION(x);
#define delay_10us(x)				MX_US_FUNCTION(10 * x);

#define delay_ms(x)					(x < 10) ? MX_US_FUNCTION(1000 * x) : vTaskDelay(x / portTICK_PERIOD_MS);
#define delay_s(x)					vTaskDelay((1000 * x) / portTICK_PERIOD_MS);

/*

I couldn't make this work

#include "soc/rtc_wdt.h"

#define MX_CLEAR_WATCHDOG { TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE; TIMERG0.wdt_feed=1; TIMERG0.wdt_wprotect=0; }


void Wdt_Delay_S(MX_UINT8 delay)
{
    MX_UINT8 i;
    MX_UINT16 j;
    for (i=0; i<delay; i++)
    {
        for (j=0; j<999; j++)
        {
            Wdt_Delay_Ms(1);
        }
    }
}

void Wdt_Delay_Ms(MX_UINT8 delay)
{
    MX_UINT8 i;
    for (i=0; i<delay; i++)
    {
        MX_CLEAR_WATCHDOG;        //Clear Watchdog Timer
        delay_ms(1);
    }
}

void Wdt_DelayInt_S(MX_UINT16 delay)
{
    MX_UINT16 i;
    MX_UINT16 j;
    for (i=0; i<delay; i++)
    {
        for (j=0; j<999; j++)
        {
            Wdt_Delay_Ms(1);
        }
    }
}

void Wdt_DelayInt_Ms(MX_UINT16 delay)
{
    MX_UINT16 i;
    for (i=0; i<delay; i++)
    {
        MX_CLEAR_WATCHDOG;        //Clear Watchdog Timer
        delay_ms(1);
    }
}

*/

/***
//Original Byte Delays
void Wdt_Delay_S(char delay);
void Wdt_Delay_Ms(char delay);
//New Int Delays
void FCI_DELAYINTWDT_MS(MX_UINT16 Delay);
void FCI_DELAYINTWDT_S(MX_UINT16 Delay);
***/



#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)	// enable functionality present in IDF v5.0
	#include <driver/gptimer.h>

	gptimer_handle_t gptimer0 = NULL;
	gptimer_handle_t gptimer1 = NULL;
	gptimer_handle_t gptimer2 = NULL;
	gptimer_handle_t gptimer3 = NULL;

	unsigned char gptimer_enabled = 0;

#else
	#include <driver/timer.h>
#endif

uint64_t FC_CAL_Timer_Period;
uint64_t FC_CAL_Timer_Multiplier;

void FC_CAL_Timer_0_ISR(void*);
void FC_CAL_Timer_1_ISR(void*);
void FC_CAL_Timer_2_ISR(void*);
void FC_CAL_Timer_3_ISR(void*);

void FC_CAL_Timer_Init(uint8_t timer, uint64_t period, void callback(void*))
{
	#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)	// enable functionality present in IDF v5.0

		gptimer_config_t timer_config = {
			.clk_src = GPTIMER_CLK_SRC_DEFAULT,
			.direction = GPTIMER_COUNT_UP,
			.resolution_hz = 1000000, // 1MHz, 1 tick=1us
		};

		gptimer_alarm_config_t alarm_config1 = {
			.reload_count = 0,
			.alarm_count = period,
			.flags.auto_reload_on_alarm = true,
		};

		gptimer_event_callbacks_t cbs = {
			.on_alarm = callback,
		};

		switch (timer)
		{
			case 0:
				if ((gptimer_enabled & 0x01) == 0)
				{
					gptimer_new_timer(&timer_config, &gptimer0);
					gptimer_register_event_callbacks(gptimer0, &cbs, NULL);
					gptimer_enable(gptimer0);
					gptimer_set_alarm_action(gptimer0, &alarm_config1);
					gptimer_enabled |= 0x01;
				}
				gptimer_set_raw_count(gptimer0, 0);
				gptimer_start(gptimer0);
				break;
			case 1:
				if ((gptimer_enabled & 0x02) == 0)
				{
					gptimer_new_timer(&timer_config, &gptimer1);
					gptimer_register_event_callbacks(gptimer1, &cbs, NULL);
					gptimer_enable(gptimer1);
					gptimer_set_alarm_action(gptimer1, &alarm_config1);
					gptimer_enabled |= 0x02;
				}
				gptimer_set_raw_count(gptimer1, 0);
				gptimer_start(gptimer1);
				break;
			case 2:
				if ((gptimer_enabled & 0x04) == 0)
				{
					gptimer_new_timer(&timer_config, &gptimer2);
					gptimer_register_event_callbacks(gptimer2, &cbs, NULL);
					gptimer_enable(gptimer2);
					gptimer_set_alarm_action(gptimer2, &alarm_config1);
					gptimer_enabled |= 0x04;
				}
				gptimer_set_raw_count(gptimer2, 0);
				gptimer_start(gptimer2);
				break;
			case 3:
				if ((gptimer_enabled & 0x08) == 0)
				{
					gptimer_new_timer(&timer_config, &gptimer3);
					gptimer_register_event_callbacks(gptimer3, &cbs, NULL);
					gptimer_enable(gptimer3);
					gptimer_set_alarm_action(gptimer3, &alarm_config1);
					gptimer_enabled |= 0x08;
				}
				gptimer_set_raw_count(gptimer3, 0);
				gptimer_start(gptimer3);
				break;
			default: break;
		}

	#else

		timer_config_t config = {
			.divider = 80,
			.counter_dir = TIMER_COUNT_UP,
			.counter_en = TIMER_PAUSE,
			.alarm_en = TIMER_ALARM_EN,
			.intr_type = TIMER_INTR_LEVEL,
			.auto_reload = true,
		};

		timer_group_t timer_group = TIMER_GROUP_0;
		timer_idx_t timer_idx = TIMER_0;

		switch (timer)
		{
			#if (MX_ESP32_TYPE == ESP32C3)
			break;
			#else
				case 1: timer_group = TIMER_GROUP_0; timer_idx = TIMER_1; break;
				case 2: timer_group = TIMER_GROUP_1; timer_idx = TIMER_0; break;
				case 3: timer_group = TIMER_GROUP_1; timer_idx = TIMER_1; break;
			#endif
			default: break;
		}

		timer_init(timer_group, timer_idx, &config);
		timer_set_counter_value(timer_group, timer_idx, 0x00000000ULL);
		timer_set_alarm_value(timer_group, timer_idx, period);
		timer_enable_intr(timer_group, timer_idx);
		timer_isr_register(timer_group, timer_idx, callback, NULL, 0, NULL);
		timer_start(timer_group, timer_idx);

	#endif
}


void FC_CAL_Timer_Rearm(uint8_t timer)
{
	#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)	// enable functionality present in IDF v5.0

	#else

		switch (timer)
		{
			#if (MX_ESP32_TYPE == ESP32C3)
				case 0:
					timer_group_clr_intr_status_in_isr(TIMER_GROUP_0, TIMER_0);
					timer_group_enable_alarm_in_isr(TIMER_GROUP_0, TIMER_0);
					break;
			#else
				case 0:
					timer_group_clr_intr_status_in_isr(TIMER_GROUP_0, TIMER_0);
					timer_group_enable_alarm_in_isr(TIMER_GROUP_0, TIMER_0);
					break;
				case 1:
					timer_group_clr_intr_status_in_isr(TIMER_GROUP_0, TIMER_1);
					timer_group_enable_alarm_in_isr(TIMER_GROUP_0, TIMER_1);
					break;
				case 2:
					timer_group_clr_intr_status_in_isr(TIMER_GROUP_1, TIMER_0);
					timer_group_enable_alarm_in_isr(TIMER_GROUP_1, TIMER_0);
					break;
				case 3:
					timer_group_clr_intr_status_in_isr(TIMER_GROUP_1, TIMER_1);
					timer_group_enable_alarm_in_isr(TIMER_GROUP_1, TIMER_1);
					break;
			#endif
			default: break;
		}

	#endif
}


void FC_CAL_Timer_Deinit(uint8_t timer)
{
	#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)	// enable functionality present in IDF v5.0

		switch (timer)
		{
			case 0:
				gptimer_stop(gptimer0);
				break;
			case 1:
				gptimer_stop(gptimer1);
				break;
			case 2:
				gptimer_stop(gptimer2);
				break;
			case 3:
				gptimer_stop(gptimer3);
				break;
			default: break;
		}

	#else

		switch (timer)
		{
			#if (MX_ESP32_TYPE == ESP32C3)
				case 0:
					timer_pause(TIMER_GROUP_0, TIMER_0);
					break;
			#else
				case 0:
					timer_pause(TIMER_GROUP_0, TIMER_0);
					break;
				case 1:
					timer_pause(TIMER_GROUP_0, TIMER_1);
					break;
				case 2:
					timer_pause(TIMER_GROUP_1, TIMER_0);
					break;
				case 3:
					timer_pause(TIMER_GROUP_1, TIMER_1);
					break;
			#endif
			default: break;
		}

	#endif
}

