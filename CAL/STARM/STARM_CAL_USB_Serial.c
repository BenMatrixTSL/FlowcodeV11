// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BE5A11A7B597E6F7EA8FE53F6FF9C4729AAFF7D054EA9B4CC9BDC419C02E9E1921C224CC8FEEF312C5C951050EA34CC75A14C7C93C31DAFADEA9B11F738DF98E1591BBDEBE7832D26A6B03417734FDB29E3B56B4E9608BE7B0EED62BE8F64CF1433C4D6AB521291475EBE8E58CB0CCE2AD1C9E057381696A8EA24B2535FC5257D0E7A48E7ED61B6A7394E281A8D4067A08232AE3563A2DB2E4549D34A0D5AD11F3B9751DA302EDA8B8E69126C02128AB92555C97E438576F95AFA22E870078457321B85372DCE0C3F0
// REVISION: 4.0
// GUID: 6E365E38-6E2E-44E5-B462-5B36686836C8
// DATE: 12\11\2026
// DIR: CAL\STARM\STARM_CAL_USB_Serial.c

/*********************************************************************
 *              Flowcode CAL USB Serial CDC Comms
 *
 * File: STARM_CAL_USB_Serial.c
 *
 * (c) 2025 Matrix TSL
 * http://www.matrixTSL.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
 * "Company") for its Flowcode graphical programming language is
 * intended and supplied to you, the Company's customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
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
 * 100725 | BR | Created (stub)
 * 160926 | BR | Implemented using STM32Cube USB Device Library (CDC-ACM class)
 * 121126 | BR | Reworked to build against the USB Device Library V2.4.2 shipped with
 *        |    | the Flowcode STARM compiler (4 member CDC interface, no TransmitCplt).
 *        |    | Middleware sources now compiled in from this file, usbd_conf.h supplied
 *        |    | in FCD\ARM\inc. Fixed F0/F3 build (no OTG only PCD init fields), F3
 *        |    | USB pin AF, missing CDC command endpoint PMA, F0/F3 48MHz USB clock,
 *        |    | stack/user buffers being transmitted asynchronously, missing ZLP.
 *
 * Notes:
 *
 *  Requirements:
 *   - STM32Cube USB Device Library (Core + CDC class), as shipped in
 *     <compilerstarm>\stm32cubeXX\Middlewares\ST\STM32_USB_Device_Library
 *     The include paths are added by FCD\ARM\batch\stm32comp.bat.
 *   - usbd_conf.h - supplied in FCD\ARM\inc (added to the include path by
 *     stm32comp.bat).
 *   - HAL_PCD_MODULE_ENABLED in the family stm32xxxx_hal_conf.h.
 *
 *  Supported USB peripherals:
 *   - USB_OTG_FS (F2/F4/F7) on PA11/PA12.
 *   - USB Full Speed device peripheral (F0/F1/F3/L0/L1/L4) on PA11/PA12.
 *
 *  USB clock (must be 48MHz):
 *   - F0 with HSI48: USB is clocked from HSI48 trimmed by the CRS from USB SOF
 *     (crystal-less), independent of the system clock configuration.
 *   - F0 without HSI48 (e.g. F070): PLL output must be 48MHz.
 *   - F3: PLL output must be 72MHz (USB = PLL / 1.5) or 48MHz (USB = PLL),
 *     PLL should be sourced from HSE for USB accuracy.
 *   - F2/F4/F7: PLLQ output (set via the chip configuration) must be 48MHz.
 *
 */


#define MX_USB_SERIAL_ENUM_TOUTEN_X     	CAL_APPEND(MX_USB_SERIAL_ENUM_TOUTEN_, MX_USB_SERIAL_NUM)
#define MX_USB_SERIAL_ENUM_TOUT_X     		CAL_APPEND(MX_USB_SERIAL_ENUM_TOUT_, MX_USB_SERIAL_NUM)
#define MX_USB_SERIAL_ENUM_RETURN_X     	CAL_APPEND(MX_USB_SERIAL_ENUM_RETURN_, MX_USB_SERIAL_NUM)


/*=====================================================================*\
   Peripheral / family detection
\*=====================================================================*/

#ifndef HAL_PCD_MODULE_ENABLED
	#error "USB Serial: HAL_PCD_MODULE_ENABLED must be defined in the stm32xxxx_hal_conf.h for this family"
#endif

#if defined(USB_OTG_FS)
	#define MX_USB_INSTANCE		USB_OTG_FS
	#define MX_USB_IS_OTG		1
