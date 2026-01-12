// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D583C45B8AED270FE40481B7BD05EB7253693DA6B1D49433749F9FFA68884A5B67F31459E5ABBB0680E5741776BD6F943499D6A8396402D60C26E7187481303A179A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF52E7CED3DC967992EDE6D87E58DB699D4558B21E118DB51061B1E9B9B7035E0A43040750159CC60EFBD9520B5D418DC93CDAB3907F91B0B1B7D10A1F17DA903C6D7BCAB5FD1259C9B8E1F3B689DDBD1A92E26F616D3C6B8F8549D34A0D5AD11F3202C8E96E0EFEEAD3DC7054606C7CC558851A2642D4A3339850400E5B608E745107C571680B732A8
// REVISION: 1.0
// GUID: 9D85EDE8-1305-4A9B-A3F5-D940743DDCC2
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series67\lib_mcu\flash\flash_drv.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief Driver routines to read (no write) datas stored in AVRMega flash
//! These routines can be stored and executed in all flash space.
//!
//! - Compiler:           IAR EWAVR and GNU GCC for AVR
//! - Supported devices:  All AVRMega devices
//!
//! \author               Atmel Corporation: http://www.atmel.com \n
//!                       Support and FAQ: http://support.atmel.no/
//!
//! ***************************************************************************

/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef FLASH_DRV_H
#define FLASH_DRV_H

//_____ I N C L U D E S ______________________________________________________

#include "config.h"


//_____ M A C R O S ________________________________________________________

//! \name These macros allow to read a specific device ID of the product.
//! @{
#define Flash_read_id1()            ( flash_read_sig(0x0000))  //!< This macro function allows to read device ID1 of the product.
#define Flash_read_id2()            ( flash_read_sig(0x0002))  //!< This macro function allows to read device ID2 of the product.
#define Flash_read_id3()            ( flash_read_sig(0x0004))  //!< This macro function allows to read device ID3 of the product.
#define Flash_read_osccal()         ( flash_read_sig(0x0001))  //!< This macro function allows to read the OSCAL byte of the product.
#define Flash_read_sn(pos)          ( flash_read_sig((0x07*2)+pos))//!< This macro function allows to read the serial number of the product.
#define SN_LENGTH                   10                         //!< Size of the serial number containt in product.
//! @}

//! \name These macros allow to read a specific fuse of the product.
//! @{
#define Flash_read_fuse_low()       ( flash_read_fuse(0x0000)) //!< @brief This macro function allows to read the low fuse byte of the product.
#define Flash_read_fuse_high()      ( flash_read_fuse(0x0003)) //!< @brief This macro function allows to read device high fuse byte of the product.
#define Flash_read_fuse_extended()  ( flash_read_fuse(0x0002)) //!< @brief This macro function allows to read extended fuse byte of the product.
#define Flash_read_lock()           ( flash_read_fuse(0x0001)) //!< @brief This macro function allows to read lock byte of the product.
//! @}

//! \name These macros allow to check bits from extended fuse of the product.
//! @{
#define Is_OCD_enable()             (0==(Flash_read_fuse_high()&(1<<FUSE_OCDEN_bp)))  //!< @brief Check if the OCD is running
#define Is_JTAG_enable()            (0==(Flash_read_fuse_high()&(1<<FUSE_JTAGEN_bp))) //!< @brief Check if the JTAG interface is enabled
//! @}


//! \name High Fuse Byte
//! @{
#define FUSE_BOOTRST_bp    0  // Select Reset Vector
#define FUSE_BOOTSZ0_bp    1  // Select Boot Size
#define FUSE_BOOTSZ1_bp    2  // Select Boot Size
#define FUSE_EESAVE_bp     3  // EEPROM memory is preserved through chip erase
#define FUSE_WDTON_bp      4  // Watchdog timer always on
#define FUSE_SPIEN_bp      5  // Enable Serial programming and Data Downloading
#define FUSE_JTAGEN_bp     6  // Enable JTAG
#define FUSE_OCDEN_bp      7  // Enable OCD
//! @}


//_____ D E C L A R A T I O N S ____________________________________________

//! @brief This macro function allows to read device IDs of the product.
//!
//! @param  add   Address of device ID to read.
//!
//! @return byte  Read value
//!
U8    flash_read_sig(unsigned long adr);

//! @brief This macro function allows to read a fuse byte of the product.
//!
//! @param  add   Address of fuse to read.
//! 
//! @return byte  Read value
//!
U8    flash_read_fuse(unsigned long adr);


#endif  // FLASH_DRV_H



