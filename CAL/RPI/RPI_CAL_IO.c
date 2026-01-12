// CRC: 34358081B117C27F7D8358E612878F8E5F343B66182D417818220CB9C07676CF839C2618FDDE2E5B47BDCC5F9C10ADC19A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5DE521F5F77A29F1B2F986A852F77EDF2ECF80E44A9D3A54635940BCAEEF2E1974B80EBFB2BCC5502C089BBD52EE8D45E6101F8CCCDD8FABFAE0F5FEFE680804EF395F551BE190E6F8513549CCF33397A9A64103F8EFA76F8549D34A0D5AD11F32BC8968EC0A20E6F6FD1E63C5AD6C5DBBACF9A1EB42EE1097E0891B16C3AB1D1B75B7955E2A3F925
// REVISION: 1.0
// GUID: 5B620AE4-AFC7-4405-B5B0-F10DB333C75F
// DATE: 08\08\2022
// DIR: CAL\RPI\RPI_CAL_IO.c
/*********************************************************************
 *                  Flowcode CAL IO File
 *
 * File: RPI_CAL_IO.c
 *
 * (c) 2011-2018 Matrix TSL
 * http://www.matrixtsl.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
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
 * 191217 | LM | Created
 *
 *
 */
 

#ifndef MX_CAL_IO_C
#define MX_CAL_IO_C

#include "RPI_CAL_IO.h"

volatile MX_UINT32 *gpio;

void mx_delay_u(MX_UINT32 delay);
void mx_delay_m(MX_UINT32 delay);

MX_UINT32 *FC_CAL_GetRegisterMap(MX_UINT32 Offset)
{
	int fd = -1;
	MX_UINT32 *map = MAP_FAILED;
	
	if (Offset == MX_REGISTER_MAP_GPIO)
	{
		// This will currently only work on Stretch
		fd = open("/dev/gpiomem", O_RDWR | O_SYNC | O_CLOEXEC);
	}

	if (fd < 0)
	{
		// This will currently only work in root/sudo mode (needed for PWM)
		if ((fd = open("/dev/mem", O_RDWR | O_SYNC | O_CLOEXEC) ) < 0) return MAP_FAILED;
		Offset += MX_REGISTER_MAP_BASE;
	}

	map = (MX_UINT32 *)mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd, Offset);
	close(fd);
	return map;
}

void FC_CAL_PullupsOff(void)
{
	MX_GPIO_PULL = 0;
	mx_delay_u(100);
	MX_GPIO_PULLCLK0 = 0x7FFFFFF;
	mx_delay_u(100);
	MX_GPIO_PULLCLK0 = 0;
}

// was void FC_CAL_Port_Out_DDR(MX_UINT32 OutMask, MX_UINT32 OutValue)
void FC_CAL_GPIO_PORT_PUT_DDR(MX_UINT32 OutMask, MX_UINT32 OutValue)
{
	MX_UINT32 Pin = 0;
	MX_UINT32 PinMask = 1;
	while (OutMask)
	{
		if (OutMask & PinMask)
		{
			MX_GPIO_OUT(Pin);
			(OutValue & PinMask)?(MX_GPIO_SET(Pin)):(MX_GPIO_CLR(Pin));
			OutMask &= ~PinMask;
		}
		Pin++;
		PinMask <<= 1;
	}
}

// was MX_UINT32 FC_CAL_Port_In_DDR(MX_UINT32 InMask)
MX_UINT32 FC_CAL_GPIO_PORT_GET_DDR(MX_UINT32 InMask)
{
	MX_UINT32 Pin = 0;
	MX_UINT32 PinMask = InMask;
	while (PinMask)
	{
		if (PinMask & 1)
		{
			MX_GPIO_IN(Pin);
		}
		Pin++;
		PinMask >>= 1;
	}
	return (*(gpio+13)&(InMask));
}


void FC_CAL_GPIO_SET(MX_UINT8 p)
{
	if (p < MX_MAX_GPIO)
		MX_GPIO_SET(p);
}

