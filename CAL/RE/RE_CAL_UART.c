// CRC: 0000000000000000000000000000000000000000000000000000000000000000
// REVISION: 1.0
// GUID: E5F6A7B8-C9D0-1234-EF01-345678901234
// DATE: 22\06\2026
// DIR: CAL\RE\RE_CAL_UART.c
/*
 * Flowcode CAL UART - Renesas RA4M1 SCI (Serial Communication Interface)
 *
 * The RA4M1 SCI peripheral supports UART (async), clock-sync, and I2C modes.
 * This driver uses UART (asynchronous) mode with polling (no interrupts).
 *
 * FCD defines injected by Flowcode:
 *   MX_UART_CHANNEL_x  - SCI unit number (0, 1, 2, 9 on RA4M1)
 *   MX_UART_BAUD_x     - Baud rate (e.g. 9600, 115200)
 *   MX_UART_TX_PIN_x   - TX pin number within port
 *   MX_UART_TX_PORT_x  - TX port number
 *   MX_UART_RX_PIN_x   - RX pin number within port
 *   MX_UART_RX_PORT_x  - RX port number
 *   MX_UART_TX_AF_x    - TX alternate function (PSEL value)
 *   MX_UART_RX_AF_x    - RX alternate function (PSEL value)
 */

#include "ra4m1.h"

/* Dynamic function naming (channel number appended) */
#define MX_UART_CHANNEL_X    CAL_APPEND(MX_UART_CHANNEL_, MX_UART_NUM)
#define MX_UART_BAUD_X       CAL_APPEND(MX_UART_BAUD_, MX_UART_NUM)
#define MX_UART_TX_PIN_X     CAL_APPEND(MX_UART_TX_PIN_, MX_UART_NUM)
#define MX_UART_TX_PORT_X    CAL_APPEND(MX_UART_TX_PORT_, MX_UART_NUM)
#define MX_UART_RX_PIN_X     CAL_APPEND(MX_UART_RX_PIN_, MX_UART_NUM)
#define MX_UART_RX_PORT_X    CAL_APPEND(MX_UART_RX_PORT_, MX_UART_NUM)
#define MX_UART_TX_AF_X      CAL_APPEND(MX_UART_TX_AF_, MX_UART_NUM)
#define MX_UART_RX_AF_X      CAL_APPEND(MX_UART_RX_AF_, MX_UART_NUM)
#define MX_UART_TX_EN_X      CAL_APPEND(MX_UART_TX_EN_, MX_UART_NUM)
#define MX_UART_RX_EN_X      CAL_APPEND(MX_UART_RX_EN_, MX_UART_NUM)

/* Baud rate calculation:
 * BRR = (PCLK / (64 * 2^(2*n-1) * B)) - 1
 * With SEMR_BGDM=1, SEMR_ABCS=1 (8x base clock):
 * BRR = (PCLK / (8 * B)) - 1
 * For 48MHz, 115200 baud: BRR = (48000000 / (8*115200)) - 1 = 51.08 ~ 51
 */
#define RA_UART_BRR(baud)  ((unsigned char)((RA4M1_SYSCLK / (8UL * (baud))) - 1UL))

CALFUNCTION(void, FC_CAL_UART_Init_, (MX_UINT16 BaudRate, MX_UINT8 DataBits, MX_UINT8 Parity, MX_UINT8 StopBits))
{
    RA_SCI_Type *sci = R_SCI(MX_UART_CHANNEL_X);

    /* Enable SCI module clock (clear module stop) */
    RA_PRCR_UNLOCK(PRCR_PRC1);
    switch (MX_UART_CHANNEL_X) {
        case 0: R_MSTP_MSTPCRB &= ~MSTP_SCI0; break;
        case 1: R_MSTP_MSTPCRB &= ~MSTP_SCI1; break;
        case 2: R_MSTP_MSTPCRB &= ~MSTP_SCI2; break;
        case 9: R_MSTP_MSTPCRB &= ~MSTP_SCI9; break;
        default: break;
    }
    RA_PRCR_LOCK();

    /* Disable TX/RX before configuration */
    sci->SCR = 0x00U;

    /* Configure TX pin: peripheral mode, PSEL=MX_UART_TX_AF_X */
    RA_PFS_UNLOCK();
    R_PFS(MX_UART_TX_PORT_X, MX_UART_TX_PIN_X) =
        PFS_PDR | PFS_PMR | PFS_PSEL(MX_UART_TX_AF_X);
    /* Configure RX pin: input, peripheral mode */
    R_PFS(MX_UART_RX_PORT_X, MX_UART_RX_PIN_X) =
        PFS_PMR | PFS_PSEL(MX_UART_RX_AF_X) | PFS_PCR;
    RA_PFS_LOCK();

    /* UART async mode, 8-bit, no parity, 1 stop */
    sci->SMR  = 0x00U;  /* async, 8-bit, no parity, 1 stop, PCLK/1 */
    sci->SCMR = 0xF2U;  /* default smart card mode off */

    /* Double-speed mode for better accuracy */
    sci->SEMR = SCI_SEMR_BGDM | SCI_SEMR_ABCS;

    /* Set baud rate */
    sci->BRR = RA_UART_BRR(MX_UART_BAUD_X);

    /* Enable TX and RX */
    sci->SCR = SCI_SCR_TE | SCI_SCR_RE;
}

CALFUNCTION(void, FC_CAL_UART_Uninit_, (void))
{
    RA_SCI_Type *sci = R_SCI(MX_UART_CHANNEL_X);
    /* Wait for transmit to finish, then disable */
    while (!(sci->SSR & SCI_SSR_TEND))
        ;
    sci->SCR = 0x00U;
}

CALFUNCTION(void, FC_CAL_UART_TX_, (MX_UINT8 Data))
{
    RA_SCI_Type *sci = R_SCI(MX_UART_CHANNEL_X);
    while (!(sci->SSR & SCI_SSR_TDRE))
        ;
    sci->TDR = Data;
}

CALFUNCTION(MX_UINT8, FC_CAL_UART_RX_, (void))
{
    RA_SCI_Type *sci = R_SCI(MX_UART_CHANNEL_X);
    while (!(sci->SSR & SCI_SSR_RDRF))
        ;
    return sci->RDR;
}

CALFUNCTION(MX_UINT8, FC_CAL_UART_RXReady_, (void))
{
    return (R_SCI(MX_UART_CHANNEL_X)->SSR & SCI_SSR_RDRF) ? 1U : 0U;
}

CALFUNCTION(MX_UINT8, FC_CAL_UART_TXReady_, (void))
{
    return (R_SCI(MX_UART_CHANNEL_X)->SSR & SCI_SSR_TDRE) ? 1U : 0U;
}

CALFUNCTION(void, FC_CAL_UART_TXString_, (MX_UINT8* Str))
{
    while (*Str)
        FC_CAL_UART_TX_CAL_APPEND(, MX_UART_NUM)(*Str++);
}
