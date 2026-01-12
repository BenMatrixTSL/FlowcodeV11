// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D57DF507285C9C50725F499CC7EBAC12FB2EAE852DAD7DAD38A62ED4709B1AE32F5A0D7AC6FDE24E631240725FEB6727305BD0F9162BB218B7AF4E1CD32F02CD429A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF53147313CF94880679B61F19DA2FD33DB0EB3F5CB3539397F1399C097C15EB21D44E01112FB4FA3C1D2D1018B6FA50398BEA3735A56E4C88AF6501E7E868C691BAC1C063175C00C48622BB3691C948D495D014FBCC70A0131549D34A0D5AD11F3291FE8C419D59762F95F694FA9FA65FE7FB3EA92B687FDBD00BCBB6501ED73225F16A50661D68CC2
// REVISION: 1.0
// GUID: 5ED75AFE-61E6-40BD-BB18-F077DF5793E3
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\demo\CDC\uart_usb_lib.h
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
