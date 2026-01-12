// CRC: 34358081B117C27F7D8358E612878F8E5F343B66182D417818220CB9C07676CF91E52931D8B0EE6801869669B83EE6EF9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF54534B0E7D1748E061AE6ABB3AD2DE2BCF7ECAFF396146D4E2631A11C8AA4FCA427BBFA7A6D330A2FCB0020B40312AEB6720A380719A7C6DD9A0B60A353172C750474657F6EBF0D531C2F1C2631D2672982F4206EE2B091C9549D34A0D5AD11F316ECCBBC313EE66A2FFD77189E38CCA8E112BDBF9FDB7EFE35CB29F668C7CEEBDE7ED4CEB4872907
// REVISION: 1.0
// GUID: 0B3E33D5-6589-44B6-A63A-5309C01C956E
// DATE: 08\08\2022
// DIR: CAL\RPI\RPI_CAL_IO.h
/*********************************************************************
 *                  Flowcode CAL IO File
 *
 * File: RPI_CAL_IO.h
 *
 * (c) 2011-2018 Matrix TSL
 * http://www.matrixTSL.com
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
 */

#ifndef MX_CAL_IO_H
#define MX_CAL_IO_H

//#define MX_DEBUG(text)  {printf(text); printf("\r\n");}
#define MX_DEBUG(text)

#define	MX_REGISTER_MAP_BASE_OLD	0x20000000
#define	MX_REGISTER_MAP_BASE_NEW	0x3F000000
//#define	MX_REGISTER_MAP_BASE_OLD	bcm_host_get_peripheral_address()
//#define	MX_REGISTER_MAP_BASE_NEW	bcm_host_get_peripheral_address()

#define	MX_REGISTER_MAP_PADS		0x00100000
#define	MX_REGISTER_MAP_CLOCK		0x00101000
#define	MX_REGISTER_MAP_GPIO		0x00200000
#define	MX_REGISTER_MAP_TIMER		0x0000B000
#define	MX_REGISTER_MAP_PWM			0x0020C000

MX_UINT32 *FC_CAL_GetRegisterMap(MX_UINT32 Offset);
void FC_CAL_Port_Out_DDR(MX_UINT32 OutMask, MX_UINT32 OutValue);
MX_UINT32 FC_CAL_Port_In_DDR(MX_UINT32 InMask);
  
/*********************************************************************************************/
extern volatile MX_UINT32 *gpio;
#define MX_GPIO_IN(p)    {*(gpio+((p)/10)) &= ~(7<<(((p)%10)*3));}
#define MX_GPIO_OUT(p)   {*(gpio+((p)/10)) = (*(gpio+((p)/10)) & ~(6<<(((p)%10)*3)))|(1<<(((p)%10)*3));}
#define MX_GPIO_ALT(p,a) {*(gpio+((p)/10)) &= ~(7<<(((p)%10)*3)); *(gpio+((p)/10)) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((p)%10)*3));}
#define MX_GPIO_SET(p)   {*(gpio+7+((p)/32))  = 1<<((p)%32);}
#define MX_GPIO_CLR(p)   {*(gpio+10+((p)/32)) = 1<<((p)%32);}
#define MX_GPIO_GET(p)   ((*(gpio+13+((p)/32))>>((p)%32))&1)
#define MX_GPIO_GET_FSEL(p)   ((*(gpio+((p)/10))>>(((p)%10)*3))&7)
// Pull up/pull down register and clock
#define MX_GPIO_PULL     (*(gpio+37)) 
#define MX_GPIO_PULLCLK0 (*(gpio+38))
/*********************************************************************************************/


#define MX_MAX_GPIO  64

// BL0036 GPIO mapping
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5
#define PORTG 6
#define porta PORTA
#define portb PORTB
#define portc PORTC
#define portd PORTD
#define porte PORTE
#define portf PORTF
#define portg PORTG

