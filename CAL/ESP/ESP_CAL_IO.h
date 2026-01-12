// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A091E52931D8B0EE6801869669B83EE6EF933584AF9226BF856C2B91C83E6201818940AE31AE32EB4A0C3CAEE8E7DA6987CD7713A0E315157E11887E8822D257A7F9791B3D8BDC20E8963FF5F3F072113712CCDCB43FEFB7EA9211E05752B21B16382C6C9064BD4FE73C05D3DC8639F0E285AB6A4C35A1E73C27D83C80E3374BB027114D98EF86616A549D34A0D5AD11F3EAC91E62CDCF29307A148549464A307C3655EB9B37A5A1E1A8B2FE2536E6C50FEBD31FED13C8BAD2
// REVISION: 5.0
// GUID: D0279C50-A295-4024-8E6D-198698942624
// DATE: 31\03\2025
// DIR: CAL\ESP\ESP_CAL_IO.h
/*********************************************************************
 *                  Flowcode CAL IO File
 *
 * File: ESP_CAL_IO.h
 *
 * (c) 2018 Matrix TSL.
 * http://www.matrixtsl.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
 * 'Company') for its Flowcode graphical programming language is
 * intended and supplied to you, the Company's customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN 'AS IS' CONDITION. NO WARRANTIES,
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
 * 130718 | BR | Created
 *
 */



#ifdef MX_BL0058_PINMAP

	#define MX_IO_JOIN(A,B)						A##B

	#define GET_PORT(Port)						MX_IO_JOIN(FC_CAL_Port_In_BL0058_,Port(0xFF, 0))
	#define GET_PORT_MASK(Port,Mask)			MX_IO_JOIN(FC_CAL_Port_In_BL0058_,Port(Mask, 0))
	#define GET_PORT_PIN(Port,Bit)				MX_IO_JOIN(FC_CAL_Port_In_BL0058_,Port(1<<Bit, Bit))

	#define SET_PORT(Port,Val)					MX_IO_JOIN(FC_CAL_Port_Out_BL0058_,Port(0xFF, Val))
	#define SET_PORT_MASK(Port,Mask,Val)		MX_IO_JOIN(FC_CAL_Port_Out_BL0058_,Port(Mask, Val))
	#define SET_PORT_PIN(Port,Bit,Val) 			MX_IO_JOIN(FC_CAL_Port_Out_BL0058_,Port(1<<Bit, (Val)?0xFF:0))

	#define FCP_SET_NODDR(p,b,v)				gpio_set_level(FC_CAL_Port_Remap(p,b), v)
	#define FCP_GET_NODDR(p,b)					gpio_get_level(FC_CAL_Port_Remap(p,b))

	#define porta A
	#define portb B
	#define portc C

	#define trisa A
	#define trisb B
	#define trisc C

#else

	#ifdef MX_BL6390_PINMAP

		#define MX_IO_JOIN(A,B)					A##B

		#define GET_PORT(Port)					MX_IO_JOIN(FC_CAL_Port_In_BL6390_,Port(0xFF, 0))
		#define GET_PORT_MASK(Port,Mask)		MX_IO_JOIN(FC_CAL_Port_In_BL6390_,Port(Mask, 0))
		#define GET_PORT_PIN(Port,Bit)			MX_IO_JOIN(FC_CAL_Port_In_BL6390_,Port(1<<Bit, Bit))

		#define SET_PORT(Port,Val)				MX_IO_JOIN(FC_CAL_Port_Out_BL6390_,Port(0xFF, Val))
		#define SET_PORT_MASK(Port,Mask,Val)	MX_IO_JOIN(FC_CAL_Port_Out_BL6390_,Port(Mask, Val))
		#define SET_PORT_PIN(Port,Bit,Val) 		MX_IO_JOIN(FC_CAL_Port_Out_BL6390_,Port(1<<Bit, (Val)?0xFF:0))

		#define FCP_SET_NODDR(p,b,v)			gpio_set_level(FC_CAL_Port_Remap(p,b), v)
		#define FCP_GET_NODDR(p,b)				gpio_get_level(FC_CAL_Port_Remap(p,b))

		#define porta A
		#define portb B
		#define portc C
		#define portd D

		#define trisa A
		#define trisb B
		#define trisc C
		#define trisd D

	#else

		#define A								0
		#define B								32

		#define porta							0
		#define portb							32

		#define GET_PORT(p)						FC_CAL_Port_In_DDR(p, 0xFFFFFFFF)
		#define GET_PORT_PIN(p,b)				FC_CAL_Bit_In_DDR((p + b))
		#define GET_PORT_SHIFT(p,s)
		#define GET_PORT_MASK_SHIFT(p,m,s)
		#define GET_PORT_MASK(p,m)				FC_CAL_Port_In_DDR(p, m)

		#define SET_PORT(p,v)					FC_CAL_Port_Out_DDR (p, 0xFFFFFFFF, v)
		#define SET_PORT_PIN(p,b,v) 			FC_CAL_Bit_Out_DDR (p+b, (v)?1:0)
		#define SET_PORT_SHIFT(p,s,v)
		#define SET_PORT_MASK_SHIFT(p,m,s,v)
		#define SET_PORT_MASK(p,m,v)			FC_CAL_Port_Out_DDR (p, m, v)

		#define FCP_SET_NODDR(p,b,v)			gpio_set_level((p + b), v)
		#define FCP_GET_NODDR(p,b)				gpio_get_level((p + b))

	#endif
#endif


