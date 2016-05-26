/* -------------------------------------------------------------------------
@file clock.c

@date 05/24/16 20:55:57
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
#include"clock.h"
#include"main.h"

void CLOCK_clean_line_screen(void)
{
	// Borro toda la línea de la terminal
	uartWriteByte(UART_USB, 8);         // BACKSPACE command, mueve 1 caracter atras
	uartWriteByte(UART_USB, 13);        // CR command
	uint8_t i = 0;
	for ( i=0; i<50; i++ ) {
		uartWriteByte(UART_USB, 32);     // SPACE command
	}
	uartWriteByte(UART_USB, 13);        // CR command
}

void CLOCK_clean_terminal(void)
{
	// Borro toda la pantalla de la terminal
   uartWriteByte( UART_USB, 27 );       // ESC command
	uartWriteString( UART_USB, "[2J" );  // clear screen command
	uartWriteByte( UART_USB, 27 );       // ESC command
	uartWriteString( UART_USB, "[H" );   // cursor to home command
}
//menu[] = 'hola';
void CLOCK_task_init(str)
{
	uartWriteString(UART_USB, (uint8_t*)str);
}
// update the task
void CLOCK_task_update()
{

   static char CHARMAP[] = "0123456789";
   static  uint8_t  hs   =  0;
   static  uint8_t  min  =  0;
   static  uint8_t  seg  =  0;
   //CLOCK_clean_line_screen();
   uint8_t CLOCK_string[16] = "\rReloj: HH:MM:SS";
   //CLOCK_clean_line_screen();
   if(++seg == 60)
   {
      seg = 0;
      if(++min == 60)
      {
         min = 0;
      
         if(++hs == 24)
         {
            hs = 0;
         }
      }
   }
   // message
   CLOCK_string[8]   =  CHARMAP[hs/10];
   CLOCK_string[9]   =  CHARMAP[hs%10];
   CLOCK_string[11]  =  CHARMAP[min/10];
   CLOCK_string[12]  =  CHARMAP[min%10];
   CLOCK_string[14]  =  CHARMAP[seg/10];
   CLOCK_string[15]  =  CHARMAP[seg%10];
   
   PC_LINK_write_string_to_buffer(CLOCK_string);
}

