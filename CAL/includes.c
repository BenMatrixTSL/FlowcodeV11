// CRC: 9127F328264D8FABC87FF80C826F04D0E463E451CD747EFC4B2F8236B78C0C84919322A6129BAB668A1F07FD2640D767265B9B5C83AAC8680C3CAEE8E7DA6987B73F1ADF2AD46F0B80E2966912EBCB9A0835AF06B53641108741CC02A86228770A3A7C70C2F8885D36DCA8B36FC67E1E68BE6FCEF249B64382B5F72235EEE72F94F04968BF60E54AFD352432F208853EF8395F2401ECB9DE549D34A0D5AD11F31C96262D0C51598CF96CEC05A3EC6EA7D3FE065936E79CC3B0330AA6FB05B88105A68DA3CE9026E5
// REVISION: 7.0
// GUID: AF5BA3D1-36BB-4DEE-A530-1F5660353617
// DATE: 01\10\2025
// DIR: CAL\includes.c
/*********************************************************************
 *           Flowcode Peripheral Slot Allocation Header File
 *
 * File: includes.c
 *
 * (c) 2011 Matrix Multimedia Ltd.
 * http://www.matrixmultimedia.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix Multimedia Ltd (the
 * “Company”) for its Flowcode graphical programming language is
 * intended and supplied to you, the Company’s customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
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
 * 160911 | BR | Created
 * 011211 | BR | Converted to new dynamic defines mechanism
 * 280612 | BR | Added new PWM - up to 16 channels
 * 120313 | LM | FC_CAL_xxx defines changed to MX_CAL_xxx
 * 260413 | LM | moved CALFUNCTION defines for case of missing REF1
 * 270521 | LM | Added support for Raspberry Pi Pico (RP2040)
 *
 ****************************************************************/


#if defined MX_MIAC_MODULE_DSP || defined MX_MIAC_MODULE_AVR
	#include "MIAC\MIAC_CAL_API.c"
#endif


#if defined MX_HYDRO
	#include "LIB\libhydrogen-master\hydrogen.c"
#endif


//Sniff to see if any Sockets are being used
#define CALFUNCTION(type, name, args) type CAL_APPEND(name, MX_SOCKET_NUM) args
#ifdef	MX_SOCKET_REF1
  #define MX_SOCKET_NUM 1
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_Socket.c"
  #endif
  #undef MX_SOCKET_NUM
#endif
#ifdef CALFUNCTION
	#undef CALFUNCTION
#endif


#define CALFUNCTION(type, name, args) type CAL_APPEND(name, MX_ADC_NUM) args

//Sniff to see if any ADC1 channels are being used
#ifdef	MX_ADC_REF1
  #define MX_ADC_NUM 1
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_ADC.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_ADC.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_ADC.c"
  #elif defined MX_CAL_PIC32
  	#include "PIC32BIT\PIC32BIT_CAL_ADC.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_ADC.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_ADC.c"
  #elif defined MX_CAL_ARD
  	#include "AVR\AVR_CAL_ADC.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_ADC.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_ADC.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_ADC.c"
  #endif
  #undef MX_ADC_NUM
#endif

//Sniff to see if any ADC2 channels are being used
#ifdef	MX_ADC_REF2
  #define MX_ADC_NUM 2
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_ADC.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_ADC.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_ADC.c"
  #elif defined MX_CAL_PIC32
  	#include "PIC32BIT\PIC32BIT_CAL_ADC.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_ADC.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_ADC.c"
  #elif defined MX_CAL_ARD
  	#include "AVR\AVR_CAL_ADC.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_ADC.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_ADC.c"
  #endif
  #undef MX_ADC_NUM
#endif

//Sniff to see if any ADC2 channels are being used
#ifdef	MX_ADC_REF3
  #define MX_ADC_NUM 3
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_ADC.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_ADC.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_ADC.c"
  #elif defined MX_CAL_PIC32
  	#include "PIC32BIT\PIC32BIT_CAL_ADC.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_ADC.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_ADC.c"
  #elif defined MX_CAL_ARD
  	#include "AVR\AVR_CAL_ADC.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_ADC.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_ADC.c"
  #endif
  #undef MX_ADC_NUM
