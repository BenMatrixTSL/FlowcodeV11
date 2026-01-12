// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D52BD23D2C6849BCE08F0CFEEA01D751FFC1BE99401A0B4FC6AABEAF885E37D8E0805E1120C22E39DEE884FDA6AA33824CF9299EA9B8A531B690004BD7593D95913A7C4832BD713AD85B78888D940FC140F704085AD00238B26502E3546407E3F39A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5C83C94D066A874989D006C6F76ADF3AC9D0E1269ED5D97C7E074B1C3360506024647EA1A41B78589E72CA24D9049D91AD203A564B34AC28C783D61F2304A05FFD722340D56707630962CD25123AFBF0A32ABD86F69D29E03549D34A0D5AD11F39AE8756230EDD2C4F9562D78B32464EDBD9C3E3BE3CE1E2F76D3E34736BD7539F516F4BDFF4A1CBE
// REVISION: 1.0
// GUID: 196EABD9-F464-4182-9911-24E2D39BDF71
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\modules\usb\device_chap9\usb_device_task.c
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file manages the USB device controller.
//!
//!  The USB task checks the income of new requests from the USB Host.
//!  When a Setup request occurs, this task will launch the processing
//!  of this setup contained in the usb_standard_request.c file.
//!  Other class specific requests are also processed in this file.
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

//_____  I N C L U D E S ___________________________________________________

#include "config.h"
#include "conf_usb.h"
#include "usb_device_task.h"
#include "modules/usb/usb_task.h"
#include "lib_mcu/usb/usb_drv.h"
#include "usb_descriptors.h"
#include "modules/usb/device_chap9/usb_standard_request.h"
#include "lib_mcu/pll/pll_drv.h"
#ifdef USE_USB_AUTOBAUD
#include "lib_mcu/wdt/wdt_drv.h"
#endif

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________

//!
//! Public : (bit) usb_connected
//! usb_connected is set to TRUE when VBUS has been detected
//! usb_connected is set to FALSE otherwise
//!/
bit   usb_connected=FALSE;

//!
//! Public : (bit) usb_suspended
//! usb_suspended is set to TRUE when USB is in suspend mode
//! usb_suspended is set to FALSE otherwise
//!/
bit   usb_suspended=FALSE;




//!
//! Public : (U8) usb_configuration_nb
//! Store the number of the USB configuration used by the USB device
//! when its value is different from zero, it means the device mode is enumerated
//! Used with USB_DEVICE_FEATURE == ENABLED only
//!/
extern U8  usb_configuration_nb;

//_____ D E C L A R A T I O N S ____________________________________________

//!
//! @brief This function initializes the USB device controller and system interrupt
//!
//! This function enables the USB controller and init the USB interrupts.
//! The aim is to allow the USB connection detection in order to send
//! the appropriate USB event to the operating mode manager.
//!
//! @param none
//!
//! @return none
//!
//!/
void usb_device_task_init(void)
{
   Usb_disable();
   Usb_enable();
#if (VBUS_SENSING_IO == ENABLED)
   Usb_vbus_sense_init();   // init. the I/O used for Vbus sensing
#endif
}

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
void usb_start_device (void)
{
   Usb_freeze_clock();
#ifndef USE_USB_AUTOBAUD
   Pll_start_auto();
#else
   usb_autobaud();
#endif
   Wait_pll_ready();
   Disable_interrupt();
   Usb_unfreeze_clock();
   Usb_attach();
#if (USB_RESET_CPU == ENABLED)
   Usb_reset_all_system();
#else
   Usb_reset_macro_only();
#endif
   usb_init_device();         // configure the USB controller EP0
   Usb_enable_suspend_interrupt();
   Usb_enable_reset_interrupt();
   Enable_interrupt();
}

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
void usb_device_task(void)
{
 
   if (usb_connected == FALSE)
   {
     #if (VBUS_SENSING_IO == ENABLED)
     if (Is_usb_vbus_on())    // check if Vbus ON to attach
     {
       Usb_enable();
       usb_connected = TRUE;
       usb_start_device();
       Usb_vbus_on_action();
     }
     #else
     usb_connected = TRUE;    // attach if application is not self-powered
     usb_start_device();
     Usb_vbus_on_action();
     #endif
   }

   #if (VBUS_SENSING_IO == ENABLED)
   if ((usb_connected == TRUE) && Is_usb_vbus_off())  // check if Vbus OFF to detach
   {
     Usb_detach();
     Usb_disable();
     Stop_pll();
     usb_connected = FALSE;
     usb_configuration_nb=0;
   }
   #endif

   if(Is_usb_event(EVT_USB_RESET))
   {
      Usb_ack_event(EVT_USB_RESET);
      Usb_reset_endpoint(0);
      usb_configuration_nb=0;
   }

   // Here connection to the device enumeration process
   Usb_select_endpoint(EP_CONTROL);
   if (Is_usb_receive_setup())
   {
      usb_process_request();
   }
}


#ifdef USE_USB_AUTOBAUD
#warning CAUTION Preliminary USB autobaud for USB DFU bootloader Only... 
//! @brief USB devive autobaud
//!
//! This function performs an autobaud configuration for the USB interface.
//! the autobaud function performs the configuration of the PLL dedicated to the USB interface.
//! The autobaud algorithm consists in trying each USB PLL until the correct detection of Start
//! of Frame (USB SOF).
//!
//! @warning Code:?? bytes (function code length)
//!
//! @param none
//!
//! @return none
void usb_autobaud(void)
{

   U16 count_rc=0;

   volatile U16 tempo;
   
   wdtdrv_interrupt_enable(WDTO_16MS);
   TCCR1B=0x00; TCCR1A=0x00;
   TCNT1=0x00;  TIFR1=0x01;            //! Clear TOV2 flag and counter value
   
   TCCR1B|=(1<<CS01) |(1<<CS00);       // ClkIO/64, with prescaler /2 -> XTAL/128
   WDTCKD|=(1<<WDEWIE);
   while(Is_not_wdt_early_warning());
   TCCR1B=0;
   wdtdrv_disable();
   WDTCKD|=(1<<WDEWIF);                // Clear early warning flag
   WDTCKD=0;                           // Clear early warning flag
   
   count_rc=TCNT1;
   TCCR1B=0x00; TCCR1A=0x00;
   TCNT1=0x00;  TIFR1=0x01;            //! Clear TOV2 flag and counter value  
   if(count_rc>1500)                   // 16MHz/128 with 16ms watchdog gives 2000 ticks
   {
      Start_pll(PLLx03);               //! FOSC 16MHz
   }
   else
   {
      Start_pll(PLLx06);                //! FOSC 8MHz
   }
   
}
#endif

