// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B8478F634975A712457CCBE7D4DA9E6C832E5E803813867B467E404F6188BF6473796EDD611F6757020C3CAEE8E7DA6987DC91422B6D417712E2AA74B8685E70DD50F5461170B0B9852390AA046D66ACFB32E5EC698503976877A84CB7DB33151B43EAC6B4286DF4F2984BE375E41DAE5648E4C53B1E59D9DCE8B0A3982700B1CB01F4F23EDD068422549D34A0D5AD11F331564E06F5BEDA54926A33803AE5E3554B980F704361F56D61112B2378F6127E5D3A7ED706D09BBA
// REVISION: 7.0
// GUID: 6F111275-6289-45A2-A69E-BCAC05A73E5D
// DATE: 11\11\2025
// DIR: CAL\PIC\PIC_CAL_UART.c
/*********************************************************************
 *                  Flowcode CAL UART File
 *
 * File: PIC_CAL_UART.c
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
 * 011211 | BR | Converted to new dynamic defines mechanism
 * 160112 | BR | Fixed issues with rx return type and low bauds on fast devices
 * 020212 | ST | Added <MX_UART_2_PIE4> routing to account for differences in 16F and 18F devices with 2 UARTs
 * 270212 | BR | Fixed a bug in the receive functionality
 * 280212 | BR | Sorted out auto echo functionality
 * 160412 | BR | Addition of HW change baud function
 * 100912 | BR | Minor bug fix for UART 2 where PIR3 was referenced instead of definition
 * 240413 | LM | Fixed typo re PORT_1 -> PORT_X for Software UART
 * 030713 | LM | Standard API calls
 * 220713 | LM | Remappable registers to lower case (for @ defs)
 * 300914 | BR | Tried to make the baud calculation a bit more reliable for higher speed bauds at odd crystal frequencies
 * 161014 | LM | Register redefinitions (for PIC18F24K50)
 * 161014 | MW | Register definitions for PIC16F15XX
 */

#if (!defined(BAUDCON) && defined(_BAUD1CON_ABDEN_POSN))
	#define BAUDCON BAUD1CON
#endif
#if (!defined(RCSTA) && defined(_RC1STA_RX9D_POSN))
	#define RCSTA RC1STA
#endif
#if (!defined(SPBRG) && defined(_SPBRG1_SP1BRGL_POSN))
	#define SPBRG SPBRG1
#endif
#if (!defined(SPBRGH) && defined(_SPBRGH1_SP1BRGH_POSN))
	#define SPBRGH SPBRGH1
#endif
#if (!defined(TXREG) && defined(_TXREG1_TX1REG_POSN))
	#define TXREG TXREG1
#endif
#if (!defined(RCREG) && defined(_RCREG1_RC1REG_POSN))
	#define RCREG RCREG1
#endif
#if (!defined(TXSTA) && defined(_TXSTA1_TX9D_POSN))
	#define TXSTA TXSTA1
#endif

#if (!defined(TXSTA2) && defined(_TX2STA_TX9D_POSN))
	#define TXSTA2 TX2STA
#endif
#if (!defined(RCSTA2) && defined(_RC2STA_RX9D_POSN))
	#define RCSTA2 RC2STA
#endif
#if (!defined(TXREG2) && defined(_TX2REG_TXREG_POSN))
	#define TXREG2 TX2REG
#endif
#if (!defined(RCREG2) && defined(_RC2REG_RCREG_POSN))
	#define RCREG2 RC2REG
#endif

//18F26K42 has a totally new UART register setup.
#ifdef U1CON0
	#define UALTREG
#endif

//PIC16F15XX has a different UART register setup.
#ifdef U1RXPPS
	#define UALTREG1
#endif



#ifndef MX_UART_SW_DEFS
	#define MX_UART_SW_DEFS

	//#ifdef _BOOSTC
	//	#define INST_COUNT	45	//65 for lower speeds or 40 for higher speeds.
	//#endif
	//#ifdef HI_TECH_C
	//	#define INST_COUNT	315
	//#endif

	//XC8 - working at 145 - 150 for 9600baud 16F1937 @ 19.6608MHz
	//XC8 - working at 135 for 19200baud 16F1937 @ 19.6608MHz

	#define INST_COUNT	148

	//Work out number of nops for software baud rate
	#define MX_INSTRUCTION_SPEED 	(MX_CLK_SPEED / 4)
	#define MX_OVERHEAD				(MX_INSTRUCTION_SPEED / INST_COUNT)
	#define SW_OFFSET				(1000000 / MX_OVERHEAD)

#endif


