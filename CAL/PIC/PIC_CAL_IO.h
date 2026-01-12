// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B891E52931D8B0EE6801869669B83EE6EF9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF58130A887C1B0D5A6735BE97DB65962AF309EF58C9B002FC2ED832F0F5259FA998B33763CE481504A78AB173D9525F10CFDFF53EF56A427FB04AA545421389C7DDB40BC94E90D0A6DD4E28CC1F274BF6A5B236E0A5AFCB6D6549D34A0D5AD11F31ADC3F446EE7E503399BB86B11BED68E576076B7D4BEB7B1ADE7F62E1D9AF28DE7B6485568F872D0
// REVISION: 1.0
// GUID: FAA4A6DD-2B13-4563-B43C-4F8CA7E89954
// DATE: 08\08\2022
// DIR: CAL\PIC\PIC_CAL_IO.h
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
 * 010911 | SK | Created
 * 050911 | BR | Added Bit manipulation expressions
 * 220812 | BR | Minor bug fix to allow 10F port pin access to work
 * 030413 | LM | FC6 Port/Pin macros
 * 220413 | LM | FC6 Port/Pin macros update
 * 220413 | LM | Use Latch for port reading, if we have one
 * 210613 | BR | Fixed an issue with outputting 0 to a single bit using the Output Icon - BoostC () Bug
 * 250913 | LM | FC6 Port/Pin macros update
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

#define FCP_GET(Type, Port, Mask, Shift) FCP_GET_##Type(##Port, Mask, Shift)
#define FCP_SET(Type, Port, Mask, Shift, Source) FCP_SET_##Type(##Port, Mask, Shift, Source)

#ifdef MX_10F_TRIS

	#define FCP_GET_B(Port, Mask, Shift)   (FC_CAL_Port_In_DDR_10F_x((Mask), (Shift)))
	#define FCP_GET_M(Port, Mask, Shift)   (FC_CAL_Port_In_DDR_10F_x((Mask), (Shift)))
	#define FCP_GET_F(Port, Mask, Shift)   (FC_CAL_Port_In_DDR_10F_x((Mask), (Shift)))

	#define FCP_SET_B(p, m, b, v) 	(FC_CAL_Port_Out_DDR_10F_x((m), ((v) << (b))))
	#define FCP_SET_M(p, m, b, v) 	(FC_CAL_Port_Out_DDR_10F_x((m), (v) << (b)))
	#define FCP_SET_F(p, m, b, v) 	(FC_CAL_Port_Out_DDR_10F_x((m), (v) << (b)))

	#define FC_CAL_Bit_In(A, B)					test_bit(GPIO, B)
	#define FC_CAL_Bit_In_DDR(A, B, C)			{set_bit(tvar, C); asm("movf(_tvar),w"); asm("TRIS 6");}
	#define FC_CAL_Bit_High(A, B)				set_bit(GPIO, B)
	#define FC_CAL_Bit_High_DDR(A, B, C)		{clear_bit(tvar, C); asm("movf(_tvar),w"); asm("TRIS 6"); set_bit(GPIO, C);}
	#define FC_CAL_Bit_Low(A, B)				clear_bit(GPIO, B)
	#define FC_CAL_Bit_Low_DDR(A, B, C)			{clear_bit(tvar, C); asm("movf(_tvar),w"); asm("TRIS 6"); clear_bit(GPIO, C);}

