#ifndef __uart_H
#define __uart_H
#include "sys.h"
#include "oled.h"
#include "system.h"

#define UART_TASK_PRIO 	5
#define UART_STK_SIZE 	128

void uart_init(u32 baudRate);
void uart_task(void *pvParameters);
void usart3_send(u8 data);
void changeUARTPeriod(int newPeriod);
int USART3_IRQHandler(void);
void APP_Show(void);
void OLED_ShowCheckConfirming(void);
void OLED_ShowChecking(void);
void OLED_ShowCheckResult(void);
#endif


