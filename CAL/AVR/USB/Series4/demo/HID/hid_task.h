// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D57DF507285C9C50725F499CC7EBAC12FBBB4005A2994832514912D9FFFBF2A794722793EC01B70E81D7BC78C8BC1EA6289A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF537C48CD3230EB642F64DE264C9180D3D68A320DBE15AF0A44014E52071B500B1A5D4141315D51BA9A8D0D66BD84B2257E3AF2665AB1479F64B99B6375449DB7438CED903B7BE875211D1F0D1E341E3B0232AE3563A2DB2E4549D34A0D5AD11F3D198A1B0DCA0D407BD65EB7613151A7B4F93C1ED5EB2B267C37F16299AE1E9D4E82474DD52B742AE
// REVISION: 1.0
// GUID: 49542092-E319-4DC9-BF03-120E735A2D78
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\demo\HID\hid_task.h
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

