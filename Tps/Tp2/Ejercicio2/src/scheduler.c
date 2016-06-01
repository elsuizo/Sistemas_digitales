/* -------------------------------------------------------------------------
   @file SCHEDULER.c

   @date 05/23/16 17:13:23
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
#include "scheduler.h"



// Keeps track of time since last error was recorded (see below)
//static int Error_tick_count;
// The code of the last error (reset after ~1 minute)
static char Last_error_code;


static void SCHEDULER_go_to_sleep(void);


// The array of tasks
sTask SCH_tasks[SCHEDULER_MAX_TASKS];

// Used to display the error code
// See Main.H for details of error codes
// See Port.H for details of the error port
char Error_code = 0;




/*------------------------------------------------------------------*-
  SCH_Dispatch_Tasks()
  This is the 'dispatcher' function. When a task (function)
  is due to run, SCH_Dispatch_Tasks() will run it.
  This function must be called (repeatedly) from the main loop.
  -*------------------------------------------------------------------*/
void SCHEDULER_dispatch_task(void)
{
   int Index;
   // Dispatches (runs) the next task (if one is ready)
   switch(modes_flag)
   {
      case ENTER:
         {
            for (Index = 0; Index < SCHEDULER_MAX_TASKS; Index++)
            {
               if ((SCH_tasks[Index].RunMe > 0)&& (SCH_tasks[Index].state_flag == ENTER)||(SCH_tasks[Index].state_flag==ALWAYS))

               {
                  (*SCH_tasks[Index].pTask)(); // Run the task
                  SCH_tasks[Index].RunMe -= 1; // Reset / reduce RunMe flag
                  // Periodic tasks will automatically run again
                  // - if this is a 'one shot' task, remove it from the array
                  if (SCH_tasks[Index].Period == 0)
                  {
                     SCHEDULER_delete_task(Index);
                  }
               }
            }
            break;
         }
      case NORMAL:
         {
            for (Index = 0; Index < SCHEDULER_MAX_TASKS; Index++)
            {
               if ((SCH_tasks[Index].RunMe > 0)&&(SCH_tasks[Index].state_flag == NORMAL)||(SCH_tasks[Index].state_flag==ALWAYS))
               {
                  (*SCH_tasks[Index].pTask)(); // Run the task
                  SCH_tasks[Index].RunMe -= 1; // Reset / reduce RunMe flag
                  // Periodic tasks will automatically run again
                  // - if this is a 'one shot' task, remove it from the array
                  if (SCH_tasks[Index].Period == 0)
                  {
                     SCHEDULER_delete_task(Index);
                  }
               }
            }
            break;
         }
      case ALARM:
         {
            for (Index = 0; Index < SCHEDULER_MAX_TASKS; Index++)
            {
               if ((SCH_tasks[Index].RunMe > 0)&&(SCH_tasks[Index].state_flag == ALARM)||(SCH_tasks[Index].state_flag==ALWAYS))
               {
                  (*SCH_tasks[Index].pTask)(); // Run the task
                  SCH_tasks[Index].RunMe -= 1; // Reset / reduce RunMe flag
                  // Periodic tasks will automatically run again
                  // - if this is a 'one shot' task, remove it from the array
                  if (SCH_tasks[Index].Period == 0)
                  {
                     SCHEDULER_delete_task(Index);
                  }
               }
            }
            break;
         }
      case DOALARM:
         {
            for (Index = 0; Index < SCHEDULER_MAX_TASKS; Index++)
            {
               if ((SCH_tasks[Index].RunMe > 0)&&(SCH_tasks[Index].state_flag == DOALARM)||(SCH_tasks[Index].state_flag==ALWAYS))
               {
                  (*SCH_tasks[Index].pTask)(); // Run the task
                  SCH_tasks[Index].RunMe -= 1; // Reset / reduce RunMe flag
                  // Periodic tasks will automatically run again
                  // - if this is a 'one shot' task, remove it from the array
                  if (SCH_tasks[Index].Period == 0)
                  {
                     SCHEDULER_delete_task(Index);
                  }
               }
            }
            break;
         }
   }

   // Report system status
   SCHEDULER_report_status();
   // The scheduler enters idle mode at this point
   SCHEDULER_go_to_sleep();
}

