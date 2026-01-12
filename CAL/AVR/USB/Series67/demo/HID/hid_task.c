// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5E971021840B65CB4A3D8D01D6B7FD05CC0A69A6C412C648223269F0F0B062523B5AC834436202BA3D2360BB45BC526BB9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5505EB3A14BCB05C0DADBE46DBE0EE44739D74C2FA9FBF17E9DCC700FA87C6C1CC08A1F30EB4CF0A3EE242F229BB8386C2045C0CD6C4ABDC06289256EABA285DE0EC39CE2830E2C62EF012D16F7B9C907CACE1431F264F0E1549D34A0D5AD11F37445C8525ED40296F55231231F530A4F8541B680E39F89B1A8B2FE2536E6C50FEBD31FED13C8BAD2
// REVISION: 1.0
// GUID: E73866E6-48AA-4C2C-BAB7-2BDFDD242FFF
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series67\demo\HID\hid_task.c
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
