// CRC: 77485F5F6A861F9125D47827B4DE492656C5431E478E8046055FD2257F64F1F3478F634975A712457CCBE7D4DA9E6C839A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF52479C8FDF3629BAF6FEE2B48E2A9CA81E0ECA4C2E97DE98C5A633A7EF8FD5B34FEF60AD2CB37B11C4A9C1F912F3274F849C80DDFF8B2FB80D711571F2B669B2CF2C7E65AF3AF87227458D5D21E5D13915B0B55DECB477F28549D34A0D5AD11F3A85BB156B4298DC94CCF33C7B1C5EA7F7F5A7AF15E46497DBFFF998DDEA49026AF90F20157562625
// REVISION: 1.0
// GUID: B55E85B8-763A-47FF-B106-68D352CDFF5A
// DATE: 08\08\2022
// DIR: CAL\AVR\AVR_CAL_UART.c
 /*********************************************************************
 *                  Flowcode CAL UART File
 *
 * File: AVR_CAL_UART.c
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
 * 010911 | BR | Created
 * 020911 | BR | Updated variables with typedef alternatives
 * 020312 | BR | Updated to v5.1 CAL Schema
 * 220512 | BR | Added XMEGA functionality
 * 190612 | BR | Fixed issues with 4 baud calc high byte
 * 240413 | LM | Fixed typo re PORT_1 -> PORT_X for Software UART
 * 030713 | LM | Standard API calls
 * 210114 | BR | Added some code to automatically switch the tris of the TX UART pin for XMEGA devices
 * 300914 | BR | Tried to make the baud calculation a bit more reliable for higher speed bauds at odd crystal frequencies
 * 121114 | LM | Added use of delay for receive timeout, as register loop was being compiled out
 */


#ifndef MX_UART_SW_DEFS
	#define MX_UART_SW_DEFS

	#define INST_COUNT	25			//----Need to test with other clock speeds----//

	//Work out number of nops for software baud rate
	#define MX_OVERHEAD				(MX_CLK_SPEED / INST_COUNT)
	#define SW_OFFSET				(1000000 / MX_OVERHEAD)

#endif


//Hardware Baud update definitions
#ifndef MX_HARD_BAUD_CHANGE_DEFS
	#define MX_HARD_BAUD_CHANGE_DEFS

	#define MX_HARD_BAUD_1200	(((MX_CLK_SPEED / 1200) - 8) / 16)		//Was - 16 but had issues with rounding down
	#define MX_HARD_HIGH_1200	0
	#if (MX_HARD_BAUD_1200 > 255)
		#undef MX_HARD_BAUD_1200
		#undef MX_HARD_HIGH_1200
		#define MX_HARD_BAUD_1200	(((MX_CLK_SPEED / 1200) - 8) / 16) & 0xFF
		#define MX_HARD_HIGH_1200	(((MX_CLK_SPEED / 1200) - 8) / 16) >> 8
	#endif

	#define MX_HARD_BAUD_2400	(((MX_CLK_SPEED / 2400) - 8) / 16)
	#define MX_HARD_HIGH_2400	0
	#if (MX_HARD_BAUD_2400 > 255)
		#undef MX_HARD_BAUD_2400
		#undef MX_HARD_HIGH_2400
		#define MX_HARD_BAUD_2400	(((MX_CLK_SPEED / 2400) - 8) / 16) & 0xFF
		#define MX_HARD_HIGH_2400	(((MX_CLK_SPEED / 2400) - 8) / 16) >> 8
	#endif

	#define MX_HARD_BAUD_4800	(((MX_CLK_SPEED / 4800) - 8) / 16)
	#define MX_HARD_HIGH_4800	0
	#if (MX_HARD_BAUD_4800 > 255)
		#undef MX_HARD_BAUD_4800
		#undef MX_HARD_HIGH_4800
		#define MX_HARD_BAUD_4800	(((MX_CLK_SPEED / 4800) - 8) / 16) & 0xFF
		#define MX_HARD_HIGH_4800	(((MX_CLK_SPEED / 4800) - 8) / 16) >> 8
	#endif

	#define MX_HARD_BAUD_9600	(((MX_CLK_SPEED / 9600) - 8) / 16)
	#define MX_HARD_HIGH_9600	0
	#if (MX_HARD_BAUD_9600 > 255)
		#undef MX_HARD_BAUD_9600
		#undef MX_HARD_HIGH_9600
		#define MX_HARD_BAUD_9600	(((MX_CLK_SPEED / 9600) - 8) / 16) & 0xFF
		#define MX_HARD_HIGH_9600	(((MX_CLK_SPEED / 9600) - 8) / 16) >> 8
	#endif

	#define MX_HARD_BAUD_19200	(((MX_CLK_SPEED / 19200) - 8) / 16)
	#define MX_HARD_HIGH_19200	0
	#if (MX_HARD_BAUD_19200 > 255)
		#undef MX_HARD_BAUD_19200
		#undef MX_HARD_HIGH_19200
		#define MX_HARD_BAUD_19200	(((MX_CLK_SPEED / 19200) - 8) / 16) & 0xFF
		#define MX_HARD_HIGH_19200	(((MX_CLK_SPEED / 19200) - 8) / 16) >> 8
	#endif

	#define MX_HARD_BAUD_38400	(((MX_CLK_SPEED / 38400) - 8) / 16)
	#define MX_HARD_HIGH_38400	0
	#if (MX_HARD_BAUD_38400 > 255)
		#undef MX_HARD_BAUD_38400
		#undef MX_HARD_HIGH_38400
		#define MX_HARD_BAUD_38400	(((MX_CLK_SPEED / 38400) - 8) / 16) & 0xFF
		#define MX_HARD_HIGH_38400	(((MX_CLK_SPEED / 38400) - 8) / 16) >> 8
	#endif

	#define MX_HARD_BAUD_57600	(((MX_CLK_SPEED / 57600) - 8) / 16)
	#define MX_HARD_HIGH_57600	0
	#if (MX_HARD_BAUD_57600 > 255)
		#undef MX_HARD_BAUD_57600
		#undef MX_HARD_HIGH_57600
		#define MX_HARD_BAUD_57600	(((MX_CLK_SPEED / 57600) - 8) / 16) & 0xFF
		#define MX_HARD_HIGH_57600	(((MX_CLK_SPEED / 57600) - 8) / 16) >> 8
	#endif

	#define MX_HARD_BAUD_115200	(((MX_CLK_SPEED / 115200) - 8) / 16)
	#define MX_HARD_HIGH_115200	0
	#if (MX_HARD_BAUD_115200 > 255)
		#undef MX_HARD_BAUD_115200
		#undef MX_HARD_HIGH_115200
		#define MX_HARD_BAUD_115200	(((MX_CLK_SPEED / 115200) - 8) / 16) & 0xFF
		#define MX_HARD_HIGH_115200	(((MX_CLK_SPEED / 115200) - 8) / 16) >> 8
	#endif

	#define MX_HARD_BAUD_250000	(((MX_CLK_SPEED / 250000) - 8) / 16)
	#define MX_HARD_HIGH_250000	0
	#if (MX_HARD_BAUD_250000 > 255)
		#undef MX_HARD_BAUD_250000
		#undef MX_HARD_HIGH_250000
		#define MX_HARD_BAUD_250000	(((MX_CLK_SPEED / 250000) - 8) / 64)
		#define MX_HARD_HIGH_250000	(((MX_CLK_SPEED / 250000) - 8) / 16) >> 8
	#endif

#endif

#define MX_RECEIVE_DELAY 	(MX_CLK_SPEED / 1000000)


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

#define UART_Delay_CAL		CAL_APPEND(FC_CAL_UART_Delay_, MX_UART_NUM)
#define UART_HalfDelay_CAL	CAL_APPEND(FC_CAL_UART_HalfDelay_, MX_UART_NUM)
#define UART_Send			CAL_APPEND(FC_CAL_UART_Send_, MX_UART_NUM)
#define UART_Uninit			CAL_APPEND(FC_CAL_UART_Uninit_, MX_UART_NUM)



#if (MX_UART_CHANNEL_X == 0)

	#define MX_SOFT_BAUD_X (1000000 / MX_UART_BAUD_X) - SW_OFFSET

	#if (MX_SOFT_BAUD_X < 1)
		#error "Software UART Baud Rate Not Available At This Clock Speed"
	#endif

#else

	#define MX_SOFT_BAUD_X	1
	#define MX_HARD_BAUD_X	(((MX_CLK_SPEED / MX_UART_BAUD_X) - 8) / 16)		//Was - 16 but had issues with rounding down
	#define MX_HARD_HIGH_X  0

	#if (MX_HARD_BAUD_X < 16)
		#undef MX_HARD_BAUD_X
		#undef MX_HARD_HIGH_X
		#define MX_HARD_BAUD_X	(((MX_CLK_SPEED / MX_UART_BAUD_X) - 4) / 8)
		#define MX_HARD_HIGH_X  0
		#define MX_UART_BAUD_X2_X
	#endif

	#if (MX_HARD_BAUD_X > 255)
		#undef MX_HARD_BAUD_X
		#undef MX_HARD_HIGH_X
		#define MX_HARD_BAUD_X (((MX_CLK_SPEED / MX_UART_BAUD_X) - 8)	/ 16) & 0xFF		//Was - 16 but had issues with rounding down
		#define MX_HARD_HIGH_X (((MX_CLK_SPEED / MX_UART_BAUD_X) - 8)	/ 16) >> 8
	#endif

#endif




//AVR Register Definitions

