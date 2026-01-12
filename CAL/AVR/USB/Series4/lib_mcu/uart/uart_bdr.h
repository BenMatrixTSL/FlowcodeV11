// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5E58CCBB21A13C09FFD3A2170FB233049BCD2941CB7B532EC295F5B40F097D0960C1F32813C580E0275F129A6EE5F0323E21F7971E9B8F6726A9BE334018058DD9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF56FB2CE5F995B68B7606DC0C04F37194EDBA84B830C6B5262CE88B4D3114F8C95DDD29D9638D602C3A9C1D08E7718E5BB24B6C4382E1BAC536F5C38F0AA24104C5FDABAF70BD7D439740A00D773A6AA1300A8FF7CFF8D36B4549D34A0D5AD11F383643386287ED092FD896448D9873770C0F0E855A542DF298D531F270564038E47F47A97AF8C57FD
// REVISION: 1.0
// GUID: 3B635682-A5CA-4B87-A3BE-87CB4B84177F
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\lib_mcu\uart\uart_bdr.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief Provide Baudrate configuration for MCU
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

#ifndef _UART_BDR_H
#define _UART_BDR_H

#ifndef __GNUC__
   #define Uart_set_baudrate(bdr)  ( UBRRH = (Uchar)((((Uint32)FOSC*1000L)/((Uint32)bdr*16)-1)>>8),\
                                  UBRRL = (Uchar)(((Uint32)FOSC*1000 )/((Uint32)bdr*16)-1)    )
#else
  #define Uart_set_baudrate(bdr)  ( UBRR = (U16)(((U32)FOSC*1000L)/((U32)bdr*16)-1))
#endif

#define Uart_double_bdr()          (UCSRA |= (1<<U2X1))

#endif/* _UART_BDR_H */

