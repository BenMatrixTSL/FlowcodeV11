// CRC: 34358081B117C27F7D8358E612878F8E5F343B66182D417818220CB9C07676CF780D0B864F5D1F680368647E196A8AAC9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5A3DA20DBA7393059FFC547AC0829FDE0976359ED4828E7E9C88A3E4AB6BC360FD6D59FC0A17FF180F45F85F1F411D457D5C415D855A048D0B7D27986E7317BF7243163DE520002ADB87190F13842289F0742DBDBADA4B874549D34A0D5AD11F350D62C8B0D0F4A7FBF1296CBE12F619225E3266FD95E5F3EE00AF8598B7CA62D1079227E43D7E189
// REVISION: 1.0
// GUID: DDBE6CAA-9AA1-48B0-82A2-0737484E6F62
// DATE: 08\08\2022
// DIR: CAL\RPI\RPI_CAL_I2C.c
/*********************************************************************
 *                  Flowcode CAL I2C File
 *
 * File: RPI_CAL_I2C.c
 *
 * (c) 2011-2018 Matrix TSL
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
 * 050118 | LM | Created from PIC CAL
 */



#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define MX_I2C_CHANNEL_X		CAL_APPEND(MX_I2C_CHANNEL_, MX_I2C_NUM)
#define MX_I2C_SDA_PIN_X		CAL_APPEND(MX_I2C_SDA_PIN_, MX_I2C_NUM)
#define MX_I2C_SDA_PORT_X		CAL_APPEND(MX_I2C_SDA_PORT_, MX_I2C_NUM)
//#define MX_I2C_SDA_TRIS_X		CAL_APPEND(MX_I2C_SDA_TRIS_, MX_I2C_NUM)
#define MX_I2C_SCL_PIN_X		CAL_APPEND(MX_I2C_SCL_PIN_, MX_I2C_NUM)
#define MX_I2C_SCL_PORT_X		CAL_APPEND(MX_I2C_SCL_PORT_, MX_I2C_NUM)
//#define MX_I2C_SCL_TRIS_X		CAL_APPEND(MX_I2C_SCL_TRIS_, MX_I2C_NUM)
#define MX_I2C_BMODE_X			CAL_APPEND(MX_I2C_BMODE_, MX_I2C_NUM)
#define MX_I2C_BAUD_X			CAL_APPEND(MX_I2C_BAUD_, MX_I2C_NUM)
#define MX_I2C_INT_X			CAL_APPEND(MX_I2C_INT_, MX_I2C_NUM)
#define MX_I2C_STOPDEL_X		CAL_APPEND(MX_I2C_STOPDEL_, MX_I2C_NUM)
#define MX_I2C_CLKSTRCH_X		CAL_APPEND(MX_I2C_CLOCKSTRETCHING_, MX_I2C_NUM)


// Now for some pin mangling for BL0036 :O) ...
#if   (MX_I2C_SCL_PORT_X == PORTA)
	#if   (MX_I2C_SCL_PIN_X == 0)
		#define MX_I2C_SCL_GPIO_X	MX_PORTA0_GPIO
	#elif (MX_I2C_SCL_PIN_X == 1)
		#define MX_I2C_SCL_GPIO_X	MX_PORTA1_GPIO
	#elif (MX_I2C_SCL_PIN_X == 2)
		#define MX_I2C_SCL_GPIO_X	MX_PORTA2_GPIO
	#elif (MX_I2C_SCL_PIN_X == 3)
		#define MX_I2C_SCL_GPIO_X	MX_PORTA3_GPIO
	#elif (MX_I2C_SCL_PIN_X == 4)
		#define MX_I2C_SCL_GPIO_X	MX_PORTA4_GPIO
	#elif (MX_I2C_SCL_PIN_X == 5)
		#define MX_I2C_SCL_GPIO_X	MX_PORTA5_GPIO
	#endif
