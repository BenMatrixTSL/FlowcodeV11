// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D50C5E48B026992FAC56EBA390E49A884C1987B3A12A7020A186DF318CF5249CF89FB732FDE902241005BA317D89010F95186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF545730A3FC3172BBCB20ACBC7D82EF26F4AA18AFF109B81AFAAE0991F9A855597A4C95759D179F8D775C7B1601E9B741DA757F167E273A001D3064AE30C07BBB2B1D20AA7C73E86365C00A80BFA316BD532ABD86F69D29E03549D34A0D5AD11F35A5903AA8E14A123E3E54E4A380CDCB17CA5025DC55960311EDE0E6E8CE8F293FC3F53D5103A0873
// REVISION: 1.0
// GUID: 4DF4CE1D-A98F-4168-A9A3-297AFA0245A7
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\lib_mcu\wdt\wdt_drv.c
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file contains the Watchdog low level driver definition
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

//_____ I N C L U D E S ____________________________________________________

#include "config.h"
#include "wdt_drv.h"

//_____ M A C R O S ________________________________________________________

#ifdef __GNUC__
#define  Wdt_reset_instruction()    wdt_reset()
#else
#define  Wdt_reset_instruction()    __watchdog_reset()
#endif


//! This functions stops the hardware watchdog timer.
//!
#ifndef __GNUC__
   // Ignored if IAR compiler optimization option "Always do cross call optimization" is enabled
   #pragma optimize=none 
#endif
void wdtdrv_disable(void)
{
   U8 save_int=Get_interrupt_state();
   Disable_interrupt();
#ifdef  __GNUC__
   Ack_wdt_reset();
   wdt_disable();
#else
   Ack_wdt_reset();
   Wdt_reset_instruction();
   WDTCSR = (1<<WDCE) | (1<<WDE);
   WDTCSR = 0x00;
#endif
   if(save_int) { Enable_interrupt(); }
}


//! This functions activates the hardware watchdog timer System Reset Mode only
//!
//! @param timeout (WDTO_x)
//!
#ifndef __GNUC__
   // Ignored if IAR compiler optimization option "Always do cross call optimization" is enabled
   #pragma optimize=none 
#endif
void wdtdrv_enable( U8 timeout )
{
   U8 save_int=Get_interrupt_state();
   Disable_interrupt();
#ifdef  __GNUC__
   Ack_wdt_reset();
   wdt_enable(timeout);
#else
   timeout = (1<<WDE)| (timeout & 0x08 ? (1<<WDP3) : 0x00) | (timeout & 0x07);
   Disable_interrupt();
   Wdt_reset_instruction();
   WDTCSR = (1<<WDCE) | (1<<WDE);
   WDTCSR = timeout;
#endif
   if(save_int) { Enable_interrupt(); }
}


//! This functions activates the hardware watchdog timer Interrupt Mode only
//!
//! @param timeout (WDTO_x)
//!
#ifndef __GNUC__
   // Ignored if IAR compiler optimization option "Always do cross call optimization" is enabled
   #pragma optimize=none 
#endif
void wdtdrv_interrupt_enable( U8 timeout )
{
   U8 save_int=Get_interrupt_state();
#ifdef  __GNUC__
   Ack_wdt_reset();
    __asm__ __volatile__ (  \
        "in __tmp_reg__,__SREG__" "\n\t"    \
        "cli" "\n\t"    \
        "wdr" "\n\t"    \
        "sts %0,%1" "\n\t"  \
        "out __SREG__,__tmp_reg__" "\n\t"   \
        "sts %0,%2" \
        : /* no outputs */  \
        : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)), \
        "r" (_BV(_WD_CHANGE_BIT) | _BV(WDE)), \
        "r" ((uint8_t) ((timeout & 0x08 ? _WD_PS3_MASK : 0x00) | \
            _BV(WDIE) | (timeout & 0x07)) ) \
        : "r0"  \
    );
#else
   timeout = (1<<WDIE)| (timeout & 0x08 ? (1<<WDP3) : 0x00) | (timeout & 0x07);
   Disable_interrupt();
   Wdt_reset_instruction();
   WDTCSR = (1<<WDCE) | (1<<WDE);
   WDTCSR = timeout;
#endif
   if(save_int) { Enable_interrupt(); }
}


//! This functions activates the hardware watchdog timer Interrupt & System Reset Mode
//!
//! @param timeout (WDTO_x)
//!
#ifndef __GNUC__
   // Ignored if IAR compiler optimization option "Always do cross call optimization" is enabled
   #pragma optimize=none 
#endif
void wdtdrv_interrupt_reset_enable( U8 timeout )
{
   U8 save_int=Get_interrupt_state();
   Disable_interrupt();
#ifdef  __GNUC__
   Ack_wdt_reset();
    __asm__ __volatile__ (  \
        "in __tmp_reg__,__SREG__" "\n\t"    \
        "cli" "\n\t"    \
        "wdr" "\n\t"    \
        "sts %0,%1" "\n\t"  \
        "out __SREG__,__tmp_reg__" "\n\t"   \
        "sts %0,%2" \
        : /* no outputs */  \
        : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)), \
        "r" (_BV(_WD_CHANGE_BIT) | _BV(WDE)), \
        "r" ((uint8_t) ((timeout & 0x08 ? _WD_PS3_MASK : 0x00) | \
            _BV(WDE) | _BV(WDIE) | (timeout & 0x07)) ) \
        : "r0"  \
    );
#else
   timeout = (1<<WDIE)|(1<<WDE)| (timeout & 0x08 ? (1<<WDP3) : 0x00) | (timeout & 0x07);
   Disable_interrupt();
   Wdt_reset_instruction();
   WDTCSR = (1<<WDCE) | (1<<WDE);
   WDTCSR = timeout;
#endif
   if(save_int) { Enable_interrupt(); }
}

