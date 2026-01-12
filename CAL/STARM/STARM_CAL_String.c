// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BE2C4B938A102D61451DE0AD0698A98F50D6F764123AD2903937CD62BCB041599F56557CC7FB74F055CCDF56843D14FE72265B9B5C83AAC8680C3CAEE8E7DA698790F886B170530A4AE8E8D481C0B40518842E37EAD556933DD52D5F1A7EC9B48C55D98374C88FBF362D84CDD126731176EF3EF8F517CF0E868BC74CF31016C67EFE64B2DAE4A1A78E64C1E90D72A2731CBC2DAB1519A12067549D34A0D5AD11F30B0301BD4ED3A59F816861C943152CFBF8308B26A8A0490C35CB29F668C7CEEBDE7ED4CEB4872907
// REVISION: 4.0
// GUID: C394BD92-3AA5-4FEC-87F9-913EF7CB8A72
// DATE: 24\11\2025
// DIR: CAL\STARM\STARM_CAL_String.c
/*********************************************************************
 *                  Flowcode CAL String File
 *
 * File: ARM_CAL_String.c
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
 * 150911 | JW | Added v5 string functions
 * 150911 | BR | Updated variables with typedef alternatives
 * 050312 | BR | Updated to v5.1 CAL Schema
 * 260612 | BR | Minor code change in number to hex function to remove warning
 * 250912 | BR | Fixed an issue with the ToString function which caused the contents of the input variable to be cleared to 0
 * 091213 | LM | Flowcode now passes FCV_PRECISION
 * 230114 | LM | Updated string compare (length params are buffer size, not character count)
 * 180214 | LM | fixed typos in TOSTR defines
 * 050314 | LM | Allow use of 32 bit mantissa in Float to String function
 * 060314 | LM | Default to using 32 bit
 * 070414 | LM | String functions to return string pointer, not length (FC6 requirement)
 * 120416 | BR | Changed length parameters from 8-bit to 16-bit
 */


// Useful call for finding the length of an (uncorrupted) string
#define FCI_GETLENGTH__x(str, max, idx)         for (idx = 0; idx < max; idx++) if (str[idx] == 0) break
#define FCI_STRMOV__x(str, max, dst, dlen, ix)  for (ix = 0; ix < (max) && ix < (dlen) && str[ix] != '\0'; ix++) dst[ix] = str[ix]
#define FCI_CONCATENATE(s0, l0, s1, l1, sd, ld) FCI_SHEAD(s0, l0, s1, l1, sd, ld)


#ifndef MX_USES_UINT32
	#define MX_USES_UINT32 1
#endif
#ifndef MX_USES_SINT32
	#define MX_USES_SINT32 1
#endif


#if (MX_USES_UINT32 || MX_USES_SINT32)
	#define MX_STRF_LONG
	#define MX_ULONG MX_UINT32
	#define MX_SLONG MX_SINT32
#else
	#define MX_ULONG MX_UINT16
	#define MX_SLONG MX_SINT16
#endif

#define FCI_ITOS8(value, text, length)		FCI_TOSTRS16(value, text, length)
#define FCI_ITOS16(value, text, length)  	FCI_TOSTRS16(value, text, length)
#define FCI_ITOS32(value, text, length)		FCI_TOSTRS32(value, text, length)

#define FCI_UTOS8(value, text, length)		FCI_TOSTRU16(value, text, length)
#define FCI_UTOS16(value, text, length)		FCI_TOSTRU16(value, text, length)
#define FCI_UTOS32(value, text, length)		FCI_TOSTRU32(value, text, length)
// FCV_PRECISION
#define FCI_FTOS32(value, precision, text, length)		FCI_FLOAT_TO_STRING(value, precision, text, length);
#define FCI_FTOS64(value, precision, text, length)		FCI_FLOAT_TO_STRING(value, precision, text, length);

#define FCI_STOF(text)						FCI_STRING_TO_FLOAT(text, 15);
#define FCI_STOI(text)						FCI_STRING_TO_INT(text, 15);
#define FCI_STOU(text)						FCI_STRING_TO_INT(text, 15);


//String function definitions
static MX_UINT8 FCI_GETCHAR(MX_STRING sStr1, MX_UINT16 iStr1_len, MX_UINT16 iPos);
static MX_UINT16 FCI_GETLENGTH(MX_STRING sStr1, MX_UINT16 iStr1_len);
static MX_STRING FCI_MIDSTRING(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_UINT16 iStart, MX_UINT16 iCount, MX_STRING sDst, MX_UINT16 iDst_len);
static MX_STRING FCI_LEFTSTRING(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_UINT16 iCount, MX_STRING sDst, MX_UINT16 iDst_len);
static MX_STRING FCI_RIGHTSTRING(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_UINT16 iCount, MX_STRING sDst, MX_UINT16 iDst_len);
static MX_STRING FCI_TOSTRING(MX_SLONG iSrc1, MX_STRING sDst, MX_UINT16 iDst_len);