#endif

#ifdef CALFUNCTION
	#undef CALFUNCTION
#endif



//Sniff to see if any DAC channels are being used
#define CALFUNCTION(type, name, args) type CAL_APPEND(name, MX_DAC_NUM) args
#ifdef	MX_DAC_REF1
  #define MX_DAC_NUM 1
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_PIC32
    //#include "PIC32BIT\PIC32BIT_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_AVR
	//#include "AVR\AVR_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_ARD
	//#include "AVR\AVR_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_ESP32
	#include "ESP\ESP_CAL_DAC.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_DAC.c"
  #elif defined MX_CAL_ARM
	//#include "ARM\ARM_CAL_DAC.c"
  #endif
  #undef MX_DAC_NUM
#endif
#ifdef	MX_DAC_REF2
  #define MX_DAC_NUM 2
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_PIC32
    //#include "PIC32BIT\PIC32BIT_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_AVR
	//#include "AVR\AVR_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_ARD
	//#include "AVR\AVR_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_ESP32
	#include "ESP\ESP_CAL_DAC.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_DAC.c"
  #elif defined MX_CAL_ARM
	//#include "ARM\ARM_CAL_DAC.c"
  #endif
  #undef MX_DAC_NUM
#endif
#ifdef	MX_DAC_REF3
  #define MX_DAC_NUM 3
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_PIC32
    //#include "PIC32BIT\PIC32BIT_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_AVR
	//#include "AVR\AVR_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_ARD
	//#include "AVR\AVR_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_STARM
	#include "STARM\STARM_CAL_DAC.c"
  #elif defined MX_CAL_ARM
	//#include "ARM\ARM_CAL_DAC.c"
  #endif
  #undef MX_DAC_NUM
#endif
#ifdef	MX_DAC_REF4
  #define MX_DAC_NUM 4
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_PIC32
    //#include "PIC32BIT\PIC32BIT_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_AVR
	//#include "AVR\AVR_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_ARD
	//#include "AVR\AVR_CAL_DAC.c"
  #endif
  #ifdef MX_CAL_STARM
	#include "STARM\STARM_CAL_DAC.c"
  #elif defined MX_CAL_ARM
	//#include "ARM\ARM_CAL_DAC.c"
  #endif
  #undef MX_DAC_NUM
#endif
#ifdef CALFUNCTION
	#undef CALFUNCTION
#endif


//Sniff to see if any Internal CAN components are being used (External CAN uses SPI)
#define CALFUNCTION(type, name, args) type CAL_APPEND(name, MX_CAN_NUM) args
#ifdef	MX_CAN_REF1
  #define MX_CAN_NUM 1
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_AVR
	#include "AVR\AVR_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_ARD
	#include "AVR\AVR_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_ESP
  	#include "ESP\ESP_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_STARM
	#include "STARM\STARM_CAL_CAN.c"
  #elif defined MX_CAL_ARM
	#error "Internal CAN not supported on ARM AT91SAM7S devices"
  #endif
  #undef MX_CAN_NUM
#endif
#ifdef	MX_CAN_REF2
  #define MX_CAN_NUM 2
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_AVR
	#include "AVR\AVR_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_ARD
	#include "AVR\AVR_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_ESP
  	#include "ESP\ESP_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_STARM
	#include "STARM\STARM_CAL_CAN.c"
  #elif defined MX_CAL_ARM
	#error "Internal CAN not supported on ARM AT91SAM7S devices"
  #endif
  #undef MX_CAN_NUM
#endif
#ifdef	MX_CAN_REF3
  #define MX_CAN_NUM 3
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_AVR
	#include "AVR\AVR_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_ARD
	#include "AVR\AVR_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_ESP
  	#include "ESP\ESP_CAL_CAN.c"
  #endif
  #ifdef MX_CAL_STARM
	#include "STARM\STARM_CAL_CAN.c"
  #elif defined MX_CAL_ARM
	#error "Internal CAN not supported on ARM AT91SAM7S devices"
  #endif
  #undef MX_CAN_NUM
#endif
#ifdef CALFUNCTION
	#undef CALFUNCTION
#endif


