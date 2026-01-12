// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B8E81ED91D49E0ED362EB402B0BFAA73A454F47991010047065377AFFBE12548F39A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF55E9A682864DBC3A57F898C97AC9CC0B4F40AB1FB1D387D6EE8BBF438F06DA4A6FF5BF3AECD03832ADBF49FC71DAC863A6B9C0549DCCE776295D2C8131F4C02D7467B1279F6EF687078F706DCACA404270E980C661EB8F258549D34A0D5AD11F3FFC4872C72D221BBA4E182C3DA1CCAA2D1E3EB90D14C71A727A8E1A814A6FBB04A61C0D2CB77CF29
// REVISION: 1.0
// GUID: 70FDA7D3-805A-4564-B03D-C703ABF0E416
// DATE: 08\08\2022
// DIR: CAL\PIC\PIC_CAL_MIAC_SYSTEM.c
/*********************************************************************
 *                  Flowcode CAL MIAC System File
 *
 * File: PIC_CAL_MIAC_SYSTEM.c
 *
 * (c) 2011 Matrix Multimedia Ltd.
 * http://www.matrixmultimedia.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix Multimedia Ltd (the
 * “Company”) for its Flowcode graphical programming language is
 * intended and supplied to you, the Company’s customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Changelog:
 *
 *  date  | by | description
 * -------+----+-----------------------------------------------------
 * 010911 | BR | Created
 * 160712 | LM | Updates to CAN processing for more flexible system
 * 200712 | LM | Support for custom module CAN ID
 * 250712 | LM | Repeat custom CAN setting to improve EEPROM write
 * 150812 | LM | Switch on the CAN Rx Filters and only for Standard Frame IDs
 * 261115 | LM | API for V6 MIAC Module/Addon Components
 * 041215 | LM | Clear MIAC_CAN_TX_COUNT after CAN_SendBuffer() to simplify use
 */


MX_UINT8 MIAC_CAN_TX[6];
MX_UINT8 MIAC_CAN_TX_COUNT = 0;
MX_UINT8 MIAC_CAN_RX[6];
MX_UINT16 MIAC_CAN_ID;

union Float4Bytes
{
	float FloatVal;
	MX_UINT8 ByteArray[4];
};
union Float4Bytes FloatConv;


void SPI_Init(void);
MX_UINT8 SPI_SendByte(MX_UINT8);
MX_UINT8 CAN_MaskFromBit(MX_UINT8);
void CAN_Reset(void);
void CAN_Write(MX_UINT8, MX_UINT8);
MX_UINT8 CAN_Read(MX_UINT8);
void CAN_Config(MX_UINT8);
MX_UINT8 CAN_ReadStatus(void);
MX_UINT8 CAN_ReadRXStatus(void);
void CAN_BitModify(MX_UINT8, MX_UINT8, MX_UINT8);
MX_UINT8 CAN_ReadRX_ID_and_Data(MX_UINT8);
void CAN_Init(void);
void CAN_SendBuffer(MX_UINT8);
MX_UINT8 CAN_CheckRx(MX_UINT8);
MX_UINT8 CAN_GetRxDataCount(MX_UINT8);
MX_UINT8 CAN_GetRxData(MX_UINT8, MX_UINT8);
void CAN_SetTxData(MX_UINT8, MX_UINT8, MX_UINT8, MX_UINT8, MX_UINT8, MX_UINT8, MX_UINT8, MX_UINT8, MX_UINT8, MX_UINT8);
void CAN_SetTxID(MX_UINT8, MX_UINT16);
MX_UINT8 CAN_GetRxIDLo(MX_UINT8);
MX_UINT8 CAN_GetRxIDHi(MX_UINT8);
void CAN_CancelTx(MX_UINT8);
void CAN_SetFilter (MX_UINT16);
void CAN_SetCNF1(MX_UINT8);

void MIAC_Module_WR(MX_UINT16, MX_UINT16, MX_UINT8, MX_UINT8, MX_UINT8);
MX_UINT8 MIAC_Module_RD(MX_UINT16, MX_UINT16);
MX_UINT8 MIAC_Module_GetAck(MX_UINT16, MX_UINT16, MX_UINT16);
void MIAC_Module_Init(MX_UINT16);
MX_UINT8 MIAC_Module_Factory_Settings(MX_UINT16);
MX_UINT8 MIAC_Module_Custom_Settings(MX_UINT16, MX_UINT16, MX_UINT16, MX_UINT16);
void MIAC_Master_RelayON(MX_UINT8);
void MIAC_Master_RelayOFF(MX_UINT8);
void MIAC_Master_OutputON(MX_UINT8);
void MIAC_Master_OutputOFF(MX_UINT8);
MX_UINT8 MIAC_Master_InputDIGITAL(MX_UINT8);
MX_UINT8 MIAC_Master_InputANA(MX_UINT8);
MX_UINT16 MIAC_Master_InputANA10(MX_UINT8);


#define MX_CAN_PORT 		portb
#define MX_CAN_TRIS 		trisb
#define MX_CAN_SDO_TRIS 	trisc
#define MX_CAN_CS_PORT 		portd
#define MX_CAN_CS_TRIS 		trisd
#define MX_CAN_INT_PORT 	porta
#define MX_CAN_INT_TRIS 	trisa
#define CAN_CHIPSEL  		7
#define CAN_INTERRUPT  		4
#define CAN_INT_MASK  		16


//common defines
#define CNF1_VAL  		0x01
#define CNF2_VAL  		0xd1
#define CNF3_VAL  		0x03
#define BFPCTRL_VAL    	0x00
#define TXRTSCTRL_VAL	0x00

#define CAN_MAX_TX_BUF	(3)
#define CAN_MAX_RX_BUF	(2)

//One shot mode, CLKOUT enable, CLKOUT prescaler
#define CANCTRL_VAL		0x80
#define MX_CANSTAT_VAL	0x80

//Extended ID Dummy Values
#define TXB0EID8_VAL	0x00
#define TXB0EID0_VAL	0x00
#define TXB1EID8_VAL	0x00
#define TXB1EID0_VAL	0x00
#define TXB2EID8_VAL	0x00
#define TXB2EID0_VAL	0x00
#define RXF0EID8_VAL	0x00
#define RXF0EID0_VAL	0x00
#define RXF1EID8_VAL	0x00
#define RXF1EID0_VAL	0x00
#define RXF2EID8_VAL	0x00
#define RXF2EID0_VAL	0x00
#define RXF3EID8_VAL	0x00
#define RXF3EID0_VAL	0x00
#define RXF4EID8_VAL	0x00
#define RXF4EID0_VAL	0x00
#define RXF5EID8_VAL	0x00
#define RXF5EID0_VAL	0x00
#define RXM0EID8_VAL	0xFF
#define RXM0EID0_VAL	0xFF
#define RXM1EID8_VAL	0xFF
#define RXM1EID0_VAL	0xFF

//CANCTRL
#define REQOP_CONFIG		0x80
#define REQOP_LISTEN		0x60
#define REQOP_LOOPBACK		0x40
#define REQOP_SLEEP			0x20
#define REQOP_NORMAL		0x00


//Transmission message (TXB0):
#define TXB0CTRL_VAL   3		//Priority (highest)
#define TXB0SIDH_VAL   0
#define TXB0SIDL_VAL   0
#define TXB0DLC_VAL    0
#define TXB0DB0_VAL    0
#define TXB0DB1_VAL    0
#define TXB0DB2_VAL    0
#define TXB0DB3_VAL    0
#define TXB0DB4_VAL    0
#define TXB0DB5_VAL    0
#define TXB0DB6_VAL    0
#define TXB0DB7_VAL    0

