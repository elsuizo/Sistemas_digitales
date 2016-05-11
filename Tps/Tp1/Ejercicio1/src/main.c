/* -------------------------------------------------------------------------
@file main.c

@date 05/11/16 00:44:43
@author Martin Noblia
@email martin.noblia@openmailbox.org

@brief
Ejercicio 1 Sistemas digitales utilizando la libreria sAPI
@detail
Realice un programa para implementar el ejemplo de semaforo mediante MEF(FSM en 
ingles) visto en clase. Se utilizan los LEDS de la EDU-CIAA-NXP
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

/*------------------------------------------------------------------------------
                           includes
------------------------------------------------------------------------------*/

#include "main.h"
#include "sAPI.h"


// TODO(elsuizo:tratar de hacer que el led verde titile 2 seg antes de pasar a amarillo)-->Thu 05 May 2016 05:20:02 PM ART

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
bool_t timeout;

delay_t delayRED_GREEN;
delay_t delayBlink;
delay_t delayYELLOW;

typedef enum{GREEN, YELLOW, RED}state; // define the states
//  
state next_state;

bool_t from_RED = FALSE;
bool_t from_GREEN = FALSE;
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

int main(void)
{
   // initialize board configurations
   boardConfig();

   tickConfig(1);

   digitalConfig(0, INITIALIZE);
   // switchs configs
   digitalConfig(TEC1, INPUT);
   digitalConfig(TEC2, INPUT);
   digitalConfig(TEC3, INPUT);
   digitalConfig(TEC4, INPUT);
   // Leds configs
   digitalConfig(LEDR, OUTPUT);
   digitalConfig(LEDG, OUTPUT);
   digitalConfig(LEDB, OUTPUT);
   digitalConfig(LED1, OUTPUT);
   digitalConfig(LED2, OUTPUT);
   digitalConfig(LED3, OUTPUT);

   // delays setups
   delayConfig(&delayRED_GREEN, 5000);
   delayConfig(&delayYELLOW, 500);
   // delay for the GREEN Blinking(like a real semaphore)
   delayConfig(&delayBlink, 1000);

   // init the Finite State Machine
   init_FSM();

   while(1) 
   {
      // update the Finite State Machine
      update_FSM();
   }


   return 0;
}

