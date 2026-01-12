// CRC: F9C65A77A483DDF22B438B7FEB8E3C81451B6760FECB07508D29EE770BB95F47626B6D0B0830C296350FCD25EAE876BF9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5DED670BFFD29F7067ABD2AFB29D0266957E23F96BACEEAF5435083CB849D859F06016CB6842986B611CDADCCB533D23C903DDFD5D162D6A4B5833719874E48FC18EE8FDFEFB7CC74C403E11131B547F3B9C5457FA442A08A549D34A0D5AD11F32DAC056F34AA00F291A32AD23802D9E68F6A277EFE56E6D35D2E1919BC6D834D57C406BC4A49D3F1
// REVISION: 1.0
// GUID: 1A8E3D6A-8C79-4521-AE7D-76F9D7157D02
// DATE: 08\08\2022
// DIR: CAL\PICO\PICO_CAL_UART.c

/*********************************************************************
 *                  Flowcode CAL UART File
 *
 * File: PICO_CAL_UART.c
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
 * 280521 | LM | Created
 *
 */

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#ifndef MX_UART_SW_DEFS
	#define MX_UART_SW_DEFS
	#define INST_COUNT	25	
	//Work out number of nops for software baud rate
	#define MX_OVERHEAD				(MX_CLK_SPEED / INST_COUNT)
	#define SW_OFFSET				(1000000 / MX_OVERHEAD)
#endif

#define MX_RECEIVE_DELAY 	(MX_CLK_SPEED / 1000000)


#define porta 0
#define portb 32


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

#define MX_UART_TX_GP_X	(MX_UART_TX_PORT_X + MX_UART_TX_PIN_X)
#define MX_UART_RX_GP_X	(MX_UART_RX_PORT_X + MX_UART_RX_PIN_X)

#define UART_Delay_CAL		CAL_APPEND(FC_CAL_UART_Delay_, MX_UART_NUM)
#define UART_HalfDelay_CAL	CAL_APPEND(FC_CAL_UART_HalfDelay_, MX_UART_NUM)
#define UART_Send			CAL_APPEND(FC_CAL_UART_Send_, MX_UART_NUM)
#define UART_Uninit			CAL_APPEND(FC_CAL_UART_Uninit_, MX_UART_NUM)


#if (MX_UART_CHANNEL_X == 0)
	#define MX_SOFT_BAUD_X (1000000 / MX_UART_BAUD_X)
	#if (MX_SOFT_BAUD_X < 1)
		#error "Software UART Baud Rate Not Available At This Clock Speed"
	#endif
#endif


// Definitions for software implementation
#define UART_STATUS_LOOP	0
#define UART_STATUS_TIMEOUT	1
#define UART_STATUS_RXBYTE	2


// This section of code is to support components such as GPS
#if   (MX_UART_CHANNEL_X == 1) && ((MX_UART_INT_X == 1) || defined (MX_UART0_INT))
	void uart0_interrupt_task(void);
#elif (MX_UART_CHANNEL_X == 2) && ((MX_UART_INT_X == 1) || defined (MX_UART1_INT))
	void uart1_interrupt_task(void);
#endif

#ifndef MX_UART_INT_DEFS
#define MX_UART_INT_DEFS

	#define MX_UART_INT_CH1_FUNC	void uart0_interrupt_task()	{
	#define MX_UART_INT_CH2_FUNC	void uart1_interrupt_task()	{
	#define MX_UART_INT_FUNC_END	}

	#define MX_UART_INT_CH1_DET		(1)
	#define MX_UART_INT_CH2_DET		(1)

	#define MX_UART_INT_CH1_EN
	#define MX_UART_INT_CH2_EN

	#define MX_UART_INT_CH1_DIS
	#define MX_UART_INT_CH2_DIS

	#define MX_UART_INT_CH1_CLR
	#define MX_UART_INT_CH2_CLR

#endif


#if (MX_UART_CHANNEL_X == 1)
	#define MX_UART_ID_X uart0
	#define MX_UART_IRQ_X UART0_IRQ
#elif (MX_UART_CHANNEL_X == 2)
	#define MX_UART_ID_X uart1
	#define MX_UART_IRQ_X UART1_IRQ
#endif


