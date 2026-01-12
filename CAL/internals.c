// CRC: FB488FE5146BF18329DE6087A4DBA5DAC9BF3CA2F3A7D21809098ED5D52053925FC36BB60D5779D524F8CD3FDC3D2E448940AE31AE32EB4A0C3CAEE8E7DA6987702F11E1D05F6D6D19474E981E53BD91CB47F9F64CCAA3C5954AB4A3E8F7CF751B14331D9B1D910F0B039C0769D58835DF0D8652BE620E706764A57C1E89AF33CD361746D2B8C8B40CF13FDBF01E44D16F6E34CEACF9C8EA549D34A0D5AD11F37867C77F0A1D0C7F9B4FA8B739CC76B72A696FC2D039E19FBB7835FE546B805B7544DA781CA69696
// REVISION: 9.0
// GUID: 7DE22287-7BE1-4B7E-BE2B-9E821B08BBC5
// DATE: 29\09\2025
// DIR: CAL\internals.c
/*********************************************************************
 *                  Flowcode Internals Header File
 *
 * File: internals.h
 *
 * (c) 2009 Matrix Multimedia Ltd.
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
 * 010107 | ST | Created
 * 010108 | SK | Edited for ICD Operation
 * 031108 | BR | Edited for integration with PPP
 * 130309 | BR | Added Floating point, Hex and Decimal String Coversion Functions
 * 160309 | BR | Added ICD Port Definitions
 * 160309 | BR | Added Watchdog Delay routines
 * 090409 | BR | Fixed minor definitions bug
 * 170409 | BR | Optimised Floating / String conversions
 * 210509 | BR | Fixed ICD Stop and wait functionality
 * 110809 | BR | Changed the amount of delay in the watchdog ms delay routine
 * 160909 | BR | Added BoostC and HiTECH definitions
 * 290909 | BR | Altered the Test_bit function and ICD arrays for HITECH
 * 161009 | BR | Added a missing semi colon and added the math.h library for 16F devices
 * 221009 | BR | Removed the FCI_TMP_STR and FCI_TMP_INT variables
 * 101209 | BR | Altered timeout val and in <dbg_hold> routine got rid of initial delay and comms now wait forever
 * 181209 | BR | Edited reset function for use with the HITECH compiler.
 * 230210 | BR | Fixed a bug with multiple string concats requiring surplus variables.
 * 230710 | BR | Fixed an overflow bug in the Float to string and string to int functions
 * 270511 | ST | Added CAN fucntions for the MIAC_SYSTEM (from SK)
 * 020611 | BR | Disabled ICD functions from running when an interrupt is active
 * 220611 | BR | Modified the watchdog delays to try to provide better delay accuracy
 * 300611 | SK | Added MIAC Add-on Float Union Code
 * 110711 | SK | Duplicated MIAC I/O Functions - System Components
 * 010911 | BR | Moved the majority of the internals code into the CAL C files
 * 270912 | BR | Mod to PIC16BIT test bit function to allow it to work in 16-bit registers
 * 210313 | JW | Added v6 defines to get code working - may need to be done more elegantly in future
 * 110713 | BR | Added FCV_PRECISION definition to allow float to string function to work correctly
 * 250913 | LM | Removed FCP_GET/FCP_SET macro defs
 * 130819 | ST | Removed creation of FCI_TMP_STR[20] - this is now done inline in relevant string calculations
 * 130819 | ST | Added MX_MAX_TMPSTR_SIZE definition for size of temporary strings (this can be overridden in FCD or by Flowcode)
 * 270521 | LM | Added support for Raspberry Pi Pico (RP2040)
 *
 ********************************************************************/



