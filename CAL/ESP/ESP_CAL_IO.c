// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A0839C2618FDDE2E5B47BDCC5F9C10ADC117B470248A3E565D848C9455C852E4568940AE31AE32EB4A0C3CAEE8E7DA6987AB7814C704472E1851B68B7E629B305EECB45AD483524AAA59ABADD35866E64AD79828AA38D7C4C01ACC0EE729ADE2F49481AF767D414B1E9522BA3E447D27D80EB700E93D75BA2CC2C3DB4131268236954E545881AEA9C6549D34A0D5AD11F31144469027ACCDE46F31DEA1489E5D459A5333B3DD4F6747EA7459FBAA187747CD4C0F0302B21EE1
// REVISION: 10.0
// GUID: E1590F3D-C1CA-46CE-8112-BAF38C65B600
// DATE: 28\04\2025
// DIR: CAL\ESP\ESP_CAL_IO.c
/*********************************************************************
 *                  Flowcode CAL IO File
 *
 * File: ESP_CAL_IO.c
 *
 * (c) 2018 Matrix TSL.
 * http://www.matrixtsl.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
 * 'Company') for its Flowcode graphical programming language is
 * intended and supplied to you, the Company's customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN 'AS IS' CONDITION. NO WARRANTIES,
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
 * 130718 | BR | Created
 *
 */

#include "ESP_CAL_IO.h"

//GPIO Pin mode mask
MX_UINT32 PORTA_GPIO_MASK = 0;
MX_UINT32 PORTB_GPIO_MASK = 0;

//AVR type DDR 0=Input, 1=Output
MX_UINT32 PORTA_GPIO_DDR = 0;
MX_UINT32 PORTB_GPIO_DDR = 0;


#define MX_USE_INLINE		//Keep this line to increase the speed of I/O by approx 2X, comment out to reduce code usage

#ifdef MX_USE_INLINE
  #define MX_ESP32_IO_INLINE inline
#else
  #define MX_ESP32_IO_INLINE
#endif



#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)	// enable functionality present in IDF v5.0

	#define gpio_pad_select_gpio esp_rom_gpio_pad_select_gpio

#else												//Original IDF v4.1

#endif



static MX_ESP32_IO_INLINE void FC_CAL_Port_Out_DDR (MX_UINT8 PORT, MX_UINT32 OutMask, MX_UINT32 OutValue)
{
	MX_UINT32 Mask;

	for (MX_UINT8 idx = 0; idx < 32; idx++)										//Loop through bits in port
	{
		Mask = (unsigned long) 1 << (idx);

		if (OutMask & Mask)														//Is the masked bit active?
		{
			if (PORT == 0)														//Pins 0-31
			{
				//Pin is not an output?
				if ((PORTA_GPIO_DDR & Mask) == 0)
				{
					//Pin is not in I/O Mode?
					if ((PORTA_GPIO_MASK & Mask) == 0)
					{

						gpio_pad_select_gpio(PORT + idx);
						PORTA_GPIO_MASK |= Mask;
					}

					gpio_set_direction(PORT + idx, GPIO_MODE_OUTPUT);
					PORTA_GPIO_DDR |= Mask;
				}
			}
			else																//Pins 32+
			{
				//Pin is not an output?
				if ((PORTB_GPIO_DDR & Mask) == 0)
				{
					//Pin is not in I/O Mode?
					if ((PORTB_GPIO_MASK & Mask) == 0)
					{

						gpio_pad_select_gpio(PORT + idx);
						PORTB_GPIO_MASK |= Mask;
					}

					gpio_set_direction(PORT + idx, GPIO_MODE_OUTPUT);
					PORTB_GPIO_DDR |= Mask;
				}
			}

			gpio_set_level((PORT + idx), (OutValue & Mask)?1:0);			//Assign Output value
		}
	}
}


