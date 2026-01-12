// CRC: 5D982BB222882C54AB4AFF20A1590FC484D3178BD0D2510D0F5A64A7853221CAE2C33FABBE4F69A6659399D51781B7B93AD2C1E57C9DD3A2E0F77167644C7039309998607486AEECF3B5FC38F9C0B531901481B78BE484580E0E1E6CE4FCFEC9ABB24D739BCDFCC30C3CAEE8E7DA6987298C49E946B5F14E8AB20088DAE20B555A05D94839A1369C42F72577D52CFA5339FDFA34FD371BABD801F45C210B77C9C19DB1C85C8268D950DB9545A87C8D6DC2EA63ACB7F998EF87498CEF1109655E0515AF603EB0F074549D34A0D5AD11F3F2DDCC8184FE8C82A7254F42ACB147109B097C2A767C202AB68A65FD090A6D6B4C68FB27E1809948
// REVISION: 3.0
// GUID: 57F0AA2B-079B-4A42-B230-9D59E64360EB
// DATE: 01\08\2025
// DIR: CAL\PIC16BIT\PIC16BIT_CAL_USB_Serial.c

/*********************************************************************
 *              Flowcode CAL USB Serial CDC Comms
 *
 * File: PIC16BIT_CAL_USB_Serial.c
 *
 * (c) 2025 Matrix TSL
 * http://www.matrixTSL.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
 * ?Company?) for its Flowcode graphical programming language is
 * intended and supplied to you, the Company?s customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
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
 * 100725 | BR | Created
 *
 */



#define MX_USB_SERIAL_ENUM_TOUTEN_X     	CAL_APPEND(MX_USB_SERIAL_ENUM_TOUTEN_, MX_USB_SERIAL_NUM)
#define MX_USB_SERIAL_ENUM_TOUT_X     		CAL_APPEND(MX_USB_SERIAL_ENUM_TOUT_, MX_USB_SERIAL_NUM)
#define MX_USB_SERIAL_ENUM_RETURN_X     	CAL_APPEND(MX_USB_SERIAL_ENUM_RETURN_, MX_USB_SERIAL_NUM)




#ifndef MX_USB_TYPE1
	#error "Your target device does not support USB components"
#endif

// Global Defines
#define USB_BUS_SENSE       1
#define self_power          1
#define tris_usb_bus_sense	1
#define tris_self_power		1

#define USB_CONFIG	"usb_serial_config.h"

// USB library includes
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_serial_config.h"
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb.h"
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_function_cdc.h"
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/GenericTypeDefs.h"
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/Compiler.h"
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_device.h"
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_device.c"
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_ch9.h"
 #if defined(__dsPIC33E__)
   #include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_hal_dspic33e.c"
 #elif defined(__PIC24E__)
   #include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_hal_pic24e.c"
 #else
   #include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_hal_pic24.c"
 #endif
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_function_cdc.c"
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_common.h"
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_hal.h"


 #if defined(__dsPIC33E__)
   #include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_hal_dspic33e.h"
 #elif defined(__PIC24E__)
   #include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_hal_pic24e.h"
 #else
   #include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_hal_pic24.h"
 #endif


// Device name and manufacturer
ROM struct{BYTE bLength;BYTE bDscType;WORD string[dev_name_count_DS];}sd001={sizeof(sd001),USB_DESCRIPTOR_STRING,{dev_name_DS}};
ROM struct{BYTE bLength;BYTE bDscType;WORD string[dev_manufacturer_count_DS];}sd002={sizeof(sd002),USB_DESCRIPTOR_STRING,{dev_manufacturer_DS}};


#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_serial_descriptors.c"
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC16BIT/USB/usb_cdc_handler.c"


