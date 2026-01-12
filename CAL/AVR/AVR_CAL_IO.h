// CRC: 77485F5F6A861F9125D47827B4DE492656C5431E478E8046055FD2257F64F1F391E52931D8B0EE6801869669B83EE6EF9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF57B8941EF49EABC599BF2A17B230079AE5B37CA602E7EBE161C892FFB225BC928236A0757D550B9A08A5329641E4B73B3204A639C9B9286F45745C968357C65FC0927B0703345DF879B666CF1D9FC0E66CEA6805CA6DD7F3D549D34A0D5AD11F347DF154471853F6ACE34D48767EB8465157F22D3E1FD1319FA0264F21FD71235929CCCA4409E3163
// REVISION: 1.0
// GUID: AF998ECF-AA19-4FFF-B4AB-34AC90B7BD9A
// DATE: 08\08\2022
// DIR: CAL\AVR\AVR_CAL_IO.h
/*********************************************************************
 *                  Flowcode CAL IO File
 *
 * File: AVR_CAL_IO.h
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
 * 020312 | BR | Updated to v5.1 CAL Schema
 * 280612 | BR | Added ports K and L
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

#define FCP_GET(Type, Port, Mask, Shift) FCP_GET_##Type(_##Port, Mask, Shift)
#define FCP_SET(Type, Port, Mask, Shift, Source) FCP_SET_##Type(_##Port, Mask, Shift, Source)

#define FCP_GET_B(Port, Mask, Shift)   (FC_CAL_Port_In_DDR__x((&FCP_PIN##Port), (&FCP_TRIS##Port), (Mask), (Shift)))
#define FCP_GET_M(Port, Mask, Shift)   (FC_CAL_Port_In_DDR__x((&FCP_PIN##Port), (&FCP_TRIS##Port), (Mask), (Shift)))
#define FCP_GET_F(Port, Mask, Shift)   (FC_CAL_Port_In_DDR__x((&FCP_PIN##Port), (&FCP_TRIS##Port), (Mask), (Shift)))

#define FCP_SET_B(Port, Mask, Shift, Source)    {FCP_TRIS##Port |= Mask; (Source)? (FCP_PORT##Port |= Mask) : (FCP_PORT##Port &= ~Mask);}
#define FCP_SET_M(Port, Mask, Shift, Source)    {FCP_TRIS##Port |= Mask; FCP_PORT##Port = (FCP_PORT##Port & ~Mask) | (((Source) << Shift) & Mask);}
#define FCP_SET_F(Port, Mask, Shift, Source)    {FCP_TRIS##Port = 255; FCP_PORT##Port = (Source);}


#ifndef MX_XMEGA

	//Port Functions
	static void FC_CAL_Port_Out__x (volatile char* PORT, MX_UINT8 OutMask, MX_UINT8 OutValue);
	static void FC_CAL_Port_Out_DDR__x (volatile char* PORT, volatile char* DDR, MX_UINT8 OutMask, MX_UINT8 OutValue);
	static MX_UINT8 FC_CAL_Port_In__x (volatile char* PIN, MX_UINT8 InMask, MX_UINT8 Shift);
	static MX_UINT8 FC_CAL_Port_In_DDR__x (volatile char* PIN, volatile char* DDR, MX_UINT8 InMask, MX_UINT8 Shift);
	static MX_UINT8 FC_CAL_Bit_In__x(volatile char* Port, MX_UINT8 Pin);

	//Pin Functions
	#define FC_CAL_Bit_In(A, B)				FC_CAL_Bit_In__x(&A, B)
	#define FC_CAL_Bit_In_DDR(A, B, C)		clear_bit(B, C)
	#define FC_CAL_Bit_High(A, B)			set_bit(A, B)
	#define FC_CAL_Bit_High_DDR(A, B, C)	{set_bit(B, C); set_bit(A, C);}
	#define FC_CAL_Bit_Low(A, B)			clear_bit(A, B)
	#define FC_CAL_Bit_Low_DDR(A, B, C)		{set_bit(B, C); clear_bit(A, C);}


	static MX_UINT8 FC_CAL_Bit_I(MX_UINT8 prt, MX_UINT8 bt, MX_UINT8 ddr);
	static void FC_CAL_Bit_O(MX_UINT8 prt, MX_UINT8 bt, MX_UINT8 ddr, MX_UINT8 data);

	//Pointer Functions
	#define FC_CAL_Port_Out(p, v, m)     FC_CAL_Port_Out__x(&PORT##p, (v), (m))
	#define FC_CAL_Port_Out_DDR(p, v, m) FC_CAL_Port_Out_DDR__x(&PORT##p, &DDR##p, (v), (m))
	#define FC_CAL_Port_In(p, m)		 FC_CAL_Port_In(&PIN##p, (m))
	#define FC_CAL_Port_In_DDR (p, m)	 FC_CAL_Port_In_DDR__x(&PIN##p, &DDR##p, (m))


	#ifdef PORTA
		#define FCP_PORT_A 	PORTA
		#define FCP_PIN_A 	PINA
		#define FCP_TRIS_A 	DDRA
		#define porta 		PORTA
		#define trisa 		DDRA
		#define TRISA 		DDRA
	#endif
	#ifdef PORTB
		#define FCP_PORT_B 	PORTB
		#define FCP_PIN_B 	PINB
		#define FCP_TRIS_B 	DDRB
		#define portb 		PORTB
		#define trisb 		DDRB
		#define TRISB 		DDRB
	#endif
	#ifdef PORTC
		#define FCP_PORT_C 	PORTC
		#define FCP_PIN_C	PINC
		#define FCP_TRIS_C 	DDRC
		#define portc 		PORTC
		#define trisc 		DDRC
		#define TRISC 		DDRC
	#endif
	#ifdef PORTD
		#define FCP_PORT_D 	PORTD
		#define FCP_PIN_D 	PIND
		#define FCP_TRIS_D 	DDRD
		#define portd 		PORTD
		#define trisd 		DDRD
		#define TRISD 		DDRD
	#endif
	#ifdef PORTE
		#define FCP_PORT_E 	PORTE
		#define FCP_PIN_E 	PINE
		#define FCP_TRIS_E 	DDRE
		#define porte 		PORTE
		#define trise 		DDRE
		#define TRISE 		DDRE
	#endif
	#ifdef PORTF
		#define FCP_PORT_F 	PORTF
		#define FCP_PIN_F 	PINF
		#define FCP_TRIS_F 	DDRF
		#define portf 		PORTF
		#define trisf 		DDRF
		#define TRISF 		DDRF
	#endif
	#ifdef PORTG
		#define FCP_PORT_G 	PORTG
		#define FCP_PIN_G 	PING
		#define FCP_TRIS_G 	DDRG
		#define portg 		PORTG
		#define trisg 		DDRG
		#define TRISG 		DDRG
	#endif
	#ifdef PORTH
		#define FCP_PORT_H 	PORTH
		#define FCP_PIN_H	PINH
		#define FCP_TRIS_H 	DDRH
		#define porth 		PORTH
		#define trish 		DDRH
		#define TRISH 		DDRH
	#endif
	#ifdef PORTJ
		#define FCP_PORT_J 	PORTJ
		#define FCP_PIN_J 	PINJ
		#define FCP_TRIS_J 	DDRJ
		#define portj 		PORTJ
		#define trisj 		DRJ
		#define TRISJ 		DDRJ
	#endif
	#ifdef PORTK
		#define FCP_PORT_K 	PORTK
		#define FCP_PIN_K 	PINK
		#define FCP_TRIS_K 	DDRK
		#define portk 		PORTK
		#define trisk 		DDRK
		#define TRISK 		DDRK
	#endif
	#ifdef PORTL
		#define FCP_PORT_L 	PORTL
		#define FCP_PIN_L 	PINL
		#define FCP_TRIS_L 	DDRL
		#define portl		PORTL
		#define trisl 		DDRL
		#define TRISL 		DDRL
	#endif
#else

	static void FC_CAL_Port_Out__x (volatile char* PORT, MX_UINT8 OutMask, MX_UINT8 OutValue);
	static void FC_CAL_Port_Out_DDR__x (volatile char* PORT, volatile char* DDR, MX_UINT8 OutMask, MX_UINT8 OutValue);
	static MX_UINT8 FC_CAL_Port_In__x (volatile char* PIN, MX_UINT8 InMask, MX_UINT8 Shift);
	static MX_UINT8 FC_CAL_Port_In_DDR__x (volatile char* PIN, volatile char* DDR, MX_UINT8 InMask, MX_UINT8 Shift);
	static MX_UINT8 FC_CAL_Bit_In__x(volatile char* Port, MX_UINT8 Pin);

	//Pin Functions
	#define FC_CAL_Bit_In(A, B)				FC_CAL_Bit_In__x(&A, B)
	#define FC_CAL_Bit_In_DDR(A, B, C)		clear_bit(B, C)
	#define FC_CAL_Bit_High(A, B)			set_bit(A, B)
	#define FC_CAL_Bit_High_DDR(A, B, C)	{set_bit(B, C); set_bit(A, C);}
	#define FC_CAL_Bit_Low(A, B)			clear_bit(A, B)
	#define FC_CAL_Bit_Low_DDR(A, B, C)		{set_bit(B, C); clear_bit(A, C);}


	static MX_UINT8 FC_CAL_Bit_I(MX_UINT8 prt, MX_UINT8 bt, MX_UINT8 ddr);
	static void FC_CAL_Bit_O(MX_UINT8 prt, MX_UINT8 bt, MX_UINT8 ddr, MX_UINT8 data);

	//Pointer Functions
	#define FC_CAL_Port_Out(p, v, m)     FC_CAL_Port_Out__x(&PORT##p.OUT, (v), (m))
	#define FC_CAL_Port_Out_DDR(p, v, m) FC_CAL_Port_Out_DDR__x(&PORT##p.OUT, &PORT##p.DIR, (v), (m))
	#define FC_CAL_Port_In(p, m)		 FC_CAL_Port_In(&PORT##p.IN, (m))
	#define FC_CAL_Port_In_DDR (p, m)	 FC_CAL_Port_In_DDR__x(&PORT##p.IN, &PORT##p.DIR, (m))

	#ifdef PORTA
		#define FCP_PORT_A 	PORTA.OUT
		#define FCP_PIN_A 	PORTA.IN
		#define FCP_TRIS_A 	PORTA.DIR
		#define porta 		PORTA.OUT
		#define trisa 		PORTA.DIR
	#endif
	#ifdef PORTB
		#define FCP_PORT_B 	PORTB.OUT
		#define FCP_PIN_B 	PORTB.IN
		#define FCP_TRIS_B 	PORTB.DIR
		#define portb 		PORTB.OUT
		#define trisb 		PORTB.DIR
	#endif
	#ifdef PORTC
		#define FCP_PORT_C 	PORTC.OUT
		#define FCP_PIN_C	PORTC.IN
		#define FCP_TRIS_C 	PORTC.DIR
		#define portc 		PORTC.OUT
		#define trisc 		PORTC.DIR
	#endif
	#ifdef PORTD
		#define FCP_PORT_D 	PORTD.OUT
		#define FCP_PIN_D 	PORTD.IN
		#define FCP_TRIS_D 	PORTD.DIR
		#define portd 		PORTD.OUT
		#define trisd 		PORTD.DIR
	#endif
	#ifdef PORTE
		#define FCP_PORT_E 	PORTE.OUT
		#define FCP_PIN_E 	PORTE.IN
		#define FCP_TRIS_E 	PORTE.DIR
		#define porte 		PORTE.OUT
		#define trise 		PORTE.DIR
	#endif
	#ifdef PORTF
		#define FCP_PORT_F 	PORTF.OUT
		#define FCP_PIN_F 	PORTF.IN
		#define FCP_TRIS_F 	PORTF.DIR
		#define portf 		PORTF.OUT
		#define trisf 		PORTF.DIR
	#endif
	#ifdef PORTG
		#define FCP_PORT_G 	PORTG.OUT
		#define FCP_PIN_G 	PORTG.IN
		#define FCP_TRIS_G 	PORTG.DIR
		#define portg 		PORTG.OUT
		#define trisg 		PORTG.DIR
	#endif
	#ifdef PORTH
		#define FCP_PORT_H 	PORTH.OUT
		#define FCP_PIN_H	PORTH.IN
		#define FCP_TRIS_H 	PORTH.DIR
		#define porth 		PORTH.OUT
		#define trish 		PORTH.DIR
	#endif
	#ifdef PORTJ
		#define FCP_PORT_J 	PORTJ.OUT
		#define FCP_PIN_J 	PORTJ.IN
		#define FCP_TRIS_J 	PORTJ.DIR
		#define portj 		PORTJ.OUT
		#define trisj 		PORTJ.DIR
	#endif
	#ifdef PORTK
		#define FCP_PORT_K 	PORTK.OUT
		#define FCP_PIN_K 	PORTK.IN
		#define FCP_TRIS_K 	PORTK.DIR
		#define portk 		PORTK.OUT
		#define trisk		PORTK.DIR
	#endif
	#ifdef PORTL
		#define FCP_PORT_L 	PORTL.OUT
		#define FCP_PIN_L 	PORTL.IN
		#define FCP_TRIS_L 	PORTL.DIR
		#define portl 		PORTL.OUT
		#define trisl		PORTL.DIR
	#endif
#endif