static MX_ESP32_IO_INLINE void FC_CAL_Bit_Low_DDR (MX_UINT8 PIN)
{
	MX_UINT32 Mask;

	if (PIN < 32)															//Pins 0-31
	{
		Mask = (unsigned long) 1 << (PIN);

		//Pin is not an output?
		if ((PORTA_GPIO_DDR & Mask) == 0)
		{
			//Pin is not in I/O Mode?
			if ((PORTA_GPIO_MASK & Mask) == 0)
			{

				gpio_pad_select_gpio(PIN);
				PORTA_GPIO_MASK |= Mask;
			}

			gpio_set_direction(PIN, GPIO_MODE_OUTPUT);
			PORTA_GPIO_DDR |= Mask;
		}
	}
	else																	//Pins 32+
	{
		Mask = (unsigned long) 1 << (PIN - 32);

		//Pin is not an output?
		if ((PORTB_GPIO_DDR & Mask) == 0)
		{
			//Pin is not in I/O Mode?
			if ((PORTB_GPIO_MASK & Mask) == 0)
			{

				gpio_pad_select_gpio(PIN);
				PORTB_GPIO_MASK |= Mask;
			}

			gpio_set_direction(PIN, GPIO_MODE_OUTPUT);
			PORTB_GPIO_DDR |= Mask;
		}
	}

	gpio_set_level(PIN, 0);
}

static MX_ESP32_IO_INLINE void FC_CAL_Bit_High_DDR (MX_UINT8 PIN)
{
	MX_UINT32 Mask;

	if (PIN < 32)															//Pins 0-31
	{
		Mask = (unsigned long) 1 << (PIN);

		//Pin is not an output?
		if ((PORTA_GPIO_DDR & Mask) == 0)
		{
			//Pin is not in I/O Mode?
			if ((PORTA_GPIO_MASK & Mask) == 0)
			{

				gpio_pad_select_gpio(PIN);
				PORTA_GPIO_MASK |= Mask;
			}

			gpio_set_direction(PIN, GPIO_MODE_OUTPUT);
			PORTA_GPIO_DDR |= Mask;
		}
	}
	else																	//Pins 32+
	{
		Mask = (unsigned long) 1 << (PIN - 32);

		//Pin is not an output?
		if ((PORTB_GPIO_DDR & Mask) == 0)
		{
			//Pin is not in I/O Mode?
			if ((PORTB_GPIO_MASK & Mask) == 0)
			{

				gpio_pad_select_gpio(PIN);
				PORTB_GPIO_MASK |= Mask;
			}

			gpio_set_direction(PIN, GPIO_MODE_OUTPUT);
			PORTB_GPIO_DDR |= Mask;
		}
	}

	gpio_set_level(PIN, 1);
}


	#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)	// enable functionality present in IDF v5.0

		#include "hal/gpio_ll.h"
		extern gpio_dev_t GPIO;

	#else												//Original IDF v4.1

		extern gpio_dev_t GPIO;

	#endif



static MX_ESP32_IO_INLINE void FC_CAL_Bit_Out_DDR (MX_UINT8 PIN, MX_UINT8 OUT)
{
	MX_UINT32 Mask;

	if (PIN < 32)															//Pins 0-31
	{
		Mask = (unsigned long) 1 << (PIN);

		//Pin is not an output?
		if ((PORTA_GPIO_DDR & Mask) == 0)
		{
			//Pin is not in I/O Mode?
			if ((PORTA_GPIO_MASK & Mask) == 0)
			{

				gpio_pad_select_gpio(PIN);
				PORTA_GPIO_MASK |= Mask;
			}

			gpio_set_direction(PIN, GPIO_MODE_OUTPUT);
			PORTA_GPIO_DDR |= Mask;
		}

		#if MX_ESP32_TYPE != ESP32C3
			if (OUT)
			{
				GPIO.out_w1ts = Mask;
			}
			else
			{
				GPIO.out_w1tc = Mask;
			}
		#endif

	}
	else																	//Pins 32+
	{
		Mask = (unsigned long) 1 << (PIN - 32);

		//Pin is not an output?
		if ((PORTB_GPIO_DDR & Mask) == 0)
		{
			//Pin is not in I/O Mode?
			if ((PORTB_GPIO_MASK & Mask) == 0)
			{

				gpio_pad_select_gpio(PIN);
				PORTB_GPIO_MASK |= Mask;
			}

			gpio_set_direction(PIN, GPIO_MODE_OUTPUT);
			PORTB_GPIO_DDR |= Mask;
		}

		#if MX_ESP32_TYPE != ESP32C3
			if (OUT)
			{
				GPIO.out1_w1ts.data = Mask;
			}
			else
			{
				GPIO.out1_w1tc.data = Mask;
			}
		#endif



	}

	#if MX_ESP32_TYPE == ESP32C3
		gpio_set_level(PIN, OUT);
	#endif
}


