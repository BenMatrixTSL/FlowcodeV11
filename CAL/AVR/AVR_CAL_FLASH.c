// CRC: 77485F5F6A861F9125D47827B4DE492656C5431E478E8046055FD2257F64F1F367A9E646346A0E58656E0C7CA00928D09A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF55D613ED7F6545CA4799EB974F74D73E376E1F04D1E17580D88F6D6B8D9D7B44474FED728D2BE52C606252612538980CC769D847A405DF32C9BF8CA66268B7DC79E34A0A085169C269F78ABCCB04F8D351BB7874C60A8CA6C549D34A0D5AD11F33384CFA783C9FF6558F0484447B07C2C5F761D7152007F4B56E599B5AD11AA62EAC3685094CA720B
// REVISION: 1.0
// GUID: FAF6A2B8-4FE6-46E6-89E7-7CF9013FB09F
// DATE: 08\08\2022
// DIR: CAL\AVR\AVR_CAL_FLASH.c
/*********************************************************************
 *                  Flowcode CAL Flash File
 *
 * File: AVR_CAL_Flash.c
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
 * 200312 | BR | Created
 *
 *
 *
 */


#ifndef __PGMSPACE_H_
	#include <avr\pgmspace.h>
#endif


char ReadFlash(long address)
{
	char a;

// RAMPZ register defined for devices with program memory > 64K
#ifdef RAMPZ
	a = pgm_read_byte_far((uint32_t) address);
#else
	a = pgm_read_byte((uint16_t) address);
#endif

	return a;

}