#define MX_PORTA0_GPIO 4
#define MX_PORTA1_GPIO 7
#define MX_PORTA2_GPIO 6
#define MX_PORTA3_GPIO 5
#define MX_PORTA4_GPIO 1
#define MX_PORTA5_GPIO 0
#define MX_PORTA6_GPIO -1
#define MX_PORTA7_GPIO -1

#define MX_PORTB0_GPIO 27
#define MX_PORTB1_GPIO 17
#define MX_PORTB2_GPIO 22
#define MX_PORTB3_GPIO 23
#define MX_PORTB4_GPIO 24
#define MX_PORTB5_GPIO 25
#define MX_PORTB6_GPIO 26
#define MX_PORTB7_GPIO 16

#define MX_PORTC0_GPIO 15
#define MX_PORTC1_GPIO 14
#define MX_PORTC2_GPIO 8
#define MX_PORTC3_GPIO 10
#define MX_PORTC4_GPIO 9
#define MX_PORTC5_GPIO 11
#define MX_PORTC6_GPIO 3
#define MX_PORTC7_GPIO 2

#define MX_PORTD0_GPIO 13
#define MX_PORTD1_GPIO 12
#define MX_PORTD2_GPIO 18
#define MX_PORTD3_GPIO 20
#define MX_PORTD4_GPIO 19
#define MX_PORTD5_GPIO 21
#define MX_PORTD6_GPIO -1
#define MX_PORTD7_GPIO -1

// RPi GPIO mapping
#define MX_PORTG0_GPIO 0
#define MX_PORTG1_GPIO 1
#define MX_PORTG2_GPIO 2
#define MX_PORTG3_GPIO 3
#define MX_PORTG4_GPIO 4
#define MX_PORTG5_GPIO 5
#define MX_PORTG6_GPIO 6
#define MX_PORTG7_GPIO 7
#define MX_PORTG8_GPIO 8
#define MX_PORTG9_GPIO 9
#define MX_PORTG10_GPIO 10
#define MX_PORTG11_GPIO 11
#define MX_PORTG12_GPIO 12
#define MX_PORTG13_GPIO 13
#define MX_PORTG14_GPIO 14
#define MX_PORTG15_GPIO 15
#define MX_PORTG16_GPIO 16
#define MX_PORTG17_GPIO 17
#define MX_PORTG18_GPIO 18
#define MX_PORTG19_GPIO 19
#define MX_PORTG20_GPIO 20
#define MX_PORTG21_GPIO 21
#define MX_PORTG22_GPIO 22
#define MX_PORTG23_GPIO 23
#define MX_PORTG24_GPIO 24
#define MX_PORTG25_GPIO 25
#define MX_PORTG26_GPIO 26
#define MX_PORTG27_GPIO 27
#define MX_PORTG28_GPIO 28
#define MX_PORTG29_GPIO 29
#define MX_PORTG30_GPIO 30
#define MX_PORTG31_GPIO 31


// Interface for CAL C code
void     FC_CAL_GPIO_SET(MX_UINT8 p);
void     FC_CAL_GPIO_CLR(MX_UINT8 p);
void     FC_CAL_GPIO_PUT(MX_UINT8 p, MX_UINT32 v);
MX_UINT32 FC_CAL_GPIO_GET(MX_UINT8 p);

void     FC_CAL_GPIO_SET_DDR(MX_UINT8 p);
void     FC_CAL_GPIO_CLR_DDR(MX_UINT8 p);
void     FC_CAL_GPIO_PUT_DDR(MX_UINT8 p, MX_UINT32 v);
MX_UINT32 FC_CAL_GPIO_GET_DDR(MX_UINT8 p);

// Interface for Flowcode 8
#define GET_PORT(p)                               FCP_GET(F,p,-1,0)
#define GET_PORT_PIN(p,b)                         FCP_GET(B,p,(1<<b),b)
#define GET_PORT_SHIFT(p,s)                       FCP_GET(M,p,-1,s)
#define GET_PORT_MASK_SHIFT(p,m,s)                FCP_GET(M,p,m,s)
#define GET_PORT_MASK(p,m)                        FCP_GET(M,p,m,0)

