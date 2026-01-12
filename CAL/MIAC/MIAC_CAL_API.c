// CRC: 6EC20609B0E0838D6280BD8BA490CD44996AE0C14A44FEA45B91845A0946B1BAC6D4AA2E252E0C4053F652166F7595E99A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF561A5EFE55AA2C50FD7C04D899D84377CA7657469792BC0E2018877E266C8D5F1CE204703E2E5430207C18E9828B77890537D8DCC394BB4208894EEB2308F8A6C9B24B39D6607A0C710F58F88EB8EECA921A029338261D5A7549D34A0D5AD11F3A5B434DA476A7D9E37E127A2FCF266395030E5CDA00AF85ABFDF2E6001B9426D00C9FC801055D429
// REVISION: 1.0
// GUID: 524FD1BA-6446-471A-8C95-50B6F3485F5D
// DATE: 08\08\2022
// DIR: CAL\MIAC\MIAC_CAL_API.c
/*********************************************************************
 *                  Flowcode CAL File
 *
 * File: MIAC_CAL_API.c
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

#include "MIAC_CAL_API.h"

/**********************************************
 WG definitions and functions
**********************************************/

#define WG_EDGE_DELAY	delay_us(10)
#define WG_EN_DELAY		delay_us(80)
#define WG_EN_FOLLOW	delay_us(10)
#define WG_BUSY_DELAY	delay_us(80)
#define WG_GLYPH_MASK (0xff >> (8-WG_CHAR_WIDTH))

static MX_UINT8 WG_CursorX;
static MX_UINT8 WG_CursorY;

static void WG_Write(MX_UINT8 data);
static MX_UINT8 WG_Read(void);
static void WG_Command(MX_UINT8 command);
static MX_UINT8 WG_Status(void);
static void WG_WriteWordAt(MX_UINT16 w, MX_UINT8 x, MX_UINT8 y);
static MX_UINT16 WG_ReadWordAt(MX_UINT8 x, MX_UINT8 y);


static void WG_WriteWordAt(MX_UINT16 w, MX_UINT8 x, MX_UINT8 y)
{
	{
		// rotate the screen data
		MX_UINT16 temp = w;
		MX_UINT8 i = 16;
		
		// re-config the memory map
		if (y > 31)
		{
			y = 31 - y - 32;
			x = 7 - x;
		}
		else
		{
			y = 31 - y;
			x = 7 - x + 8;
		}
		
		w = 0;
		while(i--)
		{
			w <<= 1;
			if (temp & 1) w |= 1;
			temp >>= 1;
		}
	}
	// wait for Busy flag inactive
	while (WG_Status() & 0x80);
	// 1.   Set vertical address ( Y ) for GDRAM 
	WG_Command(0x80 | (y & 0x3f));
	WG_EDGE_DELAY;
	// 2.   Set horizontal address ( X ) for GDRAM 
	WG_Command(0x80 | (x & 0x0f));
	//while (WG_ReadBusyFlag());
	WG_EDGE_DELAY;
	// 3.   Write D15 - D8 to GDRAM (first byte) 
	WG_Write(w >> 8);
	WG_EDGE_DELAY;
	// 4.   Write D7 - D0 to GDRAM (second byte)
	WG_Write(w);
	WG_EDGE_DELAY;
}

static MX_UINT16 WG_ReadWordAt(MX_UINT8 x, MX_UINT8 y)
{
	MX_UINT16 temp;
	MX_UINT16 w;
	MX_UINT8 i = 16;

	// re-config the memory map
	if (y > 31)
	{
		y = 31 - y - 32;
		x = 7 - x;
	}
	else
	{
		y = 31 - y;
		x = 7 - x + 8;
	}

	// wait for Busy flag inactive
	while (WG_Status() & 0x80);
	// 1.   Set vertical address ( Y ) for GDRAM 
	WG_Command(0x80 | (y & 0x3f));
	WG_EDGE_DELAY;
	// 2.   Set horizontal address ( X ) for GDRAM 
	WG_Command(0x80 | (x & 0x0f));
	
	// dummy read
	WG_BUSY_DELAY;
	WG_Read();
	
	WG_BUSY_DELAY;
	temp = WG_Read() << 8;
	WG_BUSY_DELAY;
	temp |= WG_Read();
	WG_EDGE_DELAY;

	// mirror the screen data
	w = 0;
	while(i--)
	{
		w <<= 1;
		if (temp & 1) w |= 1;
		temp >>= 1;
	}
	return w;
}

