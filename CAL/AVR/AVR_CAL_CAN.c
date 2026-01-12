// CRC: 77485F5F6A861F9125D47827B4DE492656C5431E478E8046055FD2257F64F1F332535F4E381B52A002F30B4650F87BFB9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF555BE9FD94993FB623A5210A2A95D2D3C9786782D556B2E9C4DD11825D392B7B83B5FC4F464705FE7A26B022F618DA608B38DCB35DD398B4DF13A980CC36579E54C179F3F5646A6A7DF5A51F7F8F2919D6471C7A6431958E6549D34A0D5AD11F308F36D3E182AFFAA5720D34FE3E0E71D2BABD593DC4C2D043D04CF7CD5577C5FE9D77FAA9053C2CE
// REVISION: 1.0
// GUID: FB3D235C-A9C7-48CD-8B25-04A6E69F5A6A
// DATE: 08\08\2022
// DIR: CAL\AVR\AVR_CAL_CAN.c
/*********************************************************************
 *                  Flowcode CAL CAN File
 *
 * File: AVR_CAL_CAN.c
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
 * 230911 | BR | Created
 * 020312 | BR | Updated to v5.1 CAL Schema
 * 020413 | BR | Fixed a number of simple compile bugs - where did these come from?
 * 030713 | LM | Standard API calls
 * 120913 | LM | Fixed some missing defs
 */


#ifndef MX_ECAN
	#error "Internal CAN not supported on this device"
#else

#define MX_CAN_CHANNEL_X		CAL_APPEND(MX_CAN_CHANNEL_, MX_CAN_NUM)
#define MX_CAN_BAUD1_X			CAL_APPEND(MX_CAN_BAUD1_, MX_CAN_NUM)
#define MX_CAN_BAUD2_X			CAL_APPEND(MX_CAN_BAUD2_, MX_CAN_NUM)
#define MX_CAN_BAUD3_X			CAL_APPEND(MX_CAN_BAUD3_, MX_CAN_NUM)


//Internal CAN Library Defines
#include "CAN\CAN_compiler.h"
#include "CAN\CAN_Defs.h"
//#include "CAN\CAN_mcu.h"


#define    DLC_msk 0x0F
#define    ENA      1
#define    CONMOB   6
#define    CONMOB_msk 0xC0


//Internal CAN Library Functions
void Can_clear_all_MOB (void);
char Can_get_MOB_free (void);
char Can_get_MOB_status (void);
void Can_get_data (char * pt_data);
void can_init (void);
char can_cmd (st_cmd_t* cmd);
char can_getstatus (st_cmd_t* cmd);

CALFUNCTION(void, FC_CAL_Internal_CAN_Init_, (void));
CALFUNCTION(void, FC_CAL_Internal_CAN_Uninit_, (void));
CALFUNCTION(void, FC_CAL_Internal_CAN_SendBuffer_, (MX_UINT8 buffer));
CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_CheckRx_, (MX_UINT8 buffer));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxData_, (MX_UINT8 buffer, MX_UINT8 data_cnt, MX_UINT8 d0, MX_UINT8 d1, MX_UINT8 d2, MX_UINT8 d3, MX_UINT8 d4, MX_UINT8 d5, MX_UINT8 d6, MX_UINT8 d7));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdentStd_, (MX_UINT8 buffer, MX_UINT8 hi, MX_UINT8 lo));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdentExd_, (MX_UINT8 buffer, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilterStd_, (MX_UINT8 filter, MX_UINT8 hi, MX_UINT8 lo));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilterExd_, (MX_UINT8 filter, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskStd_, (MX_UINT8 filter, MX_UINT8 hi, MX_UINT8 lo));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskExd_, (MX_UINT8 filter, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0));

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMask_, (MX_UINT8 mask, MX_UINT32 id));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilter_, (MX_UINT8 filter, MX_UINT32 id));
CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdent_, (MX_UINT8 buffer, MX_UINT32 id));
CALFUNCTION(MX_UINT32, FC_CAL_Internal_CAN_GetRxIdent_, (MX_UINT8 buffer));
CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxDataCount_, (MX_UINT8 buffer));
CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxData_, (MX_UINT8 buffer, MX_UINT8 index));

