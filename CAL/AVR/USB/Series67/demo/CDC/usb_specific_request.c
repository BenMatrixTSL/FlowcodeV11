// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5E971021840B65CB4A3D8D01D6B7FD05CEEE65B670558DA072C98DB381E8CD9FC7143BB694204BC6128FD796418B044CE526D54A06FE01DE75A26879F7B7281F28B9964656A3B4BF8F62144C149A4A8699A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF59A6FC5B02722059BAC2BD4C3A9ACFC52CF76826E10178A4C5626193FB81B790C8043B9DDB834F6694AB3A21EB84F1D7FFF78C467935CD7BF4B3ED86E43F433EDBBE4D3273561FA0D595CC07FCEF1279B06E289E88807B31E549D34A0D5AD11F30CB098B01589FD92A8419FA3150514E029A3F9B45FA2787E
// REVISION: 1.0
// GUID: 6F2A0321-E41A-4285-8372-2FC2B015B2DE
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series67\demo\CDC\usb_specific_request.c
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief user call-back functions
//!
//!  This file contains the user call-back functions corresponding to the
//!  application:
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

//_____ D E F I N I T I O N ________________________________________________

#ifdef __GNUC__
extern PGM_VOID_P pbuffer;
#else
extern U8   code *pbuffer;
#endif
extern U8   data_to_transfer;
extern S_line_coding   line_coding;
extern S_line_status line_status;

// We buffer the old state as it is wize only to send this interrupt message if
// sstate has changed.
extern S_serial_state serial_state;         // actual state
static S_serial_state serial_state_saved;   // buffered previously sent state
volatile U8 usb_request_break_generation=FALSE;


//_____ D E C L A R A T I O N ______________________________________________

//! @breif This function checks the specific request and if known then processes it
//!
//! @param type      corresponding at bmRequestType (see USB specification)
//! @param request   corresponding at bRequest (see USB specification)
//!
//! @return TRUE,  when the request is processed
//! @return FALSE, if the request is'nt know (STALL handshake is managed by the main standard request function).
//!
Bool usb_user_read_request(U8 type, U8 request)
{
   U8  wValue_msb;
   U8  wValue_lsb;

   // Read wValue
   wValue_lsb = Usb_read_byte();
   wValue_msb = Usb_read_byte();

   //** Specific request from Class
   if( USB_SETUP_GET_STAND_INTERFACE == type )
   {
      switch( request )
      {
         case SETUP_GET_DESCRIPTOR:
         switch( wValue_msb ) // Descriptor ID
         {
            default:
            // TODO
            break;
         }
         break;
      }
   }
   if( USB_SETUP_SET_CLASS_INTER == type )
   {
      switch( request )
      {
         default:
         break;
      }
   }
   if( USB_SETUP_GET_CLASS_INTER == type )
   {
      switch( request )
      {
         default:
         break;
      }
   }
   return FALSE;  // No supported request
}


//! @brief This function configures the endpoints
//!
//! @param conf_nb configuration number choosed by USB host
//!
void usb_user_endpoint_init(U8 conf_nb)
{
   usb_configure_endpoint(EP_TEMP_IN,    \
                          TYPE_BULK,     \
                          DIRECTION_IN,  \
                          SIZE_64,       \
                          ONE_BANK,      \
                          NYET_ENABLED);
   usb_configure_endpoint(EP_TEMP_OUT,   \
                          TYPE_BULK,     \
                          DIRECTION_OUT, \
                          SIZE_64,       \
                          ONE_BANK,      \
                          NYET_ENABLED);
   usb_configure_endpoint(EP_TEMP_INT_IN,\
                          TYPE_BULK,     \
                          TYPE_INTERRUPT,\
                          SIZE_64,       \
                          ONE_BANK,      \
                          NYET_ENABLED);
}


//! @brief This function returns the interface alternate setting
//!
//! @param wInterface         Interface selected
//!
//! @return alternate setting configurated
//!
U8   usb_user_interface_get( U16 wInterface )
{
   return 0;  // Only one alternate setting possible for all interface
}


//! @brief This function selects (and resets) the interface alternate setting
//!
//! @param wInterface         Interface selected
//! @param alternate_setting  alternate setting selected
//!
void usb_user_interface_reset(U16 wInterface, U8 alternate_setting)
{  
   // default setting selected = reset data toggle
   if( INTERFACE_NB_TEMP == wInterface )
   {
      // Interface reset
      Usb_select_endpoint(EP_TEMP_IN);
      Usb_disable_stall_handshake();
      Usb_reset_endpoint(EP_TEMP_IN);
      Usb_reset_data_toggle();
      Usb_select_endpoint(EP_TEMP_OUT);
      Usb_disable_stall_handshake();
      Usb_reset_endpoint(EP_TEMP_OUT);
      Usb_reset_data_toggle();
   }
   if( INTERFACE_NB_SECOND_TEMP == wInterface )
   {
      // Interface reset
      Usb_select_endpoint(EP_TEMP_INT_IN);
      Usb_disable_stall_handshake();
      Usb_reset_endpoint(EP_TEMP_INT_IN);
      Usb_reset_data_toggle();
   }
}

   
//! This function fills the global descriptor
//!
//! @param type      corresponding at MSB of wValue (see USB specification)
//! @param string    corresponding at LSB of wValue (see USB specification)
//!
//! @return FALSE, if the global descriptor no filled
//!
Bool usb_user_get_descriptor(U8 type, U8 string)
{
   switch(type)
   {
      case DESCRIPTOR_STRING:
      switch (string)
      {
         case LANG_ID:
         data_to_transfer = sizeof (usb_user_language_id);
         pbuffer = &(usb_user_language_id.bLength);
         return TRUE;
         break;
/*        
         case MAN_INDEX:
         data_to_transfer = sizeof (usb_user_manufacturer_string_descriptor);
         pbuffer = &(usb_user_manufacturer_string_descriptor.bLength);
         return TRUE;
         break;
        
         case PROD_INDEX:
         data_to_transfer = sizeof (usb_user_product_string_descriptor);
         pbuffer = &(usb_user_product_string_descriptor.bLength);
         return TRUE;
         break;
*/           
#if (USB_DEVICE_SN_USE==ENABLE)              
         case SN_INDEX:
         data_to_transfer = sizeof (usb_user_serial_number);
         pbuffer = &(usb_user_serial_number.bLength);
#if (USE_DEVICE_SN_UNIQUE==ENABLE)
         f_get_serial_string=TRUE;
         data_to_transfer += (SN_LENGTH*4);
#endif
         return TRUE;
         break;
#endif
      }
      break;
   }
   return FALSE;
}

