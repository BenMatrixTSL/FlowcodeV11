// CRC: A6459004C43C0517DC6DFC5681C2AD69C10B8AB997F36C59C8E2D33ADDA05BC16FA1F76CE5BD9A54F0CE206B244EEA38F6F63A6FB8B1500D420EB282E16823AB9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF56AD4AFEE515319B5F3216397E8472FE264AB73D41AAF909512824BBD4A8A69E50EA8530E1C18C1F4F2E5DB623712C7EA5FB4E5EEEB3A35E6B5642CBBEF6D3CD47F87D5211F63724FD2A8327F05BA6285AC40132D0E305A07549D34A0D5AD11F32F732533A35AA48604F711DF93BB8890A366B158A8F651230C9FBA1F01A7E45B08B65E7F68830DD9
// REVISION: 1.0
// GUID: B23E4284-A582-4BA4-9C91-0AFA32729092
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\USB\CDC\CDCComp.c

#include "system_config.h"
#include "system_definitions.h"
#include "CDC_Desc.h"
#include "mx_usb_cdc_conf.h"


extern APP_DATA appData;
extern uint8_t writeBuffer[];
extern uint8_t readBuffer[];


void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;


    /* Device Layer Handle  */
    appData.deviceHandle = USB_DEVICE_HANDLE_INVALID ;

    /* Device configured status */
    appData.isConfigured = false;

    /* Initial get line coding state */
    appData.getLineCodingData.dwDTERate   = 9600;
    appData.getLineCodingData.bParityType =  0;
    appData.getLineCodingData.bParityType = 0;
    appData.getLineCodingData.bDataBits   = 8;

    /* Read Transfer Handle */
    appData.readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

    /* Intialize the read data */
    appData.readProcessedLen = 0;

    /* Write Transfer Handle */
    appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
    
    /*Initialize the write data */
//    appData.writeLen = sizeof(writeString);
//	memcpy(writeBuffer, writeString, appData.writeLen);
    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************


/*******************************************************
 * USB CDC Device Events - Application Event Handler
 *******************************************************/

USB_DEVICE_CDC_EVENT_RESPONSE APP_USBDeviceCDCEventHandler
(
    USB_DEVICE_CDC_INDEX index ,
    USB_DEVICE_CDC_EVENT event ,
    void * pData,
    uintptr_t userData
)
{
    APP_DATA * appDataObject;
    appDataObject = (APP_DATA *)userData;
    USB_CDC_CONTROL_LINE_STATE * controlLineStateData;

    switch ( event )
    {
        case USB_DEVICE_CDC_EVENT_GET_LINE_CODING:

            /* This means the host wants to know the current line
             * coding. This is a control transfer request. Use the
             * USB_DEVICE_ControlSend() function to send the data to
             * host.  */

            USB_DEVICE_ControlSend(appDataObject->deviceHandle,
                    &appDataObject->getLineCodingData, sizeof(USB_CDC_LINE_CODING));

            break;

        case USB_DEVICE_CDC_EVENT_SET_LINE_CODING:

            /* This means the host wants to set the line coding.
             * This is a control transfer request. Use the
             * USB_DEVICE_ControlReceive() function to receive the
             * data from the host */

            USB_DEVICE_ControlReceive(appDataObject->deviceHandle,
                    &appDataObject->setLineCodingData, sizeof(USB_CDC_LINE_CODING));

            break;

        case USB_DEVICE_CDC_EVENT_SET_CONTROL_LINE_STATE:

            /* This means the host is setting the control line state.
             * Read the control line state. We will accept this request
             * for now. */

            controlLineStateData = (USB_CDC_CONTROL_LINE_STATE *)pData;
            appDataObject->controlLineStateData.dtr = controlLineStateData->dtr;
            appDataObject->controlLineStateData.carrier = controlLineStateData->carrier;

            USB_DEVICE_ControlStatus(appDataObject->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);

            break;

        case USB_DEVICE_CDC_EVENT_SEND_BREAK:

            /* This means that the host is requesting that a break of the
             * specified duration be sent.  */
            break;

        case USB_DEVICE_CDC_EVENT_READ_COMPLETE:
            /* This means that the host has sent some data*/
            appDataObject->readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
			USB_DEVICE_CDC_EVENT_DATA_READ_COMPLETE *evtData = pData;
			appDataObject->readLen = evtData->length;
//			readString[appDataObject->readProcessedLen] = readBuffer[0];
//			if (appDataObject->readProcessedLen < 8)
//			{
//            	appDataObject->readProcessedLen++;
//			}
            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_RECEIVED:

            /* The data stage of the last control transfer is
             * complete. For now we accept all the data */

            USB_DEVICE_ControlStatus(appDataObject->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);
            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_SENT:

            /* This means the GET LINE CODING function data is valid. We dont
             * do much with this data in this demo. */
            break;

        case USB_DEVICE_CDC_EVENT_WRITE_COMPLETE:

            /* This means that the host has sent some data*/
            appDataObject->writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
            break;

        default:
            break;
    }

    return USB_DEVICE_CDC_EVENT_RESPONSE_NONE;
}