#elif defined(USB)
	#define MX_USB_INSTANCE		USB
	#define MX_USB_IS_OTG		0
#else
	#error "USB Serial: this STM32 device does not have a USB Full Speed device peripheral"
#endif

#if MX_USB_IS_OTG
	#define MX_USB_CLOCK_ENABLE()		__HAL_RCC_USB_OTG_FS_CLK_ENABLE()
#else
	#define MX_USB_CLOCK_ENABLE()		__HAL_RCC_USB_CLK_ENABLE()
#endif

#if defined(STM32F2) || defined(STM32F4) || defined(STM32F7)
	#define MX_USB_IRQn				OTG_FS_IRQn
	#define MX_USB_IRQHandler		OTG_FS_IRQHandler
#elif defined(STM32F0)
	#define MX_USB_IRQn				USB_IRQn
	#define MX_USB_IRQHandler		USB_IRQHandler
#elif defined(STM32F1)
	#define MX_USB_IRQn				USB_LP_CAN1_RX0_IRQn
	#define MX_USB_IRQHandler		USB_LP_CAN1_RX0_IRQHandler
#elif defined(STM32F3)
	#define MX_USB_IRQn				USB_LP_CAN_RX0_IRQn
	#define MX_USB_IRQHandler		USB_LP_CAN_RX0_IRQHandler
#elif defined(STM32L0)
	#define MX_USB_IRQn				USB_IRQn
	#define MX_USB_IRQHandler		USB_IRQHandler
#elif defined(STM32L1)
	#define MX_USB_IRQn				USB_LP_IRQn
	#define MX_USB_IRQHandler		USB_LP_IRQHandler
#elif defined(STM32L4)
	#if MX_USB_IS_OTG
		#define MX_USB_IRQn			OTG_FS_IRQn
		#define MX_USB_IRQHandler	OTG_FS_IRQHandler
	#else
		#define MX_USB_IRQn			USB_IRQn
		#define MX_USB_IRQHandler	USB_IRQHandler
	#endif
#else
	#error "USB Serial: unknown STM32 family - please add the USB IRQ name for this device"
#endif


/*=====================================================================*\
   STM32Cube USB Device Library
   The library sources are compiled as part of this translation unit so
   they are only built into projects that use the USB Serial component.
\*=====================================================================*/

#include "usbd_core.h"
#include "usbd_ctlreq.h"
#include "usbd_ioreq.h"
#include "usbd_cdc.h"

#include "usbd_core.c"
#include "usbd_ctlreq.c"
#include "usbd_ioreq.c"
#include "usbd_cdc.c"


//Static allocation for the CDC class data (USBD_malloc / USBD_free in usbd_conf.h)
static uint32_t MX_USBD_CDC_ClassMem[(sizeof(USBD_CDC_HandleTypeDef) / 4) + 1];

void *USBD_static_malloc(uint32_t size)
{
	return MX_USBD_CDC_ClassMem;
}

void USBD_static_free(void *p)
{
}


/*=====================================================================*\
   Descriptors  (usbd_desc.c equivalent)
\*=====================================================================*/

#define MX_USBD_VID							MX_VID
#define MX_USBD_PID							MX_PID
#define MX_USBD_LANGID_STRING				0x0409		//English (US)
#define MX_USBD_CONFIGURATION_STRING_FS		"CDC Config"
#define MX_USBD_INTERFACE_STRING_FS			"CDC Interface"
#define MX_USBD_SERIAL_CHARS				8
#define MX_USBD_SERIAL_DESC_SIZ				(2 + (MX_USBD_SERIAL_CHARS * 2))

//Manufacturer/Product names are set by the user in the USB_Serial component and
//generated into the project as dev_manufacturer_DS / dev_name_DS (comma
//separated char lists, no null terminator) - build plain C strings from them here.
static const MX_CHAR MX_USBD_MANUFACTURER_STRING[] = {dev_manufacturer_DS, 0};
static const MX_CHAR MX_USBD_PRODUCT_STRING_FS[]   = {dev_name_DS, 0};

