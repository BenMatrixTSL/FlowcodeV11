// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5DB37BF5913B6223C6A30E26220D7A577C1BE99401A0B4FC6AABEAF885E37D8E0805E1120C22E39DEE884FDA6AA33824CF9299EA9B8A531B690004BD7593D9591254EF5C168F8ED5953B810363C9B473A08E666AF91957A7326BAA2ECD8B9851F2CD5FA18BFE3470540B49F2B949A5DD59A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5DECE52666BC69B76A9151F01197D7A5EBFCB4CC615EFA06720EDAA7DB7CDDAAB4C6035DCEA0769A6840812759A53B802DC8A797DDA1E2027B5E9E9DBF559BC1EC00F6C9FD5E8881FF09960BE7CB53EA05CA1BEB122F059D7549D34A0D5AD11F354E1874276A2CD41A7DEDC4BDC969212BCF76327986F50F0FC0E9FB60DFEAB887A64FF5F89231504
// REVISION: 1.0
// GUID: 77F33C72-D590-4465-BE62-7D84BD14369A
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\modules\usb\device_chap9\usb_standard_request.h
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

#ifndef _USB_STANDARD_REQUEST_H_
#define _USB_STANDARD_REQUEST_H_

//_____ I N C L U D E S ____________________________________________________

#include "modules/usb/usb_task.h"
#include "usb_descriptors.h"

//_____ M A C R O S ________________________________________________________

//_____ S T A N D A R D    D E F I N I T I O N S ___________________________

//! @defgroup std_request USB device standard  requests decoding
//! @{



        // Device State
#define ATTACHED                          0
#define POWERED                           1
#define DEFAULT                           2
#define ADDRESSED                         3
#define CONFIGURED                        4
#define SUSPENDED                         5

#define USB_REMOTE_WAKEUP       1

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

