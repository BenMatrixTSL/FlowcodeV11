// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A006F4274FDFAD3D87C5F8E545EDBF5F8849F2FED8D89CCBACCFB03E0A4118D1F5796EDD611F6757020C3CAEE8E7DA6987F05FEB5AA47B6E4486533D5D162AFA93FE40F020DF02129260F488C745CE1F5956DBE59174D86538F8A750A675D2CDE57B3B9A381612E5FE2D24EDAB23EBD4972DD53F3284E31A37DFBDC3C18120985B198CE075F14C289C549D34A0D5AD11F33A7A47F061F3EEDFF2214E6FD4416B9097F16C6E50E224939A9734F14306F80A27D6A9F323037F27
// REVISION: 21.0
// GUID: 97D3F7F6-982B-4A90-9CC1-0C4AC0051D49
// DATE: 17\11\2025
// DIR: CAL\ESP\ESP_CAL_SPI.c
/*********************************************************************
 *                  Flowcode CAL SPI File
 *
 * File: ESP_CAL_SPI.c
 *
 * (c) 2018 Matrix TSL.
 * http://www.matrixtsl.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
 * 'Company') for its Flowcode graphical programming language is
 * intended and supplied to you, the Company's customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN 'AS IS' CONDITION. NO WARRANTIES,
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
 * 250718 | BR | Created
 *
 */


//When using hardware SPI channels override port and pin conns with FCD conn definitions
//Only overwrite CS pin defines when using SPI in slave mode on a hardware channel
//Also sort out postscale and prescale options for hardware channels

#define MX_SPI_REF_X			CAL_APPEND(MX_SPI_REF, MX_SPI_NUM)
#define MX_SPI_CHANNEL_X		CAL_APPEND(MX_SPI_CHANNEL_, MX_SPI_NUM)
#define MX_SPI_MOSI_PIN_X		CAL_APPEND(MX_SPI_MOSI_PIN_, MX_SPI_NUM)
#define MX_SPI_MOSI_PORT_X		CAL_APPEND(MX_SPI_MOSI_PORT_, MX_SPI_NUM)
#define MX_SPI_MOSI_TRIS_X		CAL_APPEND(MX_SPI_MOSI_TRIS_, MX_SPI_NUM)
#define MX_SPI_MISO_PIN_X		CAL_APPEND(MX_SPI_MISO_PIN_, MX_SPI_NUM)
#define MX_SPI_MISO_PORT_X		CAL_APPEND(MX_SPI_MISO_PORT_, MX_SPI_NUM)
#define MX_SPI_MISO_TRIS_X		CAL_APPEND(MX_SPI_MISO_TRIS_, MX_SPI_NUM)
#define MX_SPI_SCK_PIN_X		CAL_APPEND(MX_SPI_SCK_PIN_, MX_SPI_NUM)
#define MX_SPI_SCK_PORT_X		CAL_APPEND(MX_SPI_SCK_PORT_, MX_SPI_NUM)
#define MX_SPI_SCK_TRIS_X		CAL_APPEND(MX_SPI_SCK_TRIS_, MX_SPI_NUM)
#define MX_SPI_CS_PIN_X			CAL_APPEND(MX_SPI_CS_PIN_, MX_SPI_NUM)
#define MX_SPI_CS_PORT_X		CAL_APPEND(MX_SPI_CS_PORT_, MX_SPI_NUM)
#define MX_SPI_CS_TRIS_X		CAL_APPEND(MX_SPI_CS_TRIS_, MX_SPI_NUM)
#define MX_SPI_BMODE_X			CAL_APPEND(MX_SPI_BMODE_, MX_SPI_NUM)
#define MX_SPI_PR_SCALE_X		CAL_APPEND(MX_SPI_PR_SCALE_, MX_SPI_NUM)
#define MX_SPI_PO_SCALE_X		CAL_APPEND(MX_SPI_PO_SCALE_, MX_SPI_NUM)
#define MX_SPI_INT_X			CAL_APPEND(MX_SPI_INT_, MX_SPI_NUM)
#define MX_SPI_HANDLE_X			CAL_APPEND(spiHandle_, MX_SPI_NUM)