static MX_UINT8 FCI_TOSTRS16(MX_SINT16 iSrc1, MX_STRING sDst, MX_UINT16 iDst_len);
static MX_UINT8 FCI_TOSTRS32(MX_SINT32 iSrc1, MX_STRING sDst, MX_UINT16 iDst_len);
static MX_UINT8 FCI_TOSTRU16(MX_UINT16 iSrc1, MX_STRING sDst, MX_UINT16 iDst_len);
static MX_UINT8 FCI_TOSTRU32(MX_UINT32 iSrc1, MX_STRING sDst, MX_UINT16 iDst_len);

static void FCI_TOLOWER(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_STRING sDst, MX_UINT16 iDst_len);
static void FCI_TOUPPER(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_STRING sDst, MX_UINT16 iDst_len);
static MX_UINT8 FCI_COMPARE(MX_STRING sSrc1, MX_UINT16 iSrc1_len, MX_STRING sSrc2, MX_UINT16 iSrc2_len, MX_UINT8 iNoCase);
static MX_STRING FCI_FLOAT_TO_STRING(MX_FLOAT Number, MX_UINT8 Precision, MX_STRING String, MX_UINT16 MSZ_String);
static MX_STRING FCI_NUMBER_TO_HEX(MX_ULONG Number, MX_STRING String, MX_UINT16 MSZ_String);
static MX_SINT32 FCI_STRING_TO_INT(MX_STRING String, MX_UINT16 MSZ_String);
static MX_FLOAT FCI_STRING_TO_FLOAT(MX_STRING String, MX_UINT16 MSZ_String);

// Functions for contatenation
static MX_UINT16 FCI_STRREV(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_STRING sDst, MX_UINT16 iDst_len);
static MX_UINT16 FCI_STRMOV(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_STRING sDst, MX_UINT16 iDst_len);
static void FCI_SHEAD(MX_STRING sSrc1, MX_UINT16 iSrc1_len, MX_STRING sSrc2, MX_UINT16 iSrc2_len, MX_STRING sDst, MX_UINT16 iDst_len);
static void FCI_SCOPY(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_STRING sDst, MX_UINT16 iDst_len);

MX_SINT16 FCI_CONTAINS(MX_CHAR *FCL_STRDATA, MX_UINT16 FCLsz_STRDATA, MX_CHAR *FCL_STRMATCH, MX_UINT16 FCLsz_STRMATCH, MX_UINT16 FCL_IDX);
void FCI_SPLITSTRING(MX_CHAR *FCL_STRINGINPUT, MX_UINT16 FCLsz_STRINGINPUT, MX_CHAR *FCL_DELIMITER, MX_UINT16 FCLsz_DELIMITER, MX_UINT16 INDEX, MX_CHAR *FCL_RETVAL, MX_UINT16 FCLsz_RETVAL);
void FCI_EXPLODETOINTARRAY(MX_CHAR *FCL_STRINGINPUT, MX_UINT16 FCLsz_STRINGINPUT, MX_UINT8 FCL_DELIMITER, MX_UINT16 FCL_MAXCOUNT, MX_UINT16 *FCL_DATAARRAY, MX_UINT16 FCLsz_DATAARRAY);


#include <stdlib.h>
#include <math.h>


static MX_UINT8 FCI_GETCHAR(MX_STRING sStr1, MX_UINT16 iStr1_len, MX_UINT16 iPos)
{
	if(iPos < iStr1_len)
		return sStr1[iPos];
	return '\0';
}


static MX_UINT16 FCI_GETLENGTH(MX_STRING sStr1, MX_UINT16 iStr1_len)
{
	MX_UINT16 tmp;
	FCI_GETLENGTH__x(sStr1, iStr1_len, tmp);
	return (tmp);
}


static MX_STRING FCI_MIDSTRING(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_UINT16 iStart, MX_UINT16 iCount, MX_STRING sDst, MX_UINT16 iDst_len)
{
	if (iDst_len == 0) return sDst;
	MX_UINT16 idx;
	FCI_GETLENGTH__x(sSrc, iSrc_len, idx);	//find the length of the source string

	if (iStart >= idx)
	{
		sDst[0] = '\0';						//starting position is beyond string length, so return a null string
	}
	else
	{
		if ((iStart + iCount) >= idx)		//Make sure the required length is not too big
			iCount = idx - iStart;
		if (iCount > (iDst_len))			//make sure the required length is not too big
			iCount = (iDst_len);

		for (idx = 0; idx < iCount; idx++)	//Copy the contents of the source string
		{
			sDst[idx] = sSrc[idx + iStart];
		}
		if (idx < iDst_len)						//add terminating null (if we can)
		{
			sDst[idx] = '\0';
		}
	}
	return (sDst);
}


