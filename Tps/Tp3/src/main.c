#include "board.h"
#include "sAPI.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"

#include "main.h"
#include "utils.h"
#include "UART.h"
#include "init.h"
 
static void prvPrintTask( void *pvParameters );
void prvReadTask(void *pvParameters);
uint8_t data;

char *pcStringsToPrint[] =
{
	"Task 1 ****************************************************\n",
	"Task 2 ----------------------------------------------------\n",
};


int main( void )
{
   initHardware();
   

   vUARTinit(115200);

   xTaskCreate(prvPrintTask, "Print1", 240, ( void * ) 0, 1, NULL );
   xTaskCreate(prvPrintTask, "Print2", 240, ( void * ) 1, 2, NULL );
   xTaskCreate(prvReadTask, "ReadData", 240, ( void * ) 1, 3, NULL );
   

   xTaskCreate(vUARTGatekeeperTask, "Gatekeeper", 240, NULL, 0, NULL );

   /* Start the scheduler so the created tasks start executing. */
   vTaskStartScheduler();

    /* If all is well we will never reach here as the scheduler will now be
    running the tasks.  If we do reach here then it is likely that there was
    insufficient heap memory available for a resource to be created. */
	for( ;; );
	return 0;
}

 
static void prvPrintTask( void *pvParameters )
{
int iIndexToString;

	iIndexToString = ( int ) pvParameters;

	for( ;; )
	{
		xQueueSendToBack(xUARTQueue, &( pcStringsToPrint[ iIndexToString ] ), 0 );

		//vTaskDelay(100);
		vTaskDelay( ( rand() & 0x1FF ) );
	}
} 
void prvReadTask(void *pvParameters)
{

   data = uartReadByte();
	for( ;; )
	{
		xQueueSendToBack(xUARTQueue, &data, 0 );

		vTaskDelay(100);
		//vTaskDelay( ( rand() & 0x1FF ) );
	}
}