__ALIGN_BEGIN static uint8_t MX_USBD_FS_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END =
{
	0x12,						/*bLength */
	USB_DESC_TYPE_DEVICE,		/*bDescriptorType*/
	0x00, 0x02,					/*bcdUSB = 2.00*/
	0x02,						/*bDeviceClass: CDC*/
	0x02,						/*bDeviceSubClass*/
	0x00,						/*bDeviceProtocol*/
	USB_MAX_EP0_SIZE,			/*bMaxPacketSize*/
	LOBYTE(MX_USBD_VID), HIBYTE(MX_USBD_VID),	/*idVendor*/
	LOBYTE(MX_USBD_PID), HIBYTE(MX_USBD_PID),	/*idProduct*/
	0x00, 0x02,					/*bcdDevice = 2.00*/
	USBD_IDX_MFC_STR,			/*Index of manufacturer string*/
	USBD_IDX_PRODUCT_STR,		/*Index of product string*/
	USBD_IDX_SERIAL_STR,		/*Index of serial number string*/
	USBD_MAX_NUM_CONFIGURATION	/*bNumConfigurations*/
};

__ALIGN_BEGIN static uint8_t MX_USBD_FS_LangIDDesc[USB_LEN_LANGID_STR_DESC] __ALIGN_END =
{
	USB_LEN_LANGID_STR_DESC,
	USB_DESC_TYPE_STRING,
	LOBYTE(MX_USBD_LANGID_STRING), HIBYTE(MX_USBD_LANGID_STRING)
};

__ALIGN_BEGIN static uint8_t MX_USBD_FS_SerialDesc[MX_USBD_SERIAL_DESC_SIZ] __ALIGN_END;
__ALIGN_BEGIN static uint8_t MX_USBD_FS_StrDesc[USBD_MAX_STR_DESC_SIZ] __ALIGN_END;


static void MX_USB_IntToUnicode(uint32_t value, uint8_t *pbuf, uint8_t len)
{
	uint8_t idx;

	for (idx = 0; idx < len; idx++)
	{
		if ((value >> 28) < 0xA)
			pbuf[2 * idx] = (value >> 28) + '0';
		else
			pbuf[2 * idx] = (value >> 28) + 'A' - 10;

		value = value << 4;
		pbuf[2 * idx + 1] = 0;
	}
}

static uint8_t *MX_USBD_FS_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	*length = sizeof(MX_USBD_FS_DeviceDesc);
	return MX_USBD_FS_DeviceDesc;
}

static uint8_t *MX_USBD_FS_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	*length = sizeof(MX_USBD_FS_LangIDDesc);
	return MX_USBD_FS_LangIDDesc;
}

static uint8_t *MX_USBD_FS_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	USBD_GetString((uint8_t *)MX_USBD_MANUFACTURER_STRING, MX_USBD_FS_StrDesc, length);
	return MX_USBD_FS_StrDesc;
}

static uint8_t *MX_USBD_FS_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	USBD_GetString((uint8_t *)MX_USBD_PRODUCT_STRING_FS, MX_USBD_FS_StrDesc, length);
	return MX_USBD_FS_StrDesc;
}

static uint8_t *MX_USBD_FS_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	uint32_t serial;

	#if defined(UID_BASE)
		//Unique device ID -> 8 hex digit serial number
		serial = (*(uint32_t *)(UID_BASE)) + (*(uint32_t *)(UID_BASE + 4)) + (*(uint32_t *)(UID_BASE + 8));
	#else
		serial = 0xF10CD001;	//Fallback fixed serial when device UID is not available
	#endif

	MX_USBD_FS_SerialDesc[0] = MX_USBD_SERIAL_DESC_SIZ;
	MX_USBD_FS_SerialDesc[1] = USB_DESC_TYPE_STRING;
	MX_USB_IntToUnicode(serial, &MX_USBD_FS_SerialDesc[2], MX_USBD_SERIAL_CHARS);

	*length = MX_USBD_SERIAL_DESC_SIZ;
	return MX_USBD_FS_SerialDesc;
}

static uint8_t *MX_USBD_FS_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	USBD_GetString((uint8_t *)MX_USBD_CONFIGURATION_STRING_FS, MX_USBD_FS_StrDesc, length);
	return MX_USBD_FS_StrDesc;
}

static uint8_t *MX_USBD_FS_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	USBD_GetString((uint8_t *)MX_USBD_INTERFACE_STRING_FS, MX_USBD_FS_StrDesc, length);
	return MX_USBD_FS_StrDesc;
}

static USBD_DescriptorsTypeDef MX_USB_FS_Desc =
{
	MX_USBD_FS_DeviceDescriptor,
	MX_USBD_FS_LangIDStrDescriptor,
	MX_USBD_FS_ManufacturerStrDescriptor,
	MX_USBD_FS_ProductStrDescriptor,
	MX_USBD_FS_SerialStrDescriptor,
	MX_USBD_FS_ConfigStrDescriptor,
	MX_USBD_FS_InterfaceStrDescriptor,
};


