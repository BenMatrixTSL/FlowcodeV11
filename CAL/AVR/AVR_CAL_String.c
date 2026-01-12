// CRC: 77485F5F6A861F9125D47827B4DE492656C5431E478E8046055FD2257F64F1F376C6BA0AD4FE2B3B61BD43C22CF28226E5692F76D658C38B8E817910D72F5A57275AD8A0418324DB0C3CAEE8E7DA69877549D1902EEFF251ECA820AC05B6D91F7766A5C22ECD65B974388C2AA254DF947FEEE0BC75E140404E4887DAFEE4093E34F271877483C0FC152E7A405DE9B01E84AF36D1A0E209AFBC9CB76A09AEAA054B066FE0AF5B7B80549D34A0D5AD11F376825946F63240AC10D33D132DB942E1604F9ADA267CD8F627A8E1A814A6FBB04A61C0D2CB77CF29
// REVISION: 6.0
// GUID: 49FE8FFE-F04F-4E20-8E92-D4585D519B00
// DATE: 01\04\2025
// DIR: CAL\AVR\AVR_CAL_String.c
/*********************************************************************
 *                  Flowcode CAL String File
 *
 * File: AVR_CAL_String.c
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
 * 300524 | MW | Added advance string functions created by ST
 * 300524 | MW | Fixed bug within FCI_STRING_TO_INT modified by ST
 * 300524 | MW | Fixed bug within FCI_STRING_TO_FLOAT modified by ST
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
// Advance string functions

static void FCI_REMOVEFROMSTRING(MX_STRING sMain, MX_UINT16 iMainLen, MX_UINT16 iCount, MX_UINT16 iPos, MX_STRING sReturn, MX_UINT16 iReturnLen);
static MX_SINT16 FCI_CONTAINS(MX_CHAR *FCL_STRDATA, MX_UINT16 FCLsz_STRDATA, MX_CHAR *FCL_STRMATCH, MX_UINT16 FCLsz_STRMATCH, MX_UINT16 FCL_IDX);
static void FCI_SPLITSTRING(MX_CHAR *FCL_STRINGINPUT, MX_UINT16 FCLsz_STRINGINPUT, MX_CHAR *FCL_DELIMITER, MX_UINT16 FCLsz_DELIMITER, MX_UINT16 INDEX, MX_CHAR *FCL_RETVAL, MX_UINT16 FCLsz_RETVAL);
static void FCI_SPLITSTRING(MX_CHAR *FCL_STRINGINPUT, MX_UINT16 FCLsz_STRINGINPUT, MX_CHAR *FCL_DELIMITER, MX_UINT16 FCLsz_DELIMITER, MX_UINT16 FCL_INDEX, MX_CHAR *FCL_RETVAL, MX_UINT16 FCLsz_RETVAL);
static void FCI_EXPLODETOINTARRAY(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_STRING sDelimiters, MX_UINT16 iDelimiters_len, MX_UINT8 iMaxCount, MX_SINT16 iArray[], MX_UINT8 pArraySize);
static void FCI_EXPLODETOFLOATARRAY(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_STRING sDelimiters, MX_UINT16 iDelimiters_len, MX_UINT8 iMaxCount, MX_FLOAT fArray[], MX_UINT8 iArraySize);
static void FCI_IMPLODEFROMFLOATARRAY(MX_FLOAT fArray[], MX_UINT16 iArraySize, MX_CHAR cDelimiter, MX_UINT8 iMaxCount, MX_UINT8 iPrecision, MX_STRING sReturn, MX_UINT16 iReturn_len);
static void FCI_IMPLODEFROMINTARRAY(MX_SINT16 iArray[], MX_UINT8 pArraySize, MX_CHAR cDelimiter, MX_UINT8 iMaxCount, MX_STRING sReturn, MX_UINT16 iReturn_len);
static void FCI_INSERTSTRING(MX_STRING sMain, MX_UINT16 iMainLen, MX_STRING sSub, MX_UINT16 iSubLen, MX_UINT16 iPos, MX_STRING sReturn, MX_UINT16 iReturnLen);
static void FCI_FLOATTOFORMATTEDSTRING(MX_FLOAT fVal, MX_UINT8 iMinLen, MX_CHAR cPad, MX_UINT8 iPrecision, MX_STRING sReturn, MX_UINT16 iReturnLen);
static void FCI_INTTOFORMATTEDSTRING(MX_UINT16 iVal, MX_UINT8 iMinLen, MX_CHAR cPad, MX_STRING sReturn, MX_UINT16 iReturnLen);
static MX_UINT16 FCI_SEARCHANDREPLACE(MX_STRING sMain, MX_UINT16 iMainLen, MX_STRING sSearch, MX_UINT16 iSearchLen, MX_STRING sReplace, MX_UINT16 iReplaceLen);
static void FCI_REMOVEFROMSTRING(MX_STRING sMain, MX_UINT16 iMainLen, MX_UINT16 iCount, MX_UINT16 iPos, MX_STRING sReturn, MX_UINT16 iReturnLen);

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
	while (idx < MSZ_String && (String[idx] != 0) && (String[idx] < '0' || String[idx] > '9'))
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
       :Returns sDst, suitable for chaining or passing to functions
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
       :Returns sDst, suitable for chaining or passing to functions
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
       :Returns starting character index if found, otherwise returns -1.
       :
       :Parameters for macro Contains:
       :StrData[1000] : Data string to scan
       :StrMatch[1000] : String to look for in the data
       :Position : Starting index position
       :
       :Returns : Index position of match
\*=----------------------------------------------------------------------=*/
static MX_SINT16 FCI_CONTAINS(MX_CHAR *FCL_STRDATA, MX_UINT16 FCLsz_STRDATA, MX_CHAR *FCL_STRMATCH, MX_UINT16 FCLsz_STRMATCH, MX_UINT16 FCL_IDX)
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
				break;
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

  return (FCR_RETVAL);

}

