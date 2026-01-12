// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BE7E28FE73F0197C0C4D63430680B7A772186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF55BD5EEC220EE0B8788C913ED3099C41C01B3F0FC65D3C7B8687534771809B733E427FCB6472B2D1365BF8F928E7003834383D1C6578F97D6FBDB03A1A26E5134F14BA9355CCDD5A247BF5C49B72983E6B254306AC2F96ADB549D34A0D5AD11F32266C1F28664BA521596AB7C5B52897455B83FB5639D0A02D2AD5B899D5932CF499F10447F50333B
// REVISION: 1.0
// GUID: 53DEE894-165D-48B3-B7AB-DDD3ADA35E8D
// DATE: 08\08\2022
// DIR: CAL\STARM\STARM_CAL_CAN.c
/*********************************************************************
 *                  Flowcode CAL CAN File
 *
 * File: STARM_CAL_CAN.c
 *
 * (c) 2011-2019 Matrix TSL
 * http://www.matrixtsl.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
 * Company) for its Flowcode graphical programming language is
 * intended and supplied to you, the Companys customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN AS IS CONDITION. NO WARRANTIES,
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
 * 280519 | LM | Created 
 * 
 */

#ifndef STARM_CAL_CAN_DEF
	#define STARM_CAL_CAN_DEF
	#define MX_CAN_REJECT_ALL 	(0)
	#define MX_CAN_USE_FILTERS	(1)
	#define MX_CAN_ACCEPT_ALL 	(2)
#endif

//Function Prototypes
CALFUNCTION(void, FC_CAL_Internal_CAN_Init_, (void));
CALFUNCTION(void, FC_CAL_Internal_CAN_Uninit_, (void));
CALFUNCTION(void, FC_CAL_Internal_CAN_SendBuffer_, (MX_UINT8 buffer));
CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_CheckRx_, (MX_UINT8 buffer));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxData_, (MX_UINT8 buffer, MX_UINT8 data_cnt, MX_UINT8 d0, MX_UINT8 d1, MX_UINT8 d2, MX_UINT8 d3, MX_UINT8 d4, MX_UINT8 d5, MX_UINT8 d6, MX_UINT8 d7));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdentStd_, (MX_UINT8 buffer, MX_UINT8 hi, MX_UINT8 lo));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdentExd_, (MX_UINT8 buffer, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilterStd_, (MX_UINT8 filter, MX_UINT8 hi, MX_UINT8 lo));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilterExd_, (MX_UINT8 filter, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskStd_, (MX_UINT8 filter, MX_UINT8 hi, MX_UINT8 lo));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskExd_, (MX_UINT8 filter, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0));

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMask_, (MX_UINT8 mask, MX_UINT32 id));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilter_, (MX_UINT8 filter, MX_UINT32 id));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdent_, (MX_UINT8 buffer, MX_UINT32 id));
CALFUNCTION(MX_UINT32, FC_CAL_Internal_CAN_GetRxIdent_, (MX_UINT8 buffer));
CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxDataCount_, (MX_UINT8 buffer));
CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxData_, (MX_UINT8 buffer, MX_UINT8 index));

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxBank_, (MX_UINT8 bank));


#define MX_CAN_CHANNEL_X		CAL_APPEND(MX_CAN_CHANNEL_, MX_CAN_NUM)
#define MX_CAN_CFG_X			CAL_APPEND(MX_CAN_CFG_, MX_CAN_NUM)
#define MX_CAN_EXID_X			CAL_APPEND(MX_CAN_EXID_, MX_CAN_NUM)

#define MX_CAN_RXB0CFG_X		CAL_APPEND(MX_CAN_RXB0CFG_, MX_CAN_NUM)
#define MX_CAN_RXB1CFG_X		CAL_APPEND(MX_CAN_RXB1CFG_, MX_CAN_NUM)

#define MX_CAN_RXM0_X			(MX_UINT32)CAL_APPEND(MX_CAN_RXM0_, MX_CAN_NUM)
#define MX_CAN_RXM1_X			(MX_UINT32)CAL_APPEND(MX_CAN_RXM1_, MX_CAN_NUM)

