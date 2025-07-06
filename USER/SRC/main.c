#include "main.h"
char arr[]={0};
int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	char receivedData[10]={0};   // 123\r\n \0   "123\r\n"
	Led_Init();
	Beep_Init();
	Usart1_Init(115200);
	Key_Init();
	u8 key;
	LED1_ON;
	USART1_IRQ_Config_receive();
	while(1)
	{
		printf("STM32 Usart÷–∂œ≤‚ ‘\r\n");

		LED1_FZ;
		delay_ms(1500);
	}		
}

void SysTick_Handler(void)
{
	LED1_FZ;
}
