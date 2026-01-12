// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A0780D0B864F5D1F680368647E196A8AAC052D894661F77C09299921D5FE9C78D27800D711032B6231711B8143522C2B69297610E3A16DCD691E1230A38BF4F05B64034FE6C8597E8CC8848D55B555C47418A81B2FA7108E40C76477FE95B2251FF3D0BBFC068C136B76A5F59F26B78BC64EEAD85445179A95F0D13E7CB7608A6CCEA6805CA6DD7F3D549D34A0D5AD11F3780C35AEB9D3E584D5104AFFE3F5D5A806CC568D528F6BD859A43852AB18B119835CEFDAC0E534C9
// REVISION: 11.0
// GUID: 334E8DDA-F9B4-469B-83AC-6BEAC0FE585C
// DATE: 03\11\2023
// DIR: CAL\ESP\ESP_CAL_I2C.c
/*********************************************************************
 *                  Flowcode CAL I2C File
 *
 * File: ESP_CAL_I2C.c
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
 * 130718 | BR | Created
 * 060720 | LM | ESP32 integration
 *
 */



#include "esp_log.h"
#include "driver/i2c.h"


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
#define MX_I2C_SDA_RP_X			CAL_APPEND(MX_I2C_SDA_RP_, MX_I2C_NUM)
#define MX_I2C_SCL_RP_X			CAL_APPEND(MX_I2C_SCL_RP_, MX_I2C_NUM)

#define MX_I2C_PRESCALE_VAR_X	CAL_APPEND(i2c_prescale_, MX_I2C_NUM)


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

  MX_UINT16 MX_I2C_PRESCALE_VAR_X = ((unsigned long) MX_CLK_SPEED / (unsigned long) MX_I2C_BAUD_X) / 2;

  #define MX_I2C_DELAY	for (MX_UINT16 i=0; i<MX_I2C_PRESCALE_VAR_X; i++)  nop();

  //I2C Timeout - Avoids any blocking delays
  #define MX_I2C_TIMEOUT_X		CAL_APPEND(MX_I2C_TIMEOUT_, MX_I2C_NUM)
  MX_UINT16 MX_I2C_TIMEOUT_X;

