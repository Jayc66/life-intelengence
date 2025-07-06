#include "led.h"

void Led_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 1. ʹ��GPIODʱ�ӣ���AHB1�����ϣ�
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    // 2. ����LED���ţ����������50MHz��   
    GPIO_InitStructure.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      // �������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     // ����ģʽ
    GPIO_Init(LED_PORT,&GPIO_InitStructure);

    // 3. ��ʼ���ر�����LED���ߵ�ƽϨ��
    GPIO_SetBits(LED_PORT, LED1_PIN | LED2_PIN | LED3_PIN);

}

void Led_Close_ALL()
{
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
}