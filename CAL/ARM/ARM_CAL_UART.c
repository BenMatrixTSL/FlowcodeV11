// CRC: AE5753800093D2B889297C6B876B6A21749C10AFA09C3FCE4A5F65B0FF76818F478F634975A712457CCBE7D4DA9E6C839A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5B611FDE6B4DE716763B4D43B36630FE7C6F63B5FB8ACF7AF1ADDC7F5A05275BECAD0D09C648F8A927DCE25B927184EE204765BD681D1F38B7B3E9232BC636EF079F0409BBAC560E484CB4DC2FE66797F6A20D023046EF424549D34A0D5AD11F359B009FDDD93F61E01FF7B302C9BB1E02F5FDCFECAFF479BFFCF1C90B393605E9F32B96E9FC2F3A9
// REVISION: 1.0
// GUID: A97A6913-551F-479D-801A-4078E9AB9691
// DATE: 08\08\2022
// DIR: CAL\ARM\ARM_CAL_UART.c
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
 * 050312 | BR | Updated to v5.1 CAL Schema
 * 160712 | BR | UART channel 2 used channel 1 definitions - fixed by Mantas
 * 190712 | BR | UART RX interrupt wa snot being enabled where applicable - Fixed
 * 220812 | BR | Fixed a bug in the software UART where the SW_BAUD was not being assigned
 * 240413 | LM | Fixed typo re PORT_1 -> PORT_X for Software UART
 * 030713 | LM | Standard API calls
 */


#ifndef MX_UART_SW_DEFS
	#define MX_UART_SW_DEFS

	//#define INST_COUNT	1100
	//Work out number of nops for software baud rate
	//#define MX_INSTRUCTION_SPEED 	(MX_CLK_SPEED / 1)
	//#define MX_OVERHEAD			(MX_INSTRUCTION_SPEED / INST_COUNT)
	//#define SW_OFFSET				(1000000 / MX_OVERHEAD)

	//Work out software baud rates if required
	#define SW_1200_BAUD	681			//833.3us - measured 835.5us
	#define SW_2400_BAUD	219			//416.6us - measured 414.2us
	#define SW_4800_BAUD	109			//208.3us - measured 207.6us
	#define SW_9600_BAUD	55			//104.2us - measured 106.2us
	#define SW_19200_BAUD	39			//52.08us - measured 51.77us
	#define SW_31250_BAUD	23			//32.00us - measured 31.74
	#define SW_115200_BAUD	12
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
#define MX_UART_BAUD_X		CAL_APPEND(MX_UART_BAUD_, MX_UART_NUM)		//Uses baud directly rather then via a conversion

#define UART_Delay_CAL		CAL_APPEND(FC_CAL_UART_Delay_, MX_UART_NUM)
#define UART_Send			CAL_APPEND(FC_CAL_UART_Send_, MX_UART_NUM)
#define UART_Uninit			CAL_APPEND(FC_CAL_UART_Uninit_, MX_UART_NUM)


#if (MX_UART_CHANNEL_X == 0)
	#if (MX_UART_BAUD_X == 1200)
		#define MX_SOFT_BAUD_X	SW_1200_BAUD
	#endif
	#if (MX_UART_BAUD_X == 2400)
		#define MX_SOFT_BAUD_X	SW_2400_BAUD
	#endif
	#if (MX_UART_BAUD_X == 4800)
		#define MX_SOFT_BAUD_X	SW_4800_BAUD
	#endif
	#if (MX_UART_BAUD_X == 9600)
		#define MX_SOFT_BAUD_X	SW_9600_BAUD
	#endif
	#if (MX_UART_BAUD_X == 19200)
		#define MX_SOFT_BAUD_X	SW_19200_BAUD
	#endif
	#if (MX_UART_BAUD_X == 31250)
		#define MX_SOFT_BAUD_X	SW_31250_BAUD
	#endif
	#if (MX_UART_BAUD_X == 115200)
		#define MX_SOFT_BAUD_X	SW_115200_BAUD
	#endif
	#if (MX_UART_BAUD_X == 250000)
		#define MX_SOFT_BAUD_X	SW_250000_BAUD
	#endif
	#ifndef MX_SOFT_BAUD_X
		#error "UART Baud Rate not supported in Software Mode"
	#endif
#else
	#define MX_SOFT_BAUD_X	1
#endif


//Component Definitions
#define UART_STATUS_LOOP	0
#define UART_STATUS_TIMEOUT	1
#define UART_STATUS_RXBYTE	2


//Interrupt Definitions
#if (MX_UART_INT_X == 1)

	#ifndef MX_UART_INT_DEFS
	#define MX_UART_INT_DEFS

		#define MX_UART_INT_CH1_FUNC
		#define MX_UART_INT_CH2_FUNC
		#define MX_UART_INT_FUNC_END

		#define MX_UART_INT_CH1_DET		((periphID == AT91C_ID_US1) && (IFlags & AT91C_US_RXRDY))
		#define MX_UART_INT_CH2_DET		((periphID == AT91C_ID_US0) && (IFlags & AT91C_US_RXRDY))

		#define MX_UART_INT_CH1_EN		AT91F_US_EnableIt(AT91C_BASE_US1,AT91C_US_RXRDY)
		#define MX_UART_INT_CH2_EN		AT91F_US_EnableIt(AT91C_BASE_US0,AT91C_US_RXRDY)

		#define MX_UART_INT_CH1_DIS		AT91F_US_DisableIt(AT91C_BASE_US1,AT91C_US_RXRDY)
		#define MX_UART_INT_CH2_DIS		AT91F_US_DisableIt(AT91C_BASE_US0,AT91C_US_RXRDY)

		#define MX_UART_INT_CH1_CLR
		#define MX_UART_INT_CH2_CLR

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
		#if (MX_UART_TX_EN_X == 1) && (MX_UART_RX_EN_X == 1)
			AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA21_RXD1 | AT91C_PA22_TXD1, 0);
		#else
			#if (MX_UART_TX_EN_X == 1)
				AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA22_TXD1, 0);
			#else
				AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA21_RXD1, 0);
			#endif
		#endif
		AT91F_US1_CfgPMC();

	  #if(MX_UART_DBITS_X == 9)
		AT91F_US_Configure(AT91C_BASE_US1,MCK,AT91C_US_ASYNC_MODE | AT91C_US_MODE9, MX_UART_BAUD_X, 0);		//9-bit mode
	  #else
		AT91F_US_Configure(AT91C_BASE_US1,MCK,AT91C_US_ASYNC_MODE, MX_UART_BAUD_X, 0);						//8-bit mode
	  #endif

		#if (MX_UART_TX_EN_X == 1)
			AT91F_US_ResetTx(AT91C_BASE_US1);
			AT91C_BASE_US1->US_CR = AT91C_US_TXEN;					// enable tx
		#endif
		#if (MX_UART_RX_EN_X == 1)
			AT91F_US_ResetRx(AT91C_BASE_US1);
			AT91C_BASE_US1->US_CR = AT91C_US_RXEN;					// enable rx
		#endif

	  #if (MX_UART_INT_X == 1)
	  	MX_UART_INT_CH1_EN;											//No Flag Clear Instruction Required
	  #endif
	#endif


	#if (MX_UART_CHANNEL_X == 2)
		#if (MX_UART_TX_EN_X == 1) && (MX_UART_RX_EN_X == 1)
			AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA5_RXD0 | AT91C_PA6_TXD0, 0);
		#else
			#if (MX_UART_TX_EN_X == 1)
				AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA6_TXD0, 0);
			#else
				AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA5_RXD0, 0);
			#endif
		#endif
		AT91F_US0_CfgPMC();

	  #if(MX_UART_DBITS_X == 9)
		AT91F_US_Configure(AT91C_BASE_US0,MCK,AT91C_US_ASYNC_MODE | AT91C_US_MODE9,MX_UART_BAUD_X,0);		//9-bit mode
	  #else
		AT91F_US_Configure(AT91C_BASE_US0,MCK,AT91C_US_ASYNC_MODE,MX_UART_BAUD_X,0);						//8-bit mode
	  #endif

		#if (MX_UART_TX_EN_X == 1)
			AT91F_US_ResetTx(AT91C_BASE_US0);
			AT91C_BASE_US0->US_CR = AT91C_US_TXEN;					// enable tx
		#endif
		#if (MX_UART_RX_EN_X == 1)
			AT91F_US_ResetRx(AT91C_BASE_US0);
			AT91C_BASE_US0->US_CR = AT91C_US_RXEN;					// enable rx
		#endif

	  #if (MX_UART_INT_X == 1)
	  	MX_UART_INT_CH2_EN;											//No Flag Clear Instruction Required
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
		AT91C_BASE_US1->US_CR = 0;
	#endif

	#if (MX_UART_CHANNEL_X == 2)
		AT91C_BASE_US0->US_CR = 0;
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
			while (AT91F_US_TxReady(AT91C_BASE_US1) == 0);	// Wait for tx ready
			AT91F_US_PutChar(AT91C_BASE_US1, nChar);
		#endif

		#if (MX_UART_CHANNEL_X == 2)
			while (AT91F_US_TxReady(AT91C_BASE_US0) == 0);	// Wait for tx ready
			AT91F_US_PutChar(AT91C_BASE_US0, nChar);
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
					regcheck = AT91F_US_RxReady(AT91C_BASE_US1);
					if (regcheck != 0)
						rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 2)
					regcheck = AT91F_US_RxReady(AT91C_BASE_US0);
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
				regcheck = AT91F_US_Error(AT91C_BASE_US1) & AT91C_US_FRAME;
				if (regcheck != 0)
				{
					AT91C_BASE_US1->US_CR = AT91C_US_RSTSTA;			//Reset Status
					#if (MX_UART_RETURN_X == 1)
						retVal = 0x400;									//Framing Error Flag
					#endif
				}
				else
				{
					regcheck = AT91F_US_Error(AT91C_BASE_US1) & AT91C_US_OVRE;
					if (regcheck != 0)
					{
						AT91C_BASE_US1->US_CR = AT91C_US_RSTSTA;		//Reset Status
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x800;								//Overrun Error Flag
						#endif
					}
					else
					{
						retVal = AT91F_US_GetChar(AT91C_BASE_US1);		//no error, so rx byte is valid
					}
				}
			#endif

			#if (MX_UART_CHANNEL_X == 2)
				regcheck = AT91F_US_Error(AT91C_BASE_US0) & AT91C_US_FRAME;
				if (regcheck != 0)
				{
					AT91C_BASE_US0->US_CR = AT91C_US_RSTSTA;			//Reset Status
					#if (MX_UART_RETURN_X == 1)
						retVal = 0x400;									//Framing Error Flag
					#endif
				}
				else
				{
					regcheck = AT91F_US_Error(AT91C_BASE_US0) & AT91C_US_OVRE;
					if (regcheck != 0)
					{
						AT91C_BASE_US0->US_CR = AT91C_US_RSTSTA;		//Reset Status
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x800;								//Overrun Error Flag
						#endif
					}
					else
					{
						retVal = AT91F_US_GetChar(AT91C_BASE_US0); 		//no error, so rx byte is valid
					}
				}

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

	MX_UINT32 baudrate;

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
	else if (new_baud == 7)
	{
		baudrate = 250000;
	}

	UART_Uninit();

	#if (MX_UART_CHANNEL_X == 1)

		#if (MX_UART_RX_EN_X == 1) && (MX_UART_RX_EN_X == 1)
			AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA21_RXD1 | AT91C_PA22_TXD1, 0);
		#else
			#if (MX_UART_RX_EN_X == 1)
				AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA21_RXD1, 0);
			#else
				AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA22_TXD1, 0);
			#endif
		#endif
		AT91F_US1_CfgPMC();

	  #if(MX_UART_DBITS_X == 9)
		AT91F_US_Configure(AT91C_BASE_US1,MCK,AT91C_US_ASYNC_MODE | AT91C_US_MODE9, baudrate, 0);		//9-bit mode
	  #else
		AT91F_US_Configure(AT91C_BASE_US1,MCK,AT91C_US_ASYNC_MODE, baudrate, 0);						//8-bit mode
	  #endif

		#if (MX_UART_TX_EN_X == 1)
			AT91F_US_ResetTx(AT91C_BASE_US1);
			AT91C_BASE_US1->US_CR = AT91C_US_TXEN;						// enable tx
		#endif
		#if (MX_UART_RX_EN_X == 1)
			AT91F_US_ResetRx(AT91C_BASE_US1);
			AT91C_BASE_US1->US_CR = AT91C_US_RXEN;						// enable rx
		#endif

	  #if (MX_UART_INT_X == 1)
	  	//No Flag Clear Instruction Required
	  #endif
	#endif


	#if (MX_UART_CHANNEL_X == 2)
		#if (MX_UART_RX_EN_X == 1) && (MX_UART_RX_EN_X == 1)
			AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA5_RXD0 | AT91C_PA6_TXD0, 0);
		#else
			#if (MX_UART_RX_EN_X == 1)
				AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA5_RXD0, 0);
			#else
				AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA6_TXD0, 0);
			#endif
		#endif
		AT91F_US0_CfgPMC();

	  #if(MX_UART_DBITS_X == 9)
		AT91F_US_Configure(AT91C_BASE_US0,MCK,AT91C_US_ASYNC_MODE | AT91C_US_MODE9,baudrate,0);		//9-bit mode
	  #else
		AT91F_US_Configure(AT91C_BASE_US0,MCK,AT91C_US_ASYNC_MODE,baudrate,0);						//8-bit mode
	  #endif

		#if (MX_UART_TX_EN_X == 1)
			AT91F_US_ResetTx(AT91C_BASE_US0);
			AT91C_BASE_US0->US_CR = AT91C_US_TXEN;						// enable tx
		#endif
		#if (MX_UART_RX_EN_X == 1)
			AT91F_US_ResetRx(AT91C_BASE_US0);
			AT91C_BASE_US0->US_CR = AT91C_US_RXEN;						// enable rx
		#endif

	  #if (MX_UART_INT_X == 1)
	  	//No Flag Clear Instruction Required
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


