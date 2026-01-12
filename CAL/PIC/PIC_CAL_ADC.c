// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B8298EE8C9FC6B4135A3C7E653C47A3E7E4632351310DEB60C3BFED9C3CECF35AAFD2D54CA74B4B4EB0C3CAEE8E7DA6987E1BCDB508E24C58947787A577C778A62E33141402C7CA8DA549A36A051B897639CD8045E731A9D71C2F41F5DFFBF70DD7C4F39236B60D5C97D1AB83B5762B09C8E66F15F759A26DA0D4E7CD881FCD004B9C5457FA442A08A549D34A0D5AD11F3BC5BD09477E5C88999F10467F7777B6C0ECA4D483E578AC356E599B5AD11AA62EAC3685094CA720B
// REVISION: 3.0
// GUID: 360B2A16-7118-4FFF-ADB5-6792479976C8
// DATE: 27\01\2025
// DIR: CAL\PIC\PIC_CAL_ADC.c
/*********************************************************************
 *                  Flowcode CAL ADC File
 *
 * File: PIC_CAL_ADC.c
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
 * 110512 | BR | Fixed a bug with ADC type 13 and Vref+
 * 161012 | BR | Fixed a bug with ADC type 32 and 10 bit instead of 12 bit
 * 171212 | BR | Moved the code to begin the sample to allow for more optimised ADC readings
 * 020713 | LM | Standard API calls
 * 240414 | LM | Additions to support Touch via ADC
 * 040215 | LM | 16F726 fix modified so as to work with 16F1937
 * 070716 | LM | Updates to touch re XC8 compiler
 * 210125 | MW | Updated for 18F1XQ41
 */


//ADC Function Prototypes
CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge));
CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode));
CALFUNCTION(void, FC_CAL_ADC_Disable_, ());
#ifdef MX_ADC_TOUCH
	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel);
#endif

// ADC Type 1 Supported Devices ************************************************************
// 16F818, 16F819, 16F873A, 16F874A, 16F876A, 16F877A,
// *******************************************************************************************/

#ifdef MX_ADC_TYPE_1
	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;		//Pin configured an an input
					if (Vref == 0)
						ADCON1 = 0x0E;
					else
						ADCON1 = 0x05;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;		//Pin configured an an input
					if (Vref == 0)
						ADCON1 = 0x04;
					else
						ADCON1 = 0x05;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;		//Pin configured an an input
					if (Vref == 0)
						ADCON1 = 0x02;
					else
						ADCON1 = 0x03;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;		//Pin configured an an input
					if (Vref == 0)
						ADCON1 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;		//Pin configured an an input
					if (Vref == 0)
						ADCON1 = 0x02;
					else
						ADCON1 = 0x03;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISE |= 0x01;		//Pin configured an an input
					if (Vref == 0)
						ADCON1 = 0x09;
					else
						ADCON1 = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISE |= 0x02;		//Pin configured an an input
					if (Vref == 0)
						ADCON1 = 0x00;
					else
						ADCON1 = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISE |= 0x04;		//Pin configured an an input
					if (Vref == 0)
						ADCON1 = 0x00;
					else
						ADCON1 = 0x01;
					break;
			#endif
		}

		if (Conv_Speed > 3)										//assign conversion speed
			st_bit(ADCON1, ADCS2);

		ADCON0 = (Conv_Speed << 6) | (Channel << 3);
		ADCON0 |= 0x01;											//turn ADC on
		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x04;									//begin next conversion

		while (ADCON0 & 0x04);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON1 = 0x07;
		ADCON0 = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#define MX_ADC_TOUCH_CASE(ADC, PT, BIT)		\
			case (ADC):							\
			TRIS##PT &= ~(1<<BIT);				\
			PORT##PT |= (1<<BIT);				\
			ADCON0 = (ADC << 3) | 0xC1;			\
			ADCON0 &= ~(1<<0);					\
			PORT##PT &= ~(1<<BIT);				\
			TRIS##PT |= (1<<BIT);				\
			ADCON1 = 0x80;						\
			ADCON0 |= (1<<0);					\
			ADCON0 |= (1<<2);					\
			while (ADCON0 & (1<<2));			\
			result = (ADRESH << 8) | ADRESL;	\
			break;

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		MX_UINT16 result = 0;
		MX_UINT8  temp = ADCON1;
		ADCON1 = 0x87;				// all ports digital

		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
					MX_ADC_TOUCH_CASE(0, A, 0);
			#endif
			#ifdef MX_ADC_CHANNEL_1
					MX_ADC_TOUCH_CASE(1, A, 1);
			#endif
			#ifdef MX_ADC_CHANNEL_2
					MX_ADC_TOUCH_CASE(2, A, 2);
			#endif
			#ifdef MX_ADC_CHANNEL_3
					MX_ADC_TOUCH_CASE(3, A, 3);
			#endif
			#ifdef MX_ADC_CHANNEL_4
					MX_ADC_TOUCH_CASE(4, A, 5);
			#endif
			#ifdef MX_ADC_CHANNEL_5
					MX_ADC_TOUCH_CASE(5, E, 0);
			#endif
			#ifdef MX_ADC_CHANNEL_6
					MX_ADC_TOUCH_CASE(6, E, 1);
			#endif
			#ifdef MX_ADC_CHANNEL_7
					MX_ADC_TOUCH_CASE(7, E, 2);
			#endif
		}
		ADCON1 = temp;
		return result;
	}
	#endif // MX_ADC_TOUCH

#endif


// ADC Type 2 Supported Devices ************************************************************
// 16F88
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_2


	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		if (Vref == 1)											//assign VREF functionality
			st_bit(ADCON1, VCFG1);

		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;		//Pin configured an an input
					ANSEL = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;		//Pin configured an an input
					ANSEL = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;		//Pin configured an an input
					ANSEL = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;		//Pin configured an an input
					ANSEL = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x10;		//Pin configured an an input
					ANSEL = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISB |= 0x40;		//Pin configured an an input
					ANSEL = 0x20;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISB |= 0x80;		//Pin configured an an input
					ANSEL = 0x40;
					break;
			#endif
		}

		if (Conv_Speed > 3)										//assign conversion speed
			st_bit(ADCON1, ADCS2);

		ADCON0 = (Conv_Speed << 6) | (Channel << 3);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x04;									//begin next conversion

		while (ADCON0 & 0x04);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANSEL = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif


// ADC Type 3 Supported Devices ************************************************************
// 16F616, 16F676, 16F677, 16F684, 16F685, 16F687, 16F688, 16F689, 16F690
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_3

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;		//Pin configured an an input
					ANSEL = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;		//Pin configured an an input
					ANSEL = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;		//Pin configured an an input
					ANSEL = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x10;		//Pin configured an an input
					ANSEL = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISC |= 0x01;		//Pin configured an an input
					ANSEL = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISC |= 0x02;		//Pin configured an an input
					ANSEL = 0x20;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISC |= 0x04;		//Pin configured an an input
					ANSEL = 0x40;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISC |= 0x08;		//Pin configured an an input
					ANSEL = 0x80;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISC |= 0x40;		//Pin configured an an input
					ANSELH = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					TRISC |= 0x80;		//Pin configured an an input
					ANSELH = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISB |= 0x10;		//Pin configured an an input
					ANSELH = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					TRISB |= 0x20;		//Pin configured an an input
					ANSELH = 0x08;
					break;
			#endif
		}

		ADCON1 = ((Conv_Speed & 0x07) << 4);					//assign conversion rate
		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		if (Vref == 1)											//assign VREF functionality
			st_bit(ADCON0, VCFG);

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANSEL = 0x00;

		#if defined (MX_ADC_CHANNEL_8) || defined (MX_ADC_CHANNEL_9) || defined (MX_ADC_CHANNEL_10) || defined (MX_ADC_CHANNEL_11)
		  ANSELH = 0x00;
		#endif
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 4 Supported Devices ************************************************************
// 16F737, 16F747, 16F767, 16F777
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_4

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		ADCON2 = 0x00;

		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ADCON1 = 0x0E;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ADCON1 = 0x0D;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ADCON1 = 0x0C;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ADCON1 = 0x0B;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;
					ADCON1 = 0x0A;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISE |= 0x01;
					ADCON1 = 0x09;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISE |= 0x02;
					ADCON1 = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISE |= 0x04;
					ADCON1 = 0x07;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISB |= 0x04;
					ADCON1 = 0x06;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					TRISB |= 0x08;
					ADCON1 = 0x05;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISB |= 0x02;
					ADCON1 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					TRISB |= 0x10;
					ADCON1 = 0x03;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_12
				case (12):
					TRISB |= 0x01;
					ADCON1 = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_13
				case (13):
					TRISB |= 0x20;
					ADCON1 = 0x01;
					break;
			#endif
		}

		if (Vref == 1)											//assign VREF functionality
			st_bit(ADCON1, VCFG0);

		if (Conv_Speed > 3)										//assign conversion speed
			st_bit(ADCON1, ADCS2);

		ADCON0 = (0x01 | (Conv_Speed << 6));					//turn ADC on
		ADCON0 = ADCON0 | ((Channel & 0x07) << 3);
		ADCON0 = ADCON0 | ((Channel & 0x08) >> 2);
		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x04;									//begin next conversion

		while (ADCON0 & 0x04);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON1 = 0x07;
		ADCON0 = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 5 Supported Devices ************************************************************
// 12F615, 12HV615, 12F675, 12F683
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_5

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISIO |= 0x01;
					ANSEL = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISIO |= 0x02;
					ANSEL = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISIO |= 0x04;
					ANSEL = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISIO |= 0x10;
					ANSEL = 0x08;
					break;
			#endif
		}

		ANSEL = ANSEL | ((Conv_Speed & 0x07) << 4);				//assign conversion speed
		ADCON0 = (0x01 | (Channel << 2));						//turn ADC on

		if (Vref == 1)											//assign VREF functionality
			st_bit(ADCON0, VCFG);

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANSEL = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 6 Supported Devices ************************************************************
// 16C72, 16C72A, 16CR72, 16F72, 16C73, 16C73A, 16C73B, 16F73, 16C74, 16C74A, 16C74B, 16F74,
// 16C76, 16F76, 16C77, 16F77, 16C716, 16F716
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_6

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ADCON1 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ADCON1 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ADCON1 = 0x00;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ADCON1 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;
					ADCON1 = 0x00;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISE |= 0x01;
					ADCON1 = 0x00;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISE |= 0x02;
					ADCON1 = 0x00;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISE |= 0x04;
					ADCON1 = 0x00;
					break;
			#endif
		}

		if (Vref != 0)											//assign VREF functionality
			ADCON1 = ADCON1 + 1;

		ADCON0 = (Conv_Speed << 6) | (Channel << 3);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x04;									//begin next conversion

		while (ADCON0 & 0x04);
		if (Sample_Mode)
		{
			iRetVal = (ADRES << 2);								//Mock 10-bit ADC from 8-bit value
		}
		else
			iRetVal = ADRES;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON1 = 0x07;
		ADCON0 = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif



// ADC Type 7 Supported Devices ************************************************************
// 16F883, 16F884, 16F886, 16F887
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_7

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		ADCON1 = 0x00;

		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ANSEL = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ANSEL = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ANSEL = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ANSEL = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;
					ANSEL = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISE |= 0x01;
					ANSEL = 0x20;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISE |= 0x02;
					ANSEL = 0x40;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISE |= 0x04;
					ANSEL = 0x80;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISB |= 0x04;
					ANSELH = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					TRISB |= 0x08;
					ANSELH = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISB |= 0x02;
					ANSELH = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					TRISB |= 0x10;
					ANSELH = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_12
				case (12):
					TRISB |= 0x01;
					ANSELH = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_13
				case (13):
					TRISB |= 0x20;
					ANSELH = 0x20;
					break;
			#endif
		}

		ADCON0 = (Conv_Speed << 6) | (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		if (Vref != 0)											//assign VREF functionality
			st_bit(ADCON1, VCFG0);

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANSEL = 0x00;
		#ifdef _ANSELH_ANS8_POSN
			ANSELH = 0x00;
		#endif
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 8 Supported Devices ************************************************************
// 16F785
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_8

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ANSEL0 = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ANSEL0 = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ANSEL0 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x10;
					ANSEL0 = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISC |= 0x01;
					ANSEL0 = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISC |= 0x02;
					ANSEL0 = 0x20;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISC |= 0x04;
					ANSEL0 = 0x40;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISC |= 0x08;
					ANSEL0 = 0x80;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISC |= 0x40;
					ANSEL1 = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					TRISC |= 0x80;
					ANSEL1 = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISB |= 0x10;
					ANSEL1 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					TRISB |= 0x20;
					ANSEL1 = 0x08;
					break;
			#endif
		}

		ADCON1 = ((Conv_Speed & 0x07) << 4);					//assign conversion rate
		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		if (Vref != 0)											//assign VREF functionality
			st_bit(ADCON0, VCFG);

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANSEL0 = 0x00;
		#ifdef _ANSEL1_ANS8_POSN
			ANSEL1 = 0x00;
		#endif
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 9 Supported Devices ************************************************************
// 16F913, 16F914, 16F916, 16F917, 16F946
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_9

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ANSEL = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ANSEL = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ANSEL = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ANSEL = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;
					ANSEL = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISE |= 0x01;
					ANSEL = 0x20;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISE |= 0x02;
					ANSEL = 0x40;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISE |= 0x04;
					ANSEL = 0x80;
					break;
			#endif
		}

		ADCON1 = ((Conv_Speed & 0x07) << 4);					//assign conversion rate
		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		if (Vref != 0)											//assign VREF functionality
			st_bit(ADCON0, VCFG0);

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANSEL = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 10 Supported Devices ***********************************************************
// 12C671, 12C672, 12CE673, 12CE674
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_10

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISIO |= 0x01;
					if (Vref == 0)
						ADCON1 = 0x06;
					else
						ADCON1 = 0x05;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISIO |= 0x02;
					ADCON1 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISIO |= 0x04;
					if (Vref == 0)
						ADCON1 = 0x02;
					else
						ADCON1 = 0x03;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISIO |= 0x08;
					if (Vref == 0)
						ADCON1 = 0x00;
					else
						ADCON1 = 0x01;
					break;
			#endif
		}

		ADCON0 = (Conv_Speed << 6) | (Channel << 3);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRES << 2);								//Mock 10-bit ADC from 8-bit value
		}
		else
			iRetVal = ADRES;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON1 = 0x07;
		ADCON0 = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 11 Supported Devices ***********************************************************
// 16C717, 16C770, 16C771
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_11

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					#ifdef _ANSEL_ANS0_POSN
					ANSEL = 0x01;
					#endif
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					#ifdef _ANSEL_ANS0_POSN
					ANSEL = 0x02;
					#endif
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					#ifdef _ANSEL_ANS0_POSN
					ANSEL = 0x04;
					#endif
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					#ifdef _ANSEL_ANS0_POSN
					ANSEL = 0x08;
					#endif
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISB |= 0x01;
					#ifdef _ANSEL_ANS0_POSN
					ANSEL = 0x10;
					#endif
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISB |= 0x02;
					#ifdef _ANSEL_ANS0_POSN
					ANSEL = 0x20;
					#endif
					break;
			#endif
		}

		ADCON1 = 0x00;

		if (Vref != 0)											//assign VREF functionality
		{
			st_bit(ADCON1, VCFG0);
			st_bit(ADCON1, VCFG1);
		}

		ADCON0 = (Conv_Speed << 6) | (Channel << 3);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x04;									//begin next conversion

		while (ADCON0 & 0x04);
		if (Sample_Mode)
		{
		  #ifdef MX_ADC_BITS_12
			iRetVal = (ADRESH << 4);							//12-bit ADC
			iRetVal = iRetVal | (ADRESL >> 4);
		  #else
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		  #endif
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		#ifdef _ANSEL_ANS0_POSN
		  ANSEL = 0x00;
		#else
		  ADCON1 = 0x0F;										//Restore Digital I/O mode
		#endif
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 12 Supported Devices ***********************************************************
// 18F6310, 18F6390, 18F6410, 18F6490, 18F6520, 18F6527, 18F6585, 18F66J60, 18F66J65,
// 18F6620, 18F6622, 18F6627, 18F6680, 18F67J60, 18F6720, 18F6722, 18F8310, 18F8390,
// 18F8410, 18F8490, 18F8520, 18F8527, 18F8585, 18F86J60, 18F86J65, 18F8620, 18F8622,
// 18F8627, 18F8680, 18F87J60, 18F8720, 18F8722, 18F96J60, 18F96J65, 18F97J60
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_12

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ADCON1 = 0x0E;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ADCON1 = 0x0D;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ADCON1 = 0x0C;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ADCON1 = 0x0B;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;
					ADCON1 = 0x0A;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISF |= 0x01;
					ADCON1 = 0x09;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISF |= 0x02;
					ADCON1 = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISF |= 0x04;
					ADCON1 = 0x07;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISF |= 0x08;
					ADCON1 = 0x06;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					TRISF |= 0x10;
					ADCON1 = 0x05;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISF |= 0x20;;
					ADCON1 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					TRISF |= 0x40;
					ADCON1 = 0x03;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_12
				case (12):
					TRISH |= 0x10;
					ADCON1 = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_13
				case (13):
					TRISH |= 0x20;
					ADCON1 = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_14
				case (14):
					TRISH |= 0x40;
					ADCON1 = 0x00;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_15
				case (15):
					TRISH |= 0x80;
					ADCON1 = 0x00;
					break;
			#endif
		}

		if (Vref != 0)											//assign VREF functionality
			st_bit(ADCON1, VCFG0);

		ADCON2 = Conv_Speed & 0x07;								//assign conversion rate
		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ADCON1 = 0x0f;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 13 Supported Devices ***********************************************************
// 18F2220, 18F2221, 18F2320, 18F2321, 18F24J10, 18F2410, 18F2420, 18F2423, 18F2450,
// 18F2455, 18F2480, 18F25J10, 18F2510, 18F2515, 18F2520, 18F2523, 18F2525, 18F2550,
// 18F2580, 18F2585, 18F2610, 18F2620, 18F2680, 18F4220, 18F4221, 18F4320, 18F4321,
// 18F44J10, 18F4410, 18F4420, 18F4423, 18F4450, 18F4455, 18F4480, 18F45J10, 18F4510,
// 18F4515, 18F4520, 18F4523, 18F4525, 18F4550, 18F4580, 18F4585, 18F4610, 18F4620,
// 18F4680, 18F4682, 18F4685
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_13



	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ADCON1 = 0x0E;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ADCON1 = 0x0D;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ADCON1 = 0x0C;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ADCON1 = 0x0B;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;
					ADCON1 = 0x0A;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISE |= 0x01;
					ADCON1 = 0x09;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISE |= 0x02;
					ADCON1 = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISE |= 0x04;
					ADCON1 = 0x07;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISB |= 0x04;
					ADCON1 = 0x06;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					TRISB |= 0x08;
					ADCON1 = 0x05;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISB |= 0x02;
					ADCON1 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					TRISB |= 0x10;
					ADCON1 = 0x03;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_12
				case (12):
					TRISB |= 0x01;
					ADCON1 = 0x02;
					break;
			#endif
		}

		ADCON2 = Conv_Speed & 0x07;								//assign conversion rate

		if (Vref != 0)											//assign VREF functionality
			st_bit(ADCON1, VCFG0);								//BR changed from ADCON0 05/12

		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
		  #ifdef MX_ADC_BITS_12
			iRetVal = (ADRESH << 4);							//12-bit ADC
			iRetVal = iRetVal | (ADRESL >> 4);
		  #else
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		  #endif
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ADCON1 = 0x0f;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 14 Supported Devices ***********************************************************
// 18F2331, 18F2431, 18F4331, 18F4431
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_14

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ADCON0 = 0x00;
					ANSEL0 = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ADCON0 = 0x04;
					ANSEL0 = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ADCON0 = 0x08;
					ANSEL0 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ADCON0 = 0x0C;
					ANSEL0 = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x10;
					ADCON0 = 0x00;
					ADCHS = 0x01;
					ANSEL0 = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISA |= 0x20;
					ADCON0 = 0x04;
					ADCHS = 0x10;
					ANSEL0 = 0x20;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISE |= 0x01;
					ADCON0 = 0x08;
					ADCHS = 0x04;
					ANSEL0 = 0x40;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISE |= 0x02;
					ADCON0 = 0x0C;
					ADCHS = 0x40;
					ANSEL0 = 0x80;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISB |= 0x04;
					ADCON0 = 0x00;
					ADCHS = 0x02;
					ANSEL1 = 0x01;
					break;
			#endif
		}

		ADCON1 = 0x00;											//set up ADC conversion
		ADCON2 = Conv_Speed & 0x07;
		ADCON3 = 0x00;

		ADCON0 = ADCON0 | 0x01;									//turn ADC on

		if (Vref != 0)											//assign VREF functionality
			st_bit(ADCON1, VCFG0);

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANSEL0 = 0x00;
		#ifdef ANSEL1_ANS8_POSN
			ANSEL1 = 0x00;
		#endif
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 15 Supported Devices ***********************************************************
// 18F1220, 18F1320
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_15

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ADCON1 = 0x7E;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ADCON1 = 0x7D;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ADCON1 = 0x7B;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ADCON1 = 0x77;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISB |= 0x01;
					ADCON1 = 0x6F;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISB |= 0x02;
					ADCON1 = 0x5F;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISB |= 0x10;
					ADCON1 = 0x3F;
					break;
			#endif
		}

		ADCON2 = Conv_Speed & 0x07;								//assign conversion rate
		ADCON0 = (Channel << 2);

		if (Vref != 0)											//assign VREF functionality
			st_bit(ADCON0, VCFG0);

		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ADCON1 = 0x7f;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 16 Supported Devices ***********************************************************
