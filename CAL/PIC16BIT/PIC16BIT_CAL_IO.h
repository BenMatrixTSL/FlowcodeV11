// CRC: 5D982BB222882C54AB4AFF20A1590FC484D3178BD0D2510D0F5A64A7853221CAE2C33FABBE4F69A6659399D51781B7B91E1A3B6BDBC9AEBC1F0EF6FCC3EA254B9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF561EE79BD2121AF25A95EBA1D844AF55704C217D2B37308E8D2811D28F169DC8BC4A0FF09C0E0218729132CF39A8819EF65001C54132B24DD9C976A3B013C4B1D4BED8EE69C3428C6FCF2C63805AB475D49AC82D2E3420E67549D34A0D5AD11F33B6DCFA98CF0FB3B5CA30F4CA5E6A054488D9C8A54241FC5ACA9CE2DF1EA8436E42CFE37638C9748
// REVISION: 1.0
// GUID: 57B962EA-0D75-4BD9-88F8-E77F5C828D00
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\PIC16BIT_CAL_IO.h
/*********************************************************************
 *                  Flowcode CAL IO File
 *
 * File: PIC16BIT_CAL_IO.h
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
 * 050911 | BR | Added Bit manipulation expressions
 * 270912 | ST | Changed from 8bit to 16bit to allow full port access
 * 260913 | LM | FC6 Port/Pin macros update
 * 200215 | LM | Added PORT K
 */


#define MX_JOIN(A, B)						A##B

// FC8 Port/Pin macros

#define GET_PORT(p) 					FCP_GET(F,p,0xFFFF,0)
#define GET_PORT_PIN(p,b) 				FCP_GET(B,p,(1<<b),b)
#define GET_PORT_SHIFT(p,s) 			FCP_GET(M,p,0xFFFF,s)
#define GET_PORT_MASK_SHIFT(p,m,s) 		FCP_GET(M,p,m,s)
#define GET_PORT_MASK(p,m) 				FCP_GET(M,p,m,0)

#define SET_PORT(p,v) 					FCP_SET(F,p,0xFFFF,0,v)
#define SET_PORT_PIN(p,b,v) 			FCP_SET(B,p,(1<<b),b,v)
#define SET_PORT_SHIFT(p,s,v) 			FCP_SET(M,p,0xFFFF,s,v)
#define SET_PORT_MASK_SHIFT(p,m,s,v)	FCP_SET(M,p,m,s,v)
#define SET_PORT_MASK(p,m,v)			FCP_SET(M,p,m,0,v)

// FC Legacy Port/Pin macros

#define FCP_GET(Type, Port, Mask, Shift) FCP_GET_##Type(_##Port, Mask, Shift)
#define FCP_SET(Type, Port, Mask, Shift, Source) FCP_SET_##Type(_##Port, Mask, Shift, Source)

#define FCP_GET_B(Port, Mask, Shift)   (FC_CAL_Port_In_DDR__x((&FCP_PORT##Port), (&FCP_TRIS##Port), (Mask), (Shift)))
#define FCP_GET_M(Port, Mask, Shift)   (FC_CAL_Port_In_DDR__x((&FCP_PORT##Port), (&FCP_TRIS##Port), (Mask), (Shift)))
#define FCP_GET_F(Port, Mask, Shift)   (FC_CAL_Port_In_DDR__x((&FCP_PORT##Port), (&FCP_TRIS##Port), (Mask), (Shift)))

#define FCP_SET_B(Port, Mask, Shift, Source)    {FCP_TRIS##Port &= ~Mask; (Source) ? (FCP_PORT##Port = FCP_LAT##Port | Mask) : (FCP_PORT##Port = FCP_LAT##Port & ~Mask);}
#define FCP_SET_M(Port, Mask, Shift, Source)    {FCP_TRIS##Port &= ~Mask; FCP_PORT##Port = (FCP_LAT##Port & ~Mask) | (((Source) << Shift) & Mask);}
#define FCP_SET_F(Port, Mask, Shift, Source)    {FCP_TRIS##Port = 0; FCP_PORT##Port = (Source);}

//Had to override now to get around a Flowcode bug, can be resurrected later when bug is fixed
//#define FCP_SET_F(Port, Mask, Shift, Source)    (ptmp = (Source), FCP_TRIS##Port &= ~Mask, FCP_LAT##Port = (ptmp & Mask))


//Port Functions
void FC_CAL_Port_Out__x (volatile unsigned int* PORT, MX_UINT16 OutMask, MX_UINT16 OutValue);
void FC_CAL_Port_Out_DDR__x (volatile unsigned int* PORT, volatile unsigned int* DDR, MX_UINT16 OutMask, MX_UINT16 OutValue);

