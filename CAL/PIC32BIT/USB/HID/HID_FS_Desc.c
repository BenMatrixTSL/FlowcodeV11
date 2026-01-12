// CRC: A6459004C43C0517DC6DFC5681C2AD69C10B8AB997F36C59C8E2D33ADDA05BC17E849C698F74EB624B366BF50A9985A28DA0FC61415F7CFFF05FF45AA9628CFDDD04A5F8AD9BEEB1823278EF8F2BA19C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5A15B41188F6D096D2B480FDF7F871C3E063550BE0FADC3CDC302C2632472A815A9874E372498A0E22DD16F2098ED909E3E1F81A312C1C3B87F28C4D74D50CD1824DE5B41CA02C5F32AB905B2A319141B9A64103F8EFA76F8549D34A0D5AD11F3975FB28C97A8F60AEBBB0DE3A3E42F4FF4569D67EBD396310C9FBA1F01A7E45B08B65E7F68830DD9
// REVISION: 1.0
// GUID: 5360882C-5AD3-48CA-8A50-EF226969907F
// DATE: 08\08\2022
// DIR: CAL\PIC32BIT\USB\HID\HID_FS_Desc.c
#include "system_config.h"
#include "system_definitions.h"
#include "mx_usb_hid_conf.h"

//#include "HID_Setup.h"

// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="DRV_USB Initialization Data">
/******************************************************
 * USB Driver Initialization
 ******************************************************/
/****************************************************
 * Endpoint Table needed by the Device Layer.
 ****************************************************/

uint8_t __attribute__((aligned(512))) endPointTable[DRV_USBFS_ENDPOINTS_NUMBER * 32];
const DRV_USBFS_INIT drvUSBInit =
{
    /* Assign the endpoint table */
    .endpointTable= endPointTable,

    /* Interrupt Source for USB module */
    .interruptSource = INT_SOURCE_USB_1,
    
    /* System module initialization */
    .moduleInit = {SYS_MODULE_POWER_RUN_FULL},
    
    .operationMode = DRV_USBFS_OPMODE_DEVICE,
    
    .operationSpeed = USB_SPEED_FULL,
    
    /* Stop in idle */
    .stopInIdle = false,

    /* Suspend in sleep */
    .suspendInSleep = false,

    /* Identifies peripheral (PLIB-level) ID */
    .usbID = USB_ID_1
};


// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************

const uint8_t hid_rpt0[] = MX_HID_REPORT_DESCRIPT;

//{
//	0x05, 0x01, /* Usage Page (Generic Desktop)        */
//    0x09, 0x02, /* Usage (Mouse)                       */
//    0xA1, 0x01, /* Collection (Application)            */
//    0x09, 0x01, /* Usage (Pointer)                     */
//    0xA1, 0x00, /* Collection (Physical)               */
//    0x05, 0x09, /* Usage Page (Buttons)                */
//    0x19, 0x01, /* Usage Minimum (01)                  */
//    0x29, 0x03, /* Usage Maximum (03)                  */
//    0x15, 0x00, /* Logical Minimum (0)                 */
//    0x25, 0x01, /* Logical Maximum (1)                 */
//    0x95, 0x03, /* Report Count (3)                    */
//    0x75, 0x01, /* Report Size (1)                     */
//    0x81, 0x02, /* Input (Data, Variable, Absolute)    */
//    0x95, 0x01, /* Report Count (1)                    */
//    0x75, 0x05, /* Report Size (5)                     */
//    0x81, 0x01, /* Input (Constant)    ;5 bit padding  */
//    0x05, 0x01, /* Usage Page (Generic Desktop)        */
//    0x09, 0x30, /* Usage (X)                           */
//    0x09, 0x31, /* Usage (Y)                           */
//    0x15, 0x81, /* Logical Minimum (-127)              */
//    0x25, 0x7F, /* Logical Maximum (127)               */
//    0x75, 0x08, /* Report Size (8)                     */
//    0x95, 0x02, /* Report Count (2)                    */
//    0x81, 0x06, /* Input (Data, Variable, Relative)    */
//    0xC0, 0xC0
//};


/**************************************************
 * USB Device Function Driver Init Data
 **************************************************/
