// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B832535F4E381B52A002F30B4650F87BFB9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5FC054692D120CD14EFF87C6A05C843D029536701E6F38BC7A1AB8EC1DA23E8CDD77879206EC4D14363F2AB5F1026106AD738240B0E4562425C6EC4661E40B07C3FF4DA025685799362BDEF9D0F76CFDB863DD2A7D5FC2A5E549D34A0D5AD11F345DD63DDA096E27E3C951C41F8689753A276B653C94063290DA6C43ED30373AA133F965729382C18
// REVISION: 1.0
// GUID: 40B36CB7-02B8-46B5-BD52-D12A3FD8F543
// DATE: 08\08\2022
// DIR: CAL\PIC\PIC_CAL_CAN.c
/*********************************************************************
 *                  Flowcode CAL CAN File
 *
 * File: PIC_CAL_CAN.c
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
 * 230911 | BR | Created
 * 011211 | BR | Converted to new dynamic defines mechanism
 * 104013 | LM | Changes for V6 Internal CAN
 * 200513 | LM | Fixed Mask registers
 * 200513 | LM | Change mode to CONFIG for Mask and Filter setting
 * 200513 | LM | Extended Filter functions to support all 6 Filters (Mode 0)
 * 200513 | LM | Added generic SetRxMask, SetRxFilter, SetTxIdent, GetRxIdent
 * 200513 | LM | Added functions for GetRxDataCount, GetRxData
 * 220513 | LM | Fixed GetRxIdent bugs. (Must use rx registers in Mode 0)
 * 030713 | LM | Standard API calls
 * 250416 | LM | Changes for XC8
 */


#ifndef MX_ECAN
	#error "Internal CAN not supported on this device"
#else

#define MX_CAN_CHANNEL_X		CAL_APPEND(MX_CAN_CHANNEL_, MX_CAN_NUM)
#define MX_CAN_BAUD1_X			CAL_APPEND(MX_CAN_BAUD1_, MX_CAN_NUM)
#define MX_CAN_BAUD2_X			CAL_APPEND(MX_CAN_BAUD2_, MX_CAN_NUM)
#define MX_CAN_BAUD3_X			CAL_APPEND(MX_CAN_BAUD3_, MX_CAN_NUM)
#define MX_CAN_EXID_X			CAL_APPEND(MX_CAN_EXID_, MX_CAN_NUM)

#define MX_CAN_RXB0CFG_X		CAL_APPEND(MX_CAN_RXB0CFG_, MX_CAN_NUM)
#define MX_CAN_RXB1CFG_X		CAL_APPEND(MX_CAN_RXB1CFG_, MX_CAN_NUM)

#define MX_CAN_RXM0_X			CAL_APPEND(MX_CAN_RXM0_, MX_CAN_NUM)
#define MX_CAN_RXM1_X			CAL_APPEND(MX_CAN_RXM1_, MX_CAN_NUM)

#define MX_CAN_RXF0_X			CAL_APPEND(MX_CAN_RXF0_, MX_CAN_NUM)
#define MX_CAN_RXF1_X			CAL_APPEND(MX_CAN_RXF1_, MX_CAN_NUM)
#define MX_CAN_RXF2_X			CAL_APPEND(MX_CAN_RXF2_, MX_CAN_NUM)
#define MX_CAN_RXF3_X			CAL_APPEND(MX_CAN_RXF3_, MX_CAN_NUM)
#define MX_CAN_RXF4_X			CAL_APPEND(MX_CAN_RXF4_, MX_CAN_NUM)
#define MX_CAN_RXF5_X			CAL_APPEND(MX_CAN_RXF5_, MX_CAN_NUM)

#define MX_CAN_TXB0ID_X			CAL_APPEND(MX_CAN_TXB0ID_, MX_CAN_NUM)
#define MX_CAN_TXB0LEN_X		CAL_APPEND(MX_CAN_TXB0LEN_, MX_CAN_NUM)
#define MX_CAN_TXB0DB0_X		CAL_APPEND(MX_CAN_TXB0DB0_, MX_CAN_NUM)
#define MX_CAN_TXB0DB1_X		CAL_APPEND(MX_CAN_TXB0DB1_, MX_CAN_NUM)
#define MX_CAN_TXB0DB2_X		CAL_APPEND(MX_CAN_TXB0DB2_, MX_CAN_NUM)
#define MX_CAN_TXB0DB3_X		CAL_APPEND(MX_CAN_TXB0DB3_, MX_CAN_NUM)
#define MX_CAN_TXB0DB4_X		CAL_APPEND(MX_CAN_TXB0DB4_, MX_CAN_NUM)
#define MX_CAN_TXB0DB5_X		CAL_APPEND(MX_CAN_TXB0DB5_, MX_CAN_NUM)
#define MX_CAN_TXB0DB6_X		CAL_APPEND(MX_CAN_TXB0DB6_, MX_CAN_NUM)
#define MX_CAN_TXB0DB7_X		CAL_APPEND(MX_CAN_TXB0DB7_, MX_CAN_NUM)