void FC_CAL_GPIO_CLR(MX_UINT8 p)
{
	if (p < MX_MAX_GPIO)
		MX_GPIO_CLR(p);
}

void FC_CAL_GPIO_PUT(MX_UINT8 p, MX_UINT32 v)
{
	if (p < MX_MAX_GPIO)
	{
		if (v)
		{
			MX_GPIO_SET(p);
		}
		else
		{
			MX_GPIO_CLR(p);
		}
	}
}

MX_UINT32 FC_CAL_GPIO_GET(MX_UINT8 p)
{
	if (p < MX_MAX_GPIO)
		return MX_GPIO_GET(p);
	else
		return 0;
}

void FC_CAL_GPIO_SET_DDR(MX_UINT8 p)
{
	if (p < MX_MAX_GPIO)
	{
		MX_GPIO_OUT(p);
		MX_GPIO_SET(p);
	}
}

void FC_CAL_GPIO_CLR_DDR(MX_UINT8 p)
{
	if (p < MX_MAX_GPIO)
	{
		MX_GPIO_OUT(p);
		MX_GPIO_CLR(p);
	}
}

void FC_CAL_GPIO_PUT_DDR(MX_UINT8 p, MX_UINT32 v)
{
	if (p < MX_MAX_GPIO)
	{
		MX_GPIO_OUT(p);
		if (v)
		{
			MX_GPIO_SET(p);
		}
		else
		{
			MX_GPIO_CLR(p);
		}
	}
}

MX_UINT32 FC_CAL_GPIO_GET_DDR(MX_UINT8 p)
{
	if (p < MX_MAX_GPIO)
	{
		MX_GPIO_IN(p);
		return MX_GPIO_GET(p);
	}
	else
	{
		return 0;
	}
}

MX_UINT32 FC_CAL_GET_B_PORTA(MX_UINT8 pin)
{
	switch(pin)
	{
		case  1: return FC_CAL_GPIO_GET_DDR(MX_PORTA1_GPIO);
		case  2: return FC_CAL_GPIO_GET_DDR(MX_PORTA2_GPIO);
		case  3: return FC_CAL_GPIO_GET_DDR(MX_PORTA3_GPIO);
		case  4: return FC_CAL_GPIO_GET_DDR(MX_PORTA4_GPIO);
		case  5: return FC_CAL_GPIO_GET_DDR(MX_PORTA5_GPIO);
		case  6: return FC_CAL_GPIO_GET_DDR(MX_PORTA6_GPIO);
		case  7: return FC_CAL_GPIO_GET_DDR(MX_PORTA7_GPIO);
		default: return FC_CAL_GPIO_GET_DDR(MX_PORTA0_GPIO);
	}
}

MX_UINT32 FC_CAL_GET_B_PORTB(MX_UINT8 pin)
{
	switch(pin)
	{
		case  1: return FC_CAL_GPIO_GET_DDR(MX_PORTB1_GPIO);
		case  2: return FC_CAL_GPIO_GET_DDR(MX_PORTB2_GPIO);
		case  3: return FC_CAL_GPIO_GET_DDR(MX_PORTB3_GPIO);
		case  4: return FC_CAL_GPIO_GET_DDR(MX_PORTB4_GPIO);
		case  5: return FC_CAL_GPIO_GET_DDR(MX_PORTB5_GPIO);
		case  6: return FC_CAL_GPIO_GET_DDR(MX_PORTB6_GPIO);
		case  7: return FC_CAL_GPIO_GET_DDR(MX_PORTB7_GPIO);
		default: return FC_CAL_GPIO_GET_DDR(MX_PORTB0_GPIO);
	}
}

