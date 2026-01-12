// CRC: A6459004C43C0517DC6DFC5681C2AD698104299A14C9E1875427A2F7EF4303D9CFD76A29863CD488DE50EA9D9C0AC8D16B2CA784FFAB0B31469AD0B2DE0C4AE79A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5A1EC1E89F18E77D905EA2E5615CF684533D071C86F66D5F7A823568A5D63EA45FED3136B00FB5CC0D82082FB8C8AB7F180E140ED39501DC7BC5D96B6E197E2114F38E7F0444B2C8DBBE0D1EDCE205ECB4B066FE0AF5B7B80549D34A0D5AD11F33067FADC955DBB56186110CA914EA9D45D9C37322734229FBB7835FE546B805B7544DA781CA69696
// REVISION: 1.0
// GUID: 34A71D73-B820-42D4-A401-4FF7436B82C3
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\PIC32BIT_CAL_CAN.c
/*********************************************************************
 *                  Flowcode CAL CAN File
 *
 * File: PIC32BIT_CAL_CAN.c
 *
 * (c) 2011-2018 Matrix TSL
 * http://www.matrixtsl.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix Multimedia Ltd (the
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
 * 260418 | LM | Created 
 * 
 */

#ifndef PIC32BIT_CAL_CAN_DEF
#define PIC32BIT_CAL_CAN_DEF

struct cmsgsid
{
	unsigned SID:11;
	unsigned FILHIT:5;
	unsigned CMSGTS:16;
};

struct cmsgeid
{
	unsigned DLC:4;
	unsigned RB0:1;
	unsigned :3;
	unsigned RB1:1;
	unsigned RTR:1;
	unsigned EID:18;
	unsigned IDE:1;
	unsigned SRR:1;
	unsigned :2;
} ;

struct cmsgdata0
{
	unsigned Byte0:8;
	unsigned Byte1:8;
	unsigned Byte2:8;
	unsigned Byte3:8;
} ;

struct cmsgdata1
{
	unsigned Byte4:8;
	unsigned Byte5:8;
	unsigned Byte6:8;
	unsigned Byte7:8;
} ;

struct cmsbuffer 
{
	struct cmsgsid   CMSGSID;
	struct cmsgeid   CMSGEID;
	struct cmsgdata0 CMSGDATA0;
	struct cmsgdata1 CMSGDATA1;
} ;

#endif // PIC32BIT_CAL_CAN_DEF


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


#define MX_CAN_CHANNEL_X		CAL_APPEND(MX_CAN_CHANNEL_, MX_CAN_NUM)
// MX_CAN_CFG_X is a single 32 bit value representing the CxCFG register setting
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

#define MX_CAN_MSG_DLC_X		CAL_APPEND(MX_CAN_MSG_DLC_, MX_CAN_NUM)
#define MX_CAN_MSG_DATA_X		CAL_APPEND(MX_CAN_MSG_DATA_, MX_CAN_NUM)
#define MX_CAN_MSG_ID_X			CAL_APPEND(MX_CAN_MSG_ID_, MX_CAN_NUM)

#ifndef REQOP_CONFIG
  #define REQOP_CONFIG		0x04
  #define REQOP_LISTEN		0x03
  #define REQOP_LOOPBACK	0x02
  #define REQOP_SLEEP		0x01
  #define REQOP_NORMAL		0x00
  #define MX_CAN_REJECT_ALL 	(0)
  #define MX_CAN_USE_FILTERS	(1)
  #define MX_CAN_ACCEPT_ALL 	(2)
#endif


#define MX_CAN_BUFFER_X		CAL_APPEND(MX_CAN_BUFFER_, MX_CAN_NUM)
struct cmsbuffer MX_CAN_BUFFER_X[5] __attribute__((aligned(16*16)));

// Received data buffers, two, for Flowcode API
MX_UINT8  MX_CAN_MSG_DLC_X[2];
MX_UINT8  MX_CAN_MSG_DATA_X[2][8];
MX_UINT32 MX_CAN_MSG_ID_X[2];


