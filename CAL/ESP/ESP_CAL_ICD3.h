// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A09EBD8E8CA013871BF7E734AF405DDDA4EA68E2929511E6E27D52A876A9F220FA562AF2F62E9AB6760C3CAEE8E7DA6987A5823572E05692CC1BD634B91E31C008A96C9F12DD1B72B74EBEF3420D9F1C3137C45DAD8BF74F05CDEA49B2852C7C1CE70074A6FD621DA2BB3129C70E0D0387E874CA28DAA42907BF2080D7518CEA61A61930F97993E62D549D34A0D5AD11F37B503E71200CA791B897DC1A1F0FF49EEAA7D21DB6F3315435CB29F668C7CEEBDE7ED4CEB4872907
// REVISION: 5.0
// GUID: 6880F07F-D74E-4264-B4D9-67BC024BB9C0
// DATE: 19\09\2025
// DIR: CAL\ESP\ESP_CAL_ICD3.h

/*********************************************************************
 *                  Flowcode CAL Super ICD File
 *
 * File: PIC_CAL_ICD3.h
 *
 * (c) 2024 Matrix Multimedia Ltd.
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
 * 141024 | BR | Created
 * 140425 | BR | Updated to include Flowcode ICD defines
 *
 *
 */


//ICD Command Codes
#define ICD_CMD_PAUSE  		0x80

#define ICD_CMD_STEP  		0x81
#define ICD_CMD_RUN   		0x82
#define ICD_CMD_RESENDID	0x83
#define ICD_CMD_STOP		0x84
#define ICD_CMD_SETBP		0x85
#define ICD_CMD_CLRBP		0x86
#define ICD_CMD_RDRAM		0x87
#define ICD_CMD_WRRAM		0x88
#define ICD_CMD_RDEE		0x89
#define ICD_CMD_WREE		0x8A
#define ICD_CMD_STACK		0x8B
#define ICD_CMD_FWID		0x8C

//ICD Message Codes
#define ICD_MSG_SENDID		0x90
#define ICD_MSG_RAM			0x91
#define ICD_MSG_EE			0x92
#define ICD_MSG_STACK		0x93
#define ICD_MSG_FWID		0x94

#define FC_ICD_OFF   ICD_State = ICD_State | 0x80;
#define FC_ICD_ON    ICD_State = ICD_State & 0x7F;

//ICD Global Variables
unsigned char ICD_State = 0x02;				//First run to setup comms channel indicated with value of 2
unsigned char icd_stack_ptr = 0x00;
unsigned char dbg_mode;						//This one is no longer needed!

typedef union
{
  MX_FLOAT AsFloat;
  MX_UINT32 AsLong;
  MX_UINT16 AsInt[2];
  MX_UINT8  AsByte[4];
} ICD_Union;

ICD_Union ICD_Union32;

//ICD CB Functions
void ICD_TX_CB_PutByte(unsigned char data);
unsigned char ICD_TX_CB_GetByte();
unsigned char ICD_TX_CB_Count();
void ICD_RX_CB_PutByte(unsigned char data);
unsigned char ICD_RX_CB_GetByte();
unsigned char ICD_RX_CB_Count();

//ICD Functions
void FC_MARKER(signed int block_id);
void ICD_PUSH(char macro_id);
void ICD_POP();
unsigned long  read_register(unsigned long address);
void write_register(unsigned long address, unsigned long data);
unsigned long read_ee(unsigned long address);
void write_ee(unsigned long  address, unsigned long data);
void rst_dev(void);


//Serial based ICD comms
#if ICD3_TYPE == com

	#define MX_UART_REF16

	#define MX_UART_UseTX_16 	(1)
	#define MX_UART_TX_PIN_16 	(ICD3_TX_PIN)

	#if ICD3_TX_PORT == 0
		#define MX_UART_TX_TRIS_16 	trisa
		#define MX_UART_TX_PORT_16 	porta
	#endif
	#if ICD3_TX_PORT == 1
		#define MX_UART_TX_TRIS_16 	trisb
		#define MX_UART_TX_PORT_16 	portb
	#endif
	#if ICD3_TX_PORT == 2
		#define MX_UART_TX_TRIS_16 	trisc
		#define MX_UART_TX_PORT_16 	portc
	#endif
	#if ICD3_TX_PORT == 3
		#define MX_UART_TX_TRIS_16 	trisd
		#define MX_UART_TX_PORT_16 	portd
	#endif

	#define MX_UART_UseRX_16 	(1)
	#define MX_UART_RX_PIN_16 	(ICD3_RX_PIN)

	#if ICD3_RX_PORT == 0
		#define MX_UART_RX_TRIS_16 	trisa
		#define MX_UART_RX_PORT_16 	porta
	#endif
	#if ICD3_RX_PORT == 1
		#define MX_UART_RX_TRIS_16 	trisb
		#define MX_UART_RX_PORT_16 	portb
	#endif
	#if ICD3_RX_PORT == 2
		#define MX_UART_RX_TRIS_16 	trisc
		#define MX_UART_RX_PORT_16 	portc
	#endif
	#if ICD3_RX_PORT == 3
		#define MX_UART_RX_TRIS_16 	trisd
		#define MX_UART_RX_PORT_16 	portd
	#endif


	#define MX_UART_CHANNEL_16 	(ICD3_CHANNEL)
	#define MX_UART_ECHO_16 	(0)
	#define MX_UART_DBITS_16 	(8)
	#define MX_UART_RETURN_16 	(1)
	#define MX_UART_BAUD_16 	(ICD3_BAUD)
	#define MX_UART_INT_16 		(1)
	#define MX_UART_FLOWEN_16 	(0)

	//void FC_CAL_UART_Init_16(void);
	//void FC_CAL_UART_Send_16(MX_UINT16 x);
	//MX_SINT16 FC_CAL_UART_Receive_16(MX_UINT8 x);

	#define ICD_COMMS_INIT 		FC_CAL_UART_Init_16
	#define ICD_COMMS_TX		FC_CAL_UART_Send_16
	#define ICD_COMMS_RX		FC_CAL_UART_Receive_16

	#define ICD_COMMS_INT_EN
	#define ICD_COMMS_INT_DIS

	#if ICD3_CHANNEL == 1
		#define ICD_INTERRUPT_HANDLER MX_UART_INT_CH1_FUNC if (MX_UART_INT_CH1_DET) { ICD_RX_CB_PutByte(ICD_COMMS_RX(0)); } MX_UART_INT_FUNC_END
	#endif
	#if ICD3_CHANNEL == 2
		#define ICD_INTERRUPT_HANDLER MX_UART_INT_CH2_FUNC if (MX_UART_INT_CH2_DET) { ICD_RX_CB_PutByte(ICD_COMMS_RX(0)); } MX_UART_INT_FUNC_END
	#endif
	#if ICD3_CHANNEL == 3
		#define ICD_INTERRUPT_HANDLER MX_UART_INT_CH3_FUNC if (MX_UART_INT_CH3_DET) { ICD_RX_CB_PutByte(ICD_COMMS_RX(0)); } MX_UART_INT_FUNC_END
	#endif

#endif



//Circular comms buffers
#define ICD_TX_CB_SIZE 40
#define ICD_RX_CB_SIZE 40