MX_UINT32 FC_CAL_GET_B_PORTC(MX_UINT8 pin)
{
	switch(pin)
	{
		case  1: return FC_CAL_GPIO_GET_DDR(MX_PORTC1_GPIO);
		case  2: return FC_CAL_GPIO_GET_DDR(MX_PORTC2_GPIO);
		case  3: return FC_CAL_GPIO_GET_DDR(MX_PORTC3_GPIO);
		case  4: return FC_CAL_GPIO_GET_DDR(MX_PORTC4_GPIO);
		case  5: return FC_CAL_GPIO_GET_DDR(MX_PORTC5_GPIO);
		case  6: return FC_CAL_GPIO_GET_DDR(MX_PORTC6_GPIO);
		case  7: return FC_CAL_GPIO_GET_DDR(MX_PORTC7_GPIO);
		default: return FC_CAL_GPIO_GET_DDR(MX_PORTC0_GPIO);
	}
}

MX_UINT32 FC_CAL_GET_B_PORTD(MX_UINT8 pin)
{
	switch(pin)
	{
		case  1: return FC_CAL_GPIO_GET_DDR(MX_PORTD1_GPIO);
		case  2: return FC_CAL_GPIO_GET_DDR(MX_PORTD2_GPIO);
		case  3: return FC_CAL_GPIO_GET_DDR(MX_PORTD3_GPIO);
		case  4: return FC_CAL_GPIO_GET_DDR(MX_PORTD4_GPIO);
		case  5: return FC_CAL_GPIO_GET_DDR(MX_PORTD5_GPIO);
		case  6: return FC_CAL_GPIO_GET_DDR(MX_PORTD6_GPIO);
		case  7: return FC_CAL_GPIO_GET_DDR(MX_PORTD7_GPIO);
		default: return FC_CAL_GPIO_GET_DDR(MX_PORTD0_GPIO);
	}
}

MX_UINT32 FC_CAL_GET_M_PORTA(MX_UINT32 mask)
{
	MX_UINT32 result = 0;
	if (mask & 0x01) {if (FC_CAL_GPIO_GET_DDR(MX_PORTA0_GPIO)) result |= 0x01;};
	if (mask & 0x02) {if (FC_CAL_GPIO_GET_DDR(MX_PORTA1_GPIO)) result |= 0x02;};
	if (mask & 0x04) {if (FC_CAL_GPIO_GET_DDR(MX_PORTA2_GPIO)) result |= 0x04;};
	if (mask & 0x08) {if (FC_CAL_GPIO_GET_DDR(MX_PORTA3_GPIO)) result |= 0x08;};
	if (mask & 0x10) {if (FC_CAL_GPIO_GET_DDR(MX_PORTA4_GPIO)) result |= 0x10;};
	if (mask & 0x20) {if (FC_CAL_GPIO_GET_DDR(MX_PORTA5_GPIO)) result |= 0x20;};
	if (mask & 0x40) {if (FC_CAL_GPIO_GET_DDR(MX_PORTA6_GPIO)) result |= 0x40;};
	if (mask & 0x80) {if (FC_CAL_GPIO_GET_DDR(MX_PORTA7_GPIO)) result |= 0x80;};
	return result;
}

MX_UINT32 FC_CAL_GET_M_PORTB(MX_UINT32 mask)
{
	MX_UINT32 result = 0;
	if (mask & 0x01) {if (FC_CAL_GPIO_GET_DDR(MX_PORTB0_GPIO)) result |= 0x01;};
	if (mask & 0x02) {if (FC_CAL_GPIO_GET_DDR(MX_PORTB1_GPIO)) result |= 0x02;};
	if (mask & 0x04) {if (FC_CAL_GPIO_GET_DDR(MX_PORTB2_GPIO)) result |= 0x04;};
	if (mask & 0x08) {if (FC_CAL_GPIO_GET_DDR(MX_PORTB3_GPIO)) result |= 0x08;};
	if (mask & 0x10) {if (FC_CAL_GPIO_GET_DDR(MX_PORTB4_GPIO)) result |= 0x10;};
	if (mask & 0x20) {if (FC_CAL_GPIO_GET_DDR(MX_PORTB5_GPIO)) result |= 0x20;};
	if (mask & 0x40) {if (FC_CAL_GPIO_GET_DDR(MX_PORTB6_GPIO)) result |= 0x40;};
	if (mask & 0x80) {if (FC_CAL_GPIO_GET_DDR(MX_PORTB7_GPIO)) result |= 0x80;};
	return result;
}

