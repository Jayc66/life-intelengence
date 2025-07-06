#ifndef KEY_H
#define KEY_H

#include "stm32f4xx.h"

#define Key1_Press GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1
#define Key2_Press GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0
#define Key3_Press GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0

void Key_Init();
u8 Key_Scan();

#endif
