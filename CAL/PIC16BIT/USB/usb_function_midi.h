// CRC: 5D982BB222882C54AB4AFF20A1590FC4128F294B41FC96FD138D7F694DC5EBF584323D909AEB4215CE2C0EE20719F92C4A66C83F0D9BC1A053B5E817FDC1785295BEF25A0F53B4129DD610807A36E7F59A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF577A9B4E21C4E0D731BA1348745A1062C70B4A6217AE3EB3E00DCB64A5B1C96BCDD5B82DEF58F66115FEB8678EFA396C51AB850AA1B6369AB816735FC3ADA047F4AB4B3DE306A7FC83B76E09FC1FFE0E66AFED223F004AFE0549D34A0D5AD11F386EB34F7FA73AFA9A97CE7CA470F141092CCB81C8B9F597A3B2CD482BC0EE54D2A52B2CE0373A37B
// REVISION: 1.0
// GUID: 41E8D00A-4614-485F-A9B7-DA4CB6CD1071
// DATE: 08\08\2022
// DIR: CAL\PIC16BIT\USB\usb_function_midi.h
/******************************************************************************

  USB Audio - MIDI device (Header File)

Summary:
    This file defines data types, constants, and macros that are needed by
    the MIDI USB device example

Description:
    This file defines data types, constants, and macros that are needed by
    the MIDI USB device example

    This file is located in the "\<Install Directory\>\\Microchip\\Include\\USB"
    directory.
    
    When including this file in a new project, this file can either be
    referenced from the directory in which it was installed or copied
    directly into the user application folder. If the first method is
    chosen to keep the file located in the folder in which it is installed
    then include paths need to be added so that the library and the
    application both know where to reference each others files. If the
    application folder is located in the same folder as the Microchip
    folder (like the current demo folders), then the following include
    paths need to be added to the application's project:
     
    ..\\..\\Microchip\\Include
    
    .
    
    If a different directory structure is used, modify the paths as
    required. An example using absolute paths instead of relative paths
    would be the following:
    
    C:\\Microchip Solutions\\Microchip\\Include
    
    C:\\Microchip Solutions\\My Demo Application 
*******************************************************************************/
//DOM-IGNORE-BEGIN
/*******************************************************************************

* FileName:        usb_function_midi.h
* Dependencies:    See included files, below.
* Processor:       PIC18/PIC24/PIC32MX microcontrollers with USB module
* Compiler:        C18 v3.13+/C30 v2.01+/C32 v0.00.18+
* Company:         Microchip Technology, Inc.

Software License Agreement

The software supplied herewith by Microchip Technology Incorporated
(the “Company”) for its PICmicro® Microcontroller is intended and
supplied to you, the Company’s customer, for use solely and
exclusively on Microchip PICmicro Microcontroller products. The
software is owned by the Company and/or its supplier, and is
protected under applicable copyright laws. All rights are reserved.
Any use in violation of the foregoing restrictions may subject the
user to criminal sanctions under applicable laws, as well as to
civil liability for the breach of the terms and conditions of this
license.

THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

*******************************************************************************/
//DOM-IGNORE-END
typedef union
{
    DWORD Val;
    BYTE v[4];
    union
    {
        struct
        {
            BYTE CIN :4;
            BYTE CN  :4;
            BYTE MIDI_0;
            BYTE MIDI_1;
            BYTE MIDI_2;
        }; 
        struct
        {
            BYTE CodeIndexNumber :4;
            BYTE CableNumber     :4;
            BYTE DATA_0;
            BYTE DATA_1;
            BYTE DATA_2;    
        };
    };
} USB_AUDIO_MIDI_EVENT_PACKET, *P_USB_AUDIO_MIDI_EVENT_PACKET;

/* Code Index Number (CIN) values */
/*   Table 4-1 of midi10.pdf      */
#define MIDI_CIN_MISC_FUNCTION_RESERVED         0x0
#define MIDI_CIN_CABLE_EVENTS_RESERVED          0x1
#define MIDI_CIN_2_BYTE_MESSAGE                 0x2
#define MIDI_CIN_MTC                            0x2
#define MIDI_CIN_SONG_SELECT                    0x2
#define MIDI_CIN_3_BYTE_MESSAGE                 0x3
#define MIDI_CIN_SSP                            0x3
#define MIDI_CIN_SYSEX_START                    0x4
#define MIDI_CIN_SYSEX_CONTINUE                 0x4
#define MIDI_CIN_1_BYTE_MESSAGE                 0x5
#define MIDI_CIN_SYSEX_ENDS_1                   0x5
#define MIDI_CIN_SYSEX_ENDS_2                   0x6
#define MIDI_CIN_SYSEX_ENDS_3                   0x7
#define MIDI_CIN_NOTE_OFF                       0x8
#define MIDI_CIN_NOTE_ON                        0x9
#define MIDI_CIN_POLY_KEY_PRESS                 0xA
#define MIDI_CIN_CONTROL_CHANGE                 0xB
#define MIDI_CIN_PROGRAM_CHANGE                 0xC
#define MIDI_CIN_CHANNEL_PREASURE               0xD
#define MIDI_CIN_PITCH_BEND_CHANGE              0xE
#define MIDI_CIN_SINGLE_BYTE                    0xF
