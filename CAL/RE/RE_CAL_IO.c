// CRC: 3DA5483D3EF86CFE38B5E3C960DE4A459744F5942CE158A6A1265CF6DA70E274DD04A5F8AD9BEEB1823278EF8F2BA19CA54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E150F4F08027475FB3701E00376D48AF474DB770801D1A4CC1D8365D20EA51C21176B407F126515BC1C641E224811CC6C1BA6599178E3F37E03753BD7527F51BE9289C3EA3649420342FA7545FFF73C0DCBAA1D7F7DCF288256549D34A0D5AD11F3702695953D4669831A25336F6D7765EA1AEC7555F254FF8BA3E761B0B04467EFC0CE2C344F21BA45
// REVISION: 1.0
// GUID: C3D4E5F6-A7B8-9012-CDEF-123456789012
// DATE: 25\06\2026
// DIR: CAL\RE\RE_CAL_IO.c
/*
 * Flowcode CAL IO - Renesas RA4M1
 *
 * Uses RA4M1 IOPORT PCNTRx registers for port-level operations:
 *   PCNTR1: PDR (direction, upper 16) | PODR (output, lower 16)
 *   PCNTR2: EIDR (event, upper 16) | PIDR (input, lower 16)
 *   PCNTR3: POSR (set, upper 16) | PORR (reset, lower 16)
 *
 * Pin direction must be configured by user code or the fcdx <inline> init.
 * Flowcode components that need DDR control call FC_CAL_Port_SetDir__x().
 */

#include "ra4m1.h"

/* -------------------------------------------------------------------------
   Generic port read/write helpers - all ports share the same register layout
   ------------------------------------------------------------------------- */

static inline unsigned short ra_port_read(unsigned int port_num)
{
    return (unsigned short)(R_PORT(port_num)->PIDR);
}

static inline void ra_port_write(unsigned int port_num, unsigned short mask, unsigned short value)
{
    /* Use POSR (set) and PORR (reset) for atomic bit manipulation */
    R_PORT(port_num)->POSR = (unsigned short)(mask & value);
    R_PORT(port_num)->PORR = (unsigned short)(mask & ~value);
}

static inline void ra_port_setdir(unsigned int port_num, unsigned short mask, unsigned char is_output)
{
    unsigned short pdr = R_PORT(port_num)->PDR;
    if (is_output)
        R_PORT(port_num)->PDR = (unsigned short)(pdr | mask);
    else
        R_PORT(port_num)->PDR = (unsigned short)(pdr & ~mask);
}

/* -------------------------------------------------------------------------
   Port 0
   ------------------------------------------------------------------------- */
void FC_CAL_Port_Out__0(unsigned short Mask, unsigned char Shift, unsigned short Value)
{
    ra_port_write(0, Mask, (unsigned short)(Value << Shift));
}

unsigned short FC_CAL_Port_In__0(unsigned short Mask, unsigned char Shift)
{
    return (unsigned short)((ra_port_read(0) & Mask) >> Shift);
}

void FC_CAL_Port_SetDir__0(unsigned short Mask, unsigned char IsOutput)
{
    ra_port_setdir(0, Mask, IsOutput);
}

/* -------------------------------------------------------------------------
   Port 1
   ------------------------------------------------------------------------- */
void FC_CAL_Port_Out__1(unsigned short Mask, unsigned char Shift, unsigned short Value)
{
    ra_port_write(1, Mask, (unsigned short)(Value << Shift));
}

unsigned short FC_CAL_Port_In__1(unsigned short Mask, unsigned char Shift)
{
    return (unsigned short)((ra_port_read(1) & Mask) >> Shift);
}

void FC_CAL_Port_SetDir__1(unsigned short Mask, unsigned char IsOutput)
{
    ra_port_setdir(1, Mask, IsOutput);
}

/* -------------------------------------------------------------------------
   Port 2
   ------------------------------------------------------------------------- */
void FC_CAL_Port_Out__2(unsigned short Mask, unsigned char Shift, unsigned short Value)
{
    ra_port_write(2, Mask, (unsigned short)(Value << Shift));
}

unsigned short FC_CAL_Port_In__2(unsigned short Mask, unsigned char Shift)
{
    return (unsigned short)((ra_port_read(2) & Mask) >> Shift);
}

void FC_CAL_Port_SetDir__2(unsigned short Mask, unsigned char IsOutput)
{
    ra_port_setdir(2, Mask, IsOutput);
}

/* -------------------------------------------------------------------------
   Port 3
   ------------------------------------------------------------------------- */
void FC_CAL_Port_Out__3(unsigned short Mask, unsigned char Shift, unsigned short Value)
{
    ra_port_write(3, Mask, (unsigned short)(Value << Shift));
}

unsigned short FC_CAL_Port_In__3(unsigned short Mask, unsigned char Shift)
{
    return (unsigned short)((ra_port_read(3) & Mask) >> Shift);
}

void FC_CAL_Port_SetDir__3(unsigned short Mask, unsigned char IsOutput)
{
    ra_port_setdir(3, Mask, IsOutput);
}

/* -------------------------------------------------------------------------
   Port 4
   ------------------------------------------------------------------------- */
void FC_CAL_Port_Out__4(unsigned short Mask, unsigned char Shift, unsigned short Value)
{
    ra_port_write(4, Mask, (unsigned short)(Value << Shift));
}

unsigned short FC_CAL_Port_In__4(unsigned short Mask, unsigned char Shift)
{
    return (unsigned short)((ra_port_read(4) & Mask) >> Shift);
}

void FC_CAL_Port_SetDir__4(unsigned short Mask, unsigned char IsOutput)
{
    ra_port_setdir(4, Mask, IsOutput);
}

/* -------------------------------------------------------------------------
   EXTI / external interrupt pin init (stub - expanded per chip FCD)
   ------------------------------------------------------------------------- */
void MX_EXTI_PinInit(void)
{
    /* Configured per pin in the FCDX <inline> init section */
}
