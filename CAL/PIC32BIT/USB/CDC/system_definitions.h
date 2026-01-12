// CRC: A6459004C43C0517DC6DFC5681C2AD69C10B8AB997F36C59C8E2D33ADDA05BC1BDF7731755FF6F886426E20E82D34D49BCFBCE8E0322F8E3A34E418FEC706C164CDC8175568DD796CD822EDE9FC067D5622E4A10154D10ED53988D8E819F1E2C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF541E6916AF712356B3AF157CFFCDCBAF749FC22A91A1CB5660A56866A136FA3C0B7F83664EBB1235C1E1B7D70581576BFF65BC67D8D215848EAB4C921F52EEA45A25E656E6C68C6798A893B243D35A56F6B5144C11D26A980549D34A0D5AD11F39E34534272EA2092A84C8BCEC4A082C4EE8107D2CEEF696127A8E1A814A6FBB04A61C0D2CB77CF29
// REVISION: 1.0
// GUID: B0A794B9-33F3-4A46-9DDA-A10EE843D7AA
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\USB\CDC\system_definitions.h
/*******************************************************************************
  System Definitions

  File Name:
    system_definitions.h

  Summary:
    MPLAB Harmony project system definitions.

  Description:
    This file contains the system-wide prototypes and definitions for an MPLAB
    Harmony project.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END

#ifndef _SYS_DEFINITIONS_H
#define _SYS_DEFINITIONS_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "system/common/sys_common.h"
#include "system/common/sys_module.h"
//#include "system/clk/sys_clk.h"
#include "system/devcon/sys_devcon.h"
#include "system/int/sys_int.h"
#include "system/ports/sys_ports.h"

/*
#ifdef MX_USBFS
  #include "driver/usb/usbfs/drv_usbfs.h"
#endif

#ifdef MX_USBHS
  #include "driver/usb/usbhs/drv_usbhs.h"
#endif
*/

#include "driver/usb/usbfs/drv_usbfs.h"
#include "driver/usb/usbhs/drv_usbhs.h"

#include "usb/usb_device.h"

#include "usb/usb_device_cdc.h"
#include "CDCComp.h"


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END 

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* System Objects

  Summary:
    Structure holding the system's object handles

  Description:
    This structure contains the object handles for all objects in the
    MPLAB Harmony project's system configuration.

  Remarks:
    These handles are returned from the "Initialize" functions for each module
    and must be passed into the "Tasks" function for each module.
*/

typedef struct
{
    SYS_MODULE_OBJ  sysDevcon;
    SYS_MODULE_OBJ  drvUSBObject;
    
    SYS_MODULE_OBJ  usbDevObject0;
} SYSTEM_OBJECTS;


// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************

extern SYSTEM_OBJECTS sysObj;



//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _SYS_DEFINITIONS_H */
/*******************************************************************************
 End of File
*/