/*=====================================================================*\
   Low level driver  (usbd_conf.c equivalent)
\*=====================================================================*/

static PCD_HandleTypeDef MX_USB_HANDLE_HPCD;
static USBD_HandleTypeDef MX_USB_HANDLE_HUSBD;

//dev_state is changed from the USB interrupt - always re-read it from memory
#define MX_USB_DEV_STATE		(((volatile USBD_HandleTypeDef *)&MX_USB_HANDLE_HUSBD)->dev_state)
#define MX_USB_CONFIGURED		(MX_USB_DEV_STATE == USBD_STATE_CONFIGURED)


void MX_USB_IRQHandler(void)
{
	HAL_PCD_IRQHandler(&MX_USB_HANDLE_HPCD);
}


//Make sure the USB peripheral is fed with a 48MHz clock
static void MX_USB_ClockConfig(void)
{
#if defined(STM32F0)
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	#if defined(RCC_HSI48_SUPPORT) && defined(CRS)
		RCC_CRSInitTypeDef RCC_CRSInitStruct = {0};

		//Crystal-less USB - HSI48 trimmed by the clock recovery system from the USB SOF
		__HAL_RCC_HSI48_ENABLE();
		while (__HAL_RCC_GET_FLAG(RCC_FLAG_HSI48RDY) == RESET);

		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
		PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
		HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

		__HAL_RCC_CRS_CLK_ENABLE();
		RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;
		RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_USB;
		RCC_CRSInitStruct.Polarity = RCC_CRS_SYNC_POLARITY_RISING;
		RCC_CRSInitStruct.ReloadValue = __HAL_RCC_CRS_RELOADVALUE_CALCULATE(48000000, 1000);
		RCC_CRSInitStruct.ErrorLimitValue = RCC_CRS_ERRORLIMIT_DEFAULT;
		RCC_CRSInitStruct.HSI48CalibrationValue = RCC_CRS_HSI48CALIBRATION_DEFAULT;
		HAL_RCCEx_CRSConfig(&RCC_CRSInitStruct);
	#else
		//No HSI48 (e.g. STM32F070) - the PLL must be configured for 48MHz
		PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
		PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
		HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
	#endif

#elif defined(STM32F3)
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	//USB clock is PLL / 1.5 (72MHz PLL) or PLL / 1 (48MHz PLL)
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
	if ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK) && (HAL_RCC_GetSysClockFreq() == 48000000U))
		PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL;
	else
		PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

#endif
	//F2/F4/F7: 48MHz clock comes from PLLQ which is set up by the chip clock configuration
}


void HAL_PCD_MspInit(PCD_HandleTypeDef *hpcd)
{
	if (hpcd->Instance != MX_USB_INSTANCE)
		return;

	MX_USB_ClockConfig();

	#if MX_USB_IS_OTG || defined(GPIO_AF14_USB)
	{
		//USB D-/D+ on PA11/PA12
		GPIO_InitTypeDef GPIO_InitStruct = {0};

		__HAL_RCC_GPIOA_CLK_ENABLE();

		GPIO_InitStruct.Pin       = GPIO_PIN_11 | GPIO_PIN_12;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_NOPULL;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
		#if MX_USB_IS_OTG
			GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
		#else
			GPIO_InitStruct.Alternate = GPIO_AF14_USB;		//F3
		#endif
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
	#endif
	//F0/F1: the USB pins are dedicated to the peripheral once it is enabled

	MX_USB_CLOCK_ENABLE();

	HAL_NVIC_SetPriority(MX_USB_IRQn, 3, 0);
	HAL_NVIC_EnableIRQ(MX_USB_IRQn);
}

void HAL_PCD_MspDeInit(PCD_HandleTypeDef *hpcd)
{
	if (hpcd->Instance != MX_USB_INSTANCE)
		return;

	HAL_NVIC_DisableIRQ(MX_USB_IRQn);
}


//HAL PCD callbacks - bridge into the USB Device core
void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef *hpcd)
{
	USBD_LL_SetupStage((USBD_HandleTypeDef *)hpcd->pData, (uint8_t *)hpcd->Setup);
}

void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
	USBD_LL_DataOutStage((USBD_HandleTypeDef *)hpcd->pData, epnum, hpcd->OUT_ep[epnum].xfer_buff);
}

void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
	USBD_LL_DataInStage((USBD_HandleTypeDef *)hpcd->pData, epnum, hpcd->IN_ep[epnum].xfer_buff);
}

