// CRC: 77485F5F6A861F9125D47827B4DE4926DFA614687595C12C1B924E79694876561589FA81C8D553A0DE9612A14E45277A9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF58C13F38C209C2C05AB0F3077ABE0828A4A29112A64CAF0362DC883F08201AF33BB0C9C86AE30269478ED0B984E27EF7570AA965B9A21F2A733B167716980A95E53AA5EF09A94502A05D9DE72C9F437245D014FBCC70A0131549D34A0D5AD11F39BEFECD8B1B65CF60502D2405F2EBCB512B0E714A2F71111A8B2FE2536E6C50FEBD31FED13C8BAD2
// REVISION: 1.0
// GUID: 0FB3D63E-5EBD-408B-8C6E-02D2DD928D27
// DATE: 08\08\2022
// DIR: CAL\AVR\CAN\CAN_Defs.h
#ifndef CAN_Defs_h
#define CAN_Defs_h

	//Structure Declarations
	//enum is used to select an action for a specific message
	typedef enum {
	  CMD_TX,
	  CMD_TX_REMOTE,
	  CMD_RX,
	  CMD_ABORT
	} can_cmd_t;

	//defines a CAN identifier and allows to access it in mode standart, extended or throught a table.
	typedef union{
	  unsigned long ext;
	  unsigned int std;
	  char  tab[4];
	} can_id_t;

	//defines some specific information as rtr bit and ide bit.
	typedef struct{
	  char rtr : 1;
	  char ide : 1;
	  char dummy :6;
	} can_ctrl_t;

	//defines a specific action on CAN network.
	//handle: manage by the library.
	//cmd   : select the operation
	//id    : ID
	//dlc   : number of data bytes
	//pt_data: pointer on the table which contains the send / received data
	//status: manage by the library
	//ctrl : field rtr to signal a remote frame / field ide to signal a extended frame
	typedef  struct{
	  char      handle;
	  can_cmd_t  cmd;
	  can_id_t   id;
	  char      dlc;
	  char*    pt_data;
	  char      status;
	  can_ctrl_t ctrl;
	} st_cmd_t;


	typedef enum {
	  MOB_0, MOB_1, MOB_2, MOB_3, MOB_4, MOB_5, MOB_6, MOB_7,
	  MOB_8, MOB_9, MOB_10, MOB_11, MOB_12, MOB_13, MOB_14} can_mob_t;

#endif