// CRC: 5D982BB222882C54AB4AFF20A1590FC4128F294B41FC96FD138D7F694DC5EBF522A957FA48E0002EFCF730E1497540E2D526D5410D44786AA6A75A8C0C561CF04E104E808E2B5BD10EB8FEF6ED9E48729A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF55DA984786138F67A630DDF870FCE6EA1C6FFF2F234E7ACA099F9BF8A73DEC48AEDB18205C75E902153B6BE2CABA282D30447CF03139D9A2EFC2A11EFB7AA59F54447B4B4C7471A772ADDC2953714164530C4F28FE64C6E5B549D34A0D5AD11F39FFFD3F0C2F2BF6F7020BB6544FB14B588690BE3F4FEB70807369D99911C23D5D43797C197BFDEC5
// REVISION: 1.0
// GUID: B735013A-144C-41E3-8A4A-915926CF45E9
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\USB\usb_generic_handler.c
/*********************************************************************
 *                    Flowcode USB Library Code
 *
 * (c) 2009 Matrix Multimedia Ltd.
 * http://www.matrixmultimedia.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix Multimedia Ltd (the
 * “Company”) for its Flowcode graphical programming language is
 * intended and supplied to you, the Company’s customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Changelog:
 *
 *  date  | by | description
 * -------+----+-----------------------------------------------------
 * 140910 | BR | Created
 ********************************************************************/


void USBCBSuspend(void)
{
	//Example power saving code.  Insert appropriate code here for the desired
	//application behavior.  If the microcontroller will be put to sleep, a
	//process similar to that shown below may be used:

	//ConfigureIOPinsForLowPower();
	//SaveStateOfAllInterruptEnableBits();
	//DisableAllInterruptEnableBits();
	//EnableOnlyTheInterruptsWhichWillBeUsedToWakeTheMicro();	//should enable at least USBActivityIF as a wake source
	//Sleep();
	//RestoreStateOfAllPreviouslySavedInterruptEnableBits();	//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.
	//RestoreIOPinsToNormal();									//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.

	//Alternatively, the microcontorller may use clock switching to reduce current consumption.
	#if defined(__18CXX)
    	//Configure device for low power consumption
    	mLED_1_Off();
    	mLED_2_Off();
    	//Should also configure all other I/O pins for lowest power consumption.
    	//Typically this is done by driving unused I/O pins as outputs and driving them high or low.
    	//In this example, this is not done however, in case the user is expecting the I/O pins
    	//to remain tri-state and has hooked something up to them.
    	//Leaving the I/O pins floating will waste power and should not be done in a
    	//real application.

        //Note: The clock switching code needed is processor specific, as the
        //clock trees and registers aren't identical accross all PIC18 USB device
        //families.
    	#if defined(PIC18F97J94_FAMILY)
            OSCCON = 0x06;  //FRC / 16 = 500kHz selected.
    	#else
        	OSCCON = 0x13;	//Sleep on sleep, 125kHz selected as microcontroller clock source
    	#endif
	#endif

	//IMPORTANT NOTE: Do not clear the USBActivityIF (ACTVIF) bit here.  This bit is
	//cleared inside the usb_device.c file.  Clearing USBActivityIF here will cause
	//things to not work as intended.

}

void USBCBWakeFromSuspend(void)
{
	// If clock switching or other power savings measures were taken when
	// executing the USBCBSuspend() function, now would be a good time to
	// switch back to normal full power run mode conditions.  The host allows
	// 10+ milliseconds of wakeup time, after which the device must be
	// fully back to normal, and capable of receiving and processing USB
	// packets.  In order to do this, the USB module must receive proper
	// clocking (IE: 48MHz clock must be available to SIE for full speed USB
	// operation).
	// Make sure the selected oscillator settings are consistent with USB
    // operation before returning from this function.

	//Switch clock back to main clock source necessary for USB operation
	//Previous clock source was something low frequency as set in the
	//USBCBSuspend() function.
	#if defined(__18CXX)
        #if defined(PIC18F97J94_FAMILY)
            OSCCON3 = 0x01; //8MHz FRC / 2 = 4MHz output
            OSCCON = 0x01;  //FRC with PLL selected
            while(OSCCON2bits.LOCK == 0);   //Wait for PLL lock
        #elif defined(PIC18F45K50_FAMILY)
            OSCCON = 0x70;                   //Switch to 16MHz HFINTOSC
            while(OSCCON2bits.PLLRDY != 1);  //Wait for PLL lock
        #else
        	OSCCON = 0x60;		//Primary clock source selected.
            //Adding a software start up delay will ensure
            //that the primary oscillator and PLL are running before executing any other
            //code.  If the PLL isn't being used, (ex: primary osc = 48MHz externally applied EC)
            //then this code adds a small unnecessary delay, but it is harmless to execute anyway.
        	{
                unsigned int pll_startup_counter = 800;	//Long delay at 31kHz, but ~0.8ms at 48MHz
                while(pll_startup_counter--);			//Clock will switch over while executing this delay loop
            }
        #endif
	#endif
}

