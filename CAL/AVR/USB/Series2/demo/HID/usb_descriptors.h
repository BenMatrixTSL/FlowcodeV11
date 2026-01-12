// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D53F5F6A18E6F66E466F9DB641FCB79B707EABDD0A6647EDB294D49642477A5A99555DE2D1306A6AA2C335C4C1A1F6B0E8DCC86B0F19C4140E34E49B8C3F4480FA9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF54C248FB6AB0CAC40CFA069ADF6536BE217548023EDBAE449BDC5C3976098CCE235159694D801725B98F332E6DDB4D43D4F9F976B51F4320582D836E47A98673AB8B2DB1F8947B3B30496620D8638D82879CE93A87C33DEAD549D34A0D5AD11F3589883DC5DCE7D45972C7459B44150C60FB8BF4F7369336D76D3E34736BD7539F516F4BDFF4A1CBE
// REVISION: 1.0
// GUID: DA8E63E5-F9D5-40D6-BEF8-687D622B93E2
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\demo\HID\usb_descriptors.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief USB Identifers.
//!
//!  This file contains the usb parameters that uniquely identify the
//!  USB application through descriptor tables.
//!
//! - Compiler:           IAR EWAVR and GNU GCC for AVR
//! - Supported devices:  USB Series 2
//!
//! \author               Atmel Corporation: http://www.atmel.com \n
//!                       Support and FAQ: http://support.atmel.no/
//!
//! ***************************************************************************

/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _USB_DESCRIPTORS_H_
#define _USB_DESCRIPTORS_H_

//_____ I N C L U D E S ____________________________________________________

#include "config.h"
#include "modules/usb/device_chap9/usb_standard_request.h"
#include "conf_usb.h"

//_____ M A C R O S ________________________________________________________

#define Usb_unicode(a)         ((U16)(a))
#define Usb_get_dev_desc_pointer()        (&(usb_dev_desc.bLength))
#define Usb_get_dev_desc_length()         (sizeof (usb_dev_desc))
#define Usb_get_conf_desc_pointer()       (&(usb_conf_desc.cfg_temp.bLength))
#define Usb_get_conf_desc_length()        (sizeof (usb_conf_desc))

//_____ U S B    D E F I N E _______________________________________________

                  // USB Device descriptor
#define USB_SPECIFICATION     0x0200
#define DEVICE_CLASS          0x00   //! 
#define DEVICE_SUB_CLASS      0      //! each configuration has its own sub-class
#define DEVICE_PROTOCOL       0      //! each configuration has its own protocol
#define EP_CONTROL_LENGTH     8
#define VENDOR_ID             MX_VENDOR_ID
#define PRODUCT_ID            MX_PRODUCT_ID
#define RELEASE_NUMBER        MX_RELEASE_VERSION
#define MAN_INDEX             0x01
#define PROD_INDEX            0x02   
#if (USB_DEVICE_SN_USE==ENABLE)
#define SN_INDEX              0x03
#else
#define SN_INDEX              0x00  // No serial number field
#endif
#define NB_CONFIGURATION      1

               // CONFIGURATION
#define NB_INTERFACE       1           // Number of interfaces
#define CONF_NB            1     //! Number of this configuration
#define CONF_INDEX         0
#define CONF_ATTRIBUTES    USB_CONFIG_BUSPOWERED
#define MAX_POWER          100    // 200 mA

             // USB Interface descriptor gen
#define INTERFACE_NB_TEMP        0            //! The number of this interface
#define ALTERNATE_TEMP           0            //! The alt settting nb of this interface
#define NB_ENDPOINT_TEMP         1            //! The number of endpoints this this interface have
#define INTERFACE_CLASS_TEMP     0x03         //! HID Class
#define INTERFACE_SUB_CLASS_TEMP MX_HID_SUBCLASS
#define INTERFACE_PROTOCOL_TEMP  MX_HID_PROTOCOL
#define INTERFACE_INDEX_TEMP     0

#define INTERFACE_NB_HID			INTERFACE_NB_TEMP	//NB_INTERFACE
#define ALTERNATE_HID				ALTERNATE_TEMP
#define NB_ENDPOINT_HID				NB_ENDPOINT_TEMP
#define INTERFACE_CLASS_HID			INTERFACE_CLASS_TEMP    // HID Class
#define INTERFACE_SUB_CLASS_HID		INTERFACE_SUB_CLASS_TEMP    // No Sub Class
#define INTERFACE_PROTOCOL_HID		INTERFACE_PROTOCOL_TEMP
#define INTERFACE_INDEX_HID			INTERFACE_INDEX_TEMP

            // USB Endpoint 1 descriptor FS
