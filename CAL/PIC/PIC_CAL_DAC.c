// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B88F72C7C616BF79FDECDF1017F97793DBB6336C11BE63C7B23E6A7110B5081D39796EDD611F6757020C3CAEE8E7DA6987B39187013CB09250D0F715122E3CD98D08D042C415B05A371BC6107F750867C27298DF31C9CAB16C12B1C801D0A6AEEDAE523EE87F638E2BB8B69F050034F032641F1B792143F30D93D41651FFB186876F6E34CEACF9C8EA549D34A0D5AD11F33388ADE4F056868D49C1AB2DFF96030282AB07BA452EA7D607369D99911C23D5D43797C197BFDEC5
// REVISION: 6.0
// GUID: A62004FF-B5A6-4AB7-BA45-3ECFD9087821
// DATE: 11\07\2025
// DIR: CAL\PIC\PIC_CAL_DAC.c
/*********************************************************************
 *                  Flowcode CAL DAC File
 *
 * File: PIC_CAL_DAC.c
 *
 * (c) 2016 Matrix Multimedia Ltd.
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
 * 310516 | BR | Created
 */


#define MX_DAC_CHANNEL_X		CAL_APPEND(MX_DAC_CHANNEL_, MX_DAC_NUM)
#define MX_DAC_ALTPIN_X			CAL_APPEND(MX_DAC_ALTPIN_, MX_DAC_NUM)
#define MX_DAC_VREF_X			CAL_APPEND(MX_DAC_VREF_, MX_DAC_NUM)


CALFUNCTION(void, FC_CAL_DAC_Enable_, (void));
CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output));
CALFUNCTION(void, FC_CAL_DAC_Disable_, (void));


// DAC Type 1 Supported Devices ************************************************************
// 16F188xx / 16F194x
// Up to 4 channels
// *******************************************************************************************/