#define MX_CAN_RXF0_X			(MX_UINT32)CAL_APPEND(MX_CAN_RXF0_, MX_CAN_NUM)
#define MX_CAN_RXF1_X			(MX_UINT32)CAL_APPEND(MX_CAN_RXF1_, MX_CAN_NUM)
#define MX_CAN_RXF2_X			(MX_UINT32)CAL_APPEND(MX_CAN_RXF2_, MX_CAN_NUM)
#define MX_CAN_RXF3_X			(MX_UINT32)CAL_APPEND(MX_CAN_RXF3_, MX_CAN_NUM)
#define MX_CAN_RXF4_X			(MX_UINT32)CAL_APPEND(MX_CAN_RXF4_, MX_CAN_NUM)
#define MX_CAN_RXF5_X			(MX_UINT32)CAL_APPEND(MX_CAN_RXF5_, MX_CAN_NUM)

#define MX_CAN_TXB0ID_X			(MX_UINT32)CAL_APPEND(MX_CAN_TXB0ID_, MX_CAN_NUM)
#define MX_CAN_TXB0LEN_X		CAL_APPEND(MX_CAN_TXB0LEN_, MX_CAN_NUM)
#define MX_CAN_TXB0DB0_X		CAL_APPEND(MX_CAN_TXB0DB0_, MX_CAN_NUM)
#define MX_CAN_TXB0DB1_X		CAL_APPEND(MX_CAN_TXB0DB1_, MX_CAN_NUM)
#define MX_CAN_TXB0DB2_X		CAL_APPEND(MX_CAN_TXB0DB2_, MX_CAN_NUM)
#define MX_CAN_TXB0DB3_X		CAL_APPEND(MX_CAN_TXB0DB3_, MX_CAN_NUM)
#define MX_CAN_TXB0DB4_X		CAL_APPEND(MX_CAN_TXB0DB4_, MX_CAN_NUM)
#define MX_CAN_TXB0DB5_X		CAL_APPEND(MX_CAN_TXB0DB5_, MX_CAN_NUM)
#define MX_CAN_TXB0DB6_X		CAL_APPEND(MX_CAN_TXB0DB6_, MX_CAN_NUM)
#define MX_CAN_TXB0DB7_X		CAL_APPEND(MX_CAN_TXB0DB7_, MX_CAN_NUM)

#define MX_CAN_TXB1ID_X			(MX_UINT32)CAL_APPEND(MX_CAN_TXB1ID_, MX_CAN_NUM)
#define MX_CAN_TXB1LEN_X		CAL_APPEND(MX_CAN_TXB1LEN_, MX_CAN_NUM)
#define MX_CAN_TXB1DB0_X		CAL_APPEND(MX_CAN_TXB1DB0_, MX_CAN_NUM)
#define MX_CAN_TXB1DB1_X		CAL_APPEND(MX_CAN_TXB1DB1_, MX_CAN_NUM)
#define MX_CAN_TXB1DB2_X		CAL_APPEND(MX_CAN_TXB1DB2_, MX_CAN_NUM)
#define MX_CAN_TXB1DB3_X		CAL_APPEND(MX_CAN_TXB1DB3_, MX_CAN_NUM)
#define MX_CAN_TXB1DB4_X		CAL_APPEND(MX_CAN_TXB1DB4_, MX_CAN_NUM)
#define MX_CAN_TXB1DB5_X		CAL_APPEND(MX_CAN_TXB1DB5_, MX_CAN_NUM)
#define MX_CAN_TXB1DB6_X		CAL_APPEND(MX_CAN_TXB1DB6_, MX_CAN_NUM)
#define MX_CAN_TXB1DB7_X		CAL_APPEND(MX_CAN_TXB1DB7_, MX_CAN_NUM)

