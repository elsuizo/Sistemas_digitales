/* -------------------------------------------------------------------------
@file keys.h

@date 05/26/16 14:52:18
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

#ifndef _KEYS_H_ 
#define _KEYS_H_ 
#include"main.h"
#define DEBOUNCE_DELAY (40)
typedef enum{BUTTON_UP, BUTTON_FALLING, BUTTON_DOWN, BUTTON_RISING} button_state_t;
/*==================[internal data declaration]==============================*/


/*==================[internal functions declaration]=========================*/

button_state_t button_state1;
button_state_t button_state2;
button_state_t button_state3;
button_state_t button_state4;
/* MEF para manejo de Led */
//void ledMefInit(void);
//void ledMefUpdate(void);

/* MEF para manejo de Boton */
void buttonMefInit(void);
//void buttonMefInit(button_state_t button_number);
//void buttonMefUpdate(void);
//void buttonMefUpdate(DigitalIOMap_t);
/* Eventos de Boton */
//void buttonReleased(void);
void buttonPressed(void);
//void buttonPressed(DigitalIOMap_t tec);
void incrementarContador(void);

//void buttonMefUpdate(DigitalIOMap_t tec, button_state_t button_number);
void buttonMefUpdate(DigitalIOMap_t tec);
uint32_t sw1_pressed;
uint32_t sw2_pressed;
uint32_t sw3_pressed;
uint32_t sw4_pressed;
void keys_pressed();

void KEYS_button_task_update();
#endif