//Function Prototypes
CALFUNCTION(void, FC_CAL_UART_Init_, (void));
CALFUNCTION(void, FC_CAL_UART_Uninit_, (void));
CALFUNCTION(void, FC_CAL_UART_Send_, (MX_UINT16 nChar));
CALFUNCTION(MX_SINT16, FC_CAL_UART_Receive_, (MX_UINT8 nTimeout));
CALFUNCTION(void, FC_CAL_UART_Delay_, (void));
CALFUNCTION(void, FC_CAL_UART_HalfDelay_, (void));
CALFUNCTION(void, FC_CAL_UART_UpdateBaud_, (MX_UINT8 new_baud));


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

	#if (MX_UART_CHANNEL_X == 1)||(MX_UART_CHANNEL_X == 2)

		#if (MX_UART_DBITS_X == 9)
			#error "Sorry the PICO does not support 9 bit UART packets"
		#endif

		uart_init(MX_UART_ID_X, MX_UART_BAUD_X);
		#if (MX_UART_TX_EN_X)
			gpio_set_function(MX_UART_TX_GP_X, GPIO_FUNC_UART);
		#endif
		#if (MX_UART_RX_EN_X)
			gpio_set_function(MX_UART_RX_GP_X, GPIO_FUNC_UART);
		#endif
		// Turn off CTS/RTS flow control 
		uart_set_hw_flow(MX_UART_ID_X, false, false);
		// Set data format, here mainly for reference if we ever update our API
		uart_set_format(MX_UART_ID_X, 8, 1, UART_PARITY_NONE);

		// This section of code is to support components such as GPS
		#if   (MX_UART_CHANNEL_X == 1) && ((MX_UART_INT_X == 1) || defined (MX_UART0_INT))
			uart_set_fifo_enabled(MX_UART_ID_X, false);
			irq_set_exclusive_handler(MX_UART_IRQ_X, uart0_interrupt_task);
			irq_set_enabled(MX_UART_IRQ_X, true);
			uart_set_irq_enables(MX_UART_ID_X, true, false);
			
		#elif (MX_UART_CHANNEL_X == 2) && ((MX_UART_INT_X == 1) || defined (MX_UART1_INT))
			uart_set_fifo_enabled(MX_UART_ID_X, false);
			irq_set_exclusive_handler(MX_UART_IRQ_X, uart1_interrupt_task);
			irq_set_enabled(MX_UART_IRQ_X, true);
			uart_set_irq_enables(MX_UART_ID_X, true, false);	
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

	#if (MX_UART_CHANNEL_X == 1)||(MX_UART_CHANNEL_X == 2)

   	#endif

	#if (MX_UART_FLOWEN_X == 1)				//Flowcontrol enabled?
		FC_CAL_Bit_In_DDR (MX_UART_CTS_PORT_X, MX_UART_CTS_TRIS_X, MX_UART_CTS_PIN_X);		// CTS pin is a input
		FC_CAL_Bit_In_DDR (MX_UART_RTS_PORT_X, MX_UART_RTS_TRIS_X, MX_UART_RTS_PIN_X);		// RTS not ready to accept data
  	#endif
}


