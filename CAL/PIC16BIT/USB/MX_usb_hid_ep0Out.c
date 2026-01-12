// CRC: 5D982BB222882C54AB4AFF20A1590FC4128F294B41FC96FD138D7F694DC5EBF5682BC20471DC73E5CEAB0DEE19E93584D42E4489BEB82B00C1FD2F54EAB1239DC071A914432FE88FE425100564A18C269A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF596FF4F763BBA296B4040D0C1FAD2D4A7705B4A87C2BDD2191C448E14C44B20376D9841B38FC0134EBA502A7ACC2ACEF41B4628BEE3E3F7C71DDEB946E985D5FF9187B817CC5040FBAA0AB4AB093157FB61F0A239F978847A549D34A0D5AD11F3AB693B1C20E20D93AF8534BEE6FC02B18FA232F091D283B9E7373FB746EF938F8DC82FEBD146BBA9
// REVISION: 1.0
// GUID: 2F8CDF8E-62FF-49A2-A053-5305C5FE1C70
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\USB\MX_usb_hid_ep0Out.c
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