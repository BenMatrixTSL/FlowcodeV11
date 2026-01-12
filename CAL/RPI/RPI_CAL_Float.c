// CRC: 34358081B117C27F7D8358E612878F8E5F343B66182D417818220CB9C07676CF30CA8890699375CE5768C1E8F467C1D39A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5E74E7FAC3F0B0D4BFA00FD7159D681D391F4DD678C1AD30B681E8DCDCDB5B2AC6DD8D614D551BEA48FA9ED5D7F3B7006FF0F873BF4347586AAB70CDA73B339CDDE30F5361FFA5FFA64C8B43BB272B28C7F5A2BE2E53E5160549D34A0D5AD11F3393A663446E02B0A2D23FCF93FD286CBE93802CABCC783B1072F880DBB6DFDD32544F23D1CC1FCAE
// REVISION: 1.0
// GUID: 2482CFF1-5B1B-4351-A156-F023DDBC9E1A
// DATE: 08\08\2022
// DIR: CAL\RPI\RPI_CAL_Float.c
/*********************************************************************
 *                  Flowcode CAL Float File
 *
 * File: PIC_CAL_Float.c
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
 * 010911 | BR | Created
 *
 *
 *
 */

/***
char isinf(float f);
***/

#define flt_add(a, b) ((float)(a) + (float)(b))			  	// Binary arithmetic
#define flt_sub(a, b) ((float)(a) - (float)(b))
#define flt_mul(a, b) ((float)(a) * (float)(b))
#define flt_div(a, b) ((float)(a) / (float)(b))
#define flt_rem(a, b) (fmod((float)(a), (float)(b)))

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


/****
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
***/




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