//Global variables
st_cmd_t rx_msg;
st_cmd_t tx_msg;
char tx_buffer[8];
char rx_buffer[8];

MX_UINT8 CAN_MSG_DLC;
MX_UINT8 CAN_MSG_DATA[8];

MX_UINT16 CAN_MSG_ID;

//Constant Declarations
#define CAN_CMD_REFUSED  			0xFF		//return value for the function can_cmd
#define CAN_CMD_ACCEPTED 			0x00		//return value for the function can_cmd
#define CAN_STATUS_COMPLETED     	0x00		//return value for the function can_getstatus
#define CAN_STATUS_NOT_COMPLETED 	0x01		//return value for the function can_getstatus
#define CAN_STATUS_DISABLED      	0x02		//return value for the function can_getstatus
#define NB_MOB      				15
#define NB_DATA_MAX 				8
#define LAST_MOB_NB 				14
#define NO_MOB 						0xFF
#define CH_TxENA   					1
#define CH_RxENA   					2
#define CH_RxBENA  					3
#define STATUS_MOB_USED      		0x01
#define STATUS_MOB_AVAILABLE 		0x00

//Constants returned by the function CAN_get_MOb_status
#define MOB_TX_COMPLETED    0x00
#define MOB_RX_COMPLETED    0x01
#define MOB_NOT_COMPLETED   0x02
#define MOB_DISABLE         0xFF

//CAN Enable function declaration
#define Can_enable()    { CANGCON |= (1<<ENA); }
#define Can_disable()    { CANGCON &= ~(1<<ENA); }
#define Can_set_MOB(mob) (CANPAGE = (mob << 4))
#define Can_clear_MOB()  {CANSTMOB = 0x00; CANCDMOB = 0x00; CANIDM1=0x00; \
                          CANIDM2=0x00; CANIDM3=0x00; CANIDM4=0x00; CANIDT4 = 0x00;}
#define Can_set_dlc(dlc) {CANCDMOB|=dlc;}		//MOB configuration

//Identifier definition
#define CAN_SET_STD_ID_10_4(identifier) (((*((char *)(&identifier)+1))<<5)+((*(char *)(&identifier))>>3))
#define CAN_SET_STD_ID_3_0(identifier)  ((*(char *)(&identifier))<<5)
#define Can_set_std_id(identifier) {\
        CANIDT1 = CAN_SET_STD_ID_10_4 (identifier);\
        CANIDT2 = CAN_SET_STD_ID_3_0  (identifier);}
#define Can_set_std_remote_id(identifier) {\
        CANIDT1 = CAN_SET_STD_ID_10_4 (identifier);\
        CANIDT2 = CAN_SET_STD_ID_3_0  (identifier);\
        CANIDT4 = (1<<RTRTAG);}
#define CAN_SET_EXT_ID_28_21(identifier) (((*((char *)(&identifier)+3))<<3)+((*((char *)(&identifier)+2))>>5))
#define CAN_SET_EXT_ID_20_13(identifier) (((*((char *)(&identifier)+2))<<3)+((*((char *)(&identifier)+1))>>5))
#define CAN_SET_EXT_ID_12_5(identifier)  (((*((char *)(&identifier)+1))<<3)+((* (char *)(&identifier)   )>>5))
#define CAN_SET_EXT_ID_4_0(identifier)    ((* (char *)(&identifier)   )<<3)
#define Can_set_ext_id(identifier) {\
        CANIDT1 = CAN_SET_EXT_ID_28_21 (identifier);\
        CANIDT2 = CAN_SET_EXT_ID_20_13 (identifier);\
        CANIDT3 = CAN_SET_EXT_ID_12_5  (identifier);\
        CANIDT4 = CAN_SET_EXT_ID_4_0   (identifier);\
        CANCDMOB |= (1<<IDE); }
