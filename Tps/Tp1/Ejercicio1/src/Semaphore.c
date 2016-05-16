/* -------------------------------------------------------------------------
@file Semaphore.c

@date 05/12/16 18:38:24
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

#include"Semaphore.h"
#include"main.h"

/*------------------------------------------------------------------------------
                           State diagram 
------------------------------------------------------------------------------
+-------+             +-------+
| RED   |             | GREEN |
|       +----+  +-----+       |
+----+--+    |  |     +---+---+
     ^       |  |         ^
     |     +-+--+--+      |
     |     |       |      |
     +-----+YELLOW +------+
           |       |
           +-------+
------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
                            init_FSM()
------------------------------------------------------------------------------*/
void init_FSM()
{
   next_state = RED;
}

void do_state_YELLOW()
{
   while(!delayRead(&delayYELLOW))
   {
      digitalWrite(LED3, OFF);
      digitalWrite(LED1, OFF);
      digitalWrite(LED2, ON);

   }
   if(from_GREEN)
   {
      from_GREEN = FALSE;
      timeout = FALSE;
      next_state = RED;
   }
   if(from_RED)
   {
      from_RED = FALSE;
      timeout = FALSE;
      next_state = GREEN;
   }
}

void do_state_GREEN()
{
   while(!delayRead(&delayRED_GREEN))
   {
      digitalWrite(LED3, ON);
      digitalWrite(LED1, OFF);
      digitalWrite(LED2, OFF);
   }
   timeout = FALSE;
   from_GREEN = TRUE;
   next_state = YELLOW;
}

void do_state_RED()
{
   while(!delayRead(&delayRED_GREEN))
   {
      digitalWrite(LED3, OFF);
      digitalWrite(LED1, ON);
      digitalWrite(LED2, OFF);
   }
   timeout = FALSE;
   from_RED = TRUE;
   next_state = YELLOW;
}

void (*MEF[])(void) = {do_state_GREEN, do_state_YELLOW, do_state_RED};

/*------------------------------------------------------------------------------
                           update_FSM()
/------------------------------------------------------------------------------*/
void update_FSM()
{
   (*MEF[next_state])();
}
