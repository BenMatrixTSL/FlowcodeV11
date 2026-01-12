// CRC: F9C65A77A483DDF22B438B7FEB8E3C81451B6760FECB07508D29EE770BB95F479431E163CF5ED3A438BF3E0D878C6819186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF501AE74435CA82C95B2FDC78A7FCA9DC8DDE1AD9944BF2BD6A09F8FB9C9379A1181867C49AA83AC7D9D28FFE86309063B0C282AAE02FD0190EF95547DF8A290C732833148659703E5B428F5472CBC23311D5A6FA971273679549D34A0D5AD11F3EB32BC8A6BA9CD1DDADDE35693C52955370A609CE3A9BC833E7DF3EE771A32107C30AF6F6246FD52
// REVISION: 1.0
// GUID: E80555F2-E448-4240-9E6B-3BE502F5B172
// DATE: 08\08\2022
// DIR: CAL\PICO\PICO_CAL_Float.c

/*********************************************************************
 *                  Flowcode CAL Float File
 *
 * File: PICO_CAL_Float.c
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
 * 130718 | BR | Created
 *
 */



//extern float log (float);
//extern float sqrt (float);


#define flt_add(a, b) ((a) + (b))			  	// Binary arithmetic
#define flt_sub(a, b) ((a) - (b))
#define flt_mul(a, b) ((a) * (b))
#define flt_div(a, b) ((a) / (b))
#define flt_rem(a, b) (fmod((a), (b)))

#define flt_neg(a) (-(a))					  	//Unary arithmetic

#define flt_eq(a, b) ((a) == (b))			  	//Comparisons
#define flt_ne(a, b) ((a) != (b))
#define flt_ge(a, b) ((a) >= (b))
#define flt_gt(a, b) ((a) > (b))
#define flt_le(a, b) ((a) <= (b))
#define flt_lt(a, b) ((a) < (b))

#define flt_toi(a)   ((long)(a))			  		//Assignment
#define flt_fromi(a) ((float)(a))

// Rounding functions - nearest, down, up
#define flt_round(f) ((long)(((f)>=0.0)?(f)+0.5:(f)-0.5))
#define flt_floor(f) ((long)(f))
#define flt_ceil(f)  ((long)(f) + 1)


#define float32_sqrt(A)	sqrt(A)


//Workaround to support missing fround function
#define fround(a, b)  (flt_div(flt_round(flt_mul(a,pow(10,b))),pow(10,b)))