static MX_ESP32_IO_INLINE MX_UINT32 FC_CAL_Port_In_DDR (MX_UINT8 PORT, MX_UINT32 OutMask)
{
	MX_UINT32 retval = 0;
	MX_UINT32 Mask;

	for (MX_UINT8 idx = 0; idx < 32; idx++)										//Loop through bits in port
	{
		Mask = (unsigned long) 1 << (idx);

		if (OutMask & Mask)														//Is the masked bit active?
		{
			if (PORT == 0)														//Pins 0-31
			{
				//Pin is not in I/O Mode?
				if ((PORTA_GPIO_MASK & Mask) == 0)
				{

					gpio_pad_select_gpio(PORT + idx);
					PORTA_GPIO_MASK |= Mask;
					PORTA_GPIO_DDR = PORTA_GPIO_DDR | Mask;						//Flag to force initial gpio_set_direction too
				}

				//Pin is not an input?
				if ((PORTA_GPIO_DDR & Mask))
				{
					gpio_set_direction(PORT + idx, GPIO_MODE_INPUT);
					PORTA_GPIO_DDR &= (unsigned long) ~Mask;
				}
			}
			else																//Pins 32+
			{

				//Pin is not in I/O Mode?
				if ((PORTB_GPIO_MASK & Mask) == 0)
				{

					gpio_pad_select_gpio(PORT + idx);
					PORTB_GPIO_MASK |= Mask;
					PORTB_GPIO_DDR = PORTB_GPIO_DDR | Mask;						//Flag to force initial gpio_set_direction too
				}

				//Pin is not an input?
				if ((PORTB_GPIO_DDR & Mask))
				{
					gpio_set_direction(PORT + idx, GPIO_MODE_INPUT);
					PORTB_GPIO_DDR &= (unsigned long) ~Mask;
				}
			}

			if (gpio_get_level((PORT + idx)))									//Read input value
			{
				retval |= Mask;													//If set then add set bit to return
			}
		}
	}

	return (retval);
}


static MX_ESP32_IO_INLINE MX_UINT8 FC_CAL_Bit_In_DDR (MX_UINT8 PIN)
{
	MX_UINT32 Mask;

	if (PIN < 32)															//Pins 0-31
	{
		Mask = (unsigned long) 1 << (PIN);

		//Pin is not in I/O Mode?
		if ((PORTA_GPIO_MASK & Mask) == 0)
		{

			gpio_pad_select_gpio(PIN);
			PORTA_GPIO_MASK |= Mask;
			PORTA_GPIO_DDR = PORTA_GPIO_DDR | Mask;						//Flag to force initial gpio_set_direction too
		}

		//Pin is not an input?
		if ((PORTA_GPIO_DDR & Mask))
		{
			gpio_set_direction(PIN, GPIO_MODE_INPUT);
			PORTA_GPIO_DDR &= (unsigned long) ~Mask;
		}
	}
	else																	//Pins 32+
	{
		Mask = (unsigned long) 1 << (PIN - 32);

		//Pin is not in I/O Mode?
		if ((PORTB_GPIO_MASK & Mask) == 0)
		{

			gpio_pad_select_gpio(PIN);
			PORTB_GPIO_MASK |= Mask;
			PORTB_GPIO_DDR = PORTB_GPIO_DDR | Mask;						//Flag to force initial gpio_set_direction too
		}

		//Pin is not an input?
		if ((PORTB_GPIO_DDR & Mask))
		{
			gpio_set_direction(PIN, GPIO_MODE_INPUT);
			PORTB_GPIO_DDR &= (unsigned long) ~Mask;
		}
	}

	return ( gpio_get_level(PIN) );
}




