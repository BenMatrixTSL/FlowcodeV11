// CRC: 3DA5483D3EF86CFE38B5E3C960DE4A452004EF23FE9DC811ABA8E416761E214DB51C67980A393B2E40EBDE7FEADD76C0B82E41E3F05B9517B47821D22B91C490D5EC1178E7B1FA23A9B11F738DF98E15CDFAFEF2B3A8D059330C67636EAC91669E38B5427395CBB80FD86822170445D4D2BB97C57CF170453E6C5650FBFF6C61A3AA78FD35E04AA0B0685BEE11D9C0D6D4EB60DEC73B5585BA53AFFF23DF3F497DE27EDF0A275890549D34A0D5AD11F33FBBABE8E641F80B0DB903DFBF04DF46B2AB2BFE0473868176AD1A7DB9B9D5F43F565616D7803A54
// REVISION: 1.0
// GUID: 8AEE2B8E-D928-4E89-ADCF-477C8FB3F580
// DATE: 23\10\2026
// DIR: CAL\RE\RE_CAL_Float.c

/* Flowcode CAL Float - Renesas RA (ARM Cortex-M4 with FPU, identical to STARM) */

#include <math.h>

typedef float MX_FLOAT;
typedef unsigned char MX_UINT8;
typedef signed int MX_SINT32;

MX_FLOAT FC_CAL_Float_Add_(MX_FLOAT A, MX_FLOAT B)      { return A + B; }
MX_FLOAT FC_CAL_Float_Sub_(MX_FLOAT A, MX_FLOAT B)      { return A - B; }
MX_FLOAT FC_CAL_Float_Mul_(MX_FLOAT A, MX_FLOAT B)      { return A * B; }
MX_FLOAT FC_CAL_Float_Div_(MX_FLOAT A, MX_FLOAT B)      { return (B != 0.0f) ? A / B : 0.0f; }
MX_FLOAT FC_CAL_Float_Abs_(MX_FLOAT A)                  { return fabsf(A); }
MX_FLOAT FC_CAL_Float_Sqrt_(MX_FLOAT A)                 { return sqrtf(A); }
MX_FLOAT FC_CAL_Float_Sin_(MX_FLOAT A)                  { return sinf(A); }
MX_FLOAT FC_CAL_Float_Cos_(MX_FLOAT A)                  { return cosf(A); }
MX_FLOAT FC_CAL_Float_Tan_(MX_FLOAT A)                  { return tanf(A); }
MX_FLOAT FC_CAL_Float_Asin_(MX_FLOAT A)                 { return asinf(A); }
MX_FLOAT FC_CAL_Float_Acos_(MX_FLOAT A)                 { return acosf(A); }
MX_FLOAT FC_CAL_Float_Atan_(MX_FLOAT A)                 { return atanf(A); }
MX_FLOAT FC_CAL_Float_Atan2_(MX_FLOAT Y, MX_FLOAT X)   { return atan2f(Y, X); }
MX_FLOAT FC_CAL_Float_Log_(MX_FLOAT A)                  { return logf(A); }
MX_FLOAT FC_CAL_Float_Log10_(MX_FLOAT A)                { return log10f(A); }
MX_FLOAT FC_CAL_Float_Exp_(MX_FLOAT A)                  { return expf(A); }
MX_FLOAT FC_CAL_Float_Pow_(MX_FLOAT A, MX_FLOAT B)      { return powf(A, B); }
MX_FLOAT FC_CAL_Float_Floor_(MX_FLOAT A)                { return floorf(A); }
MX_FLOAT FC_CAL_Float_Ceil_(MX_FLOAT A)                 { return ceilf(A); }
MX_SINT32 FC_CAL_Float_ToInt_(MX_FLOAT A)               { return (MX_SINT32)A; }
MX_FLOAT FC_CAL_Float_FromInt_(MX_SINT32 A)             { return (MX_FLOAT)A; }
MX_UINT8 FC_CAL_Float_Greater_(MX_FLOAT A, MX_FLOAT B)  { return (A > B) ? 1U : 0U; }
MX_UINT8 FC_CAL_Float_Less_(MX_FLOAT A, MX_FLOAT B)     { return (A < B) ? 1U : 0U; }
MX_UINT8 FC_CAL_Float_Equal_(MX_FLOAT A, MX_FLOAT B)    { return (A == B) ? 1U : 0U; }
