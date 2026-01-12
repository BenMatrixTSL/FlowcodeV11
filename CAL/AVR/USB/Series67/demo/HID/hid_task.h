// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5E971021840B65CB4A3D8D01D6B7FD05CC0A69A6C412C648223269F0F0B0625236CDC77C2B84AABC5AC74B7B7B2E4E0489A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5DD33A64AB4430A11A57F050A50D6E7ED4F6FDA046F8A71935955490856F636983D9C265B90732CA78188B2EBCCB369B2DEA4F5D37FAB2AB5AFA83542AB630BED88E06E39FF8D3A71DD338B86915446650515AF603EB0F074549D34A0D5AD11F30532E3930B3717BF6AF6C1940427FF0B77595922DC7181A2B54CBE7FC75FC27ACB6057F59853FD1A
// REVISION: 1.0
// GUID: 1F1732CF-47F9-478A-91F7-9B80C1AC4D09
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series67\demo\HID\hid_task.h
/**
 * @file mouse_task.h,v
 *
 * Copyright (c) 2004 Atmel.
 *
 * Please read file license.txt for copyright notice.
 *
 * @brief This file contains the function declarations
 *
 * @version 1.2 at90usb162-2enum-mouse_ms-1_0_1 $Id: mouse_task.h,v 1.2 2006/12/12 13:52:18 arobert Exp $
 *
 * @todo
 * @bug
 */

#ifndef _MOUSE_TASK_H_
#define _MOUSE_TASK_H_

//_____ I N C L U D E S ____________________________________________________


#include "config.h"

//_____ M A C R O S ________________________________________________________


//_____ D E C L A R A T I O N S ____________________________________________

void hid_task_init(void);
U8 hid_get_data(U8* rxBuff);
void hid_send_data(U8* txBuff, U8 txCount);
void sof_action(void);

#endif /* _MOUSE_TASK_H_ */

