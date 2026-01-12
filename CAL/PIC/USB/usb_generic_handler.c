// CRC: 20C35A1E87BE6D5C727502197CD041A78E93E071C8DEB2F9D3F427E27A444FEC00894F260DCE4AFA9E6E82A5C3BFB326ECC1F42E57A862F6B337427A7CC76EEB186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF56A4B5917FBDF3E55DEEEA30FBD2AEE2BCF897B73FDD1239AD996ACC1FDB8CF77AE67A719DC20E53714839DDCD3765C7E174E82824EA530558DFF6715FDFCDA12EA27B5F557D6B7E5E8F41B2649379A6DA5F6A0F645B58616549D34A0D5AD11F3AE5E32E83F96C9828CE3C0CD87A100830A8EFA6AA32CADC3D0E381242689B9FD3D511918C7872FD9
// REVISION: 1.0
// GUID: 270AF098-5551-4CE0-85D8-167F2E30E063
// DATE: 08\08\2022
// DIR: CAL\PIC\USB\usb_generic_handler.c
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
    switch((int)event)
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
			//initialize the variable holding the handle for the last
			// transmission
			USBGenericOutHandle = 0;
			USBGenericInHandle = 0;

			//Enable the application endpoints
			USBEnableEndpoint(USBGEN_EP_NUM,USB_OUT_ENABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

			//Arm the application OUT endpoint, so it can receive a packet from the host
			USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM,(uint8_t*)&OUTPacket,USBGEN_EP_SIZE);
            break;

        case EVENT_SET_DESCRIPTOR:
            break;

        case EVENT_EP0_REQUEST:
            /* We have received a non-standard USB request.  The vendor driver
             * needs to check to see if the request was for it. */
            USBCheckVendorRequest();
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

