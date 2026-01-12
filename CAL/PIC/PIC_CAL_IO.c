// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B8839C2618FDDE2E5B47BDCC5F9C10ADC19A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF505D5F68F430DC0CDC61EFA5C92C3296FC17C367E34D36C26426735DFDBE2981E3B67BAC9BF8C9CCA2D5D373CC0F63AABB1557AF057991FBB78B2E607A88A2A937C9B26DF2071BB6F355D724FBAB9E6C36B0466FCA2387E26549D34A0D5AD11F3E77AC09D56E7F6F0610F6E7A1FBF8D4F17AED9B29318CA524A53779878588293DF04F96FE36F6B2B
// REVISION: 1.0
// GUID: 24CC1DFD-D326-4AF1-AB5B-BF3AE7D9D77D
// DATE: 08\08\2022
// DIR: CAL\PIC\PIC_CAL_IO.c
/*********************************************************************
 *                  Flowcode CAL IO File
 *
 * File: PIC_CAL_IO.c
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
 * 010911 | SK | Created
 * 050911 | BR | Added 10F and 12F compatible I/O functions
 *
 *
 */



#include "PIC_CAL_IO.h"

#ifdef MX_10F_TRIS

	MX_UINT8 tvar = 255;

	void FC_CAL_Port_Out_DDR_10F_x (MX_UINT8 OutMask, MX_UINT8 OutValue)
	{
		tvar = tvar & (~OutMask);
		asm("movf(_tvar),w");
		asm("TRIS 6");

		GPIO = (GPIO & ~OutMask) | (OutValue & OutMask);
	}

	inline MX_UINT8 FC_CAL_Port_In_DDR_10F_x (MX_UINT8 InMask, MX_UINT8 Shift)
	{
		tvar = tvar | InMask;
		asm("movf(_tvar),w");
		asm("TRIS 6");

		return (GPIO & InMask) >> Shift;
	}

#else


	#ifdef MX_16F5x_TRIS

		#ifdef MX_16F5x_TRISA

			MX_UINT8 tvarA = 255;

			void FC_CAL_Port_Out_DDR_16F_A (MX_UINT8 OutMask, MX_UINT8 OutValue)
			{
				tvarA = tvarA & (~OutMask);
				asm("movf(_tvarA),w");
				asm("TRIS 5");

				PORTA = (PORTA & ~OutMask) | (OutValue & OutMask);
			}

			inline MX_UINT8 FC_CAL_Port_In_DDR_16F_A (MX_UINT8 InMask, MX_UINT8 Shift)
			{
				tvarA = tvarA | InMask;
				asm("movf(_tvarA),w");
				asm("TRIS 5");

				return (PORTA & InMask) >> Shift;
			}

		#endif

		#ifdef MX_16F5x_TRISB

			MX_UINT8 tvarB = 255;

			void FC_CAL_Port_Out_DDR_16F_B (MX_UINT8 OutMask, MX_UINT8 OutValue)
			{
				tvarB = tvarB & (~OutMask);
				asm("movf(_tvarB),w");
				asm("TRIS 6");

				PORTB = (PORTB & ~OutMask) | (OutValue & OutMask);
			}

			inline MX_UINT8 FC_CAL_Port_In_DDR_16F_B (MX_UINT8 InMask, MX_UINT8 Shift)
			{
				tvarB = tvarB | InMask;
				asm("movf(_tvarB),w");
				asm("TRIS 6");

				return (PORTB & InMask) >> Shift;
			}

		#endif

		#ifdef MX_16F5x_TRISC

			MX_UINT8 tvarC = 255;

			void FC_CAL_Port_Out_DDR_16F_C (MX_UINT8 OutMask, MX_UINT8 OutValue)
			{
				tvarC = tvarC & (~OutMask);
				asm("movf(_tvarC),w");
				asm("TRIS 7");

				PORTC = (PORTC & ~OutMask) | (OutValue & OutMask);
			}

			inline MX_UINT8 FC_CAL_Port_In_DDR_16F_C (MX_UINT8 InMask, MX_UINT8 Shift)
			{
				tvarC = tvarC | InMask;
				asm("movf(_tvarC),w");
				asm("TRIS 7");

				return (PORTC & InMask) >> Shift;
			}

		#endif

		#ifdef MX_16F5x_TRISD

			MX_UINT8 tvarD = 255;

			void FC_CAL_Port_Out_DDR_16F_D (MX_UINT8 OutMask, MX_UINT8 OutValue)
			{
				tvarD = tvarD & (~OutMask);
				asm("movf(_tvarD),w");
				asm("TRIS 8");

				PORTD = (PORTD & ~OutMask) | (OutValue & OutMask);
			}

			inline MX_UINT8 FC_CAL_Port_In_DDR_16F_D (MX_UINT8 InMask, MX_UINT8 Shift)
			{
				tvarD = tvarD | InMask;
				asm("movf(_tvarD),w");
				asm("TRIS 8");

				return (PORTD & InMask) >> Shift;
			}

		#endif

		#ifdef MX_16F5x_TRISE

			MX_UINT8 tvarE = 255;

			void FC_CAL_Port_Out_DDR_16F_E (MX_UINT8 OutMask, MX_UINT8 OutValue)
			{
				tvarE = tvarE & (~OutMask);
				asm("movf(_tvarE),w");
				asm("TRIS 9");

				PORTE = (PORTE & ~OutMask) | (OutValue & OutMask);
			}

			inline MX_UINT8 FC_CAL_Port_In_DDR_16F_E (MX_UINT8 InMask, MX_UINT8 Shift)
			{
				tvarE = tvarE | InMask;
				asm("movf(_tvarE),w");
				asm("TRIS 9");

				return (PORTE & InMask) >> Shift;
			}

		#endif

	#else


		void FC_CAL_Port_Out__x (MX_UINT8* Port, MX_UINT8 OutMask, MX_UINT8 OutValue)
		{
			*Port = (*Port & ~OutMask) | (OutValue & OutMask);
		}


		void FC_CAL_Port_Out_DDR__x (MX_UINT8* Port, MX_UINT8* Tris, MX_UINT8 OutMask, MX_UINT8 OutValue)
		{
			*Tris = *Tris & (~OutMask);
			*Port = (*Port & ~OutMask) | (OutValue & OutMask);
		}


		MX_UINT8 FC_CAL_Port_In__x (MX_UINT8* Port, MX_UINT8 InMask, MX_UINT8 Shift)
		{
			return (*Port & InMask) >> Shift;
		}


		inline MX_UINT8 FC_CAL_Port_In_DDR__x (volatile MX_UINT8* Port,volatile MX_UINT8* Tris, MX_UINT8 InMask, MX_UINT8 Shift)
		{
			*Tris = *Tris | InMask;
			return (*Port & InMask) >> Shift;
		}

	#endif

#endif