//Sniff to see if any Cap Touch components are being used
#ifdef	MX_CAPTOUCH_REF
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_CAPTOUCH.c"
  #endif
  #ifdef MX_CAL_PIC16
	#error "Cap Touch not currently supported on 16-bit PIC devices"
  #endif
  #ifdef MX_CAL_AVR
	#error "Cap Touch not currently supported on AVR devices"
  #endif
  #ifdef MX_CAL_ARD
	#error "Cap Touch not currently supported on AVR devices"
  #endif
  #ifdef MX_CAL_ARM
	#error "Cap Touch not currently supported on ARM AT91SAM7S devices"
  #endif
#endif


//Sniff to see if any EEPROM memory is being used
#ifdef	MX_EEPROM_REF
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_EEPROM.c"
  #endif
  #ifdef MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_EEPROM.c"
  #endif
  #ifdef MX_CAL_AVR
	#include "AVR\AVR_CAL_EEPROM.c"
  #endif
  #ifdef MX_CAL_ARD
	#include "AVR\AVR_CAL_EEPROM.c"
  #endif
  #ifdef MX_CAL_ARM
	#include "ARM\ARM_CAL_EEPROM.c"
  #endif
  #ifdef MX_CAL_ESP
	#include "ESP\ESP_CAL_EEPROM.c"
  #endif
#endif


//Sniff to see if File being used
#define CALFUNCTION(type, name, args) type CAL_APPEND(name, MX_FILE_NUM) args
#ifdef	MX_FILE_REF1
  #define MX_FILE_NUM 1
  #ifdef MX_CAL_ESP
  	#include "ESP\ESP_CAL_File.c"
  #endif
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_File.c"
  #endif
  #undef MX_FILE_NUM
#endif
#ifdef CALFUNCTION
	#undef CALFUNCTION
#endif


//Sniff to see if any Flash memory is being used
#ifdef	MX_FLASH_REF
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_FLASH.c"
  #endif
  #ifdef MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_FLASH.c"
  #endif
  #ifdef MX_CAL_AVR
	#include "AVR\AVR_CAL_FLASH.c"
  #endif
  #ifdef MX_CAL_ARD
	#include "AVR\AVR_CAL_FLASH.c"
  #endif
  #ifdef MX_CAL_ARM
	#include "ARM\ARM_CAL_FLASH.c"
  #endif
#endif


//Sniff to see if any H-Bridge Channels are being used
#define CALFUNCTION(type, name, args) type CAL_APPEND(name, MX_HBRIDGE_NUM) args
#ifdef	MX_HBRIDGE_REF1
  #define MX_HBRIDGE_NUM 1
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_HBRIDGE.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_HBRIDGE.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_HBRIDGE.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_HBRIDGE.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_HBRIDGE.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_HBRIDGE.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_HBRIDGE.c"
  #elif defined MX_CAL_STARM
    #include "STARM\STARM_CAL_HBRIDGE.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_HBRIDGE.c"
  #endif
  #undef MX_HBRIDGE_NUM
#endif
#ifdef	MX_HBRIDGE_REF2
  #define MX_HBRIDGE_NUM 2
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_HBRIDGE.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_HBRIDGE.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_HBRIDGE.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_HBRIDGE.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_HBRIDGE.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_HBRIDGE.c"
  #elif defined MX_CAL_STARM
    #include "STARM\STARM_CAL_HBRIDGE.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_HBRIDGE.c"
  #endif
  #undef MX_HBRIDGE_NUM
#endif
#ifdef	MX_HBRIDGE_REF3
  #define MX_HBRIDGE_NUM 3
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_HBRIDGE.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_HBRIDGE.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_HBRIDGE.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_HBRIDGE.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_HBRIDGE.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_HBRIDGE.c"
  #elif defined MX_CAL_STARM
    #include "STARM\STARM_CAL_HBRIDGE.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_HBRIDGE.c"
  #endif
  #undef MX_HBRIDGE_NUM
#endif
#ifdef CALFUNCTION
	#undef CALFUNCTION
#endif