#define MX_CAN_TXB2ID_X			(MX_UINT32)CAL_APPEND(MX_CAN_TXB2ID_, MX_CAN_NUM)
#define MX_CAN_TXB2LEN_X		CAL_APPEND(MX_CAN_TXB2LEN_, MX_CAN_NUM)
#define MX_CAN_TXB2DB0_X		CAL_APPEND(MX_CAN_TXB2DB0_, MX_CAN_NUM)
#define MX_CAN_TXB2DB1_X		CAL_APPEND(MX_CAN_TXB2DB1_, MX_CAN_NUM)
#define MX_CAN_TXB2DB2_X		CAL_APPEND(MX_CAN_TXB2DB2_, MX_CAN_NUM)
#define MX_CAN_TXB2DB3_X		CAL_APPEND(MX_CAN_TXB2DB3_, MX_CAN_NUM)
#define MX_CAN_TXB2DB4_X		CAL_APPEND(MX_CAN_TXB2DB4_, MX_CAN_NUM)
#define MX_CAN_TXB2DB5_X		CAL_APPEND(MX_CAN_TXB2DB5_, MX_CAN_NUM)
#define MX_CAN_TXB2DB6_X		CAL_APPEND(MX_CAN_TXB2DB6_, MX_CAN_NUM)
#define MX_CAN_TXB2DB7_X		CAL_APPEND(MX_CAN_TXB2DB7_, MX_CAN_NUM)

#define MX_CAN_TX_DLC_X			CAL_APPEND(MX_CAN_TX_DLC_, MX_CAN_NUM)
#define MX_CAN_TX_DATA_X		CAL_APPEND(MX_CAN_TX_DATA_, MX_CAN_NUM)
#define MX_CAN_TX_ID_X			CAL_APPEND(MX_CAN_TX_ID_, MX_CAN_NUM)
#define MX_CAN_TX_EXID_X			CAL_APPEND(MX_CAN_TX_EXID_, MX_CAN_NUM)

#define MX_CAN_RX_DLC_X			CAL_APPEND(MX_CAN_RX_DLC_, MX_CAN_NUM)
#define MX_CAN_RX_DATA_X		CAL_APPEND(MX_CAN_RX_DATA_, MX_CAN_NUM)
#define MX_CAN_RX_ID_X			CAL_APPEND(MX_CAN_RX_ID_, MX_CAN_NUM)
#define MX_CAN_RX_EXID_X		CAL_APPEND(MX_CAN_RX_EXID_, MX_CAN_NUM)

#define MX_CAN_RX_MASK_X		CAL_APPEND(MX_CAN_RX_MASK_, MX_CAN_NUM)
#define MX_CAN_RX_FILTER_X		CAL_APPEND(MX_CAN_RX_FILTER_, MX_CAN_NUM)

#define MX_CAN_BUFFER_X		CAL_APPEND(MX_CAN_BUFFER_, MX_CAN_NUM)
#define MX_CAN_HANDLE_X		CAL_APPEND(MX_CAN_HANDLE_, MX_CAN_NUM)

// Some new defines that we need from the CAN component properties
#define MX_CAN_BUS_RATE_X		CAL_APPEND(MX_CAN_BUS_RATE_, MX_CAN_NUM)
#define MX_CAN_SJW_X			CAL_APPEND(MX_CAN_SJW_, MX_CAN_NUM)
#define MX_CAN_SAMPLE_X			CAL_APPEND(MX_CAN_SAMPLE_, MX_CAN_NUM)

// Port Pin and Alt settings
#define MX_CAN_RX_PIN_X		CAL_APPEND(MX_CAN_RX_PIN_, MX_CAN_NUM)
#define MX_CAN_RX_PORT_X	CAL_APPEND(MX_CAN_RX_PORT_, MX_CAN_NUM)
#define MX_CAN_RX_AF_X		CAL_APPEND(MX_CAN_RX_AF_, MX_CAN_NUM)
#define MX_CAN_TX_PIN_X		CAL_APPEND(MX_CAN_TX_PIN_, MX_CAN_NUM)
#define MX_CAN_TX_PORT_X	CAL_APPEND(MX_CAN_TX_PORT_, MX_CAN_NUM)
#define MX_CAN_TX_AF_X		CAL_APPEND(MX_CAN_TX_AF_, MX_CAN_NUM)

// Just for test
#ifndef MX_CAN_RX_PIN_1
	#warning "MX_CAN_RX_PIN_1 not defined, using test value"
	#define MX_CAN_RX_PIN_1 11
#endif
#ifndef MX_CAN_TX_PIN_1
	#warning "MX_CAN_TX_PIN_1 not defined, using test value"
	#define MX_CAN_TX_PIN_1 12
#endif
#ifndef MX_CAN_RX_PORT_1
	#warning "MX_CAN_RX_PORT_1 not defined, using test value"
	#define MX_CAN_RX_PORT_1 GPIOA
