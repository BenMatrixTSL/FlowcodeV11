// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5E58CCBB21A13C09FFD3A2170FB2330491987B3A12A7020A186DF318CF5249CF89FB732FDE902241005BA317D89010F95622E4A10154D10ED53988D8E819F1E2C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5370F70A85A979C7C8B8334374803E0B0DC32A30F4E8D167076623F886DCF6233A495A95AC15A5044F22EFB602B687E30FF4860EF3C299BAA9BD4389D59C46097DFF34A249B00FBD27890E83EB3A1A38AEB33AFC7003B3C9B549D34A0D5AD11F306FA3BFB6D664A94E56EFD8CE1ECDC4403C4D0E23B111DD508DB0CC5B99E58558FAE3087E8A87EE9
// REVISION: 1.0
// GUID: DBB3CF6B-D5AD-4904-BC64-9F4F74957B05
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\lib_mcu\wdt\wdt_drv.h
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

#ifndef _WDT_DRV_H_
#define _WDT_DRV_H_

//_____ I N C L U D E S ____________________________________________________

#ifdef __GNUC__
   #include <avr/io.h>
   #include <avr/wdt.h>
#endif


//_____ M A C R O S ________________________________________________________

//! @defgroup wdt_drv Watchdog and reset sytem drivers
//! @{

#define  Is_ext_reset()                ((MCUSR&(1<<EXTRF)) ? TRUE:FALSE)
#define  Ack_ext_reset()               (MCUSR= ~(1<<EXTRF))
#define  Is_POR_reset()                ((MCUSR&(1<<(MCUSR= ~(1<<PORF)))) ? TRUE:FALSE)
#define  Ack_POR_reset()               (MCUSR= ~(1<<PORF))
#define  Is_BOD_reset()                ((MCUSR&(1<<BORF)) ? TRUE:FALSE)
#define  Ack_BOD_reset()               (MCUSR= ~(1<<BORF))
#define  Is_wdt_reset()                ((MCUSR&(1<<WDRF)) ? TRUE:FALSE)
#define  Ack_wdt_reset()               (MCUSR= ~(1<<WDRF))
        
#define  Wdt_ack_interrupt()           (WDTCSR = (U8)(1<<WDIF))
#define  Is_wdt_interrupt()            (WDTCSR&(1<<WDIF) ? TRUE:FALSE)
#define  Is_not_wdt_interrupt()        (WDTCSR&(1<<WDIF) ? FALSE:TRUE)
#define  Is_wdt_early_warning()        (WDTCKD&(1<<WDEWIF) ? TRUE:FALSE)
#define  Is_not_wdt_early_warning()    (WDTCKD&(1<<WDEWIF) ? FALSE:TRUE)

#define  WDTO_16MS   0
#define  WDTO_32MS   1
#define  WDTO_64MS   2
#define  WDTO_125MS  3
#define  WDTO_250MS  4
#define  WDTO_500MS  5
#define  WDTO_1S     6
#define  WDTO_2S     7
#define  WDTO_4S     8
#define  WDTO_8S     9


//! This functions stops the hardware watchdog timer.
//!
void wdtdrv_disable(void);


//! This functions activates the hardware watchdog timer
//!
//! @param timeout (WDTO_x)
//!
void wdtdrv_enable( U8 timeout );


//! This functions activates the hardware watchdog timer Interrupt Mode only
//!
//! @param timeout (WDTO_x)
//!
void wdtdrv_interrupt_enable( U8 timeout );


//! This functions activates the hardware watchdog timer Interrupt & System Reset Mode
//!
//! @param timeout (WDTO_x)
//!
void wdtdrv_interrupt_reset_enable( U8 timeout );


#define Soft_reset()             {asm("jmp 0000");}

//! @}

#endif  // _WDT_DRV_H_

