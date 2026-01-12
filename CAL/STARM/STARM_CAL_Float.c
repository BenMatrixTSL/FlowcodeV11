// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BECF688407D8C668C25799E546AE091433F6A5B120DF94DBAE53530CD754161A539A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5577E84BAB7E3F88313D8363E53B55C85DF40FA302D25C6DFDF959E22671B3F09DBEE8EA0BB89B4E7FB022593CF702747C382F042FA6AB37EE79C6B5AC257344E517D73412379F87CCEEB0FFBD4F45D97B6845E141E07EBE5549D34A0D5AD11F3AAA08203CF4936E954A284F712DDA7FB56906702E4C0C3EFB68A65FD090A6D6B4C68FB27E1809948
// REVISION: 1.0
// GUID: BFEC2D1F-5F9E-4E79-94F4-EEB0633AEF1E
// DATE: 08\08\2022
// DIR: CAL\STARM\STARM_CAL_Float.c
/*********************************************************************
 *                  Flowcode CAL Float File
 *
 * File: STARM_CAL_Float.c
 *
 * (c) 2016 Matrix TSL
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
 * 060911 | BR | Created
 * 020312 | BR | Updated to v5.1 CAL Schema
 */

//Float functions to allow PIC imports to work correctly
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

#define flt_toi(a)   ((long)(a))			  	//Assignment
#define flt_fromi(a) ((float)(a))

// Rounding functions - nearest, down, up
#define flt_round(f) ((long)(((f)>=0.0)?(f)+0.5:(f)-0.5))
#define flt_floor(f) ((long)(f))
#define flt_ceil(f)  ((long)(f) + 1)

//char isinf(float f);
unsigned int float32_is_signaling_nan(float f);

#define float32_sqrt(A)	sqrt(A)

//Workaround to support missing fround function
#define fround(a, b)  (flt_div(flt_round(flt_mul(a,pow(10,b))),pow(10,b)))


//Mapping functions to convert one range to another
MX_SINT32 MX_Map(MX_SINT32 x, MX_SINT32 in_min, MX_SINT32 in_max, MX_SINT32 out_min, MX_SINT32 out_max);
MX_FLOAT MX_Map_Float(MX_FLOAT x, MX_FLOAT in_min, MX_FLOAT in_max, MX_FLOAT out_min, MX_FLOAT out_max);

MX_SINT32 MX_Map(MX_SINT32 x, MX_SINT32 in_min, MX_SINT32 in_max, MX_SINT32 out_min, MX_SINT32 out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

MX_FLOAT MX_Map_Float(MX_FLOAT x, MX_FLOAT in_min, MX_FLOAT in_max, MX_FLOAT out_min, MX_FLOAT out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



/*
char isinf(float f)
{
      char* b;
      b = (char*)&f;
      if ((b[0] == 0)   &&
          (b[1] == 0)   &&
          (b[2] == 128) &&
          ((b[3] & 127) == 127))
      {
            return (255);
      }
      return (0);
}
*/

unsigned int float32_is_signaling_nan(float f)
{
      char* b;
      b = (char*)&f;
      if ((b[0] == 0)   &&
          (b[1] == 0)   &&
          (b[2] == 128) &&
          ((b[3] & 127) == 127))
      {
            return (0xFFFF);
      }
      return (0);
}

