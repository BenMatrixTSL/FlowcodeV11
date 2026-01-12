// CRC: 1CECFE3DB3A1BD5169AEA98AD43ADE6319437863F925F9E81547AF9EE8B896FF158AA2B88EADE3B2F8D60AC91451376496DF31E80C3F23C215B9CA712B919F499A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5A3C342F51D5B46CEC02C8937CF79523AFA8D9A69A9F124510377124905A7359166323F8E80DAC33E04AC24931B345AF739D84B7D77626C92B3ECA78FE91F492B2EF7D337AA2115412B40F791BC236F732C2D21A7CF10EADA549D34A0D5AD11F3B69FC04E484435BDD489D6200BB939E1EA53EB1FC90446FC04789BB7D1BE12C9008FFBF4203128CD
// REVISION: 1.0
// GUID: 5AABDBFF-F586-4279-809C-C2C5309ECECC
// DATE: 08\08\2022
// DIR: FCD\ARM\boards\F746Discovery.h
/**
  ******************************************************************************
  * @file    F746Disco.h 
  * @author  S.K.
  * @version V0.1.0
  * @date    06/11/2016
  * @brief   STM32F746 Discovery LCD header
  ******************************************************************************

  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __F746_DISCO_H
#define __F746_DISCO_H

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_lcd.h"
//#include "stm32746g_discovery_sd.h"
#include "stm32746g_discovery_sdram.h"
#include "stm32746g_discovery_qspi.h"
//#include "stm32f7xx_it.h"

/* FatFs includes component */
//#include "ff_gen_drv.h"
//#include "sd_diskio.h"

/* Macros --------------------------------------------------------------------*/
#ifdef USE_FULL_ASSERT
/* Assert activated */
#define ASSERT(__condition__)                do { if(__condition__) \
                                                   {  assert_failed(__FILE__, __LINE__); \
                                                      while(1);  \
                                                    } \
                                              }while(0)
#else
/* Assert not activated : macro has no effect */
#define ASSERT(__condition__)                  do { if(__condition__) \
                                                   {  ErrorCounter++; \
                                                    } \
                                              }while(0)
#endif /* USE_FULL_ASSERT */

#define RGB565_BYTE_PER_PIXEL     2
#define ARBG8888_BYTE_PER_PIXEL   4

/* Camera have a max resolution of VGA : 640x480 */
#define CAMERA_RES_MAX_X          640
#define CAMERA_RES_MAX_Y          480

/**
  * @brief  LCD FB_StartAddress
  * LCD Frame buffer start address : starts at beginning of SDRAM
  */
#define LCD_FRAME_BUFFER        SDRAM_DEVICE_ADDR
#define LCD_LAYER_SIZE			((uint32_t)(RK043FN48H_WIDTH * RK043FN48H_HEIGHT * ARBG8888_BYTE_PER_PIXEL))
#define LCD_FG_LAYER			((uint32_t)LCD_FRAME_BUFFER)
#define LCD_BG_LAYER			((uint32_t)(LCD_FRAME_BUFFER + LCD_LAYER_SIZE))
#define LTDC_FG					1
#define LTDC_BG					0

/**
  * @brief  Camera frame buffer start address
  * Assuming LCD frame buffer is of size 480x800 and format ARGB8888 (32 bits per pixel).
  */
#define CAMERA_FRAME_BUFFER       ((uint32_t)(LCD_FRAME_BUFFER + (2 * LCD_LAYER_SIZE)))


/**
  * @brief  SDRAM Write read buffer start address after CAM Frame buffer
  * Assuming Camera frame buffer is of size 640x480 and format RGB565 (16 bits per pixel).
  */
#define SDRAM_WRITE_READ_ADDR        ((uint32_t)(CAMERA_FRAME_BUFFER + (CAMERA_RES_MAX_X * CAMERA_RES_MAX_Y * RGB565_BYTE_PER_PIXEL)))

#define SDRAM_WRITE_READ_ADDR_OFFSET ((uint32_t)0x0800)
#define SRAM_WRITE_READ_ADDR_OFFSET  SDRAM_WRITE_READ_ADDR_OFFSET

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void BSP_LCD_DMA2D_IRQHandler(void);

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line);
#endif
#endif
/* __F746_DISCO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
