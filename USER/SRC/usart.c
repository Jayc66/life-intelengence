#include "usart.h"
#include "stdio.h"


//�������ܣ�USART1��ʼ��
//����������u32 baud ������
//��������ֵ����
//˵����PA9---USART1_TX PA10---USART1_RX
void Usart1_Init(u32 baud)
{
	//1������ʱ�ӣ�GPIOA��USART1��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//2����GPIO���г�ʼ������PA9��PA10����Ϊ����ģʽ
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//3����PA9��PA10����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	//4����USART1���г�ʼ��
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = baud;//������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	USART_InitStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;//���ͽ���
	USART_InitStruct.USART_Parity = USART_Parity_No;//����żУ��
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//1bitֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//8bit�ֳ�
	USART_Init(USART1,&USART_InitStruct);
	//5��ʹ��USART1
	USART_Cmd(USART1,ENABLE);
}

//���͵��ֽں���
void Usart1_Send_Byte(char data)
{
	USART_SendData(USART1,data);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == 0);
}

//���յ��ֽں���
char Usart1_Recv_Byte(void)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == 0);
	return USART_ReceiveData(USART1);
}

//�����ַ�������
void Usart1_Send_String(char *str)  
{
	do{
		Usart1_Send_Byte(*str);
		str++;
	 }while(*str != '\0');
}

//�����ַ�������
void Usart1_Recv_String(char *str)  
{
	char data;
	do{
			data = Usart1_Recv_Byte();
		  *str = data;
		  str++;
	}while(data != '\n');
	*str = '\0';
}

//����ض���
//printf()���Ӻ�����fputc
int fputc(int ch,FILE *f)
{
	//�滻Ϊ�������ض���ķ��͵��ֽں���
	Usart1_Send_Byte(ch);
	return ch;
}

void USART1_IRQ_Config_send()
{
	//1����ʼ��NVIC
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	//2��ʹ�ܷ������ݼĴ����ж�
	USART_ITConfig(USART1,USART_IT_TXE,ENABLE );
	//void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState)
}


void USART1_IRQ_Config_receive()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1 ;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1 ;
	NVIC_Init(&NVIC_InitStruct);
	//void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
	USART_ITConfig(USART1,USART_IT_RXNE ,ENABLE);
}

AAAusart1 rec; 
void USART1_IRQHandler()
{
	char data;
	if(USART_GetITStatus(USART1,USART_IT_TXE) == SET)
	printf ("���뷢���ж�\r\n");
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		data = USART_ReceiveData(USART1);
		rec.buff[rec.size] = data;
		rec.size++;
		if(data == '\n')
		{
			rec.buff[rec.size] = '\0';
			printf("\r\n��������:%s",rec.buff);
			printf("���ճ���:%d\r\n",rec.size-2);
			rec.size = 0;
		
		if(strcmp(rec.buff,"111\r\n")==0)
		{
			printf("��������жϣ�ָ����ȷ��LED2��ת\r\n");
			LED2_FZ;
			
		}
		else printf("��Чָ��\r\n");
		
	}
	}
}

