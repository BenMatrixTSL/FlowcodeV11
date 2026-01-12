// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BEA99F79DF56372A99CEABC1DCFEB790029A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5ECE5D94893D6F6995226350A737298D1DECDEBF1C00C87E767BDD1E8A08CC214166FBE0B7F76E90A9B408C866B29F69A3A572FB7C7384619FDE0704210F71F16ABC01007072B2188134ACEBFC949235A01BD7AD8F39DEE8D549D34A0D5AD11F30ED77C12B1D0D2BE23B56F1F03441DFE438F9B8FEFA7266CAFA22E870078457321B85372DCE0C3F0
// REVISION: 1.0
// GUID: 98C9DF97-DA17-4B8F-90EA-974879DAEF5C
// DATE: 08\08\2022
// DIR: CAL\STARM\STARM_CAL_IO.c
/*********************************************************************
 *                  Flowcode CAL IO File
 *
 * File: AVR_CAL_IO.c
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
 * 020312 | BR | Updated to v5.1 CAL Schema
 *
 */

#include "STARM_CAL_IO.h"

#ifdef MX_BL0061_PINMAP

	#define GPIO_BIT_INP(p,b)	{GPIO##p->MODER&=~(3<<((b)*2));}
	#define GPIO_BIT_GET(p,b)	((GPIO##p->IDR & (1<<b)) >> b)

	#define GPIO_BIT_OUT(p,b)	{GPIO##p->MODER&=~(2<<((b)*2));GPIO##p->MODER|=(1<<((b)*2));}
	#define GPIO_BIT_SET(p,b,v)	{if(v)GPIO##p->BSRR = 1<<b; else GPIO##p->BSRR = 1<<(b+16);}


	static void FC_CAL_Port_Out__A( uint16_t OutMask, uint16_t OutValue )
	{
		if (OutMask & 0x01)
		{
			GPIO_BIT_SET(A, 0, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			GPIO_BIT_SET(A, 1, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			GPIO_BIT_SET(C, 14, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			GPIO_BIT_SET(C, 15, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			GPIO_BIT_SET(A, 13, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			GPIO_BIT_SET(A, 14, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			GPIO_BIT_SET(A, 11, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			GPIO_BIT_SET(A, 12, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out_DDR__A( uint16_t OutMask, uint16_t OutValue )
	{
		if (OutMask & 0x01)
		{
			GPIO_BIT_OUT(A, 0);
			GPIO_BIT_SET(A, 0, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			GPIO_BIT_OUT(A, 1);
			GPIO_BIT_SET(A, 1, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			GPIO_BIT_OUT(C, 14);
			GPIO_BIT_SET(C, 14, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			GPIO_BIT_OUT(C, 15);
			GPIO_BIT_SET(C, 15, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			GPIO_BIT_OUT(A, 13);
			GPIO_BIT_SET(A, 13, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			GPIO_BIT_OUT(A, 14);
			GPIO_BIT_SET(A, 14, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			GPIO_BIT_OUT(A, 11);
			GPIO_BIT_SET(A, 11, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			GPIO_BIT_OUT(A, 12);
			GPIO_BIT_SET(A, 12, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out__B( uint16_t OutMask, uint16_t OutValue )
	{
		if (OutMask & 0x01)
		{
			GPIO_BIT_SET(B, 0, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			GPIO_BIT_SET(B, 1, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			GPIO_BIT_SET(B, 2, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			GPIO_BIT_SET(D, 2, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			GPIO_BIT_SET(B, 4, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			GPIO_BIT_SET(B, 5, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			GPIO_BIT_SET(B, 6, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			GPIO_BIT_SET(B, 7, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out_DDR__B( uint16_t OutMask, uint16_t OutValue )
	{
		if (OutMask & 0x01)
		{
			GPIO_BIT_OUT(B, 0);
			GPIO_BIT_SET(B, 0, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			GPIO_BIT_OUT(B, 1);
			GPIO_BIT_SET(B, 1, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			GPIO_BIT_OUT(B, 2);
			GPIO_BIT_SET(B, 2, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			GPIO_BIT_OUT(D, 2);
			GPIO_BIT_SET(D, 2, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			GPIO_BIT_OUT(B, 4);
			GPIO_BIT_SET(B, 4, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			GPIO_BIT_OUT(B, 5);
			GPIO_BIT_SET(B, 5, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			GPIO_BIT_OUT(B, 6);
			GPIO_BIT_SET(B, 6, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			GPIO_BIT_OUT(B, 7);
			GPIO_BIT_SET(B, 7, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out__C( uint16_t OutMask, uint16_t OutValue )
	{
		if (OutMask & 0x01)
		{
			GPIO_BIT_SET(C, 0, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			GPIO_BIT_SET(C, 1, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			GPIO_BIT_SET(C, 2, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			GPIO_BIT_SET(C, 3, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			GPIO_BIT_SET(C, 4, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			GPIO_BIT_SET(C, 5, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			GPIO_BIT_SET(C, 8, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			GPIO_BIT_SET(C, 13, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out_DDR__C( uint16_t OutMask, uint16_t OutValue )
	{
		if (OutMask & 0x01)
		{
			GPIO_BIT_OUT(C, 0);
			GPIO_BIT_SET(C, 0, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			GPIO_BIT_OUT(C, 1);
			GPIO_BIT_SET(C, 1, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			GPIO_BIT_OUT(C, 2);
			GPIO_BIT_SET(C, 2, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			GPIO_BIT_OUT(C, 3);
			GPIO_BIT_SET(C, 3, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			GPIO_BIT_OUT(C, 4);
			GPIO_BIT_SET(C, 4, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			GPIO_BIT_OUT(C, 5);
			GPIO_BIT_SET(C, 5, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			GPIO_BIT_OUT(C, 8);
			GPIO_BIT_SET(C, 8, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			GPIO_BIT_OUT(C, 13);
			GPIO_BIT_SET(C, 13, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out__D( uint16_t OutMask, uint16_t OutValue )
	{
		if (OutMask & 0x01)
		{
			GPIO_BIT_SET(A, 10, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			GPIO_BIT_SET(A, 9, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			GPIO_BIT_SET(A, 4, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			GPIO_BIT_SET(A, 7, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			GPIO_BIT_SET(A, 6, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			GPIO_BIT_SET(A, 5, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			GPIO_BIT_SET(B, 8, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			GPIO_BIT_SET(B, 9, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out_DDR__D( uint16_t OutMask, uint16_t OutValue )
	{
		if (OutMask & 0x01)
		{
			GPIO_BIT_OUT(A, 10);
			GPIO_BIT_SET(A, 10, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			GPIO_BIT_OUT(A, 9);
			GPIO_BIT_SET(A, 9, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			GPIO_BIT_OUT(A, 4);
			GPIO_BIT_SET(A, 4, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			GPIO_BIT_OUT(A, 7);
			GPIO_BIT_SET(A, 7, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			GPIO_BIT_OUT(A, 6);
			GPIO_BIT_SET(A, 6, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			GPIO_BIT_OUT(A, 5);
			GPIO_BIT_SET(A, 5, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			GPIO_BIT_OUT(B, 8);
			GPIO_BIT_SET(B, 8, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			GPIO_BIT_OUT(B, 9);
			GPIO_BIT_SET(B, 9, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out__E( uint16_t OutMask, uint16_t OutValue )
	{
		if (OutMask & 0x01)
		{
			GPIO_BIT_SET(A, 3, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			GPIO_BIT_SET(A, 2, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			GPIO_BIT_SET(B, 12, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			GPIO_BIT_SET(B, 15, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			GPIO_BIT_SET(B, 14, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			GPIO_BIT_SET(B, 13, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			GPIO_BIT_SET(B, 10, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			GPIO_BIT_SET(B, 3, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out_DDR__E( uint16_t OutMask, uint16_t OutValue )
	{
		if (OutMask & 0x01)
		{
			GPIO_BIT_OUT(A, 3);
			GPIO_BIT_SET(A, 3, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			GPIO_BIT_OUT(A, 2);
			GPIO_BIT_SET(A, 2, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			GPIO_BIT_OUT(B, 12);
			GPIO_BIT_SET(B, 12, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			GPIO_BIT_OUT(B, 15);
			GPIO_BIT_SET(B, 15, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			GPIO_BIT_OUT(B, 14);
			GPIO_BIT_SET(B, 14, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			GPIO_BIT_OUT(B, 13);
			GPIO_BIT_SET(B, 13, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			GPIO_BIT_OUT(B, 10);
			GPIO_BIT_SET(B, 10, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			GPIO_BIT_OUT(B, 3);
			GPIO_BIT_SET(B, 3, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out__F( uint16_t OutMask, uint16_t OutValue )
	{
		if (OutMask & 0x01)
		{
			GPIO_BIT_SET(C, 7, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			GPIO_BIT_SET(C, 6, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			GPIO_BIT_SET(A, 15, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			GPIO_BIT_SET(C, 12, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			GPIO_BIT_SET(C, 11, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			GPIO_BIT_SET(C, 10, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			GPIO_BIT_SET(A, 8, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			GPIO_BIT_SET(C, 9, OutValue & 0x80);
		}
	}

	static void FC_CAL_Port_Out_DDR__F( uint16_t OutMask, uint16_t OutValue )
	{
		if (OutMask & 0x01)
		{
			GPIO_BIT_OUT(C, 7);
			GPIO_BIT_SET(C, 7, OutValue & 0x01);
		}
		if (OutMask & 0x02)
		{
			GPIO_BIT_OUT(C, 6);
			GPIO_BIT_SET(C, 6, OutValue & 0x02);
		}
		if (OutMask & 0x04)
		{
			GPIO_BIT_OUT(A, 15);
			GPIO_BIT_SET(A, 15, OutValue & 0x04);
		}
		if (OutMask & 0x08)
		{
			GPIO_BIT_OUT(C, 12);
			GPIO_BIT_SET(C, 12, OutValue & 0x08);
		}
		if (OutMask & 0x10)
		{
			GPIO_BIT_OUT(C, 11);
			GPIO_BIT_SET(C, 11, OutValue & 0x10);
		}
		if (OutMask & 0x20)
		{
			GPIO_BIT_OUT(C, 10);
			GPIO_BIT_SET(C, 10, OutValue & 0x20);
		}
		if (OutMask & 0x40)
		{
			GPIO_BIT_OUT(A, 8);
			GPIO_BIT_SET(A, 8, OutValue & 0x40);
		}
		if (OutMask & 0x80)
		{
			GPIO_BIT_OUT(C, 9);
			GPIO_BIT_SET(C, 9, OutValue & 0x80);
		}
	}





	static char FC_CAL_Port_In__A( uint16_t InMask, uint16_t Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			retval |= GPIO_BIT_GET(A, 0);
		}
		if (InMask & 0x02)
		{
			retval |= GPIO_BIT_GET(A, 1) << 1;
		}
		if (InMask & 0x04)
		{
			retval |= GPIO_BIT_GET(C, 14) << 2;
		}
		if (InMask & 0x08)
		{
			retval |= GPIO_BIT_GET(C, 15) << 3;
		}
		if (InMask & 0x10)
		{
			retval |= GPIO_BIT_GET(A, 13) << 4;
		}
		if (InMask & 0x20)
		{
			retval |= GPIO_BIT_GET(A, 14) << 5;
		}
		if (InMask & 0x40)
		{
			retval |= GPIO_BIT_GET(A, 11) << 6;
		}
		if (InMask & 0x80)
		{
			retval |= GPIO_BIT_GET(A, 12) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In_DDR__A( uint16_t InMask, uint16_t Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			GPIO_BIT_INP(A, 0);
			retval |= GPIO_BIT_GET(A, 0);
		}
		if (InMask & 0x02)
		{
			GPIO_BIT_INP(A, 1);
			retval |= GPIO_BIT_GET(A, 1) << 1;
		}
		if (InMask & 0x04)
		{
			GPIO_BIT_INP(C, 14);
			retval |= GPIO_BIT_GET(C, 14) << 2;
		}
		if (InMask & 0x08)
		{
			GPIO_BIT_INP(C, 15);
			retval |= GPIO_BIT_GET(C, 15) << 3;
		}
		if (InMask & 0x10)
		{
			GPIO_BIT_INP(A, 13);
			retval |= GPIO_BIT_GET(A, 13) << 4;
		}
		if (InMask & 0x20)
		{
			GPIO_BIT_INP(A, 14);
			retval |= GPIO_BIT_GET(A, 14) << 5;
		}
		if (InMask & 0x40)
		{
			GPIO_BIT_INP(A, 11);
			retval |= GPIO_BIT_GET(A, 11) << 6;
		}
		if (InMask & 0x80)
		{
			GPIO_BIT_INP(A, 12);
			retval |= GPIO_BIT_GET(A, 12) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In__B( uint16_t InMask, uint16_t Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			retval |= GPIO_BIT_GET(B, 0);
		}
		if (InMask & 0x02)
		{
			retval |= GPIO_BIT_GET(B, 1) << 1;
		}
		if (InMask & 0x04)
		{
			retval |= GPIO_BIT_GET(B, 2) << 2;
		}
		if (InMask & 0x08)
		{
			retval |= GPIO_BIT_GET(D, 2) << 3;
		}
		if (InMask & 0x10)
		{
			retval |= GPIO_BIT_GET(B, 4) << 4;
		}
		if (InMask & 0x20)
		{
			retval |= GPIO_BIT_GET(B, 5) << 5;
		}
		if (InMask & 0x40)
		{
			retval |= GPIO_BIT_GET(B, 6) << 6;
		}
		if (InMask & 0x80)
		{
			retval |= GPIO_BIT_GET(B, 7) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In_DDR__B( uint16_t InMask, uint16_t Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			GPIO_BIT_INP(B, 0);
			retval |= GPIO_BIT_GET(B, 0);
		}
		if (InMask & 0x02)
		{
			GPIO_BIT_INP(B, 1);
			retval |= GPIO_BIT_GET(B, 1) << 1;
		}
		if (InMask & 0x04)
		{
			GPIO_BIT_INP(B, 2);
			retval |= GPIO_BIT_GET(B, 2) << 2;
		}
		if (InMask & 0x08)
		{
			GPIO_BIT_INP(D, 2);
			retval |= GPIO_BIT_GET(D, 2) << 3;
		}
		if (InMask & 0x10)
		{
			GPIO_BIT_INP(B, 4);
			retval |= GPIO_BIT_GET(B, 4) << 4;
		}
		if (InMask & 0x20)
		{
			GPIO_BIT_INP(B, 5);
			retval |= GPIO_BIT_GET(B, 5) << 5;
		}
		if (InMask & 0x40)
		{
			GPIO_BIT_INP(B, 6);
			retval |= GPIO_BIT_GET(B, 6) << 6;
		}
		if (InMask & 0x80)
		{
			GPIO_BIT_INP(B, 7);
			retval |= GPIO_BIT_GET(B, 7) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In__C( uint16_t InMask, uint16_t Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			retval |= GPIO_BIT_GET(C, 0);
		}
		if (InMask & 0x02)
		{
			retval |= GPIO_BIT_GET(C, 1) << 1;
		}
		if (InMask & 0x04)
		{
			retval |= GPIO_BIT_GET(C, 2) << 2;
		}
		if (InMask & 0x08)
		{
			retval |= GPIO_BIT_GET(C, 3) << 3;
		}
		if (InMask & 0x10)
		{
			retval |= GPIO_BIT_GET(C, 4) << 4;
		}
		if (InMask & 0x20)
		{
			retval |= GPIO_BIT_GET(C, 5) << 5;
		}
		if (InMask & 0x40)
		{
			retval |= GPIO_BIT_GET(C, 8) << 6;
		}
		if (InMask & 0x80)
		{
			retval |= GPIO_BIT_GET(C, 13) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In_DDR__C( uint16_t InMask, uint16_t Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			GPIO_BIT_INP(C, 0);
			retval |= GPIO_BIT_GET(C, 0);
		}
		if (InMask & 0x02)
		{
			GPIO_BIT_INP(C, 1);
			retval |= GPIO_BIT_GET(C, 1) << 1;
		}
		if (InMask & 0x04)
		{
			GPIO_BIT_INP(C, 2);
			retval |= GPIO_BIT_GET(C, 2) << 2;
		}
		if (InMask & 0x08)
		{
			GPIO_BIT_INP(C, 3);
			retval |= GPIO_BIT_GET(C, 3) << 3;
		}
		if (InMask & 0x10)
		{
			GPIO_BIT_INP(C, 4);
			retval |= GPIO_BIT_GET(C, 4) << 4;
		}
		if (InMask & 0x20)
		{
			GPIO_BIT_INP(C, 5);
			retval |= GPIO_BIT_GET(C, 5) << 5;
		}
		if (InMask & 0x40)
		{
			GPIO_BIT_INP(C, 8);
			retval |= GPIO_BIT_GET(C, 8) << 6;
		}
		if (InMask & 0x80)
		{
			GPIO_BIT_INP(C, 13);
			retval |= GPIO_BIT_GET(C, 13) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In__D( uint16_t InMask, uint16_t Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			retval |= GPIO_BIT_GET(A, 10);
		}
		if (InMask & 0x02)
		{
			retval |= GPIO_BIT_GET(A, 9) << 1;
		}
		if (InMask & 0x04)
		{
			retval |= GPIO_BIT_GET(A, 4) << 2;
		}
		if (InMask & 0x08)
		{
			retval |= GPIO_BIT_GET(A, 7) << 3;
		}
		if (InMask & 0x10)
		{
			retval |= GPIO_BIT_GET(A, 6) << 4;
		}
		if (InMask & 0x20)
		{
			retval |= GPIO_BIT_GET(A, 5) << 5;
		}
		if (InMask & 0x40)
		{
			retval |= GPIO_BIT_GET(B, 8) << 6;
		}
		if (InMask & 0x80)
		{
			retval |= GPIO_BIT_GET(B, 9) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In_DDR__D( uint16_t InMask, uint16_t Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			GPIO_BIT_INP(A, 10);
			retval |= GPIO_BIT_GET(A, 10);
		}
		if (InMask & 0x02)
		{
			GPIO_BIT_INP(A, 9);
			retval |= GPIO_BIT_GET(A, 9) << 1;
		}
		if (InMask & 0x04)
		{
			GPIO_BIT_INP(A, 4);
			retval |= GPIO_BIT_GET(A, 4) << 2;
		}
		if (InMask & 0x08)
		{
			GPIO_BIT_INP(A, 7);
			retval |= GPIO_BIT_GET(A, 7) << 3;
		}
		if (InMask & 0x10)
		{
			GPIO_BIT_INP(A, 6);
			retval |= GPIO_BIT_GET(A, 6) << 4;
		}
		if (InMask & 0x20)
		{
			GPIO_BIT_INP(A, 5);
			retval |= GPIO_BIT_GET(A, 5) << 5;
		}
		if (InMask & 0x40)
		{
			GPIO_BIT_INP(B, 8);
			retval |= GPIO_BIT_GET(B, 8) << 6;
		}
		if (InMask & 0x80)
		{
			GPIO_BIT_INP(B, 9);
			retval |= GPIO_BIT_GET(B, 9) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In__E( uint16_t InMask, uint16_t Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			retval |= GPIO_BIT_GET(A, 3);
		}
		if (InMask & 0x02)
		{
			retval |= GPIO_BIT_GET(A, 2) << 1;
		}
		if (InMask & 0x04)
		{
			retval |= GPIO_BIT_GET(B, 12) << 2;
		}
		if (InMask & 0x08)
		{
			retval |= GPIO_BIT_GET(B, 15) << 3;
		}
		if (InMask & 0x10)
		{
			retval |= GPIO_BIT_GET(B, 14) << 4;
		}
		if (InMask & 0x20)
		{
			retval |= GPIO_BIT_GET(B, 13) << 5;
		}
		if (InMask & 0x40)
		{
			retval |= GPIO_BIT_GET(B, 10) << 6;
		}
		if (InMask & 0x80)
		{
			retval |= GPIO_BIT_GET(B, 3) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In_DDR__E( uint16_t InMask, uint16_t Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			GPIO_BIT_INP(A, 3);
			retval |= GPIO_BIT_GET(A, 3);
		}
		if (InMask & 0x02)
		{
			GPIO_BIT_INP(A, 2);
			retval |= GPIO_BIT_GET(A, 2) << 1;
		}
		if (InMask & 0x04)
		{
			GPIO_BIT_INP(B, 12);
			retval |= GPIO_BIT_GET(B, 12) << 2;
		}
		if (InMask & 0x08)
		{
			GPIO_BIT_INP(B, 15);
			retval |= GPIO_BIT_GET(B, 15) << 3;
		}
		if (InMask & 0x10)
		{
			GPIO_BIT_INP(B, 14);
			retval |= GPIO_BIT_GET(B, 14) << 4;
		}
		if (InMask & 0x20)
		{
			GPIO_BIT_INP(B, 13);
			retval |= GPIO_BIT_GET(B, 13) << 5;
		}
		if (InMask & 0x40)
		{
			GPIO_BIT_INP(B, 10);
			retval |= GPIO_BIT_GET(B, 10) << 6;
		}
		if (InMask & 0x80)
		{
			GPIO_BIT_INP(B, 3);
			retval |= GPIO_BIT_GET(B, 3) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In__F( uint16_t InMask, uint16_t Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			retval |= GPIO_BIT_GET(C, 7);
		}
		if (InMask & 0x02)
		{
			retval |= GPIO_BIT_GET(C, 6) << 1;
		}
		if (InMask & 0x04)
		{
			retval |= GPIO_BIT_GET(A, 15) << 2;
		}
		if (InMask & 0x08)
		{
			retval |= GPIO_BIT_GET(C, 12) << 3;
		}
		if (InMask & 0x10)
		{
			retval |= GPIO_BIT_GET(C, 11) << 4;
		}
		if (InMask & 0x20)
		{
			retval |= GPIO_BIT_GET(C, 10) << 5;
		}
		if (InMask & 0x40)
		{
			retval |= GPIO_BIT_GET(A, 8) << 6;
		}
		if (InMask & 0x80)
		{
			retval |= GPIO_BIT_GET(C, 9) << 7;
		}
		return (retval >> Shift);
	}

	static char FC_CAL_Port_In_DDR__F( uint16_t InMask, uint16_t Shift )
	{
		unsigned char retval = 0;
		if (InMask & 0x01)
		{
			GPIO_BIT_INP(C, 7);
			retval |= GPIO_BIT_GET(C, 7);
		}
		if (InMask & 0x02)
		{
			GPIO_BIT_INP(C, 6);
			retval |= GPIO_BIT_GET(C, 6) << 1;
		}
		if (InMask & 0x04)
		{
			GPIO_BIT_INP(A, 15);
			retval |= GPIO_BIT_GET(A, 15) << 2;
		}
		if (InMask & 0x08)
		{
			GPIO_BIT_INP(C, 12);
			retval |= GPIO_BIT_GET(C, 12) << 3;
		}
		if (InMask & 0x10)
		{
			GPIO_BIT_INP(C, 11);
			retval |= GPIO_BIT_GET(C, 11) << 4;
		}
		if (InMask & 0x20)
		{
			GPIO_BIT_INP(C, 10);
			retval |= GPIO_BIT_GET(C, 10) << 5;
		}
		if (InMask & 0x40)
		{
			GPIO_BIT_INP(A, 8);
			retval |= GPIO_BIT_GET(A, 8) << 6;
		}
		if (InMask & 0x80)
		{
			GPIO_BIT_INP(C, 9);
			retval |= GPIO_BIT_GET(C, 9) << 7;
		}
		return (retval >> Shift);
	}


	static char FC_CAL_Bit_In_DDR(uint8_t port, uint8_t tris, uint16_t pin)
	{
		if (port == 0)
			return FC_CAL_Port_In_DDR__A(1<<pin, 0);
		if (port == 1)
			return FC_CAL_Port_In_DDR__B(1<<pin, 0);
		if (port == 2)
			return FC_CAL_Port_In_DDR__C(1<<pin, 0);
		if (port == 3)
			return FC_CAL_Port_In_DDR__D(1<<pin, 0);
		if (port == 4)
			return FC_CAL_Port_In_DDR__E(1<<pin, 0);
		if (port == 5)
			return FC_CAL_Port_In_DDR__F(1<<pin, 0);
		return 0;
	}

	static char FC_CAL_Bit_In(uint8_t port, uint16_t pin)
	{
		if (port == 0)
			return FC_CAL_Port_In__A(1<<pin, 0);
		if (port == 1)
			return FC_CAL_Port_In__B(1<<pin, 0);
		if (port == 2)
			return FC_CAL_Port_In__C(1<<pin, 0);
		if (port == 3)
			return FC_CAL_Port_In__D(1<<pin, 0);
		if (port == 4)
			return FC_CAL_Port_In__E(1<<pin, 0);
		if (port == 5)
			return FC_CAL_Port_In__F(1<<pin, 0);
		return 0;
	}

	static void FC_CAL_Bit_High_DDR(uint8_t port, uint8_t tris, uint16_t pin)
	{
		if (port == 0)
			FC_CAL_Port_Out_DDR__A(1<<pin, 1<<pin);
		if (port == 1)
			FC_CAL_Port_Out_DDR__B(1<<pin, 1<<pin);
		if (port == 2)
			FC_CAL_Port_Out_DDR__C(1<<pin, 1<<pin);
		if (port == 3)
			FC_CAL_Port_Out_DDR__D(1<<pin, 1<<pin);
		if (port == 4)
			FC_CAL_Port_Out_DDR__E(1<<pin, 1<<pin);
		if (port == 5)
			FC_CAL_Port_Out_DDR__F(1<<pin, 1<<pin);
	}

	static void FC_CAL_Bit_High(uint8_t port, uint16_t pin)
	{
		if (port == 0)
			FC_CAL_Port_Out__A(1<<pin, 1<<pin);
		if (port == 1)
			FC_CAL_Port_Out__B(1<<pin, 1<<pin);
		if (port == 2)
			FC_CAL_Port_Out__C(1<<pin, 1<<pin);
		if (port == 3)
			FC_CAL_Port_Out__D(1<<pin, 1<<pin);
		if (port == 4)
			FC_CAL_Port_Out__E(1<<pin, 1<<pin);
		if (port == 5)
			FC_CAL_Port_Out__F(1<<pin, 1<<pin);
	}

	static void FC_CAL_Bit_Low_DDR(uint8_t port, uint8_t tris, uint16_t pin)
	{
		if (port == 0)
			FC_CAL_Port_Out_DDR__A(1<<pin, 0);
		if (port == 1)
			FC_CAL_Port_Out_DDR__B(1<<pin, 0);
		if (port == 2)
			FC_CAL_Port_Out_DDR__C(1<<pin, 0);
		if (port == 3)
			FC_CAL_Port_Out_DDR__D(1<<pin, 0);
		if (port == 4)
			FC_CAL_Port_Out_DDR__E(1<<pin, 0);
		if (port == 5)
			FC_CAL_Port_Out_DDR__F(1<<pin, 0);
	}

	static void FC_CAL_Bit_Low(uint8_t port, uint16_t pin)
	{
		if (port == 0)
			FC_CAL_Port_Out__A(1<<pin, 0);
		if (port == 1)
			FC_CAL_Port_Out__B(1<<pin, 0);
		if (port == 2)
			FC_CAL_Port_Out__C(1<<pin, 0);
		if (port == 3)
			FC_CAL_Port_Out__D(1<<pin, 0);
		if (port == 4)
			FC_CAL_Port_Out__E(1<<pin, 0);
		if (port == 5)
			FC_CAL_Port_Out__F(1<<pin, 0);
	}



#endif

	static void FC_CAL_Port_Out__x (GPIO_TypeDef *PORT, uint16_t OutMask, uint16_t OutValue)
	{
		PORT->ODR = (PORT->ODR & ~OutMask) | (OutValue & OutMask);
	}


	static void FC_CAL_Port_Out_DDR__x (GPIO_TypeDef *PORT, MX_UINT16 OutMask, MX_UINT16 OutValue)
	{
		GPIO_InitTypeDef  GPIO_InitStruct;

		// Configure outputs
		GPIO_InitStruct.Pin = OutMask;
		GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull  = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(PORT, &GPIO_InitStruct);

		PORT->ODR = (PORT->ODR & ~OutMask) | (OutValue & OutMask);
	}


	static MX_UINT8 FC_CAL_Port_In__x (GPIO_TypeDef *PORT, MX_UINT16 InMask, MX_UINT16 Shift)
	{
		return (PORT->IDR & InMask) >> Shift;
	}


	static MX_UINT16 FC_CAL_Port_In_DDR__x (GPIO_TypeDef *PORT, MX_UINT16 InMask, MX_UINT16 Shift)
	{
		GPIO_InitTypeDef  GPIO_InitStruct;

		// Configure inputs
		GPIO_InitStruct.Pin = InMask;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(PORT, &GPIO_InitStruct);

		return (PORT->IDR & InMask) >> Shift;
	}


	static MX_UINT16 FC_CAL_Bit_In__x(GPIO_TypeDef *PORT, MX_UINT16 Pin)
	{
			return test_bit(PORT->IDR, Pin);
	}

	static MX_UINT16 FC_CAL_Bit_In_DDR__x(GPIO_TypeDef *PORT, MX_UINT16 Pin)
	{
	#if defined GPIO_MODER_MODER0
		PORT->MODER = PORT->MODER & ~(3<<((Pin)*2));
		return test_bit(PORT->IDR, Pin);
	#elif defined GPIO_CRH_MODE
		if (Pin < 8)
		{
			PORT->CRL = PORT->CRL&~(3<<((Pin)*4));
		}
		else
		{
			PORT->CRH = PORT->CRH&~(3<<((Pin&7)*4));
		};
		return test_bit(PORT->IDR, Pin);
	#else
		return FC_CAL_Port_In_DDR__x (PORT, (1 << Pin), (Pin));
	#endif
	}


