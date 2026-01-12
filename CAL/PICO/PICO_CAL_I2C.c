// CRC: F9C65A77A483DDF22B438B7FEB8E3C81451B6760FECB07508D29EE770BB95F47FAE5D3E402C32CC04ABA32A404641158A0EB12570AC1D760C52C09BE1FDC3819077C96126F5B25C4711B8143522C2B693FED688B5101042743D51A2E61812DA0ECE6A0D04B9F9929BEA318921BABB285E74C6A7236905A5F72580068FB19B94C840829486ED92A94A3625630209D66546410A60C2A8FCDAEE1406CC6EE25266EBF50EFAE6FD9B9CE549D34A0D5AD11F33C104DE0368ED131307316B464B55473CDCE7F36EBE1FA1BACA9CE2DF1EA8436E42CFE37638C9748
// REVISION: 3.0
// GUID: 48CC7791-3B24-4255-856E-39987E84CBE6
// DATE: 23\08\2023
// DIR: CAL\PICO\PICO_CAL_I2C.c

/*********************************************************************
 *                  Flowcode CAL I2C File
 *
 * File: PICO_CAL_I2C.c
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
 * 020621 | LM | Created
 *
 */


#include "hardware/i2c.h"

#define MX_I2C_CHANNEL_X		CAL_APPEND(MX_I2C_CHANNEL_, MX_I2C_NUM)
#define MX_I2C_SDA_PIN_X		CAL_APPEND(MX_I2C_SDA_PIN_, MX_I2C_NUM)
#define MX_I2C_SDA_PORT_X		CAL_APPEND(MX_I2C_SDA_PORT_, MX_I2C_NUM)
#define MX_I2C_SDA_TRIS_X		CAL_APPEND(MX_I2C_SDA_TRIS_, MX_I2C_NUM)
#define MX_I2C_SCL_PIN_X		CAL_APPEND(MX_I2C_SCL_PIN_, MX_I2C_NUM)
#define MX_I2C_SCL_PORT_X		CAL_APPEND(MX_I2C_SCL_PORT_, MX_I2C_NUM)
#define MX_I2C_SCL_TRIS_X		CAL_APPEND(MX_I2C_SCL_TRIS_, MX_I2C_NUM)
#define MX_I2C_BMODE_X			CAL_APPEND(MX_I2C_BMODE_, MX_I2C_NUM)
#define MX_I2C_BAUD_X			CAL_APPEND(MX_I2C_BAUD_, MX_I2C_NUM)
#define MX_I2C_INT_X			CAL_APPEND(MX_I2C_INT_, MX_I2C_NUM)
#define MX_I2C_STOPDEL_X		CAL_APPEND(MX_I2C_STOPDEL_, MX_I2C_NUM)
#define MX_I2C_CLKSTRCH_X		CAL_APPEND(MX_I2C_CLOCKSTRETCHING_, MX_I2C_NUM)

#define MX_I2C_SDA_X			(MX_I2C_SDA_PORT_X + MX_I2C_SDA_PIN_X)
#define MX_I2C_SCL_X			(MX_I2C_SCL_PORT_X + MX_I2C_SCL_PIN_X)

#define I2C_MASTER_TX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */

#define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0                       /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                             /*!< I2C ack value */
#define NACK_VAL 0x1                            /*!< I2C nack value */

//Function Prototypes
CALFUNCTION(void, FC_CAL_I2C_Master_Init_, (void));
CALFUNCTION(void, FC_CAL_I2C_Master_Uninit_, (void));
CALFUNCTION(void, FC_CAL_I2C_Master_Start_, (void));
CALFUNCTION(void, FC_CAL_I2C_Master_Restart_, (void));
CALFUNCTION(void, FC_CAL_I2C_Master_Stop_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Master_TxByte_, (MX_UINT8 Data));
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Master_RxByte_, (MX_UINT8 Last));

CALFUNCTION(void, FC_CAL_I2C_Slave_Init_, (MX_UINT8 Address, MX_UINT8 Mask));
CALFUNCTION(void, FC_CAL_I2C_Slave_Uninit_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_TxByte_, (MX_UINT8 Data));
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_RxByte_, (MX_UINT8 Last));
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_Status_, (void));