/*=----------------------------------------------------------------------=*\
   Use :Takes an ASCII string splits up, returns the string before the first delimiter
       :
       :Parameters for macro SplitString:
       :  StringInput[20] : Data string e.g. "1,2,3,4"
       :  Delimiter[20] : Delimiting string for example ","
       :  Index : starting point of the string to return
       :  Retval[20] : Data string to return
       :
       :Returns : void
\*=----------------------------------------------------------------------=*/
static void FCI_SPLITSTRING(MX_CHAR *FCL_STRINGINPUT, MX_UINT16 FCLsz_STRINGINPUT, MX_CHAR *FCL_DELIMITER, MX_UINT16 FCLsz_DELIMITER, MX_UINT16 FCL_INDEX, MX_CHAR *FCL_RETVAL, MX_UINT16 FCLsz_RETVAL)
{
    MX_UINT16 FCL_LEN_DELIM = FCI_GETLENGTH(FCL_DELIMITER, FCLsz_DELIMITER);
    MX_SINT16 FCL_START = 0;  // Changed from MX_UINT16 to MX_SINT16
    MX_SINT16 FCL_END = 0;    // Changed from MX_UINT16 to MX_SINT16
    FCL_RETVAL[0] = 0;
    MX_UINT16 FCL_ELEMENT_COUNT = 0;
    
    // Count total number of elements first
    MX_SINT16 temp_pos = 0;
    MX_UINT16 element_count = 1;  // Start with 1 for the first element
    while (temp_pos >= 0) {
	 
        temp_pos = FCI_CONTAINS(FCL_STRINGINPUT, FCLsz_STRINGINPUT, FCL_DELIMITER, FCLsz_DELIMITER, temp_pos);
        if (temp_pos >= 0) {
            element_count++;
            temp_pos += FCL_LEN_DELIM;
				  
        }
		 
	  
					
   
    }
    
    // Reset for actual processing
    FCL_START = 0;
    
    // If we're looking for an element beyond what exists, return empty
    if (FCL_INDEX >= element_count) {
        FCL_RETVAL[0] = '\0';
        return;
    }
    
    // Find the start position of our target element
    while (FCL_ELEMENT_COUNT < FCL_INDEX) {
        FCL_START = FCI_CONTAINS(FCL_STRINGINPUT, FCLsz_STRINGINPUT, FCL_DELIMITER, FCLsz_DELIMITER, FCL_START);
        if (FCL_START >= 0) {  // This check is now valid since FCL_START is signed
            FCL_START = FCL_START + FCL_LEN_DELIM;  // Point to first character after delimiter
            FCL_ELEMENT_COUNT++;
        } else {
            // Should not happen if we validated index above
            FCL_RETVAL[0] = '\0';
            return;
        }
    }
    
    // Now find the end of our target element
    FCL_END = FCI_CONTAINS(FCL_STRINGINPUT, FCLsz_STRINGINPUT, FCL_DELIMITER, FCLsz_DELIMITER, FCL_START);
    
    if (FCL_END > 0) {  // FCL_END is signed, so this check is meaningful
        // Found another delimiter - extract element up to delimiter
        FCI_MIDSTRING(FCL_STRINGINPUT, FCLsz_STRINGINPUT, FCL_START, (FCL_END - FCL_START), FCL_RETVAL, FCLsz_RETVAL);
    } else {
        // This is the last element - extract to end of string
        MX_UINT16 stringLen = FCI_GETLENGTH(FCL_STRINGINPUT, FCLsz_STRINGINPUT);
        FCI_MIDSTRING(FCL_STRINGINPUT, FCLsz_STRINGINPUT, FCL_START, (stringLen - FCL_START), FCL_RETVAL, FCLsz_RETVAL);
    }
}

