// CRC: 34358081B117C27F7D8358E612878F8E5F343B66182D417818220CB9C07676CF478F634975A712457CCBE7D4DA9E6C8340897D2E0FE9ECE9A383EF668AF0E4CBA3521E13BBF2FDECA4D1C56CD1580BF581DBCC7987CEDFD5D375FBF2FA4EC0F0DF538ED64DAE2E3551C90242524EDF467EEC26FC009293EB9F269D5C6356956265F077361C63DFA0C667977C8EE0E7E7918192987088AC5D697E93606D45252D52FEF7BDA8D89EC8549D34A0D5AD11F3C75C76CCF97A6FDF064C052F2CD5FD5982336A404576D6492FFEDCC693330B04B4FCFC5DE34EB9BE
// REVISION: 2.0
// GUID: 2DEDFEB9-50B5-4B3C-83C8-97EEB545CD54
// DATE: 19\08\2022
// DIR: CAL\RPI\RPI_CAL_UART.c
/*********************************************************************
 *                  Flowcode CAL UART File
 *
 * File: RPI_CAL_UART.c
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
 * 010911 | LM | Created from PIC
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

/*********************************************************************
By default, on Raspberry Pis equipped with the wireless/Bluetooth module
(Raspberry Pi 3 and Raspberry Pi Zero W),
the PL011 UART is connected to the BT module,
while the mini UART is used for Linux console output.
On all other models the PL011 is used for the Linux console output.

In Linux device terms, by default, /dev/ttyS0 refers to the mini UART,
and /dev/ttyAMA0 refers to the PL011.
The primary UART is that assigned to the Linux console,
which depends on the Raspberry Pi model as described above,
and can be accessed via /dev/serial0.

The Linux console can be re-enabled by adding enable_uart=1 to config.txt.
This also fixes the core_freq to 250Mhz
(unless force_turbo is set, when it will fixed to 400Mhz),
which means that the UART baud rate stays consistent.

In a default install of Raspbian, the primary UART (serial0)
is assigned to the Linux console.
Using the serial port for other purposes requires
this default behaviour to be changed.

To manually change the settings,
edit the kernel command line with sudo nano /boot/cmdline.txt.
Find the console entry that refers to the serial0 device,
and remove it, including the baud rate setting.
*********************************************************************/

//Dynamic function naming based on defines and index number
#define MX_UART_CHANNEL_X	CAL_APPEND(MX_UART_CHANNEL_, MX_UART_NUM)
#define MX_UART_TX_EN_X		CAL_APPEND(MX_UART_UseTX_, MX_UART_NUM)
#define MX_UART_TX_PIN_X	CAL_APPEND(MX_UART_TX_PIN_, MX_UART_NUM)
#define MX_UART_TX_PORT_X	CAL_APPEND(MX_UART_TX_PORT_, MX_UART_NUM)
//#define MX_UART_TX_TRIS_X	CAL_APPEND(MX_UART_TX_TRIS_, MX_UART_NUM)
#define MX_UART_RX_EN_X		CAL_APPEND(MX_UART_UseRX_, MX_UART_NUM)
#define MX_UART_RX_PIN_X	CAL_APPEND(MX_UART_RX_PIN_, MX_UART_NUM)
#define MX_UART_RX_PORT_X	CAL_APPEND(MX_UART_RX_PORT_, MX_UART_NUM)
//#define MX_UART_RX_TRIS_X	CAL_APPEND(MX_UART_RX_TRIS_, MX_UART_NUM)
//#define MX_UART_FLOWEN_X	CAL_APPEND(MX_UART_FLOWEN_, MX_UART_NUM)
//#define MX_UART_CTS_PIN_X	CAL_APPEND(MX_UART_CTS_PIN_, MX_UART_NUM)
//#define MX_UART_CTS_PORT_X	CAL_APPEND(MX_UART_CTS_PORT_, MX_UART_NUM)
//#define MX_UART_CTS_TRIS_X	CAL_APPEND(MX_UART_CTS_TRIS_, MX_UART_NUM)
//#define MX_UART_RTS_PIN_X	CAL_APPEND(MX_UART_RTS_PIN_, MX_UART_NUM)
//#define MX_UART_RTS_PORT_X	CAL_APPEND(MX_UART_RTS_PORT_, MX_UART_NUM)
//#define MX_UART_RTS_TRIS_X	CAL_APPEND(MX_UART_RTS_TRIS_, MX_UART_NUM)
//#define MX_UART_DBITS_X		CAL_APPEND(MX_UART_DBITS_, MX_UART_NUM)
#define MX_UART_RETURN_X	CAL_APPEND(MX_UART_RETURN_, MX_UART_NUM)
#define MX_UART_ECHO_X		CAL_APPEND(MX_UART_ECHO_, MX_UART_NUM)
//#define MX_UART_INT_X		CAL_APPEND(MX_UART_INT_, MX_UART_NUM)
#define MX_UART_BAUD_X		CAL_APPEND(MX_UART_BAUD_, MX_UART_NUM)