//Hardware Baud update definitions
#ifndef MX_HARD_BAUD_CHANGE_DEFS
	#define MX_HARD_BAUD_CHANGE_DEFS

	#ifdef UALTREG

		#define MX_HARD_BAUD_1200	(((MX_CLK_SPEED / 1200) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_1200 > 65535)
			#undef MX_HARD_BAUD_1200
			#define MX_HARD_BAUD_1200	(((MX_CLK_SPEED / 1200) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_1200	1
		#else
			#define MX_HARD_SLOW_1200	0
		#endif

		#define MX_HARD_BAUD_2400	(((MX_CLK_SPEED / 2400) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_2400 > 65535)
			#undef MX_HARD_BAUD_2400
			#define MX_HARD_BAUD_2400	(((MX_CLK_SPEED / 2400) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_2400	1
		#else
			#define MX_HARD_SLOW_2400	0
		#endif

		#define MX_HARD_BAUD_4800	(((MX_CLK_SPEED / 4800) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_4800 > 65535)
			#undef MX_HARD_BAUD_4800
			#define MX_HARD_BAUD_4800	(((MX_CLK_SPEED / 4800) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_4800	1
		#else
			#define MX_HARD_SLOW_4800	0
		#endif

		#define MX_HARD_BAUD_9600	(((MX_CLK_SPEED / 9600) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_9600 > 65535)
			#undef MX_HARD_BAUD_9600
			#define MX_HARD_BAUD_9600	(((MX_CLK_SPEED / 9600) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_9600	1
		#else
			#define MX_HARD_SLOW_9600	0
		#endif

		#define MX_HARD_BAUD_19200	(((MX_CLK_SPEED / 19200) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_19200 > 65535)
			#undef MX_HARD_BAUD_19200
			#define MX_HARD_BAUD_19200	(((MX_CLK_SPEED / 19200) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_19200	1
		#else
			#define MX_HARD_SLOW_19200	0
		#endif

		#define MX_HARD_BAUD_38400	(((MX_CLK_SPEED / 38400) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_38400 > 65535)
			#undef MX_HARD_BAUD_38400
			#define MX_HARD_BAUD_38400	(((MX_CLK_SPEED / 38400) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_38400	1
		#else
			#define MX_HARD_SLOW_38400	0
		#endif

		#define MX_HARD_BAUD_57600	(((MX_CLK_SPEED / 57600) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_57600 > 65535)
			#undef MX_HARD_BAUD_57600
			#define MX_HARD_BAUD_57600	(((MX_CLK_SPEED / 57600) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_57600	1
		#else
			#define MX_HARD_SLOW_57600	0
		#endif

		#define MX_HARD_BAUD_115200	(((MX_CLK_SPEED / 115200) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_115200 > 65535)
			#undef MX_HARD_BAUD_115200
			#define MX_HARD_BAUD_115200	(((MX_CLK_SPEED / 115200) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_115200	1
		#else
			#define MX_HARD_SLOW_115200	0
		#endif

		#define MX_HARD_BAUD_250000	(((MX_CLK_SPEED / 250000) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_250000 > 65535)
			#undef MX_HARD_BAUD_250000
			#define MX_HARD_BAUD_250000	(((MX_CLK_SPEED / 250000) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_250000	1
		#else
			#define MX_HARD_SLOW_250000	0
		#endif

	#elif defined(UALTREG1)

		#define MX_HARD_BAUD_1200	(((MX_CLK_SPEED / 1200) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_1200 > 65535)
			#undef MX_HARD_BAUD_1200
			#define MX_HARD_BAUD_1200	(((MX_CLK_SPEED / 1200) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_1200	1
		#else
			#define MX_HARD_SLOW_1200	0
		#endif

		#define MX_HARD_BAUD_2400	(((MX_CLK_SPEED / 2400) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_2400 > 65535)
			#undef MX_HARD_BAUD_2400
			#define MX_HARD_BAUD_2400	(((MX_CLK_SPEED / 2400) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_2400	1
		#else
			#define MX_HARD_SLOW_2400	0
		#endif

		#define MX_HARD_BAUD_4800	(((MX_CLK_SPEED / 4800) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_4800 > 65535)
			#undef MX_HARD_BAUD_4800
			#define MX_HARD_BAUD_4800	(((MX_CLK_SPEED / 4800) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_4800	1
		#else
			#define MX_HARD_SLOW_4800	0
		#endif

		#define MX_HARD_BAUD_9600	(((MX_CLK_SPEED / 9600) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_9600 > 65535)
			#undef MX_HARD_BAUD_9600
			#define MX_HARD_BAUD_9600	(((MX_CLK_SPEED / 9600) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_9600	1
		#else
			#define MX_HARD_SLOW_9600	0
		#endif

		#define MX_HARD_BAUD_19200	(((MX_CLK_SPEED / 19200) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_19200 > 65535)
			#undef MX_HARD_BAUD_19200
			#define MX_HARD_BAUD_19200	(((MX_CLK_SPEED / 19200) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_19200	1
		#else
			#define MX_HARD_SLOW_19200	0
		#endif

		#define MX_HARD_BAUD_38400	(((MX_CLK_SPEED / 38400) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_38400 > 65535)
			#undef MX_HARD_BAUD_38400
			#define MX_HARD_BAUD_38400	(((MX_CLK_SPEED / 38400) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_38400	1
		#else
			#define MX_HARD_SLOW_38400	0
		#endif

		#define MX_HARD_BAUD_57600	(((MX_CLK_SPEED / 57600) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_57600 > 65535)
			#undef MX_HARD_BAUD_57600
			#define MX_HARD_BAUD_57600	(((MX_CLK_SPEED / 57600) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_57600	1
		#else
			#define MX_HARD_SLOW_57600	0
		#endif

		#define MX_HARD_BAUD_115200	(((MX_CLK_SPEED / 115200) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_115200 > 65535)
			#undef MX_HARD_BAUD_115200
			#define MX_HARD_BAUD_115200	(((MX_CLK_SPEED / 115200) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_115200	1
		#else
			#define MX_HARD_SLOW_115200	0
		#endif

		#define MX_HARD_BAUD_250000	(((MX_CLK_SPEED / 250000) - 2) / 4)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_250000 > 65535)
			#undef MX_HARD_BAUD_250000
			#define MX_HARD_BAUD_250000	(((MX_CLK_SPEED / 250000) - 8) / 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_250000	1
		#else
			#define MX_HARD_SLOW_250000	0
		#endif


	#else

		#define MX_HARD_BAUD_1200	(((MX_CLK_SPEED / 1200) - 8) / 16)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_1200 > 255)
			#undef MX_HARD_BAUD_1200
			#define MX_HARD_BAUD_1200	(((MX_CLK_SPEED / 1200) - 8) / 64)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_1200	1
		#else
			#define MX_HARD_SLOW_1200	0
		#endif

		#define MX_HARD_BAUD_2400	(((MX_CLK_SPEED / 2400) - 8) / 16)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_2400 > 255)
			#undef MX_HARD_BAUD_2400
			#define MX_HARD_BAUD_2400	(((MX_CLK_SPEED / 2400) - 8) / 64)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_2400	1
		#else
			#define MX_HARD_SLOW_2400	0
		#endif

		#define MX_HARD_BAUD_4800	(((MX_CLK_SPEED / 4800) - 8) / 16)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_4800 > 255)
			#undef MX_HARD_BAUD_4800
			#define MX_HARD_BAUD_4800	(((MX_CLK_SPEED / 4800) - 8) / 64)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_4800	1
		#else
			#define MX_HARD_SLOW_4800	0
		#endif

		#define MX_HARD_BAUD_9600	(((MX_CLK_SPEED / 9600) - 8) / 16)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_9600 > 255)
			#undef MX_HARD_BAUD_9600
			#define MX_HARD_BAUD_9600	(((MX_CLK_SPEED / 9600) - 8) / 64)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_9600	1
		#else
			#define MX_HARD_SLOW_9600	0
		#endif

		#define MX_HARD_BAUD_19200	(((MX_CLK_SPEED / 19200) - 8) / 16)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_19200 > 255)
			#undef MX_HARD_BAUD_19200
			#define MX_HARD_BAUD_19200	(((MX_CLK_SPEED / 19200) - 8) / 64)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_19200	1
		#else
			#define MX_HARD_SLOW_19200	0
		#endif

		#define MX_HARD_BAUD_38400	(((MX_CLK_SPEED / 38400) - 8) / 16)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_38400 > 255)
			#undef MX_HARD_BAUD_38400
			#define MX_HARD_BAUD_38400	(((MX_CLK_SPEED / 38400) - 8) / 64)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_38400	1
		#else
			#define MX_HARD_SLOW_38400	0
		#endif

		#define MX_HARD_BAUD_57600	(((MX_CLK_SPEED / 57600) - 8) / 16)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_57600 > 255)
			#undef MX_HARD_BAUD_57600
			#define MX_HARD_BAUD_57600	(((MX_CLK_SPEED / 57600) - 8) / 64)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_57600	1
		#else
			#define MX_HARD_SLOW_57600	0
		#endif

		#define MX_HARD_BAUD_115200	(((MX_CLK_SPEED / 115200) - 8) / 16)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_115200 > 255)
			#undef MX_HARD_BAUD_115200
			#define MX_HARD_BAUD_115200	(((MX_CLK_SPEED / 115200) - 8) / 64)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_115200	1
		#else
			#define MX_HARD_SLOW_115200	0
		#endif

		#define MX_HARD_BAUD_250000	(((MX_CLK_SPEED / 250000) - 8) / 16)		//Was - 16 but had issues with rounding down
		#if (MX_HARD_BAUD_250000 > 255)
			#undef MX_HARD_BAUD_250000
			#define MX_HARD_BAUD_250000	(((MX_CLK_SPEED / 250000) - 8) / 64)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_250000	1
		#else
			#define MX_HARD_SLOW_250000	0
		#endif

	#endif

#endif

#define MX_RECEIVE_DELAY 	(MX_CLK_SPEED / 4000000)


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
#define UART_Send			CAL_APPEND(FC_CAL_UART_Send_, MX_UART_NUM)
#define UART_Uninit			CAL_APPEND(FC_CAL_UART_Uninit_, MX_UART_NUM)



#if (MX_UART_CHANNEL_X == 0)

	#define MX_SOFT_BAUD_X (1000000 / MX_UART_BAUD_X) - SW_OFFSET

	#if (MX_SOFT_BAUD_X < 1)
		#error "Software UART Baud Rate Not Available At This Clock Speed"
	#endif

#else

	#ifdef UALTREG

		#define MX_SOFT_BAUD_X	1
		#define MX_HARD_BAUD_X	(((MX_CLK_SPEED / MX_UART_BAUD_X) - 2) / 4)		//Was - 16 but had issues with rounding down
		#define MX_HARD_SLOW_X	0

		#if (MX_HARD_BAUD_X > 255)

			//UART BAUD switching to slow mode to generate user selected BAUD.

			#undef MX_HARD_BAUD_X
			#undef MX_HARD_SLOW_X

			#define MX_HARD_BAUD_X	(((MX_CLK_SPEED / MX_UART_BAUD_X) - 8)	/ 16)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_X	1

			#if (MX_HARD_BAUD_X > 65535)

				//UART BAUD cannot be acheived even in slow mode.
				#warning "The baud rate you have entered cannot be reached (too slow for crystal speed)"

			#endif
		#endif

	#else

		#define MX_SOFT_BAUD_X	1
		#define MX_HARD_BAUD_X	(((MX_CLK_SPEED / MX_UART_BAUD_X) - 8) / 16)		//Was - 16 but had issues with rounding down
		#define MX_HARD_SLOW_X	0

		#if (MX_HARD_BAUD_X > 255)

			//UART BAUD switching to slow mode to generate user selected BAUD.

			#undef MX_HARD_BAUD_X
			#undef MX_HARD_SLOW_X

			#define MX_HARD_BAUD_X	(((MX_CLK_SPEED / MX_UART_BAUD_X) - 8)	/ 64)		//Was - 16 but had issues with rounding down
			#define MX_HARD_SLOW_X	1

			#if (MX_HARD_BAUD_X > 255)

				//UART BAUD cannot be acheived even in slow mode.
				#warning "The baud rate you have entered cannot be reached (too slow for crystal speed)"

			#endif
		#endif
	#endif

#endif



//Component Definitions
#define UART_STATUS_LOOP	0
#define UART_STATUS_TIMEOUT	1
#define UART_STATUS_RXBYTE	2


#ifdef _PIE3_RC1IE_POSN
	#define _PIE3_RCIE_POSN
	#define RCIE RC1IE
	#define RCIF RC1IF
	#define TXIF TX1IF
#endif

#ifdef _PIE3_U1RXIE_POSN
	#define _PIE3_RCIE_POSN
	#define RCIE U1RXIE
	#define RCIF U1RXIF
	#define TXIF U1TXIF
	#define RC2IE U2RXIE
	#define RC2IF U2RXIF
#endif


#ifdef _PIE3_RCIE_POSN
  #define MX_UART1_PIE PIE3
  #define MX_UART1_PIR PIR3
#else
  #define MX_UART1_PIE PIE1
  #define MX_UART1_PIR PIR1
#endif


//Interrupt Definitions
#ifdef MX_UART_2_PIE4
  #define MX_UART2_PIE PIE4
  #define MX_UART2_PIR PIR4
  #define MX_UART2_TXSTA TX2STA
  #define MX_UART2_RCSTA RC2STA
  #define MX_UART2_TXREG TX2REG
  #define MX_UART2_RCREG RC2REG
#else
  #ifdef _PIE6_U2RXIE_POSN
    #define MX_UART2_PIE PIE6
    #define MX_UART2_PIR PIR6
    #define MX_UART2_TXSTA TXSTA2
    #define MX_UART2_RCSTA RCSTA2
    #define MX_UART2_TXREG TXREG2
    #define MX_UART2_RCREG RCREG2
  #else
    #define MX_UART2_PIE PIE3
    #define MX_UART2_PIR PIR3
    #define MX_UART2_TXSTA TXSTA2
    #define MX_UART2_RCSTA RCSTA2
    #define MX_UART2_TXREG TXREG2
    #define MX_UART2_RCREG RCREG2
  #endif
