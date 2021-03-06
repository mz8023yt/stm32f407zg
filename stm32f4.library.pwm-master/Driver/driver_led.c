#include "driver_led.h"

/**
 * @Description 初始化LED的GPIO(基于正点原子探索者开发板上的LED电路)
 */
void LED_Init(void)
{
	/*创建一个GPIO初始化结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*第一步：使能GPIOF时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

	/*第二步：配置GPIO引脚模式*/
	/*设置要配置Pin9和Pin10*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	/*设置为输出模式*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	/*设置为推挽输出*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	/*设置输出速率为100M*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	/*设置为上拉模式*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	/*通过GPIO_InitStructure结构体初始化GPIOF*/
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	/*设置GPIOF的Pin9和Pin10初始值为高电平，初始LED不亮*/
	GPIO_SetBits(GPIOF, GPIO_Pin_9 | GPIO_Pin_10);
}