// 18F242, 18F2439, 18F248, 18F252, 18F2539, 18F258, 18F442, 18F4439, 18F448, 18F452,
// 18F4539, 18F458
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_16

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					if (Vref != 0)
						ADCON1 = 0x05;
					else
						ADCON1 = 0x0E;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					if (Vref != 0)
						ADCON1 = 0x05;
					else
						ADCON1 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					if (Vref != 0)
						ADCON1 = 0x03;
					else
						ADCON1 = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ADCON1 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;
					if (Vref != 0)
						ADCON1 = 0x03;
					else
						ADCON1 = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISE |= 0x01;
					if (Vref != 0)
						ADCON1 = 0x0A;
					else
						ADCON1 = 0x09;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISE |= 0x02;;
					if (Vref != 0)
						ADCON1 = 0x01;
					else
						ADCON1 = 0x00;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISE |= 0x04;
					if (Vref != 0)
						ADCON1 = 0x01;
					else
						ADCON1 = 0x00;
					break;
			#endif
		}

		if (Conv_Speed > 3)										//assign conversion speed
			st_bit(ADCON1, ADCS2);

		ADCON0 = (Conv_Speed << 6) | (Channel << 3);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x04;									//begin next conversion

		while (ADCON0 & 0x04);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ADCON1 = 0x07;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 17 Supported Devices ***********************************************************
// 18F1230, 18F1330
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_17

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x40;
					break;
			#endif
		}

		ADCON2 = Conv_Speed & 0x07;
		ADCON1 = (0x01 << Channel);

		if (Vref != 0)											//assign VREF functionality
			st_bit(ADCON1, VCFG0);

		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01; 										//turn ADC on
		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ADCON1 = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 18 Supported Devices ***********************************************************
// 16F722, 16F723, 16F724, 16F726, 16F727, 16F1933, 16F1934, 16F1936, 16F1937, 16F1939
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_18

	#ifndef ADREF1
		#define ADREF1 ADPREF1
	#endif

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ANSELA = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ANSELA = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ANSELA = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ANSELA = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;
					ANSELA = 0x20;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISE |= 0x01;
					ANSELE = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISE |= 0x02;
					ANSELE = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISE |= 0x04;
					ANSELE = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISB |= 0x04;
					ANSELB = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					TRISB |= 0x08;
					ANSELB = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISB |= 0x02;
					ANSELB = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					TRISB |= 0x10;
					ANSELB = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_12
				case (12):
					TRISB |= 0x01;
					ANSELB = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_13
				case (13):
					TRISB |= 0x20;
					ANSELB = 0x20;
					break;
			#endif
		}

		ADCON1 = (Conv_Speed & 0x07) << 4;						//assign conversion rate

		if (Vref != 0)											//assign VREF functionality
			ADCON1 = ADCON1 | (Vref & 0x03);					//Mod to allow FVR as VREF

		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			#ifdef _ADRESH_ADRESH_POSN
			  #ifdef MX_ADC_BITS_12
				iRetVal = (ADRESH << 4);						//12-bit ADC
				iRetVal = iRetVal | (ADRESL >> 4);
			  #else
				iRetVal = (ADRESH << 2);	            		//10-bit ADC
				iRetVal = iRetVal | (ADRESL >> 6);
			  #endif
			#else
				iRetVal = (ADRES << 2);							//Mock 10-bit ADC from 8-bit value
			#endif
		}
		else
			#ifdef _ADRESH_ADRESH_POSN
				iRetVal = ADRESH;								//8-bit ADC
            #else
				iRetVal = ADRES;
		    #endif

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANSELA = 0x00;
		ANSELB = 0x00;

		#if defined (MX_ADC_CHANNEL_5) || defined (MX_ADC_CHANNEL_6) || defined (MX_ADC_CHANNEL_7)
		  ANSELE = 0x00;
		#endif
	}

	#ifdef MX_ADC_TOUCH


	#ifdef _ADRESH_ADRESH_POSN
	  #define MX_ADC_TOUCH_CASE(ADC, PORT, BIT)	\
			case (ADC):							\
			FCP_TRIS_##PORT &= ~(1<<BIT);		\
			FCP_LAT_##PORT |= (1<<BIT);			\
			ANSEL##PORT |= (1<<BIT);			\
			ADCON0 = (ADC << 2) | 1;			\
			ADCON0 &= (1<<0);					\
			FCP_LAT_##PORT &= ~(1<<BIT);		\
			FCP_TRIS_##PORT |= (1<<BIT);		\
			ADCON0 = (ADC << 2) | 1;			\
			ADCON0 = (ADC << 2) | 3;			\
			while (ADCON0 & (1<<1));			\
			ANSEL##PORT &= ~(1<<BIT);			\
			return (ADRESH << 8) | ADRESL;
	#else
	  #define MX_ADC_TOUCH_CASE(ADC, PORT, BIT)	\
			case (ADC):							\
			FCP_TRIS_##PORT &= ~(1<<BIT);		\
			FCP_LAT_##PORT |= (1<<BIT);			\
			ANSEL##PORT |= (1<<BIT);			\
			ADCON0 = (ADC << 2) | 1;			\
			ADCON0 &= (1<<0);					\
			FCP_LAT_##PORT &= ~(1<<BIT);		\
			FCP_TRIS_##PORT |= (1<<BIT);		\
			ADCON0 = (ADC << 2) | 1;			\
			ADCON0 = (ADC << 2) | 3;			\
			while (ADCON0 & (1<<1));			\
			ANSEL##PORT &= ~(1<<BIT);			\
			return (ADRES << 2);
	#endif


	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		ADCON1 = 0xf0;						// Right justified result and set FRC clock mode

		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
					MX_ADC_TOUCH_CASE(0, A, 0);
			#endif
			#ifdef MX_ADC_CHANNEL_1
					MX_ADC_TOUCH_CASE(1, A, 1);
			#endif
			#ifdef MX_ADC_CHANNEL_2
					MX_ADC_TOUCH_CASE(2, A, 2);
			#endif
			#ifdef MX_ADC_CHANNEL_3
					MX_ADC_TOUCH_CASE(3, A, 3);
			#endif
			#ifdef MX_ADC_CHANNEL_4
					MX_ADC_TOUCH_CASE(4, A, 5);
			#endif
			#ifdef MX_ADC_CHANNEL_5
					MX_ADC_TOUCH_CASE(5, A, 0);
			#endif
			#ifdef MX_ADC_CHANNEL_6
					MX_ADC_TOUCH_CASE(6, E, 1);
			#endif
			#ifdef MX_ADC_CHANNEL_7
					MX_ADC_TOUCH_CASE(7, E, 2);
			#endif
			#ifdef MX_ADC_CHANNEL_8
					MX_ADC_TOUCH_CASE(8, B, 2);
			#endif
			#ifdef MX_ADC_CHANNEL_9
					MX_ADC_TOUCH_CASE(9, B, 3);
			#endif
			#ifdef MX_ADC_CHANNEL_10
					MX_ADC_TOUCH_CASE(10, B, 1);
			#endif
			#ifdef MX_ADC_CHANNEL_11
					MX_ADC_TOUCH_CASE(11, B, 4);
			#endif
			#ifdef MX_ADC_CHANNEL_12
					MX_ADC_TOUCH_CASE(12, B, 0);
			#endif
			#ifdef MX_ADC_CHANNEL_13
					MX_ADC_TOUCH_CASE(13, B, 5);
			#endif
		}
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 19 Supported Devices ***********************************************************
// 18F13K50, 18F14K50, 18LF13K50, 18LF14K50
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_19

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		ADCON1 = 0;

		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ANSEL = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ANSEL = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ANSEL = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x10;
					ANSEL = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISC |= 0x01;
					ANSEL = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISC |= 0x02;
					ANSEL = 0x20;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISC |= 0x04;
					ANSEL = 0x40;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISC |= 0x08;
					ADCON1 = 0x80;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISC |= 0x40;
					ANSELH = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					TRISC |= 0x80;
					ANSELH = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISB |= 0x10;
					ANSELH = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					TRISB |= 0x20;
					ANSELH = 0x08;
					break;
			#endif
		}

		ADCON2 = Conv_Speed & 0x07;								//assign conversion rate

		if (Vref != 0)											//assign VREF functionality
			ADCON1 |= ((Vref & 0x03) << 2);						//Mod to allow FVR as VREF

		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANSEL = 0;
		#ifdef _ANSELH_ANS8_POSN
			ANSELH = 0;
		#endif
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 20 Supported Devices ***********************************************************
// 18F23K20, 18F24K20, 18F25K20, 18F26K20, 18F43K20, 18F44K20, 18F45K20, 18F16K20
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_20

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		ADCON1 = 0;

		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ANSEL = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ANSEL = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ANSEL = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ANSEL = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;
					ANSEL = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISE |= 0x01;
					ANSEL = 0x20;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISE |= 0x02;
					ANSEL = 0x40;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISE |= 0x04;
					ADCON1 = 0x80;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISB |= 0x04;
					ANSELH = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					TRISB |= 0x08;
					ANSELH = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISB |= 0x02;
					ANSELH = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					TRISB |= 0x10;
					ANSELH = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_12
				case (12):
					TRISB |= 0x01;
					ANSELH = 0x10;
					break;
			#endif
		}

		ADCON2 = Conv_Speed & 0x07;								//assign conversion rate

		if (Vref != 0)											//assign VREF functionality
			st_bit(ADCON1, VCFG0);

		ADCON0 = (Channel << 2);								//turn ADC on
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANSEL = 0;
		#ifdef _ANSELH_ANS8_POSN
			ANSELH = 0;
		#endif
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 21 Supported Devices ***********************************************************
// 18F2xJ11, 18F4xJ11
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_21

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ANCON0 = 0xFE;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ANCON0 = 0xFD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ANCON0 = 0xFB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ANCON0 = 0xF7;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;
					ANCON0 = 0xEF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISE |= 0x01;
					ANCON0 = 0xDF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISE |= 0x02;
					ANCON0 = 0xBF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISE |= 0x04;
					ANCON0 = 0x7F;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISB |= 0x04;
					ANCON1 = 0x1E;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					TRISB |= 0x08;
					ANCON1 = 0x1D;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISB |= 0x02;
					ANCON1 = 0x1B;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					TRISB |= 0x10;
					ANCON1 = 0x17;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_12
				case (12):
					TRISB |= 0x01;
					ANCON1 = 0x0F;
					break;
			#endif
		}

		ADCON1 = Conv_Speed & 0x07;								//assign conversion rate

		ADCON0 = (Channel << 2);

		if (Vref != 0)											//assign VREF functionality
			st_bit(ADCON0, VCFG0);

		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANCON0 = 0xFF;
		ANCON1 = 0x1F;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 22 Supported Devices ***********************************************************