#endif

// might need more family tinkering ...
// EUSART 3
  #define MX_UART3_PIE PIE4
  #define MX_UART3_PIR PIR4
  #define MX_UART3_TXSTA TX3STA
  #define MX_UART3_RCSTA RC3STA
  #define MX_UART3_TXREG TX3REG
  #define MX_UART3_RCREG RC3REG
// EUSART 4
  #define MX_UART4_PIE PIE4
  #define MX_UART4_PIR PIR4
  #define MX_UART4_TXSTA TX4STA
  #define MX_UART4_RCSTA RC4STA
  #define MX_UART4_TXREG TX4REG
  #define MX_UART4_RCREG RC4REG
// EUSART 5
  #define MX_UART5_PIE PIE4
  #define MX_UART5_PIR PIR4
  #define MX_UART5_TXSTA TX5STA
  #define MX_UART5_RCSTA RC5STA
  #define MX_UART5_TXREG TX5REG
  #define MX_UART5_RCREG RC5REG



#ifndef MX_UART_INT_DEFS
#define MX_UART_INT_DEFS

	#define MX_UART_INT_CH1_FUNC
	#define MX_UART_INT_CH2_FUNC
	#define MX_UART_INT_CH3_FUNC
	#define MX_UART_INT_CH4_FUNC
	#define MX_UART_INT_CH5_FUNC

	#define MX_UART_INT_FUNC_END

	#ifdef UALTREG										//New 18FxxK42 PIC Register Setup

		#ifdef _PIE3_U1RXIE_POSN
			#define MX_UART_INT_CH1_DET		ts_bit(PIR3, U1RXIF) && ts_bit(PIE3, U1RXIE)
			#define MX_UART_INT_CH1_EN		st_bit (PIE3, U1RXIE)
			#define MX_UART_INT_CH1_DIS		cr_bit (PIE3, U1RXIE)
			#define MX_UART_INT_CH1_CLR		cr_bit (PIR3, U1RXIF)
		#endif
		#ifdef _PIE4_U1RXIE_POSN
			#define MX_UART_INT_CH1_DET		ts_bit(PIR4, U1RXIF) && ts_bit(PIE4, U1RXIE)
			#define MX_UART_INT_CH1_EN		st_bit (PIE4, U1RXIE)
			#define MX_UART_INT_CH1_DIS		cr_bit (PIE4, U1RXIE)
			#define MX_UART_INT_CH1_CLR		cr_bit (PIR4, U1RXIF)
		#endif

		#ifdef _PIE6_U2RXIE_POSN
			#define MX_UART_INT_CH2_DET		ts_bit(PIR6, U2RXIF) && ts_bit(PIE6, U2RXIE)
			#define MX_UART_INT_CH2_EN		st_bit (PIE6, U2RXIE)
			#define MX_UART_INT_CH2_DIS		cr_bit (PIE6, U2RXIE)
			#define MX_UART_INT_CH2_CLR		cr_bit (PIR6, U2RXIF)
		#endif
		#ifdef _PIE8_U2RXIE_POSN
			#define MX_UART_INT_CH2_DET		ts_bit(PIR8, U2RXIF) && ts_bit(PIE8, U2RXIE)
			#define MX_UART_INT_CH2_EN		st_bit (PIE8, U2RXIE)
			#define MX_UART_INT_CH2_DIS		cr_bit (PIE8, U2RXIE)
			#define MX_UART_INT_CH2_CLR		cr_bit (PIR8, U2RXIF)
		#endif

		#ifdef _PIE9_U3RXIE_POSN
			#define MX_UART_INT_CH3_DET		ts_bit(PIR9, U3RXIF) && ts_bit(PIE9, U3RXIE)
			#define MX_UART_INT_CH3_EN		st_bit (PIE9, U3RXIE)
			#define MX_UART_INT_CH3_DIS		cr_bit (PIE9, U3RXIE)
			#define MX_UART_INT_CH3_CLR		cr_bit (PIR9, U3RXIF)
		#endif

		#ifdef _PIE12_U4RXIE_POSN
			#define MX_UART_INT_CH4_DET		ts_bit(PIR12, U4RXIF) && ts_bit(PIE12, U4RXIE)
			#define MX_UART_INT_CH4_EN		st_bit (PIE12, U4RXIE)
			#define MX_UART_INT_CH4_DIS		cr_bit (PIE12, U4RXIE)
			#define MX_UART_INT_CH4_CLR		cr_bit (PIR12, U4RXIF)
		#endif

		#ifdef _PIE13_U5RXIE_POSN
			#define MX_UART_INT_CH5_DET		ts_bit(PIR13, U5RXIF) && ts_bit(PIE13, U5RXIE)
			#define MX_UART_INT_CH5_EN		st_bit (PIE13, U5RXIE)
			#define MX_UART_INT_CH5_DIS		cr_bit (PIE13, U5RXIE)
			#define MX_UART_INT_CH5_CLR		cr_bit (PIR13, U5RXIF)
		#endif

	#else

		#define MX_UART_INT_CH1_DET		ts_bit(MX_UART1_PIR, RCIF) && ts_bit(MX_UART1_PIE, RCIE)
		#define MX_UART_INT_CH2_DET		ts_bit(MX_UART2_PIR, RC2IF) && ts_bit(MX_UART2_PIE, RC2IE)
		#define MX_UART_INT_CH3_DET		ts_bit(MX_UART3_PIR, RC3IF) && ts_bit(MX_UART3_PIE, RC3IE)
		#define MX_UART_INT_CH4_DET		ts_bit(MX_UART4_PIR, RC4IF) && ts_bit(MX_UART4_PIE, RC4IE)
		#define MX_UART_INT_CH5_DET		ts_bit(MX_UART5_PIR, RC5IF) && ts_bit(MX_UART5_PIE, RC5IE)

		#define MX_UART_INT_CH1_EN		st_bit (MX_UART1_PIE, RCIE)
		#define MX_UART_INT_CH2_EN		st_bit (MX_UART2_PIE, RC2IE)
		#define MX_UART_INT_CH3_EN		st_bit (MX_UART3_PIE, RC3IE)
		#define MX_UART_INT_CH4_EN		st_bit (MX_UART4_PIE, RC4IE)
		#define MX_UART_INT_CH5_EN		st_bit (MX_UART5_PIE, RC5IE)

		#define MX_UART_INT_CH1_DIS		cr_bit (MX_UART1_PIE, RCIE)
		#define MX_UART_INT_CH2_DIS		cr_bit (MX_UART2_PIE, RC2IE)
		#define MX_UART_INT_CH3_DIS		cr_bit (MX_UART3_PIE, RC3IE)
		#define MX_UART_INT_CH4_DIS		cr_bit (MX_UART4_PIE, RC4IE)
		#define MX_UART_INT_CH5_DIS		cr_bit (MX_UART5_PIE, RC5IE)

		#define MX_UART_INT_CH1_CLR		cr_bit (MX_UART1_PIR, RCIF)
		#define MX_UART_INT_CH2_CLR		cr_bit (MX_UART2_PIR, RC2IF)
		#define MX_UART_INT_CH3_CLR		cr_bit (MX_UART3_PIR, RC3IF)
		#define MX_UART_INT_CH4_CLR		cr_bit (MX_UART4_PIR, RC4IF)
		#define MX_UART_INT_CH5_CLR		cr_bit (MX_UART5_PIR, RC5IF)

	#endif
#endif


