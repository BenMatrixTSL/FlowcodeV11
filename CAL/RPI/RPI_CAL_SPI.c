// CRC: 34358081B117C27F7D8358E612878F8E5F343B66182D417818220CB9C07676CF06F4274FDFAD3D87C5F8E545EDBF5F889A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF599154D341BA0214A4A3A1E2A69953E2B7CB62F3241A0AB0DE1C7ED1FEDCB6F693182955C4EA3F87EBBB9BF96AB5CAE63318729816E5CFBC1B82DD63EDF96A1E04C9D3BE09EF54819C4A9E732825AF981E2A9F7840D9199D9549D34A0D5AD11F30B098B86D2E6A3472C9C24F14004E4620DD5D166E352E2672E2E537ED3A62AD834F73E07AA889468
// REVISION: 1.0
// GUID: 085179BE-0ADE-4BA6-B2BB-56EB6C405C3D
// DATE: 08\08\2022
// DIR: CAL\RPI\RPI_CAL_SPI.c
/*********************************************************************
 *                  Flowcode CAL SPI File
 *
 * File: PIC_CAL_SPI.c
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
 * 160118 | LM | Created from PIC
 *
 */


#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>


//Channel Abstraction
#define MX_SPI_REF_X				CAL_APPEND(MX_SPI_REF, MX_SPI_NUM)
#define MX_SPI_CHANNEL_X			CAL_APPEND(MX_SPI_CHANNEL_, MX_SPI_NUM)
#define MX_SPI_MOSI_PIN_X			CAL_APPEND(MX_SPI_MOSI_PIN_, MX_SPI_NUM)
#define MX_SPI_MOSI_PORT_X			CAL_APPEND(MX_SPI_MOSI_PORT_, MX_SPI_NUM)
//#define MX_SPI_MOSI_TRIS_X			CAL_APPEND(MX_SPI_MOSI_TRIS_, MX_SPI_NUM)
#define MX_SPI_MISO_PIN_X			CAL_APPEND(MX_SPI_MISO_PIN_, MX_SPI_NUM)
#define MX_SPI_MISO_PORT_X			CAL_APPEND(MX_SPI_MISO_PORT_, MX_SPI_NUM)
//#define MX_SPI_MISO_TRIS_X			CAL_APPEND(MX_SPI_MISO_TRIS_, MX_SPI_NUM)
#define MX_SPI_SCK_PIN_X			CAL_APPEND(MX_SPI_SCK_PIN_, MX_SPI_NUM)
#define MX_SPI_SCK_PORT_X			CAL_APPEND(MX_SPI_SCK_PORT_, MX_SPI_NUM)
//#define MX_SPI_SCK_TRIS_X			CAL_APPEND(MX_SPI_SCK_TRIS_, MX_SPI_NUM)
//#define MX_SPI_CS_PIN_X				CAL_APPEND(MX_SPI_CS_PIN_, MX_SPI_NUM)
//#define MX_SPI_CS_PORT_X			CAL_APPEND(MX_SPI_CS_PORT_, MX_SPI_NUM)
//#define MX_SPI_CS_TRIS_X			CAL_APPEND(MX_SPI_CS_TRIS_, MX_SPI_NUM)
#define MX_SPI_BMODE_X				CAL_APPEND(MX_SPI_BMODE_, MX_SPI_NUM)
#define MX_SPI_PR_SCALE_X			CAL_APPEND(MX_SPI_PR_SCALE_, MX_SPI_NUM)
#define MX_SPI_PO_SCALE_X			CAL_APPEND(MX_SPI_PO_SCALE_, MX_SPI_NUM)
#define MX_SPI_INT_X				CAL_APPEND(MX_SPI_INT_, MX_SPI_NUM)
//#define MX_SPI_REMAPPABLE_X			CAL_APPEND(MX_SPI_REMAPPABLE_, MX_SPI_NUM)
//#define MX_SPI_MISO_RPINR_X			CAL_APPEND(MX_SPI_MISO_RPINR_, MX_SPI_NUM)
//#define MX_SPI_MISO_RP_X			CAL_APPEND(MX_SPI_MISO_RP_, MX_SPI_NUM)
//#define MX_SPI_MOSI_RPOR_X			CAL_APPEND(MX_SPI_MOSI_RPOR_, MX_SPI_NUM)
//#define MX_SPI_MOSI_SDO_X			CAL_APPEND(MX_SPI_MOSI_SDO_, MX_SPI_NUM)
//#define MX_SPI_CLK_RPOR_X			CAL_APPEND(MX_SPI_CLK_RPOR_, MX_SPI_NUM)
//#define MX_SPI_CLK_SCK_X			CAL_APPEND(MX_SPI_CLK_SCK_, MX_SPI_NUM)
// SPI CAL component generates SS pin
#define MX_SPI_SS_PIN_X				CAL_APPEND(MX_SPI_SS_PIN_, MX_SPI_NUM)
#define MX_SPI_SS_PORT_X			CAL_APPEND(MX_SPI_SS_PORT_, MX_SPI_NUM)


