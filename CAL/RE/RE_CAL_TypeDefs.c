// CRC: 3DA5483D3EF86CFE38B5E3C960DE4A45D7171E1C33ED8B69D0B99CE1C516FF198E41DDBFD4BAE04B00E1ED2A77E166ABB82E41E3F05B9517B47821D22B91C490D5EC1178E7B1FA23A9B11F738DF98E15483843043D25A4CA93BCAB31A108CA0CEDE3387EB860E7B7B57E2420EE8A7E7BF558484D05FD394A9392028CDB4E591DE9F2AA1B028B07B9B3B9672DC3EA0366DE6E9288E08A6B768710216949EBAA1796A9755295761895549D34A0D5AD11F33C80537C6E2472D7396070C10E46CDBC841C6E39429BC936E846F4249C78524CED7B734AF21E187E
// REVISION: 1.0
// GUID: 87C85531-67FE-4F38-8512-858B4C559299
// DATE: 23\10\2026
// DIR: CAL\RE\RE_CAL_TypeDefs.c

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
