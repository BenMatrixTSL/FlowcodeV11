// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5E971021840B65CB4A3D8D01D6B7FD05CEEE65B670558DA072C98DB381E8CD9FC7143BB694204BC6128FD796418B044CE526D54A06FE01DE75A26879F7B7281F2DE85D3FED9F96D0A380EA7B34665D3989A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF509DC08CEC5FAD215F0AE0FAF8B3AECCAF07F03AA775360CCADB7DB2058395883070A728F7C9444ECBD281432FFA117F95AFFF7F1FCD3996101B48807F91CE94AA5B44D5DD54311E47ED64DEFC1C371B63311CE7DEFFC0EFB549D34A0D5AD11F3B223B45A2BEACC3DF249D0BB2119CC03049D3C17D013D1C43B2CD482BC0EE54D2A52B2CE0373A37B
// REVISION: 1.0
// GUID: D7FCFADB-A134-428A-8229-9A8EFD591DC3
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series67\demo\CDC\usb_specific_request.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief Specific enumeration process requests header file
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

