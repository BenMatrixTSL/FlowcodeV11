// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D53F5F6A18E6F66E466F9DB641FCB79B70BB4005A2994832514912D9FFFBF2A794722793EC01B70E81D7BC78C8BC1EA6289A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5922DC5C2A980B93B961C894EF698A54955F805799A3F3EF56DD799749DD15A73F78A3A64EFCBC2EED9B750499008A4F242AE82B0E7C2BDB3CFEDECD1168D9F678CA6E1567BF73C81F517D8A7D0F3363DF4596136F1D69FF9549D34A0D5AD11F357D5D2F126702E69C03532F721EC9A1CCFCA069B4ACA31A7FC0E9FB60DFEAB887A64FF5F89231504
// REVISION: 1.0
// GUID: 431DE424-5E8A-4A41-AF48-2301427A10D4
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series2\demo\HID\hid_task.h
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

