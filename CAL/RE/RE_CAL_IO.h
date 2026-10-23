// CRC: 3DA5483D3EF86CFE38B5E3C960DE4A459744F5942CE158A6A1265CF6DA70E274011496AE222D8A5BBDA9DACA3792E771B82E41E3F05B9517B47821D22B91C490D5EC1178E7B1FA23A9B11F738DF98E15F9A33461109E367F6C3F7A850ED419A6B813734BB24E9E663C717360A5768576C687AAC25F654685A70AF63161E48A464D72A953811A39D4C32A2705118434EEEB164BABFB0CB80BD65F33C05950CCD69368807D9AC6CCC2549D34A0D5AD11F3E895EEF84CAC65D7D19281C76683E32B07A1C4EBA06615C907369D99911C23D5D43797C197BFDEC5
// REVISION: 1.0
// GUID: 210D4A9A-80B3-47AD-A7D0-E0D63CE69C55
// DATE: 23\10\2026
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