//Sniff to see if any I2C Channels are being used
#define CALFUNCTION(type, name, args) type CAL_APPEND(name, MX_I2C_NUM) args
#ifdef	MX_I2C_REF1
  #define MX_I2C_NUM 1
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_I2C.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_I2C.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_I2C.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_I2C.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_I2C.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_STARM
    #include "STARM\STARM_CAL_I2C.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_I2C.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_I2C.c"
  #endif
  #undef MX_I2C_NUM
#endif
#ifdef	MX_I2C_REF2
  #define MX_I2C_NUM 2
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_I2C.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_I2C.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_I2C.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_I2C.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_I2C.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_STARM
    #include "STARM\STARM_CAL_I2C.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_I2C.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_I2C.c"
  #endif
  #undef MX_I2C_NUM
#endif
#ifdef	MX_I2C_REF3
  #define MX_I2C_NUM 3
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_I2C.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_I2C.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_I2C.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_I2C.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_I2C.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_STARM
    #include "STARM\STARM_CAL_I2C.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_I2C.c"
  #endif
  #undef MX_I2C_NUM
#endif
#ifdef	MX_I2C_REF4
  #define MX_I2C_NUM 4
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_I2C.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_I2C.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_I2C.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_I2C.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_I2C.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_STARM
    #include "STARM\STARM_CAL_I2C.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_I2C.c"
  #endif
  #undef MX_I2C_NUM
#endif
#ifdef	MX_I2C_REF5
  #define MX_I2C_NUM 5
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_I2C.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_I2C.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_I2C.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_I2C.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_I2C.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_STARM
    #include "STARM\STARM_CAL_I2C.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_I2C.c"
  #endif
  #undef MX_I2C_NUM
#endif
#ifdef	MX_I2C_REF6
  #define MX_I2C_NUM 6
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_I2C.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_I2C.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_I2C.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_I2C.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_I2C.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_STARM
    #include "STARM\STARM_CAL_I2C.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_I2C.c"
  #endif
  #undef MX_I2C_NUM
#endif
#ifdef	MX_I2C_REF7
  #define MX_I2C_NUM 7
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_I2C.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_I2C.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_I2C.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_I2C.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_I2C.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_STARM
    #include "STARM\STARM_CAL_I2C.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_I2C.c"
  #endif
  #undef MX_I2C_NUM
#endif
#ifdef	MX_I2C_REF8
  #define MX_I2C_NUM 8
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_I2C.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_I2C.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_I2C.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_I2C.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_I2C.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_STARM
    #include "STARM\STARM_CAL_I2C.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_I2C.c"
  #endif
  #undef MX_I2C_NUM
#endif
#ifdef	MX_I2C_REF9
  #define MX_I2C_NUM 9
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_I2C.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_I2C.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_I2C.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_I2C.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_I2C.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_STARM
    #include "STARM\STARM_CAL_I2C.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_I2C.c"
  #endif
  #undef MX_I2C_NUM
#endif
#ifdef	MX_I2C_REF10
  #define MX_I2C_NUM 10
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_I2C.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_I2C.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_I2C.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_I2C.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_I2C.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_I2C.c"
  #elif defined MX_CAL_STARM
    #include "STARM\STARM_CAL_I2C.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_I2C.c"
  #endif
  #undef MX_I2C_NUM
#endif
#ifdef CALFUNCTION
	#undef CALFUNCTION
#endif


//Sniff to see if any I2S Channels are being used
#define CALFUNCTION(type, name, args) type CAL_APPEND(name, MX_I2S_NUM) args
#ifdef	MX_I2S_REF1
  #define MX_I2S_NUM 1
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_I2S.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_I2S.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_I2S.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_I2S.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_I2S.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_I2S.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_I2S.c"
  #elif defined MX_CAL_STARM
    #include "STARM\STARM_CAL_I2S.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_I2S.c"
  #endif
  #undef MX_I2S_NUM
#endif
#ifdef	MX_I2S_REF2
  #define MX_I2S_NUM 2
  #if defined MX_CAL_RPI
	#include "RPI\RPI_CAL_I2S.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_I2S.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_I2S.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_I2S.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_I2S.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_I2S.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_I2S.c"
  #elif defined MX_CAL_STARM
    #include "STARM\STARM_CAL_I2S.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_I2S.c"
  #endif
  #undef MX_I2S_NUM