#ifndef MX_XMEGA
  #ifndef UDR0
    #ifdef UDR
  		#define UDR0	UDR
    #endif
    #ifdef UDR1
  		#define UDR0	UDR1
    #endif
  #endif

  #ifndef UBRR0H
    #ifdef UBRRH
  		#define UBRR0H	UBRRH
  	#endif
    #ifdef UBRR1H
    		#define UBRR0H	UBRR1H
  	#endif
  #endif

  #ifndef UBRR0L
    #ifdef UBRRL
  		#define UBRR0L	UBRRL
  	#endif
    #ifdef UBRR1L
   		#define UBRR0L	UBRR1L
  	#endif
  #endif

  #ifndef UCSR0C
    #ifdef UCSRC
  		#define UCSR0C	UCSRC
  	#endif
  #endif

  #ifndef UCSR0B
    #ifdef UCSRB
  		#define UCSR0B	UCSRB
  	#endif
    #ifdef UCSR1B
   		#define UCSR0B	UCSR1B
  	#endif
  #endif

  #ifndef UCSR0A
    #ifdef UCSRA
    	#define UCSR0A	UCSRA
    #endif
    #ifdef UCSR1A
      	#define UCSR0A	UCSR1A
    #endif
  #endif

  #ifndef UMSEL01
    #ifdef UMSEL1
		#define UMSEL01	UMSEL1
	#endif
  #endif

  #ifndef UMSEL00
    #ifdef UMSEL0
		#define UMSEL00	UMSEL0
	#endif
  #endif

  #ifndef UPM01
    #ifdef UPM1
		#define UPM01	UPM1
	#endif
  #endif

  #ifndef UPM00
  	#ifdef UPM0
		#define UPM00	UPM0
	#endif
  #endif

  #ifndef USBS0
  	#ifdef USBS
		#define USBS0	USBS
	#endif
  #endif

  #ifndef UCSZ01
    #ifdef UCSZ1
		#define UCSZ01	UCSZ1
	#endif
  #endif

  #ifndef UCSZ00
    #ifdef UCSZ0
		#define UCSZ00	UCSZ0
	#endif
  #endif

  #ifndef UCPOL0
    #ifdef UCPOL
		#define UCPOL0	UCPOL
	#endif
  #endif

  #ifndef RXCIE0
    #ifdef RXCIE
		#define RXCIE0	RXCIE
	#endif
    #ifdef RXCIE1
		#define RXCIE0	RXCIE1
	#endif
  #endif

  #ifndef TXCIE0
    #ifdef TXCIE
		#define TXCIE0	TXCIE
	#endif
    #ifdef TXCIE1
		#define TXCIE0	TXCIE1
	#endif
  #endif

  #ifndef UDRIE0
    #ifdef UDRIE
		#define UDRIE0	UDRIE
	#endif
  #endif

  #ifndef RXEN0
    #ifdef RXEN
		#define RXEN0	RXEN
	#endif
	#ifdef RXEN1
		#define RXEN0	RXEN1
	#endif
  #endif

  #ifndef TXEN0
    #ifdef TXEN
		#define TXEN0	TXEN
	#endif
	#ifdef TXEN1
		#define TXEN0	TXEN1
	#endif
  #endif

  #ifndef UCSZ02
  	#ifdef UCSZ2
		#define UCSZ02	UCSZ2
	#endif
  	#ifdef UCSZ12
		#define UCSZ02	UCSZ12
	#endif
  #endif

  #ifndef RXB80
    #ifdef RXB8
		#define RXB80	RXB8
	#endif
    #ifdef RXB81
		#define RXB80	RXB81
	#endif
  #endif

  #ifndef TXB80
    #ifdef TXB8
		#define TXB80	TXB8
	#endif
    #ifdef TXB81
		#define TXB80	TXB81
	#endif
  #endif

  #ifndef RXC0
    #ifdef RXC
		#define RXC0	RXC
	#endif
    #ifdef RXC1
		#define RXC0	RXC1
	#endif
  #endif

  #ifndef TXC0
    #ifdef TXC
		#define TXC0	TXC
	#endif
    #ifdef TXC1
		#define TXC0	TXC1
	#endif
  #endif

  #ifndef UDRE0
    #ifdef UDRE
		#define UDRE0	UDRE
	#endif
    #ifdef UDRE1
		#define UDRE0	UDRE1
	#endif
  #endif

  #ifndef FE0
    #ifdef FE
		#define FE0		FE
	#endif
    #ifdef FE1
		#define FE0		FE1
	#endif
  #endif

  #ifndef DOR0
    #ifdef DOR
		#define DOR0	DOR
	#endif
    #ifdef DOR1
		#define DOR0	DOR1
	#endif
  #endif

  #ifndef UPE0
    #ifdef UPE
		#define	UPE0	UPE
	#endif
  #endif

  #ifndef U2X0
    #ifdef U2X
		#define U2X0	U2X
	#endif
  #endif

  #ifndef MPCM0
    #ifdef MPCM
		#define MPCM0	MPCM
	#endif
  #endif

  #ifdef USR
  	#define UCSR0A	USR
  	#define UCSR0B	UCR
  #endif

  #ifndef USART0_RX_vect
    #ifdef USART_RX_vect
	  #define USART0_RX_vect	USART_RX_vect
	#endif
    #ifdef USART1_RX_vect
	  #define USART0_RX_vect	USART1_RX_vect
	#endif
    #ifdef USART_RXC_vect
	  #define USART0_RX_vect	USART_RXC_vect
	#endif
  #endif

#endif



//Component Definitions
#define UART_STATUS_LOOP	0
#define UART_STATUS_TIMEOUT	1
#define UART_STATUS_RXBYTE	2


