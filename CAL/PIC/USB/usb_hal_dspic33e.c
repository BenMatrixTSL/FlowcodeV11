// CRC: 20C35A1E87BE6D5C727502197CD041A78E93E071C8DEB2F9D3F427E27A444FEC0408B6155481FF8B7E89F259C3976ECFD224EE04891053121C3C0E5F0AEAF17C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF530B2FFA43E8D4C7CD314864A475F47BF3F55ABB654A69664E356E2480C0CB3B73A32CC37D1AE661BDCBCAD2B3E953DB148E3A7A15436E676387F0441C5E87E239A924095B199C9E8577E182A188AD4025A1AA5A8DF714F38549D34A0D5AD11F372B4D946A956695E8C307593A24FB3A64A8190EB5F50298FE4565E63FDA312627DD474674123A97D
// REVISION: 1.0
// GUID: 1DC5DF07-7C31-4C9E-8E14-6DB9B2B5ED84
// DATE: 08\08\2022
// DIR: CAL\PIC\USB\usb_hal_dspic33e.c
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


#ifndef USB_HAL_DSPIC33E_C
#define USB_HAL_DSPIC33E_C

#include "usb.h"


/********************************************************************
Function:
    bool USBSleepOnSuspend(void)
    
Summary:
    Places the core into sleep and sets up the USB module
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

#endif //USB_HAL_DSPIC33E_C

