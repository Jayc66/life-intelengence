#include "usart.h"
#include "stdio.h"


//函数功能：USART1初始化
//函数参数：u32 baud 波特率
//函数返回值：无
//说明：PA9---USART1_TX PA10---USART1_RX
void Usart1_Init(u32 baud)
{
	//1、开启时钟（GPIOA、USART1）
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//2、对GPIO进行初始化，将PA9和PA10配置为复用模式
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//3、将PA9和PA10复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	//4、对USART1进行初始化
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = baud;//波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控制
	USART_InitStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;//发送接收
	USART_InitStruct.USART_Parity = USART_Parity_No;//无奇偶校验
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//1bit停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//8bit字长
	USART_Init(USART1,&USART_InitStruct);
	//5、使能USART1
	USART_Cmd(USART1,ENABLE);
}

//发送单字节函数
void Usart1_Send_Byte(char data)
{
	USART_SendData(USART1,data);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == 0);
}

//接收单字节函数
char Usart1_Recv_Byte(void)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == 0);
	return USART_ReceiveData(USART1);
}

//发送字符串函数
void Usart1_Send_String(char *str)  
{
	do{
		Usart1_Send_Byte(*str);
		str++;
	 }while(*str != '\0');
}

//接收字符串函数
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

//输出重定向
//printf()的子函数：fputc
int fputc(int ch,FILE *f)
{
	//替换为开发者重定向的发送单字节函数
	Usart1_Send_Byte(ch);
	return ch;
}

void USART1_IRQ_Config_send()
{
	//1、初始化NVIC
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	//2、使能发送数据寄存器中断
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
	printf ("进入发送中断\r\n");
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		data = USART_ReceiveData(USART1);
		rec.buff[rec.size] = data;
		rec.size++;
		if(data == '\n')
		{
			rec.buff[rec.size] = '\0';
			printf("\r\n接收数据:%s",rec.buff);
			printf("接收长度:%d\r\n",rec.size-2);
			rec.size = 0;
		
		if(strcmp(rec.buff,"111\r\n")==0)
		{
			printf("进入接受中断，指令正确，LED2反转\r\n");
			LED2_FZ;
			
		}
		else printf("无效指令\r\n");
		
	}
	}
}