#ifndef MX_UART_INT_DEFS
#define MX_UART_INT_DEFS

	#ifndef MX_XMEGA

		#ifdef LINCR							//LIN/UART hardware channel

			#define MX_UART_INT_CH1_FUNC	ISR(LIN_TC_vect) {
			#define MX_UART_INT_CH1_DET		(LINSIR & (1 << LRXOK)) && (LINENIR & (1 << LENRXOK))
			#define MX_UART_INT_CH1_EN		{set_bit(LINENIR, LENRXOK); sei();}
			#define MX_UART_INT_CH1_DIS		clear_bit(LINENIR, LENRXOK)

		#else

			#define MX_UART_INT_CH1_FUNC	ISR(USART0_RX_vect)	{
			#define MX_UART_INT_CH2_FUNC	ISR(USART1_RX_vect)	{
			#define MX_UART_INT_CH3_FUNC	ISR(USART2_RX_vect)	{
			#define MX_UART_INT_CH4_FUNC	ISR(USART3_RX_vect)	{
			#define MX_UART_INT_FUNC_END	}

			#define MX_UART_INT_CH1_DET		(UCSR0A & (1 << RXC0)) && (UCSR0B & (1 << RXCIE0))
			#define MX_UART_INT_CH2_DET		(UCSR1A & (1 << RXC1)) && (UCSR1B & (1 << RXCIE1))
			#define MX_UART_INT_CH3_DET		(UCSR2A & (1 << RXC2)) && (UCSR2B & (1 << RXCIE2))
			#define MX_UART_INT_CH4_DET		(UCSR3A & (1 << RXC3)) && (UCSR3B & (1 << RXCIE3))

			#define MX_UART_INT_CH1_EN		{set_bit(UCSR0B, RXCIE0); sei();}
			#define MX_UART_INT_CH2_EN		{set_bit(UCSR1B, RXCIE1); sei();}
			#define MX_UART_INT_CH3_EN		{set_bit(UCSR2B, RXCIE2); sei();}
			#define MX_UART_INT_CH4_EN		{set_bit(UCSR3B, RXCIE3); sei();}

			#define MX_UART_INT_CH1_DIS		clear_bit(UCSR0B, RXCIE0)
			#define MX_UART_INT_CH2_DIS		clear_bit(UCSR1B, RXCIE1)
			#define MX_UART_INT_CH3_DIS		clear_bit(UCSR2B, RXCIE2)
			#define MX_UART_INT_CH4_DIS		clear_bit(UCSR3B, RXCIE3)

		#endif

	#else

		#ifdef USARTC0
			#define MX_UART_CH1_DEF		USARTC0
			#define MX_UART_CH1_INT		USARTC0_RXC_vect
		#endif
		#ifdef USARTC1
			#define MX_UART_CH2_DEF		USARTC1
			#define MX_UART_CH2_INT		USARTC1_RXC_vect
			#ifdef USARTD0
				#define MX_UART_CH3_DEF		USARTD0
				#define MX_UART_CH3_INT		USARTD0_RXC_vect
			#endif
			#ifdef USARTD1
				#define MX_UART_CH4_DEF		USARTD1
				#define MX_UART_CH4_INT		USARTD1_RXC_vect
			#endif
			#ifdef USARTE0
				#define MX_UART_CH5_DEF		USARTE0
				#define MX_UART_CH5_INT		USARTE0_RXC_vect
			#endif
			#ifdef USARTE1
				#define MX_UART_CH6_DEF		USARTE1
				#define MX_UART_CH6_INT		USARTE1_RXC_vect
				#ifdef USARTF0
					#define MX_UART_CH7_DEF		USARTF0
					#define MX_UART_CH7_INT		USARTF0_RXC_vect
				#endif
				#ifdef USARTF1
					#define MX_UART_CH8_DEF		USARTF1
					#define MX_UART_CH8_INT		USARTF1_RXC_vect
				#endif
			#else
				#ifdef USARTF0
					#define MX_UART_CH6_DEF		USARTF0
					#define MX_UART_CH6_INT		USARTF0_RXC_vect
				#endif
			#endif
		#else
			#ifdef USARTD0
				#define MX_UART_CH2_DEF		USARTD0
				#define MX_UART_CH2_INT		USARTD0_RXC_vect
			#endif
			#ifdef USARTE0
				#define MX_UART_CH3_DEF		USARTE0
				#define MX_UART_CH3_INT		USARTE0_RXC_vect
			#endif
		#endif

		#define MX_UART_INT_CH1_FUNC	ISR(MX_UART_CH1_INT)	{
		#define MX_UART_INT_CH2_FUNC	ISR(MX_UART_CH2_INT)	{
		#define MX_UART_INT_CH3_FUNC	ISR(MX_UART_CH3_INT)	{
		#define MX_UART_INT_CH4_FUNC	ISR(MX_UART_CH4_INT)	{
		#define MX_UART_INT_CH5_FUNC	ISR(MX_UART_CH5_INT)	{
		#define MX_UART_INT_CH6_FUNC	ISR(MX_UART_CH6_INT)	{
		#define MX_UART_INT_CH7_FUNC	ISR(MX_UART_CH7_INT)	{
		#define MX_UART_INT_CH8_FUNC	ISR(MX_UART_CH8_INT)	{
		#define MX_UART_INT_FUNC_END	}

		#define MX_UART_INT_CH1_DET		(MX_UART_CH1_DEF.STATUS & (1 << USART_RXCIF_bp)) && (MX_UART_CH1_DEF.CTRLA & (1 << USART_RXCINTLVL0_bp))
		#define MX_UART_INT_CH2_DET		(MX_UART_CH2_DEF.STATUS & (1 << USART_RXCIF_bp)) && (MX_UART_CH2_DEF.CTRLA & (1 << USART_RXCINTLVL0_bp))
		#define MX_UART_INT_CH3_DET		(MX_UART_CH3_DEF.STATUS & (1 << USART_RXCIF_bp)) && (MX_UART_CH3_DEF.CTRLA & (1 << USART_RXCINTLVL0_bp))
		#define MX_UART_INT_CH4_DET		(MX_UART_CH4_DEF.STATUS & (1 << USART_RXCIF_bp)) && (MX_UART_CH4_DEF.CTRLA & (1 << USART_RXCINTLVL0_bp))
		#define MX_UART_INT_CH5_DET		(MX_UART_CH5_DEF.STATUS & (1 << USART_RXCIF_bp)) && (MX_UART_CH5_DEF.CTRLA & (1 << USART_RXCINTLVL0_bp))
		#define MX_UART_INT_CH6_DET		(MX_UART_CH6_DEF.STATUS & (1 << USART_RXCIF_bp)) && (MX_UART_CH6_DEF.CTRLA & (1 << USART_RXCINTLVL0_bp))
		#define MX_UART_INT_CH7_DET		(MX_UART_CH7_DEF.STATUS & (1 << USART_RXCIF_bp)) && (MX_UART_CH7_DEF.CTRLA & (1 << USART_RXCINTLVL0_bp))
		#define MX_UART_INT_CH8_DET		(MX_UART_CH8_DEF.STATUS & (1 << USART_RXCIF_bp)) && (MX_UART_CH8_DEF.CTRLA & (1 << USART_RXCINTLVL0_bp))

		#define MX_UART_INT_CH1_EN		{set_bit(MX_UART_CH1_DEF.CTRLA, USART_RXCINTLVL0_bp); sei();}
		#define MX_UART_INT_CH2_EN		{set_bit(MX_UART_CH2_DEF.CTRLA, USART_RXCINTLVL0_bp); sei();}
		#define MX_UART_INT_CH3_EN		{set_bit(MX_UART_CH3_DEF.CTRLA, USART_RXCINTLVL0_bp); sei();}
		#define MX_UART_INT_CH4_EN		{set_bit(MX_UART_CH4_DEF.CTRLA, USART_RXCINTLVL0_bp); sei();}
		#define MX_UART_INT_CH5_EN		{set_bit(MX_UART_CH5_DEF.CTRLA, USART_RXCINTLVL0_bp); sei();}
		#define MX_UART_INT_CH6_EN		{set_bit(MX_UART_CH6_DEF.CTRLA, USART_RXCINTLVL0_bp); sei();}
		#define MX_UART_INT_CH7_EN		{set_bit(MX_UART_CH7_DEF.CTRLA, USART_RXCINTLVL0_bp); sei();}
		#define MX_UART_INT_CH8_EN		{set_bit(MX_UART_CH8_DEF.CTRLA, USART_RXCINTLVL0_bp); sei();}

		#define MX_UART_INT_CH1_DIS		clear_bit(MX_UART_CH1_DEF.CTRLA, USART_RXCINTLVL0_bp)
		#define MX_UART_INT_CH2_DIS		clear_bit(MX_UART_CH2_DEF.CTRLA, USART_RXCINTLVL0_bp)
		#define MX_UART_INT_CH3_DIS		clear_bit(MX_UART_CH3_DEF.CTRLA, USART_RXCINTLVL0_bp)
		#define MX_UART_INT_CH4_DIS		clear_bit(MX_UART_CH4_DEF.CTRLA, USART_RXCINTLVL0_bp)
		#define MX_UART_INT_CH5_DIS		clear_bit(MX_UART_CH5_DEF.CTRLA, USART_RXCINTLVL0_bp)
		#define MX_UART_INT_CH6_DIS		clear_bit(MX_UART_CH6_DEF.CTRLA, USART_RXCINTLVL0_bp)
		#define MX_UART_INT_CH7_DIS		clear_bit(MX_UART_CH7_DEF.CTRLA, USART_RXCINTLVL0_bp)
		#define MX_UART_INT_CH8_DIS		clear_bit(MX_UART_CH8_DEF.CTRLA, USART_RXCINTLVL0_bp)

	#endif

	#define MX_UART_INT_CH1_CLR
	#define MX_UART_INT_CH2_CLR
	#define MX_UART_INT_CH3_CLR
	#define MX_UART_INT_CH4_CLR
	#define MX_UART_INT_CH5_CLR
	#define MX_UART_INT_CH6_CLR
	#define MX_UART_INT_CH7_CLR
	#define MX_UART_INT_CH8_CLR
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

	#if (MX_UART_CHANNEL_X == 1)

	  		#ifndef MX_XMEGA

				#ifdef LINCR							//LIN/UART hardware channel

					LINCR = 0x0C;						//Enable UART Mode
					#if (MX_UART_RX_EN_X == 1)
						LINCR |= 0x02;					//Enable RX
					#endif
					#if (MX_UART_TX_EN_X == 1)
						LINCR |= 0x01;					//Enable TX
					#endif

					LINBRRL = MX_HARD_BAUD_X >> 1;		//BAUD Rate
					LINBRRH = MX_HARD_HIGH_X >> 1;

				#else

					UCSR0A = 0x00;						// clear all UCSRA flags
					UCSR0B = 0x00;						// clear all UCSRB flags

					#ifdef UCSR0C
						#ifdef MX_UART_UCSRC
							UCSR0C = ((1 << UCSZ01) | (1 << UCSZ00));					// configuration for 8 data bits (Individual UCSRCx)
						#else
							UCSR0C = ((1 << URSEL) | (1 << UCSZ01) | (1 << UCSZ00));	// configuration for 8 data bits (Combined UBRRHx/UCSRCx)
						#endif
					#endif

					#if(MX_UART_DBITS_X == 9)
						set_bit(UCSR0B, UCSZ02);				// enable 9-bit mode
					#endif

					#ifdef UBRR
						UBRR = MX_HARD_BAUD_X;					// same baudrate calculation as PIC
					#else
						UBRR0L = MX_HARD_BAUD_X;				// same baudrate calculation
						UBRR0H = MX_HARD_HIGH_X;
					#endif

					#ifdef MX_UART_BAUD_X2_X
						set_bit(UCSR0A, U2X0);				// enable x2 speed
						#undef MX_UART_BAUD_X2_X
					#endif

					#if (MX_UART_RX_EN_X == 1)
						set_bit(UCSR0B, RXEN0);				// enable rx
					#endif
					#if (MX_UART_TX_EN_X == 1)
						set_bit(UCSR0B, TXEN0);				// enable tx
					#endif
				#endif
			#else

				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_TX_TRIS_X, MX_UART_TX_PIN_X);
				#endif

				MX_UART_CH1_DEF.CTRLA = 0x00;			// clear all UCSRA flags
				MX_UART_CH1_DEF.CTRLB = 0x00;			// clear all UCSRB flags
				MX_UART_CH1_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

			  #if(MX_UART_DBITS_X == 9)
				set_bit(MX_UART_CH1_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
			  #endif

				MX_UART_CH1_DEF.BAUDCTRLA = MX_HARD_BAUD_X;				// same baudrate calculation
				MX_UART_CH1_DEF.BAUDCTRLB = MX_HARD_HIGH_X;

				#if (MX_UART_RX_EN_X == 1)
					set_bit(MX_UART_CH1_DEF.CTRLB, USART_RXEN_bp);		// enable rx
				#endif
				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_CH1_DEF.CTRLB, USART_TXEN_bp);		// enable tx
				#endif

			#endif

			#if (MX_UART_INT_X == 1)
				MX_UART_INT_CH1_EN;
			#else
				MX_UART_INT_CH1_DIS;
			#endif

	#endif

	#if (MX_UART_CHANNEL_X == 2)

			#ifndef MX_XMEGA

				UCSR1A = 0x00;						// clear all UCSRA flags
				UCSR1B = 0x00;						// clear all UCSRB flags

			  #ifdef UCSR0C
				#ifdef MX_UART_UCSRC
					UCSR1C = ((1 << UCSZ11) | (1 << UCSZ10));					// configuration for 8 data bits (Individual UCSRCx)
				#else
					UCSR1C = ((1 << URSEL) | (1 << UCSZ11) | (1 << UCSZ10));	// configuration for 8 data bits (Combined UBRRHx/UCSRCx)
				#endif
			  #endif

			  #if(MX_UART_DBITS_X == 9)
				set_bit(UCSR1B, UCSZ12);				// enable 9-bit mode
			  #endif

			  #ifdef UBRR
				UBRR = MX_HARD_BAUD_X;					// same baudrate calculation as PIC
			  #else
			  	UBRR1L = MX_HARD_BAUD_X;				// same baudrate calculation
				UBRR1H = MX_HARD_HIGH_X;
			  #endif

			  #ifdef MX_UART_BAUD_X2_X
				set_bit(UCSR1A, U2X1);				// enable x2 speed
				#undef MX_UART_BAUD_X2_X
			  #endif

			  	#if (MX_UART_RX_EN_X == 1)
					set_bit(UCSR1B, RXEN1);				// enable rx
				#endif
				#if (MX_UART_TX_EN_X == 1)
					set_bit(UCSR1B, TXEN1);				// enable tx
				#endif

			#else

				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_TX_TRIS_X, MX_UART_TX_PIN_X);
				#endif

				MX_UART_CH2_DEF.CTRLA = 0x00;			// clear all UCSRA flags
				MX_UART_CH2_DEF.CTRLB = 0x00;			// clear all UCSRB flags
				MX_UART_CH2_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

			  #if(MX_UART_DBITS_X == 9)
				set_bit(MX_UART_CH2_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
			  #endif

				MX_UART_CH2_DEF.BAUDCTRLA = MX_HARD_BAUD_X;				// same baudrate calculation
				MX_UART_CH2_DEF.BAUDCTRLB = MX_HARD_HIGH_X;

				#if (MX_UART_RX_EN_X == 1)
					set_bit(MX_UART_CH2_DEF.CTRLB, USART_RXEN_bp);		// enable rx
				#endif
				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_CH2_DEF.CTRLB, USART_TXEN_bp);		// enable tx
				#endif

			#endif

			#if (MX_UART_INT_X == 1)
				MX_UART_INT_CH2_EN;
			#else
				MX_UART_INT_CH2_DIS;
			#endif
	#endif

	#if (MX_UART_CHANNEL_X == 3)

			#ifndef MX_XMEGA

				UCSR2A = 0x00;						// clear all UCSRA flags
				UCSR2B = 0x00;						// clear all UCSRB flags

			  #ifdef UCSR2C
				#ifdef MX_UART_UCSRC
					UCSR2C = ((1 << UCSZ21) | (1 << UCSZ20));					// configuration for 8 data bits (Individual UCSRCx)
				#else
					UCSR2C = ((1 << URSEL) | (1 << UCSZ21) | (1 << UCSZ20));	// configuration for 8 data bits (Combined UBRRHx/UCSRCx)
				#endif
			  #endif

			  #if(MX_UART_DBITS_X == 9)
				set_bit(UCSR2B, UCSZ22);				// enable 9-bit mode
			  #endif

			  #ifdef UBRR
				UBRR = MX_HARD_BAUD_X;					// same baudrate calculation as PIC
			  #else
				UBRR2L = MX_HARD_BAUD_X;				// same baudrate calculation
				UBRR2H = MX_HARD_HIGH_X;
			  #endif

			  #ifdef MX_UART_BAUD_X2_X
				set_bit(UCSR2A, U2X2);				// enable x2 speed
				#undef MX_UART_BAUD_X2_X
			  #endif

			  	#if (MX_UART_RX_EN_X == 1)
					set_bit(UCSR2B, RXEN2);				// enable rx
				#endif
				#if (MX_UART_TX_EN_X == 1)
					set_bit(UCSR2B, TXEN2);				// enable tx
				#endif

			#else

				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_TX_TRIS_X, MX_UART_TX_PIN_X);
				#endif

				MX_UART_CH3_DEF.CTRLA = 0x00;			// clear all UCSRA flags
				MX_UART_CH3_DEF.CTRLB = 0x00;			// clear all UCSRB flags
				MX_UART_CH3_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

			  #if(MX_UART_DBITS_X == 9)
				set_bit(MX_UART_CH3_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
			  #endif

				MX_UART_CH3_DEF.BAUDCTRLA = MX_HARD_BAUD_X;				// same baudrate calculation
				MX_UART_CH3_DEF.BAUDCTRLB = MX_HARD_HIGH_X;

				#if (MX_UART_RX_EN_X == 1)
					set_bit(MX_UART_CH3_DEF.CTRLB, USART_RXEN_bp);		// enable rx
				#endif
				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_CH3_DEF.CTRLB, USART_TXEN_bp);		// enable tx
				#endif

			#endif

			#if (MX_UART_INT_X == 1)
				MX_UART_INT_CH3_EN;
			#else
				MX_UART_INT_CH3_DIS;
			#endif
  	#endif

	#if (MX_UART_CHANNEL_X == 4)

			#ifndef MX_XMEGA

				UCSR3A = 0x00;						// clear all UCSRA flags
				UCSR3B = 0x00;						// clear all UCSRB flags

			  #ifdef UCSR3C
				#ifdef MX_UART_UCSRC
					UCSR3C = ((1 << UCSZ31) | (1 << UCSZ30));					// configuration for 8 data bits (Individual UCSRCx)
				#else
					UCSR3C = ((1 << URSEL) | (1 << UCSZ31) | (1 << UCSZ30));	// configuration for 8 data bits (Combined UBRRHx/UCSRCx)
				#endif
			  #endif

			  #if(MX_UART_DBITS_X == 9)
				set_bit(UCSR3B, UCSZ32);				// enable 9-bit mode
			  #endif

			  #ifdef UBRR
				UBRR = MX_HARD_BAUD_X;					// same baudrate calculation as PIC
			  #else
				UBRR3L = MX_HARD_BAUD_X;				// same baudrate calculation
				UBRR3H = MX_HARD_HIGH_X;
			  #endif

			  #ifdef MX_UART_BAUD_X2_X
				set_bit(UCSR3A, U2X3);				// enable x2 speed
				#undef MX_UART_BAUD_X2_X
			  #endif

			  	#if (MX_UART_RX_EN_X == 1)
					set_bit(UCSR3B, RXEN3);				// enable rx
				#endif
				#if (MX_UART_TX_EN_X == 1)
					set_bit(UCSR3B, TXEN3);				// enable tx
				#endif

			#else

				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_TX_TRIS_X, MX_UART_TX_PIN_X);
				#endif

				MX_UART_CH4_DEF.CTRLA = 0x00;			// clear all UCSRA flags
				MX_UART_CH4_DEF.CTRLB = 0x00;			// clear all UCSRB flags
				MX_UART_CH4_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

			  #if(MX_UART_DBITS_X == 9)
				set_bit(MX_UART_CH4_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
			  #endif

				MX_UART_CH4_DEF.BAUDCTRLA = MX_HARD_BAUD_X;				// same baudrate calculation
				MX_UART_CH4_DEF.BAUDCTRLB = MX_HARD_HIGH_X;				// as PIC

				#if (MX_UART_RX_EN_X == 1)
					set_bit(MX_UART_CH4_DEF.CTRLB, USART_RXEN_bp);		// enable rx
				#endif
				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_CH4_DEF.CTRLB, USART_TXEN_bp);		// enable tx
				#endif

			#endif

			#if (MX_UART_INT_X == 1)
				MX_UART_INT_CH4_EN;
			#else
				MX_UART_INT_CH4_DIS;
			#endif
  	#endif

	#if (MX_UART_CHANNEL_X == 5)

			#ifndef MX_XMEGA

			#else

				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_TX_TRIS_X, MX_UART_TX_PIN_X);
				#endif

				MX_UART_CH5_DEF.CTRLA = 0x00;			// clear all UCSRA flags
				MX_UART_CH5_DEF.CTRLB = 0x00;			// clear all UCSRB flags
				MX_UART_CH5_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

			  #if(MX_UART_DBITS_X == 9)
				set_bit(MX_UART_CH5_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
			  #endif

				MX_UART_CH5_DEF.BAUDCTRLA = MX_HARD_BAUD_X;				// same baudrate calculation
				MX_UART_CH5_DEF.BAUDCTRLB = MX_HARD_HIGH_X;				// as PIC

				#if (MX_UART_RX_EN_X == 1)
					set_bit(MX_UART_CH5_DEF.CTRLB, USART_RXEN_bp);		// enable rx
				#endif
				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_CH5_DEF.CTRLB, USART_TXEN_bp);		// enable tx
				#endif

			#endif

			#if (MX_UART_INT_X == 1)
				MX_UART_INT_CH5_EN;
			#else
				MX_UART_INT_CH5_DIS;
			#endif

  	#endif

	#if (MX_UART_CHANNEL_X == 6)

			#ifndef MX_XMEGA

			#else

				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_TX_TRIS_X, MX_UART_TX_PIN_X);
				#endif

				MX_UART_CH6_DEF.CTRLA = 0x00;			// clear all UCSRA flags
				MX_UART_CH6_DEF.CTRLB = 0x00;			// clear all UCSRB flags
				MX_UART_CH6_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

			  #if(MX_UART_DBITS_X == 9)
				set_bit(MX_UART_CH6_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
			  #endif

				MX_UART_CH6_DEF.BAUDCTRLA = MX_HARD_BAUD_X;				// same baudrate calculation
				MX_UART_CH6_DEF.BAUDCTRLB = MX_HARD_HIGH_X;				// as PIC

				#if (MX_UART_RX_EN_X == 1)
					set_bit(MX_UART_CH6_DEF.CTRLB, USART_RXEN_bp);		// enable rx
				#endif
				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_CH6_DEF.CTRLB, USART_TXEN_bp);		// enable tx
				#endif

			#endif

			#if (MX_UART_INT_X == 1)
				MX_UART_INT_CH6_EN;
			#else
				MX_UART_INT_CH6_DIS;
			#endif

  	#endif

	#if (MX_UART_CHANNEL_X == 7)

			#ifndef MX_XMEGA

			#else

				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_TX_TRIS_X, MX_UART_TX_PIN_X);
				#endif

				MX_UART_CH7_DEF.CTRLA = 0x00;			// clear all UCSRA flags
				MX_UART_CH7_DEF.CTRLB = 0x00;			// clear all UCSRB flags
				MX_UART_CH7_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

			  #if(MX_UART_DBITS_X == 9)
				set_bit(MX_UART_CH7_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
			  #endif

				MX_UART_CH7_DEF.BAUDCTRLA = MX_HARD_BAUD_X;				// same baudrate calculation
				MX_UART_CH7_DEF.BAUDCTRLB = MX_HARD_HIGH_X;				// as PIC

				#if (MX_UART_RX_EN_X == 1)
					set_bit(MX_UART_CH7_DEF.CTRLB, USART_RXEN_bp);		// enable rx
				#endif
				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_CH7_DEF.CTRLB, USART_TXEN_bp);		// enable tx
				#endif

			#endif

			#if (MX_UART_INT_X == 1)
				MX_UART_INT_CH7_EN;
			#else
				MX_UART_INT_CH7_DIS;
			#endif

  	#endif

	#if (MX_UART_CHANNEL_X == 8)

			#ifndef MX_XMEGA

			#else

				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_TX_TRIS_X, MX_UART_TX_PIN_X);
				#endif

				MX_UART_CH8_DEF.CTRLA = 0x00;			// clear all UCSRA flags
				MX_UART_CH8_DEF.CTRLB = 0x00;			// clear all UCSRB flags
				MX_UART_CH8_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

			  #if(MX_UART_DBITS_X == 9)
				set_bit(MX_UART_CH8_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
			  #endif

				MX_UART_CH8_DEF.BAUDCTRLA = MX_HARD_BAUD_X;				// same baudrate calculation
				MX_UART_CH8_DEF.BAUDCTRLB = MX_HARD_HIGH_X;				// as PIC

				#if (MX_UART_RX_EN_X == 1)
					set_bit(MX_UART_CH8_DEF.CTRLB, USART_RXEN_bp);		// enable rx
				#endif
				#if (MX_UART_TX_EN_X == 1)
					set_bit(MX_UART_CH8_DEF.CTRLB, USART_TXEN_bp);		// enable tx
				#endif

			#endif

			#if (MX_UART_INT_X == 1)
				MX_UART_INT_CH8_EN;
			#else
				MX_UART_INT_CH8_DIS;
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

	#if (MX_UART_CHANNEL_X == 1)
		#ifndef MX_XMEGA
			#ifdef LINCR							//LIN/UART hardware channel
				LINCR = 0x00;						//Disable UART Mode
			#else
				UCSR0A = 0x00;						// clear all UCSRA flags
				UCSR0B = 0x00;						// clear all UCSRB flags
			#endif
		#else
			MX_UART_CH1_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH1_DEF.CTRLB = 0x00;			// clear all UCSRB flags
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 2)
		#ifndef MX_XMEGA
			UCSR1A = 0x00;						// clear all UCSRA flags
			UCSR1B = 0x00;						// clear all UCSRB flags
		#else
			MX_UART_CH2_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH2_DEF.CTRLB = 0x00;			// clear all UCSRB flags
		#endif
   	#endif

	#if (MX_UART_CHANNEL_X == 3)
		#ifndef MX_XMEGA
			UCSR2A = 0x00;						// clear all UCSRA flags
			UCSR2B = 0x00;						// clear all UCSRB flags
		#else
			MX_UART_CH3_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH3_DEF.CTRLB = 0x00;			// clear all UCSRB flags
		#endif
   	#endif

	#if (MX_UART_CHANNEL_X == 4)
		#ifndef MX_XMEGA
			UCSR3A = 0x00;						// clear all UCSRA flags
			UCSR3B = 0x00;						// clear all UCSRB flags
		#else
			MX_UART_CH4_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH4_DEF.CTRLB = 0x00;			// clear all UCSRB flags
		#endif
   	#endif

	#if (MX_UART_CHANNEL_X == 5)
		#ifndef MX_XMEGA

		#else
			MX_UART_CH5_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH5_DEF.CTRLB = 0x00;			// clear all UCSRB flags
		#endif
   	#endif

	#if (MX_UART_CHANNEL_X == 6)
		#ifndef MX_XMEGA

		#else
			MX_UART_CH6_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH6_DEF.CTRLB = 0x00;			// clear all UCSRB flags
		#endif
   	#endif

	#if (MX_UART_CHANNEL_X == 7)
		#ifndef MX_XMEGA

		#else
			MX_UART_CH7_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH7_DEF.CTRLB = 0x00;			// clear all UCSRB flags
		#endif
   	#endif

	#if (MX_UART_CHANNEL_X == 8)
		#ifndef MX_XMEGA

		#else
			MX_UART_CH8_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH8_DEF.CTRLB = 0x00;			// clear all UCSRB flags
		#endif
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

		#if (MX_UART_CHANNEL_X == 1)
			#ifndef MX_XMEGA

				#ifdef LINCR							//LIN/UART hardware channel
					LINDAT = nChar;
					while ((test_bit(LINSIR, LTXOK)) == 0);	    // wait for tx ready
				#else
					while ((test_bit(UCSR0A, UDRE0)) == 0);	    // wait for tx ready
					#if (MX_UART_DBITS_X == 9)
						if (nChar & 0x100)
							set_bit(UCSR0B, TXB80);				// set 9th bit
						else
							clear_bit(UCSR0B, TXB80);			// clear 9th bit
					#endif
					UDR0 = nChar;
				#endif
			#else
				while ((test_bit(MX_UART_CH1_DEF.STATUS, USART_DREIF_bp)) == 0);	    // wait for tx ready
				#if (MX_UART_DBITS_X == 9)
					if (nChar & 0x100)
						set_bit(MX_UART_CH1_DEF.CTRLB, USART_TXB8_bp);				// set 9th bit
					else
						clear_bit(MX_UART_CH1_DEF.CTRLB, USART_TXB8_bp);				// clear 9th bit
				#endif
				MX_UART_CH1_DEF.DATA = nChar;
			#endif
		#endif

		#if (MX_UART_CHANNEL_X == 2)
			#ifndef MX_XMEGA
				while ((test_bit(UCSR1A, UDRE1)) == 0);	    // wait for tx ready
				#if (MX_UART_DBITS_X == 9)
					if (nChar & 0x100)
						set_bit(UCSR1B, TXB81);				// set 9th bit
					else
						clear_bit(UCSR1B, TXB81);			// clear 9th bit
				#endif
				UDR1 = nChar;
			#else
				while ((test_bit(MX_UART_CH2_DEF.STATUS, USART_DREIF_bp)) == 0);	    // wait for tx ready
				#if (MX_UART_DBITS_X == 9)
					if (nChar & 0x100)
						set_bit(MX_UART_CH2_DEF.CTRLB, USART_TXB8_bp);				// set 9th bit
					else
						clear_bit(MX_UART_CH2_DEF.CTRLB, USART_TXB8_bp);				// clear 9th bit
				#endif
				MX_UART_CH2_DEF.DATA = nChar;
			#endif
		#endif

		#if (MX_UART_CHANNEL_X == 3)
			#ifndef MX_XMEGA
				while ((test_bit(UCSR2A, UDRE2)) == 0);	    // wait for tx ready
				#if (MX_UART_DBITS_X == 9)
					if (nChar & 0x100)
						set_bit(UCSR2B, TXB82);				// set 9th bit
					else
						clear_bit(UCSR2B, TXB82);			// clear 9th bit
				#endif
				UDR2 = nChar;
			#else
				while ((test_bit(MX_UART_CH3_DEF.STATUS, USART_DREIF_bp)) == 0);	    // wait for tx ready
				#if (MX_UART_DBITS_X == 9)
					if (nChar & 0x100)
						set_bit(MX_UART_CH3_DEF.CTRLB, USART_TXB8_bp);				// set 9th bit
					else
						clear_bit(MX_UART_CH3_DEF.CTRLB, USART_TXB8_bp);				// clear 9th bit
				#endif
				MX_UART_CH3_DEF.DATA = nChar;
			#endif
		#endif

		#if (MX_UART_CHANNEL_X == 4)
			#ifndef MX_XMEGA
				while ((test_bit(UCSR3A, UDRE3)) == 0);	    // wait for tx ready
				#if (MX_UART_DBITS_X == 9)
					if (nChar & 0x100)
						set_bit(UCSR3B, TXB83);				// set 9th bit
					else
						clear_bit(UCSR3B, TXB83);			// clear 9th bit
				#endif
				UDR3 = nChar;
			#else
				while ((test_bit(MX_UART_CH4_DEF.STATUS, USART_DREIF_bp)) == 0);	    // wait for tx ready
				#if (MX_UART_DBITS_X == 9)
					if (nChar & 0x100)
						set_bit(MX_UART_CH4_DEF.CTRLB, USART_TXB8_bp);				// set 9th bit
					else
						clear_bit(MX_UART_CH4_DEF.CTRLB, USART_TXB8_bp);				// clear 9th bit
				#endif
				MX_UART_CH4_DEF.DATA = nChar;
			#endif
		#endif

		#if (MX_UART_CHANNEL_X == 5)
			#ifndef MX_XMEGA
			#else
				while ((test_bit(MX_UART_CH5_DEF.STATUS, USART_DREIF_bp)) == 0);	    // wait for tx ready
				#if (MX_UART_DBITS_X == 9)
					if (nChar & 0x100)
						set_bit(MX_UART_CH5_DEF.CTRLB, USART_TXB8_bp);				// set 9th bit
					else
						clear_bit(MX_UART_CH5_DEF.CTRLB, USART_TXB8_bp);				// clear 9th bit
				#endif
				MX_UART_CH5_DEF.DATA = nChar;
			#endif
		#endif

		#if (MX_UART_CHANNEL_X == 6)
			#ifndef MX_XMEGA
			#else
				while ((test_bit(MX_UART_CH6_DEF.STATUS, USART_DREIF_bp)) == 0);	    // wait for tx ready
				#if (MX_UART_DBITS_X == 9)
					if (nChar & 0x100)
						set_bit(MX_UART_CH6_DEF.CTRLB, USART_TXB8_bp);				// set 9th bit
					else
						clear_bit(MX_UART_CH6_DEF.CTRLB, USART_TXB8_bp);				// clear 9th bit
				#endif
				MX_UART_CH6_DEF.DATA = nChar;
			#endif
		#endif

		#if (MX_UART_CHANNEL_X == 7)
			#ifndef MX_XMEGA
			#else
				while ((test_bit(MX_UART_CH7_DEF.STATUS, USART_DREIF_bp)) == 0);	    // wait for tx ready
				#if (MX_UART_DBITS_X == 9)
					if (nChar & 0x100)
						set_bit(MX_UART_CH7_DEF.CTRLB, USART_TXB8_bp);				// set 9th bit
					else
						clear_bit(MX_UART_CH7_DEF.CTRLB, USART_TXB8_bp);				// clear 9th bit
				#endif
				MX_UART_CH7_DEF.DATA = nChar;
			#endif
		#endif

		#if (MX_UART_CHANNEL_X == 8)
			#ifndef MX_XMEGA
			#else
				while ((test_bit(MX_UART_CH8_DEF.STATUS, USART_DREIF_bp)) == 0);	    // wait for tx ready
				#if (MX_UART_DBITS_X == 9)
					if (nChar & 0x100)
						set_bit(MX_UART_CH8_DEF.CTRLB, USART_TXB8_bp);				// set 9th bit
					else
						clear_bit(MX_UART_CH8_DEF.CTRLB, USART_TXB8_bp);				// clear 9th bit
				#endif
				MX_UART_CH8_DEF.DATA = nChar;
			#endif
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

		MX_UINT8 delay1 = 0;
		MX_UINT8 regcheck = 0;
		MX_UINT8 bWaitForever = 0;
		MX_UINT8 rxStatus = UART_STATUS_LOOP;
		MX_UINT16 delaycnt;

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
					if (delaycnt == 0)						//BR 10/10/18 Now more like ms delays
					{
						delaycnt = MX_RECEIVE_DELAY;
						delay1 = delay1 + 1;
						if(delay1 == 40)
						{
							nTimeout = nTimeout - 1;
							MX_CLEAR_WATCHDOG;
							delay1 = 0;
						}
					}
					else
					{
						delaycnt--;
					}
				}
			}

			#if (MX_UART_CHANNEL_X == 0)
				regcheck = FC_CAL_Bit_In(MX_UART_RX_PORT_X, MX_UART_RX_PIN_X);	//Test for start bit
				if (regcheck == 0)
					rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 1)
				#ifndef MX_XMEGA
					#ifdef LINCR							//LIN/UART hardware channel
						regcheck = (test_bit(LINSIR, LRXOK));
					#else
						regcheck = (test_bit(UCSR0A, RXC0));
					#endif
				#else
					regcheck = (test_bit(MX_UART_CH1_DEF.STATUS, USART_RXCIF_bp));
				#endif
				if (regcheck != 0)
					rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 2)
				#ifndef MX_XMEGA
					regcheck = (test_bit(UCSR1A, RXC1));
				#else
					regcheck = (test_bit(MX_UART_CH2_DEF.STATUS, USART_RXCIF_bp));
				#endif
				if (regcheck != 0)
					rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 3)
				#ifndef MX_XMEGA
					regcheck = (test_bit(UCSR2A, RXC2));
				#else
					regcheck = (test_bit(MX_UART_CH3_DEF.STATUS, USART_RXCIF_bp));
				#endif
				if (regcheck != 0)
					rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 4)
				#ifndef MX_XMEGA
					regcheck = (test_bit(UCSR3A, RXC3));
				#else
					regcheck = (test_bit(MX_UART_CH4_DEF.STATUS, USART_RXCIF_bp));
				#endif
				if (regcheck != 0)
					rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 5)
				#ifndef MX_XMEGA
				#else
					regcheck = (test_bit(MX_UART_CH5_DEF.STATUS, USART_RXCIF_bp));
				#endif
				if (regcheck != 0)
					rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 6)
				#ifndef MX_XMEGA
				#else
					regcheck = (test_bit(MX_UART_CH6_DEF.STATUS, USART_RXCIF_bp));
				#endif
				if (regcheck != 0)
					rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 7)
				#ifndef MX_XMEGA
				#else
					regcheck = (test_bit(MX_UART_CH7_DEF.STATUS, USART_RXCIF_bp));
				#endif
				if (regcheck != 0)
					rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 8)
				#ifndef MX_XMEGA
				#else
					regcheck = (test_bit(MX_UART_CH8_DEF.STATUS, USART_RXCIF_bp));
				#endif
				if (regcheck != 0)
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

			#if (MX_UART_CHANNEL_X == 1)
				#ifndef MX_XMEGA
					#ifdef LINCR							//LIN/UART hardware channel
						regcheck = test_bit(LINERR, LFERR);
						if (regcheck != 0)
						{
							clear_bit(LINSIR, LERR);			//clear ERR
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x400;					//Framing Error Flag
							#endif
						}
						else
						{
							regcheck = test_bit(LINERR, LOVERR);
							if (regcheck != 0)
							{
								clear_bit(LINSIR, LERR);		//clear ERR
								#if (MX_UART_RETURN_X == 1)
									retVal = 0x800;				//Overrun Error Flag
								#endif
							}
							else
							{
								retVal = LINDAT; 				//no error, so rx byte is valid
							}
						}
					#else
						regcheck = test_bit(UCSR0A, FE0);
						if (regcheck != 0)
						{
							dummy = UDR0;						//need to read the rcreg to clear FERR
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x400;					//Framing Error Flag
							#endif
						}
						else
						{
							regcheck = test_bit(UCSR0A, DOR0);
							if (regcheck != 0)
							{
								dummy = UDR0;
								#if (MX_UART_RETURN_X == 1)
									retVal = 0x800;				//Overrun Error Flag
								#endif
							}
							else
							{
								retVal = 0;

								#if (MX_UART_DBITS_X == 9)
									if(test_bit(UCSR0B, RXB80))
										retVal = 0x100;
								#endif

								retVal |= UDR0; 					//no error, so rx byte is valid
							}
						}
					#endif
				#else
					regcheck = test_bit(MX_UART_CH1_DEF.STATUS, USART_FERR_bp);
					if (regcheck != 0)
					{
						dummy = MX_UART_CH1_DEF.DATA;			//need to read the rcreg to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;						//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = test_bit(MX_UART_CH1_DEF.STATUS, USART_BUFOVF_bp);
						if (regcheck != 0)
						{
							dummy = MX_UART_CH1_DEF.DATA;		//need to read the rcreg to clear FERR
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;					//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;

							#if (MX_UART_DBITS_X == 9)
								if(test_bit(MX_UART_CH1_DEF.STATUS, USART_RXB8_bp))
									retVal = 0x100;
							#endif

							retVal |= MX_UART_CH1_DEF.DATA;		//no error, so rx byte is valid
						}
					}
				#endif
			#endif

			#if (MX_UART_CHANNEL_X == 2)
				#ifndef MX_XMEGA
					regcheck = test_bit(UCSR1A, FE1);
					if (regcheck != 0)
					{
						dummy = UDR1;						//need to read the rcreg to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;					//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = test_bit(UCSR1A, DOR1);
						if (regcheck != 0)
						{
							dummy = UDR1;
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;				//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;

							#if (MX_UART_DBITS_X == 9)
								if(test_bit(UCSR1B, RXB81))
									retVal = 0x100;
							#endif

							retVal |= UDR1; 				//no error, so rx byte is valid
						}
					}
				#else
					regcheck = test_bit(MX_UART_CH2_DEF.STATUS, USART_FERR_bp);
					if (regcheck != 0)
					{
						dummy = MX_UART_CH2_DEF.DATA;			//need to read the rcreg to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;						//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = test_bit(MX_UART_CH2_DEF.STATUS, USART_BUFOVF_bp);
						if (regcheck != 0)
						{
							dummy = MX_UART_CH2_DEF.DATA;		//need to read the rcreg to clear FERR
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;					//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;

							#if (MX_UART_DBITS_X == 9)
								if(test_bit(MX_UART_CH2_DEF.STATUS, USART_RXB8_bp))
									retVal = 0x100;
							#endif

							retVal |= MX_UART_CH2_DEF.DATA;		//no error, so rx byte is valid
						}
					}
				#endif
			#endif

			#if (MX_UART_CHANNEL_X == 3)
				#ifndef MX_XMEGA
					regcheck = test_bit(UCSR2A, FE2);
					if (regcheck != 0)
					{
						dummy = UDR2;						//need to read the rcreg to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;					//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = test_bit(UCSR2A, DOR2);
						if (regcheck != 0)
						{
							dummy = UDR2;
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;				//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;
							#if (MX_UART_DBITS_X == 9)
								if(test_bit(UCSR2B, RXB82))
									retVal = 0x100;
							#endif

							retVal |= UDR2; 				//no error, so rx byte is valid
						}
					}
				#else
					regcheck = test_bit(MX_UART_CH3_DEF.STATUS, USART_FERR_bp);
					if (regcheck != 0)
					{
						dummy = MX_UART_CH3_DEF.DATA;			//need to read the rcreg to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;						//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = test_bit(MX_UART_CH3_DEF.STATUS, USART_BUFOVF_bp);
						if (regcheck != 0)
						{
							dummy = MX_UART_CH3_DEF.DATA;		//need to read the rcreg to clear FERR
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;					//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;

							#if (MX_UART_DBITS_X == 9)
								if(test_bit(MX_UART_CH3_DEF.STATUS, USART_RXB8_bp))
									retVal = 0x100;
							#endif

							retVal |= MX_UART_CH3_DEF.DATA;		//no error, so rx byte is valid
						}
					}
				#endif
			#endif

			#if (MX_UART_CHANNEL_X == 4)
				#ifndef MX_XMEGA
					regcheck = test_bit(UCSR3A, FE3);
					if (regcheck != 0)
					{
						dummy = UDR3;						//need to read the rcreg to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;					//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = test_bit(UCSR3A, DOR3);
						if (regcheck != 0)
						{
							dummy = UDR3;
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;				//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;

							#if (MX_UART_DBITS_X == 9)
								if(test_bit(UCSR3B, RXB83))
									retVal = 0x100;
							#endif

							retVal |= UDR3; 				//no error, so rx byte is valid
						}
					}
				#else
					regcheck = test_bit(MX_UART_CH4_DEF.STATUS, USART_FERR_bp);
					if (regcheck != 0)
					{
						dummy = MX_UART_CH4_DEF.DATA;			//need to read the rcreg to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;						//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = test_bit(MX_UART_CH4_DEF.STATUS, USART_BUFOVF_bp);
						if (regcheck != 0)
						{
							dummy = MX_UART_CH4_DEF.DATA;		//need to read the rcreg to clear FERR
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;					//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;

							#if (MX_UART_DBITS_X == 9)
								if(test_bit(MX_UART_CH4_DEF.STATUS, USART_RXB8_bp))
									retVal = 0x100;
							#endif

							retVal |= MX_UART_CH4_DEF.DATA;		//no error, so rx byte is valid
						}
					}
				#endif
			#endif

			#if (MX_UART_CHANNEL_X == 5)
				#ifndef MX_XMEGA
				#else
					regcheck = test_bit(MX_UART_CH5_DEF.STATUS, USART_FERR_bp);
					if (regcheck != 0)
					{
						dummy = MX_UART_CH5_DEF.DATA;			//need to read the rcreg to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;						//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = test_bit(MX_UART_CH5_DEF.STATUS, USART_BUFOVF_bp);
						if (regcheck != 0)
						{
							dummy = MX_UART_CH5_DEF.DATA;		//need to read the rcreg to clear FERR
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;					//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;

							#if (MX_UART_DBITS_X == 9)
								if(test_bit(MX_UART_CH5_DEF.STATUS, USART_RXB8_bp))
									retVal = 0x100;
							#endif

							retVal |= MX_UART_CH5_DEF.DATA;		//no error, so rx byte is valid
						}
					}
				#endif
			#endif

			#if (MX_UART_CHANNEL_X == 6)
				#ifndef MX_XMEGA
				#else
					regcheck = test_bit(MX_UART_CH6_DEF.STATUS, USART_FERR_bp);
					if (regcheck != 0)
					{
						dummy = MX_UART_CH6_DEF.DATA;			//need to read the rcreg to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;						//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = test_bit(MX_UART_CH6_DEF.STATUS, USART_BUFOVF_bp);
						if (regcheck != 0)
						{
							dummy = MX_UART_CH6_DEF.DATA;		//need to read the rcreg to clear FERR
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;					//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;

							#if (MX_UART_DBITS_X == 9)
								if(test_bit(MX_UART_CH6_DEF.STATUS, USART_RXB8_bp))
									retVal = 0x100;
							#endif

							retVal |= MX_UART_CH6_DEF.DATA;		//no error, so rx byte is valid
						}
					}
				#endif
			#endif

			#if (MX_UART_CHANNEL_X == 7)
				#ifndef MX_XMEGA
				#else
					regcheck = test_bit(MX_UART_CH7_DEF.STATUS, USART_FERR_bp);
					if (regcheck != 0)
					{
						dummy = MX_UART_CH7_DEF.DATA;			//need to read the rcreg to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;						//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = test_bit(MX_UART_CH7_DEF.STATUS, USART_BUFOVF_bp);
						if (regcheck != 0)
						{
							dummy = MX_UART_CH7_DEF.DATA;		//need to read the rcreg to clear FERR
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;					//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;

							#if (MX_UART_DBITS_X == 9)
								if(test_bit(MX_UART_CH7_DEF.STATUS, USART_RXB8_bp))
									retVal = 0x100;
							#endif

							retVal |= MX_UART_CH7_DEF.DATA;		//no error, so rx byte is valid
						}
					}
				#endif
			#endif

			#if (MX_UART_CHANNEL_X == 8)
				#ifndef MX_XMEGA
				#else
					regcheck = test_bit(MX_UART_CH8_DEF.STATUS, USART_FERR_bp);
					if (regcheck != 0)
					{
						dummy = MX_UART_CH8_DEF.DATA;			//need to read the rcreg to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;						//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = test_bit(MX_UART_CH8_DEF.STATUS, USART_BUFOVF_bp);
						if (regcheck != 0)
						{
							dummy = MX_UART_CH8_DEF.DATA;		//need to read the rcreg to clear FERR
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;					//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;

							#if (MX_UART_DBITS_X == 9)
								if(test_bit(MX_UART_CH8_DEF.STATUS, USART_RXB8_bp))
									retVal = 0x100;
							#endif

							retVal |= MX_UART_CH8_DEF.DATA;		//no error, so rx byte is valid
						}
					}
				#endif
			#endif

			#if (MX_UART_ECHO_X == 1)
				UART_Send(retVal);
			#endif
		}

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

