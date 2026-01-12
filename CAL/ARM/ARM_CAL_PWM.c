// CRC: AE5753800093D2B889297C6B876B6A21749C10AFA09C3FCE4A5F65B0FF76818F0A7638C619EA04AA769141413688B2AC9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF574219D583FEB830D3A2063385FD65193036E5F4B5C8221DBDB9E79C6FC176F970EFD58CCE1277ECA0990E93806A150FAF12E90838C01804F94FBD89E80D3DCDD39C2FD8061CEF8AF3618FAEE8949FE961BB7874C60A8CA6C549D34A0D5AD11F3C15CD1A0D2368FF41B2E1F4369B16393705C4BBD8821F73B04789BB7D1BE12C9008FFBF4203128CD
// REVISION: 1.0
// GUID: CB29CE02-A3B2-465C-B3D2-B6BDAA2B84F4
// DATE: 08\08\2022
// DIR: CAL\ARM\ARM_CAL_PWM.c
/*********************************************************************
 *                  Flowcode CAL PWM File
 *
 * File: ARM_CAL_PWM.c
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
 * 270911 | BR | Created
 * 050312 | BR | Updated to v5.1 CAL Schema
 * 190712 | BR | Fixed a bug where the PWM frequency and the prescaler were not being passed correctly to the register
 * 030713 | LM | Standard API calls
 */


#define MX_PWM_CHANNEL_X		CAL_APPEND(MX_PWM_CHANNEL_, MX_PWM_NUM)
#define MX_PWM_HWALT_X			CAL_APPEND(MX_PWM_HWALT_, MX_PWM_NUM)
#define MX_PWM_PORT_X			CAL_APPEND(MX_PWM_PORT_, MX_PWM_NUM)
#define MX_PWM_TRIS_X			CAL_APPEND(MX_PWM_TRIS_, MX_PWM_NUM)
#define MX_PWM_PIN_X			CAL_APPEND(MX_PWM_PIN_, MX_PWM_NUM)

//I2C Master Functions
CALFUNCTION(void, FC_CAL_PWM_Enable_, (void));
CALFUNCTION(void, FC_CAL_PWM_Disable_, (void));
CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 duty));
CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 period, MX_UINT16 prescaler));
CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 duty));


CALFUNCTION(void, FC_CAL_PWM_Enable_, (void))
{
 #ifdef MX_PWM

 	AT91F_PWMC_CfgPMC();												// Enable system clock for PWM peripheral

	#if (MX_PWM_CHANNEL_X == 1)

		#ifndef MX_PWM_PORT_X											//Error checking
			#error "This chip does not have PWM channel 1 defined"
		#endif

		//FC_CAL_Bit_Low_DDR (MX_PWM_PORT_X, MX_PWM_TRIS_X, MX_PWM_PIN_X);			//PWM pin is an output

		AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, AT91C_PA0_PWM0);
		AT91F_PWMC_CfgChannel(AT91C_BASE_PWMC, 0, 0x020b, 255, 2);		// Set channel parameters
		AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA0_PWM0, 0);		// Configure PWM CH0 output
	#endif

	#if (MX_PWM_CHANNEL_X == 2)

		#ifndef MX_PWM_PORT_X											//Error checking
			#error "This chip does not have PWM channel 2 defined"
		#endif

		//FC_CAL_Bit_Low_DDR (MX_PWM_PORT_X, MX_PWM_TRIS_X, MX_PWM_PIN_X);			//PWM pin is an output

		AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, AT91C_PA1_PWM1);
		AT91F_PWMC_CfgChannel(AT91C_BASE_PWMC, 1, 0x020b, 255, 2);		// Set channel parameters
		AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA1_PWM1, 0);		// Configure PWM CH1 output
	#endif

	#if (MX_PWM_CHANNEL_X == 3)

		#ifndef MX_PWM_PORT_X											//Error checking
			#error "This chip does not have PWM channel 3 defined"
		#endif

		//FC_CAL_Bit_Low_DDR (MX_PWM_PORT_X, MX_PWM_TRIS_X, MX_PWM_PIN_X);			//PWM pin is an output

		AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, AT91C_PA2_PWM2);
		AT91F_PWMC_CfgChannel(AT91C_BASE_PWMC, 2, 0x020b, 255, 2);		// Set channel parameters
		AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA2_PWM2, 0);		// Configure PWM CH2 output
	#endif

	#if (MX_PWM_CHANNEL_X == 4)

		#ifndef MX_PWM_PORT_X											//Error checking
			#error "This chip does not have PWM channel 4 defined"
		#endif

		//FC_CAL_Bit_Low_DDR (MX_PWM_PORT_X, MX_PWM_TRIS_X, MX_PWM_PIN_X);			//PWM pin is an output

		AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, AT91C_PA7_PWM3);
		AT91F_PWMC_CfgChannel(AT91C_BASE_PWMC, 3, 0x020b, 255, 2);		// Set channel parameters
		AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA7_PWM3, 0);		// Configure PWM CH3 output
	#endif
 #else
 	#error "Hardware PWM not supported by Target microcontroller."
 #endif
}