// 10F220, 10F222
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_22

	//10F320 & 10F322 have ADCON register instead of ADCON0
	#ifdef _ADCON_ADON_POSN
		#define ADCON0 ADCON
	#endif

	#ifdef MX_10F_TRIS
		#define FC_CAL_ADC_Enable_1(Channel, Conv_Speed, Vref, T_Charge)\
		{\
			if (Channel == 0)\
			{\
				asm("movf 1,w");\
				asm("tris 6");\
				ADCON0 = 0x40;\
			}\
			if (Channel == 1)\
			{\
				asm("movf 2,w");\
				asm("tris 6");\
				ADCON0 = 0x84;\
			}\
			ADCON0 = ADCON0 | 0x01;\
			delay_us(T_Charge);\
		}
	#else
		#define FC_CAL_ADC_Enable_1(Channel, Conv_Speed, Vref, T_Charge)\
		{\
			if (Channel == 0)\
			{\
				TRISA |= 0x01;\
				ANSELA = 0x01;\
				ADCON0 = 0x00;\
			}\
			if (Channel == 1)\
			{\
				TRISA |= 0x02;\
				ANSELA = 0x02;\
				ADCON0 = 0x04;\
			}\
			if (Channel == 2)\
			{\
				TRISA |= 0x04;\
				ANSELA = 0x04;\
				ADCON0 = 0x08;\
			}\
			ADCON0 = ADCON0 | (Conv_Speed << 5);\
			ADCON0 = ADCON0 | 0x01;\
			delay_us(T_Charge);\
		}
	#endif

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;

		while (ADCON0 & 0x02);
		if (Sample_Mode)
			iRetVal = (ADRES << 2);								//10-bit ADC
		else
			iRetVal = ADRES;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;											//Reset ADC Registers

		#ifndef MX_10F_TRIS										//10F32x only
			ANSELA = 0;											//Digital IO Mode
		#endif
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH

#endif


// ADC Type 23 Supported Devices ***********************************************************
// 16F1826, 16F1827
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_23

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ANSELA = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ANSELA = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ANSELA = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ANSELA = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x10;
					ANSELA = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISB |= 0x40;
					ANSELB = 0x40;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISB |= 0x80;
					ANSELB = 0x80;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISB |= 0x20;
					ANSELB = 0x20;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISB |= 0x10;
					ANSELB = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					TRISB |= 0x08;
					ANSELB = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISB |= 0x04;
					ANSELB = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					TRISB |= 0x02;
					ANSELB = 0x02;
					break;
			#endif
		}

		ADCON1 = (Conv_Speed & 0x07) << 4;						//assign conversion rate

		if (Vref != 0)											//assign VREF functionality
			ADCON1 = ADCON1 | (Vref & 0x03);					//Mod to allow FVR as VREF

		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);

		if (Sample_Mode)
		{
		  #ifdef _ADRESH_ADRESH_POSN
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRES >> 6);
		  #else
		  	iRetVal = ADRES << 2;								//Mock 10-bit ADC from 8-bit value
		  #endif
		}
		else
		{
			#ifdef _ADRESH_ADRESH_POSN
				iRetVal = ADRESH;								//8-bit ADC
			#else
				iRetVal = ADRES;
			#endif
		}

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANSELA = 0x00;

		#if defined (MX_ADC_CHANNEL_5) || defined (MX_ADC_CHANNEL_6) || defined (MX_ADC_CHANNEL_7) || defined (MX_ADC_CHANNEL_8) || defined (MX_ADC_CHANNEL_9) || defined (MX_ADC_CHANNEL_10) || defined (MX_ADC_CHANNEL_11)
		  ANSELB = 0x00;
		#endif
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 24 Supported Devices ***********************************************************
// 18F65J50, 18F66J50, 18F66J55, 18F67J50, 18F85J50, 18F86J50, 18F86J55, 18F87J50
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_24

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ANCON0 &= 0b11111110;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ANCON0 &= 0b11111101;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ANCON0 &= 0b11111011;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ANCON0 &= 0b11110111;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;
					ANCON0 &= 0b11101111;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISF |= 0x04;
					ANCON0 &= 0b01111111;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISF |= 0x20;
					ANCON1 &= 0b11111011;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					TRISF |= 0x40;
					ANCON1 &= 0b11110111;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_12
				case (12):
					TRISH |= 0x10;
					ANCON1 &= 0b11101111;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_13
				case (13):
					TRISH |= 0x20;
					ANCON1 &= 0b11011111;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_14
				case (14):
					TRISH |= 0x40;
					ANCON1 &= 0b10111111;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_15
				case (15):
					TRISH |= 0x80;
					ANCON1 &= 0b01111111;
					break;
			#endif
		}

		ADCON1 = (Conv_Speed & 0x07);
		ADCON0 = (Channel << 2);

		if (Vref != 0)											//assign VREF functionality
			st_bit(ADCON0, VCFG0);

		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANCON0 = 0xFF;
		ANCON1 = 0xFF;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 25 Supported Devices ***********************************************************
// 18F66J93, 18F67J93, 18F86J93, 18F87J93, 18F66J90, 18F67J90, 18F86J90, 18F87J90
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_25

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ADCON1 = 0x0E;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ADCON1 = 0x0D;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ADCON1 = 0x0C;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ADCON1 = 0x0B;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;
					ADCON1 = 0x0A;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISF |= 0x80;
					ADCON1 = 0x09;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISF |= 0x02;
					ADCON1 = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISF |= 0x04;
					ADCON1 = 0x07;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISF |= 0x08;
					ADCON1 = 0x06;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					TRISF |= 0x10;
					ADCON1 = 0x05;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISF |= 0x20;
					ADCON1 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					TRISF |= 0x40;
					ADCON1 = 0x03;
					break;
			#endif
		}

		ADCON2 = Conv_Speed & 0x07;

		if (Vref != 0)											//assign VREF functionality
			st_bit(ADCON1, VCFG0);

		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ADCON1 = 0x0f;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 26 Supported Devices ***********************************************************
// 12F1822, 16F1823, 16F1824, 16F1825, 16F1828, 16F1829
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_26

	MX_UINT8 * ANSEL_reg;					//ANSEL register pointer
	MX_UINT8 tris_mask;

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					tris_mask = 0x01;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					tris_mask = 0x02;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					tris_mask = 0x04;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					tris_mask = 0x10;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					tris_mask = 0x01;
					TRISC |= tris_mask;
					ANSEL_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					tris_mask = 0x02;
					TRISC |= tris_mask;
					ANSEL_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					tris_mask = 0x04;
					TRISC |= tris_mask;
					ANSEL_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					tris_mask = 0x08;
					TRISC |= tris_mask;
					ANSEL_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					tris_mask = 0x40;
					TRISC |= tris_mask;
					ANSEL_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					tris_mask = 0x80;
					TRISC |= tris_mask;
					ANSEL_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					tris_mask = 0x10;
					TRISB |= tris_mask;
					ANSEL_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					tris_mask = 0x20;
					TRISB |= tris_mask;
					ANSEL_reg = &ANSELB;
					break;
			#endif
		}

		ADCON1 = (Conv_Speed & 0x07) << 4;						//assign conversion rate

		if (Vref != 0)											//assign VREF functionality
			ADCON1 = ADCON1 | (Vref & 0x03);					//Mod to allow FVR as VREF

		*ANSEL_reg = *ANSEL_reg | tris_mask;
		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		*ANSEL_reg = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 27 Supported Devices ***********************************************************
// 16F1946, 16F1947
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_27

	MX_UINT8 * ANSEL_reg;					//ANSEL register pointer
	MX_UINT8 tris_mask;

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					tris_mask = 0x01;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					tris_mask = 0x02;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					tris_mask = 0x04;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					tris_mask = 0x08;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					tris_mask = 0x20;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					tris_mask = 0x80;
					TRISF |= tris_mask;
					ANSEL_reg = &ANSELF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					tris_mask = 0x02;
					TRISF |= tris_mask;
					ANSEL_reg = &ANSELF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					tris_mask = 0x04;
					TRISF |= tris_mask;
					ANSEL_reg = &ANSELF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					tris_mask = 0x08;
					TRISF |= tris_mask;
					ANSEL_reg = &ANSELF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					tris_mask = 0x10;
					TRISF |= tris_mask;
					ANSEL_reg = &ANSELF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					tris_mask = 0x20;
					TRISF |= tris_mask;
					ANSEL_reg = &ANSELF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					tris_mask = 0x40;
					TRISF |= tris_mask;
					ANSEL_reg = &ANSELF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_12
				case (12):
					tris_mask = 0x10;
					TRISG |= tris_mask;
					ANSEL_reg = &ANSELG;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_13
				case (13):
					tris_mask = 0x08;
					TRISG |= tris_mask;
					ANSEL_reg = &ANSELG;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_14
				case (14):
					tris_mask = 0x04;
					TRISG |= tris_mask;
					ANSEL_reg = &ANSELG;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_15
				case (15):
					tris_mask = 0x02;
					TRISG |= tris_mask;
					ANSEL_reg = &ANSELG;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_16
				case (16):
					tris_mask = 0x01;
					TRISG |= tris_mask;
					ANSEL_reg = &ANSELG;
					break;
			#endif
		}

		*ANSEL_reg = *ANSEL_reg | tris_mask;

		ADCON1 = (Conv_Speed & 0x07) << 4;						//assign conversion rate

		if (Vref != 0)											//assign VREF functionality
			ADCON1 = ADCON1 | (Vref & 0x03);					//Mod to allow FVR as VREF

		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		*ANSEL_reg = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 28 Supported Devices ***********************************************************
