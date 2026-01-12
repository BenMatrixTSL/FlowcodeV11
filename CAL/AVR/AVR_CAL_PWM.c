// CRC: 77485F5F6A861F9125D47827B4DE492656C5431E478E8046055FD2257F64F1F30A7638C619EA04AA769141413688B2AC9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5390854540C52AB2B578D38B0FD7FA9D239656F85CD0F7BA617220D16E12EB6C8309A69E008B0A1100BB09D5F5A9813D12CAE19D41C58D433BCCFA3ACDFBC56AD448B7AD6EDD4FBBC985AF1B5FAAEC3B1E78EEC369734AFBC549D34A0D5AD11F30E252509A6FE96C5B155D677C17D89274398E66EAD1BB8B7E00AF8598B7CA62D1079227E43D7E189
// REVISION: 1.0
// GUID: 59F0DEE2-5D33-4509-A27A-4F629CFFE4B9
// DATE: 08\08\2022
// DIR: CAL\AVR\AVR_CAL_PWM.c
/*********************************************************************
 *                  Flowcode CAL PWM File
 *
 * File: AVR_CAL_PWM.c
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
 * 051011 | SK | Created
 * 020312 | BR | Updated to v5.1 CAL Schema
 * 230512 | BR | Some minor XMEGA related code, hopefully better support to come
 * 280512 | BR | XMEGA PWM support
 * 190612 | BR | Fixed a bug when using timer 1 PWM channels
 * 280612 | BR | Added some addition PWM channels 14-16
 * 030713 | LM | Standard API calls
 */


#define MX_PWM_CHANNEL_X		CAL_APPEND(MX_PWM_CHANNEL_, MX_PWM_NUM)
#define MX_PWM_HWALT_X			CAL_APPEND(MX_PWM_HWALT_, 	MX_PWM_NUM)
#define MX_PWM_PORT_X			CAL_APPEND(MX_PWM_PORT_, 	MX_PWM_NUM)
#define MX_PWM_TRIS_X			CAL_APPEND(MX_PWM_TRIS_, 	MX_PWM_NUM)
#define MX_PWM_PIN_X			CAL_APPEND(MX_PWM_PIN_, 	MX_PWM_NUM)

//PWM Functions
CALFUNCTION(void, FC_CAL_PWM_Enable_, (void));
CALFUNCTION(void, FC_CAL_PWM_Disable_, (void));
CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 duty));
CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 period, MX_UINT16 prescaler));
CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 duty));

//AVR PWM specific defines
#ifndef MX_PWMTYPE
	#define MX_PWMTYPE 1
#endif

#ifndef WGM13VAL
	#ifdef WGM13					// The presence of WGM13..12 determines the PWM functionality
		#define WGM13VAL (1<<WGM13)
	#else
		#define WGM13VAL 0
	#endif
#endif

#ifdef COM10						// AT90S4433 definitions
	#ifndef COM1A0
		#define COM1A0	COM10
	#endif
	#ifndef COM1A1
		#define COM1A1	COM11
	#endif
#endif

#ifndef MX_PWM_TMR0_CNT
	#define MX_PWM_TMR0_CNT	0
#endif
#ifndef MX_PWM_TMR1_CNT
	#define MX_PWM_TMR1_CNT	0
#endif
#ifndef MX_PWM_TMR2_CNT
	#define MX_PWM_TMR2_CNT	0
#endif
#ifndef MX_PWM_TMR3_CNT
	#define MX_PWM_TMR3_CNT	0
#endif
#ifndef MX_PWM_TMR4_CNT
	#define MX_PWM_TMR4_CNT	0
#endif
#ifndef MX_PWM_TMR5_CNT
	#define MX_PWM_TMR5_CNT	0
#endif

//Work out which timer resource to use.
#ifndef MX_PWM
	#error "No PWM channels currently available on this device"