const USB_DEVICE_HID_INIT hidInit0 =
{
    .hidReportDescriptorSize = sizeof(hid_rpt0),
    .hidReportDescriptor = &hid_rpt0,
    .queueSizeReportReceive = 1,
    .queueSizeReportSend = 1
};
/**************************************************
 * USB Device Layer Function Driver Registration 
 * Table
 **************************************************/
const USB_DEVICE_FUNCTION_REGISTRATION_TABLE funcRegistrationTable[1] =
{
    /* Function 1 */
    { 
        .configurationValue = 1,    /* Configuration value */ 
        .interfaceNumber = 0,       /* First interfaceNumber of this function */ 
        .speed = USB_SPEED_FULL,    /* Function Speed */ 
        .numberOfInterfaces = 1,    /* Number of interfaces */
        .funcDriverIndex = 0,  /* Index of HID Function Driver */
        .driver = (void*)USB_DEVICE_HID_FUNCTION_DRIVER,    /* USB HID function data exposed to device layer */
        .funcDriverInit = (void*)&hidInit0,    /* Function driver init data*/
    },
};

/*******************************************
 * USB Device Layer Descriptors
 *******************************************/
/*******************************************
 *  USB Device Descriptor 
 *******************************************/
const USB_DEVICE_DESCRIPTOR deviceDescriptor =
{
    0x12,                           // Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,          // DEVICE descriptor type
    0x0200,                         // USB Spec Release Number in BCD format
    0x00,                           // Class Code
    MX_HID_SUBCLASS,                // Subclass code
    MX_HID_PROTOCOL,                // Protocol code
    USB_DEVICE_EP0_BUFFER_SIZE,     // Max packet size for EP0, see system_config.h
    MX_VENDOR_ID,                   // Vendor ID
    MX_PRODUCT_ID,                  // Product ID
    0x0100,                         // Device release number in BCD format
    0x01,                           // Manufacturer string index
    0x02,                           // Product string index
    0x00,                           // Device serial number string index
    0x01                            // Number of possible configurations
};


/*******************************************
 *  USB Full Speed Configuration Descriptor
 *******************************************/
const uint8_t fullSpeedConfigurationDescriptor[]=
{
    /* Configuration Descriptor */

    0x09,                                               // Size of this descriptor in bytes
    USB_DESCRIPTOR_CONFIGURATION,                       // Descriptor Type
    41,0,                //(41 Bytes)Size of the Config descriptor.e
    1,                                               // Number of interfaces in this cfg
    0x01,                                               // Index value of this configuration
    0x00,                                               // Configuration string index
    USB_ATTRIBUTE_DEFAULT | USB_ATTRIBUTE_SELF_POWERED, // Attributes
    50,                                                 // Max power consumption (2X mA)
    /* Descriptor for Function 1 - HID     */ 
    
	/* Interface Descriptor */

    0x09,                               // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,           // INTERFACE descriptor type
    0,                                  // Interface Number
    0,                                  // Alternate Setting Number
    2,                                  // Number of endpoints in this interface
    USB_HID_CLASS_CODE,                 // Class code
    USB_HID_SUBCLASS_CODE_NO_SUBCLASS , // Subclass code
    USB_HID_PROTOCOL_CODE_NONE,         // No Protocol
    0,                                  // Interface string index

    /* HID Class-Specific Descriptor */

    0x09,                           // Size of this descriptor in bytes
    USB_HID_DESCRIPTOR_TYPES_HID,   // HID descriptor type
    0x11,0x01,                      // HID Spec Release Number in BCD format (1.11)
    0x00,                           // Country Code (0x00 for Not supported)
    1,                              // Number of class descriptors, see usbcfg.h
    USB_HID_DESCRIPTOR_TYPES_REPORT,// Report descriptor type
    USB_DEVICE_16bitTo8bitArrange(sizeof(hid_rpt0)),   // Size of the report descriptor

    /* Endpoint Descriptor */

    0x07,                           // Size of this descriptor in bytes
    USB_DESCRIPTOR_ENDPOINT,        // Endpoint Descriptor
    1 | USB_EP_DIRECTION_IN,      // EndpointAddress
    USB_TRANSFER_TYPE_INTERRUPT,    // Attributes
    0x40,0x00,                      // Size
    MX_HID_TX_IVL,                  // Interval

    /* Endpoint Descriptor */

    0x07,                           // Size of this descriptor in bytes
    USB_DESCRIPTOR_ENDPOINT,        // Endpoint Descriptor
    1 | USB_EP_DIRECTION_OUT,     // EndpointAddress
    USB_TRANSFER_TYPE_INTERRUPT,    // Attributes
    0x40,0x00,                      // size
    MX_HID_RX_IVL,                  // Interval

	
	
	
};