#define MX_CAN_TXB1ID_X			CAL_APPEND(MX_CAN_TXB1ID_, MX_CAN_NUM)
#define MX_CAN_TXB1LEN_X		CAL_APPEND(MX_CAN_TXB1LEN_, MX_CAN_NUM)
#define MX_CAN_TXB1DB0_X		CAL_APPEND(MX_CAN_TXB1DB0_, MX_CAN_NUM)
#define MX_CAN_TXB1DB1_X		CAL_APPEND(MX_CAN_TXB1DB1_, MX_CAN_NUM)
#define MX_CAN_TXB1DB2_X		CAL_APPEND(MX_CAN_TXB1DB2_, MX_CAN_NUM)
#define MX_CAN_TXB1DB3_X		CAL_APPEND(MX_CAN_TXB1DB3_, MX_CAN_NUM)
#define MX_CAN_TXB1DB4_X		CAL_APPEND(MX_CAN_TXB1DB4_, MX_CAN_NUM)
#define MX_CAN_TXB1DB5_X		CAL_APPEND(MX_CAN_TXB1DB5_, MX_CAN_NUM)
#define MX_CAN_TXB1DB6_X		CAL_APPEND(MX_CAN_TXB1DB6_, MX_CAN_NUM)
#define MX_CAN_TXB1DB7_X		CAL_APPEND(MX_CAN_TXB1DB7_, MX_CAN_NUM)

#define MX_CAN_TXB2ID_X			CAL_APPEND(MX_CAN_TXB2ID_, MX_CAN_NUM)
#define MX_CAN_TXB2LEN_X		CAL_APPEND(MX_CAN_TXB2LEN_, MX_CAN_NUM)
#define MX_CAN_TXB2DB0_X		CAL_APPEND(MX_CAN_TXB2DB0_, MX_CAN_NUM)
#define MX_CAN_TXB2DB1_X		CAL_APPEND(MX_CAN_TXB2DB1_, MX_CAN_NUM)
#define MX_CAN_TXB2DB2_X		CAL_APPEND(MX_CAN_TXB2DB2_, MX_CAN_NUM)
#define MX_CAN_TXB2DB3_X		CAL_APPEND(MX_CAN_TXB2DB3_, MX_CAN_NUM)
#define MX_CAN_TXB2DB4_X		CAL_APPEND(MX_CAN_TXB2DB4_, MX_CAN_NUM)
#define MX_CAN_TXB2DB5_X		CAL_APPEND(MX_CAN_TXB2DB5_, MX_CAN_NUM)
#define MX_CAN_TXB2DB6_X		CAL_APPEND(MX_CAN_TXB2DB6_, MX_CAN_NUM)
#define MX_CAN_TXB2DB7_X		CAL_APPEND(MX_CAN_TXB2DB7_, MX_CAN_NUM)

#ifndef MX_CAN_INT_DEFS
  #define MX_CAN_INT_DEFS

  #define MX_CAN_OP_MODE_BITS 		0xE0
  #define MX_CAN_REQOP_CONFIG		0x80
  #define MX_CAN_REQOP_LISTEN		0x60
  #define MX_CAN_REQOP_LOOPBACK		0x40
  #define MX_CAN_REQOP_SLEEP		0x20
  #define MX_CAN_REQOP_NORMAL		0x00
 
  #define MX_CAN_SIDH(v) ((MX_UINT16)v >> 3)
  #define MX_CAN_SIDL(v) ((MX_UINT16)v << 5)
  #define MX_CAN_EIDEH(v) ((MX_UINT32)v >> 8)
  #define MX_CAN_EIDEL(v) ((MX_UINT32)v)
  #define MX_CAN_EIDSH(v) ((MX_UINT32)v >> 21)
  #define MX_CAN_EIDSL(v) ((((MX_UINT32)v >> 13) & 0xe0) | 0x08 | (((MX_UINT32)v >> 16) & 3))

  #define MX_CAN_REJECT_ALL 	(0)
  #define MX_CAN_USE_FILTERS	(1)
  #define MX_CAN_ACCEPT_ALL 	(2)

  MX_UINT8 CAN_MSG_DLC;
  MX_UINT8 CAN_MSG_DATA[8];
//MX_UINT8 CAN_MSG_FLAGS = 0;
//MX_UINT8 BF_MASK;
  #if (MX_CAN_EXID_X == 1)
    MX_UINT8 CAN_MSG_ID[4];
  #else
    MX_UINT8 CAN_MSG_ID[2];
  #endif
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
CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskStd_, (MX_UINT8 mask, MX_UINT8 hi, MX_UINT8 lo));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskExd_, (MX_UINT8 mask, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0));

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMask_, (MX_UINT8 mask, MX_UINT32 id));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilter_, (MX_UINT8 filter, MX_UINT32 id));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdent_, (MX_UINT8 buffer, MX_UINT32 id));
CALFUNCTION(MX_UINT32, FC_CAL_Internal_CAN_GetRxIdent_, (MX_UINT8 buffer));

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxDataCount_, (MX_UINT8 buffer));
CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxData_, (MX_UINT8 buffer, MX_UINT8 index));