/*------------------------------------------------------------------*-
  SCH_Add_Task()
  Causes a task (function) to be executed at regular intervals
  or after a user-defined delay
  Fn_P - The name of the function which is to be scheduled.
NOTE: All scheduled functions must be 'void, void' -
that is, they must take no parameters, and have
a void return type.
DELAY - The interval (TICKS) before the task is first executed
PERIOD - If 'PERIOD' is 0, the function is only called once,
at the time determined by 'DELAY'. If PERIOD is non-zero,
then the function is called repeatedly at an interval
determined by the value of PERIOD (see below for examples
which should help clarify this)
RETURN VALUE:
Returns the position in the task array at which the task has been
added. If the return value is SCH_MAX_TASKS then the task could
not be added to the array (there was insufficient space). If the
return value is < SCH_MAX_TASKS, then the task was added
successfully.
Note: this return value may be required, if a task is
to be subsequently deleted - see SCH_Delete_Task().
EXAMPLES:
Task_ID = SCH_Add_Task(Do_X,1000,0);
Causes the function Do_X() to be executed once after 1000 sch ticks.
Task_ID = SCH_Add_Task(Do_X,0,1000);
Causes the function Do_X() to be executed regularly, every 1000 sch ticks.
Task_ID = SCH_Add_Task(Do_X,300,1000);
Causes the function Do_X() to be executed regularly, every 1000 ticks.
Task will be first executed at T = 300 ticks, then 1300, 2300, etc.
-*------------------------------------------------------------------*/
char SCHEDULER_add_task(void (* pFunction)(void), const int DELAY, const int PERIOD, system_mode mode)
{
   int Index = 0;
   // First find a gap in the array (if there is one)
   while ((SCH_tasks[Index].pTask != 0) && (Index < SCHEDULER_MAX_TASKS))
   {
      Index++;
   }
   // Have we reached the end of the list?
   if (Index == SCHEDULER_MAX_TASKS)
   {
      // Task list is full
      //
      // Set the global error variable
      Error_code = 2; //ERROR_SCH_TOO_MANY_TASKS;
      // Also return an error code
      return SCHEDULER_MAX_TASKS;
   }
   // If we're here, there is a space in the task array
   SCH_tasks[Index].pTask = pFunction;
   SCH_tasks[Index].Delay = DELAY;
   SCH_tasks[Index].Period = PERIOD;
   SCH_tasks[Index].RunMe = 0;
   SCH_tasks[Index].state_flag = mode;
   return Index; // return position of task (to allow later deletion)
}

/*------------------------------------------------------------------*-
  SCH_Delete_Task()
  Removes a task from the scheduler. Note that this does
 *not* delete the associated function from memory:
 it simply means that it is no longer called by the scheduler.
 TASK_INDEX - The task index. Provided by SCH_Add_Task().
 RETURN VALUE: RETURN_ERROR or RETURN_NORMAL
 -*------------------------------------------------------------------*/
char SCHEDULER_delete_task(const int TASK_INDEX)
{
   char Return_code;
   if (SCH_tasks[TASK_INDEX].pTask == 0)
   {
      // No task at this location...
      //
      // Set the global error variable
      Error_code = 2; //ERROR_SCH_CANNOT_DELETE_TASK;
      // ...also return an error code
      Return_code = -1; //RETURN_ERROR;
   }
   else
   {
      Return_code = 0; //RETURN_NORMAL;
   }
   SCH_tasks[TASK_INDEX].pTask = 0x0000;
   SCH_tasks[TASK_INDEX].Delay = (int)0;
   SCH_tasks[TASK_INDEX].Period = (int)0;
   SCH_tasks[TASK_INDEX].RunMe = (char)0;
   SCH_tasks[TASK_INDEX].state_flag = (system_mode)0;
   return Return_code; // return status
}

/*------------------------------------------------------------------*-
  SCH_Report_Status()
  Simple function to display error codes.
  This version displays code on a port with attached LEDs:
  adapt, if required, to report errors over serial link, etc.
  Errors are only displayed for a limited period
  (60000 ticks = 1 minute at 1ms tick interval).
  After this the the error code is reset to 0.
  This code may be easily adapted to display the last
  error 'for ever': this may be appropriate in your
  application.
  -*------------------------------------------------------------------*/
void SCHEDULER_report_status(void)
{
#ifdef SCH_REPORT_ERRORS
   // ONLY APPLIES IF WE ARE REPORTING ERRORS
   // Check for a new error code
   if (Error_code != Last_error_code)
   {
      // Negative logic on LEDs assumed
      Error_port = 255 - Error_code;
      Last_error_code = Error_code;
      if (Error_code!= 0)
      {
         Error_tick_count = 60000;
      }
      else
      {
         Error_tick_count = 0;
      }
   }
   else
   {
      if (Error_tick_count != 0)
      {
         if (--Error_tick_count == 0)
         {
            Error_code = 0; // Reset error code
         }
      }
   }
#endif
}

/*------------------------------------------------------------------*-
  SCH_Go_To_Sleep()
  This scheduler enters 'idle mode' between clock ticks
  to save power. The next clock tick will return the processor
  to the normal operating state.
 *** May wish to disable this if using a watchdog ***
 *** ADAPT AS REQUIRED FOR YOUR HARDWARE ***
 -*------------------------------------------------------------------*/
static void SCHEDULER_go_to_sleep()
{
   __asm volatile( "wfi" ); /* Wait for interrupt */
}


/** @} doxygen end group definition */

/*==================[end of file]============================================*/