MX_UINT16 MX_USBSer_RxByteCount = 0;
MX_UINT16 MX_USBSer_RxPtr = 0;
MX_UINT8 MX_USBSer_RxBuffer[RX_BUF_SZ];



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_Initialise_, ())
{

	MX_UINT16 FCL_DELAY_COUNTER = 0;
	MX_UINT8  FCL_INNER = 0;

	//On the PIC24FJ64GB004 Family of USB microcontrollers, the PLL will not power up and be enabled
	//by default, even if a PLL enabled oscillator configuration is selected (such as HS+PLL).
	//This allows the device to power up at a lower initial operating frequency, which can be
	//advantageous when powered from a source which is not gauranteed to be adequate for 48MHz
	//operation.  On these devices, user firmware needs to manually set the CLKDIV&lt;PLLEN&gt; bit to
	//power up the PLL.

	#if defined(P24FJ64GB004) || defined(P24FJ64GB002) || defined(P24FJ32GB004) || defined(P24FJ32GB002)

	  MX_UINT16 pll_startup_counter = 600;
	  CLKDIVbits.PLLEN = 1;
	  while(pll_startup_counter--);

	#endif

    USBDeviceInit();
	if(USB_BUS_SENSE && (USBGetDeviceState() == DETACHED_STATE))
        USBDeviceAttach();


	if (MX_USB_SERIAL_ENUM_TOUTEN_X)
	{
		//Wait for USB to startup and enumerate
		while((USBDeviceState != CONFIGURED_STATE) && (FCL_DELAY_COUNTER < MX_USB_SERIAL_ENUM_TOUT_X))
		{
			FCI_DELAYBYTE_MS(10);
			FCL_INNER = FCL_INNER + 1;

			if (FCL_INNER == 100)
			{
				FCL_DELAY_COUNTER = FCL_DELAY_COUNTER + 1;
				FCL_INNER = 0;
			}
		}

		if (USBDeviceState == CONFIGURED_STATE)
			return 0;

		return 255;
	}
	else
	{
		while(USBDeviceState != CONFIGURED_STATE);

		return 0;
	}

}


CALFUNCTION(MX_UINT16, FC_CAL_USB_Serial_ReadByte_, (MX_UINT8 timeout_ms))
{
	MX_UINT16 retval = 255;
	MX_UINT8 inner = 0;
	MX_UINT8 FCL_WAIT_FOREVER = 0;
	MX_UINT16 numBytesRead = 0;

	if (MX_USB_SERIAL_ENUM_RETURN_X)
		retval = 512;

	if (timeout_ms == 0)
	{
		timeout_ms = 1;
		inner = 98;
	}

	if(MX_USBSer_RxByteCount)
	{
		retval = MX_USBSer_RxBuffer[MX_USBSer_RxPtr++];

		if(MX_USBSer_RxPtr >= MX_USBSer_RxByteCount)
		{
			MX_USBSer_RxPtr = 0;
			MX_USBSer_RxByteCount = 0;
		}
	}
	else
	{
		if(timeout_ms == 255)
			FCL_WAIT_FOREVER = 1;

		while(numBytesRead == 0 && timeout_ms > 0)
		{
			numBytesRead = getsUSBUSART(MX_USBSer_RxBuffer, 64);

			if ((FCL_WAIT_FOREVER == 0) && (numBytesRead == 0))
			{
				inner++;

				#if defined(MX_CAL_PIC16)		//16-bit PIC specific
					delay_us(10);
				#else
					delay_us(3);
				#endif

				if (inner == 100)
				{
					inner = 0;
					timeout_ms--;
				}

			}
			else
			{
				retval = MX_USBSer_RxBuffer[0];

				if(numBytesRead > 1)
				{
					MX_USBSer_RxByteCount = numBytesRead;
					MX_USBSer_RxPtr = 1;
					if(numBytesRead < RX_BUF_SZ)
						MX_USBSer_RxBuffer[numBytesRead] = 0;
				}
			}
		}
	}

	return retval;
}