//Transmission message (TXB1):
#define TXB1CTRL_VAL   2		//Priority
#define TXB1SIDH_VAL   0
#define TXB1SIDL_VAL   0
#define TXB1DLC_VAL    0
#define TXB1DB0_VAL    0
#define TXB1DB1_VAL    0
#define TXB1DB2_VAL    0
#define TXB1DB3_VAL    0
#define TXB1DB4_VAL    0
#define TXB1DB5_VAL    0
#define TXB1DB6_VAL    0
#define TXB1DB7_VAL    0

//Transmission message (TXB2):
#define TXB2CTRL_VAL   1		//Priority (lowest)
#define TXB2SIDH_VAL   0
#define TXB2SIDL_VAL   0
#define TXB2DLC_VAL    0
#define TXB2DB0_VAL    0
#define TXB2DB1_VAL    0
#define TXB2DB2_VAL    0
#define TXB2DB3_VAL    0
#define TXB2DB4_VAL    0
#define TXB2DB5_VAL    0
#define TXB2DB6_VAL    0
#define TXB2DB7_VAL    0

//Reception (RXB0)
#define RXB0CTRL_VAL   0x20		// Only accept Standard IDs and use mask and filter
#define RXF0SIDH_VAL   0
#define RXF0SIDL_VAL   0
#define RXF1SIDH_VAL   0
#define RXF1SIDL_VAL   0
#define RXM0SIDH_VAL   255
#define RXM0SIDL_VAL   224		//Every bit is active

//Reception (RXB1)
#define RXB1CTRL_VAL   0x20
#define RXF2SIDH_VAL   0
#define RXF2SIDL_VAL   0
#define RXF3SIDH_VAL   0
#define RXF3SIDL_VAL   0
#define RXF4SIDH_VAL   0
#define RXF4SIDL_VAL   0
#define RXF5SIDH_VAL   0
#define RXF5SIDL_VAL   0
#define RXM1SIDH_VAL   255
#define RXM1SIDL_VAL   128


//This is the interrupt enable register (set to flag on message received - RX0 and RX1 - and on an error)
//#define CANINTE_VAL		0x23
//TODO: should we turn interrupts off, like this:
//#define CANINTE_VAL		0x00
//TODO: of just turn on RX interrupts, like this:
#define CANINTE_VAL		0x03


// **********************************************************************
// *              MCP2510 Register Definitions                          *
// **********************************************************************

//Configuration Registers
#define MX_CANSTAT			0x0E
#define CANCTRL				0x0F
#define BFPCTRL				0x0C
#define TEC					0x1C
#define REC					0x1D
#define CNF3				0x28
#define CNF2				0x29
#define CNF1				0x2A
#define CANINTE				0x2B
#define CANINTF				0x2C
#define EFLG				0x2D
#define TXRTSCTRL			0x0D

//Receive Filters
//NOTE: Use "a" for i={0,1,2} and "b" for i={3,4,5}
#define RXFxaSIDH(i)			((i*4)+0)
#define RXFxaSIDL(i)			((i*4)+1)
#define RXFxaEID8(i)			((i*4)+2)
#define RXFxaEID0(i)			((i*4)+3)
#define RXFxbSIDH(i)			((i*4)+4)
#define RXFxbSIDL(i)			((i*4)+5)
#define RXFxbEID8(i)			((i*4)+6)
#define RXFxbEID0(i)			((i*4)+7)

//Receive Masks
#define RXMxSIDH(i)			((i*4)+0x20)
#define RXMxSIDL(i)			((i*4)+0x21)
#define RXMxEID8(i)			((i*4)+0x22)
#define RXMxEID0(i)			((i*4)+0x23)

//Tx Buffers
#define TXBxCTRL(i)			((i*0x10)+0x30)
#define TXBxSIDH(i)			((i*0x10)+0x31)
#define TXBxSIDL(i)			((i*0x10)+0x32)
#define TXBxEID8(i)			((i*0x10)+0x33)
#define TXBxEID0(i)			((i*0x10)+0x34)
#define TXBxDLC(i)			((i*0x10)+0x35)
#define TXBxD0(i)			((i*0x10)+0x36)
#define TXBxDy(i,j)			((i*0x10)+0x36+j)

//Rx Buffers
#define RXBxCTRL(i)			((i*0x10)+0x60)
#define RXBxSIDH(i)			((i*0x10)+0x61)
#define RXBxSIDL(i)			((i*0x10)+0x62)
#define RXBxEID8(i)			((i*0x10)+0x63)
#define RXBxEID0(i)			((i*0x10)+0x64)
#define RXBxDLC(i)			((i*0x10)+0x65)
#define RXBxD0(i)			((i*0x10)+0x66)
#define RXBxDy(i,j)			((i*0x10)+0x66+j)


// *******************************************************************
// *               Bit register masks                                *
// *******************************************************************

//TXBnCTRL
#define MX_TXREQ			0x08
#define TXP					0x03

//RXBnCTRL
#define RXM					0x60
#define BUKT				0x04

//CANCTRL
#define REQOP				0xE0
#define MX_ABAT				0x10
#define CLKEN				0x04
#define CLKPRE				0x03
#define OSM					0x08             // (ST) new for the 2515

//MX_CANSTAT
#define REQOP				0xE0
#define ICOD				0x0E

//CANINTE
#define RX0IE				0x01
#define RX1IE				0x02
#define TX0IE				0x04
#define TX1IE				0x80
#define TX2IE				0x10
#define MX_ERRIE			0x20
#define MX_WAKIE			0x40
#define IVMIE				0x80

//CANINTF
#define RX0IF				0x01
#define RX1IF				0x02
#define TX0IF				0x04
#define TX1IF				0x80
#define TX2IF				0x10
#define MX_ERRIF			0x20
#define MX_WAKIF			0x40
#define IVMIF				0x80

//BFPCTRL
#define B1BFS				0x20
#define B0BFS				0x10
#define B1BFE				0x08
#define B0BFE				0x04
#define B1BFM				0x02
#define B0BFM				0x01

//CNF1 Masks
#define SJW					0xC0
#define BRP					0x3F

//CNF2 Masks
#define BTLMODE				0x80
#define MX_SAM				0x40
#define PHSEG1				0x38
#define PRSEG				0x07

//CNF3 Masks
#define MX_WAKFIL			0x40
#define PHSEG2				0x07
#define SOF					0x80             // (ST) new for the 2515

//TXRTSCTRL Masks
#define TXB2RTS				0x04
#define TXB1RTS				0x02
#define TXB0RTS				0x01


// *******************************************************************
// *                    Bit Timing Configuration                     *
// *******************************************************************

//CNF1
#define SJW_1TQ				0x40
#define SJW_2TQ				0x80
#define SJW_3TQ				0x90
#define SJW_4TQ				0xC0

//CNF2
#define BTLMODE_CNF3		0x80
#define BTLMODE_PH1_IPT		0x00

#define SMPL_3X				0x40
#define SMPL_1X				0x00

#define PHSEG1_8TQ			0x38
#define PHSEG1_7TQ			0x30
#define PHSEG1_6TQ			0x28
#define PHSEG1_5TQ			0x20
#define PHSEG1_4TQ			0x18
#define PHSEG1_3TQ			0x10
#define PHSEG1_2TQ			0x08
#define PHSEG1_1TQ			0x00

#define PRSEG_8TQ			0x07
#define PRSEG_7TQ			0x06
#define PRSEG_6TQ			0x05
#define PRSEG_5TQ			0x04
#define PRSEG_4TQ			0x03
#define PRSEG_3TQ			0x02
#define PRSEG_2TQ			0x01
#define PRSEG_1TQ			0x00

