// CRC: 1CECFE3DB3A1BD5169AEA98AD43ADE63C9DC86690B25D319752E410E43086C747D52CB30E1B7393A68D5C58734250788C224CC8FEEF312C5C951050EA34CC75A14C7C93C31DAFADEA9B11F738DF98E15674DDCDA0FA2D2BEB2ADE4B72D9018626EEF198B2A4744258C889237CF780A0702542BBE951C267401D6DD9855B2544A010F9ABA0FD4D9EAEA4E23355FC2673139087B94BC3FFA5DFB8DD5D41E806EA3402602CD17D9B152549D34A0D5AD11F3438225D5E6C5A12F2E288F801E453AEC6A78909DDF8B94D4C7E9BF2E0A60D235BB3AB4325F399FDA
// REVISION: 1.0
// GUID: AB13F8EB-9BDE-4C51-9544-B09EC0E939D0
// DATE: 12\11\2026
// DIR: FCD\ARM\inc\usbd_conf.h
/*********************************************************************
 *  Flowcode STARM - STM32Cube USB Device Library configuration
 *
 *  File: usbd_conf.h
 *
 *  Required by the ST USB Device Library (usbd_def.h includes it).
 *  Used by CAL\STARM\STARM_CAL_USB_Serial.c which also provides
 *  USBD_static_malloc / USBD_static_free and the USBD_LL_xxx driver
 *  layer (usbd_conf.c equivalent).
 *
 *  This directory is added to the include path by
 *  FCD\ARM\batch\stm32comp.bat.
 *
 * Changelog:
 *
 *  date  | by | description
 * -------+----+-----------------------------------------------------
 * 121126 | BR | Created for the STARM USB Serial CAL
 */

#ifndef __USBD_CONF_H
#define __USBD_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <string.h>

#if defined STM32F0
	#include "stm32f0xx.h"
#elif defined STM32F1
	#include "stm32f1xx.h"
#elif defined STM32F2
	#include "stm32f2xx.h"
#elif defined STM32F3
	#include "stm32f3xx.h"
#elif defined STM32F4
	#include "stm32f4xx.h"
#elif defined STM32F7
	#include "stm32f7xx.h"
#elif defined STM32L0
	#include "stm32l0xx.h"
#elif defined STM32L1
	#include "stm32l1xx.h"
#elif defined STM32L4
	#include "stm32l4xx.h"
#else
	#error "usbd_conf.h: unknown STM32 family"
#endif


#define USBD_MAX_NUM_INTERFACES			1
#define USBD_MAX_NUM_CONFIGURATION		1
#define USBD_MAX_STR_DESC_SIZ			0x100		//Max string descriptor length (126 characters)
#define USBD_SUPPORT_USER_STRING		0
#define USBD_SELF_POWERED				1
#define USBD_LPM_ENABLED				0
#define USBD_DEBUG_LEVEL				0

/* CDC Class Config */
#define USBD_CDC_INTERVAL				1000


/* Memory management - static allocation, see STARM_CAL_USB_Serial.c */
void *USBD_static_malloc(uint32_t size);
void USBD_static_free(void *p);

#define USBD_malloc						USBD_static_malloc
#define USBD_free						USBD_static_free
#define USBD_memset						memset
#define USBD_memcpy						memcpy
#define USBD_Delay						USBD_LL_Delay


/* Debug macros - disabled */
#define USBD_UsrLog(...)
#define USBD_ErrLog(...)
#define USBD_DbgLog(...)


#ifdef __cplusplus
}
#endif

#endif /* __USBD_CONF_H */
