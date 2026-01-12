// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5E971021840B65CB4A3D8D01D6B7FD05C517F7AB7AF72D4C2D19B1C8DC1AF66A64E8843EB54E80A126F32946B14DFE8966C72F88EB03764082E2AE040836BFD2C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF58ABFD4D1F13E043C9E8C1CB2FA22504F4E01E619040AA175D95A3EC68F733299A2DB8C6C7417D54C4B2BE1510242E7EC548D6D2A57F96005FECA3A0FE011F5E104B0D59DD7BD1F328B4E198DB031C8559AD75B158F43CD60549D34A0D5AD11F3EAD0FF2505A825BD392D934C72A212D9C8544FC93FC56E1CD2AD5B899D5932CF499F10447F50333B
// REVISION: 1.0
// GUID: 7DB5DEBF-207E-4A80-AA0C-7898840360C4
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series67\demo\CDC\uart_usb_lib.h
//!
//! @file uart_usb_lib.h,v
//!
//! Copyright (c) 2006 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file controls the UART USB functions.
//!
//! @version 1.1 at90usb162-cdc-1_0_1 $Id: uart_usb_lib.h,v 1.1 2006/09/08 10:55:11 rletendu Exp $
//!

#ifndef _UART_USB_LIB_H_
#define _UART_USB_LIB_H_

/*_____ I N C L U D E S ____________________________________________________*/


/*_____ M A C R O S ________________________________________________________*/


/*_____ D E F I N I T I O N ________________________________________________*/


/*_____ D E C L A R A T I O N ______________________________________________*/

void  uart_usb_init(void);
bit   uart_usb_test_hit(void);
char uart_usb_getchar(void);
bit   uart_usb_tx_ready(void);
int  uart_usb_putchar(int);
void  uart_usb_flush(void);
void sof_action();


#endif /* _UART_USB_LIB_H_ */