#define Can_set_ext_remote_id(identifier) {\
        CANIDT1 = CAN_SET_EXT_ID_28_21 (identifier);\
        CANIDT2 = CAN_SET_EXT_ID_20_13 (identifier);\
        CANIDT3 = CAN_SET_EXT_ID_12_5  (identifier);\
        CANIDT4 = CAN_SET_EXT_ID_4_0   (identifier);\
        CANCDMOB |= (1<<IDE); \
        CANIDT4 |= (1<<RTRTAG);}
#define Can_get_ext_id(identifier){     \
        *((char *)(&identifier)+3) = CANIDT1>>3;   \
        *((char *)(&identifier)+2) = (CANIDT2>>3)+(CANIDT1<<5);   \
        *((char *)(&identifier)+1) = (CANIDT3>>3)+(CANIDT2<<5);   \
        *((char *)(&identifier))   = (CANIDT4>>3)+(CANIDT3<<5);  }
#define Can_get_std_id(identifier){  \
        *((char *)(&identifier)+1) = CANIDT1>>5; \
        *((char *)(&identifier)  ) = (CANIDT2>>5)+(CANIDT1<<3); }
#define DISABLE_CHANNEL        ( CANCDMOB &= (~CONMOB_msk) )
#define Can_config_tx()      { CANCDMOB |=  (CH_TxENA  << CONMOB); }
#define Can_config_rx()      { DISABLE_CHANNEL ; CANCDMOB |=  (CH_RxENA  << CONMOB); }
#define Can_config_rxbuffer() { DISABLE_CHANNEL ; CANCDMOB |=  (CH_RxBENA << CONMOB); }

#define Can_MOB_abort()   {CANCDMOB &= (~CONMOB_msk);}
#define Can_get_dlc()     (CANCDMOB & DLC_msk)
#define Can_get_ide()     (CANCDMOB & (1<<IDE))
#define Can_get_rtr()     ((CANIDT4 & (1<<RTRTAG))>>RTRTAG)

//Internal CAN Library Functions

/* FUNCTION_NAME: Can_clear_all_MOB
 * PURPOSE: This function clears the Mailbox content.*/
void Can_clear_all_MOB (void)
{
  char num_mob, num_data;

  for (num_mob = 0; num_mob < NB_MOB; num_mob++)
  {
    CANPAGE  = (num_mob << 4);
    CANSTMOB = 0;
    CANCDMOB = 0;
    CANIDT4  = 0;
    CANIDT3  = 0;
    CANIDT2  = 0;
    CANIDT1  = 0;
    CANIDM4  = 0;
    CANIDM3  = 0;
    CANIDM2  = 0;
    CANIDM1  = 0;
    for (num_data = 0; num_data < NB_DATA_MAX; num_data++)
    {
      CANMSG = 0;
    }
  }
}


/* FUNCTION_NAME: Can_get_MOB_free
 * return:   handle of MOb
 * PURPOSE: This function return the number of the first MOb available
 * or 0xFF if no MOb available	*/
char Can_get_MOB_free (void)
{
  char num_MOB, Save_page;

  Save_page = CANPAGE;
  for (num_MOB = 0; num_MOB < NB_MOB; num_MOB++)
  {
    Can_set_MOB(num_MOB);
    if ((CANCDMOB&0xC0) == 0x00) // Disable configuration
    {
      CANPAGE = Save_page;
      return (num_MOB);
    }
  }
  CANPAGE = Save_page;
  return (NO_MOB);
}


/* NAME: Can_get_MOB_status
 * return: mob_status : MOB_COMPLETED | MOB_NOT_COMPLETED | MOB_DISABLE
 * PURPOSE: This function return information MOB completed its job
 * (MOB_COMPLETED) if one of the RXOK or TXOK Flag is set or MOB not completed
 * its job (MOB_NOT_COMPLETED) if no RXok and TXOK flags are set.
 * Previously, this function check if the MOb is configured or not.
 * In the case of the MOB is not configured, the function return MOB_DISABLE. */
char Can_get_MOB_status (void)
{
  if (CANSTMOB&(1<<TXOK))     {return(MOB_TX_COMPLETED);}
  if (CANSTMOB&(1<<RXOK))     {return(MOB_RX_COMPLETED);}
  /* test if mob enabled */
  if ((CANCDMOB&0xC0) == 0x00){return(MOB_DISABLE);}
  return(MOB_NOT_COMPLETED);
}