/*=----------------------------------------------------------------------=*\
   Use :Takes an ASCII string and using a delimiter converts it into an array of integers.
       :Returns the number of values discovered and placed into the DataArray,
       :e.g. "1,2,3,4" would become {1,2,3,4}
       :
       :Parameters for macro ExplodeToINTArray:
       :sSrc[20] : Data string e.g. "1,2,3,4"
       :sDelimiters : Delimiting character string for example ","
       :iArray[100] : Data array to hold the numberic values found
       :iMaxCount : Maximum number of values to return
       :
       :Returns : void
\*=----------------------------------------------------------------------=*/

static void FCI_EXPLODETOINTARRAY(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_STRING sDelimiters, MX_UINT16 iDelimiters_len, MX_UINT8 iMaxCount, MX_SINT16 iArray[], MX_UINT8 pArraySize)
{
  int iArrayIdx = 0;
  int iStringLen = FCI_GETLENGTH(sSrc, iSrc_len);
  MX_CHAR sTemp[20];
  int iSourceCharIdx = 0;
  int iTempCharIdx = 0;
  
  while ((iSourceCharIdx < iStringLen) && (iTempCharIdx < 20) && (iArrayIdx < iMaxCount) && (iArrayIdx < pArraySize))
  {
    if (sSrc[iSourceCharIdx] == sDelimiters[0])
    {
      sTemp[iTempCharIdx] = 0; //string terminator
      iArray[iArrayIdx] = FCI_STRING_TO_INT(sTemp, 20);
      iArrayIdx++;
      iTempCharIdx = 0;
    }
    else
    {
      sTemp[iTempCharIdx] = sSrc[iSourceCharIdx];
      iTempCharIdx++;
    }
    
    iSourceCharIdx++;
  }
  
  if ((iTempCharIdx < 20) && (iArrayIdx < iMaxCount) && (iArrayIdx < pArraySize))
  {
    sTemp[iTempCharIdx] = 0; //string terminator
    iArray[iArrayIdx] = FCI_STRING_TO_INT(sTemp, 20);
  }
}


/*=----------------------------------------------------------------------=*\
   Use :Takes an ASCII string and using a delimiter converts it into an array of floats.
       :Returns the number of values discovered and placed into the FloatArray,
       :e.g. "1.23,2.345,3456,4.45" would become {1.23,2.345,3456,4.45}
       :
       :Parameters for macro ExplodeToFLOATArray:
       :sSrc[20] : Data string e.g. "1,2,3,4"
       :sDelimiters : Delimiting character string for example ","
       :fArray[] : Data array to hold the numberic values found
       :iMaxCount : Maximum number of values to return
       :
       :Returns : void
\*=----------------------------------------------------------------------=*/

