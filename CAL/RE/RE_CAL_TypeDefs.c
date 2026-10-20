// CRC: 3DA5483D3EF86CFE38B5E3C960DE4A45D7171E1C33ED8B69D0B99CE1C516FF198E41DDBFD4BAE04B00E1ED2A77E166AB2796A5FA1C3C29333DB13582D41284E940F95D75065804C8A9B11F738DF98E15B86D349271CB690093B72CDBF6831B697045EACA409F8A8C58A2C3D74A1B99D9756636913E34F5318A42D13A3CD86C921917C513698B33E9570DCEAA647B79E8FE30B90CEAB803325CBBA75653F7708AAA1D7F7DCF288256549D34A0D5AD11F3D5BE0B94BB2A843920B996B7261716A909F915B8E0A5B8CF61112B2378F6127E5D3A7ED706D09BBA
// REVISION: 5.0
// GUID: A1B2C3D4-E5F6-7890-ABCD-EF1234567890
// DATE: 20\10\2026
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