#elif (MX_I2C_SCL_PORT_X == PORTB)
	#if   (MX_I2C_SCL_PIN_X == 0)
		#define MX_I2C_SCL_GPIO_X	MX_PORTB0_GPIO
	#elif (MX_I2C_SCL_PIN_X == 1)
		#define MX_I2C_SCL_GPIO_X	MX_PORTB1_GPIO
	#elif (MX_I2C_SCL_PIN_X == 2)
		#define MX_I2C_SCL_GPIO_X	MX_PORTB2_GPIO
	#elif (MX_I2C_SCL_PIN_X == 3)
		#define MX_I2C_SCL_GPIO_X	MX_PORTB3_GPIO
	#elif (MX_I2C_SCL_PIN_X == 4)
		#define MX_I2C_SCL_GPIO_X	MX_PORTB4_GPIO
	#elif (MX_I2C_SCL_PIN_X == 5)
		#define MX_I2C_SCL_GPIO_X	MX_PORTB5_GPIO
	#elif (MX_I2C_SCL_PIN_X == 6)
		#define MX_I2C_SCL_GPIO_X	MX_PORTB6_GPIO
	#elif (MX_I2C_SCL_PIN_X == 7)
		#define MX_I2C_SCL_GPIO_X	MX_PORTB7_GPIO
	#endif
#elif (MX_I2C_SCL_PORT_X == PORTC)
	#if   (MX_I2C_SCL_PIN_X == 0)
		#define MX_I2C_SCL_GPIO_X	MX_PORTC0_GPIO
	#elif (MX_I2C_SCL_PIN_X == 1)
		#define MX_I2C_SCL_GPIO_X	MX_PORTC1_GPIO
	#elif (MX_I2C_SCL_PIN_X == 2)
		#define MX_I2C_SCL_GPIO_X	MX_PORTC2_GPIO
	#elif (MX_I2C_SCL_PIN_X == 3)
		#define MX_I2C_SCL_GPIO_X	MX_PORTC3_GPIO
	#elif (MX_I2C_SCL_PIN_X == 4)
		#define MX_I2C_SCL_GPIO_X	MX_PORTC4_GPIO
	#elif (MX_I2C_SCL_PIN_X == 5)
		#define MX_I2C_SCL_GPIO_X	MX_PORTC5_GPIO
	#elif (MX_I2C_SCL_PIN_X == 6)
		#define MX_I2C_SCL_GPIO_X	MX_PORTC6_GPIO
	#elif (MX_I2C_SCL_PIN_X == 7)
		#define MX_I2C_SCL_GPIO_X	MX_PORTC7_GPIO
	#endif
#elif (MX_I2C_SCL_PORT_X == PORTD)
	#if   (MX_I2C_SCL_PIN_X == 0)
		#define MX_I2C_SCL_GPIO_X	MX_PORTD0_GPIO
	#elif (MX_I2C_SCL_PIN_X == 1)
		#define MX_I2C_SCL_GPIO_X	MX_PORTD1_GPIO
	#elif (MX_I2C_SCL_PIN_X == 2)
		#define MX_I2C_SCL_GPIO_X	MX_PORTD2_GPIO
	#elif (MX_I2C_SCL_PIN_X == 3)
		#define MX_I2C_SCL_GPIO_X	MX_PORTD3_GPIO
	#elif (MX_I2C_SCL_PIN_X == 4)
		#define MX_I2C_SCL_GPIO_X	MX_PORTD4_GPIO
	#elif (MX_I2C_SCL_PIN_X == 5)
		#define MX_I2C_SCL_GPIO_X	MX_PORTD5_GPIO
	#endif
#endif
#ifndef MX_I2C_SCL_GPIO_X
	// Nothing defined for that Port/Pin
	// Or we have GPIO numbers anyway (Port G)
	#define MX_I2C_SCL_GPIO_X MX_I2C_SCL_PIN_X
#endif

#if   (MX_I2C_SDA_PORT_X == PORTA)
	#if   (MX_I2C_SDA_PIN_X == 0)
		#define MX_I2C_SDA_GPIO_X	MX_PORTA0_GPIO
	#elif (MX_I2C_SDA_PIN_X == 1)
		#define MX_I2C_SDA_GPIO_X	MX_PORTA1_GPIO
	#elif (MX_I2C_SDA_PIN_X == 2)
		#define MX_I2C_SDA_GPIO_X	MX_PORTA2_GPIO
	#elif (MX_I2C_SDA_PIN_X == 3)
		#define MX_I2C_SDA_GPIO_X	MX_PORTA3_GPIO
	#elif (MX_I2C_SDA_PIN_X == 4)
		#define MX_I2C_SDA_GPIO_X	MX_PORTA4_GPIO
	#elif (MX_I2C_SDA_PIN_X == 5)
		#define MX_I2C_SDA_GPIO_X	MX_PORTA5_GPIO
	#endif
