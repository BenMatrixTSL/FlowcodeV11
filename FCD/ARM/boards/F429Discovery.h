// CRC: 1CECFE3DB3A1BD5169AEA98AD43ADE6319437863F925F9E81547AF9EE8B896FFF993F8B65A129F2C31DD8103D245E21996DF31E80C3F23C215B9CA712B919F499A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5F0B737D336A7E452E4FD88F4CD3FF10260635BBB446D6B22843CB79770EA7F4B5C9E2507DF6D6D1A9CD8C50639B67EBD9A2C2B310F31E3A662C3E977F4E5B8AE7A779D4B62E67514FF971700AEA1858ABC2DAB1519A12067549D34A0D5AD11F370FB9A2FF57CE828CEAF74258DECB75D99274AA7F828C12EFFF40AFCB70232C7C058EE1ADCF61339
// REVISION: 1.0
// GUID: 196E4246-A107-438F-8BE6-4FFDEA504C39
// DATE: 08\08\2022
// DIR: FCD\ARM\boards\F429Discovery.h
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
#ifndef __F429_DISCO_H
#define __F429_DISCO_H

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_ts.h"
#include "stm32f429i_discovery_lcd.h"
//#include "stm32746g_discovery_sd.h"
#include "stm32f429i_discovery_sdram.h"
//#include "stm32469i_discovery_qspi.h"
//#include "stm32f7xx_it.h"


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
  
//#define WVGA_RES_X  800
//#define WVGA_RES_Y  480

//#define LCD_FRAME_BUFFER		0xC0000000
//#define LCD_LAYER_SIZE			((uint32_t)(240 * 320 * ARBG8888_BYTE_PER_PIXEL))
#define LCD_LAYER_SIZE			((uint32_t)(0x50000))
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
/* __F429_DISCO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
