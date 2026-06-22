// CRC: 0000000000000000000000000000000000000000000000000000000000000000
// REVISION: 1.0
// GUID: A9B0C1D2-E3F4-5678-2345-789012345678
// DATE: 22\06\2026
// DIR: FCD\RE\src\system_ra4m1.c
/*
 * RA4M1 System Initialization
 *
 * The RA4M1 powers on with the HOCO (High-speed On-Chip Oscillator) at 24MHz.
 * Flowcode targets 48MHz, achieved by enabling HOCO at 48MHz via CGC HOCOR.
 *
 * Register references:
 *   CGC (Clock Generation Circuit): 0x4001E000
 *   HOCOCR: 0x4001E036 - HOCO Control (bit0: HCSTP=0 to enable)
 *   HOCOR:  Not separate - frequency set via HOCOWTCR (0x4001E0A5) and MOMCR
 *   SCKDIVCR: 0x4001E020 - System clock division
 *   SCKSCR:   0x4001E026 - System clock source select (01=HOCO)
 *
 * RA4M1 HOCO supports 16/18/20/24/32/36/40/48 MHz.
 * At POR, HOCO starts at 24MHz (reset state of HOCOWTCR bits).
 * To get 48MHz: write HOCOWTCR.HSTS = 6 before enabling HOCO.
 */

#include <stdint.h>

/* CGC registers */
#define R_CGC_BASE      0x4001E000UL
#define R_SCKDIVCR      (*(volatile uint32_t *)(R_CGC_BASE + 0x020UL))
#define R_SCKSCR        (*(volatile uint8_t  *)(R_CGC_BASE + 0x026UL))
#define R_HOCOCR        (*(volatile uint8_t  *)(R_CGC_BASE + 0x036UL))
#define R_HOCOCR2       (*(volatile uint8_t  *)(R_CGC_BASE + 0x037UL))
#define R_HOCOWTCR      (*(volatile uint8_t  *)(R_CGC_BASE + 0x0A5UL))
#define R_OSCSF         (*(volatile uint8_t  *)(R_CGC_BASE + 0x03CUL))
#define R_MEMWAIT       (*(volatile uint8_t  *)(0x407FB19CUL))

/* PRCR - Protect register (unlock/lock clock/LVD/reset settings) */
#define R_SYSTEM_PRCR   (*(volatile uint16_t *)(0x4001E3FEUL))
#define PRCR_KEY        0xA500U
#define PRCR_PRC0       0x0001U  /* Reset/clock register write enable */

/* FPU - enable hardware FPU for Cortex-M4 */
#define CPACR           (*(volatile uint32_t *)(0xE000ED88UL))

void SystemInit(void)
{
    /* Enable FPU (Cortex-M4 coprocessors CP10 and CP11) */
    CPACR |= (3UL << 20) | (3UL << 22);
    __asm volatile("dsb");
    __asm volatile("isb");

    /* Unlock clock registers */
    R_SYSTEM_PRCR = PRCR_KEY | PRCR_PRC0;

    /* Add flash wait state for 48MHz (required for >24MHz operation on RA4M1) */
    R_MEMWAIT = 0x01U;

    /* Set HOCO to 48MHz (HSTS[2:0] = 110b = 6 → 48MHz) */
    R_HOCOCR  = 0x01U;          /* Stop HOCO first */
    R_HOCOWTCR = 0x06U;         /* Set 48MHz */
    R_HOCOCR  = 0x00U;          /* Start HOCO */

    /* Wait for HOCO stable */
    while (!(R_OSCSF & 0x01U))
        ;

    /* All clock dividers = /1 (ICLK/PCLKA/B/D at 48MHz) */
    R_SCKDIVCR = 0x00000000UL;

    /* Switch system clock source to HOCO (0x01) */
    R_SCKSCR = 0x01U;

    /* Wait for clock source switch complete */
    while ((R_SCKSCR & 0x07U) != 0x01U)
        ;

    /* Lock clock registers */
    R_SYSTEM_PRCR = PRCR_KEY | 0x0000U;
}