/* FUNCTION_NAME: Can_get_data
 * PARAMS:   address pointer to data array
 * PURPOSE: This function copy the data from the selected MOb to the address
 * passed in parameter.  */
void Can_get_data (char * pt_data)
{
  char nb_data;

  for (nb_data = 0; nb_data <(CANCDMOB&DLC_msk); nb_data++)
  {
    *(pt_data + nb_data) = CANMSG;
  }
}



//Baud rate of 125kbs - Default CAN E-block compatible baud rate

#if F_CPU == 4000000UL			//4MHz Operation
    #define CONF_CANBT1  0x02
    #define CONF_CANBT2  0x0C
    #define CONF_CANBT3  0x37
#endif
#if F_CPU == 6000000UL			//6MHz Operation
    #define CONF_CANBT1  0x04
    #define CONF_CANBT2  0x0C
    #define CONF_CANBT3  0x37
#endif
#if F_CPU == 8000000UL			//8MHz Operation
    #define CONF_CANBT1  0x06
    #define CONF_CANBT2  0x0C
    #define CONF_CANBT3  0x37
#endif
#if F_CPU == 12000000UL			//12MHz Operation
    #define CONF_CANBT1  0x0A
    #define CONF_CANBT2  0x0C
    #define CONF_CANBT3  0x37
#endif
#if F_CPU == 16000000UL			//16MHz Operation
    #define CONF_CANBT1  0x0E
    #define CONF_CANBT2  0x0C
    #define CONF_CANBT3  0x37
#endif
#if F_CPU == 18000000UL			//18MHz Operation - Guessed value!!
    #define CONF_CANBT1  0x10
    #define CONF_CANBT2  0x0C
    #define CONF_CANBT3  0x37
#endif
#if F_CPU == 20000000UL			//20MHz Operation - Guessed value!!
    #define CONF_CANBT1  0x12
    #define CONF_CANBT2  0x0C
    #define CONF_CANBT3  0x37
#endif
#ifndef CONF_CANBT1
  #error the baud values relative to this clock speed have not been specified
#endif



/* FUNCTION_NAME: can_init
 * PURPOSE: Sets up the CAN boad rate and sets the CAN driver running */
void can_init (void)
{
  CANBT1 = CONF_CANBT1;
  CANBT2 = CONF_CANBT2;
  CANBT3 = CONF_CANBT3;

  Can_clear_all_MOB();
  Can_enable();
}




/* FUNCTION_NAME: can_read/write command
 * PARAMS:   Mailbox st_cmd_t
 * return: command_status : CAN_CMD_REFUSED | CAN_CMD_ACCEPTED
 * PURPOSE: Reads or Writes a CAN packet via a mailbox */
char can_cmd (st_cmd_t* cmd)
{
  char mob_handle, cpt;

  if (cmd->cmd == CMD_ABORT)
  {
    if (cmd->status!= STATUS_MOB_AVAILABLE)
    {
      Can_set_MOB(cmd->handle);
      Can_MOB_abort();
      cmd->handle = 0;
      cmd->status = STATUS_MOB_AVAILABLE;
    }
  }
  else
  {
    mob_handle = Can_get_MOB_free();
    cmd->status = STATUS_MOB_USED;

    if (mob_handle!= NO_MOB)
    {
      cmd->handle = mob_handle;
      Can_set_MOB(mob_handle);
      Can_clear_MOB();
      switch (cmd->cmd){
        case CMD_TX:
          if (cmd->ctrl.ide){ Can_set_ext_id (cmd->id.ext);}
          else               { Can_set_std_id(cmd->id.std);}
          for (cpt=0;cpt<cmd->dlc;cpt++) CANMSG = *(cmd->pt_data + cpt);
          Can_set_dlc(cmd->dlc);
          Can_config_tx();
          break;

        case CMD_TX_REMOTE:
          if (cmd->ctrl.ide){ Can_set_ext_remote_id (cmd->id.ext);}
          else               { Can_set_std_remote_id(cmd->id.std);}
          Can_set_dlc(cmd->dlc);
          Can_config_tx();
          break;

        case CMD_RX:
          Can_config_rx();
          break;

        default:
           cmd->status = STATUS_MOB_AVAILABLE;
         break;
      }
    }else {return CAN_CMD_REFUSED;}
  }
  return CAN_CMD_ACCEPTED;
}



