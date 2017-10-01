/**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
＊　ファイル名： main_apl.c
＊　責務　　　： ユーザmain関数定義
＊　作成日　　： 2017/10/1
＊　作成者　　： kern-gt

＊　コンパイラ：CC-RX

＊　備考：
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~**/

/**----------------------------------------------------------------------------
<<利用ファイルのヘッダ>>
-----------------------------------------------------------------------------**/
/*#include "r_cg_macrodriver.h"*/
/*#include "r_cg_userdefine.h"*/
#include <stdio.h>
#include "iodefine.h"

/* Kernel includes. */
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/queue.h"


/**----------------------------------------------------------------------------
<<自ファイルのヘッダ>>
-----------------------------------------------------------------------------**/
#include "main_apl.c"


void vTask1(void *pvParameters)
{
	while(1) {
		//PORTD.DR.BIT.B1 = ~PORTD.DR.BIT.B1;
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void vTask2(void *pvParameters)
{
	while(1) {
		//PORTD.DR.BIT.B2 = ~PORTD.DR.BIT.B2;
		vTaskDelay(2000/portTICK_PERIOD_MS);
	}
}

/*-----------------------------------------------------------*/

void MainApplication(void)
{
	xTaskCreate(vTask1,"Task1",100,NULL,1,NULL);
	xTaskCreate(vTask2,"Task2",100,NULL,1,NULL);
	
	/* Create the queue. */
	vTaskStartScheduler();

	/* If all is well the next line of code will not be reached as the scheduler
	will be	running.  If the next line is reached then it is likely that there was
	insufficient heap available for the idle task to be created. */
	while(1);
}