CALFUNCTION(void, FC_CAL_Internal_CAN_Init_, (void))
{
	#if (MX_CAN_CHANNEL_X == 1)
		#ifdef MX_CAN_1_REMAPPABLE
			MX_CAN_1_TX_RPOR = MX_CAN_1_TX_RPNUM;
			MX_CAN_1_RX_RPINR = MX_CAN_1_RX_RP;
		#endif
			// Request config mode.
			C1CONbits.REQOP = REQOP_CONFIG;
			while(C1CONbits.OPMOD != REQOP_CONFIG);
			
			// Setup FIFO 0
			C1FIFOCON0bits.TXEN = 1;	// Transmit buffer 0
			C1FIFOCON0bits.FSIZE = 0;	// 1 message deep
			// Setup FIFO 1
			C1FIFOCON1bits.TXEN = 1;	// Transmit buffer 1
			C1FIFOCON1bits.FSIZE = 0;	// 1 message deep
			// Setup FIFO 2
			C1FIFOCON2bits.TXEN = 1;	// Transmit buffer 2
			C1FIFOCON2bits.FSIZE = 0;	// 1 message deep
			
			// Receive buffers, yet to use the full power of FIFO!
			// Setup FIFO 3
			C1FIFOCON3bits.TXEN = 0;	// Receive buffer 0
			C1FIFOCON3bits.DONLY = 0;	// Full message is stored
			C1FIFOCON3bits.FSIZE = 0;	// 1 message deep
			// Setup FIFO 4
			C1FIFOCON4bits.TXEN = 0;	// Receive buffer 1
			C1FIFOCON4bits.DONLY = 0;	// Full message is stored
			C1FIFOCON4bits.FSIZE = 0;	// 1 message deep
			
			// Set FIFO memory location
			C1FIFOBA = (MX_UINT32)&MX_CAN_BUFFER_X[0];
			
			// Setup Baud rate prescaler and segment sizes
			// Set it all from one (32 bit int) property value, for now
			// This will be configurable as a custom value displayed as a C1CFG property in the Flowcode component
			C1CFG = MX_CAN_CFG_X;	

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
			
			// Set to operating (normal) mode
			C1CONbits.REQOP = REQOP_NORMAL;
			while(C1CONbits.OPMOD != REQOP_NORMAL);
	#endif

	#if (MX_CAN_CHANNEL_X == 2)
		#ifdef MX_CAN_1_REMAPPABLE
			MX_CAN_2_TX_RPOR = MX_CAN_2_TX_RPNUM;
			MX_CAN_2_RX_RPINR = MX_CAN_2_RX_RP;
		#endif
			// Request config mode.
			C2CONbits.REQOP = REQOP_CONFIG;
			while(C2CONbits.OPMOD != REQOP_CONFIG);
			
			// Setup FIFO 0
			C2FIFOCON0bits.TXEN = 1;	// Transmit buffer 0
			C2FIFOCON0bits.FSIZE = 0;	// 1 message deep
			// Setup FIFO 1
			C2FIFOCON1bits.TXEN = 1;	// Transmit buffer 1
			C2FIFOCON1bits.FSIZE = 0;	// 1 message deep
			// Setup FIFO 2
			C2FIFOCON2bits.TXEN = 1;	// Transmit buffer 2
			C2FIFOCON2bits.FSIZE = 0;	// 1 message deep
			
			// Receive buffers, yet to use the full power of FIFO!
			// Setup FIFO 3
			C2FIFOCON3bits.TXEN = 0;	// Receive buffer 0
			C2FIFOCON3bits.DONLY = 0;	// Full message is stored
			C2FIFOCON3bits.FSIZE = 0;	// 1 message deep
			// Setup FIFO 4
			C2FIFOCON4bits.TXEN = 0;	// Receive buffer 1
			C2FIFOCON4bits.DONLY = 0;	// Full message is stored
			C2FIFOCON4bits.FSIZE = 0;	// 1 message deep
			
			// Set FIFO memory location
			C2FIFOBA = (MX_UINT32)&MX_CAN_BUFFER_X[0];
			
			// Setup Baud rate prescaler and segment sizes
			// Set it all from one (32 bit int) property value, for now
			// This will be configurable as a custom value displayed as a C1CFG property in the Flowcode component
			C2CFG = MX_CAN_CFG_X;	

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
			
			// Set to operating (normal) mode
			C2CONbits.REQOP = REQOP_NORMAL;
			while(C2CONbits.OPMOD != REQOP_NORMAL);
   	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_Uninit_, (void))
{
		#if (MX_CAN_CHANNEL_X == 1)
			// Request config mode.
			C1CONbits.REQOP = REQOP_CONFIG;
			while(C1CONbits.OPMOD != REQOP_CONFIG);
			C1CONCLR = 0x00008000;
			while(C1CONbits.CANBUSY == 1);
		#endif

		#if (MX_CAN_CHANNEL_X == 2)
			// Request config mode.
			C2CONbits.REQOP = REQOP_CONFIG;
			while(C2CONbits.OPMOD != REQOP_CONFIG);
			C2CONCLR = 0x00008000;
			while(C2CONbits.CANBUSY == 1);
		#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SendBuffer_, (MX_UINT8 buffer))
{
	MX_UINT32 timeout = 0xFFFF;

		#if (MX_CAN_CHANNEL_X == 1)
			switch (buffer)
			{
				case 0:
					C1FIFOCON0bits.TXREQ = 1;
					while (C1FIFOCON0bits.TXREQ && timeout--);
					break;
				case 1:
					C1FIFOCON1bits.TXREQ = 1;
					while (C1FIFOCON1bits.TXREQ && timeout--);
					break;
				case 2:
					C1FIFOCON2bits.TXREQ = 1;
					while (C1FIFOCON2bits.TXREQ && timeout--);
					break;
			}
		#endif

		#if (MX_CAN_CHANNEL_X == 2)
			switch (buffer)
			{
				case 0:
					C2FIFOCON0bits.TXREQ = 1;
					while (C2FIFOCON0bits.TXREQ && timeout--);
					break;
				case 1:
					C2FIFOCON1bits.TXREQ = 1;
					while (C2FIFOCON1bits.TXREQ && timeout--);
					break;
				case 2:
					C2FIFOCON2bits.TXREQ = 1;
					while (C2FIFOCON2bits.TXREQ && timeout--);
					break;
			}
		#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_CheckRx_, (MX_UINT8 buffer))
{
#if (MX_CAN_CHANNEL_X == 1)
	switch (buffer)
	{
		case 0:
			/* Check if there is a message available to read in Buffer 0, FIFO 3 */
			if (C1FIFOINT3bits.RXNEMPTYIF == 1)
			{
				struct cmsbuffer *rxMessage = (struct cmsbuffer *)C1FIFOUA3;
				if (rxMessage->CMSGEID.IDE)
					MX_CAN_MSG_ID_X[buffer] = ((MX_UINT32)rxMessage->CMSGSID.SID << 18)|(rxMessage->CMSGEID.EID);
				else
					MX_CAN_MSG_ID_X[buffer] = rxMessage->CMSGSID.SID;
				MX_CAN_MSG_DLC_X[buffer] = rxMessage->CMSGEID.DLC;
				MX_CAN_MSG_DATA_X[buffer][0] = rxMessage->CMSGDATA0.Byte0;
				MX_CAN_MSG_DATA_X[buffer][1] = rxMessage->CMSGDATA0.Byte1;
				MX_CAN_MSG_DATA_X[buffer][2] = rxMessage->CMSGDATA0.Byte2;
				MX_CAN_MSG_DATA_X[buffer][3] = rxMessage->CMSGDATA0.Byte3;
				MX_CAN_MSG_DATA_X[buffer][4] = rxMessage->CMSGDATA1.Byte4;
				MX_CAN_MSG_DATA_X[buffer][5] = rxMessage->CMSGDATA1.Byte5;
				MX_CAN_MSG_DATA_X[buffer][6] = rxMessage->CMSGDATA1.Byte6;
				MX_CAN_MSG_DATA_X[buffer][7] = rxMessage->CMSGDATA1.Byte7;
				C1FIFOCON3bits.UINC = 1;
				return 1;
			}
			break;
		case 1:
			/* Check if there is a message available to read in Buffer 1, FIFO 4 */
			if (C1FIFOINT4bits.RXNEMPTYIF == 1)
			{
				struct cmsbuffer *rxMessage = (struct cmsbuffer *)C1FIFOUA4;
				if (rxMessage->CMSGEID.IDE)
					MX_CAN_MSG_ID_X[buffer] = ((MX_UINT32)rxMessage->CMSGSID.SID << 18)|(rxMessage->CMSGEID.EID);
				else
					MX_CAN_MSG_ID_X[buffer] = rxMessage->CMSGSID.SID;
				MX_CAN_MSG_DLC_X[buffer] = rxMessage->CMSGEID.DLC;
				MX_CAN_MSG_DATA_X[buffer][0] = rxMessage->CMSGDATA0.Byte0;
				MX_CAN_MSG_DATA_X[buffer][1] = rxMessage->CMSGDATA0.Byte1;
				MX_CAN_MSG_DATA_X[buffer][2] = rxMessage->CMSGDATA0.Byte2;
				MX_CAN_MSG_DATA_X[buffer][3] = rxMessage->CMSGDATA0.Byte3;
				MX_CAN_MSG_DATA_X[buffer][4] = rxMessage->CMSGDATA1.Byte4;
				MX_CAN_MSG_DATA_X[buffer][5] = rxMessage->CMSGDATA1.Byte5;
				MX_CAN_MSG_DATA_X[buffer][6] = rxMessage->CMSGDATA1.Byte6;
				MX_CAN_MSG_DATA_X[buffer][7] = rxMessage->CMSGDATA1.Byte7;
				C1FIFOCON4bits.UINC = 1;
				return 1;
			}
			break;
	}
#endif

#if (MX_CAN_CHANNEL_X == 2)
	switch (buffer)
	{
		case 0:
			/* Check if there is a message available to read in Buffer 0, FIFO 3 */
			if (C2FIFOINT3bits.RXNEMPTYIF == 1)
			{
				struct cmsbuffer *rxMessage = (struct cmsbuffer *)C2FIFOUA3;
				if (rxMessage->CMSGEID.IDE)
					MX_CAN_MSG_ID_X[buffer] = ((MX_UINT32)rxMessage->CMSGSID.SID << 18)|(rxMessage->CMSGEID.EID);
				else
					MX_CAN_MSG_ID_X[buffer] = rxMessage->CMSGSID.SID;
				MX_CAN_MSG_DLC_X[buffer] = rxMessage->CMSGEID.DLC;
				MX_CAN_MSG_DATA_X[buffer][0] = rxMessage->CMSGDATA0.Byte0;
				MX_CAN_MSG_DATA_X[buffer][1] = rxMessage->CMSGDATA0.Byte1;
				MX_CAN_MSG_DATA_X[buffer][2] = rxMessage->CMSGDATA0.Byte2;
				MX_CAN_MSG_DATA_X[buffer][3] = rxMessage->CMSGDATA0.Byte3;
				MX_CAN_MSG_DATA_X[buffer][4] = rxMessage->CMSGDATA1.Byte4;
				MX_CAN_MSG_DATA_X[buffer][5] = rxMessage->CMSGDATA1.Byte5;
				MX_CAN_MSG_DATA_X[buffer][6] = rxMessage->CMSGDATA1.Byte6;
				MX_CAN_MSG_DATA_X[buffer][7] = rxMessage->CMSGDATA1.Byte7;
				C2FIFOCON3bits.UINC = 1;
				return 1;
			}
			break;
		case 1:
			/* Check if there is a message available to read in Buffer 1, FIFO 4 */
			if (C2FIFOINT4bits.RXNEMPTYIF == 1)
			{
				struct cmsbuffer *rxMessage = (struct cmsbuffer *)C2FIFOUA4;
				if (rxMessage->CMSGEID.IDE)
					MX_CAN_MSG_ID_X[buffer] = ((MX_UINT32)rxMessage->CMSGSID.SID << 18)|(rxMessage->CMSGEID.EID);
				else
					MX_CAN_MSG_ID_X[buffer] = rxMessage->CMSGSID.SID;
				MX_CAN_MSG_DLC_X[buffer] = rxMessage->CMSGEID.DLC;
				MX_CAN_MSG_DATA_X[buffer][0] = rxMessage->CMSGDATA0.Byte0;
				MX_CAN_MSG_DATA_X[buffer][1] = rxMessage->CMSGDATA0.Byte1;
				MX_CAN_MSG_DATA_X[buffer][2] = rxMessage->CMSGDATA0.Byte2;
				MX_CAN_MSG_DATA_X[buffer][3] = rxMessage->CMSGDATA0.Byte3;
				MX_CAN_MSG_DATA_X[buffer][4] = rxMessage->CMSGDATA1.Byte4;
				MX_CAN_MSG_DATA_X[buffer][5] = rxMessage->CMSGDATA1.Byte5;
				MX_CAN_MSG_DATA_X[buffer][6] = rxMessage->CMSGDATA1.Byte6;
				MX_CAN_MSG_DATA_X[buffer][7] = rxMessage->CMSGDATA1.Byte7;
				C2FIFOCON4bits.UINC = 1;
				return 1;
			}
			break;
	}
#endif
	return 0;
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxData_, (MX_UINT8 buffer, MX_UINT8 data_cnt, MX_UINT8 d0, MX_UINT8 d1, MX_UINT8 d2, MX_UINT8 d3, MX_UINT8 d4, MX_UINT8 d5, MX_UINT8 d6, MX_UINT8 d7))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		if (buffer < 3)
		{
			struct cmsbuffer *txMessage = &MX_CAN_BUFFER_X[buffer];
			txMessage->CMSGEID.DLC = data_cnt;
			txMessage->CMSGDATA0.Byte0 = d0;
			txMessage->CMSGDATA0.Byte1 = d1;
			txMessage->CMSGDATA0.Byte2 = d2;
			txMessage->CMSGDATA0.Byte3 = d3;
			txMessage->CMSGDATA1.Byte4 = d4;
			txMessage->CMSGDATA1.Byte5 = d5;
			txMessage->CMSGDATA1.Byte6 = d6;
			txMessage->CMSGDATA1.Byte7 = d7;
		}
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdentStd_, (MX_UINT8 buffer, MX_UINT8 hi, MX_UINT8 lo))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		if (buffer < 3)
		{
			struct cmsbuffer *txMessage = &MX_CAN_BUFFER_X[buffer];
			txMessage->CMSGEID.IDE = 0;
			txMessage->CMSGSID.SID = ((MX_UINT16)hi << 8)|(lo);
		}
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdentExd_, (MX_UINT8 buffer, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		MX_UINT32 id = ((MX_UINT32)id3 << 24) | ((MX_UINT32)id2 << 16) | ((MX_UINT32)id1 << 8) | id0 ;
		if (buffer < 3)
		{
			struct cmsbuffer *txMessage = &MX_CAN_BUFFER_X[buffer];
			txMessage->CMSGEID.IDE = 1;
			txMessage->CMSGEID.EID = id;
			txMessage->CMSGSID.SID = id >> 18;
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

/******************************************************************
These Receiver Mask and Filter functions
maintain the same API for the Flowcode CAN component
as for the MCP2515 external controller, hence:

Receive Buffer 0 (FIFO 3) is associated with Mask 0 and Filters 0, 1
Receive Buffer 1 (FIFO 4) is associated with Mask 1 and Filters 2, 3, 4, 5

******************************************************************/
CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMask_, (MX_UINT8 mask, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)
		if (mask == 0)
		{
			// Mask 0
			#if (MX_CAN_EXID_X == 0)
				C1RXM0bits.SID = id;
				C1RXM0bits.EID = 0;
			#else
				C1RXM0bits.SID = id >> 18;
				C1RXM0bits.EID = id;
			#endif
			C1RXM0bits.MIDE = 1;		// Match only message types
		}
		else
		{
			// Mask 1
			#if (MX_CAN_EXID_X == 0)
				C1RXM1bits.SID = id;
				C1RXM1bits.EID = 0;
			#else
				C1RXM1bits.SID = id >> 18;
				C1RXM1bits.EID = id;
			#endif
			C1RXM1bits.MIDE = 1;		// Match only message types
		}
	#endif
	#if (MX_CAN_CHANNEL_X == 2)
		if (mask == 0)
		{
			// Mask 0
			#if (MX_CAN_EXID_X == 0)
				C2RXM0bits.SID = id;
				C2RXM0bits.EID = 0;
			#else
				C2RXM0bits.SID = id >> 18;
				C2RXM0bits.EID = id;
			#endif
			C2RXM0bits.MIDE = 1;		// Match only message types
		}
		else
		{
			// Mask 1
			#if (MX_CAN_EXID_X == 0)
				C2RXM1bits.SID = id;
				C2RXM1bits.EID = 0;
			#else
				C2RXM1bits.SID = id >> 18;
				C2RXM1bits.EID = id;
			#endif
			C2RXM1bits.MIDE = 1;		// Match only message types
		}
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilter_, (MX_UINT8 filter, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)
		switch (filter)
		{
			case 0:
				// Filter 0 Associated with Receive Buffer 0 (FIFO 3) and Mask 0
				C1FLTCON0bits.FLTEN0 = 0;	// Disable the filter
				while (C1FLTCON0bits.FLTEN0);
				C1FLTCON0bits.FSEL0 = 3;	// Store buffer 0 messages in FIFO 3
				C1FLTCON0bits.MSEL0 = 0;	// Use Mask 0
				#if (MX_CAN_EXID_X == 0)
					C1RXF0bits.SID = id;
					C1RXF0bits.EID = 0;
					C1RXF0bits.EXID = 0;
				#else
					C1RXF0bits.SID = id >> 18;
					C1RXF0bits.EID = id;
					C1RXF0bits.EXID = 1;
				#endif
				C1FLTCON0bits.FLTEN0 = 1;	// Enable the filter
				break;
			case 1:
				// Filter 1 Associated with Receive Buffer 0 (FIFO 3) and Mask 0
				C1FLTCON0bits.FLTEN1 = 0;	// Disable the filter
				while (C1FLTCON0bits.FLTEN1);
				C1FLTCON0bits.FSEL1 = 3;	// Store buffer 0 messages in FIFO 3
				C1FLTCON0bits.MSEL1 = 0;	// Use Mask 0
				#if (MX_CAN_EXID_X == 0)
					C1RXF1bits.SID = id;
					C1RXF1bits.EID = 0;
					C1RXF1bits.EXID = 0;
				#else
					C1RXF1bits.SID = id >> 18;
					C1RXF1bits.EID = id;
					C1RXF1bits.EXID = 1;
				#endif
				C1FLTCON0bits.FLTEN1 = 1;	// Enable the filter
				break;
			case 2:
				// Filter 2 Associated with Receive Buffer 1 (FIFO 4) and Mask 1
				C1FLTCON0bits.FLTEN2 = 0;	// Disable the filter
				while (C1FLTCON0bits.FLTEN2);
				C1FLTCON0bits.FSEL2 = 4;	// Store buffer 1 messages in FIFO 4
				C1FLTCON0bits.MSEL2 = 1;	// Use Mask 1
				#if (MX_CAN_EXID_X == 0)
					C1RXF2bits.SID = id;
					C1RXF2bits.EID = 0;
					C1RXF2bits.EXID = 0;
				#else
					C1RXF2bits.SID = id >> 18;
					C1RXF2bits.EID = id;
					C1RXF2bits.EXID = 1;
				#endif
				C1FLTCON0bits.FLTEN2 = 1;	// Enable the filter
				break;
			case 3:
				// Filter 3 Associated with Receive Buffer 1 (FIFO 4) and Mask 1
				C1FLTCON0bits.FLTEN3 = 0;	// Disable the filter
				while (C1FLTCON0bits.FLTEN3);
				C1FLTCON0bits.FSEL3 = 4;	// Store buffer 1 messages in FIFO 4
				C1FLTCON0bits.MSEL3 = 1;	// Use Mask 1
				#if (MX_CAN_EXID_X == 0)
					C1RXF3bits.SID = id;
					C1RXF3bits.EID = 0;
					C1RXF3bits.EXID = 0;
				#else
					C1RXF3bits.SID = id >> 18;
					C1RXF3bits.EID = id;
					C1RXF3bits.EXID = 1;
				#endif
				C1FLTCON0bits.FLTEN3 = 1;	// Enable the filter
				break;
			case 4:
				// Filter 4 Associated with Receive Buffer 1 (FIFO 4) and Mask 1
				C1FLTCON1bits.FLTEN4 = 0;	// Disable the filter
				while (C1FLTCON1bits.FLTEN4);
				C1FLTCON1bits.FSEL4 = 4;	// Store buffer 1 messages in FIFO 4
				C1FLTCON1bits.MSEL4 = 1;	// Use Mask 1
				#if (MX_CAN_EXID_X == 0)
					C1RXF4bits.SID = id;
					C1RXF4bits.EID = 0;
					C1RXF4bits.EXID = 0;
				#else
					C1RXF4bits.SID = id >> 18;
					C1RXF4bits.EID = id;
					C1RXF4bits.EXID = 1;
				#endif
				C1FLTCON1bits.FLTEN4 = 1;	// Enable the filter
				break;
			case 5:
				// Filter 5 Associated with Receive Buffer 1 (FIFO 4) and Mask 1
				C1FLTCON1bits.FLTEN5 = 0;	// Disable the filter
				while (C1FLTCON1bits.FLTEN5);
				C1FLTCON1bits.FSEL5 = 4;	// Store buffer 1 messages in FIFO 4
				C1FLTCON1bits.MSEL5 = 1;	// Use Mask 1
				#if (MX_CAN_EXID_X == 0)
					C1RXF5bits.SID = id;
					C1RXF5bits.EID = 0;
					C1RXF5bits.EXID = 0;
				#else
					C1RXF5bits.SID = id >> 18;
					C1RXF5bits.EID = id;
					C1RXF5bits.EXID = 1;
				#endif
				C1FLTCON1bits.FLTEN5 = 1;	// Enable the filter
				break;
		}
	#endif
	#if (MX_CAN_CHANNEL_X == 2)
		switch (filter)
		{
			case 0:
				// Filter 0 Associated with Receive Buffer 0 (FIFO 3) and Mask 0
				C2FLTCON0bits.FLTEN0 = 0;	// Disable the filter
				while (C2FLTCON0bits.FLTEN0);
				C2FLTCON0bits.FSEL0 = 3;	// Store buffer 0 messages in FIFO 3
				C2FLTCON0bits.MSEL0 = 0;	// Use Mask 0
				#if (MX_CAN_EXID_X == 0)
					C2RXF0bits.SID = id;
					C2RXF0bits.EID = 0;
					C2RXF0bits.EXID = 0;
				#else
					C2RXF0bits.SID = id >> 18;
					C2RXF0bits.EID = id;
					C2RXF0bits.EXID = 1;
				#endif
				C2FLTCON0bits.FLTEN0 = 1;	// Enable the filter
				break;
			case 1:
				// Filter 1 Associated with Receive Buffer 0 (FIFO 3) and Mask 0
				C2FLTCON0bits.FLTEN1 = 0;	// Disable the filter
				while (C2FLTCON0bits.FLTEN1);
				C2FLTCON0bits.FSEL1 = 3;	// Store buffer 0 messages in FIFO 3
				C2FLTCON0bits.MSEL1 = 0;	// Use Mask 0
				#if (MX_CAN_EXID_X == 0)
					C2RXF1bits.SID = id;
					C2RXF1bits.EID = 0;
					C2RXF1bits.EXID = 0;
				#else
					C2RXF1bits.SID = id >> 18;
					C2RXF1bits.EID = id;
					C2RXF1bits.EXID = 1;
				#endif
				C2FLTCON0bits.FLTEN1 = 1;	// Enable the filter
				break;
			case 2:
				// Filter 2 Associated with Receive Buffer 1 (FIFO 4) and Mask 1
				C2FLTCON0bits.FLTEN2 = 0;	// Disable the filter
				while (C2FLTCON0bits.FLTEN2);
				C2FLTCON0bits.FSEL2 = 4;	// Store buffer 1 messages in FIFO 4
				C2FLTCON0bits.MSEL2 = 1;	// Use Mask 1
				#if (MX_CAN_EXID_X == 0)
					C2RXF2bits.SID = id;
					C2RXF2bits.EID = 0;
					C2RXF2bits.EXID = 0;
				#else
					C2RXF2bits.SID = id >> 18;
					C2RXF2bits.EID = id;
					C2RXF2bits.EXID = 1;
				#endif
				C2FLTCON0bits.FLTEN2 = 1;	// Enable the filter
				break;
			case 3:
				// Filter 3 Associated with Receive Buffer 1 (FIFO 4) and Mask 1
				C2FLTCON0bits.FLTEN3 = 0;	// Disable the filter
				while (C2FLTCON0bits.FLTEN3);
				C2FLTCON0bits.FSEL3 = 4;	// Store buffer 1 messages in FIFO 4
				C2FLTCON0bits.MSEL3 = 1;	// Use Mask 1
				#if (MX_CAN_EXID_X == 0)
					C2RXF3bits.SID = id;
					C2RXF3bits.EID = 0;
					C2RXF3bits.EXID = 0;
				#else
					C2RXF3bits.SID = id >> 18;
					C2RXF3bits.EID = id;
					C2RXF3bits.EXID = 1;
				#endif
				C2FLTCON0bits.FLTEN3 = 1;	// Enable the filter
				break;
			case 4:
				// Filter 4 Associated with Receive Buffer 1 (FIFO 4) and Mask 1
				C2FLTCON1bits.FLTEN4 = 0;	// Disable the filter
				while (C2FLTCON1bits.FLTEN4);
				C2FLTCON1bits.FSEL4 = 4;	// Store buffer 1 messages in FIFO 4
				C2FLTCON1bits.MSEL4 = 1;	// Use Mask 1
				#if (MX_CAN_EXID_X == 0)
					C2RXF4bits.SID = id;
					C2RXF4bits.EID = 0;
					C2RXF4bits.EXID = 0;
				#else
					C2RXF4bits.SID = id >> 18;
					C2RXF4bits.EID = id;
					C2RXF4bits.EXID = 1;
				#endif
				C2FLTCON1bits.FLTEN4 = 1;	// Enable the filter
				break;
			case 5:
				// Filter 5 Associated with Receive Buffer 1 (FIFO 4) and Mask 1
				C2FLTCON1bits.FLTEN5 = 0;	// Disable the filter
				while (C2FLTCON1bits.FLTEN5);
				C2FLTCON1bits.FSEL5 = 4;	// Store buffer 1 messages in FIFO 4
				C2FLTCON1bits.MSEL5 = 1;	// Use Mask 1
				#if (MX_CAN_EXID_X == 0)
					C2RXF5bits.SID = id;
					C2RXF5bits.EID = 0;
					C2RXF5bits.EXID = 0;
				#else
					C2RXF5bits.SID = id >> 18;
					C2RXF5bits.EID = id;
					C2RXF5bits.EXID = 1;
				#endif
				C2FLTCON1bits.FLTEN5 = 1;	// Enable the filter
				break;
		}
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdent_, (MX_UINT8 buffer, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)||(MX_CAN_CHANNEL_X == 2)
		if (buffer < 3)
		{
			struct cmsbuffer *txMessage = &MX_CAN_BUFFER_X[buffer];
			#if (MX_CAN_EXID_X == 0)
				txMessage->CMSGEID.IDE = 0;
				txMessage->CMSGSID.SID = id;
			#else
				txMessage->CMSGEID.IDE = 1;
				txMessage->CMSGEID.EID = id;
				txMessage->CMSGSID.SID = id >> 18;
			#endif
		}
	#endif
}

CALFUNCTION(MX_UINT32, FC_CAL_Internal_CAN_GetRxIdent_, (MX_UINT8 buffer))
{
	return MX_CAN_MSG_ID_X[buffer & 1];
}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxDataCount_, (MX_UINT8 buffer))
{
	return (MX_CAN_MSG_DLC_X[buffer & 1]);
}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxData_, (MX_UINT8 buffer, MX_UINT8 index))
{
	return (MX_CAN_MSG_DATA_X[buffer & 1][index & 7]);
}