#define SET_PORT(p,v)                             FCP_SET(F,p,-1,0,v)
#define SET_PORT_PIN(p,b,v)                       FCP_SET(B,p,(1<<b),b,v)
#define SET_PORT_SHIFT(p,s,v)                     FCP_SET(M,p,-1,s,v)
#define SET_PORT_MASK_SHIFT(p,m,s,v)              FCP_SET(M,p,m,s,v)
#define SET_PORT_MASK(p,m,v)                      FCP_SET(M,p,m,0,v)

// Interface for Flowcode 7
#define FCP_GET(Type, Port, Mask, Shift)          FCP_GET_##Type(Port, Mask, Shift)
#define FCP_GET_B(Port, Mask, Shift)              FC_CAL_GET_B_PORT##Port(Shift)
#define FCP_GET_M(Port, Mask, Shift)              FC_CAL_GET_M_PORT##Port(Mask)
#define FCP_GET_F(Port, Mask, Shift)              FC_CAL_GET_M_PORT##Port(Mask)

#define FCP_SET(Type, Port, Mask, Shift, Source)  FCP_SET_##Type(Port, Mask, Shift, Source)
#define FCP_SET_B(Port, Mask, Shift, Source)      FC_CAL_PUT_B_PORT##Port(Shift, Source)
#define FCP_SET_M(Port, Mask, Shift, Source)      FC_CAL_PUT_M_PORT##Port(Mask, Source)
#define FCP_SET_F(Port, Mask, Shift, Source)      FC_CAL_PUT_M_PORT##Port(Mask, Source)


MX_UINT32 FC_CAL_GET_B_PORTA(MX_UINT8 p);
MX_UINT32 FC_CAL_GET_B_PORTB(MX_UINT8 p);
MX_UINT32 FC_CAL_GET_B_PORTC(MX_UINT8 p);
MX_UINT32 FC_CAL_GET_B_PORTD(MX_UINT8 p);
#define FC_CAL_GET_B_PORTG(Shift)           FC_CAL_GPIO_GET_DDR(Shift)
#define FC_CAL_GET_B_PORTH(Shift)           FC_CAL_GPIO_GET_DDR(Shift+32)

MX_UINT32 FC_CAL_GET_M_PORTA(MX_UINT32 mask);
MX_UINT32 FC_CAL_GET_M_PORTB(MX_UINT32 mask);
MX_UINT32 FC_CAL_GET_M_PORTC(MX_UINT32 mask);
MX_UINT32 FC_CAL_GET_M_PORTD(MX_UINT32 mask);
#define FC_CAL_GET_M_PORTG(Mask)            FC_CAL_GPIO_PORT_GET_DDR(Mask)

void FC_CAL_PUT_B_PORTA(MX_UINT8 p, MX_UINT32 v);
void FC_CAL_PUT_B_PORTB(MX_UINT8 p, MX_UINT32 v);
void FC_CAL_PUT_B_PORTC(MX_UINT8 p, MX_UINT32 v);
void FC_CAL_PUT_B_PORTD(MX_UINT8 p, MX_UINT32 v);
#define FC_CAL_PUT_B_PORTG(Shift, Source)   FC_CAL_GPIO_PUT_DDR(Shift, Source)
#define FC_CAL_PUT_B_PORTH(Shift, Source)   FC_CAL_GPIO_PUT_DDR(Shift+32, Source)

void FC_CAL_PUT_M_PORTA(MX_UINT32 mask, MX_UINT32 value);
void FC_CAL_PUT_M_PORTB(MX_UINT32 mask, MX_UINT32 value);
void FC_CAL_PUT_M_PORTC(MX_UINT32 mask, MX_UINT32 value);
void FC_CAL_PUT_M_PORTD(MX_UINT32 mask, MX_UINT32 value);
#define FC_CAL_PUT_M_PORTG(Mask, Source)    FC_CAL_GPIO_PORT_PUT_DDR(Mask, Source)

#endif // MX_CAL_IO_H

