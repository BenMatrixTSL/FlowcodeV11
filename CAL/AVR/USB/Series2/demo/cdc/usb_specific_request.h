// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D53F5F6A18E6F66E466F9DB641FCB79B700E82260F3703D44E9748FA55286B73229F49B15EA4FA1A5CBC04149400627248F44901BA6D6A39C58439069F5482766A2CD5FA18BFE3470540B49F2B949A5DD59A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5A45D0F166BB541B1A9FDFD26D4D8775359626F4D4427D98E42DC4C04AED95A373DD01A6D90701935B532469632CDC644C6B030A4EF241F56B452B5267006C3FAA0CB0C1464832CF84A1CB7C20951E099DF8A375CE59CE163549D34A0D5AD11F3B17D24CD97C0E2FDA0850785D64A3373387117F49C7A8FA735929AA8E37C906168E257DA63DC3B7B
// REVISION: 1.0
// GUID: 8B1FA4D0-8E2C-4C88-9FEC-C968A28BDDA1
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\demo\cdc\usb_specific_request.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief Specific enumeration process requests header file
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

#ifndef _USB_SPECIFIC_REQUEST_H_
#define _USB_SPECIFIC_REQUEST_H_

//_____ I N C L U D E S ____________________________________________________

#include "config.h"


//_____ M A C R O S ________________________________________________________

extern  code S_usb_device_descriptor usb_dev_desc;
extern  code S_usb_user_configuration_descriptor usb_conf_desc;
extern  code S_usb_manufacturer_string_descriptor usb_user_manufacturer_string_descriptor;
extern  code S_usb_product_string_descriptor usb_user_product_string_descriptor;
#if (USB_DEVICE_SN_USE==ENABLE)
extern  code S_usb_serial_number usb_user_serial_number;
#endif
extern  code S_usb_language_id usb_user_language_id;


//_____ D E F I N I T I O N ________________________________________________

Bool  usb_user_read_request      ( U8, U8 );
void  usb_user_endpoint_init     ( U8 );
U8    usb_user_interface_get     ( U16 wInterface );
void  usb_user_interface_reset   ( U16 wInterface, U8 alternate_setting );
Bool  usb_user_get_descriptor    ( U8 , U8 );
void  cdc_get_line_coding();
void  cdc_set_line_coding();
void  cdc_set_control_line_state(U16);   
void  cdc_send_break(U16);
Bool  cdc_update_serial_state();   

// ____ T Y P E  D E F I N I T I O N _______________________________________

typedef struct
{
   U32 dwDTERate;
   U8 bCharFormat;
   U8 bParityType;
   U8 bDataBits;
}S_line_coding;

// type for set control line state message
// cdc spec 1.1 chapter 6.2.14
typedef union
{
   U8 all;
   struct {
      U8 DTR:1;
      U8 RTS:1;
      U8 unused:6;
   };
}S_line_status;

// type for hardware handshake support 
// cdc spec 1.1 chapter 6.3.5
typedef union
{
   U16 all;
   struct {
      U16 bDCD:1;
      U16 bDSR:1;
      U16 bBreak:1;
      U16 bRing:1;
      U16 bFraming:1;
      U16 bParity:1;
      U16 bOverRun:1;
      U16 reserved:9;
   };
}S_serial_state;
   

#endif

