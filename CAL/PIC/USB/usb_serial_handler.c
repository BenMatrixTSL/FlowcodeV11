// CRC: 20C35A1E87BE6D5C727502197CD041A78E93E071C8DEB2F9D3F427E27A444FECC437D42B4ED35FA0269318E200F7F3694E839E98AE679622D44F511328687F839A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF557B264E2D4673FA923DA8A26DBD042EAC1873F43C888472C6303D47AC02F6468BDE1C3493A258A8D1231A33D3E2B0334D8F2624E8E5AD63BB911284EF52215C6B2F3892E7E6FDF04DD9BE2E4A4BD6AB84C53355A9F3128EF549D34A0D5AD11F3726737F581C2814516F27EA490237DC226F488EF54E1AA3E7E0891B16C3AB1D1B75B7955E2A3F925
// REVISION: 1.0
// GUID: C74184C5-AEEA-4D29-8330-955F8FC4340E
// DATE: 08\08\2022
// DIR: CAL\PIC\USB\usb_serial_handler.c

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
            CDCInitEP();
            break;

        case EVENT_SET_DESCRIPTOR:
            break;

        case EVENT_EP0_REQUEST:
            /* We have received a non-standard USB request.  The HID driver
             * needs to check to see if the request was for it. */
            USBCheckCDCRequest();
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
