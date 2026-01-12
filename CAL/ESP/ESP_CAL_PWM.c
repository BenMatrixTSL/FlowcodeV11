// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A00A7638C619EA04AA769141413688B2AC78642253E57F9DFA48624EF30B847B3F3027571EAD75915DA9B11F738DF98E15B5754DA01DD859BAABA6A4795D8DE11455BE1BC769CC0A038A4BCA8973E37F0B368074752D2AB56A3F750DE410645AB460ED9F072C2943900788E5C29F4912892CE8BD78A7C00387A9D8E21AF5CEDEAB646E5AC1639AAB89549D34A0D5AD11F33EB4A87BF2BE2CA978029C551C6D2E680DBF1404BB32D458F0B9F6FEC6D77E3F44FB7D5555DAC58F
// REVISION: 8.0
// GUID: 080DA084-A9D8-48F5-8678-F2922DF270B1
// DATE: 07\01\2026
// DIR: CAL\ESP\ESP_CAL_PWM.c
/*********************************************************************
 *                  Flowcode CAL PWM File
 *
 * File: ESP_CAL_PWM.c
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
 * 170720 | LM | Created
 *
 */


#undef porta
#undef portb

#define porta 0
#define portb 32
#ifndef PORTA
  #define PORTA 0
#endif
#ifndef PORTB
  #define PORTB 32
#endif


#define MX_PWM_CHANNEL_X	CAL_APPEND(MX_PWM_CHANNEL_, MX_PWM_NUM)
#define MX_PWM_PORT_X		CAL_APPEND(MX_PWM_PORT_, 	MX_PWM_NUM)
#define MX_PWM_PIN_X		CAL_APPEND(MX_PWM_PIN_, 	MX_PWM_NUM)

#define MX_PWM_FREQ_X		CAL_APPEND(MX_PWM_FREQ_, 	MX_PWM_NUM)
#define MX_PWM_PERIOD_X		CAL_APPEND(MX_PWM_PERIOD_, 	MX_PWM_NUM)

#ifdef MX_BL0058_PINMAP

	#define PORTC 64

	#if (MX_PWM_PORT_X == PORTA)
		#if (MX_PWM_PIN_X == 0)
			#define MX_PWM_PP_X	32
		#endif
		#if (MX_PWM_PIN_X == 1)
			#define MX_PWM_PP_X	33
		#endif
		#if (MX_PWM_PIN_X == 2)
			#define MX_PWM_PP_X	2
		#endif
		#if (MX_PWM_PIN_X == 3)
			#define MX_PWM_PP_X	26
		#endif
		#if (MX_PWM_PIN_X == 4)
			#define MX_PWM_PP_X	4
		#endif
		#if (MX_PWM_PIN_X == 5)
			#define MX_PWM_PP_X	5
		#endif
		#if (MX_PWM_PIN_X == 6)
			#define MX_PWM_PP_X	12
		#endif
		#if (MX_PWM_PIN_X == 7)
			#define MX_PWM_PP_X	13
		#endif
	#endif
	#if (MX_PWM_PORT_X == PORTB)
		#if (MX_PWM_PIN_X == 0)
			#define MX_PWM_PP_X	14
		#endif
		#if (MX_PWM_PIN_X == 1)
			#define MX_PWM_PP_X	15
		#endif
		#if (MX_PWM_PIN_X == 2)
			#define MX_PWM_PP_X	18
		#endif
		#if (MX_PWM_PIN_X == 3)
			#define MX_PWM_PP_X	19
		#endif
		#if (MX_PWM_PIN_X == 4)
			#define MX_PWM_PP_X	27
		#endif
		#if (MX_PWM_PIN_X == 5)
			#define MX_PWM_PP_X	22
		#endif
		#if (MX_PWM_PIN_X == 6)
			#define MX_PWM_PP_X	0
		#endif
		#if (MX_PWM_PIN_X == 7)
			#define MX_PWM_PP_X	25
		#endif
	#endif
	#if (MX_PWM_PORT_X == PORTC)
		#if (MX_PWM_PIN_X == 0)
			#define MX_PWM_PP_X	23
		#endif
		#if (MX_PWM_PIN_X == 2)
			#define MX_PWM_PP_X	16
		#endif
		#if (MX_PWM_PIN_X == 3)
			#define MX_PWM_PP_X	17
		#endif
		#if (MX_PWM_PIN_X == 4)
			#define MX_PWM_PP_X	34
		#endif
		#if (MX_PWM_PIN_X == 5)
			#define MX_PWM_PP_X	35
		#endif
		#if (MX_PWM_PIN_X == 6)
			#define MX_PWM_PP_X	36
		#endif
		#if (MX_PWM_PIN_X == 7)
			#define MX_PWM_PP_X	39
		#endif
	#endif
