// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D53F5F6A18E6F66E466F9DB641FCB79B707EABDD0A6647EDB294D49642477A5A999F49B15EA4FA1A5CBC04149400627248F44901BA6D6A39C58439069F5482766AF6A5B120DF94DBAE53530CD754161A539A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF52A5EC35711ADF0F1114A28BF802B560F4F5EE2FA5CC204DF0A593AE062CD3912A120149CA2246E03C4FDF01CCA1A82B434AED6E3F11BB1B0105F48A5D6CA3B1771423F3339414DFDF4AE1C151287769D7C472540D94B3D2C549D34A0D5AD11F3FB86AD5F2F73B4F512276ED7F0D706E5A44EA5E35604C64D18D34502288D3DAB5F5FD00D1D4C038A
// REVISION: 1.0
// GUID: 5D23491E-7B49-4AF1-A7D7-51565C57E58E
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\demo\HID\usb_specific_request.c
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief user call-back functions
//!
//!  This file contains the user call-back functions corresponding to the
//!  application:
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

//_____ D E F I N I T I O N ________________________________________________

#ifdef __GNUC__
extern PGM_VOID_P pbuffer;
#else
extern U8   code *pbuffer;
#endif
extern U8   data_to_transfer;
extern code S_usb_hid_report_descriptor usb_hid_report_descriptor;
extern U16  wInterface;

extern U8 HID_USB_Rx_String[];
#if (MX_HID_RX_SZ > 0)
extern volatile U8 incoming;
#endif


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
U8  descriptor_type ;
U8  string_type     ;

	string_type     = Usb_read_byte();
	descriptor_type = Usb_read_byte();
	switch(request)
	{
		case GET_DESCRIPTOR:

			switch (descriptor_type)
			{
			   case REPORT:
					hid_get_report();
					return TRUE;
      			break;

			   case HID:
					hid_get_hid_descriptor();
					return TRUE;
      			break;
			   default:
					return FALSE;
      			break;
			}
			break;

		 case SET_CONFIGURATION:
			switch (descriptor_type)
			{
			   case SET_REPORT:
					hid_set_report();
					return TRUE;
      			break;

			   default:
					return FALSE;
      			break;
			}
			break;
		
		case GET_INTERFACE:
//			usb_hid_set_idle();
			usb_hid_get_interface();
			return TRUE;
			break;

 		default:
			return FALSE;
			break;

	}
  	return FALSE;
}

