// CRC: 20C35A1E87BE6D5C727502197CD041A78E93E071C8DEB2F9D3F427E27A444FEC73353167EC0BA5C77CF87B49E6B9AABFD065BB609AA530CAB11D25C81B468C449A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5DA327973381A1976FC7F25EB12E23A8DD919814387B259D5ED861F124CA1347958BC34F73C1545DDD9B4751239957123711B967629BFAF63F9D51115FC88858FF66F34D98D7B810F32BC0CF4C35FEE74F4596136F1D69FF9549D34A0D5AD11F371856FCA8299AD0190D65382B4B9554BDF3A230D564C38D1B54CBE7FC75FC27ACB6057F59853FD1A
// REVISION: 1.0
// GUID: 610F4CD5-7417-4559-80BE-07BE184BB1B6
// DATE: 08\08\2022
// DIR: CAL\PIC\USB\usb_hid_handler.c

void USBCBInitEP(void)
{

	//enable the HID endpoint
	#if (MX_OUT_PCK_SIZE > 0)

	  #if (MX_IN_PCK_SIZE > 0)

	    USBEnableEndpoint(HID_EP,USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

	  #else

	    USBEnableEndpoint(HID_EP,USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

	  #endif

	#else

	  #if (MX_IN_PCK_SIZE > 0)

	    USBEnableEndpoint(HID_EP,USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

	  #else

	    #Warning No USB data end points are enabled!

	  #endif

	#endif

    #if (MX_OUT_PCK_SIZE > 0)
		//Re-arm the OUT endpoint for the next packet
		USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&ReceivedDataBuffer,MX_OUT_PCK_SIZE);
    #endif
}


/*******************************************************************
 * Function:        bool USER_USB_CALLBACK_EVENT_HANDLER(
 *                        USB_EVENT event, void *pdata, uint16_t size)
 *
 * PreCondition:    None
 *
 * Input:           USB_EVENT event - the type of event
 *                  void *pdata - pointer to the event data
 *                  uint16_t size - size of the event data
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called from the USB stack to
 *                  notify a user application that a USB event
 *                  occured.  This callback is in interrupt context
 *                  when the USB_INTERRUPT option is selected.
 *
 * Note:            None
 *******************************************************************/
bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size)
{
    switch( (int) event )
    {
        case EVENT_TRANSFER:
            break;

        case EVENT_SOF:
            /* We are using the SOF as a timer to time the LED indicator.  Call
             * the LED update function here. */
            //APP_LEDUpdateUSBStatus();
            break;

        case EVENT_SUSPEND:
            /* Update the LED status for the suspend event. */
            //APP_LEDUpdateUSBStatus();

            //Call the hardware platform specific handler for suspend events for
            //possible further action (like optionally going reconfiguring the application
            //for lower power states and going to sleep during the suspend event).  This
            //would normally be done in USB compliant bus powered applications, although
            //no further processing is needed for purely self powered applications that
            //don't consume power from the host.
            //SYSTEM_Initialize(SYSTEM_STATE_USB_SUSPEND);
            break;

        case EVENT_RESUME:
            /* Update the LED status for the resume event. */
            //APP_LEDUpdateUSBStatus();

            //Call the hardware platform specific resume from suspend handler (ex: to
            //restore I/O pins to higher power states if they were changed during the
            //preceding SYSTEM_Initialize(SYSTEM_STATE_USB_SUSPEND) call at the start
            //of the suspend condition.
            //SYSTEM_Initialize(SYSTEM_STATE_USB_RESUME);
            break;

        case EVENT_CONFIGURED:
            /* When the device is configured, we can (re)initialize the
             * demo code. */
            //APP_DeviceCDCBasicDemoInitialize();
            USBCBInitEP();
            break;

        case EVENT_SET_DESCRIPTOR:
            break;

        case EVENT_EP0_REQUEST:
            /* We have received a non-standard USB request.  The HID driver
             * needs to check to see if the request was for it. */
            USBCheckHIDRequest();
            break;

        case EVENT_BUS_ERROR:
            break;

        case EVENT_TRANSFER_TERMINATED:
            break;

        default:
            break;
    }
    return true;
}
