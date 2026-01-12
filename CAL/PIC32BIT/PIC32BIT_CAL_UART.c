// CRC: A6459004C43C0517DC6DFC5681C2AD698104299A14C9E1875427A2F7EF4303D9CFD76A29863CD488DE50EA9D9C0AC8D1626B6D0B0830C296350FCD25EAE876BF9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5C8A3DF1A3E6FE886EB7EE4DD2DC35D22D517B653114401EA525ADCAB15AADA3E2AFD3D66602F7E6E4331B4F1E9B235955487D1B221486C181D66A3077772211C54D5E4129251CCD7564F84014E6CF67F7506036D6262E233549D34A0D5AD11F36EE58F61A350C9C70AD0E9E9F1F6E50D9E6A9E05863576FB
// REVISION: 1.0
// GUID: B7C31651-7B94-4714-A17D-9D35F2B9006C
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\PIC32BIT_CAL_UART.c
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


//Baud Rate Clock Divider - FCD may override with baud dividor of 4 - mostly MZ devices.
#ifndef MX_UART_BAUD_DIV
	#define MX_UART_BAUD_DIV 4
#endif


//Hardware Baud update definitions
#ifndef MX_HARD_BAUD_CHANGE_DEFS
	#define MX_HARD_BAUD_CHANGE_DEFS

	#define MX_HARD_BAUD_1200	((MX_CLK_SPEED / 1200) / MX_UART_BAUD_DIV)
	#define MX_HARD_SLOW_1200	1
	#if (MX_HARD_BAUD_1200 > 65535)
		#undef MX_HARD_BAUD_1200
		#undef MX_HARD_SLOW_1200
		#define MX_HARD_SLOW_1200 	0
		#define MX_HARD_BAUD_1200	(( MX_CLK_SPEED / 1200 ) / (MX_UART_BAUD_DIV * 4))
	#endif

	#define MX_HARD_BAUD_2400	((MX_CLK_SPEED / 2400) / MX_UART_BAUD_DIV)
	#define MX_HARD_SLOW_2400	1
	#if (MX_HARD_BAUD_2400 > 65535)
		#undef MX_HARD_BAUD_2400
		#undef MX_HARD_SLOW_2400
		#define MX_HARD_SLOW_2400 	0
		#define MX_HARD_BAUD_2400	(( MX_CLK_SPEED / 2400 ) / (MX_UART_BAUD_DIV * 4))
	#endif

	#define MX_HARD_BAUD_4800	((MX_CLK_SPEED / 4800) / MX_UART_BAUD_DIV)
	#define MX_HARD_SLOW_4800	1
	#if (MX_HARD_BAUD_4800 > 65535)
		#undef MX_HARD_BAUD_4800
		#undef MX_HARD_SLOW_4800
		#define MX_HARD_SLOW_4800 	0
		#define MX_HARD_BAUD_4800	(( MX_CLK_SPEED / 4800 ) / (MX_UART_BAUD_DIV * 4))
	#endif

	#define MX_HARD_BAUD_9600	((MX_CLK_SPEED / 9600) / MX_UART_BAUD_DIV)
	#define MX_HARD_SLOW_9600	1
	#if (MX_HARD_BAUD_9600 > 65535)
		#undef MX_HARD_BAUD_9600
		#undef MX_HARD_SLOW_9600
		#define MX_HARD_SLOW_9600 	0
		#define MX_HARD_BAUD_9600	(( MX_CLK_SPEED / 9600 ) / (MX_UART_BAUD_DIV * 4))
	#endif

	#define MX_HARD_BAUD_19200	((MX_CLK_SPEED / 19200) / MX_UART_BAUD_DIV)
	#define MX_HARD_SLOW_19200	1
	#if (MX_HARD_BAUD_19200 > 65535)
		#undef MX_HARD_BAUD_19200
		#undef MX_HARD_SLOW_19200
		#define MX_HARD_SLOW_19200 	0
		#define MX_HARD_BAUD_19200	(( MX_CLK_SPEED / 19200 ) / (MX_UART_BAUD_DIV * 4))
	#endif

	#define MX_HARD_BAUD_38400	((MX_CLK_SPEED / 38400) / MX_UART_BAUD_DIV)
	#define MX_HARD_SLOW_38400	1
	#if (MX_HARD_BAUD_38400 > 65535)
		#undef MX_HARD_BAUD_38400
		#undef MX_HARD_SLOW_38400
		#define MX_HARD_SLOW_38400 	0
		#define MX_HARD_BAUD_38400	(( MX_CLK_SPEED / 38400 ) / (MX_UART_BAUD_DIV * 4))
	#endif

	#define MX_HARD_BAUD_57600	((MX_CLK_SPEED / 57600) / MX_UART_BAUD_DIV)
	#define MX_HARD_SLOW_57600	1
	#if (MX_HARD_BAUD_57600 > 65535)
		#undef MX_HARD_BAUD_57600
		#undef MX_HARD_SLOW_57600
		#define MX_HARD_SLOW_57600 	0
		#define MX_HARD_BAUD_57600	(( MX_CLK_SPEED / 57600 ) / (MX_UART_BAUD_DIV * 4))
	#endif

	#define MX_HARD_BAUD_115200	((MX_CLK_SPEED / 115200) / MX_UART_BAUD_DIV)
	#define MX_HARD_SLOW_115200	1
	#if (MX_HARD_BAUD_115200 > 65535)
		#undef MX_HARD_BAUD_115200
		#undef MX_HARD_SLOW_115200
		#define MX_HARD_SLOW_115200 	0
		#define MX_HARD_BAUD_115200	(( MX_CLK_SPEED / 115200 ) / (MX_UART_BAUD_DIV * 4))
	#endif

	#define MX_HARD_BAUD_250000	((MX_CLK_SPEED / 250000) / MX_UART_BAUD_DIV)
	#define MX_HARD_SLOW_250000	1
	#if (MX_HARD_BAUD_250000 > 65535)
		#undef MX_HARD_BAUD_250000
		#undef MX_HARD_SLOW_250000
		#define MX_HARD_SLOW_250000 	0
		#define MX_HARD_BAUD_250000	(( MX_CLK_SPEED / 250000 ) / (MX_UART_BAUD_DIV * 4))
	#endif

