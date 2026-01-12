// CRC: A6459004C43C0517DC6DFC5681C2AD698104299A14C9E1875427A2F7EF4303D9CFD76A29863CD488DE50EA9D9C0AC8D1D736E221269B259DD111497F7C88964FC90DDFD8A550770BF7832FC7BC8B9427C4965B289802A73C711B8143522C2B69D69968F8CFFB93495A6304FDEA47734DE1ECE1C51FE3B416B8C8D01E79388685C202C8C3E61B6A7E6A5686D210E76E6CB801174F7C37C9C5988DA962A1E1181C54722E78E98B0ACEFFFA11C72F27538CF93C85EB19451B75549D34A0D5AD11F35E85853EFCB30376C2C20348EA96B674ACEDB75F6BDC94B7AE50ACE3D7DDA2D28E9421B336835453
// REVISION: 6.0
// GUID: FC7919C7-AB6A-4B07-9F5D-8A166D1011CC
// DATE: 12\09\2023
// DIR: CAL\PIC32BIT\PIC32BIT_CAL_ADC.c
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
MX_UINT16 old_tris, tris_mask;
MX_STRING tris_reg;					//TRIS register pointer


/* ADC Type 1 Supported Devices ************************************************************
PIC32MX320F128H Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_1
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_reg = (MX_UINT8 *) &TRISB;
		old_tris = *tris_reg;									//store old tris value, and set the i/o pin as an input
		*tris_reg = old_tris | (1<<Channel);

		//clear_bit(AD1PCFG, Channel);							//Setup ADC Channel
		#ifdef _AD1PCFG_PCFG_POSITION
			_SFR_BIT_CLEAR(&AD1PCFG,Channel);
		#endif

		_SFR_WRITE(&AD1CON1, 0);
		_SFR_WRITE(&AD1CHS,(Channel & 0x0F) << 16);

		if (Vref == 0)											//Setup Vref+ functionality
			_SFR_BIT_CLEAR(&AD1CON2,13);
		else
			_SFR_BIT_SET(&AD1CON2,13);
		_SFR_WRITE(&AD1CON3, 0);
		if (Conv_Speed & 0xFF)									//Assign conversion speed
			_SFR_BIT_SET(&AD1CON3,15);
		else
			_SFR_WRITE(&AD1CON3,Conv_Speed & 0x7F);
		_SFR_BIT_SET(&AD1CON1,15);
		_SFR_BIT_SET(&AD1CON1,1);

		delay_us(T_Charge);										//wait the acquisition time

		_SFR_BIT_CLEAR(&AD1CON1,1);								//begin next conversion
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		while(_SFR_BIT_READ(&AD1CON1,0) == 0);

		if (Sample_Mode)
		{
			iRetVal = _SFR_READ(&ADC1BUF0);
		}
		else
			iRetVal = (_SFR_READ(&ADC1BUF0) >> 2);				//8-bit ADC

		_SFR_BIT_SET(&AD1CON1,1);
		delay_us(1);											//Required or processor locks up using Raw functions
		_SFR_BIT_CLEAR(&AD1CON1,1);								//begin next conversion

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		_SFR_BIT_CLEAR(&AD1CON1,15);

		#ifdef _AD1PCFG_PCFG_POSITION
			_SFR_WRITE(&AD1PCFG,0xFFFF);
		#endif
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
PIC32MZ2048ECG100 Family
*******************************************************************************************/


