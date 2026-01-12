// CRC: 5D982BB222882C54AB4AFF20A1590FC484D3178BD0D2510D0F5A64A7853221CAE2C33FABBE4F69A6659399D51781B7B9D736E221269B259DD111497F7C88964FE2386DF130D1CE2BC55ADF1BBD570577531B52BE29A49B59711B8143522C2B6905B031E6C3EBB6C0368540C0D9E74574A73483F3A82CC667C395C974D28C176774FE5B572986B094CD6EE320958B108787A6A0578B07D1299A43ADB7DD4EF2693512A9138B1DFBAB8D6D7A68956EB60E6FAD7B94FA35E1A3549D34A0D5AD11F3C4338C809700DE79DE927D6954D1463366D03CA5ADA79D65674573756A3EC60527D03AB401F1B0EB
// REVISION: 2.0
// GUID: FF41D6A2-F549-47B0-951D-3B6479161E1C
// DATE: 20\04\2023
// DIR: CAL\PIC16BIT\PIC16BIT_CAL_ADC.c
/*********************************************************************
 *                  Flowcode CAL ADC File
 *
 * File: PIC16BIT_CAL_ADC.c
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
 * 060911 | BR | Created
 * 200911 | BR | Updated to include all ADC type files
 * 020312 | BR | Updated to v5.1 CAL Schema
 * 170812 | BR | Fixed a bug with the RAW ADC functions where the SAMP bit was being left clear
 * 170812 | BR | Added some minor mods to allow the FCD to correctly determine ADC conv speed
 * 180912 | BR | Added an extra ADC type for 24FxxKA devices
 * 191112 | BR | Added ADC type 10 for newer EP devices
 * 171212 | BR | Moved the code to begin the sample to allow for more optimised ADC readings
 * 030713 | LM | Standard API calls
 * 240414 | LM | Additions to support Touch via ADC
 * 180914 | LM | ADC based Touch implemented on a couple of types
 * 170420 | BR | Cleaned up the code a bit, removed tris storing function, added better ansel reg support, removed delay
 * 170420 | BR | Added DMA and Scanning support
 */



//ADC Function Prototypes
CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge));
CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode));
CALFUNCTION(void, FC_CAL_ADC_Disable_, ());

#ifdef MX_ADC_SCAN
  CALFUNCTION(void, FC_CAL_ADC_ScanEnable_, (MX_UINT8 Channel, MX_UINT8 Enable));
#endif

#ifdef MX_ADC_TOUCH
  CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel));
#endif


//ADC Global Variables
//MX_UINT16 old_tris;
MX_UINT8 tris_bit, ans_bit;
volatile char* tris_reg;
volatile char* ans_reg;


