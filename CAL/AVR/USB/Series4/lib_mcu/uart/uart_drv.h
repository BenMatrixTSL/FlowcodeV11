// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5E58CCBB21A13C09FFD3A2170FB233049BCD2941CB7B532EC295F5B40F097D0961D801C8DE54E8C7F608AF134D52B0AEAD94F1D7CE1A4498618951DE29505D8039A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF52F7F9A6FC8B5437CEFB67BE8B5B12BF985C80E8EFE513ED4C8AB2C467709696538136C12F04F87C96C4AC5BBA5BCBC2002634FED29531E3D35E75807A7748A3BBC83ED5AFCD930053D477ED5D7CD8875D4FBD53EB795428B549D34A0D5AD11F341CA61157D5DFAD3252831777F4A50E6243D6A0B311F1E3D2EABD4ED9561D2123431AF726C5DC381
// REVISION: 1.0
// GUID: FC917C6E-D12B-4F8A-BD0F-3C0AD27256BA
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\lib_mcu\uart\uart_drv.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief Provide Uart driver
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

#ifndef _UART_DRV_H_
#define _UART_DRV_H_

#define MSK_UART_5BIT           0x00 /* UCSRnC register */
#define MSK_UART_6BIT           0x02
#define MSK_UART_7BIT           0x04
#define MSK_UART_8BIT           0x06
#define MSK_UART_9BIT           0x06

#define MSK_UART_RX_DONE        0x80 /* UCSRnA register */
#define MSK_UART_TX_COMPLET     0x40
#define MSK_UART_DRE            0x20

#define MSK_UART_ENABLE_IT_RX   0x80
#define MSK_UART_ENABLE_IT_TX   0x40
#define MSK_UART_ENABLE_RX      0x10 /* UCSRnB register */
#define MSK_UART_ENABLE_TX      0x08
#define MSK_UART_TX_BIT9        0x01
#define MSK_UART_RX_BIT9        0x02

#ifdef USE_UART1
    #define UCSRC   (UCSR0C)
    #define UCSRB   (UCSR0B)
    #define UCSRA   (UCSR0A)
    #define UDR     (UDR0)
    #define UBRRL   (UBRR0L)
    #define UBRRH   (UBRR0H)
    #define UBRR    (UBRR0)
#endif
#ifdef USE_UART2
    #define UCSRC    (UCSR1C)
    #define UCSRB    (UCSR1B)
    #define UCSRA    (UCSR1A)
    #define UDR      (UDR1)
    #define UBRRL    (UBRR1L)
    #define UBRRH    (UBRR1H)
    #define UBRR     (UBRR1)

#endif


#define Uart_hw_init(config)    (UCSRC=config)
#define Uart_enable()           (UCSRB|=MSK_UART_ENABLE_RX|MSK_UART_ENABLE_TX)
#define Uart_tx_ready()         (UCSRA&MSK_UART_DRE)
#define Uart_set_tx_busy()
#define Uart_send_byte(ch)      (UDR=ch)
#define Uart_rx_ready()         (UCSRA&MSK_UART_RX_DONE)
#define Uart_get_byte()         (UDR)
#define Uart_ack_rx_byte()

#define Uart_enable_it_rx()    (UCSRB|=MSK_UART_ENABLE_IT_RX)
#define Uart_enable_it_tx()    (UCSRB|=MSK_UART_ENABLE_IT_TX)
#define Uart_disable_it_rx()   (UCSRB&=~MSK_UART_ENABLE_IT_RX)

#endif