#else
	#if (MX_PWM_CHANNEL_X > MX_PWM_CNT)
		#error "PWM channel selected is greater then available PWM Channel Count"
	#else
		#if (MX_PWM_CHANNEL_X <= MX_PWM_TMR0_CNT)

			#warning "PWM Channel Uses Resource Timer 0"

			#ifndef MX_XMEGA
				#if (MX_PWM_CHANNEL_X == 1)
					#ifdef OCR0A
						#define	MX_DUTY_REG_X 	OCR0A
					#else
						#ifdef OCR0
							#define	MX_DUTY_REG_X 	OCR0
						#endif
					#endif
					#ifdef COM0A0
						#define MX_PWM_COM0_X	COM0A0
					#else
						#ifdef COM00
							#define MX_PWM_COM0_X	COM00
						#endif
					#endif
					#ifdef COM0A1
						#define MX_PWM_COM1_X	COM0A1
					#else
						#ifdef COM01
							#define MX_PWM_COM1_X	COM01
						#endif
					#endif
					#ifdef	PWM0A
						#define MX_PWM_CHAN_X	PWM0A
					#endif
				#endif
				#if (MX_PWM_CHANNEL_X == 2)
					#define	MX_DUTY_REG_X 	OCR0B
					#define MX_PWM_COM0_X	COM0B0
					#define MX_PWM_COM1_X	COM0B1
					#ifdef	PWM0B
						#define MX_PWM_CHAN_X	PWM0B
					#endif
				#endif

				#ifdef MX_TINY
					#ifdef OCR0C
						#define MX_PERIOD_X			OCR0C
					#else
						#ifdef ICR0
							#define MX_PERIOD_X		ICR0
						#endif
					#endif
				#else
					#ifdef ICR0
						#define MX_PERIOD_X			ICR0
					#endif
				#endif

				#ifdef TCCR0
					#define MX_TCCR_X 		TCCR0
					#define MX_PRESCALE_X 	TCCR0
				#else
					#define MX_TCCR_X 		TCCR0A
					#ifdef TCCR0B
						#define MX_PRESCALE_X 	TCCR0B
					#else
						#define MX_PRESCALE_X 	TCCR0A
					#endif
				#endif
			#endif

		#else
			#define MX_PWM_CHANNEL_Y1	(MX_PWM_CHANNEL_X - MX_PWM_TMR0_CNT)
			#if (MX_PWM_CHANNEL_Y1 <= MX_PWM_TMR1_CNT)

				#warning "PWM Channel Uses Resource Timer 1"

				#define MX_PWM_16BIT_TIMER

				#if (MX_PWM_CHANNEL_Y1 == 1)
					#define	MX_DUTY_REG_X 	OCR1A
					#define MX_PWM_COM0_X	COM1A0
					#define MX_PWM_COM1_X	COM1A1
					#ifdef	PWM1A
						#define MX_PWM_CHAN_X	PWM1A
					#endif
				#endif
				#if (MX_PWM_CHANNEL_Y1 == 2)
					#define	MX_DUTY_REG_X 	OCR1B
					#define MX_PWM_COM0_X	COM1B0
					#define MX_PWM_COM1_X	COM1B1
					#ifdef	PWM1B
						#define MX_PWM_CHAN_X	PWM1B
					#endif
				#endif
				#if (MX_PWM_CHANNEL_Y1 == 3)
					#define	MX_DUTY_REG_X 	OCR1C
					#define MX_PWM_COM0_X	COM1C0
					#define MX_PWM_COM1_X	COM1C1
					#ifdef	PWM1C
						#define MX_PWM_CHAN_X	PWM1C
					#endif
				#endif

				#ifdef MX_TINY
				  	#ifdef OCR1C
						#define MX_PERIOD_X			OCR1C
				  	#else
						#ifdef ICR1
							#define MX_PERIOD_X		ICR1
						#endif
				  	#endif
				#else
				  	#ifdef ICR1
						#define MX_PERIOD_X			ICR1
				  	#endif
				#endif

				#ifdef TCCR1
					#define MX_TCCR_X 		TCCR1
					#define MX_PRESCALE_X 	TCCR1
				#else
					#define MX_TCCR_X 		TCCR1A
					#ifdef TCCR1B
						#define MX_PRESCALE_X 	TCCR1B
					#else
						#define MX_PRESCALE_X 	TCCR1A
					#endif
				#endif

			#else
				#define MX_PWM_CHANNEL_Y2	(MX_PWM_CHANNEL_Y1 - MX_PWM_TMR1_CNT)
				#if (MX_PWM_CHANNEL_Y2 <= MX_PWM_TMR2_CNT)

					#warning "PWM Channel Uses Resource Timer 2"

					#if (MX_PWM_CHANNEL_Y2 == 1)
						#ifdef OCR2A
							#define	MX_DUTY_REG_X 	OCR2A
						#else
							#define	MX_DUTY_REG_X 	OCR2
						#endif
						#ifdef COM2A0
							#define MX_PWM_COM0_X	COM2A0
							#define MX_PWM_COM1_X	COM2A1
						#else
							#define MX_PWM_COM0_X	COM20
							#define MX_PWM_COM1_X	COM21
						#endif
						#ifdef	PWM2A
							#define MX_PWM_CHAN_X	PWM2A
						#endif
					#endif
					#if (MX_PWM_CHANNEL_Y2 == 2)
						#define	MX_DUTY_REG_X 	OCR2B
						#define MX_PWM_COM0_X	COM2B0
						#define MX_PWM_COM1_X	COM2B1
						#ifdef	PWM2B
							#define MX_PWM_CHAN_X	PWM2B
						#endif
					#endif

					#ifdef MX_TINY
						#ifdef OCR2C
							#define MX_PERIOD_X			OCR2C
						#else
							#ifdef ICR2
								#define MX_PERIOD_X		ICR2
							#endif
						#endif
					#else
						#ifdef ICR2
							#define MX_PERIOD_X			ICR2
						#endif
					#endif

					#ifdef TCCR2
						#define MX_TCCR_X 		TCCR2
						#define MX_PRESCALE_X 	TCCR2
					#else
						#define MX_TCCR_X 		TCCR2A
						#ifdef TCCR2B
							#define MX_PRESCALE_X 	TCCR2B
						#else
							#define MX_PRESCALE_X 	TCCR2A
						#endif
					#endif

				#else
					#define MX_PWM_CHANNEL_Y3	(MX_PWM_CHANNEL_Y2 - MX_PWM_TMR2_CNT)
					#if (MX_PWM_CHANNEL_Y3 <= MX_PWM_TMR3_CNT)

						#warning "PWM Channel Uses Resource Timer 3"

						#define MX_PWM_16BIT_TIMER

						#if (MX_PWM_CHANNEL_Y3 == 1)
							#define	MX_DUTY_REG_X 	OCR3A
							#define MX_PWM_COM0_X	COM3A0
							#define MX_PWM_COM1_X	COM3A1
							#ifdef	PWM3A
								#define MX_PWM_CHAN_X	PWM3A
							#endif
						#endif
						#if (MX_PWM_CHANNEL_Y3 == 2)
							#define	MX_DUTY_REG_X 	OCR3B
							#define MX_PWM_COM0_X	COM3B0
							#define MX_PWM_COM1_X	COM3B1
							#ifdef	PWM3B
								#define MX_PWM_CHAN_X	PWM3B
							#endif
						#endif
						#if (MX_PWM_CHANNEL_Y3 == 3)
							#define	MX_DUTY_REG_X 	OCR3C
							#define MX_PWM_COM0_X	COM3C0
							#define MX_PWM_COM1_X	COM3C1
							#ifdef	PWM3C
								#define MX_PWM_CHAN_X	PWM3C
							#endif
						#endif

						#ifdef MX_TINY
							#ifdef OCR3C
								#define MX_PERIOD_X			OCR3C
							#else
								#ifdef ICR3
									#define MX_PERIOD_X		ICR3
								#endif
							#endif
						#else
							#ifdef ICR3
								#define MX_PERIOD_X			ICR3
							#endif
						#endif

						#ifdef TCCR3
							#define MX_TCCR_X 		TCCR3
							#define MX_PRESCALE_X 	TCCR3
						#else
							#define MX_TCCR_X 		TCCR3A
							#ifdef TCCR3B
								#define MX_PRESCALE_X 	TCCR3B
							#else
								#define MX_PRESCALE_X 	TCCR3A
							#endif
						#endif

					#else
						#define MX_PWM_CHANNEL_Y4	(MX_PWM_CHANNEL_Y3 - MX_PWM_TMR3_CNT)
						#if (MX_PWM_CHANNEL_Y4 <= MX_PWM_TMR4_CNT)

							#warning "PWM Channel Uses Resource Timer 4"

							#define MX_PWM_16BIT_TIMER

							#if (MX_PWM_CHANNEL_Y4 == 1)
								#define	MX_DUTY_REG_X 	OCR4A
								#define MX_PWM_COM0_X	COM4A0
								#define MX_PWM_COM1_X	COM4A1
								#ifdef	PWM4A
									#define MX_PWM_CHAN_X	PWM4A
								#endif
							#endif
							#if (MX_PWM_CHANNEL_Y4 == 2)
								#define	MX_DUTY_REG_X 	OCR4B
								#define MX_PWM_COM0_X	COM4B0
								#define MX_PWM_COM1_X	COM4B1
								#ifdef	PWM4B
									#define MX_PWM_CHAN_X	PWM4B
								#endif
							#endif
							#if (MX_PWM_CHANNEL_Y4 == 3)

								#ifndef COM4C0
									#define	MX_DUTY_REG_X 	OCR4D
									#define MX_PWM_COM0_X	COM4D0
									#define MX_PWM_COM1_X	COM4D1
									#ifdef	PWM4D
										#define MX_PWM_CHAN_X	PWM4D
									#endif
								#else
									#define	MX_DUTY_REG_X 	OCR4C
									#define MX_PWM_COM0_X	COM4C0
									#define MX_PWM_COM1_X	COM4C1
									#ifdef	PWM4C
										#define MX_PWM_CHAN_X	PWM4C
									#endif
								#endif
							#endif

							#ifdef MX_TINY
								#ifdef OCR4C
									#define MX_PERIOD_X			OCR4C
								#else
									#ifdef ICR4
										#define MX_PERIOD_X		ICR4
									#endif
								#endif
							#else
								#ifdef ICR4
									#define MX_PERIOD_X			ICR4
								#endif
							#endif

							#ifdef TCCR4
								#define MX_TCCR_X 		TCCR4
								#define MX_PRESCALE_X 	TCCR4
							#else
								#if (MX_PWM_CHANNEL_Y4 == 3)
									#define MX_TCCR_X 		TCCR4C
								#else
									#define MX_TCCR_X 		TCCR4A
								#endif
								#ifdef TCCR4B
									#define MX_PRESCALE_X 	TCCR4B
								#else
									#define MX_PRESCALE_X 	TCCR4A
								#endif
							#endif

						#else
							#define MX_PWM_CHANNEL_Y5	(MX_PWM_CHANNEL_Y4 - MX_PWM_TMR4_CNT)
							#if (MX_PWM_CHANNEL_Y5 <= MX_PWM_TMR5_CNT)

								#warning "PWM Channel Uses Resource Timer 5"

								#define MX_PWM_16BIT_TIMER

								#if (MX_PWM_CHANNEL_Y5 == 1)
									#define	MX_DUTY_REG_X 	OCR5A
									#define MX_PWM_COM0_X	COM5A0
									#define MX_PWM_COM1_X	COM5A1
									#ifdef	PWM5A
										#define MX_PWM_CHAN_X	PWM5A
									#endif
								#endif
								#if (MX_PWM_CHANNEL_Y5 == 2)
									#define	MX_DUTY_REG_X 	OCR5B
									#define MX_PWM_COM0_X	COM5B0
									#define MX_PWM_COM1_X	COM5B1
									#ifdef	PWM5B
										#define MX_PWM_CHAN_X	PWM5B
									#endif
								#endif
								#if (MX_PWM_CHANNEL_Y5 == 3)
									#define	MX_DUTY_REG_X 	OCR5C
									#define MX_PWM_COM0_X	COM5C0
									#define MX_PWM_COM1_X	COM5C1
									#ifdef	PWM5C
										#define MX_PWM_CHAN_X	PWM5C
									#endif
								#endif

								#ifdef MX_TINY
									#ifdef OCR5C
										#define MX_PERIOD_X			OCR5C
									#else
										#ifdef ICR5
											#define MX_PERIOD_X		ICR5
										#endif
									#endif
								#else
									#ifdef ICR5
										#define MX_PERIOD_X			ICR5
									#endif
								#endif

								#ifdef TCCR5
									#define MX_TCCR_X 		TCCR5
									#define MX_PRESCALE_X 	TCCR5
								#else
									#define MX_TCCR_X 		TCCR5A
									#ifdef TCCR5B
										#define MX_PRESCALE_X 	TCCR5B
									#else
										#define MX_PRESCALE_X 	TCCR5A
									#endif
								#endif
							#else
								#error "PWM channel has not been assigned correctly"
							#endif
						#endif
					#endif
				#endif
			#endif
		#endif
	#endif
