// CRC: 77485F5F6A861F9125D47827B4DE492656C5431E478E8046055FD2257F64F1F31CCAA1F64DCE9D54FCE71B97CFC36836EAB9DC0344E07D5326A66CC0150DD556B6336C11BE63C7B23E6A7110B5081D39796EDD611F6757020C3CAEE8E7DA69877D10CA229E37F46DADF0FC1B997B2B80600A484E87124EFDDF4EEFC49008975E06EDD7F556BA2A16FD5CD77C83B4839FC5891A02EA1FE751F255713E6DAFDC07778A72FC7A789398F7647442321D543D756F2336BA56A874549D34A0D5AD11F3ACC022970339E6BBA1563AFB387129A30F0476C225B169360C9FBA1F01A7E45B08B65E7F68830DD9
// REVISION: 2.0
// GUID: 7DA56C99-21D4-46BB-A7AC-0B36153047ED
// DATE: 11\07\2025
// DIR: CAL\AVR\AVR_CAL_USB_Serial.c

/*********************************************************************
 *              Flowcode CAL USB Serial CDC Comms
 *
 * File: AVR_CAL_USB_Serial.c
 *
 * (c) 2025 Matrix TSL
 * http://www.matrixTSL.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
 * ?Company?) for its Flowcode graphical programming language is
 * intended and supplied to you, the Company?s customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
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
 * 100725 | BR | Created
 *
 */



#define MX_USB_SERIAL_ENUM_TOUTEN_X     	CAL_APPEND(MX_USB_SERIAL_ENUM_TOUTEN_, MX_USB_SERIAL_NUM)
#define MX_USB_SERIAL_ENUM_TOUT_X     		CAL_APPEND(MX_USB_SERIAL_ENUM_TOUT_, MX_USB_SERIAL_NUM)
#define MX_USB_SERIAL_ENUM_RETURN_X     	CAL_APPEND(MX_USB_SERIAL_ENUM_RETURN_, MX_USB_SERIAL_NUM)




 #include <config.h>
 #include <lib_mcu/usb/usb_drv.h>
 #include <modules\usb\device_chap9\usb_standard_request.h>
 #include <usb_specific_request.h>
 #include <uart_usb_lib.h>


 extern U8    rx_counter;
 extern U8    tx_counter;


 S_line_coding line_coding;
 S_line_status line_status;      // for detection of serial state input lines
 S_serial_state serial_state;    // for serial state output lines



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_Initialise_, ())
{
    usb_task_init();

	if (MX_USB_SERIAL_ENUM_TOUTEN_X)
	{
		//Wait for USB to startup and enumerate
		while(Is_device_enumerated() == 0 && FCL_DELAY_COUNTER < MX_USB_SERIAL_ENUM_TOUT_X)
		{
			usb_task();

			FCI_DELAYBYTE_MS(10);
			FCL_DELAY_COUNTER = FCL_DELAY_COUNTER + 1;
		}

		if (Is_device_enumerated())
		{
			uart_usb_init();
			return 0;
		}

		return 255;

	}
	else
	{
		while(Is_device_enumerated() == 0)
		{
			usb_task();
		}
		uart_usb_init();
		return 0;
	}
}


CALFUNCTION(MX_UINT16, FC_CAL_USB_Serial_ReadByte_, (MX_UINT8 timeout_ms))
{
	MX_UINT16 retval = 255;
	MX_UINT8 inner = 0;
	MX_UINT8 FCL_WAIT_FOREVER = 0;

	if (MX_USB_SERIAL_ENUM_RETURN_X)
		retval = 512;

	if (timeout_ms == 0)
	{
		timeout_ms = 1;
		inner = 98;
	}

    MX_UINT8 rx_rdy = 0;

	if(timeout_ms == 255)
		FCL_WAIT_FOREVER = 1;

	while((rx_rdy == 0) && (timeout_ms > 0))
	{
		rx_rdy = uart_usb_test_hit();

        if(rx_rdy)
            FCR_RETVAL = uart_usb_getchar();

		if ((FCL_WAIT_FOREVER == 0) && (rx_rdy == 0))
		{
			inner++;
			delay_us(10);
			if (inner == 100)
			{
				inner = 0;
				timeout_ms--;
			}
		}
	}

	return retval;
}



