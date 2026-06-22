// CRC: 0000000000000000000000000000000000000000000000000000000000000000
// REVISION: 1.0
// GUID: D0E1F2A3-B4C5-6789-3456-890123456789
// DATE: 22\06\2026
// DIR: CAL\RE\RE_CAL_String.c
/* Flowcode CAL String - Renesas RA (ARM Cortex-M4, identical to STARM) */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned char MX_UINT8;
typedef unsigned short MX_UINT16;
typedef unsigned int MX_UINT32;
typedef signed char MX_SINT8;
typedef signed short MX_SINT16;
typedef signed int MX_SINT32;
typedef unsigned char* MX_STRING;
typedef float MX_FLOAT;

MX_STRING FC_CAL_String_Copy_(MX_STRING Dest, MX_STRING Src)
{
    return (MX_STRING)strcpy((char*)Dest, (const char*)Src);
}

MX_STRING FC_CAL_String_Append_(MX_STRING Dest, MX_STRING Src)
{
    return (MX_STRING)strcat((char*)Dest, (const char*)Src);
}

MX_SINT16 FC_CAL_String_Compare_(MX_STRING Str1, MX_STRING Str2)
{
    return (MX_SINT16)strcmp((const char*)Str1, (const char*)Str2);
}

MX_UINT16 FC_CAL_String_Length_(MX_STRING Str)
{
    return (MX_UINT16)strlen((const char*)Str);
}

MX_STRING FC_CAL_String_Find_(MX_STRING Haystack, MX_STRING Needle)
{
    return (MX_STRING)strstr((const char*)Haystack, (const char*)Needle);
}

MX_SINT32 FC_CAL_String_ToInt_(MX_STRING Str)
{
    return (MX_SINT32)atoi((const char*)Str);
}

MX_FLOAT FC_CAL_String_ToFloat_(MX_STRING Str)
{
    return (MX_FLOAT)atof((const char*)Str);
}

void FC_CAL_String_FromInt_(MX_STRING Dest, MX_SINT32 Value)
{
    sprintf((char*)Dest, "%d", (int)Value);
}

void FC_CAL_String_FromFloat_(MX_STRING Dest, MX_FLOAT Value, MX_UINT8 Decimals)
{
    char fmt[8];
    sprintf(fmt, "%%.%df", (int)Decimals);
    sprintf((char*)Dest, fmt, (double)Value);
}

MX_UINT8 FC_CAL_String_GetChar_(MX_STRING Str, MX_UINT16 Index)
{
    return (MX_UINT8)Str[Index];
}

void FC_CAL_String_SetChar_(MX_STRING Str, MX_UINT16 Index, MX_UINT8 Ch)
{
    Str[Index] = (unsigned char)Ch;
}
