// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D57DF507285C9C50725F499CC7EBAC12FB26ABDD955647B92961C4459068936562DD553F164FE4F074FFF4CB1A2CB62A00011496AE222D8A5BBDA9DACA3792E7719A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5C6568075AE9CF172D0FD6B0B803A947CB0D3E547ADB2F76B24EAAA792A88F6B3C5C2E364CE1C9E59A5385918ED874B387B3732C6BF37A8E8442329DB638B0F25DBC0A2D5361F53C24F988807C3AE6F79EFA62DE588905CEC549D34A0D5AD11F3B339FACA3EDCE8CA6E582DC3FCB06E529F78C3311E19FDDFE00AF8598B7CA62D1079227E43D7E189
// REVISION: 1.0
// GUID: 3F7585B7-6531-4EC3-B719-5DACE6635C98
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\demo\HID\conf\config.h
//! @file config.h,v
//!
//! Copyright (c) 2006 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! This file contains the system configuration definition
//!
//! @version 1.1 at90usb162-cdc-1_0_1 $Id: config.h,v 1.1 2006/09/08 10:55:12 rletendu Exp $
//!
//! @todo
//! @bug

#ifndef _CONFIG_H_
#define _CONFIG_H_

//! @defgroup global_config Application configuration
//! @{

//_____ I N C L U D E S ____________________________________________________

#include <mx_usb_hid_conf.h>
#include "lib_mcu/compiler.h"             // Compiler definitions
#ifdef __GNUC__
   #include <avr/io.h>                    // Use AVR-GCC library
#elif __ICCAVR__
   #define ENABLE_BIT_DEFINITIONS
   #include <ioavr.h>                     // Use IAR-AVR library
#else
   #error Current COMPILER not supported
#endif

#define BYPASS_USB_AUTOBAUD

//! CPU core frequency in kHz
#define FOSC MX_FOSC_KHZ
#define PLL_OUT_FRQ  PLL_OUT_96MHZ

// -------- END Generic Configuration -------------------------------------

#endif // _CONFIG_H_