CALFUNCTION(void, FC_CAL_UART_HalfDelay_, (void))
{
  #if (MX_UART_CHANNEL_X == 0)

	MX_UINT16 delay = (MX_SOFT_BAUD_X) >> 1;

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

	MX_UINT8 baudrateh, baudratel;

	if (new_baud > 8)
		return;

	if (new_baud == 0)
	{
		baudratel = MX_HARD_BAUD_1200;
		baudrateh = MX_HARD_HIGH_1200;
	}
	else if (new_baud == 1)
	{
		baudratel = MX_HARD_BAUD_2400;
		baudrateh = MX_HARD_HIGH_2400;
	}
	else if (new_baud == 2)
	{
		baudratel = MX_HARD_BAUD_4800;
		baudrateh = MX_HARD_HIGH_4800;
	}
	else if (new_baud == 3)
	{
		baudratel = MX_HARD_BAUD_9600;
		baudrateh = MX_HARD_HIGH_9600;
	}
	else if (new_baud == 4)
	{
		baudratel = MX_HARD_BAUD_19200;
		baudrateh = MX_HARD_HIGH_19200;
	}
	else if (new_baud == 5)
	{
		baudratel = MX_HARD_BAUD_38400;
		baudrateh = MX_HARD_HIGH_38400;
	}
	else if (new_baud == 6)
	{
		baudratel = MX_HARD_BAUD_57600;
		baudrateh = MX_HARD_HIGH_57600;
	}
	else if (new_baud == 7)
	{
		baudratel = MX_HARD_BAUD_115200;
		baudrateh = MX_HARD_HIGH_115200;
	}
	else if (new_baud == 8)
	{
		baudratel = MX_HARD_BAUD_250000;
		baudrateh = MX_HARD_HIGH_250000;
	}

	UART_Uninit();

	#if (MX_UART_CHANNEL_X == 1)
		#ifndef MX_XMEGA

			#ifdef LINCR							//LIN/UART hardware channel

				LINBRRL = baudratel >> 1;		//BAUD Rate
				LINBRRH = baudrateh >> 1;

			#else

				UCSR0A = 0x00;						// clear all UCSRA flags
				UCSR0B = 0x00;						// clear all UCSRB flags

			  #ifdef UCSR0C
				#ifdef MX_UART_UCSRC
					UCSR0C = ((1 << UCSZ01) | (1 << UCSZ00));					// configuration for 8 data bits (Individual UCSRCx)
				#else
					UCSR0C = ((1 << URSEL) | (1 << UCSZ01) | (1 << UCSZ00));	// configuration for 8 data bits (Combined UBRRHx/UCSRCx)
				#endif
			  #endif

			  #if(MX_UART_DBITS_X == 9)
				set_bit(UCSR0B, UCSZ02);				// enable 9-bit mode
			  #endif

			  #ifdef UBRR
				UBRR = baudratel;						// same baudrate calculation as PIC
			  #else
				UBRR0L = baudratel;						// same baudrate calculation
				UBRR0H = baudrateh;						// as PIC though only /16
			  #endif

				#if (MX_UART_RX_EN_X == 1)
					set_bit(UCSR0B, RXEN0);				// enable rx
				#endif
				#if (MX_UART_TX_EN_X == 1)
					set_bit(UCSR0B, TXEN0);				// enable tx
				#endif
			#endif

		#else
			MX_UART_CH1_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH1_DEF.CTRLB = 0x00;			// clear all UCSRB flags
			MX_UART_CH1_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

		  #if(MX_UART_DBITS_X == 9)
			set_bit(MX_UART_CH1_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
		  #endif

			MX_UART_CH1_DEF.BAUDCTRLA = baudratel;					// same baudrate calculation
			MX_UART_CH1_DEF.BAUDCTRLB = baudrateh;					// as PIC though only /16

			#if (MX_UART_RX_EN_X == 1)
				set_bit(MX_UART_CH1_DEF.CTRLB, USART_RXEN_bp);		// enable rx
			#endif
			#if (MX_UART_TX_EN_X == 1)
				set_bit(MX_UART_CH1_DEF.CTRLB, USART_TXEN_bp);		// enable tx
			#endif
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH1_EN;
		#else
			//MX_UART_INT_CH1_DIS;			//Don't disable UART RX INT here!
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 2)
		#ifndef MX_XMEGA
			UCSR1A = 0x00;						// clear all UCSRA flags
			UCSR1B = 0x00;						// clear all UCSRB flags

		  #ifdef UCSR0C
			#ifdef MX_UART_UCSRC
				UCSR1C = ((1 << UCSZ11) | (1 << UCSZ10));					// configuration for 8 data bits (Individual UCSRCx)
			#else
				UCSR1C = ((1 << URSEL) | (1 << UCSZ11) | (1 << UCSZ10));	// configuration for 8 data bits (Combined UBRRHx/UCSRCx)
			#endif
		  #endif

		  #if(MX_UART_DBITS_X == 9)
			set_bit(UCSR1B, UCSZ12);					// enable 9-bit mode
		  #endif

		  #ifdef UBRR
			UBRR = baudratel;						// same baudrate calculation as PIC
		  #else
			UBRR1L = baudratel;						// same baudrate calculation
			UBRR1H = baudrateh;						// as PIC
		  #endif

		  	#if (MX_UART_RX_EN_X == 1)
				set_bit(UCSR1B, RXEN1);					// enable rx
			#endif
			#if (MX_UART_TX_EN_X == 1)
				set_bit(UCSR1B, TXEN1);					// enable tx
			#endif
		#else
			MX_UART_CH2_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH2_DEF.CTRLB = 0x00;			// clear all UCSRB flags
			MX_UART_CH2_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

		  #if(MX_UART_DBITS_X == 9)
			set_bit(MX_UART_CH2_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
		  #endif

			MX_UART_CH2_DEF.BAUDCTRLA = baudratel;					// same baudrate calculation
			MX_UART_CH2_DEF.BAUDCTRLB = baudrateh;					// as PIC

			#if (MX_UART_RX_EN_X == 1)
				set_bit(MX_UART_CH2_DEF.CTRLB, USART_RXEN_bp);		// enable rx
			#endif
			#if (MX_UART_TX_EN_X == 1)
				set_bit(MX_UART_CH2_DEF.CTRLB, USART_TXEN_bp);		// enable tx
			#endif
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH2_EN;
		#else
			//MX_UART_INT_CH2_DIS;			//Don't disable UART RX INT here!
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 3)
		#ifndef MX_XMEGA
			UCSR2A = 0x00;						// clear all UCSRA flags
			UCSR2B = 0x00;						// clear all UCSRB flags

		  #ifdef UCSR2C
			#ifdef MX_UART_UCSRC
				UCSR2C = ((1 << UCSZ21) | (1 << UCSZ20));					// configuration for 8 data bits (Individual UCSRCx)
			#else
				UCSR2C = ((1 << URSEL) | (1 << UCSZ21) | (1 << UCSZ20));	// configuration for 8 data bits (Combined UBRRHx/UCSRCx)
			#endif
		  #endif

		  #if(MX_UART_DBITS_X == 9)
			set_bit(UCSR2B, UCSZ22);					// enable 9-bit mode
		  #endif

		  #ifdef UBRR
			UBRR = baudratel;						// same baudrate calculation as PIC
		  #else
			UBRR2L = baudratel;						// same baudrate calculation
			UBRR2H = baudrateh;						// as PIC
		  #endif

		  	#if (MX_UART_RX_EN_X == 1)
				set_bit(UCSR2B, RXEN2);				// enable rx
			#endif
			#if (MX_UART_TX_EN_X == 1)
				set_bit(UCSR2B, TXEN2);				// enable tx
			#endif
		#else
			MX_UART_CH3_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH3_DEF.CTRLB = 0x00;			// clear all UCSRB flags
			MX_UART_CH3_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

		  #if(MX_UART_DBITS_X == 9)
			set_bit(MX_UART_CH3_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
		  #endif

			MX_UART_CH3_DEF.BAUDCTRLA = baudratel;					// same baudrate calculation
			MX_UART_CH3_DEF.BAUDCTRLB = baudrateh;					// as PIC

			#if (MX_UART_RX_EN_X == 1)
				set_bit(MX_UART_CH3_DEF.CTRLB, USART_RXEN_bp);		// enable rx
			#endif
			#if (MX_UART_TX_EN_X == 1)
				set_bit(MX_UART_CH3_DEF.CTRLB, USART_TXEN_bp);		// enable tx
			#endif

		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH3_EN;
		#else
			//MX_UART_INT_CH3_DIS;			//Don't disable UART RX INT here!
		#endif
  	#endif

	#if (MX_UART_CHANNEL_X == 4)
		#ifndef MX_XMEGA
			UCSR3A = 0x00;						// clear all UCSRA flags
			UCSR3B = 0x00;						// clear all UCSRB flags

		  #ifdef UCSR3C
			#ifdef MX_UART_UCSRC
				UCSR3C = ((1 << UCSZ31) | (1 << UCSZ30));					// configuration for 8 data bits (Individual UCSRCx)
			#else
				UCSR3C = ((1 << URSEL) | (1 << UCSZ31) | (1 << UCSZ30));	// configuration for 8 data bits (Combined UBRRHx/UCSRCx)
			#endif
		  #endif

		  #if(MX_UART_DBITS_X == 9)
			set_bit(UCSR3B, UCSZ32);					// enable 9-bit mode
		  #endif

		  #ifdef UBRR
			UBRR = baudratel;						// same baudrate calculation as PIC
		  #else
			UBRR3L = baudratel;						// same baudrate calculation
			UBRR3H = baudrateh;						// as PIC
		  #endif

		  	#if (MX_UART_RX_EN_X == 1)
				set_bit(UCSR3B, RXEN3);					// enable rx
			#endif
			#if (MX_UART_TX_EN_X == 1)
				set_bit(UCSR3B, TXEN3);					// enable tx
			#endif

		#else
			MX_UART_CH4_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH4_DEF.CTRLB = 0x00;			// clear all UCSRB flags
			MX_UART_CH4_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

		  #if(MX_UART_DBITS_X == 9)
			set_bit(MX_UART_CH4_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
		  #endif

			MX_UART_CH4_DEF.BAUDCTRLA = baudratel;					// same baudrate calculation
			MX_UART_CH4_DEF.BAUDCTRLB = baudrateh;					// as PIC

			#if (MX_UART_RX_EN_X == 1)
				set_bit(MX_UART_CH4_DEF.CTRLB, USART_RXEN_bp);		// enable rx
			#endif
			#if (MX_UART_TX_EN_X == 1)
				set_bit(MX_UART_CH4_DEF.CTRLB, USART_TXEN_bp);		// enable tx
			#endif
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH4_EN;
		#else
			//MX_UART_INT_CH4_DIS;			//Don't disable UART RX INT here!
		#endif
  	#endif

	#if (MX_UART_CHANNEL_X == 5)
		#ifndef MX_XMEGA
		#else
			MX_UART_CH5_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH5_DEF.CTRLB = 0x00;			// clear all UCSRB flags
			MX_UART_CH5_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

		  #if(MX_UART_DBITS_X == 9)
			set_bit(MX_UART_CH5_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
		  #endif

			MX_UART_CH5_DEF.BAUDCTRLA = baudratel;					// same baudrate calculation
			MX_UART_CH5_DEF.BAUDCTRLB = baudrateh;					// as PIC

			#if (MX_UART_RX_EN_X == 1)
				set_bit(MX_UART_CH5_DEF.CTRLB, USART_RXEN_bp);		// enable rx
			#endif
			#if (MX_UART_TX_EN_X == 1)
				set_bit(MX_UART_CH5_DEF.CTRLB, USART_TXEN_bp);		// enable tx
			#endif
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH5_EN;
		#else
			//MX_UART_INT_CH5_DIS;			//Don't disable UART RX INT here!
		#endif
  	#endif

	#if (MX_UART_CHANNEL_X == 6)
		#ifndef MX_XMEGA
		#else
			MX_UART_CH6_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH6_DEF.CTRLB = 0x00;			// clear all UCSRB flags
			MX_UART_CH6_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

		  #if(MX_UART_DBITS_X == 9)
			set_bit(MX_UART_CH6_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
		  #endif

			MX_UART_CH6_DEF.BAUDCTRLA = baudratel;					// same baudrate calculation
			MX_UART_CH6_DEF.BAUDCTRLB = baudrateh;					// as PIC

			#if (MX_UART_RX_EN_X == 1)
				set_bit(MX_UART_CH6_DEF.CTRLB, USART_RXEN_bp);		// enable rx
			#endif
			#if (MX_UART_TX_EN_X == 1)
				set_bit(MX_UART_CH6_DEF.CTRLB, USART_TXEN_bp);		// enable tx
			#endif
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH6_EN;
		#else
			//MX_UART_INT_CH6_DIS;			//Don't disable UART RX INT here!
		#endif
  	#endif

	#if (MX_UART_CHANNEL_X == 7)
		#ifndef MX_XMEGA
		#else
			MX_UART_CH7_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH7_DEF.CTRLB = 0x00;			// clear all UCSRB flags
			MX_UART_CH7_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

		  #if(MX_UART_DBITS_X == 9)
			set_bit(MX_UART_CH7_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
		  #endif

			MX_UART_CH7_DEF.BAUDCTRLA = baudratel;					// same baudrate calculation
			MX_UART_CH7_DEF.BAUDCTRLB = baudrateh;					// as PIC

			#if (MX_UART_RX_EN_X == 1)
				set_bit(MX_UART_CH7_DEF.CTRLB, USART_RXEN_bp);		// enable rx
			#endif
			#if (MX_UART_TX_EN_X == 1)
				set_bit(MX_UART_CH7_DEF.CTRLB, USART_TXEN_bp);		// enable tx
			#endif
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH7_EN;
		#else
			//MX_UART_INT_CH7_DIS;			//Don't disable UART RX INT here!
		#endif
  	#endif

	#if (MX_UART_CHANNEL_X == 8)
		#ifndef MX_XMEGA
		#else
			MX_UART_CH8_DEF.CTRLA = 0x00;			// clear all UCSRA flags
			MX_UART_CH8_DEF.CTRLB = 0x00;			// clear all UCSRB flags
			MX_UART_CH8_DEF.CTRLC = 0x03;			// configuration for 8 data bits (Combined UBRRHx/UCSRCx)

		  #if(MX_UART_DBITS_X == 9)
			set_bit(MX_UART_CH8_DEF.CTRLC, USART_CHSIZE2_bp);		// enable 9-bit mode
		  #endif

			MX_UART_CH8_DEF.BAUDCTRLA = baudratel;					// same baudrate calculation
			MX_UART_CH8_DEF.BAUDCTRLB = baudrateh;					// as PIC

			#if (MX_UART_RX_EN_X == 1)
				set_bit(MX_UART_CH8_DEF.CTRLB, USART_RXEN_bp);		// enable rx
			#endif
			#if (MX_UART_TX_EN_X == 1)
				set_bit(MX_UART_CH8_DEF.CTRLB, USART_TXEN_bp);		// enable tx
			#endif
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH8_EN;
		#else
			//MX_UART_INT_CH8_DIS;			//Don't disable UART RX INT here!
		#endif
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