/* ADC Type 1 Supported Devices ************************************************************
PIC24FJ128GA Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_1
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_reg = (MX_UINT8 *) &TRISB;
		tris_bit = Channel;
		ans_reg = (MX_UINT8 *) &AD1PCFG;

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);

		ans_reg[0] &= ~(1<<tris_bit);								//set ANSEL bit
		ans_reg[1] &= (~(1<<tris_bit) >> 8);

		AD1CHS = (Channel & 0x0F);

		if (Vref == 0)											//Setup Vref+ functionality
			AD1CON2bits.VCFG0 = 0;
		else
			AD1CON2bits.VCFG0 = 1;

		AD1CON3 = 0;
		if (Conv_Speed & 0x40)									//Assign conversion speed
			AD1CON3bits.ADRC = 1;								//Internal RC Clock
		else
			AD1CON3 = (Conv_Speed & 0x3F);						//Based on system clock

		AD1CON1bits.ADON = 1;									//Turn on ADC
		AD1CON1bits.SAMP = 1;

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		AD1CON1bits.SAMP = 0;									//begin next conversion

		while (!AD1CON1bits.DONE);

		if (Sample_Mode)
		{
			iRetVal = ADC1BUF0;									//10-bit ADC
		}
		else
			iRetVal = (ADC1BUF0 >> 2);							//8-bit ADC

		AD1CON1bits.SAMP = 1;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		AD1CON1bits.ADON = 0;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ans_reg[0] |= (1<<tris_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<tris_bit) >> 8);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 2 Supported Devices ************************************************************
PIC33FJ128GP Family
PIC33FJ64GP Family
PIC33FJ32GP Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_2
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_reg = (MX_UINT8 *) &TRISA;
		tris_bit = Channel;
		ans_reg = (MX_UINT8 *) &AD1PCFGL;

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);
		ans_reg[0] &= ~(1<<tris_bit);								//set ANSEL bit
		ans_reg[1] &= (~(1<<tris_bit) >> 8);

		clear_bit(AD1PCFGL, Channel);							//Setup ADC Channel
		AD1CHS0 = (Channel & 0x0F);

		if (Vref == 0)											//Setup Vref+ functionality
			AD1CON2bits.VCFG0 = 0;
		else
			AD1CON2bits.VCFG0 = 1;

		AD1CON3 = 0;
		if (Conv_Speed & 0x40)									//Assign conversion speed
			AD1CON3bits.ADRC = 1;								//Internal RC Clock
		else
			AD1CON3 = (Conv_Speed & 0x3F);						//Based on system clock

		AD1CON1bits.ADON = 1;									//Turn on ADC
		AD1CON1bits.AD12B = 1;
		AD1CON1bits.SAMP = 1;

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		AD1CON1bits.SAMP = 0;									//begin next conversion

		while (!AD1CON1bits.DONE);

		if (Sample_Mode)
		{
			iRetVal = ADC1BUF0;									//12-bit ADC
		}
		else
			iRetVal = (ADC1BUF0 >> 4);							//8-bit ADC

		AD1CON1bits.SAMP = 1;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		AD1CON1bits.ADON = 0;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ans_reg[0] |= (1<<tris_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<tris_bit) >> 8);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 3 Supported Devices ************************************************************
dsPIC30 Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_3
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_reg = (MX_UINT8 *) &TRISB;
		tris_bit = Channel;
		ans_reg = (MX_UINT8 *) &ADPCFG;

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);
		ans_reg[0] &= ~(1<<tris_bit);								//set ANSEL bit
		ans_reg[1] &= (~(1<<tris_bit) >> 8);

		ADCON1 = 0x0000;
		ADCON2 = 0x0000;
		ADCON3 = 0x0000;

		ADCHS = (Channel & 0x000F);

		if (Vref == 0)											//Setup Vref+ functionality
			ADCON2 = ADCON2 & 0x1FFF;
		else
			ADCON2 = ADCON2 | 0x2000;

		ADCON3 = 0;
		if (Conv_Speed & 0x40)									//Assign conversion speed
			ADCON3bits.ADRC = 1;								//Internal RC Clock
		else
			ADCON3 = (Conv_Speed & 0x3F);						//Based on system clock

		//ADCON3 |= 0x0100;										//Dont think this is needed 17/08/12 BR

		ADCON1bits.ADON = 1;									//Turn on ADC
		ADCON1bits.SAMP = 1;

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON1bits.SAMP = 0;									//begin next conversion

		while (!ADCON1bits.DONE);

		if (Sample_Mode)
		{
			iRetVal = ADCBUF0;									//10-bit ADC
		}
		else
			iRetVal = (ADCBUF0 >> 2);							//8-bit ADC

		ADCON1bits.SAMP = 1;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON1bits.ADON = 0;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ans_reg[0] |= (1<<tris_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<tris_bit) >> 8);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 4 Supported Devices ************************************************************
dsPIC33FJx6GSx0x Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_4

	MX_UINT8 MX_Current_Channel;

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		if (Channel <= 2)
		{
			tris_reg = (MX_UINT8 *) &TRISA;
			tris_bit = Channel;
		}
		else
		{
			tris_reg = (MX_UINT8 *) &TRISB;
			tris_bit = (Channel-2);
		}

		ans_reg = (MX_UINT8 *) &ADPCFG;
		ans_bit = Channel;

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);
		ans_reg[0] &= ~(1<<ans_bit);								//set ANSEL bit
		ans_reg[1] &= (~(1<<ans_bit) >> 8);

		ADCON = (Conv_Speed & 0x07);							//Assign conversion speed
		ADCONbits.ADON = 1;										//Turn on ADC
		delay_us(T_Charge);										//wait the acquisition time

		MX_Current_Channel = Channel;
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

	  #if (defined MX_ADC_CHANNEL_0 || defined MX_ADC_CHANNEL_1)
		if(MX_Current_Channel <= 1)								//begin next conversion
		{
			ADCPC0 = 0x0001;
			ADCPC0bits.SWTRG0 = 1;
			while (!ADCPC0bits.SWTRG0);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_2 || defined MX_ADC_CHANNEL_3)
		if(MX_Current_Channel >= 2 && MX_Current_Channel <= 3)
		{
			ADCPC0 = 0x0100;
			ADCPC0bits.SWTRG1 = 1;
			while (!ADCPC0bits.SWTRG1);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_4 || defined MX_ADC_CHANNEL_5)
		if(MX_Current_Channel >= 4 && MX_Current_Channel <= 5)
		{
			ADCPC1 = 0x0001;
			ADCPC1bits.SWTRG2 = 1;
			while (!ADCPC1bits.SWTRG2);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_6 || defined MX_ADC_CHANNEL_7)
		if(MX_Current_Channel >= 6 && MX_Current_Channel <= 7)
		{
			ADCPC1 = 0x0100;
			ADCPC1bits.SWTRG3 = 1;
			while (!ADCPC1bits.SWTRG3);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_8 || defined MX_ADC_CHANNEL_9)
		if(MX_Current_Channel >= 8 && MX_Current_Channel <= 9)
		{
			ADCPC2 = 0x0001;
			ADCPC2bits.SWTRG4 = 1;
			while (!ADCPC2bits.SWTRG4);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_10 || defined MX_ADC_CHANNEL_11)
		if(MX_Current_Channel >= 10 && MX_Current_Channel <= 11)
		{
			ADCPC2 = 0x0100;
			ADCPC2bits.SWTRG5 = 1;
			while (!ADCPC2bits.SWTRG5);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_12 || defined MX_ADC_CHANNEL_13)
		if(MX_Current_Channel >= 12 && MX_Current_Channel <= 13)
		{
			ADCPC3 = 0x0001;
			ADCPC3bits.SWTRG6 = 1;
			while (!ADCPC3bits.SWTRG6);
		}
	  #endif

		if (Sample_Mode)
		{
			iRetVal = ADCBUF0;									//10-bit ADC
		}
		else
			iRetVal = (ADCBUF0 >> 2);							//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCONbits.ADON = 0;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ans_reg[0] |= (1<<ans_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<ans_bit) >> 8);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 5 Supported Devices ************************************************************
dsPIC33FJx6GSx0x Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_5

	MX_UINT8 MX_Current_Channel;

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{

		if(Channel < 16)
		{
			tris_reg = (MX_UINT8 *) &TRISB;
			tris_bit = Channel;
			ans_reg = (MX_UINT8 *) &ADPCFG;
			ans_bit = Channel;
		}
	  #ifdef MX_ADC_CHANNEL_16
		if(Channel == 16)
		{
			tris_reg = (MX_UINT8 *) &TRISC;
			tris_bit = 1;
			ans_reg = (MX_UINT8 *) &ADPCFG2;
			ans_bit = Channel - 16;
		}
	  #endif
	  #ifdef MX_ADC_CHANNEL_17
		if(Channel == 17)
		{
			tris_reg = (MX_UINT8 *) &TRISC;
			tris_bit = 2;
			ans_reg = (MX_UINT8 *) &ADPCFG2;
			ans_bit = Channel - 16;
		}
	  #endif
	  #ifdef MX_ADC_CHANNEL_18
		if(Channel == 18)
		{
			tris_reg = (MX_UINT8 *) &TRISC;
			tris_bit = 3;
			ans_reg = (MX_UINT8 *) &ADPCFG2;
			ans_bit = Channel - 16;
		}
	  #endif
	  #ifdef MX_ADC_CHANNEL_19
		if(Channel == 19)
		{
			tris_reg = (MX_UINT8 *) &TRISC;
			tris_bit = 4;
			ans_reg = (MX_UINT8 *) &ADPCFG2;
			ans_bit = Channel - 16;
		}
	  #endif
	  #ifdef MX_ADC_CHANNEL_20
		if(Channel == 20)
		{
			tris_reg = (MX_UINT8 *) &TRISE;
			tris_bit = 8;
			ans_reg = (MX_UINT8 *) &ADPCFG2;
			ans_bit = Channel - 16;
		}
	  #endif
	  #ifdef MX_ADC_CHANNEL_21
		if(Channel == 21)
		{
			tris_reg = (MX_UINT8 *) &TRISE;
			tris_bit = 9;
			ans_reg = (MX_UINT8 *) &ADPCFG2;
			ans_bit = Channel - 16;
		}
	  #endif
	  #ifdef MX_ADC_CHANNEL_22
		if(Channel == 22)
		{
			tris_reg = (MX_UINT8 *) &TRISA;
			tris_bit = 6;
			ans_reg = (MX_UINT8 *) &ADPCFG2;
			ans_bit = Channel - 16;
		}
	  #endif
	  #ifdef MX_ADC_CHANNEL_23
		if(Channel == 23)
		{
			tris_reg = (MX_UINT8 *) &TRISA;
			tris_bit = 7;
			ans_reg = (MX_UINT8 *) &ADPCFG2;
			ans_bit = Channel - 16;
		}
	  #endif

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);
		ans_reg[0] &= ~(1<<ans_bit);								//set ANSEL bit
		ans_reg[1] &= (~(1<<ans_bit) >> 8);

		ADCON = 0x0000;
		ADCON = (Conv_Speed & 0x07);							//Assign conversion speed
		ADCONbits.ADON = 1;										//Turn on ADC
		delay_us(T_Charge);										//wait the acquisition time

		MX_Current_Channel = Channel;
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

	  #if (defined MX_ADC_CHANNEL_0 || defined MX_ADC_CHANNEL_1)
		if(MX_Current_Channel <= 1)								//begin next conversion
		{
			ADCPC0 = 0x0001;
			ADCPC0bits.SWTRG0 = 1;
			while (!ADCPC0bits.SWTRG0);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_2 || defined MX_ADC_CHANNEL_3)
		if(MX_Current_Channel >= 2 && MX_Current_Channel <= 3)
		{
			ADCPC0 = 0x0100;
			ADCPC0bits.SWTRG1 = 1;
			while (!ADCPC0bits.SWTRG1);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_4 || defined MX_ADC_CHANNEL_5)
		if(MX_Current_Channel >= 4 && MX_Current_Channel <= 5)
		{
			ADCPC1 = 0x0001;
			ADCPC1bits.SWTRG2 = 1;
			while (!ADCPC1bits.SWTRG2);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_6 || defined MX_ADC_CHANNEL_7)
		if(MX_Current_Channel >= 6 && MX_Current_Channel <= 7)
		{
			ADCPC1 = 0x0100;
			ADCPC1bits.SWTRG3 = 1;
			while (!ADCPC1bits.SWTRG3);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_8 || defined MX_ADC_CHANNEL_9)
		if(MX_Current_Channel >= 8 && MX_Current_Channel <= 9)
		{
			ADCPC2 = 0x0001;
			ADCPC2bits.SWTRG4 = 1;
			while (!ADCPC2bits.SWTRG4);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_10 || defined MX_ADC_CHANNEL_11)
		if(MX_Current_Channel >= 10 && MX_Current_Channel <= 11)
		{
			ADCPC2 = 0x0100;
			ADCPC2bits.SWTRG5 = 1;
			while (!ADCPC2bits.SWTRG5);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_12 || defined MX_ADC_CHANNEL_13)
		if(MX_Current_Channel >= 12 && MX_Current_Channel <= 13)
		{
			ADCPC3 = 0x0001;
			ADCPC3bits.SWTRG6 = 1;
			while (!ADCPC3bits.SWTRG6);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_14 || defined MX_ADC_CHANNEL_15)
		if(MX_Current_Channel >= 14 && MX_Current_Channel <= 15)
		{
			ADCPC3 = 0x0100;
			ADCPC3bits.SWTRG7 = 1;
			while (!ADCPC3bits.SWTRG7);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_16 || defined MX_ADC_CHANNEL_17)
		if(MX_Current_Channel >= 16 && MX_Current_Channel <= 17)
		{
			ADCPC4 = 0x0001;
			ADCPC4bits.SWTRG8 = 1;
			while (!ADCPC4bits.SWTRG8);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_18 || defined MX_ADC_CHANNEL_19)
		if(MX_Current_Channel >= 18 && MX_Current_Channel <= 19)
		{
			ADCPC4 = 0x0100;
			ADCPC4bits.SWTRG9 = 1;
			while (!ADCPC4bits.SWTRG9);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_20 || defined MX_ADC_CHANNEL_21)
		if(MX_Current_Channel >= 20 && MX_Current_Channel <= 21)
		{
			ADCPC5 = 0x0001;
			ADCPC5bits.SWTRG10 = 1;
			while (!ADCPC5bits.SWTRG10);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_22 || defined MX_ADC_CHANNEL_23)
		if(MX_Current_Channel >= 22 && MX_Current_Channel <= 23)
		{
			ADCPC5 = 0x0100;
			ADCPC5bits.SWTRG11 = 1;
			while (!ADCPC5bits.SWTRG11);
		}
	  #endif
	  #if (defined MX_ADC_CHANNEL_24 || defined MX_ADC_CHANNEL_25)
		if(MX_Current_Channel >= 24 && MX_Current_Channel <= 25)
		{
			ADCPC6 = 0x0001;
			ADCPC6bits.SWTRG12 = 1;
			while (!ADCPC6bits.SWTRG12);
		}
	  #endif

		if (Sample_Mode)
		{
			iRetVal = ADCBUF0;									//10-bit ADC
		}
		else
			iRetVal = (ADCBUF0 >> 2);							//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCONbits.ADON = 0;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ans_reg[0] |= (1<<ans_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<ans_bit) >> 8);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 6 Supported Devices ************************************************************
dsPIC30 Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_6
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_reg = (MX_UINT8 *) &TRISB;
		tris_bit = Channel;
		ans_reg = (MX_UINT8 *) &ADPCFG;

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);
		ans_reg[0] &= ~(1<<tris_bit);								//set ANSEL bit
		ans_reg[1] &= (~(1<<tris_bit) >> 8);

		ADCON1 = 0x0000;
		ADCON2 = 0x0000;
		ADCON3 = 0x0000;

		ADCHS = (Channel & 0x000F);

		if (Vref == 0)											//Setup Vref+ functionality
			ADCON2 = ADCON2 & 0x1FFF;
		else
			ADCON2 = ADCON2 | 0x2000;

		if (Conv_Speed & 0x40)									//Assign conversion speed
			ADCON3bits.ADRC = 1;								//Internal RC Clock
		else
			ADCON3 = (Conv_Speed & 0x3F);						//Based on system clock

		//ADCON3 |= 0x0100;										//Dont think this is needed 17/08/12 BR

		ADCON1bits.ADON = 1;									//Turn on ADC
		ADCON1bits.SAMP = 1;

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON1bits.SAMP = 0;									//begin next conversion

		while (!ADCON1bits.DONE);

		if (Sample_Mode)
		{
			iRetVal = ADCBUF0;									//12-bit ADC
		}
		else
			iRetVal = (ADCBUF0 >> 4);							//8-bit ADC

		ADCON1bits.SAMP = 1;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON1bits.ADON = 0;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ans_reg[0] |= (1<<tris_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<tris_bit) >> 8);
	}

	#ifdef MX_ADC_TOUCH

	#define ADC_TOUCH_CONV_SPEED_VAL	0x0101
	#define ADC_TOUCH_LOOP_VAL			8
	#define ADC_TOUCH_PORT				LATB
	#define ADC_TOUCH_DDR				TRISB

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		MX_UINT16 ADC_Value = 0;
		MX_UINT8 loop = ADC_TOUCH_LOOP_VAL;
		MX_UINT16 dummy;

		// Initial setup
		ADCON2 = 0x0000;
		ADCON3 = ADC_TOUCH_CONV_SPEED_VAL;
		ADCON1 = 0x8000;		// ADON = 1 = A/D converter module is operating
		ADCHS = (Channel & 0x000F);

		while (loop--)
		{
			// output Vdd to pin, mux to read Vss
			ADPCFG  |= (1 << Channel);				// pin as digital
			ADC_TOUCH_PORT |= (1 << Channel);		// output high to pin
			ADC_TOUCH_DDR  &= ~(1 << Channel);		// pin as an output
			ADC_TOUCH_DDR  |= (1 << Channel);		// pin as an input
			// dummy read of the Vss sample
			ADCON1bits.SAMP = 1;					// take a sample
			delay_us(100);
			ADCON1bits.SAMP = 0;					// begin conversion
			while (!ADCON1bits.DONE);
			dummy = ADCBUF0;
			// change the mux and sample the pin
			ADPCFG  &= ~(1 << Channel);				// pin as an analogue input
			ADCON1bits.SAMP = 1;					// take a sample
			delay_us(100);
			ADCON1bits.SAMP = 0;					// begin conversion
			while (!ADCON1bits.DONE);
			ADC_Value += ADCBUF0;
		}

		// Shutdown
		ADCON1 = 0x0000;
		ADPCFG  |= (1 << Channel);					// pin as digital
		return ADC_Value / ADC_TOUCH_LOOP_VAL;
	}

	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 7 Supported Devices ************************************************************
dsPIC33/PIC24EPxxGP/MCx0x Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_7

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		#ifdef MX_ADC_CHANNEL_0
			if (Channel == 0)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_1
			if (Channel == 1)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_2
			if (Channel == 2)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_3
			if (Channel == 3)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_4
			if (Channel == 4)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_5
			if (Channel == 5)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_6
			if (Channel == 6)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_7
			if (Channel == 7)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_8
			if (Channel == 8)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_9
			if (Channel == 9)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 11;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_10
			if (Channel == 10)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 12;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_11
			if (Channel == 11)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 11;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_12
			if (Channel == 12)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 12;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_13
			if (Channel == 13)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 13;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_14
			if (Channel == 14)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 14;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_15
			if (Channel == 15)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 15;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_16
			if (Channel == 16)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSELG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_17
			if (Channel == 17)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 8;
				ans_reg = (MX_UINT8 *) &ANSELG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_18
			if (Channel == 18)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSELG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_19
			if (Channel == 19)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSELG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_20
			if (Channel == 20)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_21
			if (Channel == 21)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 8;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_22
			if (Channel == 22)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 10;
				ans_reg = (MX_UINT8 *) &ANSELG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_23
			if (Channel == 23)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 15;
				ans_reg = (MX_UINT8 *) &ANSELG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_24
			if (Channel == 24)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_25
			if (Channel == 25)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_26
			if (Channel == 26)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 8;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_27
			if (Channel == 27)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_28
			if (Channel == 28)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_29
			if (Channel == 29)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_30
			if (Channel == 30)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_31
			if (Channel == 31)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 5;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_32
			if (Channel == 32)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_33
			if (Channel == 33)
			{
				tris_reg = (MX_UINT8 *) &TRISF;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSELF;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_34
			if (Channel == 34)
			{
				tris_reg = (MX_UINT8 *) &TRISF;
				tris_bit = 10;
				ans_reg = (MX_UINT8 *) &ANSELF;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_35
			if (Channel == 35)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 11;
				ans_reg = (MX_UINT8 *) &ANSELG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_36
			if (Channel == 36)
			{
				tris_reg = (MX_UINT8 *) &TRISF;
				tris_bit = 13;
				ans_reg = (MX_UINT8 *) &ANSELF;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_37
			if (Channel == 37)
			{
				tris_reg = (MX_UINT8 *) &TRISF;
				tris_bit = 12;
				ans_reg = (MX_UINT8 *) &ANSELF;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_38
			if (Channel == 38)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 14;
				ans_reg = (MX_UINT8 *) &ANSELD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_39
			if (Channel == 39)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 15;
				ans_reg = (MX_UINT8 *) &ANSELD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_40
			if (Channel == 40)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_41
			if (Channel == 16)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_42
			if (Channel == 42)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSELG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_43
			if (Channel == 43)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSELG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_44
			if (Channel == 44)
			{
				tris_reg = (MX_UINT8 *) &TRISF;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSELF;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_45
			if (Channel == 45)
			{
				tris_reg = (MX_UINT8 *) &TRISF;
				tris_bit = 5;
				ans_reg = (MX_UINT8 *) &ANSELF;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_46
			if (Channel == 46)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 14;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_47
			if (Channel == 47)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 15;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_48
			if (Channel == 48)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 10;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_49
			if (Channel == 49)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 12;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);
		ans_reg[0] |= (1<<tris_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<tris_bit) >> 8);

		AD1CHS0 = (Channel & 0x1F);

		AD1CON2bits.VCFG1 = 0;
		AD1CON2bits.VCFG2 = 0;

		if (Vref == 0)											//Setup Vref+ functionality
			AD1CON2bits.VCFG0 = 0;
		else
			AD1CON2bits.VCFG0 = 1;

		if (Conv_Speed == 64)									//Assign conversion speed
		{
			AD1CON3bits.ADRC = 1;
		}
		else
		{
			AD1CON3bits.ADRC = 0;
			AD1CON3 = (Conv_Speed & 0xFF);
		}

		AD1CON1bits.AD12B = 1;									//12bit sampling
		AD1CON1bits.ADON = 1;									//Turn on ADC
		AD1CON1bits.SAMP = 1;

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		AD1CON1bits.SAMP = 0;									//begin next conversion

		while (!AD1CON1bits.DONE);

		if (Sample_Mode)
		{
			iRetVal = ADC1BUF0;									//12-bit ADC
		}
		else
			iRetVal = (ADC1BUF0 >> 4);							//8-bit ADC

		AD1CON1bits.SAMP = 1;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		AD1CON1bits.ADON = 0;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ans_reg[0] &= ~(1<<tris_bit);								//set ANSEL bit
		ans_reg[1] &= (~(1<<tris_bit) >> 8);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 8 Supported Devices ************************************************************
PIC33FJxxxMCx06A / x08A / x10A Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_8
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		if (Channel < 16)
		{
			tris_reg = (MX_UINT8 *) &TRISB;
			tris_bit = Channel;
			ans_reg = (MX_UINT8 *) &AD1PCFGL;
			ans_bit = Channel;
		}

	  #ifdef MX_ADC_CHANNEL_16
		if (Channel == 16)
		{
			tris_reg = (MX_UINT8 *) &TRISC;
			tris_bit = 1;
			ans_reg = (MX_UINT8 *) &AD1PCFGH;
			ans_bit = 0;
		}
	  #endif
	  #ifdef MX_ADC_CHANNEL_17
		if (Channel == 17)
		{
			tris_reg = (MX_UINT8 *) &TRISC;
			tris_bit = 2;
			ans_reg = (MX_UINT8 *) &AD1PCFGH;
			ans_bit = 1;
		}
	  #endif
	  #ifdef MX_ADC_CHANNEL_18
		if (Channel == 18)
		{
			tris_reg = (MX_UINT8 *) &TRISC;
			tris_bit = 3;
			ans_reg = (MX_UINT8 *) &AD1PCFGH;
			ans_bit = 2;
		}
	  #endif
	  #ifdef MX_ADC_CHANNEL_19
		if (Channel == 19)
		{
			tris_reg = (MX_UINT8 *) &TRISC;
			tris_bit = 4;
			ans_reg = (MX_UINT8 *) &AD1PCFGH;
			ans_bit = 3;
		}
	  #endif
	  #ifdef MX_ADC_CHANNEL_20
		if (Channel == 20)
		{
			tris_reg = (MX_UINT8 *) &TRISE;
			tris_bit = 8;
			ans_reg = (MX_UINT8 *) &AD1PCFGH;
			ans_bit = 4;
		}
	  #endif
	  #ifdef MX_ADC_CHANNEL_21
		if (Channel == 21)
		{
			tris_reg = (MX_UINT8 *) &TRISE;
			tris_bit = 9;
			ans_reg = (MX_UINT8 *) &AD1PCFGH;
			ans_bit = 5;
		}
	  #endif
	  #ifdef MX_ADC_CHANNEL_22
		if (Channel == 22)
		{
			tris_reg = (MX_UINT8 *) &TRISA;
			tris_bit = 6;
			ans_reg = (MX_UINT8 *) &AD1PCFGH;
			ans_bit = 6;
		}
	  #endif
	  #ifdef MX_ADC_CHANNEL_23
		if (Channel == 23)
		{
			tris_reg = (MX_UINT8 *) &TRISA;
			tris_bit = 7;
			ans_reg = (MX_UINT8 *) &AD1PCFGH;
			ans_bit = 7;
		}
	  #endif

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);
		ans_reg[0] &= ~(1<<ans_bit);								//set ANSEL bit
		ans_reg[1] &= (~(1<<ans_bit) >> 8);

		AD1CHS0 = (Channel & 0x1F);

		if (Vref == 0)											//Setup Vref+ functionality
			AD1CON2bits.VCFG0 = 0;
		else
			AD1CON2bits.VCFG0 = 1;

		AD1CON3 = 0;
		if (Conv_Speed & 0x40)									//Assign conversion speed
			AD1CON3bits.ADRC = 1;								//Internal RC Clock
		else
			AD1CON3 = (Conv_Speed & 0x3F);						//Based on system clock

		AD1CON1bits.ADON = 1;									//Turn on ADC
		AD1CON1bits.AD12B = 1;
		AD1CON1bits.SAMP = 1;

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		AD1CON1bits.SAMP = 0;									//begin next conversion

		while (!AD1CON1bits.DONE);

		if (Sample_Mode)
		{
			iRetVal = ADC1BUF0;									//12-bit ADC
		}
		else
			iRetVal = (ADC1BUF0 >> 4);							//8-bit ADC

		AD1CON1bits.SAMP = 1;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		AD1CON1bits.ADON = 0;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ans_reg[0] |= (1<<ans_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<ans_bit) >> 8);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif



/* ADC Type 9 Supported Devices ************************************************************
PIC24FxxKAxxx Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_9
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		#ifdef MX_ADC_CHANNEL_0
			if (Channel == 0)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_1
			if (Channel == 1)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_2
			if (Channel == 2)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_3
			if (Channel == 3)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_4
			if (Channel == 4)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_5
			if (Channel == 5)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_6
			if (Channel == 6)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_7
			if (Channel == 7)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_8
			if (Channel == 8)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_9
			if (Channel == 9)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 15;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_10
			if (Channel == 10)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 14;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_11
			if (Channel == 11)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 13;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_12
			if (Channel == 12)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 12;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_13
			if (Channel == 13)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_14
			if (Channel == 14)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_15
			if (Channel == 15)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);
		ans_reg[0] |= (1<<tris_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<tris_bit) >> 8);

		AD1CHS = (Channel & 0x0F);

		if (Vref == 0)											//Setup Vref+ functionality
			AD1CON2bits.VCFG0 = 0;
		else
			AD1CON2bits.VCFG0 = 1;

		AD1CON3 = 0;
		if (Conv_Speed & 0x40)									//Assign conversion speed
			AD1CON3bits.ADRC = 1;								//Internal RC Clock
		else
			AD1CON3 = (Conv_Speed & 0x3F);						//Based on system clock

		AD1CON1bits.ADON = 1;									//Turn on ADC
		AD1CON1bits.SAMP = 1;

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		AD1CON1bits.SAMP = 0;									//begin next conversion

		while (!AD1CON1bits.DONE);

		if (Sample_Mode)
		{
			iRetVal = ADC1BUF0;									//12-bit ADC
		}
		else
			iRetVal = (ADC1BUF0 >> 2);							//8-bit ADC

		AD1CON1bits.SAMP = 1;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		AD1CON1bits.ADON = 0;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ans_reg[0] &= ~(1<<tris_bit);								//set ANSEL bit
		ans_reg[1] &= (~(1<<tris_bit) >> 8);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif



/* ADC Type 10 Supported Devices ************************************************************
dsPIC33/PIC24EPxxGU Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_10

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		#ifdef MX_ADC_CHANNEL_0
			if (Channel == 0)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_1
			if (Channel == 1)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_2
			if (Channel == 2)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_3
			if (Channel == 3)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_4
			if (Channel == 4)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_5
			if (Channel == 5)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 5;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_6
			if (Channel == 6)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_7
			if (Channel == 7)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_8
			if (Channel == 8)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 8;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_9
			if (Channel == 9)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_10
			if (Channel == 10)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 10;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_11
			if (Channel == 11)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 11;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_12
			if (Channel == 12)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 12;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_13
			if (Channel == 13)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 13;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_14
			if (Channel == 14)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 14;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_15
			if (Channel == 15)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 15;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_16
			if (Channel == 16)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_17
			if (Channel == 17)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_18
			if (Channel == 18)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_19
			if (Channel == 19)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_20
			if (Channel == 20)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 8;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_21
			if (Channel == 21)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_22
			if (Channel == 22)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_23
			if (Channel == 23)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_24
			if (Channel == 24)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_25
			if (Channel == 25)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_26
			if (Channel == 26)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_27
			if (Channel == 27)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_28
			if (Channel == 28)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_29
			if (Channel == 29)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 5;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_30
			if (Channel == 30)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_31
			if (Channel == 31)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);

		ans_reg[0] |= (1<<tris_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<tris_bit) >> 8);

		#if (MX_ADC_NUM == 1)									//ADC Peripheral 1

			AD1CHS0 = (Channel & 0x1F);

			AD1CON2bits.VCFG1 = 0;
			AD1CON2bits.VCFG2 = 0;

			if (Vref == 0)											//Setup Vref+ functionality
				AD1CON2bits.VCFG0 = 0;
			else
				AD1CON2bits.VCFG0 = 1;

			if (Conv_Speed == 64)									//Assign conversion speed
			{
				AD1CON3bits.ADRC = 1;
			}
			else
			{
				AD1CON3bits.ADRC = 0;
				AD1CON3 = (Conv_Speed & 0xFF);
			}

			AD1CON1bits.AD12B = 1;									//12bit sampling
			AD1CON1bits.ADON = 1;									//Turn on ADC
			AD1CON1bits.SAMP = 1;

			delay_us(T_Charge);										//wait the acquisition time

		#endif

		#if (MX_ADC_NUM == 2)									//ADC Peripheral 1

			AD2CHS0 = (Channel & 0x1F);

			AD2CON2bits.VCFG1 = 0;
			AD2CON2bits.VCFG2 = 0;

			if (Vref == 0)											//Setup Vref+ functionality
				AD2CON2bits.VCFG0 = 0;
			else
				AD2CON2bits.VCFG0 = 1;

			if (Conv_Speed == 64)									//Assign conversion speed
			{
				AD2CON3bits.ADRC = 1;
			}
			else
			{
				AD2CON3bits.ADRC = 0;
				AD2CON3 = (Conv_Speed & 0xFF);
			}

			//AD2 may not have 12-bit sampling available, revert to 10-bit
			#ifdef _AD2CON1_AD12B_POSITION
			  AD2CON1bits.AD12B = 1;								//12bit sampling
			#endif

			AD2CON1bits.ADON = 1;									//Turn on ADC
			AD2CON1bits.SAMP = 1;

			delay_us(T_Charge);										//wait the acquisition time

		#endif

	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		#if (MX_ADC_NUM == 1)									//ADC Peripheral 1

			AD1CON1bits.SAMP = 0;									//begin next conversion

			while (!AD1CON1bits.DONE);

			if (Sample_Mode)
			{
				iRetVal = ADC1BUF0;									//12-bit ADC
			}
			else
				iRetVal = (ADC1BUF0 >> 4);							//8-bit ADC

			AD1CON1bits.SAMP = 1;

		#endif

		#if (MX_ADC_NUM == 2)									//ADC Peripheral 2

			AD2CON1bits.SAMP = 0;									//begin next conversion

			while (!AD2CON1bits.DONE);

			if (Sample_Mode)
			{
				iRetVal = ADC2BUF0;									//12-bit ADC
			}
			else
				iRetVal = (ADC2BUF0 >> 4);							//8-bit ADC

			AD2CON1bits.SAMP = 1;

		#endif

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		#if (MX_ADC_NUM == 1)										//ADC Peripheral 1
			AD1CON1bits.ADON = 0;
		#endif

		#if (MX_ADC_NUM == 2)										//ADC Peripheral 2
			AD2CON1bits.ADON = 0;
		#endif

		//*tris_reg = old_tris;										//restore old tris value, and reset adc registers
		ans_reg[0] &= ~(1<<tris_bit);								//clear ANSEL bit
		ans_reg[1] &= ~((1<<tris_bit) >> 8);						//clear ANSEL bit
	}


    #ifdef MX_ADC_SCAN

		CALFUNCTION(void, FC_CAL_ADC_ManualSample_, ())
		{
			AD2CON1bits.SAMP = 0;									 	//begin next conversion
		}

		CALFUNCTION(void, FC_CAL_ADC_ScanEnableChannel_, (MX_UINT8 Channel, MX_UINT8 Enable))
		{
			if (Channel < 16)
			{
				#if (MX_ADC_NUM == 1)									//ADC Peripheral 1
					if (Enable)
					{
						AD1CSSL |= (1 << Channel);						//Enable Scan Channel
					}
					else
					{
						AD1CSSL &= ~(1 << Channel);						//Disable Scan Channel
					}
				#endif

				#if (MX_ADC_NUM == 2)									//ADC Peripheral 2
					if (Enable)
					{
						AD2CSSL |= (1 << (Channel - 16));				//Enable Scan Channel
					}
					else
					{
						AD2CSSL &= ~(1 << (Channel - 16));				//Disable Scan Channel
					}
				#endif
			}
			else if (Channel < 32)
			{
				#if (MX_ADC_NUM == 1)									//ADC Peripheral 1
					if (Enable)
					{
						AD1CSSH |= (1 << Channel);						//Enable Scan Channel
					}
					else
					{
						AD1CSSH &= ~(1 << Channel);						//Disable Scan Channel
					}
				#endif

				#if (MX_ADC_NUM == 2)									//ADC Peripheral 2
					//AD2CSSH Not supported on this device
				#endif
			}
		}

    #endif // MX_ADC_SCAN


	#ifdef MX_ADC_TOUCH

	#define ADC_TOUCH_CONV_SPEED_VAL	1
	#define ADC_TOUCH_LOOP_VAL			16
	#define ADC_TOUCH_VREF_VAL			0
	#define ADC_TOUCH_CHARGE_VAL		50

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		MX_UINT16 ADC_Value = 0;
		MX_UINT8 loop = ADC_TOUCH_LOOP_VAL;
		MX_UINT16* latx;
		MX_UINT16* trisx;

		// use FC_CAL_ADC_Enable to setup the globals
		FC_CAL_ADC_Enable(Channel, ADC_TOUCH_CONV_SPEED_VAL, ADC_TOUCH_VREF_VAL, ADC_TOUCH_CHARGE_VAL);
		// wait until the conversion it kicks off has completed
		while (!AD1CON1bits.DONE);
		// get the LAT register from the configured TRIS register
		trisx = (MX_UINT16*)tris_reg;
		latx = trisx + 4;

		while (loop--)
		{
			// output Vdd to pin
			*trisx &= ~(1 << tris_bit);		// pin as output
			*latx |= (1 << tris_bit);			// set pin high
			delay_us(ADC_TOUCH_CHARGE_VAL);		// wait a while
			*trisx |= (1 << tris_bit);			// pin as input
			// sample the pin
			AD1CON1bits.SAMP = 1;				// take a sample
			delay_us(ADC_TOUCH_CHARGE_VAL);		// wait a while
			AD1CON1bits.SAMP = 0;				// begin conversion
			while (!AD1CON1bits.DONE);			// wait until it completes
			ADC_Value += ADC1BUF0;
		}

		FC_CAL_ADC_Disable();
		return ADC_Value / ADC_TOUCH_LOOP_VAL;
	}

	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 11 Supported Devices ************************************************************
PIC24FJ128GA306 Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_11

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		#ifdef MX_ADC_CHANNEL_0
			if (Channel == 0)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_1
			if (Channel == 1)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_2
			if (Channel == 2)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_3
			if (Channel == 3)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_4
			if (Channel == 4)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_5
			if (Channel == 5)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 5;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_6
			if (Channel == 6)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_7
			if (Channel == 7)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_8
			if (Channel == 8)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 8;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_9
			if (Channel == 9)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_10
			if (Channel == 10)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 10;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_11
			if (Channel == 11)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 11;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_12
			if (Channel == 12)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 12;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_13
			if (Channel == 13)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 13;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_14
			if (Channel == 14)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 14;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_15
			if (Channel == 15)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 15;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_16
			if (Channel == 16)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_17
			if (Channel == 17)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_18
			if (Channel == 18)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_19
			if (Channel == 19)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 8;
				ans_reg = (MX_UINT8 *) &ANSG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_20
			if (Channel == 20)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_21
			if (Channel == 21)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_22
			if (Channel == 22)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_23
			if (Channel == 23)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);
		ans_reg[0] |= (1<<tris_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<tris_bit) >> 8);

		AD1CHS = (Channel & 0x1F);								//Setup ADC Channel

		if (Vref == 0)											//Setup Vref+ functionality
			AD1CON2bits.PVCFG = 0;
		else
			AD1CON2bits.PVCFG = 1;

		AD1CON3 = 0;
		if (Conv_Speed & 0x40)									//Assign conversion speed
			AD1CON3bits.ADRC = 1;								//Internal RC Clock
		else
			AD1CON3 = (Conv_Speed & 0x3F);						//Based on system clock

		#ifdef MX_ADC_BITS_12
			AD1CON1bits.MODE12 = 1;
		#endif

		AD1CON1bits.ADON = 1;									//Turn on ADC
		AD1CON1bits.SAMP = 1;

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		AD1CON1bits.SAMP = 0;									//begin next conversion

		while (!AD1CON1bits.DONE);

		if (Sample_Mode)
		{
			iRetVal = ADC1BUF0;									//10/12-bit ADC
		}
		else
		{
			#ifdef MX_ADC_BITS_12
				iRetVal = (ADC1BUF0 >> 4);							//8-bit ADC
			#else
				iRetVal = (ADC1BUF0 >> 2);							//8-bit ADC
			#endif
		}

		AD1CON1bits.SAMP = 1;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		AD1CON1bits.ADON = 0;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ans_reg[0] &= ~(1<<tris_bit);								//set ANSEL bit
		ans_reg[1] &= (~(1<<tris_bit) >> 8);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 12 Supported Devices ************************************************************
PIC24FJ128GC010 Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_12

MX_STRING ans_reg;

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		#ifdef MX_ADC_CHANNEL_0
			if (Channel == 0)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_1
			if (Channel == 1)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_2
			if (Channel == 2)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_3
			if (Channel == 3)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_4
			if (Channel == 4)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_5
			if (Channel == 5)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 5;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_6
			if (Channel == 6)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_7
			if (Channel == 7)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_8
			if (Channel == 8)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_9
			if (Channel == 9)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_10
			if (Channel == 10)
			{
				tris_reg = (MX_UINT8 *) &TRISF;
				tris_bit = 5;
				ans_reg = (MX_UINT8 *) &ANSF;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_11
			if (Channel == 11)
			{
				tris_reg = (MX_UINT8 *) &TRISF;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSF;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_12
			if (Channel == 12)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 12;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_13
			if (Channel == 13)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 13;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_14
			if (Channel == 14)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 14;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_15
			if (Channel == 15)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 15;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_16
			if (Channel == 16)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_17
			if (Channel == 17)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_18
			if (Channel == 18)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_19
			if (Channel == 19)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 8;
				ans_reg = (MX_UINT8 *) &ANSG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_20
			if (Channel == 20)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_21
			if (Channel == 21)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_22
			if (Channel == 22)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_23
			if (Channel == 23)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_24
			if (Channel == 24)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_25
			if (Channel == 25)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_26
			if (Channel == 26)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_27
			if (Channel == 27)
			{
				tris_reg = (MX_UINT8 *) &TRISF;
				tris_bit = 13;
				ans_reg = (MX_UINT8 *) &ANSF;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_28
			if (Channel == 28)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 14;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_29
			if (Channel == 29)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 15;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_30
			if (Channel == 30)
			{
				tris_reg = (MX_UINT8 *) &TRISF;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSF;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_31
			if (Channel == 31)
			{
				tris_reg = (MX_UINT8 *) &TRISF;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSF;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_32
			if (Channel == 32)
			{
				tris_reg = (MX_UINT8 *) &TRISF;
				tris_bit = 8;
				ans_reg = (MX_UINT8 *) &ANSF;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_33
			if (Channel == 33)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 15;
				ans_reg = (MX_UINT8 *) &ANSG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_34
			if (Channel == 34)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_35
			if (Channel == 35)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_36
			if (Channel == 36)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_37
			if (Channel == 37)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 5;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_38
			if (Channel == 38)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 14;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_39
			if (Channel == 39)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 15;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_40
			if (Channel == 40)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 8;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_41
			if (Channel == 41)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 10;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_42
			if (Channel == 42)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 11;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_43
			if (Channel == 43)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_44
			if (Channel == 44)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_45
			if (Channel == 45)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 12;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_46
			if (Channel == 46)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 13;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_47
			if (Channel == 47)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_48
			if (Channel == 48)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 5;
				ans_reg = (MX_UINT8 *) &ANSD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_49
			if (Channel == 49)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSG;
			}
		#endif


		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);
		ans_reg[0] |= (1<<tris_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<tris_bit) >> 8);

		ADTBL0 = (Channel & 0x7F);								//Setup ADC Channel

		if (Vref == 0)											//Setup Vref+ functionality
			ADCON2bits.PVCFG = 0;								//AVDD
		else
			ADCON2bits.PVCFG = 1;								//VREF+

		ADCON3 = 0;
		if (Conv_Speed & 0x40)									//Assign conversion speed
			ADCON3bits.ADRC = 1;								//Internal RC Clock
		else
			ADCON3 = (Conv_Speed & 0xFF);						//Based on system clock

		ADCON1bits.ADON = 1;									//Turn on ADC
		ADL0CONLbits.SAMP = 1;

		delay_us(T_Charge);										//wait the acquisition time

	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADL0CONLbits.SAMP = 0;									//begin next conversion

		while (ADSTATHbits.ADBUSY);

		if (Sample_Mode)
		{
			iRetVal = ADRES0;									//10-bit ADC
		}
		else
			iRetVal = (ADRES0 >> 4);							//8-bit ADC

		ADL0CONLbits.SAMP = 1;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON1bits.ADON = 0;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ans_reg[0] &= ~(1<<tris_bit);								//set ANSEL bit
		ans_reg[1] &= (~(1<<tris_bit) >> 8);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 13 Supported Devices ************************************************************
dsPIC33EPxxGS50x Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_13

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		#ifdef MX_ADC_CHANNEL_0
			if (Channel == 0)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_1
			if (Channel == 1)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_2
			if (Channel == 2)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_3
			if (Channel == 3)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_4
			if (Channel == 4)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_5
			if (Channel == 5)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 10;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_6
			if (Channel == 6)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_7
			if (Channel == 7)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_8
			if (Channel == 8)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_9
			if (Channel == 9)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_10
			if (Channel == 10)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 10;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_11
			if (Channel == 11)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_12
			if (Channel == 12)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 11;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_13
			if (Channel == 13)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 13;
				ans_reg = (MX_UINT8 *) &ANSELD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_14
			if (Channel == 14)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 12;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_15
			if (Channel == 15)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSELD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_16
			if (Channel == 16)
			{
				tris_reg = (MX_UINT8 *) &TRISD;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSELD;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_17
			if (Channel == 17)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_18
			if (Channel == 18)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_19
			if (Channel == 19)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 5;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_20
			if (Channel == 20)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_21
			if (Channel == 21)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);
		ans_reg[0] |= (1<<tris_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<tris_bit) >> 8);

		AD1CHS0 = (Channel & 0x1F);

		AD1CON2bits.VCFG1 = 0;
		AD1CON2bits.VCFG2 = 0;

		if (Vref == 0)											//Setup Vref+ functionality
			AD1CON2bits.VCFG0 = 0;
		else
			AD1CON2bits.VCFG0 = 1;

		if (Conv_Speed == 64)									//Assign conversion speed
		{
			AD1CON3bits.ADRC = 1;
		}
		else
		{
			AD1CON3bits.ADRC = 0;
			AD1CON3 = (Conv_Speed & 0xFF);
		}

		AD1CON1bits.AD12B = 1;									//12bit sampling
		AD1CON1bits.ADON = 1;									//Turn on ADC
		AD1CON1bits.SAMP = 1;

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		AD1CON1bits.SAMP = 0;									//begin next conversion

		while (!AD1CON1bits.DONE);

		if (Sample_Mode)
		{
			iRetVal = ADC1BUF0;									//12-bit ADC
		}
		else
			iRetVal = (ADC1BUF0 >> 4);							//8-bit ADC

		AD1CON1bits.SAMP = 1;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		AD1CON1bits.ADON = 0;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ans_reg[0] &= ~(1<<tris_bit);								//set ANSEL bit
		ans_reg[1] &= (~(1<<tris_bit) >> 8);
	}

	#ifdef MX_ADC_TOUCH

	#define ADC_TOUCH_CONV_SPEED_VAL	1
	#define ADC_TOUCH_LOOP_VAL			16
	#define ADC_TOUCH_VREF_VAL			0
	#define ADC_TOUCH_CHARGE_VAL		50

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		MX_UINT16 ADC_Value = 0;
		MX_UINT8 loop = ADC_TOUCH_LOOP_VAL;
		MX_UINT16* latx;
		MX_UINT16* trisx;

		// use FC_CAL_ADC_Enable to setup the globals
		FC_CAL_ADC_Enable(Channel, ADC_TOUCH_CONV_SPEED_VAL, ADC_TOUCH_VREF_VAL, ADC_TOUCH_CHARGE_VAL);
		// wait until the conversion it kicks off has completed
		while (!AD1CON1bits.DONE);
		// get the LAT register from the configured TRIS register
		trisx = (MX_UINT16*)tris_reg;
		latx = trisx + 4;

		while (loop--)
		{
			// output Vdd to pin
			*trisx &= ~(1 << tris_bit);		// pin as output
			*latx |= (1 << tris_bit);			// set pin high
			delay_us(ADC_TOUCH_CHARGE_VAL);		// wait a while
			*trisx |= (1 << tris_bit);			// pin as input
			// sample the pin
			AD1CON1bits.SAMP = 1;				// take a sample
			delay_us(ADC_TOUCH_CHARGE_VAL);		// wait a while
			AD1CON1bits.SAMP = 0;				// begin conversion
			while (!AD1CON1bits.DONE);			// wait until it completes
			ADC_Value += ADC1BUF0;
		}

		FC_CAL_ADC_Disable();
		return ADC_Value / ADC_TOUCH_LOOP_VAL;
	}

	#endif // MX_ADC_TOUCH

#endif

/* ADC Type 14 Supported Devices ************************************************************
PIC24FJ1024GA610 Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_14

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		#ifdef MX_ADC_CHANNEL_0
			if (Channel == 0)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_1
			if (Channel == 1)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_2
			if (Channel == 2)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_3
			if (Channel == 3)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_4
			if (Channel == 4)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_5
			if (Channel == 5)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 5;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_6
			if (Channel == 6)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_7
			if (Channel == 7)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_8
			if (Channel == 8)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 8;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_9
			if (Channel == 9)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_10
			if (Channel == 10)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 10;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_11
			if (Channel == 11)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 11;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_12
			if (Channel == 12)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 12;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_13
			if (Channel == 13)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 13;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_14
			if (Channel == 14)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 14;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_15
			if (Channel == 15)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 15;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_16
			if (Channel == 16)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_17
			if (Channel == 17)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_18
			if (Channel == 18)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_19
			if (Channel == 19)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 8;
				ans_reg = (MX_UINT8 *) &ANSG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_20
			if (Channel == 20)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_21
			if (Channel == 21)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_22
			if (Channel == 22)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_23
			if (Channel == 23)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);
		ans_reg[0] |= (1<<tris_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<tris_bit) >> 8);

		AD1CHS0 = (Channel & 0x1F);

		AD1CON2bits.NVCFG0 = 0;									//Negative Voltage Reference = AVSS

		//TYPO in XC16 header files PCVFG1 instead of PVCFG1

		AD1CON2bits.PCVFG1 = 0;									//Positive Voltage Reference = AVDD or ExtVREF+

		if (Vref == 0)											//Setup Vref+ functionality
			AD1CON2bits.PCVFG0 = 0;								//AVDD
		else
			AD1CON2bits.PCVFG0 = 1;								//ExtVREF+

		if (Conv_Speed == 64)									//Assign conversion speed
		{
			AD1CON3bits.ADRC = 1;
		}
		else
		{
			AD1CON3bits.ADRC = 0;
			AD1CON3 = (Conv_Speed & 0xFF);
		}

		AD1CON1bits.MODE12 = 1;									//12bit sampling
		AD1CON1bits.ADON = 1;									//Turn on ADC
		AD1CON1bits.SAMP = 1;

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		AD1CON1bits.SAMP = 0;									//begin next conversion

		while (!AD1CON1bits.DONE);

		if (Sample_Mode)
		{
			iRetVal = ADC1BUF0;									//12-bit ADC
		}
		else
			iRetVal = (ADC1BUF0 >> 4);							//8-bit ADC

		AD1CON1bits.SAMP = 1;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		AD1CON1bits.ADON = 0;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ans_reg[0] &= ~(1<<tris_bit);								//set ANSEL bit
		ans_reg[1] &= (~(1<<tris_bit) >> 8);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 15 Supported Devices ************************************************************
PIC24FJ256GA705 Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_15

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		#ifdef MX_ADC_CHANNEL_0
			if (Channel == 0)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_1
			if (Channel == 1)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_2
			if (Channel == 2)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_3
			if (Channel == 3)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_4
			if (Channel == 4)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_5
			if (Channel == 5)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_6
			if (Channel == 6)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 14;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_7
			if (Channel == 7)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 13;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_8
			if (Channel == 8)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 12;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_9
			if (Channel == 9)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 15;
				ans_reg = (MX_UINT8 *) &ANSB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_10
			if (Channel == 10)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_11
			if (Channel == 11)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_12
			if (Channel == 12)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_13
			if (Channel == 13)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSC;
			}
		#endif

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);
		ans_reg[0] |= (1<<tris_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<tris_bit) >> 8);

		AD1CHS = (Channel & 0x1F);								//Setup ADC Channel

		if (Vref == 0)											//Setup Vref+ functionality
			AD1CON2bits.PVCFG = 0;
		else
			AD1CON2bits.PVCFG = 1;

		AD1CON3 = 0;
		if (Conv_Speed == 64)									//Assign conversion speed
			AD1CON3bits.ADRC = 1;								//Internal RC Clock
		else
			AD1CON3 = (Conv_Speed & 0xFF);						//Based on system clock

		#ifdef MX_ADC_BITS_12
			AD1CON1bits.MODE12 = 1;
		#endif

		AD1CON1bits.ADON = 1;									//Turn on ADC
		AD1CON1bits.SAMP = 1;

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		AD1CON1bits.SAMP = 0;									//begin next conversion

		while (!AD1CON1bits.DONE);

		if (Sample_Mode)
		{
			iRetVal = ADC1BUF0;									//10/12-bit ADC
		}
		else
		{
			#ifdef MX_ADC_BITS_12
				iRetVal = (ADC1BUF0 >> 4);							//8-bit ADC
			#else
				iRetVal = (ADC1BUF0 >> 2);							//8-bit ADC
			#endif
		}

		AD1CON1bits.SAMP = 1;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		AD1CON1bits.ADON = 0;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ans_reg[0] &= ~(1<<tris_bit);								//set ANSEL bit
		ans_reg[1] &= (~(1<<tris_bit) >> 8);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 16 Supported Devices ************************************************************
dsPIC33EVxxxGMxxx Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_16

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		#ifdef MX_ADC_CHANNEL_0
			if (Channel == 0)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_1
			if (Channel == 1)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_2
			if (Channel == 2)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_3
			if (Channel == 3)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_4
			if (Channel == 4)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_5
			if (Channel == 5)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_6
			if (Channel == 6)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 0;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_7
			if (Channel == 7)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 1;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_8
			if (Channel == 8)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 2;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_9
			if (Channel == 9)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 11;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_10
			if (Channel == 10)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 12;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_11
			if (Channel == 11)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 11;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_12
			if (Channel == 12)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 12;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_13
			if (Channel == 13)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 13;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_14
			if (Channel == 14)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 14;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_15
			if (Channel == 15)
			{
				tris_reg = (MX_UINT8 *) &TRISE;
				tris_bit = 15;
				ans_reg = (MX_UINT8 *) &ANSELE;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_16
			if (Channel == 16)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSELG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_17
			if (Channel == 17)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 8;
				ans_reg = (MX_UINT8 *) &ANSELG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_18
			if (Channel == 18)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSELG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_19
			if (Channel == 19)
			{
				tris_reg = (MX_UINT8 *) &TRISG;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSELG;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_24
			if (Channel == 24)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_25
			if (Channel == 25)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_26
			if (Channel == 26)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 8;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_27
			if (Channel == 27)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSELB;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_28
			if (Channel == 28)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_29
			if (Channel == 29)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 3;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_30
			if (Channel == 30)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 4;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_31
			if (Channel == 31)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 5;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_48
			if (Channel == 48)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 10;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_49
			if (Channel == 49)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 12;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_51
			if (Channel == 51)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 8;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_52
			if (Channel == 52)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_53
			if (Channel == 53)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 6;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_54
			if (Channel == 54)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 9;
				ans_reg = (MX_UINT8 *) &ANSELC;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_55
			if (Channel == 55)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 7;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_56
			if (Channel == 56)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 10;
				ans_reg = (MX_UINT8 *) &ANSELA;
			}
		#endif

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);
		ans_reg[0] |= (1<<tris_bit);								//set ANSEL bit
		ans_reg[1] |= ((1<<tris_bit) >> 8);

		AD1CHS0 = (Channel & 0x3F);

		AD1CON2bits.VCFG1 = 0;
		AD1CON2bits.VCFG2 = 0;

		if (Vref == 0)											//Setup Vref+ functionality
			AD1CON2bits.VCFG0 = 0;
		else
			AD1CON2bits.VCFG0 = 1;

		if (Conv_Speed == 64)									//Assign conversion speed
		{
			AD1CON3bits.ADRC = 1;
		}
		else
		{
			AD1CON3bits.ADRC = 0;
			AD1CON3 = (Conv_Speed & 0xFF);
		}

		AD1CON1bits.AD12B = 1;									//12bit sampling
		AD1CON1bits.ADON = 1;									//Turn on ADC
		AD1CON1bits.SAMP = 1;

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		AD1CON1bits.SAMP = 0;									//begin next conversion

		while (!AD1CON1bits.DONE);

		if (Sample_Mode)
		{
			iRetVal = ADC1BUF0;									//12-bit ADC
		}
		else
			iRetVal = (ADC1BUF0 >> 4);							//8-bit ADC

		AD1CON1bits.SAMP = 1;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		AD1CON1bits.ADON = 0;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ans_reg[0] &= ~(1<<tris_bit);								//set ANSEL bit
		ans_reg[1] &= (~(1<<tris_bit) >> 8);
	}

	#ifdef MX_ADC_TOUCH

	#define ADC_TOUCH_CONV_SPEED_VAL	1
	#define ADC_TOUCH_LOOP_VAL			16
	#define ADC_TOUCH_VREF_VAL			0
	#define ADC_TOUCH_CHARGE_VAL		50

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		MX_UINT16 ADC_Value = 0;
		MX_UINT8 loop = ADC_TOUCH_LOOP_VAL;
		MX_UINT16* latx;
		MX_UINT16* trisx;

		// use FC_CAL_ADC_Enable to setup the globals
		FC_CAL_ADC_Enable(Channel, ADC_TOUCH_CONV_SPEED_VAL, ADC_TOUCH_VREF_VAL, ADC_TOUCH_CHARGE_VAL);
		// wait until the conversion it kicks off has completed
		while (!AD1CON1bits.DONE);
		// get the LAT register from the configured TRIS register
		trisx = (MX_UINT16*)tris_reg;
		latx = trisx + 4;

		while (loop--)
		{
			// output Vdd to pin
			*trisx &= ~(1 << tris_bit);		// pin as output
			*latx |= (1 << tris_bit);			// set pin high
			delay_us(ADC_TOUCH_CHARGE_VAL);		// wait a while
			*trisx |= (1 << tris_bit);			// pin as input
			// sample the pin
			AD1CON1bits.SAMP = 1;				// take a sample
			delay_us(ADC_TOUCH_CHARGE_VAL);		// wait a while
			AD1CON1bits.SAMP = 0;				// begin conversion
			while (!AD1CON1bits.DONE);			// wait until it completes
			ADC_Value += ADC1BUF0;
		}

		FC_CAL_ADC_Disable();
		return ADC_Value / ADC_TOUCH_LOOP_VAL;
	}

	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 17 Supported Devices ************************************************************
PIC24FJxxGB00x Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_17
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		#ifdef MX_ADC_CHANNEL_0
			if (Channel == 0)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 0;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_1
			if (Channel == 1)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 1;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_2
			if (Channel == 2)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 0;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_3
			if (Channel == 3)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 1;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_4
			if (Channel == 4)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 2;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_5
			if (Channel == 5)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 3;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_6
			if (Channel == 6)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 0;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_7
			if (Channel == 7)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 1;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_8
			if (Channel == 8)
			{
				tris_reg = (MX_UINT8 *) &TRISC;
				tris_bit = 2;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_9
			if (Channel == 9)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 15;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_10
			if (Channel == 10)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 14;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_11
			if (Channel == 11)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 13;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_12
			if (Channel == 12)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 12;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_13
			if (Channel == 13)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 2;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_14
			if (Channel == 14)
			{
				tris_reg = (MX_UINT8 *) &TRISA;
				tris_bit = 3;
			}
		#endif
		#ifdef MX_ADC_CHANNEL_15
			if (Channel == 15)
			{
				tris_reg = (MX_UINT8 *) &TRISB;
				tris_bit = 4;
			}
		#endif

		tris_reg[0] |= (1<<tris_bit);
		tris_reg[1] |= ((1<<tris_bit) >> 8);
		AD1PCFG &= ~(1<<Channel);

		AD1CHS = (Channel & 0x0F);

		if (Vref == 0)											//Setup Vref+ functionality
			AD1CON2bits.VCFG0 = 0;
		else
			AD1CON2bits.VCFG0 = 1;

		AD1CON3 = 0;
		if (Conv_Speed & 0x40)									//Assign conversion speed
			AD1CON3bits.ADRC = 1;								//Internal RC Clock
		else
			AD1CON3 = (Conv_Speed & 0x3F);						//Based on system clock

		AD1CON1bits.ADON = 1;									//Turn on ADC
		AD1CON1bits.SAMP = 1;

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		AD1CON1bits.SAMP = 0;									//begin next conversion

		while (!AD1CON1bits.DONE);

		if (Sample_Mode)
		{
			iRetVal = ADC1BUF0;									//10-bit ADC
		}
		else
			iRetVal = (ADC1BUF0 >> 2);							//8-bit ADC

		AD1CON1bits.SAMP = 1;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		AD1CON1bits.ADON = 0;
		AD1PCFG |= 0x3FFF;

		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif

