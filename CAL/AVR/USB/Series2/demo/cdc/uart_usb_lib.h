// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D53F5F6A18E6F66E466F9DB641FCB79B70A88B63D7935A1E73137D5E3E7185E7B75A0D7AC6FDE24E631240725FEB6727305BD0F9162BB218B7AF4E1CD32F02CD429A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5AA5437D4A507B9AF137BA18673D20F75B85FF64D9061EA050C16B827D19484B105AC1E9300CDC97FCBEF2FF2628A63A3225318F1A40E8CAADBB117328BCDBD48C7662E24F96F8F57B6F615E604BC2D615CA1BEB122F059D7549D34A0D5AD11F35CAF8E15938B4014A65CD28FF4F9C1061F3F6D41E09E1473FA0264F21FD71235929CCCA4409E3163
// REVISION: 1.0
// GUID: 6694AFD0-336F-4E95-8C2E-85C116A07D78
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\demo\cdc\uart_usb_lib.h
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
