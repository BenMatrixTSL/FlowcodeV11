
/*********************************************************************
 *                  Flowcode CAL TypeDefs File
 *
 * File: RE_CAL_TypeDefs.c
 *
 * (c) 2026 Matrix TSL
 * http://www.matrixtsl.com
 *
 * Renesas RA family (ARM Cortex-M4)
 */

#include <stdbool.h>

#define MX_GLOBAL volatile

typedef bool           MX_BOOL;
typedef signed char    MX_SINT8;
typedef signed short   MX_SINT16;
typedef signed long    MX_SINT32;
typedef unsigned char  MX_UINT8;
typedef unsigned short MX_UINT16;
typedef unsigned long  MX_UINT32;
typedef char           MX_CHAR;
typedef unsigned char* MX_STRING;

typedef float          MX_FLOAT;

typedef MX_UINT16      MX_UINT;
typedef MX_SINT16      MX_SINT;

#define MX_FSINGLE float
#define MX_UINT1 	   MX_BOOL

typedef union
{
  MX_UINT32 AsLong;
  MX_UINT16 AsInt[2];
  MX_UINT8  AsByte[4];
} MX_Union32;

typedef union
{
  MX_UINT16 AsInt;
  MX_UINT8  AsByte[2];
} MX_Union16;
