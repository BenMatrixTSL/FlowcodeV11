// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B89EBD8E8CA013871BF7E734AF405DDDA4F6B7B6BFB0C4C6F420BDE58D868796A68940AE31AE32EB4A0C3CAEE8E7DA69874B6FD30DB6B41B40BC3A712E7BD29E2A49B1A52A68DFCCBA3BA0DCC991595F692C30ED153B9EF1A38BEDF63B438FADC230066213751866DDA5B72A9E33FDB19E3274FAFB5783B6822746750A1F77374E4E7F029C349C2F7A549D34A0D5AD11F31CDC76A963B56B114D8BEC581F3B13D569D392CD7220F6AB14E084950FA5CC8F5270B55B262AFD36
// REVISION: 11.0
// GUID: C27B41C6-4822-4F88-AD83-699BCDEE2FA6
// DATE: 10\10\2025
// DIR: CAL\PIC\PIC_CAL_ICD3.h

/*********************************************************************
 *                  Flowcode CAL Super ICD File
 *
 * File: PIC_CAL_ICD3.c
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
 * 151225 | BR | Updated to include Flowcode ICD defines
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
	#if ICD3_TX_PORT == 4
		#define MX_UART_TX_TRIS_16 	trise
		#define MX_UART_TX_PORT_16 	porte
	#endif
	#if ICD3_TX_PORT == 5
		#define MX_UART_TX_TRIS_16 	trisf
		#define MX_UART_TX_PORT_16 	portf
	#endif
	#if ICD3_TX_PORT == 6
		#define MX_UART_TX_TRIS_16 	trisg
		#define MX_UART_TX_PORT_16 	portg
	#endif
	#if ICD3_TX_PORT == 7
		#define MX_UART_TX_TRIS_16 	trish
		#define MX_UART_TX_PORT_16 	porth
	#endif
	#if ICD3_TX_PORT == 8
		#define MX_UART_TX_TRIS_16 	trisj
		#define MX_UART_TX_PORT_16 	portj
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
	#if ICD3_RX_PORT == 4
		#define MX_UART_RX_TRIS_16 	trise
		#define MX_UART_RX_PORT_16 	porte
	#endif
	#if ICD3_RX_PORT == 5
		#define MX_UART_RX_TRIS_16 	trisf
		#define MX_UART_RX_PORT_16 	portf
	#endif
	#if ICD3_RTX_PORT == 6
		#define MX_UART_RX_TRIS_16 	trisg
		#define MX_UART_RX_PORT_16 	portg
	#endif
	#if ICD3_RTX_PORT == 7
		#define MX_UART_RX_TRIS_16 	trish
		#define MX_UART_RX_PORT_16 	porth
	#endif
	#if ICD3_RTX_PORT == 8
		#define MX_UART_RX_TRIS_16 	trisj
		#define MX_UART_RX_PORT_16 	portj
	#endif


	#define MX_UART_CHANNEL_16 	(ICD3_CHANNEL)
	#define MX_UART_ECHO_16 	(0)
	#define MX_UART_DBITS_16 	(8)
	#define MX_UART_RETURN_16 	(1)
	#define MX_UART_BAUD_16 	(ICD3_BAUD)
	#define MX_UART_INT_16 		(0)
	#define MX_UART_FLOWEN_16 	(0)

	//void FC_CAL_UART_Init_16(void);
	//void FC_CAL_UART_Send_16(MX_UINT16 x);
	//MX_SINT16 FC_CAL_UART_Receive_16(MX_UINT8 x);

	#define ICD_COMMS_INIT 		FC_CAL_UART_Init_16
	#define ICD_COMMS_TX		FC_CAL_UART_Send_16
	#define ICD_COMMS_RX		FC_CAL_UART_Receive_16

	#if ICD3_CHANNEL == 1
		#define ICD_COMMS_INT_EN		MX_UART_INT_CH1_EN
		#define ICD_COMMS_INT_DIS		MX_UART_INT_CH1_DIS
		#define ICD_INTERRUPT_HANDLER 	if (MX_UART_INT_CH1_DET) { ICD_RX_CB_PutByte(ICD_COMMS_RX(0)); } MX_UART_INT_FUNC_END
	#endif
	#if ICD3_CHANNEL == 2
		#define ICD_COMMS_INT_EN		MX_UART_INT_CH2_EN
		#define ICD_COMMS_INT_DIS		MX_UART_INT_CH2_DIS
		#define ICD_INTERRUPT_HANDLER 	if (MX_UART_INT_CH2_DET) { ICD_RX_CB_PutByte(ICD_COMMS_RX(0)); } MX_UART_INT_FUNC_END
	#endif
	#if ICD3_CHANNEL == 3
		#define ICD_COMMS_INT_EN		MX_UART_INT_CH3_EN
		#define ICD_COMMS_INT_DIS		MX_UART_INT_CH3_DIS
		#define ICD_INTERRUPT_HANDLER 	if (MX_UART_INT_CH3_DET) { ICD_RX_CB_PutByte(ICD_COMMS_RX(0)); } MX_UART_INT_FUNC_END
	#endif
	#if ICD3_CHANNEL == 4
		#define ICD_COMMS_INT_EN		MX_UART_INT_CH4_EN
		#define ICD_COMMS_INT_DIS		MX_UART_INT_CH4_DIS
		#define ICD_INTERRUPT_HANDLER 	if (MX_UART_INT_CH4_DET) { ICD_RX_CB_PutByte(ICD_COMMS_RX(0)); } MX_UART_INT_FUNC_END
	#endif
	#if ICD3_CHANNEL == 5
		#define ICD_COMMS_INT_EN		MX_UART_INT_CH5_EN
		#define ICD_COMMS_INT_DIS		MX_UART_INT_CH5_DIS
		#define ICD_INTERRUPT_HANDLER 	if (MX_UART_INT_CH5_DET) { ICD_RX_CB_PutByte(ICD_COMMS_RX(0)); } MX_UART_INT_FUNC_END
	#endif

#endif



//Circular comms buffers
#define ICD_TX_CB_SIZE 40
#define ICD_RX_CB_SIZE 40