// Now for some pin mangling for BL0036 :O) ...
#if   (MX_SPI_SCK_PORT_X == PORTA)
	#if   (MX_SPI_SCK_PIN_X == 0)
		#define MX_SPI_SCK_GPIO_X	MX_PORTA0_GPIO
	#elif (MX_SPI_SCK_PIN_X == 1)
		#define MX_SPI_SCK_GPIO_X	MX_PORTA1_GPIO
	#elif (MX_SPI_SCK_PIN_X == 2)
		#define MX_SPI_SCK_GPIO_X	MX_PORTA2_GPIO
	#elif (MX_SPI_SCK_PIN_X == 3)
		#define MX_SPI_SCK_GPIO_X	MX_PORTA3_GPIO
	#elif (MX_SPI_SCK_PIN_X == 4)
		#define MX_SPI_SCK_GPIO_X	MX_PORTA4_GPIO
	#elif (MX_SPI_SCK_PIN_X == 5)
		#define MX_SPI_SCK_GPIO_X	MX_PORTA5_GPIO
	#endif
#elif (MX_SPI_SCK_PORT_X == PORTB)
	#if   (MX_SPI_SCK_PIN_X == 0)
		#define MX_SPI_SCK_GPIO_X	MX_PORTB0_GPIO
	#elif (MX_SPI_SCK_PIN_X == 1)
		#define MX_SPI_SCK_GPIO_X	MX_PORTB1_GPIO
	#elif (MX_SPI_SCK_PIN_X == 2)
		#define MX_SPI_SCK_GPIO_X	MX_PORTB2_GPIO
	#elif (MX_SPI_SCK_PIN_X == 3)
		#define MX_SPI_SCK_GPIO_X	MX_PORTB3_GPIO
	#elif (MX_SPI_SCK_PIN_X == 4)
		#define MX_SPI_SCK_GPIO_X	MX_PORTB4_GPIO
	#elif (MX_SPI_SCK_PIN_X == 5)
		#define MX_SPI_SCK_GPIO_X	MX_PORTB5_GPIO
	#elif (MX_SPI_SCK_PIN_X == 6)
		#define MX_SPI_SCK_GPIO_X	MX_PORTB6_GPIO
	#elif (MX_SPI_SCK_PIN_X == 7)
		#define MX_SPI_SCK_GPIO_X	MX_PORTB7_GPIO
	#endif
#elif (MX_SPI_SCK_PORT_X == PORTC)
	#if   (MX_SPI_SCK_PIN_X == 0)
		#define MX_SPI_SCK_GPIO_X	MX_PORTC0_GPIO
	#elif (MX_SPI_SCK_PIN_X == 1)
		#define MX_SPI_SCK_GPIO_X	MX_PORTC1_GPIO
	#elif (MX_SPI_SCK_PIN_X == 2)
		#define MX_SPI_SCK_GPIO_X	MX_PORTC2_GPIO
	#elif (MX_SPI_SCK_PIN_X == 3)
		#define MX_SPI_SCK_GPIO_X	MX_PORTC3_GPIO
	#elif (MX_SPI_SCK_PIN_X == 4)
		#define MX_SPI_SCK_GPIO_X	MX_PORTC4_GPIO
	#elif (MX_SPI_SCK_PIN_X == 5)
		#define MX_SPI_SCK_GPIO_X	MX_PORTC5_GPIO
	#elif (MX_SPI_SCK_PIN_X == 6)
		#define MX_SPI_SCK_GPIO_X	MX_PORTC6_GPIO
	#elif (MX_SPI_SCK_PIN_X == 7)
		#define MX_SPI_SCK_GPIO_X	MX_PORTC7_GPIO
	#endif