#endif
#ifndef MX_CAN_TX_PORT_1
	#warning "MX_CAN_TX_PORT_1 not defined, using test value"
	#define MX_CAN_TX_PORT_1 GPIOA
#endif
#ifndef MX_CAN_RX_AF_1
	#warning "MX_CAN_RX_AF_1 not defined, using test value"
	#define MX_CAN_RX_AF_1 9
#endif
#ifndef MX_CAN_TX_AF_1
	#warning "MX_CAN_TX_AF_1 not defined, using test value"
	#define MX_CAN_TX_AF_1 9
#endif



// Received data buffers, two, for Flowcode API
MX_UINT8  MX_CAN_RX_DLC_X[2];
MX_UINT8  MX_CAN_RX_DATA_X[2][8];
MX_UINT32 MX_CAN_RX_ID_X[2];
MX_UINT32 MX_CAN_RX_EXID_X[2];
// Mask and Filter control
MX_UINT8  MX_CAN_RX_ACTIVE_BANKS_X;
MX_UINT32 MX_CAN_RX_MASK_X[2];
MX_UINT32 MX_CAN_RX_FILTER_X[6];

// Transmit data buffers, three, for Flowcode API
MX_UINT8  MX_CAN_TX_DLC_X[3];
MX_UINT8  MX_CAN_TX_DATA_X[3][8];
MX_UINT32 MX_CAN_TX_ID_X[3];
MX_UINT32 MX_CAN_TX_EXID_X[3];

// Create CAN Instance
CAN_HandleTypeDef MX_CAN_HANDLE_X;

#ifndef CAN1
	#define CAN1 CAN
#endif