CALFUNCTION(MX_UINT8, FC_CAL_I2C_Transaction_Init_,   (MX_UINT8 SlaveAddress));
CALFUNCTION(MX_UINT16, FC_CAL_I2C_Transaction_Read_,   (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length));
CALFUNCTION(MX_UINT16, FC_CAL_I2C_Transaction_Write_,  (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length));
CALFUNCTION(void,     FC_CAL_I2C_Transaction_Uninit_, (void));


//If software channel is enabled then define bit delay.
#if (MX_I2C_CHANNEL_X == 0)
  #ifndef MX_I2C_SW_DEL
	#define MX_I2C_SW_BAUD	((500000 / MX_I2C_BAUD_X)-1)

	#if (MX_I2C_SW_BAUD < 1)
		#define MX_I2C_DELAY	sleep_ms(1);	//delay_us(1);
	#else
		#define MX_I2C_DELAY	sleep_ms(1);	//delay_us(MX_I2C_SW_BAUD);
	#endif
  #endif

  //I2C Timeout - Avoids any blocking delays
  #define MX_I2C_TIMEOUT_X		CAL_APPEND(MX_I2C_TIMEOUT_, MX_I2C_NUM)
  MX_UINT16 MX_I2C_TIMEOUT_X;
#else

#endif


CALFUNCTION(void, FC_CAL_I2C_Master_Init_, (void))
{

	#if (MX_I2C_CHANNEL_X == 0)															//Use Master I2C Software
		GET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X);								//Configure SDA as Input
		GET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X);								//Configure SCL as Input
	#endif

	#if (MX_I2C_CHANNEL_X == 1)													//Use Master I2C Hardware 1

	#endif
}

CALFUNCTION(void, FC_CAL_I2C_Master_Uninit_, (void))
{

	#if (MX_I2C_CHANNEL_X == 0)																//Use Master I2C Software
		GET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X);			//Configure SDA as Input
		GET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X);				//Configure SCL as Input
	#endif

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1

	#endif
}

CALFUNCTION(void, FC_CAL_I2C_Master_Start_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)															//Use Master I2C Software
		GET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X);			//Make Sure SCL is Set
		GET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X);		//Make Sure SDA is Set
		MX_I2C_DELAY;																	//Small Delay
		SET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X, 0);			//Clear SDA
		MX_I2C_DELAY;																	//Small Delay
		SET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X, 0);			//Clear SCL
		//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR
	#endif

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1

	#endif
}

CALFUNCTION(void, FC_CAL_I2C_Master_Restart_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)															//Use Master I2C Software
		GET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X);		//Set SDA High
		MX_I2C_DELAY;
		GET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X);			//Set SCL High
		MX_I2C_DELAY;
		SET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X, 0);			//Set SDA Low
		MX_I2C_DELAY;
		SET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X, 0);			//Set SCL Low
		//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR
	#endif

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1

	#endif
}

CALFUNCTION(void, FC_CAL_I2C_Master_Stop_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)															//Use Master I2C Software
		SET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X, 0);			//Set SCL Low
		SET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X, 0);			//Set SDA Low
		MX_I2C_DELAY;
		GET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X);			//Set SCL High
		MX_I2C_DELAY;
		GET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X);		//Set SDA High
	#endif

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1

	#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_I2C_Master_TxByte_, (MX_UINT8 Data))
{
	#if (MX_I2C_CHANNEL_X == 0)												//Use Master I2C Software
		MX_UINT8 bit_mask;
		MX_UINT8 local_ack = 0;
		for(bit_mask=0x80;bit_mask;bit_mask=bit_mask>>1)
		{
			if(Data & bit_mask)
			{
				GET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X);	//Set SDA High
			}
			else
			{
				SET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X, 0);		//Set SDA Low
			}
			MX_I2C_DELAY;
			GET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X);			//Set SCL High
			MX_I2C_DELAY;

			#if (MX_I2C_CLKSTRCH_X == 1)
				MX_I2C_TIMEOUT_X = 0xFFFF;
				while (GET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X) == 0 && MX_I2C_TIMEOUT_X--);		//Wait for the clock to go high - Clock stretching.
			#endif

			SET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X, 0);			//Set SCL Low
			//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR
		}
		GET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X);			//Set SDA High
		MX_I2C_DELAY;
		GET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X);				//Set SCL High
		MX_I2C_DELAY;
		GET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X);
		if (GET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X))								//Get the Status Bit
			local_ack = 1;
		//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR
		SET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X, 0);				//Set SCL Low
		//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR
		return (local_ack);													//0 = Ack received : 1 = Ack not received
	#endif

	#if (MX_I2C_CHANNEL_X == 1)												//Use Master I2C Hardware 1

	#endif

  return 0;
}

