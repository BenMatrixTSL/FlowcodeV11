// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BE62ADBBDE7E63F33BF456827015207CF9DD04A5F8AD9BEEB1823278EF8F2BA19C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF58F073D5C6E6F879F39B0ADF0336149CA94A18C39E6B0821908A6FD922375BD48DA0EF1E96EB4195D29228F3339D39D40426ACF7A2F4B95F063EC50020B8673EADF96BFFA0126224364392142585F762E21A029338261D5A7549D34A0D5AD11F3776E2B8F858F1804DCF613DE34F45685485E52D35BD7381076D3E34736BD7539F516F4BDFF4A1CBE
// REVISION: 1.0
// GUID: 14D1491F-14DA-449F-85D6-EF251259073F
// DATE: 08\08\2022
// DIR: CAL\STARM\STARM_CAL_UART.c
/*********************************************************************
 *                  Flowcode CAL UART File
 *
 * File: STARM_CAL_UART.c
 *
 * (c) 2016 Matrix Multimedia Ltd.
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
 * 230316 | BR | Created
 */


//TODO
//Test Receive Functionality
//Test Hardware 9 bit data mode
//Test Software Baud Rate Calc and Fiddle Factor
//Add UART name, AF Name and Interrupt Name to FCD and generate defines from CAL Component.


#ifndef MX_UART_SW_DEFS
	#define MX_UART_SW_DEFS

	//Software Baud Needs Investigation to find best fiddle factor
	#define INST_COUNT	45	//65 for lower speeds or 40 for higher speeds.

	//Work out number of nops for software baud rate
	#define MX_INSTRUCTION_SPEED 	(MX_CLK_SPEED / 4)
	#define MX_OVERHEAD				(MX_INSTRUCTION_SPEED / INST_COUNT)

	// The above uses the wrong clock speed
	// Quick fix try 1uS
	// #define SW_OFFSET				(1000000 / MX_OVERHEAD)
	#define SW_OFFSET				(1)
#endif


#define MX_RECEIVE_DELAY 	(MX_CLK_SPEED / 400000)


//Dynamic function naming based on defines and index number
#define MX_UART_CHANNEL_X	CAL_APPEND(MX_UART_CHANNEL_, MX_UART_NUM)
#define MX_UART_TX_EN_X		CAL_APPEND(MX_UART_UseTX_, MX_UART_NUM)
#define MX_UART_TX_PIN_X	CAL_APPEND(MX_UART_TX_PIN_, MX_UART_NUM)
#define MX_UART_TX_PORT_X	CAL_APPEND(MX_UART_TX_PORT_, MX_UART_NUM)
#define MX_UART_TX_TRIS_X	CAL_APPEND(MX_UART_TX_TRIS_, MX_UART_NUM)
#define MX_UART_RX_EN_X		CAL_APPEND(MX_UART_UseRX_, MX_UART_NUM)
#define MX_UART_RX_PIN_X	CAL_APPEND(MX_UART_RX_PIN_, MX_UART_NUM)
#define MX_UART_RX_PORT_X	CAL_APPEND(MX_UART_RX_PORT_, MX_UART_NUM)
#define MX_UART_RX_TRIS_X	CAL_APPEND(MX_UART_RX_TRIS_, MX_UART_NUM)
#define MX_UART_FLOWEN_X	CAL_APPEND(MX_UART_FLOWEN_, MX_UART_NUM)
#define MX_UART_CTS_PIN_X	CAL_APPEND(MX_UART_CTS_PIN_, MX_UART_NUM)
#define MX_UART_CTS_PORT_X	CAL_APPEND(MX_UART_CTS_PORT_, MX_UART_NUM)
#define MX_UART_CTS_TRIS_X	CAL_APPEND(MX_UART_CTS_TRIS_, MX_UART_NUM)
#define MX_UART_RTS_PIN_X	CAL_APPEND(MX_UART_RTS_PIN_, MX_UART_NUM)
#define MX_UART_RTS_PORT_X	CAL_APPEND(MX_UART_RTS_PORT_, MX_UART_NUM)
#define MX_UART_RTS_TRIS_X	CAL_APPEND(MX_UART_RTS_TRIS_, MX_UART_NUM)
#define MX_UART_DBITS_X		CAL_APPEND(MX_UART_DBITS_, MX_UART_NUM)
#define MX_UART_RETURN_X	CAL_APPEND(MX_UART_RETURN_, MX_UART_NUM)
#define MX_UART_ECHO_X		CAL_APPEND(MX_UART_ECHO_, MX_UART_NUM)
#define MX_UART_INT_X		CAL_APPEND(MX_UART_INT_, MX_UART_NUM)
#define MX_UART_BAUD_X		CAL_APPEND(MX_UART_BAUD_, MX_UART_NUM)
#define MX_SOFT_BAUD_X		CAL_APPEND(MX_SOFT_BAUD_, MX_UART_NUM)
#define MX_HARD_SLOW_X		CAL_APPEND(MX_HARD_SLOW_, MX_UART_NUM)

