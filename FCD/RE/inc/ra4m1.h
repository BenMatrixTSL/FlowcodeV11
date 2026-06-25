// CRC: 56ACC9821434AD1AE7DB748CB428C8DFCFD1715FE1327F87E421B2A531E4B244011496AE222D8A5BBDA9DACA3792E771A54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E15F159E83FCED4583E9FBCD156B518C3E0269A576231159022CC66A7A83000063C106A4056387E7D6696926F22373EABFABAF50403BA6F973996ACB45249626CC3A2329BDBCEFF5A8DB8C218D70737B0D7304EA5BBBF8B213E549D34A0D5AD11F32BD46BF44C0CC5A32AD5AC0D119975BB9CF3BA3B66193EF6BFDF2E6001B9426D00C9FC801055D429
// REVISION: 1.0
// GUID: 2483D893-4D79-4B0E-A7F6-E8EECC2E5E2A
// DATE: 25\06\2026
// DIR: FCD\RE\inc\ra4m1.h
/*
 * ra4m1.h - Renesas RA4M1 peripheral register definitions
 * Covers: R7FA4M1AB3CFM (48MHz Cortex-M4, 256KB Flash, 32KB RAM)
 * Used on: Arduino Uno R4 Minima, Arduino Uno R4 WiFi
 *
 * Based on RA4M1 User's Manual R01UH0887EJ0110
 */

#ifndef RA4M1_H
#define RA4M1_H

#include <stdint.h>

/* =========================================================================
   IOPORT - GPIO
   ========================================================================= */

/* Port control registers: base 0x40080000, each port +0x20 */
typedef struct {
    union {
        volatile uint32_t PCNTR1;
        struct {
            volatile uint16_t PODR;   /* Port Output Data */
            volatile uint16_t PDR;    /* Port Direction (1=output) */
        };
    };
    union {
        volatile const uint32_t PCNTR2;
        struct {
            volatile const uint16_t PIDR;  /* Port Input Data */
            volatile const uint16_t EIDR;  /* Event Input Data */
        };
    };
    union {
        volatile uint32_t PCNTR3;
        struct {
            volatile uint16_t PORR;   /* Port Output Reset */
            volatile uint16_t POSR;   /* Port Output Set */
        };
    };
    union {
        volatile uint32_t PCNTR4;
        struct {
            volatile uint16_t EORR;
            volatile uint16_t EOSR;
        };
    };
} RA_PORT_Type;

#define R_PORT_BASE   0x40080000UL
#define R_PORT(n)     ((RA_PORT_Type *)(R_PORT_BASE + (n) * 0x20U))

#define R_PORT0       R_PORT(0)
#define R_PORT1       R_PORT(1)
#define R_PORT2       R_PORT(2)
#define R_PORT3       R_PORT(3)
#define R_PORT4       R_PORT(4)
#define R_PORT5       R_PORT(5)
#define R_PORT9       R_PORT(9)

/* Pin Function Select: base 0x40080800, [port][pin] each 4 bytes */
#define R_PFS_BASE    0x40080800UL
#define R_PFS(p,n)    (*(volatile uint32_t *)(R_PFS_BASE + (p)*0x20U + (n)*4U))

/* PFS bit fields */
#define PFS_PODR      (1UL << 0)   /* Output data */
#define PFS_PIDR      (1UL << 1)   /* Input data (read-only) */
#define PFS_PDR       (1UL << 2)   /* Direction: 1=output */
#define PFS_PCR       (1UL << 4)   /* Pull-up: 1=enable */
#define PFS_NCODR     (1UL << 6)   /* Open drain: 1=enable */
#define PFS_DSCR_LOW  (0UL << 8)   /* Drive strength low */
#define PFS_DSCR_MID  (1UL << 8)   /* Drive strength medium-low */
#define PFS_DSCR_HI   (2UL << 8)   /* Drive strength medium-high */
#define PFS_DSCR_MAX  (3UL << 8)   /* Drive strength high */
#define PFS_ISEL      (1UL << 14)  /* IRQ input enable */
#define PFS_ASEL      (1UL << 15)  /* Analog input enable */
#define PFS_PMR       (1UL << 16)  /* Peripheral mode: 1=peripheral */
#define PFS_PSEL(x)   (((x) & 0x1FUL) << 24) /* Peripheral select */

