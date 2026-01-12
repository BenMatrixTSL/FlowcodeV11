// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BE482449ABEBE2EB6A5CD3436EB9EF64E0C1BCA31D2ABE272513C0D3F110D57B269A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5ABB9BF7E07821C560F20BBA7692027F73164E61114BEBBE7E3CFB5CFFA22970BD10343EBFBBCD93991DC9DF4832949B3260623D699032AC045670EA855EC7FC801ACCDC11BCF13B4794394C12C2450A37BDBCDF2FCFC9AC1549D34A0D5AD11F37E8536662423F658D370058EBC6F696CD3D448A23487A80E1EDE0E6E8CE8F293FC3F53D5103A0873
// REVISION: 1.0
// GUID: E5B7C122-BD65-459F-B786-05D32D79147A
// DATE: 08\08\2022
// DIR: CAL\STARM\STARM_CAL_Delay.c
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
 * 280414 | SK | Created
 */


// Delay by bytes
#define FCI_DELAYBYTE_S(count)     delay_s((count))
#define FCI_DELAYBYTE_MS(count)    delay_ms((count))
#define FCI_DELAYBYTE_US(count)    delay_us((count))

// With watchdog timer
#define FCI_DELAYBYTEWDT_S(count)  Wdt_Delay_S((count))
#define FCI_DELAYBYTEWDT_MS(count) Wdt_Delay_Ms((count))
#define FCI_DELAYBYTEWDT_US(count) delay_us((count))


static void delay_us(uint32_t __us);
static inline void delay_10us(uint32_t __us10);
static inline void delay_ms(uint32_t __ms);
static inline void delay_s(uint32_t __ms);


static void delay_us(uint32_t __us)
{
	__IO uint32_t tNow;
	uint32_t tPrev, tTarget;
	uint32_t us_res = (SysTick->LOAD + 1) / 1000;
	uint16_t cycle = 1;

	if(__us)	// Terminate immediately if the count value is 0
	{
		tNow = SysTick->VAL;	// Sample current SysTick count value (down counter)

		/* Decrement the delay value to compensate for the call overhead */
		
		if(--__us > 999999)		// Limit us delay function to 1s
			__us = 999999;
	
		if(__us >= 1000)		// Each whole ms delay is a full cycle of the SysTick counter
		{
			cycle += (__us / 1000);
			__us %= 1000;
		}
	
		__us *= us_res;		// Delay (after ms removal) = us * resolution
	
		if(__us > tNow)		// Target value will wrap at 0 (result would be -ve)
		{
			tTarget = (tNow + SysTick->LOAD) - __us;	// Calculate wrapped value and allow additional counter cycle
			cycle++;
		} else {
			tTarget = tNow - __us;						// Calculate value without wrap adjustment
		}
	
		while(cycle)
		{
			tPrev = tNow;
			tNow = SysTick->VAL;
		
			/* Compare consecutive samples of the SysTick counter value
				- 	If the current value is greater than the previous value (down counter)
					the counter has wrapped (1ms boundary) */
			if(tNow > tPrev)		
				cycle--;

			/*	-	If the SysTick is on its final cycle (cycle == 1) and the current count value is less than
					the target value, terminate the function by clearing the cycle value */		
			if((cycle == 1) && (tNow <= tTarget))
				cycle--;
		}
	}
}


static inline void delay_10us(uint32_t __us10)
{
	delay_us(__us10 * 10);
}


static inline void delay_ms(uint32_t __ms)
{
	while(__ms--)
		delay_us(1000);
}


static inline void delay_s(uint32_t __s)
{
	while(__s--)
		delay_us(1000000);
}


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
            delay_ms(1); // Delay_Ms(1);
        }
    }
}

void Wdt_Delay_Ms(char delay)
{
    char i;
    for (i=0; i<delay; i++)
    {
        //MX_CLEAR_WATCHDOG;        //Clear Watchdog Timer
        delay_ms(1);
    }
}

void FCI_DELAYINT_US(MX_UINT16 Delay)
{
  	delay_us(Delay);
}

void FCI_DELAYINT_MS(MX_UINT16 Delay)
{
  	delay_ms(Delay);
}

void FCI_DELAYINTWDT_MS(MX_UINT16 Delay)
{
  	Wdt_Delay_Ms(Delay);
}

void FCI_DELAYINT_S(MX_UINT16 Delay)
{
  	delay_s(Delay);
}

void FCI_DELAYINTWDT_S(MX_UINT16 Delay)
{
  	Wdt_Delay_S(Delay);
}
