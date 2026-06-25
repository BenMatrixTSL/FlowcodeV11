// CRC: 3DA5483D3EF86CFE38B5E3C960DE4A45489DE1A0BAC3D68E62E767887ED5205C9A66A2BA1661F17A474E873DCF461361A54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E1514BAD95F7666935A4D631DAE5C3FB48641EC2749E4223B6310D1DE95E7F0DD496B712970E57346C867A34DEA342BCCEFD1ECE95D3C2615E5371EDAA0A5C4B522E79C3C7DB3307558DF4A08A0156CE12C14399EAC8B11DF22549D34A0D5AD11F3A19143A5DD76245555C186FF22A403EAE9430B8846A222321EF3C8BA6D793B2D3FD0D9AB4C2F44A0
// REVISION: 1.0
// GUID: D6E7F8A9-B0C1-2345-9012-456789012345
// DATE: 25\06\2026
// DIR: CAL\RE\RE_CAL_RTC.c
/*
 * Flowcode CAL RTC - Renesas RA4M1
 * The RA4M1 has an RTC peripheral at 0x40083000.
 * This is a minimal polling implementation.
 */

#include "ra4m1.h"

/* RA4M1 RTC registers */
#define R_RTC_BASE  0x40083000UL
#define R_RTC_RCR2  (*(volatile unsigned char *)(R_RTC_BASE + 0x0CU))
#define R_RTC_RSECCNT (*(volatile unsigned char *)(R_RTC_BASE + 0x10U))
#define R_RTC_RMINCNT (*(volatile unsigned char *)(R_RTC_BASE + 0x12U))
#define R_RTC_RHRCNT  (*(volatile unsigned char *)(R_RTC_BASE + 0x14U))
#define R_RTC_RDAYCNT (*(volatile unsigned char *)(R_RTC_BASE + 0x1AU))
#define R_RTC_RMONCNT (*(volatile unsigned char *)(R_RTC_BASE + 0x1CU))
#define R_RTC_RYRCNT  (*(volatile unsigned short*)(R_RTC_BASE + 0x1EU))

static unsigned char bcd2bin(unsigned char bcd) { return (bcd >> 4) * 10 + (bcd & 0x0F); }
static unsigned char bin2bcd(unsigned char bin) { return ((bin / 10) << 4) | (bin % 10); }

CALFUNCTION(void, FC_CAL_RTC_Init_, (void))
{
    RA_PRCR_UNLOCK(PRCR_PRC1);
    /* RTC clock enable - uses SOSC or LOCO */
    R_RTC_RCR2 = 0x00U;  /* Stop */
    RA_PRCR_LOCK();
}

CALFUNCTION(void, FC_CAL_RTC_SetTime_, (MX_UINT8 Hours, MX_UINT8 Minutes, MX_UINT8 Seconds))
{
    R_RTC_RCR2 &= ~0x01U;
    R_RTC_RSECCNT = bin2bcd(Seconds);
    R_RTC_RMINCNT = bin2bcd(Minutes);
    R_RTC_RHRCNT  = bin2bcd(Hours);
    R_RTC_RCR2 |= 0x01U;
}

CALFUNCTION(void, FC_CAL_RTC_GetTime_, (MX_UINT8* Hours, MX_UINT8* Minutes, MX_UINT8* Seconds))
{
    if (Seconds) *Seconds = bcd2bin(R_RTC_RSECCNT & 0x7FU);
    if (Minutes) *Minutes = bcd2bin(R_RTC_RMINCNT & 0x7FU);
    if (Hours)   *Hours   = bcd2bin(R_RTC_RHRCNT  & 0x3FU);
}

CALFUNCTION(void, FC_CAL_RTC_SetDate_, (MX_UINT16 Year, MX_UINT8 Month, MX_UINT8 Day))
{
    R_RTC_RCR2 &= ~0x01U;
    R_RTC_RDAYCNT = bin2bcd(Day);
    R_RTC_RMONCNT = bin2bcd(Month);
    R_RTC_RYRCNT  = (unsigned short)((bin2bcd((unsigned char)(Year / 100)) << 8) | bin2bcd((unsigned char)(Year % 100)));
    R_RTC_RCR2 |= 0x01U;
}

CALFUNCTION(void, FC_CAL_RTC_GetDate_, (MX_UINT16* Year, MX_UINT8* Month, MX_UINT8* Day))
{
    if (Day)   *Day   = bcd2bin(R_RTC_RDAYCNT & 0x3FU);
    if (Month) *Month = bcd2bin(R_RTC_RMONCNT & 0x1FU);
    if (Year) {
        unsigned short y = R_RTC_RYRCNT;
        *Year = (MX_UINT16)(bcd2bin((unsigned char)(y >> 8)) * 100 + bcd2bin((unsigned char)(y & 0xFF)));
    }
}