#endif


#ifndef MX_PERIOD_X
	#warning "Period control register not available on target device, period will default to 255 + 1"
#endif


CALFUNCTION(void, FC_CAL_PWM_Enable_, (void))
{
  #ifdef MX_PWM

	#if (MX_PWM_HWALT_X == 0)													//Default PWM Pin
	  #ifndef MX_PWM_PORT_X														//Error checking
		#error "This chip does not have PWM channel 1 defined"
	  #endif
		#ifndef MX_XMEGA
		  FC_CAL_Bit_Low_DDR (MX_PWM_PORT_X, MX_PWM_TRIS_X, MX_PWM_PIN_X);		//PWM pin is an output
		#else
		  MX_PWM_PORT_X.DIR |= 1 << MX_PWM_PIN_X;
		#endif
	#else																		//Alternate PWM Pin
	  #ifndef MX_PWM_PORTA_X													//Error checking
		#error "This chip does not have PWM channel 1 alt defined"
	  #endif
		#ifndef MX_XMEGA
		  FC_CAL_Bit_Low_DDR (MX_PWM_PORTA_X, MX_PWM_TRISA_X, MX_PWM_PINA_X);	//PWM pin is an output
		#else
		  MX_PWM_PORTA_X.DIR |= 1 << MX_PWM_PINA_X;
		#endif
	#endif

	#ifndef MX_XMEGA
		#ifdef MX_PWM_CHAN_X
			MX_TCCR_X &= ~(1 << MX_PWM_COM0_X);
			MX_TCCR_X |= (1 << MX_PWM_COM1_X) | (1 << MX_PWM_CHAN_X);		// 8-bit PWM timer mode
		#else
			#ifdef WGM13
				MX_TCCR_X &= ~((1 << MX_PWM_COM0_X) | 0x03);				// Select 'clear output on match'

				#ifdef MX_PWM_16BIT_TIMER
					MX_TCCR_X |= (1 << MX_PWM_COM1_X);							// phase and frequency correct PWM
				#else
					MX_TCCR_X |= (1 << MX_PWM_COM1_X) | 0x01;					// phase and frequency correct PWM
				#endif
			#else
				MX_TCCR_X &= ~((1 << MX_PWM_COM0_X) | 0x02);				// Select 'clear output on match'
				MX_TCCR_X |= (1 << MX_PWM_COM1_X) | 0x01;					// 8-bit PWM timer mode
			#endif
		#endif
	#else
		#if (MX_PWM_CHANNEL_X <= 4 )
			TCC0.CTRLB |= 0x03;												//Single Slope PWM
			TCC0.CTRLB |= (1 << (MX_PWM_CHANNEL_X + 3));					//Enable PWM Channel 1-4
		#else
			TCC1.CTRLB |= 0x03;												//Single Slope PWM
			TCC1.CTRLB |= (1 << (MX_PWM_CHANNEL_X - 1));					//Enable PWM Channel 5-6
		#endif
	#endif

  #else
 	#error "Hardware PWM not supported by Target microcontroller."
  #endif
}