#ifdef MX_ADC_TYPE_2


	MX_UINT8 MX_Current_Channel;

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_reg = (MX_UINT8 *) &TRISB;
		old_tris = *tris_reg;									//store old tris value, and set the i/o pin as an input
		*tris_reg = old_tris | (1<<Channel);

		/* Set up the CAL registers */
    	_SFR_WRITE(&AD1CAL1,0xB3341210);
    	_SFR_WRITE(&AD1CAL2,0x01FFA769);
    	_SFR_WRITE(&AD1CAL3,0x0BBBBBB8);
    	_SFR_WRITE(&AD1CAL4,0x000004AC);
    	_SFR_WRITE(&AD1CAL5,0x02028002);
    	/* Configure AD1CON1 */
    	_SFR_WRITE(&AD1CON1,0); // No AD1CON1 features are enabled including: Stop-in-Idle, early
   		// interrupt, filter delay Fractional mode and scan trigger source.

    	/* Configure AD1CON2 */
    	_SFR_WRITE(&AD1CON2,0); // Boost, Low-power mode off, SAMC set to min, set up the ADC Clock
    	//_SFR_WRITE(&AD1CON2,((_SFR_READ(&AD1CON2)&0xFFFFFCFF)|0x1FF));//AD1CON2bits.ADCSEL = 1; // 1 = SYSCLK, 2 REFCLK03, 3 FRC
    	//_SFR_WRITE(&AD1CON2,((_SFR_READ(&AD1CON2)&0xFFFFFF80)|0x4));// TQ = 1/200 MHz; Tad = 4* (TQ * 2) = 40 ns; 25 MHz ADC clock

    	if (Conv_Speed & 0x80)									//Assign conversion speed
			_SFR_WRITE(&AD1CON2,((_SFR_READ(&AD1CON2)&0xFFFFFCFF)|0x300));//3 FRC
		else
			_SFR_WRITE(&AD1CON2,((_SFR_READ(&AD1CON2)&0xFFFFFCFF)|0x100));//SYSCLK
			_SFR_WRITE(&AD1CON2,((_SFR_READ(&AD1CON2)&0xFFFFFF80)|Conv_Speed));// TQ = 1/200 MHz; Tad =  Conv_Speed* (TQ * 2)

    	/* Configure AD1CON3 */
    	_SFR_WRITE(&AD1CON3,0); // ADINSEL is not configured for this example. VREFSEL of ?0?
   		// selects AVDD and AVSS as the voltage reference.
    	if (Vref == 0)											//Setup Vref+ functionality
			_SFR_WRITE(&AD1CON3,_SFR_READ(&AD1CON3)&0xFFFFE3FF);			//AVDD AVss
		else
			_SFR_WRITE(&AD1CON3,(_SFR_READ(&AD1CON3)&0xFFFFE3FF)|0x00000400);			//001 VREF+ AVss


    	/* Configure AD1MOD */
    	_SFR_WRITE(&AD1IMOD,0); // All channels configured for default input and single-ended
	   	// with unsigned output results.
	    /* Configure AD1GIRGENx */
	    _SFR_WRITE(&AD1GIRQEN1,0); // No global interrupts are used.
	    _SFR_WRITE(&AD1GIRQEN2,0);

	    /* Configure AD1CSSx */
	    _SFR_WRITE(&AD1CSS1,0); // No channel scanning is used.
	    _SFR_WRITE(&AD1CSS2,0);
	    /* Configure AD1CMPCONx */
	    _SFR_WRITE(&AD1CMPCON1,0); // No digital comparators are used. Setting the AD1CMPCONx
	    _SFR_WRITE(&AD1CMPCON2,0); // register to ?0? ensures that the comparator is disabled. Other
	    _SFR_WRITE(&AD1CMPCON3,0); // registers are ?don?t care?.
	    _SFR_WRITE(&AD1CMPCON4,0);
	    _SFR_WRITE(&AD1CMPCON5,0);
	    _SFR_WRITE(&AD1CMPCON6,0);
	    /* Configure AD1FLTRx */
	    _SFR_WRITE(&AD1FLTR1,0); // No oversampling filters are used.
	    _SFR_WRITE(&AD1FLTR2,0);
	    _SFR_WRITE(&AD1FLTR3,0);
	    _SFR_WRITE(&AD1FLTR4,0);
	    _SFR_WRITE(&AD1FLTR5,0);
	    _SFR_WRITE(&AD1FLTR6,0);
	    /* Set up the trigger sources */
	    //4 Channels per TRG (AD1 has AN0 to AN3 or Channels 0 to 3)
	    _SFR_WRITE(&AD1TRG1+(Channel/4),((_SFR_READ(&AD1TRG1)&((0x1F<<((Channel%4)*8))^0xFFFFFFFF))|(1<<((Channel%4)*8)))); // Set AN0 to trigger from software
	    /* Turn the ADC on, start calibration */
	    _SFR_WRITE(&AD1CON1,((_SFR_READ(&AD1CON1)&0xFFFF7FFF)|0x8000));
	    /* Wait for calibration to complete */
	    while(_SFR_BIT_READ(&AD1CON2,31) == 0);

		delay_us(T_Charge);		//wait the acquisition time
		MX_Current_Channel = Channel;
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		_SFR_WRITE(&AD1CON3,((_SFR_READ(&AD1CON3)&0xBFFFFFFF)|0x40000000));
        //AD1CON3bits.GSWTRG = 1;
        /* Wait the conversions to complete */
        while (_SFR_BIT_READ(&AD1DSTAT1,MX_Current_Channel) == 0);

         /* fetch the result */
		if (Sample_Mode)
		{
			iRetVal = _SFR_READ(&AD1DATA0 + MX_Current_Channel);
		}
		else
			iRetVal = (_SFR_READ(&AD1DATA0 + MX_Current_Channel) >> 2);							//8-bit ADC

		delay_us(1);											//Required or processor locks up using Raw functions

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		*tris_reg = old_tris;	//restore old tris value, and reset adc registers
		_SFR_WRITE(&AD1TRG1,0); // Initialize all sources to no trigger.
	    _SFR_WRITE(&AD1TRG2,0);
	    _SFR_WRITE(&AD1TRG3,0);
		_SFR_WRITE(&AD1CSS1,0);
		_SFR_WRITE(&AD1CSS2,0);
		_SFR_BIT_CLEAR(&AD1CON1,15);
		//_SFR_WRITE(&AD1PCFG,0xFFFF);
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
PIC32MZ2048EFG144 Family
*******************************************************************************************/


