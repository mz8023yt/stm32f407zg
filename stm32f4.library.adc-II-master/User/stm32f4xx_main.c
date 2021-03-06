#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "explore_usart.h"
#include "driver_led.h"
#include "driver_lcd.h"
#include "driver_adc.h"

int main(void)
{
	u16 adcx;
	float voltage;
	u8 length;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Systick_Init(168);
	Usart_Init(115200);
	LED_Init();
	LCD_Init();
	Adc_Init();

	POINT_COLOR = RED;
	BACK_COLOR = WHITE;
	LCD_ClearScreen(BACK_COLOR);
	LCD_ShowString(80, 50, 440, 30, 24, "Photosensitive resistance");

	POINT_COLOR = BLUE;
	LCD_ShowString(30, 100, 450, 30, 24, "ADC Number:");
	LCD_ShowString(30, 130, 450, 30, 24, "Voltage:");

	while (1)
	{
		/*获取通道16的转换值，21次取平均*/
		adcx = Adc_GetAverageValue(ADC_Channel_5, 21);

		/*显示ADC采样后的原始值*/
		LCD_Fill(174, 100, 480, 130, BACK_COLOR);
		LCD_ShowInt(174, 100, adcx, 24);

		/*获取计算后的带小数的实际电压值，比如3.1111*/
		voltage = (float) adcx * (3.3 / 4096.0);

		/*显示电压值*/
		LCD_Fill(138, 130, 480, 160, BACK_COLOR);
		length = LCD_ShowFloat(138, 130, voltage, 24);
		LCD_ShowChar(138 + length * 12, 130, 'V', 24, DRAW_DIRECT);

		LED0 = !LED0;
		delay_ms(250);
	}
}
