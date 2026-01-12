// CRC: 77485F5F6A861F9125D47827B4DE49268C393A82E1DD33789BDC71E63800C2D5DB37BF5913B6223C6A30E26220D7A577CEB6D6F86C05BA919115957745CFB8C1B04721877DA0D5D1DDB4B3138346DF12BE5592F03AADF104C8773FD8ABA5B850622E4A10154D10ED53988D8E819F1E2C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5E8933BBADD6CE135E0FFD9835CF7EA65B6EBDD710CCC9F61D97CCC64CB865A24B404660AA68BF76BA42CC2625000AD03CD60400714658D8AD0ADF782A33B2E374261283226D8134AE226986A879DD9115B236E0A5AFCB6D6549D34A0D5AD11F3E42562ACA4E334158ADBD1D295AC58785EABED12486CE05556E599B5AD11AA62EAC3685094CA720B
// REVISION: 1.0
// GUID: 2942944B-780E-4755-B3C6-025841774A19
// DATE: 08\08\2022
// DIR: CAL\AVR\USB\Series4\modules\scheduler\scheduler.h
/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file is the definition of the scheduler
//!
//!  This file contains the scheduler definition and the task function to be
//!  executed by the scheduler
//!  NOTE:
//!    SCHEDULER_TICK & FPER are defined in config.h
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

#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

//!_____ I N C L U D E S ____________________________________________________
#ifdef KEIL
#include <intrins.h>
#define Wait_semaphore(a) while(!_testbit_(a))
#else
#define Wait_semaphore(a) while(!(a)) (a) = FALSE
#endif

//!_____ M A C R O S ________________________________________________________
//! Definition of Task ID. This ID is used to properly send the event to a
//! specific task.
//! Mind, it will be possible to send an event to many task by TASK_1 | TASK_0.
//! The name of the define can be changed by another define. That customization
//! should be done in the file mail_evt.h
#define TASK_DUMMY   0x00           // This define is mandatory
#define TASK_0       0x01
#define TASK_1       0x02
#define TASK_2       0x04
#define TASK_3       0x08
#define TASK_4       0x10
#define TASK_5       0x20
#define TASK_6       0x40
#define TASK_7       0x80

// This define is mandatory
#define ALL_TASK     (TASK_0|TASK_1|TASK_2|TASK_3|TASK_4|TASK_5|TASK_6|TASK_7)
//! End Task ID

//!----- Scheduler Types -----
#define SCHEDULER_CUSTOM      0
#define SCHEDULER_TIMED       1
#define SCHEDULER_TASK        2
#define SCHEDULER_FREE        3



#ifdef Scheduler_time_init
  extern  void Scheduler_time_init   (void);
#endif

#ifdef Scheduler_task_1_init
  extern  void Scheduler_task_1_init (void);
#else
  // if you do not want init at all, do:
  // #define Scheduler_task_1_init scheduler_empty_fct
  #error Scheduler_task_1_init must be defined in config.h file
#endif
#ifdef Scheduler_task_2_init
  extern  void Scheduler_task_2_init (void);
#endif
#ifdef Scheduler_task_3_init
  extern  void Scheduler_task_3_init (void);
#endif
#ifdef Scheduler_task_4_init
  extern  void Scheduler_task_4_init (void);
#endif
#ifdef Scheduler_task_5_init
  extern  void Scheduler_task_5_init (void);
#endif
#ifdef Scheduler_task_6_init
  extern  void Scheduler_task_6_init (void);
#endif
#ifdef Scheduler_task_7_init
  extern  void Scheduler_task_7_init (void);
#endif
#ifdef Scheduler_task_8_init
  extern  void Scheduler_task_8_init (void);
#endif
#ifdef Scheduler_task_9_init
  extern  void Scheduler_task_9_init (void);
#endif
#ifdef Scheduler_task_10_init
  extern  void Scheduler_task_10_init (void);
#endif
#ifdef Scheduler_task_11_init
  extern  void Scheduler_task_11_init (void);
#endif


#ifdef Scheduler_task_1
  extern  void Scheduler_task_1 (void);
#else
  // if you do not want task at all, do:
  // #define Scheduler_task_1 scheduler_empty_fct
  #error Scheduler_task_1 must be defined in config.h file
#endif
#ifdef Scheduler_task_2
  extern  void Scheduler_task_2 (void);
#endif
#ifdef Scheduler_task_3
  extern  void Scheduler_task_3 (void);
#endif
#ifdef Scheduler_task_4
  extern  void Scheduler_task_4 (void);
#endif
#ifdef Scheduler_task_5
  extern  void Scheduler_task_5 (void);
#endif
#ifdef Scheduler_task_6
  extern  void Scheduler_task_6 (void);
#endif
#ifdef Scheduler_task_7
  extern  void Scheduler_task_7 (void);
#endif
#ifdef Scheduler_task_8
  extern  void Scheduler_task_8 (void);
#endif
#ifdef Scheduler_task_9
  extern  void Scheduler_task_9 (void);
#endif
#ifdef Scheduler_task_10
  extern  void Scheduler_task_10 (void);
#endif
#ifdef Scheduler_task_11
  extern  void Scheduler_task_11 (void);
#endif

//!_____ D E F I N I T I O N ________________________________________________
#if SCHEDULER_TYPE != SCHEDULER_FREE
extern  bit   scheduler_tick_flag;
#endif

#ifdef TOKEN_MODE
extern Uchar token;
#define TOKEN_FREE      0
#endif

//!_____ D E C L A R A T I O N ______________________________________________
void scheduler_init         (void);
void scheduler_tasks        (void);
void scheduler              (void);
void scheduler_empty_fct    (void);

#ifndef SCHEDULER_TYPE
  #error You must define SCHEDULER_TYPE in config.h file
#elif SCHEDULER_TYPE == SCHEDULER_FREE
  #define Scheduler_set_tick_flag()
  #define Scheduler_reset_tick_flag()
#elif SCHEDULER_TYPE == SCHEDULER_TIMED
  #define Scheduler_new_schedule()      Wait_semaphore(scheduler_tick_flag)
  #define Scheduler_set_tick_flag()     (scheduler_tick_flag = TRUE)
  #define Scheduler_reset_tick_flag()   (scheduler_tick_flag = FALSE)
#elif SCHEDULER_TYPE == SCHEDULER_TASK
  #define Scheduler_call_next_task()    Wait_semaphore(scheduler_tick_flag)
  #define Scheduler_set_tick_flag()     (scheduler_tick_flag = TRUE)
  #define Scheduler_reset_tick_flag()   (scheduler_tick_flag = FALSE)
#elif SCHEDULER_TYPE == SCHEDULER_CUSTOM
  #error Make sure you have setup macro/fct Scheduler_new_schedule & Scheduler_call_next_task
  #define Scheduler_set_tick_flag()     (scheduler_tick_flag = TRUE)
  #define Scheduler_reset_tick_flag()   (scheduler_tick_flag = FALSE)
#endif

#ifndef Scheduler_call_next_task
  #define Scheduler_call_next_task()
#endif
#ifndef Scheduler_new_schedule
  #define Scheduler_new_schedule()
#endif
#ifndef Scheduler_call_next_init
  #define Scheduler_call_next_init()
#endif

#endif //! _SCHEDULER_H_

