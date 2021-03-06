/* -------------------------------------------------------------------------
@file clock.h

@date 05/24/16 20:55:05
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
#ifndef CLOCK_H_
#define CLOCK_H_
#include"main.h"

/*------------------------------------------------------------------------------
                           global variables
------------------------------------------------------------------------------*/
typedef enum{HH, MM, SS} display_states;
/*------------------------------------------------------------------------------
                           functions
------------------------------------------------------------------------------*/
void CLOCK_down();
void CLOCK_up();
void CLOCK_move_left();
void CLOCK_clean_terminal(void);
void CLOCK_clean_line_screen(void);
void CLOCK_task_init();
void CLOCK_task_update();
void CLOCK_modes_task_update();
void CLOCK_task_set_hour_update();
void CLOCK_show_update();
void CLOCK_task_set_alarm_update();
void CLOCK_task_check_alarm_update();
void CLOCK_do_alarm();
void CLOCK_set_alarm_flag();
#endif
