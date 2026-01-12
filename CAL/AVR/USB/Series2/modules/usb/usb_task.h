// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D52BD23D2C6849BCE08F0CFEEA01D751FFC1BE99401A0B4FC6AABEAF885E37D8E0A65EC3BE4AA460863F9C4E94B61908AF011496AE222D8A5BBDA9DACA3792E7719A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF53DAE20C79A339187A3B9D4D2D7EA478EE218C606A3EBA849D59CE69084B2C7A7ED38E910FDA76A6449418EF1D9B788B1DBE5E550031F69B60C4AD3C246CFE3D52CEE28AEAC103A0CD7BFCEA0FBAB231422A61D2BBA84C14E549D34A0D5AD11F39193F486BEEEC1655A762869B8453E44814516859F3616EBA3608A0B0CE69F969622A912E6E6A2FB
// REVISION: 1.0
// GUID: E9B83FE3-3F8A-4888-88B0-2D60381C0050
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\modules\usb\usb_task.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file contains the function declarations
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

#ifndef _USB_TASK_H_
#define _USB_TASK_H_

//! @defgroup usb_task USB task entry point
//! @{

//_____ I N C L U D E S ____________________________________________________


//_____ M A C R O S ________________________________________________________

      //! @defgroup usb_software_evts USB software Events Management
      //! Macros to manage USB events detected under interrupt
      //! @{
#define Usb_send_event(x)               (g_usb_event |= (1<<x))
#define Usb_ack_event(x)                (g_usb_event &= ~(1<<x))
#define Usb_clear_all_event()           (g_usb_event = 0)
#define Is_usb_event(x)                 ((g_usb_event & (1<<x)) ? TRUE : FALSE)
#define Is_not_usb_event(x)             ((g_usb_event & (1<<x)) ? FALSE: TRUE)

#define EVT_USB_POWERED               1         // USB plugged
#define EVT_USB_UNPOWERED             2         // USB un-plugged
#define EVT_USB_DEVICE_FUNCTION       3         // USB in device
#define EVT_USB_HOST_FUNCTION         4         // USB in host
#define EVT_USB_SUSPEND               5         // USB suspend
#define EVT_USB_WAKE_UP               6         // USB wake up
#define EVT_USB_RESUME                7         // USB resume
#define EVT_USB_RESET                 8         // USB reset
      //! @}

   //! @defgroup std_req_values Standard requests defines
   //! @{
   #define GET_STATUS                     0x00
   #define GET_DEVICE                     0x01
   #define CLEAR_FEATURE                  0x01           //!< see FEATURES below
   #define GET_STRING                     0x03
   #define SET_FEATURE                    0x03           //!< see FEATURES below
   #define SET_ADDRESS                    0x05
   #define GET_DESCRIPTOR                 0x06
   #define SET_DESCRIPTOR                 0x07
   #define GET_CONFIGURATION              0x08
   #define SET_CONFIGURATION              0x09
   #define GET_INTERFACE                  0x0A
   #define SET_INTERFACE                  0x0B
   #define SYNCH_FRAME                    0x0C

   #define GET_DEVICE_DESCRIPTOR             1
   #define GET_CONFIGURATION_DESCRIPTOR      4

   #define REQUEST_DEVICE_STATUS          0x80
   #define REQUEST_INTERFACE_STATUS       0x81
   #define REQUEST_ENDPOINT_STATUS        0x82
   #define ZERO_TYPE                      0x00
   #define INTERFACE_TYPE                 0x01
   #define ENDPOINT_TYPE                  0x02

                     // Descriptor Types
   #define DEVICE_DESCRIPTOR                     0x01
   #define CONFIGURATION_DESCRIPTOR              0x02
   #define STRING_DESCRIPTOR                     0x03
   #define INTERFACE_DESCRIPTOR                  0x04
   #define ENDPOINT_DESCRIPTOR                   0x05
   #define DEVICE_QUALIFIER_DESCRIPTOR           0x06
   #define OTHER_SPEED_CONFIGURATION_DESCRIPTOR  0x07



                    // Standard Features
   #define FEATURE_DEVICE_REMOTE_WAKEUP   0x01
   #define FEATURE_ENDPOINT_HALT          0x00

   #define TEST_J                         0x01
   #define TEST_K                         0x02
   #define TEST_SEO_NAK                   0x03
   #define TEST_PACKET                    0x04
   #define TEST_FORCE_ENABLE              0x05


                     // Device Status
   #define BUS_POWERED                       0
   #define SELF_POWERED                      1

   //! @}

#define USB_MODE_UNDEFINED            0x00
#define USB_MODE_HOST                 0x01
#define USB_MODE_DEVICE               0x02

//_____ D E C L A R A T I O N S ____________________________________________

extern volatile U16 g_usb_event;
extern U8 g_usb_mode;

/**
 * @brief This function initializes the USB proces.
 *
 *  This function enables the USB controller and init the USB interrupts.
 *  The aim is to allow the USB connection detection in order to send
 *  the appropriate USB event to the operating mode manager.
 *  Depending on the mode supported (HOST/DEVICE/DUAL_ROLE) the function
 *  calls the corespong usb mode initialization function
 *
 *  @param none
 *
 *  @return none
 */
void usb_task_init     (void);

/**
 *  @brief Entry point of the USB mamnagement
 *
 *  Depending on the mode supported (HOST/DEVICE/DUAL_ROLE) the function
 *  calls the corespong usb management function
 *
 *  @param none
 *
 *  @return none
*/
void usb_task          (void);

extern volatile U8 private_sof_counter;



//! @}

#endif /* _USB_TASK_H_ */