#endif
#ifdef CALFUNCTION
	#undef CALFUNCTION
#endif


//Sniff to see if any PWM channels are being used
#define CALFUNCTION(type, name, args) type CAL_APPEND(name, MX_PWM_NUM) args
#ifdef	MX_PWM_REF1
  #define MX_PWM_NUM 1
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif

#ifdef	MX_PWM_REF2
  #define MX_PWM_NUM 2
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif

#ifdef	MX_PWM_REF3
  #define MX_PWM_NUM 3
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif
#ifdef	MX_PWM_REF4
  #define MX_PWM_NUM 4
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif
#ifdef	MX_PWM_REF5
  #define MX_PWM_NUM 5
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif
#ifdef	MX_PWM_REF6
  #define MX_PWM_NUM 6
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif
#ifdef	MX_PWM_REF7
  #define MX_PWM_NUM 7
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif
#ifdef	MX_PWM_REF8
  #define MX_PWM_NUM 8
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif
#ifdef	MX_PWM_REF9
  #define MX_PWM_NUM 9
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif
#ifdef	MX_PWM_REF10
  #define MX_PWM_NUM 10
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif
#ifdef	MX_PWM_REF11
  #define MX_PWM_NUM 11
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif
#ifdef	MX_PWM_REF12
  #define MX_PWM_NUM 12
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif
#ifdef	MX_PWM_REF13
  #define MX_PWM_NUM 13
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif
#ifdef	MX_PWM_REF14
  #define MX_PWM_NUM 14
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif
#ifdef	MX_PWM_REF15
  #define MX_PWM_NUM 15
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif
#ifdef	MX_PWM_REF16
  #define MX_PWM_NUM 16
  #if   defined MX_CAL_RPI
	#include "RPI\RPI_CAL_PWM.c"
  #elif defined MX_CAL_PIC
	#include "PIC\PIC_CAL_PWM.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_PWM.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_PWM.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_PWM.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_PWM.c"
  #elif defined MX_CAL_ESP32
    #include "ESP\ESP_CAL_PWM.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_PWM.c"
  #endif
  #undef MX_PWM_NUM
#endif
#ifdef CALFUNCTION
	#undef CALFUNCTION
#endif



//Sniff to see if any RMT Channels are being used
#define CALFUNCTION(type, name, args) type CAL_APPEND(name, MX_RMT_NUM) args
#ifdef	MX_RMT_REF1
  #define MX_RMT_NUM 1
  #include "ESP\ESP_CAL_RMT.c"
  #undef MX_RMT_NUM
#endif
#ifdef	MX_RMT_REF2
  #define MX_RMT_NUM 2
  #include "ESP\ESP_CAL_RMT.c"
  #undef MX_RMT_NUM
#endif
#ifdef	MX_RMT_REF3
  #define MX_RMT_NUM 3
  #include "ESP\ESP_CAL_RMT.c"
  #undef MX_RMT_NUM
#endif
#ifdef	MX_RMT_REF4
  #define MX_RMT_NUM 4
  #include "ESP\ESP_CAL_RMT.c"
  #undef MX_RMT_NUM
#endif
#ifdef	MX_RMT_REF5
  #define MX_RMT_NUM 5
  #include "ESP\ESP_CAL_RMT.c"
  #undef MX_RMT_NUM
#endif
#ifdef	MX_RMT_REF6
  #define MX_RMT_NUM 6
  #include "ESP\ESP_CAL_RMT.c"
  #undef MX_RMT_NUM
#endif
#ifdef	MX_RMT_REF7
  #define MX_RMT_NUM 7
  #include "ESP\ESP_CAL_RMT.c"
  #undef MX_RMT_NUM
#endif
#ifdef	MX_RMT_REF8
  #define MX_RMT_NUM 8
  #include "ESP\ESP_CAL_RMT.c"
  #undef MX_RMT_NUM
#endif
#ifdef CALFUNCTION
	#undef CALFUNCTION
#endif