CALFUNCTION(void, FC_CAL_Internal_CAN_Init_, (void))
{
	#if (MX_CAN_CHANNEL_X == 1)
		//configure CAN I/O
		CIOCON = 0x30;

		// In order to setup necessary config parameters of CAN module,
		// it must be in CONFIG mode.

		// Request desired mode.
		CANCON = MX_CAN_REQOP_CONFIG;
		// Wait till desired mode is set.
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_CONFIG );

		ECANCON = 0;
		
		BRGCON3 = MX_CAN_BAUD3_X;
		BRGCON2 = MX_CAN_BAUD2_X;
		BRGCON1 = MX_CAN_BAUD1_X;
		
// setup Receive Buffer masks and filters
#if (MX_CAN_EXID_X == 1)
		RXF0SIDH = MX_CAN_EIDSH(MX_CAN_RXF0_X);    // ID Filter 0 - Buffer 0
		RXF0SIDL = MX_CAN_EIDSL(MX_CAN_RXF0_X);
		RXF0EIDH = MX_CAN_EIDEH(MX_CAN_RXF0_X);
		RXF0EIDL = MX_CAN_EIDEL(MX_CAN_RXF0_X);
		RXF1SIDH = MX_CAN_EIDSH(MX_CAN_RXF1_X);    // ID Filter 1 - Buffer 0
		RXF1SIDL = MX_CAN_EIDSL(MX_CAN_RXF1_X);
		RXF1EIDH = MX_CAN_EIDEH(MX_CAN_RXF1_X);
		RXF1EIDL = MX_CAN_EIDEL(MX_CAN_RXF1_X);
		RXF2SIDH = MX_CAN_EIDSH(MX_CAN_RXF2_X);    // ID Filter 2 - Buffer 1
		RXF2SIDL = MX_CAN_EIDSL(MX_CAN_RXF2_X);
		RXF2EIDH = MX_CAN_EIDEH(MX_CAN_RXF2_X);
		RXF2EIDL = MX_CAN_EIDEL(MX_CAN_RXF2_X);
		RXF3SIDH = MX_CAN_EIDSH(MX_CAN_RXF3_X);    // ID Filter 3 - Buffer 1
		RXF3SIDL = MX_CAN_EIDSL(MX_CAN_RXF3_X);
		RXF3EIDH = MX_CAN_EIDEH(MX_CAN_RXF3_X);
		RXF3EIDL = MX_CAN_EIDEL(MX_CAN_RXF3_X);
		RXF4SIDH = MX_CAN_EIDSH(MX_CAN_RXF4_X);    // ID Filter 4 - Buffer 1
		RXF4SIDL = MX_CAN_EIDSL(MX_CAN_RXF4_X);
		RXF4EIDH = MX_CAN_EIDEH(MX_CAN_RXF4_X);
		RXF4EIDL = MX_CAN_EIDEL(MX_CAN_RXF4_X);
		RXF5SIDH = MX_CAN_EIDSH(MX_CAN_RXF5_X);    // ID Filter 5 - Buffer 1
		RXF5SIDL = MX_CAN_EIDSL(MX_CAN_RXF5_X);
		RXF5EIDH = MX_CAN_EIDEH(MX_CAN_RXF5_X);
		RXF5EIDL = MX_CAN_EIDEL(MX_CAN_RXF5_X);
		RXM0SIDH = MX_CAN_EIDSH(MX_CAN_RXM0_X);    // ID Mask 0   - Buffer 0
		RXM0SIDL = MX_CAN_EIDSL(MX_CAN_RXM0_X);
		RXM0EIDH = MX_CAN_EIDEH(MX_CAN_RXM0_X);
		RXM0EIDL = MX_CAN_EIDEL(MX_CAN_RXM0_X);
		RXM1SIDH = MX_CAN_EIDSH(MX_CAN_RXM1_X);    // ID Mask 1   - Buffer 1
		RXM1SIDL = MX_CAN_EIDSL(MX_CAN_RXM1_X);
		RXM1EIDH = MX_CAN_EIDEH(MX_CAN_RXM1_X);
		RXM1EIDL = MX_CAN_EIDEL(MX_CAN_RXM1_X);