#else
	#ifdef MX_BL6390_PINMAP

		#define PORTC 64
		#define PORTD 96

		#if (MX_PWM_PORT_X == PORTA)
			#if (MX_PWM_PIN_X == 0)
				#define MX_PWM_PP_X	4
			#endif
			#if (MX_PWM_PIN_X == 1)
				#define MX_PWM_PP_X	5
			#endif
			#if (MX_PWM_PIN_X == 2)
				#define MX_PWM_PP_X	6
			#endif
			#if (MX_PWM_PIN_X == 3)
				#define MX_PWM_PP_X	7
			#endif
			#if (MX_PWM_PIN_X == 4)
				#define MX_PWM_PP_X	15
			#endif
			#if (MX_PWM_PIN_X == 5)
				#define MX_PWM_PP_X	16
			#endif
			#if (MX_PWM_PIN_X == 6)
				#define MX_PWM_PP_X	17
			#endif
			#if (MX_PWM_PIN_X == 7)
				#define MX_PWM_PP_X	18
			#endif
		#endif
		#if (MX_PWM_PORT_X == PORTB)
			#if (MX_PWM_PIN_X == 0)
				#define MX_PWM_PP_X	8
			#endif
			#if (MX_PWM_PIN_X == 1)
				#define MX_PWM_PP_X	19
			#endif
			#if (MX_PWM_PIN_X == 2)
				#define MX_PWM_PP_X	20
			#endif
			#if (MX_PWM_PIN_X == 3)
				#define MX_PWM_PP_X	3
			#endif
			#if (MX_PWM_PIN_X == 4)
				#define MX_PWM_PP_X	9
			#endif
			#if (MX_PWM_PIN_X == 5)
				#define MX_PWM_PP_X	10
			#endif
			#if (MX_PWM_PIN_X == 6)
				#define MX_PWM_PP_X	11
			#endif
			#if (MX_PWM_PIN_X == 7)
				#define MX_PWM_PP_X	12
			#endif
		#endif
		#if (MX_PWM_PORT_X == PORTC)
			#if (MX_PWM_PIN_X == 0)
				#define MX_PWM_PP_X	13
			#endif
			#if (MX_PWM_PIN_X == 1)
				#define MX_PWM_PP_X	14
			#endif
			#if (MX_PWM_PIN_X == 2)
				#define MX_PWM_PP_X	21
			#endif
			#if (MX_PWM_PIN_X == 3)
				#define MX_PWM_PP_X	47
			#endif
			#if (MX_PWM_PIN_X == 4)
				#define MX_PWM_PP_X	48
			#endif
			#if (MX_PWM_PIN_X == 5)
				#define MX_PWM_PP_X	45
			#endif
			#if (MX_PWM_PIN_X == 6)
				#define MX_PWM_PP_X	38
			#endif
			#if (MX_PWM_PIN_X == 7)
				#define MX_PWM_PP_X	39
			#endif
		#endif
		#if (MX_PWM_PORT_X == PORTD)
			#if (MX_PWM_PIN_X == 0)
				#define MX_PWM_PP_X	40
			#endif
			#if (MX_PWM_PIN_X == 1)
				#define MX_PWM_PP_X	41
			#endif
			#if (MX_PWM_PIN_X == 2)
				#define MX_PWM_PP_X	42
			#endif
			#if (MX_PWM_PIN_X == 3)
				#define MX_PWM_PP_X	46
			#endif
			#if (MX_PWM_PIN_X == 4)
				#define MX_PWM_PP_X	0
			#endif
		#endif
	#else
		#define MX_PWM_PP_X			(MX_PWM_PORT_X + MX_PWM_PIN_X)
	#endif
#endif


