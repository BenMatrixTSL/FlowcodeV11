// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B80A7638C619EA04AA769141413688B2ACE6D42111A55DBFF34DB1AE9C3B7A2EF3208613300A49360F0C3CAEE8E7DA6987F5152804CD52126EAC03EDF9B384E453D4F2853D11F5624A56940F47D025EBB8C526F3476F6548863F6A39118F23A5E538C97CD01C4BC57DF28D335B4544A5542E73218C5556E61C8AAD119FDE86628FB22A270D42704965549D34A0D5AD11F3945706A41175561C704AE53D2117C0A8972AF33136DACA0A9A437E7E2D43FD26DF891DB3086C82D6
// REVISION: 3.0
// GUID: 4B55EACF-670F-4981-A811-46D46DCF8196
// DATE: 16\10\2025
// DIR: CAL\PIC\PIC_CAL_PWM.c
/*********************************************************************
 *                  Flowcode CAL PWM File
 *
 * File: PIC_CAL_PWM.c
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
 * 021211 | BR | Converted to new dynamic defines mechanism
 * 090413 | LM | Ports now defined by V6 PWM CAL component
 * 030713 | LM | Standard API calls
 * 250713 | LM | Upper case register name typo fix
 * 030615 | BR | PWM Allocated Timer
 * 190516 | BR | Added support for 16F161x type CCP and PWM type none CCP
 */


#define MX_PWM_CHANNEL_X	CAL_APPEND(MX_PWM_CHANNEL_, MX_PWM_NUM)
#define MX_PWM_PORT_X		CAL_APPEND(MX_PWM_PORT_, 	MX_PWM_NUM)
#define MX_PWM_TRIS_X		CAL_APPEND(MX_PWM_TRIS_, 	MX_PWM_NUM)
#define MX_PWM_PIN_X		CAL_APPEND(MX_PWM_PIN_, 	MX_PWM_NUM)
#define MX_PWM_RPOR_X		CAL_APPEND(MX_PWM_RPOR_, 	MX_PWM_NUM)
#define MX_PWM_RPOC_X		CAL_APPEND(MX_PWM_RPOC_, 	MX_PWM_NUM)
#define MX_PWM_TMR_X		CAL_APPEND(MX_PWM_TMR_, 	MX_PWM_NUM)
#define MX_PWM_TYPE_X		CAL_APPEND(MX_PWM_TYPE_, 	MX_PWM_NUM)


//Work around for PWM with variable timers and 4 channels or less
#if defined (_CCPTMRS_CCP1TSEL_POSN) || defined (_CCPTMRS_C1TSEL_POSN)
	#define MX_TIMERSELECT0 CCPTMRS
#endif

#if defined (_CCPTMRS0_CCP1TSEL_POSN) || defined (_CCPTMRS0_C1TSEL_POSN)
	#define MX_TIMERSELECT0 CCPTMRS0
#endif

#if defined (_CCPTMRS1_CCP5TSEL_POSN) || defined (_CCPTMRS1_C5TSEL_POSN)
	#define MX_TIMERSELECT1 CCPTMRS1