#define MX_SPI_MOSI_X			CAL_APPEND(MX_SPI_MOSI_RPOR_, MX_SPI_NUM)
#define MX_SPI_MISO_X			CAL_APPEND(MX_SPI_MISO_RP_, MX_SPI_NUM)
#define MX_SPI_SCK_X			CAL_APPEND(MX_SPI_CLK_RPOR_, MX_SPI_NUM)


#define MX_PRESCALE_VAR_X		CAL_APPEND(prescale_, MX_SPI_NUM)


//Function Prototypes
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Init_, (void));
CALFUNCTION(void, FC_CAL_SPI_Master_Uninit_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Byte_, (MX_UINT8 DataOut));
CALFUNCTION(void, FC_CAL_SPI_SetPrescaler_, (MX_UINT16 Prescaler));

CALFUNCTION(void, FC_CAL_SPI_Slave_Init_, (void));
CALFUNCTION(void, FC_CAL_SPI_Slave_Uninit_, (void));
CALFUNCTION(void, FC_CAL_SPI_Slave_SetTxData_, (MX_UINT8 Data));
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Slave_GetRxData_, (void));

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_Init_,   (void));
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_,   (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length));
CALFUNCTION(void,     FC_CAL_SPI_Transaction_Uninit_, (void));


#include <string.h>
#include "driver/spi_master.h"


//Bus Mode - Bit0=CKP=CPOL, Bit1=CKE=!CPHA, Bit2=CSMP
//CKP=CPOL - Clock Polarity - Idle State of the clock 0=0, 1=1
//CKE=CPHA - Clock Phase - Clock Edge 0=leading edge, 1=trailing edge
//CSMP - Input Data Bit Sample Phase

// There are 4 SPI clock modes as follows:
//
// SPI Mode | CKP (CPOL) | CKE (CPHA) | BMODE | Explanation
//----------+------------+--------------------+------------------------------------------------
//  1 (0,1) |  0   (0)   |  0   (1)   | xx00  | idle low;  data out on falling/trailing edge
//  3 (1,1) |  1   (1)   |  0   (1)   | xx01  | idle high; data out on rising/trailing edge
//  0 (0,0) |  0   (0)   |  1   (0)   | xx10  | idle low;  data out on rising/leading edge
//  2 (1,0) |  1   (1)   |  1   (0)   | xx11  | idle high; data out on falling/leading edge
//----------+------------+---------------------------------------------------------------------
//
// So:
//     BMODE & 0x01 = CKP =  CPOL
//     BMODE & 0x02 = CKE = !CPHA


#ifndef HSPI_HOST
	#define HSPI_HOST SPI2_HOST
#endif

#ifndef VSPI_HOST
	#define VSPI_HOST SPI3_HOST
#endif

