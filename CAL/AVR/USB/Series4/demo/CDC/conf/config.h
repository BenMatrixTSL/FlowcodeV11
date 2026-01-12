// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D57DF507285C9C50725F499CC7EBAC12FBD0F9B4F2D43ECF60CD934D683207D3F2DD553F164FE4F074FFF4CB1A2CB62A00011496AE222D8A5BBDA9DACA3792E7719A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5E458147E0CF7DC3FEE1682FC108B2CE3E7C7078A2D420EF9BE9EE825FA1FB662FA104E4AB02B1817D32B6B3F04A8EACE67CF123EE47016B718981986AEBCF3CD4F05C090C44E6FBEBF774EAA7A5354743170538EF3AF3DF5549D34A0D5AD11F3BCE703E087D3118BA050DD3BD3CA4FFCE0C687383EE7916DA44501DE8C4E8A8748A9453D8E52754C
// REVISION: 1.0
// GUID: 6591441C-3BAC-4178-AECF-57C4178ECC6E
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\demo\CDC\conf\config.h
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

#include <mx_usb_cdc_conf.h>
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