#define ENDPOINT_NB_TEMP1       (EP_HID_IN | 0x80)
#define EP_ATTRIBUTES_TEMP1     0x03              // BULK = 0x02, INTERUPT = 0x03
#define EP_IN_LENGTH_TEMP1      MX_HID_TX_SZ
#define EP_SIZE_TEMP1           EP_IN_LENGTH_TEMP1
#define EP_INTERVAL_TEMP1       MX_HID_TX_IVL     // Interrupt polling interval from host

#define ENDPOINT_NB_1			ENDPOINT_NB_TEMP1
#define EP_ATTRIBUTES_1     	EP_ATTRIBUTES_TEMP1    // BULK = 0x02, INTERUPT = 0x03
#define EP_IN_LENGTH_1			EP_IN_LENGTH_TEMP1
#define EP_SIZE_1           	EP_IN_LENGTH_TEMP1
#define EP_INTERVAL_1        	EP_INTERVAL_TEMP1     // Interrupt polling interval from host

            // USB Endpoint 2 descriptor FS
#define ENDPOINT_NB_TEMP2       (EP_HID_OUT)
#define EP_ATTRIBUTES_TEMP2     0x03              // BULK = 0x02, INTERUPT = 0x03
#define EP_IN_LENGTH_TEMP2      MX_HID_RX_SZ
#define EP_SIZE_TEMP2           EP_IN_LENGTH_TEMP2
#define EP_INTERVAL_TEMP2       MX_HID_RX_IVL     // Interrupt polling interval from host

#define ENDPOINT_NB_2			ENDPOINT_NB_TEMP2
#define EP_ATTRIBUTES_2     	EP_ATTRIBUTES_TEMP2    // BULK = 0x02, INTERUPT = 0x03
#define EP_IN_LENGTH_2			EP_IN_LENGTH_TEMP2
#define EP_SIZE_2           	EP_IN_LENGTH_TEMP2
#define EP_INTERVAL_2        	EP_INTERVAL_TEMP2     // Interrupt polling interval from host

/* HID specific */
#define HID                   0x21
#define REPORT                0x22
#define SET_REPORT			  0x02

#define HID_DESCRIPTOR        0x21
#define HID_BDC               0x1001
#define HID_COUNTRY_CODE      0x00
#define HID_CLASS_DESC_NB     0x01
#define HID_DESCRIPTOR_TYPE   0x22

#define DEVICE_STATUS         USB_DEVICE_STATUS_BUS_POWERED

#define LANG_ID               0x00

#define USB_MN_LENGTH         MX_MANUF_SZ
#define USB_MANUFACTURER_NAME MX_MANF_NAME
#define USB_PN_LENGTH         MX_PRDCT_SZ
#define USB_PRODUCT_NAME      MX_PRDCT_NAME


#define USB_SN_LENGTH         0x0D
              // Serial Number should be at least 12 characters long
#define USB_SERIAL_NUMBER \
{ Usb_unicode('0') \
 ,Usb_unicode('0') \
 ,Usb_unicode('0') \
 ,Usb_unicode('0') \
 ,Usb_unicode('0') \
 ,Usb_unicode('0') \
 ,Usb_unicode('0') \
 ,Usb_unicode('0') \
 ,Usb_unicode('0') \
 ,Usb_unicode('0') \
 ,Usb_unicode('0') \
 ,Usb_unicode('0') \
 ,Usb_unicode('0') \
}

#define LANGUAGE_ID           0x0409


                  //! Usb Request
typedef struct
{
   U8      bmRequestType;        //!< Characteristics of the request
   U8      bRequest;             //!< Specific request
   U16     wValue;               //!< field that varies according to request
   U16     wIndex;               //!< field that varies according to request
   U16     wLength;              //!< Number of bytes to transfer if Data
}  S_UsbRequest;

                //! Usb Device Descriptor
typedef struct {
   U8      bLength;              //!< Size of this descriptor in bytes
   U8      bDescriptorType;      //!< DEVICE descriptor type
   U16     bscUSB;               //!< Binay Coded Decimal Spec. release
   U8      bDeviceClass;         //!< Class code assigned by the USB
   U8      bDeviceSubClass;      //!< Sub-class code assigned by the USB
   U8      bDeviceProtocol;      //!< Protocol code assigned by the USB
   U8      bMaxPacketSize0;      //!< Max packet size for EP0
   U16     idVendor;             //!< Vendor ID. ATMEL = 0x03EB
   U16     idProduct;            //!< Product ID assigned by the manufacturer
   U16     bcdDevice;            //!< Device release number
   U8      iManufacturer;        //!< Index of manu. string descriptor
   U8      iProduct;             //!< Index of prod. string descriptor
   U8      iSerialNumber;        //!< Index of S.N.  string descriptor
   U8      bNumConfigurations;   //!< Number of possible configurations
}  S_usb_device_descriptor;


          //! Usb Configuration Descriptor