CALFUNCTION(MX_UINT8, FC_CAL_I2C_Master_RxByte_, (MX_UINT8 Last))
{
	#if (MX_I2C_CHANNEL_X == 0)												//Use Master I2C Software
		MX_UINT8 bit_mask;
		MX_UINT8 Data = 0;
		GET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X);			//Set SDA High
		MX_I2C_DELAY;
		for(bit_mask=0x80;bit_mask;bit_mask=bit_mask>>1)
		{
			GET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X);			//Set SCL High
			MX_I2C_DELAY;

			#if (MX_I2C_CLKSTRCH_X == 1)
				MX_I2C_TIMEOUT_X = 0xFFFF;
				while (GET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X) == 0 && MX_I2C_TIMEOUT_X--);		//Wait for the clock to go high - Clock stretching.
			#endif

			GET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X);
			if(GET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X))	//Read Incoming Bit
				Data = Data | bit_mask;														//Add data to variable
			SET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X, 0);			//Set SCL Low
			MX_I2C_DELAY;																	//Small Delay
		}
		if (Last)																		//Acknowledge?
		{
			GET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X);	//Send Nack
		}
		else
		{
			SET_PORT_PIN(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X, 0);		//Send Ack
		}
		MX_I2C_DELAY;
		GET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X);			//Set SCL High
		MX_I2C_DELAY;
		SET_PORT_PIN(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X, 0);			//Set SCL Low
		//MX_I2C_DELAY;																	//Small Delay //Removed 050613 - BR
		return (Data);
	#endif

	#if (MX_I2C_CHANNEL_X == 1)						//Use Master I2C Hardware 1

	#endif

  return 0;
}



/**************************************************
	I2C Slave functions
**************************************************/

CALFUNCTION(void, FC_CAL_I2C_Slave_Init_, (MX_UINT8 Address, MX_UINT8 Mask))
{
	#if (MX_I2C_CHANNEL_X == 1)
	#endif
}

// Returns I2C status byte
// Bit 0 = 1 Indicates address/data byte available in the buffer to read
// Bit 5 = 1 Indicates that the last byte received or transmitted was data (else address)
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_Status_, (void))
{
	MX_UINT8 status = 0;
	#if (MX_I2C_CHANNEL_X == 1)
	#endif
	return status;
}

// Disables the I2C peripheral
CALFUNCTION(void, FC_CAL_I2C_Slave_Uninit_, (void))
{
	#if (MX_I2C_CHANNEL_X == 1)
	#endif
}

// Loads the Data byte into the shift buffer and releases SCL ready for sending
// Returns Master Ack/Nak (0=Ack=More, 1=Nak=Last)
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_TxByte_, (MX_UINT8 Data))
{
	MX_UINT8 Result = 1;	// default to Nak

	#if (MX_I2C_CHANNEL_X == 1)
	#endif

	return Result;
}

// Returns the byte from the shift buffer
// and sends Ack or Nak (0=Ack=More, 1=Nak=Last)
// nb. First check FC_CAL_I2C_Slave_Status() & 1
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_RxByte_, (MX_UINT8 Last))
{
	MX_UINT8 Data = 0;
	#if (MX_I2C_CHANNEL_X == 1)
	#endif
	return Data;			// return the received data
}




/**************************************************
	Master Transaction functions
**************************************************/

#define MX_I2C_ADDRESS_X		CAL_APPEND(MX_I2C_ADDRESS_, MX_I2C_NUM)
#define MX_I2C_INIT_X			CAL_APPEND(MX_I2C_INIT_, MX_I2C_NUM)

static MX_UINT8 MX_I2C_ADDRESS_X;
static MX_UINT8 MX_I2C_INIT_X = 0;


