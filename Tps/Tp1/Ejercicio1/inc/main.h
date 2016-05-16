/* -------------------------------------------------------------------------
@file main.h

@date 05/12/16 18:39:26
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

#ifndef _MAIN_H_
#define _MAIN_H_
#include"sAPI.h"
/*------------------------------------------------------------------------------
                        state datatype
------------------------------------------------------------------------------*/
typedef enum{GREEN, YELLOW, RED}state; // define the states

/*------------------------------------------------------------------------------
                        Global variables
------------------------------------------------------------------------------*/
// flag for timeout
bool_t timeout;

// delays
delay_t delayRED_GREEN;
delay_t delayBlink;
delay_t delayYELLOW;


state next_state;

// flags for mannage the transition of the YELLOW state
bool_t from_RED;
bool_t from_GREEN;

/*------------------------------------------------------------------------------
                           Configurations
------------------------------------------------------------------------------*/
#endif