typedef struct {
   U8      bLength;              //!< size of this descriptor in bytes
   U8      bDescriptorType;      //!< CONFIGURATION descriptor type
   U16     wTotalLength;         //!< total length of data returned
   U8      bNumInterfaces;       //!< number of interfaces for this conf.
   U8      bConfigurationValue;  //!< value for SetConfiguration resquest
   U8      iConfiguration;       //!< index of string descriptor
   U8      bmAttibutes;          //!< Configuration characteristics
   U8      MaxPower;             //!< maximum power consumption
}  S_usb_configuration_descriptor;


              //! Usb Interface Descriptor
typedef struct {
   U8      bLength;               //!< size of this descriptor in bytes
   U8      bDescriptorType;       //!< INTERFACE descriptor type
   U8      bInterfaceNumber;      //!< Number of interface
   U8      bAlternateSetting;     //!< value to select alternate setting
   U8      bNumEndpoints;         //!< Number of EP except EP 0
   U8      bInterfaceClass;       //!< Class code assigned by the USB
   U8      bInterfaceSubClass;    //!< Sub-class code assigned by the USB
   U8      bInterfaceProtocol;    //!< Protocol code assigned by the USB
   U8      iInterface;            //!< Index of string descriptor
}  S_usb_interface_descriptor;


               //! Usb Endpoint Descriptor
typedef struct {
   U8      bLength;               //!< Size of this descriptor in bytes
   U8      bDescriptorType;       //!< ENDPOINT descriptor type
   U8      bEndpointAddress;      //!< Address of the endpoint
   U8      bmAttributes;          //!< Endpoint's attributes
   U16     wMaxPacketSize;        //!< Maximum packet size for this EP
   U8      bInterval;             //!< Interval for polling EP in ms
} S_usb_endpoint_descriptor;


               //! Usb Language Descriptor
typedef struct {
   U8      bLength;               //!< size of this descriptor in bytes
   U8      bDescriptorType;       //!< STRING descriptor type
   U16     wlangid;               //!< language id
}  S_usb_language_id;


//_____ U S B   M A N U F A C T U R E R   D E S C R I P T O R _______________


//struct usb_st_manufacturer
typedef struct {
   U8  bLength;               // size of this descriptor in bytes
   U8  bDescriptorType;       // STRING descriptor type
   U16 wstring[USB_MN_LENGTH];// unicode characters
} S_usb_manufacturer_string_descriptor;


//_____ U S B   P R O D U C T   D E S C R I P T O R _________________________


//struct usb_st_product
typedef struct {
   U8  bLength;               // size of this descriptor in bytes
   U8  bDescriptorType;       // STRING descriptor type
   U16 wstring[USB_PN_LENGTH];// unicode characters
} S_usb_product_string_descriptor;


//_____ U S B   S E R I A L   N U M B E R   D E S C R I P T O R _____________


#if (USB_DEVICE_SN_USE==ENABLE)
//struct usb_st_serial_number
typedef struct {
   U8  bLength;               // size of this descriptor in bytes
   U8  bDescriptorType;       // STRING descriptor type
#if (USE_DEVICE_SN_UNIQUE==ENABLE)

#else   
   U16 wstring[USB_SN_LENGTH];// unicode characters
#endif
} S_usb_serial_number;
#endif


/*_____ U S B   H I D   D E S C R I P T O R __________________________________*/

typedef struct {
  U8  bLength;               /* Size of this descriptor in bytes */
  U8  bDescriptorType;       /* HID descriptor type */
  U16 bscHID;                /* Binay Coded Decimal Spec. release */
  U8  bCountryCode;          /* Hardware target country */
  U8  bNumDescriptors;       /* Number of HID class descriptors to follow */
  U8  bRDescriptorType;      /* Report descriptor type */
  U16 wDescriptorLength;     /* Total length of Report descriptor */
} S_usb_hid_descriptor;


typedef struct
{
   S_usb_configuration_descriptor cfg_temp;
   S_usb_interface_descriptor     hid_iface;
   S_usb_hid_descriptor           hid_class;
   S_usb_endpoint_descriptor      hid_ep1;
#if MX_HID_RX_SZ > 0
   S_usb_endpoint_descriptor      hid_ep2;
#endif
} S_usb_user_configuration_descriptor;

/*_____ USB HID REPORT DESCRIPTOR __________________________________*/
typedef struct {
   U8      report[MX_HID_REPORT_DESCRIPT_SZ];
}  S_usb_hid_report_descriptor;

#endif
