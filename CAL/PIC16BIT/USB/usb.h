// CRC: 5D982BB222882C54AB4AFF20A1590FC4128F294B41FC96FD138D7F694DC5EBF5F0EEF32FC9869FB67284F8BFEB3E19EF9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF55E4AC0F99579BA9DC7CBC9E10D37E5EF7D6273118A4FA1A6A5A608C2EBCB5FAA65E28E2D5947EAFF89B48C173368D2DFBC30C23AF69BD0F0D1B0F56672D6B0478C5CAA243747A35AF6808E9762E29B392CD69097CC056230549D34A0D5AD11F39E3E7A12162306AD84570B1BA604301C198A43C4E9F4FA4CA3E761B0B04467EFC0CE2C344F21BA45
// REVISION: 1.0
// GUID: E537A0C0-6FEE-4AFD-89B9-0C35BF72A80B
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\USB\usb.h
//DOM-IGNORE-BEGIN
/*********************************************************************
 * The following lines are used by VDI.
 * GUID=E537A0C0-6FEE-4afd-89B9-0C35BF72A80B
 * GUIInterfaceVersion=1.00
 * LibraryVersion=2.4
 *********************************************************************/
//DOM-IGNORE-END
/*******************************************************************************

    USB Header File

Summary:
    This file aggregates all necessary header files for the Microchip USB Host,
    Device, and OTG libraries.  It provides a single-file can be included in
    application code.  The USB libraries simplify the implementation of USB
    applications by providing an abstraction of the USB module and its registers
    and bits such that the source code for the can be the same across various
    hardware platforms.

Description:
    This file aggregates all necessary header files for the Microchip USB Host,
    Device, and OTG libraries.  It provides a single-file can be included in
    application code.  The USB libraries simplify the implementation of USB
    applications by providing an abstraction of the USB module and its registers
    and bits such that the source code for the can be the same across various
    hardware platforms.

    Note that this file does not include the header files for any client or
    function drivers.

    This file is located in the "\<Install Directory\>\\Microchip\\Include\\USB"
    directory.

    When including this file in a new project, this file can either be
    referenced from the directory in which it was installed or copied
    directly into the user application folder. If the first method is
    chosen to keep the file located in the folder in which it is installed
    then include paths need to be added so that the library and the
    application both know where to reference each others files. If the
    application folder is located in the same folder as the Microchip
    folder (like the current demo folders), then the following include
    paths need to be added to the application's project:

    .

    ..\\..\\Microchip\\Include

    If a different directory structure is used, modify the paths as
    required. An example using absolute paths instead of relative paths
    would be the following:

    C:\\Microchip Solutions\\Microchip\\Include

    C:\\Microchip Solutions\\My Demo Application

******************************************************************************/
/******************************************************************************
 FileName:     usb.h
 Dependencies: See INCLUDES section
 Processor:    PIC18, PIC24, & PIC32 USB Microcontrollers
 Hardware:
 Complier:     Microchip C18 (for PIC18), C30 (for PIC24), or C32 (for PIC32)
 Company:      Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PICmicro(r) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PICmicro Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
********************************************************************/
//DOM-IGNORE-END

//DOM-IGNORE-BEGIN
/********************************************************************
 File Description:

 Change History:
  Rev           Description
  ----------    -----------
  2.6 - 2.9     No change except stack revision number
********************************************************************/
//DOM-IGNORE-END

#ifndef _USB_H_
#define _USB_H_
//DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: All necessary USB Library headers
// *****************************************************************************
// *****************************************************************************

#include "GenericTypeDefs.h"
#include "Compiler.h"

#include USB_CONFIG   			// Must be defined by the application

#include "usb_common.h"         // Common USB library definitions
#include "usb_ch9.h"            // USB device framework definitions

#if defined( USB_SUPPORT_DEVICE )
    #include "usb_device.h"     // USB Device abstraction layer interface
#endif

#if defined( USB_SUPPORT_HOST )
    #include "usb_host.h"       // USB Host abstraction layer interface
#endif

#if defined ( USB_SUPPORT_OTG )
    #include "usb_otg.h"
#endif

#include "usb_hal.h"            // Hardware Abstraction Layer interface

// *****************************************************************************
// *****************************************************************************
// Section: MCHPFSUSB Firmware Version
// *****************************************************************************
// *****************************************************************************

#define USB_MAJOR_VER   2       // Firmware version, major release number.
#define USB_MINOR_VER   9       // Firmware version, minor release number.
#define USB_DOT_VER     0       // Firmware version, dot release number.

#endif // _USB_H_
/*************************************************************************
 * EOF
 */

