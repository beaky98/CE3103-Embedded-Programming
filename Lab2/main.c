#include "system.h"
#include "led.h"
#include "buzzer.h"
#include "show.h"
#include "button.h"
#include "uart.h"

#define START_TASK_PRIO			4
#define START_STK_SIZE 			256
TaskHandle_t StartTask_Handler;
void start_task(void *pvParameters);

int main(void)
{
	systemInit();
	
    xTaskCreate((TaskFunction_t ) start_task,
                (const char*    ) "start_task",
                (uint16_t       ) START_STK_SIZE,
                (void*          ) NULL,
                (UBaseType_t    ) START_TASK_PRIO,
                (TaskHandle_t*  ) &StartTask_Handler);
		
		vTaskStartScheduler();
							}

void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();

		xTaskCreate(song_task, "song_task", BUZZER_STK_SIZE, NULL, 3, NULL);
	
    vTaskDelete(StartTask_Handler);
    
    taskEXIT_CRITICAL();
}