/* PMISC - Port miscellaneous: unlock PFS writes */
#define R_PMISC_BASE  0x40080008UL
#define R_PMISC_PWPR (*(volatile uint8_t *)(R_PMISC_BASE + 0x02U))
#define PWPR_BOWI     (1U << 7)    /* Write-protect bit-operation inhibit */
#define PWPR_PFSWE    (1U << 6)    /* PFS write enable */

/* PFS write unlock/lock macros */
#define RA_PFS_UNLOCK()  do { R_PMISC_PWPR = 0U; R_PMISC_PWPR = PWPR_PFSWE; } while(0)
#define RA_PFS_LOCK()    do { R_PMISC_PWPR = 0U; R_PMISC_PWPR = PWPR_BOWI;  } while(0)

/* =========================================================================
   Protect Register - unlock write access to certain registers
   ========================================================================= */
#define R_PRCR        (*(volatile uint16_t *)0x40001FF0UL)
#define PRCR_KEY      (0xA500U)
#define PRCR_PRC0     (1U << 0)   /* Clock/LVD register access */
#define PRCR_PRC1     (1U << 1)   /* Low power mode register access */
#define PRCR_PRC3     (1U << 3)   /* CGC register access */

#define RA_PRCR_UNLOCK(bits)  (R_PRCR = PRCR_KEY | (bits))
#define RA_PRCR_LOCK()        (R_PRCR = PRCR_KEY)

/* =========================================================================
   Module Stop - enable/disable peripheral clocks
   ========================================================================= */
#define R_MSTP_MSTPCRA (*(volatile uint32_t *)0x40047000UL)
#define R_MSTP_MSTPCRB (*(volatile uint32_t *)0x40047004UL)
#define R_MSTP_MSTPCRC (*(volatile uint32_t *)0x40047008UL)
#define R_MSTP_MSTPCRD (*(volatile uint32_t *)0x4004700CUL)

/* MSTPCRD bit positions for RA4M1 peripherals */
#define MSTP_GPT0     (1UL << 5)   /* GPT0-3 */
#define MSTP_GPT4     (1UL << 4)   /* GPT4-7 */
#define MSTP_ADC0     (1UL << 16)  /* ADC140 unit 0 */
#define MSTP_DAC0     (1UL << 19)  /* DAC12 */

/* MSTPCRB bit positions */
#define MSTP_SCI0     (1UL << 31)
#define MSTP_SCI1     (1UL << 30)
#define MSTP_SCI2     (1UL << 29)
#define MSTP_SCI9     (1UL << 22)
#define MSTP_SPI0     (1UL << 19)
#define MSTP_IIC0     (1UL << 9)
#define MSTP_IIC1     (1UL << 8)

/* Enable clock to peripheral (clear stop bit) */
#define RA_MSTP_ENABLE_B(bit)  (R_MSTP_MSTPCRB &= ~(bit))
#define RA_MSTP_ENABLE_D(bit)  (R_MSTP_MSTPCRD &= ~(bit))

/* =========================================================================
   SCI - Serial Communications Interface (UART/SPI/I2C mode)
   ========================================================================= */
typedef struct {
    volatile uint8_t  SMR;    /* Serial mode register */
    volatile uint8_t  BRR;    /* Bit rate register */
    volatile uint8_t  SCR;    /* Serial control register */
    volatile uint8_t  TDR;    /* Transmit data register */
    volatile uint8_t  SSR;    /* Serial status register */
    volatile uint8_t  RDR;    /* Receive data register */
    volatile uint8_t  SCMR;   /* Smart card mode register */
    volatile uint8_t  SEMR;   /* Serial extended mode register */
    volatile uint8_t  SNFR;   /* Noise filter setting register */
    volatile uint8_t  SIMR1;  /* I2C mode register 1 */
    volatile uint8_t  SIMR2;  /* I2C mode register 2 */
    volatile uint8_t  SIMR3;  /* I2C mode register 3 */
    volatile uint8_t  SISR;   /* I2C status register */
    volatile uint8_t  SPMR;   /* SPI mode register */
    union {
        volatile uint16_t TDRHL;
        struct { volatile uint8_t TDRL; volatile uint8_t TDRH; };
    };
    union {
        volatile const uint16_t RDRHL;
        struct { volatile const uint8_t RDRL; volatile const uint8_t RDRH; };
    };
    volatile uint8_t  MDDR;   /* Modulation duty register */
    volatile uint8_t  DCCR;   /* Data compare match control register */
    volatile uint16_t FCR;    /* FIFO control register */
    volatile uint16_t FDR;    /* FIFO data count register */
    volatile uint16_t LSR;    /* Line status register */
    volatile uint16_t CDR;    /* Compare match data register */
    volatile uint8_t  SPTR;   /* Serial port register */
} RA_SCI_Type;

