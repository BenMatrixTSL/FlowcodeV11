// CRC: 3DA5483D3EF86CFE38B5E3C960DE4A451F636C310EB697443F03ED852C0FD0759A66A2BA1661F17A474E873DCF461361A54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E15AB220BC2E2C88BEAC338EE5146D922D4F87648257D33606CBF372E78459AB530D627D04BC5706ABE65F7643ECFA4EA82EABDCA0B92D9B66C8E88DE8813F4F18DACAFAB88B6F1AF5843DF262F1C9598072CC9F797FDFDC3B5549D34A0D5AD11F3093CC25AC686CD8376946C8D053B728440CECFBB9847D46D07369D99911C23D5D43797C197BFDEC5
// REVISION: 1.0
// GUID: B8C9D0E1-F2A3-4567-1234-678901234567
// DATE: 25\06\2026
// DIR: CAL\RE\RE_CAL_ADC.c
/*
 * Flowcode CAL ADC - Renesas RA4M1 ADC140 (14-bit)
 *
 * The RA4M1 has one 14-bit SAR ADC with up to 14 channels (AN000-AN013).
 * This driver runs single-conversion mode with polling.
 *
 * FCD defines:
 *   MX_ADC_CHANNEL_x   - ADC channel number (0-13 for AN000-AN013)
 *   MX_ADC_PORT_x      - GPIO port for analog pin
 *   MX_ADC_PIN_x       - GPIO pin number for analog pin
 *   MX_ADC_SPEED_x     - Conversion speed (affects ADSSTRL register)
 *
 * Channel-to-pin mapping (RA4M1 LQFP-64):
 *   AN000=P000, AN001=P001, AN002=P002, AN003=P003, AN004=P004
 *   AN005=P005, AN006=P006, AN007=P007, AN008=P014, AN009=P015
 *   AN010=P030, AN011=P031, AN012=P032, AN013=P033
 */

#include "ra4m1.h"

#define MX_ADC_CHANNEL_X  CAL_APPEND(MX_ADC_CHANNEL_, MX_ADC_NUM)
#define MX_ADC_PORT_X     CAL_APPEND(MX_ADC_PORT_, MX_ADC_NUM)
#define MX_ADC_PIN_X      CAL_APPEND(MX_ADC_PIN_, MX_ADC_NUM)

CALFUNCTION(void, FC_CAL_ADC_Enable_, (MX_UINT8 Channel, MX_UINT8 Conv_Speed, MX_UINT8 Vref, MX_UINT8 T_Charge))
{
    (void)Vref;
    (void)T_Charge;

    /* Enable ADC clock */
    RA_PRCR_UNLOCK(PRCR_PRC1);
    R_MSTP_MSTPCRD &= ~MSTP_ADC0;
    RA_PRCR_LOCK();

    /* Configure pin as analog input (ASEL=1, PMR=0, PDR=0) */
    RA_PFS_UNLOCK();
    R_PFS(MX_ADC_PORT_X, MX_ADC_PIN_X) = PFS_ASEL;
    RA_PFS_LOCK();

    /* ADC control: single scan mode, 14-bit */
    R_ADC0->ADCSR  = ADC_ADCSR_ADCS(0x00);  /* Single scan */
    R_ADC0->ADCER  = ADC_ADCER_ADPRC(0x00); /* 14-bit */

    /* Select channel in scan group A */
    if (MX_ADC_CHANNEL_X < 16)
        R_ADC0->ADANSA0 = (unsigned short)(1U << MX_ADC_CHANNEL_X);
    else
        R_ADC0->ADANSA1 = (unsigned short)(1U << (MX_ADC_CHANNEL_X - 16U));

    /* Sampling time: approx 1us at 48MHz = 48 cycles */
    /* ADSSTRL register not in struct above - write directly */
    *((volatile unsigned char *)(0x4005C060UL + MX_ADC_CHANNEL_X)) =
        (Conv_Speed > 0U) ? (unsigned char)Conv_Speed : 0x13U;
}

CALFUNCTION(MX_UINT16, FC_CAL_ADC_Sample_, (MX_UINT8 Sample_Mode))
{
    (void)Sample_Mode;

    /* Start conversion */
    R_ADC0->ADCSR |= ADC_ADCSR_ADST;

    /* Wait for conversion complete */
    while (R_ADC0->ADCSR & ADC_ADCSR_ADST)
        ;

    /* Read result (14-bit, left-justified by default → shift to 12-bit for compat) */
    unsigned short raw = R_ADC0->ADDR[MX_ADC_CHANNEL_X];
    return (MX_UINT16)(raw >> 2);  /* Return 12-bit value (0-4095) */
}

CALFUNCTION(void, FC_CAL_ADC_Disable_, (void))
{
    R_ADC0->ADCSR = 0x0000U;
}