#if (MX_SPI_CHANNEL_X == 1)
	#ifndef MX_SPI_HARDWARE_DEFINITIONS_CH1
	  	#define MX_SPI_HARDWARE_DEFINITIONS_CH1

		spi_device_handle_t MX_SPI_HANDLE_1_HSPI;

		MX_UINT8 MX_SPI_Init_1 = 0;
		MX_UINT8 MX_SPI_Mode_1 = 0;

		void FC_CAL_SPI_Master_Init_HSPI(void)
		{
			if (MX_SPI_Init_1 == 0)
			{
				//Phase and Polarity swapped on ESP
				if (MX_SPI_BMODE_X & 0x01)			//Clock Idle State
					MX_SPI_Mode_1 |= 0x02;
				if ((MX_SPI_BMODE_X & 0x02) == 0)	//Clock Phase
					MX_SPI_Mode_1 |= 0x01;

				spi_bus_config_t buscfg={
					.miso_io_num=MX_SPI_MISO_X,
					.mosi_io_num=MX_SPI_MOSI_X,
					.sclk_io_num=MX_SPI_SCK_X,
					.quadwp_io_num=-1,
					.quadhd_io_num=-1
				};

				spi_device_interface_config_t devcfg={
					.clock_speed_hz=MX_SPI_PR_SCALE_X,           			//Clock out at Prescaler defined rate
					.mode=MX_SPI_Mode_1,                                	//SPI mode
					.spics_io_num=-1,               						//CS pin - N/A
					.queue_size=1,                          				//Changed to 1 to give all 4096 bytes of SPI DMA
				};

				#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)				// enable functionality present in IDF v5.0
					spi_bus_initialize(HSPI_HOST, &buscfg, SPI_DMA_CH_AUTO);	//Initialize the SPI bus
				#else
					spi_bus_initialize(HSPI_HOST, &buscfg, 1);					//Initialize the SPI bus
				#endif

				spi_bus_add_device(HSPI_HOST, &devcfg, &MX_SPI_HANDLE_1_HSPI);	//Attach a Device to the SPI bus

				MX_SPI_Init_1 = 1;
				CALFUNCTION(, FC_CAL_SPI_Master_Byte_, (0x55));				//Send a byte - this allows the bus to be setup correctly

			}
		}


		void FC_CAL_SPI_Master_Uninit_HSPI(void)
		{
			spi_bus_remove_device(MX_SPI_HANDLE_1_HSPI);
		}


		MX_UINT8 FC_CAL_SPI_Master_Byte_HSPI (MX_UINT8 DataOut)
		{
			MX_UINT8 retVal = 0;

			spi_transaction_t t;
			memset(&t, 0, sizeof(t));
			t.length = 8;
			t.flags = (SPI_TRANS_USE_RXDATA) | (SPI_TRANS_USE_TXDATA);
			t.tx_data[0] = DataOut;

			#ifdef MX_SPI_ASYNC_MODE_1
				spi_device_queue_trans(MX_SPI_HANDLE_1_HSPI, &t, portMAX_DELAY);
				spi_device_get_trans_result(MX_SPI_HANDLE_1_HSPI, &t, 0);
			#else
				spi_device_polling_transmit(MX_SPI_HANDLE_1_HSPI, &t);
			#endif

			retVal = t.rx_data[0];

			return (retVal);
		}


		void FC_CAL_SPI_SetPrescaler_HSPI (MX_UINT16 Prescaler)
		{
			MX_UINT32 SPI_FREQ = (MX_UINT32) Prescaler * (MX_UINT32) 100000;

			spi_device_interface_config_t devcfg={
				.clock_speed_hz=SPI_FREQ,           					//Clock out at Prescaler defined rate
				.mode=MX_SPI_Mode_1,                                	//SPI mode 0
				.spics_io_num=-1,               						//CS pin - N/A
				.queue_size=1,                          				//Changed to 1 to give all 4096 bytes of SPI DMA
			};

			spi_bus_remove_device(MX_SPI_HANDLE_1_HSPI);
			spi_bus_add_device(HSPI_HOST, &devcfg, &MX_SPI_HANDLE_1_HSPI);	//Attach a Device to the SPI bus
		}


		MX_UINT8 FC_CAL_SPI_Transaction_HSPI (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length)
		{
			if (Length <= Size)
			{
				spi_transaction_t t;
				memset(&t, 0, sizeof(t));
				t.length = 8 * Length;
				t.tx_buffer = Buffer;
				t.rx_buffer = Buffer;

				#ifdef MX_SPI_ASYNC_MODE_1
					esp_err_t ret = spi_device_queue_trans(MX_SPI_HANDLE_1_HSPI, &t, portMAX_DELAY);
					spi_device_get_trans_result(MX_SPI_HANDLE_1_HSPI, &t, 0);
				#else
					esp_err_t ret = spi_device_polling_transmit(MX_SPI_HANDLE_1_HSPI, &t);
				#endif

				if (ESP_OK == ret)
					return 1;		// Success
			}
			return 0;
		}

	#endif
#endif