static MX_STRING FCI_LEFTSTRING(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_UINT16 iCount, MX_STRING sDst, MX_UINT16 iDst_len)
{
	if (iDst_len == 0) return sDst;
	MX_UINT16 idx;
	FCI_GETLENGTH__x(sSrc, iSrc_len, idx);	//find the length of the source string

	if (iCount > idx)						//make sure the required length is not too big
		iCount = idx;
	if (iCount > (iDst_len))			//make sure the required length is not too big
		iCount = (iDst_len);

	for (idx = 0; idx < iCount; idx++)		//copy the required MX_UINT8acters
	{
		sDst[idx] = sSrc[idx];
	}

	if (idx < iDst_len)						//add terminating null (if we can)
		sDst[idx] = '\0';

	return (sDst);
}


static MX_STRING FCI_RIGHTSTRING(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_UINT16 iCount, MX_STRING sDst, MX_UINT16 iDst_len)
{
	if (iDst_len == 0) return sDst;
	MX_UINT16 idx;
	MX_UINT16 delta;

	FCI_GETLENGTH__x(sSrc, iSrc_len, idx);	//find the length of the source string

	if (iCount > idx)						//make sure the required length is not too big
		iCount = idx;

	delta = idx - iCount;					//get the offset

	if (iCount > (iDst_len))				//make sure the required length is not too big
		iCount = (iDst_len);

	for(idx = 0; idx < iCount; idx++)		//copy the required characters
	{
		sDst[idx] = sSrc[idx + delta];
	}

	if (idx < iDst_len)						//add terminating null (if we can)
		sDst[idx] = '\0';

	return (sDst);
}



MX_UINT8 FCI_TOSTRS16(MX_SINT16 iSrc1, MX_STRING sDst, MX_UINT16 iDst_len)
{
	MX_UINT8  tmp1;
	MX_SINT16 iSrc = iSrc1;
	MX_UINT16 top = 10000; 		// Maximum power of 10 less than 65536
	MX_UINT16 idx = 0;

	if (iDst_len == 0) return 0;

	//copy source 1 into destination:
	//minus sign
	if (iSrc < 0)
	{
		sDst[0] = '-';
		idx++;
		iSrc = -iSrc;
	}

	tmp1 = 0;    // Nothing added yet
	if (iSrc == 0) // Force showing zero
	{
		tmp1 = 1;
		top = 1;
	}
	while (( idx < iDst_len) && (top > 0))
	{
		if (((unsigned)iSrc >= top) || (tmp1))
		{
			tmp1 = (unsigned)iSrc / top;	// Top digit
			sDst[idx] = '0' + tmp1;			// Add digit to buffer
			idx++;
			iSrc -= tmp1 * top;				// Remove digit
			tmp1 = 1;						// Add zeros now
		}
		top /= 10;							// Go to next digit
	}

	if (idx < iDst_len)						//add terminating null (if we can)
		sDst[idx] = '\0';
	return (idx);
}


MX_UINT8 FCI_TOSTRS32(MX_SINT32 iSrc1, MX_STRING sDst, MX_UINT16 iDst_len)
{
	MX_UINT8  tmp1;
	MX_SINT32 iSrc = iSrc1;
	MX_UINT32 top = 1000000000; 	// Maximum power of 10 less than 4294967296
	MX_UINT16 idx = 0;

	if (iDst_len == 0) return 0;

	//copy source 1 into destination:
	//minus sign
	if (iSrc < 0)
	{
		sDst[0] = '-';
		idx++;
		iSrc = -iSrc;
	}

	tmp1 = 0;    // Nothing added yet
	if (iSrc == 0) // Force showing zero
	{
		tmp1 = 1;
		top = 1;
	}
	while (( idx < iDst_len) && (top > 0))
	{
		if (((unsigned long)iSrc >= top) || (tmp1))
		{
			tmp1 = (unsigned long)iSrc / top;	// Top digit
			sDst[idx] = '0' + tmp1;			// Add digit to buffer
			idx++;
			iSrc -= tmp1 * top;				// Remove digit
			tmp1 = 1;						// Add zeros now
		}
		top /= 10;							// Go to next digit
	}

	if (idx < iDst_len)						//add terminating null (if we can)
		sDst[idx] = '\0';
	return (idx);
}