//CNF3
#define PHSEG2_8TQ			0x07
#define PHSEG2_7TQ			0x06
#define PHSEG2_6TQ			0x05
#define PHSEG2_5TQ			0x04
#define PHSEG2_4TQ			0x03
#define PHSEG2_3TQ			0x02
#define PHSEG2_2TQ			0x01
#define PHSEG2_1TQ			0x00

#define MX_WAKFIL_ENABLED	0x40
#define MX_WAKFIL_DISABLED	0x00


// *******************************************************************
// *                  Control/Configuration Registers                *
// *******************************************************************

//CANINTE
#define RX0IE_ENABLED		0x01
#define RX0IE_DISABLED		0x00
#define RX1IE_ENABLED		0x02
#define RX1IE_DISABLED		0x00
#define G_RXIE_ENABLED		0x03
#define G_RXIE_DISABLED		0x00

#define TX0IE_ENABLED		0x04
#define TX0IE_DISABLED		0x00
#define TX1IE_ENABLED		0x08
#define TX2IE_DISABLED		0x00
#define TX2IE_ENABLED		0x10
#define TX2IE_DISABLED		0x00
#define G_TXIE_ENABLED		0x1C
#define G_TXIE_DISABLED		0x00

#define MX_ERRIE_ENABLED	0x20
#define MX_ERRIE_DISABLED	0x00
#define MX_WAKIE_ENABLED	0x40
#define MX_WAKIE_DISABLED	0x00
#define IVRE_ENABLED		0x80
#define IVRE_DISABLED		0x00

//CANINTF
#define RX0IF_SET			0x01
#define RX0IF_RESET			0x00
#define RX1IF_SET			0x02
#define RX1IF_RESET			0x00
#define TX0IF_SET			0x04
#define TX0IF_RESET			0x00
#define TX1IF_SET			0x08
#define TX2IF_RESET			0x00
#define TX2IF_SET			0x10
#define TX2IF_RESET			0x00
#define MX_ERRIF_SET		0x20
#define MX_ERRIF_RESET		0x00
#define MX_WAKIF_SET		0x40
#define MX_WAKIF_RESET		0x00
#define IVRF_SET			0x80
#define IVRF_RESET			0x00


#define ABORT				0x10

#define CLKOUT_ENABLED		0x04
#define CLKOUT_DISABLED		0x00
#define CLKOUT_PRE_8		0x03
#define CLKOUT_PRE_4		0x02
#define CLKOUT_PRE_2		0x01
#define CLKOUT_PRE_1		0x00

//MX_CANSTAT
#define OPMODE_CONFIG		0x80
#define OPMODE_LISTEN		0x60
#define OPMODE_LOOPBACK		0x40
#define OPMODE_SLEEP		0x20
#define OPMODE_NORMAL		0x00


//RXBnCTRL
#define RXM_RCV_ALL			0x60
#define RXM_VALID_EXT		0x40
#define RXM_VALID_STD		0x20
#define RXM_VALID_ALL		0x00

#define RXRTR_REMOTE		0x08
#define RXRTR_NO_REMOTE		0x00

#define BUKT_ROLLOVER		0x04
#define BUKT_NO_ROLLOVER	0x00

#define FILHIT0_FLTR_1		0x01
#define FILHIT0_FLTR_0		0x00

#define FILHIT1_FLTR_5		0x05
#define FILHIT1_FLTR_4		0x04
#define FILHIT1_FLTR_3		0x03
#define FILHIT1_FLTR_2		0x02
#define FILHIT1_FLTR_1		0x01
#define FILHIT1_FLTR_0		0x00


//TXBnCTRL
#define MX_TXREQ_SEND		0x08
#define MX_TXREQ_ABORT		0x00

#define TXP_HIGHEST			0x03
#define TXP_INTER_HIGH		0x02
#define TXP_INTER_LOW		0x01
#define TXP_LOWEST			0x00


// *******************************************************************
// *                  Register Bit Masks                             *
// *******************************************************************

#define DLC_0				0x00
#define DLC_1				0x01
#define DLC_2				0x02
#define DLC_3				0x03
#define DLC_4				0x04
#define DLC_5				0x05
#define DLC_6				0x06
#define DLC_7				0x07
#define DLC_8				0x08


// *******************************************************************
// *                  CAN SPI commands                               *
// *******************************************************************

#define CAN_RESET			0xC0
#define CAN_READ			0x03
#define CAN_WRITE			0x02
#define CAN_RD_STATUS		0xA0
#define CAN_BIT_MODIFY		0x05

#define CAN_RTS				0x80
#define CAN_RTS_TXB0		0x81
#define CAN_RTS_TXB1		0x82
#define CAN_RTS_TXB2		0x84

#define CAN_RTS_TXB01		0x83
#define CAN_RTS_TXB02		0x85
#define CAN_RTS_TXB12		0x86
#define CAN_RTS_TXB012		0x87

#define CAN_RX_STATUS		0xB0

#define CAN_RD_RXBUF_ID(i)	(0x90 + (i*4))
#define CAN_RD_RXBUF_DT(i)	(0x92 + (i*4))

#define CAN_LD_TXBUF_ID(i)	(0x40 + (i*2))
#define CAN_LD_TXBUF_DT(i)	(0x41 + (i*2))


// SPI fixed defines
#define MX_SPI_SDI	0
#define MX_SPI_SDO	7
#define MX_SPI_SCK	1

MX_UINT8 CAN_MSG_DLC;
MX_UINT8 CAN_MSG_DATA[8];
MX_UINT8 MsgFlags = 0;

#ifdef CAN_USE_EXID
  MX_UINT8 CAN_MSG_ID[4];
#else
  MX_UINT8 CAN_MSG_ID[2];
#endif

#define BF_MASK 1


/********************************************************************
 * FUNCTIONS
 ********************************************************************/

//internal function implementations
void SPI_Init()
{
	//initialise spi
	set_bit(MX_CAN_TRIS,MX_SPI_SDI);
	clear_bit(MX_CAN_SDO_TRIS,MX_SPI_SDO);
	clear_bit(MX_CAN_TRIS,MX_SPI_SCK);
	clear_bit(MX_CAN_CS_TRIS,CAN_CHIPSEL);
	set_bit(MX_CAN_INT_TRIS,CAN_INTERRUPT);

	//disable the CAN chip select line
	set_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	SSPSTAT = 0;
	st_bit(SSPSTAT, CKE);			//SMP = 0, CKE = 1

	SSPCON1 = 0;
	st_bit(SSPCON1, SSPEN);
}


MX_UINT8 SPI_SendByte(MX_UINT8 byte)
{
	MX_UINT8 retval;
	// dummy read
	retval = SSPBUF;
	//send the byte
	SSPBUF = byte;
	//wait until data has been received (transmit complete)
	while ((SSPSTAT & BF_MASK) == 0);
	//get received byte
	retval = SSPBUF;
	return retval;
}


MX_UINT8 CAN_MaskFromBit(MX_UINT8 which_bit)
{
	MX_UINT8 retVal = 0;
	switch (which_bit)
	{
		case 0:
			retVal = 0x01;
			break;

		case 1:
			retVal = 0x02;
			break;

		case 2:
			retVal = 0x04;
			break;

		case 3:
			retVal = 0x08;
			break;

		case 4:
			retVal = 0x10;
			break;

		case 5:
			retVal = 0x20;
			break;

		case 6:
			retVal = 0x40;
			break;

		case 7:
			retVal = 0x80;
			break;
	}
	return (retVal);
}


void CAN_Reset()
{
	//enable SPI
	clear_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	SPI_SendByte(CAN_RESET);

	//disable SPI
	set_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	//wait for the CAN device to complete its OST
	delay_us(20);
}