MX_UINT32 FC_CAL_GET_M_PORTC(MX_UINT32 mask)
{
	MX_UINT32 result = 0;
	if (mask & 0x01) {if (FC_CAL_GPIO_GET_DDR(MX_PORTC0_GPIO)) result |= 0x01;};
	if (mask & 0x02) {if (FC_CAL_GPIO_GET_DDR(MX_PORTC1_GPIO)) result |= 0x02;};
	if (mask & 0x04) {if (FC_CAL_GPIO_GET_DDR(MX_PORTC2_GPIO)) result |= 0x04;};
	if (mask & 0x08) {if (FC_CAL_GPIO_GET_DDR(MX_PORTC3_GPIO)) result |= 0x08;};
	if (mask & 0x10) {if (FC_CAL_GPIO_GET_DDR(MX_PORTC4_GPIO)) result |= 0x10;};
	if (mask & 0x20) {if (FC_CAL_GPIO_GET_DDR(MX_PORTC5_GPIO)) result |= 0x20;};
	if (mask & 0x40) {if (FC_CAL_GPIO_GET_DDR(MX_PORTC6_GPIO)) result |= 0x40;};
	if (mask & 0x80) {if (FC_CAL_GPIO_GET_DDR(MX_PORTC7_GPIO)) result |= 0x80;};
	return result;
}

MX_UINT32 FC_CAL_GET_M_PORTD(MX_UINT32 mask)
{
	MX_UINT32 result = 0;
	if (mask & 0x01) {if (FC_CAL_GPIO_GET_DDR(MX_PORTD0_GPIO)) result |= 0x01;};
	if (mask & 0x02) {if (FC_CAL_GPIO_GET_DDR(MX_PORTD1_GPIO)) result |= 0x02;};
	if (mask & 0x04) {if (FC_CAL_GPIO_GET_DDR(MX_PORTD2_GPIO)) result |= 0x04;};
	if (mask & 0x08) {if (FC_CAL_GPIO_GET_DDR(MX_PORTD3_GPIO)) result |= 0x08;};
	if (mask & 0x10) {if (FC_CAL_GPIO_GET_DDR(MX_PORTD4_GPIO)) result |= 0x10;};
	if (mask & 0x20) {if (FC_CAL_GPIO_GET_DDR(MX_PORTD5_GPIO)) result |= 0x20;};
	if (mask & 0x40) {if (FC_CAL_GPIO_GET_DDR(MX_PORTD6_GPIO)) result |= 0x40;};
	if (mask & 0x80) {if (FC_CAL_GPIO_GET_DDR(MX_PORTD7_GPIO)) result |= 0x80;};
	return result;
}

void FC_CAL_PUT_B_PORTA(MX_UINT8 pin, MX_UINT32 value)
{
	switch(pin)
	{
		case  1: FC_CAL_GPIO_PUT_DDR(MX_PORTA1_GPIO, value); break;
		case  2: FC_CAL_GPIO_PUT_DDR(MX_PORTA2_GPIO, value); break;
		case  3: FC_CAL_GPIO_PUT_DDR(MX_PORTA3_GPIO, value); break;
		case  4: FC_CAL_GPIO_PUT_DDR(MX_PORTA4_GPIO, value); break;
		case  5: FC_CAL_GPIO_PUT_DDR(MX_PORTA5_GPIO, value); break;
		case  6: FC_CAL_GPIO_PUT_DDR(MX_PORTA6_GPIO, value); break;
		case  7: FC_CAL_GPIO_PUT_DDR(MX_PORTA7_GPIO, value); break;
		default: FC_CAL_GPIO_PUT_DDR(MX_PORTA0_GPIO, value); break;
	}
}