void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd)
{
	USBD_LL_SOF((USBD_HandleTypeDef *)hpcd->pData);
}

void HAL_PCD_ResetCallback(PCD_HandleTypeDef *hpcd)
{
	USBD_LL_SetSpeed((USBD_HandleTypeDef *)hpcd->pData, USBD_SPEED_FULL);
	USBD_LL_Reset((USBD_HandleTypeDef *)hpcd->pData);
}

void HAL_PCD_SuspendCallback(PCD_HandleTypeDef *hpcd)
{
	USBD_LL_Suspend((USBD_HandleTypeDef *)hpcd->pData);
}

void HAL_PCD_ResumeCallback(PCD_HandleTypeDef *hpcd)
{
	USBD_LL_Resume((USBD_HandleTypeDef *)hpcd->pData);
}

void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
	USBD_LL_IsoOUTIncomplete((USBD_HandleTypeDef *)hpcd->pData, epnum);
}

void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
	USBD_LL_IsoINIncomplete((USBD_HandleTypeDef *)hpcd->pData, epnum);
}

void HAL_PCD_ConnectCallback(PCD_HandleTypeDef *hpcd)
{
	USBD_LL_DevConnected((USBD_HandleTypeDef *)hpcd->pData);
}

void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef *hpcd)
{
	USBD_LL_DevDisconnected((USBD_HandleTypeDef *)hpcd->pData);
}


