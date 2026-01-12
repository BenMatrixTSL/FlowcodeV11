// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BE5A11A7B597E6F7EA8FE53F6FF9C4729AAFF7D054EA9B4CC9BDC419C02E9E1921B6336C11BE63C7B23E6A7110B5081D39796EDD611F6757020C3CAEE8E7DA69874F72A8E0FFF6BAB26B03417734FDB29E3B56B4E9608BE7B0EED62BE8F64CF1433C4D6AB521291475EBE8E58CB0CCE2AD1C9E057381696A8EA24B2535FC5257D0E7A48E7ED61B6A7394E281A8D4067A08232AE3563A2DB2E4549D34A0D5AD11F304612437587D555BF60C451559291572EA4561AEED75746A1EDE0E6E8CE8F293FC3F53D5103A0873
// REVISION: 2.0
// GUID: 6E365E38-6E2E-44E5-B462-5B36686836C8
// DATE: 11\07\2025
// DIR: CAL\STARM\STARM_CAL_USB_Serial.c

/*********************************************************************
 *              Flowcode CAL USB Serial CDC Comms
 *
 * File: PIC_CAL_USB_Serial.c
 *
 * (c) 2025 Matrix TSL
 * http://www.matrixTSL.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
 * ?Company?) for its Flowcode graphical programming language is
 * intended and supplied to you, the Company?s customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
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
 * 100725 | BR | Created
 *
 */



#define MX_USB_SERIAL_ENUM_TOUTEN_X     	CAL_APPEND(MX_USB_SERIAL_ENUM_TOUTEN_, MX_USB_SERIAL_NUM)
#define MX_USB_SERIAL_ENUM_TOUT_X     		CAL_APPEND(MX_USB_SERIAL_ENUM_TOUT_, MX_USB_SERIAL_NUM)
#define MX_USB_SERIAL_ENUM_RETURN_X     	CAL_APPEND(MX_USB_SERIAL_ENUM_RETURN_, MX_USB_SERIAL_NUM)



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_Initialise_, ())
{
	USBDeviceInit(0);

	if (MX_USB_SERIAL_ENUM_TOUT_X)
	{
		return 0;
		return 255;
	}
	else
	{
		return 0;
	}
}



CALFUNCTION(MX_UINT16, FC_CAL_USB_Serial_ReadByte_, (MX_UINT8 timeout_ms))
{
	MX_UINT16 retval = 255;
	MX_UINT8 inner = 0;

	if (MX_USB_SERIAL_ENUM_RETURN_X)
		retval = 512;

	if (timeout_ms == 0)
	{
		timeout_ms = 1;
		inner = 98;
	}


	return retval;
}



CALFUNCTION(MX_UINT16, FC_CAL_USB_Serial_ReadString_, (MX_CHAR *FCR_RETVAL, MX_UINT16 FCRsz_RETVAL, MX_UINT8 timeout_ms, MX_UINT8 FCL_LENGTH))
{
	MX_UINT8 FCL_WAIT_FOREVER = 0;
	MX_UINT16 inner = 0;
	MX_UINT16 idx;

	if (timeout_ms == 0)
		timeout_ms = 1;

}





CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendByte_, (MX_UINT8 FCL_DATA))
{

  MX_UINT16 FCL_TIMEOUT = (0x0);




  return (0);
}



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendByteArray_, (MX_UINT8 *FCL_DATA, MX_UINT16 FCLsz_DATA, MX_UINT8 FCL_NUMBYTES))
{
	MX_UINT16 FCL_TIMEOUT = (0x0);

	return (0);
}



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendString_, (MX_CHAR *FCL_DATA, MX_UINT16 FCLsz_DATA))
{
  	MX_UINT16 FCL_TIMEOUT = (0x0);
  	MX_UINT8 FCL_LENGTH;

	FCL_LENGTH = FCI_GETLENGTH(FCL_DATA, FCLsz_DATA);


    return (0);
}

