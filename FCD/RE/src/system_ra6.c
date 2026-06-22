// CRC: 0000000000000000000000000000000000000000000000000000000000000000
// REVISION: 1.0
// GUID: B1C2D3E4-F5A6-7890-1234-567890ABCDEF
// DATE: 22\06\2026
// DIR: FCD\RE\src\system_ra6.c
/*
 * RA6M1/M2/M3 System Initialization - 120MHz via HOCO + PLL
 *
 * RA6 series starts from reset at MOCO ~8MHz.
 * Clock sequence to reach 120MHz:
 *   1. Enable HOCO at 20MHz
 *   2. Configure PLL: source=HOCO, PLLDIV=÷1, PLLMUL=×6 → 120MHz
 *   3. Set flash wait states (3 required at 120MHz)
 *   4. Configure SCKDIVCR (all domains ÷1)
 *   5. Switch system clock to PLL
 *
 * Register addresses are common across RA6M1/M2/M3 (same CGC block).
 *
 * If RA4M1_SYSCLK is defined to something other than 120000000 (via FCDX clock
 * parameter), the PLL multiply factor may need adjustment.
 */

#include <stdint.h>

/* CGC registers */
#define R_CGC_BASE      0x4001E000UL
#define R_SCKDIVCR      (*(volatile uint32_t *)(R_CGC_BASE + 0x020UL))
#define R_SCKSCR        (*(volatile uint8_t  *)(R_CGC_BASE + 0x026UL))
#define R_PLLCCR        (*(volatile uint16_t *)(R_CGC_BASE + 0x028UL))
#define R_PLLCR         (*(volatile uint8_t  *)(R_CGC_BASE + 0x02AUL))
#define R_HOCOCR        (*(volatile uint8_t  *)(R_CGC_BASE + 0x036UL))
#define R_HOCOWTCR      (*(volatile uint8_t  *)(R_CGC_BASE + 0x0A5UL))
#define R_OSCSF         (*(volatile uint8_t  *)(R_CGC_BASE + 0x03CUL))
#define R_MEMWAIT       (*(volatile uint8_t  *)(0x407FB19CUL))

/* RA6M1/M2/M3 flash cache/prefetch at 0x407FBUL */
#define R_FCACHEE       (*(volatile uint16_t *)(0x4001C100UL))
#define R_FCACHEIV      (*(volatile uint16_t *)(0x4001C104UL))

/* PRCR - protect register */
#define R_SYSTEM_PRCR   (*(volatile uint16_t *)(0x4001E3FEUL))
#define PRCR_KEY        0xA500U
#define PRCR_PRC0       0x0001U

/* FPU enable */
#define CPACR           (*(volatile uint32_t *)(0xE000ED88UL))

/*
 * PLLCCR for RA6M1/M2/M3:
 *   Bits [13:8] = PLLMUL[5:0]:  multiplication (value+1)/2, for ×6: PLLMUL=0x0B (11)
 *   Bits [1:0]  = PLLDIV[1:0]:  ÷1=00, ÷2=01, ÷4=10
 *   Bit 4       = PLSRCSEL:     0=MOSC, 1=HOCO
 * HOCO=20MHz, PLSDIV=00(÷1), PLLMUL=0x0B(×6) → 20×6=120MHz
 */
#define RA6_PLLCCR_120MHZ   ((uint16_t)((0x0BU << 8) | (1U << 4) | 0x00U))

/* SCKSCR source selectors */
#define SCKSCR_HOCO     0x01U
#define SCKSCR_PLL      0x05U

void SystemInit(void)
{
    /* Enable hardware FPU (Cortex-M4 CP10/CP11) */
    CPACR |= (3UL << 20) | (3UL << 22);
    __asm volatile("dsb");
    __asm volatile("isb");

    /* Unlock clock/protect registers */
    R_SYSTEM_PRCR = PRCR_KEY | PRCR_PRC0;

    /* Set flash wait states for 120MHz (3 cycles required > 100MHz on RA6) */
    R_MEMWAIT = 0x03U;

    /* Enable HOCO at 20MHz (HSTS=2) */
    R_HOCOCR   = 0x01U;    /* Stop HOCO first */
    R_HOCOWTCR = 0x02U;    /* 20MHz */
    R_HOCOCR   = 0x00U;    /* Start HOCO */

    /* Wait for HOCO stable */
    while (!(R_OSCSF & 0x01U))
        ;

    /* Switch to HOCO as intermediate clock before enabling PLL */
    R_SCKDIVCR = 0x00000000UL;
    R_SCKSCR = SCKSCR_HOCO;
    while ((R_SCKSCR & 0x07U) != SCKSCR_HOCO)
        ;

    /* Configure PLL: HOCO=20MHz ×6 = 120MHz */
    R_PLLCR   = 0x01U;                /* Stop PLL */
    R_PLLCCR  = RA6_PLLCCR_120MHZ;
    R_PLLCR   = 0x00U;                /* Start PLL */

    /* Wait for PLL lock (check PLLSF bit in OSCSF) */
    while (!(R_OSCSF & 0x04U))
        ;

    /* Switch system clock to PLL */
    R_SCKSCR = SCKSCR_PLL;
    while ((R_SCKSCR & 0x07U) != SCKSCR_PLL)
        ;

    /* Lock clock registers */
    R_SYSTEM_PRCR = PRCR_KEY | 0x0000U;
}