CALFUNCTION(void, FC_CAL_UART_Send_, (MX_UINT16 nChar))
{
	#if (MX_UART_TX_EN_X == 1)

		#if (MX_UART_FLOWEN_X == 1)
			while (FC_CAL_Bit_In(MX_UART_CTS_PORT_X, MX_UART_CTS_PIN_X) != 0);		// Wait until CTS is low
		#endif

		#if (MX_UART_CHANNEL_X == 0)
			MX_UINT8 idx;
			FC_CAL_Bit_Low(MX_UART_TX_PORT_X, MX_UART_TX_PIN_X);					// Send Start bit
			UART_Delay_CAL();
			for (idx = 0; idx < MX_UART_DBITS_X; idx++)
			{
				if (nChar & 0x01)													// Mask off data bit
					FC_CAL_Bit_High(MX_UART_TX_PORT_X, MX_UART_TX_PIN_X);
				else
					FC_CAL_Bit_Low(MX_UART_TX_PORT_X, MX_UART_TX_PIN_X);
				UART_Delay_CAL();
				nChar = nChar >> 1;													// Move to next data bit
			}
			FC_CAL_Bit_High(MX_UART_TX_PORT_X, MX_UART_TX_PIN_X);					// Send Stop bit
			UART_Delay_CAL();
		#endif

		#if (MX_UART_CHANNEL_X == 1)||(MX_UART_CHANNEL_X == 2)
			uart_putc_raw(MX_UART_ID_X, nChar);
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

		#if (MX_UART_CHANNEL_X > 0)
				if (uart_is_readable_within_us(MX_UART_ID_X, nTimeout * 1000))
				{
					retVal = uart_getc(MX_UART_ID_X);
				}
		#else

			MX_UINT8 delay1 = 0;
			MX_UINT8 regcheck = 0;
			MX_UINT8 bWaitForever = 0;
			MX_UINT8 rxStatus = UART_STATUS_LOOP;

		  #if (MX_UART_CHANNEL_X == 0)
			MX_UINT8 idx;
		  #else
			MX_UINT8 dummy = 0;
		  #endif

			if (nTimeout == 255)
				bWaitForever = 1;

			#if (MX_UART_FLOWEN_X == 1)
				#if (MX_UART_INT_X == 0)
					FC_CAL_Bit_Low (MX_UART_RTS_PORT_X, MX_UART_RTS_PIN_X);			// Ready to accept data
				#endif
			#endif

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
						sleep_us(10);
						delay1 = delay1 + 1;
						if(delay1 > 99)
						{
							nTimeout = nTimeout - 1;
							delay1 = 0;
						}
					}
				}

				#if (MX_UART_CHANNEL_X == 0)
					regcheck = FC_CAL_Bit_In(MX_UART_RX_PORT_X, MX_UART_RX_PIN_X);	//Test for start bit
					if (regcheck == 0)
						rxStatus = UART_STATUS_RXBYTE;
				#endif
			}

			if (rxStatus == UART_STATUS_RXBYTE)
			{
				#if (MX_UART_CHANNEL_X == 0)

					retVal = 0;
					UART_HalfDelay_CAL();
					UART_Delay_CAL();

					for (idx = 0; idx < MX_UART_DBITS_X; idx++)
					{
						if ( FC_CAL_Bit_In(MX_UART_RX_PORT_X, MX_UART_RX_PIN_X) )
							retVal = retVal | (0x01 << idx);

						UART_Delay_CAL();
					}

				#endif
			}

		#endif

		#if (MX_UART_ECHO_X == 1)
			// UART_Send(retVal);
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
    sleep_us(MX_SOFT_BAUD_X);
  #endif
}

CALFUNCTION(void, FC_CAL_UART_HalfDelay_, (void))
{
  #if (MX_UART_CHANNEL_X == 0)
	sleep_us((MX_SOFT_BAUD_X) >> 1);
  #endif
}


CALFUNCTION(void, FC_CAL_UART_UpdateBaud_, (MX_UINT8 Baud_Select))
{
	//Baud Rates - Function compatible with hardware mode only
	MX_UINT32 Baud = 9600;

	if (Baud_Select > 8)
		return;

	switch (Baud_Select)
	{
		case 0: Baud =   1200; break;
		case 1: Baud =   2400; break;
		case 2: Baud =   4800; break;
		case 3: Baud =   9600; break;
		case 4: Baud =  19200; break;
		case 5: Baud =  38400; break;
		case 6: Baud =  57600; break;
		case 7: Baud = 115200; break;
		case 8: Baud = 250000; break;
		default: Baud =  9600; break;
	}

	#if (MX_UART_CHANNEL_X == 1)||(MX_UART_CHANNEL_X == 2)
		uart_set_baudrate(MX_UART_ID_X, Baud);
	#endif

	#if (MX_UART_FLOWEN_X == 1)						//Flowcontrol enabled?
		FC_CAL_Bit_In_DDR (MX_UART_CTS_PORT_X, MX_UART_CTS_TRIS_X, MX_UART_CTS_PIN_X);			// CTS pin is a input

		#if (MX_UART_INT_X == 1)
			FC_CAL_Bit_Low_DDR (MX_UART_RTS_PORT_X, MX_UART_RTS_TRIS_X, MX_UART_RTS_PIN_X);		// RTS is ready to accept data
		#else
			FC_CAL_Bit_High_DDR (MX_UART_RTS_PORT_X, MX_UART_RTS_TRIS_X, MX_UART_RTS_PIN_X);	// RTS not ready to accept data
		#endif
	#endif

}

#undef MX_UART_ID_X
#undef MX_UART_IRQ_X
#undef MX_UART_TX_GP_X
#undef MX_UART_RX_GP_X
