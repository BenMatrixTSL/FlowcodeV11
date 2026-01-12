// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B8585891215DADC5BD4545792B0722580C186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF583CFCF0458A4E5CB4ED9E12520781B20A03ACA64B46819753590D0E7FE1BB9D03AEE2368CA9D682874C22F2D6CD8A76CB336187FFB563FD52A1B41E30D2B0D4A08DD2BA6D683DDBCF590F929A205C1B4B9E670B98ED97111549D34A0D5AD11F37401AD45BF293031D64C58CD34B9D4EFB338E56A10ABD1BB3D04CF7CD5577C5FE9D77FAA9053C2CE
// REVISION: 1.0
// GUID: B65572E7-11DC-465A-B5DF-4A9641EA6911
// DATE: 08\08\2022
// DIR: CAL\PIC\PIC_CAL_HBridge.c
/*********************************************************************
 *                  Flowcode CAL HBridge File
 *
 * File: PIC_CAL_HBridge.c
 *
 * (c) 2018 Matrix Multimedia Ltd.
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
 * 080818 | BR | Created

 */


#define MX_HBRIDGE_EN_X			CAL_APPEND(MX_HBRIDGE_EN_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_CHANNEL_X	CAL_APPEND(MX_HBRIDGE_CHANNEL_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_TYPE			CAL_APPEND(MX_HBRIDGE_TYPE_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_MODE_X		CAL_APPEND(MX_HBRIDGE_MODE_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_POL_X		CAL_APPEND(MX_HBRIDGE_POL_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_TIMER_X		CAL_APPEND(MX_HBRIDGE_TIMER_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_PRESCALE_X	CAL_APPEND(MX_HBRIDGE_PRESCALE_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_PERIOD_X		CAL_APPEND(MX_HBRIDGE_PERIOD_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_RC_X			CAL_APPEND(MX_HBRIDGE_RC_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_FC_X			CAL_APPEND(MX_HBRIDGE_FC_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_ALTA_X		CAL_APPEND(MX_HBRIDGE_ALTA_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_ALTB_X		CAL_APPEND(MX_HBRIDGE_ALTB_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_ALTC_X		CAL_APPEND(MX_HBRIDGE_ALTC_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_ALTD_X		CAL_APPEND(MX_HBRIDGE_ALTD_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_ALTA_X		CAL_APPEND(MX_HBRIDGE_ALTA_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_PINA_X		CAL_APPEND(MX_HBRIDGE_PINA_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_PINB_X		CAL_APPEND(MX_HBRIDGE_PINB_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_PINC_X		CAL_APPEND(MX_HBRIDGE_PINC_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_PIND_X		CAL_APPEND(MX_HBRIDGE_PIND_, MX_HBRIDGE_NUM)

#define MX_HBRIDGE_PORTA		CAL_APPEND(PORT,CAL_APPEND(MX_HBRIDGE_PORTA_, MX_HBRIDGE_NUM))
#define MX_HBRIDGE_TRISA		CAL_APPEND(TRIS,CAL_APPEND(MX_HBRIDGE_PORTA_, MX_HBRIDGE_NUM))
#define MX_HBRIDGE_PORTB		CAL_APPEND(PORT,CAL_APPEND(MX_HBRIDGE_PORTB_, MX_HBRIDGE_NUM))
#define MX_HBRIDGE_TRISB		CAL_APPEND(TRIS,CAL_APPEND(MX_HBRIDGE_PORTB_, MX_HBRIDGE_NUM))
#define MX_HBRIDGE_PORTC		CAL_APPEND(PORT,CAL_APPEND(MX_HBRIDGE_PORTC_, MX_HBRIDGE_NUM))
#define MX_HBRIDGE_TRISC		CAL_APPEND(TRIS,CAL_APPEND(MX_HBRIDGE_PORTC_, MX_HBRIDGE_NUM))
#define MX_HBRIDGE_PORTD		CAL_APPEND(PORT,CAL_APPEND(MX_HBRIDGE_PORTD_, MX_HBRIDGE_NUM))
#define MX_HBRIDGE_TRISD		CAL_APPEND(TRIS,CAL_APPEND(MX_HBRIDGE_PORTD_, MX_HBRIDGE_NUM))

