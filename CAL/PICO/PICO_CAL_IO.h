// CRC: F9C65A77A483DDF22B438B7FEB8E3C81451B6760FECB07508D29EE770BB95F471E1A3B6BDBC9AEBC1F0EF6FCC3EA254B9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5214F21D4CC48F0F12E1435935F03ABF189797B183ED887637505C2886EFD2E8933BCAC082C2052A8A8E1217816825D0B3B44F00287B9BC42994CD95B90F73ED51CB9B54EC7EAED352072FC6718AAFFD9EB33AFC7003B3C9B549D34A0D5AD11F32459CC17C2D0A7E2F5802AF3825778DD0F41EA32608D43E6F97B3AD2E0D541FFE19252820FE3EB9C
// REVISION: 1.0
// GUID: 83ACEE17-5010-43E9-A3BD-BA32F9CB752D
// DATE: 08\08\2022
// DIR: CAL\PICO\PICO_CAL_IO.h

/*********************************************************************
 *                  Flowcode CAL IO File
 *
 * File: PICO_CAL_IO.h
 *
 * (c) 2021 Matrix TSL.
 * http://www.matrixtsl.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
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
 * 260521 | LM | Created
 *
 */



// Define port letters
#define A		0
#define porta	0
#define B		32
#define portb	32
#define trisa 	0
#define trisb	0

#define GET_PORT(p)						FC_PICO_CAL_Port_In_DDR(p, 0xFFFFFFFF)
#define GET_PORT_PIN(p,b)				FC_PICO_CAL_Bit_In_DDR((p + b))
#define GET_PORT_SHIFT(p,s)
#define GET_PORT_MASK_SHIFT(p,m,s)
#define GET_PORT_MASK(p,m)				FC_PICO_CAL_Port_In_DDR(p, m)

#define SET_PORT(p,v)					FC_PICO_CAL_Port_Out_DDR(p, 0xFFFFFFFF, v)
#define SET_PORT_PIN(p,b,v) 			FC_PICO_CAL_Bit_Out_DDR(p+b, (v)?1:0)
#define SET_PORT_SHIFT(p,s,v)
#define SET_PORT_MASK_SHIFT(p,m,s,v)
#define SET_PORT_MASK(p,m,v)			FC_PICO_CAL_Port_Out_DDR(p, m, v)

#define FCP_SET_NODDR(p,b,v)			gpio_put((p + b), v)
#define FCP_GET_NODDR(p,b)				gpio_get((p + b))

#define FC_CAL_Bit_In(p,b)				FCP_GET_NODDR(p,b)
#define FC_CAL_Bit_High(p,b)			FCP_SET_NODDR(p,b,1)
#define FC_CAL_Bit_Low(p,b)				FCP_SET_NODDR(p,b,0)

#define FC_CAL_Bit_In_DDR(p,t,b)		FC_PICO_CAL_Bit_In_DDR(p+b)
#define FC_CAL_Bit_High_DDR(p,t,b)		FC_PICO_CAL_Bit_High_DDR(p+b)
#define FC_CAL_Bit_Low_DDR(p,t,b)		FC_PICO_CAL_Bit_Low_DDR(p+b)
#define FC_CAL_Bit_Out_DDR(p,t,b,v)		FC_PICO_CAL_Bit_Out_DDR((p+b),v)
#define FC_CAL_Port_In_DDR(p,t,m)		FC_PICO_CAL_Port_In_DDR(p,m)
#define FC_CAL_Port_Out_DDR(p,t,m,v)	FC_PICO_CAL_Port_Out_DDR(p,m,v)