#elif (MX_SPI_SCK_PORT_X == PORTD)
	#if   (MX_SPI_SCK_PIN_X == 0)
		#define MX_SPI_SCK_GPIO_X	MX_PORTD0_GPIO
	#elif (MX_SPI_SCK_PIN_X == 1)
		#define MX_SPI_SCK_GPIO_X	MX_PORTD1_GPIO
	#elif (MX_SPI_SCK_PIN_X == 2)
		#define MX_SPI_SCK_GPIO_X	MX_PORTD2_GPIO
	#elif (MX_SPI_SCK_PIN_X == 3)
		#define MX_SPI_SCK_GPIO_X	MX_PORTD3_GPIO
	#elif (MX_SPI_SCK_PIN_X == 4)
		#define MX_SPI_SCK_GPIO_X	MX_PORTD4_GPIO
	#elif (MX_SPI_SCK_PIN_X == 5)
		#define MX_SPI_SCK_GPIO_X	MX_PORTD5_GPIO
	#endif
#endif
#ifndef MX_SPI_SCK_GPIO_X
	// Nothing defined for that Port/Pin
	// Or we have GPIO numbers anyway (Port G)
	#define MX_SPI_SCK_GPIO_X MX_SPI_SCK_PIN_X
#endif

#if   (MX_SPI_MOSI_PORT_X == PORTA)
	#if   (MX_SPI_MOSI_PIN_X == 0)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTA0_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 1)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTA1_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 2)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTA2_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 3)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTA3_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 4)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTA4_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 5)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTA5_GPIO
	#endif
#elif (MX_SPI_MOSI_PORT_X == PORTB)
	#if   (MX_SPI_MOSI_PIN_X == 0)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTB0_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 1)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTB1_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 2)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTB2_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 3)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTB3_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 4)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTB4_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 5)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTB5_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 6)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTB6_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 7)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTB7_GPIO
	#endif
#elif (MX_SPI_MOSI_PORT_X == PORTC)
	#if   (MX_SPI_MOSI_PIN_X == 0)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTC0_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 1)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTC1_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 2)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTC2_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 3)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTC3_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 4)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTC4_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 5)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTC5_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 6)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTC6_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 7)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTC7_GPIO
	#endif
#elif (MX_SPI_MOSI_PORT_X == PORTD)
	#if   (MX_SPI_MOSI_PIN_X == 0)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTD0_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 1)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTD1_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 2)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTD2_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 3)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTD3_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 4)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTD4_GPIO
	#elif (MX_SPI_MOSI_PIN_X == 5)
		#define MX_SPI_MOSI_GPIO_X	MX_PORTD5_GPIO
	#endif
#endif
#ifndef MX_SPI_MOSI_GPIO_X
	// Nothing defined for that Port/Pin
	// Or we have GPIO numbers anyway (Port G)
	#define MX_SPI_MOSI_GPIO_X MX_SPI_MOSI_PIN_X
#endif


#if   (MX_SPI_MISO_PORT_X == PORTA)
	#if   (MX_SPI_MISO_PIN_X == 0)
		#define MX_SPI_MISO_GPIO_X	MX_PORTA0_GPIO
	#elif (MX_SPI_MISO_PIN_X == 1)
		#define MX_SPI_MISO_GPIO_X	MX_PORTA1_GPIO
	#elif (MX_SPI_MISO_PIN_X == 2)
		#define MX_SPI_MISO_GPIO_X	MX_PORTA2_GPIO
	#elif (MX_SPI_MISO_PIN_X == 3)
		#define MX_SPI_MISO_GPIO_X	MX_PORTA3_GPIO
	#elif (MX_SPI_MISO_PIN_X == 4)
		#define MX_SPI_MISO_GPIO_X	MX_PORTA4_GPIO
	#elif (MX_SPI_MISO_PIN_X == 5)
		#define MX_SPI_MISO_GPIO_X	MX_PORTA5_GPIO
	#endif
#elif (MX_SPI_MISO_PORT_X == PORTB)
	#if   (MX_SPI_MISO_PIN_X == 0)
		#define MX_SPI_MISO_GPIO_X	MX_PORTB0_GPIO
	#elif (MX_SPI_MISO_PIN_X == 1)
		#define MX_SPI_MISO_GPIO_X	MX_PORTB1_GPIO
	#elif (MX_SPI_MISO_PIN_X == 2)
		#define MX_SPI_MISO_GPIO_X	MX_PORTB2_GPIO
	#elif (MX_SPI_MISO_PIN_X == 3)
		#define MX_SPI_MISO_GPIO_X	MX_PORTB3_GPIO
	#elif (MX_SPI_MISO_PIN_X == 4)
		#define MX_SPI_MISO_GPIO_X	MX_PORTB4_GPIO
	#elif (MX_SPI_MISO_PIN_X == 5)
		#define MX_SPI_MISO_GPIO_X	MX_PORTB5_GPIO
	#elif (MX_SPI_MISO_PIN_X == 6)
		#define MX_SPI_MISO_GPIO_X	MX_PORTB6_GPIO
	#elif (MX_SPI_MISO_PIN_X == 7)
		#define MX_SPI_MISO_GPIO_X	MX_PORTB7_GPIO
	#endif