static void FCI_EXPLODETOFLOATARRAY(MX_STRING sSrc, MX_UINT16 iSrc_len, MX_STRING sDelimiters, MX_UINT16 iDelimiters_len, MX_UINT8 iMaxCount, MX_FLOAT fArray[], MX_UINT8 iArraySize)
{
  int iArrayIdx = 0;
  int iStringLen = FCI_GETLENGTH(sSrc, iSrc_len);
  MX_CHAR sTemp[20];
  int iSourceCharIdx = 0;
  int iTempCharIdx = 0;
  
  while ((iSourceCharIdx < iStringLen) && (iTempCharIdx < 20) && (iArrayIdx < iMaxCount) && (iArrayIdx < iArraySize))
  {
    if (sSrc[iSourceCharIdx] == sDelimiters[0])
    {
      sTemp[iTempCharIdx] = 0; //string terminator
      fArray[iArrayIdx] = FCI_STRING_TO_FLOAT(sTemp, 20);
      iArrayIdx++;
      iTempCharIdx = 0;
    }
    else
    {
      sTemp[iTempCharIdx] = sSrc[iSourceCharIdx];
      iTempCharIdx++;
    }
    
    iSourceCharIdx++;
  }
  
  if ((iTempCharIdx < 20) && (iArrayIdx < iMaxCount) && (iArrayIdx < iArraySize))
  {
    sTemp[iTempCharIdx] = 0; //string terminator
    fArray[iArrayIdx] = FCI_STRING_TO_INT(sTemp, 20);
  }
}

/*=----------------------------------------------------------------------=*\
   Use :Takes a float array and using a delimiter converts it into string with delimiters.
       :e.g. [1.23,2.345,3456.1,4.45] would become "1.23,2.345,3456.1,4.45"
       :
       :  Parameters for macro ImplodeFromFloatArray:
       :  fArray[] : Float array e.g. [1.12,2.23,3.45,4.0]
       :  cDelimiter : Delimiting char for example ','
       :  sReturn : String to hold the numberic values found
       :  iMaxCount : Maximum number of values to return
       :
       :Returns : void
\*=----------------------------------------------------------------------=*/


static void FCI_IMPLODEFROMFLOATARRAY(MX_FLOAT fArray[], MX_UINT16 iArraySize, MX_CHAR cDelimiter, MX_UINT8 iMaxCount, MX_UINT8 iPrecision, MX_STRING sReturn, MX_UINT16 iReturn_len)
{
  int iArrayIdx = 0;
  MX_CHAR sTemp[20];
  sReturn[0] = 0;
  
  while ((iArrayIdx < iMaxCount) && (iArrayIdx < iArraySize))
  {
    if (iArrayIdx != 0)
    {
      sTemp[0] = cDelimiter;
      sTemp[1] = 0;
      FCI_SHEAD(sReturn, iReturn_len, sTemp, 1, sReturn, iReturn_len);
    }
    FCI_FLOAT_TO_STRING(fArray[iArrayIdx], iPrecision, sTemp, 20);
    FCI_SHEAD(sReturn, iReturn_len, sTemp, 20, sReturn, iReturn_len);
    iArrayIdx++;
  }
}



/*=----------------------------------------------------------------------=*\
   Use :Takes an int array and using a delimiter converts it into string with delimiters.
       :e.g. [1,2,1234,10] would become "1,2,1234,10"
       :
       :Parameters for macro ImplodeFromIntArray:
       :iArray[] : Int array e.g.  [1,2,1234,10]
       :cDelimiter : Delimiting char for example ','
       :String[20] : String to hold the numberic values found
       :iMaxCount : Maximum number of values to return
       :
       :Returns : void
\*=----------------------------------------------------------------------=*/

static void FCI_IMPLODEFROMINTARRAY(MX_SINT16 iArray[], MX_UINT8 pArraySize, MX_CHAR cDelimiter, MX_UINT8 iMaxCount, MX_STRING sReturn, MX_UINT16 iReturn_len)
{
  int iArrayIdx = 0;
  MX_CHAR sTemp[20];
  sReturn[0] = 0;
  
  while ((iArrayIdx < iMaxCount) && (iArrayIdx < pArraySize))
  {
    if (iArrayIdx != 0)
    {
      sTemp[0] = cDelimiter;
      sTemp[1] = 0;
      FCI_SHEAD(sReturn, iReturn_len, sTemp, 1, sReturn, iReturn_len);
    }
    FCI_TOSTRING(iArray[iArrayIdx], sTemp, 20);
    FCI_SHEAD(sReturn, iReturn_len, sTemp, 20, sReturn, iReturn_len);
    iArrayIdx++;
  }
}

/*=----------------------------------------------------------------------=*\
   Use :Takes a main string and inserts a string into the main string at the index position.
       :e.g. main string = "Hello test1", string to be inserted " World", 
	   :index = 5, main string will be "Hello World test1"
       :
       :Parameters for macro InsertString:
       :sMain[20] : Main string text e.g. "Hello test1"
       :sSub[20] : Sub string to insert in to sMain string e.g." World".
	   :iPos : Index position
       :sReturn: Main String  with the new string added to return.
       :
	   :Returns : void
\*=----------------------------------------------------------------------=*/

