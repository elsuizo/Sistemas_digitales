/* -------------------------------------------------------------------------
@file board_config.c

@date 05/24/16 21:19:08
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
#include"board_config.h"
#include"main.h"

void initialize_board(void)
{
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
}
