// CRC: A6459004C43C0517DC6DFC5681C2AD69C10B8AB997F36C59C8E2D33ADDA05BC19928AB236C36114ED3A65CBB2C8D91CDF66D19EB9BF0D1098260FA36729D5FD242CF814506C3A144C9EA55A52D517B409A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF572C71563D058637C51E1BA243ED23DAAD071989F686CD54DCD1AD2202D3B0815799D40050F85BA87D9ABBC9F551AE9361F2A96FAD478FD03A66B689084C92562F82F7CC9C58FCC726057CFD8D0BB639D6EE73606A3D0943B549D34A0D5AD11F37C05A1ED251BEDF9EEB0836771E4CBB69B5E3281B77685E461112B2378F6127E5D3A7ED706D09BBA
// REVISION: 1.0
// GUID: 1E8446ED-B392-4F66-A4BC-A89862ADCB58
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\USB\HID\system_config.h
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
#define DRV_USBFS_ENDPOINTS_NUMBER    2
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
#define DRV_USBHS_ENDPOINTS_NUMBER    2
#endif



/*** USB Device Stack Configuration ***/


/* The USB Device Layer will not initialize the USB Driver */
#define USB_DEVICE_DRIVER_INITIALIZE_EXPLICIT

/* Maximum device layer instances */
#define USB_DEVICE_INSTANCES_NUMBER     1

/* EP0 size in bytes */
#define USB_DEVICE_EP0_BUFFER_SIZE      64

/* Enable SOF Events */ 
#define USB_DEVICE_SOF_EVENT_ENABLE     



/* Maximum instances of HID function driver */
#define USB_DEVICE_HID_INSTANCES_NUMBER     1



/* HID Transfer Queue Size for both read and
   write. Applicable to all instances of the
   function driver */
#define USB_DEVICE_HID_QUEUE_DEPTH_COMBINED 2



//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END


#endif // _SYSTEM_CONFIG_H
/*******************************************************************************
 End of File
*/