#if (MX_SPI_CHANNEL_X == 2)
	#ifndef MX_SPI_HARDWARE_DEFINITIONS_CH2
	  	#define MX_SPI_HARDWARE_DEFINITIONS_CH2

		spi_device_handle_t MX_SPI_HANDLE_2_VSPI;

		MX_UINT8 MX_SPI_Init_2 = 0;
		MX_UINT8 MX_SPI_Mode_2 = 0;

		void FC_CAL_SPI_Master_Init_VSPI(void)
		{
			if (MX_SPI_Init_2 == 0)
			{
				//Phase and Polarity swapped on ESP
				if (MX_SPI_BMODE_X & 0x01)			//Clock Idle State
					MX_SPI_Mode_2 |= 0x02;
				if ((MX_SPI_BMODE_X & 0x02) == 0)	//Clock Phase
					MX_SPI_Mode_2 |= 0x01;

				spi_bus_config_t buscfg={
					.miso_io_num=MX_SPI_MISO_X,
					.mosi_io_num=MX_SPI_MOSI_X,
					.sclk_io_num=MX_SPI_SCK_X,
					.quadwp_io_num=-1,
					.quadhd_io_num=-1
				};

				spi_device_interface_config_t devcfg={
					.clock_speed_hz=MX_SPI_PR_SCALE_X,           			//Clock out at Prescaler defined rate
					.mode=MX_SPI_Mode_2,                               		//SPI mode
					.spics_io_num=-1,               						//CS pin - N/A
					.queue_size=1,                          				//Changed to 1 to give all 4096 bytes of SPI DMA
				};

				#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)				// enable functionality present in IDF v5.0
					spi_bus_initialize(VSPI_HOST, &buscfg, SPI_DMA_CH_AUTO);		//Initialize the SPI bus
				#else
					spi_bus_initialize(VSPI_HOST, &buscfg, 2);					//Initialize the SPI bus
				#endif


				spi_bus_add_device(VSPI_HOST, &devcfg, &MX_SPI_HANDLE_2_VSPI);	//Attach a Device to the SPI bus

				MX_SPI_Init_2 = 1;
				CALFUNCTION(, FC_CAL_SPI_Master_Byte_, (0x55));				//Send a byte - this allows the bus to be setup correctly
			}
		}


		void FC_CAL_SPI_Master_Uninit_VSPI(void)
		{
			spi_bus_remove_device(MX_SPI_HANDLE_2_VSPI);
		}


		MX_UINT8 FC_CAL_SPI_Master_Byte_VSPI (MX_UINT8 DataOut)
		{
			MX_UINT8 retVal = 0;

			spi_transaction_t t;
			memset(&t, 0, sizeof(t));
			t.length = 8;
			t.flags = (SPI_TRANS_USE_RXDATA) | (SPI_TRANS_USE_TXDATA);
			t.tx_data[0] = DataOut;

			#ifdef MX_SPI_ASYNC_MODE_2
				spi_device_queue_trans(MX_SPI_HANDLE_2_VSPI, &t, portMAX_DELAY);
				spi_device_get_trans_result(MX_SPI_HANDLE_2_VSPI, &t, 0);
			#else
				spi_device_polling_transmit(MX_SPI_HANDLE_2_VSPI, &t);
			#endif

			retVal = t.rx_data[0];

			return (retVal);
		}


		void FC_CAL_SPI_SetPrescaler_VSPI (MX_UINT16 Prescaler)
		{
			MX_UINT32 SPI_FREQ = (MX_UINT32) Prescaler * (MX_UINT32) 100000;

			spi_device_interface_config_t devcfg={
				.clock_speed_hz=SPI_FREQ,           					//Clock out at Prescaler defined rate
				.mode=MX_SPI_Mode_2,                                	//SPI mode
				.spics_io_num=-1,               						//CS pin - N/A
				.queue_size=1,                          				//Changed to 1 to give all 4096 bytes of SPI DMA
			};

			spi_bus_remove_device(MX_SPI_HANDLE_2_VSPI);
			spi_bus_add_device(VSPI_HOST, &devcfg, &MX_SPI_HANDLE_2_VSPI);	//Attach a Device to the SPI bus
		}


		MX_UINT8 FC_CAL_SPI_Transaction_VSPI (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length)
		{
			if (Length <= Size)
			{
				spi_transaction_t t;
				memset(&t, 0, sizeof(t));
				t.length = 8 * Length;
				t.tx_buffer = Buffer;
				t.rx_buffer = Buffer;

				#ifdef MX_SPI_ASYNC_MODE_2
					esp_err_t ret = spi_device_queue_trans(MX_SPI_HANDLE_2_VSPI, &t, portMAX_DELAY);
					spi_device_get_trans_result(MX_SPI_HANDLE_2_VSPI, &t, 0);
				#else
					esp_err_t ret = spi_device_polling_transmit(MX_SPI_HANDLE_2_VSPI, &t);
				#endif

				if (ESP_OK == ret)
					return 1;		// Success
			}
			return 0;
		}

	#endif