void CAN_Write(MX_UINT8 addr, MX_UINT8 data)
{
	//enable SPI
	clear_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	SPI_SendByte(CAN_WRITE);			//send a byte
	SPI_SendByte(addr);					//send the address
	SPI_SendByte(data);					//send the data

	//disable SPI
	set_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);
}


MX_UINT8 CAN_Read(MX_UINT8 addr)
{
	MX_UINT8 data;

	//enable SPI
	clear_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	SPI_SendByte(CAN_READ);				//read a byte
	SPI_SendByte(addr);					//send the address
	data = SPI_SendByte(0x5A);			//send a don't care byte

	//disable SPI
	set_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	return (data);
}


void CAN_Config(MX_UINT8 cfg)
{
	MX_UINT8 mode;
	MX_UINT8 done = 0;

	while (done == 0)
	{
		CAN_Write(CANCTRL, cfg);

		Wdt_Delay_Ms(1);				//not sure if this is needed

		//read the config mode back
		mode = CAN_Read(MX_CANSTAT);

		//mask off the config bits
		mode = mode & 0xE0;

		if (mode == cfg)
		{
			//it has been set correctly
			done = 1;
		}
	}

	Wdt_Delay_Ms(1);				//not sure if this is needed
}


MX_UINT8 CAN_ReadStatus()
{
	MX_UINT8 retval = 0;

	//enable SPI
	clear_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	SPI_SendByte(CAN_RD_STATUS);		//read the status
	retval = SPI_SendByte(0x5A);		//send a don't care byte

	//disable SPI
	set_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	return (retval);
}


MX_UINT8 CAN_ReadRXStatus()
{
	MX_UINT8 retval = 0;

	//enable SPI
	clear_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	SPI_SendByte(CAN_RX_STATUS);		//read the status
	retval = SPI_SendByte(0x5A);		//send a don't care byte

	//disable SPI
	set_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	return (retval);
}


void CAN_BitModify(MX_UINT8 addr, MX_UINT8 mask, MX_UINT8 data)
{
	//enable SPI
	clear_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	SPI_SendByte(CAN_BIT_MODIFY);		//bit modify
	SPI_SendByte(addr);					//send the address
	SPI_SendByte(mask);					//send the mask
	SPI_SendByte(data);					//send the data

	//disable SPI
	set_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);
}


MX_UINT8 CAN_ReadRX_ID_and_Data(MX_UINT8 buffer)
{
	//populates CAN_MSG_ID[], CAN_MSG_DLC, and CAN_MSG_DATA[], and returns CAN_MSG_DLC
	MX_UINT8 idx = 0;

	if (buffer > CAN_MAX_RX_BUF)
	{
		return (0);
	}

	//enable SPI
	clear_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	SPI_SendByte(CAN_RD_RXBUF_ID(buffer));		//read the RX ID

	CAN_MSG_ID[idx++] = SPI_SendByte(0x5A);		//read back SIDH

	CAN_MSG_ID[idx++] = SPI_SendByte(0x5A);		//read back SIDL

	SSPBUF = 0x5A;						//send a don't care byte
	while ((SSPSTAT & BF_MASK) == 0);	//wait until data has been received (transmit complete)
  #ifdef CAN_USE_EXID
	CAN_MSG_ID[idx++] = SSPBUF;			//read back EXID8
  #endif

	SSPBUF = 0x5A;						//send a don't care byte
	while ((SSPSTAT & BF_MASK) == 0);	//wait until data has been received (transmit complete)
  #ifdef CAN_USE_EXID
	CAN_MSG_ID[idx++] = SSPBUF;			//read back EXID0
  #endif

	CAN_MSG_DLC = SPI_SendByte(0x5A);			//read back DLC

	//now read the data (if there is any)
	if (CAN_MSG_DLC > 0)
	{
		CAN_MSG_DATA[0] = SPI_SendByte(0x5A);		//read back D0

		if (CAN_MSG_DLC > 1)
		{
			CAN_MSG_DATA[1] = SPI_SendByte(0x5A);			//read back D1

			if (CAN_MSG_DLC > 2)
			{
				CAN_MSG_DATA[2] = SPI_SendByte(0x5A);			//read back D2

				if (CAN_MSG_DLC > 3)
				{
					CAN_MSG_DATA[3] = SPI_SendByte(0x5A);			//read back D3

					if (CAN_MSG_DLC > 4)
					{
						CAN_MSG_DATA[4] = SPI_SendByte(0x5A);			//read back D4

						if (CAN_MSG_DLC > 5)
						{
							CAN_MSG_DATA[5] = SPI_SendByte(0x5A);			//read back D5

							if (CAN_MSG_DLC > 6)
							{
								CAN_MSG_DATA[6] = SPI_SendByte(0x5A);			//read back D6

								if (CAN_MSG_DLC > 7)
								{
									CAN_MSG_DATA[7] = SPI_SendByte(0x5A);			//read back D7
								}
							}
						}
					}
				}
			}
		}
	}

	//disable SPI
	set_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	return (CAN_MSG_DLC);
}


