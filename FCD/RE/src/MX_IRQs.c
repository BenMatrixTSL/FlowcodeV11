// CRC: 0000000000000000000000000000000000000000000000000000000000000000
// REVISION: 1.0
// GUID: C1D2E3F4-A5B6-7890-4567-901234567890
// DATE: 22\06\2026
// DIR: FCD\RE\src\MX_IRQs.c
/*
 * Flowcode ISR stubs for Renesas RA targets.
 * Weak empty stubs for all Flowcode timer/external interrupt hooks.
 * User Flowcode programs override these when interrupt components are placed.
 */

__attribute__((weak)) void MX_ISR_TIM0(void)  {}
__attribute__((weak)) void MX_ISR_TIM1(void)  {}
__attribute__((weak)) void MX_ISR_TIM2(void)  {}
__attribute__((weak)) void MX_ISR_TIM3(void)  {}
__attribute__((weak)) void MX_ISR_TIM4(void)  {}
__attribute__((weak)) void MX_ISR_TIM5(void)  {}
__attribute__((weak)) void MX_ISR_TIM6(void)  {}
__attribute__((weak)) void MX_ISR_TIM7(void)  {}
__attribute__((weak)) void MX_ISR_TIM8(void)  {}
__attribute__((weak)) void MX_ISR_TIM9(void)  {}

__attribute__((weak)) void MX_ISR_EXTI0(void)  {}
__attribute__((weak)) void MX_ISR_EXTI1(void)  {}
__attribute__((weak)) void MX_ISR_EXTI2(void)  {}
__attribute__((weak)) void MX_ISR_EXTI3(void)  {}
__attribute__((weak)) void MX_ISR_EXTI4(void)  {}
__attribute__((weak)) void MX_ISR_EXTI5(void)  {}
__attribute__((weak)) void MX_ISR_EXTI6(void)  {}
__attribute__((weak)) void MX_ISR_EXTI7(void)  {}
__attribute__((weak)) void MX_ISR_EXTI8(void)  {}
__attribute__((weak)) void MX_ISR_EXTI9(void)  {}
__attribute__((weak)) void MX_ISR_EXTI10(void) {}
__attribute__((weak)) void MX_ISR_EXTI11(void) {}
__attribute__((weak)) void MX_ISR_EXTI12(void) {}
__attribute__((weak)) void MX_ISR_EXTI13(void) {}
__attribute__((weak)) void MX_ISR_EXTI14(void) {}
__attribute__((weak)) void MX_ISR_EXTI15(void) {}

__attribute__((weak)) void MX_ISR_UART0(void)  {}
__attribute__((weak)) void MX_ISR_UART1(void)  {}
__attribute__((weak)) void MX_ISR_UART2(void)  {}
__attribute__((weak)) void MX_ISR_UART3(void)  {}

__attribute__((weak)) void MX_ISR_SPI0(void)   {}
__attribute__((weak)) void MX_ISR_I2C0(void)   {}
__attribute__((weak)) void MX_ISR_ADC0(void)   {}
