// CRC: 0000000000000000000000000000000000000000000000000000000000000000
// REVISION: 1.0
// GUID: F6A7B8C9-D0E1-2345-F012-456789012345
// DATE: 22\06\2026
// DIR: CAL\RE\RE_CAL_SPI.c
/*
 * Flowcode CAL SPI - Renesas RA4M1
 *
 * Uses RA4M1 SPI0 peripheral (RSPI) in master mode.
 * Alternatively SCI channels can operate in clock-sync (SPI) mode.
 *
 * FCD defines:
 *   MX_SPI_CHANNEL_x   - 0=SPI0, or SCI channel number for SCI-SPI mode
 *   MX_SPI_SCK_PORT_x / MX_SPI_SCK_PIN_x / MX_SPI_SCK_AF_x
 *   MX_SPI_MOSI_PORT_x / MX_SPI_MOSI_PIN_x / MX_SPI_MOSI_AF_x
 *   MX_SPI_MISO_PORT_x / MX_SPI_MISO_PIN_x / MX_SPI_MISO_AF_x
 *   MX_SPI_BMODE_x     - 0=mode0, 1=mode1, 2=mode2, 3=mode3
 *   MX_SPI_PR_SCALE_x  - prescaler (2,4,8,...,256)
 */

#include "ra4m1.h"

#define MX_SPI_CHANNEL_X   CAL_APPEND(MX_SPI_CHANNEL_, MX_SPI_NUM)
#define MX_SPI_SCK_PIN_X   CAL_APPEND(MX_SPI_SCK_PIN_, MX_SPI_NUM)
#define MX_SPI_SCK_PORT_X  CAL_APPEND(MX_SPI_SCK_PORT_, MX_SPI_NUM)
#define MX_SPI_SCK_AF_X    CAL_APPEND(MX_SPI_SCK_AF_, MX_SPI_NUM)
#define MX_SPI_MOSI_PIN_X  CAL_APPEND(MX_SPI_MOSI_PIN_, MX_SPI_NUM)
#define MX_SPI_MOSI_PORT_X CAL_APPEND(MX_SPI_MOSI_PORT_, MX_SPI_NUM)
#define MX_SPI_MOSI_AF_X   CAL_APPEND(MX_SPI_MOSI_AF_, MX_SPI_NUM)
#define MX_SPI_MISO_PIN_X  CAL_APPEND(MX_SPI_MISO_PIN_, MX_SPI_NUM)
#define MX_SPI_MISO_PORT_X CAL_APPEND(MX_SPI_MISO_PORT_, MX_SPI_NUM)
#define MX_SPI_MISO_AF_X   CAL_APPEND(MX_SPI_MISO_AF_, MX_SPI_NUM)
#define MX_SPI_BMODE_X     CAL_APPEND(MX_SPI_BMODE_, MX_SPI_NUM)
#define MX_SPI_PR_SCALE_X  CAL_APPEND(MX_SPI_PR_SCALE_, MX_SPI_NUM)
#define MX_SPI_CS_PIN_X    CAL_APPEND(MX_SPI_CS_PIN_, MX_SPI_NUM)
#define MX_SPI_CS_PORT_X   CAL_APPEND(MX_SPI_CS_PORT_, MX_SPI_NUM)

/* SPBR value: PCLK / (2 * (SPBR+1) * 2^n) = baud; for n=0: SPBR = PCLK/(2*baud)-1 */
/* Prescaler values map to SPBR settings for SPCMD BRDV=0:
 * 2->0, 4->1, 8->3, 16->7, 32->15, 64->31, 128->63, 256->127 */
#define RA_SPI_SPBR(prescale) ((unsigned char)((prescale) / 2U - 1U))

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Init_, (void))
{
    RA_SPI_Type *spi = R_SPI(0);  /* RA4M1 has one SPI unit */

    /* Enable SPI0 clock */
    RA_PRCR_UNLOCK(PRCR_PRC1);
    R_MSTP_MSTPCRB &= ~MSTP_SPI0;
    RA_PRCR_LOCK();

    /* Disable SPI before config */
    spi->SPCR = 0x00U;

    /* Configure pins */
    RA_PFS_UNLOCK();
    R_PFS(MX_SPI_SCK_PORT_X,  MX_SPI_SCK_PIN_X)  = PFS_PDR | PFS_PMR | PFS_PSEL(MX_SPI_SCK_AF_X);
    R_PFS(MX_SPI_MOSI_PORT_X, MX_SPI_MOSI_PIN_X) = PFS_PDR | PFS_PMR | PFS_PSEL(MX_SPI_MOSI_AF_X);
    R_PFS(MX_SPI_MISO_PORT_X, MX_SPI_MISO_PIN_X) = PFS_PMR | PFS_PSEL(MX_SPI_MISO_AF_X) | PFS_PCR;
    RA_PFS_LOCK();

    /* Full-duplex, master, SPI mode */
    spi->SPCR  = SPI_SPCR_MSTR;

    /* 8-bit transfer, MSB first */
    spi->SPDCR = 0x20U;   /* SPBYT=1: byte access mode */

    /* Bit rate */
    spi->SPBR = RA_SPI_SPBR(MX_SPI_PR_SCALE_X);

    /* Command register 0: 8-bit, CPOL/CPHA from BMODE */
    {
        unsigned short cmd = 0x0700U;  /* 8-bit frame */
        if (MX_SPI_BMODE_X & 0x01U) cmd |= (1U << 1);  /* CPHA */
        if (MX_SPI_BMODE_X & 0x02U) cmd |= (1U << 2);  /* CPOL */
        spi->SPCMD0 = cmd;
    }

    /* 1 command in sequence */
    spi->SPSCR = 0x00U;

    /* Enable SPI */
    spi->SPCR |= SPI_SPCR_SPE;

    return 1U;
}

CALFUNCTION(void, FC_CAL_SPI_Master_Uninit_, (void))
{
    R_SPI(0)->SPCR = 0x00U;
}

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Master_Byte_, (MX_UINT8 DataOut))
{
    RA_SPI_Type *spi = R_SPI(0);

    /* Wait for TX empty */
    while (!(spi->SPSR & SPI_SPSR_SPTEF))
        ;
    *((volatile unsigned char *)&spi->SPDR) = DataOut;

    /* Wait for RX full */
    while (!(spi->SPSR & SPI_SPSR_SPRF))
        ;
    return (MX_UINT8)(*((volatile const unsigned char *)&spi->SPDR));
}

CALFUNCTION(void, FC_CAL_SPI_SetPrescaler_, (MX_UINT8 Prescaler))
{
    R_SPI(0)->SPCR &= ~SPI_SPCR_SPE;
    R_SPI(0)->SPBR  = (unsigned char)(Prescaler / 2U - 1U);
    R_SPI(0)->SPCR |= SPI_SPCR_SPE;
}

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_Init_, (void))
{
    return FC_CAL_SPI_Master_Init_CAL_APPEND(, MX_SPI_NUM)();
}

CALFUNCTION(MX_UINT8, FC_CAL_SPI_Transaction_, (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length))
{
    MX_UINT16 i;
    for (i = 0; i < Length && i < Size; i++)
        Buffer[i] = FC_CAL_SPI_Master_Byte_CAL_APPEND(, MX_SPI_NUM)(Buffer[i]);
    return 1U;
}

CALFUNCTION(void, FC_CAL_SPI_Transaction_Uninit_, (void))
{
    /* Keep SPI enabled */
}
