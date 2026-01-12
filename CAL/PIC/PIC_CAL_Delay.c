// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B812C52A9A458B17900EC8DB8A0EB203079A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5A666D60F8239B0D32E8DEE16C8A7C8D11C766C6F419F42F1F6E2A26E60FEBAB12CD230809E0C5F84C495999C855BBC9779266FBB4399EB31774F5C600AA088FE36DF900B66E3364165A8D41550C0D111B22A270D42704965549D34A0D5AD11F3B8C963744EE96ADC733D9DAB4ECC4AA1F117220421888FDA76AD1A7DB9B9D5F43F565616D7803A54
// REVISION: 1.0
// GUID: FC107A06-D101-4A3A-9FCE-A0280D803398
// DATE: 08\08\2022
// DIR: CAL\PIC\PIC_CAL_Delay.c
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
 *
 *
 *
 */

//Original Byte Delays
void Wdt_Delay_S(MX_UINT8 delay);
void Wdt_Delay_Ms(MX_UINT8 delay);

// Delay by bytes
#define FCI_DELAYBYTE_S(count)     delay_s((count))
#define FCI_DELAYBYTE_MS(count)    delay_ms((count))
#define FCI_DELAYBYTE_US(count)    delay_us((count))
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

void delay_10us(MX_UINT8 del);
void delay_us(MX_UINT8 del);
void delay_ms(MX_UINT8 del);
void delay_s(MX_UINT8 del);



void delay_10us(MX_UINT8 del)
{
	while (del--)
	{
		__delay_us(10);
	}
}



void delay_us(MX_UINT8 del)
{
	while (del > 99)
	{
		__delay_us(100);
		del -= 100;
	}
	while (del > 9)
	{
		__delay_us(10);
		del -= 10;
	}
	while (del--)
	{
		__delay_us(1);
	}
}



void delay_ms(MX_UINT8 del)
{
	while (del--)
	{
		__delay_ms(1);
	}
}


void delay_s(MX_UINT8 del)
{
	MX_UINT8 i;
	for(i=0; i<del; i++)
	{
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
	}
}



void Wdt_Delay_S(MX_UINT8 delay)
{
    MX_UINT8 i;
    MX_UINT16 j;
    for (i=0; i<delay; i++)
    {
        for (j=0; j<999; j++)
        {
            Wdt_Delay_Ms(1);
        }
    }
}

void Wdt_Delay_Ms(MX_UINT8 delay)
{
    MX_UINT8 i;
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


