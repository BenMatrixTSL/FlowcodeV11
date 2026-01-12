// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B81CCAA1F64DCE9D54FCE71B97CFC36836EAB9DC0344E07D5326A66CC0150DD556901481B78BE484580E0E1E6CE4FCFEC9ABB24D739BCDFCC30C3CAEE8E7DA6987117514A3CBD291ACF3154A8FC3FEBA76B3FA004481E251B4F6EFC00A6B2119BCE80FBF456DECC7CC507136E1C2A1F04340DC414F4C011B4DDD36EF41535D94F72F655913F19FD61457023687575AD238502990E2AF2DF044549D34A0D5AD11F3252EF3FAE9F6D8552BCEFCA7FF7CCDC70FC0A4E2B260BEDCC0B4C7476DCE16968A51E041C1ABFE86
// REVISION: 3.0
// GUID: 6045D797-27BC-454E-8FB4-C115E2FB6926
// DATE: 01\08\2025
// DIR: CAL\PIC\PIC_CAL_USB_Serial.c

/*********************************************************************
 *              Flowcode CAL USB Serial CDC Comms
 *
 * File: PIC_CAL_USB_Serial.c
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



#ifdef MX_USB_TYPE1                     //ECIO / MIAC / 18F4455
 #define FIXED_ADDRESS_MEMORY
 #define IN_DATA_BUFFER_ADDRESS_TAG      @0x500
 #define OUT_DATA_BUFFER_ADDRESS_TAG     @0x540
 #define CONTROL_BUFFER_ADDRESS_TAG      @0x580
#endif

#ifdef MX_USB_TYPE3                     //18F14K50
 #define FIXED_ADDRESS_MEMORY
 #define IN_DATA_BUFFER_ADDRESS_TAG      @0x240
 #define OUT_DATA_BUFFER_ADDRESS_TAG     @0x280
 #define CONTROL_BUFFER_ADDRESS_TAG      @0x2C0
#endif

#ifdef MX_USB_TYPE5                     //16F1455
 #define FIXED_ADDRESS_MEMORY
 #define IN_DATA_BUFFER_ADDRESS_TAG      @0x0A0
 #define OUT_DATA_BUFFER_ADDRESS_TAG     @0x120
 #define CONTROL_BUFFER_ADDRESS_TAG      @0x1A0
#endif

#ifdef MX_USB_TYPE6                     //18F45K50
 #define FIXED_ADDRESS_MEMORY
 #define IN_DATA_BUFFER_ADDRESS_TAG      @0x500
 #define OUT_DATA_BUFFER_ADDRESS_TAG     @0x540
 #define CONTROL_BUFFER_ADDRESS_TAG      @0x580
#endif

#ifdef MX_USB_TYPE0
 #error "Your target device does not support USB components"
#endif

// Global Defines
#define USB_BUS_SENSE       1
#define self_power          1
#define tris_usb_bus_sense	1
#define tris_self_power		1

#define USB_CONFIG	"C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC/USB/usb_serial_config.h"

#include USB_CONFIG

// USB library includes
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC/USB/usb.h"
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC/USB/usb_device.h"
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC/USB/usb_device_cdc.h"
//#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC/USB/system.h"

#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC/USB/usb_device.c"
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC/USB/usb_device_cdc.c"
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC/USB/usb_hal_16bit.c"
//#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC/USB/system.c"

// Device name and manufacturer
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[dev_manufacturer_count_DS];}sd001={sizeof(sd001),USB_DESCRIPTOR_STRING,{dev_manufacturer_DS}};
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[dev_name_count_DS];}sd002={sizeof(sd002),USB_DESCRIPTOR_STRING,{dev_name_DS}};

#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC/USB/usb_serial_descriptors.c"
#include "C:/ProgramData/MatrixTSL/FlowcodeV10/CAL/PIC/USB/usb_serial_handler.c"

uint8_t MX_USBSer_RxByteCount = 0;
uint8_t MX_USBSer_RxPtr = 0;
uint8_t MX_USBSer_RxBuffer[RX_BUF_SZ];



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_Initialise_, ())
{

	MX_UINT16 FCL_DELAY_COUNTER = 0;
	MX_UINT8  FCL_INNER = 0;

	//On the PIC18F87J50 Family of USB microcontrollers, the PLL will not power up and be enabled
	//by default, even if a PLL enabled oscillator configuration is selected (such as HS+PLL).
	//This allows the device to power up at a lower initial operating frequency, which can be
	//advantageous when powered from a source which is not gauranteed to be adequate for 48MHz
	//operation.  On these devices, user firmware needs to manually set the OSCTUNE&lt;PLLEN&gt; bit to
	//power up the PLL.

	#if defined(P18F24J50) || defined(P18F25J55) || defined(P18F26J50) || defined(P18F44J50) || defined(P18F45J50) || defined(P18F46J55) || defined(P18F87J50) ||  defined(P18F86J55) || defined(P18F86J50) || defined(P18F85J50) || defined(P18F67J50) || defined(P18F66J55) || defined(P18F66J50) || defined(P18F65J50)

	  MX_UINT16 pll_startup_counter = 600;
	  OSCTUNEbits.PLLEN = 1;  //Enable the PLL and wait 2+ms until the PLL locks before enabling USB module
	  while(pll_startup_counter--);

	//Device switches over automatically to PLL output after PLL is locked and ready.
	#endif

	MX_USBSer_RxByteCount = 0;

    USBDeviceInit();
	if(USB_BUS_SENSE && (USBGetDeviceState() == DETACHED_STATE))
        USBDeviceAttach();

	if (MX_USB_SERIAL_ENUM_TOUTEN_X)
	{
		//Wait for USB to startup and enumerate
		while(USBDeviceState != CONFIGURED_STATE && FCL_DELAY_COUNTER < MX_USB_SERIAL_ENUM_TOUT_X)
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

