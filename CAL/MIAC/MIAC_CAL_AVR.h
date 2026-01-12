// CRC: 6EC20609B0E0838D6280BD8BA490CD44996AE0C14A44FEA45B91845A0946B1BA3125C6D160218ADBA2E7A22932CF20129A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF52BA7A10C11864E52D77B8D76B8C51E83DA50660992321E7425D6F7133275D21619F7664A1B45101CF01A76F743ED3E2236675E195E04FEA58B17C5B6770324E48332A7524F73ED0A61734D80D877634A4B066FE0AF5B7B80549D34A0D5AD11F321F2DB54FA4EE4D9F7AD019E84948FB9EE9197A8E8E26C270C9FBA1F01A7E45B08B65E7F68830DD9
// REVISION: 1.0
// GUID: 4EC1848D-1310-43B8-B303-9008E7E99070
// DATE: 08\08\2022
// DIR: CAL\MIAC\MIAC_CAL_AVR.h
/*********************************************************************
 *                  Flowcode CAL File
 *
 * File: MIAC_CAL_AVR.h
 *
 * (c) 2015 Matrix TSL
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
 * 171115 | LM | Created 
 *
 */


#ifndef MIAC_CAL_AVR_H
#define MIAC_CAL_AVR_H

// ATmega1281/2561 port/pin defines

// set DB0-7 to output and set all 8 data bits to byte x
#define MIAC_LCD_DB_VAL_DDR(x)		{DDRC = 0xff; PORTC = (x);}
// set DB0-7 to input
#define MIAC_LCD_DB_IN_DDR			{DDRC = 0;}
// read/return value of DB0-7, assume already set to input
#define MIAC_LCD_DB_GET			(PINC)

#define MIAC_I1_IN_DDR			{DDRG &= 0xfe;}
#define MIAC_I1_GET				(PING & 1)
#define MIAC_I2_IN_DDR			{DDRG &= 0xfd;}
#define MIAC_I2_GET				(PING & 2)

#define MIAC_LCD_EN_CLR			{PORTD &= ~(1<< 6);}	
#define MIAC_LCD_EN_SET			{PORTD |= (1<< 6);}	
#define MIAC_LCD_RS_CLR			{PORTD &= ~(1<< 4);}	
#define MIAC_LCD_RS_SET			{PORTD |= (1<< 4);}	
#define MIAC_LCD_RW_CLR			{PORTD &= ~(1<< 5);}	
#define MIAC_LCD_RW_SET			{PORTD |= (1<< 5);}	
#define MIAC_LCD_RT_CLR			{PORTD &= ~(1<< 7);}	
#define MIAC_LCD_RT_SET			{PORTD |= (1<< 7);}	
#define MIAC_LCD_BL_CLR			{PORTG &= ~(1<< 2);}	
#define MIAC_LCD_BL_SET			{PORTG |= (1<< 2);}	

// Handshake control
// set bit value 0 or 1 (assume DDR already set)
#define MIAC_LCD_EN_VAL(x)			{if (x) MIAC_LCD_EN_SET else MIAC_LCD_EN_CLR;}
#define MIAC_LCD_RS_VAL(x)			{if (x) MIAC_LCD_RS_SET else MIAC_LCD_RS_CLR;}
#define MIAC_LCD_RW_VAL(x)			{if (x) MIAC_LCD_RW_SET else MIAC_LCD_RW_CLR;}
#define MIAC_LCD_RT_VAL(x)			{if (x) MIAC_LCD_RT_SET else MIAC_LCD_RT_CLR;}
#define MIAC_LCD_BL_VAL(x)			{if (x) MIAC_LCD_BL_SET else MIAC_LCD_BL_CLR;}

// set DDR to out and bit value to x
#define MIAC_LCD_EN_VAL_DDR(x)		{DDRD |= (1<< 6); MIAC_LCD_EN_VAL(x);}	
#define MIAC_LCD_RS_VAL_DDR(x)		{DDRD |= (1<< 4); MIAC_LCD_RS_VAL(x);}	
#define MIAC_LCD_RW_VAL_DDR(x)		{DDRD |= (1<< 5); MIAC_LCD_RW_VAL(x);}	
#define MIAC_LCD_RT_VAL_DDR(x)		{DDRD |= (1<< 7); MIAC_LCD_RT_VAL(x);}	
#define MIAC_LCD_BL_VAL_DDR(x)		{DDRG |= (1<< 2); MIAC_LCD_BL_VAL(x);}	

