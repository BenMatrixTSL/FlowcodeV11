// CRC: AE5753800093D2B889297C6B876B6A21749C10AFA09C3FCE4A5F65B0FF76818F91E52931D8B0EE6801869669B83EE6EF9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5B9E5E6B1BA4ACA09C37B4C2CB5B7B11231EC1E05366E8B2B376CF90AA38343EDD3ADB6B10FF6F02D35379374344E7B2553B54D9DCB445A9D4FF1155F746294ADB48F9D84C400474A69A6701C943F16E27506036D6262E233549D34A0D5AD11F39BDB103476C13626A95BE491E051D29E77DE9611DF1DBD065C705324202ABA0CC88A103EBA5EA7CE
// REVISION: 1.0
// GUID: 82DE79F7-98F7-47FC-8449-1948428B1455
// DATE: 08\08\2022
// DIR: CAL\ARM\ARM_CAL_IO.h
/*********************************************************************
 *                  Flowcode CAL IO File
 *
 * File: PIC_CAL_IO.h
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
 * 160911 | BR | Added Bit manipulation expressions
 * 050312 | BR | Updated to v5.1 CAL Schema
 * 260913 | LM | FC6 Port/Pin macros update
 */




// FC8 Port/Pin macros

#define GET_PORT(p) 					FCP_GET(F,p,0xFF,0)
#define GET_PORT_PIN(p,b) 				FCP_GET(B,p,(1<<b),b)
#define GET_PORT_SHIFT(p,s) 			FCP_GET(M,p,0xFF,s)
#define GET_PORT_MASK_SHIFT(p,m,s) 		FCP_GET(M,p,m,s)
#define GET_PORT_MASK(p,m) 				FCP_GET(M,p,m,0)

#define SET_PORT(p,v) 					FCP_SET(F,p,0xFF,0,v)
#define SET_PORT_PIN(p,b,v) 			FCP_SET(B,p,(1<<b),b,v)
#define SET_PORT_SHIFT(p,s,v) 			FCP_SET(M,p,0xFF,s,v)
#define SET_PORT_MASK_SHIFT(p,m,s,v)	FCP_SET(M,p,m,s,v)
#define SET_PORT_MASK(p,m,v)			FCP_SET(M,p,m,0,v)

// FC Legacy Port/Pin macros

#define FCP_GET(Type, Port, Mask, Shift) FCP_GET_##Type(Port, Mask, Shift)
#define FCP_SET(Type, Port, Mask, Shift, Source) FCP_SET_##Type(Port, Mask, Shift, Source)

#define FCP_GET_B(Port, Mask, Shift)   (FC_CAL_Bit_Call1(port, Port, in, Mask) >> (Shift))
#define FCP_GET_M(Port, Mask, Shift)   (FC_CAL_Bit_Call1(port, Port, in, Mask) >> (Shift))
#define FCP_GET_F(Port, Mask, Shift)   (FC_CAL_Bit_Call1(port, Port, in, Mask) >> (Shift))

#define FCP_SET_B(Port, Mask, Shift, Source)    (FC_CAL_Bit_Call2(port, Port, out, Mask, (Source) << (Shift)))
#define FCP_SET_M(Port, Mask, Shift, Source)    (FC_CAL_Bit_Call2(port, Port, out, Mask, (Source) << (Shift)))
#define FCP_SET_F(Port, Mask, Shift, Source)    (FC_CAL_Bit_Call2(port, Port, out, Mask, (Source) << (Shift)))




void FC_CAL_Port_Out__x (MX_UINT8* Port, MX_UINT8 OutMask, MX_UINT8 OutValue);
void FC_CAL_Port_Out_DDR__x (MX_UINT8* Port, MX_UINT8* Tris, MX_UINT8 OutMask, MX_UINT8 OutValue);
MX_UINT8 FC_CAL_Port_In__x (MX_UINT8* Port, MX_UINT8 InMask, MX_UINT8 Shift);
MX_UINT8 FC_CAL_Port_In_DDR__x (MX_UINT8* Port, MX_UINT8* Tris, MX_UINT8 InMask, MX_UINT8 Shift);

 #define FC_CAL_Bit_Call3(Apre, Apost, B)					Apre##_##Apost(B)
 #define FC_CAL_Bit_Call4(Apre, Apost, B, C)				Apre##_##Apost(B, C)

 #define FC_CAL_Bit_In(A, B)								FC_CAL_Bit_Call3(A, in, (1<<B))
 #define FC_CAL_Bit_In_DDR(A, B, C)							FC_CAL_Bit_Call3(A, in, (1<<C))
 #define FC_CAL_Bit_High(A, B)								FC_CAL_Bit_Call4(A, out, (1<<B), (1<<B))
 #define FC_CAL_Bit_High_DDR(A, B, C)						FC_CAL_Bit_Call4(A, out, (1<<C), (1<<C))
 #define FC_CAL_Bit_Low(A, B)								FC_CAL_Bit_Call4(A, out, 0, (1<<B))
 #define FC_CAL_Bit_Low_DDR(A, B, C)						FC_CAL_Bit_Call4(A, out, 0, (1<<C))


MX_UINT8 FC_CAL_Bit_I(MX_UINT8 prt, MX_UINT8 bt, MX_UINT8 ddr);
void FC_CAL_Bit_O(MX_UINT8 prt, MX_UINT8 bt, MX_UINT8 ddr, MX_UINT8 data);


//Pointer Functions
#define FC_CAL_Port_Out(p, v, m)     	FC_CAL_Port_Out__x(&port##p, (v), (m))
#define FC_CAL_Port_Out_DDR(p, v, m) 	FC_CAL_Port_Out_DDR__x(&port##p, &tris##p, (v), (m))
#define FC_CAL_Port_In(p, m)		 	FC_CAL_Port_In__x(&port##p, (m))
#define FC_CAL_Port_In_DDR (p, m)	 	FC_CAL_Port_In_DDR__x(&port##p, &tris##p, (m))

#define FCP_PORT_A PORTA
#define FCP_TRIS_A TRISA
#define FCP_PORT_B PORTB
#define FCP_TRIS_B TRISB
#define FCP_PORT_C PORTC
#define FCP_TRIS_C TRISC
#define FCP_PORT_D PORTD
#define FCP_TRIS_D TRISD

#define portA_in	porta_in
#define portB_in	portb_in
#define portC_in	portc_in
#define portD_in	portd_in

#define portA_out	porta_out
#define portB_out	portb_out
#define portC_out	portc_out
#define portD_out	portd_out