#endif

#define MX_RECEIVE_DELAY 	(MX_CLK_SPEED / (MX_CLKS_PER_INST * 100000))


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
	#define MX_HARD_BAUD_X	(( MX_CLK_SPEED / MX_UART_BAUD_X ) / MX_UART_BAUD_DIV)
	#define MX_HARD_SLOW 1
	#if (MX_HARD_BAUD_X > 65535)
		#undef MX_HARD_BAUD_X
		#undef MX_HARD_SLOW
		#define MX_HARD_SLOW 0
		#define MX_HARD_BAUD_X	(( MX_CLK_SPEED / MX_UART_BAUD_X ) / (MX_UART_BAUD_DIV * 4))
	#endif
#endif


//Component Definitions
#define UART_STATUS_LOOP	0
#define UART_STATUS_TIMEOUT	1
#define UART_STATUS_RXBYTE	2


//Interrupt Definitions
//#if (MX_UART_INT_X == 1)

	#ifndef MX_UART_INT_DEFS
	#define MX_UART_INT_DEFS


		#ifdef _UART1_RX_VECTOR
			#define MX_UART_INT_CH1_FUNC	void __ISR(_UART1_RX_VECTOR, ipl1AUTO) _IntHandlerDrvUsartReceiveInstance0(void){
		#else
			#define MX_UART_INT_CH1_FUNC	void __ISR(_UART_1_VECTOR, ipl1AUTO) _IntHandlerDrvUsartReceiveInstance0(void){
		#endif

		#ifdef _UART2_RX_VECTOR
			#define MX_UART_INT_CH2_FUNC	void __ISR(_UART2_RX_VECTOR, ipl1AUTO) _IntHandlerDrvUsartReceiveInstance1(void){
		#else
			#define MX_UART_INT_CH2_FUNC	void __ISR(_UART_2_VECTOR, ipl1AUTO) _IntHandlerDrvUsartReceiveInstance1(void){
		#endif

		#ifdef _UART3_RX_VECTOR
			#define MX_UART_INT_CH3_FUNC	void __ISR(_UART3_RX_VECTOR, ipl1AUTO) _IntHandlerDrvUsartReceiveInstance2(void){
		#else
			#define MX_UART_INT_CH3_FUNC	void __ISR(_UART_3_VECTOR, ipl1AUTO) _IntHandlerDrvUsartReceiveInstance2(void){
		#endif

		#ifdef _UART4_RX_VECTOR
			#define MX_UART_INT_CH4_FUNC	void __ISR(_UART4_RX_VECTOR, ipl1AUTO) _IntHandlerDrvUsartReceiveInstance3(void){
		#else
			#define MX_UART_INT_CH4_FUNC	void __ISR(_UART_4_VECTOR, ipl1AUTO) _IntHandlerDrvUsartReceiveInstance3(void){
		#endif

		#ifdef _UART5_RX_VECTOR
			#define MX_UART_INT_CH5_FUNC	void __ISR(_UART5_RX_VECTOR, ipl1AUTO) _IntHandlerDrvUsartReceiveInstance4(void){
		#else
			#define MX_UART_INT_CH5_FUNC	void __ISR(_UART_5_VECTOR, ipl1AUTO) _IntHandlerDrvUsartReceiveInstance4(void){
		#endif

		#ifdef _UART6_RX_VECTOR
			#define MX_UART_INT_CH6_FUNC	void __ISR(_UART6_RX_VECTOR, ipl1AUTO) _IntHandlerDrvUsartReceiveInstance5(void){
		#else
			#define MX_UART_INT_CH6_FUNC	void __ISR(_UART_6_VECTOR, ipl1AUTO) _IntHandlerDrvUsartReceiveInstance5(void){
		#endif

		#define MX_UART_INT_FUNC_END	}


		#ifdef _IEC3_U1RXIE_POSITION
			#define MX_UART_INT_CH1_DET		IFS3bits.U1RXIF && IEC3bits.U1RXIE
		#else
			#ifdef _IEC1_U1RXIE_POSITION
				#define MX_UART_INT_CH1_DET		IFS1bits.U1RXIF && IEC1bits.U1RXIE
			#else
				#define MX_UART_INT_CH1_DET		IFS0bits.U1RXIF && IEC0bits.U1RXIE
			#endif
		#endif

		#ifdef _IEC4_U2RXIE_POSITION
			#define MX_UART_INT_CH2_DET		IFS4bits.U2RXIF && IEC4bits.U2RXIE
		#else
			#define MX_UART_INT_CH2_DET		IFS1bits.U2RXIF && IEC1bits.U2RXIE
		#endif

		#ifdef _IEC4_U3RXIE_POSITION
			#define MX_UART_INT_CH3_DET		IFS4bits.U3RXIF && IEC4bits.U3RXIE
		#else
		    #ifdef _IEC1_U3RXIE_POSITION
		    	#define MX_UART_INT_CH3_DET		IFS1bits.U3RXIF && IEC1bits.U3RXIE
		    #else
				#define MX_UART_INT_CH3_DET		IFS5bits.U3RXIF && IEC5bits.U3RXIE
			#endif
		#endif

		#ifdef _IFS2_U4RXIF_POSITION
			#define MX_UART_INT_CH4_DET		IFS2bits.U4RXIF && IEC2bits.U4RXIE
		#else
			#define MX_UART_INT_CH4_DET		IFS5bits.U4RXIF && IEC5bits.U4RXIE
		#endif

		#ifdef _IFS2_U5RXIF_POSITION
			#define MX_UART_INT_CH5_DET		IFS2bits.U5RXIF && IEC2bits.U5RXIE
		#else
			#define MX_UART_INT_CH5_DET		IFS5bits.U5RXIF && IEC5bits.U5RXIE
		#endif

		#ifdef _IFS2_U6RXIF_POSITION
			#define MX_UART_INT_CH6_DET		IFS2bits.U6RXIF && IEC2bits.U6RXIE
		#else
			#define MX_UART_INT_CH6_DET		IFS5bits.U6RXIF && IEC5bits.U6RXIE
		#endif



		#ifdef _IEC3_U1RXIE_POSITION
			#define MX_UART_INT_CH1_EN		IEC3bits.U1RXIE = 1
		#else
			#ifdef _IEC1_U1RXIE_POSITION
				#define MX_UART_INT_CH1_EN		IEC1bits.U1RXIE = 1
			#else
				#define MX_UART_INT_CH1_EN		IEC0bits.U1RXIE = 1
			#endif
		#endif

		#ifdef _IEC4_U2RXIE_POSITION
			#define MX_UART_INT_CH2_EN		IEC4bits.U2RXIE = 1
		#else
			#define MX_UART_INT_CH2_EN		IEC1bits.U2RXIE = 1
		#endif

		#ifdef _IEC4_U3RXIE_POSITION
			#define MX_UART_INT_CH3_EN		IEC4bits.U3RXIE = 1
		#else
			#ifdef _IEC1_U3RXIE_POSITION
				#define MX_UART_INT_CH3_EN		IEC1bits.U3RXIE = 1
			#else
				#define MX_UART_INT_CH3_EN		IEC5bits.U3RXIE = 1
			#endif
		#endif

		#ifdef _IFS2_U4RXIF_POSITION
			#define MX_UART_INT_CH4_EN		IEC2bits.U4RXIE = 1
		#else
			#define MX_UART_INT_CH4_EN		IEC5bits.U4RXIE = 1
		#endif

		#ifdef _IFS2_U5RXIF_POSITION
			#define MX_UART_INT_CH5_EN		IEC2bits.U5RXIE = 1
		#else
			#define MX_UART_INT_CH5_EN		IEC5bits.U5RXIE = 1
		#endif

		#ifdef _IFS2_U6RXIF_POSITION
			#define MX_UART_INT_CH6_EN		IEC2bits.U6RXIE = 1
		#else
			#define MX_UART_INT_CH6_EN		IEC5bits.U6RXIE = 1
		#endif



		#ifdef _IEC3_U1RXIE_POSITION
			#define MX_UART_INT_CH1_DIS		IEC3bits.U1RXIE = 0
		#else
			#ifdef _IEC1_U1RXIE_POSITION
				#define MX_UART_INT_CH1_DIS		IEC1bits.U1RXIE = 0
			#else
				#define MX_UART_INT_CH1_DIS		IEC0bits.U1RXIE = 0
			#endif
		#endif

		#ifdef _IEC4_U2RXIE_POSITION
			#define MX_UART_INT_CH2_DIS		IEC4bits.U2RXIE = 0
		#else
			#define MX_UART_INT_CH2_DIS		IEC1bits.U2RXIE = 0
		#endif

		#ifdef _IEC4_U3TXIE_POSITION
			#define MX_UART_INT_CH3_DIS		IEC4bits.U3RXIE = 0
		#else
			#ifdef _IEC1_U3RXIE_POSITION
				#define MX_UART_INT_CH3_DIS		IEC1bits.U3RXIE = 0
			#else
				#define MX_UART_INT_CH3_DIS		IEC5bits.U3RXIE = 0
			#endif
		#endif

		#ifdef _IFS2_U4RXIF_POSITION
			#define MX_UART_INT_CH4_DIS		IEC2bits.U4RXIE = 0
		#else
			#define MX_UART_INT_CH4_DIS		IEC5bits.U4RXIE = 0
		#endif

		#ifdef _IFS2_U5RXIF_POSITION
			#define MX_UART_INT_CH5_DIS		IEC2bits.U5RXIE = 0
		#else
			#define MX_UART_INT_CH5_DIS		IEC5bits.U5RXIE = 0
		#endif

		#ifdef _IFS2_U6RXIF_POSITION
			#define MX_UART_INT_CH6_DIS		IEC2bits.U6RXIE = 0
		#else
			#define MX_UART_INT_CH6_DIS		IEC5bits.U6RXIE = 0
		#endif



		#ifdef _IEC3_U1RXIE_POSITION
			#define MX_UART_INT_CH1_CLR		IFS3bits.U1RXIF = 0
		#else
			#ifdef _IEC1_U1RXIE_POSITION
				#define MX_UART_INT_CH1_CLR		IFS1bits.U1RXIF = 0
			#else
				#define MX_UART_INT_CH1_CLR		IFS0bits.U1RXIF = 0
			#endif
		#endif

		#ifdef _IEC4_U2RXIE_POSITION
			#define MX_UART_INT_CH2_CLR		IFS4bits.U2RXIF = 0
		#else
			#define MX_UART_INT_CH2_CLR		IFS1bits.U2RXIF = 0
		#endif

		#ifdef _IEC4_U3TXIE_POSITION
			#define MX_UART_INT_CH3_CLR		IFS4bits.U3RXIF = 0
		#else
			#ifdef _IEC1_U3RXIE_POSITION
				#define MX_UART_INT_CH3_CLR		IFS1bits.U3RXIF = 0
			#else
				#define MX_UART_INT_CH3_CLR		IFS5bits.U3RXIF = 0
			#endif
		#endif

		#ifdef _IFS2_U4RXIF_POSITION
			#define MX_UART_INT_CH4_CLR		IFS2bits.U4RXIF = 0
		#else
			#define MX_UART_INT_CH4_CLR		IFS5bits.U4RXIF = 0
		#endif

		#ifdef _IFS2_U5RXIF_POSITION
			#define MX_UART_INT_CH5_CLR		IFS2bits.U5RXIF = 0
		#else
			#define MX_UART_INT_CH5_CLR		IFS5bits.U5RXIF = 0
		#endif

		#ifdef _IFS2_U6RXIF_POSITION
			#define MX_UART_INT_CH6_CLR		IFS2bits.U6RXIF = 0
		#else
			#define MX_UART_INT_CH6_CLR		IFS5bits.U6RXIF = 0
		#endif



		//UART Interrupt Priority Register Location
		#ifdef _IPC6_U1IP_POSITION
			#define MX_UART_PRIORITY_CH1	IPC6bits.U1IP
		#endif
		#ifdef _IPC7_U1IP_POSITION
			#define MX_UART_PRIORITY_CH1	IPC7bits.U1IP
		#endif
		#ifdef _IPC28_U1RXIP_POSITION
			#define MX_UART_PRIORITY_CH1	IPC28bits.U1RXIP
		#endif

		#ifdef _IPC8_U2IP_POSITION
			#define MX_UART_PRIORITY_CH2	IPC8bits.U2IP
		#endif
		#ifdef _IPC9_U2IP_POSITION
			#define MX_UART_PRIORITY_CH2	IPC9bits.U2IP
		#endif
		#ifdef _IPC36_U2RXIP_POSITION
			#define MX_UART_PRIORITY_CH2	IPC36bits.U2RXIP
		#endif

		#ifdef _IPC7_U3IP_POSITION
			#define MX_UART_PRIORITY_CH3	IPC7bits.U3IP
		#endif
		#ifdef _IPC9_U3IP_POSITION
			#define MX_UART_PRIORITY_CH3	IPC9bits.U3IP
		#endif
		#ifdef _IPC39_U3RXIP_POSITION
			#define MX_UART_PRIORITY_CH3	IPC39bits.U3RXIP
		#endif

		#ifdef _IPC9_U4IP_POSITION
			#define MX_UART_PRIORITY_CH4	IPC9bits.U4IP
		#endif
		#ifdef _IPC12_U4IP_POSITION
			#define MX_UART_PRIORITY_CH4	IPC12bits.U4IP
		#endif
		#ifdef _IPC42_U4RXIP_POSITION
			#define MX_UART_PRIORITY_CH4	IPC42bits.U4RXIP
		#endif

		#ifdef _IPC10_U5IP_POSITION
			#define MX_UART_PRIORITY_CH5	IPC10bits.U5IP
		#endif
		#ifdef _IPC12_U5IP_POSITION
			#define MX_UART_PRIORITY_CH5	IPC12bits.U5IP
		#endif
		#ifdef _IPC45_U5RXIP_POSITION
			#define MX_UART_PRIORITY_CH5	IPC45bits.U5RXIP
		#endif

		#ifdef _IPC12_U6IP_POSITION
			#define MX_UART_PRIORITY_CH6	IPC12bits.U6IP
		#endif
		#ifdef _IPC47_U6RXIP_POSITION
			#define MX_UART_PRIORITY_CH6	IPC47bits.U6RXIP
		#endif

	#endif
