/* -------------------------------------------------------------------------
@file keys.c

@date 05/26/16 15:12:58
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
General Public License for more details

You should have received a copy of the GNU General Public License

---------------------------------------------------------------------------*/
#include"keys.h"
/* Variable de estado del boton */
#include"main.h"
#include"system.h"
//button_state_t button_state = BUTTON_UP;

button_state_t* ptr_button_state1 = &button_state1;
button_state_t* ptr_button_state2 = &button_state2;
button_state_t* ptr_button_state3 = &button_state3;
button_state_t* ptr_button_state4 = &button_state4;

void KEYS_button_task_update()   
{
   buttonMefUpdate(TEC4, ptr_button_state4);
   buttonMefUpdate(TEC3, ptr_button_state3);
   buttonMefUpdate(TEC2, ptr_button_state2);
   buttonMefUpdate(TEC1, ptr_button_state1);
}
/* Evento que se ejecuta cuando se Presiona el boton */
void buttonPressed(DigitalIOMap_t tec)
{
   /* Hacer algo al presionar el boton */
   SYSTEM_change_mode(tec);
}
/* MEF para manejo de Boton */

void buttonMefInit(button_state_t button_number)
{
   button_number = BUTTON_UP;
}

void buttonMefUpdate(DigitalIOMap_t tec, button_state_t* ptr_button_number)
{
   switch(*ptr_button_number){
      case BUTTON_UP:{
         if(!digitalRead(tec))
            *ptr_button_number = BUTTON_FALLING;
         break;
      }
      case BUTTON_FALLING:{
         delay(DEBOUNCE_DELAY);
         if(!digitalRead(tec)){
            *ptr_button_number = BUTTON_DOWN;
            /* Dispara el evento */
            buttonPressed(tec);
         }
         else
            *ptr_button_number = BUTTON_UP;
         break;
      }
      case BUTTON_DOWN:{
         if(digitalRead(tec))
            *ptr_button_number = BUTTON_RISING;
         break;
      }
      case BUTTON_RISING:{
         delay(DEBOUNCE_DELAY);
         if(digitalRead(tec)){
            *ptr_button_number = BUTTON_UP;
            /* Dispara el evento */
            //buttonReleased();
         }
         else
            *ptr_button_number = BUTTON_DOWN;
         break;
      }
   }
}