static void FCI_INSERTSTRING(MX_STRING sMain, MX_UINT16 iMainLen, MX_STRING sSub, MX_UINT16 iSubLen, MX_UINT16 iPos, MX_STRING sReturn, MX_UINT16 iReturnLen)
{
  // Get actual string lengths
  MX_UINT16 iMainActualLen = FCI_GETLENGTH(sMain, iMainLen);
  MX_UINT16 iSubActualLen = FCI_GETLENGTH(sSub, iSubLen);
  
  // Ensure position is within bounds
  if (iPos > iMainActualLen) {
    iPos = iMainActualLen;
  }
  
  // Calculate total required length and check if it fits
  MX_UINT16 iTotalLen = iMainActualLen + iSubActualLen;
  if (iTotalLen >= iReturnLen) {
    iTotalLen = iReturnLen - 1; // Leave room for null terminator
  }
  
  if (sMain == sReturn) {
    // Case 1: Main string is same as return buffer
    // Need to work backwards to avoid overwriting data
    
    // Make sure we have enough space in the return buffer
    if (iReturnLen <= (iMainActualLen + iSubActualLen)) {
      // Not enough space, truncate
      iMainActualLen = iReturnLen - iSubActualLen - 1;
				   
    }
    
    // Move the second part of the main string to make room for the substring
    MX_UINT16 i;
    for (i = iMainActualLen; i >= iPos && i < iReturnLen; i--) {
      if (i + iSubActualLen < iReturnLen) {
        sReturn[i + iSubActualLen] = sReturn[i];
      }
				
    }
    
    // Insert the substring
    for (i = 0; i < iSubActualLen && (iPos + i) < iReturnLen; i++) {
      sReturn[iPos + i] = sSub[i];
    }
    
    // Ensure null termination
    if (iMainActualLen + iSubActualLen < iReturnLen) {
      sReturn[iMainActualLen + iSubActualLen] = '\0';
    } else if (iReturnLen > 0) {
      sReturn[iReturnLen - 1] = '\0';
    }
  }
  else if (sSub == sReturn) {
    // Case 2: Substring is same as return buffer
    // Need to create a temporary copy of the substring
    MX_CHAR tempSub[256]; // Assume a reasonable maximum size
    MX_UINT16 tempLen = iSubActualLen < 256 ? iSubActualLen : 255;
    
    // Copy substring to temp buffer
    MX_UINT16 i;
    for (i = 0; i < tempLen; i++) {
      tempSub[i] = sSub[i];
    }
    tempSub[tempLen] = '\0';
    
    // Clear return buffer
    sReturn[0] = '\0';
    
    // Copy first part of main string
    for (i = 0; i < iPos && i < iMainActualLen && i < iReturnLen; i++) {
      sReturn[i] = sMain[i];
    }
    
    // Copy substring from temp buffer
    MX_UINT16 returnPos = i;
						 
    for (i = 0; i < tempLen && returnPos < iReturnLen; i++, returnPos++) {
      sReturn[returnPos] = tempSub[i];
			   
    }
    
    // Copy rest of main string
    for (i = iPos; i < iMainActualLen && returnPos < iReturnLen; i++, returnPos++) {
      sReturn[returnPos] = sMain[i];
			   
	   
    }
    
    // Ensure null termination
    if (returnPos < iReturnLen) {
      sReturn[returnPos] = '\0';
    } else if (iReturnLen > 0) {
      sReturn[iReturnLen - 1] = '\0';
    }
  }
  else {
    // Case 3: All buffers are different
    // Clear return buffer
    MX_UINT16 returnPos = 0;
    
    // Copy first part of main string
    MX_UINT16 i;
    for (i = 0; i < iPos && i < iMainActualLen && returnPos < iReturnLen; i++, returnPos++) {
	   
			  
	   
      sReturn[returnPos] = sMain[i];
				 
    }
    
    // Copy substring
    for (i = 0; i < iSubActualLen && returnPos < iReturnLen; i++, returnPos++) {
	 
      sReturn[returnPos] = sSub[i];
				   
				
    }
    
    // Copy rest of main string
    for (i = iPos; i < iMainActualLen && returnPos < iReturnLen; i++, returnPos++) {
      sReturn[returnPos] = sMain[i];
							   
	   
			  
	   
				   
				 
    }
    
    // Ensure null termination
    if (returnPos < iReturnLen) {
      sReturn[returnPos] = '\0';
    } else if (iReturnLen > 0) {
      sReturn[iReturnLen - 1] = '\0';
    }
  }
}

