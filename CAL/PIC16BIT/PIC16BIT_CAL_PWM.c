// CRC: 5D982BB222882C54AB4AFF20A1590FC484D3178BD0D2510D0F5A64A7853221CAE2C33FABBE4F69A6659399D51781B7B95ADEA58BF22D39D590A3838BC969E07E9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF547B6B8D095CB5EA58BB3B5ABF31FF032E0F8C0E46555C98E5C45AEABB8BE0CC1405E92C081F7A2F6B16364E5CD9693DC68B060F90DF143C20939CEECB23C22A76351A8083202767EA4D4EA0CCFA744771305807E2524C86E549D34A0D5AD11F3F32ED31E6C2F3EC37738B5B9A6EA1A86C9F1E9E536E3CDCA6DAE80F1ED87A78E40144AF09ADB914F
// REVISION: 1.0
// GUID: 6E689F93-BA74-403F-BF47-1D091BCDF740
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\PIC16BIT_CAL_PWM.c
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

	#if (MX_PWM_CHANNEL_X == 1)

		#ifdef MX_PWM_OCxCON
			#define OC1CON OC1CON1
			#define MXWA
		#endif

		OC1RS = 0;																//Enable Capture Compare Channel 1
		OC1R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC1CON = 0x1005;
				OC1CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC1CON = 0x0005;
				OC1CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC1CON = 0x0405;
				OC1CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC1CON = 0x0805;
				OC1CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC1CON = 0x0C05;
				OC1CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC1CON = 0x0006;		//Timer 2
        	#else
        		OC1CON = 0x000E;		//Timer 3
        	#endif
        #endif
	#endif

	#if (MX_PWM_CHANNEL_X == 2)

		#ifdef MX_PWM_OCxCON
			#define OC2CON OC2CON1
			#define MXWA
			OC2CON2 = 0x000C;			//Timer 2 is clock source
		#endif

		OC2RS = 0;																//Enable Capture Compare Channel 2
		OC2R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC2CON = 0x1005;
				OC2CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC2CON = 0x0005;
				OC2CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC2CON = 0x0405;
				OC2CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC2CON = 0x0805;
				OC2CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC2CON = 0x0C05;
				OC2CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC2CON = 0x0006;		//Timer 2
        	#else
        		OC2CON = 0x000E;		//Timer 3
        	#endif
        #endif
	#endif

	#if (MX_PWM_CHANNEL_X == 3)

		#ifdef MX_PWM_OCxCON
			#define OC3CON OC3CON1
			#define MXWA
			OC3CON2 = 0x000C;			//Timer 2 is clock source
		#endif

		OC3RS = 0;																//Enable Capture Compare Channel 3
		OC3R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC3CON = 0x1005;
				OC3CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC3CON = 0x0005;
				OC3CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC3CON = 0x0405;
				OC3CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC3CON = 0x0805;
				OC3CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC3CON = 0x0C05;
				OC3CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC3CON = 0x0006;		//Timer 2
        	#else
        		OC3CON = 0x000E;		//Timer 3
        	#endif
        #endif
	#endif

	#if (MX_PWM_CHANNEL_X == 4)

		#ifdef MX_PWM_OCxCON
			#define OC4CON OC4CON1
			#define MXWA
			OC4CON2 = 0x000C;			//Timer 2 is clock source
		#endif

		OC4RS = 0;																//Enable Capture Compare Channel 4
		OC4R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC4CON = 0x1005;
				OC4CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC4CON = 0x0005;
				OC4CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC4CON = 0x0405;
				OC4CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC4CON = 0x0805;
				OC4CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC4CON = 0x0C05;
				OC4CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC4CON = 0x0006;		//Timer 2
        	#else
        		OC4CON = 0x000E;		//Timer 3
        	#endif
        #endif
	#endif

	#if (MX_PWM_CHANNEL_X == 5)

		#ifdef MX_PWM_OCxCON
			#define OC5CON OC5CON1
			#define MXWA
			OC5CON2 = 0x000C;			//Timer 2 is clock source
		#endif

		OC5RS = 0;																//Enable Capture Compare Channel 5
		OC5R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC5CON = 0x1005;
				OC5CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC5CON = 0x0005;
				OC5CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC5CON = 0x0405;
				OC5CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC5CON = 0x0805;
				OC5CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC5CON = 0x0C05;
				OC5CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC5CON = 0x0006;		//Timer 2
        	#else
        		OC5CON = 0x000E;		//Timer 3
        	#endif
        #endif
	#endif

	#if (MX_PWM_CHANNEL_X == 6)

		#ifdef MX_PWM_OCxCON
			#define OC6CON OC6CON1
			#define MXWA
			OC6CON2 = 0x000C;			//Timer 2 is clock source
		#endif

		OC6RS = 0;																//Enable Capture Compare Channel 6
		OC6R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC6CON = 0x1005;
				OC6CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC6CON = 0x0005;
				OC6CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC6CON = 0x0405;
				OC6CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC6CON = 0x0805;
				OC6CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC6CON = 0x0C05;
				OC6CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC6CON = 0x0006;		//Timer 2
        	#else
        		OC6CON = 0x000E;		//Timer 3
        	#endif
        #endif
	#endif

	#if (MX_PWM_CHANNEL_X == 7)

		#ifdef MX_PWM_OCxCON
			#define OC7CON OC7CON1
			#define MXWA
			OC7CON2 = 0x000C;			//Timer 2 is clock source
		#endif

		OC7RS = 0;																//Enable Capture Compare Channel 7
		OC7R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC7CON = 0x1005;
				OC7CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC7CON = 0x0005;
				OC7CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC7CON = 0x0405;
				OC7CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC7CON = 0x0805;
				OC7CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC7CON = 0x0C05;
				OC7CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC7CON = 0x0006;		//Timer 2
        	#else
        		OC7CON = 0x000E;		//Timer 3
        	#endif
        #endif
	#endif

	#if (MX_PWM_CHANNEL_X == 8)

		#ifdef MX_PWM_OCxCON
			#define OC8CON OC8CON1
			#define MXWA
			OC8CON2 = 0x000C;			//Timer 2 is clock source
		#endif

		OC8RS = 0;																//Enable Capture Compare Channel 8
		OC8R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC8CON = 0x1005;
				OC8CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC8CON = 0x0005;
				OC8CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC8CON = 0x0405;
				OC8CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC8CON = 0x0805;
				OC8CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC8CON = 0x0C05;
				OC8CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC8CON = 0x0006;		//Timer 2
        	#else
        		OC8CON = 0x000E;		//Timer 3
        	#endif
        #endif
	#endif

	#if (MX_PWM_CHANNEL_X == 9)

		#ifdef MX_PWM_OCxCON
			#define OC9CON OC9CON1
			#define MXWA
			OC9CON2 = 0x000C;			//Timer 2 is clock source
		#endif

		OC9RS = 0;																//Enable Capture Compare Channel 9
		OC9R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC9CON = 0x1005;
				OC9CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC9CON = 0x0005;
				OC9CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC9CON = 0x0405;
				OC9CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC9CON = 0x0805;
				OC9CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC9CON = 0x0C05;
				OC9CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC9CON = 0x0006;		//Timer 2
        	#else
        		OC9CON = 0x000E;		//Timer 3
        	#endif
        #endif
	#endif

	#if (MX_PWM_CHANNEL_X == 10)

		#ifdef MX_PWM_OCxCON
			#define OC10CON OC10CON1
			#define MXWA
			OC10CON2 = 0x000C;			//Timer 2 is clock source
		#endif

		OC10RS = 0;																//Enable Capture Compare Channel 10
		OC10R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC10CON = 0x1005;
				OC10CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC10CON = 0x0005;
				OC10CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC10CON = 0x0405;
				OC10CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC10CON = 0x0805;
				OC10CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC10CON = 0x0C05;
				OC10CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC10CON = 0x0006;		//Timer 2
        	#else
        		OC10CON = 0x000E;		//Timer 3
        	#endif
        #endif
	#endif

	#if (MX_PWM_CHANNEL_X == 11)

		#ifdef MX_PWM_OCxCON
			#define OC11CON OC11CON1
			#define MXWA
			OC11CON2 = 0x000C;			//Timer 2 is clock source
		#endif

		OC11RS = 0;																//Enable Capture Compare Channel 11
		OC11R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC11CON = 0x1005;
				OC11CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC11CON = 0x0005;
				OC11CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC11CON = 0x0405;
				OC11CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC11CON = 0x0805;
				OC11CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC11CON = 0x0C05;
				OC11CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC11CON = 0x0006;		//Timer 2
        	#else
        		OC11CON = 0x000E;		//Timer 3
        	#endif
        #endif
	#endif

	#if (MX_PWM_CHANNEL_X == 12)

		#ifdef MX_PWM_OCxCON
			#define OC12CON OC12CON1
			#define MXWA
			OC12CON2 = 0x000C;			//Timer 2 is clock source
		#endif

		OC12RS = 0;																//Enable Capture Compare Channel 12
		OC12R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC12CON = 0x1005;
				OC12CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC12CON = 0x0005;
				OC12CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC12CON = 0x0405;
				OC12CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC12CON = 0x0805;
				OC12CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC12CON = 0x0C05;
				OC12CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC12CON = 0x0006;		//Timer 2
        	#else
        		OC12CON = 0x000E;		//Timer 3
        	#endif
        #endif
	#endif

	#if (MX_PWM_CHANNEL_X == 13)

		#ifdef MX_PWM_OCxCON
			#define OC13CON OC13CON1
			#define MXWA
			OC13CON2 = 0x000C;			//Timer 2 is clock source
		#endif

		OC13RS = 0;																//Enable Capture Compare Channel 13
		OC13R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC13CON = 0x1005;
				OC13CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC13CON = 0x0005;
				OC13CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC13CON = 0x0405;
				OC13CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC13CON = 0x0805;
				OC13CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC13CON = 0x0C05;
				OC13CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC13CON = 0x0006;		//Timer 2
        	#else
        		OC13CON = 0x000E;		//Timer 3
        	#endif
        #endif
	#endif

	#if (MX_PWM_CHANNEL_X == 14)

		#ifdef MX_PWM_OCxCON
			#define OC14CON OC14CON1
			#define MXWA
			OC14CON2 = 0x000C;			//Timer 2 is clock source
		#endif

		OC14RS = 0;																//Enable Capture Compare Channel 14
		OC14R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC14CON = 0x1005;
				OC14CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC14CON = 0x0005;
				OC14CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC14CON = 0x0405;
				OC14CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC14CON = 0x0805;
				OC14CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC14CON = 0x0C05;
				OC14CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC14CON = 0x0006;		//Timer 2
        	#else
        		OC14CON = 0x000E;		//Timer 3
        	#endif
        #endif
	#endif

	#if (MX_PWM_CHANNEL_X == 15)

		#ifdef MX_PWM_OCxCON
			#define OC15CON OC15CON1
			#define MXWA
			OC15CON2 = 0x000C;			//Timer 2 is clock source
		#endif

		OC15RS = 0;																//Enable Capture Compare Channel 15
		OC15R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC15CON = 0x1005;
				OC15CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC15CON = 0x0005;
				OC15CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC15CON = 0x0405;
				OC15CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC15CON = 0x0805;
				OC15CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC15CON = 0x0C05;
				OC15CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC15CON = 0x0006;		//Timer 2
        	#else
        		OC15CON = 0x000E;		//Timer 3
        	#endif
        #endif
	#endif

	#if (MX_PWM_CHANNEL_X == 16)

		#ifdef MX_PWM_OCxCON
			#define OC16CON OC16CON1
			#define MXWA
			OC16CON2 = 0x000C;			//Timer 2 is clock source
		#endif

		OC16RS = 0;																//Enable Capture Compare Channel 16
		OC16R = 0;

		#ifdef MXWA
			#if (MX_PWM_TMR_X == 1)		//Timer 1 is clock source
				OC16CON = 0x1005;
				OC16CON2 = 0x000B;
			#endif
			#if (MX_PWM_TMR_X == 2)		//Timer 2 is clock source
				OC16CON = 0x0005;
				OC16CON2 = 0x000C;
			#endif
			#if (MX_PWM_TMR_X == 3)		//Timer 3 is clock source
				OC16CON = 0x0405;
				OC16CON2 = 0x000D;
			#endif
			#if (MX_PWM_TMR_X == 4)		//Timer 4 is clock source
				OC16CON = 0x0805;
				OC16CON2 = 0x000E;
			#endif
			#if (MX_PWM_TMR_X == 5)		//Timer 5 is clock source
				OC16CON = 0x0C05;
				OC16CON2 = 0x000F;
			#endif
		#else
        	#if (MX_PWM_TMR_X == 2)
        		OC16CON = 0x0006;		//Timer 2
        	#else
        		OC16CON = 0x000E;		//Timer 3
        	#endif
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


	#if (MX_PWM_CHANNEL_X == 1)
		OC1CON = 0;																	//Disable Capture Compare Channel 1
	#endif

	#if (MX_PWM_CHANNEL_X == 2)
		OC2CON = 0;																	//Disable Capture Compare Channel 2
	#endif

	#if (MX_PWM_CHANNEL_X == 3)
		OC3CON = 0;																	//Disable Capture Compare Channel 3
	#endif

	#if (MX_PWM_CHANNEL_X == 4)
		OC4CON = 0;																	//Disable Capture Compare Channel 4
	#endif

	#if (MX_PWM_CHANNEL_X == 5)
		OC5CON = 0;																	//Disable Capture Compare Channel 5
	#endif

	#if (MX_PWM_CHANNEL_X == 6)
		OC6CON = 0;																	//Disable Capture Compare Channel 6
	#endif

	#if (MX_PWM_CHANNEL_X == 7)
		OC7CON = 0;																	//Disable Capture Compare Channel 7
	#endif

	#if (MX_PWM_CHANNEL_X == 8)
		OC8CON = 0;																	//Disable Capture Compare Channel 8
	#endif

	#if (MX_PWM_CHANNEL_X == 9)
		OC9CON = 0;																	//Disable Capture Compare Channel 9
	#endif

	#if (MX_PWM_CHANNEL_X == 10)
		OC10CON = 0;																	//Disable Capture Compare Channel 10
	#endif

	#if (MX_PWM_CHANNEL_X == 11)
		OC11CON = 0;																	//Disable Capture Compare Channel 11
	#endif

	#if (MX_PWM_CHANNEL_X == 12)
		OC12CON = 0;																	//Disable Capture Compare Channel 12
	#endif

	#if (MX_PWM_CHANNEL_X == 13)
		OC13CON = 0;																	//Disable Capture Compare Channel 13
	#endif

	#if (MX_PWM_CHANNEL_X == 14)
		OC14CON = 0;																	//Disable Capture Compare Channel 14
	#endif

	#if (MX_PWM_CHANNEL_X == 15)
		OC15CON = 0;																	//Disable Capture Compare Channel 15
	#endif

	#if (MX_PWM_CHANNEL_X == 16)
		OC16CON = 0;																	//Disable Capture Compare Channel 16
	#endif
}


CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 duty))
{
	if (duty == 0)
		duty = 1;

	#if (MX_PWM_CHANNEL_X == 1)
		OC1RS = duty;						//Update Capture Compare Count 1
	#endif

	#if (MX_PWM_CHANNEL_X == 2)
		OC2RS = duty;						//Update Capture Compare Count 2
	#endif

	#if (MX_PWM_CHANNEL_X == 3)
		OC3RS = duty;						//Update Capture Compare Count 3
	#endif

	#if (MX_PWM_CHANNEL_X == 4)
		OC4RS = duty;						//Update Capture Compare Count 4
	#endif

	#if (MX_PWM_CHANNEL_X == 5)
		OC5RS = duty;						//Update Capture Compare Count 5
	#endif

	#if (MX_PWM_CHANNEL_X == 6)
		OC6RS = duty;						//Update Capture Compare Count 6
	#endif

	#if (MX_PWM_CHANNEL_X == 7)
		OC7RS = duty;						//Update Capture Compare Count 7
	#endif

	#if (MX_PWM_CHANNEL_X == 8)
		OC8RS = duty;						//Update Capture Compare Count 8
	#endif

	#if (MX_PWM_CHANNEL_X == 9)
		OC9RS = duty;						//Update Capture Compare Count 9
	#endif

	#if (MX_PWM_CHANNEL_X == 10)
		OC10RS = duty;						//Update Capture Compare Count 10
	#endif

	#if (MX_PWM_CHANNEL_X == 11)
		OC11RS = duty;						//Update Capture Compare Count 11
	#endif

	#if (MX_PWM_CHANNEL_X == 12)
		OC12RS = duty;						//Update Capture Compare Count 12
	#endif

	#if (MX_PWM_CHANNEL_X == 13)
		OC13RS = duty;						//Update Capture Compare Count 13
	#endif

	#if (MX_PWM_CHANNEL_X == 14)
		OC14RS = duty;						//Update Capture Compare Count 14
	#endif

	#if (MX_PWM_CHANNEL_X == 15)
		OC15RS = duty;						//Update Capture Compare Count 15
	#endif

	#if (MX_PWM_CHANNEL_X == 16)
		OC16RS = duty;						//Update Capture Compare Count 16
	#endif


	//If the new duty is less than the current timer counter then we need to update
	//the timer to the max period so we don't get an incorrect 0% or 100% on cycle

	#if (MX_PWM_TMR_X == 1)
	  if (duty <= TMR1)
	    TMR1 = PR1;
	#endif
	#if (MX_PWM_TMR_X == 2)
	  if (duty <= TMR2)
	    TMR2 = PR2;
	#endif
	#if (MX_PWM_TMR_X == 3)
	  if (duty <= TMR3)
	    TMR3 = PR3;
	#endif
	#if (MX_PWM_TMR_X == 4)
	  if (duty <= TMR4)
	    TMR4 = PR4;
	#endif
	#if (MX_PWM_TMR_X == 5)
	  if (duty <= TMR5)
	    TMR5 = PR5;
	#endif
}


CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 period, MX_UINT16 prescaler))
{
  #ifdef MX_PWM								//Hardware Mode

	#if (MX_PWM_TMR_X == 1)
		PR1 = period;
		switch (prescaler)
		{
			default:
				T1CON = 0x8000;
				break;
			case 8:
				T1CON = 0x8010;
				break;
			case 64:
				T1CON = 0x8020;
				break;
			case 256:
				T1CON = 0x8030;
				break;
		}
	#endif

	#if (MX_PWM_TMR_X == 2)
		PR2 = period;
		switch (prescaler)
		{
			default:
				T2CON = 0x8000;
				break;
			case 8:
				T2CON = 0x8010;
				break;
			case 64:
				T2CON = 0x8020;
				break;
			case 256:
				T2CON = 0x8030;
				break;
		}
	#endif

	#if (MX_PWM_TMR_X == 3)
		PR3 = period;
		switch (prescaler)
		{
			default:
				T3CON = 0x8000;
				break;
			case 8:
				T3CON = 0x8010;
				break;
			case 64:
				T3CON = 0x8020;
				break;
			case 256:
				T3CON = 0x8030;
				break;
		}
	#endif

	#if (MX_PWM_TMR_X == 4)
		PR4 = period;
		switch (prescaler)
		{
			default:
				T4CON = 0x8000;
				break;
			case 8:
				T4CON = 0x8010;
				break;
			case 64:
				T4CON = 0x8020;
				break;
			case 256:
				T4CON = 0x8030;
				break;
		}
	#endif

	#if (MX_PWM_TMR_X == 5)
		PR5 = period;
		switch (prescaler)
		{
			default:
				T5CON = 0x8000;
				break;
			case 8:
				T5CON = 0x8010;
				break;
			case 64:
				T5CON = 0x8020;
				break;
			case 256:
				T5CON = 0x8030;
				break;
		}
	#endif


  #endif
}


CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 duty))
{
	if (duty < 1)
		duty = 1;

	#if (MX_PWM_CHANNEL_X == 1)
		OC1RS = duty;
	#endif

	#if (MX_PWM_CHANNEL_X == 2)
		OC2RS = duty;
	#endif

	#if (MX_PWM_CHANNEL_X == 3)
		OC3RS = duty;
	#endif

	#if (MX_PWM_CHANNEL_X == 4)
		OC4RS = duty;
	#endif

	#if (MX_PWM_CHANNEL_X == 5)
		OC5RS = duty;
	#endif

	#if (MX_PWM_CHANNEL_X == 6)
		OC6RS = duty;
	#endif

	#if (MX_PWM_CHANNEL_X == 7)
		OC7RS = duty;
	#endif

	#if (MX_PWM_CHANNEL_X == 8)
		OC8RS = duty;
	#endif

	#if (MX_PWM_CHANNEL_X == 9)
		OC9RS = duty;
	#endif

	#if (MX_PWM_CHANNEL_X == 10)
		OC10RS = duty;
	#endif

	#if (MX_PWM_CHANNEL_X == 11)
		OC11RS = duty;
	#endif

	#if (MX_PWM_CHANNEL_X == 12)
		OC12RS = duty;
	#endif

	#if (MX_PWM_CHANNEL_X == 13)
		OC13RS = duty;
	#endif

	#if (MX_PWM_CHANNEL_X == 14)
		OC14RS = duty;
	#endif

	#if (MX_PWM_CHANNEL_X == 15)
		OC15RS = duty;
	#endif

	#if (MX_PWM_CHANNEL_X == 16)
		OC16RS = duty;
	#endif


	//If the new duty is less than the current timer counter then we need to update
	//the timer to the max period so we don't get an incorrect 0% or 100% on cycle

	#if (MX_PWM_TMR_X == 1)
	  if (duty <= TMR1)
	    TMR1 = PR1;
	#endif
	#if (MX_PWM_TMR_X == 2)
	  if (duty <= TMR2)
	    TMR2 = PR2;
	#endif
	#if (MX_PWM_TMR_X == 3)
	  if (duty <= TMR3)
	    TMR3 = PR3;
	#endif
	#if (MX_PWM_TMR_X == 4)
	  if (duty <= TMR4)
	    TMR4 = PR4;
	#endif
	#if (MX_PWM_TMR_X == 5)
	  if (duty <= TMR5)
	    TMR5 = PR5;
	#endif
}

