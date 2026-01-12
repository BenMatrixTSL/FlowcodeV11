// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D53F5F6A18E6F66E466F9DB641FCB79B707EABDD0A6647EDB294D49642477A5A999F49B15EA4FA1A5CBC04149400627248F44901BA6D6A39C58439069F5482766A2CD5FA18BFE3470540B49F2B949A5DD59A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5DAD18FA955B4FDE3F635E7C89C80E1A677AA8CE34948A32647B6C6F2640489C0D43882F5354BBABB7841C7B65F19D46D777EC0708E878E5962BD9606B30095255AEE96107B515E79FA8D04CF3E9384CF3A8F302FE3725672549D34A0D5AD11F30DCD083097F3B1A1DDDA629B7322E0BF3BD3B7BBA164BC6018D34502288D3DAB5F5FD00D1D4C038A
// REVISION: 1.0
// GUID: 6DADF4A4-6731-461D-A499-778AD3BF3C41
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\demo\HID\usb_specific_request.h
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
void  hid_get_report();
void  hid_set_report();
void usb_hid_get_interface(void);
void usb_hid_set_idle(void);
void hid_get_hid_descriptor(void);


// ____ T Y P E  D E F I N I T I O N _______________________________________

#endif

