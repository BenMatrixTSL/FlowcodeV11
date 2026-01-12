// CRC: A6459004C43C0517DC6DFC5681C2AD69C10B8AB997F36C59C8E2D33ADDA05BC16FA1F76CE5BD9A54F0CE206B244EEA38F8F0B679987821A67B09CF8806E65CDC9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF584A34E90C0C4257B93FA98BC9188F20DEC1EDB7C2701428B37A290AF9F405E1B0194D2A3B270153DBF757CDB0809E0836FCA3C83683FA6E48186BA168B850F89CA397E4B804AFB7E1146A10DD2B23CCDD1819B2F266A640C549D34A0D5AD11F3B2827B26550A3A3C4454AA516C6B4B0846A9C86F82310154B828D9FAEE7A88865484BB54CD7ADC26
// REVISION: 1.0
// GUID: B4E4B776-7554-46DB-BAF5-3D68C60EE645
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\USB\CDC\CDC_Desc.h

#ifndef _CDCDESC_H
#define _CDCDESC_H

// SELECT USB FS or HS
//extern const DRV_USBFS_INIT drvUSBInit;
//extern const DRV_USBHS_INIT drvUSBInit;

extern const USB_DEVICE_DESCRIPTOR deviceDescriptor;
extern const uint8_t fullSpeedConfigurationDescriptor[];
extern USB_DEVICE_CONFIGURATION_DESCRIPTORS_TABLE fullSpeedConfigDescSet;
extern const USB_DEVICE_INIT usbDevInitData;

typedef enum
{
	/* Application's state machine's initial state. */
	APP_STATE_INIT=0,
	APP_STATE_SERVICE_TASKS,

	/* TODO: Define states used by the application state machine. */

} APP_STATES;


typedef struct
{
    /* The application's current state */
    APP_STATES state;

    /* TODO: Define any additional data used by the application. */

    /* Device layer handle returned by device layer open function */
    USB_DEVICE_HANDLE deviceHandle;

    /* Set Line Coding Data */
    USB_CDC_LINE_CODING setLineCodingData;

    /* Device configured state */
    bool isConfigured;

    /* Get Line Coding Data */
    USB_CDC_LINE_CODING getLineCodingData;

    /* Control Line State */
    USB_CDC_CONTROL_LINE_STATE controlLineStateData;

    /* Read transfer handle */
    USB_DEVICE_CDC_TRANSFER_HANDLE readTransferHandle;

    /* Length of data read */
    uint32_t readLen;
    
    /* Length of read data processed */
    uint32_t readProcessedLen;

    /* Write transfer handle */
    USB_DEVICE_CDC_TRANSFER_HANDLE writeTransferHandle;
    
    /* Length of data to be written */
    uint32_t writeLen;

} APP_DATA;

#endif