MX_UINT8 FCI_TOSTRU16(MX_UINT16 iSrc1, MX_STRING sDst, MX_UINT16 iDst_len)
{
	MX_UINT8  tmp1;
	MX_UINT16 iSrc = iSrc1;
	MX_UINT16 top = 10000; 		// Maximum power of 10 less than 65536
	MX_UINT16 idx = 0;

	if (iDst_len == 0) return 0;

	tmp1 = 0;    // Nothing added yet
	if (iSrc == 0) // Force showing zero
	{
		tmp1 = 1;
		top = 1;
	}
	while (( idx < iDst_len) && (top > 0))
	{
		if (((unsigned)iSrc >= top) || (tmp1))
		{
			tmp1 = (unsigned)iSrc / top;	// Top digit
			sDst[idx] = '0' + tmp1;			// Add digit to buffer
			idx++;
			iSrc -= tmp1 * top;				// Remove digit
			tmp1 = 1;						// Add zeros now
		}
		top /= 10;							// Go to next digit
	}

	if (idx < iDst_len)						//add terminating null (if we can)
		sDst[idx] = '\0';
	return (idx);
}


MX_UINT8 FCI_TOSTRU32(MX_UINT32 iSrc1, MX_STRING sDst, MX_UINT16 iDst_len)
{
	MX_UINT8  tmp1;
	MX_UINT32 iSrc = iSrc1;
	MX_UINT32 top = 1000000000; 	// Maximum power of 10 less than 4294967296
	MX_UINT16 idx = 0;

	if (iDst_len == 0) return 0;

	tmp1 = 0;    // Nothing added yet
	if (iSrc == 0) // Force showing zero
	{
		tmp1 = 1;
		top = 1;
	}
	while (( idx < iDst_len) && (top > 0))
	{
		if (((unsigned long)iSrc >= top) || (tmp1))
		{
			tmp1 = (unsigned long)iSrc / top;	// Top digit
			sDst[idx] = '0' + tmp1;			// Add digit to buffer
			idx++;
			iSrc -= tmp1 * top;				// Remove digit
			tmp1 = 1;						// Add zeros now
		}
		top /= 10;							// Go to next digit
	}

	if (idx < iDst_len)						//add terminating null (if we can)
		sDst[idx] = '\0';
	return (idx);
}



static MX_STRING FCI_TOSTRING(MX_SLONG iSrc1, MX_STRING sDst, MX_UINT16 iDst_len)
{
	MX_UINT8 tmp1;

	MX_SLONG iSrc = iSrc1;

	#ifdef MX_STRF_LONG
		unsigned long top = 1000000000; 	// Maximum power of 10 less than 4294967296
	#else
		unsigned short top = 10000; 		// Maximum power of 10 less than 65536
	#endif

	MX_UINT16 idx = 0;

	if (iDst_len == 0) return sDst;

	//copy source 1 into destination:
	//minus sign
	if (iSrc < 0)
	{
		sDst[0] = '-';
		idx++;
		iSrc = -iSrc;
	}

	tmp1 = 0;    // Nothing added yet
	if (iSrc == 0) // Force showing zero
	{
		tmp1 = 1;
		top = 1;
	}
	while (( idx < iDst_len) && (top > 0))
	{
		#ifdef MX_STRF_LONG
		if (((unsigned long)iSrc >= top) || (tmp1))
		#else
		if (((unsigned)iSrc >= top) || (tmp1))
		#endif
		{
			#ifdef MX_STRF_LONG
			tmp1 = (unsigned long)iSrc / top;	// Top digit
			#else
			tmp1 = (unsigned)iSrc / top;	// Top digit
			#endif
			sDst[idx] = '0' + tmp1;			// Add digit to buffer
			idx++;
			iSrc -= tmp1 * top;				// Remove digit
			tmp1 = 1;						// Add zeros now
		}
		top /= 10;							// Go to next digit
	}

	if (idx < iDst_len)						//add terminating null (if we can)
		sDst[idx] = '\0';
	return (sDst);
}


static void FCI_TOLOWER(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_STRING sDst, MX_UINT16 iDst_len)
{
	if (iDst_len == 0) return;
	MX_UINT16 idx;
	MX_UINT16 ch;

	if (iSrc_len < iDst_len) iSrc_len = iDst_len; // Bound so cant overflow dest
	//copy source into destination and change to lower case
	for (idx=0; idx<iSrc_len; idx++)
	{
		ch = sSrc[idx];
		if ((ch >= 'A') && (ch <= 'Z'))
		{
			ch ^= 0x20;
		}
		sDst[idx] = ch;
		if (ch == 0)
		{
			break;
		}
	}
	if (idx < iDst_len)						//add terminating null (if we can)
		sDst[idx] = '\0';
}


static void FCI_TOUPPER(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_STRING sDst, MX_UINT16 iDst_len)
{
	if (iDst_len == 0) return;
	MX_UINT16 idx;
	MX_UINT16 ch;

	if (iSrc_len < iDst_len) iSrc_len = iDst_len; // Bound so cant overflow dest
	//copy source into destination and change to upper case
	for (idx=0; idx<iSrc_len; idx++)
	{
		ch = sSrc[idx];
		if ((ch >= 'a') && (ch <= 'z'))
		{
			ch ^= 0x20;
		}
		sDst[idx] = ch;
		if (ch == 0)
		{
			break;
		}
	}
	if (idx < iDst_len)						//add terminating null (if we can)
		sDst[idx] = '\0';
}