//! cdc_get_line_coding.
//!
//! @brief This function manages reception of line coding parameters (baudrate...).
//!
//! @param none
//!
//! @return none
//!
void cdc_get_line_coding(void)
{
     Usb_ack_receive_setup();
     Usb_write_byte(LSB0(line_coding.dwDTERate));
     Usb_write_byte(LSB1(line_coding.dwDTERate));
     Usb_write_byte(LSB2(line_coding.dwDTERate));
     Usb_write_byte(LSB3(line_coding.dwDTERate));
     Usb_write_byte(line_coding.bCharFormat);
     Usb_write_byte(line_coding.bParityType);
     Usb_write_byte(line_coding.bDataBits);

     Usb_send_control_in();
     while(!(Is_usb_read_control_enabled()));
     //Usb_clear_tx_complete();

   while(!Is_usb_receive_out());
   Usb_ack_receive_out();
}


//! cdc_set_line_coding.
//!
//! @brief This function manages reception of line coding parameters (baudrate...).
//!
//! @param none
//!
//! @return none
//!
void cdc_set_line_coding (void)
{
   Usb_ack_receive_setup();
   while (!(Is_usb_receive_out()));
   LSB0(line_coding.dwDTERate) = Usb_read_byte();
   LSB1(line_coding.dwDTERate) = Usb_read_byte();
   LSB2(line_coding.dwDTERate) = Usb_read_byte();
   LSB3(line_coding.dwDTERate) = Usb_read_byte();
   line_coding.bCharFormat = Usb_read_byte();
   line_coding.bParityType = Usb_read_byte();
   line_coding.bDataBits = Usb_read_byte();
     Usb_ack_receive_out();

     Usb_send_control_in();                // send a ZLP for STATUS phase
     while(!(Is_usb_read_control_enabled()));
/*
#ifdef UART_U2
   Uart_set_baudrate((line_coding.dwDTERate)/2);
#else
   Uart_set_baudrate(line_coding.dwDTERate);
#endif
*/
}


//! cdc_set_control_line_state.
//!
//! @brief This function manages the SET_CONTROL_LINE_LINE_STATE CDC request.
//!
//! @todo Manages here hardware flow control...
//!
//! @param none
//!
//! @return none
//!
void cdc_set_control_line_state (U16 state)
{
     Usb_ack_receive_setup();
   Usb_send_control_in();
   line_status.all = state;
   
     while(!(Is_usb_read_control_enabled()));

}

//! cdc_update_serial_state.
//!
//! @brief This function checks if serial state has changed and updates host with that information.
//!
//! @todo Return TRUE only if update was accepted by host, to detect need for resending
//!
//! @param none
//!
//! @return TRUE if updated state was sent otherwise FALSE
//!
//! @comment upr: Added for hardware handshake support according cdc spec 1.1 chapter 6.3.5
//!
Bool cdc_update_serial_state()
{
   if( serial_state_saved.all != serial_state.all)
   {
      serial_state_saved.all = serial_state.all;
      
      Usb_select_endpoint(INT_EP);
      if (Is_usb_write_enabled())
      {
         Usb_write_byte(USB_SETUP_GET_CLASS_INTER);   // bmRequestType
         Usb_write_byte(SETUP_CDC_BN_SERIAL_STATE);   // bNotification
         
         Usb_write_byte(0x00);   // wValue (zero)
         Usb_write_byte(0x00);
         
         Usb_write_byte(0x00);   // wIndex (Interface)
         Usb_write_byte(0x00);
         
         Usb_write_byte(0x02);   // wLength (data count = 2)
         Usb_write_byte(0x00);
         
         Usb_write_byte(LSB(serial_state.all));   // data 0: LSB first of serial state
         Usb_write_byte(MSB(serial_state.all));   // data 1: MSB follows
         Usb_ack_in_ready();
      }
      return TRUE;
   }
   return FALSE;
}

//! @brief This function manages the SEND_BREAK CDC request.
//!
//! @todo Manages here hardware flow control...
//!
//! @param break lenght
//!
void cdc_send_break(U16 break_duration)
{
   Usb_ack_receive_setup();
    Usb_send_control_in();
   usb_request_break_generation=TRUE;
   while(!(Is_usb_read_control_enabled()));
}