CALFUNCTION(void, FC_CAL_Internal_CAN_Init_, (void))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		// Setup the port pin mappings
		GPIO_InitTypeDef  GPIO_InitStruct;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_NOPULL;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Pin       = 1 << MX_CAN_TX_PIN_X;
		GPIO_InitStruct.Alternate = MX_CAN_TX_AF_X;
		HAL_GPIO_Init(MX_CAN_TX_PORT_X, &GPIO_InitStruct);

		GPIO_InitStruct.Pin 	  = 1 << MX_CAN_RX_PIN_X;
		GPIO_InitStruct.Alternate = MX_CAN_RX_AF_X;
		HAL_GPIO_Init(MX_CAN_RX_PORT_X, &GPIO_InitStruct);
		
		// Setup defaults
		MX_CAN_RX_ACTIVE_BANKS_X = 0;
		MX_CAN_TX_EXID_X[0] = MX_CAN_EXID_X;
		MX_CAN_TX_EXID_X[1] = MX_CAN_EXID_X;
		MX_CAN_TX_EXID_X[2] = MX_CAN_EXID_X;

		#if (MX_CAN_CHANNEL_X == 2)
			__HAL_RCC_CAN2_CLK_ENABLE();
			MX_CAN_HANDLE_X.Instance = CAN2;
		#else
			__HAL_RCC_CAN1_CLK_ENABLE();
			MX_CAN_HANDLE_X.Instance = CAN1;
		#endif
		
		#define CAN_TOTAL_TQ  10
		#if   (MX_CAN_BUS_RATE_X == 3)
			// 1000kbs 
			MX_CAN_HANDLE_X.Init.Prescaler = (HAL_RCC_GetPCLK1Freq()/(1000000 * CAN_TOTAL_TQ));
		#elif (MX_CAN_BUS_RATE_X == 2)
			// 500kbs 
			MX_CAN_HANDLE_X.Init.Prescaler = (HAL_RCC_GetPCLK1Freq()/(500000 * CAN_TOTAL_TQ));
		#elif (MX_CAN_BUS_RATE_X == 1)
			// 250kbs 
			MX_CAN_HANDLE_X.Init.Prescaler = (HAL_RCC_GetPCLK1Freq()/(250000 * CAN_TOTAL_TQ));
		#elif (MX_CAN_BUS_RATE_X == 0)
			// 125kbs 
			MX_CAN_HANDLE_X.Init.Prescaler = (HAL_RCC_GetPCLK1Freq()/(125000 * CAN_TOTAL_TQ));
		#else
			// 125kbs 
			#warning "MX_CAN_BUS_RATE_X not defined, using test value"
			MX_CAN_HANDLE_X.Init.Prescaler = (HAL_RCC_GetPCLK1Freq()/(125000 * CAN_TOTAL_TQ));
		#endif
		#if   (MX_CAN_SJW_X == 0)
			MX_CAN_HANDLE_X.Init.SyncJumpWidth = CAN_SJW_1TQ;
		#elif (MX_CAN_SJW_X == 1)
			MX_CAN_HANDLE_X.Init.SyncJumpWidth = CAN_SJW_2TQ;
		#elif (MX_CAN_SJW_X == 2)
			MX_CAN_HANDLE_X.Init.SyncJumpWidth = CAN_SJW_3TQ;
		#elif (MX_CAN_SJW_X == 3)
			MX_CAN_HANDLE_X.Init.SyncJumpWidth = CAN_SJW_4TQ;
		#else
			#warning "MX_CAN_SJW_X not defined, using test value"
			MX_CAN_HANDLE_X.Init.SyncJumpWidth = CAN_SJW_2TQ;
		#endif
		#if   (MX_CAN_SAMPLE_X == 3)
			// Sample point 80%
			MX_CAN_HANDLE_X.Init.TimeSeg1 = CAN_BS1_7TQ;
			MX_CAN_HANDLE_X.Init.TimeSeg2 = CAN_BS2_2TQ;
		#elif (MX_CAN_SAMPLE_X == 2)
			// Sample point 70%
			MX_CAN_HANDLE_X.Init.TimeSeg1 = CAN_BS1_6TQ;
			MX_CAN_HANDLE_X.Init.TimeSeg2 = CAN_BS2_3TQ;
		#elif (MX_CAN_SAMPLE_X == 1)
			// Sample point 60% 
			MX_CAN_HANDLE_X.Init.TimeSeg1 = CAN_BS1_5TQ;
			MX_CAN_HANDLE_X.Init.TimeSeg2 = CAN_BS2_4TQ;
		#elif (MX_CAN_SAMPLE_X == 0)
			// Sample point 50%
			MX_CAN_HANDLE_X.Init.TimeSeg1 = CAN_BS1_4TQ;
			MX_CAN_HANDLE_X.Init.TimeSeg2 = CAN_BS2_5TQ;
		#else
			#warning "MX_CAN_SAMPLE_X not defined, using test value"
			// Sample point 50%
			MX_CAN_HANDLE_X.Init.TimeSeg1 = CAN_BS1_4TQ;
			MX_CAN_HANDLE_X.Init.TimeSeg2 = CAN_BS2_5TQ;
		#endif
		MX_CAN_HANDLE_X.Init.Mode = CAN_MODE_NORMAL;
		MX_CAN_HANDLE_X.Init.TimeTriggeredMode = DISABLE;
		MX_CAN_HANDLE_X.Init.AutoBusOff = DISABLE;
		MX_CAN_HANDLE_X.Init.AutoWakeUp = DISABLE;
		MX_CAN_HANDLE_X.Init.AutoRetransmission = DISABLE;
		MX_CAN_HANDLE_X.Init.ReceiveFifoLocked = DISABLE;
		MX_CAN_HANDLE_X.Init.TransmitFifoPriority = DISABLE;
		
		HAL_CAN_Init(&MX_CAN_HANDLE_X);
		
		// Preload transmit buffer 0 with the property set values (Note: ID Type, Std v Ext_Std, is a component property so not dynamically set)
		CALFUNCTION( , FC_CAL_Internal_CAN_SetTxIdent_, (0, MX_CAN_TXB0ID_X));
		CALFUNCTION( , FC_CAL_Internal_CAN_SetTxData_, (0, MX_CAN_TXB0LEN_X, MX_CAN_TXB0DB0_X, MX_CAN_TXB0DB1_X, MX_CAN_TXB0DB2_X, MX_CAN_TXB0DB3_X, MX_CAN_TXB0DB4_X, MX_CAN_TXB0DB5_X, MX_CAN_TXB0DB6_X, MX_CAN_TXB0DB7_X));
			
		// Preload transmit buffer 1 with the property set values (Note: ID Type, Std v Ext_Std, is a component property so not dynamically set)
		CALFUNCTION( , FC_CAL_Internal_CAN_SetTxIdent_, (1, MX_CAN_TXB1ID_X));
		CALFUNCTION( , FC_CAL_Internal_CAN_SetTxData_, (1, MX_CAN_TXB1LEN_X, MX_CAN_TXB1DB0_X, MX_CAN_TXB1DB1_X, MX_CAN_TXB1DB2_X, MX_CAN_TXB1DB3_X, MX_CAN_TXB1DB4_X, MX_CAN_TXB1DB5_X, MX_CAN_TXB1DB6_X, MX_CAN_TXB1DB7_X));
			
		// Preload transmit buffer 2 with the property set values (Note: ID Type, Std v Ext_Std, is a component property so not dynamically set)
		CALFUNCTION( , FC_CAL_Internal_CAN_SetTxIdent_, (2, MX_CAN_TXB2ID_X));
		CALFUNCTION( , FC_CAL_Internal_CAN_SetTxData_, (2, MX_CAN_TXB2LEN_X, MX_CAN_TXB2DB0_X, MX_CAN_TXB2DB1_X, MX_CAN_TXB2DB2_X, MX_CAN_TXB2DB3_X, MX_CAN_TXB2DB4_X, MX_CAN_TXB2DB5_X, MX_CAN_TXB2DB6_X, MX_CAN_TXB2DB7_X));
			
		// Set the receive buffer 0 accept configs (Mask, Filter etc)
		#if (MX_CAN_RXB0CFG_X == MX_CAN_REJECT_ALL)
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxMask_, (0, -1));
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxFilter_, (0, 0));
		#elif (MX_CAN_RXB0CFG_X == MX_CAN_USE_FILTERS)
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxMask_, (0, MX_CAN_RXM0_X));
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxFilter_, (0, MX_CAN_RXF0_X));
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxFilter_, (1, MX_CAN_RXF1_X));
		#else  // (MX_CAN_RXB0CFG_X == MX_CAN_ACCEPT_ALL)
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxMask_, (0, 0));
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxFilter_, (0, 0));
		#endif

		// Set the receive buffer 1 accept configs (Mask, Filter etc)
		#if (MX_CAN_RXB1CFG_X == MX_CAN_REJECT_ALL)
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxMask_, (1, -1));
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxFilter_, (2, 0));
		#elif (MX_CAN_RXB1CFG_X == MX_CAN_USE_FILTERS)
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxMask_, (1, MX_CAN_RXM1_X));
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxFilter_, (2, MX_CAN_RXF2_X));
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxFilter_, (3, MX_CAN_RXF3_X));
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxFilter_, (4, MX_CAN_RXF4_X));
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxFilter_, (5, MX_CAN_RXF5_X));
		#else  // (MX_CAN_RXB1CFG_X == MX_CAN_ACCEPT_ALL)
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxMask_, (1, 0));
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxFilter_, (2, 0));
		#endif
	
		HAL_CAN_Start(&MX_CAN_HANDLE_X);
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_Uninit_, (void))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		HAL_CAN_Stop(&MX_CAN_HANDLE_X);
		HAL_CAN_DeInit(&MX_CAN_HANDLE_X);
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SendBuffer_, (MX_UINT8 buffer))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		if (buffer < 3)
		{
			CAN_TxHeaderTypeDef TxHeader;
			uint32_t TxMailbox = 0;
			
			if (MX_CAN_TX_EXID_X[buffer] == 0)
			{
				TxHeader.StdId = MX_CAN_TX_ID_X[buffer];
				TxHeader.ExtId = 0;
				TxHeader.IDE = CAN_ID_STD;
			}
			else
			{
				TxHeader.StdId = 0;
				TxHeader.ExtId = MX_CAN_TX_ID_X[buffer];
				TxHeader.IDE = CAN_ID_EXT;
			}
			TxHeader.RTR = CAN_RTR_DATA;
			TxHeader.DLC = MX_CAN_TX_DLC_X[buffer];
			TxHeader.TransmitGlobalTime = DISABLE;
			HAL_CAN_AddTxMessage(&MX_CAN_HANDLE_X, &TxHeader, MX_CAN_TX_DATA_X[buffer], &TxMailbox);
		}
	#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_CheckRx_, (MX_UINT8 buffer))
{
/**
This function reads the message, if there is one, into the MX_CAN_RX_DATA_X buffer etc and returns 1, else 0
**/
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		CAN_RxHeaderTypeDef RxHeader;
		uint32_t RxFifoFillLevel = HAL_CAN_GetRxFifoFillLevel(&MX_CAN_HANDLE_X, buffer);
		if (RxFifoFillLevel)
		{
			HAL_StatusTypeDef Status = HAL_CAN_GetRxMessage(&MX_CAN_HANDLE_X, buffer, &RxHeader, &MX_CAN_RX_DATA_X[buffer]);
			if (Status == HAL_OK)
			{
				// Read the data info the Flowcode buffers
				MX_CAN_RX_DLC_X[buffer] = RxHeader.DLC;
				if (RxHeader.IDE == CAN_ID_EXT)
				{
					MX_CAN_RX_EXID_X[buffer] = 1;
					MX_CAN_RX_ID_X[buffer] = RxHeader.ExtId;
				}
				else
				{
					MX_CAN_RX_EXID_X[buffer] = 0;
					MX_CAN_RX_ID_X[buffer] = RxHeader.StdId;
				}
				return 1;
			}
		}
	#endif
	return 0;
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxData_, (MX_UINT8 buffer, MX_UINT8 data_cnt, MX_UINT8 d0, MX_UINT8 d1, MX_UINT8 d2, MX_UINT8 d3, MX_UINT8 d4, MX_UINT8 d5, MX_UINT8 d6, MX_UINT8 d7))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
	if (buffer < 3)
	{
		MX_CAN_TX_DLC_X[buffer] = data_cnt;
		MX_CAN_TX_DATA_X[buffer][0] = d0;
		MX_CAN_TX_DATA_X[buffer][1] = d1;
		MX_CAN_TX_DATA_X[buffer][2] = d2;
		MX_CAN_TX_DATA_X[buffer][3] = d3;
		MX_CAN_TX_DATA_X[buffer][4] = d4;
		MX_CAN_TX_DATA_X[buffer][5] = d5;
		MX_CAN_TX_DATA_X[buffer][6] = d6;
		MX_CAN_TX_DATA_X[buffer][7] = d7;
	}
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdentStd_, (MX_UINT8 buffer, MX_UINT8 hi, MX_UINT8 lo))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		if (buffer < 3)
		{
			MX_CAN_TX_EXID_X[buffer] = 0;
			MX_CAN_TX_ID_X[buffer] = (hi << 8) + lo;
		}
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdentExd_, (MX_UINT8 buffer, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		if (buffer < 3)
		{
			MX_CAN_TX_EXID_X[buffer] = 1;
			MX_CAN_TX_ID_X[buffer] = ((MX_UINT32)id3 << 24) | ((MX_UINT32)id2 << 16) | ((MX_UINT32)id1 << 8) | ((MX_UINT32)id0) ;
		}
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilterStd_, (MX_UINT8 filter, MX_UINT8 hi, MX_UINT8 lo))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		MX_UINT32 id = ((MX_UINT16)hi << 8) | lo ;
		CALFUNCTION( , FC_CAL_Internal_CAN_SetRxFilter_, (filter, id));
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilterExd_, (MX_UINT8 filter, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		MX_UINT32 id = ((MX_UINT32)id3 << 24) | ((MX_UINT32)id2 << 16) | ((MX_UINT32)id1 << 8) | id0 ;
		CALFUNCTION( , FC_CAL_Internal_CAN_SetRxFilter_, (filter, id));
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskStd_, (MX_UINT8 mask, MX_UINT8 hi, MX_UINT8 lo))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		MX_UINT32 id = ((MX_UINT16)hi << 8) | lo ;
		CALFUNCTION( , FC_CAL_Internal_CAN_SetRxMask_, (mask, id));
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskExd_, (MX_UINT8 mask, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		MX_UINT32 id = ((MX_UINT32)id3 << 24) | ((MX_UINT32)id2 << 16) | ((MX_UINT32)id1 << 8) | id0 ;
		CALFUNCTION( , FC_CAL_Internal_CAN_SetRxMask_, (mask, id));
	#endif
}

