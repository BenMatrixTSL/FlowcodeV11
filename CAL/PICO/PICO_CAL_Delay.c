// CRC: F9C65A77A483DDF22B438B7FEB8E3C81451B6760FECB07508D29EE770BB95F47717EEBB53B2D55924CD9FD881E61BD8E186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF52B5F54CED87080F553DF7E1CEFA7F11D40E3CBF2D8141B40A6627D1F87F73AA5EB227B1F0B659673A83D57471E59F86201113141FF41BED9A00418B3B4C16665C2B06C5282338C679441CF84F6F4201496A359A48F1E5512549D34A0D5AD11F3BECB7E3279CDAC694F87542A3C092F6CEE992DD2D1D3489907369D99911C23D5D43797C197BFDEC5
// REVISION: 1.0
// GUID: DCF4A2CF-5986-4A4C-B235-EE7762426F7E
// DATE: 08\08\2022
// DIR: CAL\PICO\PICO_CAL_Delay.c

/*********************************************************************
 *                  Flowcode CAL Delays File
 *
 * File: PICO_CAL_Delay.c
 *
 * (c) 2021 Matrix TSL.
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
 * 260521 | LM | Created
 * 
 */


// Delay by bytes
#define FCI_DELAYBYTE_S(count)     	sleep_ms((count * 1000))
#define FCI_DELAYBYTE_MS(count)    	sleep_ms((count))
#define FCI_DELAYBYTE_US(count)    	sleep_us((count))

#define FCI_DELAYINT_S(count)     	sleep_ms((count * 1000))
#define FCI_DELAYINT_MS(count)    	sleep_ms((count))
#define FCI_DELAYINT_US(count)    	sleep_us((count))

// With watchdog timer
// Probably need implementing some time
#define FCI_DELAYBYTEWDT_S(count)	sleep_ms((count * 1000))
#define FCI_DELAYBYTEWDT_MS(count)	sleep_ms((count))
#define FCI_DELAYBYTEWDT_US(count)	sleep_us((count))

#define FCI_DELAYINTWDT_S(count)	sleep_ms((count * 1000))
#define FCI_DELAYINTWDT_MS(count)	sleep_ms((count))
#define FCI_DELAYINTWDT_US(count)	sleep_us((count))


// #include <driver/timer.h>

uint64_t FC_CAL_Timer_Period;
uint64_t FC_CAL_Timer_Multiplier;

void FC_CAL_Timer_0_ISR(void*);
void FC_CAL_Timer_1_ISR(void*);
void FC_CAL_Timer_2_ISR(void*);
void FC_CAL_Timer_3_ISR(void*);

void FC_CAL_Timer_Init(uint8_t timer, uint64_t period, void callback(void*))
{

}