//Component Definitions
#define UART_STATUS_LOOP	0
#define UART_STATUS_TIMEOUT	1
#define UART_STATUS_RXBYTE	2

#ifdef MX_UART_IOC_SPEED_X
#undef MX_UART_IOC_SPEED_X
#endif
#if   (MX_UART_BAUD_X == 1200)
	#define MX_SPI_IOC_SPEED_X	B1200
#elif (MX_UART_BAUD_X == 2400)
	#define MX_SPI_IOC_SPEED_X	B2400
#elif (MX_UART_BAUD_X == 4800)
	#define MX_SPI_IOC_SPEED_X	B4800
#elif (MX_UART_BAUD_X == 9600)
	#define MX_SPI_IOC_SPEED_X	B9600
#elif (MX_UART_BAUD_X == 19200)
	#define MX_SPI_IOC_SPEED_X	B19200
#elif (MX_UART_BAUD_X == 38400)
	#define MX_SPI_IOC_SPEED_X	B38400
#elif (MX_UART_BAUD_X == 57600)
	#define MX_SPI_IOC_SPEED_X	B57600
#elif (MX_UART_BAUD_X == 115200)
	#define MX_SPI_IOC_SPEED_X	B115200
#elif (MX_UART_BAUD_X == 250000)
	#define MX_SPI_IOC_SPEED_X	B230400
#endif


//Function Prototypes
CALFUNCTION(void, FC_CAL_UART_Init_, (void));
CALFUNCTION(void, FC_CAL_UART_Uninit_, (void));
CALFUNCTION(void, FC_CAL_UART_Send_, (MX_UINT16 nChar));
CALFUNCTION(MX_SINT16, FC_CAL_UART_Receive_, (MX_UINT8 nTimeout));
CALFUNCTION(void, FC_CAL_UART_Delay_, (void));
CALFUNCTION(void, FC_CAL_UART_UpdateBaud_, (MX_UINT8 new_baud));


#if (MX_UART_CHANNEL_X == 0)

#elif (MX_UART_CHANNEL_X == 1)
int fd_uart1 = -1;
#elif (MX_UART_CHANNEL_X == 2)
int fd_uart2 = -1;
#elif (MX_UART_CHANNEL_X == 3)
int fd_uart3 = -1;
#elif (MX_UART_CHANNEL_X == 4)
int fd_uart4 = -1;
#elif (MX_UART_CHANNEL_X == 5)
int fd_uart5 = -1;
#endif