static MX_UINT8 FCI_COMPARE(MX_STRING sSrc1, MX_UINT16 iSrc1_len, MX_STRING sSrc2, MX_UINT16 iSrc2_len, MX_UINT8 iNoCase)
{
	MX_UINT16 idx = 0;
	MX_UINT8 ch1, ch2;

	while ((idx < iSrc1_len)&&(idx < iSrc2_len))
	{
		ch1 = sSrc1[idx];
		ch2 = sSrc2[idx];

		if (iNoCase)
		{
			if ((ch1 >= 'a') && (ch1 <= 'z'))
				ch1 = (ch1 & 0xDF);

			if ((ch2 >= 'a') && (ch2 <= 'z'))
				ch2 = (ch2 & 0xDF);
		}

		if (ch2 == 0)
		{
			if (ch1 == 0)
				return (0);				//end of iSrc1 as well, so we have a match
			else
				return (1);				//reached the end of iSrc2, but still more of iSrc1
		}
		else if (ch1 == 0)
			return (255);				//end of iSrc1 but not at end of iSrc2, so return -1
		else if (ch1 < ch2)
			return(255);
		else if (ch1 > ch2)
			return(1);
		// here if they are the same so far
		++idx;
	}

	// We've reached the end of one of the buffers without encountering a null terminator
	if (iSrc1_len > iSrc2_len)
	{
		if (sSrc1[idx] == 0)
			return (0);				// the next char in the longer buffer is a null so that's a match
		else
			return (1);
	}
	else if (iSrc1_len < iSrc2_len)
	{
		if (sSrc2[idx] == 0)
			return (0);
		else
			return (255);
	}
	return (0);						// the two buffers are the same size and contain the same data
}


static MX_STRING FCI_FLOAT_TO_STRING(MX_FLOAT Number, MX_UINT8 Precision, MX_STRING String, MX_UINT16 MSZ_String)
{
	MX_SLONG whole;
	MX_UINT8 idx;
	MX_UINT16 stringidx = 0;
	MX_FLOAT temp = 0.5;
	MX_FLOAT real;
	MX_UINT8 temp_string[12];

	//Rounding value calculation
	for (idx = 0; idx < Precision; idx++) temp *= 0.1;

	if (Number < 0)
	{
		Number = -Number;
		String[stringidx++] = '-';
	}
	Number += temp;							//Add rounding value

	temp = floor(Number);					//Convert to whole integer
	whole = (MX_SLONG)temp;						//Convert whole number back to floating point

	real = Number - temp;				//Subtract whole number from floating point number

	FCI_TOSTRING(whole, temp_string, sizeof(temp_string));		//Convert integer numbers to strings

	for (idx=0; temp_string[idx]; idx++)						//Copy whole part of number to string
	{
		if(stringidx < MSZ_String)
		{
			String[stringidx] = temp_string[idx];
			stringidx = stringidx + 1;
		}
	}

	if (Precision > 0)
	{
		if(stringidx < MSZ_String)						//Add decimal point to string
		{
			String[stringidx] = '.';
			stringidx = stringidx + 1;
		}

		for (idx = 0; idx < Precision; idx++)			//Output Real Part Of Number
		{
			if (stringidx >= MSZ_String)
				break;

			real = real * 10;
			whole = (MX_SLONG)real;						//Convert to whole integer
			temp = (MX_FLOAT)whole;						//Convert whole number back to floating point
			real = real - temp;							//Subtract whole number from floating point number

			String[stringidx] = '0' + whole;
			stringidx = stringidx + 1;
		}
	}

	if(stringidx < MSZ_String)									//Add null termination to string
	{
		String[stringidx] = 0;
	}

	return String;
}


static MX_STRING FCI_NUMBER_TO_HEX(MX_ULONG Number, MX_STRING String, MX_UINT16 MSZ_String)
{
	MX_UINT16 stringidx;
	MX_UINT16 idx = 0;
	MX_UINT16 temp;
	MX_UINT8 digit[8] = {0,0,0,0,0,0,0,0};

	#ifdef MX_STRF_LONG
		MX_UINT32 num = Number;
	#else
		MX_UINT16 num = Number;
	#endif

	String[0] = 0;

	//Check that output string is long enough to store result
	if(((Number >> 8) > 0xFF) && (MSZ_String < 10))
		return String;

	if((Number > 0xFF) && (MSZ_String < 6))
		return String;

	if((Number <= 0xFF) && (MSZ_String < 4))
		return String;

	//Initialise start of string with hexadecimal indicator
	String[0] = '0';
	String[1] = 'x';

	//Calculate hex values
	do
	{
		temp = num % 16;
		num = num >> 4;

		if(temp > 9)
		{
			temp = temp - 10;
			digit[idx] = temp + 'A';
		}
		else
			digit[idx] = temp + '0';

		idx = idx + 1;
	} while (num > 0);

	//Force string to be at least 2 digits - matches what the simulation does
	if(idx == 1)
	{
		digit[1] = '0';
		idx = 2;
	}

	//Copy Hex values over to output string
	for (stringidx = 2; stringidx < (idx + 2); stringidx++)
		String[stringidx] = digit[idx - (stringidx - 1)];

	//Add null termination to string
	if(stringidx < MSZ_String)
	{
		String[stringidx] = 0;
	}

	return String;
}