#ifdef MX_DAC_TYPE_1

	CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
	{
		#if (MX_DAC_CHANNEL_X == 1)

			#if (MX_DAC_ALTPIN_X == 1)
				DAC1CON0 = 0x10;		//Setup DAC OUT2 to be an output
			#else
				DAC1CON0 = 0x20;		//Setup DAC OUT1 to be an output
			#endif

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC1CON0 = DAC1CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC1CON0 = DAC1CON0 | 0x80;	//Enable DAC Module
		#endif

		#if (MX_DAC_CHANNEL_X == 2)

			#if (MX_DAC_ALTPIN_X == 1)
				DAC2CON0 = 0x10;		//Setup DAC OUT2 to be an output
			#else
				DAC2CON0 = 0x20;		//Setup DAC OUT1 to be an output
			#endif

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC2CON0 = DAC2CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC2CON0 = DAC2CON0 | 0x80;	//Enable DAC Module
		#endif

		#if (MX_DAC_CHANNEL_X == 3)

			#if (MX_DAC_ALTPIN_X == 1)
				DAC3CON0 = 0x10;		//Setup DAC OUT2 to be an output
			#else
				DAC3CON0 = 0x20;		//Setup DAC OUT1 to be an output
			#endif

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC3CON0 = DAC3CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC3CON0 = DAC3CON0 | 0x80;	//Enable DAC Module
		#endif

		#if (MX_DAC_CHANNEL_X == 4)

			#if (MX_DAC_ALTPIN_X == 1)
				DAC4CON0 = 0x10;		//Setup DAC OUT2 to be an output
			#else
				DAC4CON0 = 0x20;		//Setup DAC OUT1 to be an output
			#endif

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC4CON0 = DAC1CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC4CON0 = DAC4CON0 | 0x80;	//Enable DAC Module
		#endif

			#if (MX_DAC_CHANNEL_X == 5)

			#if (MX_DAC_ALTPIN_X == 1)
				DAC5CON0 = 0x10;		//Setup DAC OUT2 to be an output
			#else
				DAC5CON0 = 0x20;		//Setup DAC OUT1 to be an output
			#endif

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC5CON0 = DAC5CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC5CON0 = DAC5CON0 | 0x80;	//Enable DAC Module
		#endif

		#if (MX_DAC_CHANNEL_X == 6)

			#if (MX_DAC_ALTPIN_X == 1)
				DAC6CON0 = 0x10;		//Setup DAC OUT2 to be an output
			#else
				DAC6CON0 = 0x20;		//Setup DAC OUT1 to be an output
			#endif

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC6CON0 = DAC6CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC6CON0 = DAC6CON0 | 0x80;	//Enable DAC Module
		#endif

		#if (MX_DAC_CHANNEL_X == 7)

			#if (MX_DAC_ALTPIN_X == 1)
				DAC7CON0 = 0x10;		//Setup DAC OUT2 to be an output
			#else
				DAC7CON0 = 0x20;		//Setup DAC OUT1 to be an output
			#endif

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC7CON0 = DAC7CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC7CON0 = DAC7CON0 | 0x80;	//Enable DAC Module
		#endif

		#if (MX_DAC_CHANNEL_X == 8)

			#if (MX_DAC_ALTPIN_X == 1)
				DAC8CON0 = 0x10;		//Setup DAC OUT2 to be an output
			#else
				DAC8CON0 = 0x20;		//Setup DAC OUT1 to be an output
			#endif

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC8CON0 = DAC8CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC8CON0 = DAC8CON0 | 0x80;	//Enable DAC Module
		#endif
	}

	CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output))
	{
		#if (MX_DAC_CHANNEL_X == 1)
			DAC1CON1 = Output;
		#endif

		#if (MX_DAC_CHANNEL_X == 2)
			DAC2CON1 = Output;
		#endif

		#if (MX_DAC_CHANNEL_X == 3)
			DAC3CON1 = Output;
		#endif

		#if (MX_DAC_CHANNEL_X == 4)
			DAC4CON1 = Output;
		#endif

		#if (MX_DAC_CHANNEL_X == 5)
			DAC5CON1 = Output;
		#endif

		#if (MX_DAC_CHANNEL_X == 6)
			DAC6CON1 = Output;
		#endif

		#if (MX_DAC_CHANNEL_X == 7)
			DAC7CON1 = Output;
		#endif

		#if (MX_DAC_CHANNEL_X == 8)
			DAC8CON1 = Output;
		#endif
	}

	CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
	{
		#if (MX_DAC_CHANNEL_X == 1)
			DAC1CON0 = 0;
		#endif

		#if (MX_DAC_CHANNEL_X == 2)
			DAC2CON0 = 0;
		#endif

		#if (MX_DAC_CHANNEL_X == 3)
			DAC3CON0 = 0;
		#endif

		#if (MX_DAC_CHANNEL_X == 4)
			DAC4CON0 = 0;
		#endif

		#if (MX_DAC_CHANNEL_X == 5)
			DAC51CON0 = 0;
		#endif

		#if (MX_DAC_CHANNEL_X == 6)
			DAC6CON0 = 0;
		#endif

		#if (MX_DAC_CHANNEL_X == 7)
			DAC7CON0 = 0;
		#endif

		#if (MX_DAC_CHANNEL_X == 8)
			DAC8CON0 = 0;
		#endif

	}

#endif


// DAC Type 2 Supported Devices ************************************************************
// 18F2XK22 / 18F4XK22 / 18F2xK50 / 18F4xK50
// Up to 1 channel
// *******************************************************************************************/

#ifdef MX_DAC_TYPE_2

	CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
	{
		VREFCON1 = 0x60;			//Setup DAC to be an output and Positive Referenced

		#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
			VREFCON1 = VREFCON1 | (MX_DAC_VREF_X << 2);
		#endif

		VREFCON1 = VREFCON1 | 0x80;	//Enable DAC Module

	}


	CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output))
	{
		VREFCON2 = Output;
	}


	CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
	{
		VREFCON1 = 0;
	}