/*=----------------------------------------------------------------------=*\
   Use :Takes an float and converts to a string with leading padded chars
       :e.g. Float = "1234.56", minimum length number = 8 (including dp), precision = 1
	   :Pad char = '0', Float value will be 001234.5
       :
       :Parameters for macro FloatToFormattedString:
       :fVal : Initial float e.g 1234.56 
       :iMinLen: Minging length of the required floatincludung the decimal point.
	   :cPad: Char required for padding.
       :iPrecision: precision of the float value within the retuned string.
	   :sReturn: String with paaded values to return.
	   :
       :Returns : void
\*=----------------------------------------------------------------------=*/

static void FCI_FLOATTOFORMATTEDSTRING(MX_FLOAT fVal, MX_UINT8 iMinLen, MX_CHAR cPad, MX_UINT8 iPrecision, MX_STRING sReturn, MX_UINT16 iReturnLen)
{
  MX_CHAR sTemp[20];
  MX_UINT8 iIdx = 0;
  MX_UINT8 iIdx2 = 0;
  sReturn[0] = 0;
  
  if (iMinLen > iReturnLen)
  {
    iMinLen = iReturnLen;
  }
  
  FCI_FLOAT_TO_STRING(fVal, iPrecision, sTemp, 20);
  MX_UINT8 iFloatLen = FCI_GETLENGTH(sTemp, 20);
  
  //padding
  while (iIdx < (iMinLen - iFloatLen))
  {
    sReturn[iIdx] = cPad;
    iIdx++;
  }
  
  //copy the value
  while ((iIdx < iReturnLen) && (iIdx2 < iFloatLen))
  {
    sReturn[iIdx] = sTemp[iIdx2];
    iIdx++;
    iIdx2++;
  }
  
  if (iIdx < iReturnLen)
  {
    sReturn[iIdx] = 0;
  }
}

/*=----------------------------------------------------------------------=*\
   Use :Takes an Int and converts to a string with leading padded chars
       :e.g. int = "1234", minimum length number = 5
	   :Pad char = '0', Int value will be 01234
       :
       :  Parameters for macro IntToFormattedString:
       :  iVal : Initial Int e.g 1234 
       :  iMinLen: Minimum length of the required Int includung the padding char.
	   :  cPad: Char required for padding.
       :  sReturn: String with paaded values to return.
	   :
       :Returns : void
\*=----------------------------------------------------------------------=*/

static void FCI_INTTOFORMATTEDSTRING(MX_UINT16 iVal, MX_UINT8 iMinLen, MX_CHAR cPad, MX_STRING sReturn, MX_UINT16 iReturnLen)
{
  MX_CHAR sTemp[20];
  MX_UINT8 iIdx = 0;
  MX_UINT8 iIdx2 = 0;
  sReturn[0] = 0;
  
  if (iMinLen > iReturnLen)
  {
    iMinLen = iReturnLen;
  }
  
  FCI_TOSTRING(iVal, sTemp, 20);
  MX_UINT8 iIntLen = FCI_GETLENGTH(sTemp, 20);
  
  //padding
  while (iIdx < (iMinLen - iIntLen))
  {
    sReturn[iIdx] = cPad;
    iIdx++;
  }
  
  //copy the value
  while ((iIdx < iReturnLen) && (iIdx2 < iIntLen))
  {
    sReturn[iIdx] = sTemp[iIdx2];
    iIdx++;
    iIdx2++;
  }
  
  if (iIdx < iReturnLen)
  {
    sReturn[iIdx] = 0;
  }
}

/*=----------------------------------------------------------------------=*\
   Use :Takes a main string and inserts a string into the main string at the index position.
       :e.g. main string = "123,Hi,World 45", string to seach is "Hi"
	   :String to repalce the search sttring with is "Hello", main string will be "123,Hello World 45"
       :
       :Parameters for macro Searchand Replace:
       :sMain[] : Main string text e.g. "Hello test1"
       :sSearch[] : String to search within sMain string e.g." Hi".
	   :sReplace[] : String to replace the search string with.
       :
       :Returns : Number of replacements made.
\*=----------------------------------------------------------------------=*/

