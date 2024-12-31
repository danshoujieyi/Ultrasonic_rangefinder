#include "MAX7219.h"


/*写一个字节*/
void MAX7219_WriteByte (uint8_t byte)
{
	for(int i =0;i<8;i++)
	{
		CLK(0);
		DIN(byte&0x80);
		byte=byte<<1;
		CLK(1);
	}
}
/*写寄存器*/
void MAX7219_WriteReg(uint8_t Reg,uint8_t data)
{
	LOAD(0);
	MAX7219_WriteByte (Reg);
	MAX7219_WriteByte (data);
	LOAD(1);
}

/**
  * 函    数 显示内容 该函数为在BCD译码下的显示
  * 参    数 uint8_t location：在几位显示 1~8。
  * 参    数 uint8_t num：显示的数字（0~9，Line，E,H,L,P,blank）
  * 参    数 uint8_t dot: 是否需要小数点
  */
void MAX7219_ShowNum(uint8_t location,uint8_t num,uint8_t dot)
{
	if(dot==0)	MAX7219_WriteReg (location,num);
	else	
	{
		num |=0x80;
		MAX7219_WriteReg (location,num);		
	}
}

/**
  * 函    数 MAX7219_Clear 数码管清屏
  */
void MAX7219_Clear(void)
{
	for(int i=1;i<=8;i++)
	{
		MAX7219_ShowNum(i,blank,0);
	}
}
/**
  * 函    数 初始化MAX7219
  * 参    数 uint8_t BCD：D7~D0控制对于的数码管参与BCD译码。
  * 参    数 uint8_t Intensity：控制数码管的亮度 0~15(0表示熄灭)
  * 参    数 uint8_t DisplayNum: 数码管显示的个数：1~8
  */
void MAX7219_Init (uint8_t BCD,uint8_t Intensity,uint8_t DisplayNum)
{
// 使能GPIO时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

// GPIO初始化结构体
    GPIO_InitTypeDef GPIO_InitStruct = {0};

// 初始化GPIOB
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // 推挽输出
    GPIO_InitStruct.Pull = GPIO_NOPULL;         // 不上拉不下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // 速度优先级
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

// 初始化GPIOA
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	/*先配置五个控制寄存器*/
	MAX7219_WriteReg (0x0c,0x01);//设置为正常模式
	MAX7219_WriteReg (0x09,BCD);//设置BCD译码，8个数码管均使用BCD译码
	MAX7219_WriteReg (0x0a,Intensity);//设置亮度
	
	DisplayNum-=1;
	MAX7219_WriteReg (0x0b,DisplayNum);//8个数码管参与显示
	
	MAX7219_WriteReg (0x0f,0x01);//测试模式，所有数码管全亮
	HAL_Delay(100);
	MAX7219_WriteReg (0x0f,0x00);//正常显示模式
	
	MAX7219_Clear();
}