#elif (MX_I2C_SDA_PORT_X == PORTB)
	#if   (MX_I2C_SDA_PIN_X == 0)
		#define MX_I2C_SDA_GPIO_X	MX_PORTB0_GPIO
	#elif (MX_I2C_SDA_PIN_X == 1)
		#define MX_I2C_SDA_GPIO_X	MX_PORTB1_GPIO
	#elif (MX_I2C_SDA_PIN_X == 2)
		#define MX_I2C_SDA_GPIO_X	MX_PORTB2_GPIO
	#elif (MX_I2C_SDA_PIN_X == 3)
		#define MX_I2C_SDA_GPIO_X	MX_PORTB3_GPIO
	#elif (MX_I2C_SDA_PIN_X == 4)
		#define MX_I2C_SDA_GPIO_X	MX_PORTB4_GPIO
	#elif (MX_I2C_SDA_PIN_X == 5)
		#define MX_I2C_SDA_GPIO_X	MX_PORTB5_GPIO
	#elif (MX_I2C_SDA_PIN_X == 6)
		#define MX_I2C_SDA_GPIO_X	MX_PORTB6_GPIO
	#elif (MX_I2C_SDA_PIN_X == 7)
		#define MX_I2C_SDA_GPIO_X	MX_PORTB7_GPIO
	#endif
#elif (MX_I2C_SDA_PORT_X == PORTC)
	#if   (MX_I2C_SDA_PIN_X == 0)
		#define MX_I2C_SDA_GPIO_X	MX_PORTC0_GPIO
	#elif (MX_I2C_SDA_PIN_X == 1)
		#define MX_I2C_SDA_GPIO_X	MX_PORTC1_GPIO
	#elif (MX_I2C_SDA_PIN_X == 2)
		#define MX_I2C_SDA_GPIO_X	MX_PORTC2_GPIO
	#elif (MX_I2C_SDA_PIN_X == 3)
		#define MX_I2C_SDA_GPIO_X	MX_PORTC3_GPIO
	#elif (MX_I2C_SDA_PIN_X == 4)
		#define MX_I2C_SDA_GPIO_X	MX_PORTC4_GPIO
	#elif (MX_I2C_SDA_PIN_X == 5)
		#define MX_I2C_SDA_GPIO_X	MX_PORTC5_GPIO
	#elif (MX_I2C_SDA_PIN_X == 6)
		#define MX_I2C_SDA_GPIO_X	MX_PORTC6_GPIO
	#elif (MX_I2C_SDA_PIN_X == 7)
		#define MX_I2C_SDA_GPIO_X	MX_PORTC7_GPIO
	#endif
#elif (MX_I2C_SDA_PORT_X == PORTD)
	#if   (MX_I2C_SDA_PIN_X == 0)
		#define MX_I2C_SDA_GPIO_X	MX_PORTD0_GPIO
	#elif (MX_I2C_SDA_PIN_X == 1)
		#define MX_I2C_SDA_GPIO_X	MX_PORTD1_GPIO
	#elif (MX_I2C_SDA_PIN_X == 2)
		#define MX_I2C_SDA_GPIO_X	MX_PORTD2_GPIO
	#elif (MX_I2C_SDA_PIN_X == 3)
		#define MX_I2C_SDA_GPIO_X	MX_PORTD3_GPIO
	#elif (MX_I2C_SDA_PIN_X == 4)
		#define MX_I2C_SDA_GPIO_X	MX_PORTD4_GPIO
	#elif (MX_I2C_SDA_PIN_X == 5)
		#define MX_I2C_SDA_GPIO_X	MX_PORTD5_GPIO
	#endif
#endif
#ifndef MX_I2C_SDA_GPIO_X
	// Nothing defined for that Port/Pin
	// Or we have GPIO numbers anyway (Port G)
	#define MX_I2C_SDA_GPIO_X MX_I2C_SDA_PIN_X
#endif


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


#if (MX_I2C_CHANNEL_X > 0)

  #define MX_I2C_HW_BAUD	((MX_CLK_SPEED / 4) / MX_I2C_BAUD_X) - 1

  //Check for rollover
  #if MX_I2C_HW_BAUD > 255
  	#undef MX_I2C_HW_BAUD
  	#define MX_I2C_HW_BAUD 255
  #endif