CALFUNCTION(MX_UINT16, FC_CAL_USB_Serial_ReadString_, (MX_CHAR *FCR_RETVAL, MX_UINT16 FCRsz_RETVAL, MX_UINT8 timeout_ms, MX_UINT8 FCL_LENGTH))
{
	MX_UINT8 FCL_WAIT_FOREVER = 0;
	MX_UINT8 Rx_Length = 0;
	MX_UINT8 inner = 0;

	if (timeout_ms == 0)
		timeout_ms = 1;

	if(timeout_ms == 255)
		FCL_WAIT_FOREVER = 1;

	while (timeout_ms || FCL_WAIT_FOREVER)
	{
        if(uart_usb_test_hit())
        {
            FCL_WAIT_FOREVER = 0;
            while(uart_usb_test_hit() && (Rx_Length <= FCL_LENGTH))
            {
                FCR_RETVAL[Rx_Length++] = uart_usb_getchar();
            }
        }
        else
        {
			inner++;
			delay_us(10);
			if (inner == 100)
			{
				inner = 0;
				timeout_ms--;
			}
        }
    }

	if (Rx_Length < FCL_LENGTH)
	    FCR_RETVAL[Rx_Length] = 0;
}


CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendByte_, (MX_UINT8 FCL_DATA))
{
	MX_UINT16 FCL_TIMEOUT = (0x0);

	if(!Is_device_enumerated())
	{
		return(2);
	}
	else
	{
		Usb_select_endpoint(TX_EP);

		while((uart_usb_tx_ready() == 0) && (FCL_TIMEOUT < 32000))
			FCL_TIMEOUT++;

		if(FCL_TIMEOUT == 32000)
		{
			return(1);
		}
		else
		{
			uart_usb_putchar(FCL_DATA);
			Usb_ack_in_ready();
		}
	}

	return (0);
}



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendByteArray_, (MX_UINT8 *FCL_DATA, MX_UINT16 FCLsz_DATA, MX_UINT8 FCL_NUMBYTES))
{
	MX_UINT16 FCL_TIMEOUT = (0x0);
	MX_UINT8 n;

	if(!Is_device_enumerated())
	{
		return(2);
	}
	else
	{
		for(n = 0; (n < FCL_NUMBYTES); n++)
		{
			FCL_TIMEOUT = 0;

			while((!uart_usb_tx_ready()) && (FCL_TIMEOUT < 32000))
				FCL_TIMEOUT++;

			if(FCL_TIMEOUT == 32000)
			{
				return(1);
			}
			else
			{
				uart_usb_putchar(FCL_DATA[n]);
				Usb_ack_in_ready();
			}
		}
	}

	return (0);
}



CALFUNCTION(MX_UINT8, FC_CAL_USB_Serial_SendString_, (MX_CHAR *FCL_DATA, MX_UINT16 FCLsz_DATA))
{
  	MX_UINT16 FCL_TIMEOUT = (0x0);
  	MX_UINT8 FCL_LENGTH;
	MX_UINT8 n;

	FCL_LENGTH = FCI_GETLENGTH(FCL_DATA, FCLsz_DATA);

	if(!Is_device_enumerated())
	{
		return(2);
	}
	else
	{
		for(n = 0; (FCL_DATA[n] != 0) && (n < FCL_LENGTH); n++)
		{
			FCL_TIMEOUT = 0;

			while((!uart_usb_tx_ready()) && (FCL_TIMEOUT < 32000))
				FCL_TIMEOUT++;

			if(FCL_TIMEOUT == 32000)
			{
				return(1);
			}
			else
			{
				uart_usb_putchar(FCL_DATA[n]);
				Usb_ack_in_ready();
			}
		}
	}

    return (0);
}

