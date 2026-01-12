// CRC: 5D982BB222882C54AB4AFF20A1590FC484D3178BD0D2510D0F5A64A7853221CAE2C33FABBE4F69A6659399D51781B7B9717EEBB53B2D55924CD9FD881E61BD8E186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5599CF2430EE30E011663C5E80E75652FD1D90E95736203D4D571055855D075BDF9AB82199DD434C4B6351966EC77FCAAF68D970B78B5E91D0255013C8F5AB5D39A2728773B1A63736571455BE810A2D40791785AC80D155F549D34A0D5AD11F31F126304527F3A87F7E3366096A99EA7264872214D721D0A
// REVISION: 1.0
// GUID: 0A28FEB9-0A1E-40E4-9FD3-A24D8F3A2A13
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\PIC16BIT_CAL_Delay.c
/*********************************************************************
 *                  Flowcode CAL Delays File
 *
 * File: PIC_CAL_Delay.c
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
 * 010911 | BR | Created
 * 020312 | BR | Updated to v5.1 CAL Schema
 */


extern void __delay32(unsigned long count);

#ifndef MX_CLKS_PER_INST
	#define MX_CLKS_PER_INST 2
#endif


//Calculate delays based on device MIPS per clock - minimum delay 11 instructions
#define delay_us(A)				__delay32((unsigned long)(A)*(MX_Fosc / (MX_CLKS_PER_INST * 1000000)))
#define delay_10us(A)			__delay32((unsigned long)(A)*(MX_Fosc / (MX_CLKS_PER_INST * 100000)))
#define delay_ms(A)				__delay32((unsigned long)(A)*(MX_Fosc / (MX_CLKS_PER_INST * 1000)))
#define delay_s(A)				__delay32((unsigned long)(A)*(MX_Fosc / MX_CLKS_PER_INST))


#define FCI_DELAYBYTE_US	delay_us
#define FCI_DELAYBYTE_MS	delay_ms
#define FCI_DELAYBYTE_S		delay_s


// With watchdog timer
#define FCI_DELAYBYTEWDT_S(count)  Wdt_Delay_S((count))
#define FCI_DELAYBYTEWDT_MS(count) Wdt_Delay_Ms((count))
#define FCI_DELAYBYTEWDT_US(count) delay_us((count))


//New Int Delays
void FCI_DELAYINT_US(MX_UINT16 Delay);
void FCI_DELAYINT_MS(MX_UINT16 Delay);
void FCI_DELAYINTWDT_MS(MX_UINT16 Delay);
void FCI_DELAYINT_S(MX_UINT16 Delay);
void FCI_DELAYINTWDT_S(MX_UINT16 Delay);

#define nop()	asm("NOP")

void Wdt_Delay_S(char delay);
void Wdt_Delay_Ms(char delay);

void Wdt_Delay_S(char delay)
{
    char i;
    short j;
    for (i=0; i<delay; i++)
    {
        for (j=0; j<999; j++)
        {
            Wdt_Delay_Ms(1);
        }
    }
}

void Wdt_Delay_Ms(char delay)
{
    char i;
    for (i=0; i<delay; i++)
    {
        MX_CLEAR_WATCHDOG;        //Clear Watchdog Timer
        delay_ms(1);
    }
}

void FCI_DELAYINT_US(MX_UINT16 Delay)
{
  	while (Delay > 255)
  	{
	  	delay_us(255);
	  	Delay = Delay - 255;
  	}
  	if (Delay > 0)
  		delay_us(Delay & 0xFF);
}

void FCI_DELAYINT_MS(MX_UINT16 Delay)
{
  	while (Delay > 255)
  	{
	  	delay_ms(255);
	  	Delay = Delay - 255;
  	}
  	if (Delay > 0)
  		delay_ms(Delay & 0xFF);
}

void FCI_DELAYINTWDT_MS(MX_UINT16 Delay)
{
  	while (Delay > 255)
  	{
	  	Wdt_Delay_Ms(255);
	  	Delay = Delay - 255;
  	}
  	if (Delay > 0)
  		Wdt_Delay_Ms(Delay & 0xFF);
}

void FCI_DELAYINT_S(MX_UINT16 Delay)
{
  	while (Delay > 255)
  	{
	  	delay_s(255);
	  	Delay = Delay - 255;
  	}
  	if (Delay > 0)
  		delay_s(Delay & 0xFF);
}

void FCI_DELAYINTWDT_S(MX_UINT16 Delay)
{
  	while (Delay > 255)
  	{
	  	Wdt_Delay_S(255);
	  	Delay = Delay - 255;
  	}
  	if (Delay > 0)
  		Wdt_Delay_S(Delay & 0xFF);
}


