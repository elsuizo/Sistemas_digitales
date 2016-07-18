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
 

static char *pcStringsToPrint[] =
{
	"Task 1 ****************************************************\n",
	"Task 2 ----------------------------------------------------\n",
};

static void prvPrintTask( void *pvParameters );

int main( void )
{
	 initHardware();
   
    /* Before a queue is used it must be explicitly created.  The queue is created
	to hold a maximum of 5 character pointers. */
    xUARTQueue = xQueueCreate( 5, sizeof( char * ) );

	/* The tasks are going to use a pseudo random delay, seed the random number
	generator. */

	/* Check the queue was created successfully. */
	if(xUARTQueue != NULL)
	{
		/* Create two instances of the tasks that send messages to the gatekeeper.
		The	index to the string they attempt to write is passed in as the task
		parameter (4th parameter to xTaskCreate()).  The tasks are created at
		different priorities so some pre-emption will occur. */
		xTaskCreate(prvPrintTask, "Print1", 240, ( void * ) 0, 1, NULL );
		xTaskCreate(prvPrintTask, "Print2", 240, ( void * ) 1, 2, NULL );

		/* Create the gatekeeper task.  This is the only task that is permitted
		to access standard out. */
		xTaskCreate(vUARTGatekeeperTask, "Gatekeeper", 240, NULL, 0, NULL );

		/* Start the scheduler so the created tasks start executing. */
		vTaskStartScheduler();
	}

    /* If all is well we will never reach here as the scheduler will now be
    running the tasks.  If we do reach here then it is likely that there was
    insufficient heap memory available for a resource to be created. */
	for( ;; );
	return 0;
}

 
static void prvPrintTask( void *pvParameters )
{
int iIndexToString;

	/* Two instances of this task are created so the index to the string the task
	will send to the gatekeeper task is passed in the task parameter.  Cast this
	to the required type. */
	iIndexToString = ( int ) pvParameters;

	for( ;; )
	{
		/* print out the string, not directly but by passing the string to the
		gatekeeper task on the queue.  the queue is created before the scheduler is
		started so will already exist by the time this task executes.  a block time
		is not specified as there should always be space in the queue. */
		xQueueSendToBack(xUARTQueue, &( pcStringsToPrint[ iIndexToString ] ), 0 );

		/* wait a pseudo random time.  note that rand() is not necessarily
		re-entrant, but in this case it does not really matter as the code does
		not care what value is returned.  in a more secure application a version
		of rand() that is known to be re-entrant should be used - or calls to
		rand() should be protected using a critical section. */
		//vtaskdelay( ( rand() & 0x1ff ) );
	}
}
