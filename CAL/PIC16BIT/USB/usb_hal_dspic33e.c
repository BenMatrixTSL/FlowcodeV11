// CRC: 5D982BB222882C54AB4AFF20A1590FC4128F294B41FC96FD138D7F694DC5EBF5439B78CD3DB80870FA286EC3C8CB625CEA2CE75F2C8DAD43486DF67925C8FC18F7500A46C16207D3C7482202BE65C04F9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5EB259341E3875BD39436F29FC45CF32FA039DC091A66DD1CC2C0881D2B6710F203A1C24E51BDACCA61809FB34026A8E75D656968904B9ADAA92DBC979EECCEC9DFD19D81EE30A74D7141E5D939181E1AEFA62DE588905CEC549D34A0D5AD11F3052DDB122F23E3392A507577F0D2BC8CC82E0B20B7F4C9A7CC6735C2880B0855018D7FE4AA495AC4
// REVISION: 1.0
// GUID: 5CC2582F-A83E-4030-AF20-00B7660FB987
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\USB\usb_hal_dspic33e.c
/******************************************************************************

    USB Hardware Abstraction Layer (HAL)

Summary:
    This file abstracts the hardware interface.  The USB stack firmware can be
    compiled to work on different USB microcontrollers, such as PIC18 and PIC24.
    The USB related special function registers and bit names are generally very
    similar between the device families, but small differences in naming exist.

Description:
    This file abstracts the hardware interface.  The USB stack firmware can be
    compiled to work on different USB microcontrollers, such as PIC18 and PIC24.
    The USB related special function registers and bit names are generally very
    similar between the device families, but small differences in naming exist.

    In order to make the same set of firmware work accross the device families,
    when modifying SFR contents, a slightly abstracted name is used, which is
    then "mapped" to the appropriate real name in the usb_hal_picxx.h header.

    Make sure to include the correct version of the usb_hal_picxx.h file for
    the microcontroller family which will be used.

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


*******************************************************************************/
//DOM-IGNORE-BEGIN
/******************************************************************************

 File Description:

 This file defines the interface to the USB hardware abstraction layer.

 Filename:        usb_hal_pic33E.c
 Dependancies:    none
 Processor:       dsPIC33E USB Microcontrollers
 Hardware:        dsPIC33E USB Microcontrollers
 Compiler:        Microchip C30 (for PIC24)
 Company:         Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PICmicro(R) Microcontroller is intended and
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

 *************************************************************************/


#ifndef USB_HAL_DSPIC33E_C
#define USB_HAL_DSPIC33E_C

#include "usb.h"


/********************************************************************
Function:
    BOOL USBSleepOnSuspend(void)

Summary:
    Places the core into sleep and sets up the USB module
    to wake up the device on USB activity.

PreCondition:
    IPL (in the SR register) must be non-zero.

Parameters:
    None

Return Values:
    TRUE  - if entered sleep successfully
    FALSE - if there was an error entering sleep

Remarks:
    Please note that before calling this function that it is the
    responsibility of the application to place all of the other
    peripherals or board features into a lower power state if
    required.

*******************************************************************/
BOOL USBSleepOnSuspend(void)
{
    unsigned int U1EIE_save, U1IE_save, U1OTGIE_save;
    unsigned char USB1IE_save;

    #if defined(USB_POLLING)
        //If IPL is equal to 0 then there is no way for the USB module to
        //  generate an interrupt to wake up the device.
        if(_IPL == 0)
        {
            return FALSE;
        }

        //Set the interrupt priority to a level that will wake up the part (>0)
        //  but will not cause a interrupt vector jump (USB1IP<=IPL)
        _USB1IP = 1;
    #endif

    //Save the old interrupt and CPU settings
    U1EIE_save = U1EIE;
    U1IE_save = U1IE;
    U1OTGIE_save = U1OTGIE;
    USB1IE_save = IEC5bits.USB1IE;

    //Disable all USB interrupts
    U1EIE = 0;
    U1IE = 0;
    U1OTGIE = 0;

    //Enable the interrupt
    IFS5bits.USB1IF = 0;
    U1OTGIEbits.ACTVIE = 1;
    USBClearInterruptFlag(USBActivityIFReg,USBActivityIFBitNum);
    IEC5bits.USB1IE = 1;

    Sleep();

    #if defined(USB_POLLING)
        //Disable the interrupt
        _USB1IP = 0;
    #endif

    //restore the previous interrupt settings
    IEC5bits.USB1IE = USB1IE_save;
    U1EIE = U1EIE_save;
    U1IE = U1IE_save;
    U1OTGIE = U1OTGIE_save;

    return TRUE;
}

#endif //USB_HAL_DSPIC33E_C

