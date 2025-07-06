#include "key.h"
#include "delay.h"

void Key_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // ʹ��PA����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); // ʹ��PB����ʱ��

	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0;		  // ��ʼ������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;	  // ����ģʽ
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; // ��������
	GPIO_Init(GPIOA, &GPIO_InitStruct);			  // ����GPIO_InitStruct��ʼ��
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1; 	// ��ʼ������
	GPIO_Init(GPIOB, &GPIO_InitStruct);						// ����GPIO_InitStruct��ʼ��
}

u8 Key_Scan()  //��������+����ɨ�裨����ʶ��㰴�ͳ�����
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
