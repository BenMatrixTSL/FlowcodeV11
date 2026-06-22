// CRC: 0000000000000000000000000000000000000000000000000000000000000000
// REVISION: 1.0
// GUID: A7B8C9D0-E1F2-3456-0123-567890123456
// DATE: 22\06\2026
// DIR: CAL\RE\RE_CAL_I2C.c
/*
 * Flowcode CAL I2C - Renesas RA4M1 IIC Master
 *
 * Uses RA4M1 IIC0 or IIC1 peripheral in master mode (polling).
 *
 * FCD defines:
 *   MX_I2C_CHANNEL_x  - IIC unit: 0=IIC0, 1=IIC1
 *   MX_I2C_BAUD_x     - Bus clock: 100000 or 400000
 *   MX_I2C_SDA_PORT_x / MX_I2C_SDA_PIN_x / MX_I2C_SDA_AF_x
 *   MX_I2C_SCL_PORT_x / MX_I2C_SCL_PIN_x / MX_I2C_SCL_AF_x
 *
 * Timing: ICBRH/ICBRL set for approx 100kHz or 400kHz at 48MHz PCLK.
 * 100kHz: ICBRH=0x1F, ICBRL=0x1F  (each ~50% duty)
 * 400kHz: ICBRH=0x07, ICBRL=0x09
 */

#include "ra4m1.h"

#define MX_I2C_CHANNEL_X   CAL_APPEND(MX_I2C_CHANNEL_, MX_I2C_NUM)
#define MX_I2C_BAUD_X      CAL_APPEND(MX_I2C_BAUD_, MX_I2C_NUM)
#define MX_I2C_SDA_PIN_X   CAL_APPEND(MX_I2C_SDA_PIN_, MX_I2C_NUM)
#define MX_I2C_SDA_PORT_X  CAL_APPEND(MX_I2C_SDA_PORT_, MX_I2C_NUM)
#define MX_I2C_SDA_AF_X    CAL_APPEND(MX_I2C_SDA_AF_, MX_I2C_NUM)
#define MX_I2C_SCL_PIN_X   CAL_APPEND(MX_I2C_SCL_PIN_, MX_I2C_NUM)
#define MX_I2C_SCL_PORT_X  CAL_APPEND(MX_I2C_SCL_PORT_, MX_I2C_NUM)
#define MX_I2C_SCL_AF_X    CAL_APPEND(MX_I2C_SCL_AF_, MX_I2C_NUM)

/* Timeout counter for bus-stuck detection */
#define RA_I2C_TIMEOUT  50000U

static RA_IIC_Type* ra_i2c_get(void)
{
    return R_IIC(MX_I2C_CHANNEL_X);
}

static void ra_i2c_wait_tend(RA_IIC_Type *iic, unsigned int timeout)
{
    volatile unsigned int t = timeout;
    while (!(iic->ICSR2 & IIC_ICSR2_TEND) && t--)
        ;
}

static void ra_i2c_wait_rdrf(RA_IIC_Type *iic, unsigned int timeout)
{
    volatile unsigned int t = timeout;
    while (!(iic->ICSR2 & IIC_ICSR2_RDRF) && t--)
        ;
}

CALFUNCTION(void, FC_CAL_I2C_Master_Init_, (void))
{
    RA_IIC_Type *iic = ra_i2c_get();

    /* Enable IIC clock */
    RA_PRCR_UNLOCK(PRCR_PRC1);
    if (MX_I2C_CHANNEL_X == 0)
        R_MSTP_MSTPCRB &= ~MSTP_IIC0;
    else
        R_MSTP_MSTPCRB &= ~MSTP_IIC1;
    RA_PRCR_LOCK();

    /* Reset IIC */
    iic->ICCR1 = IIC_ICCR1_IICRST;
    iic->ICCR1 = IIC_ICCR1_IICRST | IIC_ICCR1_ICE;

    /* Configure pins - open-drain, peripheral mode */
    RA_PFS_UNLOCK();
    R_PFS(MX_I2C_SDA_PORT_X, MX_I2C_SDA_PIN_X) =
        PFS_PMR | PFS_NCODR | PFS_PCR | PFS_PSEL(MX_I2C_SDA_AF_X);
    R_PFS(MX_I2C_SCL_PORT_X, MX_I2C_SCL_PIN_X) =
        PFS_PMR | PFS_NCODR | PFS_PCR | PFS_PSEL(MX_I2C_SCL_AF_X);
    RA_PFS_LOCK();

    /* Set clock divider: ICMR1 CKS bits for /1 PCLK */
    iic->ICMR1 = 0x08U;  /* CKS=000 (PCLK/1), MTWP=0 */

    /* Set bit rate for 100kHz or 400kHz */
    if (MX_I2C_BAUD_X <= 100000UL) {
        iic->ICBRH = 0x1FU;
        iic->ICBRL = 0x1FU;
    } else {
        iic->ICBRH = 0x07U;
        iic->ICBRL = 0x09U;
    }

    iic->ICFER = 0x77U;  /* Enable NACK, timeout, etc. */
    iic->ICSER = 0x00U;  /* No slave addresses */
    iic->ICIER = 0x00U;  /* Polled mode - no interrupts */

    /* Release reset, enable */
    iic->ICCR1 = IIC_ICCR1_ICE;
}

