// CRC: 77485F5F6A861F9125D47827B4DE492656C5431E478E8046055FD2257F64F1F3A11FCF62CA56EE8ACA84FD30CBA639E3EA68E2929511E6E27D52A876A9F220FA562AF2F62E9AB6760C3CAEE8E7DA6987ADA37473AE3F62B84F75D50D90B14B4DCBA13F1812722DB68AB215A790148C297B372A10484B6BE67CA03B89912A86DB69DA8A738067E0A5EB53308F5927B54EA1924C5609645F7455AEA69B788AAC1F06E289E88807B31E549D34A0D5AD11F33DBA061EED95EA4B6B6C25554DD7A9206155DF1932B5094FEA7459FBAA187747CD4C0F0302B21EE1
// REVISION: 9.0
// GUID: 9C20CBDC-2B79-429E-A3F4-FCCA5C19389E
// DATE: 19\09\2025
// DIR: CAL\AVR\AVR_CAL_ICD3.c
/*********************************************************************
 *                  Flowcode CAL Super ICD File
 *
 * File: AVR_CAL_ICD3.c
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


//Circular comms buffers
unsigned char ICD_TX_Buff[ICD_TX_CB_SIZE];
unsigned char ICD_TX_Start = 0;
unsigned char ICD_TX_End = 0;

unsigned char ICD_RX_Buff[ICD_RX_CB_SIZE];
unsigned char ICD_RX_Start = 0;
unsigned char ICD_RX_End = 0;

void ICD_TX_CB_PutByte(unsigned char data)
{
	unsigned char address = ICD_TX_End + 1;
	if (address >= ICD_TX_CB_SIZE)
		address = 0;

	if (address != ICD_TX_Start)
	{
		ICD_TX_Buff[ICD_TX_End] = data;
		ICD_TX_End = address;
	}
}

unsigned char ICD_TX_CB_GetByte()
{
	if (ICD_TX_Start != ICD_TX_End)
	{
		unsigned char retval = ICD_TX_Buff[ICD_TX_Start];

		ICD_TX_Start++;
		if (ICD_TX_Start >= ICD_TX_CB_SIZE)
			ICD_TX_Start = 0;

		return (retval);
	}
	return (0);
}

unsigned char ICD_TX_CB_Count()
{
	if (ICD_TX_Start != ICD_TX_End)
	{
		if (ICD_TX_End > ICD_TX_Start)
			return ICD_TX_End - ICD_TX_Start;
		else
			return (ICD_TX_CB_SIZE - ICD_TX_Start) + ICD_TX_End;
	}
	return (0);
}

void ICD_RX_CB_PutByte(unsigned char data)
{
	unsigned char address = ICD_RX_End + 1;
	if (address >= ICD_RX_CB_SIZE)
		address = 0;

	if (address != ICD_RX_Start)
	{
		ICD_RX_Buff[ICD_RX_End] = data;
		ICD_RX_End = address;
	}
}

unsigned char ICD_RX_CB_GetByte()
{
	if (ICD_RX_Start != ICD_RX_End)
	{
		unsigned char retval = ICD_RX_Buff[ICD_RX_Start];

		ICD_RX_Start = ICD_RX_Start + 1;
		if (ICD_RX_Start >= ICD_RX_CB_SIZE)
			ICD_RX_Start = 0;

		return (retval);
	}
	return (0);
}

unsigned char ICD_RX_CB_Contains(unsigned char * data, unsigned char count)
{
	unsigned char matchcount = 0;
	unsigned char address = ICD_RX_Start;

	while (address != ICD_RX_End)
	{
		if (ICD_RX_Buff[address] == data[matchcount])
		{
			matchcount++;
			if (matchcount == count)
				return (1);
		}
		else
			matchcount = 0;

		address++;
		if (address >= ICD_RX_CB_SIZE)
			address = 0;
	}
	return (0);
}

unsigned char ICD_RX_CB_Count()
{
	if (ICD_RX_Start != ICD_RX_End)
	{
		if (ICD_RX_End > ICD_RX_Start)
			return ICD_RX_End - ICD_RX_Start;
		else
			return (ICD_RX_CB_SIZE - ICD_RX_Start) + ICD_RX_End;
	}
	return (0);
}



unsigned char ICD_CMD_State = 0;


//Checks the incoming RX CB to see if there is a complete command ready to action
unsigned char ICD_Check_For_Command()
{
	unsigned char len = ICD_RX_CB_Count();
	unsigned char ix = 0;

	//Look for command start - throw away data until we hit the command start byte
	if (ICD_CMD_State == 0)
	{
		if (ICD_RX_CB_GetByte() == ':')
			ICD_CMD_State = 1;
	}

	//Look for command end - retain data in buffer
	if (ICD_CMD_State == 1)
	{
		if (ICD_RX_CB_Contains(";\n", 2))
			ICD_CMD_State = 2;
	}

	//Action command
	if (ICD_CMD_State == 2)
	{
		ICD_CMD_State = 0;
		return (1);
	}

	return(0);
}


//Assembles an outgoing packet and stores in the outgoing TX CB
void ICD_Send_Message(unsigned char MessageCode, unsigned char * data, unsigned char count)
{
	unsigned char ix;

	ICD_TX_CB_PutByte(':');
	ICD_TX_CB_PutByte(MessageCode);

	for (ix = 0; ix < count; ix++)
	{
		ICD_TX_CB_PutByte(data[ix]);
	}
	ICD_TX_CB_PutByte(';');
	ICD_TX_CB_PutByte('\n');

	unsigned char cbcount = ICD_TX_CB_Count();

	for (ix = 0; ix < cbcount; ix++)
	{
		ICD_COMMS_TX(ICD_TX_CB_GetByte());
	}
}


//Check to see if there is any incoming data available, any available data is placed into the RX CB
//Used inside the main ICD blocking loop when interrupts are disabled
void ICD_Poll_Comms()
{
	unsigned int rx = ICD_COMMS_RX(0);
	if (rx < 256)
	{
		ICD_RX_CB_PutByte(rx);
	}
}


//ICD Marker Functions - Called at the start of every Flowcode functional icon when ICD is enabled.
void FC_MARKER(signed int block_id)
{
	if ((ICD_State & 0x80) != 0) return;

	ICD_COMMS_INT_DIS;
	unsigned char int_flags = SREG;					//Store I flag
	cli();											//Disable all interrupts

	unsigned char ICD_CMD_Code = 0;
	unsigned char msgSent = 0;
	unsigned char icd_txdata[16];
	unsigned char ix;

	if ((ICD_State & 0x7F) == 0)								//Free running mode
	{
		unsigned char ix;

		//Check for any active breakpoints
		for (ix=0; ix<ICD_NUM_BPS; ix++)
		{
			if(block_id == brk_pnt[ix])
				ICD_State = (ICD_State & 0x80) | 1;
		}

		//Is there anything in the RX CB? - This is populated by interrupts so we can only action a completed command here.
		//The only command supported at this stage is the pause command
		if (ICD_RX_CB_Count())
		{
			if (ICD_Check_For_Command())
			{
				//First byte is command code
				ICD_CMD_Code = ICD_RX_CB_GetByte();

				//The only actions we can take here is to pause or stop
				if (ICD_CMD_Code == ICD_CMD_PAUSE)
					ICD_State = (ICD_State & 0x80) | 1;

				if (ICD_CMD_Code == ICD_CMD_STOP)
					rst_dev();
			}
		}
	}

	//Blocking loop, wait for command on what to do next
	while (ICD_State & 0x7F)
	{
		//On first run startup comms channel
		if ((ICD_State & 0x7F) == 2)
		{
			delay_ms(100);		//Startup delay
			ICD_COMMS_INIT();
			ICD_State = (ICD_State & 0x80) | 1;  //Blocking mode
		}

		if ((msgSent == 0) || (ICD_CMD_Code == ICD_CMD_RESENDID))
		{
			ICD_Union32.AsInt[0] = block_id;
			icd_txdata[0] = ICD_Union32.AsByte[0];
			icd_txdata[1] = ICD_Union32.AsByte[1];

			//flag that the program has stopped
			ICD_Send_Message(ICD_MSG_SENDID, icd_txdata, 2);
			msgSent = 1;
			ICD_CMD_Code = 0;
		}

		//Poll for incoming command data here as interrupts are now disabled
		ICD_Poll_Comms();

		//Is there anything in the RX CB?
		if (ICD_RX_CB_Count())
		{
			if (ICD_Check_For_Command())
			{
				//First byte is command code
				ICD_CMD_Code = ICD_RX_CB_GetByte();

				if (ICD_CMD_Code == ICD_CMD_STEP)
					goto ICDLeaveLoop;
				if (ICD_CMD_Code == ICD_CMD_RUN)
					ICD_State = (ICD_State & 0x80) | 0;			//Non blocking mode
				if (ICD_CMD_Code == ICD_CMD_STOP)
					rst_dev();
				if (ICD_CMD_Code == ICD_CMD_SETBP)
				{
					ICD_Union32.AsByte[0] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[1] = ICD_RX_CB_GetByte();
					for (ix=0; ix < ICD_NUM_BPS; ix++)
					{
						if (brk_pnt[ix] == -1)
						{
							brk_pnt[ix] = ICD_Union32.AsInt[0];
							break;
						}
					}
				}
				if (ICD_CMD_Code == ICD_CMD_CLRBP)
				{
					ICD_Union32.AsByte[0] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[1] = ICD_RX_CB_GetByte();
					for (ix=0; ix < ICD_NUM_BPS; ix++)
					{
						if (brk_pnt[ix] == ICD_Union32.AsInt[0])
						{
							brk_pnt[ix] = -1;
						}
					}
				}
				if (ICD_CMD_Code == ICD_CMD_RDRAM)
				{
					ICD_Union32.AsByte[0] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[1] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[2] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[3] = ICD_RX_CB_GetByte();
					unsigned char iCount = ICD_RX_CB_GetByte();

					ICD_Union32.AsLong = read_register(ICD_Union32.AsLong);
					icd_txdata[0] = ICD_Union32.AsByte[0];
					icd_txdata[1] = ICD_Union32.AsByte[1];
					icd_txdata[2] = ICD_Union32.AsByte[2];
					icd_txdata[3] = ICD_Union32.AsByte[3];
					ICD_Send_Message(ICD_MSG_RAM, icd_txdata, 4);
				}
				if (ICD_CMD_Code == ICD_CMD_WRRAM)
				{
					ICD_Union32.AsByte[0] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[1] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[2] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[3] = ICD_RX_CB_GetByte();
					unsigned long address = ICD_Union32.AsLong;
					ICD_Union32.AsByte[0] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[1] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[2] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[3] = ICD_RX_CB_GetByte();
					write_register(address, ICD_Union32.AsLong);
				}
				if (ICD_CMD_Code == ICD_CMD_RDEE)
				{
					ICD_Union32.AsByte[0] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[1] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[2] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[3] = ICD_RX_CB_GetByte();
					ICD_Union32.AsLong = read_ee(ICD_Union32.AsLong);
					icd_txdata[0] = ICD_Union32.AsByte[0];
					icd_txdata[1] = ICD_Union32.AsByte[1];
					icd_txdata[2] = ICD_Union32.AsByte[2];
					icd_txdata[3] = ICD_Union32.AsByte[3];
					ICD_Send_Message(ICD_MSG_EE, icd_txdata, 4);
				}
				if (ICD_CMD_Code == ICD_CMD_WREE)
				{
					ICD_Union32.AsByte[0] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[1] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[2] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[3] = ICD_RX_CB_GetByte();
					unsigned long address = ICD_Union32.AsLong;
					ICD_Union32.AsByte[0] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[1] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[2] = ICD_RX_CB_GetByte();
					ICD_Union32.AsByte[3] = ICD_RX_CB_GetByte();
					write_ee(address, ICD_Union32.AsLong);
				}
				if (ICD_CMD_Code == ICD_CMD_STACK)
				{
					icd_txdata[0] = ICD_STACK_SIZE;
					icd_txdata[1] = icd_stack_ptr;
					for (ix=0; ix < ICD_STACK_SIZE; ix++)
						icd_txdata[ix + 2] = icd_stack[ix];

					ICD_Send_Message(ICD_MSG_STACK, icd_txdata, ICD_STACK_SIZE+2);
				}
				if (ICD_CMD_Code == ICD_CMD_FWID)
				{
					icd_txdata[0] = ICD_ID0;
					icd_txdata[1] = ICD_ID1;
					icd_txdata[2] = ICD_ID2;
					icd_txdata[3] = ICD_ID3;
					icd_txdata[4] = ICD_ID4;
					icd_txdata[5] = ICD_ID5;
					icd_txdata[6] = ICD_ID6;
					icd_txdata[7] = ICD_ID7;
					ICD_Send_Message(ICD_MSG_FWID, icd_txdata, 8);
				}
			}
		}
	}

	ICDLeaveLoop:

	if (int_flags & (1 << SREG_I)) sei();					//Restore all interrupts
	ICD_COMMS_INT_EN;

	return;
}


void ICD_PUSH (char macro_id)
{
	//We can only record the level of stack with allocated RAM
	if (icd_stack_ptr < ICD_STACK_SIZE)
	{
		icd_stack[icd_stack_ptr] = macro_id;			//Assign macro ID
	}
	icd_stack_ptr++;									//Move to next layer of stack
}


void ICD_POP()
{
	if (icd_stack_ptr)
		icd_stack_ptr--;
}


unsigned long read_register(unsigned long address)
{
	unsigned long RetVal;

	volatile unsigned char* register_ptr = (unsigned char*)address;

	RetVal = *register_ptr;

	return RetVal;
}


void write_register(unsigned long address, unsigned long data)
{
	volatile unsigned char* register_ptr = (unsigned char*)address;

	*register_ptr = data;
}


unsigned long read_ee(unsigned long address)
{
	unsigned long RetVal = 0;

	#ifdef MX_EE						//Is EEPROM Available?

		#ifdef EEWE
			while (test_bit(EECR, EEWE));
		#else
			while (test_bit(EECR, EEPE));
		#endif

		RetVal = eeprom_read_byte((unsigned char *)address);

	#endif

	return RetVal;
}


void write_ee(unsigned long address, unsigned long data)
{
	#ifdef MX_EE						//Is EEPROM Available?

		#ifdef EEWE
			while (test_bit(EECR, EEWE));
		#else
			while (test_bit(EECR, EEPE));
		#endif

		eeprom_write_byte((unsigned char *)address, data);

	#endif
}


void rst_dev()
{
	cli();				//Disable all interrupts
	wdt_enable(0);		//Enable watchdog with shortest delay
	delay_s(1);			//Wait for watchdog reset
}


//End of ICD functionality