// write a command byte to DB0-7 and do the handshake
static void WG_Command(MX_UINT8 command)
{
	MIAC_LCD_RW_VAL(0);				// RW low
	MIAC_LCD_RS_VAL(0);				// RS low
	// setup the DB0-7 data bits
	// set DB0-7 to output
	MIAC_LCD_DB_VAL_DDR(command);				
	// toggle EN
	MIAC_LCD_EN_VAL(1);
	WG_EN_DELAY;
	MIAC_LCD_EN_VAL(0);
	WG_EN_FOLLOW;
}

// write a data byte to DB0-7
static void WG_Write(MX_UINT8 data)
{
	MIAC_LCD_RW_VAL(0);				// RW low
	MIAC_LCD_RS_VAL(1);				// RS high
	// setup the DB0-7 data bits
	// set DB0-7 to output
	MIAC_LCD_DB_VAL_DDR(data);
	// toggle EN
	MIAC_LCD_EN_VAL(1);
	WG_EN_DELAY;
	MIAC_LCD_EN_VAL(0);
	WG_EN_FOLLOW;
}

// read a status byte from DB0-7
static MX_UINT8 WG_Status(void)
{
	MX_UINT8 status;
	// set DB0-7 to input
	MIAC_LCD_DB_IN_DDR;
	MIAC_LCD_RS_VAL(0);
	MIAC_LCD_RW_VAL(1);
	MIAC_LCD_EN_VAL(1);
	WG_EN_DELAY;					// wait a bit
	// read the DB0-7 data bits
	status = MIAC_LCD_DB_GET;
	MIAC_LCD_EN_VAL(0);
	WG_EN_FOLLOW;
	return status;
}

// read a data byte from DB0-7
static MX_UINT8 WG_Read(void)
{
	MX_UINT8 data;
	// set DB0-7 to input
	MIAC_LCD_DB_IN_DDR;
	MIAC_LCD_RS_VAL(1);
	MIAC_LCD_RW_VAL(1);
	WG_EDGE_DELAY;
	MIAC_LCD_EN_VAL(1);
	WG_EN_DELAY;					// wait a bit
	// read the DB0-7 data bits
	data = MIAC_LCD_DB_GET;
	MIAC_LCD_EN_VAL(0);
	WG_EN_FOLLOW;
	return data;
}


/**********************************************
 SPI0 API functions
**********************************************/

static MX_UINT8 MIAC_SPI0_cs;

MX_UINT8 MIAC_SPI0_Init(MX_UINT8 cs, MX_UINT8 mode, MX_UINT16 khz)
{
// cs: 0 = CAN, 1 = ADC
#if defined (MX_MIAC_MODULE_DSP)
// MCP3008 expects clock idle low, data out change on clock high to low, data read on clock rise, i.e. mid data period
// mode 0 used in the code as this was derived from AVR CPOL=0, CPHA=0 (AVR Mode 0: Sample on Rising, Setup on Falling)

	TRISG |= (1<<7);	// MISO on G7
	TRISG &= ~(1<<8);	// MOSI on G8
	TRISG &= ~(1<<6);	// SCLK on G6
	
	// chip selects, all high (disabled)
	MIAC_CS_CAN_SET_DDR;	// CS_CAN on B3
	MIAC_CS_ADC_SET_DDR;	// CS_ADC on B2
			
	MIAC_SPI0_cs = cs;

	SPI2CON1 = 0x1d;						// Assign Clock Prescalers f/16
	SPI2CON1bits.MSTEN = 1;					// Master mode
	SPI2CON1bits.CKE = (mode & 0x01)?0:1;	// Assign Clock Phase (1=out data changes on edge active to idle clock, i.e. falling)
	SPI2CON1bits.CKP = (mode & 0x02)?1:0;	// Assign Clock Polarity (0=idle state is low)
	SPI2CON1bits.SMP = 0;					// Assign Input Data Phase (0=in sample at middle of data out) 
	SPI2STATbits.SPIROV = 0;				// Clear unread data flag
	SPI2STATbits.SPIEN = 1;					// Enable SPI peripheral

#elif defined (MX_MIAC_MODULE_AVR)
											// Set MOSI, SCK as output, others input
	DDRB &= ~(1<<3);						// MISO on B3 input
	DDRB |= (1<<2);							// MOSI on B2 output
	DDRB |= (1<<1);							// SCLK on B1 output
											// Chip selects, all high (disabled)
	MIAC_CS_CAN_SET_DDR;					// CS_CAN on E6
	MIAC_CS_ADC_SET_DDR;					// CS_ADC on E5
	
	MIAC_SPI0_cs = cs;
											// Setup SPI Master mode, clock rate etc
	SPCR = (1 << MSTR);						// SPI Master mode (SPR1:SPR0=0 -> fosc/4)
	if (mode & 0x01) SPCR |= (1 << CPHA);	// Clock Phase
	if (mode & 0x02) SPCR |= (1 << CPOL);	// Clock Polarity
	SPCR |= (1 << SPE);						// SPI Enable
	
#endif
	return 0;
}