CALFUNCTION(void, FC_CAL_PWM_Disable_, (void))
{
	#ifndef MX_XMEGA
		MX_TCCR_X &= ~(1 << MX_PWM_COM1_X);			//Disable PWM Channel
	#else
		#if (MX_PWM_CHANNEL_X <= 4 )
			TCC0.CTRLB &= ~(1 << (MX_PWM_CHANNEL_X + 3));					//Disable PWM Channel 1-4
		#else
			TCC1.CTRLB &= ~(1 << (MX_PWM_CHANNEL_X - 1));					//Disable PWM Channel 5-6
		#endif
	#endif

	#if (MX_PWM_HWALT_X == 0)													//Default PWM Pin
		#ifndef MX_XMEGA
		  FC_CAL_Bit_In_DDR (MX_PWM_PORT_X, MX_PWM_TRIS_X, MX_PWM_PIN_X);		//PWM pin is an output
		#else
		  MX_PWM_PORT_X.DIR &= ~(1 << MX_PWM_PIN_X);
		#endif
	#else																		//Alternate PWM Pin
		#ifndef MX_XMEGA
		  FC_CAL_Bit_In_DDR (MX_PWM_PORTA_X, MX_PWM_TRISA_X, MX_PWM_PINA_X);	//PWM pin is an output
		#else
		  MX_PWM_PORTA_X.DIR &= ~(1 << MX_PWM_PINA_X);
		#endif
	#endif
}