static MX_SINT32 FCI_STRING_TO_INT(MX_STRING String, MX_UINT16 MSZ_String)
{
	MX_UINT8 bNegative = 0;
	MX_UINT16 idx = 0;
	MX_SINT32 RetVal = 0;

	//While string contains none numeric characters
	while (idx < MSZ_String && (String[idx] < '0' || String[idx] > '9'))
	{
		//Is number negative
		if(String[idx] == '-')
		{
			bNegative = 1;
			idx = idx + 1;
			break;
		}
		idx = idx + 1;
	}

	//While string contains a valid number
	while (idx < MSZ_String && String[idx] >= '0' && String[idx] <= '9')
	{
		//Pull MX_UINT8acter from string and add to running total
		RetVal = (long) RetVal * 10;
		RetVal = (long) RetVal + (String[idx] - '0');
		idx = idx + 1;
	}

	if (bNegative)
		RetVal = (long) 0 - RetVal;

	return RetVal;
}



static MX_FLOAT FCI_STRING_TO_FLOAT(MX_STRING String, MX_UINT16 MSZ_String)
{
	MX_FLOAT RetVal = 0;
	MX_FLOAT real_divider = 1;
	MX_UINT32 whole, real;			//Changed from INT 23/07/10
	MX_UINT16 idx = 0;
	//MX_UINT8 idx2 = 0;
	MX_UINT8 offset = 0;
	MX_UINT8 bNegative = 0;
	MX_UINT8 Comp_String[8];

	//Is number negative
	if(String[0] == '-')
	{
		bNegative = 1;
		offset = 1;
	}

	//Scan for decimal point
	for(idx=offset; idx<MSZ_String; idx++)
	{
		if(String[idx] == '.')
			break;
	}

	//Convert whole portion of number from string
	whole = FCI_STRING_TO_INT (String, idx);

	//No decimal point found
	if(idx == MSZ_String)
	{
		RetVal = (MX_FLOAT)whole;
		return RetVal;
	}

	//Collect real portion of number into new string
	offset = idx + 1;
	for(idx=offset; idx<MSZ_String; idx++)
	{
		if(String[idx] >= '0' && String[idx] <= '9')
		{
			Comp_String[idx - offset] = String[idx];
			real_divider = real_divider * 0.1;
		}
		else
			break;
	}

	//Convert real portion of number from string
	real = FCI_STRING_TO_INT (Comp_String, (idx - offset));

	//Adjust weighting of values and combine into one float variable
	RetVal = (MX_FLOAT)real;
	RetVal = RetVal * real_divider;
	real_divider = (MX_FLOAT)whole;
	RetVal = RetVal + real_divider;

	if (bNegative)
		RetVal = -RetVal;

	return RetVal;
}


/*=----------------------------------------------------------------------=*\
   Use :Move but do not null-terminate sSrc to sDst, max len iSrc_len
       :This differs from FCI_STRMOV() in that the bytes are copied from the
       :end of the string to the start
       :Returns length of copy
\*=----------------------------------------------------------------------=*/
static MX_UINT16 FCI_STRREV(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_STRING sDst, MX_UINT16 iDst_len)
{
  MX_UINT16 ix, len;
  FCI_GETLENGTH__x(sSrc, iSrc_len, len);
  if (len > iDst_len)
  {
    len = iDst_len;
  }
  ix = len;
  while (ix > 0)
  {
    ix--;
    sDst[ix] = sSrc[ix];
  }
  // No null terminate
  // Return length of string
  return len;
}


/*=----------------------------------------------------------------------=*\
   Use :Move but do not null-terminate sSrc to sDst, max len iSrc_len
       :Returns length of copy
\*=----------------------------------------------------------------------=*/
static MX_UINT16 FCI_STRMOV(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_STRING sDst, MX_UINT16 iDst_len)
{
  MX_UINT16 ix;
  ix = 0;
  while (ix < iSrc_len && ix < iDst_len && sSrc[ix] != '\0')
  {
    sDst[ix] = sSrc[ix];
    ix++;
  }
  // No null terminate
  // Return length of string
  return ix;
}