#define R_SCI_BASE    0x40118000UL
#define R_SCI(n)      ((RA_SCI_Type *)(R_SCI_BASE + (n) * 0x100U))
#define R_SCI0        R_SCI(0)
#define R_SCI1        R_SCI(1)
#define R_SCI2        R_SCI(2)
#define R_SCI9        R_SCI(9)

/* SCR bits */
#define SCI_SCR_CKE(x) ((x) & 3U)
#define SCI_SCR_TEIE   (1U << 2)
#define SCI_SCR_MPIE   (1U << 3)
#define SCI_SCR_RE     (1U << 4)   /* Receive enable */
#define SCI_SCR_TE     (1U << 5)   /* Transmit enable */
#define SCI_SCR_RIE    (1U << 6)   /* Receive interrupt enable */
#define SCI_SCR_TIE    (1U << 7)   /* Transmit interrupt enable */

/* SSR bits */
#define SCI_SSR_TEND   (1U << 2)   /* Transmit end */
#define SCI_SSR_RDRF   (1U << 6)   /* Receive data full */
#define SCI_SSR_TDRE   (1U << 7)   /* Transmit data empty */

/* SMR bits */
#define SCI_SMR_CM     (1U << 7)   /* 0=async, 1=clock sync */

/* SEMR bits */
#define SCI_SEMR_ABCS  (1U << 4)   /* 8 base clock cycles per bit */
#define SCI_SEMR_BGDM  (1U << 6)   /* Baud rate generator double */

/* =========================================================================
   IIC - I2C Master/Slave
   ========================================================================= */
typedef struct {
    volatile uint8_t  ICCR1;   /* I2C control register 1 */
    volatile uint8_t  ICCR2;   /* I2C control register 2 */
    volatile uint8_t  ICMR1;   /* I2C mode register 1 */
    volatile uint8_t  ICMR2;   /* I2C mode register 2 */
    volatile uint8_t  ICMR3;   /* I2C mode register 3 */
    volatile uint8_t  ICFER;   /* I2C function enable register */
    volatile uint8_t  ICSER;   /* I2C status enable register */
    volatile uint8_t  ICIER;   /* I2C interrupt enable register */
    volatile uint8_t  ICSR1;   /* I2C status register 1 */
    volatile uint8_t  ICSR2;   /* I2C status register 2 */
    volatile uint8_t  SARL0;   /* Slave address register L0 */
    volatile uint8_t  SARU0;   /* Slave address register U0 */
    volatile uint8_t  SARL1;
    volatile uint8_t  SARU1;
    volatile uint8_t  SARL2;
    volatile uint8_t  SARU2;
    volatile uint8_t  ICBRL;   /* I2C bit rate low register */
    volatile uint8_t  ICBRH;   /* I2C bit rate high register */
    volatile uint8_t  ICDRT;   /* I2C transmit data register */
    volatile uint8_t  ICDRR;   /* I2C receive data register */
} RA_IIC_Type;

#define R_IIC_BASE    0x40053000UL
#define R_IIC(n)      ((RA_IIC_Type *)(R_IIC_BASE + (n) * 0x100U))
#define R_IIC0        R_IIC(0)
#define R_IIC1        R_IIC(1)

/* ICCR1 bits */
#define IIC_ICCR1_SDAI  (1U << 0)
#define IIC_ICCR1_SCLI  (1U << 1)
#define IIC_ICCR1_SDAO  (1U << 2)
#define IIC_ICCR1_SCLO  (1U << 3)
#define IIC_ICCR1_SOWP  (1U << 4)
#define IIC_ICCR1_CLO   (1U << 5)
#define IIC_ICCR1_IICRST (1U << 6)
#define IIC_ICCR1_ICE   (1U << 7)

/* ICCR2 bits */
#define IIC_ICCR2_ST    (1U << 1)  /* Start condition */
#define IIC_ICCR2_RS    (1U << 2)  /* Restart condition */
#define IIC_ICCR2_SP    (1U << 3)  /* Stop condition */
#define IIC_ICCR2_TRS   (1U << 5)  /* Transmit/receive mode */
#define IIC_ICCR2_MST   (1U << 6)  /* Master/slave mode */
#define IIC_ICCR2_BBSY  (1U << 7)  /* Bus busy */

