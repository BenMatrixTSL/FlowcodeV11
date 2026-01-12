// CRC: F9C65A77A483DDF22B438B7FEB8E3C81451B6760FECB07508D29EE770BB95F4762C5EB630D1FECDDCBEF1BA7CAEA61529A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF578CBF28E3E301C0C801A7D47A5D9EB97AEC5CFE66327754B4876DAC9BD86CA0CF74C7159331A14C5D0535631A1616CA69ECE3F550DC77CD07C738EDCB3BF7DDE07D2AC2731B454D9B0D6D616A34823F5CEA6805CA6DD7F3D549D34A0D5AD11F3DEC0D88F66D2C4DB1DF132FA00A8F486568AD284118FAF482EABD4ED9561D2123431AF726C5DC381
// REVISION: 1.0
// GUID: 4657287A-2D9C-44B6-8DDD-CCFC64F45CE4
// DATE: 08\08\2022
// DIR: CAL\PICO\PICO_CAL_SPI.c

/*********************************************************************
 *                  Flowcode CAL SPI File
 *
 * File: PICO_CAL_SPI.c
 *
 * (c) 2021 Matrix TSL.
 * http://www.matrixtsl.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
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
 * 010621 | LM | Created
 *
 */

#include <string.h>
#include "hardware/spi.h"

#define porta 0
#define portb 32

#define MX_SPI_REF_X			CAL_APPEND(MX_SPI_REF, MX_SPI_NUM)
#define MX_SPI_CHANNEL_X		CAL_APPEND(MX_SPI_CHANNEL_, MX_SPI_NUM)
#define MX_SPI_MOSI_PIN_X		CAL_APPEND(MX_SPI_MOSI_PIN_, MX_SPI_NUM)
#define MX_SPI_MOSI_PORT_X		CAL_APPEND(MX_SPI_MOSI_PORT_, MX_SPI_NUM)
//#define MX_SPI_MOSI_TRIS_X		CAL_APPEND(MX_SPI_MOSI_TRIS_, MX_SPI_NUM)
#define MX_SPI_MISO_PIN_X		CAL_APPEND(MX_SPI_MISO_PIN_, MX_SPI_NUM)
#define MX_SPI_MISO_PORT_X		CAL_APPEND(MX_SPI_MISO_PORT_, MX_SPI_NUM)
//#define MX_SPI_MISO_TRIS_X		CAL_APPEND(MX_SPI_MISO_TRIS_, MX_SPI_NUM)
#define MX_SPI_SCK_PIN_X		CAL_APPEND(MX_SPI_SCK_PIN_, MX_SPI_NUM)
#define MX_SPI_SCK_PORT_X		CAL_APPEND(MX_SPI_SCK_PORT_, MX_SPI_NUM)
//#define MX_SPI_SCK_TRIS_X		CAL_APPEND(MX_SPI_SCK_TRIS_, MX_SPI_NUM)
#define MX_SPI_CS_PIN_X			CAL_APPEND(MX_SPI_CS_PIN_, MX_SPI_NUM)
#define MX_SPI_CS_PORT_X		CAL_APPEND(MX_SPI_CS_PORT_, MX_SPI_NUM)
//#define MX_SPI_CS_TRIS_X		CAL_APPEND(MX_SPI_CS_TRIS_, MX_SPI_NUM)
#define MX_SPI_BMODE_X			CAL_APPEND(MX_SPI_BMODE_, MX_SPI_NUM)
#define MX_SPI_PR_SCALE_X		CAL_APPEND(MX_SPI_PR_SCALE_, MX_SPI_NUM)
#define MX_SPI_PO_SCALE_X		CAL_APPEND(MX_SPI_PO_SCALE_, MX_SPI_NUM)
#define MX_SPI_INT_X			CAL_APPEND(MX_SPI_INT_, MX_SPI_NUM)
#define MX_SPI_HANDLE_X			CAL_APPEND(spiHandle_, MX_SPI_NUM)
//#define MX_SPI_CBF_X			CAL_APPEND(mx_pre_transfer_callback_, MX_SPI_NUM)

