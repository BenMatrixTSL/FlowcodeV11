// CRC: 20C35A1E87BE6D5C727502197CD041A78E93E071C8DEB2F9D3F427E27A444FEC04AFE21C2AA5BD5C26226AFBA2F1AE3CDCC2E067A0D7F98657743682A44EFDF89A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5A4CE5C77CC7EB87EF6B00C87F2261F09BF2C1D7824A46A3BD50E4BC2A68E33AD98FD9048126C2CC4BCC4AD608AE42CFBF04281F524319EC55DD39DB4694861DD3D52C9C723A75393C82445C125E741CEEA59970E87DEB940549D34A0D5AD11F366F3C94FB5E2BBD23F71B3A9A5E641A9251D8DED5F679CEC42BD2180FD7CFFB0161DC776D051D9AD
// REVISION: 1.0
// GUID: 41DE9948-31BD-4FFA-9415-96A47C3B1AC8
// DATE: 08\08\2022
// DIR: CAL\PIC\USB\usb_hal_pic24.c
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

#ifndef USB_HAL_PIC24F_C
#define USB_HAL_PIC24F_C

#include "system.h"
#include "system_config.h"
#include "usb.h"

//Only include the source for this file if you are using C30.  This code
//  applies only to PIC24 parts.
#if defined(__C30__) || defined __XC16__

/********************************************************************
Function:
    bool USBSleepOnSuspend(void)
    
Summary:
    Places the PIC24F core into sleep and sets up the USB module
    to wake up the device on USB activity.
    
PreCondition:
    IPL (in the SR register) must be non-zero.
    
Parameters:
    None
    
Return Values:
    true  - if entered sleep successfully
    false - if there was an error entering sleep
    
Remarks:
    Please note that before calling this function that it is the
    responsibility of the application to place all of the other
    peripherals or board features into a lower power state if
    required.

*******************************************************************/
bool USBSleepOnSuspend(void)
{
    unsigned int U1EIE_save, U1IE_save, U1OTGIE_save;
    unsigned char USB1IE_save;

    #if defined(USB_POLLING)
        //If IPL is equal to 0 then there is no way for the USB module to
        //  generate an interrupt to wake up the device.  
        if(_IPL == 0)
        {
            return false;
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

    return true;
}

#endif //__C30__

#endif //USB_HAL_PIC24F_C