//USB Device core -> low level driver calls
USBD_StatusTypeDef USBD_LL_Init(USBD_HandleTypeDef *pdev)
{
	MX_USB_HANDLE_HPCD.pData = pdev;
	pdev->pData = &MX_USB_HANDLE_HPCD;

	MX_USB_HANDLE_HPCD.Instance = MX_USB_INSTANCE;
	MX_USB_HANDLE_HPCD.Init.speed = PCD_SPEED_FULL;
	MX_USB_HANDLE_HPCD.Init.ep0_mps = DEP0CTL_MPS_64;
	MX_USB_HANDLE_HPCD.Init.phy_itface = PCD_PHY_EMBEDDED;
	MX_USB_HANDLE_HPCD.Init.Sof_enable = DISABLE;
	MX_USB_HANDLE_HPCD.Init.low_power_enable = DISABLE;
	MX_USB_HANDLE_HPCD.Init.lpm_enable = DISABLE;
	MX_USB_HANDLE_HPCD.Init.battery_charging_enable = DISABLE;

	#if MX_USB_IS_OTG
		MX_USB_HANDLE_HPCD.Init.dev_endpoints = 4;		//OTG_FS has 4 bidirectional endpoints on F2/F4
		MX_USB_HANDLE_HPCD.Init.dma_enable = DISABLE;
		MX_USB_HANDLE_HPCD.Init.vbus_sensing_enable = DISABLE;
		MX_USB_HANDLE_HPCD.Init.use_dedicated_ep1 = DISABLE;
	#else
		MX_USB_HANDLE_HPCD.Init.dev_endpoints = 8;
	#endif

	if (HAL_PCD_Init(&MX_USB_HANDLE_HPCD) != HAL_OK)
		return USBD_FAIL;

	#if MX_USB_IS_OTG
		//FIFO sizes in 32-bit words (OTG_FS has 320 words in total)
		HAL_PCDEx_SetRxFiFo(&MX_USB_HANDLE_HPCD, 0x80);
		HAL_PCDEx_SetTxFiFo(&MX_USB_HANDLE_HPCD, 0, 0x40);
		HAL_PCDEx_SetTxFiFo(&MX_USB_HANDLE_HPCD, 1, 0x80);
	#else
		//Packet memory allocation - buffer table occupies the first 3 x 8 bytes
		HAL_PCDEx_PMAConfig(&MX_USB_HANDLE_HPCD, 0x00, PCD_SNG_BUF, 0x18);			//EP0 OUT
		HAL_PCDEx_PMAConfig(&MX_USB_HANDLE_HPCD, 0x80, PCD_SNG_BUF, 0x58);			//EP0 IN
		HAL_PCDEx_PMAConfig(&MX_USB_HANDLE_HPCD, CDC_IN_EP, PCD_SNG_BUF, 0xC0);		//CDC data IN (64)
		HAL_PCDEx_PMAConfig(&MX_USB_HANDLE_HPCD, CDC_OUT_EP, PCD_SNG_BUF, 0x110);	//CDC data OUT (64)
		HAL_PCDEx_PMAConfig(&MX_USB_HANDLE_HPCD, CDC_CMD_EP, PCD_SNG_BUF, 0x100);	//CDC command IN (8)
	#endif

	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_DeInit(USBD_HandleTypeDef *pdev)
{
	HAL_PCD_DeInit((PCD_HandleTypeDef *)pdev->pData);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_Start(USBD_HandleTypeDef *pdev)
{
	HAL_PCD_Start((PCD_HandleTypeDef *)pdev->pData);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_Stop(USBD_HandleTypeDef *pdev)
{
	HAL_PCD_Stop((PCD_HandleTypeDef *)pdev->pData);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_OpenEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr, uint8_t ep_type, uint16_t ep_mps)
{
	HAL_PCD_EP_Open((PCD_HandleTypeDef *)pdev->pData, ep_addr, ep_mps, ep_type);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_CloseEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
	HAL_PCD_EP_Close((PCD_HandleTypeDef *)pdev->pData, ep_addr);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_FlushEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
	HAL_PCD_EP_Flush((PCD_HandleTypeDef *)pdev->pData, ep_addr);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_StallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
	HAL_PCD_EP_SetStall((PCD_HandleTypeDef *)pdev->pData, ep_addr);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_ClearStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
	HAL_PCD_EP_ClrStall((PCD_HandleTypeDef *)pdev->pData, ep_addr);
	return USBD_OK;
}

uint8_t USBD_LL_IsStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
	PCD_HandleTypeDef *hpcd = (PCD_HandleTypeDef *)pdev->pData;

	if ((ep_addr & 0x80) == 0x80)
		return hpcd->IN_ep[ep_addr & 0x7F].is_stall;

	return hpcd->OUT_ep[ep_addr & 0x7F].is_stall;
}

USBD_StatusTypeDef USBD_LL_SetUSBAddress(USBD_HandleTypeDef *pdev, uint8_t dev_addr)
{
	HAL_PCD_SetAddress((PCD_HandleTypeDef *)pdev->pData, dev_addr);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_Transmit(USBD_HandleTypeDef *pdev, uint8_t ep_addr, uint8_t *pbuf, uint16_t size)
{
	HAL_PCD_EP_Transmit((PCD_HandleTypeDef *)pdev->pData, ep_addr, pbuf, size);
	return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_PrepareReceive(USBD_HandleTypeDef *pdev, uint8_t ep_addr, uint8_t *pbuf, uint16_t size)
{
	HAL_PCD_EP_Receive((PCD_HandleTypeDef *)pdev->pData, ep_addr, pbuf, size);
	return USBD_OK;
}

uint32_t USBD_LL_GetRxDataSize(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
	return HAL_PCD_EP_GetRxCount((PCD_HandleTypeDef *)pdev->pData, ep_addr);
}

void USBD_LL_Delay(uint32_t Delay)
{
	delay_ms(Delay);
}


/*=====================================================================*\
   CDC class interface  (usbd_cdc_if.c equivalent)
\*=====================================================================*/

#define MX_USB_PACKET_SZ	CDC_DATA_FS_MAX_PACKET_SIZE		//64 bytes

__ALIGN_BEGIN static uint8_t MX_USB_TxBuffer[MX_USB_PACKET_SZ] __ALIGN_END;
__ALIGN_BEGIN static uint8_t MX_USB_RxBuffer[MX_USB_PACKET_SZ] __ALIGN_END;

//Shared between the USB interrupt and the Flowcode API calls
static volatile uint8_t MX_USBSer_RxByteCount = 0;
static volatile uint8_t MX_USBSer_RxPtr = 0;

static int8_t MX_CDC_Init_FS(void);
static int8_t MX_CDC_DeInit_FS(void);
static int8_t MX_CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t MX_CDC_Receive_FS(uint8_t *pbuf, uint32_t *Len);

static USBD_CDC_ItfTypeDef MX_USBD_Interface_fops_FS =
{
	MX_CDC_Init_FS,
	MX_CDC_DeInit_FS,
	MX_CDC_Control_FS,
	MX_CDC_Receive_FS
};

static int8_t MX_CDC_Init_FS(void)
{
	USBD_CDC_SetTxBuffer(&MX_USB_HANDLE_HUSBD, MX_USB_TxBuffer, 0);
	USBD_CDC_SetRxBuffer(&MX_USB_HANDLE_HUSBD, MX_USB_RxBuffer);

	MX_USBSer_RxByteCount = 0;
	MX_USBSer_RxPtr = 0;

	return (USBD_OK);
}

static int8_t MX_CDC_DeInit_FS(void)
{
	return (USBD_OK);
}

static int8_t MX_CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length)
{
	static uint8_t line_coding[7] = {0x80, 0x25, 0x00, 0x00, 0x00, 0x00, 0x08};	//9600,8,N,1
	uint8_t i;

	//Line coding / control line requests are accepted but not acted upon -
	//Flowcode treats the link as a fixed configuration virtual COM port.
	//The line coding is remembered so that terminal programs reading it back are happy.
	if (cmd == CDC_SET_LINE_CODING)
	{
		for (i = 0; i < 7; i++)
			line_coding[i] = pbuf[i];
	}
	else if (cmd == CDC_GET_LINE_CODING)
	{
		for (i = 0; i < 7; i++)
			pbuf[i] = line_coding[i];
	}

	return (USBD_OK);
}

static int8_t MX_CDC_Receive_FS(uint8_t *Buf, uint32_t *Len)
{
	//Called from USB interrupt context when a new packet of data has arrived.
	//Buf == MX_USB_RxBuffer, *Len == number of bytes received.
	//The endpoint is NAKed (flow control) until the packet has been drained.

	MX_USBSer_RxPtr = 0;
	MX_USBSer_RxByteCount = (uint8_t) (*Len);

	if (MX_USBSer_RxByteCount == 0)
		USBD_CDC_ReceivePacket(&MX_USB_HANDLE_HUSBD);

	return (USBD_OK);
}


//Wait for the previous IN transfer to complete - returns 1 if the endpoint is free
static uint8_t MX_CDC_WaitTxFree(void)
{
	MX_UINT16 timeout = 0;
	volatile USBD_CDC_HandleTypeDef *hcdc;

	while (timeout < 32000)
	{
		if (!MX_USB_CONFIGURED)
			return 0;

		hcdc = (volatile USBD_CDC_HandleTypeDef *)MX_USB_HANDLE_HUSBD.pClassData;
		if (hcdc->TxState == 0)
			return 1;

		timeout = timeout + 1;
		delay_us(10);
	}

	return 0;
}

//Queue one packet (0 - 64 bytes). Data is copied into the CDC transmit buffer as
//the transfer completes asynchronously after this function returns.
static uint8_t MX_CDC_Transmit_FS(const uint8_t *Buf, uint16_t Len)
{
	uint16_t i;

	if (!MX_USB_CONFIGURED)
		return (USBD_FAIL);

	if (!MX_CDC_WaitTxFree())
		return (USBD_BUSY);

	for (i = 0; i < Len; i++)
		MX_USB_TxBuffer[i] = Buf[i];

	USBD_CDC_SetTxBuffer(&MX_USB_HANDLE_HUSBD, MX_USB_TxBuffer, Len);
	return USBD_CDC_TransmitPacket(&MX_USB_HANDLE_HUSBD);
}

//Send a block of data split into packets. A transfer ending on a full packet is
//terminated with a zero length packet so the host passes the data on immediately.
static MX_UINT8 MX_CDC_TransmitBlock(const uint8_t *Buf, uint16_t Len)
{
	uint16_t chunk = 0;

	if (!MX_USB_CONFIGURED)
		return (2);		//USB Not Configured

	while (Len)
	{
		chunk = (Len > MX_USB_PACKET_SZ) ? MX_USB_PACKET_SZ : Len;

		if (MX_CDC_Transmit_FS(Buf, chunk) != USBD_OK)
			return (1);		//USB Not Ready

		Buf += chunk;
		Len -= chunk;
	}

	if (chunk == MX_USB_PACKET_SZ)
	{
		if (MX_CDC_Transmit_FS(Buf, 0) != USBD_OK)
			return (1);		//USB Not Ready
	}

	return (0);
}


static MX_UINT8 MX_CDC_DrainRxByte(void)
{
	MX_UINT8 data;

	data = MX_USB_RxBuffer[MX_USBSer_RxPtr];
	MX_USBSer_RxPtr = MX_USBSer_RxPtr + 1;

	if (MX_USBSer_RxPtr >= MX_USBSer_RxByteCount)
	{
		MX_USBSer_RxPtr = 0;
		MX_USBSer_RxByteCount = 0;

		//Buffer has been fully drained - re-arm the endpoint for the next packet
		USBD_CDC_ReceivePacket(&MX_USB_HANDLE_HUSBD);
	}

	return data;
}


/*=====================================================================*\
   Flowcode CAL entry points
\*=====================================================================*/

CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_Initialise_, ())
{
	MX_UINT16 FCL_DELAY_COUNTER = 0;
	MX_UINT8  FCL_INNER = 0;

	MX_USBSer_RxByteCount = 0;
	MX_USBSer_RxPtr = 0;

	USBD_Init(&MX_USB_HANDLE_HUSBD, &MX_USB_FS_Desc, 0);
	USBD_RegisterClass(&MX_USB_HANDLE_HUSBD, &USBD_CDC);
	USBD_CDC_RegisterInterface(&MX_USB_HANDLE_HUSBD, &MX_USBD_Interface_fops_FS);
	USBD_Start(&MX_USB_HANDLE_HUSBD);

	if (MX_USB_SERIAL_ENUM_TOUTEN_X)
	{
		//Wait for USB to startup and enumerate
		while ((!MX_USB_CONFIGURED) && (FCL_DELAY_COUNTER < MX_USB_SERIAL_ENUM_TOUT_X))
		{
			delay_ms(10);
			FCL_INNER = FCL_INNER + 1;

			if (FCL_INNER == 100)
			{
				FCL_DELAY_COUNTER = FCL_DELAY_COUNTER + 1;
				FCL_INNER = 0;
			}
		}

		if (MX_USB_CONFIGURED)
			return 0;

		return 255;
	}
	else
	{
		while (!MX_USB_CONFIGURED);
		return 0;
	}
}



CALFUNCTION(MX_UINT16, FC_CAL_USB_Serial_ReadByte_, (MX_UINT8 timeout_ms))
{
	MX_UINT16 retval = 255;
	MX_UINT8 inner = 0;
	MX_UINT8 FCL_WAIT_FOREVER = 0;

	if (MX_USB_SERIAL_ENUM_RETURN_X)
		retval = 512;

	if (timeout_ms == 0)
	{
		timeout_ms = 1;
		inner = 98;
	}

	if (timeout_ms == 255)
		FCL_WAIT_FOREVER = 1;

	while ((MX_USBSer_RxByteCount == 0) && (timeout_ms > 0))
	{
		inner++;
		delay_us(10);

		if (inner == 100)
		{
			inner = 0;
			if (FCL_WAIT_FOREVER == 0)
				timeout_ms--;
		}
	}

	if (MX_USBSer_RxByteCount)
		retval = MX_CDC_DrainRxByte();

	return retval;
}



CALFUNCTION(void, FC_CAL_USB_Serial_ReadString_, (MX_CHAR *FCR_RETVAL, MX_UINT16 FCRsz_RETVAL, MX_UINT8 timeout_ms, MX_UINT8 FCL_LENGTH))
{
	MX_UINT8 FCL_WAIT_FOREVER = 0;
	MX_UINT16 inner = 0;
	MX_UINT16 idx = 0;

	if (FCRsz_RETVAL == 0)
		return;

	if (timeout_ms == 0)
		timeout_ms = 1;

	if (timeout_ms == 255)
		FCL_WAIT_FOREVER = 1;

	if (FCL_LENGTH >= FCRsz_RETVAL)
		FCL_LENGTH = FCRsz_RETVAL - 1;

	while ((idx < FCL_LENGTH) && (timeout_ms > 0))
	{
		if (MX_USBSer_RxByteCount)
		{
			FCR_RETVAL[idx] = (MX_CHAR) MX_CDC_DrainRxByte();
			idx++;
		}
		else
		{
			inner++;
			delay_us(10);

			if (inner == 100)
			{
				inner = 0;
				if (FCL_WAIT_FOREVER == 0)
					timeout_ms--;
			}
		}
	}

	FCR_RETVAL[idx] = 0;
}



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendByte_, (MX_UINT8 FCL_DATA))
{
	return MX_CDC_TransmitBlock(&FCL_DATA, 1);
}



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendByteArray_, (MX_UINT8 *FCL_DATA, MX_UINT16 FCLsz_DATA, MX_UINT8 FCL_NUMBYTES))
{
	return MX_CDC_TransmitBlock(FCL_DATA, FCL_NUMBYTES);
}



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendString_, (MX_CHAR *FCL_DATA, MX_UINT16 FCLsz_DATA))
{
	MX_UINT16 FCL_LENGTH;

	FCL_LENGTH = FCI_GETLENGTH((MX_STRING)FCL_DATA, FCLsz_DATA);

	return MX_CDC_TransmitBlock((const uint8_t *)FCL_DATA, FCL_LENGTH);
}
