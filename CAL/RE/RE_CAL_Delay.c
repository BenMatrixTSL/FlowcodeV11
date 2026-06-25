// CRC: 3DA5483D3EF86CFE38B5E3C960DE4A45485B4DFC6BA9FBAD3BD86F068823E4C035FBD5A4776A6F3EEC59A7B2A7480528A54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E150D3E80BF86F1B0DBC06FDDA5DB7610E0FD32EDE4D78F68B1963950FA4B28B11EC6D526E2337E70B7AA14006AE1CF71DDBC91091C7DC1D684EAEDC56B9CA8ED6F152536D475FA8D09220F6971E2AA525AB6330F903D737808549D34A0D5AD11F3C442464253BBDEB95706FFAAAA3169D7C7CACE59293285D6A8B2FE2536E6C50FEBD31FED13C8BAD2
// REVISION: 1.0
// GUID: D4E5F6A7-B8C9-0123-DEF0-234567890123
// DATE: 25\06\2026
// DIR: CAL\RE\RE_CAL_Delay.c
/*
 * Flowcode CAL Delay - Renesas RA4M1 (ARM Cortex-M4)
 *
 * Uses SysTick down-counter at processor clock frequency.
 * RA4M1 default clock: 48MHz HOCO. Adjust RA4M1_SYSCLK if different.
 *
 * SysTick counts DOWN from LOAD to 0, then sets COUNTFLAG.
 * Max single delay: ~350ms at 48MHz (24-bit counter @ 48M ticks/s).
 */

#include "ra4m1.h"

/* Byte-level delay wrappers */
#define FCI_DELAYBYTE_US(x)          delay_us(x)
#define FCI_DELAYBYTEWDT_US(x)       delay_us(x)
#define FCI_DELAYBYTE_10US(x)        delay_10us(x)
#define FCI_DELAYBYTEWDT_10US(x)     delay_10us(x)
#define FCI_DELAYBYTE_MS(x)          delay_ms(x)
#define FCI_DELAYBYTEWDT_MS(x)       delay_ms(x)
#define FCI_DELAYBYTE_S(x)           delay_s(x)
#define FCI_DELAYBYTEWDT_S(x)        delay_s(x)

/* Integer (16-bit) delay wrappers */
#define FCI_DELAYINT_US(x)           delay_us((unsigned long)(x))
#define FCI_DELAYINTWDT_US(x)        delay_us((unsigned long)(x))
#define FCI_DELAYINT_10US(x)         delay_10us((unsigned long)(x))
#define FCI_DELAYINTWDT_10US(x)      delay_10us((unsigned long)(x))
#define FCI_DELAYINT_MS(x)           delay_ms((unsigned long)(x))
#define FCI_DELAYINTWDT_MS(x)        delay_ms((unsigned long)(x))
#define FCI_DELAYINT_S(x)            delay_s((unsigned long)(x))
#define FCI_DELAYINTWDT_S(x)         delay_s((unsigned long)(x))

/* Cycles per microsecond at the system clock */
#define RA_CYCLES_PER_US  (RA4M1_SYSCLK / 1000000UL)

/* Overhead compensation: approximate cycles consumed before the loop */
#define RA_DELAY_OVERHEAD_CYCLES  12UL

static void delay_us(unsigned long us)
{
    if (us == 0UL)
        return;

    /* Cap at ~350ms to avoid 24-bit overflow */
    if (us > 349000UL)
        us = 349000UL;

    unsigned long ticks = us * RA_CYCLES_PER_US;
    if (ticks > RA_DELAY_OVERHEAD_CYCLES)
        ticks -= RA_DELAY_OVERHEAD_CYCLES;

    SysTick->LOAD = ticks - 1UL;
    SysTick->VAL  = 0UL;
    SysTick->CTRL = SysTick_CTRL_ENABLE | SysTick_CTRL_CLKSOURCE;

    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG) == 0U)
        ;

    SysTick->CTRL = 0UL;
}

static void delay_10us(unsigned long tens_of_us)
{
    delay_us(tens_of_us * 10UL);
}

static void delay_ms(unsigned long ms)
{
    unsigned long i;
    for (i = 0UL; i < ms; i++)
        delay_us(1000UL);
}

static void delay_s(unsigned long s)
{
    unsigned long i;
    for (i = 0UL; i < s; i++)
        delay_ms(1000UL);
}

/* Watchdog variants - same as plain (no WDT on RA4M1 via CAL yet) */
static void Wdt_Delay_Ms(unsigned long ms)  { delay_ms(ms); }
static void Wdt_Delay_S(unsigned long s)    { delay_s(s); }
