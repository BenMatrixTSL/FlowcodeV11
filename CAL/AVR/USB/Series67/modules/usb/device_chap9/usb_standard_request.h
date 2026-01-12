// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5452E5B9F9FBCCE45F6091E51280FBE78B5BA3015492E6356D38D596C2A3EE5D6B299C72173C6F3085DED91B107FEE9B2DB3CAFC891DD11A1D92394416A8B4A6284B2B9285900D0386A54D28FCC3116C654C182E63E57F29BA1B905F13DAE5C98DE85D3FED9F96D0A380EA7B34665D3989A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF51E6771A65F48926C47BC65DB39B0D5A413BA68B8A592FEC8772CEEC4F284D64DFE28CB8AAC106FFD107ABB8A8EB480B6EE017205875F14EB7A97C12B94DC7DDE95843389E5D62ACC7DF53A75327D61E2944A36F755ACB4ED549D34A0D5AD11F35D1664A96E7FB16E440ED49AC7323785F8EE31107D61E895B0330AA6FB05B88105A68DA3CE9026E5
// REVISION: 1.0
// GUID: EA65977C-6A95-427F-B662-AD3F786BAF41
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series67\modules\usb\device_chap9\usb_standard_request.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief Process USB device enumeration requests header file.
//!
//!  This file contains the USB endpoint 0 management routines corresponding to
//!  the standard enumeration process (refer to chapter 9 of the USB
//!  specification.
//!  This file calls routines of the usb_specific_request.c file for non-standard
//!  request management.
//!  The enumeration parameters (descriptor tables) are contained in the
//!  usb_descriptors.c file.
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

#ifndef _USB_STANDARD_REQUEST_H_
#define _USB_STANDARD_REQUEST_H_

//_____ I N C L U D E S ____________________________________________________

#include "modules/usb/usb_task.h"
#include "usb_descriptors.h"

//_____ M A C R O S ________________________________________________________

//_____ S T A N D A R D    D E F I N I T I O N S ___________________________

//! @defgroup std_request USB device standard requests decoding
//! @{



        // Device State
#define ATTACHED                          0
#define POWERED                           1
#define DEFAULT                           2
#define ADDRESSED                         3
#define CONFIGURED                        4
#define SUSPENDED                         5

#define USB_REMOTE_WAKEUP       1
#define OTG_B_HNP_ENABLE        3
#define OTG_A_HNP_SUPPORT       4
#define OTG_A_ALT_HNP_SUPPORT   5


//_____ D E C L A R A T I O N ______________________________________________

   //! @brief Returns true when device connected and correctly enumerated with an host.
   //! The device high level application should tests this before performing any applicative requests
#define Is_device_enumerated()            ((usb_configuration_nb!=0)   ? TRUE : FALSE)
#define Is_device_not_enumerated()        ((usb_configuration_nb!=0)   ? FALSE : TRUE)




//! @brief This function reads the SETUP request sent to the default control endpoint
//! and calls the appropriate function. When exiting of the usb_read_request
//! function, the device is ready to manage the next request.
//!
//! If the received request is not supported or a none USB standard request, the function
//! will call for custom decoding function in usb_specific_request module.
//!
//! @param none
//!
//! @return none
//! @note list of supported requests:
//! SETUP_GET_DESCRIPTOR
//! SETUP_GET_CONFIGURATION
//! SETUP_SET_ADDRESS
//! SETUP_SET_CONFIGURATION
//! SETUP_CLEAR_FEATURE
//! SETUP_SET_FEATURE
//! SETUP_GET_STATUS
//!
void    usb_process_request( void);

//! @brief This function manages the remote wakeup generation to wake up the host controlle.
//!
//! If the received request is not supported or a none USB standard request, the function
//! will call for custom decoding function in usb_specific_request module.
//!
//! @param none
//!
//! @return none
//!
void     usb_generate_remote_wakeup(void);

extern  U8   usb_configuration_nb;
extern  U8   remote_wakeup_feature;


#if (USE_DEVICE_SN_UNIQUE==ENABLE)
extern  U8   f_get_serial_string;
#endif

//! @}

#endif  // _USB_STANDARD_REQUEST_H_

