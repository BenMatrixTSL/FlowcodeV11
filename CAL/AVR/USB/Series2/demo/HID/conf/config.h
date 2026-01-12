// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D53F5F6A18E6F66E466F9DB641FCB79B7026ABDD955647B92961C4459068936562DD553F164FE4F074FFF4CB1A2CB62A00011496AE222D8A5BBDA9DACA3792E7719A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF54D20B5E779016FA3BA8FC83610F7ABA13F8460364C4694F4C0CD1349FD395A08878C5A08AE1184A0F290801DF2F8F91B1013CC0C709702EADAB711501938311078FC57185A499629902FBEE1BDA6BBE3B9E670B98ED97111549D34A0D5AD11F3E35E1878C705A5001E95A33EB5D7293498A6C32E8B57845B850400E5B608E745107C571680B732A8
// REVISION: 1.0
// GUID: 40DD3CE5-E3AF-4CAA-AAEA-EF50A9849F1B
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\demo\HID\conf\config.h
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

// -------- END Generic Configuration -------------------------------------

#endif // _CONFIG_H_

