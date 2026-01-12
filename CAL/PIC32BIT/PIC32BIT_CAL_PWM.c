// CRC: A6459004C43C0517DC6DFC5681C2AD698104299A14C9E1875427A2F7EF4303D9CFD76A29863CD488DE50EA9D9C0AC8D15ADEA58BF22D39D590A3838BC969E07E9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF58677B4D785B632095C97D0667C7296B426E08F24B144E6AA4819C3BBCF6090F4059B25CEB18DBF3E7F2A279792AEB805FE16ACDA26BEC51DD5EC012CA9E04290D2E85E142E7E6C63C2F2E68C186BE94C6E20EB16C570132F549D34A0D5AD11F334E917E03F440EF59CCDF539CF1AE25E93A4814833AAD64C3E7DF3EE771A32107C30AF6F6246FD52
// REVISION: 1.0
// GUID: A4C52461-8FA8-4869-88E0-3BBDD4C066EC
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\PIC32BIT_CAL_PWM.c
/*********************************************************************
 *                  Flowcode CAL PWM File
 *
 * File: PIC16BIT_CAL_PWM.c
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
 * 041011 | BR | Created
 * 050312 | BR | Updated to v5.1 CAL Schema
 * 290812 | BR | Added new FCD supplied code and upped max PWM count from 10 to 16
 * 040912 | BR | Added the MX_OCx definition to allow all families to work
 * 280912 | BR | Fixed an issue with PWM remappable defines
 * 011012 | BR | Added workaround for non working PWM on EP devices
 * 030713 | LM | Standard API calls
 * 030615 | BR | PWM Allocated Timer
 */


#define MX_PWM_CHANNEL_X		CAL_APPEND(MX_PWM_CHANNEL_, MX_PWM_NUM)
#define MX_PWM_HWALT_X			CAL_APPEND(MX_PWM_HWALT_, 	MX_PWM_NUM)
#define MX_PWM_PORT_X			CAL_APPEND(MX_PWM_PORT_, 	MX_PWM_NUM)
#define MX_PWM_TRIS_X			CAL_APPEND(MX_PWM_TRIS_, 	MX_PWM_NUM)
#define MX_PWM_PIN_X			CAL_APPEND(MX_PWM_PIN_, 	MX_PWM_NUM)
#define MX_PWM_RPOR_X			CAL_APPEND(MX_PWM_RPOR_, 	MX_PWM_NUM)
#define MX_PWM_RPOC_X			CAL_APPEND(MX_PWM_RPOC_, 	MX_PWM_NUM)
#define MX_PWM_TMR_X			CAL_APPEND(MX_PWM_TMR_, 	MX_PWM_NUM)


//I2C Master Functions
CALFUNCTION(void, FC_CAL_PWM_Enable_, (void));
CALFUNCTION(void, FC_CAL_PWM_Disable_, (void));
CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 duty));
CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 period, MX_UINT16 prescaler));
CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 duty));



CALFUNCTION(void, FC_CAL_PWM_Enable_, (void))
{

  #ifdef MX_PWM

	//Remappable PWM Functionality
	#ifdef MX_PWM_REMAPPABLE
		MX_PWM_RPOR_X = MX_PWM_RPOC_X;											//Assign PWM Channel OCx -> RPx - See FCD Defines For Info
	#endif

	#if (MX_PWM_HWALT_X == 0)													//Default PWM Pin
	  #ifndef MX_PWM_PORT_X														//Error checking
		#error "This chip does not have PWM channel 1 defined"
	  #endif
		FC_CAL_Bit_Low_DDR (MX_PWM_PORT_X, MX_PWM_TRIS_X, MX_PWM_PIN_X);		//PWM pin is an output
	#else																		//Alternate PWM Pin
	  #ifndef MX_PWM_PORTA_X													//Error checking
		#error "This chip does not have PWM alt channel 1 defined"
	  #endif
		FC_CAL_Bit_Low_DDR (MX_PWM_PORTA_A, MX_PWM_TRISA_X, MX_PWM_PINA_X);		//PWM pin is an output
	#endif

	#if (MX_PWM_CHANNEL_X > 0)

		_SFR_WRITE(&OC1RS + (0x80*(MX_PWM_CHANNEL_X-1)), 0);
		_SFR_WRITE(&OC1CON + (0x80*(MX_PWM_CHANNEL_X-1)), 0x8006); // OCM = 6, OC32 = 0

    	#if (MX_PWM_TMR_X == 2)
    		_SFR_BIT_CLEAR(&OC1CON + (0x80*(MX_PWM_CHANNEL_X-1)),3);	//Timer 2
    	#else
    		_SFR_BIT_SET(&OC1CON + (0x80*(MX_PWM_CHANNEL_X-1)),3);	//Timer 3
    	#endif
	#endif

  #else
 	#error "Hardware PWM not supported by Target microcontroller."
  #endif
}


CALFUNCTION(void, FC_CAL_PWM_Disable_, (void))
{

	#if (MX_PWM_HWALT_X == 0)														//Default PWM Pin
		FC_CAL_Bit_In_DDR (MX_PWM_PORT_X, MX_PWM_TRIS_X, MX_PWM_PIN_X);				//PWM pin is an input
	#else																			//Alternate PWM Pin
		FC_CAL_Bit_In_DDR (MX_PWM_PORTA_X, MX_PWM_TRISA_X, MX_PWM_PINA_X);			//PWM pin is an input
	#endif


	#if (MX_PWM_CHANNEL_X > 0)
		_SFR_WRITE(&OC1CON + (0x80*(MX_PWM_CHANNEL_X-1)), 0);																	//Disable Capture Compare Channel 1
	#endif
}


CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 nDuty))
{
	if (nDuty == 0)
		nDuty = 1;

	#if (MX_PWM_CHANNEL_X == 1)
		_SFR_WRITE(&OC1RS + (0x80*(MX_PWM_CHANNEL_X-1)), nDuty);
	#endif

}


CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 period, MX_UINT16 prescaler))
{
  #ifdef MX_PWM								//Hardware Mode

	#if (MX_PWM_TMR_X > 0)
	_SFR_WRITE(&PR1 + (0x80*(MX_PWM_TMR_X-1)), period);
		switch (prescaler)
		{
			default:
				_SFR_WRITE(&T1CON + (0x80*(MX_PWM_TMR_X-1)), 0x8000);
				break;
			case 2:
				_SFR_WRITE(&T1CON + (0x80*(MX_PWM_TMR_X-1)), 0x8010);
				break;
			case 4:
				_SFR_WRITE(&T1CON + (0x80*(MX_PWM_TMR_X-1)), 0x8020);
				break;
			case 8:
				_SFR_WRITE(&T1CON + (0x80*(MX_PWM_TMR_X-1)), 0x8030);
				break;
			case 16:
				_SFR_WRITE(&T1CON + (0x80*(MX_PWM_TMR_X-1)), 0x8040);
				break;
			case 32:
				_SFR_WRITE(&T1CON + (0x80*(MX_PWM_TMR_X-1)), 0x8050);
				break;
			case 64:
				_SFR_WRITE(&T1CON + (0x80*(MX_PWM_TMR_X-1)), 0x8060);
				break;
			case 256:
				_SFR_WRITE(&T1CON + (0x80*(MX_PWM_TMR_X-1)), 0x8070);
				break;
		}
	#endif
  #endif
}


CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 duty))
{
	if (duty < 1)
		duty = 1;

	#if (MX_PWM_CHANNEL_X > 0)
		_SFR_WRITE(&OC1RS + (0x80*(MX_PWM_CHANNEL_X-1)), duty);
	#endif
}

