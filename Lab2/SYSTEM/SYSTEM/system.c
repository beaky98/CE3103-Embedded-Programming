#include "system.h"

unsigned char temp_show;

u8 Flag_Stop=1;

void systemInit(void)
{
	JTAG_Set(JTAG_SWD_DISABLE);     
	JTAG_Set(SWD_ENABLE);           
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	delay_init();					          
	LED_Init();                     
  BUZZER_Init();             	
	OLED_Init(); 
	Button_Init();
	uart_init(115200);
	

}
