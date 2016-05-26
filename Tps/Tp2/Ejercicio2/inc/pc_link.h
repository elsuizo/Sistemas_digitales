/* -------------------------------------------------------------------------
@file pc_link.h

@date 05/23/16 17:36:56
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
#ifndef PC_LINK_H_
#define PC_LINK_H_
#include"main.h"
// initialize the conection
void PC_LINK_task_init(uint32_t baud_rate);
// update the conection?
void PC_LINK_task_update();

void PC_LINK_write_char_to_buffer(uint8_t data);

void PC_LINK_write_string_to_buffer(uint8_t *);

void PC_LINK_send_char(uint8_t data);

//char PC_LINK_receive_data(char *data);
#endif
