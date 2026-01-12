// CRC: 77485F5F6A861F9125D47827B4DE492656C5431E478E8046055FD2257F64F1F312C52A9A458B17900EC8DB8A0EB203079A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF591591302675A58FA10A92574E444B5A4CB100DCAAA7853E27305F1EEACD428F1BACFE609763316D0AD65E8FC9B9217E02CD8B316293C1C9552D7BC67341C182FDF7726BDA4E5F359178D158EB41B3C831C005DC9F7ACB165549D34A0D5AD11F3CCB4070A1093D2314FAAFA089D847934C77D31BAAD7852B94646F04394134BC3E9D58A8ADF3C3B45
// REVISION: 1.0
// GUID: 363E36E3-6F33-43E9-9BD5-D2001DE20757
// DATE: 08\08\2022
// DIR: CAL\AVR\AVR_CAL_Delay.c
/*********************************************************************
 *                  Flowcode CAL Delays File
 *
 * File: AVR_CAL_Delay.c
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
 * 020312 | BR | Updated to v5.1 CAL Schema
 * 210114 | BR | Added some warnings which indicate if delays are being calculated incorrectly due to project clock speed
 */


#include <inttypes.h>

#include <util/delay_basic.h>


// Delay by bytes
#define FCI_DELAYBYTE_S(count)     delay_s((count))
#define FCI_DELAYBYTE_MS(count)    delay_ms((count))
#define FCI_DELAYBYTE_US(count)    delay_us((count))

// With watchdog timer
#define FCI_DELAYBYTEWDT_S(count)  Wdt_Delay_S((count))
#define FCI_DELAYBYTEWDT_MS(count) Wdt_Delay_Ms((count))
#define FCI_DELAYBYTEWDT_US(count) delay_us((count))


static inline void delay_us(uint8_t __us) __attribute__((always_inline));
static inline void delay_10us(uint8_t __us10) __attribute__((always_inline));
static inline void delay_ms(uint8_t __ms) __attribute__((always_inline));
static inline void delay_s(uint8_t __ms) __attribute__((always_inline));


// Define number of counts per time period using _delay_loop_2
#if (F_CPU >= 4000)
  #define MS_COUNT2 F_CPU / 4000
#else
  #define MS_COUNT2 1
  #warning "Your clock speed is too low for Millisecond delays to be calculated accurately"
#endif

#if (F_CPU >= 400000)
  #define US10_COUNT2 F_CPU / 400000
#else
  #define US10_COUNT2 1
  #warning "Your clock speed is too low for 10 x Microsecond delays to be calculated accurately"
#endif

#if (F_CPU >= 4000000)
  #define US_COUNT2 F_CPU / 4000000
#else
  #define US_COUNT2 1
  #warning "Your clock speed is too low for Microsecond delays to be calculated accurately"
#endif


void delay_us(uint8_t __us)
{
	_delay_loop_2(US_COUNT2 * __us);
}


void delay_10us(uint8_t __us10)
{
	_delay_loop_2(US10_COUNT2 * __us10);
}


void delay_ms(uint8_t __ms)
{
	uint8_t __ticks;

	for(__ticks=0;__ticks<__ms;__ticks++)
	{
		_delay_loop_2(MS_COUNT2);
	}
}


void delay_s(uint8_t __s)
{
	uint8_t __ticks;

	for(__ticks=0; __ticks<__s; __ticks++)
	{
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
		delay_ms(250);
	}
}


#define nop()	asm("NOP")

//Original Byte Delays
void Wdt_Delay_S(char delay);
void Wdt_Delay_Ms(char delay);

//New Int Delays
void FCI_DELAYINT_US(MX_UINT16 Delay);

void FCI_DELAYINT_MS(MX_UINT16 Delay);
void FCI_DELAYINTWDT_MS(MX_UINT16 Delay);

void FCI_DELAYINT_S(MX_UINT16 Delay);
void FCI_DELAYINTWDT_S(MX_UINT16 Delay);



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