void CAN_Init()
{
	//Init SPI
	SPI_Init();

	//brief pause here
	Wdt_Delay_Ms(50);

	//Reset the CAN device
	CAN_Reset();

	//Put the CAN device into config mode
	CAN_Config(REQOP_CONFIG);

	//Initialise all the CAN device registers
	//enable SPI
	clear_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	SPI_SendByte(CAN_WRITE);        //CAN write mode
	SPI_SendByte(0x00);             //start writting at address 0x00

	SPI_SendByte(RXF0SIDH_VAL);     // RXF0SIDH  0x00
	SPI_SendByte(RXF0SIDL_VAL);     // RXF0SIDL  0x01
	SPI_SendByte(RXF0EID8_VAL);     // RXF0EID8  0x02
	SPI_SendByte(RXF0EID0_VAL);     // RXF0EID0  0x03
	SPI_SendByte(RXF1SIDH_VAL);     // RXF1SIDH  0x04
	SPI_SendByte(RXF1SIDL_VAL);     // RXF1SIDL  0x05
	SPI_SendByte(RXF1EID8_VAL);     // RXF1EID8  0x06
	SPI_SendByte(RXF1EID0_VAL);     // RXF1EID0  0x07
	SPI_SendByte(RXF2SIDH_VAL);     // RXF2SIDH  0x08
	SPI_SendByte(RXF2SIDL_VAL);     // RXF2SIDL  0x09
	SPI_SendByte(RXF2EID8_VAL);     // RXF2EID8  0x0A
	SPI_SendByte(RXF2EID0_VAL);     // RXF2EID0  0x0B
	SPI_SendByte(BFPCTRL_VAL);      // BFPCTRL   0x0C
	SPI_SendByte(TXRTSCTRL_VAL);    // TXRTSCTRL 0x0D
	SPI_SendByte(MX_CANSTAT_VAL);   // MX_CANSTAT   0x0E
	SPI_SendByte(CANCTRL_VAL);      // CANCTRL   0x0F

	SPI_SendByte(RXF3SIDH_VAL);     // RXF3SIDH  0x10
	SPI_SendByte(RXF3SIDL_VAL);     // RXF3SIDL  0x11
	SPI_SendByte(RXF3EID8_VAL);     // RXF3EID8  0x12
	SPI_SendByte(RXF3EID0_VAL);     // RXF3EID0  0x13
	SPI_SendByte(RXF4SIDH_VAL);     // RXF4SIDH  0x14
	SPI_SendByte(RXF4SIDL_VAL);     // RXF4SIDL  0x15
	SPI_SendByte(RXF4EID8_VAL);     // RXF4EID8  0x16
	SPI_SendByte(RXF4EID0_VAL);     // RXF4EID0  0x17
	SPI_SendByte(RXF5SIDH_VAL);     // RXF5SIDH  0x18
	SPI_SendByte(RXF5SIDL_VAL);     // RXF5SIDL  0x19
	SPI_SendByte(RXF5EID8_VAL);     // RXF5EID8  0x1A
	SPI_SendByte(RXF5EID0_VAL);     // RXF5EID0  0x1B
	SPI_SendByte(0x00);             // TEC       0x1C
	SPI_SendByte(0x00);             // REC       0x1D
	SPI_SendByte(MX_CANSTAT_VAL);   // MX_CANSTAT   0x1E
	SPI_SendByte(CANCTRL_VAL);      // CANCTRL   0x1F

	SPI_SendByte(RXM0SIDH_VAL);     // RXM0SIDH  0x20
	SPI_SendByte(RXM0SIDL_VAL);     // RXM0SIDL  0x21
	SPI_SendByte(RXM0EID8_VAL);     // RXM0EID8  0x22
	SPI_SendByte(RXM0EID0_VAL);     // RXM0EID0  0x23
	SPI_SendByte(RXM1SIDH_VAL);     // RXM1SIDH  0x20
	SPI_SendByte(RXM1SIDL_VAL);     // RXM1SIDL  0x21
	SPI_SendByte(RXM1EID8_VAL);     // RXM1EID8  0x26
	SPI_SendByte(RXM1EID0_VAL);     // RXM1EID0  0x27
	SPI_SendByte(CNF3_VAL);         // CNF3      0x28
	SPI_SendByte(CNF2_VAL);         // CNF2      0x29
	SPI_SendByte(CNF1_VAL);         // CNF1      0x2A
	SPI_SendByte(CANINTE_VAL);      // CANINTE   0x2B
	SPI_SendByte(0x00);             // CANINTF   0x2C
	SPI_SendByte(0x00);             // EFLG      0x2D
	SPI_SendByte(MX_CANSTAT_VAL);   // MX_CANSTAT   0x2E
	SPI_SendByte(CANCTRL_VAL);      // CANCTRL   0x2F

	SPI_SendByte(TXB0CTRL_VAL);     // TXB0CTRL  0x30
	SPI_SendByte(TXB0SIDH_VAL);     // TXB0SIDH  0x31
	SPI_SendByte(TXB0SIDL_VAL);     // TXB0SIDL  0x32
	SPI_SendByte(TXB0EID8_VAL);     // TXB0EID8  0x33
	SPI_SendByte(TXB0EID0_VAL);     // TXB0EID0  0x34
	SPI_SendByte(TXB0DLC_VAL);      // TXB0DLC   0x35
	SPI_SendByte(TXB0DB0_VAL);      // TXB0DB0   0x36
	SPI_SendByte(TXB0DB1_VAL);      // TXB0DB1   0x37
	SPI_SendByte(TXB0DB2_VAL);      // TXB0DB2   0x38
	SPI_SendByte(TXB0DB3_VAL);      // TXB0DB3   0x39
	SPI_SendByte(TXB0DB4_VAL);      // TXB0DB4   0x3A
	SPI_SendByte(TXB0DB5_VAL);      // TXB0DB5   0x3B
	SPI_SendByte(TXB0DB6_VAL);      // TXB0DB6   0x3C
	SPI_SendByte(TXB0DB7_VAL);      // TXB0DB7   0x3D
	SPI_SendByte(MX_CANSTAT_VAL);   // MX_CANSTAT   0x3E
	SPI_SendByte(CANCTRL_VAL);      // CANCTRL   0x3F

	SPI_SendByte(TXB1CTRL_VAL);     // TXB1CTRL  0x40 Highest priority
	SPI_SendByte(TXB1SIDH_VAL);     // TXB1SIDH  0x41
	SPI_SendByte(TXB1SIDL_VAL);     // TXB1SIDL  0x42
	SPI_SendByte(TXB1EID8_VAL);     // TXB1EID8  0x43
	SPI_SendByte(TXB1EID0_VAL);     // TXB1EID0  0x44
	SPI_SendByte(TXB1DLC_VAL);      // TXB1DLC   0x45
	SPI_SendByte(TXB1DB0_VAL);      // TXB1DB0   0x46
	SPI_SendByte(TXB1DB1_VAL);      // TXB1DB1   0x47
	SPI_SendByte(TXB1DB2_VAL);      // TXB1DB2   0x48
	SPI_SendByte(TXB1DB3_VAL);      // TXB1DB3   0x49
	SPI_SendByte(TXB1DB4_VAL);      // TXB1DB4   0x4A
	SPI_SendByte(TXB1DB5_VAL);      // TXB1DB5   0x4B
	SPI_SendByte(TXB1DB6_VAL);      // TXB1DB6   0x4C
	SPI_SendByte(TXB1DB7_VAL);      // TXB1DB7   0x4D
	SPI_SendByte(MX_CANSTAT_VAL);   // MX_CANSTAT   0x4E
	SPI_SendByte(CANCTRL_VAL);      // CANCTRL   0x4F

	SPI_SendByte(TXB2CTRL_VAL);     // TXB2CTRL  0x50
	SPI_SendByte(TXB2SIDH_VAL);     // TXB2SIDH  0x51
	SPI_SendByte(TXB2SIDL_VAL);     // TXB2SIDL  0x52
	SPI_SendByte(TXB2EID8_VAL);     // TXB2EID8  0x53
	SPI_SendByte(TXB2EID0_VAL);     // TXB2EID0  0x54
	SPI_SendByte(TXB2DLC_VAL);      // TXB2DLC   0x55
	SPI_SendByte(TXB2DB0_VAL);      // TXB2DB0   0x56
	SPI_SendByte(TXB2DB1_VAL);      // TXB2DB1   0x57
	SPI_SendByte(TXB2DB2_VAL);      // TXB2DB2   0x58
	SPI_SendByte(TXB2DB3_VAL);      // TXB2DB3   0x59
	SPI_SendByte(TXB2DB4_VAL);      // TXB2DB4   0x5A
	SPI_SendByte(TXB2DB5_VAL);      // TXB2DB5   0x5B
	SPI_SendByte(TXB2DB6_VAL);      // TXB2DB6   0x5C
	SPI_SendByte(TXB2DB7_VAL);      // TXB2DB7   0x5D
	SPI_SendByte(MX_CANSTAT_VAL);   // MX_CANSTAT   0x5E
	SPI_SendByte(CANCTRL_VAL);      // CANCTRL   0x5F

	SPI_SendByte(RXB0CTRL_VAL);     // RXB0CTRL  0x60
	SPI_SendByte(0x00);             // RXB0SIDH  0x61
	SPI_SendByte(0x00);             // RXB0SIDL  0x62
	SPI_SendByte(0x00);             // RXB0EID8  0x63
	SPI_SendByte(0x00);             // RXB0EID0  0x64
	SPI_SendByte(0x00);             // RXB0DLC   0x65
	SPI_SendByte(0x00);             // RXB0DB0   0x66
	SPI_SendByte(0x00);             // RXB0DB1   0x67
	SPI_SendByte(0x00);             // RXB0DB2   0x68
	SPI_SendByte(0x00);             // RXB0DB3   0x69
	SPI_SendByte(0x00);             // RXB0DB4   0x6A
	SPI_SendByte(0x00);             // RXB0DB5   0x6B
	SPI_SendByte(0x00);             // RXB0DB6   0x6C
	SPI_SendByte(0x00);             // RXB0DB7   0x6D
	SPI_SendByte(MX_CANSTAT_VAL);   // MX_CANSTAT   0x6E
	SPI_SendByte(CANCTRL_VAL);      // CANCTRL   0x6F

	SPI_SendByte(RXB1CTRL_VAL);     // RXB1CTRL  0x70
	SPI_SendByte(0x00);             // RXB1SIDH  0x71
	SPI_SendByte(0x00);             // RXB1SIDL  0x72
	SPI_SendByte(0x00);             // RXB1EID8  0x73
	SPI_SendByte(0x00);             // RXB1EID0  0x74
	SPI_SendByte(0x00);             // RXB1DLC   0x75
	SPI_SendByte(0x00);             // RXB1DB0   0x76
	SPI_SendByte(0x00);             // RXB1DB1   0x77
	SPI_SendByte(0x00);             // RXB1DB2   0x78
	SPI_SendByte(0x00);             // RXB1DB3   0x79
	SPI_SendByte(0x00);             // RXB1DB4   0x7A
	SPI_SendByte(0x00);             // RXB1DB5   0x7B
	SPI_SendByte(0x00);             // RXB1DB6   0x7C
	SPI_SendByte(0x00);             // RXB1DB7   0x7D
	SPI_SendByte(MX_CANSTAT_VAL);   // MX_CANSTAT   0x7E
	SPI_SendByte(CANCTRL_VAL);      // CANCTRL   0x7F

	//disable SPI
	set_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	//Put the CAN device into normal mode
	CAN_Config(REQOP_NORMAL);

}


