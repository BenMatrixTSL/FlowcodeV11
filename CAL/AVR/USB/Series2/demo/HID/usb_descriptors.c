// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D53F5F6A18E6F66E466F9DB641FCB79B707EABDD0A6647EDB294D49642477A5A99555DE2D1306A6AA2C335C4C1A1F6B0E84C583A04AB25A1C66E2CF8008F71C5299A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5AA51C1183D8C2CAE03C9FC9F1F8A99F00CDD22D7C9B7ABBDDD9945DDAEB2C46FAC129E01CCE61099A05781B5DC05A0D4039D49B795671DDDB41526100AC4741740B29F0AA26FF5709730999B80433AC39368807D9AC6CCC2549D34A0D5AD11F3823A3EA7CA51CFC9E2A2C09F75C562CB1CBD120381DB960C07369D99911C23D5D43797C197BFDEC5
// REVISION: 1.0
// GUID: 726D4E1A-DB37-439E-BE3D-0079ECDAA66B
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\demo\HID\usb_descriptors.c
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief USB parameters.
//!
//!  This file contains the usb parameters that uniquely identify the
//!  application through descriptor tables.
//!
//! - Compiler:           IAR EWAVR and GNU GCC for AVR
//! - Supported devices:  USB Series 2
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
 , INTERFACE_NB_HID
 , ALTERNATE_HID
 , NB_ENDPOINT_HID
 , INTERFACE_CLASS_HID
 , INTERFACE_SUB_CLASS_HID
 , INTERFACE_PROTOCOL_HID
 , INTERFACE_INDEX_HID
 }
 ,
 { sizeof(S_usb_hid_descriptor)
 , HID_DESCRIPTOR
 , HID_BDC
 , HID_COUNTRY_CODE
 , HID_CLASS_DESC_NB
 , HID_DESCRIPTOR_TYPE
 , Usb_write_word_enum_struc(sizeof(S_usb_hid_report_descriptor))
 }
 ,
 { sizeof(S_usb_endpoint_descriptor)
 , ENDPOINT_DESCRIPTOR
 , ENDPOINT_NB_1
 , EP_ATTRIBUTES_1
 , Usb_write_word_enum_struc(EP_SIZE_1)
 , EP_INTERVAL_1
 }
#if MX_HID_RX_SZ > 0
 ,
 { sizeof(S_usb_endpoint_descriptor)
 , ENDPOINT_DESCRIPTOR
 , ENDPOINT_NB_2
 , EP_ATTRIBUTES_2
 , Usb_write_word_enum_struc(EP_SIZE_2)
 , EP_INTERVAL_2
 }
#endif
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


                                      // usb_hid report descriptor
									  
code S_usb_hid_report_descriptor usb_hid_report_descriptor = MX_HID_REPORT_DESCRIPT;
