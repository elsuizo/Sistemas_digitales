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
#include"scheduler.h"
#include"system.h"
#include"keys.h"

display_states clock_states;

char CHARMAP[] = "0123456789";
uint8_t  hs;
uint8_t  min;
uint8_t  seg;

uint8_t* ptr_hs = &hs;
uint8_t* ptr_min = &min;
uint8_t* ptr_seg = &seg;
//clock_clean_line_screen();
uint8_t CLOCK_string[] = "\rReloj: HH:MM:SS";
uint8_t CLOCK_string_min[] = "\rminutos: MM";
uint8_t CLOCK_string_hs[] = "\rhora: HH";
uint8_t CLOCK_string_seg[] = "\rsegundos: SS";

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
   CLOCK_show_update();
}

void CLOCK_task_set_hour_update()
{
   //uint8_t CLOCK_string2[] = "\rReloj: HH:MM:SS";  
      switch(clock_states)
      {
         case HH:
            {
               PC_LINK_write_string_to_buffer(CLOCK_string_hs);
               break;
            }
         case MM:
            {
               PC_LINK_write_string_to_buffer(CLOCK_string_min);
               break;
            }
         case SS:
            {
               PC_LINK_write_string_to_buffer(CLOCK_string_seg);
               break;
            }
      }
}
   //PC_LINK_write_string_to_buffer(CLOCK_string2);
   //SYSTEM_change_mode();

void CLOCK_down()
{
   if(modes_flag == ENTER)
   {
      switch(clock_states)
      {
         case HH:
            {
               *ptr_hs--;
               CLOCK_string_hs[7]   =  CHARMAP[(*ptr_hs)/10];
               CLOCK_string_hs[8]   =  CHARMAP[(*ptr_hs)%10];
               CLOCK_clean_terminal();
               break;
            }
         case MM:
            {
               *ptr_min--;
               CLOCK_string_min[10]  =  CHARMAP[(*ptr_min)/10];
               CLOCK_string_min[11]  =  CHARMAP[(*ptr_min)%10];
               CLOCK_clean_terminal();
               break;
            }
         case SS:
            {
               *ptr_seg--;
               CLOCK_string_seg[11]  =  CHARMAP[(*ptr_seg)/10];
               CLOCK_string_seg[12]  =  CHARMAP[(*ptr_seg)%10];
               CLOCK_clean_terminal();
               break;
            }
      }
   }
}

void CLOCK_up()
{
   if(modes_flag == ENTER)
   {
      switch(clock_states)
      {
         case HH:
            {
               ++(*ptr_hs);
                  CLOCK_string_hs[7]   =  CHARMAP[(*ptr_hs)/10];
                  CLOCK_string_hs[8]   =  CHARMAP[(*ptr_hs)%10];
               CLOCK_clean_terminal();
               break;
            }
         case MM:
            {
               ++(*ptr_min);
                  CLOCK_string_min[10]  =  CHARMAP[(*ptr_min)/10];
                  CLOCK_string_min[11]  =  CHARMAP[(*ptr_min)%10];
               CLOCK_clean_terminal();
               break;
            }
         case SS:
            {
               //seg++;
               ++(*ptr_seg);
                  CLOCK_string_seg[11]  =  CHARMAP[(*ptr_seg)/10];
                  CLOCK_string_seg[12]  =  CHARMAP[(*ptr_seg)%10];
               CLOCK_clean_terminal();
               break;
            }
      }
   }
}

void CLOCK_move_left()
{
   if(modes_flag == ENTER)
   {
      switch(clock_states)
      {
         case HH:
            {
               clock_states = MM;
               break;
            }
         case MM:
            {
               clock_states = SS;
               break;
            }
         case SS:
            {
               clock_states = HH;
               break;
            }
      }
   }
}


void CLOCK_show_update()
{

   //CLOCK_clean_terminal();
   //uint8_t CLOCK_string[] = "\rReloj: HH:MM:SS";
   if(++(*ptr_seg) == 60)
   {
      *ptr_seg = 0;
      if(++(*ptr_min) == 60)
      {
         *ptr_min = 0;
      
         if(++(*ptr_hs) == 24)
         {
            *ptr_hs = 0;
         }
      }
   }
   // message
   CLOCK_string[8]   =  CHARMAP[(*ptr_hs)/10];
   CLOCK_string[9]   =  CHARMAP[(*ptr_hs)%10];
   CLOCK_string[11]  =  CHARMAP[(*ptr_min)/10];
   CLOCK_string[12]  =  CHARMAP[(*ptr_min)%10];
   CLOCK_string[14]  =  CHARMAP[(*ptr_seg)/10];
   CLOCK_string[15]  =  CHARMAP[(*ptr_seg)%10];
   PC_LINK_write_string_to_buffer(CLOCK_string);
}
