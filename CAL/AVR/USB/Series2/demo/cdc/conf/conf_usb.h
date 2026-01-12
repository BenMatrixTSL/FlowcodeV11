// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D53F5F6A18E6F66E466F9DB641FCB79B702CE4B21FC8957E8F68FFB13AEC3055C7564068C1B21783D675E97A84ECE56D0C14C01C354FBE404183D640563716A67A9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF54CDA56901623E1C10740DACD529846EFA64A7B1A188FBF085AEFD51FD94F14FF7BFFC3099772BB9069108335B9BF5CB810670F072D91E754DE7DDC804283790B6C381F7928E0E84D7D1DA29685A7A167A1B93B6F26A46D89549D34A0D5AD11F3FE0EF2181DB97241BB0EEBA2E3FBFD57771A0BF3372B970C1970AB48E245A709734CC46D5AB08C67
// REVISION: 1.0
// GUID: 89F6F06A-3B0C-4D2D-97E3-13B6DAE70EC3
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\demo\cdc\conf\conf_usb.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file contains the possible external configuration of the USB
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
#ifndef _CONF_USB_H_
#define _CONF_USB_H_

#include "modules/usb/usb_commun.h"
#include "modules/usb/usb_commun_hid.h"
#include "modules/usb/usb_commun_ms.h"
#include "modules/usb/usb_commun_cdc.h"

//! @defgroup usb_general_conf USB application configuration
//!
//! @{


   // _________________ USB MODE CONFIGURATION ____________________________
   //
   //! @defgroup USB_op_mode USB operating modes configuration
   //! defines to enable device or host usb operating modes
   //! supported by the application
   //! @{

      //! @brief ENABLE to activate the device software library support
      //!
      //! Possible values ENABLE or DISABLE
      #define USB_DEVICE_FEATURE          ENABLED

   //! @}

   // _________________ USB REGULATOR CONFIGURATION _______________________
   //
   //! @defgroup USB_reg_mode USB regulator configuration
   //! @{

   //! @brief Enable the internal regulator for USB pads
   //!
   //! When the application voltage is lower than 3.5V, to optimize power consumption
   //! the internal USB pads regulatr can be disabled.
#ifndef USE_USB_PADS_REGULATOR
   #define USE_USB_PADS_REGULATOR   DISABLE      // Possible values ENABLE or DISABLE
#endif
   //! @}



// _________________ DEVICE MODE CONFIGURATION __________________________

   //! @defgroup USB_device_mode_cfg USB device operating mode configuration
   //!
   //! @{

#define USB_DEVICE_SN_USE          DISABLE            // DISABLE
#define USE_DEVICE_SN_UNIQUE       DISABLE            // ignore if USB_DEVICE_SN_USE = DISABLE

#define NB_ENDPOINTS          4  //  number of endpoints in the application including control endpoint
#define EP_TEMP_IN            1
#define EP_TEMP_OUT           2
#define EP_TEMP_INT_IN        3

#define RX_EP    EP_TEMP_OUT
#define TX_EP    EP_TEMP_IN
#define INT_EP   EP_TEMP_INT_IN

#define USB_REMOTE_WAKEUP_FEATURE     DISABLED   //! don't allow remote wake up

#define VBUS_SENSING_IO       DISABLED   //! device will connect directly on reset

#define USB_RESET_CPU         DISABLED   //! an USB reset does not reset the CPU

#define Usb_unicode(a)         ((U16)(a))

   //! @defgroup device_cst_actions USB device custom actions
   //!
   //! @{
   // write here the action to associate to each USB event
   // be carefull not to waste time in order not disturbing the functions
#define Usb_sof_action()         sof_action();
#define Usb_wake_up_action()
#define Usb_resume_action()
#define Usb_suspend_action()
#define Usb_reset_action()
#define Usb_vbus_on_action()
#define Usb_vbus_off_action()
#define Usb_set_configuration_action()
   //! @}

extern void sof_action(void);
   //! @}

//! @}

#endif // _CONF_USB_H_