#else
		RXF0SIDH = MX_CAN_SIDH(MX_CAN_RXF0_X);    // ID Filter 0 - Buffer 0
		RXF0SIDL = MX_CAN_SIDL(MX_CAN_RXF0_X);
		RXF1SIDH = MX_CAN_SIDH(MX_CAN_RXF1_X);    // ID Filter 1 - Buffer 0
		RXF1SIDL = MX_CAN_SIDL(MX_CAN_RXF1_X);
		RXF2SIDH = MX_CAN_SIDH(MX_CAN_RXF2_X);    // ID Filter 2 - Buffer 1
		RXF2SIDL = MX_CAN_SIDL(MX_CAN_RXF2_X);
		RXF3SIDH = MX_CAN_SIDH(MX_CAN_RXF3_X);    // ID Filter 3 - Buffer 1
		RXF3SIDL = MX_CAN_SIDL(MX_CAN_RXF3_X);
		RXF4SIDH = MX_CAN_SIDH(MX_CAN_RXF4_X);    // ID Filter 4 - Buffer 1
		RXF4SIDL = MX_CAN_SIDL(MX_CAN_RXF4_X);
		RXF5SIDH = MX_CAN_SIDH(MX_CAN_RXF5_X);    // ID Filter 5 - Buffer 1
		RXF5SIDL = MX_CAN_SIDL(MX_CAN_RXF5_X);
		RXM0SIDH = MX_CAN_SIDH(MX_CAN_RXM0_X);    // ID Mask 0   - Buffer 0
		RXM0SIDL = MX_CAN_SIDL(MX_CAN_RXM0_X);
		RXM1SIDH = MX_CAN_SIDH(MX_CAN_RXM1_X);    // ID Mask 1   - Buffer 1
		RXM1SIDL = MX_CAN_SIDL(MX_CAN_RXM1_X);
#endif

// Receive Buffer 0 Control
		CANCON = CANCON & 0xE0;
		//CANCON = CANCON | 0x0C;
#if (MX_CAN_RXB0CFG_X == MX_CAN_ACCEPT_ALL)
		RXB0CON = 0x60;
#else
		RXB0CON = 0;  		
#endif

// Receive Buffer 1 Control
		CANCON = CANCON & 0xE0;
		CANCON = CANCON | 0x0A;
#if (MX_CAN_RXB1CFG_X == MX_CAN_ACCEPT_ALL)
		RXB1CON = 0x60;
#else
		RXB1CON = 0;  		
#endif

		CANCON = CANCON & 0xE0;
		CANCON = CANCON | 0x08;
		TXB0CON = 0; // TXB0CTRL_VAL;     // Transmit Buffer 0 Control

#if (MX_CAN_EXID_X == 1)
		TXB0EIDL = MX_CAN_EIDEL(MX_CAN_TXB0ID_X);
		TXB0EIDH = MX_CAN_EIDEH(MX_CAN_TXB0ID_X);
		TXB0SIDL = MX_CAN_EIDSL(MX_CAN_TXB0ID_X);
		TXB0SIDH = MX_CAN_EIDSH(MX_CAN_TXB0ID_X);
#else
		TXB0SIDL = MX_CAN_SIDL(MX_CAN_TXB0ID_X);
		TXB0SIDH = MX_CAN_SIDH(MX_CAN_TXB0ID_X);
#endif
		TXB0DLC = MX_CAN_TXB0LEN_X;
		TXB0D0 = MX_CAN_TXB0DB0_X;      // Transmit Data Bytes
		TXB0D1 = MX_CAN_TXB0DB1_X;
		TXB0D2 = MX_CAN_TXB0DB2_X;
		TXB0D3 = MX_CAN_TXB0DB3_X;
		TXB0D4 = MX_CAN_TXB0DB4_X;
		TXB0D5 = MX_CAN_TXB0DB5_X;
		TXB0D6 = MX_CAN_TXB0DB6_X;
		TXB0D7 = MX_CAN_TXB0DB7_X;

		CANCON = CANCON & 0xE0;
		CANCON = CANCON | 0x06;
		TXB1CON = 0; // TXB1CTRL_VAL;     // Transmit Buffer 1 Control

#if (MX_CAN_EXID_X == 1)
		TXB1EIDL = MX_CAN_EIDEL(MX_CAN_TXB1ID_X);
		TXB1EIDH = MX_CAN_EIDEH(MX_CAN_TXB1ID_X);
		TXB1SIDL = MX_CAN_EIDSL(MX_CAN_TXB1ID_X);
		TXB1SIDH = MX_CAN_EIDSH(MX_CAN_TXB1ID_X);
#else
		TXB1SIDL = MX_CAN_SIDL(MX_CAN_TXB1ID_X);
		TXB1SIDH = MX_CAN_SIDH(MX_CAN_TXB1ID_X);