#endif


// DAC Type 3 Supported Devices ************************************************************
// 16F1455 / 16F1459 / 16F193x
// Up to 1 channel
// *******************************************************************************************/

#ifdef MX_DAC_TYPE_3

	CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
	{
		DACCON0 = 0x20;				//Setup DAC to be an output and Positive Referenced

		#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
			DACCON0 = DACCON0 | (MX_DAC_VREF_X << 2);
		#endif

		DACCON0 = DACCON0 | 0x80;	//Enable DAC Module

	}


	CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output))
	{
		DACCON1 = Output;
	}


	CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
	{
		DACCON0 = 0;
	}

#endif



// DAC Type 4 Supported Devices ************************************************************
// 16F1764
// Up to 8 channels
// *******************************************************************************************/

#ifdef MX_DAC_TYPE_4

	CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
	{
		#if (MX_DAC_CHANNEL_X == 1)
			DAC1CON0 = 0x20;			//Setup DAC to be an output

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC1CON0 = DAC1CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC1CON0 = DAC1CON0 | 0x80;	//Enable DAC Module
		#endif

		#if (MX_DAC_CHANNEL_X == 2)
			DAC2CON0 = 0x20;			//Setup DAC to be an output

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC2CON0 = DAC2CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC2CON0 = DAC2CON0 | 0x80;	//Enable DAC Module
		#endif

		#if (MX_DAC_CHANNEL_X == 3)
			DAC3CON0 = 0x20;			//Setup DAC to be an output

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC3CON0 = DAC3CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC3CON0 = DAC3CON0 | 0x80;	//Enable DAC Module
		#endif

		#if (MX_DAC_CHANNEL_X == 4)
			DAC4CON0 = 0x20;			//Setup DAC to be an output

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC4CON0 = DAC1CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC4CON0 = DAC4CON0 | 0x80;	//Enable DAC Module
		#endif
		
		#if (MX_DAC_CHANNEL_X == 5)
			DAC5CON0 = 0x20;			//Setup DAC to be an output

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC5CON0 = DAC5CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC5CON0 = DAC5CON0 | 0x80;	//Enable DAC Module
		#endif

		#if (MX_DAC_CHANNEL_X == 6)
			DAC6CON0 = 0x20;			//Setup DAC to be an output

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC6CON0 = DAC6CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC6CON0 = DAC6CON0 | 0x80;	//Enable DAC Module
		#endif

		#if (MX_DAC_CHANNEL_X == 7)
			DAC7CON0 = 0x20;			//Setup DAC to be an output

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC7CON0 = DAC7CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC7CON0 = DAC7CON0 | 0x80;	//Enable DAC Module
		#endif

		#if (MX_DAC_CHANNEL_X == 8)
			DAC8CON0 = 0x20;			//Setup DAC to be an output

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC8CON0 = DAC8CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC8CON0 = DAC8CON0 | 0x80;	//Enable DAC Module
		#endif

	}

	CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output))
	{
		#if (MX_DAC_CHANNEL_X == 1)
			DAC1REFH = Output >> 8;
			DAC1REFL = Output;
			DACLD = DACLD | 0x01;
		#endif

		#if (MX_DAC_CHANNEL_X == 2)
			DAC2REFH = Output >> 8;
			DAC2REFL = Output;
			DACLD = DACLD | 0x02;
		#endif

		#if (MX_DAC_CHANNEL_X == 3)
			DAC3REF = Output;
		#endif

		#if (MX_DAC_CHANNEL_X == 4)
			DAC4REF = Output;
		#endif

		#if (MX_DAC_CHANNEL_X == 5)
			DAC5REFH = Output >> 8;
			DAC5REFL = Output;
			DACLD = DACLD | 0x01;
		#endif

		#if (MX_DAC_CHANNEL_X == 6)
			DAC6REFH = Output >> 8;
			DAC6REFL = Output;
			DACLD = DACLD | 0x02;
		#endif

		#if (MX_DAC_CHANNEL_X == 7)
			DAC7REF = Output;
		#endif

		#if (MX_DAC_CHANNEL_X == 8)
			DAC8REF = Output;
		#endif
	}

	CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
	{
		#if (MX_DAC_CHANNEL_X == 1)
			DAC1CON0 = 0;
		#endif

		#if (MX_DAC_CHANNEL_X == 2)
			DAC2CON0 = 0;
		#endif

		#if (MX_DAC_CHANNEL_X == 3)
			DAC3CON0 = 0;
		#endif

		#if (MX_DAC_CHANNEL_X == 4)
			DAC4CON0 = 0;
		#endif

		#if (MX_DAC_CHANNEL_X == 5)
			DAC5CON0 = 0;
		#endif

		#if (MX_DAC_CHANNEL_X == 6)
			DAC6CON0 = 0;
		#endif

		#if (MX_DAC_CHANNEL_X == 7)
			DAC7CON0 = 0;
		#endif

		#if (MX_DAC_CHANNEL_X == 8)
			DAC8CON0 = 0;
		#endif


	}

