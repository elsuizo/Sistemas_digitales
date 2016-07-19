/* -------------------------------------------------------------------------
@file UART.h

@date 07/17/16 13:59:56
@author Martin Noblia
@email martin.noblia@openmailbox.org

@brief
UART driver API for RTOS
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
#ifndef __UART_H__
#define __UART_H__
#include"main.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"
#include "sAPI.h"
// maximum length
#define mainMAX_MSG_LEN	( 80 )
// 
void vUARTGatekeeperTask( void *pvParameters );
void vUARTinit(uint32_t);
/*-----------------------------------------------------------*/

xQueueHandle xUARTQueue;

#endif