#define MX_SPI_MOSI_X			(MX_SPI_MOSI_PORT_X + MX_SPI_MOSI_PIN_X)
#define MX_SPI_MISO_X			(MX_SPI_MISO_PORT_X + MX_SPI_MISO_PIN_X)
#define MX_SPI_SCK_X			(MX_SPI_SCK_PORT_X + MX_SPI_SCK_PIN_X)
#define MX_SPI_CS_X				(MX_SPI_CS_PORT_X + MX_SPI_CS_PIN_X)


#define MX_PRESCALE_VAR_X		CAL_APPEND(prescale_, MX_SPI_NUM)
// MX_SPI_PR_SCALE_X is the actual bit rate in this ESP implementation,
// so this maths no longer applies here.
// This needs a re-visit if we want to implement speed setting in software mode
MX_UINT8 MX_PRESCALE_VAR_X = 0; // (MX_SPI_PR_SCALE_X / 2) - 1;


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

	#elif (MX_SPI_CHANNEL_X == 1)

		spi_init(spi0, MX_SPI_PR_SCALE_X);
		spi_set_format(spi0, 8, (MX_SPI_BMODE_X & 1)? SPI_CPOL_1: SPI_CPOL_0, (MX_SPI_BMODE_X & 2)? SPI_CPHA_0: SPI_CPHA_1, SPI_MSB_FIRST);
		gpio_set_function(MX_SPI_MOSI_X, GPIO_FUNC_SPI);
		gpio_set_function(MX_SPI_MISO_X, GPIO_FUNC_SPI);
		gpio_set_function(MX_SPI_SCK_X, GPIO_FUNC_SPI);

		// might be able to add auto CS later
	    // gpio_init(MX_SPI_CS_X);
		// gpio_set_dir(MX_SPI_CS_X, GPIO_OUT);
		// gpio_put(MX_SPI_CS_X, 1);

	#elif (MX_SPI_CHANNEL_X == 2)

		spi_init(spi1, MX_SPI_PR_SCALE_X);
		spi_set_format(spi1, 8, (MX_SPI_BMODE_X & 1)? SPI_CPOL_1: SPI_CPOL_0, (MX_SPI_BMODE_X & 2)? SPI_CPHA_0: SPI_CPHA_1, SPI_MSB_FIRST);
		gpio_set_function(MX_SPI_MOSI_X, GPIO_FUNC_SPI);
		gpio_set_function(MX_SPI_MISO_X, GPIO_FUNC_SPI);
		gpio_set_function(MX_SPI_SCK_X, GPIO_FUNC_SPI);

		// might be able to add auto CS later
	    // gpio_init(MX_SPI_CS_X);
		// gpio_set_dir(MX_SPI_CS_X, GPIO_OUT);
		// gpio_put(MX_SPI_CS_X, 1);

   	#endif

	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_Master_Uninit_, (void))
{
	#if (MX_SPI_CHANNEL_X == 1)
		spi_deinit(spi0);
	#elif (MX_SPI_CHANNEL_X == 2)
		spi_deinit(spi1);
	#endif

	//Reset Pins to Inputs
//	gpio_init(MX_SPI_MOSI_X);
//	gpio_init(MX_SPI_MISO_X);
//	gpio_init(MX_SPI_SCK_X);

// These will need to do the init ?
	GET_PORT_PIN (MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_PIN_X);
	GET_PORT_PIN (MX_SPI_MISO_PORT_X, MX_SPI_MISO_PIN_X);
	GET_PORT_PIN (MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X);
}


CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Byte_, (MX_UINT8 DataOut))
{
	MX_UINT8 retVal = 0;

	#if (MX_SPI_CHANNEL_X == 0)

		MX_UINT16 idx, i;
		for (idx = 0; idx < 8; idx++)
		{
			retVal = retVal << 1;

			//If mode 1 or 3, switch the clock
			#if ((MX_SPI_BMODE_X & 0x02) == 0x00)									//CKE = 0; (mode 1 or 3) Set SCK active before data
				#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
					FCP_SET_NODDR(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,1);			//CKP = 0; (mode 1)
				#else
					FCP_SET_NODDR(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,0);			//CKP = 1; (mode 3)
				#endif
			#endif

			//Data setup
			if (DataOut & 0x80)														//Test Data bit
			{
				FCP_SET_NODDR(MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_PIN_X,1);				//Set SDO bit
			}
			else
			{
				FCP_SET_NODDR (MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_PIN_X,0);				//Clear SDO bit
			}

			//Clock delay
			for (i=0; i<MX_PRESCALE_VAR_X; i++);

			//Switch clock - high for modes 0 and 3; low for modes 1 and 2
			#if ((MX_SPI_BMODE_X & 0x02) == 0x02)									//CKE = 1; (mode 0 or 2)
				#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
					FCP_SET_NODDR(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,1);			//CKP = 0; (mode 0)
				#else
					FCP_SET_NODDR(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,0);			//CKP = 1; (mode 2)
				#endif
			#else
				#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
					FCP_SET_NODDR(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,0);			//CKP = 0; (mode 1)
				#else
					FCP_SET_NODDR(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,1);			//CKP = 1; (mode 3)
				#endif
			#endif

			//Sample at middle of data output?
			#if ((MX_SPI_BMODE_X & 0x04) == 0)										//Sample at the middle of period
				if(FCP_GET_NODDR(MX_SPI_MISO_PORT_X, MX_SPI_MISO_PIN_X))
					retVal = retVal | 0x01;
				else
					retVal = retVal & 0xFE;
			#endif

			//Clock delay
			for (i=0; i<MX_PRESCALE_VAR_X; i++);

			//If mode 0 or 2, switch the clock
			#if ((MX_SPI_BMODE_X & 0x02) == 0x02)									//CKE = 1; (mode 0 or 2)																//CKE = 0; Set SCK idle after data
				#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
					FCP_SET_NODDR(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,0);			//CKP = 0; (mode 0)
				#else
					FCP_SET_NODDR(MX_SPI_SCK_PORT_X, MX_SPI_SCK_PIN_X,1);			//CKP = 1; (mode 2)
				#endif
			#endif

			//Sample at end of data output?
			#if ((MX_SPI_BMODE_X & 0x04) == 0x04)									//Sample at the end of period
				if(FCP_GET_NODDR(MX_SPI_MISO_PORT_X, MX_SPI_MISO_PIN_X))
					retVal = retVal | 0x01;
				else
					retVal = retVal & 0xFE;
			#endif

			DataOut = DataOut << 1;							//Move to next data bit
		}

	#elif (MX_SPI_CHANNEL_X == 1)

		spi_write_read_blocking(spi0, (const uint8_t *) &DataOut, (uint8_t *) &retVal, 1);

	#elif (MX_SPI_CHANNEL_X == 2)

		spi_write_read_blocking(spi1, (const uint8_t *) &DataOut, (uint8_t *) &retVal, 1);

	#endif

	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_SetPrescaler_, (MX_UINT16 Prescaler))
{
	#if (MX_SPI_CHANNEL_X == 0)

		MX_PRESCALE_VAR_X = Prescaler;

	#elif (MX_SPI_CHANNEL_X == 1)

		spi_set_baudrate(spi0, (unsigned long) Prescaler * 100000UL);

	#elif (MX_SPI_CHANNEL_X == 2)

		spi_set_baudrate(spi1, (unsigned long) Prescaler * 100000UL);

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

	#elif (MX_SPI_CHANNEL_X == 1)

		MX_UINT8* ReadBuffer = malloc(Length);
		if (ReadBuffer)
		{
			spi_write_read_blocking(spi0, (const uint8_t *)Buffer, (uint8_t *)ReadBuffer, Length);
			memcpy(Buffer, ReadBuffer, Length);
			free(ReadBuffer);
			return 1;
		}
		return 0;

	#elif (MX_SPI_CHANNEL_X == 2)

		MX_UINT8* ReadBuffer = malloc(Length);
		if (ReadBuffer)
		{
			spi_write_read_blocking(spi1, (const uint8_t *)Buffer, (uint8_t *)ReadBuffer, Length);
			memcpy(Buffer, ReadBuffer, Length);
			free(ReadBuffer);
			return 1;
		}
		return 0;

	#endif
}

CALFUNCTION(void, FC_CAL_SPI_Transaction_Uninit_, (void))
{
	CALFUNCTION(, FC_CAL_SPI_Master_Uninit_, ());
}



#undef MX_SPI_PR_SCALE_HW
