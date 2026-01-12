// CRC: A6459004C43C0517DC6DFC5681C2AD69C10B8AB997F36C59C8E2D33ADDA05BC17E849C698F74EB624B366BF50A9985A2F6F63A6FB8B1500D420EB282E16823AB9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5176A27A75861CECE3CB872D05D2A02AF31E9FD00CB0357E681CD73D16F8D34BB2E822DB4F9FC27FB7969C1A9C4187520A30AED881AADABAD4912738B63D5742BF2B33F46ABF8DB9DC5A6EEF6CD4479A00E1031E311592434549D34A0D5AD11F3134BE53D72F7BA62F7A60AEC820B5ECAF61C8429A96DCBD053C738B67729C4F08AC626FF3259D902
// REVISION: 1.0
// GUID: B8F5306D-B1A7-43ED-A9AD-367FD85883AB
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\USB\HID\HIDComp.c
#include "system_config.h"
#include "system_definitions.h"
#include "HID_Desc.h"
#include "mx_usb_hid_conf.h"

#define APP_USB_CONVERT_TO_MILLISECOND	4

extern APP_DATA appData;
extern uint8_t HID_USB_Rx_String[];

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    appData.handleUsbDevice       = USB_DEVICE_HANDLE_INVALID;
    appData.hidInstance 		  = 0;
    appData.usbDeviceIsConfigured = false;
	
    appData.isReportSentComplete  = true;
	appData.isReportReceived      = false;
	
    appData.idleRate              = 0;
    appData.setIdleTimer          = 0;

    appData.hidInstance = 0;
}


static void APP_USBDeviceHIDEventHandler(USB_DEVICE_HID_INDEX hidInstance,
                                         USB_DEVICE_HID_EVENT event, 
                                         void *               eventData, 
                                         uintptr_t            userData)
{
    APP_DATA * appData = (APP_DATA *)userData;

    switch(event)
    {
        case USB_DEVICE_HID_EVENT_REPORT_SENT:
            appData->isReportSentComplete = true;
            break;

        case USB_DEVICE_HID_EVENT_REPORT_RECEIVED:
		    #if (MX_HID_RX_SZ > 0)
            USB_DEVICE_HID_ReportReceive(appData->hidInstance,
                                         &appData->receiveTransferHandle,
                                         HID_USB_Rx_String,
										 64);			
            appData->isReportReceived = true;
			#endif
            break;

        case USB_DEVICE_HID_EVENT_SET_IDLE:
			USB_DEVICE_ControlStatus(appData->handleUsbDevice, USB_DEVICE_CONTROL_STATUS_OK);
            appData->idleRate = ((USB_DEVICE_HID_EVENT_DATA_SET_IDLE*)eventData)->duration;
            break;

        case USB_DEVICE_HID_EVENT_GET_IDLE:
            USB_DEVICE_ControlSend(appData->handleUsbDevice, &(appData->idleRate),1);
            break;

        case USB_DEVICE_HID_EVENT_SET_PROTOCOL:
            appData->activeProtocol = *(USB_HID_PROTOCOL_CODE *)eventData;
            USB_DEVICE_ControlStatus(appData->handleUsbDevice, USB_DEVICE_CONTROL_STATUS_OK);
            break;

        case  USB_DEVICE_HID_EVENT_GET_PROTOCOL:
             USB_DEVICE_ControlSend(appData->handleUsbDevice, &(appData->activeProtocol), 1);
             break;

        case USB_DEVICE_HID_EVENT_CONTROL_TRANSFER_DATA_SENT:
            break;

        default:
            break;
    }
}

/***********************************************
 * Application USB Device Layer Event Handler.
 ***********************************************/
void APP_USBDeviceEventHandler ( USB_DEVICE_EVENT event, void * eventData, uintptr_t context )
{
    USB_DEVICE_EVENT_DATA_CONFIGURED * configurationValue;
    
    switch(event)
    {
        case USB_DEVICE_EVENT_SOF:
			appData.sofEventHasOccurred = true;                      
            break;
            
        case USB_DEVICE_EVENT_RESET:
        case USB_DEVICE_EVENT_DECONFIGURED:

            appData.usbDeviceIsConfigured = false;
			appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
            break;

        case USB_DEVICE_EVENT_CONFIGURED:

            /* Device is configured */			
            configurationValue = (USB_DEVICE_EVENT_DATA_CONFIGURED *)eventData;
            if(configurationValue->configurationValue == 1)
            {
                /* Register the Application HID Event Handler. */
                USB_DEVICE_HID_EventHandlerSet(appData.hidInstance,
											   APP_USBDeviceHIDEventHandler,
											   (uintptr_t)&appData);
                
                appData.usbDeviceIsConfigured = true;                
                appData.isReportSentComplete = true;
            }
            break;

        case USB_DEVICE_EVENT_POWER_DETECTED:

            /* VBUS was detected. We can attach the device */
            USB_DEVICE_Attach(appData.handleUsbDevice);
            
            break;

        case USB_DEVICE_EVENT_POWER_REMOVED:

            /* VBUS is not available any more. Detach the device. */
            USB_DEVICE_Detach(appData.handleUsbDevice);
            
            break;

        case USB_DEVICE_EVENT_SUSPENDED:
            break;

        case USB_DEVICE_EVENT_CONTROL_TRANSFER_DATA_RECEIVED:
        case USB_DEVICE_EVENT_CONTROL_TRANSFER_ABORTED:
        case USB_DEVICE_EVENT_CONTROL_TRANSFER_SETUP_REQUEST:
        case USB_DEVICE_EVENT_CONTROL_TRANSFER_DATA_SENT:
        case USB_DEVICE_EVENT_ENDPOINT_READ_COMPLETE:
        case USB_DEVICE_EVENT_ENDPOINT_WRITE_COMPLETE:
        case USB_DEVICE_EVENT_SET_DESCRIPTOR:
        case USB_DEVICE_EVENT_SYNCH_FRAME:
        case USB_DEVICE_EVENT_RESUMED:
        case USB_DEVICE_EVENT_ERROR:
        default:
            break;

    }
}

/*******************************************************************************
 End of File
 */
