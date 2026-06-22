// CRC: 0000000000000000000000000000000000000000000000000000000000000000
// REVISION: 1.0
// GUID: C5D6E7F8-A9B0-1234-8901-345678901234
// DATE: 22\06\2026
// DIR: CAL\RE\RE_CAL_I2S.c
/* Flowcode CAL I2S - Renesas RA (stub - I2S/SSI not on all RA4M1 variants) */

CALFUNCTION(void, FC_CAL_I2S_Init_, (MX_UINT32 SampleRate, MX_UINT8 BitsPerSample))
{
    (void)SampleRate; (void)BitsPerSample;
}

CALFUNCTION(void, FC_CAL_I2S_Uninit_, (void))
{
}

CALFUNCTION(void, FC_CAL_I2S_Write_, (MX_UINT32 Left, MX_UINT32 Right))
{
    (void)Left; (void)Right;
}

CALFUNCTION(void, FC_CAL_I2S_Read_, (MX_UINT32* Left, MX_UINT32* Right))
{
    if (Left)  *Left  = 0U;
    if (Right) *Right = 0U;
}
