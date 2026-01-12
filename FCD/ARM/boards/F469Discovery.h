// CRC: 1CECFE3DB3A1BD5169AEA98AD43ADE6319437863F925F9E81547AF9EE8B896FFD3A99D108D9CC529CDE5767CC10AEF8D96DF31E80C3F23C215B9CA712B919F499A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF55C740F484C7D2B57DA0E1635E367465AAF4F07D614951653E430221C85C30C67F7786AB7CBAC9B8C8B029C77460D1FA0DDF2079305C70C7CFFF36CEEF8ABE444D22F76C72E57F2195F1C534703E02322470F05DC44C02CEB549D34A0D5AD11F3526515390C49193976204D537751DFD9D32987A57BDB35E1A7E0A38DADB65FFF85A60D01A8F5E6C8
// REVISION: 1.0
// GUID: 2DBE7786-7DEA-4C28-B85B-425EC9B474C7
// DATE: 08\08\2022
// DIR: FCD\ARM\boards\F469Discovery.h
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
#ifndef __F469_DISCO_H
#define __F469_DISCO_H

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stm32469i_discovery.h"
#include "stm32469i_discovery_ts.h"
#include "stm32469i_discovery_lcd.h"
//#include "stm32746g_discovery_sd.h"
#include "stm32469i_discovery_sdram.h"
//#include "stm32469i_discovery_qspi.h"
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


/**
  * @brief  LCD FB_StartAddress
  * LCD Frame buffer start address : starts at beginning of SDRAM
  */
  
#define WVGA_RES_X  800
#define WVGA_RES_Y  480

#define LCD_FRAME_BUFFER		0xC0000000
#define LCD_LAYER_SIZE			((uint32_t)(WVGA_RES_X * WVGA_RES_Y * ARBG8888_BYTE_PER_PIXEL))
#define LCD_FG_LAYER			((uint32_t)LCD_FRAME_BUFFER)
#define LCD_BG_LAYER			((uint32_t)(LCD_FRAME_BUFFER + LCD_LAYER_SIZE))
#define LTDC_FG					1
#define LTDC_BG					0


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
/* __F469_DISCO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
