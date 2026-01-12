// CRC: 6EC20609B0E0838D6280BD8BA490CD44996AE0C14A44FEA45B91845A0946B1BAD7CD70F76642156A3318A69686A823079A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF567A296E23EB720378727A03294C15C90FE0FECB0496A408230054BB24C9CDBBAC90F7AB73F8DB26F2793B15C4FFA890000D58CEF80AA76FE72881140518E61C3EE937483032F937740D7A4B698B442C811DA6271DD1D7342549D34A0D5AD11F3C8044ED557B79387D0D657B9EEFF64429111EBA50A5384C5C7E9BF2E0A60D235BB3AB4325F399FDA
// REVISION: 1.0
// GUID: 8E155D05-51ED-4013-9732-B6F10E33BAAD
// DATE: 08\08\2022
// DIR: CAL\MIAC\MIAC_CAL_API.h
/*********************************************************************
 *                  Flowcode CAL File
 *
 * File: MIAC_CAL_API.h
 *
 * (c) 2015 Matrix TSL
 * http://www.matrixtsl.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
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
 * 171115 | LM | Created
 *
 */

#if defined MX_MIAC_MODULE_DSP
	#include "MIAC_CAL_DSP.h"
#elif defined MX_MIAC_MODULE_AVR
	#include "MIAC_CAL_AVR.h"
#endif

#ifndef MIAC_CAL_API_H
#define MIAC_CAL_API_H

// Initialises the MIAC driver. Call before any other MIAC function calls.
extern MX_UINT8 MIAC_Init(void);
// Releases any resources. Call before exit.
extern MX_UINT8 MIAC_Uninit(void);
	
/* Display funnctions */
// Controls the gLCD backlight: state=1=on state=0=off
extern void MIAC_DisplayLight(MX_UINT8 state);
// Clears the gLCD to all spaces
extern void MIAC_DisplayClear(void);
// Places the gLCD text cursor at column (0-19) and row (0-3)
extern void MIAC_DisplayCursor(MX_UINT8 column, MX_UINT8 row);
// Initialises the gLCD display. Call before use.
extern void MIAC_DisplayStart(void);
// 
extern void MIAC_PrintString(MX_CHAR *text, MX_UINT16 max);
// 
extern void MIAC_PrintASCII(MX_CHAR c);
	
// Drawing functions
extern void MIAC_DrawPixel(MX_UINT8 px, MX_UINT8 py, MX_UINT8 state);
extern void MIAC_DrawGlyph(MX_UINT8 c, MX_UINT8 x, MX_UINT8 y, MX_UINT8 mode);
	
// Returns the key pressed. 255 if nothing pressed
extern MX_UINT8 MIAC_GetKeypad(void);
// 
extern MX_UINT8 MIAC_InputAnalog(MX_UINT8 channel);
extern MX_UINT16 MIAC_InputAnalog_10bit(MX_UINT8 channel);
extern MX_UINT8 MIAC_InputDigital(MX_UINT8 channel);
	
extern void MIAC_OutputOn(MX_UINT8 channel);
extern void MIAC_OutputOff(MX_UINT8 channel);
	
extern void MIAC_RelayOn(MX_UINT8 channel);
extern void MIAC_RelayOff(MX_UINT8 channel);

#endif