/*=----------------------------------------------------------------------=*\
   Use :Concatenate sDst = (sSrc1 + sSrc2)
       :sDst is always null terminated if (iDst_len > 0)
       :Returns sDst, suitable for chaining or passing to functinos
\*=----------------------------------------------------------------------=*/
static void FCI_SHEAD(MX_STRING sSrc1, MX_UINT16 iSrc1_len, MX_STRING sSrc2, MX_UINT16 iSrc2_len, MX_STRING sDst, MX_UINT16 iDst_len)
{
  MX_UINT16 len, strt;

  len = 0;
  if (sSrc2 == sDst)
  {
    FCI_GETLENGTH__x(sSrc1, iSrc1_len, strt);
    if (strt < iDst_len)
    {
      // Copy second, in reverse
      // len = FCI_STRREV(sSrc2, iSrc2_len, sDst + strt, iDst_len - strt);
      FCI_GETLENGTH__x(sSrc2, iSrc2_len, len);
      if (len > (iDst_len - strt))
      {
        len = (iDst_len - strt); // Length of string to copy to
      }
      iSrc2_len = strt + len; // Use no longer needed var as an offset
      strt = len;
      while (strt > 0)
      {
        strt--;
        iSrc2_len--;
        sDst[iSrc2_len] = sSrc2[strt];
      }
      // Move first
      FCI_STRMOV__x(sSrc1, iSrc1_len, sDst, iDst_len, strt);
      len += strt;
    }
    else
    {
      // Copy first
      FCI_STRMOV__x(sSrc1, iSrc1_len, sDst, iDst_len, len);
    }
  }
  else
  {
    // Copy first
    FCI_STRMOV__x(sSrc1, iSrc1_len, sDst, iDst_len, len);
    // Copy second
    if (len < iDst_len)
    {
      sSrc1 = sDst + len; // make temp copies in no longer used variables
      iSrc1_len = iDst_len - len;
      FCI_STRMOV__x(sSrc2, iSrc2_len, sSrc1, iSrc1_len, strt);
      len += strt;
    }
  }
  // Terminate (only if can)
  if (len < iDst_len)
  {
    sDst[len] = '\0';
  }
}


/*=----------------------------------------------------------------------=*\
   Use :Copy and null-terminate sSrc to sDst, max len iSrc_len
       :sDst is always null terminated if (iDst_len > 0)
       :Returns sDst, suitable for chaining or passing to functinos
\*=----------------------------------------------------------------------=*/
static void FCI_SCOPY(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_STRING sDst, MX_UINT16 iDst_len)
{
  MX_UINT16 len;

  // Move first
  FCI_STRMOV__x(sSrc, iSrc_len, sDst, iDst_len, len);
  // Terminate (only if can)
  if (len < iDst_len)
  {
    sDst[len] = '\0';
  }
}


/*=----------------------------------------------------------------------=*\
   Use :Scans a string to see if it contains a specific substring.
       :Returns index if found, otherwise returns -1.
       :
       :Parameters for macro Contains:
       :  StrData[1000] : Data string to scan
       :  StrMatch[1000] : String to look for in the data
       :  Position : Starting index position
       :
       :Returns : Index position of match
\*=----------------------------------------------------------------------=*/
MX_SINT16 FCI_CONTAINS(MX_CHAR *FCL_STRDATA, MX_UINT16 FCLsz_STRDATA, MX_CHAR *FCL_STRMATCH, MX_UINT16 FCLsz_STRMATCH, MX_UINT16 FCL_IDX)
{
	MX_UINT16 FCL_SUBIDX = (0x0);
	MX_UINT16 FCL_LEN;
	MX_UINT16 FCL_SUBLEN;
	MX_SINT16 FCR_RETVAL = -1;

	FCL_LEN = FCI_GETLENGTH(FCL_STRDATA, FCLsz_STRDATA);
	FCL_SUBLEN = FCI_GETLENGTH(FCL_STRMATCH, FCLsz_STRMATCH);

	while (FCL_IDX < FCL_LEN)
	{
		if (FCL_STRDATA[FCL_IDX] == FCL_STRMATCH[FCL_SUBIDX])
		{
			FCL_SUBIDX = FCL_SUBIDX + 1;

			if (FCL_SUBIDX == FCL_SUBLEN)
			{
				FCR_RETVAL = FCL_IDX + 1 - FCL_SUBLEN;
				goto FCC_Contains_A;
			}
		}
		else
		{
			if (FCL_SUBIDX)
			{
				FCL_IDX = FCL_IDX - FCL_SUBIDX;
			}
	  		FCL_SUBIDX = 0;
		}

		FCL_IDX = FCL_IDX + 1;
	}

FCC_Contains_A:
  ;

  return (FCR_RETVAL);

}


