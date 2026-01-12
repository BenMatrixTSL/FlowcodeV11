// CRC: 20C35A1E87BE6D5C727502197CD041A7B491451D5915BA6B046B33DA966607B8AD3DD26F1F43761446ED8FD3A619351AFB40D73136BE14A70084AEB8CDF9200F9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF59515584C55864406A16AAEEE4B6FCC873E3AE011E9C4A1DFBF269AC3D2155AFC3B6B2AAF32C62294394AF3AD28E3377403B1078396CB5A6D8C6B07B8EFFFD990077BFF8CBE63413390F5BA75F4CF7C166FAD7B94FA35E1A3549D34A0D5AD11F37CB0FBADD2A74A54548155D77EDB08DF3085B363AD7B4E748D531F270564038E47F47A97AF8C57FD
// REVISION: 1.0
// GUID: CE21AC68-929A-4062-9797-AC658B6520DF
// DATE: 08\08\2022
// DIR: CAL\PIC\PIC_CAL_COMPARATOR.c
/*********************************************************************
 *                Flowcode CAL COMPARATOR File
 *
 * File: PIC_CAL_COMPARATOR.c
 *
 * (c) 2017 Matrix Multimedia Ltd.
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
 * 220217 | BR | Created
 */


#define MX_COMP_CHANNEL_X		CAL_APPEND(MX_DAC_CHANNEL_, MX_DAC_NUM)
#define MX_COMP_VREF_X			CAL_APPEND(MX_DAC_VREF_, MX_DAC_NUM)


CALFUNCTION(void, FC_CAL_COMP_Enable_, (void));
CALFUNCTION(void, FC_CAL_COMP_Disable_, (void));


// COMPARATOR Type 1 Supported Devices ************************************************************
// 16F188xx / 16F194x
// Up to 4 channels
// *******************************************************************************************/

#ifdef MX_COMP_TYPE_1

#endif
