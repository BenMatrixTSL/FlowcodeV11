// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D53F5F6A18E6F66E466F9DB641FCB79B70A88B63D7935A1E73137D5E3E7185E7B75A0D7AC6FDE24E631240725FEB672730FAA4458EC9CAE498CB82F7AC975D21D49A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5E936B69D61FD85DE1788FA0BD8A8A22A1623532833A3FF5F6F9C937557109F093395469A89EAF32F65730ABF78AE325C0FEF8724CF05C0EDE3BDC2AE47D2616FDEEC8EFB245AC46B79DE6CD36D1AF7E8DCB9A08A2AB345FF549D34A0D5AD11F3C8384EB3C4338FD85650B8C80A7059FF132404F19834376A76AD1A7DB9B9D5F43F565616D7803A54
// REVISION: 1.0
// GUID: 0D781FB3-C843-415E-B7BA-8D4DB299A042
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\demo\cdc\uart_usb_lib.c
//!
//! @file uart_usb_lib.c,v
//!
//! Copyright (c) 2006 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file controls the UART USB functions.
//!
//! @version 1.1 at90usb162-cdc-1_0_1 $Id: uart_usb_lib.c,v 1.1 2006/09/08 10:55:11 rletendu Exp $
//!

/*_____ I N C L U D E S ____________________________________________________*/

#include "config.h"
#include "lib_mcu\usb\usb_drv.h"
#include "usb_descriptors.h"

#include "uart_usb_lib.h"

/*_____ M A C R O S ________________________________________________________*/

/*_____ D E F I N I T I O N ________________________________________________*/

Uchar tx_counter;
Uchar rx_counter;

/*_____ D E C L A R A T I O N ______________________________________________*/

/** 
  * @brief Initializes the uart_usb library
  */
void uart_usb_init(void)
{
  tx_counter = 0;
  rx_counter = 0;
  Usb_enable_sof_interrupt();
}

/** 
  * @brief This function checks if a character has been received on the USB bus.
  * 
  * @return bit (true if a byte is ready to be read)
  */
bit uart_usb_test_hit(void)
{
  if (!rx_counter)
  {
    Usb_select_endpoint(RX_EP);
    if (Is_usb_receive_out())
    {
      rx_counter = Usb_byte_counter();
      if (!rx_counter)
		{
          Usb_ack_receive_out();
		}
    }
  }
  return (rx_counter!=0);
}

/** 
  * @brief This function reads one byte from the USB bus
  *
  * If one byte is present in the USB fifo, this byte is returned. If no data
  * is present in the USB fifo, this function waits for USB data.
  * 
  * @return U8 byte received
  */
char uart_usb_getchar(void)
{
  register Uchar data_rx;

  Usb_select_endpoint(RX_EP);
  if (!rx_counter) while (!uart_usb_test_hit());
  data_rx=Usb_read_byte();
  rx_counter--;
  if (!rx_counter) Usb_ack_receive_out();
  return data_rx;
}


/** 
  * @brief This function checks if the USB emission buffer is ready to accept at
  * at least 1 byte
  * 
  * @return Boolean. TRUE if the firmware can write a new byte to transmit.
  */
bit uart_usb_tx_ready(void)
{
  if (!Is_usb_write_enabled())
  {
    return FALSE;
  }
  return TRUE;
}

/** 
  * @brief This function fills the USB transmit buffer with the new data. This buffer
  * is sent if complete. To flush this buffer before waiting full, launch
  * the uart_usb_flush() function.
  * 
  * @param data_to_send 
  * 
  * @return 
  */
int uart_usb_putchar(int data_to_send)
{
  	Usb_select_endpoint(TX_EP);
  	while(!uart_usb_tx_ready()); // Wait Endpoint ready
	Usb_write_byte(data_to_send);
	tx_counter++;
  	if(!Is_usb_write_enabled()) //If Endpoint full -> flush
  	{
   	    uart_usb_flush();
  	}
	return data_to_send;
}


/** 
  * @brief This function sends the data stored in the USB transmit buffer.
  * This function does nothing if there is no data in the buffer.
  */
void uart_usb_flush (void)
{
   Usb_select_endpoint(TX_EP);
   Usb_send_in();
   tx_counter = 0;

}


void sof_action() {
    U8 ep_temp;

    ep_temp = Usb_get_selected_endpoint();
    usb_task();
    Usb_select_endpoint(ep_temp);
}
  