#else

	#ifdef MX_16F5x_TRIS

		#define FCP_GET_B(Port, Mask, Shift)   (FC_CAL_Port_In_DDR_16F_##Port((Mask), (Shift)))
		#define FCP_GET_M(Port, Mask, Shift)   (FC_CAL_Port_In_DDR_16F_##Port((Mask), (Shift)))
		#define FCP_GET_F(Port, Mask, Shift)   (FC_CAL_Port_In_DDR_16F_##Port((Mask), (Shift)))

		#define FCP_SET_B(p, m, b, v) 	(FC_CAL_Port_Out_DDR_16F_##p((m), ((v) << (b))))
		#define FCP_SET_M(p, m, b, v) 	(FC_CAL_Port_Out_DDR_16F_##p((m), (v) << (b)))
		#define FCP_SET_F(p, m, b, v) 	(FC_CAL_Port_Out_DDR_16F_##p((m), (v) << (b)))


		#warning "Reduced functionality IO on your target device, components such as Software I2C and SPI may not compile correctly"
		/*
		#define FC_CAL_Bit_In(A, B)					test_bit(PORT##A, B)
		#define FC_CAL_Bit_In_DDR(A, B, C)			{set_bit(tvar, C); asm("movf(_tvar),w"); asm("TRIS 6");}
		#define FC_CAL_Bit_High(A, B)				set_bit(PORT##A, B)
		#define FC_CAL_Bit_High_DDR(A, B, C)		{clear_bit(tvar, C); asm("movf(_tvar),w"); asm("TRIS 6"); set_bit(PORT##A, C);}
		#define FC_CAL_Bit_Low(A, B)				clear_bit(PORT##A, B)
		#define FC_CAL_Bit_Low_DDR(A, B, C)			{clear_bit(tvar, C); asm("movf(_tvar),w"); asm("TRIS 6"); clear_bit(PORT##A, C);}
		*/

	#else

		#define FCP_GET_B(Port, Mask, Shift)   (FC_CAL_Port_In_DDR__x((&FCP_PORT_##Port), (&FCP_TRIS_##Port), (Mask), (Shift)))
		#define FCP_GET_M(Port, Mask, Shift)   (FC_CAL_Port_In_DDR__x((&FCP_PORT_##Port), (&FCP_TRIS_##Port), (Mask), (Shift)))
		#define FCP_GET_F(Port, Mask, Shift)   (FC_CAL_Port_In_DDR__x((&FCP_PORT_##Port), (&FCP_TRIS_##Port), (Mask), (Shift)))

		#define FCP_SET_B(Port, Mask, Shift, Source)    {FCP_TRIS_##Port &= ~Mask; (Source) ? (FCP_PORT_##Port = FCP_LAT_##Port | Mask) : (FCP_PORT_##Port = FCP_LAT_##Port & ~Mask);}
		#define FCP_SET_M(Port, Mask, Shift, Source)    {FCP_TRIS_##Port &= ~Mask; FCP_PORT_##Port = (FCP_LAT_##Port & ~Mask) | (((Source) << Shift) & Mask);}
		#define FCP_SET_F(Port, Mask, Shift, Source)    {FCP_TRIS_##Port = 0; FCP_PORT_##Port = (Source);}

		#define FC_CAL_Bit_In(A, B)					test_bit(A, B)
		#define FC_CAL_Bit_In_DDR(A, B, C)			set_bit(B, C)
		#define FC_CAL_Bit_High(A, B)				set_bit(A, B)
		#define FC_CAL_Bit_High_DDR(A, B, C)		{clear_bit(B, C); set_bit(A, C);}
		#define FC_CAL_Bit_Low(A, B)				clear_bit(A, B)
		#define FC_CAL_Bit_Low_DDR(A, B, C)			{clear_bit(B, C); clear_bit(A, C);}

	#endif

#endif