#define MX_UART_CLOCK_X     CAL_APPEND(MX_UART_CLOCK_, MX_UART_NUM)         //UART Clock Config - eg __HAL_RCC_USART1_CLK_ENABLE

#define MX_UART_USART_X		CAL_APPEND(MX_UART_NAME_, MX_UART_NUM)			//UART Name - eg USART1
#define MX_UART_TX_AF_X		CAL_APPEND(MX_UART_TX_AF_, MX_UART_NUM)			//UART Alt Function Name - eg GPIO_AF7_USART1
#define MX_UART_RX_AF_X		CAL_APPEND(MX_UART_RX_AF_, MX_UART_NUM)			//UART Alt Function Name - eg GPIO_AF7_USART1

#define MX_UART_NAME_X		CAL_APPEND(MX_UART_NAME_, MX_UART_NUM)			//UART Name

#define MX_UART_HANDLE_X	CAL_APPEND(MX_UART_NUMBER_, MX_UART_NUM)
#define MX_UART_RX_VAL		CAL_APPEND(MX_UART_HANDLE_X, _RX_VAL)
#define MX_UART_IRQ_EN		CAL_APPEND(MX_UART_HANDLE_X, _IRQ_EN)
#define MX_UART_IRQ_X		CAL_APPEND(MX_UART_IRQ_, MX_UART_NUM)

#if (MX_UART_CHANNEL_X == 0)
	#define MX_SOFT_BAUD_X (1000000 / MX_UART_BAUD_X) - SW_OFFSET

	#if (MX_SOFT_BAUD_X < 1)
		#error "Software UART Baud Rate Not Available At This Clock Speed"
	#endif
#endif


#define UART_Delay_CAL		CAL_APPEND(FC_CAL_UART_Delay_, MX_UART_NUM)
#define UART_Send			CAL_APPEND(FC_CAL_UART_Send_, MX_UART_NUM)
#define UART_Uninit			CAL_APPEND(FC_CAL_UART_Uninit_, MX_UART_NUM)


//Component Definitions
#define UART_STATUS_LOOP	0
#define UART_STATUS_TIMEOUT	1
#define UART_STATUS_RXBYTE	2