#endif


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
		MX_PWM_RPOR_X = MX_PWM_RPOC_X;									//Assign PWM Channel OCx -> RPx - See FCD Defines For Info
	#endif

	FC_CAL_Bit_Low_DDR (MX_PWM_PORT_X, MX_PWM_TRIS_X, MX_PWM_PIN_X);	//PWM pin is an output

	#if (MX_PWM_CHANNEL_X == 1)

		//Alt Reg Functionality											//Mods for alt pin on 16F1939 family and others
		#ifdef MX_PWM_AREG_1
			MX_PWM_AREG_1 = MX_PWM_AREG_1 | MX_PWM_AMASK_1;
		#endif

		#if (MX_PWM_TYPE_X == 1)
			PWM1CON = 0xC0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM1CON = 0xC0;
		#else
			#ifdef MX_PWM_NEW_TMR_CONF										//PIC16F16xx, 17xx Workaround
				CCP1CON = 0x9C;												//Enable Capture Compare Channel 1
			#else
			  #if defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)	//PIC16F188xx, 183xx Workaround
			    CCP1CON = 0x9F;
			  #else
				CCP1CON = 0x0C;												//Enable Capture Compare Channel 1
			  #endif
			#endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 2)

		//Alt Reg Functionality											//Mods for alt pin on 16F1939 family and others
		#ifdef MX_PWM_AREG_2
			MX_PWM_AREG_2 = MX_PWM_AREG_2 | MX_PWM_AMASK_2;
		#endif

		#if (MX_PWM_TYPE_X == 1)
			PWM2CON = 0xC0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM2CON = 0xC0;
		#else
			#ifdef MX_PWM_NEW_TMR_CONF
				CCP2CON = 0x9C;												//Enable Capture Compare Channel 2
			#else
			  #if defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)	//PIC16F188xx, 183xx Workaround
			    CCP2CON = 0x9F;
			  #else
				CCP2CON = 0x0C;												//Enable Capture Compare Channel 2
			  #endif
			#endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 3)

		//Alt Reg Functionality											//Mods for alt pin on 16F1939 family and others
		#ifdef MX_PWM_AREG_3
			MX_PWM_AREG_3 = MX_PWM_AREG_3 | MX_PWM_AMASK_3;
		#endif

		#if (MX_PWM_TYPE_X == 1)
			PWM3CON = 0xC0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM3CON = 0xC0;
		#else
			#ifdef MX_PWM_NEW_TMR_CONF
				CCP3CON = 0x9C;												//Enable Capture Compare Channel 3
			#else
			  #if defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)	//PIC16F188xx, 183xx Workaround
			    CCP3CON = 0x9F;
			  #else
				CCP3CON = 0x0C;												//Enable Capture Compare Channel 3
			  #endif
			#endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 4)

		//Alt Reg Functionality											//Mods for alt pin on 16F1939 family and others
		#ifdef MX_PWM_AREG_4
			MX_PWM_AREG_4 = MX_PWM_AREG_4 | MX_PWM_AMASK_4;
		#endif

		#if (MX_PWM_TYPE_X == 1)
			PWM4CON = 0xC0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM4CON = 0xC0;
		#else
			#ifdef MX_PWM_NEW_TMR_CONF
				CCP4CON = 0x9C;												//Enable Capture Compare Channel 4
			#else
			  #if defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)	//PIC16F188xx, 183xx Workaround
			    CCP4CON = 0x9F;
			  #else
				CCP4CON = 0x0C;												//Enable Capture Compare Channel 4
			  #endif
			#endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 5)

		//Alt Reg Functionality											//Mods for alt pin on 16F1939 family and others
		#ifdef MX_PWM_AREG_5
			MX_PWM_AREG_5 = MX_PWM_AREG_5 | MX_PWM_AMASK_5;
		#endif

		#if (MX_PWM_TYPE_X == 1)
			PWM5CON = 0xC0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM5CON = 0xC0;
		#else
			#ifdef MX_PWM_NEW_TMR_CONF
				CCP5CON = 0x9C;												//Enable Capture Compare Channel 5
			#else
			  #if defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)	//PIC16F188xx, 183xx Workaround
			    CCP5CON = 0x9F;
			  #else
				CCP5CON = 0x0C;												//Enable Capture Compare Channel 5
			  #endif
			#endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 6)

		//Alt Reg Functionality											//Mods for alt pin on 16F1939 family and others
		#ifdef MX_PWM_AREG_6
			MX_PWM_AREG_6 = MX_PWM_AREG_6 | MX_PWM_AMASK_6;
		#endif

		#if (MX_PWM_TYPE_X == 1)
			PWM6CON = 0xC0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM6CON = 0xC0;
		#else
			#ifdef MX_PWM_NEW_TMR_CONF
				CCP6CON = 0x9C;												//Enable Capture Compare Channel 6
			#else
			  #if defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)	//PIC16F188xx, 183xx Workaround
			    CCP6CON = 0x9F;
			  #else
				CCP6CON = 0x0C;												//Enable Capture Compare Channel 6
			  #endif
			#endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 7)

		//Alt Reg Functionality											//Mods for alt pin on 16F1939 family and others
		#ifdef MX_PWM_AREG_7
			MX_PWM_AREG_7 = MX_PWM_AREG_7 | MX_PWM_AMASK_7;
		#endif

		#if (MX_PWM_TYPE_X == 1)
			PWM7CON = 0xC0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM7CON = 0xC0;
		#else
			#ifdef MX_PWM_NEW_TMR_CONF
				CCP7CON = 0x9C;												//Enable Capture Compare Channel 7
			#else
			  #if defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)	//PIC16F188xx, 183xx Workaround
			    CCP7CON = 0x9F;
			  #else
				CCP7CON = 0x0C;												//Enable Capture Compare Channel 7
			  #endif
			#endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 8)

		//Alt Reg Functionality											//Mods for alt pin on 16F1939 family and others
		#ifdef MX_PWM_AREG_8
			MX_PWM_AREG_8 = MX_PWM_AREG_8 | MX_PWM_AMASK_8;
		#endif

		#if (MX_PWM_TYPE_X == 1)
			PWM8CON = 0xC0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM8CON = 0xC0;
		#else
			#ifdef MX_PWM_NEW_TMR_CONF
				CCP8CON = 0x9C;												//Enable Capture Compare Channel 8
			#else
			  #if defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)	//PIC16F188xx, 183xx Workaround
			    CCP8CON = 0x9F;
			  #else
				CCP8CON = 0x0C;												//Enable Capture Compare Channel 8
			  #endif
			#endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 9)

		//Alt Reg Functionality											//Mods for alt pin on 16F1939 family and others
		#ifdef MX_PWM_AREG_9
			MX_PWM_AREG_9 = MX_PWM_AREG_9 | MX_PWM_AMASK_9;
		#endif

		#if (MX_PWM_TYPE_X == 1)
			PWM9CON = 0xC0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM9CON = 0xC0;
		#else
			#ifdef MX_PWM_NEW_TMR_CONF
				CCP9CON = 0x9C;												//Enable Capture Compare Channel 9
			#else
			  #if defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)	//PIC16F188xx, 183xx Workaround
			    CCP9CON = 0x9F;
			  #else
				CCP9CON = 0x0C;												//Enable Capture Compare Channel 9
			  #endif
			#endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 10)

		//Alt Reg Functionality											//Mods for alt pin on 16F1939 family and others
		#ifdef MX_PWM_AREG_10
			MX_PWM_AREG_10 = MX_PWM_AREG_10 | MX_PWM_AMASK_10;
		#endif

		#if (MX_PWM_TYPE_X == 1)
			PWM10CON = 0xC0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM10CON = 0xC0;
		#else
			#ifdef MX_PWM_NEW_TMR_CONF
				CCP10CON = 0x9C;											//Enable Capture Compare Channel 10
			#else
			  #if defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)	//PIC16F188xx, 183xx Workaround
			    CCP10CON = 0x9F;
			  #else
				CCP10CON = 0x0C;											//Enable Capture Compare Channel 10
			  #endif
			#endif
		#endif
	#endif

 #else
 	#warning "Hardware PWM not supported by Target microcontroller."
 	#undef MX_PWM_CHANNEL_X
 #endif

}


