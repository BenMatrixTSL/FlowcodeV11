// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5DB37BF5913B6223C6A30E26220D7A577CEB6D6F86C05BA919115957745CFB8C1B04721877DA0D5D1DDB4B3138346DF12BE5592F03AADF104C8773FD8ABA5B850186EF292F6E67B0826724E02FB1A52139A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF58CE80998ADF5D360574607DA4C8D0ED9A47FAC8E336B7FB9549583D6F9AEAC9C0B89B7FEC153B601677E8B513EBA3658D0E3B909E4F4A7F9A9E59D34F313D82AB0D06D3E5774CB8C835F82012A0FC8DFD5D4432F9E781524549D34A0D5AD11F3927C0C41FC5D12EB6062AC9FC4B7F15D1638CC98E8B241DCB70D32482E1A79DC3042F59BC2B95F11
// REVISION: 1.0
// GUID: 7699441C-8A86-45BB-B930-F15C58425F17
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\modules\scheduler\scheduler.c
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file contains the scheduler routines
//!
//! Configuration:
//!   - SCHEDULER_TYPE in scheduler.h header file
//!   - Task & init for at least task number 1 must be defined
//!
//! - Compiler:           IAR EWAVR and GNU GCC for AVR
//! - Supported devices:  ATmega32U4
//!
//! \author               Atmel Corporation: http://www.atmel.com \n
//!                       Support and FAQ: http://support.atmel.no/
//!
//! ***************************************************************************

/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//!_____ I N C L U D E S ____________________________________________________
#define _SCHEDULER_C_
#include "config.h"                         // system definition 
#include "scheduler.h"                      // scheduler definition 


//!_____ M A C R O S ________________________________________________________
//!_____ D E F I N I T I O N ________________________________________________
#if SCHEDULER_TYPE != SCHEDULER_FREE
//! When SCHEDULER_TYPE != SCHEDULER_FREE, this flag control task calls.
bit   scheduler_tick_flag;
#endif

#ifdef TOKEN_MODE
//! Can be used to avoid that some tasks executes at same time. 
//! The tasks check if the token is free before executing. 
//! If the token is free, the tasks reserve it at the begin of the execution 
//! and release it at the end of the execution to enable next waiting tasks to 
//! run.   
Uchar token;
#endif

//!_____ D E C L A R A T I O N ______________________________________________
//! Scheduler initialization
//!
//! Task_x_init() and Task_x_fct() are defined in config.h
//!
//! @warning Code:XX bytes (function code length)
//!
//! @param  :none
//! @return :none
void scheduler_init (void)
{
   #ifdef Scheduler_time_init
      Scheduler_time_init();
   #endif
   #ifdef TOKEN_MODE
      token =  TOKEN_FREE;
   #endif
   #ifdef Scheduler_task_1_init
      Scheduler_task_1_init();  
      Scheduler_call_next_init();
   #endif
   #ifdef Scheduler_task_2_init
      Scheduler_task_2_init();  
      Scheduler_call_next_init();
   #endif
   #ifdef Scheduler_task_3_init
      Scheduler_task_3_init();  
      Scheduler_call_next_init();
   #endif
   #ifdef Scheduler_task_4_init
      Scheduler_task_4_init();  
      Scheduler_call_next_init();
   #endif
   #ifdef Scheduler_task_5_init
      Scheduler_task_5_init();  
      Scheduler_call_next_init();
   #endif
   #ifdef Scheduler_task_6_init
      Scheduler_task_6_init();  
      Scheduler_call_next_init();
   #endif
   #ifdef Scheduler_task_7_init
      Scheduler_task_7_init();  
      Scheduler_call_next_init();
   #endif
   #ifdef Scheduler_task_8_init
      Scheduler_task_8_init();  
      Scheduler_call_next_init();
   #endif
   #ifdef Scheduler_task_9_init
      Scheduler_task_9_init();  
      Scheduler_call_next_init();
   #endif
   #ifdef Scheduler_task_10_init
      Scheduler_task_10_init();
      Scheduler_call_next_init();
   #endif
   #ifdef Scheduler_task_11_init
      Scheduler_task_11_init();
      Scheduler_call_next_init();
   #endif
   Scheduler_reset_tick_flag();
}

//! Task execution scheduler
//!
//! @warning Code:XX bytes (function code length)
//!
//! @param  :none
//! @return :none
void scheduler_tasks (void)
{
   // To avoid uncalled segment warning if the empty function is not used
   scheduler_empty_fct();

   for(;;)
   {
      Scheduler_new_schedule();
      #ifdef Scheduler_task_1
         Scheduler_task_1();
         Scheduler_call_next_task();
      #endif
      #ifdef Scheduler_task_2
         Scheduler_task_2();
         Scheduler_call_next_task();
      #endif
      #ifdef Scheduler_task_3
         Scheduler_task_3();
         Scheduler_call_next_task();
      #endif
      #ifdef Scheduler_task_4
         Scheduler_task_4();
         Scheduler_call_next_task();
      #endif
      #ifdef Scheduler_task_5
         Scheduler_task_5();
         Scheduler_call_next_task();
      #endif
      #ifdef Scheduler_task_6
         Scheduler_task_6();
         Scheduler_call_next_task();
      #endif
      #ifdef Scheduler_task_7
         Scheduler_task_7();
         Scheduler_call_next_task();
      #endif
      #ifdef Scheduler_task_8
         Scheduler_task_8();
         Scheduler_call_next_task();
      #endif
      #ifdef Scheduler_task_9
         Scheduler_task_9();
         Scheduler_call_next_task();
      #endif
      #ifdef Scheduler_task_10
         Scheduler_task_10();
         Scheduler_call_next_task();
      #endif
      #ifdef Scheduler_task_11
         Scheduler_task_11();
         Scheduler_call_next_task();
      #endif
   }
}

//! Init & run the scheduler
//!
//! @warning Code:XX bytes (function code length)
//!
//! @param  :none
//! @return :none
void scheduler (void)
{
   scheduler_init();
   scheduler_tasks();
}


//! Do nothing
//! Avoid uncalled segment warning if the empty function is not used
//!
//! @warning Code:XX bytes (function code length)
//!
//! @param  :none
//! @return :none
void scheduler_empty_fct (void)
{
}