/*=----------------------------------------------------------------------=*\
   Use :Takes an ASCII string chops up into segments using the delimiter string, returns the indexed segment
       :
       :Parameters for macro ExplodeToStringArray:
       :  StringInput[20] : Data string e.g. "1,2,3,4"
       :  Delimiter[20] : Delimiting string for example ","
       :  Index : Section index to return
       :  Retval[20] : Data string to return
       :
       :Returns : void
\*=----------------------------------------------------------------------=*/
void FCI_SPLITSTRING(MX_CHAR *FCL_STRINGINPUT, MX_UINT16 FCLsz_STRINGINPUT, MX_CHAR *FCL_DELIMITER, MX_UINT16 FCLsz_DELIMITER, MX_UINT16 FCL_INDEX, MX_CHAR *FCL_RETVAL, MX_UINT16 FCLsz_RETVAL)
{
	MX_UINT16 FCL_LEN_DELIM = FCI_GETLENGTH(FCL_DELIMITER, FCLsz_DELIMITER);
    MX_UINT16 FCL_START = 0;
    MX_UINT16 FCL_END = 0;

	FCL_RETVAL[0] = 0;

    while (FCL_INDEX > 0)
    {
    	FCL_START = FCI_CONTAINS(FCL_STRINGINPUT, FCLsz_STRINGINPUT, FCL_DELIMITER, FCLsz_DELIMITER, FCL_START);
    	if (FCL_START >= 0)
    	{
    		FCL_START = FCL_START + FCL_LEN_DELIM;		//Point to first character after delimiter
    		FCL_INDEX--;
		}
    	else
    	{
    		FCL_INDEX = 0;
		}
    }

	if (FCL_START >= 0)
	{
	    FCL_END = FCI_CONTAINS(FCL_STRINGINPUT, FCLsz_STRINGINPUT, FCL_DELIMITER, FCLsz_DELIMITER, FCL_START);

		if (FCL_END > 0)
    		FCI_MIDSTRING(FCL_STRINGINPUT, FCLsz_STRINGINPUT, FCL_START, (FCL_END - FCL_START), FCL_RETVAL, FCLsz_RETVAL);
	}
}


/*=----------------------------------------------------------------------=*\
   Use :Takes an ASCII string and using a delimiter converts it into an array of integers.
       :Returns the number of values discovered and placed into the DataArray,
       :e.g. "1,2,3,4" would become {1,2,3,4}
       :
       :Parameters for macro ExplodeToINTArray:
       :  StringInput[20] : Data string e.g. "1,2,3,4"
       :  Delimiter : Delimiting character byte for example ','
       :  DataArray[100] : Data array to hold the numberic values found
       :  MaxCount : Maximum number of values to return
       :
       :Returns : MX_UINT16
\*=----------------------------------------------------------------------=*/
void FCI_EXPLODETOINTARRAY(MX_CHAR *FCL_STRINGINPUT, MX_UINT16 FCLsz_STRINGINPUT, MX_UINT8 FCL_DELIMITER, MX_UINT16 FCL_MAXCOUNT, MX_UINT16 *FCL_DATAARRAY, MX_UINT16 FCLsz_DATAARRAY)
{
  MX_CHAR FCL_TEMPSTR[20];
  MX_UINT16 FCL_IDX = (0x0);
  MX_UINT16 FCL_LEN;
  MX_UINT8 FCL_TSIDX = (0x0);
  MX_UINT16 FCR_RETVAL;

  FCR_RETVAL = 0;

  FCL_LEN = FCI_GETLENGTH(FCL_STRINGINPUT, FCLsz_STRINGINPUT);

  while (FCL_IDX < FCL_LEN)
  {
    if (FCL_STRINGINPUT[FCL_IDX] == FCL_DELIMITER)
    {
      FCL_TEMPSTR[FCL_TSIDX] = 0;
      FCL_TSIDX = 0;
      FCL_DATAARRAY[FCR_RETVAL] = FCI_STRING_TO_INT(FCL_TEMPSTR, 20);
      FCR_RETVAL = FCR_RETVAL + 1;

      if (FCR_RETVAL == FCL_MAXCOUNT)
      {
        goto FCC_ExplodeToINTArray_A;
      }

    }
    else
    {
      if (FCL_TSIDX < 19)
      {
        FCL_TEMPSTR[FCL_TSIDX] = FCL_STRINGINPUT[FCL_IDX];
        FCL_TSIDX = FCL_TSIDX + 1;
      }
    }

    FCL_IDX = FCL_IDX + 1;
  }

  if (FCL_TSIDX > 0)
  {
    FCL_TEMPSTR[FCL_TSIDX] = 0;
    FCL_TSIDX = 0;
    FCL_DATAARRAY[FCR_RETVAL] = FCI_STRING_TO_INT(FCL_TEMPSTR, 20);
    FCR_RETVAL = FCR_RETVAL + 1;
  }

FCC_ExplodeToINTArray_A:
  ;
}

