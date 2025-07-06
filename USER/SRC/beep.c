#include "beep.h"

/******
������  ����  PD15 
�ߵ�ƽ��Ӧ

**/


void Beep_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 1. ʹ��GPIODʱ�ӣ���AHB1�����ϣ�
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    // 2. ����Beep���ţ����������50MHz��
    GPIO_InitStructure.GPIO_Pin = Beep_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      // �������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     // ����ģʽ
    GPIO_Init(Beep_PORT,&GPIO_InitStructure);

    // 3. ��ʼ���رշ��������͵�ƽϨ��
    GPIO_ResetBits(Beep_PORT, Beep_PIN);

}