CALFUNCTION(void, FC_CAL_I2C_Master_Uninit_, (void))
{
    ra_i2c_get()->ICCR1 = 0x00U;
}

CALFUNCTION(void, FC_CAL_I2C_Master_Start_, (void))
{
    RA_IIC_Type *iic = ra_i2c_get();
    volatile unsigned int t = RA_I2C_TIMEOUT;
    /* Wait until bus is free */
    while ((iic->ICCR2 & IIC_ICCR2_BBSY) && t--)
        ;
    iic->ICCR2 = IIC_ICCR2_ST | IIC_ICCR2_MST | IIC_ICCR2_TRS;
    t = RA_I2C_TIMEOUT;
    while (!(iic->ICSR2 & IIC_ICSR2_START) && t--)
        ;
    iic->ICSR2 &= ~IIC_ICSR2_START;
}

CALFUNCTION(void, FC_CAL_I2C_Master_Restart_, (void))
{
    RA_IIC_Type *iic = ra_i2c_get();
    iic->ICCR2 = IIC_ICCR2_RS | IIC_ICCR2_MST | IIC_ICCR2_TRS;
    volatile unsigned int t = RA_I2C_TIMEOUT;
    while (!(iic->ICSR2 & IIC_ICSR2_START) && t--)
        ;
    iic->ICSR2 &= ~IIC_ICSR2_START;
}

CALFUNCTION(void, FC_CAL_I2C_Master_Stop_, (void))
{
    RA_IIC_Type *iic = ra_i2c_get();
    iic->ICSR2 &= ~IIC_ICSR2_STOP;
    iic->ICCR2 = IIC_ICCR2_SP | IIC_ICCR2_MST;
    volatile unsigned int t = RA_I2C_TIMEOUT;
    while (!(iic->ICSR2 & IIC_ICSR2_STOP) && t--)
        ;
    iic->ICSR2 &= ~IIC_ICSR2_STOP;
}

CALFUNCTION(MX_UINT8, FC_CAL_I2C_Master_TxByte_, (MX_UINT8 Data))
{
    RA_IIC_Type *iic = ra_i2c_get();
    iic->ICDRT = Data;
    ra_i2c_wait_tend(iic, RA_I2C_TIMEOUT);
    iic->ICSR2 &= ~IIC_ICSR2_TEND;
    return (iic->ICSR2 & IIC_ICSR2_NACKF) ? 0U : 1U;
}

CALFUNCTION(MX_UINT8, FC_CAL_I2C_Master_RxByte_, (MX_UINT8 Last))
{
    RA_IIC_Type *iic = ra_i2c_get();
    /* Switch to receive mode */
    iic->ICCR2 = IIC_ICCR2_MST;
    if (Last)
        iic->ICMR3 = 0x40U;  /* ACKWP=1, ACKBT=1 (send NACK after this byte) */
    else
        iic->ICMR3 = 0x00U;
    ra_i2c_wait_rdrf(iic, RA_I2C_TIMEOUT);
    unsigned char d = iic->ICDRR;
    iic->ICSR2 &= ~IIC_ICSR2_RDRF;
    return d;
}

/* Transaction API */
CALFUNCTION(MX_UINT8, FC_CAL_I2C_Transaction_Init_, (MX_UINT8 SlaveAddr))
{
    FC_CAL_I2C_Master_Start_CAL_APPEND(, MX_I2C_NUM)();
    return FC_CAL_I2C_Master_TxByte_CAL_APPEND(, MX_I2C_NUM)((SlaveAddr << 1) | 0U);
}

CALFUNCTION(MX_UINT16, FC_CAL_I2C_Transaction_Write_, (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length))
{
    MX_UINT16 i;
    for (i = 0; i < Length && i < Size; i++)
        FC_CAL_I2C_Master_TxByte_CAL_APPEND(, MX_I2C_NUM)(Buffer[i]);
    return i;
}

CALFUNCTION(MX_UINT16, FC_CAL_I2C_Transaction_Read_, (MX_UINT8* Buffer, MX_UINT16 Size, MX_UINT16 Length))
{
    MX_UINT16 i;
    for (i = 0; i < Length && i < Size; i++)
        Buffer[i] = FC_CAL_I2C_Master_RxByte_CAL_APPEND(, MX_I2C_NUM)((i == (Length - 1U)) ? 1U : 0U);
    return i;
}

CALFUNCTION(void, FC_CAL_I2C_Transaction_Uninit_, (void))
{
    FC_CAL_I2C_Master_Stop_CAL_APPEND(, MX_I2C_NUM)();
}