void MIAC_SPI0_Transaction(MX_UINT8* buffer, MX_UINT8 count)
{
	MX_UINT8 txn = 0;
	MX_UINT8 dummy;
	
	// chip select active
	if (MIAC_SPI0_cs) MIAC_CS_ADC_CLR_DDR else MIAC_CS_CAN_CLR_DDR;

#if defined (MX_MIAC_MODULE_DSP)
	dummy = SPI2BUF;					// dummy read to clear flags
	while (count--)
	{
		SPI2BUF = buffer[txn];					// send outgoing byte
		while (SPI2STATbits.SPIRBF == 0);		// wait until data has been sent
		buffer[txn++] = SPI2BUF;				// receive the byte
	}
#elif defined (MX_MIAC_MODULE_AVR)
	while (count--)
	{
		SPDR = buffer[txn];					// send outgoing byte
		while (!(SPSR & (1<<SPIF)));		// wait until data has been sent
		buffer[txn++] = SPDR;				// receive the byte
	}
#endif	
	// chip select de-activate
	if (MIAC_SPI0_cs) MIAC_CS_ADC_SET_DDR else MIAC_CS_CAN_SET_DDR;
}

MX_UINT8 MIAC_SPI0_Unint()
{
	return 0;
}

/**********************************************
 public functions
**********************************************/

MX_UINT8 MIAC_Init(void)
{
	// default motor and relays to low/clear/off
	// enable the motor outputs (this is the default action on MIAC)
	MIAC_OutputOff(1);
	MIAC_OutputOff(2);
	MIAC_OutputOff(3);
	MIAC_OutputOff(4);
	MIAC_RelayOff(1);
	MIAC_RelayOff(2);
	MIAC_RelayOff(3);
	MIAC_RelayOff(4);
	// initialise the gLCD display
	MIAC_DisplayStart();
	return 0;
}

MX_UINT8 MIAC_Uninit(void)
{
		return 0;
}

void MIAC_DisplayStart(void)
{
	// setup LCD handshake outputs
	MIAC_LCD_EN_VAL_DDR(0);		// set DDR to out and bit value to 0
	MIAC_LCD_RS_VAL_DDR(0);
	MIAC_LCD_RW_VAL_DDR(0);
	MIAC_LCD_RT_VAL_DDR(0);
	// reset the gLCD
	delay_ms(250);
	MIAC_LCD_RT_VAL(1);			// set bit value 1 (assume DDR already set)
	delay_ms(100);

// do the gLCD init sequence...
	WG_Command(0x30);		// 8 bit interface
	WG_Command(0x30);		// 8 bit interface
	WG_Command(0x01);		// clear RAM
	delay_ms(50);
	WG_Command(0xC0);		// cursor off, display on
	WG_Command(0xC0);		// cursor off, display on
	WG_Command(0x32);		// graphic mode on
	WG_Command(0x36);		// extended instruction set
	delay_ms(1);
	WG_Command(0x02);		// enable IRAM address
	WG_Command(0x40);		// IRAM 0
	WG_Command(0x80);		// GRAM 0
	WG_Command(0x80);		// GRAM 0
	
	delay_ms(100);
	MIAC_DisplayClear();
	MIAC_DisplayCursor(0,0);
	// default gLCD backlight to On
	MIAC_LCD_BL_VAL_DDR(1);		// set DDR as output, and pin set high
}

void MIAC_DisplayClear(void)
{
	MX_UINT8 row;
	MX_UINT8 col;

	WG_WriteWordAt(0, 0, 0);
	for (row=0; row < 64; ++row)
	{
		for (col=0; col < 8; ++col)
			WG_WriteWordAt(0, col, row);
	}
	
	WG_CursorX = 0;
	WG_CursorY = 0;
}

void MIAC_DisplayCursor(MX_UINT8 x, MX_UINT8 y)
{
	WG_CursorX = x;
	WG_CursorY = y;
}

// Test for WG_CHAR_COUNT defined. Just to avoid compiler errors in the case of no MIAC macros used
#ifdef WG_CHAR_COUNT

void MIAC_PrintString(MX_CHAR *p, MX_UINT16 max)
{
	while((*p) && (max--))
		MIAC_PrintASCII(*p++);
}

