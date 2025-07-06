#include "key.h"
#include "delay.h"

void Key_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // 使能PA外设时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); // 使能PB外设时钟

	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0;		  // 初始化引脚
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;	  // 输入模式
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; // 无上下拉
	GPIO_Init(GPIOA, &GPIO_InitStruct);			  // 根据GPIO_InitStruct初始化
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1; 	// 初始化引脚
	GPIO_Init(GPIOB, &GPIO_InitStruct);						// 根据GPIO_InitStruct初始化
}

u8 Key_Scan()  //按键消抖+按键扫描（可以识别点按和长按）
{

	if(Key1_Press)
	{
		delay_ms(80);
		if(Key1_Press)
		{
			while(Key1_Press)
			return 1;
		}
	}
	if(Key2_Press)
	{
		delay_ms(80);
		if(Key2_Press)
		{
			while(Key2_Press)
			return 2;
		}

	}
	if(Key3_Press)
	{
		delay_ms(80);
		if(Key3_Press)
		{
			while(Key3_Press)
			return 3;
		}
	}
	return 0;

}
