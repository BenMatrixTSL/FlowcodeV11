// CRC: 20C35A1E87BE6D5C727502197CD041A78E93E071C8DEB2F9D3F427E27A444FEC04AFE21C2AA5BD5C26226AFBA2F1AE3C73656FB9AB32025F92A3078D7323CB4F9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5104B444E6016286F9E3FC133F31D83D33E06D5C5820F3932E1F1203792197A2D90C48173A8268B4B8599D17B932B78F47FA1FA73EC3AF0392A94BB0B133522E6EDEA9FBFE436AC7AF5ABB5B3A8DFE83782F4206EE2B091C9549D34A0D5AD11F3DF010FA1A84E6EDB48CA74EDC298B50EC679BB0131C7F0D3FFCF1C90B393605E9F32B96E9FC2F3A9
// REVISION: 1.0
// GUID: 54978A9B-5988-46C9-89A5-FC6D32D6E720
// DATE: 08\08\2022
// DIR: CAL\PIC\USB\usb_hal_pic24f.c
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

//DOM-IGNORE-BEGIN
/********************************************************************
 Change History:
  Rev    Description
  ----   -----------
  2.7    Created USBSleepOnSuspend() function to simply process of putting
           the PIC24F device in the correct state before issuing the sleep
           instruction and returning the device to the correct state after
           exiting sleep. 
********************************************************************/
//DOM-IGNORE-END

#ifndef USB_HAL_PIC24F_C
#define USB_HAL_PIC24F_C

#include "usb.h"

//Only include the source for this file if you are using C30.  This code
//  applies only to PIC24 parts.
#if defined(__C30__) || defined __XC16__

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

#endif //__C30__

#endif //USB_HAL_PIC24F_C
