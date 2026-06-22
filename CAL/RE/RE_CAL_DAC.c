// CRC: 0000000000000000000000000000000000000000000000000000000000000000
// REVISION: 1.0
// GUID: F2A3B4C5-D6E7-8901-5678-012345678901
// DATE: 22\06\2026
// DIR: CAL\RE\RE_CAL_DAC.c
/* Flowcode CAL DAC - Renesas RA4M1 DAC12 (12-bit, 2-channel: DA0, DA1) */

#include "ra4m1.h"

#define MX_DAC_CHANNEL_X  CAL_APPEND(MX_DAC_CHANNEL_, MX_DAC_NUM)

CALFUNCTION(void, FC_CAL_DAC_Enable_, (void))
{
    RA_PRCR_UNLOCK(PRCR_PRC1);
    R_MSTP_MSTPCRB &= ~MSTP_DAC0;
    RA_PRCR_LOCK();
    /* Configure pin as analog: P014 (DA0) or P015 (DA1) */
    RA_PFS_UNLOCK();
    if (MX_DAC_CHANNEL_X == 0)
        R_PFS(0, 14) = PFS_ASEL;
    else
        R_PFS(0, 15) = PFS_ASEL;
    RA_PFS_LOCK();
    /* Enable the channel */
    R_DAC0->DACR |= (unsigned char)(1U << MX_DAC_CHANNEL_X);
}

CALFUNCTION(void, FC_CAL_DAC_Disable_, (void))
{
    R_DAC0->DACR &= (unsigned char)(~(1U << MX_DAC_CHANNEL_X));
}

CALFUNCTION(void, FC_CAL_DAC_SetOutput_, (MX_UINT16 Value))
{
    if (MX_DAC_CHANNEL_X == 0)
        R_DAC0->DADR0 = (unsigned short)(Value & 0x0FFFU);
    else
        R_DAC0->DADR1 = (unsigned short)(Value & 0x0FFFU);
}