#ifdef MX_BL0058_PINMAP

	static MX_UINT8 FC_CAL_Port_Remap(MX_UINT8 port, MX_UINT8 pin)
	{
		if (port == 0)
		{
			if (pin == 0)
				return 32;
			else if (pin == 1)
				return 33;
			else if (pin == 2)
				return 2;
			else if (pin == 3)
				return 26;
			else if (pin == 4)
				return 4;
			else if (pin == 5)
				return 5;
			else if (pin == 6)
				return 12;
			else if (pin == 7)
				return 13;
		}
		if (port == 1)
		{
			if (pin == 0)
				return 14;
			else if (pin == 1)
				return 15;
			else if (pin == 2)
				return 18;
			else if (pin == 3)
				return 19;
			else if (pin == 4)
				return 27;
			else if (pin == 5)
				return 22;
			else if (pin == 6)
				return 0;
			else if (pin == 7)
				return 25;
		}
		if (port == 2)
		{
			if (pin == 0)
				return 23;
			else if (pin == 2)
				return 16;
			else if (pin == 3)
				return 17;
			else if (pin == 4)
				return 34;
			else if (pin == 5)
				return 35;
			else if (pin == 6)
				return 36;
			else if (pin == 7)
				return 39;
		}
		return 0;
	}


	static void FC_CAL_Port_Out_BL0058_A( MX_UINT8 OutMask, MX_UINT8 OutValue )
	{
		if (OutMask & 0x01)
		{
			FC_CAL_Bit_Out_DDR(32, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			FC_CAL_Bit_Out_DDR(33, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			FC_CAL_Bit_Out_DDR(2, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			FC_CAL_Bit_Out_DDR(26, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			FC_CAL_Bit_Out_DDR(4, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			FC_CAL_Bit_Out_DDR(5, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			FC_CAL_Bit_Out_DDR(12, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			FC_CAL_Bit_Out_DDR(13, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out_BL0058_B( MX_UINT8 OutMask, MX_UINT8 OutValue )
	{
		if (OutMask & 0x01)
		{
			FC_CAL_Bit_Out_DDR(14, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			FC_CAL_Bit_Out_DDR(15, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			FC_CAL_Bit_Out_DDR(18, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			FC_CAL_Bit_Out_DDR(19, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			FC_CAL_Bit_Out_DDR(27, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			FC_CAL_Bit_Out_DDR(22, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			FC_CAL_Bit_Out_DDR(0, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			FC_CAL_Bit_Out_DDR(25, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out_BL0058_C( MX_UINT8 OutMask, MX_UINT8 OutValue )
	{
		if (OutMask & 0x01)
		{
			FC_CAL_Bit_Out_DDR(23, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			FC_CAL_Bit_Out_DDR(21, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			FC_CAL_Bit_Out_DDR(16, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			FC_CAL_Bit_Out_DDR(17, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			FC_CAL_Bit_Out_DDR(34, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			FC_CAL_Bit_Out_DDR(35, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			FC_CAL_Bit_Out_DDR(36, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			FC_CAL_Bit_Out_DDR(39, OutValue & 0x80);
		}
	}


	#define FC_CAL_Port_Out_DDR_BL0058_A(M,V) 	FC_CAL_Port_Out_BL0058_A(M,V)
	#define FC_CAL_Port_Out_DDR_BL0058_B(M,V) 	FC_CAL_Port_Out_BL0058_B(M,V)
	#define FC_CAL_Port_Out_DDR_BL0058_C(M,V) 	FC_CAL_Port_Out_BL0058_C(M,V)


	static char FC_CAL_Port_In_BL0058_A( MX_UINT8 InMask, MX_UINT8 Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			retval |= FC_CAL_Bit_In_DDR(32);
		}
		if (InMask & 0x02)
		{
			retval |= FC_CAL_Bit_In_DDR(33) << 1;
		}
		if (InMask & 0x04)
		{
			retval |= FC_CAL_Bit_In_DDR(2) << 2;
		}
		if (InMask & 0x08)
		{
			retval |= FC_CAL_Bit_In_DDR(26) << 3;
		}
		if (InMask & 0x10)
		{
			retval |= FC_CAL_Bit_In_DDR(4) << 4;
		}
		if (InMask & 0x20)
		{
			retval |= FC_CAL_Bit_In_DDR(5) << 5;
		}
		if (InMask & 0x40)
		{
			retval |= FC_CAL_Bit_In_DDR(12) << 6;
		}
		if (InMask & 0x80)
		{
			retval |= FC_CAL_Bit_In_DDR(13) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In_BL0058_B( MX_UINT8 InMask, MX_UINT8 Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			retval |= FC_CAL_Bit_In_DDR(14);
		}
		if (InMask & 0x02)
		{
			retval |= FC_CAL_Bit_In_DDR(15) << 1;
		}
		if (InMask & 0x04)
		{
			retval |= FC_CAL_Bit_In_DDR(18) << 2;
		}
		if (InMask & 0x08)
		{
			retval |= FC_CAL_Bit_In_DDR(19) << 3;
		}
		if (InMask & 0x10)
		{
			retval |= FC_CAL_Bit_In_DDR(27) << 4;
		}
		if (InMask & 0x20)
		{
			retval |= FC_CAL_Bit_In_DDR(22) << 5;
		}
		if (InMask & 0x40)
		{
			retval |= FC_CAL_Bit_In_DDR(0) << 6;
		}
		if (InMask & 0x80)
		{
			retval |= FC_CAL_Bit_In_DDR(25) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In_BL0058_C( MX_UINT8 InMask, MX_UINT8 Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			retval |= FC_CAL_Bit_In_DDR(23);
		}
		if (InMask & 0x02)
		{
			retval |= FC_CAL_Bit_In_DDR(21) << 1;
		}
		if (InMask & 0x04)
		{
			retval |= FC_CAL_Bit_In_DDR(16) << 2;
		}
		if (InMask & 0x08)
		{
			retval |= FC_CAL_Bit_In_DDR(17) << 3;
		}
		if (InMask & 0x10)
		{
			retval |= FC_CAL_Bit_In_DDR(34) << 4;
		}
		if (InMask & 0x20)
		{
			retval |= FC_CAL_Bit_In_DDR(35) << 5;
		}
		if (InMask & 0x40)
		{
			retval |= FC_CAL_Bit_In_DDR(36) << 6;
		}
		if (InMask & 0x80)
		{
			retval |= FC_CAL_Bit_In_DDR(39) << 7;
		}
		return (retval >> Shift);
	}


	#define FC_CAL_Port_In_DDR_BL0058_A(M,S) 	FC_CAL_Port_In_BL0058_A(M,S)
	#define FC_CAL_Port_In_DDR_BL0058_B(M,S) 	FC_CAL_Port_In_BL0058_B(M,S)
	#define FC_CAL_Port_In_DDR_BL0058_C(M,S) 	FC_CAL_Port_In_BL0058_C(M,S)

#endif




#ifdef MX_BL6390_PINMAP

	static MX_UINT8 FC_CAL_Port_Remap(MX_UINT8 port, MX_UINT8 pin)
	{
		if (port == 0)
		{
			if (pin == 0)
				return 4;
			else if (pin == 1)
				return 5;
			else if (pin == 2)
				return 6;
			else if (pin == 3)
				return 7;
			else if (pin == 4)
				return 15;
			else if (pin == 5)
				return 16;
			else if (pin == 6)
				return 17;
			else if (pin == 7)
				return 18;
		}
		if (port == 1)
		{
			if (pin == 0)
				return 8;
			else if (pin == 1)
				return 19;
			else if (pin == 2)
				return 20;
			else if (pin == 3)
				return 3;
			else if (pin == 4)
				return 9;
			else if (pin == 5)
				return 10;
			else if (pin == 6)
				return 11;
			else if (pin == 7)
				return 12;
		}
		if (port == 2)
		{
			if (pin == 0)
				return 13;
			else if (pin == 1)
				return 14;
			else if (pin == 2)
				return 21;
			else if (pin == 3)
				return 47;
			else if (pin == 4)
				return 48;
			else if (pin == 5)
				return 45;
			else if (pin == 6)
				return 38;
			else if (pin == 7)
				return 39;
		}
		if (port == 3)
		{
			if (pin == 0)
				return 40;
			else if (pin == 1)
				return 41;
			else if (pin == 2)
				return 42;
			else if (pin == 3)
				return 46;
			else if (pin == 4)
				return 0;
		}
		return 0;
	}


	static void FC_CAL_Port_Out_BL6390_A( MX_UINT8 OutMask, MX_UINT8 OutValue )
	{
		if (OutMask & 0x01)
		{
			FC_CAL_Bit_Out_DDR(4, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			FC_CAL_Bit_Out_DDR(5, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			FC_CAL_Bit_Out_DDR(6, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			FC_CAL_Bit_Out_DDR(7, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			FC_CAL_Bit_Out_DDR(15, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			FC_CAL_Bit_Out_DDR(16, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			FC_CAL_Bit_Out_DDR(17, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			FC_CAL_Bit_Out_DDR(18, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out_BL6390_B( MX_UINT8 OutMask, MX_UINT8 OutValue )
	{
		if (OutMask & 0x01)
		{
			FC_CAL_Bit_Out_DDR(8, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			FC_CAL_Bit_Out_DDR(19, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			FC_CAL_Bit_Out_DDR(20, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			FC_CAL_Bit_Out_DDR(3, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			FC_CAL_Bit_Out_DDR(9, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			FC_CAL_Bit_Out_DDR(10, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			FC_CAL_Bit_Out_DDR(11, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			FC_CAL_Bit_Out_DDR(12, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out_BL6390_C( MX_UINT8 OutMask, MX_UINT8 OutValue )
	{
		if (OutMask & 0x01)
		{
			FC_CAL_Bit_Out_DDR(13, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			FC_CAL_Bit_Out_DDR(14, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			FC_CAL_Bit_Out_DDR(21, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			FC_CAL_Bit_Out_DDR(47, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			FC_CAL_Bit_Out_DDR(48, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			FC_CAL_Bit_Out_DDR(45, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			FC_CAL_Bit_Out_DDR(38, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			FC_CAL_Bit_Out_DDR(39, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out_BL6390_D( MX_UINT8 OutMask, MX_UINT8 OutValue )
	{
		if (OutMask & 0x01)
		{
			FC_CAL_Bit_Out_DDR(40, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			FC_CAL_Bit_Out_DDR(41, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			FC_CAL_Bit_Out_DDR(42, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			FC_CAL_Bit_Out_DDR(46, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			FC_CAL_Bit_Out_DDR(0, OutValue & 0x10);
		}
	}


	#define FC_CAL_Port_Out_DDR_BL6390_A(M,V) 	FC_CAL_Port_Out_BL6390_A(M,V)
	#define FC_CAL_Port_Out_DDR_BL6390_B(M,V) 	FC_CAL_Port_Out_BL6390_B(M,V)
	#define FC_CAL_Port_Out_DDR_BL6390_C(M,V) 	FC_CAL_Port_Out_BL6390_C(M,V)
	#define FC_CAL_Port_Out_DDR_BL6390_D(M,V) 	FC_CAL_Port_Out_BL6390_D(M,V)

	static char FC_CAL_Port_In_BL6390_A( MX_UINT8 InMask, MX_UINT8 Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			retval |= FC_CAL_Bit_In_DDR(4);
		}
		if (InMask & 0x02)
		{
			retval |= FC_CAL_Bit_In_DDR(5) << 1;
		}
		if (InMask & 0x04)
		{
			retval |= FC_CAL_Bit_In_DDR(6) << 2;
		}
		if (InMask & 0x08)
		{
			retval |= FC_CAL_Bit_In_DDR(7) << 3;
		}
		if (InMask & 0x10)
		{
			retval |= FC_CAL_Bit_In_DDR(15) << 4;
		}
		if (InMask & 0x20)
		{
			retval |= FC_CAL_Bit_In_DDR(16) << 5;
		}
		if (InMask & 0x40)
		{
			retval |= FC_CAL_Bit_In_DDR(17) << 6;
		}
		if (InMask & 0x80)
		{
			retval |= FC_CAL_Bit_In_DDR(18) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In_BL6390_B( MX_UINT8 InMask, MX_UINT8 Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			retval |= FC_CAL_Bit_In_DDR(8);
		}
		if (InMask & 0x02)
		{
			retval |= FC_CAL_Bit_In_DDR(19) << 1;
		}
		if (InMask & 0x04)
		{
			retval |= FC_CAL_Bit_In_DDR(20) << 2;
		}
		if (InMask & 0x08)
		{
			retval |= FC_CAL_Bit_In_DDR(3) << 3;
		}
		if (InMask & 0x10)
		{
			retval |= FC_CAL_Bit_In_DDR(9) << 4;
		}
		if (InMask & 0x20)
		{
			retval |= FC_CAL_Bit_In_DDR(10) << 5;
		}
		if (InMask & 0x40)
		{
			retval |= FC_CAL_Bit_In_DDR(11) << 6;
		}
		if (InMask & 0x80)
		{
			retval |= FC_CAL_Bit_In_DDR(12) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In_BL6390_C( MX_UINT8 InMask, MX_UINT8 Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			retval |= FC_CAL_Bit_In_DDR(13);
		}
		if (InMask & 0x02)
		{
			retval |= FC_CAL_Bit_In_DDR(14) << 1;
		}
		if (InMask & 0x04)
		{
			retval |= FC_CAL_Bit_In_DDR(21) << 2;
		}
		if (InMask & 0x08)
		{
			retval |= FC_CAL_Bit_In_DDR(47) << 3;
		}
		if (InMask & 0x10)
		{
			retval |= FC_CAL_Bit_In_DDR(48) << 4;
		}
		if (InMask & 0x20)
		{
			retval |= FC_CAL_Bit_In_DDR(45) << 5;
		}
		if (InMask & 0x40)
		{
			retval |= FC_CAL_Bit_In_DDR(38) << 6;
		}
		if (InMask & 0x80)
		{
			retval |= FC_CAL_Bit_In_DDR(39) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In_BL6390_D( MX_UINT8 InMask, MX_UINT8 Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			retval |= FC_CAL_Bit_In_DDR(40);
		}
		if (InMask & 0x02)
		{
			retval |= FC_CAL_Bit_In_DDR(41) << 1;
		}
		if (InMask & 0x04)
		{
			retval |= FC_CAL_Bit_In_DDR(42) << 2;
		}
		if (InMask & 0x08)
		{
			retval |= FC_CAL_Bit_In_DDR(46) << 3;
		}
		if (InMask & 0x10)
		{
			retval |= FC_CAL_Bit_In_DDR(0) << 4;
		}
		return (retval >> Shift);
	}


	#define FC_CAL_Port_In_DDR_BL6390_A(M,S) 	FC_CAL_Port_In_BL6390_A(M,S)
	#define FC_CAL_Port_In_DDR_BL6390_B(M,S) 	FC_CAL_Port_In_BL6390_B(M,S)
	#define FC_CAL_Port_In_DDR_BL6390_C(M,S) 	FC_CAL_Port_In_BL6390_C(M,S)
	#define FC_CAL_Port_In_DDR_BL6390_D(M,S) 	FC_CAL_Port_In_BL6390_D(M,S)

#endif