#elif (MX_SPI_MISO_PORT_X == PORTC)
	#if   (MX_SPI_MISO_PIN_X == 0)
		#define MX_SPI_MISO_GPIO_X	MX_PORTC0_GPIO
	#elif (MX_SPI_MISO_PIN_X == 1)
		#define MX_SPI_MISO_GPIO_X	MX_PORTC1_GPIO
	#elif (MX_SPI_MISO_PIN_X == 2)
		#define MX_SPI_MISO_GPIO_X	MX_PORTC2_GPIO
	#elif (MX_SPI_MISO_PIN_X == 3)
		#define MX_SPI_MISO_GPIO_X	MX_PORTC3_GPIO
	#elif (MX_SPI_MISO_PIN_X == 4)
		#define MX_SPI_MISO_GPIO_X	MX_PORTC4_GPIO
	#elif (MX_SPI_MISO_PIN_X == 5)
		#define MX_SPI_MISO_GPIO_X	MX_PORTC5_GPIO
	#elif (MX_SPI_MISO_PIN_X == 6)
		#define MX_SPI_MISO_GPIO_X	MX_PORTC6_GPIO
	#elif (MX_SPI_MISO_PIN_X == 7)
		#define MX_SPI_MISO_GPIO_X	MX_PORTC7_GPIO
	#endif
#elif (MX_SPI_MISO_PORT_X == PORTD)
	#if   (MX_SPI_MISO_PIN_X == 0)
		#define MX_SPI_MISO_GPIO_X	MX_PORTD0_GPIO
	#elif (MX_SPI_MISO_PIN_X == 1)
		#define MX_SPI_MISO_GPIO_X	MX_PORTD1_GPIO
	#elif (MX_SPI_MISO_PIN_X == 2)
		#define MX_SPI_MISO_GPIO_X	MX_PORTD2_GPIO
	#elif (MX_SPI_MISO_PIN_X == 3)
		#define MX_SPI_MISO_GPIO_X	MX_PORTD3_GPIO
	#elif (MX_SPI_MISO_PIN_X == 4)
		#define MX_SPI_MISO_GPIO_X	MX_PORTD4_GPIO
	#elif (MX_SPI_MISO_PIN_X == 5)
		#define MX_SPI_MISO_GPIO_X	MX_PORTD5_GPIO
	#endif
#endif
#ifndef MX_SPI_MISO_GPIO_X
	// Nothing defined for that Port/Pin
	// Or we have GPIO numbers anyway (Port G)
	#define MX_SPI_MISO_GPIO_X MX_SPI_MISO_PIN_X
#endif

#if   (MX_SPI_SS_PORT_X == PORTA)
	#if   (MX_SPI_SS_PIN_X == 0)
		#define MX_SPI_SS_GPIO_X	MX_PORTA0_GPIO
	#elif (MX_SPI_SS_PIN_X == 1)
		#define MX_SPI_SS_GPIO_X	MX_PORTA1_GPIO
	#elif (MX_SPI_SS_PIN_X == 2)
		#define MX_SPI_SS_GPIO_X	MX_PORTA2_GPIO
	#elif (MX_SPI_SS_PIN_X == 3)
		#define MX_SPI_SS_GPIO_X	MX_PORTA3_GPIO
	#elif (MX_SPI_SS_PIN_X == 4)
		#define MX_SPI_SS_GPIO_X	MX_PORTA4_GPIO
	#elif (MX_SPI_SS_PIN_X == 5)
		#define MX_SPI_SS_GPIO_X	MX_PORTA5_GPIO
	#endif
