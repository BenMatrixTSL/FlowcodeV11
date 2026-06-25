// CRC: 3DA5483D3EF86CFE38B5E3C960DE4A452004EF23FE9DC811ABA8E416761E214DB51C67980A393B2E40EBDE7FEADD76C0A54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E15CD214BADEA29F97282C0B1996FBC923E52129D351159A3B32BC7495DE08EE81A446D6E75C6CFF6D21E350E509ECDDF7782DB1842AE7C989B1ABE46781790D351856C138D3A9BB2DD5CBBA75653F7708AAA1D7F7DCF288256549D34A0D5AD11F3EE54055D5663F49CD4AA3E3F18A533831AD84B95974007B4FFCF1C90B393605E9F32B96E9FC2F3A9
// REVISION: 1.0
// GUID: E1F2A3B4-C5D6-7890-4567-901234567890
// DATE: 25\06\2026
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
