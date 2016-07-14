#include "board.h"
#include "sAPI.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"

#include "main.h"

static void initHardware(void);

/* char* itoa(int value, char* result, int base) { */
/*    // check that the base if valid */
/*    if (base < 2 || base > 36) { *result = '\0'; return result; } */
/*  */
/*    char* ptr = result, *ptr1 = result, tmp_char; */
/*    int tmp_value; */
/*  */
/*    do { */
/*       tmp_value = value; */
/*       value /= base; */
/*       *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)]; */
/*    } while ( value ); */
/*  */
/*    // Apply negative sign */
/*    if (tmp_value < 0) *ptr++ = '-'; */
/*    *ptr-- = '\0'; */
/*    while(ptr1 < ptr) { */
/*       tmp_char = *ptr; */
/*       *ptr--= *ptr1; */
/*       *ptr1++ = tmp_char; */
/*    } */
/*    return result; */
/* } */

static void initHardware(void)
{
   /* Inicializar la placa */
   boardConfig();
   
   Board_Init(); // <-- NECESARIO PARA QUE COMPILE

   /* Inicializar DigitalIO */
   digitalConfig( 0, ENABLE_DIGITAL_IO );

   /* Configuración de pines de entrada para
	   Teclas de la CIAA-NXP */
   digitalConfig( TEC1, INPUT );
   digitalConfig( TEC2, INPUT );
   digitalConfig( TEC3, INPUT );
   digitalConfig( TEC4, INPUT );

   /* Configuración de pines de salida para
	   Leds de la CIAA-NXP */
   digitalConfig( LEDR, OUTPUT );
   digitalConfig( LEDG, OUTPUT );
   digitalConfig( LEDB, OUTPUT );
   digitalConfig( LED1, OUTPUT );
   digitalConfig( LED2, OUTPUT );
   digitalConfig( LED3, OUTPUT );
    
   /* Inicializar Uart */
   uartConfig( UART_USB, 115200 );
}

void vPrintString( char * string){
   uartWriteString( UART_USB, (uint8_t *) string );
}
void vPrintNumber( int32_t number){
   uint8_t uartBuff[10];
   /* Conversión de number entero a ascii con base decimal */
   itoa( number, uartBuff, 10 ); /* 10 significa decimal */
   /* Enviar number */
   uartWriteString(UART_USB, uartBuff);
}
void vPrintStringAndNumber( char * string, int32_t number){
   vPrintString( string );
   vPrintNumber( number );
   vPrintString( "\r\n" );
}

/*==================[external functions definition]==========================*/


/* The tasks to be created.  Two instances are created of the sender task while
only a single instance is created of the receiver task. */
static void UARTGatekeeperTask( void *pvParameters );
/*-----------------------------------------------------------*/

/* Declare a variable of type xQueueHandle.  This is used to store the queue
that is accessed by all three tasks. */
xQueueHandle xQueue;


int main( void )
{
	 initHardware();
   
}


