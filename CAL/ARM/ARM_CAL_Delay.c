// CRC: AE5753800093D2B889297C6B876B6A21749C10AFA09C3FCE4A5F65B0FF76818F12C52A9A458B17900EC8DB8A0EB203079A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5DC4CAABFC691D37072C59BEE67F442B3AEC6AF90E981A94DACF898FB5C9CB943C47ECC54AB155911F0993C4BC36A6B9F1983207AEA0549354D4035FC536147D2FCAD4DAF314C9AE02501BFEDA9213805A75E782813476158549D34A0D5AD11F3230DC10488B38A446D3F61C215191E25E23DE50C65CB71E4FFCF1C90B393605E9F32B96E9FC2F3A9
// REVISION: 1.0
// GUID: F6E55A9F-2BF9-46D4-AF32-07155CA28408
// DATE: 08\08\2022
// DIR: CAL\ARM\ARM_CAL_Delay.c
/*********************************************************************
 *                  Flowcode CAL Delays File
 *
 * File: ARM_CAL_Delay.c
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
 * 060911 | BR | Created
 * 050312 | BR | Updated to v5.1 CAL Schema
 */

void delay_s(unsigned char count);
void delay_ms(unsigned char count);
void delay_10us(unsigned int count);
void delay_us(unsigned int count);
void Wdt_Delay_S(char delay);
void Wdt_Delay_Ms(char delay);


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


#define USCOUNT (MCK / 7500000)
#define US10COUNT (MCK / 800000)
#define nop()	asm("NOP")

void delay_s(unsigned char count)
{
	unsigned char i;

	for(i=0; i<count; i++)
	{
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
	}
}

void FCI_DELAYBYTE_MS(unsigned char count)
{
	unsigned char i;
	unsigned int loop;

	for(i=0; i<count; i++)
	{
		delay_10us(100);
	}
}

void delay_10us(unsigned int count)
{
	unsigned int i, max = US10COUNT * count;

	for(i=0; i<max; i++);
}

void delay_us(unsigned int count)
{
	unsigned int i, max = USCOUNT * count;

	for(i=0; i<max; i++);
}

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


#undef USCOUNT
#undef US10COUNT
