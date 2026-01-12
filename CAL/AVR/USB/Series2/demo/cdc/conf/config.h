// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D53F5F6A18E6F66E466F9DB641FCB79B702CE4B21FC8957E8F68FFB13AEC3055C7DD553F164FE4F074FFF4CB1A2CB62A00011496AE222D8A5BBDA9DACA3792E7719A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF578FC6064B2535E8F8265199E5102A93D67B32F3B121F3B61DDDDB2B67839AE85FDEE22C06849D154CD9E2B9246C819FB08FE447E8C71B80F622D5A97CD579448D4CA94A37B97D8330183ED9DD52E1ACF954E545881AEA9C6549D34A0D5AD11F38243792067153C1E73E6DC4E8703E7677DCB9275B14F3D36BCC7899FCA2DDCC03543C1004297ACD4
// REVISION: 1.0
// GUID: FC86B4D2-F1D4-4DE5-BF05-8CEAD4A9401B
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\demo\cdc\conf\config.h
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

// -------- END Generic Configuration -------------------------------------

#endif // _CONFIG_H_

