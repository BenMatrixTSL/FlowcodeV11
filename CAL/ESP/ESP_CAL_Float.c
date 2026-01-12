// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A030CA8890699375CE5768C1E8F467C1D39A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF51E00F0C51ED3547FBE4950A91E7DE2CE3D7EEA8BE7635568FECF5B034B64F58F53D713AD593DB9349AC982C04869370CE3D1FD926F6EEB05E1DF752B1242E74FFF41A7881F8CF1806D100C490DD3FC1940062368282E385D549D34A0D5AD11F374D0C14BB7F53BDD63D9791FDAC208163E2169FC8BAA8C92850400E5B608E745107C571680B732A8
// REVISION: 1.0
// GUID: 5B656B66-4CB4-472F-BDC9-8D26A4AE8FFF
// DATE: 08\08\2022
// DIR: CAL\ESP\ESP_CAL_Float.c
/*********************************************************************
 *                  Flowcode CAL Float File
 *
 * File: ESP_CAL_Float.c
 *
 * (c) 2018 Matrix TSL.
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





/*=----------------------------------------------------------------------=*\
  Use :Calculates cos(Rads) as a float, where Rads is in radian
      :
      :This uses the power series to 4 levels, and is accurate to 12-bit:
      :  1 - x^2/2 + x^4/24 - x^6/720 + x^8/40320
      :
      :Note: 10321920 = (4096 * 5040) / 2
      :      This is required for the sin part of the expansion
      :
      :Returns fixed point cosine of the Rads in base 10321920
\*=----------------------------------------------------------------------=*/
inline signed long flt_cos_i(unsigned long Rads12)
{
  unsigned long x, x2, x4, x6, x8, err;
  signed int    sgn;

  x = Rads12; // Now a max 14-bit number
  if (x > 6433 && x <= 19301) // x > PI/2 && x < 3*PI/2
  {
    sgn = -1;
  }
  else
  {
    sgn = 1;
  }
  if (x > 12867) // PI (180deg)
  {
    x -= 12867;
  }
  if (x > 6433) // PI/2 (90deg)
  {
    x = 12867 - x;
  }
  // 0 <= x <= 6433
  x2 = (x * x + 2047) >> 12; // Square of value
  x4 = (x2 * x2) >> 12;      // Power 4
  x6 = (x4 * x2) >> 12;      // Power 6
  x8 = (x4 * x4) >> 12;      // Power 8
  // Multiply up for rounding errors
  x2 *= 360;                 // 720 / 2
  x4 *= 30;                  // 720 / 24
  x8 /= 90;                  // 40320 / 720
  err = 250;                 // Error correction value, magic number calculated by eye
  return ((signed long)((2949120L - x2 + x4 - x6 + x8 - err) * sgn) * 7) >> 1; // Base 10321920
}


/*=----------------------------------------------------------------------=*\
  Use :Calculates sin(Rads) as a long, where Rads is in radians, base 12
      :Here Rads12 0 <= Rads < 2*PI
      :
      :This uses the power series to 4 levels, and is accurate to 12-bit:
      :  x - x^3/6 + x^5/120 - x^7/5040 + x^9/362880
      :
      :Note: 10321920 = (4096 * 5040) / 2
      :      This is required for the sin part of the expansion
      :
      :Returns fixed point sin of the Rads in base 10321920
\*=----------------------------------------------------------------------=*/
inline signed long flt_sin_i(unsigned long Rads12)
{
  unsigned long x, x2, x3, x5, x7, x9, err;
  signed int    sgn;

  x = Rads12; // Now a max 14-bit number
  if (x > 12867)
  {
    sgn = -1;
    x -= 12867; // 0->PI
  }
  else
  {
    sgn = 1;
  }
  if (x > 6433)
  {
    x = 12867 - x;
  }
  x2 = (x * x + 2047) >> 12; // Square of value
  x3 = (x2 * x) >> 12;       // Power 3
  x5 = (x3 * x2) >> 12;      // Power 5
  x7 = (x5 * x2) >> 12;      // Power 7
  x9 = (x7 * x2) >> 12;      // Power 9
  // Multiply up for rounding errors
  x *= 2520;                 // (5040) / 2
  x3 *= 420;                 // (5040 / 6) / 2
  x5 *= 21;                  // (5040 / 120) / 2
  x9 /= 36;                  // (362880 / 5040) / 2
  err = 2048;                // Error correction value, magic number calculated by eye
  return (signed long)(x - x3 + x5 - x7 + x9 + err) * sgn; // Base 10321920
}