void FC_CAL_PUT_B_PORTB(MX_UINT8 pin, MX_UINT32 value)
{
	switch(pin)
	{
		case  1: FC_CAL_GPIO_PUT_DDR(MX_PORTB1_GPIO, value); break;
		case  2: FC_CAL_GPIO_PUT_DDR(MX_PORTB2_GPIO, value); break;
		case  3: FC_CAL_GPIO_PUT_DDR(MX_PORTB3_GPIO, value); break;
		case  4: FC_CAL_GPIO_PUT_DDR(MX_PORTB4_GPIO, value); break;
		case  5: FC_CAL_GPIO_PUT_DDR(MX_PORTB5_GPIO, value); break;
		case  6: FC_CAL_GPIO_PUT_DDR(MX_PORTB6_GPIO, value); break;
		case  7: FC_CAL_GPIO_PUT_DDR(MX_PORTB7_GPIO, value); break;
		default: FC_CAL_GPIO_PUT_DDR(MX_PORTB0_GPIO, value); break;
	}
}

void FC_CAL_PUT_B_PORTC(MX_UINT8 pin, MX_UINT32 value)
{
	switch(pin)
	{
		case  1: FC_CAL_GPIO_PUT_DDR(MX_PORTC1_GPIO, value); break;
		case  2: FC_CAL_GPIO_PUT_DDR(MX_PORTC2_GPIO, value); break;
		case  3: FC_CAL_GPIO_PUT_DDR(MX_PORTC3_GPIO, value); break;
		case  4: FC_CAL_GPIO_PUT_DDR(MX_PORTC4_GPIO, value); break;
		case  5: FC_CAL_GPIO_PUT_DDR(MX_PORTC5_GPIO, value); break;
		case  6: FC_CAL_GPIO_PUT_DDR(MX_PORTC6_GPIO, value); break;
		case  7: FC_CAL_GPIO_PUT_DDR(MX_PORTC7_GPIO, value); break;
		default: FC_CAL_GPIO_PUT_DDR(MX_PORTC0_GPIO, value); break;
	}
}

void FC_CAL_PUT_B_PORTD(MX_UINT8 pin, MX_UINT32 value)
{
	switch(pin)
	{
		case  1: FC_CAL_GPIO_PUT_DDR(MX_PORTD1_GPIO, value); break;
		case  2: FC_CAL_GPIO_PUT_DDR(MX_PORTD2_GPIO, value); break;
		case  3: FC_CAL_GPIO_PUT_DDR(MX_PORTD3_GPIO, value); break;
		case  4: FC_CAL_GPIO_PUT_DDR(MX_PORTD4_GPIO, value); break;
		case  5: FC_CAL_GPIO_PUT_DDR(MX_PORTD5_GPIO, value); break;
		case  6: FC_CAL_GPIO_PUT_DDR(MX_PORTD6_GPIO, value); break;
		case  7: FC_CAL_GPIO_PUT_DDR(MX_PORTD7_GPIO, value); break;
		default: FC_CAL_GPIO_PUT_DDR(MX_PORTD0_GPIO, value); break;
	}
}

void FC_CAL_PUT_M_PORTA(MX_UINT32 mask, MX_UINT32 value)
{
	if (mask & 0x01) FC_CAL_GPIO_PUT_DDR(MX_PORTA0_GPIO, 0x01 & value);
	if (mask & 0x02) FC_CAL_GPIO_PUT_DDR(MX_PORTA1_GPIO, 0x02 & value);
	if (mask & 0x04) FC_CAL_GPIO_PUT_DDR(MX_PORTA2_GPIO, 0x04 & value);
	if (mask & 0x08) FC_CAL_GPIO_PUT_DDR(MX_PORTA3_GPIO, 0x08 & value);
	if (mask & 0x10) FC_CAL_GPIO_PUT_DDR(MX_PORTA4_GPIO, 0x10 & value);
	if (mask & 0x20) FC_CAL_GPIO_PUT_DDR(MX_PORTA5_GPIO, 0x20 & value);
	if (mask & 0x40) FC_CAL_GPIO_PUT_DDR(MX_PORTA6_GPIO, 0x40 & value);
	if (mask & 0x80) FC_CAL_GPIO_PUT_DDR(MX_PORTA7_GPIO, 0x80 & value);
}

