// CRC: AE5753800093D2B889297C6B876B6A21749C10AFA09C3FCE4A5F65B0FF76818F1C1D9B46CD5A2250B072AE94224B49139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF51E0A59E5B5F9649C9E4E07848A6D79C2EFA0AA1D13FB9FB1BD4119A2D7DF05D56328F61B959647663045D74B2D106EF737F0D6E193474061B860C75E4429307E80DD0D324402E982DFF6457B71FEFBC06897A1C64EC68459549D34A0D5AD11F38DABAC69564335450A1CE1DF7C68838A32345B631E9349A95C705324202ABA0CC88A103EBA5EA7CE
// REVISION: 1.0
// GUID: FA9C66D7-C928-4606-B21D-87EA40A61F04
// DATE: 08\08\2022
// DIR: CAL\ARM\ARM_CAL_EEPROM.c
/*********************************************************************
 *                  Flowcode CAL EEPROM File
 *
 * File: PIC16BIT_CAL_EEPROM.c
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
 * 210911 | BR | Created
 * 050312 | BR | Updated to v5.1 CAL Schema
 * 010513 | LM | V6 EEPROM CAL standardised API to 16 bit data word size
 */



MX_UINT16 FC_CAL_EE_Read (MX_UINT16 Address)
{
	#ifdef MX_EE

	#else
		#error "Chip does not have EEPROM memory"
	#endif

	return (0);
}

void FC_CAL_EE_Write (MX_UINT16 Address, MX_UINT16 Data)
{
	#ifdef MX_EE

	#else
		#error "Chip does not have EEPROM memory"
	#endif
}

