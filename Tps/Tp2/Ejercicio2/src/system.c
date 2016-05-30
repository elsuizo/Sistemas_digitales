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

uint32_t sw4_pressed;

void SYSTEM_init()
{
   initialize_board();
   modes_flag = NORMAL;
   button_state3 = BUTTON_UP;
   button_state4 = BUTTON_UP;
   buttonMefInit(button_state3);
   buttonMefInit(button_state4);
}

void SYSTEM_change_mode(DigitalIOMap_t tec)
{
   switch(tec)
   {
      case TEC4:
         {
            if(modes_flag == ENTER) 
            {
               modes_flag = NORMAL;
               digitalWrite(LEDG, ON);
               digitalWrite(LEDR, OFF);
            }
            else
            {
               modes_flag = ENTER;
               digitalWrite(LEDR, ON);
               digitalWrite(LEDG, OFF);
            }
            break;
         }
      case TEC3:
         {
            digitalWrite(LED1, ON);
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