CALFUNCTION(void, FC_CAL_USB_Serial_ReadString_, (MX_CHAR *FCR_RETVAL, MX_UINT16 FCRsz_RETVAL, MX_UINT8 timeout_ms, MX_UINT8 FCL_LENGTH))
{
    MX_USBSer_RxByteCount = 0;
	MX_UINT8 inner = 0;
	MX_UINT16 numBytesRead = 0;
	MX_UINT8 FCL_WAIT_FOREVER = 0;

	if (timeout_ms == 0)
		timeout_ms = 1;

	if(timeout_ms == 255)
		FCL_WAIT_FOREVER = 1;

	while(numBytesRead == 0 && timeout_ms > 0)
	{
		numBytesRead = getsUSBUSART(FCR_RETVAL, FCL_LENGTH);

		if ((FCL_WAIT_FOREVER == 0) && (numBytesRead == 0))
		{
			inner++;
			delay_us(10);

			if (inner == 100)
			{
				inner = 0;
				timeout_ms--;
			}
		}

        if(numBytesRead < FCL_LENGTH)
            FCR_RETVAL[numBytesRead] = 0;
	}
}



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendByte_, (MX_UINT8 FCL_DATA))
{
	MX_UINT16 FCL_TIMEOUT = (0x0);

  	if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1))
  	{
  		return(2);		//USB Not Configured
  	}
  	else
  	{
		while ((USBUSARTIsTxTrfReady() == 0) && (FCL_TIMEOUT < 32000))		//Wait for outgoing buffer to empty
			FCL_TIMEOUT = FCL_TIMEOUT + 1;

		if (FCL_TIMEOUT == 32000)	//Pipeline full or disconnected
		{
			return(1);		//USB Not Ready
		}
		else
		{
			putUSBUSART(&FCL_DATA,1);
		}
	}

	while (mUSBUSARTIsTxTrfReady() == 0)		//Wait for outgoing buffer to empty
	    CDCTxService();

  return (0);
}



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendByteArray_, (MX_UINT8 *FCL_DATA, MX_UINT16 FCLsz_DATA, MX_UINT8 FCL_NUMBYTES))
{
	MX_UINT16 FCL_TIMEOUT = (0x0);
	MX_UINT16 FCL_POINTER = 0;

	if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1))
	{
		return(2);	    //USB Not Configured
	}
	else
	{
		while (FCL_NUMBYTES)
		{
			CDCTxService();		//Required or every other send fails

			while ((mUSBUSARTIsTxTrfReady() == 0) && (FCL_TIMEOUT < 32000))		//Wait for outgoing buffer to empty
				FCL_TIMEOUT = FCL_TIMEOUT + 1;

			if (FCL_TIMEOUT >= 32000)	//Pipeline full or disconnected
			{
				return(1);		//USB Not Ready
			}
			else
			{
				//Break transmission up into 64 byte packets - max USB can handle for CDC class.
				if (FCL_NUMBYTES > 64)
				{
					putUSBUSART(&FCL_DATA[FCL_POINTER], 64);
					FCL_NUMBYTES -= 64;
					FCL_POINTER += 64;
				}
				else
				{
					putUSBUSART(&FCL_DATA[FCL_POINTER], FCL_NUMBYTES);
					FCL_NUMBYTES = 0;
				}
			}
		}
	}

	while (mUSBUSARTIsTxTrfReady() == 0)		//Wait for outgoing buffer to empty
	    CDCTxService();

	return (0);
}



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendString_, (MX_CHAR *FCL_DATA, MX_UINT16 FCLsz_DATA))
{
  	MX_UINT16 FCL_TIMEOUT = (0x0);
  	MX_UINT16 FCL_POINTER = 0;
  	MX_UINT8 FCL_LENGTH;

	FCL_LENGTH = FCI_GETLENGTH(FCL_DATA, FCLsz_DATA);

	if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1))
	{
		return(2);	    //USB Not Configured
	}
	else
	{
		while (FCL_LENGTH)
		{
			CDCTxService();		//Required or every other send fails

			while ((mUSBUSARTIsTxTrfReady() == 0) && (FCL_TIMEOUT < 32000))		//Wait for outgoing buffer to empty
				FCL_TIMEOUT = FCL_TIMEOUT + 1;

			if (FCL_TIMEOUT >= 32000)	//Pipeline full or disconnected
			{
				return(1);		//USB Not Ready
			}
			else
			{
				//Break transmission up into 64 byte packets - max USB can handle for CDC class.
				if (FCL_LENGTH > 64)
				{
					putUSBUSART(&FCL_DATA[FCL_POINTER], 64);
					FCL_LENGTH -= 64;
					FCL_POINTER += 64;
				}
				else
				{
					putUSBUSART(&FCL_DATA[FCL_POINTER], FCL_LENGTH);
					FCL_LENGTH = 0;
				}
				FCL_TIMEOUT = 0;
			}
		}
	}

	while (mUSBUSARTIsTxTrfReady() == 0)		//Wait for outgoing buffer to empty
	    CDCTxService();

    return (0);
}
