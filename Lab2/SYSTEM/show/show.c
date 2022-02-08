#include "show.h"

void show_task(void *pvParameters)
{
   u32 lastWakeTime = getSysTickCnt();
   while(1)
    {	

			vTaskDelayUntil(&lastWakeTime, F2T(RATE_50_HZ));

			oled_show(); 
				
    }
}  

void show_timer_task(void *pvParameters)
{
   u32 lastWakeTime = getSysTickCnt();
   while(1)
    {	

			vTaskDelayUntil(&lastWakeTime, F2T(RATE_50_HZ));

			oled_timer_show(); 
				
    }
}  

void oled_show(void)
{  
     //To DO
	 
	 
	 //call some function in oled to display something
	int count = 0;
	while(1){
		OLED_ShowString(0,0, "KK");
		OLED_ShowNumber(0,28, count, 5, 15);
		count++;
		delay_ms(1000);
		OLED_Refresh_Gram(); //refresh the OLED RAM
		if(count == 60) count = 0;
	}
	
   
	 //OLED_Refresh_Gram(); //refresh the OLED RAM

	  		
	}

void oled_timer_show(void)
{  
  //To Do Exercise C
	int sec = 0;
	int min = 0;
	OLED_ShowString(30,40,"KEEKONG");
	OLED_ShowString(0,0,"Sec");
	OLED_ShowString(0,30,"Min");
	while (1) {
		vTaskDelay(1000);
		OLED_ShowNumber(0,10,sec,16,16);
		OLED_ShowNumber(0,50,min,16,16);
		
		if (sec == 59) {
			sec = 0;
			min++;
			
		}
		else {
		sec++;
		}
		OLED_Refresh_Gram(); //refresh the OLED RAM
	}
	
	  		
	}