//#endif


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

		U1BRG = MX_HARD_BAUD_X;   					// Set the baud rate
		U1STA = 0;    								// Reset the UART
		U1MODE = 0;									// Reset the mode

		U1MODEbits.BRGH = MX_HARD_SLOW;				// Fast/Slow Baud Mode

		#if(MX_UART_DBITS_X == 9)
			U1MODEbits.PDSEL = 3;					// 9-bit TX & RX
	  	#endif

		U1MODEbits.UARTEN = 1;         				// Switch on serial interface

		#if (MX_UART_TX_EN_X == 1)
			U1STAbits.UTXEN = 1;
		#endif
		#if (MX_UART_RX_EN_X == 1)
			U1STAbits.URXEN = 1;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH1_EN;
			MX_UART_PRIORITY_CH1 = 1;				//1 = Low Priority
			INTCONbits.MVEC = 1;
			__builtin_mtc0(12,0,(__builtin_mfc0(12,0) | 0x0001));

		#else
			MX_UART_INT_CH1_DIS;
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

		U2MODEbits.BRGH = MX_HARD_SLOW;				// Fast/Slow Baud Mode

		#if(MX_UART_DBITS_X == 9)
			U2MODEbits.PDSEL = 3;					// 9-bit TX & RX
	  	#endif

		U2MODEbits.UARTEN = 1;         				// Switch on serial interface

		#if (MX_UART_TX_EN_X == 1)
			U2STAbits.UTXEN = 1;
		#endif
		#if (MX_UART_RX_EN_X == 1)
			U2STAbits.URXEN = 1;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH2_EN;
			MX_UART_PRIORITY_CH2 = 1;				//1 = Low Priority
			INTCONbits.MVEC = 1;
			__builtin_mtc0(12,0,(__builtin_mfc0(12,0) | 0x0001));
		#else
			MX_UART_INT_CH2_DIS;
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

		U3MODEbits.BRGH = MX_HARD_SLOW;				// Fast/Slow Baud Mode

		#if(MX_UART_DBITS_X == 9)
			U3MODEbits.PDSEL = 3;					// 9-bit TX & RX
	  	#endif

		U3MODEbits.UARTEN = 1;         				// Switch on serial interface

		#if (MX_UART_TX_EN_X == 1)
			U3STAbits.UTXEN = 1;
		#endif
		#if (MX_UART_RX_EN_X == 1)
			U3STAbits.URXEN = 1;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH3_EN;
			MX_UART_PRIORITY_CH3 = 1;				//1 = Low Priority
			INTCONbits.MVEC = 1;
			__builtin_mtc0(12,0,(__builtin_mfc0(12,0) | 0x0001));
		#else
			MX_UART_INT_CH3_DIS;
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

		U4MODEbits.BRGH = MX_HARD_SLOW;				// Fast/Slow Baud Mode

		#if(MX_UART_DBITS_X == 9)
			U4MODEbits.PDSEL = 3;					// 9-bit TX & RX
	  	#endif

		U4MODEbits.UARTEN = 1;         				// Switch on serial interface

		#if (MX_UART_TX_EN_X == 1)
			U4STAbits.UTXEN = 1;
		#endif
		#if (MX_UART_RX_EN_X == 1)
			U4STAbits.URXEN = 1;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH4_EN;
			MX_UART_PRIORITY_CH4 = 1;				//1 = Low Priority
			INTCONbits.MVEC = 1;
			__builtin_mtc0(12,0,(__builtin_mfc0(12,0) | 0x0001));
		#else
			MX_UART_INT_CH4_DIS;
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

		U5MODEbits.BRGH = MX_HARD_SLOW;				// Fast/Slow Baud Mode

		#if(MX_UART_DBITS_X == 9)
			U5MODEbits.PDSEL = 3;					// 9-bit TX & RX
	  	#endif

		U5MODEbits.UARTEN = 1;         				// Switch on serial interface

		#if (MX_UART_TX_EN_X == 1)
			U5STAbits.UTXEN = 1;
		#endif
		#if (MX_UART_RX_EN_X == 1)
			U5STAbits.URXEN = 1;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH5_EN;
			MX_UART_PRIORITY_CH5 = 1;				//1 = Low Priority
			INTCONbits.MVEC = 1;
			__builtin_mtc0(12,0,(__builtin_mfc0(12,0) | 0x0001));
		#else
			MX_UART_INT_CH5_DIS;
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

		U6MODEbits.BRGH = MX_HARD_SLOW;				// Fast/Slow Baud Mode

		#if(MX_UART_DBITS_X == 9)
			U6MODEbits.PDSEL = 3;					// 9-bit TX & RX
	  	#endif

		U6MODEbits.UARTEN = 1;         				// Switch on serial interface

		#if (MX_UART_TX_EN_X == 1)
			U6STAbits.UTXEN = 1;
		#endif
		#if (MX_UART_RX_EN_X == 1)
			U6STAbits.URXEN = 1;
		#endif

		#if (MX_UART_INT_X == 1)
			MX_UART_INT_CH6_EN;
			MX_UART_PRIORITY_CH6 = 1;				//1 = Low Priority
			INTCONbits.MVEC = 1;
			__builtin_mtc0(12,0,(__builtin_mfc0(12,0) | 0x0001));
		#else
			MX_UART_INT_CH6_DIS;
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
		U1STA = 0;
		U1MODE = 0;								// Reset the mode
	  #if (MX_UART_INT_X == 1)
		MX_UART_INT_CH1_DIS;					// Interrupt Disabled
	  #endif
	#endif

	#if (MX_UART_CHANNEL_X == 2)
		U2STA = 0;
		U2MODE = 0;
	  #if (MX_UART_INT_X == 1)
		MX_UART_INT_CH2_DIS;					// Interrupt Disabled
	  #endif
	#endif

	#if (MX_UART_CHANNEL_X == 3)
		U3STA = 0;
		U3MODE = 0;
	  #if (MX_UART_INT_X == 1)
		MX_UART_INT_CH3_DIS;					// Interrupt Disabled
	  #endif
	#endif

	#if (MX_UART_CHANNEL_X == 4)
		U4STA = 0;
		U4MODE = 0;
	  #if (MX_UART_INT_X == 1)
		MX_UART_INT_CH4_DIS;					// Interrupt Disabled
	  #endif
   	#endif

	#if (MX_UART_CHANNEL_X == 5)
		U5STA = 0;
		U5MODE = 0;
	  #if (MX_UART_INT_X == 1)
		MX_UART_INT_CH5_DIS;					// Interrupt Disabled
	  #endif
   	#endif

	#if (MX_UART_CHANNEL_X == 6)
		U6STA = 0;
		U6MODE = 0;
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

		#if (MX_UART_CHANNEL_X > 0)
			while (_SFR_BIT_READ(&U1STA + (0x80*(MX_UART_CHANNEL_X-1)),9) == 1);
		  #if (MX_UART_DBITS_X == 9)
			nChar = nChar & 0x01FF;
		  #else
			nChar = nChar & 0xFF;
		  #endif
			_SFR_WRITE(&U1TXREG + (0x80*(MX_UART_CHANNEL_X-1)),nChar);
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

			#if (MX_UART_CHANNEL_X > 0)
					regcheck = _SFR_BIT_READ(&U1STA + (0x80*(MX_UART_CHANNEL_X-1)),0);
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

			#if (MX_UART_CHANNEL_X > 0)
				regcheck = _SFR_BIT_READ(&U1STA + (0x80*(MX_UART_CHANNEL_X-1)),2);
				if (regcheck != 0)
				{
					dummy = _SFR_READ(&U1RXREG + (0x80*(MX_UART_CHANNEL_X-1)));
					#if (MX_UART_RETURN_X == 1)
						retVal = 0x400;					//Framing Error Flag
					#endif
				}
				else
				{
					regcheck = _SFR_BIT_READ(&U1STA + (0x80*(MX_UART_CHANNEL_X-1)),1);
					if (regcheck != 0)
					{
						_SFR_BIT_CLEAR(&U1STA + (0x80*(MX_UART_CHANNEL_X-1)),1);
						#if (MX_UART_RETURN_X == 1)
							retVal = 0x800;				//Overrun Error Flag
						#endif
					}
					else
					{
						retVal = 0;

					  #if (MX_UART_DBITS_X == 9)
						retVal = _SFR_READ(&U1RXREG + (0x80*(MX_UART_CHANNEL_X-1))) & 0x1FF;
					  #else
						retVal = _SFR_READ(&U1RXREG + (0x80*(MX_UART_CHANNEL_X-1))) & 0xFF;
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
	MX_UINT8 bauddiv;

	if (new_baud > 8)
		return;

	if (new_baud == 0)
	{
		baudrate = MX_HARD_BAUD_1200;
		bauddiv = MX_HARD_SLOW_1200;
	}
	else if (new_baud == 1)
	{
		baudrate = MX_HARD_BAUD_2400;
		bauddiv = MX_HARD_SLOW_2400;
	}
	else if (new_baud == 2)
	{
		baudrate = MX_HARD_BAUD_4800;
		bauddiv = MX_HARD_SLOW_4800;
	}
	else if (new_baud == 3)
	{
		baudrate = MX_HARD_BAUD_9600;
		bauddiv = MX_HARD_SLOW_9600;
	}
	else if (new_baud == 4)
	{
		baudrate = MX_HARD_BAUD_19200;
		bauddiv = MX_HARD_SLOW_19200;
	}
	else if (new_baud == 5)
	{
		baudrate = MX_HARD_BAUD_38400;
		bauddiv = MX_HARD_SLOW_38400;
	}
	else if (new_baud == 6)
	{
		baudrate = MX_HARD_BAUD_57600;
		bauddiv = MX_HARD_SLOW_57600;
	}
	else if (new_baud == 7)
	{
		baudrate = MX_HARD_BAUD_115200;
		bauddiv = MX_HARD_SLOW_115200;
	}
	else if (new_baud == 8)
	{
		baudrate = MX_HARD_BAUD_250000;
		bauddiv = MX_HARD_SLOW_250000;
	}

	#if (MX_UART_CHANNEL_X == 1)
		U1MODEbits.BRGH = bauddiv;				// Fast/Slow Baud Mode
		U1BRG = baudrate;   					// Set the baud rate
	#endif

	#if (MX_UART_CHANNEL_X == 2)
		U2MODEbits.BRGH = bauddiv;				// Fast/Slow Baud Mode
		U2BRG = baudrate;   					// Set the baud rate
	#endif

	#if (MX_UART_CHANNEL_X == 3)
		U3MODEbits.BRGH = bauddiv;				// Fast/Slow Baud Mode
		U3BRG = baudrate;   					// Set the baud rate
	#endif

	#if (MX_UART_CHANNEL_X == 4)
		U4MODEbits.BRGH = bauddiv;				// Fast/Slow Baud Mode
		U4BRG = baudrate;   					// Set the baud rate
	#endif

	#if (MX_UART_CHANNEL_X == 5)
		U5MODEbits.BRGH = bauddiv;				// Fast/Slow Baud Mode
		U5BRG = baudrate;   					// Set the baud rate
	#endif

	#if (MX_UART_CHANNEL_X == 6)
		U6MODEbits.BRGH = bauddiv;				// Fast/Slow Baud Mode
		U6BRG = baudrate;   					// Set the baud rate
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


#undef MX_HARD_SLOW