#define MX_HBRIDGE_A_RPOR_X		CAL_APPEND(MX_HBRIDGE_A_RPOR_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_B_RPOR_X		CAL_APPEND(MX_HBRIDGE_B_RPOR_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_C_RPOR_X		CAL_APPEND(MX_HBRIDGE_C_RPOR_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_D_RPOR_X		CAL_APPEND(MX_HBRIDGE_D_RPOR_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_A_RPOC_X		CAL_APPEND(MX_HBRIDGE_A_RPOC_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_B_RPOC_X		CAL_APPEND(MX_HBRIDGE_B_RPOC_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_C_RPOC_X		CAL_APPEND(MX_HBRIDGE_C_RPOC_, MX_HBRIDGE_NUM)
#define MX_HBRIDGE_D_RPOC_X		CAL_APPEND(MX_HBRIDGE_D_RPOC_, MX_HBRIDGE_NUM)


CALFUNCTION(void, FC_CAL_HBRIDGE_Enable_, (void));
CALFUNCTION(void, FC_CAL_HBRIDGE_Disable_, (void));
CALFUNCTION(void, FC_CAL_HBRIDGE_SetSpeed_, (MX_UINT16 duty));
CALFUNCTION(void, FC_CAL_HBRIDGE_SetDirection_, (MX_UINT8 direction));


#ifndef _CCPTMRS0_C1TSEL0_POSN
  #ifdef _CCPTMRS_C1TSEL0_POSN
    #define CCPTMRS0 CCPTMRS
  #endif
#endif



