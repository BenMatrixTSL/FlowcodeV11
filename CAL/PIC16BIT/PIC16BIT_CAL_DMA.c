// CRC: 5D982BB222882C54AB4AFF20A1590FC484D3178BD0D2510D0F5A64A7853221CAE2C33FABBE4F69A6659399D51781B7B95FA13464D8332A7570782B589D84CA509A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF51B28679DC6095B7C8C953ED0BF09A42F402D98A057D8E7769B29136FB31F074E73FB78D0F867719E2A9371F7ED9AAEDF8A1CEF2B749255656166C8E4594DEC5E64EFD556A116CDD34BFF9465BF29D4B95EA50C43CDDEFF66549D34A0D5AD11F33D186D8B2CB662D3B675AF13015E6467BB1C3FFB7DFFBADDA7E0A38DADB65FFF85A60D01A8F5E6C8
// REVISION: 1.0
// GUID: 5F9DFC54-D94D-4453-A762-00F086EA0348
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\PIC16BIT_CAL_DMA.c
/*********************************************************************
 *                  Flowcode CAL DMA File
 *
 * File: PIC16BIT_CAL_DMA.c
 *
 * (c) 2019 Matrix Multimedia Ltd.
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
 * 121219 | BR | Created
 */

//DMA CAL Definitions
#define MX_DMA_CHANNEL_X		CAL_APPEND(MX_DMA_CHANNEL_,MX_DMA_NUM)
#define MX_DMA_PING_X			CAL_APPEND(MX_DMA_PING_,MX_DMA_NUM)
#define MX_DMA_MODE_X			CAL_APPEND(MX_DMA_MODE_,MX_DMA_NUM)
#define MX_DMA_PERIPH_X			CAL_APPEND(MX_DMA_PERIPH_,MX_DMA_NUM)
#define MX_DMA_SIZE_X			CAL_APPEND(MX_DMA_SIZE_,MX_DMA_NUM)
#define MX_DMA_DBUF_X			CAL_APPEND(MX_DMA_DBUF_,MX_DMA_NUM)
#define MX_DMA_RX_X				CAL_APPEND(MX_DMA_RX_,MX_DMA_NUM)
#define MX_DMA_TX_X				CAL_APPEND(MX_DMA_TX_,MX_DMA_NUM)
#define MX_DMA_CALLBACK_X		CAL_APPEND(MX_DMA_CALLBACK_,MX_DMA_NUM)

//register definitions
#define MX_DMAXCON				CAL_APPEND(CAL_APPEND(DMA,MX_DMA_NUM),CON)
#define MX_DMAXREQ				CAL_APPEND(CAL_APPEND(DMA,MX_DMA_NUM),REQ)
#define MX_DMAXSTAH				CAL_APPEND(CAL_APPEND(DMA,MX_DMA_NUM),STAH)
#define MX_DMAXSTAL				CAL_APPEND(CAL_APPEND(DMA,MX_DMA_NUM),STAL)
#define MX_DMAXSTBH				CAL_APPEND(CAL_APPEND(DMA,MX_DMA_NUM),STBH)
#define MX_DMAXSTBL				CAL_APPEND(CAL_APPEND(DMA,MX_DMA_NUM),STBL)
#define MX_DMAXPAD				CAL_APPEND(CAL_APPEND(DMA,MX_DMA_NUM),PAD)
#define MX_DMAXCNT				CAL_APPEND(CAL_APPEND(DMA,MX_DMA_NUM),CNT)

//register bits definitions
#define MX_DMAXCONbits			CAL_APPEND(CAL_APPEND(DMA,MX_DMA_NUM),CONbits)

//buffer definitions
#define MX_DMA_Buff_A_X			CAL_APPEND(MX_DMA_Buff_A_,MX_DMA_NUM)
#define MX_DMA_Buff_B_X			CAL_APPEND(MX_DMA_Buff_B_,MX_DMA_NUM)
#define MX_DMA_Buff_X			CAL_APPEND(MX_DMA_Buff_,MX_DMA_NUM)

//Define Registers and flags - Build up to _DMA1xx which is defined as XXXxbits.DMA1xx
#define MX_DMA_FLAG_PRE_X		CAL_APPEND(_DMA,MX_DMA_CHANNEL_X)
#define MX_DMA_IFS_FLAG_X		CAL_APPEND(MX_DMA_FLAG_PRE_X,IF)
#define MX_DMA_IEC_FLAG_X		CAL_APPEND(MX_DMA_FLAG_PRE_X,IE)
#define MX_DMA_IPC_FLAG_X		CAL_APPEND(MX_DMA_FLAG_PRE_X,IP)
#define MX_DMA_INTERRUPT_X		CAL_APPEND(MX_DMA_FLAG_PRE_X,Interrupt)


