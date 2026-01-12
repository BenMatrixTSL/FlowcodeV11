// CRC: 77485F5F6A861F9125D47827B4DE492656C5431E478E8046055FD2257F64F1F3298EE8C9FC6B4135A3C7E653C47A3E7E6E3D68567ED4A85AA23EB4FF97C4D92A077C96126F5B25C4711B8143522C2B698E411797686592ACF01F0A31D20B2A7754D8476EEF1E941535842394C699BFACD7A42172D765B716C5FB79DED7823D2E44E4E6CD7F8AA23C6DE271F57E38FB63FDF6879B53B14789EB076C513D4B3BDBDFACD1B6308AD93E549D34A0D5AD11F38B55CF34C0B2759FD1FF8A594BCE4BE4CB6D0B03C76A9173072F880DBB6DFDD32544F23D1CC1FCAE
// REVISION: 2.0
// GUID: 4CD67F85-EA8E-4195-99F2-69003AC7F93E
// DATE: 13\03\2023
// DIR: CAL\AVR\AVR_CAL_ADC.c
/*********************************************************************
 *                  Flowcode CAL ADC File
 *
 * File: AVR_CAL_ADC.c
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
 * 210911 | BR | Updated to include all ADC type files
 * 020312 | BR | Updated to v5.1 CAL Schema
 * 230512 | BR | Added XMEGA functionality
 * 171212 | BR | Moved the code to begin the sample to allow for more optimised ADC readings
 * 030713 | LM | Standard API calls
 * 240414 | LM | Additions to support Touch via ADC
 * 170914 | LM | Additions to support Touch via ADC (some types now actually work!)
 */


//ADC Function Prototypes
CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge));
CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode));
CALFUNCTION(void, FC_CAL_ADC_Disable_, ());
#ifdef MX_ADC_TOUCH
	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel);
#endif

//ADC Global Variables
//MX_UINT8 old_tris;
MX_UINT8 tris_mask;
MX_UINT8 * tris_reg;					//TRIS register pointer


/* ADC Type 1 Supported Devices ************************************************************
// Unknown
*******************************************************************************************/

#ifdef MX_ADC_TYPE_1
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_reg = (MX_UINT8*) &DDRA;
		//old_tris = *tris_reg;

		*tris_reg &= ~(1 << Channel);							//turn selected ADC on
		ADCSRA = (1 << ADEN) | Conv_Speed;
		ADMUX = (Vref << REFS0) | (1 << ADLAR) | Channel;

		if (T_Charge > 0)
			delay_us(T_Charge);									//wait the acquisition time

		ADCSRA |= (1 << ADSC);									//begin next conversion
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		while(ADCSRA & (1 << ADSC));

		if (Sample_Mode)
		{
			iRetVal = (ADCL >> 6);								//10-bit ADC
			iRetVal |= (ADCH << 2);
		}
		else
			iRetVal = ADCH;										//8-bit ADC

		ADCSRA |= (1 << ADSC);									//begin next conversion

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ADCSRA &= ~(1 << ADEN);
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
// Unknown
*******************************************************************************************/

