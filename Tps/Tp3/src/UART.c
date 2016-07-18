/* -------------------------------------------------------------------------
@file UART.c

@date 07/17/16 14:06:14
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
#include"UART.h"
#include"main.h"

void vUARTGatekeeperTask( void *pvParameters )
{
   
   char *pcMessageToPrint;
   char cBuffer[ mainMAX_MSG_LEN ];

	for( ;; )
	{
		/* Wait for a message to arrive. */
		xQueueReceive(xUARTQueue, &pcMessageToPrint, portMAX_DELAY);

      // funtion for printing(only Gatekeeper task)
      //vPrintString(pcMessageToPrint);
		//sprintf( cBuffer, "%s", pcMessageToPrint );
      vPrintString(pcMessageToPrint);
		//consoleprint( cBuffer );

	}
}