CALFUNCTION(void, FC_CAL_PWM_Disable_, (void))
{
	FC_CAL_Bit_In_DDR (MX_PWM_PORT_X, MX_PWM_TRIS_X, MX_PWM_PIN_X);		//PWM pin is an input

	#if (MX_PWM_CHANNEL_X == 1)
		#if (MX_PWM_TYPE_X == 1)
			PWM1CON = 0x00;													//Disable Capture Compare Channel
		#elif (MX_PWM_TYPE_X == 2)
			PWM1CON = 0x00;
		#else
			CCP1CON = 0x00;													//Disable Capture Compare Channel
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 2)
		#if (MX_PWM_TYPE_X == 1)
			PWM2CON = 0x00;													//Disable Capture Compare Channel
		#elif (MX_PWM_TYPE_X == 2)
			PWM2CON = 0x00;
		#else
			CCP2CON = 0x00;													//Disable Capture Compare Channel
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 3)
		#if (MX_PWM_TYPE_X == 1)
			PWM3CON = 0x00;													//Disable Capture Compare Channel
		#elif (MX_PWM_TYPE_X == 2)
			PWM3CON = 0x00;
		#else
			CCP3CON = 0x00;													//Disable Capture Compare Channel
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 4)
		#if (MX_PWM_TYPE_X == 1)
			PWM4CON = 0x00;													//Disable Capture Compare Channel
		#elif (MX_PWM_TYPE_X == 2)
			PWM4CON = 0x00;
		#else
			CCP4CON = 0x00;													//Disable Capture Compare Channel
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 5)
		#if (MX_PWM_TYPE_X == 1)
			PWM5CON = 0x00;													//Disable Capture Compare Channel
		#elif (MX_PWM_TYPE_X == 2)
			PWM5CON = 0x00;
		#else
			CCP5CON = 0x00;													//Disable Capture Compare Channel
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 6)
		#if (MX_PWM_TYPE_X == 1)
			PWM6CON = 0x00;													//Disable Capture Compare Channel
		#elif (MX_PWM_TYPE_X == 2)
			PWM6CON = 0x00;
		#else
			CCP6CON = 0x00;													//Disable Capture Compare Channel
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 7)
		#if (MX_PWM_TYPE_X == 1)
			PWM7CON = 0x00;													//Disable Capture Compare Channel
		#elif (MX_PWM_TYPE_X == 2)
			PWM7CON = 0x00;
		#else
			CCP7CON = 0x00;													//Disable Capture Compare Channel
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 8)
		#if (MX_PWM_TYPE_X == 1)
			PWM8CON = 0x00;													//Disable Capture Compare Channel
		#elif (MX_PWM_TYPE_X == 2)
			PWM8CON = 0x00;
		#else
			CCP8CON = 0x00;													//Disable Capture Compare Channel
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 9)
		#if (MX_PWM_TYPE_X == 1)
			PWM9CON = 0x00;													//Disable Capture Compare Channel
		#elif (MX_PWM_TYPE_X == 2)
			PWM9CON = 0x00;
		#else
			CCP9CON = 0x00;													//Disable Capture Compare Channel
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 10)
		#if (MX_PWM_TYPE_X == 1)
			PWM10CON = 0x00;												//Disable Capture Compare Channel
		#elif (MX_PWM_TYPE_X == 2)
			PWM10CON = 0x00;
		#else
			CCP10CON = 0x00;												//Disable Capture Compare Channel
		#endif
	#endif
}


CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 duty))
{
	#if (MX_PWM_CHANNEL_X == 1)
		#if (MX_PWM_TYPE_X == 1)
			PWM1DCH = duty;
			PWM1DCL = 0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM1DCH = duty;
			PWM1DCL = 0;
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR1H = duty;													//Update Capture Compare Count
			CCPR1L = 0;
		  #else
			CCPR1L = duty;													//Update Capture Compare Count
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 2)
		#if (MX_PWM_TYPE_X == 1)
			PWM2DCH = duty;
			PWM2DCL = 0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM2DCH = duty;
			PWM2DCL = 0;
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR2H = duty;													//Update Capture Compare Count
			CCPR2L = 0;
		  #else
			CCPR2L = duty;													//Update Capture Compare Count
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 3)
		#if (MX_PWM_TYPE_X == 1)
			PWM3DCH = duty;
			PWM3DCL = 0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM3DCH = duty;
			PWM3DCL = 0;
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR3H = duty;													//Update Capture Compare Count
			CCPR3L = 0;
		  #else
			CCPR3L = duty;													//Update Capture Compare Count
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 4)
		#if (MX_PWM_TYPE_X == 1)
			PWM4DCH = duty;
			PWM4DCL = 0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM4DCH = duty;
			PWM4DCL = 0;
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR4H = duty;													//Update Capture Compare Count
			CCPR4L = 0;
		  #else
			CCPR4L = duty;													//Update Capture Compare Count
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 5)
		#if (MX_PWM_TYPE_X == 1)
			PWM5DCH = duty;
			PWM5DCL = 0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM5DCH = duty;
			PWM5DCL = 0;
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR5H = duty;													//Update Capture Compare Count
			CCPR5L = 0;
		  #else
			CCPR5L = duty;													//Update Capture Compare Count
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 6)
		#if (MX_PWM_TYPE_X == 1)
			PWM6DCH = duty;
			PWM6DCL = 0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM6DCH = duty;
			PWM6DCL = 0;
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR6H = duty;													//Update Capture Compare Count
			CCPR6L = 0;
		  #else
			CCPR6L = duty;													//Update Capture Compare Count
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 7)
		#if (MX_PWM_TYPE_X == 1)
			PWM7DCH = duty;
			PWM7DCL = 0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM7DCH = duty;
			PWM7DCL = 0;
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR7H = duty;													//Update Capture Compare Count
			CCPR7L = 0;
		  #else
			CCPR7L = duty;													//Update Capture Compare Count
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 8)
		#if (MX_PWM_TYPE_X == 1)
			PWM8DCH = duty;
			PWM8DCL = 0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM8DCH = duty;
			PWM8DCL = 0;
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR8H = duty;													//Update Capture Compare Count
			CCPR8L = 0;
		  #else
			CCPR8L = duty;													//Update Capture Compare Count
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 9)
		#if (MX_PWM_TYPE_X == 1)
			PWM9DCH = duty;
			PWM9DCL = 0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM9DCH = duty;
			PWM9DCL = 0;
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR9H = duty;													//Update Capture Compare Count
			CCPR9L = 0;
		  #else
			CCPR9L = duty;													//Update Capture Compare Count
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 10)
		#if (MX_PWM_TYPE_X == 1)
			PWM10DCH = duty;
			PWM10DCL = 0;
		#elif (MX_PWM_TYPE_X == 2)
			PWM10DCH = duty;
			PWM10DCL = 0;
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR10H = duty;													//Update Capture Compare Count
			CCPR10L = 0;
		  #else
			CCPR10L = duty;													//Update Capture Compare Count
		  #endif
		#endif
	#endif
}


CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 period, MX_UINT16 prescaler))
{
  #ifdef MX_PWM								//Hardware Mode

	#if (MX_PWM_TYPE_X == 2)

		#if (MX_PWM_CHANNEL_X == 1)
			switch (prescaler)
			{
				case 1:
					PWM1CLKCON = 0x00 | MX_PWM_TMR_X;
					break;
				case 2:
					PWM1CLKCON = 0x10 | MX_PWM_TMR_X;
					break;
				case 4:
					PWM1CLKCON = 0x20 | MX_PWM_TMR_X;
					break;
				case 8:
					PWM1CLKCON = 0x30 | MX_PWM_TMR_X;
					break;
				case 16:
					PWM1CLKCON = 0x40 | MX_PWM_TMR_X;
					break;
				case 32:
					PWM1CLKCON = 0x50 | MX_PWM_TMR_X;
					break;
				case 64:
					PWM1CLKCON = 0x60 | MX_PWM_TMR_X;
					break;
				case 128:
					PWM1CLKCON = 0x70 | MX_PWM_TMR_X;
					break;
				default:
					PWM1CLKCON = 0x20 | MX_PWM_TMR_X;
					break;
			}

			PWM1PRH = period >> 8;
			PWM1PRL = period;
		#endif

		#if (MX_PWM_CHANNEL_X == 2)
			switch (prescaler)
			{
				case 1:
					PWM2CLKCON = 0x00 | MX_PWM_TMR_X;
					break;
				case 2:
					PWM2CLKCON = 0x10 | MX_PWM_TMR_X;
					break;
				case 4:
					PWM2CLKCON = 0x20 | MX_PWM_TMR_X;
					break;
				case 8:
					PWM2CLKCON = 0x30 | MX_PWM_TMR_X;
					break;
				case 16:
					PWM2CLKCON = 0x40 | MX_PWM_TMR_X;
					break;
				case 32:
					PWM2CLKCON = 0x50 | MX_PWM_TMR_X;
					break;
				case 64:
					PWM2CLKCON = 0x60 | MX_PWM_TMR_X;
					break;
				case 128:
					PWM2CLKCON = 0x70 | MX_PWM_TMR_X;
					break;
				default:
					PWM2CLKCON = 0x20 | MX_PWM_TMR_X;
					break;
			}

			PWM2PRH = period >> 8;
			PWM2PRL = period;
		#endif

		#if (MX_PWM_CHANNEL_X == 3)
			switch (prescaler)
			{
				case 1:
					PWM3CLKCON = 0x00 | MX_PWM_TMR_X;
					break;
				case 2:
					PWM3CLKCON = 0x10 | MX_PWM_TMR_X;
					break;
				case 4:
					PWM3CLKCON = 0x20 | MX_PWM_TMR_X;
					break;
				case 8:
					PWM3CLKCON = 0x30 | MX_PWM_TMR_X;
					break;
				case 16:
					PWM3CLKCON = 0x40 | MX_PWM_TMR_X;
					break;
				case 32:
					PWM3CLKCON = 0x50 | MX_PWM_TMR_X;
					break;
				case 64:
					PWM3CLKCON = 0x60 | MX_PWM_TMR_X;
					break;
				case 128:
					PWM3CLKCON = 0x70 | MX_PWM_TMR_X;
					break;
				default:
					PWM3CLKCON = 0x20 | MX_PWM_TMR_X;
					break;
			}

			PWM3PRH = period >> 8;
			PWM3PRL = period;
		#endif

	#else
		#if (MX_PWM_TMR_X == 2)

			#if (MX_PWM_CHANNEL_X == 1)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS0bits.C1TSEL = 0;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0xFC;
						#if (MX_PWM_ALTTIMER == 1)
							MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x01;
						#endif
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 2)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS0bits.C2TSEL = 0;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0xF3;
						#if (MX_PWM_ALTTIMER == 1)
							MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x04;
						#endif
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 3)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS0bits.C3TSEL = 0;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0xCF;
						#if (MX_PWM_ALTTIMER == 1)
							MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x10;
						#endif
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 4)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS1bits.C4TSEL = 0;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0x3F;
						#if (MX_PWM_ALTTIMER == 1)
							MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x40;
						#endif
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 5)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS1bits.C5TSEL = 0;
				#else
					#ifdef MX_TIMERSELECT1
						MX_TIMERSELECT1 = MX_TIMERSELECT1 & 0xFC;
						#if (MX_PWM_ALTTIMER == 1)
							MX_TIMERSELECT1 = MX_TIMERSELECT1 | 0x01;
						#endif
					#endif
				#endif
			#endif

			PR2 = period;

			#if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2)
				#ifdef MX_PWM_NEW_TMR_CONF2
					T2CLKCON = 1; 				//FOSC/4
				#endif
				switch (prescaler)
				{
					case 1:
						T2CON = 0x80;
						break;
					case 2:
						T2CON = 0x90;
						break;
					case 4:
						T2CON = 0xA0;
						break;
					case 8:
						T2CON = 0xB0;
						break;
					case 16:
						T2CON = 0xC0;
						break;
					case 32:
						T2CON = 0xD0;
						break;
					case 64:
						T2CON = 0xE0;
						break;
					case 128:
						T2CON = 0xF0;
						break;
					default:
						T2CON = 0x80;
						break;
				}
			#else
				switch (prescaler)
				{
					case 1:
						T2CON = 0x04;
						break;
					case 4:
						T2CON = 0x05;
						break;
					case 16:
						T2CON = 0x06;
						break;
					case 64:
						T2CON = 0x07;					//Note some earlier devices do not have the /64 option
						break;
					default:
						T2CON = 0x05;
						break;
				}
			#endif
		#endif

		#if (MX_PWM_TMR_X == 4)

			#if (MX_PWM_CHANNEL_X == 1)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS0bits.C1TSEL = 1;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0xFC;
						#if (MX_PWM_ALTTIMER == 1)
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x02;
						#else
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x01;
						#endif
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 2)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS0bits.C2TSEL = 1;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0xF3;
						#if (MX_PWM_ALTTIMER == 1)
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x08;
						#else
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x04;
						#endif
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 3)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS0bits.C3TSEL = 1;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0xCF;
						#if (MX_PWM_ALTTIMER == 1)
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x20;
						#else
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x10;
						#endif
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 4)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS1bits.C4TSEL = 1;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0x3F;
						#if (MX_PWM_ALTTIMER == 1)
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x80;
						#else
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x40;
						#endif
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 5)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS1bits.C5TSEL = 1;
				#else
					#ifdef MX_TIMERSELECT1
						MX_TIMERSELECT1 = MX_TIMERSELECT1 & 0xFC;
						#if (MX_PWM_ALTTIMER == 1)
						  MX_TIMERSELECT1 = MX_TIMERSELECT1 | 0x02;
						#else
						  MX_TIMERSELECT1 = MX_TIMERSELECT1 | 0x01;
						#endif
					#endif
				#endif
			#endif

			PR4 = period;

			#if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2)
				#ifdef MX_PWM_NEW_TMR_CONF2
					T4CLKCON = 1; 				//FOSC/4
				#endif
				switch (prescaler)
				{
					case 1:
						T4CON = 0x80;
						break;
					case 2:
						T4CON = 0x90;
						break;
					case 4:
						T4CON = 0xA0;
						break;
					case 8:
						T4CON = 0xB0;
						break;
					case 16:
						T4CON = 0xC0;
						break;
					case 32:
						T4CON = 0xD0;
						break;
					case 64:
						T4CON = 0xE0;
						break;
					case 128:
						T4CON = 0xF0;
						break;
					default:
						T4CON = 0x80;
						break;
				}
			#else
				switch (prescaler)
				{
					case 1:
						T4CON = 0x04;
						break;
					case 4:
						T4CON = 0x05;
						break;
					case 16:
						T4CON = 0x06;
						break;
					case 64:
						T4CON = 0x07;					//Note some earlier devices do not have the /64 option
						break;
					default:
						T4CON = 0x05;
						break;
				}
			#endif
		#endif

		#if (MX_PWM_TMR_X == 6)

			#if (MX_PWM_CHANNEL_X == 1)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS0bits.C1TSEL = 2;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0xFC;
						#if (MX_PWM_ALTTIMER == 1)
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x03;
						#else
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x02;
						#endif
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 2)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS0bits.C2TSEL = 1;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0xF3;
						#if (MX_PWM_ALTTIMER == 1)
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x0C;
						#else
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x08;
						#endif
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 3)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS0bits.C3TSEL = 2;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0xCF;
						#if (MX_PWM_ALTTIMER == 1)
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x30;
						#else
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x20;
						#endif
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 4)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS1bits.C4TSEL = 2;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0x3F;
						#if (MX_PWM_ALTTIMER == 1)
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0xC0;
						#else
						  MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x80;
						#endif
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 5)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS1bits.C5TSEL = 2;
				#else
					#ifdef MX_TIMERSELECT1
						MX_TIMERSELECT1 = MX_TIMERSELECT1 & 0xFC;
						#if (MX_PWM_ALTTIMER == 1)
						  MX_TIMERSELECT1 = MX_TIMERSELECT1 | 0x03;
						#else
						  MX_TIMERSELECT1 = MX_TIMERSELECT1 | 0x02;
						#endif
					#endif
				#endif
			#endif

			PR6 = period;

			#if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2)
				#ifdef MX_PWM_NEW_TMR_CONF2
					T6CLKCON = 1; 				//FOSC/4
				#endif
				switch (prescaler)
				{
					case 1:
						T6CON = 0x80;
						break;
					case 2:
						T6CON = 0x90;
						break;
					case 4:
						T6CON = 0xA0;
						break;
					case 8:
						T6CON = 0xB0;
						break;
					case 16:
						T6CON = 0xC0;
						break;
					case 32:
						T6CON = 0xD0;
						break;
					case 64:
						T6CON = 0xE0;
						break;
					case 128:
						T6CON = 0xF0;
						break;
					default:
						T6CON = 0x80;
						break;
				}
			#else
				switch (prescaler)
				{
					case 1:
						T6CON = 0x04;
						break;
					case 4:
						T6CON = 0x05;
						break;
					case 16:
						T6CON = 0x06;
						break;
					case 64:
						T6CON = 0x07;					//Note some earlier devices do not have the /64 option
						break;
					default:
						T6CON = 0x05;
						break;
				}
			#endif
		#endif

		#if (MX_PWM_TMR_X == 8)

			#if (MX_PWM_CHANNEL_X == 1)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS0bits.C1TSEL = 3;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0xFC;
  					  	MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x03;
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 2)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS0bits.C2TSEL = 1;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0xF3;
					  	MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x0C;
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 3)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS0bits.C3TSEL = 2;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0xCF;
						MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0x30;
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 4)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS1bits.C4TSEL = 2;
				#else
					#ifdef MX_TIMERSELECT0
						MX_TIMERSELECT0 = MX_TIMERSELECT0 & 0x3F;
						MX_TIMERSELECT0 = MX_TIMERSELECT0 | 0xC0;
					#endif
				#endif
			#endif
			#if (MX_PWM_CHANNEL_X == 5)
				#if (MX_PWM_ALTTIMER == 2)
					CCPTMRS1bits.C5TSEL = 2;
				#else
					#ifdef MX_TIMERSELECT1
						MX_TIMERSELECT1 = MX_TIMERSELECT1 & 0xFC;
						MX_TIMERSELECT1 = MX_TIMERSELECT1 | 0x03;
					#endif
				#endif
			#endif

			PR8 = period;

			#if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2)
				#ifdef MX_PWM_NEW_TMR_CONF2
					T8CLKCON = 1; 				//FOSC/4
				#endif
				switch (prescaler)
				{
					case 1:
						T8CON = 0x80;
						break;
					case 2:
						T8CON = 0x90;
						break;
					case 4:
						T8CON = 0xA0;
						break;
					case 8:
						T8CON = 0xB0;
						break;
					case 16:
						T8CON = 0xC0;
						break;
					case 32:
						T8CON = 0xD0;
						break;
					case 64:
						T8CON = 0xE0;
						break;
					case 128:
						T8CON = 0xF0;
						break;
					default:
						T8CON = 0x80;
						break;
				}
			#else
				switch (prescaler)
				{
					case 1:
						T8CON = 0x04;
						break;
					case 4:
						T8CON = 0x05;
						break;
					case 16:
						T8CON = 0x06;
						break;
					case 64:
						T8CON = 0x07;					//Note some earlier devices do not have the /64 option
						break;
					default:
						T8CON = 0x05;
						break;
				}
			#endif
		#endif

	#endif
  #endif
}


CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 duty))
{
	#ifndef MX_PWM_NEW_TMR_CONF
		char nCCPxCONtemp;
	#endif

	#if (MX_PWM_CHANNEL_X == 1)
		#if (MX_PWM_TYPE_X == 1)
			PWM1DCH = duty >> 2;			//8MSB HHHHHHHH
			PWM1DCL = duty << 6;			//2LSB LL000000
		#elif (MX_PWM_TYPE_X == 2)
			PWM1DCH = duty >> 8;			//8MSB HHHHHHHH
			PWM1DCL = duty;					//8LSB LLLLLLLL
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR1H = duty >> 2;				//8MSB HHHHHHHH
			CCPR1L = duty << 6;				//2LSB LL000000
		  #else
			CCPR1L = (duty & 0x3FC) >> 2;									//Update Capture Compare Count 1
			duty = (duty & 0x03) << 4;
			nCCPxCONtemp = (CCP1CON & 0xCF) | duty;
			CCP1CON = nCCPxCONtemp;
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 2)
		#if (MX_PWM_TYPE_X == 1)
			PWM2DCH = duty >> 2;			//8MSB HHHHHHHH
			PWM2DCL = duty << 6;			//2LSB LL000000
		#elif (MX_PWM_TYPE_X == 2)
			PWM2DCH = duty >> 8;			//8MSB HHHHHHHH
			PWM2DCL = duty;					//8LSB LLLLLLLL
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR2H = duty >> 2;				//8MSB HHHHHHHH
			CCPR2L = duty << 6;				//2LSB LL000000
		  #else
			CCPR2L = (duty & 0x3FC) >> 2;									//Update Capture Compare Count 2
			duty = (duty & 0x03) << 4;
			nCCPxCONtemp = (CCP2CON & 0xCF) | duty;
			CCP2CON = nCCPxCONtemp;
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 3)
		#if (MX_PWM_TYPE_X == 1)
			PWM3DCH = duty >> 2;			//8MSB HHHHHHHH
			PWM3DCL = duty << 6;			//2LSB LL000000
		#elif (MX_PWM_TYPE_X == 2)
			PWM3DCH = duty >> 8;			//8MSB HHHHHHHH
			PWM3DCL = duty;					//8LSB LLLLLLLL
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR3H = duty >> 2;				//8MSB HHHHHHHH
			CCPR3L = duty << 6;				//2LSB LL000000
		  #else
			CCPR3L = (duty & 0x3FC) >> 2;									//Update Capture Compare Count 3
			duty = (duty & 0x03) << 4;
			nCCPxCONtemp = (CCP3CON & 0xCF) | duty;
			CCP3CON = nCCPxCONtemp;
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 4)
		#if (MX_PWM_TYPE_X == 1)
			PWM4DCH = duty >> 2;			//8MSB HHHHHHHH
			PWM4DCL = duty << 6;			//2LSB LL000000
		#elif (MX_PWM_TYPE_X == 2)
			PWM4DCH = duty >> 8;			//8MSB HHHHHHHH
			PWM4DCL = duty;					//8LSB LLLLLLLL
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR4H = duty >> 2;				//8MSB HHHHHHHH
			CCPR4L = duty << 6;				//2LSB LL000000
		  #else
			CCPR4L = (duty & 0x3FC) >> 2;									//Update Capture Compare Count 4
			duty = (duty & 0x03) << 4;
			nCCPxCONtemp = (CCP4CON & 0xCF) | duty;
			CCP4CON = nCCPxCONtemp;
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 5)
		#if (MX_PWM_TYPE_X == 1)
			PWM5DCH = duty >> 2;			//8MSB HHHHHHHH
			PWM5DCL = duty << 6;			//2LSB LL000000
		#elif (MX_PWM_TYPE_X == 2)
			PWM5DCH = duty >> 8;			//8MSB HHHHHHHH
			PWM5DCL = duty;					//8LSB LLLLLLLL
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR5H = duty >> 2;				//8MSB HHHHHHHH
			CCPR5L = duty << 6;				//2LSB LL000000
		  #else
			CCPR5L = (duty & 0x3FC) >> 2;									//Update Capture Compare Count 5
			duty = (duty & 0x03) << 4;
			nCCPxCONtemp = (CCP5CON & 0xCF) | duty;
			CCP5CON = nCCPxCONtemp;
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 6)
		#if (MX_PWM_TYPE_X == 1)
			PWM6DCH = duty >> 2;			//8MSB HHHHHHHH
			PWM6DCL = duty << 6;			//2LSB LL000000
		#elif (MX_PWM_TYPE_X == 2)
			PWM6DCH = duty >> 8;			//8MSB HHHHHHHH
			PWM6DCL = duty;					//8LSB LLLLLLLL
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR6H = duty >> 2;				//8MSB HHHHHHHH
			CCPR6L = duty << 6;				//2LSB LL000000
		  #else
			CCPR6L = (duty & 0x3FC) >> 2;									//Update Capture Compare Count 6
			duty = (duty & 0x03) << 4;
			nCCPxCONtemp = (CCP6CON & 0xCF) | duty;
			CCP6CON = nCCPxCONtemp;
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 7)
		#if (MX_PWM_TYPE_X == 1)
			PWM7DCH = duty >> 2;			//8MSB HHHHHHHH
			PWM7DCL = duty << 6;			//2LSB LL000000
		#elif (MX_PWM_TYPE_X == 2)
			PWM7DCH = duty >> 8;			//8MSB HHHHHHHH
			PWM7DCL = duty;					//8LSB LLLLLLLL
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR7H = duty >> 2;				//8MSB HHHHHHHH
			CCPR7L = duty << 6;				//2LSB LL000000
		  #else
			CCPR7L = (duty & 0x3FC) >> 2;									//Update Capture Compare Count 7
			duty = (duty & 0x03) << 4;
			nCCPxCONtemp = (CCP7CON & 0xCF) | duty;
			CCP7CON = nCCPxCONtemp;
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 8)
		#if (MX_PWM_TYPE_X == 1)
			PWM8DCH = duty >> 2;			//8MSB HHHHHHHH
			PWM8DCL = duty << 6;			//2LSB LL000000
		#elif (MX_PWM_TYPE_X == 2)
			PWM8DCH = duty >> 8;			//8MSB HHHHHHHH
			PWM8DCL = duty;					//8LSB LLLLLLLL
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR8H = duty >> 2;				//8MSB HHHHHHHH
			CCPR8L = duty << 6;				//2LSB LL000000
		  #else
			CCPR8L = (duty & 0x3FC) >> 2;									//Update Capture Compare Count 8
			duty = (duty & 0x03) << 4;
			nCCPxCONtemp = (CCP8CON & 0xCF) | duty;
			CCP8CON = nCCPxCONtemp;
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 9)
		#if (MX_PWM_TYPE_X == 1)
			PWM9DCH = duty >> 2;			//8MSB HHHHHHHH
			PWM9DCL = duty << 6;			//2LSB LL000000
		#elif (MX_PWM_TYPE_X == 2)
			PWM9DCH = duty >> 8;			//8MSB HHHHHHHH
			PWM9DCL = duty;					//8LSB LLLLLLLL
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR9H = duty >> 2;				//8MSB HHHHHHHH
			CCPR9L = duty << 6;				//2LSB LL000000
		  #else
			CCPR9L = (duty & 0x3FC) >> 2;									//Update Capture Compare Count 9
			duty = (duty & 0x03) << 4;
			nCCPxCONtemp = (CCP9CON & 0xCF) | duty;
			CCP9CON = nCCPxCONtemp;
		  #endif
		#endif
	#endif

	#if (MX_PWM_CHANNEL_X == 10)
		#if (MX_PWM_TYPE_X == 1)
			PWM10DCH = duty >> 2;			//8MSB HHHHHHHH
			PWM10DCL = duty << 6;			//2LSB LL000000
		#elif (MX_PWM_TYPE_X == 2)
			PWM10DCH = duty >> 8;			//8MSB HHHHHHHH
			PWM10DCL = duty;				//8LSB LLLLLLLL
		#else
		  #if defined (MX_PWM_NEW_TMR_CONF) || defined (MX_PWM_NEW_TMR_CONF2) || defined (MX_PWM_NEW_TMR_CONF3)
			CCPR10H = duty >> 2;			//8MSB HHHHHHHH
			CCPR10L = duty << 6;			//2LSB LL000000
		  #else
			CCPR10L = (duty & 0x3FC) >> 2;									//Update Capture Compare Count 10
			duty = (duty & 0x03) << 4;
			nCCPxCONtemp = (CCP10CON & 0xCF) | duty;
			CCP10CON = nCCPxCONtemp;
		  #endif
		#endif
	#endif
}