#ifdef MX_ADC_TYPE_3

	MX_UINT16 old_ans;
	MX_STRING ans_reg;					//ANSEL register pointer

	MX_UINT8 MX_Current_Channel;

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{

		switch (Channel)
		{
		  #ifdef MX_ADC_CHANNEL_0
			case 0:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 0;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_1
			case 1:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 1;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_2
			case 2:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 2;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_3
			case 3:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 3;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_4
			case 4:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 4;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_5
			case 5:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 10;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_6
			case 6:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 11;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_7
			case 7:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 12;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_8
			case 8:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 13;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_9
			case 9:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 14;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_10
			case 10:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 15;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_11
			case 11:
				tris_reg = (MX_UINT8 *) &TRISG;
				ans_reg = (MX_UINT8 *) &ANSELG;
				tris_mask = 9;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_12
			case 12:
				tris_reg = (MX_UINT8 *) &TRISG;
				ans_reg = (MX_UINT8 *) &ANSELG;
				tris_mask = 8;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_13
			case 13:
				tris_reg = (MX_UINT8 *) &TRISG;
				ans_reg = (MX_UINT8 *) &ANSELG;
				tris_mask = 7;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_14
			case 14:
				tris_reg = (MX_UINT8 *) &TRISG;
				ans_reg = (MX_UINT8 *) &ANSELG;
				tris_mask = 6;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_15
			case 15:
				tris_reg = (MX_UINT8 *) &TRISE;
				ans_reg = (MX_UINT8 *) &ANSELE;
				tris_mask = 7;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_16
			case 16:
				tris_reg = (MX_UINT8 *) &TRISE;
				ans_reg = (MX_UINT8 *) &ANSELE;
				tris_mask = 6;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_17
			case 17:
				tris_reg = (MX_UINT8 *) &TRISE;
				ans_reg = (MX_UINT8 *) &ANSELE;
				tris_mask = 5;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_18
			case 18:
				tris_reg = (MX_UINT8 *) &TRISE;
				ans_reg = (MX_UINT8 *) &ANSELE;
				tris_mask = 4;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_19
			case 19:
				tris_reg = (MX_UINT8 *) &TRISC;
				ans_reg = (MX_UINT8 *) &ANSELC;
				tris_mask = 4;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_20
			case 20:
				tris_reg = (MX_UINT8 *) &TRISC;
				ans_reg = (MX_UINT8 *) &ANSELC;
				tris_mask = 3;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_21
			case 21:
				tris_reg = (MX_UINT8 *) &TRISC;
				ans_reg = (MX_UINT8 *) &ANSELC;
				tris_mask = 2;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_22
			case 22:
				tris_reg = (MX_UINT8 *) &TRISC;
				ans_reg = (MX_UINT8 *) &ANSELC;
				tris_mask = 1;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_23
			case 23:
				tris_reg = (MX_UINT8 *) &TRISG;
				ans_reg = (MX_UINT8 *) &ANSELG;
				tris_mask = 15;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_24
			case 24:
				tris_reg = (MX_UINT8 *) &TRISA;
				ans_reg = (MX_UINT8 *) &ANSELA;
				tris_mask = 0;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_25
			case 25:
				tris_reg = (MX_UINT8 *) &TRISE;
				ans_reg = (MX_UINT8 *) &ANSELE;
				tris_mask = 8;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_26
			case 26:
				tris_reg = (MX_UINT8 *) &TRISE;
				ans_reg = (MX_UINT8 *) &ANSELE;
				tris_mask = 9;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_27
			case 27:
				tris_reg = (MX_UINT8 *) &TRISA;
				ans_reg = (MX_UINT8 *) &ANSELA;
				tris_mask = 9;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_28
			case 28:
				tris_reg = (MX_UINT8 *) &TRISA;
				ans_reg = (MX_UINT8 *) &ANSELA;
				tris_mask = 10;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_29
			case 29:
				tris_reg = (MX_UINT8 *) &TRISA;
				ans_reg = (MX_UINT8 *) &ANSELA;
				tris_mask = 1;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_30
			case 30:
				tris_reg = (MX_UINT8 *) &TRISF;
				ans_reg = (MX_UINT8 *) &ANSELF;
				tris_mask = 13;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_31
			case 31:
				tris_reg = (MX_UINT8 *) &TRISF;
				ans_reg = (MX_UINT8 *) &ANSELF;
				tris_mask = 12;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_32
			case 32:
				tris_reg = (MX_UINT8 *) &TRISD;
				ans_reg = (MX_UINT8 *) &ANSELD;
				tris_mask = 14;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_33
			case 33:
				tris_reg = (MX_UINT8 *) &TRISD;
				ans_reg = (MX_UINT8 *) &ANSELD;
				tris_mask = 15;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_34
			case 34:
				tris_reg = (MX_UINT8 *) &TRISA;
				ans_reg = (MX_UINT8 *) &ANSELA;
				tris_mask = 5;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_35
			case 35:
				tris_reg = (MX_UINT8 *) &TRISJ;
				ans_reg = (MX_UINT8 *) &ANSELJ;
				tris_mask = 8;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_36
			case 36:
				tris_reg = (MX_UINT8 *) &TRISJ;
				ans_reg = (MX_UINT8 *) &ANSELJ;
				tris_mask = 9;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_37
			case 37:
				tris_reg = (MX_UINT8 *) &TRISJ;
				ans_reg = (MX_UINT8 *) &ANSELJ;
				tris_mask = 11;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_38
			case 38:
				tris_reg = (MX_UINT8 *) &TRISH;
				ans_reg = (MX_UINT8 *) &ANSELH;
				tris_mask = 0;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_39
			case 39:
				tris_reg = (MX_UINT8 *) &TRISH;
				ans_reg = (MX_UINT8 *) &ANSELH;
				tris_mask = 1;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_40
			case 40:
				tris_reg = (MX_UINT8 *) &TRISH;
				ans_reg = (MX_UINT8 *) &ANSELH;
				tris_mask = 4;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_41
			case 41:
				tris_reg = (MX_UINT8 *) &TRISH;
				ans_reg = (MX_UINT8 *) &ANSELH;
				tris_mask = 5;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_42
			case 42:
				tris_reg = (MX_UINT8 *) &TRISH;
				ans_reg = (MX_UINT8 *) &ANSELH;
				tris_mask = 6;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_45
			case 45:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 5;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_46
			case 46:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 6;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_47
			case 47:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 7;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_48
			case 48:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 8;
				break;
		  #endif
		  #ifdef MX_ADC_CHANNEL_49
			case 49:
				tris_reg = (MX_UINT8 *) &TRISB;
				ans_reg = (MX_UINT8 *) &ANSELB;
				tris_mask = 9;
				break;
		  #endif
		}

		old_tris = *tris_reg;									//store old tris value, and set the i/o pin as an input
		*tris_reg = old_tris | (1 << tris_mask);

		old_ans = *ans_reg;
		*ans_reg = old_ans | (1 << tris_mask);

		/* initialize ADC calibration setting */
		//ADC0CFG = DEVADC0;
		//ADC1CFG = DEVADC1;
		//ADC2CFG = DEVADC2;
		//ADC3CFG = DEVADC3;
		//ADC4CFG = DEVADC4;
		//ADC5CFG = DEVADC5;
		//ADC6CFG = DEVADC6;
		//ADC7CFG = DEVADC7;
		/* Configure ADCCON1 */

		ADCCON1 = 0; // No ADCCON1 features are enabled including: Stop-in-Idle, turbo, CVD mode, Fractional mode and scan trigger source.

		/* Configure ADCCON2 */
		ADCCON2 = 0; // Since, we are using only the Class 1 inputs, no setting is required for ADCDIV

		/* Initialize warm up time register */
		ADCANCON = 0;
		ADCANCONbits.WKUPCLKCNT = 5; // Wakeup exponent = 32 * TADx

		/* Clock setting */
		ADCCON3 = 0;

		if (Conv_Speed == 128)		//FRC
		{
			ADCCON3bits.ADCSEL = 3; 		// Select input clock source
			ADCCON3bits.CONCLKDIV = 1;  	// Control clock frequency is half of input clock
		}
		else
		{
			ADCCON3bits.ADCSEL = 0; 		// Select input clock source
			ADCCON3bits.CONCLKDIV = Conv_Speed;  // Control clock frequency is half of input clock
		}

		if (Vref)
			ADCCON3bits.VREFSEL = 1;  // Select Ext VREFH and AVSS as reference source
		else
			ADCCON3bits.VREFSEL = 0;  // Select AVDD and AVSS as reference source

		ADCCON3bits.ADINSEL = Channel;	//Select ADC Channel

		/* Select ADC sample time and conversion clock */
		ADC0TIMEbits.ADCDIV = 1;  // ADC0 clock frequency is half of control clock = TAD0
		ADC0TIMEbits.SAMC = 5;  // ADC0 sampling time = 5 * TAD0
		ADC0TIMEbits.SELRES = 3;  // ADC0 resolution is 12 bits
		ADC1TIMEbits.ADCDIV = 1;  // ADC1 clock frequency is half of control clock = TAD1
		ADC1TIMEbits.SAMC = 5;  // ADC1 sampling time = 5 * TAD1
		ADC1TIMEbits.SELRES = 3;  // ADC1 resolution is 12 bits
		ADC2TIMEbits.ADCDIV = 1;  // ADC2 clock frequency is half of control clock = TAD2
		ADC2TIMEbits.SAMC = 5;  // ADC2 sampling time = 5 * TAD2
		ADC2TIMEbits.SELRES = 3;  // ADC2 resolution is 12 bits

		/* Select analog input for ADC modules, no presync trigger, not sync sampling */
		ADCTRGMODEbits.SH0ALT = 0;  // ADC0 = AN0
		ADCTRGMODEbits.SH1ALT = 0;  // ADC1 = AN1
		ADCTRGMODEbits.SH2ALT = 0;  // ADC2 = AN2

		/* Select ADC input mode */
		ADCIMCON1bits.SIGN0 = 0;  // unsigned data format
		ADCIMCON1bits.DIFF0 = 0;  // Single ended mode
		ADCIMCON1bits.SIGN1 = 0;  // unsigned data format
		ADCIMCON1bits.DIFF1 = 0;  // Single ended mode
		ADCIMCON1bits.SIGN2 = 0;  // unsigned data format
		ADCIMCON1bits.DIFF2 = 0;  // Single ended mode
		/* Configure ADCGIRQENx */
		ADCGIRQEN1 = 0;  // No interrupts are used
		ADCGIRQEN2 = 0;
		/* Configure ADCCSSx */
		ADCCSS1 = 0;  // No scanning is used
		ADCCSS2 = 0;
		/* Configure ADCCMPCONx */
		ADCCMPCON1 = 0;  // No digital comparators are used. Setting the ADCCMPCONx
		ADCCMPCON2 = 0;  // register to '0' ensures that the comparator is disabled.
		ADCCMPCON3 = 0;  // Other registers are “don't care”.
		ADCCMPCON4 = 0;
		ADCCMPCON5 = 0;
		ADCCMPCON6 = 0;

		/* Configure ADCFLTRx */
		ADCFLTR1 = 0;  // No oversampling filters are used.
		ADCFLTR2 = 0;
		ADCFLTR3 = 0;
		ADCFLTR4 = 0;
		ADCFLTR5 = 0;
		ADCFLTR6 = 0;

		/* Set up the trigger sources */
		ADCTRGSNSbits.LVL0 = 0;  // Edge trigger
		//ADCTRGSNSbits.LVL1 = 0;  // Edge trigger
		//ADCTRGSNSbits.LVL2 = 0;  // Edge trigger

		ADCTRG1bits.TRGSRC0 = 1;  // Set AN0 to trigger from software.
		//ADCTRG1bits.TRGSRC1 = 1;  // Set AN1 to trigger from software.
		//ADCTRG1bits.TRGSRC2 = 1;  // Set AN2 to trigger from software.

		/* Early interrupt */
		ADCEIEN1 = 0; // No early interrupt
		ADCEIEN2 = 0;

		/* Turn the ADC on */
		ADCCON1bits.ON = 1;

		/* Wait for voltage reference to be stable */
		while(!ADCCON2bits.BGVRRDY);  // Wait until the reference voltage is ready
		while(ADCCON2bits.REFFLT);  // Wait if there is a fault with the reference voltage

		/* Enable clock to analog circuit */
		ADCANCONbits.ANEN0 = 1;  // Enable the clock to analog bias
		//ADCANCONbits.ANEN1 = 1;  // Enable the clock to analog bias
		//ADCANCONbits.ANEN2 = 1;  // Enable the clock to analog bias

		/* Wait for ADC to be ready */
		while(!ADCANCONbits.WKRDY0);  // Wait until ADC0 is ready
		//while(!ADCANCONbits.WKRDY1);  // Wait until ADC1 is ready
		//while(!ADCANCONbits.WKRDY2);  // Wait until ADC2 is ready

		/* Enable the ADC module */
		ADCCON3bits.DIGEN0 = 1;  // Enable ADC0
		//ADCCON3bits.DIGEN1 = 1;  // Enable ADC1
		//ADCCON3bits.DIGEN2 = 1;  // Enable ADC2

		/* Trigger a conversion */
		ADCCON3bits.GSWTRG = 1;

		delay_us(T_Charge);		//wait the acquisition time
		MX_Current_Channel = Channel;
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		/* Wait the conversions to complete */
		while (ADCDSTAT1bits.ARDY0 == 0);

		/* fetch the result */
		iRetVal = ADCDATA0;

         /* fetch the result */
		if (Sample_Mode)
		{
			iRetVal = ADCDATA0;
		}
		else
			iRetVal = ADCDATA0 >> 4;							//8-bit ADC

		delay_us(1);											//Required or processor locks up using Raw functions

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		*tris_reg = old_tris;	//restore old tris value, and reset adc registers

		ADCCON1bits.ON = 0;
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
PIC32MM Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_4
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_reg = (MX_UINT8 *) &TRISB;
		old_tris = *tris_reg;									//store old tris value, and set the i/o pin as an input
		*tris_reg = old_tris | (1<<Channel);

		//clear_bit(AD1PCFG, Channel);							//Setup ADC Channel
		#ifdef _AD1PCFG_PCFG_POSITION
			_SFR_BIT_CLEAR(&AD1PCFG,Channel);
		#endif

		_SFR_WRITE(&AD1CON1, 0);
		_SFR_WRITE(&AD1CHS, (Channel & 0x1F));

		if (Vref == 0)											//Setup Vref+ functionality
			_SFR_BIT_CLEAR(&AD1CON2,14);
		else
			_SFR_BIT_SET(&AD1CON2,14);

		_SFR_WRITE(&AD1CON3, 0);
		if (Conv_Speed & 0xFF)									//Assign conversion speed
			_SFR_BIT_SET(&AD1CON3,15);
		else
			_SFR_WRITE(&AD1CON3,Conv_Speed & 0x7F);

		_SFR_BIT_SET(&AD1CON1,3);								//12-Bit Mode

		_SFR_BIT_SET(&AD1CON1,15);
		_SFR_BIT_SET(&AD1CON1,1);

		delay_us(T_Charge);										//wait the acquisition time

		_SFR_BIT_CLEAR(&AD1CON1,1);								//begin next conversion
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		while(_SFR_BIT_READ(&AD1CON1,0) == 0);

		if (Sample_Mode)
		{
			iRetVal = _SFR_READ(&ADC1BUF0);
		}
		else
			iRetVal = (_SFR_READ(&ADC1BUF0) >> 4);				//8-bit ADC

		_SFR_BIT_SET(&AD1CON1,1);
		delay_us(1);											//Required or processor locks up using Raw functions
		_SFR_BIT_CLEAR(&AD1CON1,1);								//begin next conversion

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		_SFR_BIT_CLEAR(&AD1CON1,15);

		#ifdef _AD1PCFG_PCFG_POSITION
			_SFR_WRITE(&AD1PCFG,0xFFFF);
		#endif
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
Sysblocks
*******************************************************************************************/

#ifdef MX_ADC_TYPE_5

	unsigned char MX_SYSBLOCKS_CAL_ADC_Initialised = 0;

	void MX_SYSBLOCKS_CAL_ADC_INIT()
	{
    	/* Setup pins for ADC input */
		ANSELB = 0x154; // Pins 2,4,6,8
		TRISB = TRISB | 0x154;

		ANSELG = 0xC0; 					// Pins G6/7
		TRISG = TRISG | 0xC0;

		/* initialize ADC calibration setting */
		/*ADC0CFG = DEVADC0;
		ADC1CFG = DEVADC1;
		ADC2CFG = DEVADC2;
		ADC3CFG = DEVADC3;
		ADC4CFG = DEVADC4;
		ADC7CFG = DEVADC7;*/
		/* Configure ADCCON1 */
		ADCCON1 = 0; // No ADCCON1 features are enabled including: Stop-in-Idle, turbo,
		// CVD mode, Fractional mode and scan trigger source.
		/* Configure ADCCON2 */
		ADCCON2 = 0; // Since, we are using only the Class 1 inputs, no setting is
		// required for ADCDIV
		/* Initialize warm up time register */
		ADCANCON = 0;
		ADCANCONbits.WKUPCLKCNT = 5; // Wakeup exponent = 32 * TADx
		/* Clock setting */
		ADCCON3 = 0;
		ADCCON3bits.ADCSEL = 0; // Select input clock source
		/* CONVERSION SPEED */
		ADCCON3bits.CONCLKDIV = 8; // Control clock frequency divider
		ADCCON3bits.VREFSEL = 0; // Select AVDD and AVSS as reference source
		/* Select ADC sample time and conversion clock */
		ADC1TIMEbits.ADCDIV = 1; // ADC1 clock frequency is half of control clock = TAD1
		ADC1TIMEbits.SAMC = 5; // ADC1 sampling time = 5 * TAD1
		ADC1TIMEbits.SELRES = 3; // ADC1 resolution is 12 bits
		ADC2TIMEbits.ADCDIV = 1; // ADC2 clock frequency is half of control clock = TAD2
		ADC2TIMEbits.SAMC = 5; // ADC2 sampling time = 5 * TAD2
		ADC2TIMEbits.SELRES = 3; // ADC2 resolution is 12 bits
		ADC3TIMEbits.ADCDIV = 1; // ADC3 clock frequency is half of control clock = TAD0
		ADC3TIMEbits.SAMC = 5; // ADC3 sampling time = 5 * TAD0
		ADC3TIMEbits.SELRES = 3; // ADC3 resolution is 12 bits
		ADC4TIMEbits.ADCDIV = 1; // ADC4 clock frequency is half of control clock = TAD0
		ADC4TIMEbits.SAMC = 5; // ADC4 sampling time = 5 * TAD0
		ADC4TIMEbits.SELRES = 3; // ADC4 resolution is 12 bits

		/* Select analog input for ADC modules, no presync trigger, not sync sampling */
		ADCTRGMODEbits.SH1ALT = 1; // ADC1 = AN46 / RB6 / IN0
		ADCTRGMODEbits.SH2ALT = 0; // ADC2 = AN2  / RB2 / Line In L
		ADCTRGMODEbits.SH3ALT = 1; // ADC3 = AN48 / RB8 / Line In R
		ADCTRGMODEbits.SH4ALT = 0; // ADC4 = AN4  / RB4 / IN1

		/* Select ADC input mode */
		ADCIMCON1bits.SIGN1 = 0; // unsigned data format
		ADCIMCON1bits.DIFF1 = 0; // Single ended mode
		ADCIMCON1bits.SIGN2 = 0; // unsigned data format
		ADCIMCON1bits.DIFF2 = 0; // Single ended mode
		ADCIMCON1bits.SIGN3 = 0; // unsigned data format
		ADCIMCON1bits.DIFF3 = 0; // Single ended mode
		ADCIMCON1bits.SIGN4 = 0; // unsigned data format
		ADCIMCON1bits.DIFF4 = 0; // Single ended mode

		/* Configure ADCGIRQENx */
		ADCGIRQEN1 = 0; // No interrupts are used
		ADCGIRQEN2 = 0;
		/* Configure ADCCSSx */
		ADCCSS1 = 0; // No scanning is used
		ADCCSS2 = 0;
		/* Configure ADCCMPCONx */
		ADCCMPCON1 = 0; // No digital comparators are used. Setting the ADCCMPCONx
		ADCCMPCON2 = 0; // register to '0' ensures that the comparator is disabled.
		ADCCMPCON3 = 0; // Other registers are “don't care”.
		ADCCMPCON4 = 0;
		ADCCMPCON5 = 0;
		ADCCMPCON6 = 0;
		/* Configure ADCFLTRx */
		ADCFLTR1 = 0; // No oversampling filters are used.
		ADCFLTR2 = 0;
		ADCFLTR3 = 0;
		ADCFLTR4 = 0;
		ADCFLTR5 = 0;
		ADCFLTR6 = 0;
		/* Set up the trigger sources */
		ADCTRGSNSbits.LVL0 = 0; // Edge trigger
		ADCTRGSNSbits.LVL1 = 0; // Edge trigger
		ADCTRGSNSbits.LVL2 = 0; // Edge trigger
		ADCTRGSNSbits.LVL3 = 0; // Edge trigger
		ADCTRGSNSbits.LVL4 = 0; // Edge trigger
		ADCTRG1bits.TRGSRC0 = 1; // Set AN0 to trigger from software.
		ADCTRG1bits.TRGSRC1 = 1; // Set AN1 to trigger from software.
		ADCTRG1bits.TRGSRC2 = 1; // Set AN2 to trigger from software.
		ADCTRG1bits.TRGSRC3 = 1; // Set AN0 to trigger from software.
		ADCTRG2bits.TRGSRC4 = 1; // Set AN0 to trigger from software.

		/* Early interrupt */
		ADCEIEN1 = 0; // No early interrupt
		ADCEIEN2 = 0;
		/* Turn the ADC on */
		ADCCON1bits.ON = 1;
		/* Wait for voltage reference to be stable */
		while(!ADCCON2bits.BGVRRDY); // Wait until the reference voltage is ready
		while(ADCCON2bits.REFFLT); // Wait if there is a fault with the reference voltage
		/* Enable clock to analog circuit */
		ADCANCONbits.ANEN0 = 1; // Enable the clock to analog bias
		ADCANCONbits.ANEN1 = 1; // Enable the clock to analog bias
		ADCANCONbits.ANEN2 = 1; // Enable the clock to analog bias
		ADCANCONbits.ANEN3 = 1; // Enable the clock to analog bias
		ADCANCONbits.ANEN4 = 1; // Enable the clock to analog bias

		/* Wait for ADC to be ready */
		while(!ADCANCONbits.WKRDY0); // Wait until ADC0 is ready
		while(!ADCANCONbits.WKRDY1); // Wait until ADC1 is ready
		while(!ADCANCONbits.WKRDY2); // Wait until ADC2 is ready
		while(!ADCANCONbits.WKRDY3); // Wait until ADC1 is ready
		while(!ADCANCONbits.WKRDY4); // Wait until ADC2 is ready

		/* Enable the ADC module */
		ADCCON3bits.DIGEN0 = 1; // Enable ADC0
		ADCCON3bits.DIGEN1 = 1; // Enable ADC1
		ADCCON3bits.DIGEN2 = 1; // Enable ADC2
		ADCCON3bits.DIGEN3 = 1; // Enable ADC1
		ADCCON3bits.DIGEN4 = 1; // Enable ADC2

		MX_SYSBLOCKS_CAL_ADC_Initialised = 1;
	}


	#define FC_CAL_ADC_Enable_1(A, B, C, D) 	FC_CAL_ADC_Enable(A)

	MX_UINT8 MX_ADC_ChannelMask = 0x0F;
	MX_UINT8 MX_ADC_Channel = 0;
	MX_UINT16 FCV_ADC_READING[4];

	void FC_CAL_ADC_Enable(MX_UINT8 Channel)
	{
		if (MX_SYSBLOCKS_CAL_ADC_Initialised == 0)
			MX_SYSBLOCKS_CAL_ADC_INIT();

		//Check to see if current channel needs a new sample
		if (MX_ADC_ChannelMask & (1 << Channel))
		{
			/* Trigger a conversion */
			ADCCON3bits.GSWTRG = 1;
			int i;

			for( i = 0; i < 50; i++ ){ Nop(); }

			/* Wait the conversion to complete IN0 */
			while (ADCDSTAT1bits.ARDY1 == 0);
			/* fetch the result */
			FCV_ADC_READING[0] = ADCDATA1;

			/* Wait the conversion to complete Line In L */
			while (ADCDSTAT1bits.ARDY2 == 0);
			/* fetch the result */
			FCV_ADC_READING[1] = ADCDATA2;

			/* Wait the conversion to complete Line In R */
			while (ADCDSTAT1bits.ARDY3 == 0);
			/* fetch the result */
			FCV_ADC_READING[2] = ADCDATA3;

			/* Wait the conversion to complete IN1 */
			while (ADCDSTAT1bits.ARDY4 == 0);
			/* fetch the result */
			FCV_ADC_READING[3] = ADCDATA4;


			MX_ADC_ChannelMask = 0;
		}

		MX_ADC_ChannelMask |= (1 << Channel);		//Flag channel as sampled
		MX_ADC_Channel = Channel;
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		if (MX_ADC_Channel < 4)
			return FCV_ADC_READING[MX_ADC_Channel];

		return 0;
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		return;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif

