// CRC: 5D982BB222882C54AB4AFF20A1590FC484D3178BD0D2510D0F5A64A7853221CAE2C33FABBE4F69A6659399D51781B7B9626B6D0B0830C296350FCD25EAE876BF9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5007F3687EE497233930012FF95A4BBBA84D4A8E9F8FF624BA1E713926F3804ECE610DAE98FFD07643EDCC55CC4BA5B8C879EACBEF4837A5AAF585A93E6A3F5A316C481E645AE7AA00CAA3E060A726DF5662B045258C19883549D34A0D5AD11F38F3792372EDFF5AC5195A48A41DD117C0E45C119C11010BAB54CBE7FC75FC27ACB6057F59853FD1A
// REVISION: 1.0
// GUID: 4980AFE8-B3C2-40AB-BD8B-6AE522758C3B
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\PIC16BIT_CAL_UART.c
/*********************************************************************
 *                  Flowcode CAL UART File
 *
 * File: PIC16BIT_CAL_UART.c
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
 * 230812 | BR | Fixed a bug in the software UART baud calculation defines
 * 070912 | BR | Updated remappable functionality - now loaded via FCD
 * 260912 | BR | Init now auto starts up the transmit functionality and few minor edits to the update baud function
 * 280912 | BR | Port Remappable Definition had changed but code had not - fixed
 * 280912 | BR | Fixed a baud calculation bug for dsPIC33 and PIC24 devices
 * 240413 | LM | Fixed typo re PORT_1 -> PORT_X for Software UART
 * 030713 | LM | Standard API calls
 * 280813 | LM | Removed MX_UART_x define checks
 * 170514 | JK | Fixes for dsPIC33 and dsPIC24 baudrates
 * 300914 | BR | Tried to make the baud calculation a bit more reliable for higher speed bauds at odd crystal frequencies
 */


#ifndef MX_UART_SW_DEFS
	#define MX_UART_SW_DEFS

	#define INST_COUNT	15			//----Need to find a suitable value----//

	//Work out number of nops for software baud rate
	#define MX_INSTRUCTION_SPEED 	(MX_CLK_SPEED / MX_CLKS_PER_INST)
	#define MX_OVERHEAD				(MX_INSTRUCTION_SPEED / INST_COUNT)
	#define SW_OFFSET				(1000000 / MX_OVERHEAD)

	#if (SW_OFFSET < 1)
		#undef SW_OFFSET
		#define SW_OFFSET	0
	#endif

#endif


//Hardware Baud update definitions
#ifndef MX_HARD_BAUD_CHANGE_DEFS
	#define MX_HARD_BAUD_CHANGE_DEFS
	#if defined(__dsPIC33E__) || defined(__dsPIC33F__) || defined(__PIC24E__) || defined(__PIC24F__) || defined(__PIC24H__)
		#define MX_HARD_BAUD_1200	(((MX_CLK_SPEED / 1200) - 8) / 32)		//Was - 16 but had issues with rounding down
		#define MX_HARD_BAUD_2400	(((MX_CLK_SPEED / 2400) - 8) / 32)
		#define MX_HARD_BAUD_4800	(((MX_CLK_SPEED / 4800) - 8) / 32)
		#define MX_HARD_BAUD_9600	(((MX_CLK_SPEED / 9600) - 8) / 32)
		#define MX_HARD_BAUD_19200	(((MX_CLK_SPEED / 19200) - 8) / 32)
		#define MX_HARD_BAUD_38400	(((MX_CLK_SPEED / 38400) - 8) / 32)
		#define MX_HARD_BAUD_57600	(((MX_CLK_SPEED / 57600) - 8) / 32)
		#define MX_HARD_BAUD_115200	(((MX_CLK_SPEED / 115200) - 8) / 32)
		#define MX_HARD_BAUD_250000	(((MX_CLK_SPEED / 250000) - 8) / 32)
	#else
	#define MX_HARD_BAUD_1200	(((MX_CLK_SPEED / 1200) - 8) / 64)
	#define MX_HARD_BAUD_2400	(((MX_CLK_SPEED / 2400) - 8) / 64)		//Was - 16 but had issues with rounding down
	#define MX_HARD_BAUD_4800	(((MX_CLK_SPEED / 4800) - 8) / 64)
	#define MX_HARD_BAUD_9600	(((MX_CLK_SPEED / 9600) - 8) / 64)
	#define MX_HARD_BAUD_19200	(((MX_CLK_SPEED / 19200) - 8) / 64)
	#define MX_HARD_BAUD_38400	(((MX_CLK_SPEED / 38400) - 8) / 64)
	#define MX_HARD_BAUD_57600	(((MX_CLK_SPEED / 57600) - 8) / 64)
	#define MX_HARD_BAUD_115200	(((MX_CLK_SPEED / 115200) - 8) / 64)
	#define MX_HARD_BAUD_250000	(((MX_CLK_SPEED / 250000) - 8) / 64)
	#endif
#endif

#define MX_RECEIVE_DELAY 	(MX_CLK_SPEED / (MX_CLKS_PER_INST * 1000000))


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
	#define MX_SOFT_BAUD_X	1

	#if defined(__dsPIC33E__) || defined(__dsPIC33F__) || defined(__PIC24E__) || defined(__PIC24F__) || defined(__PIC24H__)
		#define MX_HARD_BAUD_X	(((MX_CLK_SPEED / MX_UART_BAUD_X) - 8) / 32)		//Was - 16 but had issues with rounding down
	#else
		#define MX_HARD_BAUD_X	(((MX_CLK_SPEED / MX_UART_BAUD_X) - 8) / 64)		//Was - 16 but had issues with rounding down
	#endif
#endif



//Component Definitions
#define UART_STATUS_LOOP	0
#define UART_STATUS_TIMEOUT	1
#define UART_STATUS_RXBYTE	2


//Interrupt Definitions
#if (MX_UART_INT_X == 1)

	#ifndef MX_UART_INT_DEFS
	#define MX_UART_INT_DEFS

		#define MX_UART_INT_CH1_FUNC	void _ISR _U1RXInterrupt(void)	{
		#define MX_UART_INT_CH2_FUNC	void _ISR _U2RXInterrupt(void)	{
		#define MX_UART_INT_CH3_FUNC	void _ISR _U3RXInterrupt(void)	{
		#define MX_UART_INT_CH4_FUNC	void _ISR _U4RXInterrupt(void)	{
		#define MX_UART_INT_CH5_FUNC	void _ISR _U5RXInterrupt(void)	{
		#define MX_UART_INT_CH6_FUNC	void _ISR _U6RXInterrupt(void)	{
		#define MX_UART_INT_FUNC_END	}

		#define MX_UART_INT_CH1_DET		IFS0bits.U1RXIF && IEC0bits.U1RXIE
		#define MX_UART_INT_CH2_DET		IFS1bits.U2RXIF && IEC1bits.U2RXIE
		#define MX_UART_INT_CH3_DET		IFS5bits.U3RXIF && IEC5bits.U3RXIE
		#define MX_UART_INT_CH4_DET		IFS5bits.U4RXIF && IEC5bits.U4RXIE
		#define MX_UART_INT_CH5_DET		IFS6bits.U5RXIF && IEC6bits.U5RXIE
		#define MX_UART_INT_CH6_DET		IFS7bits.U6RXIF && IEC7bits.U6RXIE

		#define MX_UART_INT_CH1_EN		IEC0bits.U1RXIE = 1
		#define MX_UART_INT_CH2_EN		IEC1bits.U2RXIE = 1
		#define MX_UART_INT_CH3_EN		IEC5bits.U3RXIE = 1
		#define MX_UART_INT_CH4_EN		IEC5bits.U4RXIE = 1
		#define MX_UART_INT_CH5_EN		IEC6bits.U5RXIE = 1
		#define MX_UART_INT_CH6_EN		IEC7bits.U6RXIE = 1

		#define MX_UART_INT_CH1_DIS		IEC0bits.U1RXIE = 0
		#define MX_UART_INT_CH2_DIS		IEC1bits.U2RXIE = 0
		#define MX_UART_INT_CH3_DIS		IEC5bits.U3RXIE = 0
		#define MX_UART_INT_CH4_DIS		IEC5bits.U4RXIE = 0
		#define MX_UART_INT_CH5_DIS		IEC6bits.U5RXIE = 0
		#define MX_UART_INT_CH6_DIS		IEC7bits.U6RXIE = 0

		#define MX_UART_INT_CH1_CLR		IFS0bits.U1RXIF = 0
		#define MX_UART_INT_CH2_CLR		IFS1bits.U2RXIF = 0
		#define MX_UART_INT_CH3_CLR		IFS5bits.U3RXIF = 0
		#define MX_UART_INT_CH4_CLR		IFS5bits.U4RXIF = 0
		#define MX_UART_INT_CH5_CLR		IFS6bits.U5RXIF = 0
		#define MX_UART_INT_CH6_CLR		IFS7bits.U6RXIF = 0

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

	  #ifdef MX_UART_1_REMAPPABLE
	  	#if (MX_UART_TX_EN_X == 1)
			MX_UART_1_TX_RPOR = MX_UART_1_TX_UTX;
		#endif
		#if (MX_UART_RX_EN_X == 1)
			MX_UART_1_RX_RPINR = MX_UART_1_RX_RP;
		#endif
	  #endif

		U1BRG = MX_HARD_BAUD_X; 					// Set the baud rate
		U1STA = 0;    								// Reset the UART
		U1MODE = 0;									// Reset the mode

		#if(MX_UART_DBITS_X == 9)
			U1MODE = U1MODE | 0x0006;				// 9-bit TX & RX
	  	#endif

		U1MODEbits.UARTEN = 1;         				// turn on serial interface 1
		#if (MX_UART_TX_EN_X == 1)
			U1STAbits.UTXEN = 1;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH1_EN;
		#else
			IEC0bits.U1RXIE = 0;
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

		U2BRG = MX_HARD_BAUD_X;   					// Set the baud rate
		U2STA = 0;    								// Reset the UART
		U2MODE = 0;									// Reset the mode

		#if(MX_UART_DBITS_X == 9)
			U2MODE = U2MODE | 0x0006;				// 9-bit TX & RX
	  	#endif

		U2MODEbits.UARTEN = 1;         				// turn on serial interface 2

		#if (MX_UART_TX_EN_X == 1)
			U2STAbits.UTXEN = 1;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH2_EN;
		#else
			IEC1bits.U2RXIE = 0;
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

		U3BRG = MX_HARD_BAUD_X;   					// Set the baud rate
		U3STA = 0;    								// Reset the UART
		U3MODE = 0;									// Reset the mode

		#if(MX_UART_DBITS_X == 9)
			U3MODE = U3MODE | 0x0006;				// 9-bit TX & RX
	  	#endif

		U3MODEbits.UARTEN = 1;         				// turn on serial interface 2

		#if (MX_UART_TX_EN_X == 1)
			U3STAbits.UTXEN = 1;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH3_EN;
		#else
			IEC5bits.U3RXIE = 0;
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

		U4BRG = MX_HARD_BAUD_X;   					// Set the baud rate
		U4STA = 0;    								// Reset the UART
		U4MODE = 0;									// Reset the mode

		#if(MX_UART_DBITS_X == 9)
			U4MODE = U4MODE | 0x0006;				// 9-bit TX & RX
	 	#endif

		U4MODEbits.UARTEN = 1;         				// turn on serial interface 2

		#if (MX_UART_TX_EN_X == 1)
			U4STAbits.UTXEN = 1;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH4_EN;
		#else
			IEC5bits.U4RXIE = 0;
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

		U5BRG = MX_HARD_BAUD_X;   					// Set the baud rate
		U5STA = 0;    								// Reset the UART
		U5MODE = 0;									// Reset the mode

		#if(MX_UART_DBITS_X == 9)
			U5MODE = U5MODE | 0x0006;				// 9-bit TX & RX
	 	#endif

		U5MODEbits.UARTEN = 1;         				// turn on serial interface 2

		#if (MX_UART_TX_EN_X == 1)
			U5STAbits.UTXEN = 1;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH5_EN;
		#else
			IEC6bits.U5RXIE = 0;
		#endif

    #endif

	#if (MX_UART_CHANNEL_X == 6)

	  #ifdef MX_UART_6_REMAPPABLE
	  	#if (MX_UART_TX_EN_X == 1)
			MX_UART_6_TX_RPOR = MX_UART_6_TX_UTX;
		#endif
		#if (MX_UART_RX_EN_X == 1)
			MX_UART_6_RX_RPINR = MX_UART_6_RX_RP;
		#endif
	  #endif

		U6BRG = MX_HARD_BAUD_X;   					// Set the baud rate
		U6STA = 0;    								// Reset the UART
		U6MODE = 0;									// Reset the mode

		#if(MX_UART_DBITS_X == 9)
			U6MODE = U6MODE | 0x0006;				// 9-bit TX & RX
	 	#endif

		U6MODEbits.UARTEN = 1;         				// turn on serial interface 2

		#if (MX_UART_TX_EN_X == 1)
			U6STAbits.UTXEN = 1;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH6_EN;
		#else
			IEC7bits.U6RXIE = 0;
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
		U1STA = 0;    							// Reset the UART
		U1MODE = 0;								// Reset the mode
	  #if (MX_UART_INT_X == 1)
		MX_UART_INT_CH1_DIS;					// Interrupt Disabled
	  #endif
	#endif

	#if (MX_UART_CHANNEL_X == 2)
		U2STA = 0;    							// Reset the UART
		U2MODE = 0;								// Reset the mode
	  #if (MX_UART_INT_X == 1)
		MX_UART_INT_CH2_DIS;					// Interrupt Disabled
	  #endif
	#endif

	#if (MX_UART_CHANNEL_X == 3)
		U3STA = 0;    							// Reset the UART
		U3MODE = 0;								// Reset the mode
	  #if (MX_UART_INT_X == 1)
		MX_UART_INT_CH3_DIS;					// Interrupt Disabled
	  #endif
	#endif

	#if (MX_UART_CHANNEL_X == 5)
		U5STA = 0;    							// Reset the UART
		U5MODE = 0;								// Reset the mode
	  #if (MX_UART_INT_X == 1)
		MX_UART_INT_CH5_DIS;					// Interrupt Disabled
	  #endif
   	#endif

	#if (MX_UART_CHANNEL_X == 6)
		U6STA = 0;    							// Reset the UART
		U6MODE = 0;								// Reset the mode
	  #if (MX_UART_INT_X == 1)
		MX_UART_INT_CH6_DIS;					// Interrupt Disabled
	  #endif
   	#endif

	#if (MX_UART_FLOWEN_X == 1)					//Flowcontrol enabled?
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

			while (U1STAbits.UTXBF != 0);

		  #if (MX_UART_DBITS_X == 9)
			nChar = nChar & 0x01FF;
		  #else
			nChar = nChar & 0xFF;
		  #endif

			U1TXREG = nChar;
		#endif

		#if (MX_UART_CHANNEL_X == 2)
			while (U2STAbits.UTXBF != 0);

		  #if (MX_UART_DBITS_X == 9)
			nChar = nChar & 0x01FF;
		  #else
			nChar = nChar & 0xFF;
		  #endif

			U2TXREG = nChar;
		#endif

		#if (MX_UART_CHANNEL_X == 3)

			while (U3STAbits.UTXBF != 0);

		  #if (MX_UART_DBITS_X == 9)
			nChar = nChar & 0x01FF;
		  #else
			nChar = nChar & 0xFF;
		  #endif

			U3TXREG = nChar;
		#endif

		#if (MX_UART_CHANNEL_X == 4)

			while (U4STAbits.UTXBF != 0);

		  #if (MX_UART_DBITS_X == 9)
			nChar = nChar & 0x01FF;
		  #else
			nChar = nChar & 0xFF;
		  #endif

			U4TXREG = nChar;
		#endif

		#if (MX_UART_CHANNEL_X == 5)

			while (U5STAbits.UTXBF != 0);

		  #if (MX_UART_DBITS_X == 9)
			nChar = nChar & 0x01FF;
		  #else
			nChar = nChar & 0xFF;
		  #endif

			U5TXREG = nChar;
		#endif

		#if (MX_UART_CHANNEL_X == 6)

			while (U6STAbits.UTXBF != 0);

		  #if (MX_UART_DBITS_X == 9)
			nChar = nChar & 0x01FF;
		  #else
			nChar = nChar & 0xFF;
		  #endif

			U6TXREG = nChar;
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

		MX_UINT16 delay1 = 0;
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
					if(delay1 == 25000)
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
					regcheck = U1STAbits.URXDA;
					if (regcheck != 0)
						rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 2)
					regcheck = U2STAbits.URXDA;
					if (regcheck != 0)
						rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 3)
					regcheck = U3STAbits.URXDA;
					if (regcheck != 0)
						rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 4)
					regcheck = U4STAbits.URXDA;
					if (regcheck != 0)
						rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 5)
					regcheck = U5STAbits.URXDA;
					if (regcheck != 0)
						rxStatus = UART_STATUS_RXBYTE;
			#endif

			#if (MX_UART_CHANNEL_X == 6)
					regcheck = U6STAbits.URXDA;
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
				regcheck = U1STAbits.FERR;
				if (regcheck != 0)
				{
					dummy = U1RXREG;     	 			//need to read the rcreg to clear FERR
					#if (MX_UART_RETURN_X == 1)
						retVal = 0x400;					//Framing Error Flag
					#endif
				}
				else
				{
					regcheck = U1STAbits.OERR;
					if (regcheck != 0)
					{
						U1STAbits.OERR = 0;
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x800;				//Overrun Error Flag
						#endif
					}
					else
					{
						retVal = 0;

					  #if (MX_UART_DBITS_X == 9)
						retVal = U1RXREG & 0x1FF;
					  #else
						retVal = U1RXREG & 0xFF;
					  #endif
					}
				}
			#endif

			#if (MX_UART_CHANNEL_X == 2)
				regcheck = U2STAbits.FERR;
				if (regcheck != 0)
				{
					dummy = U2RXREG;     	 			//need to read the rcreg to clear FERR
					#if (MX_UART_RETURN_X == 1)
						retVal = 0x400;					//Framing Error Flag
					#endif
				}
				else
				{
					regcheck = U2STAbits.OERR;
					if (regcheck != 0)
					{
						U2STAbits.OERR = 0;
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x800;				//Overrun Error Flag
						#endif
					}
					else
					{
						retVal = 0;

					  #if (MX_UART_DBITS_X == 9)
						retVal = U2RXREG & 0x1FF;
					  #else
						retVal = U2RXREG & 0xFF;
					  #endif
					}
				}
			#endif

			#if (MX_UART_CHANNEL_X == 3)
				regcheck = U3STAbits.FERR;
				if (regcheck != 0)
				{
					dummy = U3RXREG;     	 			//need to read the rcreg to clear FERR
					#if (MX_UART_RETURN_X == 1)
						retVal = 0x400;					//Framing Error Flag
					#endif
				}
				else
				{
					regcheck = U3STAbits.OERR;
					if (regcheck != 0)
					{
						U3STAbits.OERR = 0;
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x800;				//Overrun Error Flag
						#endif
					}
					else
					{
						retVal = 0;

					  #if (MX_UART_DBITS_X == 9)
						retVal = U3RXREG & 0x1FF;
					  #else
						retVal = U3RXREG & 0xFF;
					  #endif
					}
				}
			#endif

			#if (MX_UART_CHANNEL_X == 4)
				regcheck = U4STAbits.FERR;
				if (regcheck != 0)
				{
					dummy = U4RXREG;     	 			//need to read the rcreg to clear FERR
					#if (MX_UART_RETURN_X == 1)
						retVal = 0x400;					//Framing Error Flag
					#endif
				}
				else
				{
					regcheck = U4STAbits.OERR;
					if (regcheck != 0)
					{
						U4STAbits.OERR = 0;
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x800;				//Overrun Error Flag
						#endif
					}
					else
					{
						retVal = 0;

					  #if (MX_UART_DBITS_X == 9)
						retVal = U4RXREG & 0x1FF;
					  #else
						retVal = U4RXREG & 0xFF;
					  #endif
					}
				}
			#endif

			#if (MX_UART_CHANNEL_X == 5)
				regcheck = U5STAbits.FERR;
				if (regcheck != 0)
				{
					dummy = U5RXREG;     	 			//need to read the rcreg to clear FERR
					#if (MX_UART_RETURN_X == 1)
						retVal = 0x400;					//Framing Error Flag
					#endif
				}
				else
				{
					regcheck = U5STAbits.OERR;
					if (regcheck != 0)
					{
						U5STAbits.OERR = 0;
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x800;				//Overrun Error Flag
						#endif
					}
					else
					{
						retVal = 0;

					  #if (MX_UART_DBITS_X == 9)
						retVal = U5RXREG & 0x1FF;
					  #else
						retVal = U5RXREG & 0xFF;
					  #endif
					}
				}
			#endif

			#if (MX_UART_CHANNEL_X == 6)
				regcheck = U6STAbits.FERR;
				if (regcheck != 0)
				{
					dummy = U6RXREG;     	 			//need to read the rcreg to clear FERR
					#if (MX_UART_RETURN_X == 1)
						retVal = 0x400;					//Framing Error Flag
					#endif
				}
				else
				{
					regcheck = U6STAbits.OERR;
					if (regcheck != 0)
					{
						U6STAbits.OERR = 0;
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x800;				//Overrun Error Flag
						#endif
					}
					else
					{
						retVal = 0;

					  #if (MX_UART_DBITS_X == 9)
						retVal = U6RXREG & 0x1FF;
					  #else
						retVal = U6RXREG & 0xFF;
					  #endif
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

	MX_UINT16 baudrate;

	if (new_baud > 8)
		return;

	if (new_baud == 0)
	{
		baudrate = MX_HARD_BAUD_1200;
	}
	else if (new_baud == 1)
	{
		baudrate = MX_HARD_BAUD_2400;
	}
	else if (new_baud == 2)
	{
		baudrate = MX_HARD_BAUD_4800;
	}
	else if (new_baud == 3)
	{
		baudrate = MX_HARD_BAUD_9600;
	}
	else if (new_baud == 4)
	{
		baudrate = MX_HARD_BAUD_19200;
	}
	else if (new_baud == 5)
	{
		baudrate = MX_HARD_BAUD_38400;
	}
	else if (new_baud == 6)
	{
		baudrate = MX_HARD_BAUD_57600;
	}
	else if (new_baud == 7)
	{
		baudrate = MX_HARD_BAUD_115200;
	}
	else if (new_baud == 8)
	{
		baudrate = MX_HARD_BAUD_250000;
	}

	#if (MX_UART_CHANNEL_X == 1)
		U1MODEbits.UARTEN = 0;         				// turn on serial interface 1
		U1STAbits.UTXEN = 0;
		U1BRG = baudrate; 							// Set the baud rate
		U1MODEbits.UARTEN = 1;         				// turn on serial interface 1
		#if (MX_UART_TX_EN_X == 1)
			U1STAbits.UTXEN = 1;
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 2)
		U2MODEbits.UARTEN = 0;         				// turn on serial interface 1
		U2STAbits.UTXEN = 0;
		U2BRG = baudrate;   						// Set the baud rate
		U2MODEbits.UARTEN = 1;         				// turn on serial interface 1
		#if (MX_UART_TX_EN_X == 1)
			U2STAbits.UTXEN = 1;
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 3)
		U3MODEbits.UARTEN = 0;         				// turn on serial interface 1
		U3STAbits.UTXEN = 0;
		U3BRG = baudrate;   						// Set the baud rate
		U3MODEbits.UARTEN = 1;         				// turn on serial interface 1
		#if (MX_UART_TX_EN_X == 1)
			U3STAbits.UTXEN = 1;
		#endif
	#endif

	#if (MX_UART_CHANNEL_X == 4)
		U4MODEbits.UARTEN = 0;         				// turn on serial interface 1
		U4STAbits.UTXEN = 0;
		U4BRG = baudrate;   						// Set the baud rate
		U4MODEbits.UARTEN = 1;         				// turn on serial interface 1
		#if (MX_UART_TX_EN_X == 1)
			U4STAbits.UTXEN = 1;
		#endif
    #endif

	#if (MX_UART_CHANNEL_X == 5)
		U5MODEbits.UARTEN = 0;         				// turn on serial interface 1
		U5STAbits.UTXEN = 0;
		U5BRG = baudrate;   						// Set the baud rate
		U5MODEbits.UARTEN = 1;         				// turn on serial interface 1
		#if (MX_UART_TX_EN_X == 1)
			U5STAbits.UTXEN = 1;
		#endif
    #endif

	#if (MX_UART_CHANNEL_X == 6)
		U6MODEbits.UARTEN = 0;         				// turn on serial interface 1
		U6STAbits.UTXEN = 0;
		U6BRG = baudrate;   						// Set the baud rate
		U6MODEbits.UARTEN = 1;         				// turn on serial interface 1
		#if (MX_UART_TX_EN_X == 1)
			U6STAbits.UTXEN = 1;
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


