/* -------------------------------------------------------------------------
@file scheduler.h

@date 05/23/16 17:13:52
@author Martin Noblia
@email martin.noblia@openmailbox.org

@brief

@detail

Licence:
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
---------------------------------------------------------------------------*/

#ifndef _SCHEDULER_H_ 
#define _SCHEDULER_H_

#ifdef __cplusplus
extern "C" {
#endif


// The maximum number of tasks required at any one time during the execution
// of the program
// MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCHEDULER_MAX_TASKS (7)
//
//
//// Store in DATA area, if possible, for rapid access
//// Total memory per task is 7 bytes
//typedef struct
//{
//   // Pointer to the task (must be a 'void (void)' function)
//   void (* pTask)(void);
//   // Delay (ticks) until the function will (next) be run
//   // - see SCHEDULER_Add_Task() for further details
//   int Delay;
//   // Interval (ticks) between subsequent runs.
//   // - see SCHEDULER_Add_Task() for further details
//   int Period;
//   // Incremented (by scheduler) when task is due to execute
//   int RunMe;
//} sTask;


typedef enum {ENTER, NORMAL, ALLWAYS} system_mode;
// Store in DATA area, if possible, for rapid access
// Total memory per task is 7 bytes
system_mode modes_flag;

typedef struct
{
   // Pointer to the task (must be a 'void (void)' function)
   void (* pTask)(void);
   // Delay (ticks) until the function will (next) be run
   // - see SCHEDULER_Add_Task() for further details
   int Delay;
   // Interval (ticks) between subsequent runs.
   // - see SCHEDULER_Add_Task() for further details
   int Period;
   // Incremented (by scheduler) when task is due to execute
   int RunMe;

   system_mode state_flag;
} sTask;


void SCHEDULER_dispatch_tasks(void);
//char SCHEDULER_add_task(void (*) (void), const int, const int);
char SCHEDULER_add_task(void (* pFunction)(void), const int DELAY, const int PERIOD, system_mode mode);
char SCHEDULER_delete_task(const int);
void SCHEDULER_report_status(void);



#ifdef __cplusplus
}
#endif

#endif 