#endif
		TXB1DLC = MX_CAN_TXB1LEN_X;
		TXB1D0 = MX_CAN_TXB1DB0_X;      // Transmit Data Bytes
		TXB1D1 = MX_CAN_TXB1DB1_X;
		TXB1D2 = MX_CAN_TXB1DB2_X;
		TXB1D3 = MX_CAN_TXB1DB3_X;
		TXB1D4 = MX_CAN_TXB1DB4_X;
		TXB1D5 = MX_CAN_TXB1DB5_X;
		TXB1D6 = MX_CAN_TXB1DB6_X;
		TXB1D7 = MX_CAN_TXB1DB7_X;

		CANCON = CANCON & 0xE0;
		CANCON = CANCON | 0x04;
		TXB2CON = 0; // TXB2CTRL_VAL;     // Transmit Buffer 2 Control

#if (MX_CAN_EXID_X == 1)
		TXB2EIDL = MX_CAN_EIDEL(MX_CAN_TXB2ID_X);
		TXB2EIDH = MX_CAN_EIDEH(MX_CAN_TXB2ID_X);
		TXB2SIDL = MX_CAN_EIDSL(MX_CAN_TXB2ID_X);
		TXB2SIDH = MX_CAN_EIDSH(MX_CAN_TXB2ID_X);
#else
		TXB2SIDL = MX_CAN_SIDL(MX_CAN_TXB2ID_X);
		TXB2SIDH = MX_CAN_SIDH(MX_CAN_TXB2ID_X);
