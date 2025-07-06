#include "delay.h"

/*******************************************************************
 * Function  : 毫秒级别延时
 * Parameter : u16 xms：延时时长
 * Return    : void
 * Comment   : 时钟源：21Mhz
               最大计数值：1677 7216
							 最大定时时长：798ms
********************************************************************/
void delay_ms(u16 xms)  
{
	//1、选择时钟源，为了延长定时时长，采用外部参考时钟：21Mhz
	SysTick->CTRL &= ~(1<<2);
	//2、填入计数值
	SysTick->LOAD = xms * 21000-1;
	//3、开启计数器
	SysTick->VAL = 0;
	SysTick->CTRL |= (1<<0);
	//4、等待计数完成
	while((SysTick->CTRL & (1<<16)) == 0);
	//5、关闭计数器
	SysTick->CTRL &= ~(1<<0);
}


/*******************************************************************
 * Function  : 微秒级别延时
 * Parameter : u16 xus：延时时长
 * Return    : void
 * Comment   : 时钟源：21Mhz
               最大计数值：1677 7216
							 最大定时时长：798000us
********************************************************************/
void delay_us(u16 xus)  
{
	//1、选择时钟源，为了延长定时时长，采用外部参考时钟：21Mhz
	SysTick->CTRL &= ~(1<<2);
	//2、填入计数值
	SysTick->LOAD = xus * 21-1;
	//3、开启计数器
	SysTick->VAL = 0;
	SysTick->CTRL |= (1<<0);
	//4、等待计数完成
	while((SysTick->CTRL & (1<<16)) == 0);
	//5、关闭计数器
	SysTick->CTRL &= ~(1<<0);
}


/*******************************************************************
 * Function  : 微秒级别不限时延时
 * Parameter : u16 xus：延时时长
 * Return    : void
 * Comment   : 时钟源：21Mhz
               最大计数值：1677 7216						 
********************************************************************/
void delay_random(u32 time)  
{
	u32 cnt = 0;
	u32 temp = 0;
	cnt = time / 500;
	temp = time % 500;
	for(u32 i=0;i < cnt;i++)
	{
		delay_ms(500);
	}
	if(temp != 0)
	{
		delay_ms(temp);
	}
}

