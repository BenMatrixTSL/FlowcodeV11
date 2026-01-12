// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D57DF507285C9C50725F499CC7EBAC12FBBB4005A2994832514912D9FFFBF2A7943B3F0A0C08CFCC73B2B27D12798FE9B99A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5A5CCAD186437C79306A6BF80D0715BBCAD1DF4D02788EDD261D59B4909D8AB54DDE827B66DDE7A14D99C7641F646A7D167846A5CACDEF592BC922601E1A746B168B77184FC62F8BC4B16A59602926E349EB0DFF2E2527A2C549D34A0D5AD11F3204BBE2BF6BE6D3BD05E408AC6383D3FFDA9F510B6031427F8E785FACEA3D272F4AEDF261F4C8924
// REVISION: 1.0
// GUID: 03475875-0761-4B67-8A01-30EC420F260B
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\demo\HID\hid_task.c
//!
//! @file mouse_task.c,v
//!
//! Copyright (c) 2004 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file manages the Mouse task.
//!
//! @version 1.4 at90usb162-2enum-mouse_ms-1_0_1 $Id: mouse_task.c,v 1.4 2007/01/08 16:09:44 arobert Exp $
//!
//! @todo
//! @bug
//!/

//_____  I N C L U D E S ___________________________________________________

#include "config.h"
#include "conf_usb.h"
#include "hid_task.h"
#include "lib_mcu/usb/usb_drv.h"
#include "usb_descriptors.h"
#include "modules/usb/device_chap9/usb_standard_request.h"
#include "lib_mcu/wdt/wdt_drv.h"
#include "lib_mcu/power/power_drv.h"
#include "lib_mcu/pll/pll_drv.h"

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________

Uchar rx_counter;

//_____ D E C L A R A T I O N S ____________________________________________

//!
//! @brief This function initializes the hardware/software resources required for hid tasks.
//!
//! @param none
//!
//! @return none
//!
//!/
void hid_task_init(void)
{
   Usb_enable_sof_interrupt();
}

/** 
  * @brief This function checks if a character has been received on the USB bus.
  * 
  * @return U8 (number of bytes received)
  */
U8 hid_get_data(U8* rxBuff)
{
#if MX_HID_RX_SZ > 0	
  U8 idx, rx_counter = 0;
  
  Usb_select_endpoint(EP_HID_OUT);
  if(Is_usb_receive_out())
  {
    rx_counter = Usb_byte_counter();
	
	for(idx = 0; idx < rx_counter; idx++)
	{
	  rxBuff[idx] = Usb_read_byte();
	}

    Usb_ack_receive_out();
  }
  return (rx_counter);
#else
  return (0);
#endif
}

void hid_send_data(U8* txBuff, U8 txCount)
{
	U8 idx;
	
	for(idx = 0; idx < txCount; idx++) {
		Usb_write_byte(txBuff[idx]);
	}
	Usb_ack_in_ready();
}


//! @brief sof_action
//!
//! @param none
//!
//! @return none
void sof_action()
{
   U8 ep_selected;

   ep_selected = Usb_get_selected_endpoint();   // the currently selected endpoint must be saved to avoid                                                  // problems when interrupt happens during mass storage endpoint reading/writing  
   usb_task();
   Usb_select_endpoint(ep_selected);            // restore current selected endpoint
}