#endif
		TXB2DLC = MX_CAN_TXB2LEN_X;
		TXB2D0 = MX_CAN_TXB2DB0_X;      // Transmit Data Bytes
		TXB2D1 = MX_CAN_TXB2DB1_X;
		TXB2D2 = MX_CAN_TXB2DB2_X;
		TXB2D3 = MX_CAN_TXB2DB3_X;
		TXB2D4 = MX_CAN_TXB2DB4_X;
		TXB2D5 = MX_CAN_TXB2DB5_X;
		TXB2D6 = MX_CAN_TXB2DB6_X;
		TXB2D7 = MX_CAN_TXB2DB7_X;

		// Request desired mode.
		CANCON = MX_CAN_REQOP_NORMAL;

		// Wait till desired mode is set.
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_NORMAL );
	#endif

	#if (MX_CAN_CHANNEL_X == 2)
   		#error "8-Bit PICs only ever have 1 CAN channel..... For now";
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_Uninit_, (void))
{
	#if (MX_CAN_CHANNEL_X == 1)
		CANCON = 0x00;			//Need to test this works.
		CANSTAT = 0x00;
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SendBuffer_, (MX_UINT8 buffer))
{
	#if (MX_CAN_CHANNEL_X == 1)
		unsigned int timeout = 0xFFFF;
		switch (buffer)
		{
			case 0:
				CANCON = CANCON & 0xE0;
				CANCON = CANCON | 0x08;
				st_bit(TXB0CON, TXREQ);							//Set Message Transmission Flag
				while (ts_bit(TXB0CON, TXREQ) && timeout)		//Wait for message to send
					timeout = timeout - 1;
				break;
			case 1:
				CANCON = CANCON & 0xE0;
				CANCON = CANCON | 0x06;
				st_bit(TXB0CON, TXREQ);
				while (ts_bit(TXB0CON, TXREQ) && timeout)
					timeout = timeout - 1;
				break;
			case 2:
				CANCON = CANCON & 0xE0;
				CANCON = CANCON | 0x04;
				st_bit(TXB0CON, TXREQ);
				while (ts_bit(TXB0CON, TXREQ) && timeout)
					timeout = timeout - 1;
				break;
		}
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_CheckRx_, (MX_UINT8 buffer))
{
	#if (MX_CAN_CHANNEL_X == 1)
		if (buffer == 0)
		{
			CANCON = CANCON & 0xE0;
			//CANCON = CANCON | 0x0C;	//Rx Buffer 0
		}
		else
		{
			CANCON = CANCON & 0xE0;
			CANCON = CANCON | 0x0A; 	//Rx Buffer 1
		}

		if (ts_bit(RXB0CON, RXFUL))
		{
			CAN_MSG_DLC = RXB0DLC & 0b00001111;	// Retrieve message length.
			CAN_MSG_ID[0] = RXB0SIDH;
			CAN_MSG_ID[1] = RXB0SIDL;
			if(CAN_MSG_DLC > 0)
			{
				CAN_MSG_DATA[0] = RXB0D0;
				if(CAN_MSG_DLC > 1)
				{
					CAN_MSG_DATA[1] = RXB0D1;
					if(CAN_MSG_DLC > 2)
					{
						CAN_MSG_DATA[2] = RXB0D2;
						if(CAN_MSG_DLC > 3)
						{
							CAN_MSG_DATA[3] = RXB0D3;
							if(CAN_MSG_DLC > 4)
							{
								CAN_MSG_DATA[4] = RXB0D4;
								if(CAN_MSG_DLC > 5)
								{
									CAN_MSG_DATA[5] = RXB0D5;
									if(CAN_MSG_DLC > 6)
									{
										CAN_MSG_DATA[6] = RXB0D6;
										if(CAN_MSG_DLC > 7)
										{
											CAN_MSG_DATA[7] = RXB0D7;
										}
									}
								}
							}
						}
					}
				}
			}
			cr_bit(RXB0CON, RXFUL);
			return 1;
		}
		else
			return 0;
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxData_, (MX_UINT8 buffer, MX_UINT8 data_cnt, MX_UINT8 d0, MX_UINT8 d1, MX_UINT8 d2, MX_UINT8 d3, MX_UINT8 d4, MX_UINT8 d5, MX_UINT8 d6, MX_UINT8 d7))
{
	#if (MX_CAN_CHANNEL_X == 1)
		switch(buffer)
		{
			case 0:
				CANCON = CANCON & 0xE0;
				CANCON = CANCON | 0x08;	//Tx Buffer 0
				break;
			case 1:
				CANCON = CANCON & 0xE0;
				CANCON = CANCON | 0x06;	//Tx Buffer 1
				break;
			case 2:
				CANCON = CANCON & 0xE0;
				CANCON = CANCON | 0x04;	//Tx Buffer 2
				break;
		}

		RXB0DLC = data_cnt;				// Set data count
		if (data_cnt > 0)
		{
		   RXB0D0 = d0;
		   if (data_cnt > 1)
		   {
			   RXB0D1 = d1;
			   if (data_cnt > 2)
			   {
				   RXB0D2 = d2;
				   if (data_cnt > 3)
				   {
					   RXB0D3 = d3;
					   if (data_cnt > 4)
					   {
						   RXB0D4 = d4;
						   if (data_cnt > 5)
						   {
							   RXB0D5 = d5;
							   if (data_cnt > 6)
							   {
								   RXB0D6 = d6;
								   if (data_cnt > 7)
								   {
									   RXB0D7 = d7;
								   }
							   }
						   }
					   }
				   }
			   }
		   }
		}
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdentStd_, (MX_UINT8 buffer, MX_UINT8 hi, MX_UINT8 lo))
{
	#if (MX_CAN_CHANNEL_X == 1)
		switch(buffer)
		{
			case 0:
				CANCON = CANCON & 0xE0;
				CANCON = CANCON | 0x08;
				TXB0SIDH = hi;			//set the Hi ID value
				TXB0SIDL = lo;			//set the Lo ID value
				break;
			case 1:
				CANCON = CANCON & 0xE0;
				CANCON = CANCON | 0x06;
				TXB1SIDH = hi;			//set the Hi ID value
				TXB1SIDL = lo;			//set the Lo ID value
				break;
			case 2:
				CANCON = CANCON & 0xE0;
				CANCON = CANCON | 0x04;
				TXB2SIDH = hi;			//set the Hi ID value
				TXB2SIDL = lo;			//set the Lo ID value
				break;
		}
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdentExd_, (MX_UINT8 buffer, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)
		switch(buffer)
		{
			case 0:
				CANCON = CANCON & 0xE0;
				CANCON = CANCON | 0x08;
				TXB0SIDH = id1;			//set the Hi ID value
				TXB0SIDL = id0;			//set the Lo ID value
				TXB0EIDH = id3;			//set the Hi ID value
				TXB0EIDL = id2;			//set the Lo ID value
				break;
			case 1:
				CANCON = CANCON & 0xE0;
				CANCON = CANCON | 0x06;
				TXB1SIDH = id1;			//set the Hi ID value
				TXB1SIDL = id0;			//set the Lo ID value
				TXB1EIDH = id3;			//set the Hi ID value
				TXB1EIDL = id2;			//set the Lo ID value
				break;
			case 2:
				CANCON = CANCON & 0xE0;
				CANCON = CANCON | 0x04;
				TXB2SIDH = id1;			//set the Hi ID value
				TXB2SIDL = id0;			//set the Lo ID value
				TXB2EIDH = id3;			//set the Hi ID value
				TXB2EIDL = id2;			//set the Lo ID value
				break;
		}
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilterStd_, (MX_UINT8 filter, MX_UINT8 hi, MX_UINT8 lo))
{
	#if (MX_CAN_CHANNEL_X == 1)
		// change to config mode
		CANCON = MX_CAN_REQOP_CONFIG;
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_CONFIG );

		switch(filter)
		{
			case 0:
				RXF0SIDH = hi;				//set the Hi ID value
				RXF0SIDL = lo;				//set the Lo ID value
				break;
			case 1:
				RXF1SIDH = hi;				//set the Hi ID value
				RXF1SIDL = lo;				//set the Lo ID value
				break;
			case 2:
				RXF2SIDH = hi;				//set the Hi ID value
				RXF2SIDL = lo;				//set the Lo ID value
				break;
			case 3:
				RXF3SIDH = hi;				//set the Hi ID value
				RXF3SIDL = lo;				//set the Lo ID value
				break;
			case 4:
				RXF4SIDH = hi;				//set the Hi ID value
				RXF4SIDL = lo;				//set the Lo ID value
				break;
			case 5:
				RXF5SIDH = hi;				//set the Hi ID value
				RXF5SIDL = lo;				//set the Lo ID value
				break;
		}
		// change to normal mode
		CANCON = MX_CAN_REQOP_NORMAL;
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_NORMAL );
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilterExd_, (MX_UINT8 filter, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)
		// change to config mode
		CANCON = MX_CAN_REQOP_CONFIG;
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_CONFIG );

		switch(filter)
		{
			case 0:
				RXF0SIDH = id1;			//set the Hi ID value
				RXF0SIDL = id0;			//set the Lo ID value
				RXF0EIDH = id3;
				RXF0EIDL = id2;
				break;
			case 1:
				RXF1SIDH = id1;			//set the Hi ID value
				RXF1SIDL = id0;			//set the Lo ID value
				RXF1EIDH = id3;
				RXF1EIDL = id2;
				break;
			case 2:
				RXF2SIDH = id1;			//set the Hi ID value
				RXF2SIDL = id0;			//set the Lo ID value
				RXF2EIDH = id3;
				RXF2EIDL = id2;
				break;
			case 3:
				RXF3SIDH = id1;			//set the Hi ID value
				RXF3SIDL = id0;			//set the Lo ID value
				RXF3EIDH = id3;
				RXF3EIDL = id2;
				break;
			case 4:
				RXF4SIDH = id1;			//set the Hi ID value
				RXF4SIDL = id0;			//set the Lo ID value
				RXF4EIDH = id3;
				RXF4EIDL = id2;
				break;
			case 5:
				RXF5SIDH = id1;			//set the Hi ID value
				RXF5SIDL = id0;			//set the Lo ID value
				RXF5EIDH = id3;
				RXF5EIDL = id2;
				break;
		}
		// change to normal mode
		CANCON = MX_CAN_REQOP_NORMAL;
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_NORMAL );
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskStd_, (MX_UINT8 mask, MX_UINT8 hi, MX_UINT8 lo))
{
	#if (MX_CAN_CHANNEL_X == 1)
		// change to config mode
		CANCON = MX_CAN_REQOP_CONFIG;
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_CONFIG );

		switch(mask)
		{
			case 0:
				RXM0SIDH = hi;			//set the Hi ID value
				RXM0SIDL = lo;			//set the Lo ID value
				break;
			case 1:
				RXM1SIDH = hi;			//set the Hi ID value
				RXM1SIDL = lo;			//set the Lo ID value
				break;
		}
		// change to normal mode
		CANCON = MX_CAN_REQOP_NORMAL;
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_NORMAL );
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskExd_, (MX_UINT8 mask, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)
		// change to config mode
		CANCON = MX_CAN_REQOP_CONFIG;
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_CONFIG );

		switch(mask)
		{
			case 0:
				RXM0SIDH = id1;		//set the Hi ID value
				RXM0SIDL = id0;		//set the Lo ID value
				RXM0EIDH = id3;
				RXM0EIDL = id2;
				break;
			case 1:
				RXM1SIDH = id1;		//set the Hi ID value
				RXM1SIDL = id0;		//set the Lo ID value
				RXM1EIDH = id3;
				RXM1EIDL = id2;
				break;
		}
		// change to normal mode
		CANCON = MX_CAN_REQOP_NORMAL;
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_NORMAL );
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMask_, (MX_UINT8 mask, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)
		MX_UINT8 sidh;
		MX_UINT8 sidl;
		MX_UINT8 eidh;
		MX_UINT8 eidl;
		// change to config mode
		CANCON = MX_CAN_REQOP_CONFIG;
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_CONFIG );
		#if (MX_CAN_EXID_X == 1)
			sidh = MX_CAN_EIDSH(id);
			sidl = MX_CAN_EIDSL(id);
			eidh = MX_CAN_EIDEH(id);
			eidl = MX_CAN_EIDEL(id);
		#else
			sidh = MX_CAN_SIDH(id);
			sidl = MX_CAN_SIDL(id);
			eidh = 0xff;
			eidl = 0xff;
		#endif
		switch(mask)
		{
			case 0:
				RXM0SIDH = sidh;
				RXM0SIDL = sidl;
				RXM0EIDH = eidh;
				RXM0EIDL = eidl;
				break;
			case 1:
				RXM1SIDH = sidh;
				RXM1SIDL = sidl;
				RXM1EIDH = eidh;
				RXM1EIDL = eidl;
				break;
		}
		// change to normal mode
		CANCON = MX_CAN_REQOP_NORMAL;
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_NORMAL );
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilter_, (MX_UINT8 filter, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)
		MX_UINT8 sidh;
		MX_UINT8 sidl;
		MX_UINT8 eidh;
		MX_UINT8 eidl;
		// change to config mode
		CANCON = MX_CAN_REQOP_CONFIG;
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_CONFIG );
		#if (MX_CAN_EXID_X == 1)
			sidh = MX_CAN_EIDSH(id);
			sidl = MX_CAN_EIDSL(id);
			eidh = MX_CAN_EIDEH(id);
			eidl = MX_CAN_EIDEL(id);
		#else
			sidh = MX_CAN_SIDH(id);
			sidl = MX_CAN_SIDL(id);
			eidh = 0xff;
			eidl = 0xff;
		#endif
		switch(filter)
		{
			case 0:
				RXF0SIDH = sidh;
				RXF0SIDL = sidl;
				RXF0EIDH = eidh;
				RXF0EIDL = eidl;
				break;
			case 1:
				RXF1SIDH = sidh;
				RXF1SIDL = sidl;
				RXF1EIDH = eidh;
				RXF1EIDL = eidl;
				break;
			case 2:
				RXF2SIDH = sidh;
				RXF2SIDL = sidl;
				RXF2EIDH = eidh;
				RXF2EIDL = eidl;
				break;
			case 3:
				RXF3SIDH = sidh;
				RXF3SIDL = sidl;
				RXF3EIDH = eidh;
				RXF3EIDL = eidl;
				break;
			case 4:
				RXF4SIDH = sidh;
				RXF4SIDL = sidl;
				RXF4EIDH = eidh;
				RXF4EIDL = eidl;
				break;
			case 5:
				RXF5SIDH = sidh;
				RXF5SIDL = sidl;
				RXF5EIDH = eidh;
				RXF5EIDL = eidl;
				break;
		}
		// change to normal mode
		CANCON = MX_CAN_REQOP_NORMAL;
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_NORMAL );
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdent_, (MX_UINT8 buffer, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)
		MX_UINT8 sidh;
		MX_UINT8 sidl;
		MX_UINT8 eidh;
		MX_UINT8 eidl;
		// change to config mode
		CANCON = MX_CAN_REQOP_CONFIG;
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_CONFIG );
		#if (MX_CAN_EXID_X == 1)
			sidh = MX_CAN_EIDSH(id);
			sidl = MX_CAN_EIDSL(id);
			eidh = MX_CAN_EIDEH(id);
			eidl = MX_CAN_EIDEL(id);
		#else
			sidh = MX_CAN_SIDH(id);
			sidl = MX_CAN_SIDL(id);
			eidh = 0xff;
			eidl = 0xff;
		#endif
		switch(buffer)
		{
			case 0:
				TXB0SIDH = sidh;
				TXB0SIDL = sidl;
				TXB0EIDH = eidh;
				TXB0EIDL = eidl;
				break;
			case 1:
				TXB1SIDH = sidh;
				TXB1SIDL = sidl;
				TXB1EIDH = eidh;
				TXB1EIDL = eidl;
				break;
			case 2:
				TXB2SIDH = sidh;
				TXB2SIDL = sidl;
				TXB2EIDH = eidh;
				TXB2EIDL = eidl;
				break;
		}
		// change to normal mode
		CANCON = MX_CAN_REQOP_NORMAL;
		while( (CANSTAT & MX_CAN_OP_MODE_BITS) != MX_CAN_REQOP_NORMAL );
	#endif
}