//Peripheral Functions
CALFUNCTION(void, FC_CAL_UART_Init_, (void))
{
	#if (MX_UART_CHANNEL_X == 0)
		#error "Cannot guarantee timings accurate enough to support this mode"

	#elif (MX_UART_CHANNEL_X == 1)
	if (fd_uart1 < 0)
	{
		if ((fd_uart1 = open((char*)"/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY)) >= 0)
		{
			struct termios config;
			tcgetattr(fd_uart1, &config);
			config.c_cflag = MX_SPI_IOC_SPEED_X | CS8 | CLOCAL | CREAD;
			config.c_iflag = IGNPAR;
			config.c_oflag = 0;
			#if (MX_UART_ECHO_X == 1)
				config.c_lflag = ECHO;
			#else
				config.c_lflag = 0;
			#endif
			tcflush(fd_uart1, TCIFLUSH);
			tcsetattr(fd_uart1, TCSANOW, &config);
		}
	}

	#elif (MX_UART_CHANNEL_X == 2)
	if (fd_uart2 < 0)
	{
		if ((fd_uart2 = open((char*)"/dev/serial1", O_RDWR | O_NOCTTY | O_NDELAY)) >= 0)
		{
			struct termios config;
			tcgetattr(fd_uart2, &config);
			config.c_cflag = MX_SPI_IOC_SPEED_X | CS8 | CLOCAL | CREAD;
			config.c_iflag = IGNPAR;
			config.c_oflag = 0;
			#if (MX_UART_ECHO_X == 1)
				config.c_lflag = ECHO;
			#else
				config.c_lflag = 0;
			#endif
			tcflush(fd_uart2, TCIFLUSH);
			tcsetattr(fd_uart2, TCSANOW, &config);
		}
	}

	#elif (MX_UART_CHANNEL_X == 3)
	if (fd_uart3 < 0)
	{
		if ((fd_uart3 = open((char*)"/dev/serial2", O_RDWR | O_NOCTTY | O_NDELAY)) >= 0)
		{
			struct termios config;
			tcgetattr(fd_uart3, &config);
			config.c_cflag = MX_SPI_IOC_SPEED_X | CS8 | CLOCAL | CREAD;
			config.c_iflag = IGNPAR;
			config.c_oflag = 0;
			#if (MX_UART_ECHO_X == 1)
				config.c_lflag = ECHO;
			#else
				config.c_lflag = 0;
			#endif
			tcflush(fd_uart3, TCIFLUSH);
			tcsetattr(fd_uart3, TCSANOW, &config);
		}
	}

	#elif (MX_UART_CHANNEL_X == 4)
	if (fd_uart4 < 0)
	{
		if ((fd_uart4 = open((char*)"/dev/serial3", O_RDWR | O_NOCTTY | O_NDELAY)) >= 0)
		{
			struct termios config;
			tcgetattr(fd_uart4, &config);
			config.c_cflag = MX_SPI_IOC_SPEED_X | CS8 | CLOCAL | CREAD;
			config.c_iflag = IGNPAR;
			config.c_oflag = 0;
			#if (MX_UART_ECHO_X == 1)
				config.c_lflag = ECHO;
			#else
				config.c_lflag = 0;
			#endif
			tcflush(fd_uart4, TCIFLUSH);
			tcsetattr(fd_uart4, TCSANOW, &config);
		}
	}

	#elif (MX_UART_CHANNEL_X == 5)
	if (fd_uart5 < 0)
	{
		if ((fd_uart5 = open((char*)"/dev/serial4", O_RDWR | O_NOCTTY | O_NDELAY)) >= 0)
		{
			struct termios config;
			tcgetattr(fd_uart5, &config);
			config.c_cflag = MX_SPI_IOC_SPEED_X | CS8 | CLOCAL | CREAD;
			config.c_iflag = IGNPAR;
			config.c_oflag = 0;
			#if (MX_UART_ECHO_X == 1)
				config.c_lflag = ECHO;
			#else
				config.c_lflag = 0;
			#endif
			tcflush(fd_uart5, TCIFLUSH);
			tcsetattr(fd_uart5, TCSANOW, &config);
		}
	}

	#endif
}


CALFUNCTION(void, FC_CAL_UART_Uninit_, (void))
{
	#if (MX_UART_CHANNEL_X == 0)
		// Cannot guarantee timings accurate enough to support this mode

	#elif (MX_UART_CHANNEL_X == 1)
		if (fd_uart1 >= 0) close(fd_uart1);
		fd_uart1 = -1;

	#elif (MX_UART_CHANNEL_X == 2)
		if (fd_uart2 >= 0) close(fd_uart2);
		fd_uart2 = -1;

	#elif (MX_UART_CHANNEL_X == 3)
		if (fd_uart3 >= 0) close(fd_uart3);
		fd_uart3 = -1;

	#elif (MX_UART_CHANNEL_X == 4)
		if (fd_uart4 >= 0) close(fd_uart4);
		fd_uart4 = -1;

	#elif (MX_UART_CHANNEL_X == 5)
		if (fd_uart5 >= 0) close(fd_uart5);
		fd_uart5 = -1;

	#endif
}


CALFUNCTION(void, FC_CAL_UART_Send_, (MX_UINT16 nChar))
{
	#if (MX_UART_TX_EN_X == 1)

		#if (MX_UART_CHANNEL_X == 0)
			// Cannot guarantee timings accurate enough to support this mode

		#elif (MX_UART_CHANNEL_X == 1)
		if (fd_uart1 >= 0)
		{
			MX_UINT8 b[2];
			b[0] = nChar;			// I don't think the Linux driver supports 9 bit characters
			write(fd_uart1, b, 1);	// Also, we don't have a mechanism for returning errors
		}
		#elif (MX_UART_CHANNEL_X == 2)
		if (fd_uart2 >= 0)
		{
			MX_UINT8 b[2];
			b[0] = nChar;			// I don't think the Linux driver supports 9 bit characters
			write(fd_uart2, b, 1);	// Also, we don't have a mechanism for returning errors
		}
		#elif (MX_UART_CHANNEL_X == 3)
		if (fd_uart3 >= 0)
		{
			MX_UINT8 b[2];
			b[0] = nChar;			// I don't think the Linux driver supports 9 bit characters
			write(fd_uart3, b, 1);	// Also, we don't have a mechanism for returning errors
		}
		#elif (MX_UART_CHANNEL_X == 4)
		if (fd_uart4 >= 0)
		{
			MX_UINT8 b[2];
			b[0] = nChar;			// I don't think the Linux driver supports 9 bit characters
			write(fd_uart4, b, 1);	// Also, we don't have a mechanism for returning errors
		}
		#elif (MX_UART_CHANNEL_X == 5)
		if (fd_uart5 >= 0)
		{
			MX_UINT8 b[2];
			b[0] = nChar;			// I don't think the Linux driver supports 9 bit characters
			write(fd_uart5, b, 1);	// Also, we don't have a mechanism for returning errors
		}
		#endif

	#endif
}


CALFUNCTION(MX_SINT16, FC_CAL_UART_Receive_, (MX_UINT8 nTimeout))
{
	#if (MX_UART_RETURN_X == 1)
		MX_UINT16 retVal = 512;
	#else
		MX_UINT8 retVal = 255;
	#endif

	#if (MX_UART_RX_EN_X == 1)

		#if (MX_UART_CHANNEL_X > 0)

			MX_UINT8 delay1 = 0;
			MX_UINT8 bWaitForever = 0;
			MX_UINT8 rxStatus = UART_STATUS_LOOP;
			MX_UINT8 buffer[2];

			if (nTimeout == 255)
				bWaitForever = 1;

			while (rxStatus == UART_STATUS_LOOP)
			{
				if (bWaitForever == 0)
				{
					if (nTimeout == 0)
					{
						rxStatus = UART_STATUS_TIMEOUT;
					}
					else
					{
						// Small delay 1/100 of nTimeout resolution, which is 1mS?
						mx_delay_u(10);
						if(++delay1 == 100)
						{
							nTimeout = nTimeout - 1;
							delay1 = 0;
						}
					}
				}

				#if (MX_UART_CHANNEL_X == 1)
				if (fd_uart1 >= 0)
				{
					if (read(fd_uart1, (void*)buffer, 1) == 1)
					{
						rxStatus = UART_STATUS_RXBYTE;
					}
				}

				#elif (MX_UART_CHANNEL_X == 2)
				if (fd_uart2 >= 0)
				{
					if (read(fd_uart2, (void*)buffer, 1) == 1)
					{
						rxStatus = UART_STATUS_RXBYTE;
					}
				}

				#elif (MX_UART_CHANNEL_X == 3)
				if (fd_uart3 >= 0)
				{
					if (read(fd_uart3, (void*)buffer, 1) == 1)
					{
						rxStatus = UART_STATUS_RXBYTE;
					}
				}

				#elif (MX_UART_CHANNEL_X == 4)
				if (fd_uart4 >= 0)
				{
					if (read(fd_uart4, (void*)buffer, 1) == 1)
					{
						rxStatus = UART_STATUS_RXBYTE;
					}
				}

				#elif (MX_UART_CHANNEL_X == 5)
				if (fd_uart5 >= 0)
				{
					if (read(fd_uart5, (void*)buffer, 1) == 1)
					{
						rxStatus = UART_STATUS_RXBYTE;
					}
				}
				#endif
			}

			if (rxStatus == UART_STATUS_RXBYTE)
			{
				retVal = buffer[0];
				/**
				#if (MX_UART_ECHO_X == 1)
					UART_Send(retVal);
				#endif
				**/
			}
		#endif	// #if (MX_UART_CHANNEL_X > 0)

	#endif

	return (retVal);
}


CALFUNCTION(void, FC_CAL_UART_Delay_, (void))
{
  #if (MX_UART_CHANNEL_X == 0)

  #endif
}


CALFUNCTION(void, FC_CAL_UART_UpdateBaud_, (MX_UINT8 new_baud))
{
	MX_UINT32 ioc_speed;
	switch(new_baud)
	{
		case 0: ioc_speed = B1200; break;
		case 1: ioc_speed = B2400; break;
		case 2: ioc_speed = B4800; break;
		case 3: ioc_speed = B9600; break;
		case 4: ioc_speed = B19200; break;
		case 5: ioc_speed = B38400; break;
		case 6: ioc_speed = B57600; break;
		case 7: ioc_speed = B115200; break;
		case 8: ioc_speed = B230400; break;
		default: return;	// We don't support anything else
	}

	#if (MX_UART_CHANNEL_X == 1)
		if (fd_uart1 >= 0)
		{
			struct termios config;
			tcgetattr(fd_uart1, &config);
			config.c_cflag = ioc_speed | CS8 | CLOCAL | CREAD;
			config.c_iflag = IGNPAR;
			config.c_oflag = 0;
			#if (MX_UART_ECHO_X == 1)
				config.c_lflag = ECHO;
			#else
				config.c_lflag = 0;
			#endif
			// tcflush(fd_uart1, TCIFLUSH);
			tcsetattr(fd_uart1, TCSANOW, &config);
		}

	#elif (MX_UART_CHANNEL_X == 2)
		if (fd_uart2 >= 0)
		{
			struct termios config;
			tcgetattr(fd_uart2, &config);
			config.c_cflag = ioc_speed | CS8 | CLOCAL | CREAD;
			config.c_iflag = IGNPAR;
			config.c_oflag = 0;
			#if (MX_UART_ECHO_X == 1)
				config.c_lflag = ECHO;
			#else
				config.c_lflag = 0;
			#endif
			// tcflush(fd_uart2, TCIFLUSH);
			tcsetattr(fd_uart2, TCSANOW, &config);
		}

	#elif (MX_UART_CHANNEL_X == 3)
		if (fd_uart3 >= 0)
		{
			struct termios config;
			tcgetattr(fd_uart3, &config);
			config.c_cflag = ioc_speed | CS8 | CLOCAL | CREAD;
			config.c_iflag = IGNPAR;
			config.c_oflag = 0;
			#if (MX_UART_ECHO_X == 1)
				config.c_lflag = ECHO;
			#else
				config.c_lflag = 0;
			#endif
			// tcflush(fd_uart3, TCIFLUSH);
			tcsetattr(fd_uart3, TCSANOW, &config);
		}

	#elif (MX_UART_CHANNEL_X == 4)
		if (fd_uart4 >= 0)
		{
			struct termios config;
			tcgetattr(fd_uart4, &config);
			config.c_cflag = ioc_speed | CS8 | CLOCAL | CREAD;
			config.c_iflag = IGNPAR;
			config.c_oflag = 0;
			#if (MX_UART_ECHO_X == 1)
				config.c_lflag = ECHO;
			#else
				config.c_lflag = 0;
			#endif
			// tcflush(fd_uart4, TCIFLUSH);
			tcsetattr(fd_uart4, TCSANOW, &config);
		}

	#elif (MX_UART_CHANNEL_X == 5)
		if (fd_uart5 >= 0)
		{
			struct termios config;
			tcgetattr(fd_uart5, &config);
			config.c_cflag = ioc_speed | CS8 | CLOCAL | CREAD;
			config.c_iflag = IGNPAR;
			config.c_oflag = 0;
			#if (MX_UART_ECHO_X == 1)
				config.c_lflag = ECHO;
			#else
				config.c_lflag = 0;
			#endif
			// tcflush(fd_uart5, TCIFLUSH);
			tcsetattr(fd_uart5, TCSANOW, &config);
		}

	#endif
}



