// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B8A11FCF62CA56EE8ACA84FD30CBA639E39CE852FCC2E76CD08880CFFD18B90BBB208613300A49360F0C3CAEE8E7DA6987A0A79AF5CEAF68CA9F48C272D1043A04E2837A14265F0DD0F2190C286C330D627A562B4D8ECFD629FD3B8CDA0896753A0970B9AFAA21645694C31E856D02A11469D4A371346BA44387B796BE4041A3AECB011AE44E4E45FD549D34A0D5AD11F36BCA608CFD658EB76C9D3CE6311C6E1DFF6DC238D758ADE2FFCF1C90B393605E9F32B96E9FC2F3A9
// REVISION: 6.0
// GUID: 7408E905-9791-4B64-B342-9B8C6BF8982C
// DATE: 15\10\2025
// DIR: CAL\PIC\PIC_CAL_ICD3.c

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
	INTCONbits.GIE = 0;

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
			//delay_ms(100);		//Startup delay
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

	INTCONbits.PEIE = 1;					//Restore all interrupts
	INTCONbits.GIE = 1;						//Restore all interrupts
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
	//cli();				//Disable all interrupts
	//wdt_enable(0);		//Enable watchdog with shortest delay
	delay_s(1);			//Wait for watchdog reset
}


//End of ICD functionality