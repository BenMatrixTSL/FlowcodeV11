// CRC: 5D982BB222882C54AB4AFF20A1590FC4128F294B41FC96FD138D7F694DC5EBF557FE541F4454158E1086265B0E5E1BA972D4F96D66F8918652B3E0EB213188944E104E808E2B5BD10EB8FEF6ED9E48729A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF57EFF3D33253F641DCABF6771820C8DD6BB0A70100977CCBA9C11C1F78BD5537F20431C94BAD137D549EE72D3E7267697E3BF4E576954EB14D606E41B95C5AF17996E5E64F7044376130129257D3AD403AC40132D0E305A07549D34A0D5AD11F3BBBF5C4B16D8F8D5A7EE35E88BA3219BDF4FA34804A563B7BFDF2E6001B9426D00C9FC801055D429
// REVISION: 1.0
// GUID: 9E8DF90A-6CE9-47F2-98AB-82E05DD62489
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\USB\usb_speaker_handler.c
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


 extern USB_HANDLE USBRxEvenHandle;
 extern USB_HANDLE USBRxOddHandle;
 extern INT16 ReceivedDataEvenBuffer[NO_OF_SAMPLES_IN_A_USB_FRAME];
 extern INT16 ReceivedDataOddBuffer[NO_OF_SAMPLES_IN_A_USB_FRAME];
 extern UINT8 audioMute;
 extern BOOL receivedDataEvenNeedsServicingNext;


 #if defined USB_AUDIO_INPUT_TERMINAL_CONTROL_REQUESTS_HANDLER
 void UsbAudioInputTerminalControlRequestsHandler(void)
 {


 }
 #endif

 #if defined USB_AUDIO_OUTPUT_TERMINAL_CONTROL_REQUESTS_HANDLER
 void UsbAudioOutputTerminalControlRequestsHandler(void)
 {


 }
 #endif

 #if defined USB_AUDIO_MIXER_UNIT_CONTROL_REQUESTS_HANDLER
 void UsbAudioMixerUnitControlRequestsHandler(void)
 {


 }
 #endif

 #if defined USB_AUDIO_SELECTOR_UNIT_CONTROL_REQUESTS_HANDLER
 void UsbAudioSelectorUnitControlRequestsHabdler(void)
 {


 }
 #endif

 #if defined USB_AUDIO_FEATURE_UNIT_CONTROL_REQUESTS_HANDLER
 void UsbAudioFeatureUnitControlRequestsHandler(void)
 {
     switch (SetupPkt.W_Value.byte.HB)
     {
        case MUTE_CONTROL:
            if (SetupPkt.bRequest == SET_CUR)
            {
                USBEP0Receive((BYTE*)&audioMute,SetupPkt.wLength,NULL);
            }
            else if (SetupPkt.bRequest == GET_CUR)
            {
                // Get Mute Control Status
                CtrlTrfData[0] = audioMute;
    			//CtrlTrfData[1] = 0x00;
    			USBEP0SendRAMPtr((BYTE*)CtrlTrfData, 1, USB_EP0_NO_OPTIONS);
            }
            break;
        case VOLUME_CONTROL:
            switch(SetupPkt.bRequest)
            {
                case SET_CUR:
                    //Set Current Volume
                    break;
                case SET_MIN:
                    break;
                case SET_MAX:
                    break;
                case SET_RES:
                    break;
                case GET_CUR:
                    // up on this request user needs to send the current volume to the host.
			        CtrlTrfData[0] = 0x43;
			        CtrlTrfData[1] = 0x00;
			        USBEP0SendRAMPtr((BYTE*)CtrlTrfData, 2, USB_EP0_NO_OPTIONS);
                    break;
                case GET_MIN:
			        CtrlTrfData[0] = 0;
			        CtrlTrfData[1] = 0;
			        USBEP0SendRAMPtr((BYTE*)CtrlTrfData, 2, USB_EP0_NO_OPTIONS);
                    break;
                case GET_MAX:
			        CtrlTrfData[0] = 0xFF;
			        CtrlTrfData[1] = 0xFF;
			        USBEP0SendRAMPtr((BYTE*)CtrlTrfData, 2, USB_EP0_NO_OPTIONS);
                    break;
                case GET_RES:
			        CtrlTrfData[0] = 0xFF;
			        CtrlTrfData[1] = 0xFF;
			        USBEP0SendRAMPtr((BYTE*)CtrlTrfData, 2, USB_EP0_NO_OPTIONS);
                    break;
                default:
                    break;
                }// end of switch(SetupPkt.bRequest)
            break;
        case BASS_CONTROL:
             break;
        case MID_CONTROL:
             break;
        case TREBLE_CONTROL:
             break;
        case GRAPHIC_EQUALIZER_CONTROL:
             break;
        case AUTOMATIC_GAIN_CONTROL:
             break;
        case DELAY_CONTROL:
             break;
        case BASS_BOOST_CONTROL:
             break;
        case LOUDNESS_CONTROL:
             break;
        default:
             break;
       }  //end of switch (SetupPkt.W_Value.byte.HB)

 }//end of void UsbFeatureUnitHandler(void)
 #endif

 #if defined USB_AUDIO_PROCESSING_UNIT_CONTROL_REQUESTS_HANDLER
 void UsbAudioProcessingUnitControlRequestsHandler(void)
 {
 }
 #endif

 #if defined USB_AUDIO_EXTENSION_UNIT_CONTROL_REQUESTS_HANDLER
 void UsbAudioExtensionUnitControlRequestsHandler(void)
 {
 }
 #endif

 #if defined USB_AUDIO_INTRFACE_CONTROL_REQUESTS_HANDLER
 void UsbAudioInterfaceControlRequestsHandler(void)
 {
 }
 #endif

 #if defined USB_AUDIO_ENDPOINT_CONTROL_REQUESTS_HANDLER
 void UsbAudioEndpointControlRequestsHandler(void)
 {
 }
 #endif

 #if defined USB_AUDIO_MEMORY_REQUESTS_HANDLER
 void UsbAudioMemoryRequestsHandler(void)
 {
 }
 #endif

 #if defined USB_AUDIO_STATUS_REQUESTS_HANDLER
 void UsbAudioStatusRequestsHandler(void)
 {
 }
 #endif


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
	USBCheckAudioRequest();
}

void USBCBStdSetDscHandler(void)
{
    // Must claim session ownership if supporting this request
}

void USBCBInitEP(void)
{
    //enable the Audio Streaming OUT endpoint
    USBEnableEndpoint(AS_EP,USB_OUT_ENABLED|USB_IN_ENABLED|USB_DISALLOW_SETUP);

    //Prepare the OUT endpoints to receive the first packets from the host.
    USBRxEvenHandle = USBRxOnePacket(AS_EP,(BYTE*)&ReceivedDataEvenBuffer,BYTES_PER_USB_FRAME); //First Audio Packet sent will arrive in the even buffer.
	USBRxOddHandle = USBRxOnePacket(AS_EP,(BYTE*)&ReceivedDataOddBuffer,BYTES_PER_USB_FRAME); //Second Audio Packet sent will arrive in the even buffer.
	receivedDataEvenNeedsServicingNext = TRUE;	//Used to keep track of which buffer will contain the next sequential data packet.

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
    switch( event )
    {
        case EVENT_TRANSFER:
            //Add application specific callback task or callback function here if desired.
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
