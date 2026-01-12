// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D50C5E48B026992FAC56EBA390E49A884CBCD2941CB7B532EC295F5B40F097D0960C1F32813C580E0275F129A6EE5F0323E21F7971E9B8F6726A9BE334018058DD9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5794B0FE3DC204687AF633238E20F9EA33AB2E73ABBD3922037F66C927B12E9FE857F46A5321BE9A54D46CE70BE8F2EE1A56D7B326D4FA58DE5C5E46315BCFFDF68A67FC3276720E582BC9ECFF9ACAE74A5F6A0F645B58616549D34A0D5AD11F3AFAB21170A32AAF2443F773DFE4477D5C18ED10E1D2EA89476AD1A7DB9B9D5F43F565616D7803A54
// REVISION: 1.0
// GUID: 0A123F8B-6250-4C13-96A2-165100763D30
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\lib_mcu\uart\uart_bdr.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief Provide Baudrate configuration for MCU
//!
//! - Compiler:           IAR EWAVR and GNU GCC for AVR
//! - Supported devices:  AT90USB162, AT90USB82
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

