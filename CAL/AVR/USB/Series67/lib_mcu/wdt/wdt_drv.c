// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D583C45B8AED270FE40481B7BD05EB7253D1725C4DBBA168AE059BE679A71BED79898E107BB37BF4C0DFF995D2760DAB82DD04A5F8AD9BEEB1823278EF8F2BA19C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5147424864274D2FFF28EAD50EE94FE19AF5B38D44A573CFE61D5929F481D11F35D39A7654A62F2B872A24AA30A2D8E0BEF0E011A8C3175A550AC7EE6CEE818E8E91803126A2E768B650B50114FB54DC91305807E2524C86E549D34A0D5AD11F3359EF040EB23794891383B8035928F8F659A6A817FCEF6D5FFCF1C90B393605E9F32B96E9FC2F3A9
// REVISION: 1.0
// GUID: CE0A9495-3DE9-4494-B0C6-11695943B316
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series67\lib_mcu\wdt\wdt_drv.c
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file contains the Watchdog low level driver definition
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