#elif (MX_SPI_SS_PORT_X == PORTB)
	#if   (MX_SPI_SS_PIN_X == 0)
		#define MX_SPI_SS_GPIO_X	MX_PORTB0_GPIO
	#elif (MX_SPI_SS_PIN_X == 1)
		#define MX_SPI_SS_GPIO_X	MX_PORTB1_GPIO
	#elif (MX_SPI_SS_PIN_X == 2)
		#define MX_SPI_SS_GPIO_X	MX_PORTB2_GPIO
	#elif (MX_SPI_SS_PIN_X == 3)
		#define MX_SPI_SS_GPIO_X	MX_PORTB3_GPIO
	#elif (MX_SPI_SS_PIN_X == 4)
		#define MX_SPI_SS_GPIO_X	MX_PORTB4_GPIO
	#elif (MX_SPI_SS_PIN_X == 5)
		#define MX_SPI_SS_GPIO_X	MX_PORTB5_GPIO
	#elif (MX_SPI_SS_PIN_X == 6)
		#define MX_SPI_SS_GPIO_X	MX_PORTB6_GPIO
	#elif (MX_SPI_SS_PIN_X == 7)
		#define MX_SPI_SS_GPIO_X	MX_PORTB7_GPIO
	#endif
#elif (MX_SPI_SS_PORT_X == PORTC)
	#if   (MX_SPI_SS_PIN_X == 0)
		#define MX_SPI_SS_GPIO_X	MX_PORTC0_GPIO
	#elif (MX_SPI_SS_PIN_X == 1)
		#define MX_SPI_SS_GPIO_X	MX_PORTC1_GPIO
	#elif (MX_SPI_SS_PIN_X == 2)
		#define MX_SPI_SS_GPIO_X	MX_PORTC2_GPIO
	#elif (MX_SPI_SS_PIN_X == 3)
		#define MX_SPI_SS_GPIO_X	MX_PORTC3_GPIO
	#elif (MX_SPI_SS_PIN_X == 4)
		#define MX_SPI_SS_GPIO_X	MX_PORTC4_GPIO
	#elif (MX_SPI_SS_PIN_X == 5)
		#define MX_SPI_SS_GPIO_X	MX_PORTC5_GPIO
	#elif (MX_SPI_SS_PIN_X == 6)
		#define MX_SPI_SS_GPIO_X	MX_PORTC6_GPIO
	#elif (MX_SPI_SS_PIN_X == 7)
		#define MX_SPI_SS_GPIO_X	MX_PORTC7_GPIO
	#endif
#elif (MX_SPI_SS_PORT_X == PORTD)
	#if   (MX_SPI_SS_PIN_X == 0)
		#define MX_SPI_SS_GPIO_X	MX_PORTD0_GPIO
	#elif (MX_SPI_SS_PIN_X == 1)
		#define MX_SPI_SS_GPIO_X	MX_PORTD1_GPIO
	#elif (MX_SPI_SS_PIN_X == 2)
		#define MX_SPI_SS_GPIO_X	MX_PORTD2_GPIO
	#elif (MX_SPI_SS_PIN_X == 3)
		#define MX_SPI_SS_GPIO_X	MX_PORTD3_GPIO
	#elif (MX_SPI_SS_PIN_X == 4)
		#define MX_SPI_SS_GPIO_X	MX_PORTD4_GPIO
	#elif (MX_SPI_SS_PIN_X == 5)
		#define MX_SPI_SS_GPIO_X	MX_PORTD5_GPIO
	#endif
#endif
#ifndef MX_SPI_SS_GPIO_X
	// Nothing defined for that Port/Pin
	// Or we have GPIO numbers anyway (Port G)
	#define MX_SPI_SS_GPIO_X MX_SPI_SS_PIN_X
#endif

#define MX_PRESCALE_VAR_X			CAL_APPEND(prescale_, MX_SPI_NUM)

#ifdef MX_SPI_IOC_MODE_X
#undef MX_SPI_IOC_MODE_X
#endif

#if (MX_SPI_BMODE_X == 1)
	#define MX_SPI_IOC_MODE_X 	SPI_MODE_3
#elif (MX_SPI_BMODE_X == 2)
	#define MX_SPI_IOC_MODE_X 	SPI_MODE_0
#elif (MX_SPI_BMODE_X == 3)
	#define MX_SPI_IOC_MODE_X 	SPI_MODE_2
#else
	#define MX_SPI_IOC_MODE_X 	SPI_MODE_1
#endif

#ifdef MX_SPI_IOC_SPEED_X
#undef MX_SPI_IOC_SPEED_X
#endif
#if (MX_SPI_PR_SCALE_X > 15)
	#define MX_SPI_IOC_SPEED_X	(250000)
#elif (MX_SPI_PR_SCALE_X > 7)
	#define MX_SPI_IOC_SPEED_X	(500000)
#elif (MX_SPI_PR_SCALE_X > 3)
	#define MX_SPI_IOC_SPEED_X	(1000000)
#else
	#define MX_SPI_IOC_SPEED_X	(2000000)
#endif

