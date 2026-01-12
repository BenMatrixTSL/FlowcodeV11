// CRC: 5D982BB222882C54AB4AFF20A1590FC484D3178BD0D2510D0F5A64A7853221CAE2C33FABBE4F69A6659399D51781B7B96B2CA784FFAB0B31469AD0B2DE0C4AE7F354AA71734CF0DA1345D4F62132DD03562AF2F62E9AB6760C3CAEE8E7DA6987D6CFCA890B0101BEFC26F6046DEEE1BDC289C1AC3D44D4438C6CD581AF9C057043214DA6C569CDAAD938365A0B1E94A4D7FA7622D65226135C23DCFB6B9176E26EDAC1A7CB13B6620F41C431DF4F39CEA234862CBD14D6A7549D34A0D5AD11F3B0E7FE5A41EF69FD674885F709F626952F9D03BEA8F75AF1A3608A0B0CE69F969622A912E6E6A2FB
// REVISION: 2.0
// GUID: B2E7FADF-EF51-464D-8DD4-293A82E94B3D
// DATE: 18\12\2025
// DIR: CAL\PIC16BIT\PIC16BIT_CAL_CAN.c
/*********************************************************************
 *                  Flowcode CAL CAN File
 *
 * File: PIC16BIT_CAL_CAN.c
 *
 * (c) 2011 Matrix Multimedia Ltd.
 * http://www.matrixmultimedia.com
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
 * 230911 | BR | Created
 * 020312 | BR | Updated to v5.1 CAL Schema
 * 101012 | BR | Fixed a bug where the config mode bits were not defined correctly
 * 111012 | LM | Added initialization value for CANCTRL (and fixed typo)
 * 030713 | LM | Standard API calls
 * 110913 | LM | Change to unified config for id, mask and filter setting
 * 020614 | JK | Add support for ECAN controllers in dsPIC33 series
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
#endif

#ifndef MX_CAN_INT_DEFS
  #define MX_CAN_INT_DEFS
  #define CAN_OP_MODE_BITS 		0xE0

  #define MX_CAN_RXESID(v) ((v >> 16) | 1)
  #define MX_CAN_RXEIDL(v) (v << 10)
  #define MX_CAN_RXEIDH(v) (v >> 6)
  #define MX_CAN_TXESID(v) ((((v&0x1F000000) >> 13)|((v&0xFC0000) >> 16)) | 1)
  #define MX_CAN_TXEEID(v) (((v&0x3C000) >> 2)|((v&0x3FC0) >> 6))
  #define MX_CAN_TXEDLC(v) (v << 10)

  #define MX_CAN_RXSSID(v) (v << 2)
  #define MX_CAN_TXSSID(v) (((v&0x7C0) << 5)|((v&0x3F) << 2))

  #define C1CTRL_VAL  0x0800		// set CAN CKS
  #define C2CTRL_VAL  0x0800		// set CAN CKS

  #define TXB0CTRL_VAL 0
  #define TXB1CTRL_VAL 0
  #define TXB2CTRL_VAL 0

  #define RXB0CTRL_VAL 0
  #define RXB1CTRL_VAL 0

  /**
   * Not directly supported by this family CAN controller
   * Set Mask and Filter for desired result
  #define MX_CAN_REJECT_ALL 	(0)
  #define MX_CAN_USE_FILTERS	(1)
  #define MX_CAN_ACCEPT_ALL 	(2)
  **/

#endif // MX_CAN_INT_DEFS

MX_UINT8 MX_CAN_MSG_DLC_X;
MX_UINT8 MX_CAN_MSG_DATA_X[8];
#if defined (__dsPIC33E__) || defined (__PIC24E__) || defined (__dsPIC33F__) || defined (__PIC24H__)
	// For dsPIC33 now use a MX_UINT32
	MX_UINT32 MX_CAN_MSG_ID_X;
#else
MX_UINT8 MX_CAN_MSG_ID_X[4];
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

// Reserve DMA buffers for dsPIC33 family
#ifndef MX_30FCAN
#define	MX_MEMBUF_X	CAL_APPEND(MX_MEMBUF_, MX_CAN_NUM)
#define NUM_OF_CAN_BUFFERS 12

// Allocate 12 buffers, buffers 0,1,2 for transmit
// buffer 3 for 'RX Buffer 0'
// buffers 4-8 for 'RX Buffer 1', FIFO mode
#if defined (__dsPIC33E__) || defined (__PIC24E__) || defined (__dsPIC33F__) || defined (__PIC24H__)
  #if defined (FCV_DMA_BASE) && defined(__dsPIC33E__)
    __eds__ unsigned int MX_MEMBUF_X[NUM_OF_CAN_BUFFERS][8] __attribute__((eds,space(dma),aligned(16*16)));
  #else
	// The following attributes addition was a fix for dsPIC33EP128 MC502/MC506/MU806 ...
	// __eds__ unsigned int MX_MEMBUF_X[NUM_OF_CAN_BUFFERS][8] __attribute__((eds,aligned(16*16)));
	// But it seems to break dsPIC33EP512GM710 and a few others, so runs as this ...
	// (If we need it back, then add it as specific fixes)
	unsigned int MX_MEMBUF_X[NUM_OF_CAN_BUFFERS][8] __attribute__((aligned(16*16)));
  #endif
/***
  #ifndef FCV_DMA_BASE
    #define	FCV_DMA_BASE	1
  #endif
***/
#else
  #if defined (FCV_DMA_BASE) && defined(__dsPIC33E__)
    __eds__ unsigned int MX_MEMBUF_X[NUM_OF_CAN_BUFFERS][8] __attribute__((eds,space(dma),aligned(16*16)));
  #else
	__eds__ unsigned int MX_MEMBUF_X[NUM_OF_CAN_BUFFERS][8] __attribute__((eds,aligned(16*16)));
  #endif
#endif
#endif