CALFUNCTION(void, FC_CAL_PWM_Enable_, (void));
CALFUNCTION(void, FC_CAL_PWM_Disable_, (void));
CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 duty));
CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 period, MX_UINT16 prescaler));
CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 duty));



MX_FLOAT MX_PWM_PERIOD_X = 65535.0;


#ifdef MX_CAL_ESP32C3

//ESP32 C3 doesn't have standard PWM peripherals, instead it has LEDC peripherals which do a similar thing.



#include "driver/ledc.h"

#define MX_PWM_TMR_X			CAL_APPEND(MX_PWM_TMR_, 	MX_PWM_NUM)


CALFUNCTION(void, FC_CAL_PWM_Enable_, (void))
{
    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = MX_PWM_CHANNEL_X,
        .timer_sel      = MX_PWM_TMR_X,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = MX_PWM_PP_X,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
	ledc_channel_config(&ledc_channel);
}

CALFUNCTION(void, FC_CAL_PWM_Disable_, (void))
{
	ledc_stop(LEDC_LOW_SPEED_MODE, MX_PWM_CHANNEL_X, 0);
}

//Duty is specified as a floating point percentage 0.0 to 100.0
CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 duty))
{
	// Set duty
	ledc_set_duty(LEDC_LOW_SPEED_MODE, MX_PWM_CHANNEL_X, duty);
	// Update duty to apply the new value
    ledc_update_duty(LEDC_LOW_SPEED_MODE, MX_PWM_CHANNEL_X);
}

//Duty is specified as a 16-bit floating point percentage 0.0 to 100.0
CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 duty))
{
	// Set duty
	ledc_set_duty(LEDC_LOW_SPEED_MODE, MX_PWM_CHANNEL_X, duty);
	// Update duty to apply the new value
    ledc_update_duty(LEDC_LOW_SPEED_MODE, MX_PWM_CHANNEL_X);
}

CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 period, MX_UINT16 prescaler))
{
	MX_UINT8 prd = 0;
	while (period > 1)
	{
		period = period >> 1;
		prd++;
	}

	//Max 14-bit PWM period
	if (prd > 14)
		prd = 14;

    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = prd,
        .timer_num        = MX_PWM_TMR_X,
        .freq_hz          = MX_PWM_FREQ_X,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);
}

CALFUNCTION(void, FC_CAL_PWM_ChangeFrequency_, (MX_UINT32 frequency))
{
	ledc_set_freq(LEDC_LOW_SPEED_MODE, MX_PWM_TMR_X, frequency);
}


//Duty is specified as a floating point percentage 0.0 to 100.0
CALFUNCTION(void, FC_CAL_PWM_SetDutyFloat_, (MX_FLOAT duty))
{
	MX_UINT16 dty = (float) (duty / 100.0) * MX_PWM_PERIOD_X;

	// Set duty
	ledc_set_duty(LEDC_LOW_SPEED_MODE, MX_PWM_CHANNEL_X, dty);
	// Update duty to apply the new value
    ledc_update_duty(LEDC_LOW_SPEED_MODE, MX_PWM_CHANNEL_X);
}






#else





//All other devices use the standard PWM peripheral.

#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"


