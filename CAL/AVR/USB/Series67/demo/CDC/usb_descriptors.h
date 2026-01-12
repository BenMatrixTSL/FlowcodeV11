// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5E971021840B65CB4A3D8D01D6B7FD05CEEE65B670558DA072C98DB381E8CD9FC9DBD8A54F9020375FD269077E468819C887B572FFDC41D4035FB865286B0C37D9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5098D1E60AC6791D35F7D2524F73565CDF1BB24018759CC25D3E84CBDD63C6BB9239AFB53A6A8CEA4EBBF0278FE3106B692D2C4335641D50B5DD4C94B98C32200082E348AFB820CF61C5BD10A4EE9D269AD01D95B5C2AC90D549D34A0D5AD11F38FB7FC4DAE9CFDB28BFE4A7F4A7D543AC5D0EE48D127920876D3E34736BD7539F516F4BDFF4A1CBE
// REVISION: 1.0
// GUID: EC676682-74FC-4F71-9A46-0BBACF66BAC5
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series67\demo\CDC\usb_descriptors.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief USB Identifers.
//!
//!  This file contains the usb parameters that uniquely identify the
//!  USB application through descriptor tables.
//!
//! - Compiler:           IAR EWAVR and GNU GCC for AVR
//! - Supported devices:  AT90USB162, AT90USB82
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
#define DEVICE_CLASS          0x02   //! CDC class
#define DEVICE_SUB_CLASS      0      //! each configuration has its own sub-class
#define DEVICE_PROTOCOL       0      //! each configuration has its own protocol
#define EP_CONTROL_LENGTH     32
#define VENDOR_ID             MX_VENDOR_ID
#define PRODUCT_ID            MX_PRODUCT_ID
#define RELEASE_NUMBER        MX_RELEASE_VERSION
#define MAN_INDEX             0x00
#define PROD_INDEX            0x00   
#if (USB_DEVICE_SN_USE==ENABLE)
#define SN_INDEX              0x03
#else
#define SN_INDEX              0x00  // No serial number field
#endif
#define NB_CONFIGURATION      1

               // CONFIGURATION
#define NB_INTERFACE       2           // Number of interfaces
#define CONF_NB            1     //! Number of this configuration
#define CONF_INDEX         0
#define CONF_ATTRIBUTES    USB_CONFIG_BUSPOWERED
#define MAX_POWER          100    // 200 mA

             // USB Interface descriptor gen
#define INTERFACE_NB_TEMP        0            //! The number of this interface
#define ALTERNATE_TEMP           0            //! The alt settting nb of this interface
#define NB_ENDPOINT_TEMP         1            //! The number of endpoints this this interface have
#define INTERFACE_CLASS_TEMP     0x02         //! CDC ACM Com
#define INTERFACE_SUB_CLASS_TEMP 0x02
#define INTERFACE_PROTOCOL_TEMP  0x01
#define INTERFACE_INDEX_TEMP     0

            // USB Endpoint 1 descriptor FS
#define ENDPOINT_NB_TEMP1       (0x80 | TX_EP)
#define EP_ATTRIBUTES_TEMP1     0x02              // BULK = 0x02, INTERUPT = 0x03
#define EP_IN_LENGTH_TEMP1      MX_TX_EP_SIZE
#define EP_SIZE_TEMP1           EP_IN_LENGTH_TEMP1
#define EP_INTERVAL_TEMP1       0x00              // Interrupt polling interval from host

            // USB Endpoint 2 descriptor FS
#define ENDPOINT_NB_TEMP2       RX_EP
#define EP_ATTRIBUTES_TEMP2     0x02              // BULK = 0x02, INTERUPT = 0x03
#define EP_IN_LENGTH_TEMP2      MX_RX_EP_SIZE
#define EP_SIZE_TEMP2           EP_IN_LENGTH_TEMP2
#define EP_INTERVAL_TEMP2       0x00              // Interrupt polling interval from host

            // USB Endpoint 3 descriptor FS
#define ENDPOINT_NB_TEMP3       (0x80 | INT_EP)
#define EP_ATTRIBUTES_TEMP3     0x03              // BULK = 0x02, INTERUPT = 0x03
#define EP_IN_LENGTH_TEMP3      0x20
#define EP_SIZE_TEMP3           EP_IN_LENGTH_TEMP3
#define EP_INTERVAL_TEMP3       0xFF              // Interrupt polling interval from host

             // USB Second Interface descriptor gen
#define INTERFACE_NB_SECOND_TEMP        1        //! The number of this interface
#define ALTERNATE_SECOND_TEMP           0        //! The alt settting nb of this interface
#define NB_ENDPOINT_SECOND_TEMP         2        //! The number of endpoints this this interface have
#define INTERFACE_CLASS_SECOND_TEMP     0x0A     //! CDC ACM Data
#define INTERFACE_SUB_CLASS_SECOND_TEMP 0x00     //! Sub Class
#define INTERFACE_PROTOCOL_SECOND_TEMP  0x00     //! Protocol
#define INTERFACE_INDEX_SECOND_TEMP     0

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




// Configuration descriptor template
// The device has two interfaces
// - First interface has 1 interrupt IN endpoint
// - Second interface has 2 bulk endpoints

typedef struct
{
   S_usb_configuration_descriptor cfg_temp;
   S_usb_interface_descriptor     ifc_temp;
	U8 CS_INTERFACE[19];
   S_usb_endpoint_descriptor      ep3_temp;
   S_usb_interface_descriptor     ifc_second_temp;
   S_usb_endpoint_descriptor      ep1_temp;
   S_usb_endpoint_descriptor      ep2_temp;
} S_usb_user_configuration_descriptor;




#endif