CALFUNCTION(MX_UINT8, FC_CAL_I2C_Transaction_Init_,   (MX_UINT8 SlaveAddress))
{
	MX_I2C_ADDRESS_X = SlaveAddress;

	if (MX_I2C_INIT_X == 0)
	{
		MX_I2C_INIT_X = 1;

		#if (MX_I2C_CHANNEL_X == 0)
			CALFUNCTION(, FC_CAL_I2C_Master_Init_, ());
			return 1;	// Success
		#elif (MX_I2C_CHANNEL_X == 1)
			i2c_init(i2c0, MX_I2C_BAUD_X);
			gpio_set_function(MX_I2C_SDA_X, GPIO_FUNC_I2C);
			gpio_set_function(MX_I2C_SCL_X, GPIO_FUNC_I2C);
			gpio_pull_up(MX_I2C_SDA_X);
			gpio_pull_up(MX_I2C_SCL_X);
			return 1;	// Success
		#elif (MX_I2C_CHANNEL_X == 2)
			i2c_init(i2c1, MX_I2C_BAUD_X);
			gpio_set_function(MX_I2C_SDA_X, GPIO_FUNC_I2C);
			gpio_set_function(MX_I2C_SCL_X, GPIO_FUNC_I2C);
			gpio_pull_up(MX_I2C_SDA_X);
			gpio_pull_up(MX_I2C_SCL_X);
			return 1;	// Success
		#endif
	}
}

CALFUNCTION(MX_UINT16, FC_CAL_I2C_Transaction_Read_,   (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length))
{
	MX_UINT16 n = 0;
	if (Length > Size) return 0;

	#if (MX_I2C_CHANNEL_X == 0)
		CALFUNCTION( , FC_CAL_I2C_Master_Start_, ());
		if ( CALFUNCTION( , FC_CAL_I2C_Master_TxByte_, ((MX_I2C_ADDRESS_X<<1)|1)))
			return 0;
		while (n < Length)
		{
			Buffer[n] = CALFUNCTION(, FC_CAL_I2C_Master_RxByte_, ((n+1==Length)?1:0));
			++n;
		}
		CALFUNCTION( , FC_CAL_I2C_Master_Stop_, ());
		return n;
	#elif (MX_I2C_CHANNEL_X == 1)
		n = i2c_read_blocking(i2c0, MX_I2C_ADDRESS_X, Buffer, Length, false);
		return n;
	#elif (MX_I2C_CHANNEL_X == 2)
		n = i2c_read_blocking(i2c1, MX_I2C_ADDRESS_X, Buffer, Length, false);
		return n;
	#endif
}

CALFUNCTION(MX_UINT16, FC_CAL_I2C_Transaction_Write_,  (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length))
{
	MX_UINT16 n = 0;
	MX_UINT8 sendStop = 1;
	if (Length & 0x8000)
	{
		Length = Length & 0x7FFF;
		sendStop = 0;
	}

	if (Length > Size) return 0;

	#if (MX_I2C_CHANNEL_X == 0)
		CALFUNCTION( , FC_CAL_I2C_Master_Start_, ());
		if ( CALFUNCTION( , FC_CAL_I2C_Master_TxByte_, (MX_I2C_ADDRESS_X<<1)))
			return 0;
		while (n < Length)
		{
			if ( CALFUNCTION( , FC_CAL_I2C_Master_TxByte_, (Buffer[n])))
				break;
			++n;
		}
		if (sendStop)
			CALFUNCTION( , FC_CAL_I2C_Master_Stop_, ());
		return n;
	#elif (MX_I2C_CHANNEL_X == 1)
		n = i2c_write_blocking(i2c0, MX_I2C_ADDRESS_X, Buffer, Length, !(sendStop));
		return n;
	#elif (MX_I2C_CHANNEL_X == 2)
		n = i2c_write_blocking(i2c1, MX_I2C_ADDRESS_X, Buffer, Length, !(sendStop));
		return n;
	#endif
}

CALFUNCTION(void,     FC_CAL_I2C_Transaction_Uninit_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)
		CALFUNCTION(, FC_CAL_I2C_Master_Uninit_, ());
	#elif (MX_I2C_CHANNEL_X == 1)
		i2c_deinit(i2c0);
	#elif (MX_I2C_CHANNEL_X == 2)
		i2c_deinit(i2c1);
	#endif
}

