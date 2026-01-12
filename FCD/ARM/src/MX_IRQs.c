// CRC: 1CECFE3DB3A1BD5169AEA98AD43ADE6372B0769B507F81115D8154FA38791F8D840D1BC31E56037F838FBC742DDCD3C49A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5189AF36EBEDCC92958C7E17CC94FDF18494E74938D4D50057DCAAABCADB100799DB6BF6C84972FB541FF6CB691500DB24EF767DC2777A58EC338247D801B81F3231409C1C2DA23814D36BB4B3CFC00FC756684AB1CA1D8F2549D34A0D5AD11F3B13AAAC3AEEAAE053431A3E8C96C7E821011C9B5051802E407369D99911C23D5D43797C197BFDEC5
// REVISION: 1.0
// GUID: B4FC325C-94C3-4D6B-99FA-D28E958E6E35
// DATE: 08\08\2022
// DIR: FCD\ARM\src\MX_IRQs.c

#ifdef STM32F0
	#include "stm32f0xx_hal.h"
#elif defined STM32F1
	#include "stm32f1xx_hal.h"
#elif defined STM32F2
	#include "stm32f2xx_hal.h"
#elif defined STM32F3
	#include "stm32f3xx_hal.h"
#elif defined STM32F4
	#include "stm32f4xx_hal.h"
#elif defined STM32F7
	#include "stm32f7xx_hal.h"
#endif

__weak void MX_ISR_TIM1(){}
__weak void MX_ISR_TIM2(){}
__weak void MX_ISR_TIM3(){}
__weak void MX_ISR_TIM4(){}
__weak void MX_ISR_TIM5(){}
__weak void MX_ISR_TIM6(){}
__weak void MX_ISR_TIM7(){}
__weak void MX_ISR_TIM8(){}
__weak void MX_ISR_TIM9(){}
__weak void MX_ISR_TIM10(){}
__weak void MX_ISR_TIM11(){}
__weak void MX_ISR_TIM12(){}
__weak void MX_ISR_TIM13(){}
__weak void MX_ISR_TIM14(){}
__weak void MX_ISR_TIM15(){}
__weak void MX_ISR_TIM16(){}
__weak void MX_ISR_TIM17(){}

__weak void MX_ISR_EXTI0(){}
__weak void MX_ISR_EXTI1(){}
__weak void MX_ISR_EXTI2(){}
__weak void MX_ISR_EXTI3(){}
__weak void MX_ISR_EXTI4(){}
__weak void MX_ISR_EXTI5(){}
__weak void MX_ISR_EXTI6(){}
__weak void MX_ISR_EXTI7(){}
__weak void MX_ISR_EXTI8(){}
__weak void MX_ISR_EXTI9(){}
__weak void MX_ISR_EXTI10(){}
__weak void MX_ISR_EXTI11(){}
__weak void MX_ISR_EXTI12(){}
__weak void MX_ISR_EXTI13(){}
__weak void MX_ISR_EXTI14(){}
__weak void MX_ISR_EXTI15(){}

__weak void MX_ISR_UART1(){}
__weak void MX_ISR_UART2(){}
__weak void MX_ISR_UART3(){}
__weak void MX_ISR_UART4(){}
__weak void MX_ISR_UART5(){}
__weak void MX_ISR_UART6(){}
__weak void MX_ISR_UART7(){}
__weak void MX_ISR_UART8(){}

