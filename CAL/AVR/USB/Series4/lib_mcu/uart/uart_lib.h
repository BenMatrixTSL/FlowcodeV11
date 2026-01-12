// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5E58CCBB21A13C09FFD3A2170FB233049BCD2941CB7B532EC295F5B40F097D096CDECA312D6EC2B5880E938F99FE2404F5BD0F9162BB218B7AF4E1CD32F02CD429A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5A8BF29F1DE69F9BBAD5FA27AC90B2553BFE4229EA7ABFA234420C681648A987B6D7AC78CDB50D231786D759688146981C450452115524C0E0571C8A3CE1F5FF34EAAFCA2D76FC7EFD8373DA57F6AE40C6897A1C64EC68459549D34A0D5AD11F35A99B088DED8C12D8085AF9E7397791990895395127CF8AD07369D99911C23D5D43797C197BFDEC5
// REVISION: 1.0
// GUID: C468D6FD-36ED-4C68-B56B-BA3C7F42BD00
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\lib_mcu\uart\uart_lib.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file contains Uart lib header file.
//!
//! - Compiler:           IAR EWAVR and GNU GCC for AVR
//! - Supported devices:  ATmega32U4
//!
//! \author               Atmel Corporation: http://www.atmel.com \n
//!                       Support and FAQ: http://support.atmel.no/
//!
//! ***************************************************************************

/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _UART_LIB_H_
#define _UART_LIB_H_

/*_____ I N C L U D E - F I L E S ____________________________________________*/
#include "uart_drv.h"


/*_____ D E F I N I T I O N S ______________________________________________*/
#ifndef UART_CONFIG
#define UART_CONFIG     MSK_UART_8BIT
#endif

#ifndef BAUDRATE
#error You must define BAUDRATE in config.h
#define BAUDRATE        999
#endif

#define AUTOBAUD        0

#if BAUDRATE == AUTOBAUD
#define Uart_set_baudrate(bdr)  autobaud()
#include "modules/autobaud/autobaud.h"
#else
#include "lib_mcu/uart/uart_bdr.h"
#endif

/*_____ D E C L A R A T I O N ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ P R O T O T Y P E S ____________________________________________________________*/

/**
 * @brief This function configures the UART configuration and timming following 
 * the constant definition of BAUDRATE and enables the UART controller.
 *
 * @pre before calling this function some declaration must be define in config.h:\n
 * - FOSC Frequency of crystal in kHz (mandatory)Standard crystals available
 * - BAUDRATE Baudrate in bit per second used for UART configuration (mandatory)
 * - UART_CONFIG : (by default 8 bits| 1 bit stop |without parity)
 *
 */
bit uart_init (void);

/**
 * @brief This function allows to send a character on the UART
 *
 * @param uc_wr_byte character to print on UART.
 *
 * @return character sent.
 *
 * @par Note:
*  the type p_uart_ptchar and r_uart_ptchar can be define to macth with a printf
 * need.
 *
 */
r_uart_ptchar uart_putchar (p_uart_ptchar uc_wr_byte);

/**
 * @brief This function allows to get a character from the UART
 *
 * @return character read.
 *
 */
char uart_getchar (void);

/**
 * @brief This function allows to inform if a character was received
 *
 * @return True if character received.
 *
 */
bit uart_test_hit (void);



#endif /* _UART_LIB_H_ */
