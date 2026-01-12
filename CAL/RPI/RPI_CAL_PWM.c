// CRC: 34358081B117C27F7D8358E612878F8E5F343B66182D417818220CB9C07676CF0A7638C619EA04AA769141413688B2AC9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5FAACAAAD666044DB9C3338CDB1E23B0A1792A6BCB0979524B6C1A4A83F9EA7D410072FEF5008875B17E65E63C98A054EC34171883EDF2B88FAD34A363326A20E4637597E94C50C5B15BA95265262E81E6897A1C64EC68459549D34A0D5AD11F34BA08B7FBC740119C9BDAB401E5E66CD2CAE0C83C56D9AC82FFEDCC693330B04B4FCFC5DE34EB9BE
// REVISION: 1.0
// GUID: 53CFD83B-7E91-4E4F-AFC5-09B9D1E14C14
// DATE: 08\08\2022
// DIR: CAL\RPI\RPI_CAL_PWM.c
/*********************************************************************
 *                  Flowcode CAL PWM File
 *
 * File: RPI_CAL_PWM.c
 *
 * (c) 2011-2018 Matrix TSL
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
 * 100118 | LM | Created from PIC PWM
 *
 */

/********************************************************************
Notes:
The PWM clock is 19.2 MHz
Valid values for prescaler are 2 to 4095
As /1 is not allowed I've set the FCD divider to 2 
and multiply the prescaler value by 2 in this CAL code
********************************************************************/
 
#define MX_PWM_CHANNEL_X	CAL_APPEND(MX_PWM_CHANNEL_, MX_PWM_NUM)
#define MX_PWM_PIN_X		CAL_APPEND(MX_PWM_PIN_, 	MX_PWM_NUM)
#define MX_PWM_PORT_X		CAL_APPEND(MX_PWM_PORT_, 	MX_PWM_NUM)

// Now for some pin mangling for BL0036 :O) ...
#if (MX_PWM_PORT_X == PORTD)
	#if   (MX_PWM_PIN_X == 0)
		#define MX_PWM_GPIO_X	MX_PORTD0_GPIO
	#elif (MX_PWM_PIN_X == 1)
		#define MX_PWM_GPIO_X	MX_PORTD1_GPIO
	#elif (MX_PWM_PIN_X == 2)
		#define MX_PWM_GPIO_X	MX_PORTD2_GPIO
	#elif (MX_PWM_PIN_X == 4)
		#define MX_PWM_GPIO_X	MX_PORTD4_GPIO
	#endif
#endif
#ifndef MX_PWM_GPIO_X
	// Nothing defined for that Port/Pin
	// Or we have GPIO numbers anyway (Port G)
	#define MX_PWM_GPIO_X MX_PWM_PIN_X
#endif


CALFUNCTION(void, FC_CAL_PWM_Enable_, (void));
CALFUNCTION(void, FC_CAL_PWM_Disable_, (void));
CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 duty));
CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 period, MX_UINT16 prescaler));
CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 duty));


CALFUNCTION(void, FC_CAL_PWM_Enable_, (void))
{
	#if (MX_PWM_CHANNEL_X == 1)||(MX_PWM_CHANNEL_X == 2)
	// get the PWM register map
	MX_UINT32 *pwm_map = FC_CAL_GetRegisterMap(MX_REGISTER_MAP_PWM);
	if (pwm_map != MAP_FAILED)
	{
		// set pin to PWM alt
		#if (MX_PWM_GPIO_X == 12)||(MX_PWM_GPIO_X == 13)
			MX_GPIO_ALT(MX_PWM_GPIO_X, 0);
		#endif
		#if (MX_PWM_GPIO_X == 18)||(MX_PWM_GPIO_X == 19)
			MX_GPIO_ALT(MX_PWM_GPIO_X, 5);
		#endif
		#if (MX_PWM_CHANNEL_X == 1)
			// set PWM M/S mode and enable channel 1
			pwm_map[0] |= 0x0081;
		#else
			// set PWM M/S mode and enable channel 2
			pwm_map[0] |= 0x8100;
		#endif
		// release resources
		munmap((void *)pwm_map, getpagesize());
	}
	#endif
}


CALFUNCTION(void, FC_CAL_PWM_Disable_, (void))
{
	#if (MX_PWM_CHANNEL_X == 1)||(MX_PWM_CHANNEL_X == 2)
	// Set PWM pin to an input
	MX_GPIO_IN(MX_PWM_GPIO_X);		
	// Get the PWM register map
	MX_UINT32 *pwm_map = FC_CAL_GetRegisterMap(MX_REGISTER_MAP_PWM);
	if (pwm_map != MAP_FAILED)
	{
		#if (MX_PWM_CHANNEL_X == 1)
			// Disable channel 1
			pwm_map[0] &= ~0x0001;
		#else
			// Disable channel 2
			pwm_map[0] &= ~0x0100;
		#endif
		// Release resources
		munmap((void *)pwm_map, getpagesize());
	}
	#endif
}


CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 duty))
{
	#if (MX_PWM_CHANNEL_X == 1)||(MX_PWM_CHANNEL_X == 2)
	// Get the PWM register map
	MX_UINT32 *pwm_map = FC_CAL_GetRegisterMap(MX_REGISTER_MAP_PWM);
	if (pwm_map != MAP_FAILED)
	{
		// Set the period (M)
		#if (MX_PWM_CHANNEL_X == 1)
			pwm_map[5] = duty;
		#else
			pwm_map[9] = duty;
		#endif
		// Release resources
		munmap((void *)pwm_map, getpagesize());
	}
	#endif
}


CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 period, MX_UINT16 prescaler))
{
	#if (MX_PWM_CHANNEL_X == 1)||(MX_PWM_CHANNEL_X == 2)
	MX_UINT32 *clk_map = FC_CAL_GetRegisterMap(MX_REGISTER_MAP_CLOCK);
	if (clk_map != MAP_FAILED)
	{
		clk_map[40] = 0x5A000000 | 1;
		usleep(100);
		while(clk_map[40] & 0x80) usleep(1);
		// the prescaler is at << 12, but we multiply prescaler by 2, as value 1 not allowed
		clk_map[41] = 0x5A000000 | (prescaler << 13);
		clk_map[40] = 0x5A000000 | 0x11;
		// release resources
		munmap((void *)clk_map, getpagesize());
	}

	// Get the PWM register map
	MX_UINT32 *pwm_map = FC_CAL_GetRegisterMap(MX_REGISTER_MAP_PWM);
	if (pwm_map != MAP_FAILED)
	{
		// Set the period (S)
		#if (MX_PWM_CHANNEL_X == 1)
			pwm_map[4] = period;
		#else
			pwm_map[8] = period;
		#endif
		// Release resources
		munmap((void *)pwm_map, getpagesize());
	}
	#endif
}


CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 duty))
{
	#if (MX_PWM_CHANNEL_X == 1)||(MX_PWM_CHANNEL_X == 2)
	// Get the PWM register map
	MX_UINT32 *pwm_map = FC_CAL_GetRegisterMap(MX_REGISTER_MAP_PWM);
	if (pwm_map != MAP_FAILED)
	{
		// Set the period (M)
		#if (MX_PWM_CHANNEL_X == 1)
			pwm_map[5] = duty;
		#else
			pwm_map[9] = duty;
		#endif
		// Release resources
		munmap((void *)pwm_map, getpagesize());
	}
	#endif
}

#undef MX_PWM_GPIO_X