void FC_CAL_PUT_M_PORTB(MX_UINT32 mask, MX_UINT32 value)
{
	if (mask & 0x01) FC_CAL_GPIO_PUT_DDR(MX_PORTB0_GPIO, 0x01 & value);
	if (mask & 0x02) FC_CAL_GPIO_PUT_DDR(MX_PORTB1_GPIO, 0x02 & value);
	if (mask & 0x04) FC_CAL_GPIO_PUT_DDR(MX_PORTB2_GPIO, 0x04 & value);
	if (mask & 0x08) FC_CAL_GPIO_PUT_DDR(MX_PORTB3_GPIO, 0x08 & value);
	if (mask & 0x10) FC_CAL_GPIO_PUT_DDR(MX_PORTB4_GPIO, 0x10 & value);
	if (mask & 0x20) FC_CAL_GPIO_PUT_DDR(MX_PORTB5_GPIO, 0x20 & value);
	if (mask & 0x40) FC_CAL_GPIO_PUT_DDR(MX_PORTB6_GPIO, 0x40 & value);
	if (mask & 0x80) FC_CAL_GPIO_PUT_DDR(MX_PORTB7_GPIO, 0x80 & value);
}

void FC_CAL_PUT_M_PORTC(MX_UINT32 mask, MX_UINT32 value)
{
	if (mask & 0x01) FC_CAL_GPIO_PUT_DDR(MX_PORTC0_GPIO, 0x01 & value);
	if (mask & 0x02) FC_CAL_GPIO_PUT_DDR(MX_PORTC1_GPIO, 0x02 & value);
	if (mask & 0x04) FC_CAL_GPIO_PUT_DDR(MX_PORTC2_GPIO, 0x04 & value);
	if (mask & 0x08) FC_CAL_GPIO_PUT_DDR(MX_PORTC3_GPIO, 0x08 & value);
	if (mask & 0x10) FC_CAL_GPIO_PUT_DDR(MX_PORTC4_GPIO, 0x10 & value);
	if (mask & 0x20) FC_CAL_GPIO_PUT_DDR(MX_PORTC5_GPIO, 0x20 & value);
	if (mask & 0x40) FC_CAL_GPIO_PUT_DDR(MX_PORTC6_GPIO, 0x40 & value);
	if (mask & 0x80) FC_CAL_GPIO_PUT_DDR(MX_PORTC7_GPIO, 0x80 & value);
}

void FC_CAL_PUT_M_PORTD(MX_UINT32 mask, MX_UINT32 value)
{
	if (mask & 0x01) FC_CAL_GPIO_PUT_DDR(MX_PORTD0_GPIO, 0x01 & value);
	if (mask & 0x02) FC_CAL_GPIO_PUT_DDR(MX_PORTD1_GPIO, 0x02 & value);
	if (mask & 0x04) FC_CAL_GPIO_PUT_DDR(MX_PORTD2_GPIO, 0x04 & value);
	if (mask & 0x08) FC_CAL_GPIO_PUT_DDR(MX_PORTD3_GPIO, 0x08 & value);
	if (mask & 0x10) FC_CAL_GPIO_PUT_DDR(MX_PORTD4_GPIO, 0x10 & value);
	if (mask & 0x20) FC_CAL_GPIO_PUT_DDR(MX_PORTD5_GPIO, 0x20 & value);
	if (mask & 0x40) FC_CAL_GPIO_PUT_DDR(MX_PORTD6_GPIO, 0x40 & value);
	if (mask & 0x80) FC_CAL_GPIO_PUT_DDR(MX_PORTD7_GPIO, 0x80 & value);
}

#endif // MX_CAL_IO_C
