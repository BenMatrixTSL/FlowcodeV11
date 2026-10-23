// CRC: 3DA5483D3EF86CFE38B5E3C960DE4A45489DE1A0BAC3D68E62E767887ED5205C9A66A2BA1661F17A474E873DCF461361B82E41E3F05B9517B47821D22B91C490D5EC1178E7B1FA23A9B11F738DF98E156D67A700B2FBD4EAE4FEE5049A7B614497DB209196D308FC167F9D1B097694B55A57DC8074FB78A1468DEDFB082AF41B40B8088025D92A09DE3856D84EE4A2068D9C371D54DD921D3A1A03BE0183048E3C5777F71A2C6A5A549D34A0D5AD11F36F1F562C3016976D08968A652CDC3751A6C0476009A55C4E76AD1A7DB9B9D5F43F565616D7803A54
// REVISION: 1.0
// GUID: FB2B7E91-F2EC-45F4-9210-CFD56605638D
// DATE: 23\10\2026
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
