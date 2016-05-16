/* -------------------------------------------------------------------------
@file Semaphore.h

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

#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include"main.h"

// Initialize the Finite State Machine
void init_FSM();

// update the Finite State Machine
void update_FSM();

// YELLOW state
void do_state_YELLOW();

// GREEN state
void do_state_GREEN();

// RED state
void do_state_RED();


#endif