CALFUNCTION(void, FC_CAL_Internal_CAN_Init_, (void))
{

	#if defined (__dsPIC33E__) || defined (__PIC24E__)
		MSTRPR = 0x20;		// DMA bug fix - make DMA top priority
	#endif


	#if (MX_CAN_CHANNEL_X == 1)

		//#ifndef dsPIC30	//Non dsPIC30F Device - Internal CAN different!!!
			//#error "Internal CAN is not supported in the device type. dsPIC30 only supported."
		//#endif

		// Remap pins
		#ifdef MX_CAN_1_REMAPPABLE
			MX_CAN_1_TX_RPOR = MX_CAN_1_TX_RPNUM;
			MX_CAN_1_RX_RPINR = MX_CAN_1_RX_RP;
		#endif

		#ifdef __dsPIC30F__	// dsPIC30F Device
			//configure CAN I/O - ds30F??

			C1CTRL = C1CTRL_VAL;

			// Request config mode.
			C1CTRLbits.REQOP = REQOP_CONFIG;

			// Wait till desired mode is set.
			while( C1CTRLbits.OPMODE != REQOP_CONFIG );

			// Now set the baud rate.
			C1CFG2 = MX_CAN_BAUD2_X | (MX_CAN_BAUD3_X << 8);
			C1CFG1 = MX_CAN_BAUD1_X;

			//Setup the CAN comms Masks and Filters
			#if (MX_CAN_EXID_X == 1)

				#if (MX_CAN_RXB0CFG_X == 0)		//Reject All

					C1RXF0SID = 0xFFFF;	// ID Filter 0 - Buffer 0
					C1RXF0EIDL = 0xFFFF;
					C1RXF0EIDH = 0xFFFF;
					C1RXF1SID = 0xFFFF;	// ID Filter 1 - Buffer 0
					C1RXF1EIDL = 0xFFFF;
					C1RXF1EIDH = 0xFFFF;
					C1RXM0SID = 0xFFFF;	// ID Mask 0 - Buffer 0
					C1RXM0EIDL = 0xFFFF;
					C1RXM0EIDH = 0xFFFF;

				#endif

				#if (MX_CAN_RXB0CFG_X == 1)		//Use Mask and Filter

					C1RXF0SID = MX_CAN_RXESID(MX_CAN_RXF0_X);	// ID Filter 0 - Buffer 0
					C1RXF0EIDL = MX_CAN_RXEIDL(MX_CAN_RXF0_X);
					C1RXF0EIDH = MX_CAN_RXEIDH(MX_CAN_RXF0_X);
					C1RXF1SID = MX_CAN_RXESID(MX_CAN_RXF1_X);	// ID Filter 1 - Buffer 0
					C1RXF1EIDL = MX_CAN_RXEIDL(MX_CAN_RXF1_X);
					C1RXF1EIDH = MX_CAN_RXEIDH(MX_CAN_RXF1_X);
					C1RXM0SID = MX_CAN_RXESID(MX_CAN_RXM0_X);	// ID Mask 0 - Buffer 0
					C1RXM0EIDL = MX_CAN_RXEIDL(MX_CAN_RXM0_X);
					C1RXM0EIDH = MX_CAN_RXEIDH(MX_CAN_RXM0_X);

				#endif

				#if (MX_CAN_RXB0CFG_X == 2)		//Accept All

					C1RXF0SID = 0xFFFF;	// ID Filter 0 - Buffer 0
					C1RXF0EIDL = 0xFFFF;
					C1RXF0EIDH = 0xFFFF;
					C1RXF1SID = 0xFFFF;	// ID Filter 1 - Buffer 0
					C1RXF1EIDL = 0xFFFF;
					C1RXF1EIDH = 0xFFFF;
					C1RXM0SID = 0x0000;	// ID Mask 0 - Buffer 0
					C1RXM0EIDL = 0x0000;
					C1RXM0EIDH = 0x0000;

				#endif


				#if (MX_CAN_RXB1CFG_X == 0)		//Reject All

					C1RXF2SID = 0xFFFF;	// ID Filter 2 - Buffer 1
					C1RXF2EIDL = 0xFFFF;
					C1RXF2EIDH = 0xFFFF;
					C1RXF3SID = 0xFFFF;	// ID Filter 3 - Buffer 1
					C1RXF3EIDL = 0xFFFF;
					C1RXF3EIDH = 0xFFFF;
					C1RXF4SID = 0xFFFF;	// ID Filter 4 - Buffer 1
					C1RXF4EIDL = 0xFFFF;
					C1RXF4EIDH = 0xFFFF;
					C1RXF5SID = 0xFFFF;	// ID Filter 5 - Buffer 1
					C1RXF5EIDL = 0xFFFF;
					C1RXF5EIDH = 0xFFFF;
					C1RXM1SID = 0xFFFF;	// ID Mask 1 - Buffer 1
					C1RXM1EIDL = 0xFFFF;
					C1RXM1EIDH = 0xFFFF;

				#endif

				#if (MX_CAN_RXB1CFG_X == 1)		//Use Mask and Filter

					C1RXF2SID = MX_CAN_RXESID(MX_CAN_RXF2_X);	// ID Filter 2 - Buffer 1
					C1RXF2EIDL = MX_CAN_RXEIDL(MX_CAN_RXF2_X);
					C1RXF2EIDH = MX_CAN_RXEIDH(MX_CAN_RXF2_X);
					C1RXF3SID = MX_CAN_RXESID(MX_CAN_RXF3_X);	// ID Filter 3 - Buffer 1
					C1RXF3EIDL = MX_CAN_RXEIDL(MX_CAN_RXF3_X);
					C1RXF3EIDH = MX_CAN_RXEIDH(MX_CAN_RXF3_X);
					C1RXF4SID = MX_CAN_RXESID(MX_CAN_RXF4_X);	// ID Filter 4 - Buffer 1
					C1RXF4EIDL = MX_CAN_RXEIDL(MX_CAN_RXF4_X);
					C1RXF4EIDH = MX_CAN_RXEIDH(MX_CAN_RXF4_X);
					C1RXF5SID = MX_CAN_RXESID(MX_CAN_RXF5_X);	// ID Filter 5 - Buffer 1
					C1RXF5EIDL = MX_CAN_RXEIDL(MX_CAN_RXF5_X);
					C1RXF5EIDH = MX_CAN_RXEIDH(MX_CAN_RXF5_X);
					C1RXM1SID = MX_CAN_RXESID(MX_CAN_RXM1_X);	// ID Mask 1 - Buffer 1
					C1RXM1EIDL = MX_CAN_RXEIDL(MX_CAN_RXM1_X);
					C1RXM1EIDH = MX_CAN_RXEIDH(MX_CAN_RXM1_X);

				#endif

				#if (MX_CAN_RXB1CFG_X == 2)		//Accept All

					C1RXF2SID = 0xFFFF;	// ID Filter 2 - Buffer 1
					C1RXF2EIDL = 0xFFFF;
					C1RXF2EIDH = 0xFFFF;
					C1RXF3SID = 0xFFFF;	// ID Filter 3 - Buffer 1
					C1RXF3EIDL = 0xFFFF;
					C1RXF3EIDH = 0xFFFF;
					C1RXF4SID = 0xFFFF;	// ID Filter 4 - Buffer 1
					C1RXF4EIDL = 0xFFFF;
					C1RXF4EIDH = 0xFFFF;
					C1RXF5SID = 0xFFFF;	// ID Filter 5 - Buffer 1
					C1RXF5EIDL = 0xFFFF;
					C1RXF5EIDH = 0xFFFF;
					C1RXM1SID = 0x0000;	// ID Mask 1 - Buffer 1
					C1RXM1EIDL = 0x0000;
					C1RXM1EIDH = 0x0000;

				#endif

			#else

				#if (MX_CAN_RXB0CFG_X == 0)		//Reject All

					C1RXM0SID = 0xFFFF;	// ID Mask 0 - Buffer 0
					C1RXF0SID = 0xFFFF;	// ID Filter 0 - Buffer 0
					C1RXF1SID = 0xFFFF;	// ID Filter 1 - Buffer 0

				#endif

				#if (MX_CAN_RXB0CFG_X == 1)		//Use Mask and Filter

					C1RXM0SID = MX_CAN_RXSSID(MX_CAN_RXM0_X);	// ID Mask 0 - Buffer 0
					C1RXF0SID = MX_CAN_RXSSID(MX_CAN_RXF0_X);	// ID Filter 0 - Buffer 0
					C1RXF1SID = MX_CAN_RXSSID(MX_CAN_RXF1_X);	// ID Filter 1 - Buffer 0

				#endif

				#if (MX_CAN_RXB0CFG_X == 2)		//Accept All

					C1RXM0SID = 0x0000;	// ID Mask 0 - Buffer 0
					C1RXF0SID = 0xFFFF;	// ID Filter 0 - Buffer 0
					C1RXF1SID = 0xFFFF;	// ID Filter 1 - Buffer 0

				#endif


				#if (MX_CAN_RXB1CFG_X == 0)		//Reject All

					C1RXM1SID = 0xFFFF;	// ID Mask 1 - Buffer 1
					C1RXF2SID = 0xFFFF;	// ID Filter 2 - Buffer 1
					C1RXF3SID = 0xFFFF;	// ID Filter 3 - Buffer 1
					C1RXF4SID = 0xFFFF;	// ID Filter 4 - Buffer 1
					C1RXF5SID = 0xFFFF;	// ID Filter 5 - Buffer 1

				#endif

				#if (MX_CAN_RXB1CFG_X == 1)		//Use Mask and Filter

					C1RXM1SID = MX_CAN_RXSSID(MX_CAN_RXM1_X);	// ID Mask 1 - Buffer 1
					C1RXF2SID = MX_CAN_RXSSID(MX_CAN_RXF2_X);	// ID Filter 2 - Buffer 1
					C1RXF3SID = MX_CAN_RXSSID(MX_CAN_RXF3_X);	// ID Filter 3 - Buffer 1
					C1RXF4SID = MX_CAN_RXSSID(MX_CAN_RXF4_X);	// ID Filter 4 - Buffer 1
					C1RXF5SID = MX_CAN_RXSSID(MX_CAN_RXF5_X);	// ID Filter 5 - Buffer 1

				#endif

				#if (MX_CAN_RXB1CFG_X == 2)		//Accept All

					C1RXM1SID = 0x0000;	// ID Mask 1 - Buffer 1
					C1RXF2SID = 0xFFFF;	// ID Filter 2 - Buffer 1
					C1RXF3SID = 0xFFFF;	// ID Filter 3 - Buffer 1
					C1RXF4SID = 0xFFFF;	// ID Filter 4 - Buffer 1
					C1RXF5SID = 0xFFFF;	// ID Filter 5 - Buffer 1

				#endif

			#endif
			C1RX0CON = RXB0CTRL_VAL;
			C1RX1CON = RXB1CTRL_VAL;

			C1TX0CON = TXB0CTRL_VAL;	// Transmit Buffer 0 Control
	#if (MX_CAN_EXID_X == 1)
			C1TX0SID = MX_CAN_TXESID(MX_CAN_TXB0ID_X);
			C1TX0EID = MX_CAN_TXEEID(MX_CAN_TXB0ID_X);
			C1TX0DLC = (MX_CAN_TXEDLC(MX_CAN_TXB0ID_X)) | (MX_CAN_TXB0LEN_X << 3);
	#else
			C1TX0SID = MX_CAN_TXSSID(MX_CAN_TXB0ID_X);	//Transmit Preload S-ID
			C1TX0DLC = MX_CAN_TXB0LEN_X << 3;
	#endif
			C1TX0B1 = (MX_CAN_TXB0DB1_X << 8) | MX_CAN_TXB0DB0_X;		// Transmit Data Bytes
			C1TX0B2 = (MX_CAN_TXB0DB3_X << 8) | MX_CAN_TXB0DB2_X;
			C1TX0B3 = (MX_CAN_TXB0DB5_X << 8) | MX_CAN_TXB0DB4_X;
			C1TX0B4 = (MX_CAN_TXB0DB7_X << 8) | MX_CAN_TXB0DB6_X;

			C1TX1CON = TXB1CTRL_VAL;	// Transmit Buffer 1 Control
	#if (MX_CAN_EXID_X == 1)
			C1TX1SID = MX_CAN_TXESID(MX_CAN_TXB1ID_X);
			C1TX1EID = MX_CAN_TXEEID(MX_CAN_TXB1ID_X);
			C1TX1DLC = (MX_CAN_TXEDLC(MX_CAN_TXB1ID_X)) | (MX_CAN_TXB1LEN_X << 3);
	#else
			C1TX1SID = MX_CAN_TXSSID(MX_CAN_TXB1ID_X);	//Transmit Preload S-ID
			C1TX1DLC = MX_CAN_TXB1LEN_X << 3;
	#endif
			C1TX1B1 = (MX_CAN_TXB1DB1_X << 8) | MX_CAN_TXB1DB0_X;		// Transmit Data Bytes
			C1TX1B2 = (MX_CAN_TXB1DB3_X << 8) | MX_CAN_TXB1DB2_X;
			C1TX1B3 = (MX_CAN_TXB1DB5_X << 8) | MX_CAN_TXB1DB4_X;
			C1TX1B4 = (MX_CAN_TXB1DB7_X << 8) | MX_CAN_TXB1DB6_X;

			C1TX2CON = TXB2CTRL_VAL;	// Transmit Buffer 2 Control
	#if (MX_CAN_EXID_X == 1)
			C1TX2SID = MX_CAN_TXESID(MX_CAN_TXB2ID_X);
			C1TX2EID = MX_CAN_TXEEID(MX_CAN_TXB2ID_X);
			C1TX2DLC = (MX_CAN_TXEDLC(MX_CAN_TXB2ID_X)) | (MX_CAN_TXB2LEN_X << 3);
	#else
			C1TX2SID = MX_CAN_TXSSID(MX_CAN_TXB2ID_X);	//Transmit Preload S-ID
			C1TX2DLC = MX_CAN_TXB2LEN_X << 3;
	#endif
			C1TX2B1 = (MX_CAN_TXB2DB1_X << 8) | MX_CAN_TXB2DB0_X;		// Transmit Data Bytes
			C1TX2B2 = (MX_CAN_TXB2DB3_X << 8) | MX_CAN_TXB2DB2_X;
			C1TX2B3 = (MX_CAN_TXB2DB5_X << 8) | MX_CAN_TXB2DB4_X;
			C1TX2B4 = (MX_CAN_TXB2DB7_X << 8) | MX_CAN_TXB2DB6_X;

			// Request normal mode.
			C1CTRLbits.REQOP = REQOP_NORMAL;

			// Wait till desired mode is set.
			while( C1CTRLbits.OPMODE != REQOP_NORMAL );
		#else // __dsPIC30F__
			//
			// Configure ECAN module on dsPIC33E/PIC24
			//
			//
			// Request config mode.
			C1CTRL1bits.REQOP = REQOP_CONFIG;

			// Wait till desired mode is set.
			while( C1CTRL1bits.OPMODE != REQOP_CONFIG );

			//
			// Setup DMA
			//

			// DMA0 for ECAN Xmit
			DMA0CONbits.SIZE = 0x0;
			DMA0CONbits.DIR = 0x1;
			DMA0CONbits.AMODE = 0x2;
			DMA0CONbits.MODE = 0x0;
			DMA0REQ = 70;
			DMA0CNT = 7;
			DMA0PAD = (volatile unsigned int) & C1TXD;
			#if defined (__dsPIC33E__) || defined (__PIC24E__)
				DMA0STAL = (MX_UINT32) &MX_MEMBUF_X;
				DMA0STAH = (MX_UINT32) &MX_MEMBUF_X >> 16;
			#elif defined (__dsPIC33F__) || defined (__PIC24H__)
				DMA0STA = (MX_UINT32) &MX_MEMBUF_X;
			#else
				DMA0STA = __builtin_dmaoffset(&MX_MEMBUF_X);
			#endif
			DMA0CONbits.CHEN = 0x1;

			// DMA1 for ECAN Rcv
			DMA1CONbits.SIZE = 0x0;
			DMA1CONbits.DIR = 0x0;
			DMA1CONbits.AMODE = 0x2;
			DMA1CONbits.MODE = 0x0;
			DMA1REQ = 34;
			DMA1CNT = 7;
			DMA1PAD = (volatile unsigned int) &C1RXD;
			#if defined (__dsPIC33E__) || defined (__PIC24E__)
				DMA1STAL = (MX_UINT32) &MX_MEMBUF_X;
				DMA1STAH = (MX_UINT32) &MX_MEMBUF_X >> 16;
			#elif defined (__dsPIC33F__) || defined (__PIC24H__)
				DMA0STA = (MX_UINT32) &MX_MEMBUF_X;
			#else
				DMA1STA = __builtin_dmaoffset(&MX_MEMBUF_X);
			#endif
			DMA1CONbits.CHEN = 0x1;

			// Setup channel 1:
			C1CTRL1bits.WIN=0x0;
			C1FCTRLbits.DMABS = 3;		// 12 buffers in DMA RAM
			C1FCTRLbits.FSA = 4;		// Start at buffer 4

			// No CANCKS on 33F/24H (http://www.microchip.com/forums/m421868.aspx)
			#if __dsPIC33E__ || __dsPIC24E__ || __dsPIC33F__ || __PIC24H_
				/*************************************************
				// Setup clock:
				// Set CAN clock to Fp (==Fosc/2)
				#if __dsPIC33EP256MU806__  \
					|| __dsPIC33EP256MU810__ \
					|| __dsPIC33EP256MU814__ \
					|| __PIC24EP256GU810__ \
					|| __PIC24EP256GU814__ \
					|| __dsPIC33EP512MU810__ \
					|| __dsPIC33EP512MU814__ \
					|| __dsPIC33EP512GP806__ \
					|| __dsPIC33EP512MC806__
					// (Errata: this bit is reversed)
					C1CTRL1bits.CANCKS = 1;
				#else
					C1CTRL1bits.CANCKS = 0;
				#endif

				WE NEED SOME OTHER WAY OF DOING THE ABOVE ERRATA FIX,
				DOES NOT SEEM TO APPLY IN ALL CASES.
				MAYBE AN OPTION IN THE CAN COMPONENT?
				**************************************************/
					C1CTRL1bits.CANCKS = 0;
			#endif

			// Set baudrate registers
			C1CFG1 = MX_CAN_BAUD1_X;
			C1CFG2 = MX_CAN_BAUD2_X | (MX_CAN_BAUD3_X << 8);

			/* Enable Window to Access Acceptance Filter Registers */
			C1CTRL1bits.WIN=0x1;

			//
			// Set acceptance filters
			//

			/* Select Acceptance Filter Mask 0 for Acceptance Filters 0 & 1 */
			C1FMSKSEL1bits.F0MSK=0x0;
			C1FMSKSEL1bits.F1MSK=0x0;
			/* Acceptance Filter 0 & 1 to use Message Buffer 3 to store message */
			C1BUFPNT1bits.F0BP = 0x3;
			C1BUFPNT1bits.F1BP = 0x3;
			/* Filter 0 & 1 enabled for Identifier match with incoming message */
			C1FEN1bits.FLTEN0=0x1;
			C1FEN1bits.FLTEN1=0x1;

			/* Select Acceptance Filter Mask 1 for Acceptance Filters 2,3,4,5 */
			C1FMSKSEL1bits.F2MSK=0x1;
			C1FMSKSEL1bits.F3MSK=0x1;
			C1FMSKSEL1bits.F4MSK=0x1;
			C1FMSKSEL1bits.F5MSK=0x1;
			/* Acceptance Filter 2,3,4 & 5 to use FIFO to store message */
			C1BUFPNT1bits.F2BP = 0xf;
			C1BUFPNT1bits.F3BP = 0xf;
			C1BUFPNT2bits.F4BP = 0xf;
			C1BUFPNT2bits.F5BP = 0xf;
			/* Filter 2,3,4 & 5 enabled for Identifier match with incoming message */
			C1FEN1bits.FLTEN2=0x1;
			C1FEN1bits.FLTEN3=0x1;
			C1FEN1bits.FLTEN4=0x1;
			C1FEN1bits.FLTEN5=0x1;

			#if (MX_CAN_EXID_X == 1)

				#if (MX_CAN_RXB0CFG_X == 0)		//Reject All

					C1RXM0SIDbits.SID = 0xFFFF;
					C1RXM0SIDbits.EID = 0xFFFF;
					C1RXM0EIDbits.EID = 0xFFFF;
					C1RXF0SIDbits.SID = 0xFFFF;
					C1RXF0SIDbits.EID = 0xFFFF;
					C1RXF0EIDbits.EID = 0xFFFF;

				#endif

				#if (MX_CAN_RXB0CFG_X == 1)		//Use Mask and Filter

					// Configure Acceptance Filter Mask 0 register
					C1RXM0SIDbits.SID = (MX_CAN_RXM0_X >> 18) & 0x7ff;
					C1RXM0SIDbits.EID = (MX_CAN_RXM0_X >> 16) & 0x3;
					C1RXM0EIDbits.EID = (MX_CAN_RXM0_X & 0xffff);

					// Configure Acceptance Filter 0 & 1 to match extended identifier
					C1RXF0SIDbits.SID = (MX_CAN_RXF0_X >> 18) & 0x7ff;
					C1RXF0SIDbits.EID = (MX_CAN_RXF0_X >> 16) & 0x3;
					C1RXF0EIDbits.EID = (MX_CAN_RXF0_X & 0xffff);
					C1RXF1SIDbits.SID = (MX_CAN_RXF1_X >> 18) & 0x7ff;
					C1RXF1SIDbits.EID = (MX_CAN_RXF1_X >> 16) & 0x3;
					C1RXF1EIDbits.EID = (MX_CAN_RXF1_X & 0xffff);

				#endif

				#if (MX_CAN_RXB0CFG_X == 2)		//Accept All

					C1RXM0SIDbits.SID = 0x0000;
					C1RXM0SIDbits.EID = 0x0000;
					C1RXM0EIDbits.EID = 0x0000;
					C1RXF0SIDbits.SID = 0xFFFF;
					C1RXF0SIDbits.EID = 0xFFFF;
					C1RXF0EIDbits.EID = 0xFFFF;

				#endif


				#if (MX_CAN_RXB1CFG_X == 0)		//Reject All

					C1RXM1SIDbits.SID = 0xFFFF;
					C1RXM1SIDbits.EID = 0xFFFF;
					C1RXM1EIDbits.EID = 0xFFFF;
					C1RXF2SIDbits.SID = 0xFFFF;
					C1RXF2SIDbits.EID = 0xFFFF;
					C1RXF2EIDbits.EID = 0xFFFF;
					C1RXF3SIDbits.SID = 0xFFFF;
					C1RXF3SIDbits.EID = 0xFFFF;
					C1RXF3EIDbits.EID = 0xFFFF;
					C1RXF4SIDbits.SID = 0xFFFF;
					C1RXF4SIDbits.EID = 0xFFFF;
					C1RXF4EIDbits.EID = 0xFFFF;
					C1RXF5SIDbits.SID = 0xFFFF;
					C1RXF5SIDbits.EID = 0xFFFF;
					C1RXF5EIDbits.EID = 0xFFFF;

				#endif

				#if (MX_CAN_RXB1CFG_X == 1)		//Use Mask and Filter

					// Configure Acceptance Filter Mask 1 register
					C1RXM1SIDbits.SID = (MX_CAN_RXM1_X >> 18) & 0x7ff;
					C1RXM1SIDbits.EID = (MX_CAN_RXM1_X >> 16) & 0x3;
					C1RXM1EIDbits.EID = (MX_CAN_RXM1_X & 0xffff);
					// Configure Acceptance Filter 2,3,4 & 5 to match extend identifier
					C1RXF2SIDbits.SID = (MX_CAN_RXF2_X >> 18) & 0x7ff;
					C1RXF2SIDbits.EID = (MX_CAN_RXF2_X >> 16) & 0x3;
					C1RXF2EIDbits.EID = (MX_CAN_RXF2_X & 0xffff);
					C1RXF3SIDbits.SID = (MX_CAN_RXF3_X >> 18) & 0x7ff;
					C1RXF3SIDbits.EID = (MX_CAN_RXF3_X >> 16) & 0x3;
					C1RXF3EIDbits.EID = (MX_CAN_RXF3_X & 0xffff);
					C1RXF4SIDbits.SID = (MX_CAN_RXF4_X >> 18) & 0x7ff;
					C1RXF4SIDbits.EID = (MX_CAN_RXF4_X >> 16) & 0x3;
					C1RXF4EIDbits.EID = (MX_CAN_RXF4_X & 0xffff);
					C1RXF5SIDbits.SID = (MX_CAN_RXF5_X >> 18) & 0x7ff;
					C1RXF5SIDbits.EID = (MX_CAN_RXF5_X >> 16) & 0x3;
					C1RXF5EIDbits.EID = (MX_CAN_RXF5_X & 0xffff);

				#endif

				#if (MX_CAN_RXB1CFG_X == 2)		//Accept All

					C1RXM1SIDbits.SID = 0x0000;
					C1RXM1SIDbits.EID = 0x0000;
					C1RXM1EIDbits.EID = 0x0000;
					C1RXF2SIDbits.SID = 0xFFFF;
					C1RXF2SIDbits.EID = 0xFFFF;
					C1RXF2EIDbits.EID = 0xFFFF;
					C1RXF3SIDbits.SID = 0xFFFF;
					C1RXF3SIDbits.EID = 0xFFFF;
					C1RXF3EIDbits.EID = 0xFFFF;
					C1RXF4SIDbits.SID = 0xFFFF;
					C1RXF4SIDbits.EID = 0xFFFF;
					C1RXF4EIDbits.EID = 0xFFFF;
					C1RXF5SIDbits.SID = 0xFFFF;
					C1RXF5SIDbits.EID = 0xFFFF;
					C1RXF5EIDbits.EID = 0xFFFF;

				#endif

				/* Acceptance Filter 0 & 1 to check for Extended Identifier */
				C1RXM0SIDbits.MIDE = 0x0;
				C1RXF0SIDbits.EXIDE= 0x1;
				C1RXF1SIDbits.EXIDE= 0x1;

				/* Acceptance Filter 2,3,4 & 5 to check for Extended Identifier */
				C1RXM1SIDbits.MIDE = 0x0;
				C1RXF2SIDbits.EXIDE= 0x1;
				C1RXF3SIDbits.EXIDE= 0x1;
				C1RXF4SIDbits.EXIDE= 0x1;
				C1RXF5SIDbits.EXIDE= 0x1;

			#else

				#if (MX_CAN_RXB0CFG_X == 0)		//Reject All

					C1RXM0SIDbits.SID = 0xFFFF;
					C1RXF0SIDbits.SID = 0xFFFF;

				#endif

				#if (MX_CAN_RXB0CFG_X == 1)		//Use Mask and Filter

					// Configure Acceptance Filter Mask 0 register
					C1RXM0SIDbits.SID = MX_CAN_RXM0_X;
					// Configure Acceptance Filter 0 & 1 to match standard identifier
					C1RXF0SIDbits.SID = MX_CAN_RXF0_X;
					C1RXF1SIDbits.SID = MX_CAN_RXF1_X;

				#endif

				#if (MX_CAN_RXB0CFG_X == 2)		//Accept All

					C1RXM0SIDbits.SID = 0x0000;
					C1RXF0SIDbits.SID = 0xFFFF;

				#endif


				#if (MX_CAN_RXB1CFG_X == 0)		//Reject All

					C1RXM1SIDbits.SID = 0xFFFF;
					C1RXF2SIDbits.SID = 0xFFFF;
					C1RXF3SIDbits.SID = 0xFFFF;
					C1RXF4SIDbits.SID = 0xFFFF;
					C1RXF5SIDbits.SID = 0xFFFF;

				#endif

				#if (MX_CAN_RXB1CFG_X == 1)		//Use Mask and Filter

					// Configure Acceptance Filter Mask 1 register
					C1RXM1SIDbits.SID = MX_CAN_RXM1_X;
					// Configure Acceptance Filter 2,3,4 & 5 to match standard identifier
					C1RXF2SIDbits.SID = MX_CAN_RXF2_X;
					C1RXF3SIDbits.SID = MX_CAN_RXF3_X;
					C1RXF4SIDbits.SID = MX_CAN_RXF4_X;
					C1RXF5SIDbits.SID = MX_CAN_RXF5_X;

				#endif

				#if (MX_CAN_RXB1CFG_X == 2)		//Accept All

					C1RXM1SIDbits.SID = 0x0000;
					C1RXF2SIDbits.SID = 0xFFFF;
					C1RXF3SIDbits.SID = 0xFFFF;
					C1RXF4SIDbits.SID = 0xFFFF;
					C1RXF5SIDbits.SID = 0xFFFF;

				#endif

				/* Acceptance Filter 0 & 1 to check for Standard Identifier */
				C1RXM0SIDbits.MIDE = 0x1;
				C1RXF0SIDbits.EXIDE= 0x0;
				C1RXF1SIDbits.EXIDE= 0x0;

				/* Acceptance Filter 2,3,4 & 5 to check for Standard Identifier */
				C1RXM1SIDbits.MIDE = 0x1;
				C1RXF2SIDbits.EXIDE= 0x0;
				C1RXF3SIDbits.EXIDE= 0x0;
				C1RXF4SIDbits.EXIDE= 0x0;
				C1RXF5SIDbits.EXIDE= 0x0;
			#endif

			/* Clear Window Bit to Access ECAN Control Registers */
			C1CTRL1bits.WIN=0x0;

			//
			// Preload transmit buffers
			//
			/* Configure Message Buffer 0 for Transmission and assign priority*/
			C1TR01CONbits.TXEN0 = 0x1;
			C1TR01CONbits.TX0PRI = 0x3;

			#if (MX_CAN_EXID_X == 1)
				MX_MEMBUF_X[0][0] = ((MX_CAN_TXB0ID_X >> 16) & 0b0001111111111100) | 0x01;
				MX_MEMBUF_X[0][1] = ((MX_CAN_TXB0ID_X >> 6 ) & 0b0000111111111111);
				MX_MEMBUF_X[0][2] = ((MX_CAN_TXB0ID_X & 0b111111) << 10) | (MX_CAN_TXB0LEN_X & 0xf);
			#else
				MX_MEMBUF_X[0][0] = (MX_CAN_TXB0ID_X << 2) & 0b0001111111111100;
				MX_MEMBUF_X[0][1] = 0x0000;
				MX_MEMBUF_X[0][2] = MX_CAN_TXB0LEN_X & 0xf;
			#endif
			MX_MEMBUF_X[0][3] = (MX_CAN_TXB0DB1_X << 8) | MX_CAN_TXB0DB0_X;		// Transmit Data Bytes
			MX_MEMBUF_X[0][4] = (MX_CAN_TXB0DB3_X << 8) | MX_CAN_TXB0DB2_X;
			MX_MEMBUF_X[0][5] = (MX_CAN_TXB0DB5_X << 8) | MX_CAN_TXB0DB4_X;
			MX_MEMBUF_X[0][6] = (MX_CAN_TXB0DB7_X << 8) | MX_CAN_TXB0DB6_X;

			/* Configure Message Buffer 1 for Transmission and assign priority*/
			C1TR01CONbits.TXEN1 = 0x1;
			C1TR01CONbits.TX1PRI = 0x3;

			#if (MX_CAN_EXID_X == 1)
				MX_MEMBUF_X[1][0] = ((MX_CAN_TXB1ID_X >> 16) & 0b0001111111111100) | 0x01;
				MX_MEMBUF_X[1][1] = ((MX_CAN_TXB1ID_X >> 6 ) & 0b0000111111111111);
				MX_MEMBUF_X[1][2] = ((MX_CAN_TXB1ID_X & 0b111111) << 10) | (MX_CAN_TXB1LEN_X & 0xf);
			#else
				MX_MEMBUF_X[1][0] = (MX_CAN_TXB1ID_X << 2) & 0b0001111111111100;
				MX_MEMBUF_X[1][1] = 0x0000;
				MX_MEMBUF_X[1][2] = MX_CAN_TXB1LEN_X & 0xf;
			#endif
			MX_MEMBUF_X[1][3] = (MX_CAN_TXB1DB1_X << 8) | MX_CAN_TXB1DB0_X;		// Transmit Data Bytes
			MX_MEMBUF_X[1][4] = (MX_CAN_TXB1DB3_X << 8) | MX_CAN_TXB1DB2_X;
			MX_MEMBUF_X[1][5] = (MX_CAN_TXB1DB5_X << 8) | MX_CAN_TXB1DB4_X;
			MX_MEMBUF_X[1][6] = (MX_CAN_TXB1DB7_X << 8) | MX_CAN_TXB1DB6_X;

			/* Configure Message Buffer 3 for Transmission and assign priority*/
			C1TR23CONbits.TXEN2 = 0x1;
			C1TR23CONbits.TX2PRI = 0x3;

			#if (MX_CAN_EXID_X == 1)
				MX_MEMBUF_X[2][0] = ((MX_CAN_TXB2ID_X >> 16) & 0b0001111111111100) | 0x01;
				MX_MEMBUF_X[2][1] = ((MX_CAN_TXB2ID_X >> 6 ) & 0b0000111111111111);
				MX_MEMBUF_X[2][2] = ((MX_CAN_TXB2ID_X & 0b111111) << 10) | (MX_CAN_TXB2LEN_X & 0xf);
			#else
				MX_MEMBUF_X[2][0] = (MX_CAN_TXB2ID_X << 2) & 0b0001111111111100;
				MX_MEMBUF_X[2][1] = 0x0000;
				MX_MEMBUF_X[2][2] = MX_CAN_TXB2LEN_X & 0xf;
			#endif
			MX_MEMBUF_X[2][3] = (MX_CAN_TXB2DB1_X << 8) | MX_CAN_TXB2DB0_X;		// Transmit Data Bytes
			MX_MEMBUF_X[2][4] = (MX_CAN_TXB2DB3_X << 8) | MX_CAN_TXB2DB2_X;
			MX_MEMBUF_X[2][5] = (MX_CAN_TXB2DB5_X << 8) | MX_CAN_TXB2DB4_X;
			MX_MEMBUF_X[2][6] = (MX_CAN_TXB2DB7_X << 8) | MX_CAN_TXB2DB6_X;

			//
			// Switch to Normal Mode Operating Mode
			//
			C1CTRL1bits.REQOP = 0;
			while(C1CTRL1bits.OPMODE != 0);
		#endif

	#endif

	#if (MX_CAN_CHANNEL_X == 2)

		// Remap pins
		#ifdef MX_CAN_2_REMAPPABLE
			MX_CAN_2_TX_RPOR = MX_CAN_2_TX_RPNUM;
			MX_CAN_2_RX_RPINR = MX_CAN_2_RX_RP;
		#endif

		#ifdef __dsPIC30F__	// dsPIC30F Device
			//configure CAN I/O - ds30F??

			C2CTRL = C2CTRL_VAL;

			// Request config mode.
			C2CTRLbits.REQOP = REQOP_CONFIG;

			// Wait till desired mode is set.
			while( C2CTRLbits.OPMODE != REQOP_CONFIG );

			// Now set the baud rate.
			C2CFG2 = MX_CAN_BAUD2_X | (MX_CAN_BAUD3_X << 8);
			C2CFG1 = MX_CAN_BAUD1_X;

			//Setup the CAN comms Masks and Filters
			#if (MX_CAN_EXID_X == 1)

				#if (MX_CAN_RXB0CFG_X == 0)		//Reject All

					C2RXF0SID = 0xFFFF;	// ID Filter 0 - Buffer 0
					C2RXF0EIDL = 0xFFFF;
					C2RXF0EIDH = 0xFFFF;
					C2RXF1SID = 0xFFFF;	// ID Filter 1 - Buffer 0
					C2RXF1EIDL = 0xFFFF;
					C2RXF1EIDH = 0xFFFF;
					C2RXM0SID = 0xFFFF;	// ID Mask 0 - Buffer 0
					C2RXM0EIDL = 0xFFFF;
					C2RXM0EIDH = 0xFFFF;

				#endif

				#if (MX_CAN_RXB0CFG_X == 1)		//Use Mask and Filter

					C2RXF0SID = MX_CAN_RXESID(MX_CAN_RXF0_X);	// ID Filter 0 - Buffer 0
					C2RXF0EIDL = MX_CAN_RXEIDL(MX_CAN_RXF0_X);
					C2RXF0EIDH = MX_CAN_RXEIDH(MX_CAN_RXF0_X);
					C2RXF1SID = MX_CAN_RXESID(MX_CAN_RXF1_X);	// ID Filter 1 - Buffer 0
					C2RXF1EIDL = MX_CAN_RXEIDL(MX_CAN_RXF1_X);
					C2RXF1EIDH = MX_CAN_RXEIDH(MX_CAN_RXF1_X);
					C2RXM0SID = MX_CAN_RXESID(MX_CAN_RXM0_X);	// ID Mask 0 - Buffer 0
					C2RXM0EIDL = MX_CAN_RXEIDL(MX_CAN_RXM0_X);
					C2RXM0EIDH = MX_CAN_RXEIDH(MX_CAN_RXM0_X);

				#endif

				#if (MX_CAN_RXB0CFG_X == 2)		//Accept All

					C2RXF0SID = 0xFFFF;	// ID Filter 0 - Buffer 0
					C2RXF0EIDL = 0xFFFF;
					C2RXF0EIDH = 0xFFFF;
					C2RXF1SID = 0xFFFF;	// ID Filter 1 - Buffer 0
					C2RXF1EIDL = 0xFFFF;
					C2RXF1EIDH = 0xFFFF;
					C2RXM0SID = 0x0000;	// ID Mask 0 - Buffer 0
					C2RXM0EIDL = 0x0000;
					C2RXM0EIDH = 0x0000;

				#endif


				#if (MX_CAN_RXB1CFG_X == 0)		//Reject All

					C2RXF2SID = 0xFFFF;	// ID Filter 2 - Buffer 1
					C2RXF2EIDL = 0xFFFF;
					C2RXF2EIDH = 0xFFFF;
					C2RXF3SID = 0xFFFF;	// ID Filter 3 - Buffer 1
					C2RXF3EIDL = 0xFFFF;
					C2RXF3EIDH = 0xFFFF;
					C2RXF4SID = 0xFFFF;	// ID Filter 4 - Buffer 1
					C2RXF4EIDL = 0xFFFF;
					C2RXF4EIDH = 0xFFFF;
					C2RXF5SID = 0xFFFF;	// ID Filter 5 - Buffer 1
					C2RXF5EIDL = 0xFFFF;
					C2RXF5EIDH = 0xFFFF;
					C2RXM1SID = 0xFFFF;	// ID Mask 1 - Buffer 1
					C2RXM1EIDL = 0xFFFF;
					C2RXM1EIDH = 0xFFFF;

				#endif

				#if (MX_CAN_RXB1CFG_X == 1)		//Use Mask and Filter

					C2RXF2SID = MX_CAN_RXESID(MX_CAN_RXF2_X);	// ID Filter 2 - Buffer 1
					C2RXF2EIDL = MX_CAN_RXEIDL(MX_CAN_RXF2_X);
					C2RXF2EIDH = MX_CAN_RXEIDH(MX_CAN_RXF2_X);
					C2RXF3SID = MX_CAN_RXESID(MX_CAN_RXF3_X);	// ID Filter 3 - Buffer 1
					C2RXF3EIDL = MX_CAN_RXEIDL(MX_CAN_RXF3_X);
					C2RXF3EIDH = MX_CAN_RXEIDH(MX_CAN_RXF3_X);
					C2RXF4SID = MX_CAN_RXESID(MX_CAN_RXF4_X);	// ID Filter 4 - Buffer 1
					C2RXF4EIDL = MX_CAN_RXEIDL(MX_CAN_RXF4_X);
					C2RXF4EIDH = MX_CAN_RXEIDH(MX_CAN_RXF4_X);
					C2RXF5SID = MX_CAN_RXESID(MX_CAN_RXF5_X);	// ID Filter 5 - Buffer 1
					C2RXF5EIDL = MX_CAN_RXEIDL(MX_CAN_RXF5_X);
					C2RXF5EIDH = MX_CAN_RXEIDH(MX_CAN_RXF5_X);
					C2RXM1SID = MX_CAN_RXESID(MX_CAN_RXM1_X);	// ID Mask 1 - Buffer 1
					C2RXM1EIDL = MX_CAN_RXEIDL(MX_CAN_RXM1_X);
					C2RXM1EIDH = MX_CAN_RXEIDH(MX_CAN_RXM1_X);

				#endif

				#if (MX_CAN_RXB1CFG_X == 2)		//Accept All

					C2RXF2SID = 0xFFFF;	// ID Filter 2 - Buffer 1
					C2RXF2EIDL = 0xFFFF;
					C2RXF2EIDH = 0xFFFF;
					C2RXF3SID = 0xFFFF;	// ID Filter 3 - Buffer 1
					C2RXF3EIDL = 0xFFFF;
					C2RXF3EIDH = 0xFFFF;
					C2RXF4SID = 0xFFFF;	// ID Filter 4 - Buffer 1
					C2RXF4EIDL = 0xFFFF;
					C2RXF4EIDH = 0xFFFF;
					C2RXF5SID = 0xFFFF;	// ID Filter 5 - Buffer 1
					C2RXF5EIDL = 0xFFFF;
					C2RXF5EIDH = 0xFFFF;
					C2RXM1SID = 0x0000;	// ID Mask 1 - Buffer 1
					C2RXM1EIDL = 0x0000;
					C2RXM1EIDH = 0x0000;

				#endif

			#else

				#if (MX_CAN_RXB0CFG_X == 0)		//Reject All

					C2RXM0SID = 0xFFFF;	// ID Mask 0 - Buffer 0
					C2RXF0SID = 0xFFFF;	// ID Filter 0 - Buffer 0
					C2RXF1SID = 0xFFFF;	// ID Filter 1 - Buffer 0

				#endif

				#if (MX_CAN_RXB0CFG_X == 1)		//Use Mask and Filter

					C2RXM0SID = MX_CAN_RXSSID(MX_CAN_RXM0_X);	// ID Mask 0 - Buffer 0
					C2RXF0SID = MX_CAN_RXSSID(MX_CAN_RXF0_X);	// ID Filter 0 - Buffer 0
					C2RXF1SID = MX_CAN_RXSSID(MX_CAN_RXF1_X);	// ID Filter 1 - Buffer 0

				#endif

				#if (MX_CAN_RXB0CFG_X == 2)		//Accept All

					C2RXM0SID = 0x0000;	// ID Mask 0 - Buffer 0
					C2RXF0SID = 0xFFFF;	// ID Filter 0 - Buffer 0
					C2RXF1SID = 0xFFFF;	// ID Filter 1 - Buffer 0

				#endif


				#if (MX_CAN_RXB1CFG_X == 0)		//Reject All

					C2RXM1SID = 0xFFFF;	// ID Mask 1 - Buffer 1
					C2RXF2SID = 0xFFFF;	// ID Filter 2 - Buffer 1
					C2RXF3SID = 0xFFFF;	// ID Filter 3 - Buffer 1
					C2RXF4SID = 0xFFFF;	// ID Filter 4 - Buffer 1
					C2RXF5SID = 0xFFFF;	// ID Filter 5 - Buffer 1

				#endif

				#if (MX_CAN_RXB1CFG_X == 1)		//Use Mask and Filter

					C2RXM1SID = MX_CAN_RXSSID(MX_CAN_RXM1_X);	// ID Mask 1 - Buffer 1
					C2RXF2SID = MX_CAN_RXSSID(MX_CAN_RXF2_X);	// ID Filter 2 - Buffer 1
					C2RXF3SID = MX_CAN_RXSSID(MX_CAN_RXF3_X);	// ID Filter 3 - Buffer 1
					C2RXF4SID = MX_CAN_RXSSID(MX_CAN_RXF4_X);	// ID Filter 4 - Buffer 1
					C2RXF5SID = MX_CAN_RXSSID(MX_CAN_RXF5_X);	// ID Filter 5 - Buffer 1

				#endif

				#if (MX_CAN_RXB1CFG_X == 2)		//Accept All

					C2RXM1SID = 0x0000;	// ID Mask 1 - Buffer 1
					C2RXF2SID = 0xFFFF;	// ID Filter 2 - Buffer 1
					C2RXF3SID = 0xFFFF;	// ID Filter 3 - Buffer 1
					C2RXF4SID = 0xFFFF;	// ID Filter 4 - Buffer 1
					C2RXF5SID = 0xFFFF;	// ID Filter 5 - Buffer 1

				#endif

			#endif
			C2RX0CON = RXB0CTRL_VAL;
			C2RX1CON = RXB1CTRL_VAL;

			C2TX0CON = TXB0CTRL_VAL;	// Transmit Buffer 0 Control
	#if (MX_CAN_EXID_X == 1)
			C2TX0SID = MX_CAN_TXESID(MX_CAN_TXB0ID_X);
			C2TX0EID = MX_CAN_TXEEID(MX_CAN_TXB0ID_X);
			C2TX0DLC = (MX_CAN_TXEDLC(MX_CAN_TXB0ID_X)) | (MX_CAN_TXB0LEN_X << 3);
	#else
			C2TX0SID = MX_CAN_TXSSID(MX_CAN_TXB0ID_X);	//Transmit Preload S-ID
			C2TX0DLC = MX_CAN_TXB0LEN_X << 3;
	#endif
			C2TX0B1 = (MX_CAN_TXB0DB1_X << 8) | MX_CAN_TXB0DB0_X;		// Transmit Data Bytes
			C2TX0B2 = (MX_CAN_TXB0DB3_X << 8) | MX_CAN_TXB0DB2_X;
			C2TX0B3 = (MX_CAN_TXB0DB5_X << 8) | MX_CAN_TXB0DB4_X;
			C2TX0B4 = (MX_CAN_TXB0DB7_X << 8) | MX_CAN_TXB0DB6_X;

			C2TX1CON = TXB1CTRL_VAL;	// Transmit Buffer 1 Control
	#if (MX_CAN_EXID_X == 1)
			C2TX1SID = MX_CAN_TXESID(MX_CAN_TXB1ID_X);
			C2TX1EID = MX_CAN_TXEEID(MX_CAN_TXB1ID_X);
			C2TX1DLC = (MX_CAN_TXEDLC(MX_CAN_TXB1ID_X)) | (MX_CAN_TXB1LEN_X << 3);
	#else
			C2TX1SID = MX_CAN_TXSSID(MX_CAN_TXB1ID_X);	//Transmit Preload S-ID
			C2TX1DLC = MX_CAN_TXB1LEN_X << 3;
	#endif
			C2TX1B1 = (MX_CAN_TXB1DB1_X << 8) | MX_CAN_TXB1DB0_X;		// Transmit Data Bytes
			C2TX1B2 = (MX_CAN_TXB1DB3_X << 8) | MX_CAN_TXB1DB2_X;
			C2TX1B3 = (MX_CAN_TXB1DB5_X << 8) | MX_CAN_TXB1DB4_X;
			C2TX1B4 = (MX_CAN_TXB1DB7_X << 8) | MX_CAN_TXB1DB6_X;

			C2TX2CON = TXB2CTRL_VAL;	// Transmit Buffer 2 Control
	#if (MX_CAN_EXID_X == 1)
			C2TX2SID = MX_CAN_TXESID(MX_CAN_TXB2ID_X);
			C2TX2EID = MX_CAN_TXEEID(MX_CAN_TXB2ID_X);
			C2TX2DLC = (MX_CAN_TXEDLC(MX_CAN_TXB2ID_X)) | (MX_CAN_TXB2LEN_X << 3);
	#else
			C2TX2SID = MX_CAN_TXSSID(MX_CAN_TXB2ID_X);	//Transmit Preload S-ID
			C2TX2DLC = MX_CAN_TXB2LEN_X << 3;
	#endif
			C2TX2B1 = (MX_CAN_TXB2DB1_X << 8) | MX_CAN_TXB2DB0_X;		// Transmit Data Bytes
			C2TX2B2 = (MX_CAN_TXB2DB3_X << 8) | MX_CAN_TXB2DB2_X;
			C2TX2B3 = (MX_CAN_TXB2DB5_X << 8) | MX_CAN_TXB2DB4_X;
			C2TX2B4 = (MX_CAN_TXB2DB7_X << 8) | MX_CAN_TXB2DB6_X;

			// Request normal mode.
			C2CTRLbits.REQOP = REQOP_NORMAL;

			// Wait till desired mode is set.
			while( C2CTRLbits.OPMODE != REQOP_NORMAL );
		#else // __dsPIC30F__
			//
			// Configure ECAN module on dsPIC33E/PIC24
			//
			//
			// Request config mode.
			C2CTRL1bits.REQOP = REQOP_CONFIG;

			// Wait till desired mode is set.
			while( C2CTRL1bits.OPMODE != REQOP_CONFIG );

			//
			// Setup DMA
			//

			// DMA2 for ECAN Xmit
			DMA2CONbits.SIZE = 0x0;
			DMA2CONbits.DIR = 0x1;
			DMA2CONbits.AMODE = 0x2;
			DMA2CONbits.MODE = 0x0;
			DMA2REQ = 71;
			DMA2CNT = 7;
			DMA2PAD = (volatile unsigned int) & C2TXD;
			#if defined (__dsPIC33E__) || defined (__PIC24E__) || defined (__dsPIC33F__)
				DMA2STAL = (MX_UINT32) &MX_MEMBUF_X;
				DMA2STAH = (MX_UINT32) &MX_MEMBUF_X >> 16;
			#else
				DMA2STA = __builtin_dmaoffset(&MX_MEMBUF_X);
			#endif
			DMA2CONbits.CHEN = 0x1;

			// DMA3 for ECAN Rcv
			DMA3CONbits.SIZE = 0x0;
			DMA3CONbits.DIR = 0x0;
			DMA3CONbits.AMODE = 0x2;
			DMA3CONbits.MODE = 0x0;
			DMA3REQ = 55;
			DMA3CNT = 7;
			DMA3PAD = (volatile unsigned int) &C2RXD;
			#if defined (__dsPIC33E__) || defined (__PIC24E__) || defined (__dsPIC33F__)
				DMA3STAL = (MX_UINT32) &MX_MEMBUF_X;
				DMA3STAH = (MX_UINT32) &MX_MEMBUF_X >> 16;
			#else
				DMA3STA = __builtin_dmaoffset(&MX_MEMBUF_X);
			#endif
			DMA3CONbits.CHEN = 0x1;

			// Setup channel 1:
			C2CTRL1bits.WIN=0x0;
			C2FCTRLbits.DMABS = 3;		// 12 buffers in DMA RAM
			C2FCTRLbits.FSA = 4;		// Start at buffer 4

			// No CANCKS on 33F/24H (http://www.microchip.com/forums/m421868.aspx)
			#if __dsPIC33E__ || __dsPIC24E__ || __dsPIC33F__ || _PIC24H_
				/*************************************************
				// Setup clock:
				// Set CAN clock to Fp (==Fosc/2)
				#if __dsPIC33EP256MU806__  \
					|| __dsPIC33EP256MU810__ \
					|| __dsPIC33EP256MU814__ \
					|| __PIC24EP256GU810__ \
					|| __PIC24EP256GU814__ \
					|| __dsPIC33EP512MU810__ \
					|| __dsPIC33EP512MU814__ \
					|| __dsPIC33EP512GP806__ \
					|| __dsPIC33EP512MC806__
					// (Errata: this bit is reversed)
					C2CTRL1bits.CANCKS = 1;
				#else
					C2CTRL1bits.CANCKS = 0;
				#endif

				WE NEED SOME OTHER WAY OF DOING THE ABOVE ERRATA FIX,
				DOES NOT SEEM TO APPLY IN ALL CASES.
				MAYBE AN OPTION IN THE CAN COMPONENT?
				**************************************************/
					C2CTRL1bits.CANCKS = 0;
			#endif

			// Set baudrate registers
			C2CFG1 = MX_CAN_BAUD1_X;
			C2CFG2 = MX_CAN_BAUD2_X | (MX_CAN_BAUD3_X << 8);

			/* Enable Window to Access Acceptance Filter Registers */
			C2CTRL1bits.WIN=0x1;

			//
			// Set acceptance filters
			//

			/* Select Acceptance Filter Mask 0 for Acceptance Filters 0 & 1 */
			C2FMSKSEL1bits.F0MSK=0x0;
			C2FMSKSEL1bits.F1MSK=0x0;
			/* Acceptance Filter 0 & 1 to use Message Buffer 3 to store message */
			C2BUFPNT1bits.F0BP = 0x3;
			C2BUFPNT1bits.F1BP = 0x3;
			/* Filter 0 & 1 enabled for Identifier match with incoming message */
			C2FEN1bits.FLTEN0=0x1;
			C2FEN1bits.FLTEN1=0x1;

			/* Select Acceptance Filter Mask 1 for Acceptance Filters 2,3,4,5 */
			C2FMSKSEL1bits.F2MSK=0x1;
			C2FMSKSEL1bits.F3MSK=0x1;
			C2FMSKSEL1bits.F4MSK=0x1;
			C2FMSKSEL1bits.F5MSK=0x1;
			/* Acceptance Filter 2,3,4 & 5 to use FIFO to store message */
			C2BUFPNT1bits.F2BP = 0xf;
			C2BUFPNT1bits.F3BP = 0xf;
			C2BUFPNT2bits.F4BP = 0xf;
			C2BUFPNT2bits.F5BP = 0xf;
			/* Filter 2,3,4 & 5 enabled for Identifier match with incoming message */
			C2FEN1bits.FLTEN2=0x1;
			C2FEN1bits.FLTEN3=0x1;
			C2FEN1bits.FLTEN4=0x1;
			C2FEN1bits.FLTEN5=0x1;

			#if (MX_CAN_EXID_X == 1)

				#if (MX_CAN_RXB0CFG_X == 0)		//Reject All

					C2RXM0SIDbits.SID = 0xFFFF;
					C2RXM0SIDbits.EID = 0xFFFF;
					C2RXM0EIDbits.EID = 0xFFFF;
					C2RXF0SIDbits.SID = 0xFFFF;
					C2RXF0SIDbits.EID = 0xFFFF;
					C2RXF0EIDbits.EID = 0xFFFF;

				#endif

				#if (MX_CAN_RXB0CFG_X == 1)		//Use Mask and Filter

					// Configure Acceptance Filter Mask 0 register
					C2RXM0SIDbits.SID = (MX_CAN_RXM0_X >> 18) & 0x7ff;
					C2RXM0SIDbits.EID = (MX_CAN_RXM0_X >> 16) & 0x3;
					C2RXM0EIDbits.EID = (MX_CAN_RXM0_X & 0xffff);

					// Configure Acceptance Filter 0 & 1 to match extended identifier
					C2RXF0SIDbits.SID = (MX_CAN_RXF0_X >> 18) & 0x7ff;
					C2RXF0SIDbits.EID = (MX_CAN_RXF0_X >> 16) & 0x3;
					C2RXF0EIDbits.EID = (MX_CAN_RXF0_X & 0xffff);
					C2RXF1SIDbits.SID = (MX_CAN_RXF1_X >> 18) & 0x7ff;
					C2RXF1SIDbits.EID = (MX_CAN_RXF1_X >> 16) & 0x3;
					C2RXF1EIDbits.EID = (MX_CAN_RXF1_X & 0xffff);

				#endif

				#if (MX_CAN_RXB0CFG_X == 2)		//Accept All

					C2RXM1SIDbits.SID = 0x0000;
					C2RXM1SIDbits.EID = 0x0000;
					C2RXM1EIDbits.EID = 0x0000;
					C2RXF2SIDbits.SID = 0xFFFF;
					C2RXF2SIDbits.EID = 0xFFFF;
					C2RXF2EIDbits.EID = 0xFFFF;
					C2RXF3SIDbits.SID = 0xFFFF;
					C2RXF3SIDbits.EID = 0xFFFF;
					C2RXF3EIDbits.EID = 0xFFFF;
					C2RXF4SIDbits.SID = 0xFFFF;
					C2RXF4SIDbits.EID = 0xFFFF;
					C2RXF4EIDbits.EID = 0xFFFF;
					C2RXF5SIDbits.SID = 0xFFFF;
					C2RXF5SIDbits.EID = 0xFFFF;
					C2RXF5EIDbits.EID = 0xFFFF;

				#endif


				#if (MX_CAN_RXB1CFG_X == 0)		//Reject All

					C2RXM1SIDbits.SID = 0xFFFF;
					C2RXM1SIDbits.EID = 0xFFFF;
					C2RXM1EIDbits.EID = 0xFFFF;
					C2RXF2SIDbits.SID = 0xFFFF;
					C2RXF2SIDbits.EID = 0xFFFF;
					C2RXF2EIDbits.EID = 0xFFFF;
					C2RXF3SIDbits.SID = 0xFFFF;
					C2RXF3SIDbits.EID = 0xFFFF;
					C2RXF3EIDbits.EID = 0xFFFF;
					C2RXF4SIDbits.SID = 0xFFFF;
					C2RXF4SIDbits.EID = 0xFFFF;
					C2RXF4EIDbits.EID = 0xFFFF;
					C2RXF5SIDbits.SID = 0xFFFF;
					C2RXF5SIDbits.EID = 0xFFFF;
					C2RXF5EIDbits.EID = 0xFFFF;

				#endif

				#if (MX_CAN_RXB1CFG_X == 1)		//Use Mask and Filter

					// Configure Acceptance Filter Mask 1 register
					C2RXM1SIDbits.SID = (MX_CAN_RXM1_X >> 18) & 0x7ff;
					C2RXM1SIDbits.EID = (MX_CAN_RXM1_X >> 16) & 0x3;
					C2RXM1EIDbits.EID = (MX_CAN_RXM1_X & 0xffff);
					// Configure Acceptance Filter 2,3,4 & 5 to match extend identifier
					C2RXF2SIDbits.SID = (MX_CAN_RXF2_X >> 18) & 0x7ff;
					C2RXF2SIDbits.EID = (MX_CAN_RXF2_X >> 16) & 0x3;
					C2RXF2EIDbits.EID = (MX_CAN_RXF2_X & 0xffff);
					C2RXF3SIDbits.SID = (MX_CAN_RXF3_X >> 18) & 0x7ff;
					C2RXF3SIDbits.EID = (MX_CAN_RXF3_X >> 16) & 0x3;
					C2RXF3EIDbits.EID = (MX_CAN_RXF3_X & 0xffff);
					C2RXF4SIDbits.SID = (MX_CAN_RXF4_X >> 18) & 0x7ff;
					C2RXF4SIDbits.EID = (MX_CAN_RXF4_X >> 16) & 0x3;
					C2RXF4EIDbits.EID = (MX_CAN_RXF4_X & 0xffff);
					C2RXF5SIDbits.SID = (MX_CAN_RXF5_X >> 18) & 0x7ff;
					C2RXF5SIDbits.EID = (MX_CAN_RXF5_X >> 16) & 0x3;
					C2RXF5EIDbits.EID = (MX_CAN_RXF5_X & 0xffff);

				#endif

				#if (MX_CAN_RXB1CFG_X == 2)		//Accept All

					C2RXM1SIDbits.SID = 0x0000;
					C2RXM1SIDbits.EID = 0x0000;
					C2RXM1EIDbits.EID = 0x0000;
					C2RXF2SIDbits.SID = 0xFFFF;
					C2RXF2SIDbits.EID = 0xFFFF;
					C2RXF2EIDbits.EID = 0xFFFF;
					C2RXF3SIDbits.SID = 0xFFFF;
					C2RXF3SIDbits.EID = 0xFFFF;
					C2RXF3EIDbits.EID = 0xFFFF;
					C2RXF4SIDbits.SID = 0xFFFF;
					C2RXF4SIDbits.EID = 0xFFFF;
					C2RXF4EIDbits.EID = 0xFFFF;
					C2RXF5SIDbits.SID = 0xFFFF;
					C2RXF5SIDbits.EID = 0xFFFF;
					C2RXF5EIDbits.EID = 0xFFFF;

				#endif

				/* Acceptance Filter 0 & 1 to check for Extended Identifier */
				C2RXM0SIDbits.MIDE = 0x0;
				C2RXF0SIDbits.EXIDE= 0x1;
				C2RXF1SIDbits.EXIDE= 0x1;

				/* Acceptance Filter 2,3,4 & 5 to check for Extended Identifier */
				C2RXM1SIDbits.MIDE = 0x0;
				C2RXF2SIDbits.EXIDE= 0x1;
				C2RXF3SIDbits.EXIDE= 0x1;
				C2RXF4SIDbits.EXIDE= 0x1;
				C2RXF5SIDbits.EXIDE= 0x1;

			#else

				#if (MX_CAN_RXB0CFG_X == 0)		//Reject All

					C2RXM0SIDbits.SID = 0xFFFF;
					C2RXF0SIDbits.SID = 0xFFFF;

				#endif

				#if (MX_CAN_RXB0CFG_X == 1)		//Use Mask and Filter

					// Configure Acceptance Filter Mask 0 register
					C2RXM0SIDbits.SID = MX_CAN_RXM0_X;
					// Configure Acceptance Filter 0 & 1 to match standard identifier
					C2RXF0SIDbits.SID = MX_CAN_RXF0_X;
					C2RXF1SIDbits.SID = MX_CAN_RXF1_X;

				#endif

				#if (MX_CAN_RXB0CFG_X == 2)		//Accept All

					C2RXM0SIDbits.SID = 0x0000;
					C2RXF0SIDbits.SID = 0xFFFF;

				#endif


				#if (MX_CAN_RXB1CFG_X == 0)		//Reject All

					C2RXM1SIDbits.SID = 0xFFFF;
					C2RXF2SIDbits.SID = 0xFFFF;
					C2RXF3SIDbits.SID = 0xFFFF;
					C2RXF4SIDbits.SID = 0xFFFF;
					C2RXF5SIDbits.SID = 0xFFFF;

				#endif

				#if (MX_CAN_RXB1CFG_X == 1)		//Use Mask and Filter

					// Configure Acceptance Filter Mask 1 register
					C2RXM1SIDbits.SID = MX_CAN_RXM1_X;
					// Configure Acceptance Filter 2,3,4 & 5 to match standard identifier
					C2RXF2SIDbits.SID = MX_CAN_RXF2_X;
					C2RXF3SIDbits.SID = MX_CAN_RXF3_X;
					C2RXF4SIDbits.SID = MX_CAN_RXF4_X;
					C2RXF5SIDbits.SID = MX_CAN_RXF5_X;

				#endif

				#if (MX_CAN_RXB1CFG_X == 2)		//Accept All

					C2RXM1SIDbits.SID = 0x0000;
					C2RXF2SIDbits.SID = 0xFFFF;
					C2RXF3SIDbits.SID = 0xFFFF;
					C2RXF4SIDbits.SID = 0xFFFF;
					C2RXF5SIDbits.SID = 0xFFFF;

				#endif

				/* Acceptance Filter 0 & 1 to check for Standard Identifier */
				C2RXM0SIDbits.MIDE = 0x1;
				C2RXF0SIDbits.EXIDE= 0x0;
				C2RXF1SIDbits.EXIDE= 0x0;

				/* Acceptance Filter 2,3,4 & 5 to check for Standard Identifier */
				C2RXM1SIDbits.MIDE = 0x1;
				C2RXF2SIDbits.EXIDE= 0x0;
				C2RXF3SIDbits.EXIDE= 0x0;
				C2RXF4SIDbits.EXIDE= 0x0;
				C2RXF5SIDbits.EXIDE= 0x0;
			#endif

			/* Clear Window Bit to Access ECAN Control Registers */
			C2CTRL1bits.WIN=0x0;

			//
			// Preload transmit buffers
			//
			/* Configure Message Buffer 0 for Transmission and assign priority*/
			C2TR01CONbits.TXEN0 = 0x1;
			C2TR01CONbits.TX0PRI = 0x3;

			#if (MX_CAN_EXID_X == 1)
				MX_MEMBUF_X[0][0] = ((MX_CAN_TXB0ID_X >> 16) & 0b0001111111111100) | 0x01;
				MX_MEMBUF_X[0][1] = ((MX_CAN_TXB0ID_X >> 6 ) & 0b0000111111111111);
				MX_MEMBUF_X[0][2] = ((MX_CAN_TXB0ID_X & 0b111111) << 10) | (MX_CAN_TXB0LEN_X & 0xf);
			#else
				MX_MEMBUF_X[0][0] = (MX_CAN_TXB0ID_X << 2) & 0b0001111111111100;
				MX_MEMBUF_X[0][1] = 0x0000;
				MX_MEMBUF_X[0][2] = MX_CAN_TXB0LEN_X & 0xf;
			#endif
			MX_MEMBUF_X[0][3] = (MX_CAN_TXB0DB1_X << 8) | MX_CAN_TXB0DB0_X;		// Transmit Data Bytes
			MX_MEMBUF_X[0][4] = (MX_CAN_TXB0DB3_X << 8) | MX_CAN_TXB0DB2_X;
			MX_MEMBUF_X[0][5] = (MX_CAN_TXB0DB5_X << 8) | MX_CAN_TXB0DB4_X;
			MX_MEMBUF_X[0][6] = (MX_CAN_TXB0DB7_X << 8) | MX_CAN_TXB0DB6_X;

			/* Configure Message Buffer 1 for Transmission and assign priority*/
			C2TR01CONbits.TXEN1 = 0x1;
			C2TR01CONbits.TX1PRI = 0x3;

			#if (MX_CAN_EXID_X == 1)
				MX_MEMBUF_X[1][0] = ((MX_CAN_TXB1ID_X >> 16) & 0b0001111111111100) | 0x01;
				MX_MEMBUF_X[1][1] = ((MX_CAN_TXB1ID_X >> 6 ) & 0b0000111111111111);
				MX_MEMBUF_X[1][2] = ((MX_CAN_TXB1ID_X & 0b111111) << 10) | (MX_CAN_TXB1LEN_X & 0xf);
			#else
				MX_MEMBUF_X[1][0] = (MX_CAN_TXB1ID_X << 2) & 0b0001111111111100;
				MX_MEMBUF_X[1][1] = 0x0000;
				MX_MEMBUF_X[1][2] = MX_CAN_TXB1LEN_X & 0xf;
			#endif
			MX_MEMBUF_X[1][3] = (MX_CAN_TXB1DB1_X << 8) | MX_CAN_TXB1DB0_X;		// Transmit Data Bytes
			MX_MEMBUF_X[1][4] = (MX_CAN_TXB1DB3_X << 8) | MX_CAN_TXB1DB2_X;
			MX_MEMBUF_X[1][5] = (MX_CAN_TXB1DB5_X << 8) | MX_CAN_TXB1DB4_X;
			MX_MEMBUF_X[1][6] = (MX_CAN_TXB1DB7_X << 8) | MX_CAN_TXB1DB6_X;

			/* Configure Message Buffer 3 for Transmission and assign priority*/
			C2TR23CONbits.TXEN2 = 0x1;
			C2TR23CONbits.TX2PRI = 0x3;

			#if (MX_CAN_EXID_X == 1)
				MX_MEMBUF_X[2][0] = ((MX_CAN_TXB2ID_X >> 16) & 0b0001111111111100) | 0x01;
				MX_MEMBUF_X[2][1] = ((MX_CAN_TXB2ID_X >> 6 ) & 0b0000111111111111);
				MX_MEMBUF_X[2][2] = ((MX_CAN_TXB2ID_X & 0b111111) << 10) | (MX_CAN_TXB2LEN_X & 0xf);
			#else
				MX_MEMBUF_X[2][0] = (MX_CAN_TXB2ID_X << 2) & 0b0001111111111100;
				MX_MEMBUF_X[2][1] = 0x0000;
				MX_MEMBUF_X[2][2] = MX_CAN_TXB2LEN_X & 0xf;
			#endif
			MX_MEMBUF_X[2][3] = (MX_CAN_TXB2DB1_X << 8) | MX_CAN_TXB2DB0_X;		// Transmit Data Bytes
			MX_MEMBUF_X[2][4] = (MX_CAN_TXB2DB3_X << 8) | MX_CAN_TXB2DB2_X;
			MX_MEMBUF_X[2][5] = (MX_CAN_TXB2DB5_X << 8) | MX_CAN_TXB2DB4_X;
			MX_MEMBUF_X[2][6] = (MX_CAN_TXB2DB7_X << 8) | MX_CAN_TXB2DB6_X;

			//
			// Switch to Normal Mode Operating Mode
			//
			C2CTRL1bits.REQOP = 0;
			while(C2CTRL1bits.OPMODE != 0);
		#endif


   	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_Uninit_, (void))
{
	#ifdef __dsPIC30F__
		#if (MX_CAN_CHANNEL_X == 1)
			C1CTRL = 0x00;
		#endif

		#if (MX_CAN_CHANNEL_X == 2)
			C2CTRL = 0x00;
		#endif
	#else
		#if (MX_CAN_CHANNEL_X == 1)
			C1CTRL1bits.CANCAP = 0;
		#endif

		#if (MX_CAN_CHANNEL_X == 2)
			C2CTRL1bits.CANCAP = 0;
		#endif
	#endif

}

