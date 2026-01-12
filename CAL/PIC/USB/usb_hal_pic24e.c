// CRC: 20C35A1E87BE6D5C727502197CD041A78E93E071C8DEB2F9D3F427E27A444FEC04AFE21C2AA5BD5C26226AFBA2F1AE3C38762EC6A048CF96A74A0FD5DF1FE5AC9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF527298BF1EE94FDF7E489A54499300AECD3231565C3570B11F7AD770AA0A7413DE86977E5F3D24ABEDE87C26BB51684EA8E4C97CB715B211E4E1474883660CA5F794D42C48431357DCFC174B1628AB7906897A1C64EC68459549D34A0D5AD11F3B9130539C8DBA0F978E1FC4C290A3DB6C8625B491CF65A62ACA9CE2DF1EA8436E42CFE37638C9748
// REVISION: 1.0
// GUID: F8ED875B-2CE3-46AF-B972-530A9B356731
// DATE: 08\08\2022
// DIR: CAL\PIC\USB\usb_hal_pic24e.c
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

#ifndef USB_HAL_PIC24E_C
#define USB_HAL_PIC24E_C

#include "usb.h"


/********************************************************************
Function:
    BOOL USBSleepOnSuspend(void)
    
Summary:
    Places the PIC24F core into sleep and sets up the USB module
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

#endif //USB_HAL_PIC24E_C