void MIAC_PrintASCII(MX_CHAR c)
{
	switch(c)
	{
	case '\n':	// 0x0a newline
		WG_CursorX = 0;
		if (++WG_CursorY >= WG_CHAR_ROWS)
		{
			WG_CursorY = 0;
		}
		break;
		
	case '\r':	// 0x0d carriage return
		WG_CursorX = 0;
		break;

	case '\f':	// 0x0c Form feed, new page
		MIAC_DisplayClear();
		break;

	default:
		if ((MX_UINT8)c >= WG_CHAR_COUNT)
		{
			switch (c)
			{
				case 0xB0:
				case 0xDF:
					c = 0x1F;	// re-map the Deg symbol
					break;
				case 0xC2:		// ignore esc
				default:		// or anything else
					return;
			}
		}
		// buffer boundary checks ...
		if (WG_CursorY >= WG_CHAR_ROWS) WG_CursorY = 0;
		if (WG_CursorX >= WG_CHAR_COLS) WG_CursorX = 0;
		//WG_CharBuffer[WG_CursorY][WG_CursorX] = c;
		MIAC_DrawGlyph(c, (WG_CursorX * WG_CHAR_WIDTH), (WG_CursorY * WG_CHAR_HEIGHT), 0);
		// move the cursor ...
		if (++WG_CursorX >= WG_CHAR_COLS)
		{
			WG_CursorX = 0;
			if (++WG_CursorY >= WG_CHAR_ROWS)
			{
				WG_CursorY = 0;
			}
		}
		break;
	}
}

void MIAC_DrawPixel(MX_UINT8 px, MX_UINT8 py, MX_UINT8 state)
{
	// state = 0 turns off the pixel, else turns on (white)
	MX_UINT8 BitRow = py + WG_ORIGIN_Y;
	MX_UINT8 BitCol = px + WG_ORIGIN_X;
	MX_UINT8 WordCol = BitCol / 16;
	MX_UINT8 BitShift = BitCol % 16;
	MX_UINT16 DisplayData = WG_ReadWordAt(WordCol, BitRow);

	if (state)
	{
		// draw the pixel
		DisplayData |= (0x8000 >> BitShift);
	}
	else
	{
		// delete the pixel
		DisplayData &= ~(0x8000 >> BitShift);
	}
	WG_WriteWordAt(DisplayData, WordCol, BitRow);	
}

void MIAC_DrawGlyph(MX_UINT8 glyph, MX_UINT8 px, MX_UINT8 py, MX_UINT8 mode)
{
	// MX_UINT8 glyph	character/glyph to draw
	// MX_UINT8 px		pixel column relative to the drawing origin (top left)
	// MX_UINT8 py		pixel row relative to the drawing origin (top left)
	// MX_UINT8 mode	0=opaque/cleared background, 1=transparent background
	// the display row for the first row of the glyph ...
	MX_UINT8 BitRowStart = py + WG_ORIGIN_Y;
	// the display column for the first col of the glyph
	MX_UINT8 BitColStart = px + WG_ORIGIN_X;
	// the display word row start ...
	MX_UINT8 WordCol = BitColStart / 16;
	// bit shift for mask and glyph row ...
	MX_UINT8 BitRemainder = BitColStart % 16;
	MX_SINT8 MaskShift = 16 - WG_CHAR_WIDTH - BitRemainder;
	
	MX_UINT8 y;
	MX_UINT16 GlyphRow;
	MX_UINT16 DisplayData;
	
	for (y = 0; y < WG_CHAR_HEIGHT; ++y)
	{
		GlyphRow = WG_CharMap[(glyph * WG_CHAR_HEIGHT) + y];
		
		if (MaskShift >= 0)
		{
			// glyph is fully contained within a single word
			DisplayData = WG_ReadWordAt(WordCol, BitRowStart + y);
			if (mode==0) DisplayData &= ~(WG_GLYPH_MASK << MaskShift);
			WG_WriteWordAt(DisplayData | (GlyphRow << MaskShift), WordCol, BitRowStart + y);
		}
		else
		{
			// glyph is not fully contained within a single word
			// do the first part
			DisplayData = WG_ReadWordAt(WordCol, BitRowStart + y);
			if (mode==0) DisplayData &= ~(WG_GLYPH_MASK >> (0-MaskShift));
			WG_WriteWordAt(DisplayData | (GlyphRow >> (0-MaskShift)), WordCol, BitRowStart + y);
			// now the second part in the next word
			DisplayData = WG_ReadWordAt(WordCol+1, BitRowStart + y);
			if (mode==0) DisplayData &= ~(WG_GLYPH_MASK << (16+MaskShift));
			WG_WriteWordAt(DisplayData | (GlyphRow << (16+MaskShift)), WordCol+1, BitRowStart + y);
		}
	}
}