//Function Prototypes
CALFUNCTION(void, FC_CAL_UART_Init_, (void));
CALFUNCTION(void, FC_CAL_UART_Uninit_, (void));
CALFUNCTION(void, FC_CAL_UART_Send_, (MX_UINT16 nChar));
CALFUNCTION(MX_SINT16, FC_CAL_UART_Receive_, (MX_UINT8 nTimeout));
CALFUNCTION(void, FC_CAL_UART_Delay_, (void));
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

		#ifdef MX_UART_1_REMAPPABLE						//Setup Remappable I/O
			#if (MX_UART_TX_EN_X == 1)
				MX_UART_1_TX_RPOR = MX_UART_1_TX_UTX;
			#endif
			#if (MX_UART_RX_EN_X == 1)
				MX_UART_1_RX_RPINR = MX_UART_1_RX_RP;
			#endif
		#endif

		#ifdef MX_UART_1_TX_ALT							//Setup Alt I/O
			#if (MX_UART_TX_EN_X == 1)
		  		MX_UART_1_TX_ALT;
		  	#endif
		#endif
		#ifdef MX_UART_1_RX_ALT
			#if (MX_UART_RX_EN_X == 1)
			  	MX_UART_1_RX_ALT;
			#endif
		#endif

		#ifdef UALTREG										//New 18FxxK42 PIC Register Setup

			#if (MX_HARD_SLOW_X == 1)
				cr_bit(U1CON0, BRGS);						//Low Speed
			#else
				st_bit(U1CON0, BRGS);						//High Speed
			#endif

			U1BRGL = MX_HARD_BAUD_X;   						// set the baud rate
			U1BRGH = MX_HARD_BAUD_X >> 8;   				// set the baud rate

			#if(MX_UART_DBITS_X == 9)
				st_bit(U1CON0, 2);   						// 9-bit TX&RX
			#endif

			st_bit(U1CON1, ON);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(U1CON0, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(U1CON0, RXEN);
			#endif

			#if (MX_UART_INT_X == 1)
				#ifdef _PIE3_U1RXIE_POSN
					st_bit (PIE3, U1RXIE);
				#endif
				#ifdef _PIE4_U1RXIE_POSN
					st_bit (PIE3, U1RXIE);
				#endif

				//st_bit(INTCON, PEIE);
				st_bit(INTCON0, GIE);
			#else
				#ifdef _PIE3_U1RXIE_POSN
					cr_bit (PIE3, U1RXIE);
				#endif
				#ifdef _PIE4_U1RXIE_POSN
					cr_bit (PIE4, U1RXIE);
				#endif
			#endif


	#elif defined(UALTREG1)									//New PIC16F15XX PIC Register Setup

			#if (MX_HARD_SLOW_X == 1)
				cr_bit(U1CON0, BRGS);						//Low Speed
			#else
				st_bit(U1CON0, BRGS);						//High Speed
			#endif

			U1BRGL = MX_HARD_BAUD_X;   						// set the baud rate
			U1BRGH = MX_HARD_BAUD_X >> 8;   				// set the baud rate

			#if(MX_UART_DBITS_X == 9)
				st_bit(U1CON0, 2);   						// 9-bit TX&RX
			#endif

			st_bit(U1CON1, ON);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(U1CON0, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(U1CON0, RXEN);
			#endif

			#if (MX_UART_INT_X == 1)
				#ifdef _PIE3_U1RXIE_POSN
					st_bit (PIE3, U1RXIE);
				#endif
				#ifdef _PIE4_U1RXIE_POSN
					st_bit (PIE4, U1RXIE);
				#endif

				//st_bit(INTCON, PEIE);
				st_bit(INTCON0, GIE);
			#else
				#ifdef _PIE3_U1RXIE_POSN
					cr_bit (PIE3, U1RXIE);
				#endif
				#ifdef _PIE4_U1RXIE_POSN
					cr_bit (PIE4, U1RXIE);
				#endif
			#endif

		#else												//Normal PIC Register Setup

			#if (MX_HARD_SLOW_X == 1)
				cr_bit(TXSTA, BRGH);						//Low Speed
			#else
				st_bit(TXSTA, BRGH);						//High Speed
			#endif

			#ifdef _BAUD1CON_BRG16_POSN
				BAUD1CON = 0;
			#endif

			SPBRG = MX_HARD_BAUD_X;   						// set the baud rate
			RCSTA = 0;                    					// 8-bit, disabled

			#if(MX_UART_DBITS_X == 9)
				#if (MX_UART_TX_EN_X == 1)
					st_bit(TXSTA, TX9);   					// 9-bit TX
				#endif
				#if (MX_UART_RX_EN_X == 1)
					st_bit(RCSTA, RX9);                		// 9-bit RX
				#endif
			#endif

			st_bit(RCSTA, SPEN);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(TXSTA, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(RCSTA, CREN);
			#endif

			#if (MX_UART_INT_X == 1)
				MX_UART_INT_CH1_EN;
				st_bit(INTCON, PEIE);
				st_bit(INTCON, GIE);
			#else
				cr_bit (MX_UART1_PIE, RCIE);
			#endif

		#endif

	#endif


	#if (MX_UART_CHANNEL_X == 2)

		#ifdef MX_UART_2_REMAPPABLE
			#if (MX_UART_TX_EN_X == 1)
				MX_UART_2_TX_RPOR = MX_UART_2_TX_UTX;
			#endif
			#if (MX_UART_RX_EN_X == 1)
				MX_UART_2_RX_RPINR = MX_UART_2_RX_RP;
			#endif
		#endif

		#ifdef MX_UART_2_TX_ALT						//Setup Alt I/O
			#if (MX_UART_TX_EN_X == 1)
			  	MX_UART_2_TX_ALT;
			#endif
		#endif
		#ifdef MX_UART_2_RX_ALT
			#if (MX_UART_RX_EN_X == 1)
			  	MX_UART_2_RX_ALT;
			#endif
		#endif

		#ifdef UALTREG										//New 18FxxK42 PIC Register Setup

			#if (MX_HARD_SLOW_X == 1)
				cr_bit(U2CON0, BRGS);						//Low Speed
			#else
				st_bit(U2CON0, BRGS);						//High Speed
			#endif

			U2BRGL = MX_HARD_BAUD_X;   						// set the baud rate
			U2BRGH = MX_HARD_BAUD_X >> 8;   				// set the baud rate

			#if(MX_UART_DBITS_X == 9)
				st_bit(U2CON0, 2);   						// 9-bit TX&RX
			#endif

			st_bit(U2CON1, ON);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(U2CON0, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(U2CON0, RXEN);
			#endif

			#if (MX_UART_INT_X == 1)
				#ifdef _PIE6_U2RXIE_POSN
					st_bit (PIE6, U2RXIE);
				#endif
				#ifdef _PIE8_U2RXIE_POSN
					st_bit (PIE8, U2RXIE);
				#endif

				//st_bit(INTCON, PEIE);
				st_bit(INTCON0, GIE);
			#else
				#ifdef _PIE6_U2RXIE_POSN
					cr_bit (PIE6, U2RXIE);
				#endif
				#ifdef _PIE8_U2RXIE_POSN
					cr_bit (PIE8, U2RXIE);
				#endif
			#endif
		#elif defined(UALTREG1)									//New PIC16F15XX PIC Register Setup

			#if (MX_HARD_SLOW_X == 1)
				cr_bit(U2CON0, BRGS);						//Low Speed
			#else
				st_bit(U2CON0, BRGS);						//High Speed
			#endif

			U2BRGL = MX_HARD_BAUD_X;   						// set the baud rate
			U2BRGH = MX_HARD_BAUD_X >> 8;   				// set the baud rate

			#if(MX_UART_DBITS_X == 9)
				st_bit(U2CON0, 2);   						// 9-bit TX&RX
			#endif

			st_bit(U2CON1, ON);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(U2CON0, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(U2CON0, RXEN);
			#endif

			#if (MX_UART_INT_X == 1)
				#ifdef _PIE6_U2RXIE_POSN
					st_bit (PIE6, U2RXIE);
				#endif
				#ifdef _PIE8_U2RXIE_POSN
					st_bit (PIE8, U2RXIE);
				#endif

				//st_bit(INTCON, PEIE);
				st_bit(INTCON0, GIE);
			#else
				#ifdef _PIE6_U2RXIE_POSN
					cr_bit (PIE6, U2RXIE);
				#endif
				#ifdef _PIE8_U2RXIE_POSN
					cr_bit (PIE8, U2RXIE);
				#endif
			#endif

		#else												//Normal PIC Register Setup

			#if (MX_HARD_SLOW_X == 1)
				cr_bit(MX_UART2_TXSTA, BRGH);			//Low Speed
			#else
				st_bit(MX_UART2_TXSTA, BRGH);			//High Speed
			#endif

			#ifdef _BAUD2CON_BRG16_POSN
				BAUD2CON = 0;
			#endif

			SPBRG2 = MX_HARD_BAUD_X;   					// set the baud rate
			MX_UART2_RCSTA = 0;                    		// 8-bit, disabled

			#if(MX_UART_DBITS_X == 9)
				#if (MX_UART_TX_EN_X == 1)
					st_bit(MX_UART2_TXSTA, TX9);   		// 9-bit TX
				#endif
				#if (MX_UART_RX_EN_X == 1)
					st_bit(MX_UART2_RCSTA, RX9);        // 9-bit RX
				#endif
			#endif

			st_bit(MX_UART2_RCSTA, SPEN);         		// turn on serial interface
			#if (MX_UART_TX_EN_X == 1)
				st_bit(MX_UART2_TXSTA, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(MX_UART2_RCSTA, CREN);
			#endif

			#if (MX_UART_INT_X == 1)
				MX_UART_INT_CH2_EN;
				st_bit(INTCON, PEIE);
				st_bit(INTCON, GIE);
			#else
				cr_bit (MX_UART2_PIE, RC2IE);
			#endif

		#endif

	#endif

	#if (MX_UART_CHANNEL_X == 3)

		#ifdef MX_UART_3_REMAPPABLE
		  	#if (MX_UART_TX_EN_X == 1)
				MX_UART_3_TX_RPOR = MX_UART_3_TX_UTX;
			#endif
			#if (MX_UART_RX_EN_X == 1)
				MX_UART_3_RX_RPINR = MX_UART_3_RX_RP;
			#endif
		  #endif

		#ifdef MX_UART_3_TX_ALT						//Setup Alt I/O
			#if (MX_UART_TX_EN_X == 1)
			  	MX_UART_3_TX_ALT;
			#endif
		#endif
		#ifdef MX_UART_3_RX_ALT
			#if (MX_UART_RX_EN_X == 1)
			 	MX_UART_3_RX_ALT;
			 #endif
		#endif

		#ifdef UALTREG										//New 18FxxK42 PIC Register Setup

			#if (MX_HARD_SLOW_X == 1)
				cr_bit(U3CON0, BRGS);						//Low Speed

		#elif defined(UALTREG1)									//New PIC16F15XX PIC Register Setup

			#if (MX_HARD_SLOW_X == 1)
				cr_bit(U3CON0, BRGS);						//Low Speed
			#else
				st_bit(U3CON0, BRGS);						//High Speed
			#endif

			U3BRGL = MX_HARD_BAUD_X;   						// set the baud rate
			U3BRGH = MX_HARD_BAUD_X >> 8;   				// set the baud rate

			#if(MX_UART_DBITS_X == 9)
				st_bit(U3CON0, 2);   						// 9-bit TX&RX
			#endif

			st_bit(U3CON1, ON);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(U3CON0, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(U3CON0, RXEN);
			#endif

			#if (MX_UART_INT_X == 1)
				#ifdef _PIE9_U3RXIE_POSN
					st_bit (PIE9, U3RXIE);
				#endif
				#ifdef _PIE9_U3RXIE_POSN
					st_bit (PIE9, U3RXIE);
				#endif

				//st_bit(INTCON, PEIE);
				st_bit(INTCON0, GIE);
			#else
				#ifdef _PIE9_U3RXIE_POSN
					cr_bit (PIE9, U3RXIE);
				#endif
				#ifdef _PIE9_U3RXIE_POSN
					cr_bit (PIE9, U3RXIE);
				#endif
			#endif
			#else
				st_bit(U3CON0, BRGS);						//High Speed
			#endif

			U3BRGL = MX_HARD_BAUD_X;   						// set the baud rate
			U3BRGH = MX_HARD_BAUD_X >> 8;   				// set the baud rate

			#if(MX_UART_DBITS_X == 9)
				st_bit(U3CON0, 2);   						// 9-bit TX&RX
			#endif

			st_bit(U3CON1, ON);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(U3CON0, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(U3CON0, RXEN);
			#endif

			#if (MX_UART_INT_X == 1)
				#ifdef _PIE9_U3RXIE_POSN
					st_bit (PIE9, U3RXIE);
				#endif

				//st_bit(INTCON, PEIE);
				st_bit(INTCON0, GIE);
			#else
				#ifdef _PIE9_U3RXIE_POSN
					cr_bit (PIE9, U3RXIE);
				#endif
			#endif

		#else												//Normal PIC Register Setup

			#if (MX_HARD_SLOW_X == 1)
				cr_bit(MX_UART3_TXSTA, BRGH);			//Low Speed
			#else
				st_bit(MX_UART3_TXSTA, BRGH);			//High Speed
			#endif

			#ifdef _BAUD3CON_BRG16_POSN
				BAUD3CON = 0;
			#endif

			SPBRG3 = MX_HARD_BAUD_X;   					// set the baud rate
			MX_UART3_RCSTA = 0;                    		// 8-bit, disabled

			#if(MX_UART_DBITS_X == 9)
				#if (MX_UART_TX_EN_X == 1)
					st_bit(MX_UART3_TXSTA, TX9);   		// 9-bit TX
				#endif
				#if (MX_UART_RX_EN_X == 1)
					st_bit(MX_UART3_RCSTA, RX9);        // 9-bit RX
				#endif
			#endif

			st_bit(MX_UART3_RCSTA, SPEN);         		// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(MX_UART3_TXSTA, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(MX_UART3_RCSTA, CREN);
			#endif

			#if (MX_UART_INT_X == 1)
				MX_UART_INT_CH3_EN;
				st_bit(INTCON, PEIE);
				st_bit(INTCON, GIE);
			#else
				cr_bit (MX_UART3_PIE, RC3IE);
			#endif
		#endif

	#endif


	#if (MX_UART_CHANNEL_X == 4)

		#ifdef MX_UART_4_REMAPPABLE
			#if (MX_UART_TX_EN_X == 1)
				MX_UART_4_TX_RPOR = MX_UART_4_TX_UTX;
			#endif
			#if (MX_UART_RX_EN_X == 1)
				MX_UART_4_RX_RPINR = MX_UART_4_RX_RP;
			#endif
		#endif

		#ifdef MX_UART_4_TX_ALT						//Setup Alt I/O
			#if (MX_UART_TX_EN_X == 1)
				MX_UART_4_TX_ALT;
			#endif
		#endif
		#ifdef MX_UART_4_RX_ALT
			#if (MX_UART_RX_EN_X == 1)
				MX_UART_4_RX_ALT;
			#endif
		#endif

		#ifdef UALTREG										//New 18FxxK42 PIC Register Setup

			#if (MX_HARD_SLOW_X == 1)
				cr_bit(U4CON0, BRGS);						//Low Speed

		#elif defined(UALTREG1)									//New PIC16F15XX PIC Register Setup

			#if (MX_HARD_SLOW_X == 1)
				cr_bit(U4CON0, BRGS);						//Low Speed
			#else
				st_bit(U4CON0, BRGS);						//High Speed
			#endif

			U4BRGL = MX_HARD_BAUD_X;   						// set the baud rate
			U4BRGH = MX_HARD_BAUD_X >> 8;   				// set the baud rate

			#if(MX_UART_DBITS_X == 9)
				st_bit(U4CON0, 2);   						// 9-bit TX&RX
			#endif

			st_bit(U4CON1, ON);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(U4CON0, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(U4CON0, RXEN);
			#endif

			#if (MX_UART_INT_X == 1)
				#ifdef _PIE12_U4RXIE_POSN
					st_bit (PIE12, U4RXIE);
				#endif
				#ifdef _PIE12_U4RXIE_POSN
					st_bit (PIE12, U4RXIE);
				#endif

				//st_bit(INTCON, PEIE);
				st_bit(INTCON0, GIE);
			#else
				#ifdef _PIE12_U4RXIE_POSN
					cr_bit (PIE12, U4RXIE);
				#endif
				#ifdef _PIE12_U4RXIE_POSN
					cr_bit (PIE12, U4RXIE);
				#endif
			#endif
			#else
				st_bit(U4CON0, BRGS);						//High Speed
			#endif

			U1BRGL = MX_HARD_BAUD_X;   						// set the baud rate
			U1BRGH = MX_HARD_BAUD_X >> 8;   				// set the baud rate

			#if(MX_UART_DBITS_X == 9)
				st_bit(U4CON0, 2);   						// 9-bit TX&RX
			#endif

			st_bit(U4CON1, ON);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(U4CON0, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(U4CON0, RXEN);
			#endif

			#if (MX_UART_INT_X == 1)
				#ifdef _PIE4_U1RXIE_POSN
					st_bit (PIE3, U1RXIE);
				#endif
				#ifdef _PIE4_U1RXIE_POSN
					st_bit (PIE3, U1RXIE);
				#endif

				//st_bit(INTCON, PEIE);
				st_bit(INTCON0, GIE);
			#else
				#ifdef _PIE3_U1RXIE_POSN
					cr_bit (PIE3, U1RXIE);
				#endif
				#ifdef _PIE4_U1RXIE_POSN
					cr_bit (PIE4, U1RXIE);
				#endif
			#endif

		#else

			#if (MX_HARD_SLOW_X == 1)
			cr_bit(MX_UART4_TXSTA, BRGH);				//Low Speed
			#else
			st_bit(MX_UART4_TXSTA, BRGH);				//High Speed
			#endif

			#ifdef _BAUD4CON_BRG16_POSN
				BAUD4CON = 0;
			#endif

			SPBRG4 = MX_HARD_BAUD_X;   					// set the baud rate
			MX_UART4_RCSTA = 0;                    		// 8-bit, disabled

			#if(MX_UART_DBITS_X == 9)
				#if (MX_UART_TX_EN_X == 1)
					st_bit(MX_UART4_TXSTA, TX9);   		// 9-bit TX
				#endif
				#if (MX_UART_RX_EN_X == 1)
					st_bit(MX_UART4_RCSTA, RX9);        // 9-bit RX
				#endif
			#endif

			st_bit(MX_UART4_RCSTA, SPEN);         		// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(MX_UART4_TXSTA, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(MX_UART4_RCSTA, CREN);
			#endif

			#if (MX_UART_INT_X == 1)
				MX_UART_INT_CH4_EN;
				st_bit(INTCON, PEIE);
				st_bit(INTCON, GIE);
			#else
				cr_bit (MX_UART4_PIE, RC4IE);
			#endif

		#endif
	#endif


	#if (MX_UART_CHANNEL_X == 5)

		#ifdef MX_UART_5_REMAPPABLE
			#if (MX_UART_TX_EN_X == 1)
				MX_UART_5_TX_RPOR = MX_UART_5_TX_UTX;
			#endif
			#if (MX_UART_RX_EN_X == 1)
				MX_UART_5_RX_RPINR = MX_UART_5_RX_RP;
			#endif
		#endif

		#ifdef MX_UART_5_TX_ALT						//Setup Alt I/O
			#if (MX_UART_TX_EN_X == 1)
				MX_UART_5_TX_ALT;
			#endif
		#endif
		#ifdef MX_UART_5_RX_ALT
			#if (MX_UART_RX_EN_X == 1)
				MX_UART_5_RX_ALT;
			#endif
		#endif

		#ifdef UALTREG										//New 18FxxK42 PIC Register Setup

			#if (MX_HARD_SLOW_X == 1)
				cr_bit(U5CON0, BRGS);						//Low Speed

		#elif defined(UALTREG1)									//New PIC16F15XX PIC Register Setup

			#if (MX_HARD_SLOW_X == 1)
				cr_bit(U5CON0, BRGS);						//Low Speed
			#else
				st_bit(U5CON0, BRGS);						//High Speed
			#endif

			U5BRGL = MX_HARD_BAUD_X;   						// set the baud rate
			U5BRGH = MX_HARD_BAUD_X >> 8;   				// set the baud rate

			#if(MX_UART_DBITS_X == 9)
				st_bit(U5CON0, 2);   						// 9-bit TX&RX
			#endif

			st_bit(U5CON1, ON);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(U5CON0, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(U5CON0, RXEN);
			#endif

			#if (MX_UART_INT_X == 1)
				#ifdef _PIE13_U5RXIE_POSN
					st_bit (PIE13, U5RXIE);
				#endif
				#ifdef _PIE13_U5RXIE_POSN
					st_bit (PIE13, U5RXIE);
				#endif

				//st_bit(INTCON, PEIE);
				st_bit(INTCON0, GIE);
			#else
				#ifdef _PIE13_U5RXIE_POSN
					cr_bit (PIE13, U5RXIE);
				#endif
				#ifdef _PIE13_U5RXIE_POSN
					cr_bit (PIE13, U5RXIE);
				#endif
			#endif
			#else
				st_bit(U5CON0, BRGS);						//High Speed
			#endif

			U1BRGL = MX_HARD_BAUD_X;   						// set the baud rate
			U1BRGH = MX_HARD_BAUD_X >> 8;   				// set the baud rate

			#if(MX_UART_DBITS_X == 9)
				st_bit(U5CON0, 2);   						// 9-bit TX&RX
			#endif

			st_bit(U5CON1, ON);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(U5CON0, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(U5CON0, RXEN);
			#endif

			#if (MX_UART_INT_X == 1)
				#ifdef _PIE3_U1RXIE_POSN
					st_bit (PIE14, U5RXIE);
				#endif
				#ifdef _PIE4_U1RXIE_POSN
					st_bit (PIE14, U5RXIE);
				#endif

				//st_bit(INTCON, PEIE);
				st_bit(INTCON0, GIE);
			#else
				#ifdef _PIE3_U1RXIE_POSN
					cr_bit (PIE14, U5RXIE);
				#endif
				#ifdef _PIE4_U1RXIE_POSN
					cr_bit (PIE4, U1RXIE);
				#endif
			#endif

		#else

			#if (MX_HARD_SLOW_X == 1)
				cr_bit(MX_UART5_TXSTA, BRGH);			//Low Speed
			#else
				st_bit(MX_UART5_TXSTA, BRGH);			//High Speed
			#endif

			#ifdef _BAUD5CON_BRG16_POSN
				BAUD5CON = 0;
			#endif

			SPBRG5 = MX_HARD_BAUD_X;   					// set the baud rate
			MX_UART5_RCSTA = 0;                    		// 8-bit, disabled

			#if(MX_UART_DBITS_X == 9)
				#if (MX_UART_TX_EN_X == 1)
					st_bit(MX_UART5_TXSTA, TX9);   		// 9-bit TX
				#endif
				#if (MX_UART_RX_EN_X == 1)
					st_bit(MX_UART5_RCSTA, RX9);        // 9-bit RX
				#endif
			#endif

			st_bit(MX_UART5_RCSTA, SPEN);         		// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(MX_UART5_TXSTA, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(MX_UART5_RCSTA, CREN);
			#endif

			#if (MX_UART_INT_X == 1)
				MX_UART_INT_CH5_EN;
				st_bit(INTCON, PEIE);
				st_bit(INTCON, GIE);
			#else
				cr_bit (MX_UART5_PIE, RC5IE);
			#endif

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
		#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
			U1CON1 = 0;                    										// 8-bit, disabled
			U1CON0 = 0;
		#else												//Normal Setup
			RCSTA = 0;                    										// 8-bit, disabled
			TXSTA = 0;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH1_DIS;
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 2)
		#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
			U2CON1 = 0;                    										// 8-bit, disabled
			U2CON0 = 0;
		#else												//Normal Setup
			MX_UART2_RCSTA = 0;                    								// 8-bit, disabled
			MX_UART2_TXSTA = 0;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH2_DIS;
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 3)
		#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
			U3CON1 = 0;                    										// 8-bit, disabled
			U3CON0 = 0;
		#else
			MX_UART3_RCSTA = 0;                    								// 8-bit, disabled
			MX_UART3_TXSTA = 0;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH3_DIS;
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 4)
		#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
			U4CON1 = 0;                    										// 8-bit, disabled
			U4CON0 = 0;
		#else
			MX_UART4_RCSTA = 0;                    								// 8-bit, disabled
			MX_UART4_TXSTA = 0;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH4_DIS;
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 5)
		#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
			U5CON1 = 0;                    										// 8-bit, disabled
			U5CON0 = 0;
		#else
			MX_UART5_RCSTA = 0;                    								// 8-bit, disabled
			MX_UART5_TXSTA = 0;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH5_DIS;
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

		#if (MX_UART_CHANNEL_X == 1)
			#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
				while (ts_bit(U1ERRIR, TXMTIF) == 0);
				U1TXB = nChar;
			#else
				while (ts_bit(MX_UART1_PIR, TXIF) == 0);

				#if (MX_UART_DBITS_X == 9)
					if (test_bit(nChar, 8))
						st_bit(TXSTA, TX9D);
					else
						cr_bit(TXSTA, TX9D);
				#endif
				TXREG = nChar;
			#endif
		#endif

		#if (MX_UART_CHANNEL_X == 2)
			#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
				while (ts_bit(U2ERRIR, TXMTIF) == 0);
				U2TXB = nChar;
			#else
				while (ts_bit(MX_UART2_PIR, TX2IF) == 0);

				#if (MX_UART_DBITS_X == 9)
					if (test_bit(nChar, 8))
						st_bit(MX_UART2_TXSTA, TX9D);
					else
						cr_bit(MX_UART2_TXSTA, TX9D);
				#endif
				MX_UART2_TXREG = nChar;
			#endif
		#endif

		#if (MX_UART_CHANNEL_X == 3)
			#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
				while (ts_bit(U3ERRIR, TXMTIF) == 0);
				U3TXB = nChar;
			#else
				while (ts_bit(MX_UART3_PIR, TX3IF) == 0);

				#if (MX_UART_DBITS_X == 9)
					if (test_bit(nChar, 8))
						st_bit(MX_UART3_TXSTA, TX9D);
					else
						cr_bit(MX_UART3_TXSTA, TX9D);
				#endif
				MX_UART3_TXREG = nChar;
			#endif
		#endif

		#if (MX_UART_CHANNEL_X == 4)
			#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
				while (ts_bit(U4ERRIR, TXMTIF) == 0);
				U4TXB = nChar;
			#else
				while (ts_bit(MX_UART4_PIR, TX4IF) == 0);

				#if (MX_UART_DBITS_X == 9)
					if (test_bit(nChar, 8))
						st_bit(MX_UART4_TXSTA, TX9D);
					else
						cr_bit(MX_UART4_TXSTA, TX9D);
				#endif
				MX_UART4_TXREG = nChar;
			#endif
		#endif

		#if (MX_UART_CHANNEL_X == 5)
			#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
				while (ts_bit(U5ERRIR, TXMTIF) == 0);
				U5TXB = nChar;
			#else
				while (ts_bit(MX_UART5_PIR, TX5IF) == 0);

				#if (MX_UART_DBITS_X == 9)
					if (test_bit(nChar, 8))
						st_bit(MX_UART5_TXSTA, TX9D);
					else
						cr_bit(MX_UART5_TXSTA, TX9D);
				#endif
				MX_UART5_TXREG = nChar;
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

			#if (MX_UART_CHANNEL_X == 0)
				regcheck = FC_CAL_Bit_In(MX_UART_RX_PORT_X, MX_UART_RX_PIN_X);	//Test for start bit
				if (regcheck == 0)
					rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 1)
				#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
					#ifdef _PIE3_U1RXIE_POSN
						regcheck = ts_bit(PIR3, U1RXIF);
					#endif
					#ifdef _PIE4_U1RXIE_POSN
						regcheck = ts_bit(PIR4, U1RXIF);
					#endif
				#else
					regcheck = ts_bit(MX_UART1_PIR, RCIF);
				#endif
				if (regcheck != 0)
					rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 2)
				#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
					#ifdef _PIE6_U2RXIE_POSN
						regcheck = ts_bit(PIR6, U2RXIF);
					#endif
					#ifdef _PIE8_U2RXIE_POSN
						regcheck = ts_bit(PIR8, U2RXIF);
					#endif
				#else
					regcheck = ts_bit(MX_UART2_PIR, RC2IF);
				#endif
				if (regcheck != 0)
					rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 3)
				#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
					#ifdef _PIE9_U3RXIE_POSN
						regcheck = ts_bit(PIR9, U3RXIF);
					#endif
				#else
					regcheck = ts_bit(MX_UART3_PIR, RC3IF);
				#endif
				if (regcheck != 0)
					rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 4)
				#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
					#ifdef _PIE12_U4RXIE_POSN
						regcheck = ts_bit(PIR12, U4RXIF);
					#endif
				#else
					regcheck = ts_bit(MX_UART4_PIR, RC4IF);
				#endif
				if (regcheck != 0)
					rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 5)
				#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
					#ifdef _PIE13_U5RXIE_POSN
						regcheck = ts_bit(PIR13, U5RXIF);
					#endif
				#else
					regcheck = ts_bit(MX_UART5_PIR, RC5IF);
				#endif
				if (regcheck != 0)
					rxStatus = UART_STATUS_RXBYTE;
			#endif

		}

		if (rxStatus == UART_STATUS_RXBYTE)
		{
			#if (MX_UART_CHANNEL_X == 0)

				retVal = 0;
				UART_Delay_CAL();

				for (idx = 0; idx < MX_UART_DBITS_X; idx++)
				{
					if (FC_CAL_Bit_In(MX_UART_RX_PORT_X, MX_UART_RX_PIN_X))
						retVal = retVal | (0x01 << idx);

					UART_Delay_CAL();
				}
			#endif

			#if (MX_UART_CHANNEL_X == 1)
				#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
					regcheck = ts_bit(U1ERRIR, FERIF);
					if (regcheck != 0)
					{
						dummy = U1RXB;						//need to read the RCREG to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;					//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = ts_bit(U1ERRIR, RXFOIF);
						if (regcheck != 0)
						{
							cr_bit(U1CON0, RXEN);			//Reset receiver to clear error
							st_bit(U1CON0, RXEN);

							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;				//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = U1RXB; 			//no error, so rx byte is valid
						}
					}

				#else
					regcheck = ts_bit(RCSTA, FERR);
					if (regcheck != 0)
					{
						dummy = RCREG;						//need to read the RCREG to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;					//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = ts_bit(RCSTA, OERR);
						if (regcheck != 0)
						{
							cr_bit(RCSTA, CREN);			//Reset receiver to clear error
							st_bit(RCSTA, CREN);

							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;				//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;

							#if (MX_UART_DBITS_X == 9)
								if(ts_bit(RCSTA, RX9D))
									retVal = 0x100;
							#endif

							retVal = retVal | RCREG; 			//no error, so rx byte is valid
						}
					}
				#endif
			#endif

			#if (MX_UART_CHANNEL_X == 2)
				#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
					regcheck = ts_bit(U2ERRIR, FERIF);
					if (regcheck != 0)
					{
						dummy = U2RXB;						//need to read the RCREG to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;					//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = ts_bit(U2ERRIR, RXFOIF);
						if (regcheck != 0)
						{
							cr_bit(U2CON0, RXEN);			//Reset receiver to clear error
							st_bit(U2CON0, RXEN);

							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;				//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = U2RXB; 			//no error, so rx byte is valid
						}
					}

				#else
					regcheck = ts_bit(MX_UART2_RCSTA, FERR);
					if (regcheck != 0)
					{
						dummy = MX_UART2_RCREG;			//need to read the RCREG to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;					//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = ts_bit(MX_UART2_RCSTA, OERR);
						if (regcheck != 0)
						{
							cr_bit(MX_UART2_RCSTA, CREN);	//Reset receiver to clear error
							st_bit(MX_UART2_RCSTA, CREN);
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;				//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;

							#if (MX_UART_DBITS_X == 9)
								if(ts_bit(MX_UART2_RCSTA, RX9D))
									retVal = 0x100;
							#endif

							retVal = retVal | MX_UART2_RCREG; 			//no error, so rx byte is valid
						}
					}
				#endif
			#endif

			#if (MX_UART_CHANNEL_X == 3)
				#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
					regcheck = ts_bit(U3ERRIR, FERIF);
					if (regcheck != 0)
					{
						dummy = U3RXB;						//need to read the RCREG to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;					//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = ts_bit(U3ERRIR, RXFOIF);
						if (regcheck != 0)
						{
							cr_bit(U3CON0, RXEN);			//Reset receiver to clear error
							st_bit(U3CON0, RXEN);

							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;				//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = U3RXB; 			//no error, so rx byte is valid
						}
					}

				#else
					regcheck = ts_bit(MX_UART3_RCSTA, FERR);
					if (regcheck != 0)
					{
						dummy = MX_UART3_RCREG;			//need to read the RCREG to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;					//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = ts_bit(MX_UART3_RCSTA, OERR);
						if (regcheck != 0)
						{
							cr_bit(MX_UART3_RCSTA, CREN);	//Reset receiver to clear error
							st_bit(MX_UART3_RCSTA, CREN);
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;				//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;

							#if (MX_UART_DBITS_X == 9)
								if(ts_bit(MX_UART3_RCSTA, RX9D))
									retVal = 0x100;
							#endif

							retVal = retVal | MX_UART3_RCREG; 			//no error, so rx byte is valid
						}
					}
				#endif
			#endif

			#if (MX_UART_CHANNEL_X == 4)
				#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
					regcheck = ts_bit(U4ERRIR, FERIF);
					if (regcheck != 0)
					{
						dummy = U4RXB;						//need to read the RCREG to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;					//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = ts_bit(U4ERRIR, RXFOIF);
						if (regcheck != 0)
						{
							cr_bit(U4CON0, RXEN);			//Reset receiver to clear error
							st_bit(U4CON0, RXEN);

							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;				//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = U4RXB; 			//no error, so rx byte is valid
						}
					}

				#else
					regcheck = ts_bit(MX_UART4_RCSTA, FERR);
					if (regcheck != 0)
					{
						dummy = MX_UART4_RCREG;			//need to read the RCREG to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;					//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = ts_bit(MX_UART4_RCSTA, OERR);
						if (regcheck != 0)
						{
							cr_bit(MX_UART4_RCSTA, CREN);	//Reset receiver to clear error
							st_bit(MX_UART4_RCSTA, CREN);
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;				//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;

							#if (MX_UART_DBITS_X == 9)
								if(ts_bit(MX_UART4_RCSTA, RX9D))
									retVal = 0x100;
							#endif

							retVal = retVal | MX_UART4_RCREG; 			//no error, so rx byte is valid
						}
					}
				#endif
			#endif

			#if (MX_UART_CHANNEL_X == 5)
				#ifdef UALTREG										//New 18FxxK42 PIC Register Setup
					regcheck = ts_bit(U5ERRIR, FERIF);
					if (regcheck != 0)
					{
						dummy = U5RXB;						//need to read the RCREG to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;					//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = ts_bit(U5ERRIR, RXFOIF);
						if (regcheck != 0)
						{
							cr_bit(U5CON0, RXEN);			//Reset receiver to clear error
							st_bit(U5CON0, RXEN);

							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;				//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = U5RXB; 			//no error, so rx byte is valid
						}
					}

				#else
					regcheck = ts_bit(MX_UART5_RCSTA, FERR);
					if (regcheck != 0)
					{
						dummy = MX_UART5_RCREG;			//need to read the RCREG to clear FERR
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x400;					//Framing Error Flag
						#endif
					}
					else
					{
						regcheck = ts_bit(MX_UART5_RCSTA, OERR);
						if (regcheck != 0)
						{
							cr_bit(MX_UART5_RCSTA, CREN);	//Reset receiver to clear error
							st_bit(MX_UART5_RCSTA, CREN);
							#if (MX_UART_RETURN_X == 1)
								retVal = 0x800;				//Overrun Error Flag
							#endif
						}
						else
						{
							retVal = 0;

							#if (MX_UART_DBITS_X == 9)
								if(ts_bit(MX_UART5_RCSTA, RX9D))
									retVal = 0x100;
							#endif

							retVal = retVal | MX_UART5_RCREG; 			//no error, so rx byte is valid
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

	MX_UINT16 baudrate;
	MX_UINT8 baudmode;

	if (new_baud > 8)
		return;

	if (new_baud == 0)
	{
		baudrate = MX_HARD_BAUD_1200;
		baudmode = MX_HARD_SLOW_1200;
	}
	else if (new_baud == 1)
	{
		baudrate = MX_HARD_BAUD_2400;
		baudmode = MX_HARD_SLOW_2400;
	}
	else if (new_baud == 2)
	{
		baudrate = MX_HARD_BAUD_4800;
		baudmode = MX_HARD_SLOW_4800;
	}
	else if (new_baud == 3)
	{
		baudrate = MX_HARD_BAUD_9600;
		baudmode = MX_HARD_SLOW_9600;
	}
	else if (new_baud == 4)
	{
		baudrate = MX_HARD_BAUD_19200;
		baudmode = MX_HARD_SLOW_19200;
	}
	else if (new_baud == 5)
	{
		baudrate = MX_HARD_BAUD_38400;
		baudmode = MX_HARD_SLOW_38400;
	}
	else if (new_baud == 6)
	{
		baudrate = MX_HARD_BAUD_57600;
		baudmode = MX_HARD_SLOW_57600;
	}
	else if (new_baud == 7)
	{
		baudrate = MX_HARD_BAUD_115200;
		baudmode = MX_HARD_SLOW_115200;
	}
	else if (new_baud == 8)
	{
		baudrate = MX_HARD_BAUD_250000;
		baudmode = MX_HARD_SLOW_250000;
	}

	UART_Uninit();

	#if (MX_UART_CHANNEL_X == 1)

		#ifdef UALTREG										//New 18FxxK42 PIC Register Setup

			cr_bit(U1CON1, ON);         					// turn off serial interface

			#if (baudmode == 1)
				cr_bit(U1CON0, BRGS);						//Low Speed
			#else
				st_bit(U1CON0, BRGS);						//High Speed
			#endif

			U1BRGL = baudrate;   							// set the baud rate
			U1BRGH = baudrate >> 8;   						// set the baud rate

			#if(MX_UART_DBITS_X == 9)
				st_bit(U1CON0, 2);   						// 9-bit TX&RX
			#endif

			st_bit(U1CON1, ON);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(U1CON0, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(U1CON0, RXEN);
			#endif

		#else												//Normal PIC Register Setup

			if (baudmode == 1)
				cr_bit(TXSTA, BRGH);					//Low Speed
			else
				st_bit(TXSTA, BRGH);					//High Speed

			SPBRG = baudrate;   						// set the baud rate
			RCSTA = 0;                    				// 8-bit, disabled

			#if(MX_UART_DBITS_X == 9)
				#if (MX_UART_TX_EN_X == 1)
					st_bit(TXSTA, TX9);   				// 9-bit TX
				#endif
				#if (MX_UART_RX_EN_X == 1)
					st_bit(RCSTA, RX9);                 // 9-bit RX
				#endif
			#endif

			st_bit(RCSTA, SPEN);         				// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(TXSTA, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(RCSTA, CREN);
			#endif

		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH1_EN;

			#ifndef UALTREG
			  st_bit(INTCON, PEIE);
			  st_bit(INTCON, GIE);
			#else
			  st_bit(INTCON0, GIE);
			#endif

		#else
			//cr_bit (MX_UART1_PIE, RCIE);			//Don't disable UART RX INT here!
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 2)

		#ifdef UALTREG										//New 18FxxK42 PIC Register Setup

			cr_bit(U2CON1, ON);         					// turn off serial interface

			#if (baudmode == 1)
				cr_bit(U2CON0, BRGS);						//Low Speed
			#else
				st_bit(U2CON0, BRGS);						//High Speed
			#endif

			U2BRGL = baudrate;   							// set the baud rate
			U2BRGH = baudrate >> 8;   						// set the baud rate

			#if(MX_UART_DBITS_X == 9)
				st_bit(U2CON0, 2);   						// 9-bit TX&RX
			#endif

			st_bit(U2CON1, ON);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(U2CON0, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(U2CON0, RXEN);
			#endif

		#else												//Normal PIC Register Setup

			if (baudmode == 1)
				cr_bit(MX_UART2_TXSTA, BRGH);			//Low Speed
			else
				st_bit(MX_UART2_TXSTA, BRGH);			//High Speed

			SPBRG2 = baudrate;   						// set the baud rate
			MX_UART2_RCSTA = 0;                    		// 8-bit, disabled

			#if(MX_UART_DBITS_X == 9)
				#if (MX_UART_TX_EN_X == 1)
					st_bit(MX_UART2_TXSTA, TX9);   		// 9-bit TX
				#endif
				#if (MX_UART_RX_EN_X == 1)
					st_bit(MX_UART2_RCSTA, RX9);        // 9-bit RX
				#endif
			#endif

			st_bit(MX_UART2_RCSTA, SPEN);         		// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(MX_UART2_TXSTA, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(MX_UART2_RCSTA, CREN);
			#endif

		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH2_EN;

			#ifndef UALTREG
			  st_bit(INTCON, PEIE);
			  st_bit(INTCON, GIE);
			#else
			  st_bit(INTCON0, GIE);
			#endif
		#else
			//cr_bit (MX_UART2_PIE, RC2IE);			//Don't disable UART RX INT here!
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 3)

		#ifdef UALTREG										//New 18FxxK42 PIC Register Setup

			cr_bit(U3CON1, ON);         					// turn off serial interface

			#if (baudmode == 1)
				cr_bit(U3CON0, BRGS);						//Low Speed
			#else
				st_bit(U3CON0, BRGS);						//High Speed
			#endif

			U3BRGL = baudrate;   							// set the baud rate
			U3BRGH = baudrate >> 8;   						// set the baud rate

			#if(MX_UART_DBITS_X == 9)
				st_bit(U3CON0, 2);   						// 9-bit TX&RX
			#endif

			st_bit(U3CON1, ON);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(U3CON0, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(U3CON0, RXEN);
			#endif

		#else

			if (baudmode == 1)
				cr_bit(MX_UART3_TXSTA, BRGH);			//Low Speed
			else
				st_bit(MX_UART3_TXSTA, BRGH);			//High Speed

			SPBRG3 = baudrate;   						// set the baud rate
			MX_UART3_RCSTA = 0;                    		// 8-bit, disabled

			#if(MX_UART_DBITS_X == 9)
				#if (MX_UART_TX_EN_X == 1)
					st_bit(MX_UART3_TXSTA, TX9);   		// 9-bit TX
				#endif
				#if (MX_UART_RX_EN_X == 1)
					st_bit(MX_UART3_RCSTA, RX9);        // 9-bit RX
				#endif
			#endif

			st_bit(MX_UART3_RCSTA, SPEN);         		// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(MX_UART3_TXSTA, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(MX_UART3_RCSTA, CREN);
		#endif

		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH3_EN;
			st_bit(INTCON, PEIE);
			st_bit(INTCON, GIE);
		#else
			//cr_bit (MX_UART3_PIE, RC3IE);			//Don't disable UART RX INT here!
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 4)

		#ifdef UALTREG										//New 18FxxK42 PIC Register Setup

			cr_bit(U4CON1, ON);         					// turn off serial interface

			#if (baudmode == 1)
				cr_bit(U4CON0, BRGS);						//Low Speed
			#else
				st_bit(U4CON0, BRGS);						//High Speed
			#endif

			U4BRGL = baudrate;   							// set the baud rate
			U4BRGH = baudrate >> 8;   						// set the baud rate

			#if(MX_UART_DBITS_X == 9)
				st_bit(U4CON0, 2);   						// 9-bit TX&RX
			#endif

			st_bit(U4CON1, ON);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(U4CON0, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(U4CON0, RXEN);
			#endif

		#else

			if (baudmode == 1)
				cr_bit(MX_UART4_TXSTA, BRGH);			//Low Speed
			else
				st_bit(MX_UART4_TXSTA, BRGH);			//High Speed

			SPBRG4 = baudrate;   						// set the baud rate
			MX_UART4_RCSTA = 0;                    		// 8-bit, disabled

			#if(MX_UART_DBITS_X == 9)
				#if (MX_UART_TX_EN_X == 1)
					st_bit(MX_UART4_TXSTA, TX9);   		// 9-bit TX
				#endif
				#if (MX_UART_RX_EN_X == 1)
					st_bit(MX_UART4_RCSTA, RX9);        // 9-bit RX
				#endif
			#endif

			st_bit(MX_UART4_RCSTA, SPEN);         		// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(MX_UART4_TXSTA, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(MX_UART4_RCSTA, CREN);
			#endif

		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH4_EN;
			st_bit(INTCON, PEIE);
			st_bit(INTCON, GIE);
		#else
			//cr_bit (MX_UART4_PIE, RC4IE);			//Don't disable UART RX INT here!
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 5)

		#ifdef UALTREG										//New 18FxxK42 PIC Register Setup

			cr_bit(U5CON1, ON);         					// turn off serial interface

			#if (baudmode == 1)
				cr_bit(U5CON0, BRGS);						//Low Speed
			#else
				st_bit(U5CON0, BRGS);						//High Speed
			#endif

			U5BRGL = baudrate;   							// set the baud rate
			U5BRGH = baudrate >> 8;   						// set the baud rate

			#if(MX_UART_DBITS_X == 9)
				st_bit(U5CON0, 2);   						// 9-bit TX&RX
			#endif

			st_bit(U5CON1, ON);         					// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(U5CON0, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(U5CON0, RXEN);
			#endif

		#else

			if (baudmode == 1)
				cr_bit(MX_UART5_TXSTA, BRGH);			//Low Speed
			else
				st_bit(MX_UART5_TXSTA, BRGH);			//High Speed

			SPBRG5 = baudrate;   						// set the baud rate
			MX_UART5_RCSTA = 0;                    		// 8-bit, disabled

			#if(MX_UART_DBITS_X == 9)
				#if (MX_UART_TX_EN_X == 1)
					st_bit(MX_UART5_TXSTA, TX9);   		// 9-bit TX
				#endif
				#if (MX_UART_RX_EN_X == 1)
					st_bit(MX_UART5_RCSTA, RX9);        // 9-bit RX
				#endif
			#endif

			st_bit(MX_UART5_RCSTA, SPEN);         		// turn on serial interface

			#if (MX_UART_TX_EN_X == 1)
				st_bit(MX_UART5_TXSTA, TXEN);
			#endif
			#if (MX_UART_RX_EN_X == 1)
				st_bit(MX_UART5_RCSTA, CREN);
			#endif

		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH5_EN;
			st_bit(INTCON, PEIE);
			st_bit(INTCON, GIE);
		#else
			//cr_bit (MX_UART5_PIE, RC5IE);			//Don't disable UART RX INT here!
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




//Get rid of defines to avoid redefinition warnings for otrher UART channels
#undef MX_HARD_BAUD_X
#undef MX_HARD_SLOW_X