static MX_UINT16 FCI_SEARCHANDREPLACE(MX_STRING sMain, MX_UINT16 iMainLen, MX_STRING sSearch, MX_UINT16 iSearchLen, MX_STRING sReplace, MX_UINT16 iReplaceLen)
{
  MX_UINT16 iCount = 0;
  MX_SINT16 iIdx = 0;
  MX_UINT16 iSearchIdx = 0;
  MX_UINT16 iRealSearchLen = FCI_GETLENGTH(sSearch, iSearchLen);
  MX_UINT16 iRealReplaceLen = FCI_GETLENGTH(sReplace, iReplaceLen);
  MX_SINT16 iDiff = iRealReplaceLen - iRealSearchLen;
  
  while ((iIdx < iMainLen) && (sMain[iIdx] != 0))
  {
    if (sMain[iIdx] == sSearch[iSearchIdx])
    {
      iSearchIdx++;
    
      if (iSearchIdx == iRealSearchLen)
      {
        //found it
        iCount++;
        
        if (iDiff > 0)
        {
          //replacement is larger, so make room first
          iSearchIdx = 1;
          while (iMainLen-iDiff-iSearchIdx >= iIdx)
          {
            sMain[iMainLen-iSearchIdx] = sMain[iMainLen-iDiff-iSearchIdx];
            iSearchIdx++;
          }
        }
        
        //replace the string
        iSearchIdx = 0;
        while ((iSearchIdx < iRealReplaceLen) && (iIdx - iRealSearchLen + iSearchIdx + 1 < iMainLen))
        {
          sMain[iIdx - iRealSearchLen + iSearchIdx + 1] = sReplace[iSearchIdx];
          iSearchIdx++;
        }
        
        if (iDiff < 0)
        {
          //replacement is smaller, so reduce
          iSearchIdx = iIdx + 1;
          while (iSearchIdx + iDiff < iMainLen)
          {
            if (iSearchIdx < iMainLen)
            {
              sMain[iSearchIdx + iDiff] = sMain[iSearchIdx];
            }
            else
            {
              //fill any remaining as null
              sMain[iSearchIdx + iDiff] = 0;
            }
            iSearchIdx++;
          }
        }
        
        //adjust the indexes
        iIdx = iIdx + iDiff;
        iSearchIdx = 0;
      }
    }
    else
    {
      iSearchIdx = 0;
    }
    iIdx++;
  }
  
  return iCount;
}

/*=----------------------------------------------------------------------=*\
   Use :Takes a main string and removes chars from it starting at the index position.
       :e.g. main string = "Hello test1", chars to be remove =  "test", 
	   :Total chars to be removed = 4, index will be 6, main string will be "Hello 1"
       :
       :Parameters for macro RemoveFromString:
       :sMain[20] : Main string text e.g. "Hello test1"
       :iCount : Total number of chars to rmove from the mainstring
	   :iPos : Index position of the start of chars to be removed.
       :
       :Returns : void
\*=----------------------------------------------------------------------=*/

static void FCI_REMOVEFROMSTRING(MX_STRING sMain, MX_UINT16 iMainLen, MX_UINT16 iCount, MX_UINT16 iPos, MX_STRING sReturn, MX_UINT16 iReturnLen)
{
  MX_UINT16 iIdx = 0;
  while ((iIdx < iMainLen) && (iIdx < iReturnLen) && (iIdx < iPos))
  {
    sReturn[iIdx] = sMain[iIdx];
    iIdx++;
  }
  while ((iIdx + iCount < iMainLen) && (iIdx < iReturnLen))
  {
    sReturn[iIdx] = sMain[iIdx + iCount];
    iIdx++;
  }
}

MX_UINT16 FCI_GETUTF8LEN(MX_STRING sMain, MX_UINT16 iMainLen)
{
  MX_UINT16 iCount = 0;
  MX_SINT16 iIdx = 0;
  
  while ((iIdx < iMainLen) && (sMain[iIdx] != 0))
  {
    if ((sMain[iIdx] & 0xC0) != 0x80)
    {
      iCount++;
    }
    iIdx++;
  }
  
  return iCount;
}
