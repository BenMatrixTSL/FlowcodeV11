// CRC: 0000000000000000000000000000000000000000000000000000000000000000
// REVISION: 1.0
// GUID: B2C3D4E5-F6A7-8901-BCDE-F12345678901
// DATE: 22\06\2026
// DIR: CAL\RE\RE_CAL_IO.h
/*
 * Flowcode CAL IO Header - Renesas RA family
 * Maps Flowcode port abstractions to RA4M1 IOPORT registers.
 *
 * Flowcode ports 0-4 map directly to RA4M1 ports 0-4.
 * Bit operations use PCNTR3 (POSR/PORR) for atomic set/clear.
 */

/* FC8 Port/Pin macros - used by Flowcode-generated code */

#define GET_PORT(p)                 FCP_GET(F, p, 0xFFFF, 0)
#define GET_PORT_PIN(p, b)          FCP_GET(B, p, (1U << (b)), (b))
#define GET_PORT_SHIFT(p, s)        FCP_GET(M, p, 0xFFFF, (s))
#define GET_PORT_MASK_SHIFT(p, m, s) FCP_GET(M, p, (m), (s))
#define GET_PORT_MASK(p, m)         FCP_GET(M, p, (m), 0)

#define SET_PORT(p, v)              FCP_SET(F, p, 0xFFFF, 0, (v))
#define SET_PORT_PIN(p, b, v)       FCP_SET(B, p, (1U << (b)), (b), ((v) ? 0xFFFFU : 0U))
#define SET_PORT_SHIFT(p, s, v)     FCP_SET(M, p, 0xFFFF, (s), (v))
#define SET_PORT_MASK_SHIFT(p, m, s, v) FCP_SET(M, p, (m), (s), (v))
#define SET_PORT_MASK(p, m, v)      FCP_SET(M, p, (m), 0, (v))

/* DDR (direction) macro overrides - RA uses PDR field in PCNTR1 upper word */
#define FCP_USE_TRIS

/* FCP macros for RA4M1 - use R_PORT(n)->PIDR for read, PODR for write,
 * PDR for direction, POSR/PORR for atomic bit set/clear.
 *
 * These macros are expanded by the STARM-style IO functions.
 */
#define FCP_GET(type, port, mask, shift) FC_CAL_Port_In__##port(mask, shift)
#define FCP_SET(type, port, mask, shift, val) FC_CAL_Port_Out__##port(mask, shift, val)

/* Port pointer aliases - RA4M1 ports addressed by R_PORT(n) */
#define porta   0
#define portb   1
#define portc   2
#define portd   3
#define porte   4

/* These aliases follow the FCD pin-definition convention where
 * port='0' means port index 0, etc. */
#define port0   0
#define port1   1
#define port2   2
#define port3   3
#define port4   4
#define port5   5

/* Declare IO functions used by the CAL */
void FC_CAL_Port_Out__0(unsigned short Mask, unsigned char Shift, unsigned short Value);
void FC_CAL_Port_Out__1(unsigned short Mask, unsigned char Shift, unsigned short Value);
void FC_CAL_Port_Out__2(unsigned short Mask, unsigned char Shift, unsigned short Value);
void FC_CAL_Port_Out__3(unsigned short Mask, unsigned char Shift, unsigned short Value);
void FC_CAL_Port_Out__4(unsigned short Mask, unsigned char Shift, unsigned short Value);

unsigned short FC_CAL_Port_In__0(unsigned short Mask, unsigned char Shift);
unsigned short FC_CAL_Port_In__1(unsigned short Mask, unsigned char Shift);
unsigned short FC_CAL_Port_In__2(unsigned short Mask, unsigned char Shift);
unsigned short FC_CAL_Port_In__3(unsigned short Mask, unsigned char Shift);
unsigned short FC_CAL_Port_In__4(unsigned short Mask, unsigned char Shift);

void FC_CAL_Port_SetDir__0(unsigned short Mask, unsigned char IsOutput);
void FC_CAL_Port_SetDir__1(unsigned short Mask, unsigned char IsOutput);
void FC_CAL_Port_SetDir__2(unsigned short Mask, unsigned char IsOutput);
void FC_CAL_Port_SetDir__3(unsigned short Mask, unsigned char IsOutput);
void FC_CAL_Port_SetDir__4(unsigned short Mask, unsigned char IsOutput);

void MX_EXTI_PinInit(void);
