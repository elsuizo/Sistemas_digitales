/* -------------------------------------------------------------------------
@file main.c

@date 05/22/16 14:37:19
@author Martin Noblia
@email martin.noblia@openmailbox.org

@brief

@detail
   Realice un programa, de manera modular, que incluya las funcionalidades básicas de un
   reloj (registro de hora, minutos y segundos). Para visualizar la hora, se utilizará la salida a
   consola por medio de la UART2 y además un led de la placa debe destellar cada 1 seg.
   El formato a mostrar será: HH:MM:SS actualizado 1 vez por segundo sobre la misma línea
   de la consola.
   El programa debe permitir modificar la hora del sistema mediante los cuatro pulsadores de
   la EDU-CIAA con las siguientes funcionalidades:
   Pulsador 1: izquierda
   Pulsador 2: arriba(incrementar)
   Pulsador 3: abajo(decrementar)
   Pulsador 4: enter(MODO-ENTER)
   Ejemplo para establecer la hora: presionar la tecla MODO, se establece un cursor titilante
   en el primer dígito de la hora. Si se desea modificar este dígito presionar incrementar o
   decrementar. Luego mover el cursor al siguiente dígito presionando el pulsador 1,
   incrementar o decrementar. Para corregir dígito anterior, se puede desplazar cursor hasta el
   final y volver a la posición inicial (cursor circular). Continuar con los dígitos de minutos y
   segundos. Finalmente, para introducir los cambios en la hora presionar ENTER.
   Utilizar el Led RGB para indicar mediante diferente color, el modo en el cual se encuentra.
   b) Agregue el modo de configurar una alarma. Cuando se alcance dicho horario el reloj
   deberá mostrar en la consola intermitentemente el mensaje:
   HH:MM:SS ¡Alarma!
   Además generar una señal lumínica intermitente de alama mediante un LED de la placa.
   Para cancelar la alarma presionar ENTER
   Debe utilizarse el sEOS cooperativo con interrupción única de timer (SysTick) para la
   planificación y despacho de las tareas en la misma.
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
/*------------------------------------------------------------------------------
                           includes
------------------------------------------------------------------------------*/
#include"main.h"
#include"sAPI.h"
#include"board_config.h"
#include"clock.h"
#include"Isr.h"
#include"pc_link.h"
#include"scheduler.h"
#include"led.h"
#include"system.h"
#include"keys.h"

/*------------------------------------------------------------------------------
                           main 
------------------------------------------------------------------------------*/

int main()
{
   /*------------------------------------------------------------------------------
                              inits
   ------------------------------------------------------------------------------*/
   SYSTEM_init();
   /*------------------------------------------------------------------------------
                              NORMAL tasks
   ------------------------------------------------------------------------------*/
   SCHEDULER_add_task(CLOCK_task_update, 0, 1000, NORMAL); // update every 1 second
   SCHEDULER_add_task(LED_toggle_task_update, 9, 1000, NORMAL); // blink led every 1 second
   /*------------------------------------------------------------------------------
                              ALWAYS tasks
   ------------------------------------------------------------------------------*/
   SCHEDULER_add_task(KEYS_button_task_update, 3, 50, ALWAYS); // update every 5 milliseconds
   SCHEDULER_add_task(PC_LINK_task_update, 4, 5, ALWAYS); // update every 5 milliseconds
   SCHEDULER_add_task(CLOCK_task_check_alarm_update, 8, 500, ALWAYS); // update every 5 milliseconds
   /*------------------------------------------------------------------------------
                              ENTER tasks
   ------------------------------------------------------------------------------*/
   SCHEDULER_add_task(CLOCK_task_set_hour_update, 0, 100, ENTER); // update every 1 second
   /*------------------------------------------------------------------------------
                              ALARM tasks
   ------------------------------------------------------------------------------*/
   SCHEDULER_add_task(CLOCK_task_set_alarm_update, 8, 100, ALARM); // update every 1 second
   /*------------------------------------------------------------------------------
                              DOALARM task
   ------------------------------------------------------------------------------*/
   SCHEDULER_add_task(CLOCK_do_alarm, 8, 100, DOALARM); // update every 1 second
   SCHEDULER_add_task(LED_toggle_task_update2, 10, 300, DOALARM); // blink led every 1 second
   /*------------------------------------------------------------------------------
                              start scheduler
   ------------------------------------------------------------------------------*/
   SCHEDULER_start(1); // initialize SCHDULER with tick rate 1
   /*------------------------------------------------------------------------------
                              main loop
   ------------------------------------------------------------------------------*/
   while(1)
   {
      // dispatch tasks
      SCHEDULER_dispatch_task();
   }
   return 0;
}
