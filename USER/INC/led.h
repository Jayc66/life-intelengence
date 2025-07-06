#ifndef LED_H
#define LED_H

#include "stm32f4xx.h"

// LED引脚定义
#define LED1_PIN    GPIO_Pin_12
#define LED2_PIN    GPIO_Pin_13
#define LED3_PIN    GPIO_Pin_14
#define LED_PORT    GPIOD

// 控制宏（直接操作寄存器实现高效开关）
#define LED1_ON    GPIO_ResetBits(LED_PORT, LED1_PIN)  
#define LED1_OFF   GPIO_SetBits(LED_PORT, LED1_PIN)
#define LED1_FZ    GPIO_ToggleBits(LED_PORT,LED1_PIN);

#define LED2_ON    GPIO_ResetBits(LED_PORT, LED2_PIN)
#define LED2_OFF   GPIO_SetBits(LED_PORT, LED2_PIN)
#define LED2_FZ    GPIO_ToggleBits(LED_PORT,LED2_PIN);

#define LED3_ON    GPIO_ResetBits(LED_PORT, LED3_PIN)
#define LED3_OFF   GPIO_SetBits(LED_PORT, LED3_PIN)
#define LED3_FZ    GPIO_ToggleBits(LED_PORT,LED3_PIN);

void Led_Init();
void Led_Close_ALL();

#endif