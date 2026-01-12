// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D52BD23D2C6849BCE08F0CFEEA01D751FFC1BE99401A0B4FC6AABEAF885E37D8E0805E1120C22E39DEE884FDA6AA33824CF9299EA9B8A531B690004BD7593D95913A7C4832BD713AD85B78888D940FC140FF49D5420975B3BAACE3A039CEC7C4409A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF53CA23F3BB738F129D662C20B910B41D1D67C8A0FB922A20B4CB240774B1F6E828AE362408AD799118684DD2E8E3ACC71EDA671FB72F984EE614BA4B07F2E099F65C2700EC65B82C8F9B5F4705F8EB4549368807D9AC6CCC2549D34A0D5AD11F35773E8FF9F34C6688682CF31C29BAF2BC29559F084503DDE61112B2378F6127E5D3A7ED706D09BBA
// REVISION: 1.0
// GUID: E8561A71-0FFF-4C36-B7BF-0C1ACE6C3DC0
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\modules\usb\device_chap9\usb_device_task.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file contains the function declarations for USB device task
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

#ifndef _USB_DEVICE_TASK_H_
#define _USB_DEVICE_TASK_H_

//! @defgroup usb_device_task USB device task
//! @{

//_____ I N C L U D E S ____________________________________________________


//_____ M A C R O S ________________________________________________________


//_____ D E C L A R A T I O N S ____________________________________________


//!
//! Public : (bit) usb_suspended
//! usb_suspended is set to TRUE when USB is in suspend mode
//! usb_suspended is set to FALSE otherwise
//!/
extern bit   usb_suspended;

//! Public : (bit) usb_connected
//! usb_connected is set to TRUE when VBUS has been detected
//! usb_connected is set to FALSE otherwise
//!/
extern bit   usb_connected;


//!
//! @brief This function initializes the USB device controller.
//!
//! This function enables the USB controller and init the USB interrupts.
//! The aim is to allow the USB connection detection in order to send
//! the appropriate USB event to the operating mode manager.
//!
//!
//! @param none
//!
//! @return none
//!
void usb_device_task_init     (void);

//!
//! @brief This function initializes the USB device controller
//!
//! This function enables the USB controller and init the USB interrupts.
//! The aim is to allow the USB connection detection in order to send
//! the appropriate USB event to the operating mode manager.
//! Start device function is executed once VBUS connection has been detected
//! either by the VBUS change interrupt either by the VBUS high level
//!
//! @param none
//!
//! @return none
//!
void usb_start_device  (void);

//! @brief Entry point of the USB device mamagement
//!
//! This function is the entry point of the USB management. Each USB
//! event is checked here in order to launch the appropriate action.
//! If a Setup request occurs on the Default Control Endpoint,
//! the usb_process_request() function is call in the usb_standard_request.c file
//!
//! @param none
//!
//! @return none
void usb_device_task   (void);

#ifdef USE_USB_AUTOBAUD
//! @brief USB based autobaud function
//!
//! This function configures the pll prescaler to get USB functionnnal with current XTAL
//!
//! @param none
//!
//! @return none
void usb_autobaud(void);
#endif

//! @}

#endif /* _USB_DEVICE_TASK_H_ */

