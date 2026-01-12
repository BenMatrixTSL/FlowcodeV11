// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5DB37BF5913B6223C6A30E26220D7A577C1BE99401A0B4FC6AABEAF885E37D8E0A65EC3BE4AA460863F9C4E94B61908AF011496AE222D8A5BBDA9DACA3792E7719A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5DEF9B18ACC578E23084AA6151CD848FE872BFFA7C013F45018E99D8EB0492C385C5EB95635B22C2391B31B1E08592DA8D19723CE6597C85E54D64CAE91A9E4068A29E4BFF551206B7EEA6A3DFE0A661AF0ECE8BF552EA248549D34A0D5AD11F3469EACABB0B78807191FC52F7BA31DB6515CC412C02FEB6A6CFC63B583D3C0065E5746CE888A1719
// REVISION: 1.0
// GUID: D8EE8704-80D7-4625-9865-05A78BA23BED
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\modules\usb\usb_task.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file contains the function declarations
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