#define MIAC_DB0_SET_DDR	{DDRC |= (1<<0); PORTC |= (1<<0);}
#define MIAC_DB1_SET_DDR	{DDRC |= (1<<1); PORTC |= (1<<1);}
#define MIAC_DB2_SET_DDR	{DDRC |= (1<<2); PORTC |= (1<<2);}
#define MIAC_DB3_SET_DDR	{DDRC |= (1<<3); PORTC |= (1<<3);}
#define MIAC_DB4_SET_DDR	{DDRC |= (1<<4); PORTC |= (1<<4);}
#define MIAC_DB5_SET_DDR	{DDRC |= (1<<5); PORTC |= (1<<5);}
#define MIAC_DB6_SET_DDR	{DDRC |= (1<<6); PORTC |= (1<<6);}
#define MIAC_DB7_SET_DDR	{DDRC |= (1<<7); PORTC |= (1<<7);}

#define MIAC_DB0_CLR_DDR	{DDRC |= (1<<0); PORTC &= ~(1<<0);}
#define MIAC_DB1_CLR_DDR	{DDRC |= (1<<1); PORTC &= ~(1<<1);}
#define MIAC_DB2_CLR_DDR	{DDRC |= (1<<2); PORTC &= ~(1<<2);}
#define MIAC_DB3_CLR_DDR	{DDRC |= (1<<3); PORTC &= ~(1<<3);}
#define MIAC_DB4_CLR_DDR	{DDRC |= (1<<4); PORTC &= ~(1<<4);}
#define MIAC_DB5_CLR_DDR	{DDRC |= (1<<5); PORTC &= ~(1<<5);}
#define MIAC_DB6_CLR_DDR	{DDRC |= (1<<6); PORTC &= ~(1<<6);}
#define MIAC_DB7_CLR_DDR	{DDRC |= (1<<7); PORTC &= ~(1<<7);}

#define MIAC_M1_SET_DDR	{DDRB |= (1<< 7); PORTB |= (1<< 7);}
#define MIAC_MA_SET_DDR	{DDRB |= (1<< 5); PORTB |= (1<< 5);}
#define MIAC_MB_SET_DDR	{DDRB |= (1<< 6); PORTB |= (1<< 6);}
#define MIAC_M2_SET_DDR	{DDRB |= (1<< 4); PORTB |= (1<< 4);}
#define MIAC_MC_SET_DDR	{DDRE |= (1<< 3); PORTE |= (1<< 3);}
#define MIAC_MD_SET_DDR	{DDRE |= (1<< 4); PORTE |= (1<< 4);}

#define MIAC_M1_CLR_DDR	{DDRB |= (1<< 7); PORTB &= ~(1<< 7);}
#define MIAC_MA_CLR_DDR	{DDRB |= (1<< 5); PORTB &= ~(1<< 5);}
#define MIAC_MB_CLR_DDR	{DDRB |= (1<< 6); PORTB &= ~(1<< 6);}
#define MIAC_M2_CLR_DDR	{DDRB |= (1<< 4); PORTB &= ~(1<< 4);}
#define MIAC_MC_CLR_DDR	{DDRE |= (1<< 3); PORTE &= ~(1<< 3);}
#define MIAC_MD_CLR_DDR	{DDRE |= (1<< 4); PORTE &= ~(1<< 4);}

#define MIAC_Q1_SET_DDR	{DDRA |= (1<<0); PORTA |= (1<<0);}
#define MIAC_Q2_SET_DDR	{DDRA |= (1<<1); PORTA |= (1<<1);}
#define MIAC_Q3_SET_DDR	{DDRA |= (1<<2); PORTA |= (1<<2);}
#define MIAC_Q4_SET_DDR	{DDRA |= (1<<3); PORTA |= (1<<3);}

#define MIAC_Q1_CLR_DDR	{DDRA |= (1<<0); PORTA &= ~(1<<0);}
#define MIAC_Q2_CLR_DDR	{DDRA |= (1<<1); PORTA &= ~(1<<1);}
#define MIAC_Q3_CLR_DDR	{DDRA |= (1<<2); PORTA &= ~(1<<2);}
#define MIAC_Q4_CLR_DDR	{DDRA |= (1<<3); PORTA &= ~(1<<3);}


#define MIAC_CS_CAN_CLR_DDR	{DDRE |= (1<< 6); PORTE &= ~(1<< 6);}
#define MIAC_CS_ADC_CLR_DDR	{DDRE |= (1<< 5); PORTE &= ~(1<< 5);}

#define MIAC_CS_CAN_SET_DDR	{DDRE |= (1<< 6); PORTE |= (1<< 6);}
#define MIAC_CS_ADC_SET_DDR	{DDRE |= (1<< 5); PORTE |= (1<< 5);}

#define MIAC_RTS1_CLR				{PORTG &= ~(1<< 4);}	
#define MIAC_RTS1_SET				{PORTG |= (1<< 4);}	
#define MIAC_RTS1_VAL(x)			{if (x) MIAC_RTS1_SET else MIAC_RTS1_CLR;}
#define MIAC_RTS1_VAL_DDR(x)		{DDRG |= (1<< 4); MIAC_RTS1_VAL(x);}	

#endif
