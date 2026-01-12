// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5E58CCBB21A13C09FFD3A2170FB233049BCD2941CB7B532EC295F5B40F097D096CDECA312D6EC2B5880E938F99FE2404FFAA4458EC9CAE498CB82F7AC975D21D49A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5B56E5A7211055A7C272560FC2C9AA03FB8F15C2209CC8C6B46D7708249C155DE3F904DD8B8D80943C91AB626C51D6380C807E4781363D9220844A19E51271745F28749834175D79DCE5467C8AF7B187A9A6DA71FF9458762549D34A0D5AD11F352CE9CA726C3BDFC971D18D385A4767483982520611B89A959A43852AB18B119835CEFDAC0E534C9
// REVISION: 1.0
// GUID: 4202AF9E-EAC4-40E6-99C3-65B5B0E0030F
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\lib_mcu\uart\uart_lib.c
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file provides a minimal VT100 terminal access through UART
//! and compatibility with Custom I/O support
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

/*_____ I N C L U D E S ____________________________________________________*/
#include "config.h"
#include "lib_mcu/uart/uart_lib.h"


/*_____ G L O B A L    D E F I N I T I O N _________________________________*/


/*_____ D E F I N I T I O N ________________________________________________*/

/*_____ M A C R O S ________________________________________________________*/


bit uart_test_hit (void)
{
return Uart_rx_ready();
}


bit uart_init (void)
{
#ifndef UART_U2
  Uart_set_baudrate(BAUDRATE);
  Uart_hw_init(UART_CONFIG);
#else
  Uart_set_baudrate(BAUDRATE/2);
  Uart_double_bdr();
  Uart_hw_init(UART_CONFIG);

#endif
  Uart_enable();
  return TRUE;
}


r_uart_ptchar uart_putchar (p_uart_ptchar ch)
{
  while(!Uart_tx_ready());
  Uart_set_tx_busy(); // Set Busy flag before sending (always)
  Uart_send_byte(ch);
   
  return ch;
}




char uart_getchar (void)
{
  register char c;

  while(!Uart_rx_ready());
  c = Uart_get_byte();
  Uart_ack_rx_byte();
  return c;
}