CALFUNCTION(void, FC_CAL_Internal_CAN_SendBuffer_, (MX_UINT8 buffer))
{
	unsigned int cantimeout = 0xFFFF;

	#ifdef __dsPIC30F__
		#if (MX_CAN_CHANNEL_X == 1)
			switch (buffer)
			{
				case 0:
					C1TX0CONbits.TXREQ = 1;							//Set Message Transmission Flag
					while (C1TX0CONbits.TXREQ && cantimeout)			//Wait for message to send
						cantimeout = cantimeout - 1;
					break;
				case 1:
					C1TX1CONbits.TXREQ = 1;
					while (C1TX1CONbits.TXREQ && cantimeout)
						cantimeout = cantimeout - 1;
					break;
				case 2:
					C1TX2CONbits.TXREQ = 1;
					while (C1TX2CONbits.TXREQ && cantimeout)
						cantimeout = cantimeout - 1;
					break;
			}
		#endif

		#if (MX_CAN_CHANNEL_X == 2)
			switch (buffer)
			{
				case 0:
					C2TX0CONbits.TXREQ = 1;							//Set Message Transmission Flag
					while (C2TX0CONbits.TXREQ && cantimeout)			//Wait for message to send
						cantimeout = cantimeout - 1;
					break;
				case 1:
					C2TX1CONbits.TXREQ = 1;
					while (C2TX1CONbits.TXREQ && cantimeout)
						cantimeout = cantimeout - 1;
					break;
				case 2:
					C2TX2CONbits.TXREQ = 1;
					while (C2TX2CONbits.TXREQ && cantimeout)
						cantimeout = cantimeout - 1;
					break;
			}
		#endif
	#else // __dsPIC30F__
		#if (MX_CAN_CHANNEL_X == 1)
			switch (buffer)
			{
				case 0:
					C1TR01CONbits.TXREQ0 = 1;
					while (C1TR01CONbits.TXREQ0 && cantimeout)			//Wait for message to send
						cantimeout = cantimeout - 1;
					break;
				case 1:
					C1TR01CONbits.TXREQ1 = 1;
					while (C1TR01CONbits.TXREQ1 && cantimeout)			//Wait for message to send
						cantimeout = cantimeout - 1;
					break;
				case 2:
					C1TR23CONbits.TXREQ2= 1;
					while (C1TR23CONbits.TXREQ2 && cantimeout)			//Wait for message to send
						cantimeout = cantimeout - 1;
					break;
			}
		#endif

		#if (MX_CAN_CHANNEL_X == 2)
			switch (buffer)
			{
				case 0:
					C2TR01CONbits.TXREQ0= 1;
					while (C2TR01CONbits.TXREQ0 && cantimeout)			//Wait for message to send
						cantimeout = cantimeout - 1;
					break;
				case 1:
					C2TR01CONbits.TXREQ1 = 1;
					while (C2TR01CONbits.TXREQ1 && cantimeout)			//Wait for message to send
						cantimeout = cantimeout - 1;
					break;
				case 2:
					C2TR23CONbits.TXREQ2= 1;
					while (C2TR23CONbits.TXREQ2 && cantimeout)			//Wait for message to send
						cantimeout = cantimeout - 1;
					break;
			}
		#endif
	#endif


}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_CheckRx_, (MX_UINT8 buffer))
{
	#if (MX_CAN_CHANNEL_X == 1)
		#ifdef __dsPIC30F__
			if (buffer == 0)
			{
				if (C1RX0CONbits.RXFUL)
				{
					MX_CAN_MSG_DLC_X = C1RX0DLC & 0x000F;	// Retrieve message length.
					MX_CAN_MSG_ID_X[0] = C1RX0SID >> 5;
					MX_CAN_MSG_ID_X[1] = C1RX0SID << 3;

					if(MX_CAN_MSG_DLC_X > 0)
					{
						MX_CAN_MSG_DATA_X[0] = C1RX0B1 & 0xFF;
						if(MX_CAN_MSG_DLC_X > 1)
						{
							MX_CAN_MSG_DATA_X[1] = C1RX0B1 >> 8;
							if(MX_CAN_MSG_DLC_X > 2)
							{
								MX_CAN_MSG_DATA_X[2] = C1RX0B2 & 0xFF;
								if(MX_CAN_MSG_DLC_X > 3)
								{
									MX_CAN_MSG_DATA_X[3] = C1RX0B2 >> 8;
									if(MX_CAN_MSG_DLC_X > 4)
									{
										MX_CAN_MSG_DATA_X[4] = C1RX0B3 & 0xFF;
										if(MX_CAN_MSG_DLC_X > 5)
										{
											MX_CAN_MSG_DATA_X[5] = C1RX0B3 >> 8;
											if(MX_CAN_MSG_DLC_X > 6)
											{
												MX_CAN_MSG_DATA_X[6] = C1RX0B4 & 0xFF;
												if(MX_CAN_MSG_DLC_X > 7)
												{
													MX_CAN_MSG_DATA_X[7] = C1RX0B4 >> 8;
												}
											}
										}
									}
								}
							}
						}
					}
					C1RX0CONbits.RXFUL = 0;
				}
				else
					return 0;
			}
			else
			{
				if (C1RX1CONbits.RXFUL)
				{
					MX_CAN_MSG_DLC_X = C1RX1DLC & 0x000F;	// Retrieve message length.
					MX_CAN_MSG_ID_X[0] = C1RX1SID >> 5;
					MX_CAN_MSG_ID_X[1] = C1RX1SID << 3;

					if(MX_CAN_MSG_DLC_X > 0)
					{
						MX_CAN_MSG_DATA_X[0] = C1RX1B1 & 0xFF;
						if(MX_CAN_MSG_DLC_X > 1)
						{
							MX_CAN_MSG_DATA_X[1] = C1RX1B1 >> 8;
							if(MX_CAN_MSG_DLC_X > 2)
							{
								MX_CAN_MSG_DATA_X[2] = C1RX1B2 & 0xFF;
								if(MX_CAN_MSG_DLC_X > 3)
								{
									MX_CAN_MSG_DATA_X[3] = C1RX1B2 >> 8;
									if(MX_CAN_MSG_DLC_X > 4)
									{
										MX_CAN_MSG_DATA_X[4] = C1RX1B3 & 0xFF;
										if(MX_CAN_MSG_DLC_X > 5)
										{
											MX_CAN_MSG_DATA_X[5] = C1RX1B3 >> 8;
											if(MX_CAN_MSG_DLC_X > 6)
											{
												MX_CAN_MSG_DATA_X[6] = C1RX1B4 & 0xFF;
												if(MX_CAN_MSG_DLC_X > 7)
												{
													MX_CAN_MSG_DATA_X[7] = C1RX1B4 >> 8;
												}
											}
										}
									}
								}
							}
						}
					}
					C1RX1CONbits.RXFUL = 0;
				}
				else
					return 0;
			}
			return 1;
		#else // __dsPIC30F__
			C1CTRL1bits.WIN = 0;

			// get ID of next FIFO buffer
			unsigned char id;
			if (buffer == 0)
			{
				id = 3;
			} else {
				id = C1FIFObits.FNRB;
			}

			unsigned int mask = 0x01 << id;
			if (C1RXFUL1 & mask) {
				#if defined (FCV_DMA_BASE) && defined(__dsPIC33E__)
				int tmpdsr = DSRPAG;
				DSRPAG = __builtin_edspage (MX_MEMBUF_X);
				#endif

				MX_CAN_MSG_DLC_X = MX_MEMBUF_X[id][2] & 0x000F;	// Retrieve message length.
				// Message IDE flag
				if (MX_MEMBUF_X[id][0] & 1)
					// Extended ID
					MX_CAN_MSG_ID_X = (((MX_UINT32)MX_MEMBUF_X[id][0] & 0x1FFC) << 16)|(((MX_UINT32)MX_MEMBUF_X[id][1] & 0x0FFF) << 6)|((MX_MEMBUF_X[id][2] & 0xFC00) >> 10);
				else
					// Standard ID
					MX_CAN_MSG_ID_X = (MX_MEMBUF_X[id][0] >> 2) & 0b0000011111111111;

				// Always copy all data
				MX_CAN_MSG_DATA_X[0] = MX_MEMBUF_X[id][3] & 0xff;
				MX_CAN_MSG_DATA_X[1] = (MX_MEMBUF_X[id][3] >> 8) & 0xff;
				MX_CAN_MSG_DATA_X[2] = MX_MEMBUF_X[id][4] & 0xff;
				MX_CAN_MSG_DATA_X[3] = (MX_MEMBUF_X[id][4] >> 8) & 0xff;
				MX_CAN_MSG_DATA_X[4] = MX_MEMBUF_X[id][5] & 0xff;
				MX_CAN_MSG_DATA_X[5] = (MX_MEMBUF_X[id][5] >> 8) & 0xff;
				MX_CAN_MSG_DATA_X[6] = MX_MEMBUF_X[id][6] & 0xff;
				MX_CAN_MSG_DATA_X[7] = (MX_MEMBUF_X[id][6] >> 8) & 0xff;

				#if defined (FCV_DMA_BASE) && defined(__dsPIC33E__)
				DSRPAG = tmpdsr;
				#endif
				// Empty buffer
				C1RXFUL1 &= ~ (mask);
			}
			else
				return 0;

			return 1;
		#endif // __dsPIC30F__
	#endif
	#if (MX_CAN_CHANNEL_X == 2)
		#ifdef __dsPIC30F__
			if (buffer == 0)
			{
				if (C2RX0CONbits.RXFUL)
				{
					MX_CAN_MSG_DLC_X = C2RX0DLC & 0x000F;	// Retrieve message length.
					MX_CAN_MSG_ID_X[0] = C2RX0SID >> 5;
					MX_CAN_MSG_ID_X[1] = C2RX0SID << 3;

					if(MX_CAN_MSG_DLC_X > 0)
					{
						MX_CAN_MSG_DATA_X[0] = C2RX0B1 & 0xFF;
						if(MX_CAN_MSG_DLC_X > 1)
						{
							MX_CAN_MSG_DATA_X[1] = C2RX0B1 >> 8;
							if(MX_CAN_MSG_DLC_X > 2)
							{
								MX_CAN_MSG_DATA_X[2] = C2RX0B2 & 0xFF;
								if(MX_CAN_MSG_DLC_X > 3)
								{
									MX_CAN_MSG_DATA_X[3] = C2RX0B2 >> 8;
									if(MX_CAN_MSG_DLC_X > 4)
									{
										MX_CAN_MSG_DATA_X[4] = C2RX0B3 & 0xFF;
										if(MX_CAN_MSG_DLC_X > 5)
										{
											MX_CAN_MSG_DATA_X[5] = C2RX0B3 >> 8;
											if(MX_CAN_MSG_DLC_X > 6)
											{
												MX_CAN_MSG_DATA_X[6] = C2RX0B4 & 0xFF;
												if(MX_CAN_MSG_DLC_X > 7)
												{
													MX_CAN_MSG_DATA_X[7] = C2RX0B4 >> 8;
												}
											}
										}
									}
								}
							}
						}
					}
					C2RX0CONbits.RXFUL = 0;
				}
				else
					return 0;
			}
			else
			{
				if (C2RX1CONbits.RXFUL)
				{
					MX_CAN_MSG_DLC_X = C2RX1DLC & 0x000F;	// Retrieve message length.
					MX_CAN_MSG_ID_X[0] = C2RX1SID >> 5;
					MX_CAN_MSG_ID_X[1] = C2RX1SID << 3;

					if(MX_CAN_MSG_DLC_X > 0)
					{
						MX_CAN_MSG_DATA_X[0] = C2RX1B1 & 0xFF;
						if(MX_CAN_MSG_DLC_X > 1)
						{
							MX_CAN_MSG_DATA_X[1] = C2RX1B1 >> 8;
							if(MX_CAN_MSG_DLC_X > 2)
							{
								MX_CAN_MSG_DATA_X[2] = C2RX1B2 & 0xFF;
								if(MX_CAN_MSG_DLC_X > 3)
								{
									MX_CAN_MSG_DATA_X[3] = C2RX1B2 >> 8;
									if(MX_CAN_MSG_DLC_X > 4)
									{
										MX_CAN_MSG_DATA_X[4] = C2RX1B3 & 0xFF;
										if(MX_CAN_MSG_DLC_X > 5)
										{
											MX_CAN_MSG_DATA_X[5] = C2RX1B3 >> 8;
											if(MX_CAN_MSG_DLC_X > 6)
											{
												MX_CAN_MSG_DATA_X[6] = C2RX1B4 & 0xFF;
												if(MX_CAN_MSG_DLC_X > 7)
												{
													MX_CAN_MSG_DATA_X[7] = C2RX1B4 >> 8;
												}
											}
										}
									}
								}
							}
						}
					}
					C2RX1CONbits.RXFUL = 0;
				}
				else
					return 0;
			}
			return 1;
		#else // __dsPIC30F__
			C2CTRL1bits.WIN = 0;

			// get ID of next FIFO buffer
			unsigned char id;
			if (buffer == 0)
			{
				id = 3;
			} else {
				id = C2FIFObits.FNRB;
			}

			unsigned int mask = 0x01 << id;
			if (C2RXFUL1 & mask) {
				#if defined (FCV_DMA_BASE) && defined(__dsPIC33E__)
				int tmpdsr = DSRPAG;
				DSRPAG = __builtin_edspage (MX_MEMBUF_X);
				#endif

				MX_CAN_MSG_DLC_X = MX_MEMBUF_X[id][2] & 0x000F;	// Retrieve message length.
				// Message IDE flag
				if (MX_MEMBUF_X[id][0] & 1)
					// Extended ID
					MX_CAN_MSG_ID_X = (((MX_UINT32)MX_MEMBUF_X[id][0] & 0x1FFC) << 16)|(((MX_UINT32)MX_MEMBUF_X[id][1] & 0x0FFF) << 6)|((MX_MEMBUF_X[id][2] & 0xFC00) >> 10);
				else
					// Standard ID
					MX_CAN_MSG_ID_X = (MX_MEMBUF_X[id][0] >> 2) & 0b0000011111111111;

				// Always copy all data
				MX_CAN_MSG_DATA_X[0] = MX_MEMBUF_X[id][3] & 0xff;
				MX_CAN_MSG_DATA_X[1] = (MX_MEMBUF_X[id][3] >> 8) & 0xff;
				MX_CAN_MSG_DATA_X[2] = MX_MEMBUF_X[id][4] & 0xff;
				MX_CAN_MSG_DATA_X[3] = (MX_MEMBUF_X[id][4] >> 8) & 0xff;
				MX_CAN_MSG_DATA_X[4] = MX_MEMBUF_X[id][5] & 0xff;
				MX_CAN_MSG_DATA_X[5] = (MX_MEMBUF_X[id][5] >> 8) & 0xff;
				MX_CAN_MSG_DATA_X[6] = MX_MEMBUF_X[id][6] & 0xff;
				MX_CAN_MSG_DATA_X[7] = (MX_MEMBUF_X[id][6] >> 8) & 0xff;

				#if defined (FCV_DMA_BASE) && defined(__dsPIC33E__)
				DSRPAG = tmpdsr;
				#endif
				// Empty buffer
				C2RXFUL1 &= ~ (mask);
			}
			else
				return 0;

			return 1;
		#endif // __dsPIC30F__
  	#endif

  return 0;
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxData_, (MX_UINT8 buffer, MX_UINT8 data_cnt, MX_UINT8 d0, MX_UINT8 d1, MX_UINT8 d2, MX_UINT8 d3, MX_UINT8 d4, MX_UINT8 d5, MX_UINT8 d6, MX_UINT8 d7))
{
	#ifdef __dsPIC30F__
		#if (MX_CAN_CHANNEL_X == 1)
			switch(buffer)
			{
				case 0:
					C1TX0DLC = data_cnt << 3;		// TX Buffer 0
					if (data_cnt > 0)
					{
					   C1TX0B1 = d0;
					   if (data_cnt > 1)
					   {
						   C1TX0B1 = C1TX0B1 | (d1 << 8);
						   if (data_cnt > 2)
						   {
							   C1TX0B2 = d2;
							   if (data_cnt > 3)
							   {
								   C1TX0B2 = C1TX0B2 | (d3 << 8);
								   if (data_cnt > 4)
								   {
									   C1TX0B3 = d4;
									   if (data_cnt > 5)
									   {
										   C1TX0B3 = C1TX0B3 | (d5 << 8);
										   if (data_cnt > 6)
										   {
											   C1TX0B4 = d6;
											   if (data_cnt > 7)
											   {
													C1TX0B4 = C1TX0B4 | (d7 << 8);
											   }
										   }
									   }
								   }
							   }
						   }
					   }
					}
					break;
				case 1:
					C1TX1DLC = data_cnt << 3;		// TX Buffer 1
					if (data_cnt > 0)
					{
					   C1TX1B1 = d0;
					   if (data_cnt > 1)
					   {
						   C1TX1B1 = C1TX1B1 | (d1 << 8);
						   if (data_cnt > 2)
						   {
							   C1TX1B2 = d2;
							   if (data_cnt > 3)
							   {
								   C1TX1B2 = C1TX1B2 | (d3 << 8);
								   if (data_cnt > 4)
								   {
									   C1TX1B3 = d4;
									   if (data_cnt > 5)
									   {
										   C1TX1B3 = C1TX1B3 | (d5 << 8);
										   if (data_cnt > 6)
										   {
											   C1TX1B4 = d6;
											   if (data_cnt > 7)
											   {
													C1TX1B4 = C1TX1B4 | (d7 << 8);
											   }
										   }
									   }
								   }
							   }
						   }
					   }
					}
					break;
				case 2:
					C1TX2DLC = data_cnt << 3;		// TX Buffer 0
					if (data_cnt > 0)
					{
					   C1TX2B1 = d0;
					   if (data_cnt > 1)
					   {
						   C1TX2B1 = C1TX2B1 | (d1 << 8);
						   if (data_cnt > 2)
						   {
							   C1TX2B2 = d2;
							   if (data_cnt > 3)
							   {
								   C1TX2B2 = C1TX2B2 | (d3 << 8);
								   if (data_cnt > 4)
								   {
									   C1TX2B3 = d4;
									   if (data_cnt > 5)
									   {
										   C1TX2B3 = C1TX2B3 | (d5 << 8);
										   if (data_cnt > 6)
										   {
											   C1TX2B4 = d6;
											   if (data_cnt > 7)
											   {
													C1TX2B4 = C1TX2B4 | (d7 << 8);
											   }
										   }
									   }
								   }
							   }
						   }
					   }
					}
					break;
			}
		#endif

		#if (MX_CAN_CHANNEL_X == 2)
			switch(buffer)
			{
				case 0:
					C2TX0DLC = data_cnt << 3;		// TX Buffer 0
					if (data_cnt > 0)
					{
					   C2TX0B1 = d0;
					   if (data_cnt > 1)
					   {
						   C2TX0B1 = C2TX0B1 | (d1 << 8);
						   if (data_cnt > 2)
						   {
							   C2TX0B2 = d2;
							   if (data_cnt > 3)
							   {
								   C2TX0B2 = C2TX0B2 | (d3 << 8);
								   if (data_cnt > 4)
								   {
									   C2TX0B3 = d4;
									   if (data_cnt > 5)
									   {
										   C2TX0B3 = C2TX0B3 | (d5 << 8);
										   if (data_cnt > 6)
										   {
											   C2TX0B4 = d6;
											   if (data_cnt > 7)
											   {
													C2TX0B4 = C2TX0B4 | (d7 << 8);
											   }
										   }
									   }
								   }
							   }
						   }
					   }
					}
					break;
				case 1:
					C2TX1DLC = data_cnt << 3;		// TX Buffer 1
					if (data_cnt > 0)
					{
					   C2TX1B1 = d0;
					   if (data_cnt > 1)
					   {
						   C2TX1B1 = C2TX1B1 | (d1 << 8);
						   if (data_cnt > 2)
						   {
							   C2TX1B2 = d2;
							   if (data_cnt > 3)
							   {
								   C2TX1B2 = C2TX1B2 | (d3 << 8);
								   if (data_cnt > 4)
								   {
									   C2TX1B3 = d4;
									   if (data_cnt > 5)
									   {
										   C2TX1B3 = C2TX1B3 | (d5 << 8);
										   if (data_cnt > 6)
										   {
											   C2TX1B4 = d6;
											   if (data_cnt > 7)
											   {
													C2TX1B4 = C2TX1B4 | (d7 << 8);
											   }
										   }
									   }
								   }
							   }
						   }
					   }
					}
					break;
				case 2:
					C2TX2DLC = data_cnt << 3;		// TX Buffer 0
					if (data_cnt > 0)
					{
					   C2TX2B1 = d0;
					   if (data_cnt > 1)
					   {
						   C2TX2B1 = C2TX2B1 | (d1 << 8);
						   if (data_cnt > 2)
						   {
							   C2TX2B2 = d2;
							   if (data_cnt > 3)
							   {
								   C2TX2B2 = C2TX2B2 | (d3 << 8);
								   if (data_cnt > 4)
								   {
									   C2TX2B3 = d4;
									   if (data_cnt > 5)
									   {
										   C2TX2B3 = C2TX2B3 | (d5 << 8);
										   if (data_cnt > 6)
										   {
											   C2TX2B4 = d6;
											   if (data_cnt > 7)
											   {
													C2TX2B4 = C2TX2B4 | (d7 << 8);
											   }
										   }
									   }
								   }
							   }
						   }
					   }
					}
					break;
			}
		#endif
	#else // __dsPIC30F__
		if (buffer < 3) {
			#if defined (FCV_DMA_BASE) && defined(__dsPIC33E__)
			int tmpdsr = DSRPAG;
			DSRPAG = __builtin_edspage (MX_MEMBUF_X);
			#endif

			MX_MEMBUF_X[buffer][2] = (MX_MEMBUF_X[buffer][2] & 0xfff0) | (data_cnt & 0xf);
			MX_MEMBUF_X[buffer][3] = (d1 << 8) | d0;		// Transmit Data Bytes
			MX_MEMBUF_X[buffer][4] = (d3 << 8) | d2;
			MX_MEMBUF_X[buffer][5] = (d5 << 8) | d4;
			MX_MEMBUF_X[buffer][6] = (d7 << 8) | d6;

			#if defined (FCV_DMA_BASE) && defined(__dsPIC33E__)
			DSRPAG = tmpdsr;
			#endif
		}
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdentStd_, (MX_UINT8 buffer, MX_UINT8 hi, MX_UINT8 lo))
{
	#ifdef __dsPIC30F__
		#if (MX_CAN_CHANNEL_X == 1)
			switch(buffer)
			{
				case 0:
					C1TX0SID = ((hi << 5) | (lo >> 3)) & 0x00FF;	//Transmit Buffer 0 S-ID
					C1TX0SID = C1TX0SID | ((hi << 8) & 0xFF00);
					break;
				case 1:
					C1TX1SID = ((hi << 5) | (lo >> 3)) & 0x00FF;	//Transmit Buffer 1 S-ID
					C1TX1SID = C1TX1SID | ((hi << 8) & 0xFF00);
					break;
				case 2:
					C1TX2SID = ((hi << 5) | (lo >> 3)) & 0x00FF;	//Transmit Buffer 2 S-ID
					C1TX2SID = C1TX2SID | ((hi << 8) & 0xFF00);
					break;
			}
		#endif
		#if (MX_CAN_CHANNEL_X == 2)
			switch(buffer)
			{
				case 0:
					C2TX0SID = ((hi << 5) | (lo >> 3)) & 0x00FF;	//Transmit Buffer 0 S-ID
					C2TX0SID = C2TX0SID | ((hi << 8) & 0xFF00);
					break;
				case 1:
					C2TX1SID = ((hi << 5) | (lo >> 3)) & 0x00FF;	//Transmit Buffer 1 S-ID
					C2TX1SID = C2TX1SID | ((hi << 8) & 0xFF00);
					break;
				case 2:
					C2TX2SID = ((hi << 5) | (lo >> 3)) & 0x00FF;	//Transmit Buffer 2 S-ID
					C2TX2SID = C2TX2SID | ((hi << 8) & 0xFF00);
					break;
			}
		#endif
	#else // __dsPIC30F__
		if (buffer < 3) {
			MX_MEMBUF_X[buffer][0] = (MX_CAN_TXB0ID_X << 2) & 0b0001111111111100;
		}
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdentExd_, (MX_UINT8 buffer, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)
		//Not Currently Supported!!
	#endif

	#if (MX_CAN_CHANNEL_X == 2)
   		//Not Currently Supported!!
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilterStd_, (MX_UINT8 filter, MX_UINT8 hi, MX_UINT8 lo))
{
	#if (MX_CAN_CHANNEL_X == 1)
		//Not Currently Supported!!
	#endif

	#if (MX_CAN_CHANNEL_X == 2)
   		//Not Currently Supported!!
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilterExd_, (MX_UINT8 filter, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)
		//Not Currently Supported!!
	#endif

	#if (MX_CAN_CHANNEL_X == 2)
   		//Not Currently Supported!!
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskStd_, (MX_UINT8 filter, MX_UINT8 hi, MX_UINT8 lo))
{
	#if (MX_CAN_CHANNEL_X == 1)
		//Not Currently Supported!!
	#endif

	#if (MX_CAN_CHANNEL_X == 2)
   		//Not Currently Supported!!
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskExd_, (MX_UINT8 filter, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)
		//Not Currently Supported!!
	#endif

	#if (MX_CAN_CHANNEL_X == 2)
   		//Not Currently Supported!!
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMask_, (MX_UINT8 mask, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)
		#ifdef __dsPIC30F__
			MX_UINT16 sid;
			MX_UINT16 eih;
			MX_UINT16 eil;
			// change to config mode
			// Request config mode.
			C1CTRLbits.REQOP = REQOP_CONFIG;
			while( C1CTRLbits.OPMODE != REQOP_CONFIG );

			#if (MX_CAN_EXID_X == 1)
				sid = MX_CAN_RXESID(id);
				eih = MX_CAN_RXEIDH(id);
				eil = MX_CAN_RXEIDL(id);
			#else
				sid = MX_CAN_RXSSID(id);
				eih = -1;
				eil = -1;
			#endif
			switch(mask)
			{
				case 0:
					C1RXM0SID = sid;
					C1RXM0EIDH = eih;
					C1RXM0EIDL = eil;
					break;
				case 1:
					C1RXM1SID = sid;
					C1RXM1EIDH = eih;
					C1RXM1EIDL = eil;
					break;
			}
			// Request normal mode.
			C1CTRLbits.REQOP = REQOP_NORMAL;
			while( C1CTRLbits.OPMODE != REQOP_NORMAL );
		#else // __dsPIC30F__
			// Request config mode.
			C1CTRL1bits.REQOP = REQOP_CONFIG;
			while( C1CTRL1bits.OPMODE != REQOP_CONFIG );

			/* Enable Window to Access Acceptance Filter Registers */
			C1CTRL1bits.WIN=0x1;

			switch (mask)
			{
				case 0:
			#if (MX_CAN_EXID_X == 1)
					C1RXM0SIDbits.SID = (id >> 18) & 0x7ff;
					C1RXM0SIDbits.EID = (id >> 16) & 0x3;
					C1RXM0EIDbits.EID = (id & 0xffff);
			#else
					C1RXM0SIDbits.SID = id;
			#endif
					break;
				case 1:
			#if (MX_CAN_EXID_X == 1)
					C1RXM1SIDbits.SID = (id >> 18) & 0x7ff;
					C1RXM1SIDbits.EID = (id >> 16) & 0x3;
					C1RXM1EIDbits.EID = (id & 0xffff);
			#else
					C1RXM1SIDbits.SID = id;
			#endif
					break;
			}

			/* Clear Window Bit to Access ECAN Control Registers */
			C1CTRL1bits.WIN=0x0;

			// Request normal mode.
			C1CTRL1bits.REQOP = REQOP_NORMAL;
			while( C1CTRL1bits.OPMODE != REQOP_NORMAL );
		#endif
	#endif
	#if (MX_CAN_CHANNEL_X == 2)
		#ifdef __dsPIC30F__
			MX_UINT16 sid;
			MX_UINT16 eih;
			MX_UINT16 eil;
			// change to config mode
			// Request config mode.
			C2CTRLbits.REQOP = REQOP_CONFIG;
			while( C2CTRLbits.OPMODE != REQOP_CONFIG );

			#if (MX_CAN_EXID_X == 1)
				sid = MX_CAN_RXESID(id);
				eih = MX_CAN_RXEIDH(id);
				eil = MX_CAN_RXEIDL(id);
			#else
				sid = MX_CAN_RXSSID(id);
				eih = -1;
				eil = -1;
			#endif
			switch(mask)
			{
				case 0:
					C2RXM0SID = sid;
					C2RXM0EIDH = eih;
					C2RXM0EIDL = eil;
					break;
				case 1:
					C2RXM1SID = sid;
					C2RXM1EIDH = eih;
					C2RXM1EIDL = eil;
					break;
			}
			// Request normal mode.
			C2CTRLbits.REQOP = REQOP_NORMAL;
			while( C2CTRLbits.OPMODE != REQOP_NORMAL );
		#else // __dsPIC30F__
			// Request config mode.
			C2CTRL1bits.REQOP = REQOP_CONFIG;
			while( C2CTRL1bits.OPMODE != REQOP_CONFIG );

			/* Enable Window to Access Acceptance Filter Registers */
			C2CTRL1bits.WIN=0x1;

			switch (mask)
			{
				case 0:
			#if (MX_CAN_EXID_X == 1)
					C2RXM0SIDbits.SID = (id >> 18) & 0x7ff;
					C2RXM0SIDbits.EID = (id >> 16) & 0x3;
					C2RXM0EIDbits.EID = (id & 0xffff);
			#else
					C2RXM0SIDbits.SID = id;
			#endif
					break;
				case 1:
			#if (MX_CAN_EXID_X == 1)
					C2RXM1SIDbits.SID = (id >> 18) & 0x7ff;
					C2RXM1SIDbits.EID = (id >> 16) & 0x3;
					C2RXM1EIDbits.EID = (id & 0xffff);
			#else
					C2RXM1SIDbits.SID = id;
			#endif
					break;
			}

			/* Clear Window Bit to Access ECAN Control Registers */
			C2CTRL1bits.WIN=0x0;

			// Request normal mode.
			C2CTRL1bits.REQOP = REQOP_NORMAL;
			while( C2CTRL1bits.OPMODE != REQOP_NORMAL );
		#endif
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilter_, (MX_UINT8 filter, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)
		#ifdef __dsPIC30F__
			MX_UINT16 sid;
			MX_UINT16 eih;
			MX_UINT16 eil;
			// change to config mode
			// Request config mode.
			C1CTRLbits.REQOP = REQOP_CONFIG;
			while( C1CTRLbits.OPMODE != REQOP_CONFIG );

			#if (MX_CAN_EXID_X == 1)
				sid = MX_CAN_RXESID(id);
				eih = MX_CAN_RXEIDH(id);
				eil = MX_CAN_RXEIDL(id);
			#else
				sid = MX_CAN_RXSSID(id);
				eih = -1;
				eil = -1;
			#endif
			switch(filter)
			{
				case 0:
					C1RXF0SID = sid;
					C1RXF0EIDH = eih;
					C1RXF0EIDL = eil;
					break;
				case 1:
					C1RXF1SID = sid;
					C1RXF1EIDH = eih;
					C1RXF1EIDL = eil;
					break;
				case 2:
					C1RXF2SID = sid;
					C1RXF2EIDH = eih;
					C1RXF2EIDL = eil;
					break;
				case 3:
					C1RXF3SID = sid;
					C1RXF3EIDH = eih;
					C1RXF3EIDL = eil;
					break;
				case 4:
					C1RXF4SID = sid;
					C1RXF4EIDH = eih;
					C1RXF4EIDL = eil;
					break;
				case 5:
					C1RXF5SID = sid;
					C1RXF5EIDH = eih;
					C1RXF5EIDL = eil;
					break;
			}
			// Request normal mode.
			C1CTRLbits.REQOP = REQOP_NORMAL;
			while( C1CTRLbits.OPMODE != REQOP_NORMAL );
		#else // __dsPIC30F__
			C1CTRL1bits.REQOP = REQOP_CONFIG;
			while( C1CTRL1bits.OPMODE != REQOP_CONFIG );

			// Switch to filter page
			C1CTRL1bits.WIN=0x1;

			#if (MX_CAN_EXID_X == 1)
			switch(filter)
			{
				case 0:
					C1RXF0SIDbits.SID = (id >> 18) & 0x7ff;
					C1RXF0SIDbits.EID = (id >> 16) & 0x3;
					C1RXF0EIDbits.EID = (id & 0xffff);
					break;
				case 1:
					C1RXF1SIDbits.SID = (id >> 18) & 0x7ff;
					C1RXF1SIDbits.EID = (id >> 16) & 0x3;
					C1RXF1EIDbits.EID = (id & 0xffff);
					break;
				case 2:
					C1RXF2SIDbits.SID = (id >> 18) & 0x7ff;
					C1RXF2SIDbits.EID = (id >> 16) & 0x3;
					C1RXF2EIDbits.EID = (id & 0xffff);
					break;
				case 3:
					C1RXF3SIDbits.SID = (id >> 18) & 0x7ff;
					C1RXF3SIDbits.EID = (id >> 16) & 0x3;
					C1RXF3EIDbits.EID = (id & 0xffff);
					break;
				case 4:
					C1RXF4SIDbits.SID = (id >> 18) & 0x7ff;
					C1RXF4SIDbits.EID = (id >> 16) & 0x3;
					C1RXF4EIDbits.EID = (id & 0xffff);
					break;
				case 5:
					C1RXF5SIDbits.SID = (id >> 18) & 0x7ff;
					C1RXF5SIDbits.EID = (id >> 16) & 0x3;
					C1RXF5EIDbits.EID = (id & 0xffff);
			}
			#else
			switch(filter)
			{
				case 0:
					C1RXF0SIDbits.SID = id & 0x7ff;
					break;
				case 1:
					C1RXF1SIDbits.SID = id & 0x7ff;
					break;
				case 2:
					C1RXF2SIDbits.SID = id & 0x7ff;
					break;
				case 3:
					C1RXF3SIDbits.SID = id & 0x7ff;
					break;
				case 4:
					C1RXF4SIDbits.SID = id & 0x7ff;
					break;
				case 5:
					C1RXF5SIDbits.SID = id & 0x7ff;
			}
			#endif

			// Back to normal mode
			C1CTRL1bits.WIN=0x0;
			C1CTRL1bits.REQOP = REQOP_NORMAL;
			while( C1CTRL1bits.OPMODE != REQOP_NORMAL );
		#endif
	#endif
	#if (MX_CAN_CHANNEL_X == 2)
		#ifdef __dsPIC30F__
			MX_UINT16 sid;
			MX_UINT16 eih;
			MX_UINT16 eil;
			// change to config mode
			// Request config mode.
			C2CTRLbits.REQOP = REQOP_CONFIG;
			while( C2CTRLbits.OPMODE != REQOP_CONFIG );

			#if (MX_CAN_EXID_X == 1)
				sid = MX_CAN_RXESID(id);
				eih = MX_CAN_RXEIDH(id);
				eil = MX_CAN_RXEIDL(id);
			#else
				sid = MX_CAN_RXSSID(id);
				eih = -1;
				eil = -1;
			#endif
			switch(filter)
			{
				case 0:
					C2RXF0SID = sid;
					C2RXF0EIDH = eih;
					C2RXF0EIDL = eil;
					break;
				case 1:
					C2RXF1SID = sid;
					C2RXF1EIDH = eih;
					C2RXF1EIDL = eil;
					break;
				case 2:
					C2RXF2SID = sid;
					C2RXF2EIDH = eih;
					C2RXF2EIDL = eil;
					break;
				case 3:
					C2RXF3SID = sid;
					C2RXF3EIDH = eih;
					C2RXF3EIDL = eil;
					break;
				case 4:
					C2RXF4SID = sid;
					C2RXF4EIDH = eih;
					C2RXF4EIDL = eil;
					break;
				case 5:
					C2RXF5SID = sid;
					C2RXF5EIDH = eih;
					C2RXF5EIDL = eil;
					break;
			}
			// Request normal mode.
			C2CTRLbits.REQOP = REQOP_NORMAL;
			while( C2CTRLbits.OPMODE != REQOP_NORMAL );
		#else // __dsPIC30F__
			C2CTRL1bits.REQOP = REQOP_CONFIG;
			while( C2CTRL1bits.OPMODE != REQOP_CONFIG );

			// Switch to filter page
			C2CTRL1bits.WIN=0x1;

			#if (MX_CAN_EXID_X == 1)
			switch(filter)
			{
				case 0:
					C2RXF0SIDbits.SID = (id >> 18) & 0x7ff;
					C2RXF0SIDbits.EID = (id >> 16) & 0x3;
					C2RXF0EIDbits.EID = (id & 0xffff);
					break;
				case 1:
					C2RXF1SIDbits.SID = (id >> 18) & 0x7ff;
					C2RXF1SIDbits.EID = (id >> 16) & 0x3;
					C2RXF1EIDbits.EID = (id & 0xffff);
					break;
				case 2:
					C2RXF2SIDbits.SID = (id >> 18) & 0x7ff;
					C2RXF2SIDbits.EID = (id >> 16) & 0x3;
					C2RXF2EIDbits.EID = (id & 0xffff);
					break;
				case 3:
					C2RXF3SIDbits.SID = (id >> 18) & 0x7ff;
					C2RXF3SIDbits.EID = (id >> 16) & 0x3;
					C2RXF3EIDbits.EID = (id & 0xffff);
					break;
				case 4:
					C2RXF4SIDbits.SID = (id >> 18) & 0x7ff;
					C2RXF4SIDbits.EID = (id >> 16) & 0x3;
					C2RXF4EIDbits.EID = (id & 0xffff);
					break;
				case 5:
					C2RXF5SIDbits.SID = (id >> 18) & 0x7ff;
					C2RXF5SIDbits.EID = (id >> 16) & 0x3;
					C2RXF5EIDbits.EID = (id & 0xffff);
			}
			#else
			switch(filter)
			{
				case 0:
					C2RXF0SIDbits.SID = id & 0x7ff;
					break;
				case 1:
					C2RXF1SIDbits.SID = id & 0x7ff;
					break;
				case 2:
					C2RXF2SIDbits.SID = id & 0x7ff;
					break;
				case 3:
					C2RXF3SIDbits.SID = id & 0x7ff;
					break;
				case 4:
					C2RXF4SIDbits.SID = id & 0x7ff;
					break;
				case 5:
					C2RXF5SIDbits.SID = id & 0x7ff;
			}
			#endif

			C2CTRL1bits.WIN=0x0;
			C2CTRL1bits.REQOP = REQOP_NORMAL;
			while( C2CTRL1bits.OPMODE != REQOP_NORMAL );
		#endif
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdent_, (MX_UINT8 buffer, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)
		#ifdef __dsPIC30F__
			// Request config mode.
			C1CTRLbits.REQOP = REQOP_CONFIG;
			while( C1CTRLbits.OPMODE != REQOP_CONFIG );

			#if (MX_CAN_EXID_X == 1)
			MX_UINT16 sid;
			MX_UINT16 eid;
			MX_UINT16 dlc;
			MX_UINT16 tmp;

			sid = MX_CAN_TXESID(id);
			eid = MX_CAN_TXEEID(id);
			dlc = MX_CAN_TXEDLC(id);

			switch(buffer)
			{
				case 0:
					tmp = C1TX0DLC & 0x78;
					C1TX0SID = sid;
					C1TX0EID = eid;
					C1TX0DLC = dlc | tmp;
					break;
				case 1:
					tmp = C1TX1DLC & 0x78;
					C1TX1SID = sid;
					C1TX1EID = eid;
					C1TX1DLC = dlc | tmp;
					break;
				case 2:
					tmp = C1TX2DLC & 0x78;
					C1TX2SID = sid;
					C1TX2EID = eid;
					C1TX2DLC = dlc | tmp;
					break;
			}
			#else
			switch(buffer)
			{
				case 0:
					C1TX0SID = MX_CAN_TXSSID(id);
					break;
				case 1:
					C1TX1SID = MX_CAN_TXSSID(id);
					break;
				case 2:
					C1TX2SID = MX_CAN_TXSSID(id);
					break;
			}
			#endif
			// Request normal mode.
			C1CTRLbits.REQOP = REQOP_NORMAL;
			while( C1CTRLbits.OPMODE != REQOP_NORMAL );
		#else // __dsPIC30F__
			if (buffer < 3) {
				#if (MX_CAN_EXID_X == 1)
					#if defined (FCV_DMA_BASE) && defined(__dsPIC33E__)
					int tmpdsr = DSRPAG;
					DSRPAG = __builtin_edspage (MX_MEMBUF_X);
					#endif

					MX_MEMBUF_X[buffer][0] = ((id >> 16) & 0b0001111111111100) | 0x01;
					MX_MEMBUF_X[buffer][1] = ((id >> 6 ) & 0b0000111111111111);
					MX_MEMBUF_X[buffer][2] = ((id & 0b111111) << 10) | (MX_MEMBUF_X[buffer][2] & 0xf);

					#if defined (FCV_DMA_BASE) && defined(__dsPIC33E__)
					DSRPAG = tmpdsr;
					#endif
				#else
					MX_MEMBUF_X[buffer][0] = (id << 2) & 0b0001111111111100;
				#endif
			}
		#endif
	#endif
	#if (MX_CAN_CHANNEL_X == 2)
		#ifdef __dsPIC30F__
			// Request config mode.
			C2CTRLbits.REQOP = REQOP_CONFIG;
			while( C2CTRLbits.OPMODE != REQOP_CONFIG );

			#if (MX_CAN_EXID_X == 1)
			MX_UINT16 sid;
			MX_UINT16 eid;
			MX_UINT16 dlc;
			MX_UINT16 tmp;

			sid = MX_CAN_TXESID(id);
			eid = MX_CAN_TXEEID(id);
			dlc = MX_CAN_TXEDLC(id);

			switch(buffer)
			{
				case 0:
					tmp = C2TX0DLC & 0x78;
					C2TX0SID = sid;
					C2TX0EID = eid;
					C2TX0DLC = dlc | tmp;
					break;
				case 1:
					tmp = C2TX1DLC & 0x78;
					C2TX1SID = sid;
					C2TX1EID = eid;
					C2TX1DLC = dlc | tmp;
					break;
				case 2:
					tmp = C2TX2DLC & 0x78;
					C2TX2SID = sid;
					C2TX2EID = eid;
					C2TX2DLC = dlc | tmp;
					break;
			}
			#else
			switch(buffer)
			{
				case 0:
					C2TX0SID = MX_CAN_TXSSID(id);
					break;
				case 1:
					C2TX1SID = MX_CAN_TXSSID(id);
					break;
				case 2:
					C2TX2SID = MX_CAN_TXSSID(id);
					break;
			}
			#endif
			// Request normal mode.
			C2CTRLbits.REQOP = REQOP_NORMAL;
			while( C2CTRLbits.OPMODE != REQOP_NORMAL );
		#else // __dsPIC30F__
			if (buffer < 3) {
				#if (MX_CAN_EXID_X == 1)
					#if defined (FCV_DMA_BASE) && defined(__dsPIC33E__)
					int tmpdsr = DSRPAG;
					DSRPAG = __builtin_edspage (MX_MEMBUF_X);
					#endif

					MX_MEMBUF_X[buffer][0] = ((id >> 16) & 0b0001111111111100) | 0x01;
					MX_MEMBUF_X[buffer][1] = ((id >> 6 ) & 0b0000111111111111);
					MX_MEMBUF_X[buffer][2] = ((id & 0b111111) << 10) | (MX_MEMBUF_X[buffer][2] & 0xf);

					#if defined (FCV_DMA_BASE) && defined(__dsPIC33E__)
					DSRPAG = tmpdsr;
					#endif
				#else
					MX_MEMBUF_X[buffer][0] = (id << 2) & 0b0001111111111100;
				#endif
			}
		#endif
	#endif
}

