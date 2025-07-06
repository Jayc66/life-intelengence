#ifndef BEEP_H
#define BEEP_H

#include "stm32f4xx.h"

#define Beep_PIN     GPIO_Pin_15
#define Beep_PORT    GPIOD

#define Beep_OFF    GPIO_ResetBits(Beep_PORT, Beep_PIN)
#define Beep_ON     GPIO_SetBits(Beep_PORT, Beep_PIN)

void Beep_Init();


#endif 