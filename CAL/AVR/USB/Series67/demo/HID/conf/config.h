// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5E971021840B65CB4A3D8D01D6B7FD05CAFBBAB597C9E797EA377F63D986356660116A181A6D85DA3716E6ACFF49C0B72DD38D2276393E55DBFE8F2A9164C6C739A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF56B4E05CA5267BA1DF64DF4DD5905B61783D1CDF75F03E868737499BCC9ADB257E32B568453A34720CF6FFA2AD13E45A0FFF093C9CE26852511CAECEF85A71753E29A154B50AE3F0475BE85F0FEBA6AAD304EA5BBBF8B213E549D34A0D5AD11F387A0418B702647CCF5A61C85767F55668B56A67E09811967ADE7F62E1D9AF28DE7B6485568F872D0
// REVISION: 1.0
// GUID: 6B85556D-CE96-4A61-9B34-CCF605491F47
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series67\demo\HID\conf\config.h
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

