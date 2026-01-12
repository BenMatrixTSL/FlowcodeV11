// CRC: A6459004C43C0517DC6DFC5681C2AD698104299A14C9E1875427A2F7EF4303D9CFD76A29863CD488DE50EA9D9C0AC8D1717EEBB53B2D55924CD9FD881E61BD8E186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF52C66D56D205A63B6BFC3B49519C4FE1462A96EF7E2B3F275C2FFB068B8AA1D9766D11D7A006FE1C6D7A8A1614C5CE42A6152EB7EB920B78652C45724AFC11D1A6C8DF3C5342E47765E1D9AF31D63C944A053822A9B71577C549D34A0D5AD11F307EEF6DCD5F4236B6D6BAEA229BE87E5B5485268F03CA3DC77651D1BAA682C68D0B2E42AC1619AB5
// REVISION: 1.0
// GUID: 4D193109-6EF0-468E-A5E0-3B78A86A990A
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\PIC32BIT_CAL_Delay.c
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

void __attribute__((nomips16)) WriteCoreTimer(unsigned int timer)
{
    uint32_t loadZero = 0;
    asm volatile("mtc0   %0, $9" : "+r"(loadZero));
    asm volatile("mtc0   %0, $11" : "+r" (timer));
}

unsigned int __attribute__((nomips16)) ReadCoreTimer(void)
{
    unsigned int timer;

    // get the count reg
    asm volatile("mfc0   %0, $9" : "=r"(timer));

    return timer;
}


#ifdef MX_PIC32_MZ
	#define __delay32(A) 	{ WriteCoreTimer(0); while(ReadCoreTimer() < (A >> 2)); }
#else
	#define __delay32(A) 	{ WriteCoreTimer(0); while(ReadCoreTimer() < (A >> 1)); }
#endif


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