#ifndef MX_SPI_DELAY
#define MX_SPI_DELAY	{volatile int x=((MX_SPI_PR_SCALE_X + 1) * 10); while(x) --x;}
#endif

//Function Prototypes
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Init_, (void));
CALFUNCTION(void, FC_CAL_SPI_Master_Uninit_, (void));
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Byte_, (MX_UINT8 DataOut));
CALFUNCTION(void, FC_CAL_SPI_SetPrescaler_, (MX_UINT8 Prescaler));

CALFUNCTION(void, FC_CAL_SPI_Slave_Init_, (void));
CALFUNCTION(void, FC_CAL_SPI_Slave_Uninit_, (void));
CALFUNCTION(void, FC_CAL_SPI_Slave_SetTxData_, (MX_UINT8 Data));
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Slave_GetRxData_, (void));

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_Init_,   (void));
CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_,   (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length));
CALFUNCTION(void,     FC_CAL_SPI_Transaction_Uninit_, (void));



#if (MX_SPI_CHANNEL_X > 0)
	#if (MX_SPI_PR_SCALE_X == 4)
		#undef MX_SPI_PR_SCALE_X
		#define MX_SPI_PR_SCALE_X 0
	#endif
	#if (MX_SPI_PR_SCALE_X == 16)
		#undef MX_SPI_PR_SCALE_X
		#define MX_SPI_PR_SCALE_X 1
	#endif
	#if (MX_SPI_PR_SCALE_X == 64)
		#undef MX_SPI_PR_SCALE_X
		#define MX_SPI_PR_SCALE_X 2
	#endif
#endif



//Bus Mode - Bit0=CKP=CPOL, Bit1=CKE=!CPHA, Bit2=CSMP
//CKP=CPOL - Clock Polarity - Idle State of the clock 0=0, 1=1
//CKE=CPHA - Clock Phase - Clock Edge 0=leading edge, 1=trailing edge
//CSMP - Input Data Bit Sample Phase
//CRAT - SPI Clock Rate 0=1/4, 1=1/16, 2=1/64

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
	MX_UINT8 retVal = 0;
	
	#if (MX_SPI_CHANNEL_X == 0)
	// MX_GPIO_IN(MX_SPI_SS_GPIO_X);				// SS pin is a input (Alt Off)
	MX_GPIO_IN(MX_SPI_SCK_GPIO_X);				// SCK pin is a input (Alt Off)
	MX_GPIO_IN(MX_SPI_MISO_GPIO_X);				// MISO pin is a input (Alt Off)
	MX_GPIO_IN(MX_SPI_MOSI_GPIO_X);				// MOIS pin is a input (Alt Off)
	FC_CAL_GPIO_SET_DDR(MX_SPI_MOSI_GPIO_X);	// MOSI pin is default high

		#if (MX_SPI_BMODE_X & 0x01)
			FC_CAL_GPIO_SET_DDR(MX_SPI_SCK_GPIO_X);		// Clock pin is default high
		#else
			FC_CAL_GPIO_CLR_DDR(MX_SPI_SCK_GPIO_X);		// Clock pin is default low
		#endif
	retVal = 1;
	
	#elif (MX_SPI_CHANNEL_X == 1)
	retVal = CALFUNCTION( , FC_CAL_SPI_Transaction_Init_, ());
	
	#elif (MX_SPI_CHANNEL_X == 2)
	retVal = CALFUNCTION( , FC_CAL_SPI_Transaction_Init_, ());
	
	#endif
	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_Master_Uninit_, (void))
{
	#if (MX_SPI_CHANNEL_X == 0)
	//Reset Pins to Inputs
	MX_GPIO_IN(MX_SPI_MOSI_GPIO_X);
	MX_GPIO_IN(MX_SPI_MISO_GPIO_X);
	MX_GPIO_IN(MX_SPI_SCK_GPIO_X);
	// MX_GPIO_IN(MX_SPI_SS_GPIO_X);
	
	#elif (MX_SPI_CHANNEL_X == 1)
	CALFUNCTION( , FC_CAL_SPI_Transaction_Uninit_, ());
	
	#elif (MX_SPI_CHANNEL_X == 2)
	CALFUNCTION( , FC_CAL_SPI_Transaction_Uninit_, ());
	
	#endif
}


CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Byte_, (MX_UINT8 DataOut))
{
	MX_UINT8 retVal = 0;

	#if (MX_SPI_CHANNEL_X == 0)

		MX_UINT8 idx, i;
		for (idx = 0; idx < 8; idx++)
		{
			retVal = retVal << 1;

			//If mode 1 or 3, switch the clock
			#if ((MX_SPI_BMODE_X & 0x02) == 0x00)				//CKE = 0; (mode 1 or 3) Set SCK active before data
				#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
					FC_CAL_GPIO_SET(MX_SPI_SCK_GPIO_X);			//CKP = 0; (mode 1)
				#else
					FC_CAL_GPIO_CLR(MX_SPI_SCK_GPIO_X);			//CKP = 1; (mode 3)
				#endif
			#endif

			//Data setup
			if (DataOut & 0x80)									//Test Data bit
				FC_CAL_GPIO_SET(MX_SPI_MOSI_GPIO_X);				//Set SDO bit
			else
				FC_CAL_GPIO_CLR(MX_SPI_MOSI_GPIO_X);				//Clear SDO bit

			//Clock delay
			MX_SPI_DELAY;

			//Switch clock - high for modes 0 and 3; low for modes 1 and 2
			#if ((MX_SPI_BMODE_X & 0x02) == 0x02)				//CKE = 1; (mode 0 or 2)
				#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
					FC_CAL_GPIO_SET(MX_SPI_SCK_GPIO_X);			//CKP = 0; (mode 0)
				#else
					FC_CAL_GPIO_CLR(MX_SPI_SCK_GPIO_X);			//CKP = 1; (mode 2)
				#endif
			#else
				#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
					FC_CAL_GPIO_CLR(MX_SPI_SCK_GPIO_X);			//CKP = 0; (mode 1)
				#else
					FC_CAL_GPIO_SET(MX_SPI_SCK_GPIO_X);			//CKP = 1; (mode 3)
				#endif
			#endif

			//Sample at middle of data output?
			#if ((MX_SPI_BMODE_X & 0x04) == 0)					//Sample at the middle of period
				if(MX_GPIO_GET(MX_SPI_MISO_GPIO_X))
					retVal = retVal | 0x01;
				else
					retVal = retVal & 0xFE;
			#endif

			//Clock delay
			MX_SPI_DELAY;

			//If mode 0 or 2, switch the clock
			#if ((MX_SPI_BMODE_X & 0x02) == 0x02)				//CKE = 1; (mode 0 or 2)
				#if ((MX_SPI_BMODE_X & 0x01) == 0x00)
					FC_CAL_GPIO_CLR(MX_SPI_SCK_GPIO_X);			//CKP = 0; (mode 0)
				#else
					FC_CAL_GPIO_SET(MX_SPI_SCK_GPIO_X);			//CKP = 1; (mode 2)
				#endif
			#endif

			//Sample at end of data output?
			#if ((MX_SPI_BMODE_X & 0x04) == 0x04)				//Sample at the end of period
				if(MX_GPIO_GET(MX_SPI_MISO_GPIO_X))
					retVal = retVal | 0x01;
				else
					retVal = retVal & 0xFE;
			#endif

			DataOut = DataOut << 1;							//Move to next data bit
		}
		
	#elif (MX_SPI_CHANNEL_X == 1)
		CALFUNCTION( , FC_CAL_SPI_Transaction_,  (&DataOut, 1, 1));
		retVal = DataOut;
		
	#elif (MX_SPI_CHANNEL_X == 2)
		CALFUNCTION( , FC_CAL_SPI_Transaction_,  (&DataOut, 1, 1));
		retVal = DataOut;
	
    #endif

	return (retVal);
}


CALFUNCTION(void, FC_CAL_SPI_SetPrescaler_, (MX_UINT8 Prescaler))
{
	// MX_PRESCALE_VAR_X = Prescaler;

	//0 = Fosc/4
	//1 = Fosc/16
	//2 = Fosc/64
}


/**************************************************
SPI Slave functions not supported on Raspberry Pi
**************************************************/

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
SPI Master Transaction functions for Raspberry Pi
**************************************************/
#if (MX_SPI_CHANNEL_X == 0)