#endif







//Check to see if hardware channel is used by another component
#if (MX_SPI_CHANNEL_X > 0)

    #if (MX_SPI_CHANNEL_X == 1)
    	#ifdef MX_SPI_CH1_IN_USE
    		#define MX_SPI_CHANNEL_IN_USE MX_SPI_CH1_IN_USE
    	#endif
	#endif
    #if (MX_SPI_CHANNEL_X == 2)
    	#ifdef MX_SPI_CH2_IN_USE
    		#define MX_SPI_CHANNEL_IN_USE MX_SPI_CH2_IN_USE
    	#endif
	#endif

#else

	//Software number of nops to acheive prescale delay
	MX_UINT16 MX_PRESCALE_VAR_X = ((unsigned long) MX_CLK_SPEED / (unsigned long) MX_SPI_PR_SCALE_X) / 2;

#endif



#ifdef MX_SPI_CHANNEL_IN_USE

	//if the channel is already in use then redirect the macro calls to the first instance of the channel
	#warning "SPI Hardware Channel has already been created by another instance. Relying on previous instance configuration."

#endif




CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Init_, (void))
{
	MX_UINT8 retVal = 1;

	#if (MX_SPI_CHANNEL_X == 0)

		SET_PORT_PIN (MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_PIN_X, 1);		// MOSI pin is default high
		GET_PORT_PIN (MX_SPI_MISO_PORT_X, MX_SPI_MISO_PIN_X);			// MISO pin is a input

		#if (MX_SPI_BMODE_X & 0x01)
			SET_PORT_PIN (MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X, 1);		// Clock pin is default high
		#else
			SET_PORT_PIN (MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X, 0);		// Clock pin is default low
		#endif

	#endif

	#if (MX_SPI_CHANNEL_X == 1)

		FC_CAL_SPI_Master_Init_HSPI();

	#endif

	#if (MX_SPI_CHANNEL_X == 2)

		FC_CAL_SPI_Master_Init_VSPI();

	#endif

	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_Master_Uninit_, (void))
{
	#if (MX_SPI_CHANNEL_X == 1)

		FC_CAL_SPI_Master_Uninit_HSPI();

	#endif

	#if (MX_SPI_CHANNEL_X == 2)

		FC_CAL_SPI_Master_Uninit_VSPI();

	#endif

	//Reset Pins to Inputs
	//GET_PORT_PIN (MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_PIN_X);
	//GET_PORT_PIN (MX_SPI_MISO_PORT_X, MX_SPI_MISO_PIN_X);
	//GET_PORT_PIN (MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X);
}




CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Byte_, (MX_UINT8 DataOut))
{
	MX_UINT8 retVal = 0;

	#if (MX_SPI_CHANNEL_X == 0)

		MX_UINT8 idx;
		MX_UINT16 i;
		for (idx = 0; idx < 8; idx++)
		{
			retVal = retVal << 1;

			//If mode 1 or 3, switch the clock
			#if ((MX_SPI_BMODE_X & 0x02) == 0x00)									//CKE = 0; (mode 1 or 3) Set SCK active before data
				#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
					SET_PORT_PIN(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,1);			//CKP = 0; (mode 1)
				#else
					SET_PORT_PIN(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,0);			//CKP = 1; (mode 3)
				#endif
			#endif

			//Data setup
			if (DataOut & 0x80)														//Test Data bit
			{
				SET_PORT_PIN(MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_PIN_X,1);				//Set SDO bit
			}
			else
			{
				SET_PORT_PIN (MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_PIN_X,0);				//Clear SDO bit
			}

			//Clock delay
			for (i=0; i<MX_PRESCALE_VAR_X; i++)
				nop();

			//Switch clock - high for modes 0 and 3; low for modes 1 and 2
			#if ((MX_SPI_BMODE_X & 0x02) == 0x02)									//CKE = 1; (mode 0 or 2)
				#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
					SET_PORT_PIN(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,1);			//CKP = 0; (mode 0)
				#else
					SET_PORT_PIN(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,0);			//CKP = 1; (mode 2)
				#endif
			#else
				#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
					SET_PORT_PIN(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,0);			//CKP = 0; (mode 1)
				#else
					SET_PORT_PIN(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,1);			//CKP = 1; (mode 3)
				#endif
			#endif

			//Sample at middle of data output?
			#if ((MX_SPI_BMODE_X & 0x04) == 0)										//Sample at the middle of period
				if(GET_PORT_PIN(MX_SPI_MISO_PORT_X, MX_SPI_MISO_PIN_X))
					retVal = retVal | 0x01;
				else
					retVal = retVal & 0xFE;
			#endif

			//Clock delay
			for (i=0; i<MX_PRESCALE_VAR_X; i++)
				nop();

			//If mode 0 or 2, switch the clock
			#if ((MX_SPI_BMODE_X & 0x02) == 0x02)									//CKE = 1; (mode 0 or 2)																//CKE = 0; Set SCK idle after data
				#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
					SET_PORT_PIN(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,0);			//CKP = 0; (mode 0)
				#else
					SET_PORT_PIN(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,1);			//CKP = 1; (mode 2)
				#endif
			#endif

			//Sample at end of data output?
			#if ((MX_SPI_BMODE_X & 0x04) == 0x04)									//Sample at the end of period
				if(GET_PORT_PIN(MX_SPI_MISO_PORT_X, MX_SPI_MISO_PIN_X))
					retVal = retVal | 0x01;
				else
					retVal = retVal & 0xFE;
			#endif

			DataOut = DataOut << 1;							//Move to next data bit
		}
	#endif

	#if (MX_SPI_CHANNEL_X == 1)

		retVal = FC_CAL_SPI_Master_Byte_HSPI(DataOut);

	#endif

	#if (MX_SPI_CHANNEL_X == 2)

		retVal = FC_CAL_SPI_Master_Byte_VSPI(DataOut);

	#endif

	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_SetPrescaler_, (MX_UINT16 Prescaler))
{
	#if (MX_SPI_CHANNEL_X == 1)

		FC_CAL_SPI_SetPrescaler_HSPI(Prescaler);

	#endif

	#if (MX_SPI_CHANNEL_X == 2)

		FC_CAL_SPI_SetPrescaler_VSPI(Prescaler);

	#endif
}




CALFUNCTION(void, FC_CAL_SPI_Slave_Init_, (void))
{

}

CALFUNCTION(void, FC_CAL_SPI_Slave_Uninit_, (void))
{

}

CALFUNCTION(void, FC_CAL_SPI_Slave_SetTxData_, (MX_UINT8 Data))
{

}

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Slave_GetRxData_, (void))
{
	return(0);
}


/**************************************************
	SPI Master Transaction based functions
**************************************************/

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_Init_,   (void))
{
	CALFUNCTION(, FC_CAL_SPI_Master_Init_, ());
	return 1;	// Success
}

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_,   (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length))
{
	#if (MX_SPI_CHANNEL_X == 0)
		if (Length > Size) return 0;
		MX_UINT16 n = 0;
		while (n < Length)
		{
			Buffer[n] = CALFUNCTION(, FC_CAL_SPI_Master_Byte_, (Buffer[n]));
			++n;
		}
		return 1;		// Success
	#endif

	#if (MX_SPI_CHANNEL_X == 1)
		return FC_CAL_SPI_Transaction_HSPI(Buffer, Size, Length);
	#endif

	#if (MX_SPI_CHANNEL_X == 2)
		return FC_CAL_SPI_Transaction_VSPI(Buffer, Size, Length);
	#endif
}

CALFUNCTION(void, FC_CAL_SPI_Transaction_Uninit_, (void))
{
	CALFUNCTION(, FC_CAL_SPI_Master_Uninit_, ());
}


//Define hardware channel usage
#if (MX_SPI_CHANNEL_X > 0)
	#if (MX_SPI_CHANNEL_X == 1)
		#define MX_SPI_CH1_IN_USE MX_SPI_NUM
	#endif
	#if (MX_SPI_CHANNEL_X == 2)
		#define MX_SPI_CH2_IN_USE MX_SPI_NUM
	#endif
#endif



#undef MX_SPI_CHANNEL_IN_USE