CALFUNCTION(void, FC_CAL_PWM_SetDuty8Bit_, (MX_UINT8 duty))
{
	#ifndef MX_XMEGA
		MX_DUTY_REG_X = duty;						//Update Capture Compare Count
	#else
		#if (MX_PWM_CHANNEL_X == 1)
			TCC0.CCA = duty;
		#endif
		#if (MX_PWM_CHANNEL_X == 2)
			TCC0.CCB = duty;
		#endif
		#if (MX_PWM_CHANNEL_X == 3)
			TCC0.CCC = duty;
		#endif
		#if (MX_PWM_CHANNEL_X == 4)
			TCC0.CCD = duty;
		#endif
		#if (MX_PWM_CHANNEL_X == 5)
			TCC1.CCA = duty;
		#endif
		#if (MX_PWM_CHANNEL_X == 6)
			TCC1.CCB = duty;
		#endif
	#endif
}


CALFUNCTION(void, FC_CAL_PWM_ChangePeriod_, (MX_UINT16 period, MX_UINT16 prescaler))
{
  #if (MX_PWM_CNT >= 1)							//Hardware Mode

	#ifndef MX_XMEGA

		#ifdef MX_PERIOD_X
			MX_PERIOD_X = period;
		#endif

		#if (MX_PWMTYPE == 2)
			switch (prescaler)
			{
			  //#ifdef MX_PWM_PSCA1
				case 1:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x01;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA2
				case 2:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x02;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA4
				case 4:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x03;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA8
				case 8:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x04;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA16
				case 16:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x05;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA32
				case 32:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x06;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA64
				case 64:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x07;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA128
				case 128:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x08;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA256
				case 256:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x09;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA512
				case 512:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x0a;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA1024
				case 1024:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x0b;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA2048
				case 2048:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x0c;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA4096
				case 4096:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x0d;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA8192
				case 8192:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x0e;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA16384
				case 16384:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x0f;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCAEXTF
				case 0x8000:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x0d;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCAEXTR
				case 0x8001:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0) | 0x0e;
					break;
			  //#endif

				default:
					MX_PRESCALE_X = (MX_PRESCALE_X & 0xf0);
					break;
			}
		#else
			switch (prescaler)
			{
			  //#ifdef MX_PWM_PSCA1
				case 1:
					MX_PRESCALE_X = WGM13VAL | 0x01;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA8
				case 8:
					MX_PRESCALE_X = WGM13VAL | 0x02;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA64
				case 64:
					MX_PRESCALE_X = WGM13VAL | 0x03;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA256
				case 256:
					MX_PRESCALE_X = WGM13VAL | 0x04;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA1024
				case 1024:
					MX_PRESCALE_X = WGM13VAL | 0x05;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCAEXTF
				case 0xffff:
					MX_PRESCALE_X = WGM13VAL | 0x06;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCAEXTR
				case 0xfffe:
					MX_PRESCALE_X = WGM13VAL | 0x07;
					break;
			  //#endif

				default:
					MX_PRESCALE_X = WGM13VAL;
					break;
			}
		#endif
	#else

		#if (MX_PWM_CHANNEL_X <= 4 )
			TCC0.PER = period;					//Set Timer0 Period

			switch (prescaler)
			{
			  //#ifdef MX_PWM_PSCA1
				case 1:
					TCC0.CTRLA = 0x01;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA2
				case 2:
					TCC0.CTRLA = 0x02;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA4
				case 4:
					TCC0.CTRLA = 0x03;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA8
				case 8:
					TCC0.CTRLA = 0x04;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA64
				case 64:
					TCC0.CTRLA = 0x05;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA256
				case 256:
					TCC0.CTRLA = 0x06;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA1024
				case 1024:
					TCC0.CTRLA = 0x07;
					break;
			  //#endif

				default:
					TCC0.CTRLA = 0x03;
					break;
			}

		#else
			TCC1.PER = period;					//Set Timer1 Period

			switch (prescaler)
			{
			  //#ifdef MX_PWM_PSCA1
				case 1:
					TCC1.CTRLA = 0x01;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA2
				case 2:
					TCC1.CTRLA = 0x02;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA4
				case 4:
					TCC1.CTRLA = 0x03;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA8
				case 8:
					TCC1.CTRLA = 0x04;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA64
				case 64:
					TCC1.CTRLA = 0x05;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA256
				case 256:
					TCC1.CTRLA = 0x06;
					break;
			  //#endif
			  //#ifdef MX_PWM_PSCA1024
				case 1024:
					TCC1.CTRLA = 0x07;
					break;
			  //#endif

				default:
					TCC1.CTRLA = 0x03;
					break;
			}

		#endif

	#endif
  #endif
}


CALFUNCTION(void, FC_CAL_PWM_SetDuty10Bit_, (MX_UINT16 duty))
{

	#ifndef MX_XMEGA
		MX_DUTY_REG_X = duty >> 2;						//Update Capture Compare Count
	#else
		#if (MX_PWM_CHANNEL_X == 1)
			TCC0.CCA = duty >> 2;
		#endif
		#if (MX_PWM_CHANNEL_X == 2)
			TCC0.CCB = duty >> 2;
		#endif
		#if (MX_PWM_CHANNEL_X == 3)
			TCC0.CCC = duty >> 2;
		#endif
		#if (MX_PWM_CHANNEL_X == 4)
			TCC0.CCD = duty >> 2;
		#endif
		#if (MX_PWM_CHANNEL_X == 5)
			TCC1.CCA = duty >> 2;
		#endif
		#if (MX_PWM_CHANNEL_X == 6)
			TCC1.CCB = duty >> 2;
		#endif
	#endif

}


#undef MX_DUTY_REG_X
#undef MX_PWM_COM0_X
#undef MX_PWM_COM1_X
#undef MX_TCCR_X
#undef MX_PRESCALE_X
#undef MX_PERIOD_X
#undef MX_PWM_16BIT_TIMER

