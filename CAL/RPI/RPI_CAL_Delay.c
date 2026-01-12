// CRC: 34358081B117C27F7D8358E612878F8E5F343B66182D417818220CB9C07676CF12C52A9A458B17900EC8DB8A0EB203079A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF51FE59CFADAB1B789521F81E75DB234A2D9D87FE0F2D678C28916ED9E802D901EAC27F76DFF9E12A36DE417B92F9065B0F31BE4A919BD8D2AD749B7A2C47E5E794AFA969CF4A96826B52022D4A1A3F85455D07B5E07B4F4E2549D34A0D5AD11F36BF57CAA50631DC2F1B7B81D96C8FCF3D93762E272FB7878CC6735C2880B0855018D7FE4AA495AC4
// REVISION: 1.0
// GUID: 18EA2AEB-97EE-429D-A88D-90C1B2C3A81E
// DATE: 08\08\2022
// DIR: CAL\RPI\RPI_CAL_Delay.c
/*********************************************************************
 *                  Flowcode CAL Delays File
 *
 * File: RPI_CAL_Delay.c
 *
 * (c) 2011-2018 Matrix TSL
 * http://www.matrixTSL.com
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
 * 191217 | LM | Created
 *
 */

#define FCI_DELAYBYTE_US(count)    mx_delay_u((MX_UINT32)(count))
#define FCI_DELAYINT_US(count)     mx_delay_u((MX_UINT32)(count))
#define FCI_DELAYBYTE_MS(count)    mx_delay_m((MX_UINT32)(count))
#define FCI_DELAYINT_MS(count)     mx_delay_m((MX_UINT32)(count))
#define FCI_DELAYBYTE_S(count)     mx_delay_s((MX_UINT32)(count))
#define FCI_DELAYINT_S(count)      mx_delay_s((MX_UINT32)(count))

void mx_delay_u(MX_UINT32 delay)
{
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = delay * 1000;
	nanosleep(&ts, 0);
}

void mx_delay_m(MX_UINT32 delay)
{
	struct timespec ts;
	ts.tv_sec = delay / 1000;
	ts.tv_nsec = (delay % 1000) * 1000000;
	nanosleep(&ts, 0);
}

void mx_delay_s(MX_UINT32 delay)
{
	struct timespec ts;
	ts.tv_sec = delay;
	ts.tv_nsec = 0;
	nanosleep(&ts, 0);
}