#ifdef MX_ADC_TYPE_2
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_reg = (MX_UINT8*) &DDRC;
		//old_tris = *tris_reg;

		*tris_reg &= ~(1 << Channel);							//turn selected ADC on
		ADCSRA = (1 << ADEN) | Conv_Speed;
		ADMUX = (Vref << REFS0) | (1 << ADLAR) | Channel;

		if (T_Charge > 0)
			delay_us(T_Charge);									//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCSRA |= (1 << ADSC);									//begin next conversion
		while(ADCSRA & (1 << ADSC));

		if (Sample_Mode)
		{
			iRetVal = (ADCL >> 6);								//10-bit ADC
			iRetVal |= (ADCH << 2);
		}
		else
			iRetVal = ADCH;										//8-bit ADC

		//ADCSRA |= (1 << ADSC);								//begin next conversion

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ADCSRA &= ~(1 << ADEN);
	}

	#ifdef MX_ADC_TOUCH
	// Arduino Uno, ATMEGA328P ...
	#define ADC_TOUCH_CONV_SPEED_VAL	6
	#define ADC_TOUCH_VREF_VAL			1
	#define ADC_TOUCH_ADLAR_VAL			0
	#define ADC_TOUCH_LOOP_VAL			8
	#define ADC_TOUCH_PORT				PORTC
	#define ADC_TOUCH_DDR				DDRC

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		MX_UINT16 ADC_Value = 0;
		MX_UINT8 loop = ADC_TOUCH_LOOP_VAL;
		MX_UINT8 dummy;
		while (loop--)
		{
			// setup, initially to sample GND whilst output Vcc to pin
			ADMUX = (ADC_TOUCH_VREF_VAL << REFS0) | (ADC_TOUCH_ADLAR_VAL << ADLAR) | 0x1f;
			ADCSRA = (1 << ADEN) | ADC_TOUCH_CONV_SPEED_VAL;
			ADC_TOUCH_PORT |= (1 << Channel);
			ADC_TOUCH_DDR  |= (1 << Channel);
			ADC_TOUCH_DDR  &= ~(1 << Channel);
			// dummy read of the GND sample
			ADCSRA |= (1 << ADSC);
			while(ADCSRA & (1 << ADSC));
			dummy = ADCH;
			// change the mux and sample pin
			ADMUX = (ADC_TOUCH_VREF_VAL << REFS0) | (ADC_TOUCH_ADLAR_VAL << ADLAR) | Channel;
			ADCSRA |= (1 << ADSC);
			while(ADCSRA & (1 << ADSC));
			ADC_Value += ADCL;
			ADC_Value += ADCH << 8;
		}
		return ADC_Value / ADC_TOUCH_LOOP_VAL;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 3 Supported Devices ************************************************************
// Unknown
*******************************************************************************************/

#ifdef MX_ADC_TYPE_3

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_reg = (MX_UINT8*) &DDRF;
		//old_tris = *tris_reg;

		*tris_reg &= ~(1 << Channel);							//turn selected ADC on
		ADCSRA = (1 << ADEN) | Conv_Speed;
		ADMUX = (Vref << REFS0) | (1 << ADLAR) | Channel;

		if (T_Charge > 0)
			delay_us(T_Charge);										//wait the acquisition time

		ADCSRA |= (1 << ADSC);									//begin next conversion
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		while(ADCSRA & (1 << ADSC));

		if (Sample_Mode)
		{
			iRetVal = (ADCL >> 6);								//10-bit ADC
			iRetVal |= (ADCH << 2);
		}
		else
			iRetVal = ADCH;										//8-bit ADC

		ADCSRA |= (1 << ADSC);									//begin next conversion

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ADCSRA &= ~(1 << ADEN);
	}

	#ifdef MX_ADC_TOUCH
	// Arduino Leonardo, ATMEGA32U4 ...
	#define ADC_TOUCH_CONV_SPEED_VAL	6
	#define ADC_TOUCH_VREF_VAL			1
	#define ADC_TOUCH_ADLAR_VAL			0
	#define ADC_TOUCH_LOOP_VAL			8
	#define ADC_TOUCH_PORT				PORTF
	#define ADC_TOUCH_DDR				DDRF

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		MX_UINT16 ADC_Value = 0;
		MX_UINT8 loop = ADC_TOUCH_LOOP_VAL;
		MX_UINT8 dummy;
		while (loop--)
		{
			// setup, initially to sample GND whilst output Vcc to pin
			ADMUX = (ADC_TOUCH_VREF_VAL << REFS0) | (ADC_TOUCH_ADLAR_VAL << ADLAR) | 0x1f;
			ADCSRA = (1 << ADEN) | ADC_TOUCH_CONV_SPEED_VAL;
			ADC_TOUCH_PORT |= (1 << Channel);
			ADC_TOUCH_DDR  |= (1 << Channel);
			ADC_TOUCH_DDR  &= ~(1 << Channel);
			// dummy read of the GND sample
			ADCSRA |= (1 << ADSC);
			while(ADCSRA & (1 << ADSC));
			dummy = ADCH;
			// change the mux and sample pin
			ADMUX = (ADC_TOUCH_VREF_VAL << REFS0) | (ADC_TOUCH_ADLAR_VAL << ADLAR) | Channel;
			ADCSRA |= (1 << ADSC);
			while(ADCSRA & (1 << ADSC));
			ADC_Value += ADCL;
			ADC_Value += ADCH << 8;
		}
		return ADC_Value / ADC_TOUCH_LOOP_VAL;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 4 Supported Devices ************************************************************
// Unknown
*******************************************************************************************/

