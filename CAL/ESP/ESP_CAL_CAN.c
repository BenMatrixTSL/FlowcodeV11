// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A032535F4E381B52A002F30B4650F87BFB5FC36BB60D5779D524F8CD3FDC3D2E448940AE31AE32EB4A0C3CAEE8E7DA6987959A4FF4A4E78C02FA280D20A4F44CF34B94565145CEF58B41D383E24CE24514BD92C08C8A058764533B43458368A5CE89B20AC17103D045D75846D5559449635CC515B8A6BE9D6CD2F19382ED02D6086A20D023046EF424549D34A0D5AD11F327C176AAFF49B0AEC21DC0110D7586ED6388D935928FC8453C4E04E7CDB5FC3F295E1D946A835C79
// REVISION: 3.0
// GUID: AAF0C05B-85DB-4C6F-92D2-A56CF4200B2B
// DATE: 29\09\2025
// DIR: CAL\ESP\ESP_CAL_CAN.c
/*********************************************************************
 *                  Flowcode CAL CAN File
 *
 * File: ESP_CAL_CAN.c
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
 * 051120 | BR | Created
 * 200221 | LM | major updates
 */


#ifndef MX_ECAN
	#error "Internal CAN not supported on this device"
#else


#define MX_CAN_CHANNEL_X		CAL_APPEND(MX_CAN_CHANNEL_, MX_CAN_NUM)

#define MX_CAN_TX_PORT_X		CAL_APPEND(MX_CAN_TX_PORT_, MX_CAN_NUM)
#define MX_CAN_TX_PIN_X			CAL_APPEND(MX_CAN_TX_PIN_, MX_CAN_NUM)

#define MX_CAN_RX_PORT_X		CAL_APPEND(MX_CAN_RX_PORT_, MX_CAN_NUM)
#define MX_CAN_RX_PIN_X			CAL_APPEND(MX_CAN_RX_PIN_, MX_CAN_NUM)

#define MX_CAN_BUS_RATE_X			CAL_APPEND(MX_CAN_BUS_RATE_, MX_CAN_NUM)

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

//#define porta					0
//#define portb					32

#define MX_CAN_TX_X (MX_CAN_TX_PORT_X + MX_CAN_TX_PIN_X)
#define MX_CAN_RX_X (MX_CAN_RX_PORT_X + MX_CAN_RX_PIN_X)

//Unsupported BAUD Rates
#define BAUD_5K 4
#define BAUD_16K 5
#define BAUD_20K 6
#define BAUD_25K 7
#define BAUD_50K 8
#define BAUD_100K 9
#define BAUD_800K 10

//Supported Baud Rates
#define BAUD_125K 0
#define BAUD_250K 1
#define BAUD_500K 2
#define BAUD_1000K 3


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


#include "driver/gpio.h"
#include "driver/twai.h"


//Transmission Message Buffers
twai_message_t TxMsg0 = {
	#if (MX_CAN_EXID_X == 1)
		.flags = TWAI_MSG_FLAG_EXTD,
	#else
		.flags = TWAI_MSG_FLAG_NONE,
	#endif
	.identifier = MX_CAN_TXB0ID_X,
	.data_length_code = MX_CAN_TXB0LEN_X,
	.data[0] = MX_CAN_TXB0DB0_X,
	.data[1] = MX_CAN_TXB0DB1_X,
	.data[2] = MX_CAN_TXB0DB2_X,
	.data[3] = MX_CAN_TXB0DB3_X,
	.data[4] = MX_CAN_TXB0DB4_X,
	.data[5] = MX_CAN_TXB0DB5_X,
	.data[6] = MX_CAN_TXB0DB6_X,
	.data[7] = MX_CAN_TXB0DB7_X,
};
twai_message_t TxMsg1 = {
	#if (MX_CAN_EXID_X == 1)
		.flags = TWAI_MSG_FLAG_EXTD,
	#else
		.flags = TWAI_MSG_FLAG_NONE,
	#endif
	.identifier = MX_CAN_TXB1ID_X,
	.data_length_code = MX_CAN_TXB1LEN_X,
	.data[0] = MX_CAN_TXB1DB0_X,
	.data[1] = MX_CAN_TXB1DB1_X,
	.data[2] = MX_CAN_TXB1DB2_X,
	.data[3] = MX_CAN_TXB1DB3_X,
	.data[4] = MX_CAN_TXB1DB4_X,
	.data[5] = MX_CAN_TXB1DB5_X,
	.data[6] = MX_CAN_TXB1DB6_X,
	.data[7] = MX_CAN_TXB1DB7_X,
};
twai_message_t TxMsg2 = {
	#if (MX_CAN_EXID_X == 1)
		.flags = TWAI_MSG_FLAG_EXTD,
	#else
		.flags = TWAI_MSG_FLAG_NONE,
	#endif
	.identifier = MX_CAN_TXB2ID_X,
	.data_length_code = MX_CAN_TXB2LEN_X,
	.data[0] = MX_CAN_TXB2DB0_X,
	.data[1] = MX_CAN_TXB2DB1_X,
	.data[2] = MX_CAN_TXB2DB2_X,
	.data[3] = MX_CAN_TXB2DB3_X,
	.data[4] = MX_CAN_TXB2DB4_X,
	.data[5] = MX_CAN_TXB2DB5_X,
	.data[6] = MX_CAN_TXB2DB6_X,
	.data[7] = MX_CAN_TXB2DB7_X,
};

