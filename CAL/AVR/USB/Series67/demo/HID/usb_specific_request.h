// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5E971021840B65CB4A3D8D01D6B7FD05CDF4ADE460CC6832CA0A01C4FE0C27A507143BB694204BC6128FD796418B044CE526D54A06FE01DE75A26879F7B7281F2DE85D3FED9F96D0A380EA7B34665D3989A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF525F92385BA6D8138331F6C2AFF5BF414EF9658CB3143D7DABFF600D2AEA2CC9B672C6F3F55E62F4892FF630761A65ED5819DF000351F6297AB7DDEF4C13FD7FF884A061D59ED7E81948FDBDAF4BC0F80C118E21ABB5E4EE9549D34A0D5AD11F3421019CD6AA7C8086E0D4B84DDB5DADB498595A5F76D49D5D2AD5B899D5932CF499F10447F50333B
// REVISION: 1.0
// GUID: D59A69CA-C212-449C-8BE4-57F8EAB071A0
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series67\demo\HID\usb_specific_request.h
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

