// CRC: A6459004C43C0517DC6DFC5681C2AD698104299A14C9E1875427A2F7EF4303D9CFD76A29863CD488DE50EA9D9C0AC8D13AD2C1E57C9DD3A2E0F77167644C7039309998607486AEECF3B5FC38F9C0B531A99365E6319B07079C40BB93043A73C94746FB16C5FE42290C3CAEE8E7DA6987CD33A5C684F99AD6D523CE6650717858884B0B5379CE4A1EBC21BC8638A2514F77DDB3D971D4E719E2F27DB434EC2CAFB5CAAEC32EE186B2CE287016F8E37156F3E174B7D450B6CDC75635571165C73DBFE2A2EEA02FA36E549D34A0D5AD11F31F72AF6BDD30AC80A441C29BF5F7717AE091E7F8360F97D35D2E1919BC6D834D57C406BC4A49D3F1
// REVISION: 3.0
// GUID: 98E277C9-2363-4F5A-8BBB-E6BBECF9EEAC
// DATE: 19\11\2025
// DIR: CAL\PIC32BIT\PIC32BIT_CAL_USB_Serial.c

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



#include "CDC_Setup.h"
#include "CDC_Desc.h"

SYSTEM_OBJECTS sysObj;
APP_DATA appData;

#ifdef MX_PIC32_MX
extern const DRV_USBFS_INIT drvUSBInit;
#endif

#ifdef MX_PIC32_MZ
extern const DRV_USBHS_INIT drvUSBInit;
#endif

const SYS_DEVCON_INIT sysDevconInit =
{
    .moduleInit = {0},
};

#define APP_MAKE_BUFFER_DMA_READY __attribute__((coherent)) __attribute__((aligned(16)))
static uint8_t APP_MAKE_BUFFER_DMA_READY writeBuffer[TX_BUF_SZ];
static uint8_t APP_MAKE_BUFFER_DMA_READY readBuffer[RX_BUF_SZ];

uint16_t MX_USBSer_RxByteCount = 0;
uint16_t MX_USBSer_RxPtr = 0;
uint8_t MX_USBSer_RxBuffer[RX_BUF_SZ];




CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_Initialise_, ())
{
	MX_UINT16 FCL_DELAY_COUNTER = 0;

	sysObj.sysDevcon = SYS_DEVCON_Initialize(SYS_DEVCON_INDEX_0, (SYS_MODULE_INIT*)&sysDevconInit);

	#ifdef MX_PIC32_MX
		sysObj.drvUSBObject = DRV_USBFS_Initialize(DRV_USBFS_INDEX_0, &drvUSBInit);
		SYS_INT_Initialize();
		SYS_INT_VectorPrioritySet(INT_VECTOR_USB1, INT_PRIORITY_LEVEL4);
		SYS_INT_VectorSubprioritySet(INT_VECTOR_USB1, INT_SUBPRIORITY_LEVEL0);
	#endif

	#ifdef MX_PIC32_MZ
		sysObj.drvUSBObject = DRV_USBHS_Initialize(DRV_USBHS_INDEX_0, &drvUSBInit);
		SYS_INT_Initialize();
		SYS_INT_VectorPrioritySet(INT_VECTOR_USB1, INT_PRIORITY_LEVEL4);
		SYS_INT_VectorSubprioritySet(INT_VECTOR_USB1, INT_SUBPRIORITY_LEVEL0);
		SYS_INT_VectorPrioritySet(INT_VECTOR_USB1_DMA, INT_PRIORITY_LEVEL4);
		SYS_INT_VectorSubprioritySet(INT_VECTOR_USB1_DMA, INT_SUBPRIORITY_LEVEL0);
	#endif

    sysObj.usbDevObject0 = USB_DEVICE_Initialize(USB_DEVICE_INDEX_0, &usbDevInitData);

    SYS_INT_Enable();

    APP_Initialize();


	if (MX_USB_SERIAL_ENUM_TOUTEN_X)
	{
		appData.deviceHandle = -1;
		while(appData.deviceHandle == -1 && FCL_DELAY_COUNTER < MX_USB_SERIAL_ENUM_TOUT_X)
		{

			appData.deviceHandle = USB_DEVICE_Open(USB_DEVICE_INDEX_0, DRV_IO_INTENT_READWRITE);

			SYS_DEVCON_Tasks(sysObj.sysDevcon);

			#ifdef MX_PIC32_MX
				DRV_USBFS_Tasks(sysObj.drvUSBObject);
			#endif

			#ifdef MX_PIC32_MZ
				DRV_USBHS_Tasks(sysObj.drvUSBObject);
			#endif

			USB_DEVICE_Tasks(sysObj.usbDevObject0);

			FCI_DELAYBYTE_MS(10);
			FCL_DELAY_COUNTER = FCL_DELAY_COUNTER + 1;
		}

		if(appData.deviceHandle != USB_DEVICE_HANDLE_INVALID)
		{
			USB_DEVICE_EventHandlerSet(appData.deviceHandle, APP_USBDeviceEventHandler, 0);
			appData.state = APP_STATE_SERVICE_TASKS;

			FCI_DELAYBYTE_MS(200);

			SYS_DEVCON_Tasks(sysObj.sysDevcon);

			#ifdef MX_PIC32_MX
				DRV_USBFS_Tasks(sysObj.drvUSBObject);
			#endif

			#ifdef MX_PIC32_MZ
				DRV_USBHS_Tasks(sysObj.drvUSBObject);
			#endif

			USB_DEVICE_Tasks(sysObj.usbDevObject0);

			return 0;
		}

		return 255;

	}
	else
	{
	  	do
	  	{
			appData.deviceHandle = USB_DEVICE_Open(USB_DEVICE_INDEX_0, DRV_IO_INTENT_READWRITE);

			SYS_DEVCON_Tasks(sysObj.sysDevcon);

			#ifdef MX_PIC32_MX
				DRV_USBFS_Tasks(sysObj.drvUSBObject);
			#endif

			#ifdef MX_PIC32_MZ
				DRV_USBHS_Tasks(sysObj.drvUSBObject);
			#endif

			USB_DEVICE_Tasks(sysObj.usbDevObject0);
		}
		while(appData.deviceHandle == USB_DEVICE_HANDLE_INVALID);

		USB_DEVICE_EventHandlerSet(appData.deviceHandle, APP_USBDeviceEventHandler, 0);
		appData.state = APP_STATE_SERVICE_TASKS;

		FCI_DELAYBYTE_MS(200);

		SYS_DEVCON_Tasks(sysObj.sysDevcon);

		#ifdef MX_PIC32_MX
			DRV_USBFS_Tasks(sysObj.drvUSBObject);
		#endif

		#ifdef MX_PIC32_MZ
			DRV_USBHS_Tasks(sysObj.drvUSBObject);
		#endif

		USB_DEVICE_Tasks(sysObj.usbDevObject0);

		return 0;
	}
}