#ifdef MX_ADC_TYPE_4

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_mask = Channel;
		if (Channel > 2)
			tris_mask++;

		if (Channel < 7)
		{
			tris_reg = (MX_UINT8*) &DDRA;
		}
		else
		{
			tris_mask -= 4;
			tris_reg = (MX_UINT8*) &DDRB;
		}

		//old_tris = *tris_reg;

		*tris_reg &= ~(1 << tris_mask);							//turn selected ADC on
		ADCSRA = (1 << ADEN) | Conv_Speed;
		ADMUX = (Vref << REFS0) | (1 << ADLAR) | Channel;

		if (T_Charge > 0)
			delay_us(T_Charge);									//wait the acquisition time

		ADCSRA |= (1 << ADSC);									//begin next conversion
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		while(ADCSRA & (1 << ADSC));

		if (Sample_Mode)
		{
			iRetVal = (ADCL >> 6);								//10-bit ADC
			iRetVal |= (ADCH << 2);
		}
		else
			iRetVal = ADCH;										//8-bit ADC

		ADCSRA |= (1 << ADSC);									//begin next conversion

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ADCSRA &= ~(1 << ADEN);
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
// Unknown
*******************************************************************************************/

#ifdef MX_ADC_TYPE_5

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_mask = Channel;
		if (Channel != 3)
		{
			if (Channel == 0)
				tris_mask = 5;
			else tris_mask <<= 1;
		}
		tris_reg = (MX_UINT8*) &DDRB;
		//old_tris = *tris_reg;

		*tris_reg &= ~(1 << tris_mask);							//turn selected ADC on
		ADCSRA = (1 << ADEN) | Conv_Speed;
		ADMUX = (Vref << REFS0) | (1 << ADLAR) | Channel;

		if (T_Charge > 0)
			delay_us(T_Charge);									//wait the acquisition time

		ADCSRA |= (1 << ADSC);									//begin next conversion
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		while(ADCSRA & (1 << ADSC));

		if (Sample_Mode)
		{
			iRetVal = (ADCL >> 6);								//10-bit ADC
			iRetVal |= (ADCH << 2);
		}
		else
			iRetVal = ADCH;										//8-bit ADC

		ADCSRA |= (1 << ADSC);									//begin next conversion

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ADCSRA &= ~(1 << ADEN);
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
// Unknown
*******************************************************************************************/

#ifdef MX_ADC_TYPE_6

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_reg = (MX_UINT8*) &DDRA;
		//old_tris = *tris_reg;

		*tris_reg &= ~(1 << Channel);							//turn selected ADC on
		ADCSRA = (1 << ADEN) | Conv_Speed;
		ADMUX = (Vref << REFS0) | (1 << ADLAR) | Channel;

		if (T_Charge > 0)
			delay_us(T_Charge);									//wait the acquisition time

		ADCSRA |= (1 << ADSC);									//begin next conversion
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		while(ADCSRA & (1 << ADSC));

		if (Sample_Mode)
		{
			iRetVal = (ADCL >> 6);								//10-bit ADC
			iRetVal |= (ADCH << 2);
		}
		else
			iRetVal = ADCH;										//8-bit ADC

		ADCSRA |= (1 << ADSC);									//begin next conversion

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ADCSRA &= ~(1 << ADEN);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif



/* ADC Type 7 Supported Devices ************************************************************
// Unknown
*******************************************************************************************/

#ifdef MX_ADC_TYPE_7

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_mask = Channel;
		if (Channel > 2)
			tris_mask++;

		if (Channel < 7)
		{
			tris_reg = (MX_UINT8*) &DDRA;
		}
		else
		{
			tris_mask -= 4;
			tris_reg = (MX_UINT8*) &DDRB;
		}

		//old_tris = *tris_reg;

		*tris_reg &= ~(1 << tris_mask);							//turn selected ADC on
		ADCSR = (1 << ADEN) | Conv_Speed;
		ADMUX = (Vref << REFS0) | (1 << ADLAR) | Channel;

		if (T_Charge > 0)
			delay_us(T_Charge);									//wait the acquisition time

		ADCSR |= (1 << ADSC);									//begin next conversion
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		while(ADCSR & (1 << ADSC));

		if (Sample_Mode)
		{
			iRetVal = (ADCL >> 6);								//10-bit ADC
			iRetVal |= (ADCH << 2);
		}
		else
			iRetVal = ADCH;										//8-bit ADC

		ADCSR |= (1 << ADSC);									//begin next conversion

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ADCSR &= ~(1 << ADEN);
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
// Unknown
*******************************************************************************************/

