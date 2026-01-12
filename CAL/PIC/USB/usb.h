// CRC: 20C35A1E87BE6D5C727502197CD041A75C76786D3D52769C47E2A1680F235F57622E4A10154D10ED53988D8E819F1E2C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF549909503AC740351A070E59A79C743768E42762BE655005DCACB4499B37DA13464E43E1C1997594F6BC7182B4A028660E82CF4E4A35E5124E2B7AB1C157A987F07D5B83BDF0948847BB702C08A962CC07C961175CCF4CAAB549D34A0D5AD11F3C50B38170CC2FA53D1F028E276F65A49F813EF87D726C107B68A65FD090A6D6B4C68FB27E1809948
// REVISION: 1.0
// GUID: 710E06E2-FB10-4FA9-BC91-AAD6866BDEA7
// DATE: 08\08\2022
// DIR: CAL\PIC\USB\usb.h
// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright 2015 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license),
please contact mla_licensing@microchip.com
*******************************************************************************/
//DOM-IGNORE-END


/*******************************************************************************
 Module for Microchip USB Library

  Company:
    Microchip Technology Inc.

  File Name:
    usb.h

  Summary:
    This header file exposes the core library APIs and definitions for the USB
    library.

  Description:
    This header file exposes the core library APIs and definitions for the USB
    library.  The user is responsible for also including the header file for
    the specific driver they will be using.
*******************************************************************************/

#ifndef _USB_H_
#define _USB_H_

#include "../../../CAL/PIC/USB/system.h"
#include "../../../CAL/PIC/USB/system_config.h"          // Must be defined by the application

#include "../../../CAL/PIC/USB/usb_common.h"         // Common USB library definitions
#include "../../../CAL/PIC/USB/usb_ch9.h"            // USB device framework definitions

#if defined( USB_SUPPORT_DEVICE )
    #include "../../../CAL/PIC/USB/usb_device.h"     // USB Device abstraction layer interface
#endif

#if defined( USB_SUPPORT_HOST )
    #include "../../../CAL/PIC/USB/usb_host.h"       // USB Host abstraction layer interface
#endif

#include "../../../CAL/PIC/USB/usb_hal.h"            // Hardware Abstraction Layer interface

/* USB Library version number.  This can be used to verify in an application
   specific version of the library is being used.
 */
#define USB_MAJOR_VER   2        // Firmware version, major release number.
#define USB_MINOR_VER   13       // Firmware version, minor release number.
#define USB_DOT_VER     0        // Firmware version, dot release number.

#endif // _USB_H_