#else
	#define MX_I2C_DELAY	{volatile int x=100; while(x) --x;}

	//I2C Timeout - Avoids any blocking delays
	#define MX_I2C_TIMEOUT_X		CAL_APPEND(MX_I2C_TIMEOUT_, MX_I2C_NUM)
	MX_UINT16 MX_I2C_TIMEOUT_X;
#endif



CALFUNCTION(void, FC_CAL_I2C_Master_Init_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)				// Use Master I2C Software
		MX_GPIO_IN(MX_I2C_SDA_GPIO_X);		// Configure SDA as Input
		MX_GPIO_IN(MX_I2C_SCL_GPIO_X);		// Configure SCL as Input
	#endif
}

CALFUNCTION(void, FC_CAL_I2C_Master_Uninit_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)				// Use Master I2C Software
		MX_GPIO_IN(MX_I2C_SDA_GPIO_X);		// Configure SDA as Input
		MX_GPIO_IN(MX_I2C_SCL_GPIO_X);		// Configure SCL as Input
	#endif
}

CALFUNCTION(void, FC_CAL_I2C_Master_Start_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)				// Use Master I2C Software
		MX_GPIO_IN(MX_I2C_SDA_GPIO_X);		// Configure SDA as Input
		MX_GPIO_IN(MX_I2C_SCL_GPIO_X);		// Configure SCL as Input
		MX_I2C_DELAY;
		FC_CAL_GPIO_CLR_DDR(MX_I2C_SDA_GPIO_X);	// Clear SDA
		MX_I2C_DELAY;
		FC_CAL_GPIO_CLR_DDR(MX_I2C_SCL_GPIO_X);	// Clear SCL
		MX_I2C_DELAY;						// Delay or not delay?
	#endif
}

CALFUNCTION(void, FC_CAL_I2C_Master_Restart_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)				// Use Master I2C Software
		MX_GPIO_IN(MX_I2C_SDA_GPIO_X);		// Set SDA High
		MX_I2C_DELAY;
		MX_GPIO_IN(MX_I2C_SCL_GPIO_X);		// Set SCL High
		MX_I2C_DELAY;
		FC_CAL_GPIO_CLR_DDR(MX_I2C_SDA_GPIO_X);	// Set SDA Low
		MX_I2C_DELAY;
		FC_CAL_GPIO_CLR_DDR(MX_I2C_SCL_GPIO_X);  // Set SCL Low
		MX_I2C_DELAY;						// Delay or not delay?
	#endif
}