#else

	#if (MX_I2C_CHANNEL_X == 1)
		#ifndef MX_I2C_HARDWARE_DEFINITIONS_CH1
			#define MX_I2C_HARDWARE_DEFINITIONS_CH1

			static esp_err_t MX_ESP_I2C1_ERROR = 0;
			i2c_cmd_handle_t MX_I2C1_HANDLE = 0;
			MX_UINT8 Mx_I2c_1_init = 0;

			MX_UINT8 FC_CAL_I2C1_Master_Init()
			{
				if (Mx_I2c_1_init == 0)
				{
					int i2c_master_port = 0;
					i2c_config_t conf = {0};
					conf.mode = I2C_MODE_MASTER;
					conf.sda_io_num = MX_I2C_SDA_RP_X;
					conf.scl_io_num = MX_I2C_SCL_RP_X;
					conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
					conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
					conf.master.clk_speed = MX_I2C_BAUD_X;

					if (ESP_OK == (MX_ESP_I2C1_ERROR = i2c_param_config(i2c_master_port, &conf)))
					{
						if (ESP_OK == (MX_ESP_I2C1_ERROR = i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0)))
						{
							Mx_I2c_1_init = 1;
							return 1;
						}
					}
					return 0;
				}

				return 1;
			}


			MX_UINT16 FC_CAL_I2C1_Master_Read(MX_UINT8 Address, MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length)
			{
				if (Length > Size) return 0;

				MX_I2C1_HANDLE = i2c_cmd_link_create();
				i2c_master_start(MX_I2C1_HANDLE);
				i2c_master_write_byte(MX_I2C1_HANDLE, (Address << 1) | I2C_MASTER_READ, ACK_CHECK_EN);
				if (Length > 1)
				{
					i2c_master_read(MX_I2C1_HANDLE, Buffer, Length - 1, ACK_VAL);
				}
				i2c_master_read_byte(MX_I2C1_HANDLE, Buffer + Length - 1, NACK_VAL);
				i2c_master_stop(MX_I2C1_HANDLE);
				MX_ESP_I2C1_ERROR = i2c_master_cmd_begin(0, MX_I2C1_HANDLE, 100 / portTICK_PERIOD_MS);
				i2c_cmd_link_delete(MX_I2C1_HANDLE);
				return (MX_ESP_I2C1_ERROR == ESP_OK)?Length:0;
			}


			MX_UINT16 FC_CAL_I2C1_Master_Write(MX_UINT8 Address, MX_UINT8 sendStop, MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length)
			{
				MX_I2C1_HANDLE = i2c_cmd_link_create();
				i2c_master_start(MX_I2C1_HANDLE);
				i2c_master_write_byte(MX_I2C1_HANDLE, (Address << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
				i2c_master_write(MX_I2C1_HANDLE, Buffer, Length, ACK_CHECK_EN);
				if (sendStop)
					i2c_master_stop(MX_I2C1_HANDLE);
				MX_ESP_I2C1_ERROR = i2c_master_cmd_begin(0, MX_I2C1_HANDLE, 100 / portTICK_PERIOD_MS);
				i2c_cmd_link_delete(MX_I2C1_HANDLE);
				return (MX_ESP_I2C1_ERROR == ESP_OK)?Length:0;
			}


		#endif
	#endif

	#if (MX_I2C_CHANNEL_X == 2)
		#ifndef MX_I2C_HARDWARE_DEFINITIONS_CH2
			#define MX_I2C_HARDWARE_DEFINITIONS_CH2

			static esp_err_t MX_ESP_I2C2_ERROR = 0;
			i2c_cmd_handle_t MX_I2C2_HANDLE = 0;
			MX_UINT8 Mx_I2c_2_init = 0;

			MX_UINT8 FC_CAL_I2C2_Master_Init()
			{
				if (Mx_I2c_2_init == 0)
				{
					int i2c_master_port = 1;
					i2c_config_t conf = {0};
					conf.mode = I2C_MODE_MASTER;
					conf.sda_io_num = MX_I2C_SDA_RP_X;
					conf.scl_io_num = MX_I2C_SCL_RP_X;
					conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
					conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
					conf.master.clk_speed = MX_I2C_BAUD_X;

					if (ESP_OK == (MX_ESP_I2C2_ERROR = i2c_param_config(i2c_master_port, &conf)))
					{
						if (ESP_OK == (MX_ESP_I2C2_ERROR = i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0)))
						{
							Mx_I2c_2_init = 1;
							return 1;
						}
					}
					return 0;
				}

				return 1;
			}


			MX_UINT16 FC_CAL_I2C2_Master_Read(MX_UINT8 Address, MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length)
			{
				if (Length > Size) return 0;

				MX_I2C2_HANDLE = i2c_cmd_link_create();
				i2c_master_start(MX_I2C2_HANDLE);
				i2c_master_write_byte(MX_I2C2_HANDLE, (Address << 1) | I2C_MASTER_READ, ACK_CHECK_EN);
				if (Length > 1)
				{
					i2c_master_read(MX_I2C2_HANDLE, Buffer, Length - 1, ACK_VAL);
				}
				i2c_master_read_byte(MX_I2C2_HANDLE, Buffer + Length - 1, NACK_VAL);
				i2c_master_stop(MX_I2C2_HANDLE);
				MX_ESP_I2C2_ERROR = i2c_master_cmd_begin(1, MX_I2C2_HANDLE, 100 / portTICK_PERIOD_MS);
				i2c_cmd_link_delete(MX_I2C2_HANDLE);
				return (MX_ESP_I2C2_ERROR == ESP_OK)?Length:0;
			}


			MX_UINT16 FC_CAL_I2C2_Master_Write(MX_UINT8 Address, MX_UINT8 sendStop, MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length)
			{
				MX_I2C2_HANDLE = i2c_cmd_link_create();
				i2c_master_start(MX_I2C2_HANDLE);
				i2c_master_write_byte(MX_I2C2_HANDLE, (Address << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
				i2c_master_write(MX_I2C2_HANDLE, Buffer, Length, ACK_CHECK_EN);
				if (sendStop)
					i2c_master_stop(MX_I2C2_HANDLE);
				MX_ESP_I2C2_ERROR = i2c_master_cmd_begin(1, MX_I2C2_HANDLE, 100 / portTICK_PERIOD_MS);
				i2c_cmd_link_delete(MX_I2C2_HANDLE);
				return (MX_ESP_I2C2_ERROR == ESP_OK)?Length:0;
			}

		#endif
	#endif

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
		#endif

		#if (MX_I2C_CHANNEL_X == 1)
			return FC_CAL_I2C1_Master_Init();
		#endif

		#if (MX_I2C_CHANNEL_X == 2)
			return FC_CAL_I2C2_Master_Init();
		#endif
	}

	//Already initialised
	return 1;
}

CALFUNCTION(MX_UINT16, FC_CAL_I2C_Transaction_Read_,   (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length))
{
	if (Length > Size) return 0;

	#if (MX_I2C_CHANNEL_X == 0)
		MX_UINT16 n = 0;
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
	#endif

	#if (MX_I2C_CHANNEL_X == 1)
		return FC_CAL_I2C1_Master_Read(MX_I2C_ADDRESS_X, Buffer, Size, Length);
	#endif

	#if (MX_I2C_CHANNEL_X == 2)
		return FC_CAL_I2C2_Master_Read(MX_I2C_ADDRESS_X, Buffer, Size, Length);
	#endif

	return 0;
}

CALFUNCTION(MX_UINT16, FC_CAL_I2C_Transaction_Write_,  (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length))
{
	MX_UINT8 sendStop = 1;
	if (Length & 0x8000)
	{
		Length = Length & 0x7FFF;
		sendStop = 0;
	}

	if (Length > Size) return 0;

	#if (MX_I2C_CHANNEL_X == 0)
		MX_UINT16 n = 0;
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
	#endif

	#if (MX_I2C_CHANNEL_X == 1)
		return FC_CAL_I2C1_Master_Write(MX_I2C_ADDRESS_X, sendStop, Buffer, Size, Length);
	#endif

	#if (MX_I2C_CHANNEL_X == 2)
		return FC_CAL_I2C2_Master_Write(MX_I2C_ADDRESS_X, sendStop, Buffer, Size, Length);
	#endif

	return 0;
}

CALFUNCTION(void,     FC_CAL_I2C_Transaction_Uninit_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)
		CALFUNCTION(, FC_CAL_I2C_Master_Uninit_, ());
	#else

	#endif
}