void USBCB_SOF_Handler(void)
{
    // No need to clear UIRbits.SOFIF to 0 here.
    // Callback caller is already doing that.
}

void USBCBErrorHandler(void)
{
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.

	// Typically, user firmware does not need to do anything special
	// if a USB error occurs.  For example, if the host sends an OUT
	// packet to your device, but the packet gets corrupted (ex:
	// because of a bad connection, or the user unplugs the
	// USB cable during the transmission) this will typically set
	// one or more USB error interrupt flags.  Nothing specific
	// needs to be done however, since the SIE will automatically
	// send a "NAK" packet to the host.  In response to this, the
	// host will normally retry to send the packet again, and no
	// data loss occurs.  The system will typically recover
	// automatically, without the need for application firmware
	// intervention.

	// Nevertheless, this callback function is provided, such as
	// for debugging purposes.
}

void USBCBCheckOtherReq(void)
{
}

void USBCBStdSetDscHandler(void)
{
    // Must claim session ownership if supporting this request
}

void USBCBInitEP(void)
{
    //Enable the appplication data endpoint(s)
    USBEnableEndpoint(USBGEN_EP_NUM,USB_OUT_ENABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    //Prepare the OUT endpoint for the next packet that the host might try to send
    USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM,(BYTE*)&OUTPacket,USBGEN_EP_SIZE);
}

void USBCBSendResume(void)
{
    static WORD delay_count;

    //First verify that the host has armed us to perform remote wakeup.
    //It does this by sending a SET_FEATURE request to enable remote wakeup,
    //usually just before the host goes to standby mode (note: it will only
    //send this SET_FEATURE request if the configuration descriptor declares
    //the device as remote wakeup capable, AND, if the feature is enabled
    //on the host (ex: on Windows based hosts, in the device manager
    //properties page for the USB device, power management tab, the
    //"Allow this device to bring the computer out of standby." checkbox
    //should be checked).
    if(USBGetRemoteWakeupStatus() == TRUE)
    {
        //Verify that the USB bus is in fact suspended, before we send
        //remote wakeup signalling.
        if(USBIsBusSuspended() == TRUE)
        {
            USBMaskInterrupts();

            //Clock switch to settings consistent with normal USB operation.
            USBCBWakeFromSuspend();
            USBSuspendControl = 0;
            USBBusIsSuspended = FALSE;  //So we don't execute this code again,
                                        //until a new suspend condition is detected.

            //Section 7.1.7.7 of the USB 2.0 specifications indicates a USB
            //device must continuously see 5ms+ of idle on the bus, before it sends
            //remote wakeup signalling.  One way to be certain that this parameter
            //gets met, is to add a 2ms+ blocking delay here (2ms plus at
            //least 3ms from bus idle to USBIsBusSuspended() == TRUE, yeilds
            //5ms+ total delay since start of idle).
            delay_count = 3600U;
            do
            {
                delay_count--;
            }while(delay_count);

            //Now drive the resume K-state signalling onto the USB bus.
            USBResumeControl = 1;       // Start RESUME signaling
            delay_count = 1800U;        // Set RESUME line for 1-13 ms
            do
            {
                delay_count--;
            }while(delay_count);
            USBResumeControl = 0;       //Finished driving resume signalling

            USBUnmaskInterrupts();
        }
    }
}

BOOL USER_USB_CALLBACK_EVENT_HANDLER(int event, void *pdata, WORD size)
{
    switch(event)
    {
        case EVENT_TRANSFER:
            transfer = 1;
			Nop();
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_CONFIGURED:
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER_TERMINATED:
            //Add application specific callback task or callback function here if desired.
            //The EVENT_TRANSFER_TERMINATED event occurs when the host performs a CLEAR
            //FEATURE (endpoint halt) request on an application endpoint which was
            //previously armed (UOWN was = 1).  Here would be a good place to:
            //1.  Determine which endpoint the transaction that just got terminated was
            //      on, by checking the handle value in the *pdata.
            //2.  Re-arm the endpoint if desired (typically would be the case for OUT
            //      endpoints).
            break;
        default:
            break;
    }
    return TRUE;
}