#endif


// DAC Type 5 Supported Devices ************************************************************
// 16F753
// Up to 1 channels 9-bit data
// *******************************************************************************************/

#ifdef MX_DAC_TYPE_5

	CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
	{
		#if (MX_DAC_CHANNEL_X == 1)
			DAC1CON0 = 0x20;			//Setup DAC to be an output

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC1CON0 = DAC1CON0 | (MX_DAC_VREF_X << 2);
			#endif

			DAC1CON0 = DAC1CON0 | 0xC0;	//Enable DAC Module - Right justified Data
		#endif
	}

	CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output))
	{
		#if (MX_DAC_CHANNEL_X == 1)
			DAC1REFL = Output;
			DAC1REFH = Output >> 8;
		#endif
	}

	CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
	{
		#if (MX_DAC_CHANNEL_X == 1)
			DAC1CON0 = 0;
		#endif
	}

#endif


// DAC Type 6 Supported Devices ************************************************************
// 18FxxQ41
// Up to 2 channels
// *******************************************************************************************/

#ifdef MX_DAC_TYPE_6

	CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
	{
		#if (MX_DAC_CHANNEL_X == 1)

			#if (MX_DAC_ALTPIN_X == 1)
				DAC1CON = 0x20;		//Setup DAC OUT2 to be an output
			#else
				DAC1CON = 0x10;		//Setup DAC OUT1 to be an output
			#endif

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC1CON = DAC1CON | (MX_DAC_VREF_X << 2);
			#endif

			DAC1CON = DAC1CON | 0x80;	//Enable DAC Module
		#endif

		#if (MX_DAC_CHANNEL_X == 2)

			#if (MX_DAC_ALTPIN_X == 1)
				DAC2CON = 0x20;		//Setup DAC OUT2 to be an output
			#else
				DAC2CON = 0x10;		//Setup DAC OUT1 to be an output
			#endif

			#if (MX_DAC_VREF_X > 0)		//Setup +Ve Vref
				DAC2CON = DAC2CON | (MX_DAC_VREF_X << 2);
			#endif

			DAC2CON = DAC2CON | 0x80;	//Enable DAC Module
		#endif

	}

	CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Output))
	{
		#if (MX_DAC_CHANNEL_X == 1)
			DAC1DATL = Output;
		#endif

		#if (MX_DAC_CHANNEL_X == 2)
			DAC2DATL = Output;
		#endif

	}

	CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
	{
		#if (MX_DAC_CHANNEL_X == 1)
			DAC1CON = 0;
		#endif

		#if (MX_DAC_CHANNEL_X == 2)
			DAC2CON = 0;
		#endif

	}

#endif