#elif (MX_SPI_CHANNEL_X == 1)
int fd_spi1 = -1;
#elif (MX_SPI_CHANNEL_X == 2)
int fd_spi2 = -1;
#endif

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_Init_,   (void))
{
#if (MX_SPI_CHANNEL_X == 0)
	CALFUNCTION(, FC_CAL_SPI_Master_Init_, ());
	return 1;	// Success
	
#elif (MX_SPI_CHANNEL_X == 1)
	if (fd_spi1 != -1)
		return 0;	// Fail (already open)
	
	// Set pins to SPI Alt function, just in case we have used them as IO
	// MX_GPIO_ALT(8,0);		// CS0
	MX_GPIO_ALT(9,0);		// MISO
	MX_GPIO_ALT(10,0);		// MOSI
	MX_GPIO_ALT(11,0);		// SCLK
	
	if ((fd_spi1 = open((char*)"/dev/spidev0.0", O_RDWR)) < 0)
		return 0;	// Fail

	MX_UINT8 mode = MX_SPI_IOC_MODE_X | SPI_NO_CS;
	ioctl(fd_spi1, SPI_IOC_WR_MODE, &mode);
	
	// If GPIO 8 is set to Alt 0 then change it back to an input
	if (MX_GPIO_GET_FSEL(8) == 4)
		MX_GPIO_IN(8);
	return 1;	// Success

#elif (MX_SPI_CHANNEL_X == 2)
	if (fd_spi2 != -1)
		return 0;	// Fail (already open)
		
	// Set pins to SPI Alt function, just in case we have used them as IO
	// MX_GPIO_ALT(7,0);		// CS1
	MX_GPIO_ALT(9,0);		// MISO
	MX_GPIO_ALT(10,0);		// MOSI
	MX_GPIO_ALT(11,0);		// SCLK
	
	if ((fd_spi2 = open((char*)"/dev/spidev0.1", O_RDWR)) < 0)
		return 0;	// Fail

	MX_UINT8 mode = MX_SPI_IOC_MODE_X | SPI_NO_CS;
	ioctl(fd_spi2, SPI_IOC_WR_MODE, &mode);
	
	// If GPIO 7 is set to Alt 0 then change it back to an input
	if (MX_GPIO_GET_FSEL(7) == 4)
		MX_GPIO_IN(7);
	return 1;	// Success

#else
	return 0;	// Fail
#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_,   (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length))
{
	if (Length > Size) return 0;
#if (MX_SPI_CHANNEL_X == 0)
	MX_UINT16 n = 0;
	// FC_CAL_GPIO_CLR_DDR(MX_SPI_SS_GPIO_X);	// CS pin low
	while (n < Length)
	{
		Buffer[n] = CALFUNCTION(, FC_CAL_SPI_Master_Byte_, (Buffer[n]));
		++n;
	}
	// FC_CAL_GPIO_SET_DDR(MX_SPI_SS_GPIO_X);	// CS pin high
	return 1;		// Success

#elif (MX_SPI_CHANNEL_X == 1)
	// Check that we have a valid handle i.e. the channel has been opened correctly
	if (fd_spi1 < 0) return 0;
	
	struct spi_ioc_transfer spi;
	spi.tx_buf        = Buffer;
	spi.rx_buf        = Buffer;
	spi.len           = Length;
	spi.delay_usecs   = 0 ;
	spi.speed_hz      = MX_SPI_IOC_SPEED_X;
	spi.bits_per_word = 8;		// fixed at 8 bit words for now
	spi.cs_change = 0;
	// return 0 = Failure,  1 = Success
	return (ioctl (fd_spi1, SPI_IOC_MESSAGE(1), &spi) < 0)?0:1;

#elif (MX_SPI_CHANNEL_X == 2)
	// Check that we have a valid handle i.e. the channel has been opened correctly
	if (fd_spi2 < 0) return 0;

	struct spi_ioc_transfer spi;
	spi.tx_buf        = Buffer;
	spi.rx_buf        = Buffer;
	spi.len           = Length;
	spi.delay_usecs   = 0 ;
	spi.speed_hz      = MX_SPI_IOC_SPEED_X;
	spi.bits_per_word = 8;		// fixed at 8 bit words for now
	spi.cs_change = 0;
	// return 0 = Failure,  1 = Success
	return (ioctl (fd_spi2, SPI_IOC_MESSAGE(1), &spi) < 0)?0:1;

#else
	return 0;
#endif
}

CALFUNCTION(void,     FC_CAL_SPI_Transaction_Uninit_, (void))
{
#if (MX_SPI_CHANNEL_X == 0)
	CALFUNCTION(, FC_CAL_SPI_Master_Uninit_, ());

#elif (MX_SPI_CHANNEL_X == 1)
	if (fd_spi1 >= 0) close(fd_spi1);
	fd_spi1 = -1;

#elif (MX_SPI_CHANNEL_X == 2)
	if (fd_spi2 >= 0) close(fd_spi2);
	fd_spi2 = -1;
#endif
}

#undef MX_SPI_SCK_GPIO_X
#undef MX_SPI_MISO_GPIO_X
#undef MX_SPI_MOSI_GPIO_X
#undef MX_SPI_PR_SCALE_X

