#include "led.h"

int Led_Count;//LED blink Delay 
TimerHandle_t ledTimer;
//LED initialization
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); //Enable APB Clock
	
	GPIO_InitStructure.GPIO_Pin = LED_PIN;				//LED Pin
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//Push pull output
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	GPIO_Init(LED_PORT, &GPIO_InitStructure);			//Initialize LED GPIO
	GPIO_SetBits(LED_PORT,LED_PIN);

	ledTimer = xTimerCreate(
		"led1sec", 			// name
		pdMS_TO_TICKS(1000),	// period
		pdTRUE,								// auto reload
		(void*) 0,						// timer ID
		led_task							// callback
	);
	xTimerStart(ledTimer, pdMS_TO_TICKS(0)); 
}


void led_task(void *pvParameters)
{
      LED=~LED;        //0 on, 1 off   
      //delay_ms(5000);			
     // vTaskDelay(Led_Count); //Delay 
    
}  
