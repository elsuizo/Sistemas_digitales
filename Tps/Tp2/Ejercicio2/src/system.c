/* -------------------------------------------------------------------------
   @file system.c

   @date 05/27/16 19:42:29
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
#include"main.h"
#include"system.h"
#include"scheduler.h"
#include"keys.h"


void SYSTEM_init()
{
   initialize_board(); // board configurations
   SCHEDULER_init();
   uint8_t message[] = "hola"; // test message
   /*------------------------------------------------------------------------------
     tasks inits
     ------------------------------------------------------------------------------*/
   PC_LINK_init(115200);
   CLOCK_task_init(message);
   LED_toggle_task_init();
   LED_toggle_task_init2();
   modes_flag = NORMAL;
   button_state4 = BUTTON_UP;
   button_state3 = BUTTON_UP;
   button_state2 = BUTTON_UP;
   button_state1 = BUTTON_UP;
   buttonMefInit(button_state1);
   buttonMefInit(button_state2);
   buttonMefInit(button_state3);
   buttonMefInit(button_state4);
}

void SYSTEM_change_mode(DigitalIOMap_t tec)
{
   switch(tec)
   {
      case TEC4:
         {
            switch(modes_flag)
            {
               case NORMAL:
                  {
                     digitalWrite(LEDR, OFF);
                     digitalWrite(LEDG, OFF);
                     digitalWrite(LEDB, ON);
                     modes_flag = ENTER;
                     break;
                  }
               case ENTER:
                  {
                     digitalWrite(LEDR, ON);
                     digitalWrite(LEDG, OFF);
                     digitalWrite(LEDB, OFF);
                     modes_flag = ALARM;
                     break;
                  }
               case ALARM:
                  {
                     digitalWrite(LEDG, ON);
                     digitalWrite(LEDB, OFF);
                     digitalWrite(LEDR, OFF);
                     modes_flag = NORMAL;
                     break;
                  }
               case DOALARM:
                  {
                     modes_flag = NORMAL;
                     break;
                  }
            }
            break;
         }
      case TEC3:
         {
            CLOCK_down();
            break;
         }
      case TEC2:
         {
            CLOCK_up();
            break;
         }
      case TEC1:
         {
            CLOCK_move_left();
            break;
         }
   }
}

