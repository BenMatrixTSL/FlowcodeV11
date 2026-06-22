// CRC: 0000000000000000000000000000000000000000000000000000000000000000
// REVISION: 1.0
// GUID: A3B4C5D6-E7F8-9012-6789-123456789012
// DATE: 22\06\2026
// DIR: CAL\RE\RE_CAL_CAN.c
/* Flowcode CAL CAN - Renesas RA (stub - CAN not present on RA4M1 base device) */

/* The RA4M1 does not include a CAN peripheral. This stub satisfies the
 * includes.c include chain. RA6M devices with CAN would implement this fully. */

CALFUNCTION(void, FC_CAL_CAN_Init_, (MX_UINT32 Baud))
{
    (void)Baud;
}

CALFUNCTION(void, FC_CAL_CAN_Uninit_, (void))
{
}

CALFUNCTION(MX_UINT8, FC_CAL_CAN_Tx_, (MX_UINT32 ID, MX_UINT8* Data, MX_UINT8 Len))
{
    (void)ID; (void)Data; (void)Len;
    return 0U;
}

CALFUNCTION(MX_UINT8, FC_CAL_CAN_Rx_, (MX_UINT32* ID, MX_UINT8* Data, MX_UINT8* Len))
{
    (void)ID; (void)Data; (void)Len;
    return 0U;
}
