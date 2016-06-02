/* -------------------------------------------------------------------------
   @file pc_link.c

   @date 05/23/16 17:37:15
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
#include"pc_link.h"
#include"main.h" // en el main esta la sAPI
//#include"sAPI.h"

char RX_read_index;     
char RX_waiting_index;  

char TX_write_index;  
char TX_read_index;  

// ------ Public variable declarations -----------------------------

extern uint32_t Error_code;


// ------ Private constants ----------------------------------------

// buffer RX(reception) length
#define RX_BUFFER_LENGTH 5

// buffer TX(transmision) length
#define TX_BUFFER_LENGTH 50


// ------ Private variables ----------------------------------------

static uint8_t RX_buffer[RX_BUFFER_LENGTH];
static uint8_t TX_buffer[TX_BUFFER_LENGTH];


// initialize the conection
void PC_LINK_init(uint32_t baud_rate)
{
   uartConfig(UART_USB, baud_rate);
}
void PC_LINK_task_update(void)
{
   //SYSTEM_change_mode();
   // any byte on buffer??? 
   if(TX_read_index < TX_write_index)
   {
      PC_LINK_send_char(TX_buffer[TX_read_index]);
      TX_read_index++;
   }
   else
   {
      // NO data to send
      TX_read_index   =  0;
      TX_write_index  =  0;
   }
}

void PC_LINK_write_string_to_buffer(uint8_t *ptr_char)
{
   char i = 0;

   while(ptr_char[i] != '\0')
   {
      PC_LINK_write_char_to_buffer(ptr_char[i]);
      i++;
   }

}

void PC_LINK_write_char_to_buffer(uint8_t data)
{
   // write to buffer only if there is space 
   if(TX_write_index < TX_BUFFER_LENGTH)
   {
      TX_buffer[TX_write_index] = data;
      TX_write_index++;
   }
   else
   {
      Error_code = ERROR_UART_FULL_BUFFER;
   }
}


void PC_LINK_send_char(uint8_t data)
{
   // sAPI function 
   uartWriteByte(UART_USB, data);
}
