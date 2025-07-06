#include "beep.h"

/******
蜂鸣器  引脚  PD15 
高电平响应

**/


void Beep_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 1. 使能GPIOD时钟（在AHB1总线上）
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    // 2. 配置Beep引脚（推挽输出，50MHz）
    GPIO_InitStructure.GPIO_Pin = Beep_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     // 高速模式
    GPIO_Init(Beep_PORT,&GPIO_InitStructure);

    // 3. 初始化关闭蜂鸣器（低电平熄灭）
    GPIO_ResetBits(Beep_PORT, Beep_PIN);

}