#endif

void MIAC_DisplayLight(MX_UINT8 state)
{
	MIAC_LCD_BL_VAL_DDR(state);
}



MX_UINT8 MIAC_GetKeypad(void)
{
	MX_UINT8 sample = 0;
	MX_UINT8 strobe;

	MIAC_LCD_EN_CLR;
	MIAC_LCD_DB_IN_DDR;

	for (strobe=0; strobe<3; ++strobe)
	{
		switch(strobe)
		{
			case 0:
				// strobe 0, DB0 High
				MIAC_DB5_CLR_DDR;
				delay_us(10);
				sample = MIAC_LCD_DB_GET;
				MIAC_LCD_DB_IN_DDR;
				break;
			case 1:
				// strobe 1
				MIAC_DB4_CLR_DDR;
				delay_us(10);
				sample = MIAC_LCD_DB_GET;
				MIAC_LCD_DB_IN_DDR;
				break;
			case 2:
				// strobe 2
				MIAC_DB3_CLR_DDR;
				delay_us(10);
				sample = MIAC_LCD_DB_GET;
				MIAC_LCD_DB_IN_DDR;
				break;
		}
		if (!(sample & 0x01))
		{
			return (strobe * 3) + 0;
		}
		else if (!(sample & 0x02))
		{
			return (strobe * 3) + 1;
		}
		else if (!(sample & 0x04))
		{
			return (strobe * 3) + 2;
		}
	}
	return 255;
}



MX_UINT8 MIAC_InputAnalog(MX_UINT8 channel)
{
	return MIAC_InputAnalog_10bit(channel) >> 2;
}

MX_UINT16 MIAC_InputAnalog_10bit(MX_UINT8 channel)
{
/**
	MCP3008 channel numbers are 0-7
	MIAC numbering is 1-8
**/
	MX_UINT8 buffer[3];

	buffer[0] = 0x01;
	buffer[1] = 0x80 | ((channel-1) << 4);
	buffer[2] = 0;

	// CS1 for ADC
	MIAC_SPI0_Init(1, 0, 200);
	MIAC_SPI0_Transaction(buffer, sizeof(buffer));
	MIAC_SPI0_Unint();

	return ((buffer[1] << 8) | buffer[2]) & 0x3ff;
}


MX_UINT8 MIAC_InputDigital(MX_UINT8 channel)
{
	switch(channel)
	{
		case 1:		MIAC_I1_IN_DDR; return (MIAC_I1_GET)?0:1;
		case 2:		MIAC_I2_IN_DDR; return (MIAC_I2_GET)?0:1;
		default:	return ((MIAC_InputAnalog(channel) > 85)?1:0);
	}
}


void MIAC_OutputOn(MX_UINT8 channel)
{
	switch (channel)
	{
		case 1: MIAC_M1_SET_DDR; MIAC_MA_SET_DDR; break;
		case 2: MIAC_M1_SET_DDR; MIAC_MB_SET_DDR; break;
		case 3: MIAC_M2_SET_DDR; MIAC_MC_SET_DDR; break;
		case 4: MIAC_M2_SET_DDR; MIAC_MD_SET_DDR; break;
	}
}

void MIAC_OutputOff(MX_UINT8 channel)
{
	switch (channel)
	{
		case 1: MIAC_M1_SET_DDR; MIAC_MA_CLR_DDR; break;
		case 2: MIAC_M1_SET_DDR; MIAC_MB_CLR_DDR; break;
		case 3: MIAC_M2_SET_DDR; MIAC_MC_CLR_DDR; break;
		case 4: MIAC_M2_SET_DDR; MIAC_MD_CLR_DDR; break;
	}
}

void MIAC_RelayOn(MX_UINT8 channel)
{
	switch (channel)
	{
		case 1: MIAC_Q1_SET_DDR; break;
		case 2: MIAC_Q2_SET_DDR; break;
		case 3: MIAC_Q3_SET_DDR; break;
		case 4: MIAC_Q4_SET_DDR; break;
	}
}

void MIAC_RelayOff(MX_UINT8 channel)
{
	switch (channel)
	{
		case 1: MIAC_Q1_CLR_DDR; break;
		case 2: MIAC_Q2_CLR_DDR; break;
		case 3: MIAC_Q3_CLR_DDR; break;
		case 4: MIAC_Q4_CLR_DDR; break;
	}
}



