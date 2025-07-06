#include "led.h"

void Led_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 1. 使能GPIOD时钟（在AHB1总线上）
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    // 2. 配置LED引脚（推挽输出，50MHz）   
    GPIO_InitStructure.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     // 高速模式
    GPIO_Init(LED_PORT,&GPIO_InitStructure);

    // 3. 初始化关闭所有LED（高电平熄灭）
    GPIO_SetBits(LED_PORT, LED1_PIN | LED2_PIN | LED3_PIN);

}

void Led_Close_ALL()
{
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
}