// CRC: 3DA5483D3EF86CFE38B5E3C960DE4A45B7FD41E515EDCEC6890426BB6770E40B245638F146D24C057FFB0C7C1A93D1CEA54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E151A523EE96F499AB889DBB31317C6251E34A9F59E735F3AC6B682D83AAB1A0841D5FE60968D241FB3677FA6427E5A4DF7E7635E970C637D2AB2724DC9BB937394CB728E224ED01CAC3F6621F1E72156335884D874256A074E549D34A0D5AD11F3E552C0507A6711434DE4C4B23A56B527DCB6F320AE43967B76AD1A7DB9B9D5F43F565616D7803A54
// REVISION: 1.0
// GUID: C9D0E1F2-A3B4-5678-2345-789012345678
// DATE: 25\06\2026
// DIR: CAL\RE\RE_CAL_PWM.c
/*
 * Flowcode CAL PWM - Renesas RA4M1 GPT (General PWM Timer)
 *
 * The RA4M1 has GPT0-GPT9 (10 timers), each with two output channels (A/B).
 * This driver configures a GPT in saw-wave mode for standard PWM output.
 *
 * FCD defines:
 *   MX_PWM_CHANNEL_x   - GPT unit (0-9)
 *   MX_PWM_PIN_x       - GPIO pin number
 *   MX_PWM_PORT_x      - GPIO port number
 *   MX_PWM_AF_x        - Alternate function (PSEL value for GTIOCA/GTIOCB)
 *   MX_PWM_TYPE_x      - 0=GTIOCA output, 1=GTIOCB output
 *   MX_PWM_CLOCK_x     - Timer clock prescaler (1,4,16,64,256,1024)
 *
 * Default: 1kHz PWM at 48MHz (period = 48000 counts at /1 prescaler)
 */

#include "ra4m1.h"

#define MX_PWM_CHANNEL_X  CAL_APPEND(MX_PWM_CHANNEL_, MX_PWM_NUM)
#define MX_PWM_PIN_X      CAL_APPEND(MX_PWM_PIN_, MX_PWM_NUM)
#define MX_PWM_PORT_X     CAL_APPEND(MX_PWM_PORT_, MX_PWM_NUM)
#define MX_PWM_AF_X       CAL_APPEND(MX_PWM_AF_, MX_PWM_NUM)
#define MX_PWM_TYPE_X     CAL_APPEND(MX_PWM_TYPE_, MX_PWM_NUM)
#define MX_PWM_CLOCK_X    CAL_APPEND(MX_PWM_CLOCK_, MX_PWM_NUM)
#define MX_PWM_NUMBER_X   CAL_APPEND(MX_PWM_NUMBER_, MX_PWM_NUM)

/* GPT prescaler encoding: 0=/1, 1=/4, 2=/16, 3=/64, 4=/256, 5=/1024 */
static unsigned char ra_gpt_prescaler_encode(unsigned int clkdiv)
{
    if      (clkdiv <= 1U)    return 0U;
    else if (clkdiv <= 4U)    return 1U;
    else if (clkdiv <= 16U)   return 2U;
    else if (clkdiv <= 64U)   return 3U;
    else if (clkdiv <= 256U)  return 4U;
    else                       return 5U;
}

/* GTIOC output setting: initial-low, toggle on GTCCR compare match */
#define GPT_OUTPUT_ACTIVE   0x19U  /* Initial=Low, toggle-on-A-compare, toggle-on-B-compare */

CALFUNCTION(void, FC_CAL_PWM_Enable_, (MX_UINT32 Frequency, MX_UINT8 Resolution))
{
    RA_GPT_Type *gpt = R_GPT(MX_PWM_CHANNEL_X);
    unsigned char psc = ra_gpt_prescaler_encode(MX_PWM_CLOCK_X);
    unsigned long clk = RA4M1_SYSCLK;
    unsigned long dividers[] = {1UL, 4UL, 16UL, 64UL, 256UL, 1024UL};
    unsigned long period_counts = (clk / dividers[psc]) / Frequency;

    /* Enable GPT clock */
    RA_PRCR_UNLOCK(PRCR_PRC1);
    if (MX_PWM_CHANNEL_X < 4)
        R_MSTP_MSTPCRD &= ~MSTP_GPT0;
    else
        R_MSTP_MSTPCRD &= ~MSTP_GPT4;
    RA_PRCR_LOCK();

    /* Stop and clear timer */
    gpt->GTSTP = 1UL;
    gpt->GTCLR = 1UL;

    /* Configure output pin as GTIOCA or GTIOCB */
    RA_PFS_UNLOCK();
    R_PFS(MX_PWM_PORT_X, MX_PWM_PIN_X) = PFS_PDR | PFS_PMR | PFS_PSEL(MX_PWM_AF_X);
    RA_PFS_LOCK();

    /* Set period */
    gpt->GTPR   = period_counts - 1UL;
    gpt->GTPBR  = period_counts - 1UL;

    /* Set initial compare (50% duty) */
    if (MX_PWM_TYPE_X == 0) {
        gpt->GTCCRA = period_counts / 2UL;
        gpt->GTIOR  = GPT_GTIOR_GTIOA(GPT_OUTPUT_ACTIVE);
    } else {
        gpt->GTCCRB = period_counts / 2UL;
        gpt->GTIOR  = GPT_GTIOR_GTIOB(GPT_OUTPUT_ACTIVE);
    }

    /* Saw-wave mode, count-up, configured prescaler */
    gpt->GTCR = GPT_GTCR_MD(0) | GPT_GTCR_TPCS(psc);
    gpt->GTUDDTYC = GPT_GTUDDTYC_UD | GPT_GTUDDTYC_UDF;

    /* Clear counter and start */
    gpt->GTCNT  = 0UL;
    gpt->GTSTR  = 1UL;
}

CALFUNCTION(void, FC_CAL_PWM_Disable_, (void))
{
    RA_GPT_Type *gpt = R_GPT(MX_PWM_CHANNEL_X);
    gpt->GTSTP  = 1UL;
    gpt->GTCNT  = 0UL;
    /* Set output low */
    if (MX_PWM_TYPE_X == 0)
        gpt->GTIOR = 0x00U;
    else
        gpt->GTIOR = 0x00U;
}

CALFUNCTION(void, FC_CAL_PWM_SetDuty_, (MX_UINT8 Duty))
{
    RA_GPT_Type *gpt = R_GPT(MX_PWM_CHANNEL_X);
    unsigned long period = gpt->GTPR + 1UL;
    unsigned long compare = (period * (unsigned long)Duty) / 255UL;
    if (MX_PWM_TYPE_X == 0)
        gpt->GTCCRA = compare;
    else
        gpt->GTCCRB = compare;
}

CALFUNCTION(void, FC_CAL_PWM_SetDutyPercent_, (MX_UINT8 Percent))
{
    RA_GPT_Type *gpt = R_GPT(MX_PWM_CHANNEL_X);
    unsigned long period = gpt->GTPR + 1UL;
    unsigned long compare = (period * (unsigned long)Percent) / 100UL;
    if (MX_PWM_TYPE_X == 0)
        gpt->GTCCRA = compare;
    else
        gpt->GTCCRB = compare;
}