CALFUNCTION(void, FC_CAL_PWM_Disable_, (void))
{
	#if (MX_PWM_CHANNEL_X == 1)
		AT91F_PWMC_StopChannel(AT91C_BASE_PWMC, 0x01);
	#endif

	#if (MX_PWM_CHANNEL_X == 2)
		AT91F_PWMC_StopChannel(AT91C_BASE_PWMC, 0x02);
	#endif

	#if (MX_PWM_CHANNEL_X == 3)
		AT91F_PWMC_StopChannel(AT91C_BASE_PWMC, 0x04);
	#endif

	#if (MX_PWM_CHANNEL_X == 4)
		AT91F_PWMC_StopChannel(AT91C_BASE_PWMC, 0x08);
	#endif
}


CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 duty))
{
	#if (MX_PWM_CHANNEL_X == 1)
		AT91C_BASE_PWMC->PWMC_CH[0].PWMC_CMR &= ~0x0400;				// Set update to duty cycle
		if(duty < 2)
		{
			AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, AT91C_PA0_PWM0);		// Disconnect PWM CH0 output
			AT91F_PWMC_StopChannel(AT91C_BASE_PWMC, 0x01);				// Stop PWM CH0
		}
		else
		{
			AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 0, duty);
			AT91F_PWMC_StartChannel(AT91C_BASE_PWMC, 0x01);
			AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA0_PWM0, 0);	// Configure PWM CH0 output
		}
	#endif

	#if (MX_PWM_CHANNEL_X == 2)
		AT91C_BASE_PWMC->PWMC_CH[1].PWMC_CMR &= ~0x0400;				// Set update to duty cycle
		if(duty < 2)
		{
			AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, AT91C_PA1_PWM1);
			AT91F_PWMC_StopChannel(AT91C_BASE_PWMC, 0x02);
		}
		else
		{
			AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 1, duty);
			AT91F_PWMC_StartChannel(AT91C_BASE_PWMC, 0x02);
			AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA1_PWM1, 0);	// Configure PWM CH1 output
		}
	#endif

	#if (MX_PWM_CHANNEL_X == 3)
		AT91C_BASE_PWMC->PWMC_CH[2].PWMC_CMR &= ~0x0400;				// Set update to duty cycle
		if(duty < 2)
		{
			AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, AT91C_PA2_PWM2);
			AT91F_PWMC_StopChannel(AT91C_BASE_PWMC, 0x04);
		}
		else
		{
			AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 2, duty);
			AT91F_PWMC_StartChannel(AT91C_BASE_PWMC, 0x04);
			AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA2_PWM2, 0);	// Configure PWM CH2 output
		}
	#endif

	#if (MX_PWM_CHANNEL_X == 4)
		AT91C_BASE_PWMC->PWMC_CH[3].PWMC_CMR &= ~0x0400;				// Set update to duty cycle
		if(duty < 2)
		{
			AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, AT91C_PA7_PWM3);
			AT91F_PWMC_StopChannel(AT91C_BASE_PWMC, 0x08);
		}
		else
		{
			AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 3, duty);
			AT91F_PWMC_StartChannel(AT91C_BASE_PWMC, 0x08);
			AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA7_PWM3, 0);	// Configure PWM CH3 output
		}
	#endif
}


CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 period, MX_UINT16 prescaler))
{
	unsigned char prescale_val = 0;

  #ifdef MX_PWM

	if (prescaler == 1)
		prescale_val = 0;
	if (prescaler == 2)
		prescale_val = 1;
	if (prescaler == 4)
		prescale_val = 2;
	if (prescaler == 8)
		prescale_val = 3;
	if (prescaler == 16)
		prescale_val = 4;
	if (prescaler == 32)
		prescale_val = 5;
	if (prescaler == 64)
		prescale_val = 6;
	if (prescaler == 128)
		prescale_val = 7;
	if (prescaler == 256)
		prescale_val = 8;
	if (prescaler == 512)
		prescale_val = 9;
	if (prescaler == 1024)
		prescale_val = 10;

  	#if (MX_PWM_CHANNEL_X == 1)
    	AT91C_BASE_PWMC->PWMC_CH[0].PWMC_CMR |= 0x0400;				// Set update to period
    	AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 0, period);
    	AT91C_BASE_PWMC->PWMC_MR = 0x01 | (prescale_val << 8);		// Configure clock dividers
    #endif
    #if (MX_PWM_CHANNEL_X == 2)
  		AT91C_BASE_PWMC->PWMC_CH[1].PWMC_CMR |= 0x0400;				// Set update to period
  		AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 1, period);
  		AT91C_BASE_PWMC->PWMC_MR = 0x02 | (prescale_val << 8);		// Configure clock dividers
    #endif
  	#if (MX_PWM_CHANNEL_X == 3)
  		AT91C_BASE_PWMC->PWMC_CH[2].PWMC_CMR |= 0x0400;				// Set update to period
  		AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 2, period);
  		AT91C_BASE_PWMC->PWMC_MR = 0x04 | (prescale_val << 8);		// Configure clock dividers
    #endif
  	#if (MX_PWM_CHANNEL_X == 4)
  		AT91C_BASE_PWMC->PWMC_CH[3].PWMC_CMR |= 0x0400;				// Set update to period
  		AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 3, period);
  		AT91C_BASE_PWMC->PWMC_MR = 0x08 | (prescale_val << 8);		// Configure clock dividers
    #endif

  #endif
}


CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 duty))
{
	duty = (duty >> 2) & 0xff;

	#if (MX_PWM_CHANNEL_X == 1)
		AT91C_BASE_PWMC->PWMC_CH[0].PWMC_CMR &= ~0x0400;				// Set update to duty cycle
		if(duty < 2)
		{
			AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, AT91C_PA0_PWM0);		// Disconnect PWM CH0 output
			AT91F_PWMC_StopChannel(AT91C_BASE_PWMC, 0x01);				// Stop PWM CH0
		}
		else
		{
			AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 0, duty);
			AT91F_PWMC_StartChannel(AT91C_BASE_PWMC, 0x01);
			AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA0_PWM0, 0);	// Configure PWM CH0 output
		}
	#endif

	#if (MX_PWM_CHANNEL_X == 2)
		AT91C_BASE_PWMC->PWMC_CH[1].PWMC_CMR &= ~0x0400;				// Set update to duty cycle
		if(duty < 2)
		{
			AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, AT91C_PA1_PWM1);
			AT91F_PWMC_StopChannel(AT91C_BASE_PWMC, 0x02);
		}
		else
		{
			AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 1, duty);
			AT91F_PWMC_StartChannel(AT91C_BASE_PWMC, 0x02);
			AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA1_PWM1, 0);	// Configure PWM CH1 output
		}
	#endif

	#if (MX_PWM_CHANNEL_X == 3)
		AT91C_BASE_PWMC->PWMC_CH[2].PWMC_CMR &= ~0x0400;				// Set update to duty cycle
		if(duty < 2)
		{
			AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, AT91C_PA2_PWM2);
			AT91F_PWMC_StopChannel(AT91C_BASE_PWMC, 0x04);
		}
		else
		{
			AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 2, duty);
			AT91F_PWMC_StartChannel(AT91C_BASE_PWMC, 0x04);
			AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA2_PWM2, 0);	// Configure PWM CH2 output
		}
	#endif

	#if (MX_PWM_CHANNEL_X == 4)
		AT91C_BASE_PWMC->PWMC_CH[3].PWMC_CMR &= ~0x0400;				// Set update to duty cycle
		if(duty < 2)
		{
			AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, AT91C_PA7_PWM3);
			AT91F_PWMC_StopChannel(AT91C_BASE_PWMC, 0x08);
		}
		else
		{
			AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 3, duty);
			AT91F_PWMC_StartChannel(AT91C_BASE_PWMC, 0x08);
			AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA7_PWM3, 0);	// Configure PWM CH3 output
		}
	#endif
}

