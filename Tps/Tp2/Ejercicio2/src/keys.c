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
button_state_t button_state = BUTTON_UP;

/* Variable de estado del Led */

//uint8_t keys_led_state = OFF;
///* Variable de conteo de teclas pulsadas */
//uint8_t counter = 0;
//
//void ledMefInit(void){
//   keys_led_state = OFF;
//}
//
//void ledMefUpdate(void){
//   if(keys_led_state)
//      keys_led_state = OFF;
//   else
//      keys_led_state = ON;
//   digitalWrite( LEDB, keys_led_state );
//}

/* MEF para manejo de Boton */

void buttonMefInit(void){
   button_state = BUTTON_UP;
}

void buttonMefUpdate(DigitalIOMap_t tec)
{
   switch(button_state){
      case BUTTON_UP:{
         if(!digitalRead(tec))
            button_state = BUTTON_FALLING;
         break;
      }
      case BUTTON_FALLING:{
         delay(DEBOUNCE_DELAY);
         if(!digitalRead(tec)){
            button_state = BUTTON_DOWN;
            /* Dispara el evento */
            buttonPressed();
         }
         else
            button_state = BUTTON_UP;
         break;
      }
      case BUTTON_DOWN:{
         if(digitalRead(tec))
            button_state = BUTTON_RISING;
         break;
      }
      case BUTTON_RISING:{
         delay(DEBOUNCE_DELAY);
         if(digitalRead(tec)){
            button_state = BUTTON_UP;
            /* Dispara el evento */
            //buttonReleased();
         }
         else
            button_state = BUTTON_DOWN;
         break;
      }
      default:{
         buttonMefInit();
      }
   }
}


/* Evento que se ejecuta cuando se Libera el boton */
//void buttonReleased(void){
//   /* Hacer algo al liberar el boton */
//   ledMefUpdate();
//}

/* Evento que se ejecuta cuando se Presiona el boton */
void buttonPressed(void){
   /* Hacer algo al presionar el boton */
   SYSTEM_change_mode();
}
	
void KEYS_button_task_update()   
{
   //buttonPressed();
   buttonMefUpdate(TEC4);
   //buttonMefUpdate(TEC4);
}