/***************************************************************************************
These Receiver Mask and Filter functions
maintain the same API for the Flowcode CAN component
as for the MCP2515 external controller, hence:
Receive Buffer (aka fifo) 0 is associated with Mask 0 and Filter (aka bank) 0, 1
Receive Buffer (aka fifo) 1 is associated with Mask 1 and Filter (aka bank) 2, 3, 4, 5
****************************************************************************************/
CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxBank_, (MX_UINT8 bank))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		CAN_FilterTypeDef FilterConfig;
		FilterConfig.FilterIdHigh = (MX_CAN_RX_FILTER_X[bank] >> 16) & 0xFFFF;
		FilterConfig.FilterIdLow = MX_CAN_RX_FILTER_X[bank] & 0xFFFF;
		FilterConfig.FilterMaskIdHigh = (MX_CAN_RX_MASK_X[bank] >> 16) & 0xFFFF;
		FilterConfig.FilterMaskIdLow = MX_CAN_RX_MASK_X[bank] & 0xFFFF;
		FilterConfig.FilterFIFOAssignment = (bank < 2)?CAN_RX_FIFO0:CAN_RX_FIFO1;	// As above note
		#if (MX_CAN_CHANNEL_X == 1)
			FilterConfig.FilterBank = bank;					// Banks start at 0 for CAN channel 1
		#else
			FilterConfig.FilterBank = bank + 14;			// Banks start at 14 for CAN channel 2
		#endif
		FilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;	// Forces use of mask and filter
		FilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;	// Forces one filter per bank (to keep things simple!)
		FilterConfig.FilterActivation = CAN_FILTER_ENABLE;
		FilterConfig.SlaveStartFilterBank = 14;
		HAL_CAN_ConfigFilter(&MX_CAN_HANDLE_X, &FilterConfig);
		MX_CAN_RX_ACTIVE_BANKS_X |= (1<<bank);
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMask_, (MX_UINT8 mask, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		switch (mask)
		{
			case 0:
				MX_CAN_RX_MASK_X[0] = id;
				if (MX_CAN_RX_ACTIVE_BANKS_X & (1<<0)) CALFUNCTION( , FC_CAL_Internal_CAN_SetRxBank_, (0));
				if (MX_CAN_RX_ACTIVE_BANKS_X & (1<<1)) CALFUNCTION( , FC_CAL_Internal_CAN_SetRxBank_, (1));
				break;
			case 1:
				MX_CAN_RX_MASK_X[1] = id;
				if (MX_CAN_RX_ACTIVE_BANKS_X & (1<<2)) CALFUNCTION( , FC_CAL_Internal_CAN_SetRxBank_, (2));
				if (MX_CAN_RX_ACTIVE_BANKS_X & (1<<3)) CALFUNCTION( , FC_CAL_Internal_CAN_SetRxBank_, (3));
				if (MX_CAN_RX_ACTIVE_BANKS_X & (1<<4)) CALFUNCTION( , FC_CAL_Internal_CAN_SetRxBank_, (4));
				if (MX_CAN_RX_ACTIVE_BANKS_X & (1<<5)) CALFUNCTION( , FC_CAL_Internal_CAN_SetRxBank_, (5));
				break;
		}
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilter_, (MX_UINT8 filter, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		if (filter < 6)
		{
			MX_CAN_RX_FILTER_X[filter] = id;
			CALFUNCTION( , FC_CAL_Internal_CAN_SetRxBank_, (filter));
		}
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdent_, (MX_UINT8 buffer, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		if (buffer < 3)
		{
			// This function assumes component property sets Std/Ext mode for ID
			MX_CAN_TX_EXID_X[buffer] = MX_CAN_EXID_X;
			MX_CAN_TX_ID_X[buffer] = id;
		}
	#endif
}

CALFUNCTION(MX_UINT32, FC_CAL_Internal_CAN_GetRxIdent_, (MX_UINT8 buffer))
{
	return MX_CAN_RX_ID_X[buffer & 1];
}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxDataCount_, (MX_UINT8 buffer))
{
	return (MX_CAN_RX_DLC_X[buffer & 1]);
}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxData_, (MX_UINT8 buffer, MX_UINT8 index))
{
	return (MX_CAN_RX_DATA_X[buffer & 1][index & 7]);
}