/*******************************************
 * Array of Full speed config descriptors
 *******************************************/
USB_DEVICE_CONFIGURATION_DESCRIPTORS_TABLE fullSpeedConfigDescSet[1] =
{
    fullSpeedConfigurationDescriptor
};

/**************************************
 *  String descriptors.
 *************************************/

 /*******************************************
 *  Language code string descriptor
 *******************************************/
    const struct
    {
        uint8_t bLength;
        uint8_t bDscType;
        uint16_t string[1];
    }
    sd000 =
    {
        sizeof(sd000),          // Size of this descriptor in bytes
        USB_DESCRIPTOR_STRING,  // STRING descriptor type
        {0x0409}                // Language ID
    };
/*******************************************
 *  Manufacturer string descriptor
 *******************************************/
    const struct
    {
        uint8_t bLength;        // Size of this descriptor in bytes
        uint8_t bDscType;       // STRING descriptor type
        uint16_t string[MX_MANUF_SZ];    // String
    }
    sd001 =
    {
        sizeof(sd001),
        USB_DESCRIPTOR_STRING,
        MX_MANF_NAME_P32
		
    };

/*******************************************
 *  Product string descriptor
 *******************************************/
    const struct
    {
        uint8_t bLength;        // Size of this descriptor in bytes
        uint8_t bDscType;       // STRING descriptor type
		uint16_t string[MX_PRDCT_SZ];    // String
    }
    sd002 =
    {
        sizeof(sd002),
        USB_DESCRIPTOR_STRING,
		MX_PRDCT_NAME_P32
    };

/***************************************
 * Array of string descriptors
 ***************************************/
USB_DEVICE_STRING_DESCRIPTORS_TABLE stringDescriptors[3]=
{
    (const uint8_t *const)&sd000,
    (const uint8_t *const)&sd001,
    (const uint8_t *const)&sd002
};

/*******************************************
 * USB Device Layer Master Descriptor Table 
 *******************************************/
const USB_DEVICE_MASTER_DESCRIPTOR usbMasterDescriptor =
{
    &deviceDescriptor,          /* Full speed descriptor */
    1,                          /* Total number of full speed configurations available */
    fullSpeedConfigDescSet,     /* Pointer to array of full speed configurations descriptors*/
    NULL, 
    0, 
    NULL, 
    3,                          // Total number of string descriptors available.
    stringDescriptors,          // Pointer to array of string descriptors.
    NULL, 
    NULL
};


/****************************************************
 * USB Device Layer Initialization Data
 ****************************************************/
const USB_DEVICE_INIT usbDevInitData =
{
    /* System module initialization */
    .moduleInit = {SYS_MODULE_POWER_RUN_FULL},
    
    /* Number of function drivers registered to this instance of the
       USB device layer */
    .registeredFuncCount = 1,
    
    /* Function driver table registered to this instance of the USB device layer*/
    .registeredFunctions = (USB_DEVICE_FUNCTION_REGISTRATION_TABLE*)funcRegistrationTable,

    /* Pointer to USB Descriptor structure */
    .usbMasterDescriptor = (USB_DEVICE_MASTER_DESCRIPTOR*)&usbMasterDescriptor,

    /* USB Device Speed */
    .deviceSpeed = USB_SPEED_FULL,
    
    /* Index of the USB Driver to be used by this Device Layer Instance */
    .driverIndex = DRV_USBFS_INDEX_0,

    /* Pointer to the USB Driver Functions. */
    .usbDriverInterface = DRV_USBFS_DEVICE_INTERFACE,
    
};