/* ICSR2 bits */
#define IIC_ICSR2_NACKF  (1U << 4)
#define IIC_ICSR2_STOP   (1U << 3)
#define IIC_ICSR2_START  (1U << 2)
#define IIC_ICSR2_TDRE   (1U << 7)
#define IIC_ICSR2_RDRF   (1U << 5)
#define IIC_ICSR2_TEND   (1U << 6)

/* =========================================================================
   SPI - Serial Peripheral Interface
   ========================================================================= */
typedef struct {
    volatile uint8_t  SPCR;    /* SPI control register */
    volatile uint8_t  SSLP;    /* SPI slave select polarity */
    volatile uint8_t  SPPCR;   /* SPI pin control register */
    volatile uint8_t  SPSR;    /* SPI status register */
    volatile uint32_t SPDR;    /* SPI data register (32-bit) */
    volatile uint8_t  SPSCR;   /* SPI sequence control register */
    volatile uint8_t  SPSSR;   /* SPI sequence status register */
    volatile uint8_t  SPBR;    /* SPI bit rate register */
    volatile uint8_t  SPDCR;   /* SPI data control register */
    volatile uint8_t  SPCKD;   /* SPI clock delay register */
    volatile uint8_t  SSLND;   /* SPI slave select negation delay */
    volatile uint8_t  SPND;    /* SPI next-access delay register */
    volatile uint8_t  SPDCR2;  /* SPI data control register 2 */
    volatile uint16_t SPCMD0;  /* SPI command register 0 */
    volatile uint16_t SPCMD1;
    volatile uint16_t SPCMD2;
    volatile uint16_t SPCMD3;
    volatile uint16_t SPCMD4;
    volatile uint16_t SPCMD5;
    volatile uint16_t SPCMD6;
    volatile uint16_t SPCMD7;
    volatile uint8_t  SPDCR3;
} RA_SPI_Type;

#define R_SPI_BASE    0x40072000UL
#define R_SPI(n)      ((RA_SPI_Type *)(R_SPI_BASE + (n) * 0x100U))
#define R_SPI0        R_SPI(0)

/* SPCR bits */
#define SPI_SPCR_SPMS   (1U << 0)   /* 0=SPI, 1=Clock sync */
#define SPI_SPCR_TXMD   (1U << 1)   /* 0=full duplex, 1=transmit only */
#define SPI_SPCR_MSTR   (1U << 3)   /* 1=master */
#define SPI_SPCR_SPE    (1U << 6)   /* SPI function enable */
#define SPI_SPCR_SPRIE  (1U << 7)   /* Receive interrupt enable */

/* SPSR bits */
#define SPI_SPSR_OVRF   (1U << 0)
#define SPI_SPSR_IDLNF  (1U << 1)
#define SPI_SPSR_MODF   (1U << 2)
#define SPI_SPSR_PERF   (1U << 3)
#define SPI_SPSR_UDRF   (1U << 4)
#define SPI_SPSR_SPTEF  (1U << 5)   /* Transmit buffer empty */
#define SPI_SPSR_SPRF   (1U << 7)   /* Receive buffer full */

/* =========================================================================
   ADC140 - 14-bit ADC
   ========================================================================= */
typedef struct {
    volatile uint16_t ADCSR;    /* A/D control register */
    volatile uint8_t  reserved0[2];
    volatile uint16_t ADANSA0;  /* A/D channel select A0 */
    volatile uint16_t ADANSA1;
    volatile uint16_t ADADS0;   /* A/D-converted value average channel select 0 */
    volatile uint16_t ADADS1;
    volatile uint8_t  ADADC;    /* A/D-converted value average count select */
    volatile uint8_t  reserved1;
    volatile uint16_t ADCER;    /* A/D control extended register */
    volatile uint16_t ADSTRGR;  /* A/D conversion start trigger select register */
    volatile uint8_t  reserved2[2];
    volatile uint16_t ADANSB0;
    volatile uint16_t ADANSB1;
    volatile uint16_t ADDBLDR;  /* A/D double trigger data register */
    volatile uint8_t  reserved3[4];
    volatile uint16_t ADRD;     /* A/D self-diagnosis data register */
    volatile uint16_t ADDR[29]; /* A/D data registers (channels 0-28) */
} RA_ADC_Type;