/***********************************************
 * Application USB Device Layer Event Handler.
 ***********************************************/
void APP_USBDeviceEventHandler ( USB_DEVICE_EVENT event, void * eventData, uintptr_t context )
{
    USB_DEVICE_EVENT_DATA_CONFIGURED *configuredEventData;

    switch ( event )
    {
        case USB_DEVICE_EVENT_SOF:
            break;

        case USB_DEVICE_EVENT_RESET:

            appData.isConfigured = false;

            break;

        case USB_DEVICE_EVENT_CONFIGURED:

            /* Check the configuration. We only support configuration 1 */
            configuredEventData = (USB_DEVICE_EVENT_DATA_CONFIGURED*)eventData;
            if ( configuredEventData->configurationValue == 1)
            {
                /* Register the CDC Device application event handler here.
                 * Note how the appData object pointer is passed as the
                 * user data */

                USB_DEVICE_CDC_EventHandlerSet(USB_DEVICE_CDC_INDEX_0, APP_USBDeviceCDCEventHandler, (uintptr_t)&appData);

                /* Mark that the device is now configured */
                appData.isConfigured = true;

            }
            break;

        case USB_DEVICE_EVENT_POWER_DETECTED:

            /* VBUS was detected. We can attach the device */
            USB_DEVICE_Attach(appData.deviceHandle);
            break;

        case USB_DEVICE_EVENT_POWER_REMOVED:

            /* VBUS is not available any more. Detach the device. */
            USB_DEVICE_Detach(appData.deviceHandle);
            break;

        case USB_DEVICE_EVENT_SUSPENDED:
            break;

        case USB_DEVICE_EVENT_RESUMED:
        case USB_DEVICE_EVENT_ERROR:
        default:
            break;
    }
}

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    static void USB_TX_Task (void)
    
   Remarks:
    Feeds the USB write function. 
*/
void USB_TX_Task (void)
{
    if(!appData.isConfigured)
    {
        appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
    }
    else
    {
        /* Schedule a write if data is pending 
         */
        if ((appData.writeLen > 0)/* && (appData.writeTransferHandle == USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID)*/)
        {
            USB_DEVICE_CDC_Write(USB_DEVICE_CDC_INDEX_0,
                                 &appData.writeTransferHandle,
                                 writeBuffer, 
                                 appData.writeLen,
                                 USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
        }
    }
}

/******************************************************************************
  Function:
    static void USB_RX_Task (void)
    
   Remarks:
    Reads from the USB. 
*/
void USB_RX_Task(void)
{
    if(!appData.isConfigured)
    {
        appData.readTransferHandle  = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
        appData.readProcessedLen    = 0;
    }
    else
    {
        /* Schedule a read if none is pending and all previously read data
           has been processed
         */
        if((appData.readProcessedLen < 8) && (appData.readTransferHandle  == USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID))
        {
            USB_DEVICE_CDC_Read (USB_DEVICE_CDC_INDEX_0,
                                 &appData.readTransferHandle, 
                                 readBuffer,
                                 MX_RX_EP_SIZE);
        };
    }
}

/*******************************************************************************
 End of File
 */