void MX_EXTI_PinInit(GPIO_TypeDef *EXTI_Port, uint32_t EXTI_Pin, uint32_t EXTI_Mode, uint32_t WeakBias)
{
	GPIO_InitTypeDef hPin;
	
	hPin.Pin = EXTI_Pin;
	hPin.Mode = EXTI_Mode;
	hPin.Pull = WeakBias;
	hPin.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(EXTI_Port, &hPin);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
		case GPIO_PIN_0:
			MX_ISR_EXTI0();
			break;

		case GPIO_PIN_1:
			MX_ISR_EXTI1();
			break;

		case GPIO_PIN_2:
			MX_ISR_EXTI2();
			break;

		case GPIO_PIN_3:
			MX_ISR_EXTI3();
			break;

		case GPIO_PIN_4:
			MX_ISR_EXTI4();
			break;

		case GPIO_PIN_5:
			MX_ISR_EXTI5();
			break;

		case GPIO_PIN_6:
			MX_ISR_EXTI6();
			break;

		case GPIO_PIN_7:
			MX_ISR_EXTI7();
			break;

		case GPIO_PIN_8:
			MX_ISR_EXTI8();
			break;

		case GPIO_PIN_9:
			MX_ISR_EXTI9();
			break;

		case GPIO_PIN_10:
			MX_ISR_EXTI10();
			break;

		case GPIO_PIN_11:
			MX_ISR_EXTI11();
			break;

		case GPIO_PIN_12:
			MX_ISR_EXTI12();
			break;

		case GPIO_PIN_13:
			MX_ISR_EXTI13();
			break;

		case GPIO_PIN_14:
			MX_ISR_EXTI14();
			break;

		case GPIO_PIN_15:
			MX_ISR_EXTI15();
			break;
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *hTim)
{
	uint32_t TIMinst = (uint32_t)hTim->Instance;
	
	switch(TIMinst)
	{
	  #if defined TIM1
		case (uint32_t)TIM1:
			MX_ISR_TIM1();
			break;
	  #endif
	  #if defined TIM2
		case (uint32_t)TIM2:
			MX_ISR_TIM2();
			break;
	  #endif
	  #if defined TIM3
		case (uint32_t)TIM3:
			MX_ISR_TIM3();
			break;
	  #endif
	  #if defined TIM4
		case (uint32_t)TIM4:
			MX_ISR_TIM4();
			break;
	  #endif
	  #if defined TIM5
		case (uint32_t)TIM5:
			MX_ISR_TIM5();
			break;
	  #endif
	  #if defined TIM6
		case (uint32_t)TIM6:
			MX_ISR_TIM6();
			break;
	  #endif
	  #if defined TIM7
		case (uint32_t)TIM7:
			MX_ISR_TIM7();
			break;
	  #endif
	  #if defined TIM8
		case (uint32_t)TIM8:
			MX_ISR_TIM8();
			break;
	  #endif
	  #if defined TIM9
		case (uint32_t)TIM9:
			MX_ISR_TIM9();
			break;
	  #endif
	  #if defined TIM10
		case (uint32_t)TIM10:
			MX_ISR_TIM10();
			break;
	  #endif
	  #if defined TIM11
		case (uint32_t)TIM11:
			MX_ISR_TIM11();
			break;
	  #endif
	  #if defined TIM12
		case (uint32_t)TIM12:
			MX_ISR_TIM12();
			break;
	  #endif
	  #if defined TIM13
		case (uint32_t)TIM13:
			MX_ISR_TIM13();
			break;
	  #endif
	  #if defined TIM14
		case (uint32_t)TIM14:
			MX_ISR_TIM14();
			break;
	  #endif
	  #if defined TIM15
		case (uint32_t)TIM15:
			MX_ISR_TIM15();
			break;
	  #endif
	  #if defined TIM16
		case (uint32_t)TIM16:
			MX_ISR_TIM16();
			break;
	  #endif
	  #if defined TIM17
		case (uint32_t)TIM17:
			MX_ISR_TIM17();
			break;
	  #endif
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *hUart)
{
	uint32_t UARTinst = (uint32_t)hUart->Instance;
	
	switch(UARTinst)
	{
	  #if defined USART1
		case (uint32_t)USART1:
			MX_ISR_UART1();
			break;
	  #endif
	  #if defined USART2
		case (uint32_t)USART2:
			MX_ISR_UART2();
			break;
	  #endif
	  #if defined USART3
		case (uint32_t)USART3:
			MX_ISR_UART3();
			break;
	  #endif
	  #if defined UART4
		case (uint32_t)UART4:
			MX_ISR_UART4();
			break;
	  #endif
	  #if defined UART5
		case (uint32_t)UART5:
			MX_ISR_UART5();
			break;
	  #endif
	  #if defined USART6
		case (uint32_t)USART6:
			MX_ISR_UART6();
			break;
	  #endif
	  #if defined UART7
		case (uint32_t)UART7:
			MX_ISR_UART7();
			break;
	  #endif
	  #if defined UART8
		case (uint32_t)UART8:
			MX_ISR_UART8();
			break;
	  #endif
	}
}