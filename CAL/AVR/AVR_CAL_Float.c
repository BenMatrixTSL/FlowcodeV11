// CRC: 77485F5F6A861F9125D47827B4DE492656C5431E478E8046055FD2257F64F1F330CA8890699375CE5768C1E8F467C1D39A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF58B2EED470757A59E5F0CF989606836F961D81C1059E012C75893F7374B94E20501B2EC616F1F912CFC430F2C8194359676AB00A1BA24A841C21037573D6B56C927FA0CC5CD152536156FDAE693AE00505D014FBCC70A0131549D34A0D5AD11F30E4333335C70BCD157D3C9F766A7843FA4E6E41330BB70C476D3E34736BD7539F516F4BDFF4A1CBE
// REVISION: 1.0
// GUID: B7644120-B177-4DF1-8044-0A3D48115656
// DATE: 08\08\2022
// DIR: CAL\AVR\AVR_CAL_Float.c
/*********************************************************************
 *                  Flowcode CAL Float File
 *
 * File: AVR_CAL_Float.c
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
 * 020312 | BR | Updated to v5.1 CAL Schema
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

//static double cbrt(double);
//static double asinh(double);
//static double acosh(double);
//static double atanh(double);
static double fround(double, int);
//static char isinf(float f);

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



// Additional floating-point functions
/*
static double cbrt(double x)
{
	return(pow(x, RECIP3));
}
*/

/*static double asinh(double x)
{
	return (log(x + sqrt(x * x + 1)));
}

static double acosh(double x)
{
	if (x >= 1)
		return (log(x + sqrt(x * x - 1)));
	else
		return(NAN);
}

static double atanh(double x)
{
	if (fabs(x) < 1)
		return (log((1 + x)/(1 - x)) / 2);
	else
		if (fabs(x) == 1)
			return(INFINITY);
		else
			return(NAN);
}*/

/*
static char isinf(float f)
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

