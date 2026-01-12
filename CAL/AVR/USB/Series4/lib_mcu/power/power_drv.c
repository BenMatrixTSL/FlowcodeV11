// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5E58CCBB21A13C09FFD3A2170FB233049D669C360ADF98258B3DD04C0C28D036585BBD76498C0192033AD38306CDCB9478FD74B4BE3E03D59F3C315521EA0FA289A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF56708A9329D23933702083CD6935EDE8434B31933E33F3CA4EA0E47E62CC73BC35D2B37F71B9593FD9FEB57BB4839A67877D7852D1AAA961D1B0D5929761BD64701DBBDD51CFA25B5E5B3EA740BFBCAAD1305807E2524C86E549D34A0D5AD11F3722D83246973CE8F623EF15320FEBD6F8A90AFFBD547ECC4A7E0A38DADB65FFF85A60D01A8F5E6C8
// REVISION: 1.0
// GUID: 898507E8-1E83-4B9D-8AAB-0D0CD08021CA
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\lib_mcu\power\power_drv.c
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file contains the Power and clock management driver routines.
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
#include "power_drv.h"


//_____ D E C L A R A T I O N ______________________________________________


//! This function write the CPU prescaler register to a define value
//!
//! @param U8 the precaler value to be written
//!
#ifndef __GNUC__
// Ignored if IAR compiler optimization option "Always do cross call optimization" is enabled
#pragma optimize=none 
void Set_cpu_prescaler(U8 x)
{
   U8 save_int=Get_interrupt_state();
   Disable_interrupt();
   CLKPR=(1<<CLKPCE);
   CLKPR=x;
   if(save_int) { Enable_interrupt(); }
}
#endif


//! This function makes the AVR core enter power down mode.
//!
void set_power_down_mode(void)
{
   Setup_power_down_mode();
   Sleep_instruction();
}


//! This function makes the AVR core enter idle mode.
//!
void set_idle_mode(void)
{
   Setup_idle_mode();
   Sleep_instruction();
}


//! This function makes the AVR core enter adc noise reduction mode.
//!
void set_adc_noise_reduction_mode(void)
{
   Setup_adc_noise_reduction_mode();
   Sleep_instruction();
}


//! This function makes the AVR core enter power save mode.
//!
void set_power_save_mode(void)
{
   Setup_power_save_mode();
   Sleep_instruction();
}


//! This function makes the AVR core enter standby mode.
//!
void set_standby_mode(void)
{
   Setup_standby_mode();
   Sleep_instruction();
}


//! This function makes the AVR core enter extended standby mode.
//!
void set_ext_standby_mode(void)
{
   Setup_ext_standby_mode();
   Sleep_instruction();
}


//! This function makes the AVR selects the EXTERNAL clock source (CRYSTAL)
//!
void Clock_switch_external(void)
{
  Enable_external_clock();
  while (!External_clock_ready());
  Select_external_clock();
  Disable_RC_clock();
}


//! This function makes the AVR selects the INTERNAL clock source (RC)
//!
void Clock_switch_internal(void)
{
  Enable_RC_clock();
  while (!RC_clock_ready());
  Select_RC_clock();
  Disable_external_clock();
}