//DMA Buffer Variable Declarations
unsigned char MX_DMA_Buff_X = 0;
unsigned int MX_DMA_Buff_A_X[MX_DMA_SIZE_X] __attribute__((space(dma),aligned(32)));

#if (MX_DMA_PING_X == 0)
  unsigned int MX_DMA_Buff_B_X[MX_DMA_SIZE_X] __attribute__((space(dma),aligned(32)));
#endif


//DMA Master Functions
CALFUNCTION(void, FC_CAL_DMA_Enable_, (void));
CALFUNCTION(void, FC_CAL_DMA_Disable_, (void));
CALFUNCTION(void, FC_CAL_DMA_Buffer_, (MX_UINT16 *data));



CALFUNCTION(void, FC_CAL_DMA_Enable_, (void))
{

  #ifdef MX_DMA

	MX_DMAXCONbits.AMODE = 0;								//Register Indirect Mode - Post Increment
	MX_DMAXCONbits.MODE = MX_DMA_PING_X + 2;				//Continuous = 2 / One Shot = 3
	MX_DMAXPAD = (volatile unsigned int) &MX_DMA_DBUF_X;	//Point DMA to Peripheral Buffer
	MX_DMAXCNT = MX_DMA_SIZE_X;								//Number Of DMA Requests per buffer

	#if (MX_DMA_RX_X == 1)
	  MX_DMAXREQ = MX_DMA_PERIPH_X;							//Select DMA Source
	#endif

	MX_DMAXSTAL = __builtin_dmaoffset(MX_DMA_Buff_A_X);
	MX_DMAXSTAH = (unsigned long)__builtin_dmaoffset(MX_DMA_Buff_A_X) >> 16;

	#if (MX_DMA_PING_X == 0)
	  MX_DMAXSTBL = __builtin_dmaoffset(MX_DMA_Buff_B_X);
	  MX_DMAXSTBH = (unsigned long)__builtin_dmaoffset(MX_DMA_Buff_B_X) >> 16;
	#endif

	MX_DMA_IFS_FLAG_X = 0;									//Clear DMA Interrupt Flag
	MX_DMA_IPC_FLAG_X = 4;									//Default Priority
	MX_DMA_IEC_FLAG_X = 1;									//Interrupt Enable

	MX_DMAXCONbits.CHEN = 1;								//Enable DMA Channel

  #else
 	#error "Hardware DMA not supported by Target microcontroller."
  #endif
}


CALFUNCTION(void, FC_CAL_DMA_Disable_, (void))
{
	MX_DMAXCONbits.CHEN = 0;								//Disable DMA Channel
}


CALFUNCTION(void, FC_CAL_DMA_Buffer_, (MX_UINT16 *data))
{
	for (int x = 0; x < MX_DMA_SIZE_X; x++)
	{

		#if (MX_DMA_TX_X == 1)
			if (MX_DMA_Buff_X == 0)
			{
				MX_DMA_Buff_A_X[x] = data[x];
			}
			else
			{
				#if (MX_DMA_PING_X == 0)
				  MX_DMA_Buff_B_X[x] = data[x];
				#endif
			}
		#endif

		#if (MX_DMA_RX_X == 1)
			if (MX_DMA_Buff_X == 0)
			{
				data[x] = MX_DMA_Buff_A_X[x];
			}
			else
			{
				#if (MX_DMA_PING_X == 0)
				  data[x] = MX_DMA_Buff_B_X[x];
				#endif
			}
		#endif

	}

	#if (MX_DMA_PING_X == 0)
  	  MX_DMA_Buff_X = (MX_DMA_Buff_X + 1) & 1;
  	#endif
}


void __attribute__ ( (interrupt, auto_psv) ) MX_DMA_INTERRUPT_X( void )
{
	MX_DMA_CALLBACK_X();
	MX_DMA_Buff_X ^= 1;
}


#undef MX_DMA_FLAG_PRE_X
#undef MX_DMA_IFS_FLAG_X
#undef MX_DMA_IEC_FLAG_X
#undef MX_DMA_IPC_FLAG_X
#undef MX_DMA_INTERRUPT_X
