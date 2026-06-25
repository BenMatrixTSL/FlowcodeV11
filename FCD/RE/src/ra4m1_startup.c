// CRC: D3A5712EBD65B64EC20166ACC65F83975CFD4AC31A3F4BBA4926F653120FC5D7C6D9D9900CF77F8A82BAEF96855F6585DD04A5F8AD9BEEB1823278EF8F2BA19CA54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E158B564CC0C62AE4EE2DA78BAC7DB617A5AB0E4B834C308CF6DEF7B5AB3E0F919FFCAA9ACB14F6C40A65F7643ECFA4EA82EABDCA0B92D9B66C8E88DE8813F4F18DACAFAB88B6F1AF5843DF262F1C9598072CC9F797FDFDC3B5549D34A0D5AD11F3B9F669F596DF67630A7918B98EA053854FE1E16AE1DF6B3407369D99911C23D5D43797C197BFDEC5
// REVISION: 1.0
// GUID: F8A9B0C1-D2E3-4567-1234-678901234567
// DATE: 25\06\2026
// DIR: FCD\RE\src\ra4m1_startup.c
/*
 * RA4M1 Bare-Metal Startup (C implementation)
 * Sets up .data, zeroes .bss, then calls main().
 * No dependency on Renesas FSP or CMSIS device packs.
 */

#include <stdint.h>
#include <string.h>

/* Symbols from linker script */
extern uint32_t _sidata;   /* Start of .data in flash */
extern uint32_t _sdata;    /* Start of .data in RAM */
extern uint32_t _edata;    /* End of .data in RAM */
extern uint32_t _sbss;     /* Start of .bss */
extern uint32_t _ebss;     /* End of .bss */
extern uint32_t _estack;   /* Top of stack */

/* Forward declarations */
int main(void);
void SystemInit(void);

/* Default weak handlers - user/CAL code can override */
void Default_Handler(void) { while (1) {} }

__attribute__((weak, alias("Default_Handler"))) void NMI_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void HardFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void MemManage_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void BusFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void UsageFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void SVC_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void DebugMon_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void PendSV_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void SysTick_Handler(void);

/* RA4M1 peripheral IRQs (up to 32 external, user-configurable via ELC/ICU) */
__attribute__((weak, alias("Default_Handler"))) void IRQ0_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ1_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ2_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ3_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ4_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ5_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ6_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ7_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ8_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ9_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ10_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ11_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ12_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ13_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ14_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ15_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ16_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ17_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ18_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ19_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ20_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ21_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ22_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ23_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ24_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ25_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ26_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ27_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ28_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ29_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ30_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void IRQ31_Handler(void);

/* Reset handler - entry point */
void Reset_Handler(void)
{
    /* Copy .data section from flash to RAM */
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while (dst < &_edata)
        *dst++ = *src++;

    /* Zero .bss section */
    dst = &_sbss;
    while (dst < &_ebss)
        *dst++ = 0U;

    /* System/clock init */
    SystemInit();

    /* Call application entry point */
    main();

    /* Should never return */
    while (1) {}
}

/* Vector table - placed at .isr_vector section by linker script */
__attribute__((section(".isr_vector")))
void (* const g_vector_table[])(void) =
{
    /* ARM Cortex-M4 core exceptions */
    (void (*)(void))&_estack,   /* 0: Initial SP */
    Reset_Handler,              /* 1: Reset */
    NMI_Handler,                /* 2: NMI */
    HardFault_Handler,          /* 3: Hard Fault */
    MemManage_Handler,          /* 4: MPU Fault */
    BusFault_Handler,           /* 5: Bus Fault */
    UsageFault_Handler,         /* 6: Usage Fault */
    0,                          /* 7: Reserved */
    0,                          /* 8: Reserved */
    0,                          /* 9: Reserved */
    0,                          /* 10: Reserved */
    SVC_Handler,                /* 11: SVCall */
    DebugMon_Handler,           /* 12: Debug Monitor */
    0,                          /* 13: Reserved */
    PendSV_Handler,             /* 14: PendSV */
    SysTick_Handler,            /* 15: SysTick */

    /* RA4M1 external interrupts (configurable via ICU/ELC) */
    IRQ0_Handler,   IRQ1_Handler,   IRQ2_Handler,   IRQ3_Handler,
    IRQ4_Handler,   IRQ5_Handler,   IRQ6_Handler,   IRQ7_Handler,
    IRQ8_Handler,   IRQ9_Handler,   IRQ10_Handler,  IRQ11_Handler,
    IRQ12_Handler,  IRQ13_Handler,  IRQ14_Handler,  IRQ15_Handler,
    IRQ16_Handler,  IRQ17_Handler,  IRQ18_Handler,  IRQ19_Handler,
    IRQ20_Handler,  IRQ21_Handler,  IRQ22_Handler,  IRQ23_Handler,
    IRQ24_Handler,  IRQ25_Handler,  IRQ26_Handler,  IRQ27_Handler,
    IRQ28_Handler,  IRQ29_Handler,  IRQ30_Handler,  IRQ31_Handler,
};