CALFUNCTION(MX_UINT16, FC_CAL_USB_Serial_ReadByte_, (MX_UINT8 timeout_ms))
{
	MX_UINT16 FCR_RETVAL = 255;
	MX_UINT8 inner = 0;
	MX_UINT8 FCL_WAIT_FOREVER = 0;

	if (MX_USB_SERIAL_ENUM_RETURN_X)
		FCR_RETVAL = 512;

	if (timeout_ms == 0)
	{
		timeout_ms = 1;
		inner = 98;
	}

    if(MX_USBSer_RxByteCount)
    {
        FCR_RETVAL = MX_USBSer_RxBuffer[MX_USBSer_RxPtr++];
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

        appData.readLen = 0;
    	while(appData.readLen == 0 && timeout_ms > 0)
	    {
			SYS_DEVCON_Tasks(sysObj.sysDevcon);

			#ifdef MX_PIC32_MX
				DRV_USBFS_Tasks(sysObj.drvUSBObject);
			#endif

			#ifdef MX_PIC32_MZ
				DRV_USBHS_Tasks(sysObj.drvUSBObject);
			#endif

			USB_DEVICE_Tasks(sysObj.usbDevObject0);

			if(appData.readTransferHandle == USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID)
			{
				USB_DEVICE_CDC_Read(USB_DEVICE_CDC_INDEX_0,
								&appData.readTransferHandle,
								readBuffer,
								RX_BUF_SZ);
			}

			if ((FCL_WAIT_FOREVER == 0) && (appData.readLen == 0))
			{
				inner++;
				delay_us(10);
				if (inner == 100)
				{
					inner = 0;
					timeout_ms--;
				}
			}
			else
			{
				FCR_RETVAL = readBuffer[0];

				if(appData.readLen > 1)
				{
					MX_USBSer_RxByteCount = appData.readLen;
					MX_USBSer_RxPtr = 1;
					if(appData.readLen < RX_BUF_SZ)
					MX_USBSer_RxBuffer[appData.readLen] = 0;
				}
			}
		}
    }

	return FCR_RETVAL;
}