//Sniff to see if any RTC peripherals are being used
#define CALFUNCTION(type, name, args) type CAL_APPEND(name, MX_RTC_NUM) args
#ifdef	MX_RTC_INTERNAL
  #define MX_RTC_NUM 1
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_RTC.c"
  #endif
  #ifdef MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_RTC.c"
  #endif
  #ifdef MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_RTC.c"
  #endif
  #ifdef MX_CAL_AVR
	//#include "AVR\AVR_CAL_RTC.c"
  #endif
  #ifdef MX_CAL_ARD
	//#include "AVR\AVR_CAL_RTC.c"
  #endif
  #ifdef MX_CAL_STARM
	#include "STARM\STARM_CAL_RTC.c"
  #elif defined MX_CAL_ARM
	//#include "ARM\ARM_CAL_RTC.c"
  #endif
  #undef MX_RTC_NUM
#endif
#ifdef CALFUNCTION
	#undef CALFUNCTION
#endif




//Sniff to see if any SPI channels are being used
#define CALFUNCTION(type, name, args) type CAL_APPEND(name, MX_SPI_NUM) args
#ifdef	MX_SPI_REF1
  #define MX_SPI_NUM 1
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_SPI.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_SPI.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_SPI.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_SPI.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_SPI.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_SPI.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_SPI.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_SPI.c"
  #endif
  #undef MX_SPI_NUM
#endif
#ifdef	MX_SPI_REF2
  #define MX_SPI_NUM 2
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_SPI.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_SPI.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_SPI.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_SPI.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_SPI.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_SPI.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_SPI.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_SPI.c"
  #endif
  #undef MX_SPI_NUM
#endif
#ifdef	MX_SPI_REF3
  #define MX_SPI_NUM 3
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_SPI.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_SPI.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_SPI.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_SPI.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_SPI.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_SPI.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_SPI.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_SPI.c"
  #endif
  #undef MX_SPI_NUM
#endif
#ifdef	MX_SPI_REF4
  #define MX_SPI_NUM 4
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_SPI.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_SPI.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_SPI.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_SPI.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_SPI.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_SPI.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_SPI.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_SPI.c"
  #endif
  #undef MX_SPI_NUM
#endif
#ifdef	MX_SPI_REF5
  #define MX_SPI_NUM 5
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_SPI.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_SPI.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_SPI.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_SPI.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_SPI.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_SPI.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_SPI.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_SPI.c"
  #endif
  #undef MX_SPI_NUM
#endif
#ifdef	MX_SPI_REF6
  #define MX_SPI_NUM 6
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_SPI.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_SPI.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_SPI.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_SPI.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_SPI.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_SPI.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_SPI.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_SPI.c"
  #endif
  #undef MX_SPI_NUM
#endif
#ifdef	MX_SPI_REF7
  #define MX_SPI_NUM 7
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_SPI.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_SPI.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_SPI.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_SPI.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_SPI.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_SPI.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_SPI.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_SPI.c"
  #endif
  #undef MX_SPI_NUM
#endif
#ifdef	MX_SPI_REF8
  #define MX_SPI_NUM 8
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_SPI.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_SPI.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_SPI.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_SPI.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_SPI.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_SPI.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_SPI.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_SPI.c"
  #endif
  #undef MX_SPI_NUM
#endif
#ifdef	MX_SPI_REF9
  #define MX_SPI_NUM 9
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_SPI.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_SPI.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_SPI.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_SPI.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_SPI.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_SPI.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_SPI.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_SPI.c"
  #endif
  #undef MX_SPI_NUM
#endif
#ifdef	MX_SPI_REF10
  #define MX_SPI_NUM 10
  #ifdef MX_CAL_PIC
	#include "PIC\PIC_CAL_SPI.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_SPI.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_SPI.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_SPI.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_SPI.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_SPI.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_SPI.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_SPI.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_SPI.c"
  #endif
  #undef MX_SPI_NUM
#endif
#ifdef CALFUNCTION
	#undef CALFUNCTION
#endif


