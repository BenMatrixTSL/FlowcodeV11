// CRC: 20C35A1E87BE6D5C727502197CD041A70BE17189BB69E7BE04A18BA52A626875ABBE62C3873F1797E13A57ACC2F6622A49837B2A882EFB9D67AEB87FD33BE1769A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5103257AA0399AE7BD3275BAE2523AA35E74731E1C5B6AD779CC2A4FA9196A5259DCDC0A0E64B6EFD580D351E8EB420E5F298E0AB62B64B677304910E491A3ED9CBE6EF5A66E1DB7797F58F57971A98F1D4950D1467E34F13549D34A0D5AD11F3A06C6B37D1C172FFFA7F75F63C1DBDFE01515DF10A2013FFC1E0961D1CF9D810AE94354B8E74C3BA
// REVISION: 1.0
// GUID: F5689AA6-577C-418F-A981-EAF760CB0FB2
// DATE: 08\08\2022
// DIR: CAL\PIC\USB\MX_usb_hid_ep0Out.c
/*********************************************************************
 *                    Flowcode USB Library Code
 *
 * (c) 2009 Matrix Multimedia Ltd.
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
 * 2809617 | SK | Created
 ********************************************************************/

#if (MX_OUT_PCK_SIZE > 0)
	#define USER_SET_REPORT_HANDLER	   USBHIDCBSetReportHandler

	void USBHIDCBSetReportHandler(void)
	{
		USBEP0Receive((MX_UINT8*)&ReceivedDataBuffer[0], MX_OUT_PCK_SIZE, 0);
		incoming = MX_OUT_PCK_SIZE;
	}
#endif