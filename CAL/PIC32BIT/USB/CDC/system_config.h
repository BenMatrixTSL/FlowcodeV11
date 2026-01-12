// CRC: A6459004C43C0517DC6DFC5681C2AD69C10B8AB997F36C59C8E2D33ADDA05BC1BDF7731755FF6F886426E20E82D34D49F66D19EB9BF0D1098260FA36729D5FD242CF814506C3A144C9EA55A52D517B409A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF512FE87582842F1B4978CE45C415F03723B85E1D4C39EE10288AD3247C5A721266F51BD79B23AE55D7C8BFC49843ED02B8E52983D4369C2F78FA9A339948FBF4966D1A7B91739A0D00E48F705A4656D696974C58542E236D8549D34A0D5AD11F3F9E607FE347FA7F869F8CB03B664C10B0B032CC660C3A1957C7C0C9FABE651313F9A05C84301D1C0
// REVISION: 1.0
// GUID: 211CD5A9-642A-4BA2-88BC-CD8C60856024
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\USB\CDC\system_config.h
/*******************************************************************************
  MPLAB Harmony System Configuration Header

  File Name:
    system_config.h

  Summary:
    Build-time configuration header for the system defined by this MPLAB Harmony
    project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    This configuration header must not define any prototypes or data
    definitions (or include any files that do).  It only provides macro
    definitions for build-time configuration options that are not instantiated
    until used by another MPLAB Harmony module or application.

    Created with MPLAB Harmony Version 1.11
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef _SYSTEM_CONFIG_H
#define _SYSTEM_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/
//#include "bsp_config.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: System Service Configuration
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
/* Common System Service Configuration Options
*/
#define SYS_VERSION_STR           "1.11"
#define SYS_VERSION               11100

/*** USB Driver Configuration ***/

#ifdef MX_USBFS
/* Enables Device Support */
#define DRV_USBFS_DEVICE_SUPPORT      true

/* Disable Device Support */
#define DRV_USBFS_HOST_SUPPORT      false

/* Maximum USB driver instances */
#define DRV_USBFS_INSTANCES_NUMBER    1

/* Interrupt mode enabled */
#define DRV_USBFS_INTERRUPT_MODE      true

/* Number of Endpoints used */
#define DRV_USBFS_ENDPOINTS_NUMBER    3
#endif

#ifdef MX_USBHS
/* Enables Device Support */
#define DRV_USBHS_DEVICE_SUPPORT      true

/* Disable Device Support */
#define DRV_USBHS_HOST_SUPPORT      false

/* Maximum USB driver instances */
#define DRV_USBHS_INSTANCES_NUMBER    1

/* Interrupt mode enabled */
#define DRV_USBHS_INTERRUPT_MODE      true

/* Number of Endpoints used */
#define DRV_USBHS_ENDPOINTS_NUMBER    3
#endif



/*** USB Device Stack Configuration ***/


/* The USB Device Layer will not initialize the USB Driver */
#define USB_DEVICE_DRIVER_INITIALIZE_EXPLICIT

/* Maximum device layer instances */
#define USB_DEVICE_INSTANCES_NUMBER     1

/* EP0 size in bytes */
#define USB_DEVICE_EP0_BUFFER_SIZE      64


/* Maximum instances of CDC function driver */
#define USB_DEVICE_CDC_INSTANCES_NUMBER     1


/* CDC Transfer Queue Size for both read and
   write. Applicable to all instances of the
   function driver */
#define USB_DEVICE_CDC_QUEUE_DEPTH_COMBINED 3


//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END


#endif // _SYSTEM_CONFIG_H
/*******************************************************************************
 End of File
*/

