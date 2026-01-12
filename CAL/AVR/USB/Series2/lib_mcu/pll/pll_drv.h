// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D50C5E48B026992FAC56EBA390E49A884CEB2A445A5450A697CCE93F5647F480A67F0409091FFEAF7FC2E250C322A6823D622E4A10154D10ED53988D8E819F1E2C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF59BB7F70F40BA81E7F5AD3D428ECF5821F006020F177E2CBAA72FDAC72D38EF75A4694B491CC306AB0041618AB2F831A3B7252C32335C6967BC30D9318EB73CC591A46D241FC4CAB68D2D1081D2A451979EB0DFF2E2527A2C549D34A0D5AD11F3E7E91FE1B3AB22A4D661935FBD089E0CD59FFA4F68597E57EC7A7697432197DD7C4D788F9A5608EF
// REVISION: 1.0
// GUID: 2E0A0FF7-6C64-40EF-9087-CA3B9613EB64
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\lib_mcu\pll\pll_drv.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file contains the low level macros and definition for the USB PLL
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


#ifndef PLL_DRV_H
#define PLL_DRV_H

//_____ I N C L U D E S ____________________________________________________

//! @defgroup PLL PLL driver
//! PLL Module
//! @{
//_____ M A C R O S ________________________________________________________

   //! @defgroup PLL_macros PLL Macros
   //! These functions allow to control the PLL
   //! @{
#define PLLx06          ( (0<<PLLP2) | (0<<PLLP1) | (0<<PLLP0) )
#define PLLx03          ( (0<<PLLP2) | (0<<PLLP1) | (1<<PLLP0) )


      //! @brief Start the PLL at only 48 MHz, regarding CPU frequency
      //! Start the USB PLL with clockfactor
      //! clockfactor can be PLLx24, PLLx12, PLLx08
      //! PLLx06, PLLx04, PLLx03
#define Start_pll(clockfactor)                                                  \
           (PLLCSR = ( clockfactor  | (1<<PLLE)  ))

      //! return 1 when PLL locked
#define Is_pll_ready()       (PLLCSR & (1<<PLOCK) )

      //! Test PLL lock bit and wait until lock is set
#define Wait_pll_ready()     while (!(PLLCSR & (1<<PLOCK)))

      //! Stop the PLL
#define Stop_pll()           (PLLCSR  &= (~(1<<PLLE)),PLLCSR=0 ) 

      // Start the PLL in autofactor mode
      // regarding FOSC define

#ifdef CUSTOM_PLL_START_AUTO
   #define    Pll_start_auto()   CUSTOM_PLL_START_AUTO
#else
#if   (FOSC==8000)
      //! Start the PLL in autofactor mode
      //! regarding FOSC define
   #define Pll_start_auto()   Start_pll(PLLx06)
#elif (FOSC==16000)
   #define Pll_start_auto()   Start_pll(PLLx03)
#else
   #error   "FOSC should be defined in config.h"
#endif
#endif
   //! @}

//! @}
#endif  // PLL_DRV_H


