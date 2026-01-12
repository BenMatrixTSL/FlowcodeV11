// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D53F5F6A18E6F66E466F9DB641FCB79B70BB4005A2994832514912D9FFFBF2A7943B3F0A0C08CFCC73B2B27D12798FE9B99A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF512E91A503D6F3E7DFD6E6A3D50E9B6B549A3CB0F99F673EEFE657373C0FDEFD1BB5CF8EF391E71416373F1AE2CD25F7590CA662A30413F2A5189B638906EA38B5B5AD6B1A933C5D1A198CA3D5EBF4635636F7A56F194CD15549D34A0D5AD11F3951EC2D4B9D3FCB33197ACFBE32EF5286B9804226E637E75C1E0961D1CF9D810AE94354B8E74C3BA
// REVISION: 1.0
// GUID: AFAAEB89-02A3-4F2A-96BA-B82CE8AD4465
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\demo\HID\hid_task.c
//!
//! @file hid_task.c,v
//!
//! @brief This file manages the HID task.
//!
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