CALFUNCTION(void, FC_CAL_I2C_Master_Stop_, (void))
{
	#if (MX_I2C_CHANNEL_X == 0)				// Use Master I2C Software
		FC_CAL_GPIO_CLR_DDR(MX_I2C_SCL_GPIO_X);	// Set SCL Low
		FC_CAL_GPIO_CLR_DDR(MX_I2C_SDA_GPIO_X);	// Set SDA Low
		MX_I2C_DELAY;
		MX_GPIO_IN(MX_I2C_SCL_GPIO_X);		//Set SCL High
		MX_I2C_DELAY;
		MX_GPIO_IN(MX_I2C_SDA_GPIO_X);		//Set SDA High
	#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_I2C_Master_TxByte_, (MX_UINT8 Data))
{
		MX_UINT8 local_ack = 1;						// Default to Nak
	#if (MX_I2C_CHANNEL_X == 0)						// Use Master I2C Software
		MX_UINT8 bit_mask;
		for (bit_mask=0x80;bit_mask;bit_mask=bit_mask>>1)
		{
			if (Data & bit_mask)
			{
				MX_GPIO_IN(MX_I2C_SDA_GPIO_X);		// Set SDA High
			}
			else
			{
				FC_CAL_GPIO_CLR_DDR(MX_I2C_SDA_GPIO_X);	// Set SDA Low
			}
			MX_I2C_DELAY;
			MX_GPIO_IN(MX_I2C_SCL_GPIO_X);			// Set SCL High
			MX_I2C_DELAY;

			#if (MX_I2C_CLKSTRCH_X == 1)
				MX_I2C_TIMEOUT_X = 0xFFFF;
				while (FC_CAL_GPIO_GET(MX_I2C_SCL_GPIO_X) == 0 && MX_I2C_TIMEOUT_X--);	// Wait for the clock to go high - Clock stretching.
			#endif

			FC_CAL_GPIO_CLR_DDR(MX_I2C_SCL_GPIO_X);		// Set SCL Low
			MX_I2C_DELAY;							// Delay or not delay?
		}
		MX_GPIO_IN(MX_I2C_SDA_GPIO_X);			// Set SDA High
		MX_I2C_DELAY;
		MX_GPIO_IN(MX_I2C_SCL_GPIO_X);			// Set SCL High
		MX_I2C_DELAY;
		if (!FC_CAL_GPIO_GET(MX_I2C_SDA_GPIO_X))		// Get the Status Bit
			local_ack = 0;
		MX_I2C_DELAY;							// Delay or not delay?
		FC_CAL_GPIO_CLR_DDR(MX_I2C_SCL_GPIO_X);		// Set SCL Low
		MX_I2C_DELAY;							// Delay or not delay?
	#endif
		return (local_ack);						// 0 = Ack received : 1 = Ack not received
}

CALFUNCTION(MX_UINT8, FC_CAL_I2C_Master_RxByte_, (MX_UINT8 Last))
{
		MX_UINT8 Data = 0;
	#if (MX_I2C_CHANNEL_X == 0)					// Use Master I2C Software
		MX_UINT8 bit_mask;
		MX_GPIO_IN(MX_I2C_SDA_GPIO_X);			// Set SDA High
		MX_I2C_DELAY;
		for(bit_mask=0x80;bit_mask;bit_mask=bit_mask>>1)
		{
			MX_GPIO_IN(MX_I2C_SCL_GPIO_X);		// Set SCL High
			MX_I2C_DELAY;

			#if (MX_I2C_CLKSTRCH_X == 1)
				MX_I2C_TIMEOUT_X = 0xFFFF;
				while (FC_CAL_GPIO_GET(MX_I2C_SCL_GPIO_X) == 0 && MX_I2C_TIMEOUT_X--);		//Wait for the clock to go high - Clock stretching.
			#endif

			if(FC_CAL_GPIO_GET(MX_I2C_SDA_GPIO_X))	// Read Incoming Bit
				Data = Data | bit_mask;			// Add data to variable
			FC_CAL_GPIO_CLR_DDR(MX_I2C_SCL_GPIO_X);	// Set SCL Low
			MX_I2C_DELAY;
		}
		if (Last)								// Acknowledge?
		{
			MX_GPIO_IN(MX_I2C_SDA_GPIO_X);		// Send Nack
		}
		else
		{
			FC_CAL_GPIO_CLR_DDR(MX_I2C_SDA_GPIO_X);	// Send Ack
		}
		MX_I2C_DELAY;
		MX_GPIO_IN(MX_I2C_SCL_GPIO_X);			// Set SCL High
		MX_I2C_DELAY;
		FC_CAL_GPIO_CLR_DDR(MX_I2C_SCL_GPIO_X);		// Set SCL Low
	#endif
		return (Data);
}



/***********************************************
Slave functions, not supported on Raspberry Pi
***********************************************/

CALFUNCTION(void, FC_CAL_I2C_Slave_Init_, (MX_UINT8 Address, MX_UINT8 Mask))
{
}

// Returns I2C status byte (SSPSTAT = SMP CKE D/A P S R/W UA BF)
// Bit 0 = 1 Indicates address/data byte available in the buffer to read
// Bit 5 = 1 Indicates that the last byte received or transmitted was data (else address)
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_Status_, (void))
{
	return 0;
}

// Disables the I2C peripheral
CALFUNCTION(void, FC_CAL_I2C_Slave_Uninit_, (void))
{
}

// Loads the Data byte into the shift buffer and releases SCL ready for sending
// Returns Master Ack/Nak (0=Ack=More, 1=Nak=Last)
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_TxByte_, (MX_UINT8 Data))
{
	return 0;
}

// Returns the byte from the shift buffer
// and sends Ack or Nak (0=Ack=More, 1=Nak=Last)
// nb. First check FC_CAL_I2C_Slave_Status() & 1
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Slave_RxByte_, (MX_UINT8 Last))
{
	return 0;
}


