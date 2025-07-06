#ifndef USART_H
#define USART_H

#include "stm32f4xx.h"
#include "string.h"
#include "led.h"
void Usart1_Init(u32 baud);
void Usart1_Send_Byte(char data);
char Usart1_Recv_Byte(void);
void Usart1_Send_String(char *str);
void Usart1_Recv_String(char *str);
void USART1_IRQ_Config_send();
void USART1_IRQ_Config_receive();

typedef struct {
 char buff[50];
 char size;

}AAAusart1;

#endif