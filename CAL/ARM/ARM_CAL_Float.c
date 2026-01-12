// CRC: AE5753800093D2B889297C6B876B6A21749C10AFA09C3FCE4A5F65B0FF76818F30CA8890699375CE5768C1E8F467C1D39A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5DA2FDA87FDFCB69DCD88051B5BECCB05F05E5FF89CE9B3AFC05B77E60F3CEA6D6CF8FBB2FE61754D51005D448CEC8504EDBF4D14D39EAE535821C0ADAB8711C382F3682AB086EC4496A90EBB55E6DFF45D014FBCC70A0131549D34A0D5AD11F31417AA8C4F6105CA3A0ED235FBA03551D37180160F0D0D7DE4565E63FDA312627DD474674123A97D
// REVISION: 1.0
// GUID: 239476D8-683E-4ECF-85AE-F4CFEEC93382
// DATE: 08\08\2022
// DIR: CAL\ARM\ARM_CAL_Float.c
/*********************************************************************
 *                  Flowcode CAL Float File
 *
 * File: ARM_CAL_Float.c
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
 * 060911 | BR | Created
 * 050312 | BR | Updated to v5.1 CAL Schema
 * 160712 | JW | Fix to the float rem function to use fmod rather then int mod operator '%'
 */



#define flt_add(a, b) ((a) + (b))			// Binary arithmetic
#define flt_sub(a, b) ((a) - (b))
#define flt_mul(a, b) ((a) * (b))
#define flt_div(a, b) ((a) / (b))
#define flt_rem(a, b) (fmod((a), (b)))

#define flt_neg(a) (-(a))					//Unary arithmetic

#define flt_eq(a, b) ((a) == (b))			//Comparisons
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

double fround(double val, int dp);
//char isinf(float f);

#define random() (rand() & 0x7fff)
#define fact(x) round(gamma(x+1))

#define float32_sqrt(A)	sqrt(A)

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