/* FUNCTION_NAME: can_getstatus
 * PARAMS:   Mailbox st_cmd_t
 * return: mailbox_status : CAN_STATUS_COMPLETED | CAN_STATUS_DISABLED | status
 * PURPOSE: Checks the status of a mailbox */
char can_getstatus (st_cmd_t* cmd)
{
  char status;

  if (cmd->status == STATUS_MOB_AVAILABLE) {return CAN_STATUS_DISABLED;}
  Can_set_MOB(cmd->handle);
  status = Can_get_MOB_status();
  if (status == MOB_RX_COMPLETED)
  {
    cmd->status = 0;
    cmd->dlc = Can_get_dlc();
    Can_get_data(cmd->pt_data);///,0);
    cmd->ctrl.rtr = Can_get_rtr();

    if (Can_get_ide()) // if extended frame
    {
      cmd->ctrl.ide = 1; // extended frame
      Can_get_ext_id(cmd->id.ext);
    }
    else // else standard frame
    {
      cmd->ctrl.ide = 0;
      Can_get_std_id(cmd->id.std);
    }
    Can_MOB_abort(); // freed the MOB
    return CAN_STATUS_COMPLETED;

  }else if (status == MOB_TX_COMPLETED)
  {
    cmd->status = 0;
    Can_MOB_abort(); // freed the MOB
    return CAN_STATUS_COMPLETED;
  }

  return (status);
}


//CAL Functions

