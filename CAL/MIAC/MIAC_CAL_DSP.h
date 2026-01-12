// CRC: 6EC20609B0E0838D6280BD8BA490CD44996AE0C14A44FEA45B91845A0946B1BA51D239AAF805F364957D38E4E2B5615A9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF56C25AD415F35E75870807C21F088C046F29623F8FB52D752A12E5FB5E05DDFC8A9E5687A358F4DC586DA11A1CCF6F46F96D23EF3072C25DA6296F97CB9F71ABD0E80D8A22B0F9675DFC12EECF0790B6D756684AB1CA1D8F2549D34A0D5AD11F3E096F18646CF0CCF47B9F7D7B54F1E1E47E11C9510A2E761850400E5B608E745107C571680B732A8
// REVISION: 1.0
// GUID: D6AADCA3-32AE-49E2-9BDA-599A67983C1D
// DATE: 08\08\2022
// DIR: CAL\MIAC\MIAC_CAL_DSP.h
/*********************************************************************
 *                  Flowcode CAL File
 *
 * File: MIAC_CAL_DSP.h
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


#ifndef MIAC_CAL_DSP_H
#define MIAC_CAL_DSP_H

// dsPIC port/pin defines

// set DB0-7 to output and set all 8 data bits to byte x
#define MIAC_LCD_DB_VAL_DDR(x)		{TRISB &= 0x00ff; LATB = (LATB & 0x00ff)|(x<<8);}
// set DB0-7 to input
#define MIAC_LCD_DB_IN_DDR			{TRISB |= 0xff00;}
// read/return value of DB0-7, assume already set to input
#define MIAC_LCD_DB_GET				(PORTB >> 8)

#define MIAC_I1_IN_DDR			{TRISB |= 1;}
#define MIAC_I1_GET				(PORTB & 1)
#define MIAC_I2_IN_DDR			{TRISB |= 2;}
#define MIAC_I2_GET				(PORTB & 2)

#define MIAC_LCD_EN_CLR			{LATD &= ~(1<<10);}	
#define MIAC_LCD_EN_SET			{LATD |= (1<<10);}	
#define MIAC_LCD_RS_CLR			{LATD &= ~(1<< 8);}	
#define MIAC_LCD_RS_SET			{LATD |= (1<< 8);}	
#define MIAC_LCD_RW_CLR			{LATD &= ~(1<< 9);}	
#define MIAC_LCD_RW_SET			{LATD |= (1<< 9);}	
#define MIAC_LCD_RT_CLR			{LATD &= ~(1<<11);}	
#define MIAC_LCD_RT_SET			{LATD |= (1<<11);}	
#define MIAC_LCD_BL_CLR			{LATF &= ~(1<< 3);}	
#define MIAC_LCD_BL_SET			{LATF |= (1<< 3);}	

// Handshake control
// set bit value 0 or 1 (assume DDR already set)
#define MIAC_LCD_EN_VAL(x)			{if (x) MIAC_LCD_EN_SET else MIAC_LCD_EN_CLR;}
#define MIAC_LCD_RS_VAL(x)			{if (x) MIAC_LCD_RS_SET else MIAC_LCD_RS_CLR;}
#define MIAC_LCD_RW_VAL(x)			{if (x) MIAC_LCD_RW_SET else MIAC_LCD_RW_CLR;}
#define MIAC_LCD_RT_VAL(x)			{if (x) MIAC_LCD_RT_SET else MIAC_LCD_RT_CLR;}
#define MIAC_LCD_BL_VAL(x)			{if (x) MIAC_LCD_BL_SET else MIAC_LCD_BL_CLR;}

// set DDR to out and bit value to x
#define MIAC_LCD_EN_VAL_DDR(x)		{TRISD &= ~(1<<10); MIAC_LCD_EN_VAL(x);}	
#define MIAC_LCD_RS_VAL_DDR(x)		{TRISD &= ~(1<< 8); MIAC_LCD_RS_VAL(x);}	
#define MIAC_LCD_RW_VAL_DDR(x)		{TRISD &= ~(1<< 9); MIAC_LCD_RW_VAL(x);}	
#define MIAC_LCD_RT_VAL_DDR(x)		{TRISD &= ~(1<<11); MIAC_LCD_RT_VAL(x);}	
#define MIAC_LCD_BL_VAL_DDR(x)		{TRISF &= ~(1<< 3); MIAC_LCD_BL_VAL(x);}	

#define MIAC_DB0_SET_DDR	{TRISB &= ~(1<<8); LATB |= (1<<8);}
#define MIAC_DB1_SET_DDR	{TRISB &= ~(1<<9); LATB |= (1<<9);}
#define MIAC_DB2_SET_DDR	{TRISB &= ~(1<<10); LATB |= (1<<10);}
#define MIAC_DB3_SET_DDR	{TRISB &= ~(1<<11); LATB |= (1<<11);}
#define MIAC_DB4_SET_DDR	{TRISB &= ~(1<<12); LATB |= (1<<12);}
#define MIAC_DB5_SET_DDR	{TRISB &= ~(1<<13); LATB |= (1<<13);}
#define MIAC_DB6_SET_DDR	{TRISB &= ~(1<<14); LATB |= (1<<14);}
#define MIAC_DB7_SET_DDR	{TRISB &= ~(1<<15); LATB |= (1<<15);}

#define MIAC_DB0_CLR_DDR	{TRISB &= ~(1<<8); LATB &= ~(1<<8);}
#define MIAC_DB1_CLR_DDR	{TRISB &= ~(1<<9); LATB &= ~(1<<9);}
#define MIAC_DB2_CLR_DDR	{TRISB &= ~(1<<10); LATB &= ~(1<<10);}
#define MIAC_DB3_CLR_DDR	{TRISB &= ~(1<<11); LATB &= ~(1<<11);}
#define MIAC_DB4_CLR_DDR	{TRISB &= ~(1<<12); LATB &= ~(1<<12);}
#define MIAC_DB5_CLR_DDR	{TRISB &= ~(1<<13); LATB &= ~(1<<13);}
#define MIAC_DB6_CLR_DDR	{TRISB &= ~(1<<14); LATB &= ~(1<<14);}
#define MIAC_DB7_CLR_DDR	{TRISB &= ~(1<<15); LATB &= ~(1<<15);}

#define MIAC_M1_SET_DDR	{TRISF &= ~(1<< 0); LATF |= (1<< 0);}
#define MIAC_MA_SET_DDR	{TRISD &= ~(1<< 4); LATD |= (1<< 4);}
#define MIAC_MB_SET_DDR	{TRISD &= ~(1<< 5); LATD |= (1<< 5);}
#define MIAC_M2_SET_DDR	{TRISF &= ~(1<< 1); LATF |= (1<< 1);}
#define MIAC_MC_SET_DDR	{TRISD &= ~(1<< 6); LATD |= (1<< 6);}
#define MIAC_MD_SET_DDR	{TRISD &= ~(1<< 7); LATD |= (1<< 7);}

#define MIAC_M1_CLR_DDR	{TRISF &= ~(1<< 0); LATF &= ~(1<< 0);}
#define MIAC_MA_CLR_DDR	{TRISD &= ~(1<< 4); LATD &= ~(1<< 4);}
#define MIAC_MB_CLR_DDR	{TRISD &= ~(1<< 5); LATD &= ~(1<< 5);}
#define MIAC_M2_CLR_DDR	{TRISF &= ~(1<< 1); LATF &= ~(1<< 1);}
#define MIAC_MC_CLR_DDR	{TRISD &= ~(1<< 6); LATD &= ~(1<< 6);}
#define MIAC_MD_CLR_DDR	{TRISD &= ~(1<< 7); LATD &= ~(1<< 7);}

#define MIAC_Q1_SET_DDR	{TRISD &= ~(1<< 0); LATD |= (1<< 0);}
#define MIAC_Q2_SET_DDR	{TRISD &= ~(1<< 1); LATD |= (1<< 1);}
#define MIAC_Q3_SET_DDR	{TRISD &= ~(1<< 2); LATD |= (1<< 2);}
#define MIAC_Q4_SET_DDR	{TRISD &= ~(1<< 3); LATD |= (1<< 3);}

#define MIAC_Q1_CLR_DDR	{TRISD &= ~(1<< 0); LATD &= ~(1<< 0);}
#define MIAC_Q2_CLR_DDR	{TRISD &= ~(1<< 1); LATD &= ~(1<< 1);}
#define MIAC_Q3_CLR_DDR	{TRISD &= ~(1<< 2); LATD &= ~(1<< 2);}
#define MIAC_Q4_CLR_DDR	{TRISD &= ~(1<< 3); LATD &= ~(1<< 3);}


#define MIAC_CS_CAN_CLR_DDR	{TRISB &= ~(1<< 3); LATB &= ~(1<< 3);}
#define MIAC_CS_ADC_CLR_DDR	{TRISB &= ~(1<< 2); LATB &= ~(1<< 2);}

#define MIAC_CS_CAN_SET_DDR	{TRISB &= ~(1<< 3); LATB |= (1<< 3);}
#define MIAC_CS_ADC_SET_DDR	{TRISB &= ~(1<< 2); LATB |= (1<< 2);}

#endif