/**************************************************
Master Transaction functions (for Raspberry Pi)
**************************************************/
#if (MX_I2C_CHANNEL_X == 0)
#define MX_I2C_ADDRESS_X		CAL_APPEND(MX_I2C_ADDRESS_, MX_I2C_NUM)
MX_UINT8 MX_I2C_ADDRESS_X;
#elif (MX_I2C_CHANNEL_X == 1)
int fd_i2c1 = -1;
#elif (MX_I2C_CHANNEL_X == 2)
int fd_i2c2 = -1;
#endif

CALFUNCTION(MX_UINT8, FC_CAL_I2C_Transaction_Init_,   (MX_UINT8 SlaveAddress))
{
#if (MX_I2C_CHANNEL_X == 0)
	MX_I2C_ADDRESS_X = SlaveAddress;
	CALFUNCTION(, FC_CAL_I2C_Master_Init_, ());
	return 1;	// Success

#elif (MX_I2C_CHANNEL_X == 1)
	if (fd_i2c1 != -1)
		return 0;	// Fail (already open)
	MX_GPIO_ALT(MX_I2C_SCL_GPIO_X, 0);
	MX_GPIO_ALT(MX_I2C_SDA_GPIO_X, 0);
	#if (MX_I2C_SDA_GPIO_X == 0)
	// Pi 1 B Rev 1 only
	if ((fd_i2c1 = open((char*)"/dev/i2c-0", O_RDWR)) < 0)
		return 0;	// Fail
	#else
	if ((fd_i2c1 = open((char*)"/dev/i2c-1", O_RDWR)) < 0)
		return 0;	// Fail
	#endif
	if (ioctl(fd_i2c1, I2C_SLAVE_FORCE, SlaveAddress) < 0)
	{
		close(fd_i2c1);
		fd_i2c1 = -1;
		return 0;	// Fail
	}
	return 1;	// Success

#elif (MX_I2C_CHANNEL_X == 2)
	// Channel 2 not supported as standard on RPi
	if (fd_i2c2 != -1)
		return 0;	// Fail (already open)
	MX_GPIO_ALT(MX_I2C_SCL_GPIO_X, 0);
	MX_GPIO_ALT(MX_I2C_SDA_GPIO_X, 0);
	if ((fd_i2c2 = open((char*)"/dev/i2c-2", O_RDWR)) < 0)
		return 0;	// Fail
	if (ioctl(fd_i2c2, I2C_SLAVE_FORCE, SlaveAddress) < 0)
	{
		close(fd_i2c2);
		fd_i2c2 = -1;
		return 0;	// Fail
	}
	return 1;	// Success
#else
	return 0;	// Fail
#endif
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

#elif (MX_I2C_CHANNEL_X == 1)
	// Check that we have a valid handle i.e. the channel has been opened correctly
	if (fd_i2c1 < 0) return 0;
	// Return number of bytes read, caller should check that this matches requested Length
	return read(fd_i2c1, Buffer, Length);

#elif (MX_I2C_CHANNEL_X == 2)
	// Check that we have a valid handle i.e. the channel has been opened correctly
	if (fd_i2c2 < 0) return 0;
	// Return number of bytes read, caller should check that this matches requested Length
	return read(fd_i2c2, Buffer, Length);
#else
	return 0;
#endif
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

#elif (MX_I2C_CHANNEL_X == 1)
	// Check that we have a valid handle i.e. the channel has been opened correctly
	if (fd_i2c1 < 0) return 0;
	// Return number of bytes written, caller should check that this matches requested Length
	return write(fd_i2c1, Buffer, Length);

#elif (MX_I2C_CHANNEL_X == 2)
	// Check that we have a valid handle i.e. the channel has been opened correctly
	if (fd_i2c2 < 0) return 0;
	// Return number of bytes written, caller should check that this matches requested Length
	return write(fd_i2c2, Buffer, Length);
#else
	return 0;
#endif
}

CALFUNCTION(void,     FC_CAL_I2C_Transaction_Uninit_, (void))
{
#if (MX_I2C_CHANNEL_X == 0)
	CALFUNCTION(, FC_CAL_I2C_Master_Uninit_, ());

#elif (MX_I2C_CHANNEL_X == 1)
	close(fd_i2c1);
	fd_i2c1 = -1;

#elif (MX_I2C_CHANNEL_X == 2)
	close(fd_i2c2);
	fd_i2c2 = -1;
#endif
}

#undef MX_I2C_SCL_GPIO_X
#undef MX_I2C_SDA_GPIO_X

