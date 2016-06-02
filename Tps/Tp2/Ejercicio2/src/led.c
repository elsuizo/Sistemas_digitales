/* -------------------------------------------------------------------------
@file led.c

@date 05/25/16 23:23:14
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
#include"led.h"
#include"keys.h"
void LED_toggle_task_init()
{
   led_state = OFF;
   led = LED3;
}


void LED_toggle_task_update()
{
   if (led_state == ON)
   {
      led_state = OFF; // Apago el pin
   }
   else
   {
      led_state = ON; // Prendo el pin
   }

   // Use of digitalWrite
   //buttonMefUpdate();
   digitalWrite(led, led_state);
}
void LED_toggle_task_init2()
{
   led_state2 = OFF;
   led2 = LED1;
}


void LED_toggle_task_update2()
{
   if (led_state2 == ON)
   {
      led_state2 = OFF; // Apago el pin
   }
   else
   {
      led_state2 = ON; // Prendo el pin
   }

   // Use of digitalWrite
   digitalWrite(led2, led_state2);
}