void CAN_SendBuffer(MX_UINT8 buffer)
{
	if (buffer > CAN_MAX_TX_BUF)
	{
	   return;
	}

	MX_UINT8 cmd = CAN_RTS;         //default value

	switch (buffer)
	{
	   case 0:
		   cmd = CAN_RTS_TXB0;
		   break;

	   case 1:
		   cmd = CAN_RTS_TXB1;
		   break;

	   case 2:
		   cmd = CAN_RTS_TXB2;
		   break;
	}
	//NOTE: this following didn't work:
	//cmd = CAN_RTS_TXB(buffer);

	//enable SPI
	clear_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	SPI_SendByte(cmd);

	//disable SPI
	set_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);
}


MX_UINT8 CAN_CheckRx(MX_UINT8 buffer)
{
	//returns 1 if the buffer is full, 0 otherwise
	MX_UINT8 rx_status;
	MX_UINT8 status_mask;
	MX_UINT8 retval = 0;

	if (buffer > CAN_MAX_RX_BUF)
	{
	   return (0);
	}


	if (buffer == 1)
	{
	   //status_mask = 0x02;       //if using CAN_ReadStatus
	   status_mask = 0x80;         //if using CAN_ReadRXStatus
	} else {
	   //status_mask = 0x01;       //if using CAN_ReadStatus
	   status_mask = 0x40;         //if using CAN_ReadRXStatus
	}

	//rx_status = CAN_ReadStatus();    //if using CAN_ReadStatus
	rx_status = CAN_ReadRXStatus();    //if using CAN_ReadRXStatus

	if ((rx_status & status_mask) != 0)
	{
	   retval = 1;

	   //now read in the id and data info
	   CAN_ReadRX_ID_and_Data(buffer);
	}

	return (retval);
}


MX_UINT8 CAN_GetRxDataCount(MX_UINT8 buffer)
{
	return (CAN_MSG_DLC);
}


MX_UINT8 CAN_GetRxData(MX_UINT8 buffer, MX_UINT8 index)
{
	if (index > 7)
	{
	   return (0);
	}
	return (CAN_MSG_DATA[index]);
}


void CAN_SetTxData(MX_UINT8 buffer, MX_UINT8 data_cnt, MX_UINT8 d0, MX_UINT8 d1, MX_UINT8 d2, MX_UINT8 d3, MX_UINT8 d4, MX_UINT8 d5, MX_UINT8 d6, MX_UINT8 d7)
{
	// Code_CAN_SetTxData
	if (buffer > CAN_MAX_TX_BUF)
	{
	   return;
	}

	if (data_cnt > 8)
	{
	   return;
	}

	MX_UINT8 i;
	MX_UINT8 dlc_addr = TXBxDLC(buffer);

	//enable SPI
	clear_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	SPI_SendByte(CAN_WRITE);        //CAN write mode
	SPI_SendByte(dlc_addr);         //start writting at address 0x00
	SPI_SendByte(data_cnt);         //send the DLC value

	//now fill the data bytes...
	if (data_cnt > 0)
	{
	   SPI_SendByte(d0);
	   if (data_cnt > 1)
	   {
		   SPI_SendByte(d1);
		   if (data_cnt > 2)
		   {
			   SPI_SendByte(d2);
			   if (data_cnt > 3)
			   {
				   SPI_SendByte(d3);
				   if (data_cnt > 4)
				   {
					   SPI_SendByte(d4);
					   if (data_cnt > 5)
					   {
						   SPI_SendByte(d5);
						   if (data_cnt > 6)
						   {
							   SPI_SendByte(d6);
							   if (data_cnt > 7)
							   {
								   SPI_SendByte(d7);
							   }
						   }
					   }
				   }
			   }
		   }
	   }
	}

	//disable SPI
	set_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);
}


void CAN_SetTxID(MX_UINT8 buffer, MX_UINT16 ID)
{
	// Code_SetTxID
	if (buffer > CAN_MAX_TX_BUF)
	{
	   return;
	}

	MX_UINT8 ID_L;
	MX_UINT8 id_addr = TXBxSIDH(buffer);

	ID_L = ID;						//Store low byte of ID
	ID >>= 8;						//Shift ID high byte to low byte

	//enable SPI
	clear_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	SPI_SendByte(CAN_WRITE);        //CAN write mode
	SPI_SendByte(id_addr);          //start writting at hi id address
	SPI_SendByte(ID);               //send the Hi ID value
	SPI_SendByte(ID_L);               //send the Lo ID value

	//disable SPI
	set_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);
}


MX_UINT8 CAN_GetRxIDLo(MX_UINT8 buffer)
{
	return (CAN_MSG_ID[1]);
}


MX_UINT8 CAN_GetRxIDHi(MX_UINT8 buffer)
{
	return (CAN_MSG_ID[0]);
}


void CAN_CancelTx(MX_UINT8 buffer)
{
	if (buffer <= 2)
	{
		CAN_BitModify(TXBxCTRL(buffer), MX_TXREQ_SEND, 0x00);
	}
}


void CAN_SetFilter (MX_UINT16 ID)
{
	MX_UINT8 ID_L;

	// Split ID into bytes
	ID_L = ID;
	ID = ID >> 8;

	//Put the CAN device into config mode
	CAN_Config(REQOP_CONFIG);

	//enable SPI
	clear_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	SPI_SendByte(CAN_WRITE);       	//CAN write mode
	SPI_SendByte(0x00);				//start writting at address 0x00 (RXF0SIDH)

	SPI_SendByte(ID);     			// RXF0SIDH  0x00
	SPI_SendByte(ID_L);				// RXF0SIDL  0x01

	//disable SPI
	set_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	//Put the CAN device into normal mode
	CAN_Config(REQOP_NORMAL);
}

void CAN_SetCNF1(MX_UINT8 VALUE)
{
	//Put the CAN device into config mode
	CAN_Config(REQOP_CONFIG);

	//enable SPI
	clear_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	SPI_SendByte(CAN_WRITE);       	//CAN write mode
	SPI_SendByte(0x2A);				//start writting at address 0x2A CNF1
	SPI_SendByte(VALUE);
	
	//disable SPI
	set_bit(MX_CAN_CS_PORT, CAN_CHIPSEL);

	//Put the CAN device into normal mode
	CAN_Config(REQOP_NORMAL);
}