CALFUNCTION(MX_UINT32, FC_CAL_Internal_CAN_GetRxIdent_, (MX_UINT8 buffer))
{
	#if (MX_CAN_CHANNEL_X == 1)
		MX_UINT32 id = 0;
		MX_UINT8 sidh = 0;
		MX_UINT8 sidl = 0;
		MX_UINT8 eidh = 0;
		MX_UINT8 eidl = 0;
		switch(buffer)
		{
			case 0:
				sidh = RXB0SIDH;
				sidl = RXB0SIDL;
				eidh = RXB0EIDH;
				eidl = RXB0EIDL;
				break;
			case 1:
				sidh = RXB1SIDH;
				sidl = RXB1SIDL;
				eidh = RXB1EIDH;
				eidl = RXB1EIDL;
				break;
		}
		if (sidl & 0x08)
		{
			// Extended ID message
			id = ((MX_UINT32)sidh << 21) | (((MX_UINT32)sidl & 0xE0) << 13) | (((MX_UINT32)sidl & 0x03) << 16) | ((MX_UINT32)eidh << 8) | (MX_UINT32)eidl;
		}
		else
		{
			// Standard ID message
			id = ((MX_UINT16)sidh << 3) | (((MX_UINT16)sidl >> 5) & 7);
		}
		return id;
	#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxDataCount_, (MX_UINT8 buffer))
{
	#if (MX_CAN_CHANNEL_X == 1)
	return (CAN_MSG_DLC);
	#endif
}
	
CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxData_, (MX_UINT8 buffer, MX_UINT8 index))
{
	#if (MX_CAN_CHANNEL_X == 1)
	return (CAN_MSG_DATA[index & 7]);
	#endif
}

#endif