//Reception Message Buffers
twai_message_t RxMsg0;
twai_message_t RxMsg1;



CALFUNCTION(void, FC_CAL_Internal_CAN_Init_, (void))
{
	#if (MX_CAN_CHANNEL_X == 1)

		//Initialize configuration structures using macro initializers
		twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(MX_CAN_TX_X, MX_CAN_RX_X, TWAI_MODE_NORMAL);
		twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

		#if (MX_CAN_BUS_RATE_X == BAUD_5K)
			twai_timing_config_t t_config = TWAI_TIMING_CONFIG_12_5KBITS();
		#elif (MX_CAN_BUS_RATE_X == BAUD_16K)
			twai_timing_config_t t_config = TWAI_TIMING_CONFIG_16KBITS();
		#elif (MX_CAN_BUS_RATE_X == BAUD_20K)
			twai_timing_config_t t_config = TWAI_TIMING_CONFIG_20KBITS();
		#elif (MX_CAN_BUS_RATE_X == BAUD_25K)
			twai_timing_config_t t_config = TWAI_TIMING_CONFIG_25KBITS();
		#elif (MX_CAN_BUS_RATE_X == BAUD_50K)
			twai_timing_config_t t_config = TWAI_TIMING_CONFIG_50KBITS();
		#elif (MX_CAN_BUS_RATE_X == BAUD_100K)
			twai_timing_config_t t_config = TWAI_TIMING_CONFIG_100KBITS();
		#elif (MX_CAN_BUS_RATE_X == BAUD_125K)
			twai_timing_config_t t_config = TWAI_TIMING_CONFIG_125KBITS();
		#elif (MX_CAN_BUS_RATE_X == BAUD_250K)
			twai_timing_config_t t_config = TWAI_TIMING_CONFIG_250KBITS();
		#elif (MX_CAN_BUS_RATE_X == BAUD_500K)
			twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
		#elif (MX_CAN_BUS_RATE_X == BAUD_800K)
			twai_timing_config_t t_config = TWAI_TIMING_CONFIG_800KBITS();
		#else // (MX_CAN_BUS_RATE_X == BAUD_1000K)
			twai_timing_config_t t_config = TWAI_TIMING_CONFIG_1MBITS();
		#endif

		//Install CAN driver
		twai_driver_install(&g_config, &t_config, &f_config);

		//Start CAN driver
		twai_start();

	#endif

	#if (MX_CAN_CHANNEL_X == 2)
   		#error "ESP32 only has 1 CAN channel";
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_Uninit_, (void))
{
	#if (MX_CAN_CHANNEL_X == 1)

		//Stop the CAN driver
		twai_stop();

		//Uninstall the CAN driver
		twai_driver_uninstall();

	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}