// 18F65K22, 18F66K22, 18F67K22, 18F85K22, 18F86K22, 18F87K22,
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_28

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ANCON0 = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ANCON0 = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ANCON0 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ANCON0 = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;
					ANCON0 = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISF |= 0x80;
					ANCON0 = 0x20;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISF |= 0x02;
					ANCON0 = 0x40;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISF |= 0x04;
					ANCON0 = 0x80;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISF |= 0x08;
					ANCON1 = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					TRISF |= 0x10;
					ANCON1 = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISF |= 0x20;
					ANCON1 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					TRISF |= 0x40;
					ANCON1 = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_12
				case (12):
					TRISH |= 0x10;
					ANCON1 = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_13
				case (13):
					TRISH |= 0x20;
					ANCON1 = 0x20;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_14
				case (14):
					TRISH |= 0x40;
					ANCON1 = 0x40;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_15
				case (15):
					TRISH |= 0x80;
					ANCON1 = 0x80;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_16
				case (16):
					TRISG |= 0x10;
					ANCON2 = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_17
				case (17):
					TRISG |= 0x08;
					ANCON2 = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_18
				case (18):
					TRISG |= 0x04;
					ANCON2 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_19
				case (19):
					TRISG |= 0x02;
					ANCON2 = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_20
				case (20):
					TRISH |= 0x08;
					ANCON2 = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_21
				case (21):
					TRISH |= 0x04;
					ANCON2 = 0x20;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_22
				case (22):
					TRISH |= 0x02;
					ANCON2 = 0x40;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_23
				case (23):
					TRISH |= 0x01;
					ANCON2 = 0x80;
					break;
			#endif
		}

		ADCON2 = Conv_Speed & 0x07;

		if (Vref != 0)											//assign VREF functionality
			ADCON1 = ADCON1 | ((Vref & 0x03) << 4);				//Mod to allow FVR as VREF

		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 4);							//12-bit ADC
			iRetVal = iRetVal | (ADRESL >> 4);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANCON0 = 0x00;
		#ifdef _ANCON1_ANSEL8_POSN
			ANCON1 = 0x00;
		#endif
		#ifdef _ANCON2_ANSEL16_POSN
			ANCON2 = 0x00;
		#endif
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 29 Supported Devices ***********************************************************
// 18F23K22, 18F24K22, 18F25K22, 18F26K22, 18F43K22, 18F44K22, 18F45K22, 18F46K22,
// 18LF23K22, 18LF24K22, 18LF25K22, 18LF26K22, 18LF43K22, 18LF44K22, 18LF45K22, 18LF46K22,
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_29

	volatile MX_UINT8 * ANSEL_reg;					//ANSEL register pointer
	MX_UINT8 tris_mask;

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					tris_mask = 0x01;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					tris_mask = 0x02;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					tris_mask = 0x04;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					tris_mask = 0x08;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					tris_mask = 0x20;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					tris_mask = 0x01;
					TRISE |= tris_mask;
					ANSEL_reg = &ANSELE;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					tris_mask = 0x02;
					TRISE |= tris_mask;
					ANSEL_reg = &ANSELE;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					tris_mask = 0x04;
					TRISE |= tris_mask;
					ANSEL_reg = &ANSELE;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					tris_mask = 0x04;
					TRISB |= tris_mask;
					ANSEL_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					tris_mask = 0x08;
					TRISB |= tris_mask;
					ANSEL_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					tris_mask = 0x02;
					TRISB |= tris_mask;
					ANSEL_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					tris_mask = 0x10;
					TRISB |= tris_mask;
					ANSEL_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_12
				case (12):
					tris_mask = 0x01;
					TRISB |= tris_mask;
					ANSEL_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_13
				case (13):
					tris_mask = 0x20;
					TRISB |= tris_mask;
					ANSEL_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_14
				case (14):
					tris_mask = 0x04;
					TRISC |= tris_mask;
					ANSEL_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_15
				case (15):
					tris_mask = 0x08;
					TRISC |= tris_mask;
					ANSEL_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_16
				case (16):
					tris_mask = 0x10;
					TRISC |= tris_mask;
					ANSEL_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_17
				case (17):
					tris_mask = 0x20;
					TRISC |= tris_mask;
					ANSEL_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_18
				case (18):
					tris_mask = 0x40;
					TRISC |= tris_mask;
					ANSEL_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_19
				case (19):
					tris_mask = 0x80;
					TRISC |= tris_mask;
					ANSEL_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_20
				case (20):
					tris_mask = 0x01;
					TRISD |= tris_mask;
					ANSEL_reg = &ANSELD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_21
				case (21):
					tris_mask = 0x02;
					TRISD |= tris_mask;
					ANSEL_reg = &ANSELD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_22
				case (22):
					tris_mask = 0x04;
					TRISD |= tris_mask;
					ANSEL_reg = &ANSELD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_23
				case (23):
					tris_mask = 0x08;
					TRISD |= tris_mask;
					ANSEL_reg = &ANSELD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_24
				case (24):
					tris_mask = 0x10;
					TRISD |= tris_mask;
					ANSEL_reg = &ANSELD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_25
				case (25):
					tris_mask = 0x20;
					TRISD |= tris_mask;
					ANSEL_reg = &ANSELD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_26
				case (26):
					tris_mask = 0x40;
					TRISD |= tris_mask;
					ANSEL_reg = &ANSELD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_27
				case (27):
					tris_mask = 0x80;
					TRISD |= tris_mask;
					ANSEL_reg = &ANSELD;
					break;
			#endif
		}

		*ANSEL_reg = *ANSEL_reg | tris_mask;

		ADCON2 = Conv_Speed & 0x07;

		if (Vref != 0)											//assign VREF functionality
			ADCON1 = ADCON1 | ((Vref & 0x03) << 2);				//Mod to allow FVR as VREF

		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		*ANSEL_reg = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 30 Supported Devices ************************************************************
// 16F870, 16F871, 16F872, 16F873, 16F874, 16F876, 16F877
// *******************************************************************************************/

#ifdef MX_ADC_TYPE_30

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					if (Vref == 0)
						ADCON1 = 0x0E;
					else
						ADCON1 = 0x05;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					if (Vref == 0)
						ADCON1 = 0x04;
					else
						ADCON1 = 0x05;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					if (Vref == 0)
						ADCON1 = 0x02;
					else
						ADCON1 = 0x03;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					if (Vref == 0)
						ADCON1 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;
					if (Vref == 0)
						ADCON1 = 0x02;
					else
						ADCON1 = 0x03;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISE |= 0x01;
					if (Vref == 0)
						ADCON1 = 0x09;
					else
						ADCON1 = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISE |= 0x02;
					if (Vref == 0)
						ADCON1 = 0x00;
					else
						ADCON1 = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISE |= 0x04;
					if (Vref == 0)
						ADCON1 = 0x00;
					else
						ADCON1 = 0x01;
					break;
			#endif
		}

		ADCON0 = (Conv_Speed << 6) | (Channel << 3);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x04;									//begin next conversion

		while (ADCON0 & 0x04);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON1 = 0x07;
		ADCON0 = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 31 Supported Devices ************************************************************
// 12F510, 16F506
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_31

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		ADCON0 = (Conv_Speed << 4) | (Channel << 2);
		ADCON0 |= 0xC1;											//turn ADC on
		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);

		iRetVal = ADRES;										//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 32 Supported Devices ***********************************************************
// 18F2xK80, 18F4xK80, 18F6xK80
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_32

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ANCON0 = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ANCON0 = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ANCON0 = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x08;
					ANCON0 = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISA |= 0x20;
					ANCON0 = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISE |= 0x01;
					ANCON0 = 0x20;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISE |= 0x02;
					ANCON0 = 0x40;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISE |= 0x04;
					ANCON0 = 0x80;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISB |= 0x02;
					ANCON1 = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					TRISB |= 0x10;
					ANCON1 = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISB |= 0x01;
					ANCON1 = 0x04;
					break;
			#endif
		}

		ADCON1 = 0;
		ADCON2 = Conv_Speed & 0x07;								//assign conversion rate

		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		if (Vref != 0)											//assign VREF functionality
			ADCON1 = ADCON1 | ((Vref & 0x03) << 4);				//Mod to allow FVR as VREF

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 4);							//12-bit ADC
			iRetVal = iRetVal | (ADRESL >> 4);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANCON0 = 0x00;
		ANCON1 = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 33 Supported Devices ***********************************************************
// 16F183xx
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_33