#ifdef MX_ADC_TYPE_8

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_reg = (MX_UINT8*) &DDRC;
		//old_tris = *tris_reg;

		*tris_reg &= ~(1 << Channel);							//turn selected ADC on
		ADCSR = (1 << ADEN) | Conv_Speed;
		ADMUX = (Vref << REFS0) | (1 << ADLAR) | Channel;

		if (T_Charge > 0)
			delay_us(T_Charge);									//wait the acquisition time

		ADCSR |= (1 << ADSC);									//begin next conversion
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		while(ADCSR & (1 << ADSC));

		if (Sample_Mode)
		{
			iRetVal = (ADCH << 8);								//10-bit ADC
			iRetVal |= ADCL;
		}
		else
		{
			iRetVal = (ADCH << 6);								//8-bit ADC
			iRetVal |= (ADCL >> 2);
		}

		ADCSR |= (1 << ADSC);									//begin next conversion

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ADCSR &= ~(1 << ADEN);
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
// Unknown
*******************************************************************************************/

#ifdef MX_ADC_TYPE_9

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		tris_reg = (MX_UINT8*) &DDRA;
		//old_tris = *tris_reg;

		*tris_reg &= ~(1 << Channel);							//turn selected ADC on
		ADCSR = (1 << ADEN) | Conv_Speed;
		ADMUX = Channel;

		if (T_Charge > 0)
			delay_us(T_Charge);									//wait the acquisition time

		ADCSR |= (1 << ADSC);									//begin next conversion
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		while(ADCSR & (1 << ADSC));

		if (Sample_Mode)
		{
			iRetVal = (ADCH << 8);								//10-bit ADC
			iRetVal |= ADCL;
		}
		else
		{
			iRetVal = (ADCH << 6);								//8-bit ADC
			iRetVal |= (ADCL >> 2);
		}

		ADCSR |= (1 << ADSC);									//begin next conversion

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ADCSR &= ~(1 << ADEN);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 10 Supported Devices ***********************************************************
// Unknown
*******************************************************************************************/

#ifdef MX_ADC_TYPE_10

	MX_UINT8 Chan;

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		Chan = Channel & 0x07;
		tris_mask = Chan;

		if (Channel < 8)
		{
			ADCSRB &= ~(1 << MUX5);
			tris_reg = (MX_UINT8*) &DDRF;
		}
		else
		{
			ADCSRB |= (1 << MUX5);
			tris_reg = (MX_UINT8*) &DDRK;
		}

		//clear_bit(ADCSRB, MUX5);
		//old_tris = *tris_reg;

		*tris_reg &= ~(1 << tris_mask);							//turn selected ADC on
		ADCSRA = (1 << ADEN) | Conv_Speed;
		ADMUX = (Vref << REFS0) | (1 << ADLAR) | Chan;

		//ADCSRA = (1<<ADEN)|(1<<ADFR)|(1<<ADATE)|(1<<ADPS2);
  		//ADMUX  = (1<<ADLAR) | (1<<REFS0) | 9;    // Left-adjust, Ref. = AVCC

		if (T_Charge > 0)
			delay_us(T_Charge);									//wait the acquisition time

		ADCSRA |= (1 << ADSC);									//begin next conversion
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		while(ADCSRA & (1 << ADSC));

		if (Sample_Mode)
		{
			iRetVal = (ADCL >> 6);								//10-bit ADC
			iRetVal |= (ADCH << 2);
		}
		else
			iRetVal = ADCH;										//8-bit ADC


		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ADCSRA &= ~(1 << ADEN);
	}

	#ifdef MX_ADC_TOUCH
	// Arduino Mega 2560, ATMEGA2560
	#define ADC_TOUCH_CONV_SPEED_VAL	6
	#define ADC_TOUCH_VREF_VAL			1
	#define ADC_TOUCH_ADLAR_VAL			0
	#define ADC_TOUCH_LOOP_VAL			8

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		MX_UINT16 ADC_Value = 0;
		MX_UINT8 loop = ADC_TOUCH_LOOP_VAL;
		MX_UINT8 dummy;
		while (loop--)
		{
			// setup, initially to sample GND whilst output Vcc to pin
			ADCSRB = 0;		// MUX5 = 0
			ADMUX = (ADC_TOUCH_VREF_VAL << REFS0) | (ADC_TOUCH_ADLAR_VAL << ADLAR) | 0x1f;
			ADCSRA = (1 << ADEN) | ADC_TOUCH_CONV_SPEED_VAL;
			if (Channel < 8)
			{
				PORTF |= (1 << Channel);
				DDRF  |= (1 << Channel);
				DDRF  &= ~(1 << Channel);
			}
			else
			{
				PORTK |= (1 << (Channel & 7));
				DDRK  |= (1 << (Channel & 7));
				DDRK  &= ~(1 << (Channel & 7));
			}
			// dummy read of the GND sample
			ADCSRA |= (1 << ADSC);
			while(ADCSRA & (1 << ADSC));
			dummy = ADCH;
			// change the mux and sample pin
			if (Channel > 7)
				ADCSRB |= 8;	// MUX5 = 1
			ADMUX = (ADC_TOUCH_VREF_VAL << REFS0) | (ADC_TOUCH_ADLAR_VAL << ADLAR) | (Channel & 7);
			ADCSRA |= (1 << ADSC);
			while(ADCSRA & (1 << ADSC));
			ADC_Value += ADCL;
			ADC_Value += ADCH << 8;
		}
		return ADC_Value / ADC_TOUCH_LOOP_VAL;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 11 Supported Devices ***********************************************************
