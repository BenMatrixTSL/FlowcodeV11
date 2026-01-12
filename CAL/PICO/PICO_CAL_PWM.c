// CRC: F9C65A77A483DDF22B438B7FEB8E3C81451B6760FECB07508D29EE770BB95F475ADEA58BF22D39D590A3838BC969E07EB6E88CF16DD83FC964341515DB7BB96D3307584D5060F214711B8143522C2B69CEB1F447A460839DE42078D24A1C648A1297F03E203B972366BF4A3A67F37CE99058802849C3A5F2F6EDBDF3CE23A8D4640F70FBAFFF8DD26143802B44E15F9DFE56E831A89668771BA585167B694D4F17E9878E77E2F2C2549D34A0D5AD11F3F7A4E39D0400D8B9103B82B0A12F597C9754537DD54BE3AA76D3E34736BD7539F516F4BDFF4A1CBE
// REVISION: 2.0
// GUID: B5BC82D1-E446-456B-93DE-6B9FC9559970
// DATE: 28\07\2023
// DIR: CAL\PICO\PICO_CAL_PWM.c

/*********************************************************************
 *                  Flowcode CAL PWM File
 *
 * File: PICO_CAL_PWM.c
 *
 * (c) 2021 Matrix TSL
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
 * 290621 | LM | Created
 *
 */
 
#include "hardware/pwm.h"
 
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
#define MX_PWM_PP_X			(MX_PWM_PORT_X + MX_PWM_PIN_X)
#define MX_PWM_FREQ_X		CAL_APPEND(MX_PWM_FREQ_, 	MX_PWM_NUM)
#define MX_PWM_PERIOD_X		CAL_APPEND(MX_PWM_PERIOD_, 	MX_PWM_NUM)
#define MX_PWM_DUTY_X		CAL_APPEND(MX_PWM_DUTY_, 	MX_PWM_NUM)
#define MX_PWM_PRESCALEX	CAL_APPEND(MX_PWM_PRESCALE, MX_PWM_NUM)


CALFUNCTION(void, FC_CAL_PWM_Enable_, (void));
CALFUNCTION(void, FC_CAL_PWM_Disable_, (void));
CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 duty));
CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 period, MX_UINT16 prescaler));
CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 duty));


MX_UINT16 MX_PWM_PERIOD_X = 65535;
MX_UINT16 MX_PWM_DUTY_X = 65535/2;

CALFUNCTION(void, FC_CAL_PWM_Enable_, (void))
{
	MX_UINT16 SliceNumber = pwm_gpio_to_slice_num(MX_PWM_PP_X);
	gpio_set_function(MX_PWM_PP_X, GPIO_FUNC_PWM);
	pwm_set_wrap(SliceNumber, MX_PWM_PERIOD_X);
	pwm_set_clkdiv_int_frac(SliceNumber, MX_PWM_PRESCALEX, 0);
	if ((MX_PWM_PP_X) & 1)
		pwm_set_chan_level(SliceNumber, PWM_CHAN_B, MX_PWM_DUTY_X);
	else
		pwm_set_chan_level(SliceNumber, PWM_CHAN_A, MX_PWM_DUTY_X);
	pwm_set_enabled(SliceNumber, true);
}

CALFUNCTION(void, FC_CAL_PWM_Disable_, (void))
{
	MX_UINT16 SliceNumber = pwm_gpio_to_slice_num(MX_PWM_PP_X);
	pwm_set_enabled(SliceNumber, false);
}

//Duty is specified as a floating point percentage 0.0 to 100.0
CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 duty))
{
	MX_UINT16 SliceNumber = pwm_gpio_to_slice_num(MX_PWM_PP_X);
	MX_PWM_DUTY_X = duty;
	if ((MX_PWM_PP_X) & 1)
		pwm_set_chan_level(SliceNumber, PWM_CHAN_B, MX_PWM_DUTY_X);
	else
		pwm_set_chan_level(SliceNumber, PWM_CHAN_A, MX_PWM_DUTY_X);
}

//Duty is specified as a 16-bit floating point percentage 0.0 to 100.0
CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 duty))
{
	MX_UINT16 SliceNumber = pwm_gpio_to_slice_num(MX_PWM_PP_X);
	MX_PWM_DUTY_X = duty;
	if ((MX_PWM_PP_X) & 1)
		pwm_set_chan_level(SliceNumber, PWM_CHAN_B, MX_PWM_DUTY_X);
	else
		pwm_set_chan_level(SliceNumber, PWM_CHAN_A, MX_PWM_DUTY_X);
}

CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 period, MX_UINT16 prescaler))
{
	MX_UINT16 SliceNumber = pwm_gpio_to_slice_num(MX_PWM_PP_X);
	if (prescaler == 0) prescaler = 1;
	MX_PWM_PERIOD_X = period;
	pwm_set_wrap(SliceNumber, MX_PWM_PERIOD_X);
	pwm_set_clkdiv_int_frac(SliceNumber, prescaler, 0);
}

CALFUNCTION(void, FC_CAL_PWM_ChangeFrequency_, (MX_UINT32 frequency))
{

}

//Duty is specified as a floating point percentage 0.0 to 100.0
CALFUNCTION(void, FC_CAL_PWM_SetDutyFloat_, (MX_FLOAT duty))
{

}

