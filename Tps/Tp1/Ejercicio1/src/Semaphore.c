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

state do_state_YELLOW()
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
      return RED;
   }
   if(from_RED)
   {
      from_RED = FALSE;
      timeout = FALSE;
      return GREEN;
   }
}

state do_state_GREEN()
{
   while(!delayRead(&delayRED_GREEN))
   {
      digitalWrite(LED3, ON);
      digitalWrite(LED1, OFF);
      digitalWrite(LED2, OFF);
   }
   timeout = FALSE;
   from_GREEN = TRUE;
   return YELLOW;
}

state do_state_RED()
{
   while(!delayRead(&delayRED_GREEN))
   {
      digitalWrite(LED3, OFF);
      digitalWrite(LED1, ON);
      digitalWrite(LED2, OFF);
   }
   timeout = FALSE;
   from_RED = TRUE;
   return YELLOW;
}


/*------------------------------------------------------------------------------
                           update_FSM()
/------------------------------------------------------------------------------*/
void update_FSM()
{
   switch(next_state)
   {

      case YELLOW:
         next_state = do_state_YELLOW();
         break;

      case GREEN:
         next_state = do_state_GREEN();
         break;

      case RED:
         next_state = do_state_RED();
         break;

   }
}