#define FCP_SET_NODDR(Port, Pin, Value)	\
#if defined(_LAT##Port##Pin) || defined(_LAT##Port##_LAT##Port##Pin##_POSITION) \
LAT##Port##bits.LAT##Port##Pin = Value;\
#else \
PORT##Port##bits.R##Port##Pin = Value; \
#endif \

	#if defined (_GPIO_GP0_POSN) || defined (_GPIO_GP1_POSN) || defined (_GPIO_GP2_POSN) || defined (_GPIO_GP3_POSN)
		#define FCP_PORT_A GPIO
		#define FCP_TRIS_A TRISIO
		#define PORTA GPIO
		#define TRISA TRISIO
		#define porta GPIO
		#define trisa TRISIO
	#endif
	#if defined (_LATA_LATA0_POSN) || defined (_LATA_LATA1_POSN) || defined (_LATA_LATA2_POSN) || defined (_LATA_LATA3_POSN) || defined (_LATA_LATA4_POSN) || defined (_LATA_LATA5_POSN) || defined (_LATA_LATA6_POSN) || defined (_LATA_LATA7_POSN)
		#define FCP_LAT_A LATA
	#else
		#define FCP_LAT_A FCP_PORT_A
	#endif
	#if defined (_PORTA_RA0_POSN) || defined (_PORTA_RA1_POSN) || defined (_PORTA_RA2_POSN) || defined (_PORTA_RA3_POSN) || defined (_PORTA_RA4_POSN) || defined (_PORTA_RA5_POSN) || defined (_PORTA_RA6_POSN) || defined (_PORTA_RA7_POSN) || defined (_GPIO_GP0_POSN) || defined (_GPIO_GP1_POSN) || defined (_GPIO_GP2_POSN) || defined (_GPIO_GP3_POSN)
		#ifndef FCP_PORT_A
			#define FCP_PORT_A PORTA
			#define FCP_TRIS_A TRISA
			#define trisa TRISA
			#define porta PORTA
		#endif
	#endif
	#if defined (_LATB_LATB0_POSN) || defined (_LATB_LATB1_POSN) || defined (_LATB_LATB2_POSN) || defined (_LATB_LATB3_POSN) || defined (_LATB_LATB4_POSN) || defined (_LATB_LATB5_POSN) || defined (_LATB_LATB6_POSN) || defined (_LATB_LATB7_POSN)
		#define FCP_LAT_B LATB
	#else
		#define FCP_LAT_B FCP_PORT_B
	#endif
	#if defined (_PORTB_RB0_POSN) || defined (_PORTB_RB1_POSN) || defined (_PORTB_RB2_POSN) || defined (_PORTB_RB3_POSN) || defined (_PORTB_RB4_POSN) || defined (_PORTB_RB5_POSN) || defined (_PORTB_RB6_POSN) || defined (_PORTB_RB7_POSN)
		#define FCP_PORT_B PORTB
		#define FCP_TRIS_B TRISB
		#define trisb TRISB
		#define portb PORTB
	#endif
	#if defined (_LATC_LATC0_POSN) || defined (_LATC_LATC1_POSN) || defined (_LATC_LATC2_POSN) || defined (_LATC_LATC3_POSN) || defined (_LATC_LATC4_POSN) || defined (_LATC_LATC5_POSN) || defined (_LATC_LATC6_POSN) || defined (_LATC_LATC7_POSN)
		#define FCP_LAT_C LATC
	#else
		#define FCP_LAT_C FCP_PORT_C
	#endif
	#if defined (_PORTC_RC0_POSN) || defined (_PORTC_RC1_POSN) || defined (_PORTC_RC2_POSN) || defined (_PORTC_RC3_POSN) || defined (_PORTC_RC4_POSN) || defined (_PORTC_RC5_POSN) || defined (_PORTC_RC6_POSN) || defined (_PORTC_RC7_POSN)
		#define FCP_PORT_C PORTC
		#define FCP_TRIS_C TRISC
		#define trisc TRISC
		#define portc PORTC
	#endif
	#if defined (_LATD_LATD0_POSN) || defined (_LATD_LATD1_POSN) || defined (_LATD_LATD2_POSN) || defined (_LATD_LATD3_POSN) || defined (_LATD_LATD4_POSN) || defined (_LATD_LATD5_POSN) || defined (_LATD_LATD6_POSN) || defined (_LATD_LATD7_POSN)
		#define FCP_LAT_D LATD
	#else
		#define FCP_LAT_D FCP_PORT_D
	#endif
	#if defined (_PORTD_RD0_POSN) || defined (_PORTD_RD1_POSN) || defined (_PORTD_RD2_POSN) || defined (_PORTD_RD3_POSN) || defined (_PORTD_RD4_POSN) || defined (_PORTD_RD5_POSN) || defined (_PORTD_RD6_POSN) || defined (_PORTD_RD7_POSN)
		#define FCP_PORT_D PORTD
		#define FCP_TRIS_D TRISD
		#define trisd TRISD
		#define portd PORTD
	#endif
	#if defined (_LATE_LATE0_POSN) || defined (_LATE_LATE1_POSN) || defined (_LATE_LATE2_POSN) || defined (_LATE_LATE3_POSN) || defined (_LATE_LATE4_POSN) || defined (_LATE_LATE5_POSN) || defined (_LATE_LATE6_POSN) || defined (_LATE_LATE7_POSN)
		#define FCP_LAT_E LATE
	#else
		#define FCP_LAT_E FCP_PORT_E
	#endif
	#if defined (_PORTE_RE0_POSN) || defined (_PORTE_RE1_POSN) || defined (_PORTE_RE2_POSN) || defined (_PORTE_RE3_POSN) || defined (_PORTE_RE4_POSN) || defined (_PORTE_RE5_POSN) || defined (_PORTE_RE6_POSN) || defined (_PORTE_RE7_POSN)
		#define FCP_PORT_E PORTE
		#define FCP_TRIS_E TRISE
		#define trise TRISE
		#define porte PORTE
	#endif
	#if defined (_LATF_LATF0_POSN) || defined (_LATF_LATF1_POSN) || defined (_LATF_LATF2_POSN) || defined (_LATF_LATF3_POSN) || defined (_LATF_LATF4_POSN) || defined (_LATF_LATF5_POSN) || defined (_LATF_LATF6_POSN) || defined (_LATF_LATF7_POSN)
		#define FCP_LAT_F LATF
	#else
		#define FCP_LAT_F FCP_PORT_F
	#endif
	#if defined (_PORTF_RF0_POSN) || defined (_PORTF_RF1_POSN) || defined (_PORTF_RF2_POSN) || defined (_PORTF_RF3_POSN) || defined (_PORTF_RF4_POSN) || defined (_PORTF_RF5_POSN) || defined (_PORTF_RF6_POSN) || defined (_PORTF_RF7_POSN)
		#define FCP_PORT_F PORTF
		#define FCP_TRIS_F TRISF
		#define trisf TRISF
		#define portf PORTF
	#endif
	#if defined (_LATG_LATG0_POSN) || defined (_LATG_LATG1_POSN) || defined (_LATG_LATG2_POSN) || defined (_LATG_LATG3_POSN) || defined (_LATG_LATG4_POSN) || defined (_LATG_LATG5_POSN) || defined (_LATG_LATG6_POSN) || defined (_LATG_LATG7_POSN)
		#define FCP_LAT_G LATG
	#else
		#define FCP_LAT_G FCP_PORT_G
	#endif
	#if defined (_PORTG_RG0_POSN) || defined (_PORTG_RG1_POSN) || defined (_PORTG_RG2_POSN) || defined (_PORTG_RG3_POSN) || defined (_PORTG_RG4_POSN) || defined (_PORTG_RG5_POSN) || defined (_PORTG_RG6_POSN) || defined (_PORTG_RG7_POSN)
		#define FCP_PORT_G PORTG
		#define FCP_TRIS_G TRISG
		#define trisg TRISG
		#define portg PORTG
	#endif
	#if defined (_LATH_LATH0_POSN) || defined (_LATH_LATH1_POSN) || defined (_LATH_LATH2_POSN) || defined (_LATH_LATH3_POSN) || defined (_LATH_LATH4_POSN) || defined (_LATH_LATH5_POSN) || defined (_LATH_LATH6_POSN) || defined (_LATH_LATH7_POSN)
		#define FCP_LAT_H LATH
	#else
		#define FCP_LAT_H FCP_PORT_H
	#endif
	#if defined (_PORTH_RH0_POSN) || defined (_PORTH_RH1_POSN) || defined (_PORTH_RH2_POSN) || defined (_PORTH_RH3_POSN) || defined (_PORTH_RH4_POSN) || defined (_PORTH_RH5_POSN) || defined (_PORTH_RH6_POSN) || defined (_PORTH_RH7_POSN)
		#define FCP_PORT_H PORTH
		#define FCP_TRIS_H TRISH
		#define trish TRISH
		#define porth PORTH
	#endif
	#if defined (_LATJ_LATJ0_POSN) || defined (_LATJ_LATJ1_POSN) || defined (_LATJ_LATJ2_POSN) || defined (_LATJ_LATJ3_POSN) || defined (_LATJ_LATJ4_POSN) || defined (_LATJ_LATJ5_POSN) || defined (_LATJ_LATJ6_POSN) || defined (_LATJ_LATJ7_POSN)
		#define FCP_LAT_J LATJ
	#else
		#define FCP_LAT_J FCP_PORT_J
	#endif
	#if defined (_PORTJ_RJ0_POSN) || defined (_PORTJ_RJ1_POSN) || defined (_PORTJ_RJ2_POSN) || defined (_PORTJ_RJ3_POSN) || defined (_PORTJ_RJ4_POSN) || defined (_PORTJ_RJ5_POSN) || defined (_PORTJ_RJ6_POSN) || defined (_PORTJ_RJ7_POSN)
		#define FCP_PORT_J PORTJ
		#define FCP_TRIS_J TRISJ
		#define trisj TRISJ
		#define portj PORTJ
	#endif
	#if defined (_LATK_LATK0_POSN) || defined (_LATK_LATK1_POSN) || defined (_LATK_LATK2_POSN) || defined (_LATK_LATK3_POSN) || defined (_LATK_LATK4_POSN) || defined (_LATK_LATK5_POSN) || defined (_LATK_LATK6_POSN) || defined (_LATK_LATK7_POSN)
		#define FCP_LAT_K LATK
	#else
		#define FCP_LAT_K FCP_PORT_K
	#endif
	#if defined (_PORTK_RK0_POSN) || defined (_PORTK_RK1_POSN) || defined (_PORTK_RK2_POSN) || defined (_PORTK_RK3_POSN) || defined (_PORTK_RK4_POSN) || defined (_PORTK_RK5_POSN) || defined (_PORTK_RK6_POSN) || defined (_PORTK_RK7_POSN)
		#define FCP_PORT_K PORTK
		#define FCP_TRIS_K TRISK
		#define trisk TRISK
		#define portk PORTK
	#endif