CALFUNCTION(void, FC_CAL_Internal_CAN_SendBuffer_, (MX_UINT8 buffer))
{
	#if (MX_CAN_CHANNEL_X == 1)
		switch (buffer)
		{
			case 0:
				twai_transmit(&TxMsg0, pdMS_TO_TICKS(1000));
				break;
			case 1:
				twai_transmit(&TxMsg1, pdMS_TO_TICKS(1000));
				break;
			case 2:
				twai_transmit(&TxMsg2, pdMS_TO_TICKS(1000));
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
			if (twai_receive(&RxMsg0, pdMS_TO_TICKS(10000)) == ESP_OK)
				return 1;
		}
		else
		{
			if (twai_receive(&RxMsg1, pdMS_TO_TICKS(10000)) == ESP_OK)
				return 1;
		}

	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif

	return 0;
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxData_, (MX_UINT8 buffer, MX_UINT8 data_cnt, MX_UINT8 d0, MX_UINT8 d1, MX_UINT8 d2, MX_UINT8 d3, MX_UINT8 d4, MX_UINT8 d5, MX_UINT8 d6, MX_UINT8 d7))
{
	#if (MX_CAN_CHANNEL_X == 1)

		switch(buffer)
		{
			case 0:
				TxMsg0.data_length_code = data_cnt;
				TxMsg0.data[0] = d0;
				TxMsg0.data[1] = d1;
				TxMsg0.data[2] = d2;
				TxMsg0.data[3] = d3;
				TxMsg0.data[4] = d4;
				TxMsg0.data[5] = d5;
				TxMsg0.data[6] = d6;
				TxMsg0.data[7] = d7;
				break;
			case 1:
				TxMsg1.data_length_code = data_cnt;
				TxMsg1.data[0] = d0;
				TxMsg1.data[1] = d1;
				TxMsg1.data[2] = d2;
				TxMsg1.data[3] = d3;
				TxMsg1.data[4] = d4;
				TxMsg1.data[5] = d5;
				TxMsg1.data[6] = d6;
				TxMsg1.data[7] = d7;
				break;
			case 2:
				TxMsg2.data_length_code = data_cnt;
				TxMsg2.data[0] = d0;
				TxMsg2.data[1] = d1;
				TxMsg2.data[2] = d2;
				TxMsg2.data[3] = d3;
				TxMsg2.data[4] = d4;
				TxMsg2.data[5] = d5;
				TxMsg2.data[6] = d6;
				TxMsg2.data[7] = d7;
				break;
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
				TxMsg0.identifier = (hi << 8) | lo;
				TxMsg0.flags = TWAI_MSG_FLAG_NONE;
				break;
			case 1:
				TxMsg1.identifier = (hi << 8) | lo;
				TxMsg1.flags = TWAI_MSG_FLAG_NONE;
				break;
			case 2:
				TxMsg2.identifier = (hi << 8) | lo;
				TxMsg2.flags = TWAI_MSG_FLAG_NONE;
				break;
		}

	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdentExd_, (MX_UINT8 buffer, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)

		MX_UINT32 id = id3;
		id = id << 8;
		id |= id2;
		id = id << 8;
		id |= id1;
		id = id << 8;
		id |= id0;

		switch(buffer)
		{
			case 0:
				TxMsg0.identifier = id;
				TxMsg0.flags = TWAI_MSG_FLAG_EXTD;
				break;
			case 1:
				TxMsg1.identifier = id;
				TxMsg1.flags = TWAI_MSG_FLAG_EXTD;
				break;
			case 2:
				TxMsg2.identifier = id;
				TxMsg2.flags = TWAI_MSG_FLAG_EXTD;
				break;
		}

	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilterStd_, (MX_UINT8 filter, MX_UINT8 hi, MX_UINT8 lo))
{
	#if (MX_CAN_CHANNEL_X == 1)

	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilterExd_, (MX_UINT8 filter, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskStd_, (MX_UINT8 mask, MX_UINT8 hi, MX_UINT8 lo))
{
	#if (MX_CAN_CHANNEL_X == 1)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskExd_, (MX_UINT8 mask, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMask_, (MX_UINT8 mask, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilter_, (MX_UINT8 filter, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdent_, (MX_UINT8 buffer, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)

		switch(buffer)
		{
			case 0:
				TxMsg0.identifier = id;
				#if (MX_CAN_EXID_X == 1)
				TxMsg0.flags = TWAI_MSG_FLAG_EXTD;
				#else
					if (id < 2048)
					TxMsg0.flags = TWAI_MSG_FLAG_NONE;
					else
						TxMsg0.flags = TWAI_MSG_FLAG_EXTD;
				#endif
				break;
			case 1:
				TxMsg1.identifier = id;
				#if (MX_CAN_EXID_X == 1)
				TxMsg1.flags = TWAI_MSG_FLAG_EXTD;
				#else
					if (id < 2048)
					TxMsg1.flags = TWAI_MSG_FLAG_NONE;
					else
						TxMsg1.flags = TWAI_MSG_FLAG_EXTD;
				#endif
				break;
			case 2:
				TxMsg2.identifier = id;
				#if (MX_CAN_EXID_X == 1)
				TxMsg2.flags = TWAI_MSG_FLAG_EXTD;
				#else
					if (id < 2048)
					TxMsg2.flags = TWAI_MSG_FLAG_NONE;
					else
						TxMsg2.flags = TWAI_MSG_FLAG_EXTD;
				#endif
				break;
		}

	#endif
}

CALFUNCTION(MX_UINT32, FC_CAL_Internal_CAN_GetRxIdent_, (MX_UINT8 buffer))
{
	MX_UINT32 id = 0;

	#if (MX_CAN_CHANNEL_X == 1)

		switch(buffer)
		{
			case 0:
				id = RxMsg0.identifier;
				break;
			case 1:
				id = RxMsg1.identifier;
				break;
		}

	#endif

	return id;
}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxDataCount_, (MX_UINT8 buffer))
{
	MX_UINT8 MsgLength = 0;

	#if (MX_CAN_CHANNEL_X == 1)

		switch(buffer)
		{
			case 0:
				MsgLength = RxMsg0.data_length_code;
				break;
			case 1:
				MsgLength = RxMsg1.data_length_code;
				break;
		}

	#endif

	return (MsgLength);
}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxData_, (MX_UINT8 buffer, MX_UINT8 index))
{
	MX_UINT8 MsgData = 0;

	#if (MX_CAN_CHANNEL_X == 1)

		switch(buffer)
		{
			case 0:
				MsgData = RxMsg0.data[index];
				break;
			case 1:
				MsgData = RxMsg1.data[index];
				break;
		}

	#endif

	return (MsgData);
}

#endif