CALFUNCTION(void, FC_CAL_PWM_Enable_, (void))
{
 #ifdef MX_PWM

	#if (MX_PWM_CHANNEL_X == 1)
	  mcpwm_unit_t mcpwm_num = MCPWM_UNIT_0;
	  mcpwm_io_signals_t io_signal = MCPWM0A;
	  mcpwm_timer_t timer_num = MCPWM_TIMER_0;
	#elif (MX_PWM_CHANNEL_X == 2)
	  mcpwm_unit_t mcpwm_num = MCPWM_UNIT_0;
	  mcpwm_io_signals_t io_signal = MCPWM0B;
	  mcpwm_timer_t timer_num = MCPWM_TIMER_0;
	#elif (MX_PWM_CHANNEL_X == 3)
	  mcpwm_unit_t mcpwm_num = MCPWM_UNIT_0;
	  mcpwm_io_signals_t io_signal = MCPWM1A;
	  mcpwm_timer_t timer_num = MCPWM_TIMER_1;
	#elif (MX_PWM_CHANNEL_X == 4)
	  mcpwm_unit_t mcpwm_num = MCPWM_UNIT_0;
	  mcpwm_io_signals_t io_signal = MCPWM1B;
	  mcpwm_timer_t timer_num = MCPWM_TIMER_1;
	#elif (MX_PWM_CHANNEL_X == 5)
	  mcpwm_unit_t mcpwm_num = MCPWM_UNIT_0;
	  mcpwm_io_signals_t io_signal = MCPWM2A;
	  mcpwm_timer_t timer_num = MCPWM_TIMER_2;
	#elif (MX_PWM_CHANNEL_X == 6)
	  mcpwm_unit_t mcpwm_num = MCPWM_UNIT_0;
	  mcpwm_io_signals_t io_signal = MCPWM2B;
	  mcpwm_timer_t timer_num = MCPWM_TIMER_2;
	#elif (MX_PWM_CHANNEL_X == 7)
	  mcpwm_unit_t mcpwm_num = MCPWM_UNIT_1;
	  mcpwm_io_signals_t io_signal = MCPWM0A;
	  mcpwm_timer_t timer_num = MCPWM_TIMER_0;
	#elif (MX_PWM_CHANNEL_X == 8)
	  mcpwm_unit_t mcpwm_num = MCPWM_UNIT_1;
	  mcpwm_io_signals_t io_signal = MCPWM0B;
	  mcpwm_timer_t timer_num = MCPWM_TIMER_0;
	#elif (MX_PWM_CHANNEL_X == 9)
	  mcpwm_unit_t mcpwm_num = MCPWM_UNIT_1;
	  mcpwm_io_signals_t io_signal = MCPWM1A;
	  mcpwm_timer_t timer_num = MCPWM_TIMER_1;
	#elif (MX_PWM_CHANNEL_X == 10)
	  mcpwm_unit_t mcpwm_num = MCPWM_UNIT_1;
	  mcpwm_io_signals_t io_signal = MCPWM1B;
	  mcpwm_timer_t timer_num = MCPWM_TIMER_1;
	#elif (MX_PWM_CHANNEL_X == 11)
	  mcpwm_unit_t mcpwm_num = MCPWM_UNIT_1;
	  mcpwm_io_signals_t io_signal = MCPWM2A;
	  mcpwm_timer_t timer_num = MCPWM_TIMER_2;
	#elif (MX_PWM_CHANNEL_X == 12)
	  mcpwm_unit_t mcpwm_num = MCPWM_UNIT_1;
	  mcpwm_io_signals_t io_signal = MCPWM2B;
	  mcpwm_timer_t timer_num = MCPWM_TIMER_2;
	#endif

	const mcpwm_config_t  mcpwm_conf = {
		#if (MX_PWM_FREQ_X > 0)
			.frequency = (uint32_t)MX_PWM_FREQ_X,
		#else
			.frequency = 1000,
		#endif
        .cmpr_a = 0.0,
		.cmpr_b = 0.0,
		.duty_mode = MCPWM_DUTY_MODE_0,
		.counter_mode = MCPWM_UP_COUNTER,
    };

	if (ESP_OK == mcpwm_gpio_init(mcpwm_num, io_signal, MX_PWM_PP_X))
	{
		if (ESP_OK == mcpwm_init(mcpwm_num, timer_num, &mcpwm_conf))
		{
			mcpwm_start(mcpwm_num, timer_num);
		}
	}
 #else
 	#warning "Hardware PWM not supported by Target microcontroller."
 	#undef MX_PWM_CHANNEL_X
 #endif

}

CALFUNCTION(void, FC_CAL_PWM_Disable_, (void))
{
	#if (MX_PWM_CHANNEL_X == 1)
		mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
	#elif (MX_PWM_CHANNEL_X == 2)
		mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_0);
	#elif (MX_PWM_CHANNEL_X == 3)
		mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_1);
	#elif (MX_PWM_CHANNEL_X == 4)
		mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_1);
	#elif (MX_PWM_CHANNEL_X == 5)
		mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_2);
	#elif (MX_PWM_CHANNEL_X == 6)
		mcpwm_stop(MCPWM_UNIT_0, MCPWM_TIMER_2);
	#elif (MX_PWM_CHANNEL_X == 7)
		mcpwm_stop(MCPWM_UNIT_1, MCPWM_TIMER_0);
	#elif (MX_PWM_CHANNEL_X == 8)
		mcpwm_stop(MCPWM_UNIT_1, MCPWM_TIMER_0);
	#elif (MX_PWM_CHANNEL_X == 9)
		mcpwm_stop(MCPWM_UNIT_1, MCPWM_TIMER_1);
	#elif (MX_PWM_CHANNEL_X == 10)
		mcpwm_stop(MCPWM_UNIT_1, MCPWM_TIMER_1);
	#elif (MX_PWM_CHANNEL_X == 11)
		mcpwm_stop(MCPWM_UNIT_1, MCPWM_TIMER_2);
	#elif (MX_PWM_CHANNEL_X == 12)
		mcpwm_stop(MCPWM_UNIT_1, MCPWM_TIMER_2);
	#endif
}

//Duty is specified as a floating point percentage 0.0 to 100.0
CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 duty))
{
	#if (MX_PWM_CHANNEL_X == 1)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, (float) (duty*100.0)/255.0);
	#elif (MX_PWM_CHANNEL_X == 2)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, (float) (duty*100.0)/255.0);
	#elif (MX_PWM_CHANNEL_X == 3)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_GEN_A, (float) (duty*100.0)/255.0);
	#elif (MX_PWM_CHANNEL_X == 4)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_GEN_B, (float) (duty*100.0)/255.0);
	#elif (MX_PWM_CHANNEL_X == 5)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_GEN_A, (float) (duty*100.0)/255.0);
	#elif (MX_PWM_CHANNEL_X == 6)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_GEN_B, (float) (duty*100.0)/255.0);
	#elif (MX_PWM_CHANNEL_X == 7)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_GEN_A, (float) (duty*100.0)/255.0);
	#elif (MX_PWM_CHANNEL_X == 8)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_GEN_B, (float) (duty*100.0)/255.0);
	#elif (MX_PWM_CHANNEL_X == 9)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_GEN_A, (float) (duty*100.0)/255.0);
	#elif (MX_PWM_CHANNEL_X == 10)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_GEN_B, (float) (duty*100.0)/255.0);
	#elif (MX_PWM_CHANNEL_X == 11)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_2, MCPWM_GEN_A, (float) (duty*100.0)/255.0);
	#elif (MX_PWM_CHANNEL_X == 12)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_2, MCPWM_GEN_B, (float) (duty*100.0)/255.0);
	#endif
}

//Duty is specified as a 16-bit floating point percentage 0.0 to 100.0
CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 duty))
{
	#if (MX_PWM_CHANNEL_X == 1)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, (float) (duty*100.0)/MX_PWM_PERIOD_X);
	#elif (MX_PWM_CHANNEL_X == 2)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_B, (float) (duty*100.0)/MX_PWM_PERIOD_X);
	#elif (MX_PWM_CHANNEL_X == 3)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_GEN_A, (float) (duty*100.0)/MX_PWM_PERIOD_X);
	#elif (MX_PWM_CHANNEL_X == 4)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_GEN_B, (float) (duty*100.0)/MX_PWM_PERIOD_X);
	#elif (MX_PWM_CHANNEL_X == 5)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_GEN_A, (float) (duty*100.0)/MX_PWM_PERIOD_X);
	#elif (MX_PWM_CHANNEL_X == 6)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_GEN_B, (float) (duty*100.0)/MX_PWM_PERIOD_X);
	#elif (MX_PWM_CHANNEL_X == 7)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_GEN_A, (float) (duty*100.0)/MX_PWM_PERIOD_X);
	#elif (MX_PWM_CHANNEL_X == 8)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_GEN_B, (float) (duty*100.0)/MX_PWM_PERIOD_X);
	#elif (MX_PWM_CHANNEL_X == 9)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_GEN_A, (float) (duty*100.0)/MX_PWM_PERIOD_X);
	#elif (MX_PWM_CHANNEL_X == 10)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_GEN_B, (float) (duty*100.0)/MX_PWM_PERIOD_X);
	#elif (MX_PWM_CHANNEL_X == 11)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_2, MCPWM_GEN_A, (float) (duty*100.0)/MX_PWM_PERIOD_X);
	#elif (MX_PWM_CHANNEL_X == 12)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_2, MCPWM_GEN_B, (float) (duty*100.0)/MX_PWM_PERIOD_X);
	#endif
}

CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 period, MX_UINT16 prescaler))
{
	MX_PWM_PERIOD_X = period;
}

CALFUNCTION(void, FC_CAL_PWM_ChangeFrequency_, (MX_UINT32 frequency))
{
	//Frequency of at least 1Hz
	if (frequency == 0) frequency = 1;

	#if (MX_PWM_CHANNEL_X == 1)
		mcpwm_set_frequency(MCPWM_UNIT_0, MCPWM_TIMER_0, (uint32_t) frequency);
	#elif (MX_PWM_CHANNEL_X == 2)
		mcpwm_set_frequency(MCPWM_UNIT_0, MCPWM_TIMER_0, (uint32_t) frequency);
	#elif (MX_PWM_CHANNEL_X == 3)
		mcpwm_set_frequency(MCPWM_UNIT_0, MCPWM_TIMER_1, (uint32_t) frequency);
	#elif (MX_PWM_CHANNEL_X == 4)
		mcpwm_set_frequency(MCPWM_UNIT_0, MCPWM_TIMER_1, (uint32_t) frequency);
	#elif (MX_PWM_CHANNEL_X == 5)
		mcpwm_set_frequency(MCPWM_UNIT_0, MCPWM_TIMER_2, (uint32_t) frequency);
	#elif (MX_PWM_CHANNEL_X == 6)
		mcpwm_set_frequency(MCPWM_UNIT_0, MCPWM_TIMER_2, (uint32_t) frequency);
	#elif (MX_PWM_CHANNEL_X == 7)
		mcpwm_set_frequency(MCPWM_UNIT_1, MCPWM_TIMER_0, (uint32_t) frequency);
	#elif (MX_PWM_CHANNEL_X == 8)
		mcpwm_set_frequency(MCPWM_UNIT_1, MCPWM_TIMER_0, (uint32_t) frequency);
	#elif (MX_PWM_CHANNEL_X == 9)
		mcpwm_set_frequency(MCPWM_UNIT_1, MCPWM_TIMER_1, (uint32_t) frequency);
	#elif (MX_PWM_CHANNEL_X == 10)
		mcpwm_set_frequency(MCPWM_UNIT_1, MCPWM_TIMER_1, (uint32_t) frequency);
	#elif (MX_PWM_CHANNEL_X == 11)
		mcpwm_set_frequency(MCPWM_UNIT_1, MCPWM_TIMER_2, (uint32_t) frequency);
	#elif (MX_PWM_CHANNEL_X == 12)
		mcpwm_set_frequency(MCPWM_UNIT_1, MCPWM_TIMER_2, (uint32_t) frequency);
	#endif
}


//Duty is specified as a floating point percentage 0.0 to 100.0
CALFUNCTION(void, FC_CAL_PWM_SetDutyFloat_, (MX_FLOAT duty))
{
	#if (MX_PWM_CHANNEL_X == 1)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, duty);
	#elif (MX_PWM_CHANNEL_X == 2)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_B, duty);
	#elif (MX_PWM_CHANNEL_X == 3)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_GEN_A, duty);
	#elif (MX_PWM_CHANNEL_X == 4)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_GEN_B, duty);
	#elif (MX_PWM_CHANNEL_X == 5)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_GEN_A, duty);
	#elif (MX_PWM_CHANNEL_X == 6)
		mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_GEN_B, duty);
	#elif (MX_PWM_CHANNEL_X == 7)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_GEN_A, duty);
	#elif (MX_PWM_CHANNEL_X == 8)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_GEN_B, duty);
	#elif (MX_PWM_CHANNEL_X == 9)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_GEN_A, duty);
	#elif (MX_PWM_CHANNEL_X == 10)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_GEN_B, duty);
	#elif (MX_PWM_CHANNEL_X == 11)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_2, MCPWM_GEN_A, duty);
	#elif (MX_PWM_CHANNEL_X == 12)
		mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_2, MCPWM_GEN_B, duty);
	#endif
}

#endif


#undef MX_PWM_CHANNEL_X
#undef MX_PWM_PORT_X
#undef MX_PWM_PIN_X
#undef MX_PWM_FREQ_X
#undef MX_PWM_PERIOD_X
#undef MX_PWM_PP_X