// Unknown
*******************************************************************************************/

#ifdef MX_ADC_TYPE_11

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		if (Channel == 0)
		{
			tris_mask = 0;
			tris_reg = (MX_UINT8*) &DDRE;
		}
		else
		{
			if (Channel < 4)
			{
				tris_mask = Channel + 3;
				tris_reg = (MX_UINT8*) &DDRD;
			}
			else
			{
				switch (Channel)
				{
					case (4):
						tris_mask = 7;
						break;
					case (5):
						tris_mask = 2;
						break;
					case (6):
						tris_mask = 5;
						break;
					case (7):
						tris_mask = 6;
						break;
				}
				tris_reg = (MX_UINT8*) &DDRB;
			}
		}
		//old_tris = *tris_reg;

		*tris_reg &= ~(1 << tris_mask);							//turn selected ADC on
		ADCSRA = (1 << ADEN) | Conv_Speed;
		ADMUX = (Vref << REFS0) | (1 << ADLAR) | Channel;

		if (T_Charge > 0)
			delay_us(T_Charge);									//wait the acquisition time

		ADCSRA |= (1 << ADSC);									//begin next conversion
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		while(ADCSRA & (1 << ADSC));

		if (Sample_Mode)
		{
			iRetVal = (ADCL >> 6);								//10-bit ADC
			iRetVal |= (ADCH << 2);
		}
		else
			iRetVal = ADCH;										//8-bit ADC

		ADCSRA |= (1 << ADSC);									//begin next conversion

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ADCSRA &= ~(1 << ADEN);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 12 Supported Devices ***********************************************************
// Unknown
*******************************************************************************************/

#ifdef MX_ADC_TYPE_12

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		if (Channel == 0)
		{
			tris_mask = 0;
			tris_reg = (MX_UINT8*) &DDRE;
		}
		else
		{
			if (Channel < 4)
			{
				tris_mask = Channel + 3;
				tris_reg = (MX_UINT8*) &DDRD;
			}
			else if (Channel > 7)
			{
				tris_mask = Channel - 4;
				tris_reg = (MX_UINT8*) &DDRD;
			}
			else
			{
				switch (Channel)
				{
					case (4):
						tris_mask = 7;
						break;
					case (5):
						tris_mask = 2;
						break;
					case (6):
						tris_mask = 5;
						break;
					case (7):
						tris_mask = 6;
						break;
				}
				tris_reg = (MX_UINT8*) &DDRB;
			}
		}
		//old_tris = *tris_reg;

		*tris_reg &= ~(1 << tris_mask);							//turn selected ADC on
		ADCSRA = (1 << ADEN) | Conv_Speed;
		ADMUX = (Vref << REFS0) | (1 << ADLAR) | Channel;

		if (T_Charge > 0)
			delay_us(T_Charge);									//wait the acquisition time

		ADCSRA |= (1 << ADSC);									//begin next conversion
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		while(ADCSRA & (1 << ADSC));

		if (Sample_Mode)
		{
			iRetVal = (ADCL >> 6);								//10-bit ADC
			iRetVal |= (ADCH << 2);
		}
		else
			iRetVal = ADCH;										//8-bit ADC

		ADCSRA |= (1 << ADSC);									//begin next conversion

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers
		ADCSRA &= ~(1 << ADEN);
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif


/* ADC Type 13 Supported Devices ***********************************************************
// ATXMEGA Device Family
*******************************************************************************************/

#ifdef MX_ADC_TYPE_13

	//MX_UINT8 mx_adcport;

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		if (Channel < 8)
		{
			tris_mask = Channel;
			tris_reg = (MX_UINT8*) &PORTA.DIR;
			//mx_adcport = 'A';
		}
		else
		{
			tris_mask = Channel - 8;
			tris_reg = (MX_UINT8*) &PORTB.DIR;
			//mx_adcport = 'B';
		}

		//old_tris = *tris_reg;
		*tris_reg &= ~(1 << tris_mask);

		//if (mx_adcport == 'A')
		//{
			ADCA.CTRLA = (1 << ADC_ENABLE_bp);					//turn selected ADC on
			ADCA.PRESCALER = Conv_Speed;

			ADCA.REFCTRL = (Vref << ADC_REFSEL1_bp);

			ADCA.CH0.CTRL = 0x01;								//Single ended sample mode - 1x gain
			ADCA.CH0.MUXCTRL = (Channel << 3);
		//}
		//else
		//{
		//	ADCB.CTRLA = (1 << ADC_ENABLE_bp);					//turn selected ADC on
		//	ADCB.PRESCALER = Conv_Speed;

		//	ADCB.REFCTRL = (Vref << ADC_REFSEL1_bp);

		//	ADCB.CH0.CTRL = 0x01;								//Single ended sample mode - 1x gain
		//	ADCB.CH0.MUXCTRL = (Channel << 3);
		//}

		if (T_Charge > 0)
			delay_us(T_Charge);									//wait the acquisition time

		//if (mx_adcport == 'A')
		//{
			ADCA.INTFLAGS |= 1;									//Clear CH0 interrupt flag if set
			ADCA.CTRLA |= (1 << ADC_CH0START_bp);				//begin next conversion
		//}
		//else
		//{
		//	ADCB.INTFLAGS |= 1;									//Clear CH0 interrupt flag if set
		//	ADCB.CTRLA |= (1 << ADC_CH0START_bp);				//begin next conversion
		//}

	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		//if (mx_adcport == 'A')
		//{
			while((ADCA.INTFLAGS & 1) == 0);					//Wait for sample to end

			if (Sample_Mode)
			{
				iRetVal = ADCA.CH0RESL;							//12-bit ADC
				iRetVal |= (ADCA.CH0RESH << 8);
			}
			else
			{
				iRetVal = (ADCA.CH0RESL >> 4);					//8-bit ADC
				iRetVal |= (ADCA.CH0RESH << 4);
			}

			ADCA.INTFLAGS |= 1;									//Clear CH0 interrupt flag if set
			ADCA.CTRLA |= (1 << ADC_CH0START_bp);				//begin next conversion
		//}
		//else
		//{
		//	while((ADCB.INTFLAGS & 1) == 0);					//Wait for sample to end

		//	if (Sample_Mode)
		//	{
		//		iRetVal = ADCB.CH0RESL;							//12-bit ADC
		//		iRetVal |= (ADCB.CH0RESH << 8);
		//	}
		//	else
		//	{
		//		iRetVal = (ADCB.CH0RESL >> 4);					//8-bit ADC
		//		iRetVal |= (ADCB.CH0RESH << 4);
		//	}

		//	ADCB.INTFLAGS |= 1;									//Clear CH0 interrupt flag if set
		//	ADCB.CTRLA |= (1 << ADC_CH0START_bp);				//begin next conversion
		//}

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		//*tris_reg = old_tris;									//restore old tris value, and reset adc registers

		//if (mx_adcport == 'A')
		//{
			ADCA.CTRLA &= ~(1 << ADC_ENABLE_bp);				//turn selected ADC off
		//}
		//else
		//{
		//	ADCB.CTRLA &= ~(1 << ADC_ENABLE_bp);				//turn selected ADC off
		//}
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Touch_, (MX_UINT8 Channel))
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif

