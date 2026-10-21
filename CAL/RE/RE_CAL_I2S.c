
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