CALFUNCTION(MX_UINT32, FC_CAL_Internal_CAN_GetRxIdent_, (MX_UINT8 buffer))
{
#ifdef __dsPIC30F__
#if (MX_CAN_CHANNEL_X == 1)
		MX_UINT32 id = 0;
		MX_UINT32 sid = 0;
		MX_UINT32 eid = 0;
		MX_UINT32 dlc = 0;

		switch(buffer)
		{
			case 0:
				sid = C1RX0SID;
				eid = C1RX0EID;
				dlc = C1RX0DLC;
				break;
			case 1:
				sid = C1RX1SID;
				eid = C1RX1EID;
				dlc = C1RX1DLC;
				break;
		}
		if (sid & 1)
		{
			// Extended ID message
			id = ((dlc >> 10)& 0x3f) | ((eid << 6) & 0x3ffc0) | ((sid << 16) & 0x1ffc0000);
		}
		else
		{
			// Standard ID message
			id = (sid >> 2) & 0x7ff;
		}
		return id;
#endif
#if (MX_CAN_CHANNEL_X == 2)
	#ifndef dsPIC30	//Non dsPIC30F Device - Internal CAN different!!!
		#error "Internal CAN is not supported in the device type. dsPIC30 only supported."
	#endif
		MX_UINT32 id = 0;
		MX_UINT32 sid = 0;
		MX_UINT32 eid = 0;
		MX_UINT32 dlc = 0;

		switch(buffer)
		{
			case 0:
				sid = C2RX0SID;
				eid = C2RX0EID;
				dlc = C2RX0DLC;
				break;
			case 1:
				sid = C2RX1SID;
				eid = C2RX1EID;
				dlc = C2RX1DLC;
				break;
		}
		if (sid & 1)
		{
			// Extended ID message
			id = ((dlc >> 10)& 0x3f) | ((eid << 6) & 0x3ffc0) | ((sid << 16) & 0x1ffc0000);
		}
		else
		{
			// Standard ID message
			id = (sid >> 2) & 0x7ff;
		}
		return id;
#endif
#else // __dsPIC30F__
		return MX_CAN_MSG_ID_X;
#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxDataCount_, (MX_UINT8 buffer))
{
	return (MX_CAN_MSG_DLC_X);
}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxData_, (MX_UINT8 buffer, MX_UINT8 index))
{
	return (MX_CAN_MSG_DATA_X[index & 7]);
}

#endif