CALFUNCTION(void, FC_CAL_USB_Serial_ReadString_, (MX_CHAR *FCR_RETVAL, MX_UINT16 FCRsz_RETVAL, MX_UINT8 timeout_ms, MX_UINT8 FCL_LENGTH))
{
	MX_UINT8 FCL_WAIT_FOREVER = 0;
	MX_UINT16 inner = 0;
	MX_UINT16 idx;

	if (timeout_ms == 0)
		timeout_ms = 1;

	MX_USBSer_RxByteCount = 0;

	if(!appData.isConfigured)
	{
		appData.readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
		FCR_RETVAL[0] = 0;
		appData.readProcessedLen = 0;
	}
	else
	{
		if(timeout_ms == 255)
			FCL_WAIT_FOREVER = 1;

		appData.readLen = 0;
		while((appData.readLen == 0) && (timeout_ms > 0))
		{
			SYS_DEVCON_Tasks(sysObj.sysDevcon);

			#ifdef MX_PIC32_MX
				DRV_USBFS_Tasks(sysObj.drvUSBObject);
			#endif

			#ifdef MX_PIC32_MZ
				DRV_USBHS_Tasks(sysObj.drvUSBObject);
			#endif

			USB_DEVICE_Tasks(sysObj.usbDevObject0);

			if(appData.readTransferHandle == USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID)
			{
				USB_DEVICE_CDC_Read(USB_DEVICE_CDC_INDEX_0,
								&appData.readTransferHandle,
								readBuffer,
								RX_BUF_SZ);
			}

			if((appData.readLen) && (FCL_WAIT_FOREVER == 0))
			{
				delay_us(10);
				inner++;
				if(inner >= 100)
				{
					inner = 0;
					timeout_ms --;
				}
			}
		}

		if(appData.readLen)
		{
			if(appData.readLen <= FCL_LENGTH)
			{
				for(idx = 0; idx <= appData.readLen; idx++)
					FCR_RETVAL[idx] = readBuffer[idx];
			}
		}

		if(appData.readLen < FCL_LENGTH);
		  FCR_RETVAL[appData.readLen] = 0;

		appData.readLen = 0;
	}
}


CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendByte_, (MX_UINT8 FCL_DATA))
{
	MX_UINT16 FCL_TIMEOUT = (0x0);

	writeBuffer[0] = FCL_DATA;

	if(!appData.isConfigured)
	{
		appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
		return(2);
	}
	else
	{
		USB_DEVICE_CDC_Write(USB_DEVICE_CDC_INDEX_0,
					   &appData.writeTransferHandle,
					   writeBuffer,
					   1,
					   USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);

		SYS_DEVCON_Tasks(sysObj.sysDevcon);

		#ifdef MX_PIC32_MX
			DRV_USBFS_Tasks(sysObj.drvUSBObject);
		#endif

		#ifdef MX_PIC32_MZ
			DRV_USBHS_Tasks(sysObj.drvUSBObject);
		#endif

		USB_DEVICE_Tasks(sysObj.usbDevObject0);
	}

	return (0);
}


CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendByteArray_, (MX_UINT8 *FCL_DATA, MX_UINT16 FCLsz_DATA, MX_UINT8 FCL_NUMBYTES))
{
	MX_UINT16 FCL_TIMEOUT = (0x0);
	MX_UINT8 n;

	for(n = 0; (n < FCL_NUMBYTES); n++)
	{
		writeBuffer[n] = FCL_DATA[n];
	}

	if(!appData.isConfigured)
	{
		appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
		return(2);
	}
	else
	{
		USB_DEVICE_CDC_Write(USB_DEVICE_CDC_INDEX_0,
					   &appData.writeTransferHandle,
					   writeBuffer,
					   FCL_NUMBYTES,
					   USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);

		SYS_DEVCON_Tasks(sysObj.sysDevcon);

		#ifdef MX_PIC32_MX
			DRV_USBFS_Tasks(sysObj.drvUSBObject);
		#endif

		#ifdef MX_PIC32_MZ
			DRV_USBHS_Tasks(sysObj.drvUSBObject);
		#endif

		USB_DEVICE_Tasks(sysObj.usbDevObject0);
	}

	return (0);
}



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendString_, (MX_CHAR *FCL_DATA, MX_UINT16 FCLsz_DATA))
{
  	MX_UINT16 FCL_TIMEOUT = (0x0);
  	MX_UINT8 FCL_LENGTH;
	MX_UINT8 n;

	FCL_LENGTH = FCI_GETLENGTH(FCL_DATA, FCLsz_DATA);

	if(FCL_LENGTH)
	{
		memcpy(writeBuffer, FCL_DATA, FCL_LENGTH);

		if(!appData.isConfigured)
		{
	  		appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
	  		return(2);
		}
		else
		{
	  		USB_DEVICE_CDC_Write(USB_DEVICE_CDC_INDEX_0,
						 &appData.writeTransferHandle,
						 writeBuffer,
						 FCL_LENGTH,
						 USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);

	  		SYS_DEVCON_Tasks(sysObj.sysDevcon);

			#ifdef MX_PIC32_MX
	  			DRV_USBFS_Tasks(sysObj.drvUSBObject);
			#endif

			#ifdef MX_PIC32_MZ
	  			DRV_USBHS_Tasks(sysObj.drvUSBObject);
			#endif

	  		USB_DEVICE_Tasks(sysObj.usbDevObject0);
		}
	}

    return (0);
}

