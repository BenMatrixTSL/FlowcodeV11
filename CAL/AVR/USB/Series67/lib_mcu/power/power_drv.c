// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D583C45B8AED270FE40481B7BD05EB725315623B87F333C9F691565E54C17F346C41DC2730D8ECE9EF586B6658CF571A4D2C6AC979ED4B39B809E10EFDAB87B8629A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5E635A81E814375B29B8C6FEA9A8F1E77EE8D4CF8A58656CB808F50F23CAAD631F8B27B60C49D2DA403A17C092B08C4C6E31A6CC9A682B4D581E86932142F5B149E76F90194548C1C877202C02DDF24942E26F616D3C6B8F8549D34A0D5AD11F361D932EBECEAAD1BE93B886765EA6DE7A16E1266250E41C8F0B9F6FEC6D77E3F44FB7D5555DAC58F
// REVISION: 1.0
// GUID: F9FB248D-F6F1-463E-9F05-61C80F93161C
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series67\lib_mcu\power\power_drv.c
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file contains the Power and clock management driver routines.
//!
//! - Compiler:           IAR EWAVR and GNU GCC for AVR
//! - Supported devices:  AT90USB1287, AT90USB1286, AT90USB647, AT90USB646
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

