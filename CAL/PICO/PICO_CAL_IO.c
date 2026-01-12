// CRC: F9C65A77A483DDF22B438B7FEB8E3C81451B6760FECB07508D29EE770BB95F4716F8D538056A8D1637947D276E0FE9699A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF565935E81A6FF8DCC02073EE31F8184EA2931F9C433015276127D16D54A41CDF6F4880638219D8050668918053A8F5F39FA6CFC277E8F1EFB72C58CD89CF5E47C6D7F926A93C98EA0A9B8C5A42AB8D1F8A8A4E8676377D932549D34A0D5AD11F3EE792CC44C1EA9FE354400186E3120F1D7A2EF74D6E9726C3D04CF7CD5577C5FE9D77FAA9053C2CE
// REVISION: 1.0
// GUID: 5865D50D-623C-427E-9B88-56B0F4AF2A68
// DATE: 08\08\2022
// DIR: CAL\PICO\PICO_CAL_IO.c

/*********************************************************************
 *                  Flowcode CAL IO File
 *
 * File: PICO_CAL_IO.c
 *
 * (c) 2021 Matrix TSL.
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
 * 260521 | LM | Created
 *
 */

#include "PICO_CAL_IO.h"

// GPIO Pin mode mask. Bit set when pin initialised as IO 
MX_UINT32 MX_GPIO_INIT_FLAGS = 0;

// Keep this line to increase the speed of I/O, comment out to reduce code usage
#define MX_USE_INLINE

#ifdef MX_USE_INLINE
  #define MX_PICO_IO_INLINE inline
#else
  #define MX_PICO_IO_INLINE
#endif


static MX_PICO_IO_INLINE void FC_PICO_CAL_Port_Out_DDR (MX_UINT8 Port, MX_UINT32 Mask, MX_UINT32 Value)
{
	if ((MX_GPIO_INIT_FLAGS & Mask) ^ Mask)
	{
		gpio_init_mask(Mask);
		MX_GPIO_INIT_FLAGS |= Mask;
	}
	gpio_set_dir_out_masked(Mask);
	gpio_put_masked(Mask, Value);
}

static MX_PICO_IO_INLINE void FC_PICO_CAL_Bit_Low_DDR (MX_UINT8 Pin)
{
	MX_UINT32 Mask = 1ul << (Pin);
	if (!(MX_GPIO_INIT_FLAGS & Mask))
	{
		gpio_init(Pin);
		MX_GPIO_INIT_FLAGS |= Mask;
	}
	gpio_set_dir_out_masked(Mask);
	gpio_clr_mask(Mask);
}

static MX_PICO_IO_INLINE void FC_PICO_CAL_Bit_High_DDR (MX_UINT8 Pin)
{
	MX_UINT32 Mask = 1ul << (Pin);
	if (!(MX_GPIO_INIT_FLAGS & Mask))
	{
		gpio_init(Pin);
		MX_GPIO_INIT_FLAGS |= Mask;
	}
	gpio_set_dir_out_masked(Mask);
	gpio_set_mask(Mask);
}

static MX_PICO_IO_INLINE void FC_PICO_CAL_Bit_Out_DDR (MX_UINT8 Pin, MX_UINT8 Value)
{
	MX_UINT32 Mask = 1ul << (Pin);
	if (!(MX_GPIO_INIT_FLAGS & Mask))
	{
		gpio_init(Pin);
		MX_GPIO_INIT_FLAGS |= Mask;
	}
	gpio_set_dir_out_masked(Mask);
    if (Value)
        gpio_set_mask(Mask);
    else
        gpio_clr_mask(Mask);
}

static MX_PICO_IO_INLINE MX_UINT32 FC_PICO_CAL_Port_In_DDR (MX_UINT8 Port, MX_UINT32 Mask)
{
	if ((MX_GPIO_INIT_FLAGS & Mask) ^ Mask)
	{
		gpio_init_mask(Mask);
		MX_GPIO_INIT_FLAGS |= Mask;
	}
	gpio_set_dir_in_masked(Mask);
	return (MX_UINT32)(gpio_get_all() & Mask);
}

static MX_PICO_IO_INLINE MX_UINT8 FC_PICO_CAL_Bit_In_DDR (MX_UINT8 Pin)
{
	MX_UINT32 Mask = 1ul << (Pin);
	if (!(MX_GPIO_INIT_FLAGS & Mask))
	{
		gpio_init(Pin);
		MX_GPIO_INIT_FLAGS |= Mask;
	}
	gpio_set_dir_in_masked(Mask);
	return (MX_UINT8)(!!(gpio_get_all() & Mask));
}