//Interrupt Definitions
#if (MX_UART_INT_X == 1)

	#ifndef MX_UART_INT_DEFS
	#define MX_UART_INT_DEFS

		#define MX_UART_INT_CH1_FUNC \
				void USART1_IRQHandler(void) {HAL_UART_IRQHandler(&(MX_HANDLE_UART1)); HAL_UART_Receive_IT(&(MX_HANDLE_UART1), (uint8_t *)&(MX_HANDLE_UART1_RX_VAL), 1);} \
				void MX_ISR_UART1() {

		#define MX_UART_INT_CH2_FUNC \
				void USART2_IRQHandler(void) {HAL_UART_IRQHandler(&(MX_HANDLE_UART2)); HAL_UART_Receive_IT(&(MX_HANDLE_UART2), (uint8_t *)&(MX_HANDLE_UART2_RX_VAL), 1);} \
				void MX_ISR_UART2() {

		#define MX_UART_INT_CH3_FUNC \
				void USART3_IRQHandler(void) {HAL_UART_IRQHandler(&(MX_HANDLE_UART3)); HAL_UART_Receive_IT(&(MX_HANDLE_UART3), (uint8_t *)&(MX_HANDLE_UART3_RX_VAL), 1);} \
				void MX_ISR_UART3() {

		#define MX_UART_INT_CH4_FUNC \
				void USART4_IRQHandler(void) {HAL_UART_IRQHandler(&(MX_HANDLE_UART4)); HAL_UART_Receive_IT(&(MX_HANDLE_UART4), (uint8_t *)&(MX_HANDLE_UART4_RX_VAL), 1);} \
				void MX_ISR_UART4() {

		#define MX_UART_INT_CH5_FUNC \
				void USART5_IRQHandler(void) {HAL_UART_IRQHandler(&(MX_HANDLE_UART5)); HAL_UART_Receive_IT(&(MX_HANDLE_UART5), (uint8_t *)&(MX_HANDLE_UART5_RX_VAL), 1);} \
				void MX_ISR_UART5() {

		#define MX_UART_INT_CH6_FUNC \
				void USART6_IRQHandler(void) {HAL_UART_IRQHandler(&(MX_HANDLE_UART6)); HAL_UART_Receive_IT(&(MX_HANDLE_UART6), (uint8_t *)&(MX_HANDLE_UART6_RX_VAL), 1);} \
				void MX_ISR_UART6() {

		#define MX_UART_INT_FUNC_END	}

		#define MX_UART_INT_CH1_DET		1
		#define MX_UART_INT_CH2_DET		1
		#define MX_UART_INT_CH3_DET		1
		#define MX_UART_INT_CH4_DET		1
		#define MX_UART_INT_CH5_DET		1
		#define MX_UART_INT_CH6_DET		1

		#define MX_UART_INT_CH1_EN
		#define MX_UART_INT_CH2_EN
		#define MX_UART_INT_CH3_EN
		#define MX_UART_INT_CH4_EN
		#define MX_UART_INT_CH5_EN
		#define MX_UART_INT_CH6_EN

		#define MX_UART_INT_CH1_DIS
		#define MX_UART_INT_CH2_DIS
		#define MX_UART_INT_CH3_DIS
		#define MX_UART_INT_CH4_DIS
		#define MX_UART_INT_CH5_DIS
		#define MX_UART_INT_CH6_DIS

		#define MX_UART_INT_CH1_CLR
		#define MX_UART_INT_CH2_CLR
		#define MX_UART_INT_CH3_CLR
		#define MX_UART_INT_CH4_CLR
		#define MX_UART_INT_CH5_CLR
		#define MX_UART_INT_CH6_CLR

	#endif
#endif


//Function Prototypes
CALFUNCTION(void, FC_CAL_UART_Init_, (void));
CALFUNCTION(void, FC_CAL_UART_Uninit_, (void));
CALFUNCTION(void, FC_CAL_UART_Send_, (MX_UINT16 nChar));
CALFUNCTION(MX_SINT16, FC_CAL_UART_Receive_, (MX_UINT8 nTimeout));
CALFUNCTION(void, FC_CAL_UART_Delay_, (void));
CALFUNCTION(void, FC_CAL_UART_UpdateBaud_, (MX_UINT8 new_baud));


//Create UART Structure
UART_HandleTypeDef MX_UART_HANDLE_X;
MX_UINT16	MX_UART_RX_VAL, MX_UART_IRQ_EN;

//Peripheral Functions
CALFUNCTION(void, FC_CAL_UART_Init_, (void))
{

	#if (MX_UART_CHANNEL_X == 0)
		#if (MX_UART_RX_EN_X == 1)
			FC_CAL_Bit_In_DDR 	(MX_UART_RX_PORT_X, MX_UART_RX_TRIS_X, MX_UART_RX_PIN_X);		// Receive pin is a input
		#endif
		#if (MX_UART_TX_EN_X == 1)
			FC_CAL_Bit_High_DDR (MX_UART_TX_PORT_X, MX_UART_TX_TRIS_X, MX_UART_TX_PIN_X);		// Transmit pin is default high
		#endif
	#endif

	#if (MX_UART_CHANNEL_X > 0)


		/* Enable USARTx clock */
		MX_UART_CLOCK_X();


		MX_UART_HANDLE_X.Instance          = MX_UART_USART_X;

		MX_UART_HANDLE_X.Init.BaudRate     = MX_UART_BAUD_X;

		#if(MX_UART_DBITS_X == 9)
			MX_UART_HANDLE_X.Init.WordLength   = UART_WORDLENGTH_9B;
		#else
			MX_UART_HANDLE_X.Init.WordLength   = UART_WORDLENGTH_8B;
		#endif

		MX_UART_HANDLE_X.Init.StopBits     = UART_STOPBITS_1;
		MX_UART_HANDLE_X.Init.Parity       = UART_PARITY_NONE;
		MX_UART_HANDLE_X.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
		MX_UART_HANDLE_X.Init.Mode         = UART_MODE_TX_RX;
		MX_UART_HANDLE_X.Init.OverSampling = UART_OVERSAMPLING_16;

		HAL_UART_DeInit(&MX_UART_HANDLE_X);
		HAL_UART_Init(&MX_UART_HANDLE_X);


		GPIO_InitTypeDef  GPIO_InitStruct;

		/*##-2- Configure peripheral GPIO ##########################################*/
		/* UART TX GPIO pin configuration  */

		//Special case for BL0061 ARM EB2 Board - Remap Flowcode Pins to Actual Port Pins
		#ifdef MX_BL0061_PINMAP
			#undef MX_UART_TX_PIN_X
			#undef MX_UART_RX_PIN_X
			#undef MX_UART_TX_PORT_X
			#undef MX_UART_RX_PORT_X

			#if MX_UART_CHANNEL_X == 1
				#define MX_UART_TX_PIN_X (9)
				#define MX_UART_RX_PIN_X (10)
				#define MX_UART_TX_PORT_X GPIOA
				#define MX_UART_RX_PORT_X GPIOA
			#endif
			#if MX_UART_CHANNEL_X == 2
				#define MX_UART_TX_PIN_X (2)
				#define MX_UART_RX_PIN_X (3)
				#define MX_UART_TX_PORT_X GPIOA
				#define MX_UART_RX_PORT_X GPIOA
			#endif
			#if MX_UART_CHANNEL_X == 6
				#define MX_UART_TX_PIN_X (6)
				#define MX_UART_RX_PIN_X (7)
				#define MX_UART_TX_PORT_X GPIOC
				#define MX_UART_RX_PORT_X GPIOC
			#endif
		#endif

		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_NOPULL;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;			// GPIO_SPEED_FAST;
		#if (MX_UART_TX_EN_X == 1)
			GPIO_InitStruct.Pin       = 1 << MX_UART_TX_PIN_X;			//GPIO_PIN_2;
			GPIO_InitStruct.Alternate = MX_UART_TX_AF_X;				//GPIO_AF7_USART2;
			HAL_GPIO_Init(MX_UART_TX_PORT_X, &GPIO_InitStruct);
		#endif
		#if (MX_UART_RX_EN_X == 1)
			/* UART RX GPIO pin configuration  */
			GPIO_InitStruct.Pin 	  = 1 << MX_UART_RX_PIN_X;			//GPIO_PIN_3;
			GPIO_InitStruct.Alternate = MX_UART_RX_AF_X;				//GPIO_AF7_USART2;
			HAL_GPIO_Init(MX_UART_RX_PORT_X, &GPIO_InitStruct);
		#endif

		MX_UART_IRQ_EN = 0;

		/* NVIC for U(S)ART */
		#if (MX_UART_INT_X == 1)
			HAL_NVIC_SetPriority(MX_UART_IRQ_X, 0, 1);
			HAL_NVIC_EnableIRQ(MX_UART_IRQ_X);
			MX_UART_IRQ_EN = 1;
			HAL_UART_Receive_IT(&(MX_UART_HANDLE_X), (uint8_t *)&(MX_UART_RX_VAL), 1);
		#endif

	#endif

	#if (MX_UART_FLOWEN_X == 1)						//Flowcontrol enabled?
		FC_CAL_Bit_In_DDR (MX_UART_CTS_PORT_X, MX_UART_CTS_TRIS_X, MX_UART_CTS_PIN_X);	// CTS pin is a input

		#if (MX_UART_INT_X == 1)
			FC_CAL_Bit_Low_DDR (MX_UART_RTS_PORT_X, MX_UART_RTS_TRIS_X, MX_UART_RTS_PIN_X);		// RTS is ready to accept data
		#else
			FC_CAL_Bit_High_DDR (MX_UART_RTS_PORT_X, MX_UART_RTS_TRIS_X, MX_UART_RTS_PIN_X);	// RTS not ready to accept data
		#endif
	#endif

}



CALFUNCTION(void, FC_CAL_UART_Uninit_, (void))
{

	#if (MX_UART_CHANNEL_X == 0)
		#if (MX_UART_RX_EN_X == 1)
			FC_CAL_Bit_In_DDR (MX_UART_RX_PORT_X, MX_UART_RX_TRIS_X, MX_UART_RX_PIN_X);		// Receive pin is a input
		#endif
		#if (MX_UART_TX_EN_X == 1)
			FC_CAL_Bit_In_DDR (MX_UART_TX_PORT_X, MX_UART_TX_TRIS_X, MX_UART_TX_PIN_X);		// Transmit pin is default high
		#endif
	#endif

	#if (MX_UART_CHANNEL_X > 0)

		/*##-1- Reset peripherals ##################################################*/
		__HAL_RCC_USART1_FORCE_RESET();
		__HAL_RCC_USART1_RELEASE_RESET();

		/*##-2- Disable peripherals and GPIO Clocks ################################*/
		/* Configure UART Tx as alternate function */
		#if (MX_UART_TX_EN_X == 1)
			HAL_GPIO_DeInit(MX_UART_TX_PORT_X, 1 << MX_UART_TX_PIN_X);
		#endif
		/* Configure UART Rx as alternate function */
		#if (MX_UART_RX_EN_X == 1)
			HAL_GPIO_DeInit(MX_UART_RX_PORT_X, 1 << MX_UART_RX_PIN_X);
		#endif
		#if (MX_UART_INT_X == 1)
			HAL_NVIC_DisableIRQ(MX_UART_IRQ_X);
			MX_UART_IRQ_EN = 0;
		#endif

	#endif

	#if (MX_UART_FLOWEN_X == 1)										//Flowcontrol enabled?
		FC_CAL_Bit_In_DDR (MX_UART_CTS_PORT_X, MX_UART_CTS_TRIS_X, MX_UART_CTS_PIN_X);		// CTS pin is a input
		FC_CAL_Bit_In_DDR (MX_UART_RTS_PORT_X, MX_UART_RTS_TRIS_X, MX_UART_RTS_PIN_X);		// RTS not ready to accept data
	#endif
}



CALFUNCTION(void, FC_CAL_UART_Send_, (MX_UINT16 nChar))
{
	#if (MX_UART_TX_EN_X == 1)

		#if (MX_UART_FLOWEN_X == 1)
			while (FC_CAL_Bit_In(MX_UART_CTS_PORT_X, MX_UART_CTS_PIN_X) != 0);	// Wait until CTS is low
		#endif

		#if (MX_UART_CHANNEL_X == 0)													// Software UART TX
			MX_UINT8 idx;
			FC_CAL_Bit_Low(MX_UART_TX_PORT_X, MX_UART_TX_PIN_X);					// Send Start bit
			UART_Delay_CAL();
			for (idx = 0; idx < MX_UART_DBITS_X; idx++)
			{
				if (nChar & 0x01)														// Mask off data bit
					FC_CAL_Bit_High(MX_UART_TX_PORT_X, MX_UART_TX_PIN_X);
				else
					FC_CAL_Bit_Low(MX_UART_TX_PORT_X, MX_UART_TX_PIN_X);
				UART_Delay_CAL();
				nChar = nChar >> 1;														// Move to next data bit
			}
			FC_CAL_Bit_High(MX_UART_TX_PORT_X, MX_UART_TX_PIN_X);					// Send Stop bit
			UART_Delay_CAL();
		#endif

		#if (MX_UART_CHANNEL_X > 0)

			//What happens for 9 bit data mode?

			uint8_t dataout = (uint8_t) nChar;

			//TX Byte
			HAL_UART_Transmit(&MX_UART_HANDLE_X, &dataout, 1, 1000);

		#endif

	#endif

}


CALFUNCTION(MX_SINT16, FC_CAL_UART_Receive_, (MX_UINT8 nTimeout))
{
	#if (MX_UART_RETURN_X == 1)
		MX_UINT16 retVal = 512;
	#else
		MX_UINT8 retVal = 255;
	#endif

	#if (MX_UART_RX_EN_X == 1)

		#if (MX_UART_FLOWEN_X == 1)
			#if (MX_UART_INT_X == 0)
				FC_CAL_Bit_Low (MX_UART_RTS_PORT_X, MX_UART_RTS_PIN_X);			// Ready to accept data
			#endif
		#endif

		#if (MX_UART_CHANNEL_X == 0)

			MX_UINT8 delay1 = 0;
			MX_UINT8 regcheck = 0;
			MX_UINT8 bWaitForever = 0;
			MX_UINT8 rxStatus = UART_STATUS_LOOP;
			MX_UINT16 delaycnt;
			MX_UINT8 idx;


			if (nTimeout == 255)
				bWaitForever = 1;

			while (rxStatus == UART_STATUS_LOOP)
			{
				if (bWaitForever == 0)
				{
					if (nTimeout == 0)							//don't wait forever, so do timeout thing...
					{
						rxStatus = UART_STATUS_TIMEOUT;
					}
					else
					{
						for (delaycnt = 0; delaycnt < MX_RECEIVE_DELAY; delaycnt++);	//Delay without calling delay function
						delay1 = delay1 + 1;
						if(delay1 == 100)
						{
							nTimeout = nTimeout - 1;
							MX_CLEAR_WATCHDOG;
							delay1 = 0;
						}
					}
				}

				regcheck = FC_CAL_Bit_In(MX_UART_RX_PORT_X, MX_UART_RX_PIN_X);	//Test for start bit
				if (regcheck == 0)
					rxStatus = UART_STATUS_RXBYTE;

			}

			if (rxStatus == UART_STATUS_RXBYTE)
			{
				retVal = 0;
				UART_Delay_CAL();

				for (idx = 0; idx < MX_UART_DBITS_X; idx++)
				{
					if (FC_CAL_Bit_In(MX_UART_RX_PORT_X, MX_UART_RX_PIN_X))
						retVal = retVal | (0x01 << idx);

					UART_Delay_CAL();
				}

				#if (MX_UART_ECHO_X == 1)
					UART_Send(retVal);
				#endif
			}
		#endif


		#if (MX_UART_CHANNEL_X > 0)

			//What about 9 bit data
			if(MX_UART_IRQ_EN)
			{
				retVal = MX_UART_RX_VAL;
			}
			else
			{
			#if defined (USART_SR_FE)
			/**************** Start of direct access UART code in order to support framing error **********/
			// Default retVal to timeout error
			#if (MX_UART_RETURN_X == 1)
				retVal = 0x200;
			#else
				retVal = 255;
			#endif
			MX_UINT32 start = HAL_GetTick();
			do
			{
				if (MX_UART_NAME_X->SR & USART_SR_FE)
				{
					// Framing error
					// Dummy data read
					retVal =  MX_UART_NAME_X->DR;
					// Now clear some error flags
					MX_UART_NAME_X->SR &= ~(USART_SR_PE | USART_SR_LBD | USART_SR_IDLE | USART_SR_FE | USART_SR_ORE);
				#if (MX_UART_RETURN_X == 1)
					retVal = 0x400;
				#else
					retVal = 255;
				#endif
					break;
				}
				else if (MX_UART_NAME_X->SR & USART_SR_RXNE)
				{
					// Data ready
					retVal =  MX_UART_NAME_X->DR;
					// Now clear some error flags
					MX_UART_NAME_X->SR &= ~(USART_SR_PE | USART_SR_LBD | USART_SR_IDLE | USART_SR_FE | USART_SR_ORE);
					#if (MX_UART_ECHO_X == 1)
						UART_Send(retVal);
					#endif
					break;
				}
			} while (HAL_GetTick() - start < nTimeout);
			/**************** End of direct access UART code in order to support framing error **********/
			#else
			retVal = 0;
			switch (HAL_UART_Receive(&MX_UART_HANDLE_X, &retVal, 1, nTimeout))
			{
				case HAL_OK:
					#if (MX_UART_ECHO_X == 1)
						UART_Send(retVal);
					#endif
					break;
				case HAL_ERROR:
				#if (MX_UART_RETURN_X == 1)
						if (MX_UART_HANDLE_X.ErrorCode == HAL_UART_ERROR_FE)
						retVal = 0x400;					//Framing Error Flag
						else if (MX_UART_HANDLE_X.ErrorCode == HAL_UART_ERROR_ORE)
						retVal = 0x800;				//Overrun Error Flag
					else
							retVal = 0xC00;
				#else
					retVal = 255;
				#endif
					break;
				case HAL_BUSY:
				case HAL_TIMEOUT:
				default:
					#if (MX_UART_RETURN_X == 1)
						retVal = 0x200;
					#else
						retVal = 255;
				#endif
					break;
				}
			#endif
			}
		#endif

		#if (MX_UART_FLOWEN_X == 1)
			#if (MX_UART_INT_X == 0)
				FC_CAL_Bit_High(MX_UART_RTS_PORT_X, MX_UART_RTS_PIN_X);		//not ready to accept data
			#endif
		#endif

	#endif

	return (retVal);
}


CALFUNCTION(void, FC_CAL_UART_Delay_, (void))
{
  #if (MX_UART_CHANNEL_X == 0)

	MX_UINT16 delay = MX_SOFT_BAUD_X;

	while (delay > 255)
	{
		delay_us(255);
		delay = delay - 255;
		MX_CLEAR_WATCHDOG;
	}
	delay_us(delay);
	MX_CLEAR_WATCHDOG;

  #endif
}


CALFUNCTION(void, FC_CAL_UART_UpdateBaud_, (MX_UINT8 new_baud))
{
	//Baud Rates - Function compatible with hardware mode only
	/*
	0 - 1200
	1 - 2400
	2 - 4800
	3 - 9600
	4 - 19200
	5 - 38400
	6 - 57600
	7 - 115200
	8 - 250000
	*/

	MX_UINT32 baudrate;

	#if (MX_UART_CHANNEL_X > 0)

		if (new_baud > 8)
			return;

		if (new_baud == 0)
		{
			baudrate = 1200;
		}
		else if (new_baud == 1)
		{
			baudrate = 2400;
		}
		else if (new_baud == 2)
		{
			baudrate = 4800;
		}
		else if (new_baud == 3)
		{
			baudrate = 9600;
		}
		else if (new_baud == 4)
		{
			baudrate = 19200;
		}
		else if (new_baud == 5)
		{
			baudrate = 38400;
		}
		else if (new_baud == 6)
		{
			baudrate = 57600;
		}
		else if (new_baud == 7)
		{
			baudrate = 115200;
		}
		else if (new_baud == 8)
		{
			baudrate = 250000;
		}

		MX_UART_HANDLE_X.Init.BaudRate = baudrate;
		HAL_UART_Init(&MX_UART_HANDLE_X);

	#endif

}