void MIAC_Module_WR(MX_UINT16 CAN_ID, MX_UINT16 CMD_ID, MX_UINT8 Count, MX_UINT8 Start, MX_UINT8 More)
{
// CAN_ID parameters of the MIAC_Module_xxx functions are now the un-shifted versions <10:0>
	MX_UINT8 Cmd_L;
	
	Cmd_L = CMD_ID;
	CMD_ID >>= 8;
	CMD_ID &= 0x07;

	if (Start) CMD_ID |= 0x08;
	if (More) CMD_ID |= 0x10;

	if (Count > 6)
		Count = 8;
	else
		Count += 2;

	CAN_SetTxID(0, CAN_ID << 5);
	CAN_SetTxData(0,Count,CMD_ID,Cmd_L,MIAC_CAN_TX[0],MIAC_CAN_TX[1],MIAC_CAN_TX[2],MIAC_CAN_TX[3],MIAC_CAN_TX[4],MIAC_CAN_TX[5]);
	CAN_SendBuffer(0);
	MIAC_CAN_TX_COUNT = 0;
}


MX_UINT8 MIAC_Module_RD(MX_UINT16 CAN_ID, MX_UINT16 CMD_ID)
{
// nb. CAN_ID no longer used, replies come to MIAC_CAN_ID
	MX_UINT16 Rx_ID;
	MX_UINT8 MsgRx, MsgFlags;
	MX_UINT8 DataCount;
	MX_UINT8 Idx;
	MX_UINT8 RetVal = 0xe0;

	if(CAN_CheckRx(0))		//Message received?
	{
		Rx_ID = (CAN_GetRxIDHi(0) << 8) | CAN_GetRxIDLo(0);		//Get CAN ID

		if(Rx_ID == (MIAC_CAN_ID << 5))		//Expected CAN ID?
		{
			DataCount = CAN_GetRxDataCount(0);

			if(DataCount > 1)		//Minimum of 2 data bytes?
			{
				MsgFlags = CAN_GetRxData(0,0);		//Read msb of message ID

				Rx_ID = ((MsgFlags & 0x07) << 8) | CAN_GetRxData(0,1);		//Make message ID

				MsgFlags = MsgFlags & 0x18;		//Mask out message flags

				if(Rx_ID == CMD_ID)		//Expected message ID?
				{
					for(Idx = 2; Idx < DataCount; Idx++)		//Read data
					{
						MIAC_CAN_RX[Idx - 2] = CAN_GetRxData(0,Idx);
					}
					RetVal = (DataCount - 2) | MsgFlags;
				}else{
					RetVal = 0x80;		//Unexpected message ID
				}
			}else{
				RetVal = 0xa0;		//Insufficient data
			}
		}else{
			RetVal = 0xc0;		//Unexpected CAN ID
		}
	}
	return(RetVal);		//Return 0xe0 if no message received
}


MX_UINT8 MIAC_Module_GetAck(MX_UINT16 CAN_ID, MX_UINT16 CMD_ID, MX_UINT16 TimeOut)
{
	MX_UINT8 MsgAck;
	do
	{
		MsgAck = MIAC_Module_RD(CAN_ID, CMD_ID);

		if(MsgAck == 0xe0)
			delay_us(200);	// delay_10us(20);

		if(TimeOut != 0xffff)		//Wait indefinitely
			TimeOut = TimeOut - 1;
	}
	while(((MsgAck & 0xe0) == 0xe0) && (TimeOut));

	return(MsgAck);
}

void MIAC_Module_PushData(MX_UINT8 Data)
{
	MIAC_CAN_TX[MIAC_CAN_TX_COUNT++] = Data;
}

void MIAC_Module_SetData(MX_UINT8 COUNT, MX_UINT8 D0, MX_UINT8 D1, MX_UINT8 D2, MX_UINT8 D3, MX_UINT8 D4, MX_UINT8 D5)
{
	MIAC_CAN_TX_COUNT = COUNT;
	MIAC_CAN_TX[0] = D0;
	MIAC_CAN_TX[1] = D1;
	MIAC_CAN_TX[2] = D2;
	MIAC_CAN_TX[3] = D3;
	MIAC_CAN_TX[4] = D4;
	MIAC_CAN_TX[5] = D5;
}

MX_UINT8 MIAC_Module_GetData(MX_UINT8 Index)
{
	return MIAC_CAN_RX[Index];
}

/* Write to the module and get the Ack */
MX_UINT8 MIAC_Module_Message(MX_UINT16 CAN_ID, MX_UINT16 CMD_ID)
{
	MX_UINT8 Cmd_H;
	MX_UINT8 Cmd_L;
	MX_UINT8 MsgAck;
	MX_UINT8 TimeOut = 200;
	MX_UINT8 Count = MIAC_CAN_TX_COUNT;
	
	Cmd_L = CMD_ID;
	Cmd_H = (CMD_ID >> 8) & 7;
	Cmd_H |= 0x08; 	// Start, no More

	if (Count > 6)
		Count = 8;
	else
		Count += 2;

	CAN_SetTxID(0, CAN_ID << 5);
	CAN_SetTxData(0,Count,Cmd_H,Cmd_L,MIAC_CAN_TX[0],MIAC_CAN_TX[1],MIAC_CAN_TX[2],MIAC_CAN_TX[3],MIAC_CAN_TX[4],MIAC_CAN_TX[5]);
	CAN_SendBuffer(0);
	MIAC_CAN_TX_COUNT = 0;
	
	do
	{
		MsgAck = MIAC_Module_RD(CAN_ID, CMD_ID);
		if(MsgAck == 0xe0)
			delay_us(200);	// delay_10us(20);
		TimeOut = TimeOut - 1;
	}
	while(((MsgAck & 0xe0) == 0xe0) && (TimeOut));

	return((MsgAck & 0xe0)?0:1);
}


void MIAC_Module_Init(MX_UINT16 CAN_ID)
{
	// Common function for forcing software reset on Expansion Module, Command 132
	// The Expansion module will perform an immediate software reset, 
	// so we do not expect a reply
	// and the module will be out of action for up to 10mS
	MIAC_Module_WR(CAN_ID, 132, 0, 1, 0);
	CAN_CheckRx(0);
	delay_ms(10);
}

MX_UINT8 MIAC_Module_Factory_Settings(MX_UINT16 CAN_ID)
{
	// Common function for forcing factory defaults on Expansion Module, Command 135 
	// CAN parameters (in EEPROM) will revert to factory settings.
	// NB. The new values will not be actioned until a power cycle or software reset,
	// hence the ack reply will be at the current settings
	MIAC_Module_WR(CAN_ID, 135, 0, 1, 0);
	// returns zero if ack received
	return MIAC_Module_GetAck(CAN_ID, 135, 200) & 0xe0;
}