#ifndef internals_h
#define internals_h

	#define CAL_APD(a, b) 		a##b
	#define CAL_APPEND(a, b) 	CAL_APD(a, b)

	#ifndef MX_MAX_TMPSTR_SIZE
		#define MX_MAX_TMPSTR_SIZE (20)
	#endif

	//BR 23/02/10 - These are needed by multiple concat statements?
	//However 10F devices could not allocate enough memory to create array
	#if !defined(MX_10F_TRIS) && !defined(MX_16F5x_TRIS)
		int FCI_TMP_INT;
	#else
		#warning "Temporary integer variable not defined to save on limited RAM space on your current target device"
	#endif

	//Code for variable manager port code
	#ifndef FCP_USE_TRIS
	  #define FCP_USE_TRIS 1
	#endif

	//Code for float to string
	#ifndef FCV_PRECISION
	  #define FCV_PRECISION 6
	#endif

	#ifdef MX_CAL_RPI

		#include <stdio.h>
		#include <stdarg.h>
		#include <stdint.h>
		#include <stdlib.h>
		#include <ctype.h>
		#include <poll.h>
		#include <unistd.h>
		#include <errno.h>
		#include <string.h>
		#include <time.h>
		#include <fcntl.h>
		#include <pthread.h>
		#include <sys/time.h>
		#include <sys/mman.h>
		#include <sys/stat.h>
		#include <sys/wait.h>
		#include <sys/ioctl.h>
		#include <asm/ioctl.h>
		#include <math.h>

		#include "RPI\RPI_CAL_TypeDefs.c"	//Variable Type Definitions

		#define ROMARRAY_S				const MX_UINT8
		#define ROMARRAY_(t)			const t
		#define ROMARRAY_E				[]

	    #define st_bit(var,bitno) 		CAL_APPEND(var, bits.bitno) = 1
		#define cr_bit(var,bitno) 		CAL_APPEND(var, bits.bitno) = 0
		#define ld_bit(var,bitno,val) 	CAL_APPEND(var, bits.bitno) = (val)?1:0
		#define ts_bit(var,bitno) 		(CAL_APPEND(var, bits.bitno))

		#define set_bit(var,bitno) 		var |= (1 << bitno)
		#define clear_bit(var,bitno) 	var &= ~(1 << bitno)
		#define test_bit(var,bitno) 	(var & (1 << bitno))

		#include "RPI\RPI_CAL_IO.c"			//I/O Definitions and Functions XC8
		#include "RPI\RPI_CAL_Delay.c"	//Delay Definitions
		#include "RPI\RPI_CAL_String.c"	//String Definitions
		#include "RPI\RPI_CAL_Float.c"	//Float Definitions

		#ifdef USE_FLOWCODE_ICD			//ICD SPECIFICS
		    extern unsigned char dbg_mode;
			//#include "RPI\PIC_CAL_ICD.c"
		#endif
		#ifdef USE_FLOWCODE_ICD2		//ICD2 SPECIFICS
		    extern unsigned char dbg_mode;
			#include "RPI\RPI_CAL_ICD2.c"
		#endif
		#ifdef USE_FLOWCODE_ICD3		//ICD3 SPECIFICS
			#include "RPI\RPI_CAL_ICD3.c"
		#endif

	#endif

	#ifdef MX_CAL_PIC

		#if 0		//Disabled
			#if (FCP_USE_TRIS == 1)
				#define FCP_GET(p, m, b) FC_CAL_Port_In_DDR__x((&FCP_PORT_##p), (&FCP_TRIS_##p), (m), (b)) 	/* Gets the value of a port variable */
				#define FCP_SET(p, m, b, v) clear_bit(FCP_TRIS_##p, b); if (v) set_bit(FCP_LAT_##p, b); else clear_bit(FCP_LAT_##p, b);
			#else
				#define FCP_GET(p, m, b) test_bit(FCP_PORT_##p, b); 										/* Gets the value of a port variable */
				#define FCP_SET(p, m, b, v) if (v) set_bit(FCP_LAT_##p, b); else clear_bit(FCP_LAT_##p, b); /* Sets the value of a port variable */
			#endif
		#endif

		#include "PIC\PIC_CAL_TypeDefs.c"	//Variable Type Definitions

		/******************** XC8 SPECIFICS *****************/
        #define _XTAL_FREQ 				MX_CLK_SPEED
        #define MX_INTERRUPT_MACRO		interrupt myisr
		#define MX_CLEAR_WATCHDOG		CLRWDT()

		#define ROMARRAY_S				const MX_UINT8
		#define ROMARRAY_(t)			const t
		#define ROMARRAY_E				[]

	    #define st_bit(var,bitno) 		CAL_APPEND(var, bits.bitno) = 1
		#define cr_bit(var,bitno) 		CAL_APPEND(var, bits.bitno) = 0
		#define ld_bit(var,bitno,val) 	CAL_APPEND(var, bits.bitno) = (val)?1:0
		#define ts_bit(var,bitno) 		(CAL_APPEND(var, bits.bitno))

		#define set_bit(var,bitno) 		var |= (1 << bitno)
		#define clear_bit(var,bitno) 	var &= ~(1 << bitno)
		#define test_bit(var,bitno) 	(var & (1 << bitno))

		#define true					1
		#define false					0

		#include "PIC\PIC_CAL_IO.c"			//I/O Definitions and Functions XC8
		#include "PIC\PIC_CAL_Delay.c"	//Delay Definitions


		#ifndef MX_NO_STRING
			#include "PIC\PIC_CAL_String.c"	//String Definitions
		#endif

		#ifndef MX_NO_FLOAT
			#include "PIC\PIC_CAL_Float.c"	//Float Definitions
		#endif

		#ifdef MX_MIAC_SYSTEM		//Automatic CAN implementation
			#include "PIC\PIC_CAL_MIAC_SYSTEM.c"
		#endif

		#ifdef USE_FLOWCODE_ICD			//ICD SPECIFICS
		    extern unsigned char dbg_mode;
			#include "PIC\PIC_CAL_ICD.c"
		#endif
		#ifdef USE_FLOWCODE_ICD2		//ICD2 SPECIFICS
		    extern unsigned char dbg_mode;
			#include "PIC\PIC_CAL_ICD2.c"
		#endif
		#ifdef USE_FLOWCODE_ICD3		//ICD3 SPECIFICS
			//ICD3.c handled in includes to allow it to come after CAL function defines
			#include "PIC\PIC_CAL_ICD3.h"
		#endif
	#endif


	#ifdef MX_CAL_PIC16

		#if 0		//Disabled
			#if (FCP_USE_TRIS == 1)
				#define FCP_GET(p, m, b) FC_CAL_Port_In_DDR__x((&FCP_PORT_##p), (&FCP_TRIS_##p), (m), (b)) /* Gets the value of a port variable */
				#define FCP_SET(p, m, b, v) FC_CAL_Port_Out_DDR__x((&FCP_PORT_##p), (&FCP_TRIS_##p), (m), (v) << (b)) /* Sets the value of a port variable */
			#else
				#define FCP_GET(p, m, b) FC_CAL_Port_In__x((&FCP_PORT_##p), (m), (b)) /* Gets the value of a port variable */
				#define FCP_SET(p, m, b, v) FC_CAL_Port_Out__x((&FCP_PORT_##p), (m), (v) << (b)) /* Sets the value of a port variable */
			#endif
		#endif

		#ifndef MX_CLKS_PER_INST
			#define MX_CLKS_PER_INST 2
		#endif

		#include "PIC16BIT\PIC16BIT_CAL_TypeDefs.c"	//Variable Type Definitions

		#define MX_CLEAR_WATCHDOG		asm("clrwdt")

		#define MX_Fosc 	MX_CLK_SPEED

		#define set_bit(var,bitno) 		var |= (1 << bitno)
		#define clear_bit(var,bitno) 	var &= ~(1 << bitno)
		#define test_bit(var, bitno)    (var & (1 << bitno))

		#define cr_bit					clear_bit
		#define st_bit					set_bit
		#define ts_bit					test_bit

		#define ROMARRAY_S				const MX_UINT8
		#define ROMARRAY_(t)			const t
		#define ROMARRAY_E				[]

		#include "PIC16BIT\PIC16BIT_CAL_IO.c"		//I/O Definitions and Functions
		#include "PIC16BIT\PIC16BIT_CAL_Delay.c"	//Delay Definitions
		#include "PIC16BIT\PIC16BIT_CAL_String.c"	//String Definitions
		#include "PIC16BIT\PIC16BIT_CAL_Float.c"	//Float Definitions

		#ifdef MX_MIAC_SYSTEM		//Automatic CAN implementation
			#include "MIAC\MIAC_CAL_SYSTEM.c"
		#endif

		#ifdef USE_FLOWCODE_ICD			//ICD SPECIFICS
			#include "PIC16BIT\PIC16BIT_CAL_ICD.c"
		#endif
		#ifdef USE_FLOWCODE_ICD2		//ICD2 SPECIFICS
			#include "PIC16BIT\PIC16BIT_CAL_ICD2.c"
		#endif
		#ifdef USE_FLOWCODE_ICD3		//ICD3 SPECIFICS
			//ICD3.c handled in includes to allow it to come after CAL function defines
			#include "PIC16BIT\PIC16BIT_CAL_ICD3.h"
		#endif

	#endif


	#ifdef MX_CAL_PIC32
		#if 0
			#if (FCP_USE_TRIS == 1)
				#define FCP_GET(p, m, b) FC_CAL_Port_In_DDR__x((&FCP_PORT_##p), (&FCP_TRIS_##p), (m), (b)) /* Gets the value of a port variable */
				#define FCP_SET(p, m, b, v) FC_CAL_Port_Out_DDR__x((&FCP_PORT_##p), (&FCP_TRIS_##p), (m), (v) << (b)) /* Sets the value of a port variable */
			#else
				#define FCP_GET(p, m, b) FC_CAL_Port_In__x((&FCP_PORT_##p), (m), (b)) /* Gets the value of a port variable */
				#define FCP_SET(p, m, b, v) FC_CAL_Port_Out__x((&FCP_PORT_##p), (m), (v) << (b)) /* Sets the value of a port variable */
			#endif
		#endif

		#ifndef MX_CLKS_PER_INST
			#define MX_CLKS_PER_INST 2
		#endif

		#include "PIC32BIT\PIC32BIT_CAL_TypeDefs.c" //Variable Type Definitions

		#ifdef MX_PIC32_MM
			#define MX_CLEAR_WATCHDOG			WDTCONbits.WDTCLRKEY = 0x5743
		#else
			#ifdef _WDTCON_WDTCLRKEY0_MASK
				#define MX_CLEAR_WATCHDOG       WDTCONSET = _WDTCON_WDTCLRKEY0_MASK
			#else
			    #ifdef _WDTCON_WDTCLR_MASK
					#define MX_CLEAR_WATCHDOG       WDTCONSET = _WDTCON_WDTCLR_MASK
				#else
					#ifdef _WDTCON_WDTCLRKEY_MASK
						#define MX_CLEAR_WATCHDOG       WDTCONSET = _WDTCON_WDTCLRKEY_MASK
					#endif
				#endif
			#endif
		#endif

		typedef volatile uint32_t SFR_TYPE;

		#define _SFR_WRITE(reg,val)  		( *((SFR_TYPE *)(reg))  =  (val) )
		#define _SFR_READ(reg)       		( *((SFR_TYPE *)(reg)) )
		#define _SFR_BIT_READ(reg,pos)      (  ( ( *((SFR_TYPE *)(reg)) )&(1<<(pos)) ) ? 1 : 0  )
		#define _SFR_BIT_SET(reg,pos)       ( *((SFR_TYPE *)((reg)+(2))) = 1<<(pos) )
		#define _SFR_BIT_CLEAR(reg,pos)     ( *((SFR_TYPE *)((reg)+(1))) = 1<<(pos) )

		#ifdef MX_MZ_MODE
			#define MX_Fosc          MX_CLK_SPEED*4
		#else
			#define MX_Fosc          MX_CLK_SPEED*2
		#endif

		#define set_bit(var,bitno)      var |= (1 << bitno)
		#define clear_bit(var,bitno)    var &= ~(1 << bitno)
		#define test_bit(var, bitno)    (var & (1 << bitno))

		#define cr_bit                                                    clear_bit
		#define st_bit                                                    set_bit
		#define ts_bit                                                    test_bit

		#define ROMARRAY_S                           const MX_UINT8
		#define ROMARRAY_(t)                         const t
		#define ROMARRAY_E                           []

		#include "PIC32BIT\PIC32BIT_CAL_IO.c"             //I/O Definitions and Functions
		#include "PIC32BIT\PIC32BIT_CAL_Delay.c"       //Delay Definitions
		#include "PIC32BIT\PIC32BIT_CAL_String.c"       //String Definitions
		#include "PIC32BIT\PIC32BIT_CAL_Float.c"        //Float Definitions

		#ifdef USE_FLOWCODE_ICD                            //ICD SPECIFICS
			#include "PIC32BIT\PIC32BIT_CAL_ICD.c"
		#endif
		#ifdef USE_FLOWCODE_ICD2              //ICD2 SPECIFICS
			#include "PIC32BIT\PIC32BIT_CAL_ICD2.c"
		#endif
		#ifdef USE_FLOWCODE_ICD3		//ICD3 SPECIFICS
			//ICD3.c handled in includes to allow it to come after CAL function defines
			#include "PIC32BIT\PIC32BIT_CAL_ICD3.h"
		#endif

	#endif



	#ifdef MX_CAL_AVR

		#if 0		//Disabled
			#if (FCP_USE_TRIS == 1)
				#define FCP_GET(p, m, b) FC_CAL_Port_In_DDR__x((&FCP_PIN_##p), (&FCP_TRIS_##p), (m), (b)) 	/* Gets the value of a port variable */
				#define FCP_SET(p, m, b, v) set_bit(FCP_TRIS_##p, b); if (v) set_bit(FCP_PORT_##p, b); else clear_bit(FCP_PORT_##p, b);
			#else
				#define FCP_GET(p, m, b) test_bit(FCP_PIN_##p, b);											/* Gets the value of a port variable */
				#define FCP_SET(p, m, b, v) if (v) set_bit(FCP_PORT_##p, b); else clear_bit(FCP_PORT_##p, b); /* Sets the value of a port variable */
			#endif
		#endif

		#include <stdlib.h>

		#define MX_CLEAR_WATCHDOG	wdt_reset()
		#define RECIP3 1.0/3.0

		#define F_CPU	MX_CLK_SPEED

		#define clear_bit( reg, bitNumb )	((reg) &= ~(1 << (bitNumb)))
		#define set_bit( reg, bitNumb )		((reg) |= (1 << (bitNumb)))
		#define test_bit( reg, bitNumb )	((reg) & (1 << (bitNumb)))

		#define cr_bit					clear_bit
		#define st_bit					set_bit
		#define ts_bit					test_bit

		#include <avr/pgmspace.h>

		#define ROMARRAY_S				const MX_UINT8
		#define ROMARRAY_(t)			const t
		#define ROMARRAY_E				[] PROGMEM

		#ifdef SPIF
			#define BF 	(1 << SPIF)
		#endif

		#include "AVR\AVR_CAL_TypeDefs.c"	//Variable Type Definitions
		#include "AVR\AVR_CAL_IO.c"		//I/O Definitions and Functions
		#include "AVR\AVR_CAL_Delay.c"	//Delay Definitions

		#ifndef MX_NO_STRING
			#include "AVR\AVR_CAL_String.c"	//String Definitions
		#endif

		#ifndef MX_NO_FLOAT
			#include "AVR\AVR_CAL_Float.c"	//Float Definitions
		#endif

		#ifdef MX_MIAC_SYSTEM		//Automatic CAN implementation
			#include "MIAC\MIAC_CAL_SYSTEM.c"
		#endif

		#ifdef USE_FLOWCODE_ICD			//ICD SPECIFICS
			#include "AVR\AVR_CAL_ICD.c"
		#endif
		#ifdef USE_FLOWCODE_ICD2		//ICD2 SPECIFICS
			#include "AVR\AVR_CAL_ICD2.c"
		#endif
		#ifdef USE_FLOWCODE_ICD3		//ICD3 SPECIFICS
			//ICD3.c handled in includes to allow it to come after CAL function defines
			#include "AVR\AVR_CAL_ICD3.h"
		#endif

	#endif


	#ifdef MX_CAL_ARD

		#if 0		//Disabled
			#if (FCP_USE_TRIS == 1)
				#define FCP_GET(p, m, b) FC_CAL_Port_In_DDR__x((&FCP_PIN_##p), (&FCP_TRIS_##p), (m), (b)) 	/* Gets the value of a port variable */
				#define FCP_SET(p, m, b, v) set_bit(FCP_TRIS_##p, b); if (v) set_bit(FCP_PORT_##p, b); else clear_bit(FCP_PORT_##p, b);
			#else
				#define FCP_GET(p, m, b) test_bit(FCP_PIN_##p, b);											/* Gets the value of a port variable */
				#define FCP_SET(p, m, b, v) if (v) set_bit(FCP_PORT_##p, b); else clear_bit(FCP_PORT_##p, b); /* Sets the value of a port variable */
			#endif
		#endif

		#include <stdlib.h>

		#define MX_CLEAR_WATCHDOG	wdt_reset()
		#define RECIP3 1.0/3.0

		#define F_CPU	MX_CLK_SPEED

		#define clear_bit( reg, bitNumb )	((reg) &= ~(1 << (bitNumb)))
		#define set_bit( reg, bitNumb )		((reg) |= (1 << (bitNumb)))
		#define test_bit( reg, bitNumb )	((reg) & (1 << (bitNumb)))

		#define cr_bit					clear_bit
		#define st_bit					set_bit
		#define ts_bit					test_bit

		#include <avr/pgmspace.h>

		#define ROMARRAY_S				const MX_UINT8
		#define ROMARRAY_(t)			const t
		#define ROMARRAY_E				[] PROGMEM

		#ifdef SPIF
			#define BF 	(1 << SPIF)
		#endif

		#include "AVR\AVR_CAL_TypeDefs.c"	//Variable Type Definitions
		#include "AVR\AVR_CAL_IO.c"		//I/O Definitions and Functions
		#include "AVR\AVR_CAL_Delay.c"	//Delay Definitions
		#include "AVR\AVR_CAL_String.c"	//String Definitions
		#include "AVR\AVR_CAL_Float.c"	//Float Definitions

		#ifdef MX_MIAC_SYSTEM		//Automatic CAN implementation
			#include "MIAC\MIAC_CAL_SYSTEM.c"
		#endif

		#ifdef USE_FLOWCODE_ICD			//ICD SPECIFICS
			#include "AVR\AVR_CAL_ICD.c"
		#endif
		#ifdef USE_FLOWCODE_ICD2		//ICD2 SPECIFICS
			#include "AVR\AVR_CAL_ICD2.c"
		#endif
		#ifdef USE_FLOWCODE_ICD3		//ICD3 SPECIFICS
			//ICD3.c handled in includes to allow it to come after CAL function defines
			#include "AVR\AVR_CAL_ICD3.h"
		#endif

	#endif


	// ST ARM .....
	#ifdef MX_CAL_STARM

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
		#endif

		#if defined STM32L0
			#include "stm32l0xx.h"
		#elif defined STM32L1
			#include "stm32l1xx.h"
		#elif defined STM32L4
			#include "stm32l4xx.h"
		#endif

		#define FC_CAL_Bit_Call1(Apre, Alett, Apost, B)				Apre##Alett##_##Apost(B)
		#define FC_CAL_Bit_Call2(Apre, Alett, Apost, B, C)			Apre##Alett##_##Apost(C, B)

		#if 0		//Disabled
			#define FCP_GET(p, m, b)									(FC_CAL_Bit_Call1(port, p, in, m) >> (b))
			#define FCP_SET(p, m, b, v)									FC_CAL_Bit_Call2(port, p, out, m, (v) << (b))
		#endif

		#include <stdint.h>
		#include <stdlib.h>
		#include <math.h>


		#define MX_CLEAR_WATCHDOG

		// Bit manipulation
		#define clear_bit( reg, bitNumb )	((reg) &= ~(1 << (bitNumb)))
		#define set_bit( reg, bitNumb )		((reg) |= (1 << (bitNumb)))
		#define test_bit( reg, bitNumb )	((reg) & (1 << (bitNumb)))

		#define cr_bit						clear_bit
		#define st_bit						set_bit
		#define ts_bit						test_bit

		#define ROMARRAY_S					const MX_UINT8
		#define ROMARRAY_(t)				const t
		#define ROMARRAY_E					[]


		#include "STARM\STARM_CAL_TypeDefs.c"	//Variable Type Definitions
		#include "STARM\STARM_CAL_IO.c"		//I/O Definitions and Functions
		#include "STARM\STARM_CAL_Delay.c"	//Delay Definitions
		#include "STARM\STARM_CAL_String.c"	//String Definitions
		#include "STARM\STARM_CAL_Float.c"	//Float Definitions

		#include "STARM\STARM_CAL_CLOCKS.c"

		#ifdef USE_FLOWCODE_ICD			//ICD SPECIFICS
			#include "STARM\STARM_CAL_ICD.c"
		#endif
		#ifdef USE_FLOWCODE_ICD2		//ICD2 SPECIFICS
			#include "STARM\STARM_CAL_ICD2.c"
		#endif
		#ifdef USE_FLOWCODE_ICD3		//ICD3 SPECIFICS
			//ICD3.c handled in includes to allow it to come after CAL function defines
			#include "STARM\PIC_CAL_ICD3.h"
		#endif

	#elif defined MX_CAL_ARM

		#define FC_CAL_Bit_Call1(Apre, Alett, Apost, B)				Apre##Alett##_##Apost(B)
		#define FC_CAL_Bit_Call2(Apre, Alett, Apost, B, C)			Apre##Alett##_##Apost(C, B)

		#if 0		//Disabled
			#define FCP_GET(p, m, b)									(FC_CAL_Bit_Call1(port, p, in, m) >> (b))
			#define FCP_SET(p, m, b, v)									FC_CAL_Bit_Call2(port, p, out, m, (v) << (b))
		#endif

		#include <stdlib.h>
		#include <math.h>

		#define MX_CLEAR_WATCHDOG

		// Bit manipulation
		#define clear_bit( reg, bitNumb )	((reg) &= ~(1 << (bitNumb)))
		#define set_bit( reg, bitNumb )		((reg) |= (1 << (bitNumb)))
		#define test_bit( reg, bitNumb )	((reg) & (1 << (bitNumb)))

		#define cr_bit						clear_bit
		#define st_bit						set_bit
		#define ts_bit						test_bit

		#define ROMARRAY_S					const MX_UINT8
		#define ROMARRAY_(t)				const t
		#define ROMARRAY_E					[]

		#include "ARM\ARM_CAL_TypeDefs.c"	//Variable Type Definitions
		#include "ARM\ARM_CAL_IO.c"		//I/O Definitions and Functions
		#include "ARM\ARM_CAL_Delay.c"	//Delay Definitions
		#include "ARM\ARM_CAL_String.c"	//String Definitions
		#include "ARM\ARM_CAL_Float.c"	//Float Definitions

		#ifdef USE_FLOWCODE_ICD			//ICD SPECIFICS
			#include "ARM\ARM_CAL_ICD.c"
		#endif
		#ifdef USE_FLOWCODE_ICD2		//ICD2 SPECIFICS
			#include "ARM\ARM_CAL_ICD2.c"
		#endif
		#ifdef USE_FLOWCODE_ICD3		//ICD3 SPECIFICS
			//ICD3.c handled in includes to allow it to come after CAL function defines
			#include "ARM\ARM_CAL_ICD3.h"
		#endif

	#endif

	#ifdef MX_CAL_ESP32

		#include "ESP\ESP_CAL_TypeDefs.c"	//Variable Type Definitions
		#include "ESP\ESP_CAL_IO.c"			//I/O Definitions and Functions
		#include "ESP\ESP_CAL_Delay.c"		//Delay Definitions
		#include "ESP\ESP_CAL_String.c"		//String Definitions
		#include "ESP\ESP_CAL_Float.c"		//Float Definitions

		#define ROMARRAY_S					const MX_UINT8
		#define ROMARRAY_(t)				const t
		#define ROMARRAY_E					[]
		#define nop()                       asm("nop")

		#ifdef USE_FLOWCODE_ICD2		//ICD2 SPECIFICS
			#include "ESP\ESP_CAL_ICD2.c"
		#endif
		#ifdef USE_FLOWCODE_ICD3		//ICD3 SPECIFICS
			//ICD3.c handled in includes to allow it to come after CAL function defines
			#include "ESP\ESP_CAL_ICD3.h"
		#endif

	#endif

	#ifdef MX_CAL_PICO

		#include <stdio.h>
		#include "pico/stdlib.h"
		#include "hardware/gpio.h"

		#include "PICO\PICO_CAL_TypeDefs.c"	//Variable Type Definitions
		#include "PICO\PICO_CAL_IO.c"			//I/O Definitions and Functions
		#include "PICO\PICO_CAL_Delay.c"		//Delay Definitions
		#include "PICO\PICO_CAL_String.c"		//String Definitions
		#include "PICO\PICO_CAL_Float.c"		//Float Definitions

		#define ROMARRAY_S					const MX_UINT8
		#define ROMARRAY_(t)				const t
		#define ROMARRAY_E					[]

		#define nop()						tight_loop_contents()

		#ifdef USE_FLOWCODE_ICD2		//ICD2 SPECIFICS
			#include "PICO\PICO_CAL_ICD2.c"
		#endif
		#ifdef USE_FLOWCODE_ICD3		//ICD3 SPECIFICS
			//ICD3.c handled in includes to allow it to come after CAL function defines
			#include "PICO\PICO_CAL_ICD3.h"
		#endif
	#endif

	#ifndef USE_FLOWCODE_ICD3
		#define FC_ICD_OFF   ;
		#define FC_ICD_ON    ;
	#endif

#endif		//End of internals_h

