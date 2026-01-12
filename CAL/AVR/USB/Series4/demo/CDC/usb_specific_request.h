// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D57DF507285C9C50725F499CC7EBAC12FB7CEFEFE752EDAF102944149DFB642A449F49B15EA4FA1A5CBC04149400627248F44901BA6D6A39C58439069F5482766A2CD5FA18BFE3470540B49F2B949A5DD59A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF555FE94A42DAB974BE69EB04AD658E32D9775E11F5290F8168F249A461BB185903DCABEF55EE4D00E2F6E47ECE2E57401D48C5A6EBD7D3443D089DB8ABF772F37E1396429F3A668B7E46E5924AF1AD61F6CD6DFE1FFA9EED0549D34A0D5AD11F3A3DBA298769E2E9D0583569D6F223113F54ED10F05D5D9FD9A437E7E2D43FD26DF891DB3086C82D6
// REVISION: 1.0
// GUID: AFE38B80-4396-4E8A-B307-CC1A9D1AAEBD
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\demo\CDC\usb_specific_request.h
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