MX_UINT8 MIAC_Module_Custom_Settings(MX_UINT16 OLD_CAN_ID, MX_UINT16 NEW_CAN_ID, MX_UINT16 NEW_REPLY_ID, MX_UINT16 NEW_RATE)
{
	// Common function for setting custom CAN parameters on Expansion Module, Command 134 
	// The values will be stored in the Module EEPROM
	// NB. The new values will not be actioned until a power cycle or software reset,
	// hence the ack reply will be at the current settings.

	MX_UINT16 CAN_CFG1;
	MX_UINT16 CAN_CFG2;
	MX_UINT8 n;
	MX_UINT8 Ack;
	
	if (NEW_RATE >= 1000)
	{
		// set nominal bit rate to 1000Kbs
		CAN_CFG1 = 0;		// BRP=0
		CAN_CFG2 = 0x01c8;	// SYNC=1, PS=1, PS1=2, PS2=2
	}
	else if (NEW_RATE >= 500)
	{
		// set nominal bit rate to 500Kbs
		CAN_CFG1 = 0;		// BRP=0
		CAN_CFG2 = 0x03e8;	// SYNC=1, PS=1, PS1=6, PS2=4
	}
	else if (NEW_RATE >= 250)
	{
		// set nominal bit rate to 250Kbs
		CAN_CFG1 = 1;		// BRP=1
		CAN_CFG2 = 0x03e8;	// SYNC=1, PS=1, PS1=6, PS2=4
	}
	else
	{
		// set nominal bit rate to 125Kbs
		CAN_CFG1 = 3;		// BRP=3
		CAN_CFG2 = 0x03e8;	// SYNC=1, PS=1, PS1=6, PS2=4
	}
	
	// seems that we need to hit the EEPROM a few times
	for (n=0;n<3;++n)
	{
		MIAC_CAN_TX[0] = NEW_CAN_ID >> 8;
		MIAC_CAN_TX[1] = NEW_CAN_ID;
		MIAC_CAN_TX[2] = NEW_REPLY_ID >> 8;
		MIAC_CAN_TX[3] = NEW_REPLY_ID;
		MIAC_CAN_TX[4] = CAN_CFG2 >> 8;
		MIAC_CAN_TX[5] = CAN_CFG2;
		MIAC_Module_WR(OLD_CAN_ID, 134, 6, 1, 1);
		MIAC_Module_GetAck(OLD_CAN_ID, 134, 200);

		MIAC_CAN_TX[0] = CAN_CFG1 >> 8;
		MIAC_CAN_TX[1] = CAN_CFG1;
		MIAC_Module_WR(OLD_CAN_ID, 134, 2, 0, 0);
		Ack = MIAC_Module_GetAck(OLD_CAN_ID, 134, 200) & 0xe0;
	}
	// returns zero if ack received
	return Ack;
}

// Duplicate MIAC I/O functions. Used by MIAC System when LED, Switch, and ADC components are used with the MIAC Master

void MIAC_Master_RelayON(MX_UINT8 RelayID)
{
	if(RelayID && (RelayID < 5))
	{
		clear_bit(trisb, RelayID + 3);
		set_bit(portb, RelayID + 3);
	}
}

void MIAC_Master_RelayOFF(MX_UINT8 RelayID)
{
	if(RelayID && (RelayID < 5))
	{
		clear_bit(trisb, RelayID + 3);
		clear_bit(portb, RelayID + 3);
	}
}

void MIAC_Master_OutputON(MX_UINT8 TransID)
{
	if(TransID && (TransID < 5))
	{
		switch(TransID)
		{
			case(1):	trisc &= ~0x04;
						portc |= 0x04;
						break;
			case(2):	trisc &= ~0x01;
						portc |= 0x01;
						break;
			case(3):	trisc &= ~0x02;
						portc |= 0x02;
						break;
			case(4):	trisc &= ~0x40;
						portc |= 0x40;
						break;
		}
	}
}


void MIAC_Master_OutputOFF(MX_UINT8 TransID)
{
	if(TransID && (TransID < 5))
	{
		switch(TransID)
		{
			case(1):	trisc &= ~0x04;
						portc &= ~0x04;
						break;
			case(2):	trisc &= ~0x01;
						portc &= ~0x01;
						break;
			case(3):	trisc &= ~0x02;
						portc &= ~0x02;
						break;
			case(4):	trisc &= ~0x40;
						portc &= ~0x40;
						break;
		}
	}
}

MX_UINT8 MIAC_Master_InputDIGITAL(MX_UINT8 InputID)
{
	MX_UINT8 RetVal = 255;

	if(InputID && (InputID < 9))
	{
		switch(InputID)
		{
			case(1):	trisa |= 0x01;
						RetVal = ((porta & 0x01) == 0x01);
						break;
			case(2):	trisa |= 0x02;
						RetVal = ((porta & 0x02) == 0x02);
						break;
			case(3):	trisa |= 0x04;
						RetVal = ((porta & 0x04) == 0x04);
						break;
			case(4):	trisa |= 0x08;
						RetVal = ((porta & 0x08) == 0x08);
						break;
			case(5):	trise |= 0x01;
						RetVal = ((porte & 0x01) == 0x01);
						break;
			case(6):	trise |= 0x02;
						RetVal = ((porte & 0x02) == 0x02);
						break;
			case(7):	trise |= 0x04;
						RetVal = ((porte & 0x04) == 0x04);
						break;
			case(8):	trisb |= 0x04;
						RetVal = ((portb & 0x04) == 0x04);
						break;
		}
	}
	return(RetVal);
}

MX_UINT8 MIAC_Master_InputANA(MX_UINT8 InputID)
{
	#define MIAC_MASTER_ADC_SAMP_TIME 40

	//set up ADC conversion
	MX_UINT8 old_tris, cnt, tris_mask, chan_id;

	if(InputID && (InputID < 9))
	{
		chan_id = InputID;
		if (InputID >= 5) chan_id++;

		ADCON2 = 0x03;
		ADCON1 = 15 - chan_id;

		//store old tris value, and set the i/o pin as an input
		switch (InputID)
		{
			case(1):	old_tris = trisa;
						trisa |= 0x01;
						break;
			case(2):	old_tris = trisa;
						trisa |= 0x02;
						break;
			case(3):	old_tris = trisa;
						trisa |= 0x04;
						break;
			case(4):	old_tris = trisa;
						trisa |= 0x08;
						break;
			case(5):	old_tris = trise;
						trise |= 0x01;
						break;
			case(6):	old_tris = trise;
						trise |= 0x02;
						break;
			case(7):	old_tris = trise;
						trise |= 0x04;
						break;
			case(8):	old_tris = trisb;
						trisb |= 0x04;
						break;
		}

		//turn ADC on
		ADCON0 = 0x01 | ((chan_id - 1) << 2);

		//wait the acquisition time
		cnt = 0;
		while (cnt < MIAC_MASTER_ADC_SAMP_TIME) cnt++;

		//begin conversion and wait until it has finished
		ADCON0 = ADCON0 | 0x02;
		while (ADCON0 & 0x02);

		//restore old tris value, and reset adc registers
		if(InputID == 8)
		{
			trisb = old_tris;
		}
		else
		{
			if(InputID < 5)
			{
				trisa = old_tris;
			}
			else
			{
				trise = old_tris;
			}
		}
		ADCON1 = 0x0f;
		ADCON0 = 0x00;
	}

	return(ADRESH);
}

MX_UINT16 MIAC_Master_InputANA10(MX_UINT8 InputID)
{
	MX_UINT16 result;

	result = MIAC_Master_InputANA(InputID);
	result = result << 2;
	result = result | (ADRESL >> 6);

	return(result);
}

/****************************************
*            MIAC System Code           *
****************************************/
// MIAC System Master reply CAN ID can be customized here, MIAC System default is 240 (0xf0)
// For example, to set the MIAC Master CAN ID to 100 (0x64) uncomment the following line
// #define MX_MASTER_CAN_ID (100)

// MIAC System CAN Bit Rate can be customized here, MIAC System default is 500Kbs
// This can be changed to 125, 250 or 1000
// For example, to set the rate to 125Kbs uncomment the following line
// #define MX_MASTER_BIT_RATE (125)

#ifndef MX_MASTER_CAN_ID
  #define MX_MASTER_CAN_ID (0x0f0)
#endif

#ifdef MX_MIAC_SYSTEM
void MIAC_System_Setup()
{
	// Setup the receive CAN filter for the replies to the Master MIAC
	MIAC_CAN_ID = MX_MASTER_CAN_ID;
	CAN_Init();
	CAN_SetFilter(MIAC_CAN_ID << 5);
#if (MX_MASTER_BIT_RATE == 125)
	CAN_SetCNF1(7);
#endif
#if (MX_MASTER_BIT_RATE == 250)
	CAN_SetCNF1(3);
#endif
#if (MX_MASTER_BIT_RATE == 1000)
	CAN_SetCNF1(0);
#endif
}
#endif

