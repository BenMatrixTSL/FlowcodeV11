// CRC: 20C35A1E87BE6D5C727502197CD041A7B4F897819DC0E5BED5B717A7EE83366C45518EAA0C104FEC62C1CBCFFFCD4A4E9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF59B4947EA40ADB7212C234363F26112178966DFF49BF0D29B39B880B40E6F871C808C37FD5C99C6F3228FF5570D60867270CFA20D0755C518B63612F6761A04D9823C77C55ACC35C66D7AE79F1E442871A053822A9B71577C549D34A0D5AD11F386E44FAD56E69D416151901BA19F70985682B0CF4C686C32C0B4C7476DCE16968A51E041C1ABFE86
// REVISION: 1.0
// GUID: AF1803C2-655F-40E7-A914-97C60BE5948C
// DATE: 08\08\2022
// DIR: CAL\PIC\USB\system.h
/********************************************************************
 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
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
 *******************************************************************/

#ifndef SYSTEM_H
#define SYSTEM_H

#include <xc.h>
#include <stdbool.h>




#define MAIN_RETURN void

/*** System States **************************************************/
typedef enum
{
    SYSTEM_STATE_USB_START,
    SYSTEM_STATE_USB_SUSPEND,
    SYSTEM_STATE_USB_RESUME
} SYSTEM_STATE;

/*********************************************************************
* Function: void SYSTEM_Initialize( SYSTEM_STATE state )
*
* Overview: Initializes the system.
*
* PreCondition: None
*
* Input:  SYSTEM_STATE - the state to initialize the system into
*
* Output: None
*
********************************************************************/
void SYSTEM_Initialize( SYSTEM_STATE state );

/*********************************************************************
* Function: void SYSTEM_Tasks(void)
*
* Overview: Runs system level tasks that keep the system running
*
* PreCondition: System has been initalized with SYSTEM_Initialize()
*
* Input: None
*
* Output: None
*
********************************************************************/
//void SYSTEM_Tasks(void);
#define SYSTEM_Tasks()

#endif //SYSTEM_H