CALFUNCTION(void, FC_CAL_Internal_CAN_Init_, (void))
{
  	#if (MX_CAN_CHANNEL_X == 1)
		rx_msg.pt_data = &rx_buffer[0];
		rx_msg.status = 0;
		rx_msg.handle = 0;

		tx_msg.pt_data = &tx_buffer[0];
		tx_msg.status = 0;
		tx_msg.handle = 0;

		can_init();
  	#endif

  	#if (MX_CAN_CHANNEL_X == 2)
		#error "8-Bit AVRs only ever have 1 CAN channel..... For now";
  	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_Uninit_, (void))
{
	#if (MX_CAN_CHANNEL_X == 1)
		Can_disable();
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SendBuffer_, (MX_UINT8 buffer))
{
	#if (MX_CAN_CHANNEL_X == 1)
		MX_UINT8 retry = 255;		//Specifies number of retries
		MX_UINT16 retry2 = 255;

		tx_msg.cmd = CMD_TX;

		while (retry)
		{
			if( can_cmd(&tx_msg) == CAN_CMD_ACCEPTED );
			{
				while( can_getstatus(&tx_msg) != CAN_STATUS_COMPLETED)
				{
					retry2 = retry2 - 1;
					delay_us(100);			//0.0001 * 256 = 25.6ms
					if (retry2 == 0)
						return;// 1;			//Completed Failed
				}
				return;// 0;					//Send completed ok
			}
			retry = retry - 1;
		}
		//return 1;					//Completed Failed
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_CheckRx_, (MX_UINT8 buffer))
{
	#if (MX_CAN_CHANNEL_X == 1)
		static MX_UINT8 command_sent = 0;
		MX_UINT8 i;

		rx_msg.cmd = CMD_RX;		//Receive Mode

		if(command_sent == 0)
		{
			if( can_cmd(&rx_msg) == CAN_CMD_ACCEPTED )
			{
				command_sent = 1;
			}
		}

		if(command_sent == 1)
		{
			if( can_getstatus(&rx_msg) == CAN_STATUS_COMPLETED )
			{
				command_sent = 0;
				CAN_MSG_ID = rx_msg.id.std;

				//CAN_MSG_ID[0] = (rx_msg.id.std >> 8) & 0xFF;	//Copy Std Hi Byte
				//CAN_MSG_ID[1] = rx_msg.id.std & 0xFF;			//Copy Std Lo Byte
				CAN_MSG_DLC = rx_msg.dlc;						//Copy number of data bytes

				for (i=0; i<CAN_MSG_DLC; i++)					//Copy data bytes to Flowcode Buffer
					CAN_MSG_DATA[i] = rx_buffer[i];

				return 1;
			}
		}
		return 0;
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxData_, (MX_UINT8 buffer, MX_UINT8 data_cnt, MX_UINT8 d0, MX_UINT8 d1, MX_UINT8 d2, MX_UINT8 d3, MX_UINT8 d4, MX_UINT8 d5, MX_UINT8 d6, MX_UINT8 d7))
{
	#if (MX_CAN_CHANNEL_X == 1)
		if (data_cnt > 8)
		   return;

		tx_msg.dlc = data_cnt;

		if (data_cnt > 0)
		{
		   tx_buffer[0] = d0;
		   if (data_cnt > 1)
		   {
			   tx_buffer[1] = d1;
			   if (data_cnt > 2)
			   {
				   tx_buffer[2] = d2;
				   if (data_cnt > 3)
				   {
					   tx_buffer[3] = d3;
					   if (data_cnt > 4)
					   {
						   tx_buffer[4] = d4;
						   if (data_cnt > 5)
						   {
							   tx_buffer[5] = d5;
							   if (data_cnt > 6)
							   {
								   tx_buffer[6] = d6;
								   if (data_cnt > 7)
								   {
									   tx_buffer[7] = d7;
								   }
							   }
						   }
					   }
				   }
			   }
		   }
		}
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdentStd_, (MX_UINT8 buffer, MX_UINT8 hi, MX_UINT8 lo))
{
	#if (MX_CAN_CHANNEL_X == 1)
		tx_msg.id.std = ((hi << 8) | lo);
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdentExd_, (MX_UINT8 buffer, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)
		//Extended CAN not currently supported on AVR
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilterStd_, (MX_UINT8 filter, MX_UINT8 hi, MX_UINT8 lo))
{
	#if (MX_CAN_CHANNEL_X == 1)
		//RX filtering not currently supported on AVR
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilterExd_, (MX_UINT8 filter, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)
		//RX filtering not currently supported on AVR
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskStd_, (MX_UINT8 filter, MX_UINT8 hi, MX_UINT8 lo))
{
	#if (MX_CAN_CHANNEL_X == 1)
		//RX masking not currently supported on AVR
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMaskExd_, (MX_UINT8 filter, MX_UINT8 id3, MX_UINT8 id2, MX_UINT8 id1, MX_UINT8 id0))
{
	#if (MX_CAN_CHANNEL_X == 1)
		//RX masking not currently supported on AVR
	#endif

	#if (MX_CAN_CHANNEL_X == 2)

	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxMask_, (MX_UINT8 mask, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)
		//RX masking not currently supported on AVR
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetRxFilter_, (MX_UINT8 filter, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)
		//RX filtering not currently supported on AVR
	#endif
}

CALFUNCTION(void, FC_CAL_Internal_CAN_SetTxIdent_, (MX_UINT8 buffer, MX_UINT32 id))
{
	#if (MX_CAN_CHANNEL_X == 1)
		tx_msg.id.std = id;
	#endif
}

CALFUNCTION(MX_UINT32, FC_CAL_Internal_CAN_GetRxIdent_, (MX_UINT8 buffer))
{
	#if (MX_CAN_CHANNEL_X == 1)
		return CAN_MSG_ID;
	#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxDataCount_, (MX_UINT8 buffer))
{
	#if (MX_CAN_CHANNEL_X == 1)
	return (CAN_MSG_DLC);
	#endif
}

CALFUNCTION(MX_UINT8, FC_CAL_Internal_CAN_GetRxData_, (MX_UINT8 buffer, MX_UINT8 index))
{
	#if (MX_CAN_CHANNEL_X == 1)
	if (index > CAN_MSG_DLC)
	{
	   return (0);
	}
	return (CAN_MSG_DATA[index]);
	#endif
}

#endif