volatile MX_UINT8 * ansel_reg;					//TRIS register pointer

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		if (Channel < 8)
		{
			#if defined (MX_ADC_CHANNEL_0) || defined (MX_ADC_CHANNEL_1) || defined (MX_ADC_CHANNEL_2) || defined (MX_ADC_CHANNEL_3) || defined (MX_ADC_CHANNEL_4) || defined (MX_ADC_CHANNEL_5) || defined (MX_ADC_CHANNEL_6) || defined (MX_ADC_CHANNEL_7)
				TRISA |= 1 << (Channel & 0x07);
				ansel_reg = &ANSELA;
			#endif
		}
		else if (Channel < 16)
		{
			#if defined (MX_ADC_CHANNEL_8) || defined (MX_ADC_CHANNEL_9) || defined (MX_ADC_CHANNEL_10) || defined (MX_ADC_CHANNEL_11) || defined (MX_ADC_CHANNEL_12) || defined (MX_ADC_CHANNEL_13) || defined (MX_ADC_CHANNEL_14) || defined (MX_ADC_CHANNEL_15)
				TRISB |= 1 << (Channel & 0x07);
				ansel_reg = &ANSELB;
			#endif
		}
		else if (Channel < 24)
		{
			#if defined (MX_ADC_CHANNEL_16) || defined (MX_ADC_CHANNEL_17) || defined (MX_ADC_CHANNEL_18) || defined (MX_ADC_CHANNEL_19) || defined (MX_ADC_CHANNEL_20) || defined (MX_ADC_CHANNEL_21) || defined (MX_ADC_CHANNEL_22) || defined (MX_ADC_CHANNEL_23)
				TRISC |= 1 << (Channel & 0x07);
				ansel_reg = &ANSELC;
			#endif
		}
		else if (Channel < 32)
		{
			#if defined (MX_ADC_CHANNEL_24) || defined (MX_ADC_CHANNEL_25) || defined (MX_ADC_CHANNEL_26) || defined (MX_ADC_CHANNEL_27) || defined (MX_ADC_CHANNEL_28) || defined (MX_ADC_CHANNEL_29) || defined (MX_ADC_CHANNEL_30) || defined (MX_ADC_CHANNEL_31)
				TRISD |= 1 << (Channel & 0x07);
				ansel_reg = &ANSELD;
			#endif
		}
		else if (Channel < 40)
		{
			#if defined (MX_ADC_CHANNEL_32) || defined (MX_ADC_CHANNEL_33) || defined (MX_ADC_CHANNEL_34) || defined (MX_ADC_CHANNEL_35) || defined (MX_ADC_CHANNEL_36) || defined (MX_ADC_CHANNEL_37) || defined (MX_ADC_CHANNEL_38) || defined (MX_ADC_CHANNEL_39)
				TRISE |= 1 << (Channel & 0x07);
				ansel_reg = &ANSELE;
			#endif
		}

		*ansel_reg = 1 << (Channel & 0x07);

		ADCON1 = (Conv_Speed << 4) | (Vref);

		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);

		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		*ansel_reg = 0;											//Restore pin to Digital mode
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 34 Supported Devices ***********************************************************
// 16F188xx
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_34

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		// set the ADCC to the options selected in the User Interface
	    // ADDSEN disabled; ADGPOL digital_low; ADIPEN disabled; ADPPOL VSS;
	    //ADCON1 = 0x00;
	    // ADCRS 0; ADMD Basic_mode; ADACLR disabled; ADPSIS ADFLTR;
	    //ADCON2 = 0x00;
	    // ADCALC First derivative of Single measurement; ADTMD disabled; ADSOI ADGO not cleared;
	    //ADCON3 = 0x00;
	    // ADACT disabled;
	    //ADSTAT = 0x00;
	    // Conversion Speed;
	    //ADCLK = 0x00;
	    // ADNREF VSS; ADPREF VDD;

		if (Channel < 8)
		{
			#if defined (MX_ADC_CHANNEL_0) || defined (MX_ADC_CHANNEL_1) || defined (MX_ADC_CHANNEL_2) || defined (MX_ADC_CHANNEL_3) || defined (MX_ADC_CHANNEL_4) || defined (MX_ADC_CHANNEL_5) || defined (MX_ADC_CHANNEL_6) || defined (MX_ADC_CHANNEL_7)
				TRISA |= 1 << (Channel & 0x07);
			#endif
		}
		else if (Channel < 16)
		{
			#if defined (MX_ADC_CHANNEL_8) || defined (MX_ADC_CHANNEL_9) || defined (MX_ADC_CHANNEL_10) || defined (MX_ADC_CHANNEL_11) || defined (MX_ADC_CHANNEL_12) || defined (MX_ADC_CHANNEL_13) || defined (MX_ADC_CHANNEL_14) || defined (MX_ADC_CHANNEL_15)
				TRISB |= 1 << (Channel & 0x07);
			#endif
		}
		else if (Channel < 24)
		{
			#if defined (MX_ADC_CHANNEL_16) || defined (MX_ADC_CHANNEL_17) || defined (MX_ADC_CHANNEL_18) || defined (MX_ADC_CHANNEL_19) || defined (MX_ADC_CHANNEL_20) || defined (MX_ADC_CHANNEL_21) || defined (MX_ADC_CHANNEL_22) || defined (MX_ADC_CHANNEL_23)
				TRISC |= 1 << (Channel & 0x07);
			#endif
		}
		else if (Channel < 32)
		{
			#if defined (MX_ADC_CHANNEL_24) || defined (MX_ADC_CHANNEL_25) || defined (MX_ADC_CHANNEL_26) || defined (MX_ADC_CHANNEL_27) || defined (MX_ADC_CHANNEL_28) || defined (MX_ADC_CHANNEL_29) || defined (MX_ADC_CHANNEL_30) || defined (MX_ADC_CHANNEL_31)
				TRISD |= 1 << (Channel & 0x07);
			#endif
		}
		else if (Channel < 40)
		{
			#if defined (MX_ADC_CHANNEL_32) || defined (MX_ADC_CHANNEL_33) || defined (MX_ADC_CHANNEL_34) || defined (MX_ADC_CHANNEL_35) || defined (MX_ADC_CHANNEL_36) || defined (MX_ADC_CHANNEL_37) || defined (MX_ADC_CHANNEL_38) || defined (MX_ADC_CHANNEL_39)
				TRISE |= 1 << (Channel & 0x07);
			#endif
		}

		ADPCH = Channel;

	    ADREF = 0x00;
	    ADCON0 = 0x80;							// ADGO stop; ADFM left; ADON enabled; ADCONT disabled; ADCS FRC;

		ADCLK = Conv_Speed & 0x3F;				//assign conversion rate

		if (Vref != 0)							//assign VREF functionality
			ADREF = ADREF | Vref;				//Mod to allow FVR as VREF

		delay_us(T_Charge);						//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

        ADCON0bits.ADGO = 1;					// Start the conversion

		while (ADCON0bits.ADGO);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 35 Supported Devices ************************************************************
// PIC16F1764
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_35

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					TRISA |= 0x01;
					ANSELA = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					TRISA |= 0x02;
					ANSELA = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					TRISA |= 0x04;
					ANSELA = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					TRISA |= 0x10;
					ANSELA = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					TRISC |= 0x01;
					ANSELC = 0x01;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					TRISC |= 0x02;
					ANSELC = 0x02;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					TRISC |= 0x04;
					ANSELC = 0x04;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					TRISC |= 0x08;
					ANSELC = 0x08;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					TRISC |= 0x40;
					ANSELC = 0x40;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					TRISC |= 0x80;
					ANSELC = 0x80;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					TRISB |= 0x10;
					ANSELB = 0x10;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					TRISB |= 0x20;
					ANSELB = 0x20;
					break;
			#endif
		}

		ADCON1 = ((Conv_Speed & 0x07) << 4);					//assign conversion rate
		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		if (Vref == 1)											//assign VREF functionality
			ADCON1 |= 2;

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		ANSELA = 0x00;
		ANSELC = 0x00;
		#ifdef _ANSELB_ANSB4_POSN
			ANSELB = 0x00;
		#endif
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif



// ADC Type 36 Supported Devices ************************************************************
// PIC18F24K40
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_36

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		if (Channel < 8)
		{
			#if defined (MX_ADC_CHANNEL_0) || defined (MX_ADC_CHANNEL_1) || defined (MX_ADC_CHANNEL_2) || defined (MX_ADC_CHANNEL_3) || defined (MX_ADC_CHANNEL_4) || defined (MX_ADC_CHANNEL_5) || defined (MX_ADC_CHANNEL_6) || defined (MX_ADC_CHANNEL_7)
				TRISA |= 1 << (Channel & 0x07);
				ANSELA |= 1 << (Channel & 0x07);
			#endif
		}
		else if (Channel < 16)
		{
			#if defined (MX_ADC_CHANNEL_8) || defined (MX_ADC_CHANNEL_9) || defined (MX_ADC_CHANNEL_10) || defined (MX_ADC_CHANNEL_11) || defined (MX_ADC_CHANNEL_12) || defined (MX_ADC_CHANNEL_13) || defined (MX_ADC_CHANNEL_14) || defined (MX_ADC_CHANNEL_15)
				TRISB |= 1 << (Channel & 0x07);
				ANSELB |= 1 << (Channel & 0x07);
			#endif
		}
		else if (Channel < 24)
		{
			#if defined (MX_ADC_CHANNEL_16) || defined (MX_ADC_CHANNEL_17) || defined (MX_ADC_CHANNEL_18) || defined (MX_ADC_CHANNEL_19) || defined (MX_ADC_CHANNEL_20) || defined (MX_ADC_CHANNEL_21) || defined (MX_ADC_CHANNEL_22) || defined (MX_ADC_CHANNEL_23)
				TRISC |= 1 << (Channel & 0x07);
				ANSELC |= 1 << (Channel & 0x07);
			#endif
		}
		else if (Channel < 32)
		{
			#if defined (MX_ADC_CHANNEL_24) || defined (MX_ADC_CHANNEL_25) || defined (MX_ADC_CHANNEL_26) || defined (MX_ADC_CHANNEL_27) || defined (MX_ADC_CHANNEL_28) || defined (MX_ADC_CHANNEL_29) || defined (MX_ADC_CHANNEL_30) || defined (MX_ADC_CHANNEL_31)
				TRISD |= 1 << (Channel & 0x07);
				ANSELD |= 1 << (Channel & 0x07);
			#endif
		}
		else if (Channel < 40)
		{
			#if defined (MX_ADC_CHANNEL_32) || defined (MX_ADC_CHANNEL_33) || defined (MX_ADC_CHANNEL_34) || defined (MX_ADC_CHANNEL_35) || defined (MX_ADC_CHANNEL_36) || defined (MX_ADC_CHANNEL_37) || defined (MX_ADC_CHANNEL_38) || defined (MX_ADC_CHANNEL_39)
				TRISE |= 1 << (Channel & 0x07);
				ANSELE |= 1 << (Channel & 0x07);
			#endif
		}
		else if (Channel < 48)
		{
			#if defined (MX_ADC_CHANNEL_40) || defined (MX_ADC_CHANNEL_41) || defined (MX_ADC_CHANNEL_42) || defined (MX_ADC_CHANNEL_43) || defined (MX_ADC_CHANNEL_44) || defined (MX_ADC_CHANNEL_45) || defined (MX_ADC_CHANNEL_46) || defined (MX_ADC_CHANNEL_47)
				TRISF |= 1 << (Channel & 0x07);
				ANSELF |= 1 << (Channel & 0x07);
			#endif
		}
		else if (Channel < 56)
		{
			#if defined (MX_ADC_CHANNEL_48) || defined (MX_ADC_CHANNEL_49) || defined (MX_ADC_CHANNEL_50) || defined (MX_ADC_CHANNEL_51) || defined (MX_ADC_CHANNEL_52) || defined (MX_ADC_CHANNEL_53) || defined (MX_ADC_CHANNEL_54) || defined (MX_ADC_CHANNEL_55)
				TRISG |= 1 << (Channel & 0x07);
				ANSELG |= 1 << (Channel & 0x07);
			#endif
		}

		if (Conv_Speed & 0x40)
		{
			ADCON0 = 0x10;										//FRC Clock Source
		}
		else
		{
			ADCON0 = 0x00;										//OSC Based Clock Source
			ADCLK = Conv_Speed & 0x3F;							//assign conversion rate
		}

		ADREF = Vref;											//assign VREF functionality
		ADPCH = Channel;
		ADCON0 |= 0x80;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 |= 0x01;											//begin next conversion

		while (ADCON0 & 0x01);
		if (Sample_Mode)
		{
		  #ifdef MX_ADC_BITS_12
			iRetVal = (ADRESH << 4);							//12-bit ADC
			iRetVal = iRetVal | (ADRESL >> 4);
		  #else
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		  #endif
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		#ifdef _ANSELA_ANSA0_POSN
			ANSELA = 0x00;
		#endif
		#ifdef _ANSELB_ANSB0_POSN
			ANSELB = 0x00;
		#endif
		#ifdef _ANSELC_ANSC0_POSN
			ANSELC = 0x00;
		#endif
		#ifdef _ANSELD_ANSD0_POSN
			ANSELD = 0x00;
		#endif
		#ifdef _ANSELE_ANSE0_POSN
			ANSELE = 0x00;
		#endif
		#ifdef _ANSELF_ANSF0_POSN
			ANSELF = 0x00;
		#endif
		#ifdef _ANSELG_ANSG0_POSN
			ANSELG = 0x00;
		#endif
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif

// ADC Type 37 Supported Devices ***********************************************************
// 16F1784
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_37

	volatile MX_UINT8 * ANSEL_reg;					//ANSEL register pointer
	MX_UINT8 tris_mask;

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					tris_mask = 0x01;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					tris_mask = 0x02;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					tris_mask = 0x04;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					tris_mask = 0x08;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					tris_mask = 0x20;
					TRISA |= tris_mask;
					ANSEL_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					tris_mask = 0x01;
					TRISE |= tris_mask;
					ANSEL_reg = &ANSELE;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					tris_mask = 0x02;
					TRISE |= tris_mask;
					ANSEL_reg = &ANSELE;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					tris_mask = 0x04;
					TRISE |= tris_mask;
					ANSEL_reg = &ANSELE;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					tris_mask = 0x04;
					TRISB |= tris_mask;
					ANSEL_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					tris_mask = 0x08;
					TRISB |= tris_mask;
					ANSEL_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					tris_mask = 0x02;
					TRISB |= tris_mask;
					ANSEL_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					tris_mask = 0x10;
					TRISB |= tris_mask;
					ANSEL_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_12
				case (12):
					tris_mask = 0x01;
					TRISB |= tris_mask;
					ANSEL_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_13
				case (13):
					tris_mask = 0x20;
					TRISB |= tris_mask;
					ANSEL_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_21
				case (21):
					tris_mask = 0x02;
					TRISD |= tris_mask;
					ANSEL_reg = &ANSELD;
					break;
			#endif
		}

		*ANSEL_reg = *ANSEL_reg | tris_mask;

		ADCON1 = (Conv_Speed & 0x07) << 4;						//assign conversion rate

		if (Vref != 0)											//assign VREF functionality
			ADCON1 = ADCON1 | (Vref & 0x03);					//Mod to allow FVR as VREF

		ADCON2 = 0x0F;											//VREF- is ADNREF which = VSS pin

		ADCON0 = (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on
		delay_us(T_Charge);										//wait the acquisition time

		ADCON0 = ADCON0 | 0x02;									//begin next conversion
	}

CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
		  #ifdef MX_ADC_BITS_12
			iRetVal = (ADRESH << 4);							//12-bit ADC
			iRetVal = iRetVal | (ADRESL >> 4);
		  #else
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		  #endif
		}
		else
		{
			iRetVal = ADRESH;									//8-bit ADC
		}

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		*ANSEL_reg = 0x00;
	}

	#ifdef MX_ADC_TOUCH


	#ifdef _ADRESH_ADRESH_POSN
	  #define MX_ADC_TOUCH_CASE(ADC, PORT, BIT)	\
			case (ADC):							\
			FCP_TRIS_##PORT &= ~(1<<BIT);		\
			FCP_LAT_##PORT |= (1<<BIT);			\
			ANSEL##PORT |= (1<<BIT);			\
			ADCON0 = (ADC << 2) | 1;			\
			ADCON0 &= (1<<0);					\
			FCP_LAT_##PORT &= ~(1<<BIT);		\
			FCP_TRIS_##PORT |= (1<<BIT);		\
			ADCON0 = (ADC << 2) | 1;			\
			ADCON0 = (ADC << 2) | 3;			\
			while (ADCON0 & (1<<1));			\
			ANSEL##PORT &= ~(1<<BIT);			\
			return (ADRESH << 8) | ADRESL;
	#else
	  #define MX_ADC_TOUCH_CASE(ADC, PORT, BIT)	\
			case (ADC):							\
			FCP_TRIS_##PORT &= ~(1<<BIT);		\
			FCP_LAT_##PORT |= (1<<BIT);			\
			ANSEL##PORT |= (1<<BIT);			\
			ADCON0 = (ADC << 2) | 1;			\
			ADCON0 &= (1<<0);					\
			FCP_LAT_##PORT &= ~(1<<BIT);		\
			FCP_TRIS_##PORT |= (1<<BIT);		\
			ADCON0 = (ADC << 2) | 1;			\
			ADCON0 = (ADC << 2) | 3;			\
			while (ADCON0 & (1<<1));			\
			ANSEL##PORT &= ~(1<<BIT);			\
			return (ADRES << 2);
	#endif


	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		ADCON1 = 0xf0;						// Right justified result and set FRC clock mode

		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
					MX_ADC_TOUCH_CASE(0, A, 0);
			#endif
			#ifdef MX_ADC_CHANNEL_1
					MX_ADC_TOUCH_CASE(1, A, 1);
			#endif
			#ifdef MX_ADC_CHANNEL_2
					MX_ADC_TOUCH_CASE(2, A, 2);
			#endif
			#ifdef MX_ADC_CHANNEL_3
					MX_ADC_TOUCH_CASE(3, A, 3);
			#endif
			#ifdef MX_ADC_CHANNEL_4
					MX_ADC_TOUCH_CASE(4, A, 5);
			#endif
			#ifdef MX_ADC_CHANNEL_5
					MX_ADC_TOUCH_CASE(5, A, 0);
			#endif
			#ifdef MX_ADC_CHANNEL_6
					MX_ADC_TOUCH_CASE(6, E, 1);
			#endif
			#ifdef MX_ADC_CHANNEL_7
					MX_ADC_TOUCH_CASE(7, E, 2);
			#endif
			#ifdef MX_ADC_CHANNEL_8
					MX_ADC_TOUCH_CASE(8, B, 2);
			#endif
			#ifdef MX_ADC_CHANNEL_9
					MX_ADC_TOUCH_CASE(9, B, 3);
			#endif
			#ifdef MX_ADC_CHANNEL_10
					MX_ADC_TOUCH_CASE(10, B, 1);
			#endif
			#ifdef MX_ADC_CHANNEL_11
					MX_ADC_TOUCH_CASE(11, B, 4);
			#endif
			#ifdef MX_ADC_CHANNEL_12
					MX_ADC_TOUCH_CASE(12, B, 0);
			#endif
			#ifdef MX_ADC_CHANNEL_13
					MX_ADC_TOUCH_CASE(13, B, 5);
			#endif
		}
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif

// ADC Type 38 Supported Devices ***********************************************************
// 16F15xxx
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_38

	volatile MX_UINT8 * ansel_reg;					//ANSEL register pointer
	MX_UINT8 tris_mask;

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					tris_mask = 0x01;
					TRISA |= tris_mask;
					ansel_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					tris_mask = 0x02;
					TRISA |= tris_mask;
					ansel_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					tris_mask = 0x04;
					TRISA |= tris_mask;
					ansel_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					tris_mask = 0x08;
					TRISA |= tris_mask;
					ansel_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					tris_mask = 0x10;
					TRISA |= tris_mask;
					ansel_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					tris_mask = 0x20;
					TRISA |= tris_mask;
					ansel_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					tris_mask = 0x40;
					TRISA |= tris_mask;
					ansel_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					tris_mask = 0x80;
					TRISA |= tris_mask;
					ansel_reg = &ANSELA;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_8
				case (8):
					tris_mask = 0x01;
					TRISB |= tris_mask;
					ansel_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_9
				case (9):
					tris_mask = 0x02;
					TRISB |= tris_mask;
					ansel_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_10
				case (10):
					tris_mask = 0x04;
					TRISB |= tris_mask;
					ansel_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_11
				case (11):
					tris_mask = 0x08;
					TRISB |= tris_mask;
					ansel_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_12
				case (12):
					tris_mask = 0x10;
					TRISB |= tris_mask;
					ansel_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_13
				case (13):
					tris_mask = 0x20;
					TRISB |= tris_mask;
					ansel_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_14
				case (14):
					tris_mask = 0x40;
					TRISB |= tris_mask;
					ansel_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_15
				case (15):
					tris_mask = 0x80;
					TRISB |= tris_mask;
					ansel_reg = &ANSELB;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_16
				case (16):
					tris_mask = 0x01;
					TRISC |= tris_mask;
					ansel_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_17
				case (17):
					tris_mask = 0x02;
					TRISC |= tris_mask;
					ansel_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_18
				case (18):
					tris_mask = 0x04;
					TRISC |= tris_mask;
					ansel_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_19
				case (19):
					tris_mask = 0x08;
					TRISC |= tris_mask;
					ansel_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_20
				case (20):
					tris_mask = 0x10;
					TRISC |= tris_mask;
					ansel_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_21
				case (21):
					tris_mask = 0x20;
					TRISC |= tris_mask;
					ansel_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_22
				case (22):
					tris_mask = 0x40;
					TRISC |= tris_mask;
					ansel_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_23
				case (23):
					tris_mask = 0x80;
					TRISC |= tris_mask;
					ansel_reg = &ANSELC;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_24
				case (24):
					tris_mask = 0x01;
					TRISD |= tris_mask;
					ansel_reg = &ANSELD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_25
				case (25):
					tris_mask = 0x02;
					TRISD |= tris_mask;
					ansel_reg = &ANSELD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_26
				case (26):
					tris_mask = 0x04;
					TRISD |= tris_mask;
					ansel_reg = &ANSELD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_27
				case (27):
					tris_mask = 0x08;
					TRISD |= tris_mask;
					ansel_reg = &ANSELD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_28
				case (28):
					tris_mask = 0x10;
					TRISD |= tris_mask;
					ansel_reg = &ANSELD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_29
				case (29):
					tris_mask = 0x20;
					TRISD |= tris_mask;
					ansel_reg = &ANSELD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_30
				case (30):
					tris_mask = 0x40;
					TRISD |= tris_mask;
					ansel_reg = &ANSELD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_31
				case (31):
					tris_mask = 0x80;
					TRISD |= tris_mask;
					ansel_reg = &ANSELD;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_32
				case (32):
					tris_mask = 0x01;
					TRISE |= tris_mask;
					ansel_reg = &ANSELE;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_33
				case (33):
					tris_mask = 0x02;
					TRISE |= tris_mask;
					ansel_reg = &ANSELE;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_34
				case (34):
					tris_mask = 0x04;
					TRISE |= tris_mask;
					ansel_reg = &ANSELE;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_35
				case (35):
					tris_mask = 0x01;
					TRISF |= tris_mask;
					ansel_reg = &ANSELF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_36
				case (36):
					tris_mask = 0x02;
					TRISF |= tris_mask;
					ansel_reg = &ANSELF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_37
				case (37):
					tris_mask = 0x04;
					TRISF |= tris_mask;
					ansel_reg = &ANSELF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_38
				case (38):
					tris_mask = 0x08;
					TRISF |= tris_mask;
					ansel_reg = &ANSELF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_39
				case (39):
					tris_mask = 0x10;
					TRISF |= tris_mask;
					ansel_reg = &ANSELF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_40
				case (40):
					tris_mask = 0x20;
					TRISF |= tris_mask;
					ansel_reg = &ANSELF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_41
				case (41):
					tris_mask = 0x40;
					TRISF |= tris_mask;
					ansel_reg = &ANSELF;
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_42
				case (42):
					tris_mask = 0x80;
					TRISF |= tris_mask;
					ansel_reg = &ANSELF;
					break;
			#endif
		}

		*ansel_reg = tris_mask;					//Put the pin in analog mode

		ADCON1 = ((Conv_Speed & 7) << 4);		//assign conversion rate
		ADCON0 = (Channel << 2);				//assign conversion channel
		ADCON0 |= 0x01;							//enable ADC

		if (Vref != 0)							//assign VREF functionality
			ADCON1 = ADCON1 | Vref;				//Mod to allow FVR as VREF

		delay_us(T_Charge);						//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

        ADCON0bits.GOnDONE = 1;					// Start the conversion

		while (ADCON0bits.GOnDONE);
		if (Sample_Mode)
		{
			iRetVal = (ADRESH << 2);			//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		}
		else
			iRetVal = ADRESH;

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		*ansel_reg = 0x00;						//Restore digital mode
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif


// ADC Type 39 Supported Devices ************************************************************
// 16F527
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_39

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
				case (0):
					tvarA |= 0x01;
					asm("movf(_tvarA),w");
					asm("TRIS 5");
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_1
				case (1):
					tvarA |= 0x02;
					asm("movf(_tvarA),w");
					asm("TRIS 5");
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_2
				case (2):
					tvarA |= 0x04;
					asm("movf(_tvarA),w");
					asm("TRIS 5");
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_3
				case (3):
					tvarA |= 0x10;
					asm("movf(_tvarA),w");
					asm("TRIS 5");
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_4
				case (4):
					tvarC |= 0x01;
					asm("movf(_tvarC),w");
					asm("TRIS 7");
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_5
				case (5):
					tvarC |= 0x02;
					asm("movf(_tvarC),w");
					asm("TRIS 7");
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_6
				case (6):
					tvarC |= 0x04;
					asm("movf(_tvarC),w");
					asm("TRIS 7");
					break;
			#endif
			#ifdef MX_ADC_CHANNEL_7
				case (7):
					tvarC |= 0x08;
					asm("movf(_tvarC),w");
					asm("TRIS 7");
					break;
			#endif
		}

		ADCON0 = (Conv_Speed << 6) | (Channel << 2);
		ADCON0 |= 0x01;											//turn ADC on

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x02;									//begin next conversion

		while (ADCON0 & 0x02);
		if (Sample_Mode)
		{
			iRetVal = (ADRES << 2);								//Mock 10-bit ADC from 8-bit value
		}
		else
			iRetVal = ADRES;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
	}

	#ifdef MX_ADC_TOUCH

	#warning "ADC Touch not yet supported on this device"

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		return 0;
	}
	#endif // MX_ADC_TOUCH