#ifdef MX_HBRIDGE_TYPE

  #if (MX_HBRIDGE_EN_X == 1)

	#if (MX_HBRIDGE_TYPE == 1)			//PIC16F1937

		CALFUNCTION(void, FC_CAL_HBRIDGE_Enable_, (void))
		{
			//Set pins to output - This is needed for the HBRIDGE outputs to work
			FC_CAL_Bit_Low_DDR (MX_HBRIDGE_PORTA, MX_HBRIDGE_TRISA, MX_HBRIDGE_PINA_X);		//HBRIDGE pin A is an output
			FC_CAL_Bit_Low_DDR (MX_HBRIDGE_PORTB, MX_HBRIDGE_TRISB, MX_HBRIDGE_PINB_X);		//HBRIDGE pin B is an output

			#if (MX_HBRIDGE_MODE_X == 1)
				FC_CAL_Bit_Low_DDR (MX_HBRIDGE_PORTC, MX_HBRIDGE_TRISC, MX_HBRIDGE_PINC_X);	//HBRIDGE pin C is an output
				FC_CAL_Bit_Low_DDR (MX_HBRIDGE_PORTD, MX_HBRIDGE_TRISD, MX_HBRIDGE_PIND_X);	//HBRIDGE pin D is an output
			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 1)

				//Disable PWM functionality
				CCP1CON = 0;

				//Configure CCP1 Timer - Default Timer2
				CCPTMRS0 = CCPTMRS0 & ~(0x03);
				#if (MX_HBRIDGE_TIMER_X == 2)
					PR2 = (MX_HBRIDGE_PERIOD_X >> 2);
					T2CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 4)
					CCPTMRS0 = CCPTMRS0 | 0x01;
					PR4 = (MX_HBRIDGE_PERIOD_X >> 2);
					T4CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 6)
					CCPTMRS0 = CCPTMRS0 | 0x02;
					PR6 = (MX_HBRIDGE_PERIOD_X >> 2);
					T6CON = MX_HBRIDGE_PRESCALE_X;
				#endif

				//Initialise the duty to 0%
				CCPR1L = 0;

				//Set the mode and enable
				#if (MX_HBRIDGE_MODE_X == 0)			//Half Bridge Mode
				  PWM1CON = MX_HBRIDGE_RC_X;			//Initialise rising counter
				  CCP1CON = 0x80 | MX_HBRIDGE_POL_X;	//Enable PWM HB Mode
				#endif
				#if (MX_HBRIDGE_MODE_X == 1)			//Full Bridge Mode
				  CCP1CON = 0x40 | MX_HBRIDGE_POL_X;	//Enable PWM FB Forwards Mode
				#endif

			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 2)

				//Disable PWM functionality
				CCP2CON = 0;

				//Configure CCP1 Timer - Default Timer2
				CCPTMRS0 = CCPTMRS0 & ~(0x0C);
				#if (MX_HBRIDGE_TIMER_X == 2)
					PR2 = (MX_HBRIDGE_PERIOD_X >> 2);
					T2CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 4)
					CCPTMRS0 = CCPTMRS0 | 0x04;
					PR4 = (MX_HBRIDGE_PERIOD_X >> 2);
					T4CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 6)
					CCPTMRS0 = CCPTMRS0 | 0x08;
					PR6 = (MX_HBRIDGE_PERIOD_X >> 2);
					T6CON = MX_HBRIDGE_PRESCALE_X;
				#endif

				//Initialise the duty to 0%
				CCPR2L = 0;

				//Alt Pins
				#if (MX_HBRIDGE_ALTA_X == 1)
				    APFCON |= 0x01;
				#endif
				#if (MX_HBRIDGE_ALTB_X == 1)
					APFCON |= 0x10;
				#endif

				//Set the mode and enable
				#if (MX_HBRIDGE_MODE_X == 0)			//Half Bridge Mode
				  PWM2CON = MX_HBRIDGE_RC_X;			//Initialise rising counter
				  CCP2CON = 0x80 | MX_HBRIDGE_POL_X;	//Enable PWM HB Mode
				#endif
				#if (MX_HBRIDGE_MODE_X == 1)			//Full Bridge Mode
				  CCP2CON = 0x40 | MX_HBRIDGE_POL_X;	//Enable PWM FB Forwards Mode
				#endif

			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 3)

				//Disable PWM functionality
				CCP3CON = 0;

				//Configure CCP1 Timer - Default Timer2
				CCPTMRS0 = CCPTMRS0 & ~(0x30);
				#if (MX_HBRIDGE_TIMER_X == 2)
					PR2 = (MX_HBRIDGE_PERIOD_X >> 2);
					T2CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 4)
					CCPTMRS0 = CCPTMRS0 | 0x10;
					PR4 = (MX_HBRIDGE_PERIOD_X >> 2);
					T4CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 6)
					CCPTMRS0 = CCPTMRS0 | 0x20;
					PR6 = (MX_HBRIDGE_PERIOD_X >> 2);
					T6CON = MX_HBRIDGE_PRESCALE_X;
				#endif

				//Initialise the duty to 0%
				CCPR3L = 0;

				//Alt Pins
				#if (MX_HBRIDGE_ALTA_X == 1)
				    APFCON |= 0x40;
				#endif

				//Set the mode and enable
				#if (MX_HBRIDGE_MODE_X == 0)			//Half Bridge Mode
				  PWM3CON = MX_HBRIDGE_RC_X;			//Initialise rising counter
				  CCP3CON = 0x80 | MX_HBRIDGE_POL_X;	//Enable PWM HB Mode
				#endif
				#if (MX_HBRIDGE_MODE_X == 1)			//Full Bridge Mode
				  CCP3CON = 0x40 | MX_HBRIDGE_POL_X;	//Enable PWM FB Forwards Mode
				#endif

			#endif
		}

		CALFUNCTION(void, FC_CAL_HBRIDGE_Disable_, (void))
		{
			#if (MX_HBRIDGE_CHANNEL_X == 1)
				CCP1CON = 0;							//Disable PWM functionality
			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 2)
				CCP2CON = 0;							//Disable PWM functionality
			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 3)
				CCP3CON = 0;							//Disable PWM functionality
			#endif
		}

		CALFUNCTION(void, FC_CAL_HBRIDGE_SetSpeed_, (MX_UINT16 duty))
		{

			#ifndef MX_PWM_NEW_TMR_CONF
				MX_UINT8 nCCPxCONtemp;
				MX_UINT8 dutyTemp;
			#endif

			if (duty > 1023)
				duty = 1023;

			#if (MX_HBRIDGE_CHANNEL_X == 1)

				CCPR1L = duty >> 2;
				dutyTemp = (duty & 0x03) << 4;
				nCCPxCONtemp = (CCP1CON & 0xCF) | dutyTemp;
				CCP1CON = nCCPxCONtemp;

			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 2)

				CCPR2L = duty >> 2;
				dutyTemp = (duty & 0x03) << 4;
				nCCPxCONtemp = (CCP2CON & 0xCF) | dutyTemp;
				CCP2CON = nCCPxCONtemp;

			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 3)

				CCPR3L = duty >> 2;
				dutyTemp = (duty & 0x03) << 4;
				nCCPxCONtemp = (CCP3CON & 0xCF) | dutyTemp;
				CCP3CON = nCCPxCONtemp;

			#endif
		}

		CALFUNCTION(void, FC_CAL_HBRIDGE_SetDirection_, (MX_UINT8 direction))
		{
			#if (MX_HBRIDGE_MODE_X == 1)				//Direction Control Only In Full Bridge Mode

				#if (MX_HBRIDGE_CHANNEL_X == 1)

					if (direction == 0)					//Forwards
						CCP1CON &= 0x7F;
					else								//Reverse
						CCP1CON |= 0x80;

				#endif

				#if (MX_HBRIDGE_CHANNEL_X == 2)

					if (direction == 0)					//Forwards
						CCP2CON &= 0x7F;
					else								//Reverse
						CCP2CON |= 0x80;

				#endif

				#if (MX_HBRIDGE_CHANNEL_X == 3)

					if (direction == 0)					//Forwards
						CCP3CON &= 0x7F;
					else								//Reverse
						CCP3CON |= 0x80;

				#endif

			#endif
		}

	#endif	//MX_HBRIDGE_TYPE_X == 1




	#if (MX_HBRIDGE_TYPE == 2)			//PIC16F18877

		CALFUNCTION(void, FC_CAL_HBRIDGE_Enable_, (void))
		{
			#ifdef MX_PWM_REMAPPABLE

				MX_HBRIDGE_A_RPOR_X = MX_HBRIDGE_A_RPOC_X;			//Assign RP Output A
				MX_HBRIDGE_B_RPOR_X = MX_HBRIDGE_B_RPOC_X;			//Assign RP Output B

				#if (MX_HBRIDGE_MODE_X == 1)						//Pins C&D only available in Full Bridge Mode
					MX_HBRIDGE_C_RPOR_X = MX_HBRIDGE_C_RPOC_X;		//Assign RP Output C
					MX_HBRIDGE_D_RPOR_X = MX_HBRIDGE_D_RPOC_X;		//Assign RP Output D
				#endif

			#endif

			//Set pins to output - This is needed for the HBRIDGE outputs to work
			FC_CAL_Bit_Low_DDR (MX_HBRIDGE_PORTA, MX_HBRIDGE_TRISA, MX_HBRIDGE_PINA_X);		//HBRIDGE pin A is an output
			FC_CAL_Bit_Low_DDR (MX_HBRIDGE_PORTB, MX_HBRIDGE_TRISB, MX_HBRIDGE_PINB_X);		//HBRIDGE pin B is an output

			#if (MX_HBRIDGE_MODE_X == 1)
				FC_CAL_Bit_Low_DDR (MX_HBRIDGE_PORTC, MX_HBRIDGE_TRISC, MX_HBRIDGE_PINC_X);	//HBRIDGE pin C is an output
				FC_CAL_Bit_Low_DDR (MX_HBRIDGE_PORTD, MX_HBRIDGE_TRISD, MX_HBRIDGE_PIND_X);	//HBRIDGE pin D is an output
			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 1)

				//Disable PWM functionality
				CCP1CON = 0;

				//Configure CCP1 Timer - Default Timer2
				CCPTMRS0 = CCPTMRS0 & ~(0x03);
				#if (MX_HBRIDGE_TIMER_X == 2)
					CCPTMRS0 = CCPTMRS0 | 0x01;
					PR2 = (MX_HBRIDGE_PERIOD_X >> 2);
					T2CLKCON = 0x01;
					T2CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 4)
					CCPTMRS0 = CCPTMRS0 | 0x02;
					PR4 = (MX_HBRIDGE_PERIOD_X >> 2);
					T4CLKCON = 0x01;
					T4CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 6)
					CCPTMRS0 = CCPTMRS0 | 0x03;
					PR6 = (MX_HBRIDGE_PERIOD_X >> 2);
					T6CLKCON = 0x01;
					T6CON = MX_HBRIDGE_PRESCALE_X;
				#endif

				//Initialise the duty to 0%
				CCPR1L = 0;
				CCPR1H = 0;

				CCP1CON = 0x9F;							//Enable CCP Peripheral - PWM Mode

				//Initialise rising and falling counters
				CWG1DBR = MX_HBRIDGE_RC_X;
				CWG1DBF	= MX_HBRIDGE_FC_X;

				CWG1CON1 = MX_HBRIDGE_POL_X;			//Set output polarity
				CWG1ISM = 0x01;							//Based on CCP1 period / duty

				//Set the mode and enable
				#if (MX_HBRIDGE_MODE_X == 0)			//Half Bridge Mode
				  CWG1CON0 = 0x84;						//Enable CWG HB Mode
				#endif
				#if (MX_HBRIDGE_MODE_X == 1)			//Full Bridge Mode
				  CWG1CON0 = 0x82;						//Enable CWG FB Forwards Mode
				#endif

			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 2)

				//Disable PWM functionality
				CCP2CON = 0;

				//Configure CCP1 Timer - Default Timer2
				CCPTMRS0 = CCPTMRS0 & ~(0x0C);
				#if (MX_HBRIDGE_TIMER_X == 2)
					CCPTMRS0 = CCPTMRS0 | 0x04;
					PR2 = (MX_HBRIDGE_PERIOD_X >> 2);
					T2CLKCON = 0x01;
					T2CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 4)
					CCPTMRS0 = CCPTMRS0 | 0x08;
					PR4 = (MX_HBRIDGE_PERIOD_X >> 2);
					T4CLKCON = 0x01;
					T4CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 6)
					CCPTMRS0 = CCPTMRS0 | 0x0C;
					PR6 = (MX_HBRIDGE_PERIOD_X >> 2);
					T6CLKCON = 0x01;
					T6CON = MX_HBRIDGE_PRESCALE_X;
				#endif

				//Initialise the duty to 0%
				CCPR2L = 0;
				CCPR2H = 0;

				CCP2CON = 0x9F;							//Enable CCP Peripheral - PWM Mode

				//Initialise rising and falling counters
				CWG2DBR = MX_HBRIDGE_RC_X;
				CWG2DBF	= MX_HBRIDGE_FC_X;

				CWG2CON1 = MX_HBRIDGE_POL_X;			//Set output polarity
				CWG2ISM = 0x02;							//Based on CCP2 period / duty

				//Set the mode and enable
				#if (MX_HBRIDGE_MODE_X == 0)			//Half Bridge Mode
				  CWG2CON0 = 0x84;						//Enable CWG HB Mode
				#endif
				#if (MX_HBRIDGE_MODE_X == 1)			//Full Bridge Mode
				  CWG2CON0 = 0x82;						//Enable CWG FB Forwards Mode
				#endif

			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 3)

				//Disable PWM functionality
				CCP3CON = 0;

				//Configure CCP1 Timer - Default Timer2
				CCPTMRS0 = CCPTMRS0 & ~(0x30);
				#if (MX_HBRIDGE_TIMER_X == 2)
					CCPTMRS0 = CCPTMRS0 | 0x01;
					PR2 = (MX_HBRIDGE_PERIOD_X >> 2);
					T2CLKCON = 0x01;
					T2CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 4)
					CCPTMRS0 = CCPTMRS0 | 0x02;
					PR4 = (MX_HBRIDGE_PERIOD_X >> 2);
					T4CLKCON = 0x01;
					T4CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 6)
					CCPTMRS0 = CCPTMRS0 | 0x03;
					PR6 = (MX_HBRIDGE_PERIOD_X >> 2);
					T6CLKCON = 0x01;
					T6CON = MX_HBRIDGE_PRESCALE_X;
				#endif

				//Initialise the duty to 0%
				CCPR3L = 0;
				CCPR3H = 0;

				CCP3CON = 0x9F;							//Enable CCP Peripheral - PWM Mode

				//Initialise rising and falling counters
				CWG3DBR = MX_HBRIDGE_RC_X;
				CWG3DBF	= MX_HBRIDGE_FC_X;

				CWG3CON1 = MX_HBRIDGE_POL_X;			//Set output polarity
				CWG3ISM = 0x01;							//Based on CCP1 period / duty

				//Set the mode and enable
				#if (MX_HBRIDGE_MODE_X == 0)			//Half Bridge Mode
				  CWG3CON0 = 0x84;						//Enable CWG HB Mode
				#endif
				#if (MX_HBRIDGE_MODE_X == 1)			//Full Bridge Mode
				  CWG3CON0 = 0x82;						//Enable CWG FB Forwards Mode
				#endif

			#endif
		}

		CALFUNCTION(void, FC_CAL_HBRIDGE_Disable_, (void))
		{
			#if (MX_HBRIDGE_CHANNEL_X == 1)
				CCP1CON = 0;			//Disable PWM functionality
				CWG1CON0 = 0;			//Disable CWG functionality
			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 2)
				CCP2CON = 0;			//Disable PWM functionality
				CWG2CON0 = 0;			//Disable CWG functionality
			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 3)
				CCP3CON = 0;			//Disable PWM functionality
				CWG3CON0 = 0;			//Disable CWG functionality
			#endif
		}

		CALFUNCTION(void, FC_CAL_HBRIDGE_SetSpeed_, (MX_UINT16 duty))
		{
			if (duty > 1023)
				duty = 1023;

			#if (MX_HBRIDGE_CHANNEL_X == 1)
				CCPR1H = duty >> 2;				//8MSB HHHHHHHH
				CCPR1L = duty << 6;				//2LSB LL000000
			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 2)
				CCPR2H = duty >> 2;				//8MSB HHHHHHHH
				CCPR2L = duty << 6;				//2LSB LL000000
			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 3)
				CCPR3H = duty >> 2;				//8MSB HHHHHHHH
				CCPR3L = duty << 6;				//2LSB LL000000
			#endif
		}

		CALFUNCTION(void, FC_CAL_HBRIDGE_SetDirection_, (MX_UINT8 direction))
		{
			#if (MX_HBRIDGE_MODE_X == 1)				//Direction Control Only In Full Bridge Mode

				#if (MX_HBRIDGE_CHANNEL_X == 1)

					if (direction == 0)					//Forwards
						CWG1CON0 &= 0xFE;
					else								//Reverse
						CWG1CON0 |= 0x01;

				#endif

				#if (MX_HBRIDGE_CHANNEL_X == 2)

					if (direction == 0)					//Forwards
						CWG2CON0 &= 0xFE;
					else								//Reverse
						CWG2CON0 |= 0x01;

				#endif

				#if (MX_HBRIDGE_CHANNEL_X == 3)

					if (direction == 0)					//Forwards
						CWG3CON0 &= 0xFE;
					else								//Reverse
						CWG3CON0 |= 0x01;

				#endif

			#endif
		}

	#endif	//MX_HBRIDGE_TYPE_X == 2



	#if (MX_HBRIDGE_TYPE == 3)			//PIC16F1509

		CALFUNCTION(void, FC_CAL_HBRIDGE_Enable_, (void))
		{
			//Set pins to output - This is needed for the HBRIDGE outputs to work
			FC_CAL_Bit_Low_DDR (MX_HBRIDGE_PORTA, MX_HBRIDGE_TRISA, MX_HBRIDGE_PINA_X);		//HBRIDGE pin A is an output
			FC_CAL_Bit_Low_DDR (MX_HBRIDGE_PORTB, MX_HBRIDGE_TRISB, MX_HBRIDGE_PINB_X);		//HBRIDGE pin B is an output

			#if (MX_HBRIDGE_CHANNEL_X == 1)

				//Disable PWM functionality
				PWM1CON = 0;

				//Configure PWM Timer - Timer2
				#if (MX_HBRIDGE_TIMER_X == 2)
					PR2 = (MX_HBRIDGE_PERIOD_X >> 2);
					T2CON = MX_HBRIDGE_PRESCALE_X;
				#endif

				//Initialise the duty to 0%
				PWM1DCH = 0;
				PWM1DCL = 0;

				PWM1CON = 0x80;							//Enable PWM Peripheral

				//Alt Pins
				#if (MX_HBRIDGE_ALTA_X == 1)
				    APFCON |= 0x40;
				#endif
				#if (MX_HBRIDGE_ALTB_X == 1)
					APFCON |= 0x80;
				#endif

				CWG1CON1 = 0x02;						//Based on PWM1 period / duty

				//Initialise rising and falling counters
				CWG1DBR = MX_HBRIDGE_RC_X;
				CWG1DBF	= MX_HBRIDGE_FC_X;

				//Set the mode and enable
				#if (MX_HBRIDGE_MODE_X == 0)			//Half Bridge Mode
				  CWG1CON0 = 0xE0 | MX_HBRIDGE_POL_X;	//Enable PWM HB Mode
				#endif

			#endif

		}

		CALFUNCTION(void, FC_CAL_HBRIDGE_Disable_, (void))
		{
			#if (MX_HBRIDGE_CHANNEL_X == 1)
				PWM1CON = 0;							//Disable PWM functionality
				CWG1CON0 = 0;							//Disable CWG Functionality
			#endif
		}

		CALFUNCTION(void, FC_CAL_HBRIDGE_SetSpeed_, (MX_UINT16 duty))
		{
			if (duty > 1023)
				duty = 1023;

			#if (MX_HBRIDGE_CHANNEL_X == 1)

				PWM1DCH = duty >> 2;
				PWM1DCL = duty << 6;

			#endif

		}

		CALFUNCTION(void, FC_CAL_HBRIDGE_SetDirection_, (MX_UINT8 direction))
		{

		}

	#endif	//MX_HBRIDGE_TYPE_X == 3



	#if (MX_HBRIDGE_TYPE == 4)			//PIC16F18313

		CALFUNCTION(void, FC_CAL_HBRIDGE_Enable_, (void))
		{
			#ifdef MX_PWM_REMAPPABLE

				MX_HBRIDGE_A_RPOR_X = MX_HBRIDGE_A_RPOC_X;			//Assign RP Output A
				MX_HBRIDGE_B_RPOR_X = MX_HBRIDGE_B_RPOC_X;			//Assign RP Output B

				#if (MX_HBRIDGE_MODE_X == 1)						//Pins C&D only available in Full Bridge Mode
					MX_HBRIDGE_C_RPOR_X = MX_HBRIDGE_C_RPOC_X;		//Assign RP Output C
					MX_HBRIDGE_D_RPOR_X = MX_HBRIDGE_D_RPOC_X;		//Assign RP Output D
				#endif

			#endif

			//Set pins to output - This is needed for the HBRIDGE outputs to work
			FC_CAL_Bit_Low_DDR (MX_HBRIDGE_PORTA, MX_HBRIDGE_TRISA, MX_HBRIDGE_PINA_X);		//HBRIDGE pin A is an output
			FC_CAL_Bit_Low_DDR (MX_HBRIDGE_PORTB, MX_HBRIDGE_TRISB, MX_HBRIDGE_PINB_X);		//HBRIDGE pin B is an output

			#if (MX_HBRIDGE_MODE_X == 1)
				FC_CAL_Bit_Low_DDR (MX_HBRIDGE_PORTC, MX_HBRIDGE_TRISC, MX_HBRIDGE_PINC_X);	//HBRIDGE pin C is an output
				FC_CAL_Bit_Low_DDR (MX_HBRIDGE_PORTD, MX_HBRIDGE_TRISD, MX_HBRIDGE_PIND_X);	//HBRIDGE pin D is an output
			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 1)

				//Disable PWM functionality
				CCP1CON = 0;

				//Configure CCP1 Timer - Default Timer2
				CCPTMRS0 = CCPTMRS0 & ~(0x03);
				#if (MX_HBRIDGE_TIMER_X == 2)
					PR2 = (MX_HBRIDGE_PERIOD_X >> 2);
					T2CLKCON = 0x01;
					T2CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 4)
					CCPTMRS = CCPTMRS | 0x02;
					PR4 = (MX_HBRIDGE_PERIOD_X >> 2);
					T4CLKCON = 0x01;
					T4CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 6)
					CCPTMRS = CCPTMRS | 0x03;
					PR6 = (MX_HBRIDGE_PERIOD_X >> 2);
					T6CLKCON = 0x01;
					T6CON = MX_HBRIDGE_PRESCALE_X;
				#endif

				//Initialise the duty to 0%
				CCPR1L = 0;
				CCPR1H = 0;

				CCP1CON = 0x9F;							//Enable CCP Peripheral - PWM Mode

				//Initialise rising and falling counters
				CWG1DBR = MX_HBRIDGE_RC_X;
				CWG1DBF	= MX_HBRIDGE_FC_X;

				CWG1CON1 = MX_HBRIDGE_POL_X;			//Set output polarity
				CWG1DAT = 0x03;							//Based on CCP1 period / duty

				//Set the mode and enable
				#if (MX_HBRIDGE_MODE_X == 0)			//Half Bridge Mode
				  CWG1CON0 = 0x84;						//Enable CWG HB Mode
				#endif
				#if (MX_HBRIDGE_MODE_X == 1)			//Full Bridge Mode
				  CWG1CON0 = 0x82;						//Enable CWG FB Forwards Mode
				#endif

			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 2)

				//Disable PWM functionality
				CCP2CON = 0;

				//Configure CCP1 Timer - Default Timer2
				CCPTMRS0 = CCPTMRS0 & ~(0x0C);
				#if (MX_HBRIDGE_TIMER_X == 2)
					PR2 = (MX_HBRIDGE_PERIOD_X >> 2);
					T2CLKCON = 0x01;
					T2CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 4)
					CCPTMRS = CCPTMRS | 0x08;
					PR4 = (MX_HBRIDGE_PERIOD_X >> 2);
					T4CLKCON = 0x01;
					T4CON = MX_HBRIDGE_PRESCALE_X;
				#endif
				#if (MX_HBRIDGE_TIMER_X == 6)
					CCPTMRS = CCPTMRS | 0x0C;
					PR6 = (MX_HBRIDGE_PERIOD_X >> 2);
					T6CLKCON = 0x01;
					T6CON = MX_HBRIDGE_PRESCALE_X;
				#endif

				//Initialise the duty to 0%
				CCPR2L = 0;
				CCPR2H = 0;

				CCP2CON = 0x9F;							//Enable CCP Peripheral - PWM Mode

				//Initialise rising and falling counters
				CWG2DBR = MX_HBRIDGE_RC_X;
				CWG2DBF	= MX_HBRIDGE_FC_X;

				CWG2CON1 = MX_HBRIDGE_POL_X;			//Set output polarity
				CWG1DAT = 0x04;							//Based on CCP2 period / duty

				//Set the mode and enable
				#if (MX_HBRIDGE_MODE_X == 0)			//Half Bridge Mode
				  CWG2CON0 = 0x84;						//Enable CWG HB Mode
				#endif
				#if (MX_HBRIDGE_MODE_X == 1)			//Full Bridge Mode
				  CWG2CON0 = 0x82;						//Enable CWG FB Forwards Mode
				#endif

			#endif

		}

		CALFUNCTION(void, FC_CAL_HBRIDGE_Disable_, (void))
		{
			#if (MX_HBRIDGE_CHANNEL_X == 1)
				CCP1CON = 0;			//Disable PWM functionality
				CWG1CON0 = 0;			//Disable CWG functionality
			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 2)
				CCP2CON = 0;			//Disable PWM functionality
				CWG2CON0 = 0;			//Disable CWG functionality
			#endif

		}

		CALFUNCTION(void, FC_CAL_HBRIDGE_SetSpeed_, (MX_UINT16 duty))
		{
			if (duty > 1023)
				duty = 1023;

			#if (MX_HBRIDGE_CHANNEL_X == 1)
				CCPR1H = duty >> 2;				//8MSB HHHHHHHH
				CCPR1L = duty << 6;				//2LSB LL000000
			#endif

			#if (MX_HBRIDGE_CHANNEL_X == 2)
				CCPR2H = duty >> 2;				//8MSB HHHHHHHH
				CCPR2L = duty << 6;				//2LSB LL000000
			#endif

		}

		CALFUNCTION(void, FC_CAL_HBRIDGE_SetDirection_, (MX_UINT8 direction))
		{
			#if (MX_HBRIDGE_MODE_X == 1)				//Direction Control Only In Full Bridge Mode

				#if (MX_HBRIDGE_CHANNEL_X == 1)

					if (direction == 0)					//Forwards
						CWG1CON0 &= 0xFE;
					else								//Reverse
						CWG1CON0 |= 0x01;

				#endif

				#if (MX_HBRIDGE_CHANNEL_X == 2)

					if (direction == 0)					//Forwards
						CWG2CON0 &= 0xFE;
					else								//Reverse
						CWG2CON0 |= 0x01;

				#endif

			#endif
		}

	#endif	//MX_HBRIDGE_TYPE_X == 4

  #endif  //MX_HBRIDGE_EN_X == 1

#endif	//MX_HBRIDGE_TYPE
