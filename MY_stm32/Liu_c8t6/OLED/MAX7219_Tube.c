//
// Created by 刘嘉俊 on 24-10-8.
//

#include "MAX7219_Tube.h"



/******************************************************************
 * 函 数 名 称：MAX7219_GPIO_Init
 * 函 数 说 明：初始化MAX7219引脚
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void MAX7219_GPIO_Init(void)
{
    // 定义 GPIO 初始化结构体
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能 GPIO 时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    // 配置 MAX7219 的引脚为输出模式
    GPIO_InitStructure.Pin = GPIO_MAX7219_CLK ; // 设置要初始化的引脚
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; // 设置为推挽输出
    GPIO_InitStructure.Pull = GPIO_NOPULL; // 撤销上下拉电阻
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; // 设置 GPIO 输出速度为高速

    // 初始化 GPIO 引脚
    HAL_GPIO_Init(PORT_MAX7219_A, &GPIO_InitStructure);

    // 配置 MAX7219 的引脚为输出模式
    GPIO_InitStructure.Pin = GPIO_MAX7219_DIN | GPIO_MAX7219_CS; // 设置要初始化的引脚
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; // 设置为推挽输出
    GPIO_InitStructure.Pull = GPIO_NOPULL; // 撤销上下拉电阻
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; // 设置 GPIO 输出速度为高速

    // 初始化 GPIO 引脚
    HAL_GPIO_Init(PORT_MAX7219_B, &GPIO_InitStructure);
}

/******************************************************************
 * 函 数 名 称：Write_Max7219_byte
 * 函 数 说 明：向MAX7219写入字节
 * 函 数 形 参：dat写入的数据
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void Write_Max7219_byte(uint8_t dat)
{
    uint8_t i;
    MAX7219_CS(0);
    for(i=8;i>=1;i--)
    {
        MAX7219_CLK(0);
        if( dat&0x80 )
        {
            MAX7219_DIN(1);
        }
        else
        {
            MAX7219_DIN(0);
        }
        dat=dat<<1;
        MAX7219_CLK(1);
    }
}

/******************************************************************
 * 函 数 名 称：Write_Max7219
 * 函 数 说 明：向MAX7219写入数据
 * 函 数 形 参：address写入地址  dat写入数据
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void Write_Max7219(uint8_t address, uint8_t dat)
{
    MAX7219_CS(0);
    Write_Max7219_byte(address);           //写入地址，即数码管编号1-8
    // 判断是否需要显示小数点
    if (dat == 10)
    {
        // 下面的逻辑需要根据您所用数码管的具体情况来编写
        // 通常将小数点设置为相应单位的位置
        // 假设小数点的位置在某个地址，比如显存的特定位置
        Write_Max7219_byte(0x80); // 示例：可能的操作，使用合适的编码实现小数点
    }
    else
    {
        Write_Max7219_byte(dat); // 写入正常的数据
    }
    MAX7219_CS(1);
}

/******************************************************************
 * 函 数 名 称：Write_Max7219_2
 * 函 数 说 明：向第二片MAX7219写入数据
 * 函 数 形 参：address写入地址  dat写入数据
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：只有接入第二片MAX7219才可以用
******************************************************************/
void Write_Max7219_2(uint8_t address,uint8_t dat)
{
    MAX7219_CS(0);
    Write_Max7219_byte(address);   //写入地址，即数码管编号1-8
    Write_Max7219_byte(dat);       //写入数据，即数码管显示内容
    MAX7219_CLK(1);
    Write_Max7219_byte(0X00);      //对第一片执行空操作
    Write_Max7219_byte(0X00);
    MAX7219_CS(1);
}

/******************************************************************
 * 函 数 名 称：Write_Max7219_AllOff
 * 函 数 说 明：控制第一片MAX7219的全部数码管全灭
 * 函 数 形 参：address写入地址  dat写入数据
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：
******************************************************************/
void Write_Max7219_AllOff(void)
{
    int i =  0;
    for( i = 1; i < 9; i++ )
    {
        MAX7219_CS(0);
        Write_Max7219_byte(i);   //写入地址，即数码管编号1-8
        Write_Max7219_byte(15);  //全灭
        MAX7219_CS(1);
    }

}
/******************************************************************
 * 函 数 名 称：MAX7219_Init
 * 函 数 说 明：MAX7219初始化
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void MAX7219_Init(void)
{
    MAX7219_GPIO_Init();             //引脚初始化
    Write_Max7219(0x09, 0xff);       //译码方式：BCD码
//Write_Max7219(0x09, 0x00);       //译码方式：无译码
    Write_Max7219(0x0a, 0x03);       //亮度
    Write_Max7219(0x0b, 0x07);       //扫描界限；4个数码管显示
    Write_Max7219(0x0c, 0x01);       //掉电模式：0，普通模式：1
    Write_Max7219(0x0f, 0x01);       //显示测试：1；测试结束，正常显示：0
}



//// 八段数码管显示在定时器二的定时周期中
//// 八段数码管实时显示报警阈值
//
//Write_Max7219(1, (int)(cnt / 1000));
//Write_Max7219(2, (int)((cnt / 100)%10));
//Write_Max7219(3, (int)((cnt % 100) / 10));
//Write_Max7219(4, (int)(cnt % 10));
//// 八段数码管实时显示测量距离，分辨率0.01cm
//displayValue = (int)(distance_offset * 100);
//integerPart = displayValue / 100;
//decimalPart = displayValue % 100;
//if (integerPart > 99)
//{
//integerPart = 99;
//decimalPart = 0;
//}
//Write_Max7219(5, (integerPart / 10));
//Write_Max7219(6, (integerPart % 10) | 0x80);
//Write_Max7219(7, (decimalPart / 10));
//Write_Max7219(8, (decimalPart % 10));
//// 报警
//if (displayValue <= cnt*100)
//{
//Buzzer_Alarm((int)distance);
//HAL_IWDG_Refresh(&hiwdg);   //看门狗喂狗
//}