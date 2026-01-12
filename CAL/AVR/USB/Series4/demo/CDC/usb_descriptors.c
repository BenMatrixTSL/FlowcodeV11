// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D57DF507285C9C50725F499CC7EBAC12FB7CEFEFE752EDAF102944149DFB642A44555DE2D1306A6AA2C335C4C1A1F6B0E84C583A04AB25A1C66E2CF8008F71C5299A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF56A7A1675A8A26E4A239184B75D7C857969D3DB573038A1821564189BF3988DEE6B38D29D0F9747D0913FD205237B7EF85996B0099CC67601C5F8F849205328509CAE58172BDB372AF99EE35CF88E4B443311CE7DEFFC0EFB549D34A0D5AD11F3BFFBC46AD80324E90BBF2721E06B3D01041F889356645EB976D3E34736BD7539F516F4BDFF4A1CBE
// REVISION: 1.0
// GUID: 48C8B8C4-E088-4C2E-BCBA-3DD15C125F15
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\demo\CDC\usb_descriptors.c
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief USB parameters.
//!
//!  This file contains the usb parameters that uniquely identify the
//!  application through descriptor tables.
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
#include "conf_usb.h"

#include "lib_mcu/usb/usb_drv.h"
#include "usb_descriptors.h"
#include "modules/usb/device_chap9/usb_standard_request.h"
#include "usb_specific_request.h"
#if ((USB_DEVICE_SN_USE==ENABLE) && (USE_DEVICE_SN_UNIQUE==ENABLE))
#include "lib_mcu/flash/flash_drv.h"
#endif

//_____ M A C R O S ________________________________________________________




//_____ D E F I N I T I O N ________________________________________________

// usb_user_device_descriptor
code S_usb_device_descriptor usb_dev_desc =
{
  sizeof(usb_dev_desc)
, DESCRIPTOR_DEVICE
, Usb_write_word_enum_struc(USB_SPECIFICATION)
, DEVICE_CLASS
, DEVICE_SUB_CLASS
, DEVICE_PROTOCOL
, EP_CONTROL_LENGTH
, Usb_write_word_enum_struc(VENDOR_ID)
, Usb_write_word_enum_struc(PRODUCT_ID)
, Usb_write_word_enum_struc(RELEASE_NUMBER)
, MAN_INDEX
, PROD_INDEX
, SN_INDEX
, NB_CONFIGURATION
};

// usb_user_configuration_descriptor FS
code S_usb_user_configuration_descriptor usb_conf_desc = {
 { sizeof(S_usb_configuration_descriptor)
 , DESCRIPTOR_CONFIGURATION
 , Usb_write_word_enum_struc(sizeof(S_usb_user_configuration_descriptor))
 , NB_INTERFACE
 , CONF_NB
 , CONF_INDEX
 , CONF_ATTRIBUTES
 , MAX_POWER
 }
 ,
 { sizeof(S_usb_interface_descriptor)
 , DESCRIPTOR_INTERFACE
 , INTERFACE_NB_TEMP
 , ALTERNATE_TEMP
 , NB_ENDPOINT_TEMP
 , INTERFACE_CLASS_TEMP
 , INTERFACE_SUB_CLASS_TEMP
 , INTERFACE_PROTOCOL_TEMP
 , INTERFACE_INDEX_TEMP
 }
 ,
 { 0x05, 0x24, 0x00, 0x10, 0x01, 0x05, 0x24, 0x01, 0x03, 0x01, 0x04, 0x24, 0x02, 0x06, 0x05, 0x24, 0x06, 0x00, 0x01 }
 ,
 { sizeof(S_usb_endpoint_descriptor)
 , DESCRIPTOR_ENDPOINT
 , ENDPOINT_NB_TEMP3
 , EP_ATTRIBUTES_TEMP3
 , Usb_write_word_enum_struc(EP_SIZE_TEMP3)
 , EP_INTERVAL_TEMP3
 }
 ,
 { sizeof(S_usb_interface_descriptor)
 , DESCRIPTOR_INTERFACE
 , INTERFACE_NB_SECOND_TEMP
 , ALTERNATE_SECOND_TEMP
 , NB_ENDPOINT_SECOND_TEMP
 , INTERFACE_CLASS_SECOND_TEMP
 , INTERFACE_SUB_CLASS_SECOND_TEMP
 , INTERFACE_PROTOCOL_SECOND_TEMP
 , INTERFACE_INDEX_SECOND_TEMP
 }
 ,
 { sizeof(S_usb_endpoint_descriptor)
 , DESCRIPTOR_ENDPOINT
 , ENDPOINT_NB_TEMP1
 , EP_ATTRIBUTES_TEMP1
 , Usb_write_word_enum_struc(EP_SIZE_TEMP1)
 , EP_INTERVAL_TEMP1
 }
 ,
 { sizeof(S_usb_endpoint_descriptor)
 , DESCRIPTOR_ENDPOINT
 , ENDPOINT_NB_TEMP2
 , EP_ATTRIBUTES_TEMP2
 , Usb_write_word_enum_struc(EP_SIZE_TEMP2)
 , EP_INTERVAL_TEMP2
 }
};



                                      // usb_user_manufacturer_string_descriptor
code S_usb_manufacturer_string_descriptor usb_user_manufacturer_string_descriptor = {
  sizeof(usb_user_manufacturer_string_descriptor)
, DESCRIPTOR_STRING
, USB_MANUFACTURER_NAME
};


                                      // usb_user_product_string_descriptor

code S_usb_product_string_descriptor usb_user_product_string_descriptor = {
  sizeof(usb_user_product_string_descriptor)
, DESCRIPTOR_STRING
, USB_PRODUCT_NAME
};


                                      // usb_user_serial_number
#if (USB_DEVICE_SN_USE==ENABLE)
code S_usb_serial_number usb_user_serial_number = {
#if (USE_DEVICE_SN_UNIQUE==ENABLE)
  sizeof(usb_user_serial_number)+4*SN_LENGTH
, DESCRIPTOR_STRING
#else
sizeof(usb_user_serial_number)
, DESCRIPTOR_STRING
, USB_SERIAL_NUMBER
#endif
};
#endif

                                      // usb_user_language_id

code S_usb_language_id usb_user_language_id = {
  sizeof(usb_user_language_id)
, DESCRIPTOR_STRING
, Usb_write_word_enum_struc(LANGUAGE_ID)
};