//! usb_user_endpoint_init.
//!
//! @brief This function configures the endpoints.
//!
//! @param none
//!
//! @return none
//!
void usb_user_endpoint_init(U8 conf_nb)
{
 usb_configure_endpoint(EP_HID_IN,      \
                         TYPE_INTERRUPT,     \
                         DIRECTION_IN,  \
                         SIZE_8,       \
                         ONE_BANK,     \
                         NYET_ENABLED);
 Usb_reset_endpoint(EP_HID_IN);
						 
#if MX_HID_RX_SZ > 0
 usb_configure_endpoint(EP_HID_OUT,      \
                         TYPE_INTERRUPT,     \
                         DIRECTION_OUT,  \
                         SIZE_8,       \
                         ONE_BANK,     \
                         NYET_ENABLED);
 Usb_reset_endpoint(EP_HID_OUT);
#endif
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
      Usb_select_endpoint(EP_HID_IN);
      Usb_disable_stall_handshake();
      Usb_reset_endpoint(EP_HID_IN);
      Usb_reset_data_toggle();

#if MX_HID_RX_SZ > 0
      // Interface reset
      Usb_select_endpoint(EP_HID_OUT);
      Usb_disable_stall_handshake();
      Usb_reset_endpoint(EP_HID_OUT);
      Usb_reset_data_toggle();
#endif
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

//! hid_get_report.
//!
//! @brief This function manages hit get repport request.
//!
//! @param none
//!
//! @return none
//!
void hid_get_report(void)
{

U16 wLength;
U8  nb_byte;
bit zlp=0;



   LSB(wInterface)=Usb_read_byte();
   MSB(wInterface)=Usb_read_byte();

   data_to_transfer = sizeof(usb_hid_report_descriptor);
   pbuffer = &(usb_hid_report_descriptor.report[0]);

   LSB(wLength) = Usb_read_byte();      //!< read wLength
   MSB(wLength) = Usb_read_byte();
   Usb_ack_receive_setup() ;                  //!< clear the receive setup flag

   if (wLength > data_to_transfer)
   {
      if ((data_to_transfer % EP_CONTROL_LENGTH) == 0) { zlp = TRUE; }
      else { zlp = FALSE; }                   //!< no need of zero length packet
   }
   else
   {
      data_to_transfer = (U8)wLength;         //!< send only requested number of data
   }

    while((data_to_transfer != 0) )
   {
      while(!Is_usb_read_control_enabled());

		nb_byte=0;
      while(data_to_transfer != 0)			//!< Send data until necessary
      {
			if(nb_byte++==EP_CONTROL_LENGTH) //!< Check endpoint 0 size
			{
				break;
			}

#warning with avrgcc assumes devices descriptors are stored in the lower 64Kbytes of on-chip flash memory
         Usb_write_byte(pgm_read_byte_near((unsigned int)pbuffer++));
         data_to_transfer --;
      }
      Usb_send_control_in();
   }

   Usb_send_control_in();

   if(Is_usb_receive_out()) { Usb_ack_receive_out(); return; } //!< abort from Host
   if(zlp == TRUE)        { Usb_send_control_in(); }

   while(!Is_usb_receive_out());
   Usb_ack_receive_out();
}



//! hid_set_report.
//!
//! @brief This function manages hit set report request.
//!
//! @param none
//!
//! @return none
//!
void hid_set_report (void)
{
	U8 idx = 0;
	
	Usb_ack_receive_setup();
	Usb_send_control_in();
	
	while(!Is_usb_receive_out());

#if (MX_HID_RX_SZ > 0)
	while(idx < MX_HID_RX_SZ)
		HID_USB_Rx_String[idx++] = Usb_read_byte();
	
	incoming = 1;
#endif
	Usb_ack_receive_out();
	Usb_send_control_in();
}


//! usb_hid_set_idle.
//!
//! @brief This function manages hid set idle request.
//!
//! @param none
//!
//! @return none
//!
void usb_hid_set_idle (void)
{
  U8 dummy;
  
  dummy = Usb_read_byte();
  dummy = Usb_read_byte();
  LSB(wInterface)=Usb_read_byte();
  MSB(wInterface)=Usb_read_byte();

  Usb_ack_receive_setup();

  Usb_send_control_in();                       /* send a ZLP for STATUS phase */
  while(!Is_usb_in_ready());
}


//! usb_hid_get_interface.
//!
//! @brief This function manages hid get interface request.
//!
//! @param none
//!
//! @return none
//!
void usb_hid_get_interface (void)
{
  U8 dummy;
  dummy = Usb_read_byte();
  dummy = Usb_read_byte();
  LSB(wInterface)=Usb_read_byte();
  MSB(wInterface)=Usb_read_byte();

  Usb_ack_receive_setup();

  Usb_send_control_in();                       /* send a ZLP for STATUS phase */
  while(!Is_usb_in_ready());
}

//! hid_get_hid_descriptor.
//!
//! @brief This function manages hid get hid descriptor request.
//!
//! @param none
//!
//! @return none
//!
void hid_get_hid_descriptor(void)
{

U16 wLength;
U8  nb_byte;
bit zlp=0;

   LSB(wInterface)=Usb_read_byte();
   MSB(wInterface)=Usb_read_byte();

   data_to_transfer = sizeof(usb_conf_desc.hid_class);
   pbuffer = &(usb_conf_desc.hid_class.bLength);

   LSB(wLength) = Usb_read_byte();      //!< read wLength
   MSB(wLength) = Usb_read_byte();
   Usb_ack_receive_setup() ;                  //!< clear the receive setup flag

   if (wLength > data_to_transfer)
   {
      if ((data_to_transfer % EP_CONTROL_LENGTH) == 0) { zlp = TRUE; }
      else { zlp = FALSE; }                   //!< no need of zero length packet
   }
   else
   {
      data_to_transfer = (U8)wLength;         //!< send only requested number of data
   }

   while((data_to_transfer != 0) && (!Is_usb_receive_out()))
   {
      while(!Is_usb_read_control_enabled());

		nb_byte=0;
      while(data_to_transfer != 0)			//!< Send data until necessary
      {
			if(nb_byte++==EP_CONTROL_LENGTH) //!< Check endpoint 0 size
			{
				break;
			}
#warning with avrgcc assumes devices descriptors are stored in the lower 64Kbytes of on-chip flash memory
         Usb_write_byte(pgm_read_byte_near((unsigned int)pbuffer++));
         data_to_transfer --;
      }
      Usb_send_control_in();
   }

   Usb_send_control_in();

   if(Is_usb_receive_out()) { Usb_ack_receive_out(); return; } //!< abort from Host
   if(zlp == TRUE)        { Usb_send_control_in(); }

   while(!Is_usb_receive_out());
   Usb_ack_receive_out();
}