#define R_ADC_BASE    0x4005C000UL
#define R_ADC0        ((RA_ADC_Type *)R_ADC_BASE)

/* ADCSR bits */
#define ADC_ADCSR_DBLANS(x) ((x) & 0x1FU)
#define ADC_ADCSR_GBADIE    (1U << 6)
#define ADC_ADCSR_DBLE      (1U << 7)
#define ADC_ADCSR_EXTRG     (1U << 8)
#define ADC_ADCSR_TRGE      (1U << 9)
#define ADC_ADCSR_ADHSC     (1U << 10)
#define ADC_ADCSR_ADIE      (1U << 12)
#define ADC_ADCSR_ADCS(x)   (((x) & 3U) << 13)  /* 00=single, 01=sequence A, 11=continuous */
#define ADC_ADCSR_ADST      (1U << 15)           /* Start conversion */

/* ADCER bits */
#define ADC_ADCER_ADPRC(x)  (((x) & 3U) << 1)   /* 00=14-bit, 01=12-bit, 02=10-bit, 03=8-bit */
#define ADC_ADCER_DCE       (1U << 5)
#define ADC_ADCER_ACE       (1U << 9)
#define ADC_ADCER_DIAGVAL(x)(((x) & 3U) << 14)
#define ADC_ADCER_DIAGLD    (1U << 13)
#define ADC_ADCER_DIAGM     (1U << 11)

/* =========================================================================
   GPT - General PWM Timer
   ========================================================================= */
typedef struct {
    volatile uint32_t GTWP;     /* Write-protect register */
    volatile uint32_t GTSTR;    /* Start register */
    volatile uint32_t GTSTP;    /* Stop register */
    volatile uint32_t GTCLR;    /* Clear register */
    volatile uint32_t GTSSR;    /* Start/stop/clear source select register */
    volatile uint32_t GTPSR;
    volatile uint32_t GTCSR;
    volatile uint32_t GTUPSR;
    volatile uint32_t GTDNSR;
    volatile uint32_t GTICASR;
    volatile uint32_t GTICBSR;
    volatile uint32_t GTCR;     /* Control register */
    volatile uint32_t GTUDDTYC; /* Up/down/duty register */
    volatile uint32_t GTIOR;    /* I/O control register */
    volatile uint32_t GTINTAD;
    volatile uint32_t GTST;     /* Status register */
    volatile uint32_t GTBER;    /* Buffer enable register */
    volatile uint32_t GTITC;
    volatile uint32_t GTCNT;    /* Counter */
    volatile uint32_t GTCCRA;   /* Capture/compare register A */
    volatile uint32_t GTCCRB;
    volatile uint32_t GTCCRC;
    volatile uint32_t GTCCRE;
    volatile uint32_t GTCCRD;
    volatile uint32_t GTCCRF;
    volatile uint32_t GTPR;     /* Period register */
    volatile uint32_t GTPBR;    /* Period buffer register */
    volatile uint32_t GTPDBR;
    volatile uint32_t GTADTRA;
    volatile uint32_t GTADTRB;
    volatile uint32_t GTADTBRA;
    volatile uint32_t GTADTBRB;
    volatile uint32_t GTADTDBRA;
    volatile uint32_t GTADTDBRB;
    volatile uint32_t GTDTCR;   /* Dead time control register */
    volatile uint32_t GTDVU;    /* Dead time value register U */
    volatile uint32_t GTDVD;
} RA_GPT_Type;

#define R_GPT_BASE    0x40169000UL
#define R_GPT(n)      ((RA_GPT_Type *)(R_GPT_BASE + (n) * 0x100U))

/* GTCR bits */
#define GPT_GTCR_CST     (1UL << 0)    /* Counter start */
#define GPT_GTCR_MD(x)   (((x) & 0xFUL) << 16) /* Mode: 0=saw-wave, 3=triangle */
#define GPT_GTCR_TPCS(x) (((x) & 0xFUL) << 23) /* Timer prescaler */

/* GTUDDTYC bits */
#define GPT_GTUDDTYC_UD    (1UL << 0)   /* 1=count-up, 0=count-down */
#define GPT_GTUDDTYC_UDF   (1UL << 1)   /* Force update */
#define GPT_GTUDDTYC_OADTY(x) (((x) & 3UL) << 16) /* GTIOCA duty 0=0%, 2=cycle, 3=100% */
#define GPT_GTUDDTYC_OBDTY(x) (((x) & 3UL) << 24)