//Sniff to see if any UARTS are being used
#define CALFUNCTION(type, name, args) type CAL_APPEND(name, MX_UART_NUM) args
#ifdef	MX_UART_REF1
  #define MX_UART_NUM 1
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef	MX_UART_REF2
  #define MX_UART_NUM 2
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #elif defined MX_CAL_PICO
	#include "PICO\PICO_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef	MX_UART_REF3
  #define MX_UART_NUM 3
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef	MX_UART_REF4
  #define MX_UART_NUM 4
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef	MX_UART_REF5
  #define MX_UART_NUM 5
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef	MX_UART_REF6
  #define MX_UART_NUM 6
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef	MX_UART_REF7
  #define MX_UART_NUM 7
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef	MX_UART_REF8
  #define MX_UART_NUM 8
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef	MX_UART_REF9
  #define MX_UART_NUM 9
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef	MX_UART_REF10
  #define MX_UART_NUM 10
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef	MX_UART_REF11
  #define MX_UART_NUM 11
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef	MX_UART_REF12
  #define MX_UART_NUM 12
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef	MX_UART_REF13
  #define MX_UART_NUM 13
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef	MX_UART_REF14
  #define MX_UART_NUM 14
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef	MX_UART_REF15
  #define MX_UART_NUM 15
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef	MX_UART_REF16
  #define MX_UART_NUM 16
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_UART.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_UART.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_UART.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_UART.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_UART.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_UART.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_UART.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_UART.c"
  #endif
  #undef MX_UART_NUM
#endif
#ifdef CALFUNCTION
	#undef CALFUNCTION
#endif


//Sniff to see if USB Serial being used
#define CALFUNCTION(type, name, args) type CAL_APPEND(name, MX_USB_SERIAL_NUM) args
#ifdef	MX_USB_SERIAL_REF1
  #define MX_USB_SERIAL_NUM 1
  #if defined MX_CAL_PIC
  	#include "PIC\PIC_CAL_USB_Serial.c"
  #elif defined MX_CAL_PIC16
  	#include "PIC16BIT\PIC16BIT_CAL_USB_Serial.c"
  #elif defined MX_CAL_PIC32
  	#include "PIC32BIT\PIC32BIT_CAL_USB_Serial.c"
  #elif defined MX_CAL_AVR
  	#include "AVR\AVR_CAL_USB_Serial.c"
  #elif defined MX_CAL_ARD
  	#include "AVR\AVR_CAL_USB_Serial.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_USB_Serial.c"
  #else
  	#error "Sorry USB Serial not yet supported by your target microcontroller family"
  #endif
  #undef MX_USB_SERIAL_NUM
#endif
#ifdef CALFUNCTION
	#undef CALFUNCTION
#endif



#ifdef USE_FLOWCODE_ICD3		//ICD3 SPECIFICS
  #if defined MX_CAL_PIC
	#include "PIC\PIC_CAL_ICD3.c"
  #elif defined MX_CAL_PIC16
	#include "PIC16BIT\PIC16BIT_CAL_ICD3.c"
  #elif defined MX_CAL_PIC32
    #include "PIC32BIT\PIC32BIT_CAL_ICD3.c"
  #elif defined MX_CAL_ESP32
  	#include "ESP\ESP_CAL_ICD3.c"
  #elif defined MX_CAL_AVR
	#include "AVR\AVR_CAL_ICD3.c"
  #elif defined MX_CAL_ARD
	#include "AVR\AVR_CAL_ICD3.c"
  #elif defined MX_CAL_RPI
	#include "RPI\RPI_CAL_ICD3.c"
  #elif defined MX_CAL_STARM
	#include "STARM\STARM_CAL_ICD3.c"
  #elif defined MX_CAL_ARM
	#include "ARM\ARM_CAL_ICD3.c"
  #endif
#endif


#if defined MX_CAL_ESP32
	#if defined MX_CAL_ESP32_WIFI
		#include "ESP\ESP_CAL_WIFI.c"
	#endif
	#if defined MX_CAL_ESP32_BT_SPP
		#include "ESP\ESP_CAL_BT_SPP.c"
	#endif
	#if defined MX_CAL_ESP32_BLE_GATT_SPP_SERVER
		#include "ESP\ESP_CAL_BLE_SPP_Server.c"
	#endif
	#if defined MX_CAL_ESP32_BLE_GATT_SPP_CLIENT
		#include "ESP\ESP_CAL_BLE_SPP_Client.c"
	#endif
#endif


#ifdef CALFUNCTION
	#undef CALFUNCTION
#endif