#endif



// ADC Type 40 Supported Devices ***********************************************************
// 18F24Q10, 18F25Q10, 18FX5Q41
// *****************************************************************************************/

#ifdef MX_ADC_TYPE_40

	volatile MX_UINT8 * ANSEL_reg;					//ANSEL register pointer

	CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
	{
		if (Channel < 8)
		{
			#if defined (MX_ADC_CHANNEL_0) || defined (MX_ADC_CHANNEL_1) || defined (MX_ADC_CHANNEL_2) || defined (MX_ADC_CHANNEL_3) || defined (MX_ADC_CHANNEL_4) || defined (MX_ADC_CHANNEL_5) || defined (MX_ADC_CHANNEL_6) || defined (MX_ADC_CHANNEL_7)
				TRISA |= 1 << (Channel & 0x07);
				ANSELA |= 1 << (Channel & 0x07);
			#endif
		}
		else if (Channel < 16)
		{
			#if defined (MX_ADC_CHANNEL_8) || defined (MX_ADC_CHANNEL_9) || defined (MX_ADC_CHANNEL_10) || defined (MX_ADC_CHANNEL_11) || defined (MX_ADC_CHANNEL_12) || defined (MX_ADC_CHANNEL_13) || defined (MX_ADC_CHANNEL_14) || defined (MX_ADC_CHANNEL_15)
				TRISB |= 1 << ((Channel - 8) & 0x07);
				ANSELB |= 1 << ((Channel - 8) & 0x07);
			#endif
		}
		else if (Channel < 24)
		{
			#if defined (MX_ADC_CHANNEL_16) || defined (MX_ADC_CHANNEL_17) || defined (MX_ADC_CHANNEL_18) || defined (MX_ADC_CHANNEL_19) || defined (MX_ADC_CHANNEL_20) || defined (MX_ADC_CHANNEL_21) || defined (MX_ADC_CHANNEL_22) || defined (MX_ADC_CHANNEL_23)
				TRISC |= 1 << ((Channel - 16) & 0x07);
				ANSELC |= 1 << ((Channel - 16) & 0x07);
			#endif
		}

		ADCON0 = 0x80;											//turn on ADC
		ADPCH = Channel;

		if (Conv_Speed == 128)
		{
			ADCON0bits.ADCS = 1;								//FRC Timing
		}
		else
		{
			ADCLK = Conv_Speed;									//Assign conversion speed
		}

		ADREF = Vref;											//assign VREF functionality

		delay_us(T_Charge);										//wait the acquisition time
	}

	CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
	{
		MX_UINT16 iRetVal;

		ADCON0 = ADCON0 | 0x01;									//begin next conversion

		while (ADCON0 & 0x01);
		if (Sample_Mode)
		{
		  #ifdef MX_ADC_BITS_12
			iRetVal = (ADRESH << 4);							//12-bit ADC
			iRetVal = iRetVal | (ADRESL >> 4);
		 #else
			iRetVal = (ADRESH << 2);							//10-bit ADC
			iRetVal = iRetVal | (ADRESL >> 6);
		  #endif
		}
		else
			iRetVal = ADRESH;									//8-bit ADC

		return (iRetVal);
	}

	CALFUNCTION(void, FC_CAL_ADC_Disable_, ())
	{
		ADCON0 = 0x00;
		#ifdef _ANSELA_ANSA0_POSN
			ANSELA = 0x00;
		#endif
		#ifdef _ANSELB_ANSB0_POSN
			ANSELB = 0x00;
		#endif
		#ifdef _ANSELC_ANSC0_POSN
			ANSELC = 0x00;
		#endif
	}

	#ifdef MX_ADC_TOUCH

	#define MX_ADC_TOUCH_CASE(ADC, PT, BIT)		\
			case (ADC):							\
			TRIS##PT &= ~(1<<BIT);				\
			PORT##PT |= (1<<BIT);				\
			ADPCH = ADC;						\
			PORT##PT &= ~(1<<BIT);				\
			TRIS##PT |= (1<<BIT);				\
			ANSEL##PT |= (1<<BIT);				\
			ADCON0 = 0x92;						\
			ADCON0 |= (1<<0);					\
			while (ADCON0 & (1<<0));			\
			result = (ADRESH << 8) | ADRESL;	\
			ANSEL##PT = 0;						\
			break;

	MX_UINT16 FC_CAL_ADC_Touch (MX_UINT8 Channel)
	{
		MX_UINT16 result = 0;

		switch (Channel)
		{
			#ifdef MX_ADC_CHANNEL_0
					MX_ADC_TOUCH_CASE(0, A, 0);
			#endif
			#ifdef MX_ADC_CHANNEL_1
					MX_ADC_TOUCH_CASE(1, A, 1);
			#endif
			#ifdef MX_ADC_CHANNEL_2
					MX_ADC_TOUCH_CASE(2, A, 2);
			#endif
			#ifdef MX_ADC_CHANNEL_3
					MX_ADC_TOUCH_CASE(3, A, 3);
			#endif
			#ifdef MX_ADC_CHANNEL_4
					MX_ADC_TOUCH_CASE(4, A, 4);
			#endif
			#ifdef MX_ADC_CHANNEL_5
					MX_ADC_TOUCH_CASE(5, A, 5);
			#endif
			#ifdef MX_ADC_CHANNEL_6
					MX_ADC_TOUCH_CASE(6, A, 6);
			#endif
			#ifdef MX_ADC_CHANNEL_7
					MX_ADC_TOUCH_CASE(7, A, 7);
			#endif
			#ifdef MX_ADC_CHANNEL_8
					MX_ADC_TOUCH_CASE(8, B, 0);
			#endif
			#ifdef MX_ADC_CHANNEL_9
					MX_ADC_TOUCH_CASE(9, B, 1);
			#endif
			#ifdef MX_ADC_CHANNEL_10
					MX_ADC_TOUCH_CASE(10, B, 2);
			#endif
			#ifdef MX_ADC_CHANNEL_11
					MX_ADC_TOUCH_CASE(11, B, 3);
			#endif
			#ifdef MX_ADC_CHANNEL_12
					MX_ADC_TOUCH_CASE(12, B, 4);
			#endif
			#ifdef MX_ADC_CHANNEL_13
					MX_ADC_TOUCH_CASE(13, B, 5);
			#endif
			#ifdef MX_ADC_CHANNEL_14
					MX_ADC_TOUCH_CASE(14, B, 6);
			#endif
			#ifdef MX_ADC_CHANNEL_15
					MX_ADC_TOUCH_CASE(15, B, 7);
			#endif
			#ifdef MX_ADC_CHANNEL_16
					MX_ADC_TOUCH_CASE(16, C, 0);
			#endif
			#ifdef MX_ADC_CHANNEL_17
					MX_ADC_TOUCH_CASE(17, C, 1);
			#endif
			#ifdef MX_ADC_CHANNEL_18
					MX_ADC_TOUCH_CASE(18, C, 2);
			#endif
			#ifdef MX_ADC_CHANNEL_19
					MX_ADC_TOUCH_CASE(19, C, 3);
			#endif
			#ifdef MX_ADC_CHANNEL_20
					MX_ADC_TOUCH_CASE(20, C, 4);
			#endif
			#ifdef MX_ADC_CHANNEL_21
					MX_ADC_TOUCH_CASE(21, C, 5);
			#endif
			#ifdef MX_ADC_CHANNEL_22
					MX_ADC_TOUCH_CASE(22, C, 6);
			#endif
			#ifdef MX_ADC_CHANNEL_23
					MX_ADC_TOUCH_CASE(23, C, 7);
			#endif
		}
		return result;
	}

	#endif // MX_ADC_TOUCH
#endif