/* GTIOR bits */
#define GPT_GTIOR_GTIOA(x)  ((x) & 0x1FUL)       /* GTIOCA output: 9=initial low, toggle on match */
#define GPT_GTIOR_GTIOB(x)  (((x) & 0x1FUL) << 16)

/* GTPR - period value, GTCCRA - compare A (duty) */

/* =========================================================================
   DAC12 - 12-bit DAC
   ========================================================================= */
typedef struct {
    volatile uint16_t DADR[2];  /* D/A data registers */
    volatile uint8_t  DACR;     /* D/A control register */
    volatile uint8_t  DADPR;    /* D/A data format select */
    volatile uint8_t  DAADSCR; /* D/A A/D sync start control */
    volatile uint8_t  reserved[3];
    volatile uint8_t  DAVREFCR; /* D/A VREF control */
} RA_DAC_Type;

#define R_DAC_BASE    0x4005E000UL
#define R_DAC0        ((RA_DAC_Type *)R_DAC_BASE)

/* DACR bits */
#define DAC_DACR_DAOE0  (1U << 6)  /* DAC channel 0 output enable */
#define DAC_DACR_DAOE1  (1U << 7)  /* DAC channel 1 output enable */

/* =========================================================================
   ARM Cortex-M4 system registers (from CMSIS core_cm4.h)
   ========================================================================= */
#ifndef __CM4_CORE_H
#define SysTick_BASE    0xE000E010UL
typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile const uint32_t CALIB;
} SysTick_Type;
#define SysTick         ((SysTick_Type *)SysTick_BASE)
#define SysTick_CTRL_ENABLE     (1UL << 0)
#define SysTick_CTRL_TICKINT    (1UL << 1)
#define SysTick_CTRL_CLKSOURCE  (1UL << 2)
#define SysTick_CTRL_COUNTFLAG  (1UL << 16)
#define NVIC_BASE       0xE000E100UL
#define SCB_BASE        0xE000ED00UL
typedef struct {
    volatile const uint32_t CPUID;
    volatile uint32_t ICSR;
    volatile uint32_t VTOR;
    volatile uint32_t AIRCR;
    volatile uint32_t SCR;
    volatile uint32_t CCR;
    volatile uint8_t  SHP[12U];
    volatile uint32_t SHCSR;
    volatile uint32_t CFSR;
    volatile uint32_t HFSR;
    volatile uint32_t DFSR;
    volatile uint32_t MMFAR;
    volatile uint32_t BFAR;
    volatile uint32_t AFSR;
} SCB_Type;
#define SCB             ((SCB_Type *)SCB_BASE)
#endif /* __CM4_CORE_H */

/* =========================================================================
   RA4M1 Clock - HOCO (48MHz) default, or external crystal
   ========================================================================= */
#define R_SYSTEM_BASE   0x4001E000UL
#define R_SCKSCR        (*(volatile uint8_t  *)(R_SYSTEM_BASE + 0x026U))  /* Clock source select */
#define R_HOCOCR        (*(volatile uint8_t  *)(R_SYSTEM_BASE + 0x036U))  /* HOCO control */
#define R_HOCOCR2       (*(volatile uint8_t  *)(R_SYSTEM_BASE + 0x037U))  /* HOCO control 2 */
#define R_HOCOWTCR      (*(volatile uint8_t  *)(R_SYSTEM_BASE + 0x0A5U))  /* HOCO wait control */
#define R_OSCSF         (*(volatile const uint8_t *)(R_SYSTEM_BASE + 0x03CU)) /* Oscillator stabilisation flag */

/* SCKSCR values */
#define SCKSCR_HOCO     0x00U   /* HOCO (default) */
#define SCKSCR_MOCO     0x01U   /* MOCO */
#define SCKSCR_LOCO     0x02U   /* LOCO */
#define SCKSCR_MOSC     0x03U   /* Main oscillator */
#define SCKSCR_SOSC     0x04U   /* Sub-clock oscillator */
#define SCKSCR_PLL      0x05U   /* PLL */

/* HOCO frequency select (HOCOCR2) */
#define HOCOCR2_24MHZ   0x00U
#define HOCOCR2_32MHZ   0x02U
#define HOCOCR2_48MHZ   0x04U

/* System clock frequency (set by racomp.bat define or user) */
#ifndef RA4M1_SYSCLK
  #define RA4M1_SYSCLK  48000000UL
#endif

#endif /* RA4M1_H */