MX_UINT16 FC_CAL_Port_In__x (volatile unsigned int* PORT, MX_UINT16 InMask, MX_UINT8 Shift);
MX_UINT16 FC_CAL_Port_In_DDR__x (volatile unsigned int* PORT, volatile unsigned int* DDR, MX_UINT16 InMask, MX_UINT8 Shift);


//Pin Functions
#define FC_CAL_Bit_In(A, B)					test_bit(A, B)
#define FC_CAL_Bit_In_DDR(A, B, C)			set_bit(B, C)
#define FC_CAL_Bit_High(A, B)				set_bit(MX_JOIN(A,LAT), B)
#define FC_CAL_Bit_High_DDR(A, B, C)		{clear_bit(B, C); set_bit(MX_JOIN(A,LAT), C);}
#define FC_CAL_Bit_Low(A, B)				clear_bit(MX_JOIN(A,LAT), B)
#define FC_CAL_Bit_Low_DDR(A, B, C)			{clear_bit(B, C); clear_bit(MX_JOIN(A,LAT), C);}

MX_UINT8 FC_CAL_Bit_I(MX_UINT8 prt, MX_UINT8 bt, MX_UINT8 ddr);
void FC_CAL_Bit_O(MX_UINT8 prt, MX_UINT8 bt, MX_UINT8 ddr, MX_UINT8 data);

//Pointer Functions
#define FC_CAL_Port_Out(p, v, m)     FC_CAL_Port_Out__x(&PORT##p, (v), (m))
#define FC_CAL_Port_Out_DDR(p, v, m) FC_CAL_Port_Out_DDR__x(&PORT##p, &DDR##p, (v), (m))
#define FC_CAL_Port_In(p, m)		 FC_CAL_Port_In(&PORT##p, (m))
#define FC_CAL_Port_In_DDR (p, m)	 FC_CAL_Port_In_DDR__x(&PORT##p, &DDR##p, (m))


/*
#define FCP_SET_NODDR(Port, Pin, Value)	\
#if defined(_LAT##Port##Pin) || defined(_LAT##Port##_LAT##Port##Pin##_POSITION) \
LAT##Port##bits.LAT##Port##Pin = Value;\
#else \
PORT##Port##bits.R##Port##Pin = Value; \
#endif \
*/

//All possible ports can be defined out as only referenced if ports exist in FCD
#define FCP_PORT_A 	PORTA
#define FCP_TRIS_A 	TRISA
#define porta		PORTA
#define trisa		TRISA
#define PORTALAT	LATA
#define FCP_LAT_A	LATA

#define FCP_PORT_B 	PORTB
#define FCP_TRIS_B 	TRISB
#define portb		PORTB
#define trisb		TRISB
#define PORTBLAT	LATB
#define FCP_LAT_B	LATB

#define FCP_PORT_C 	PORTC
#define FCP_TRIS_C 	TRISC
#define portc		PORTC
#define trisc		TRISC
#define PORTCLAT	LATC
#define FCP_LAT_C	LATC

#define FCP_PORT_D 	PORTD
#define FCP_TRIS_D 	TRISD
#define portd		PORTD
#define trisd		TRISD
#define PORTDLAT	LATD
#define FCP_LAT_D	LATD

#define FCP_PORT_E 	PORTE
#define FCP_TRIS_E 	TRISE
#define porte		PORTE
#define trise		TRISE
#define PORTELAT	LATE
#define FCP_LAT_E	LATE

#define FCP_PORT_F 	PORTF
#define FCP_TRIS_F 	TRISF
#define portf		PORTF
#define trisf		TRISF
#define PORTFLAT	LATF
#define FCP_LAT_F	LATF

#define FCP_PORT_G 	PORTG
#define FCP_TRIS_G 	TRISG
#define portg		PORTG
#define trisg		TRISG
#define PORTGLAT	LATG
#define FCP_LAT_G	LATG

#define FCP_PORT_H 	PORTH
#define FCP_TRIS_H 	TRISH
#define porth		PORTH
#define trish		TRISH
#define PORTHLAT	LATH
#define FCP_LAT_H	LATH

#define FCP_PORT_J 	PORTJ
#define FCP_TRIS_J 	TRISJ
#define portj		PORTJ
#define trisj		TRISJ
#define PORTJLAT	LATJ
#define FCP_LAT_J	LATJ

#define FCP_PORT_K 	PORTK
#define FCP_TRIS_K 	TRISK
#define portk		PORTK
#define trisk		TRISK
#define PORTKLAT	LATK
#define FCP_LAT_K	LATK




