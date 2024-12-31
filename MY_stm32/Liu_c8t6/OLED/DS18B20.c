//
// Created by 刘嘉俊 on 24-11-9.
//

#include "DS18B20.h"
#include "Delay_us.h"
/******************************************************************
 * 函 数 名 称：bsp_ds18b20_GPIO_Init
 * 函 数 说 明：MLX90614的引脚初始化
 * 函 数 形 参：无
 * 函 数 返 回：1未检测到器件   0检测到器件
 * 作       者：LC
 * 备       注：无
******************************************************************/
char DS18B20_GPIO_Init(void)
{
    unsigned char ret = 255;

    // 使能 GPIO 时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_DQ; // 使用 GPIO_DQ 引脚
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // 推挽输出
    GPIO_InitStruct.Pull = GPIO_NOPULL; // 不上拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // 高速
    HAL_GPIO_Init(PORT_DQ, &GPIO_InitStruct); // 初始化引脚

    ret = DS18B20_Check(); // 检测器件是否存在
    return ret;
}

/******************************************************************
 * 函 数 名 称：DS18B20_Read_Byte
 * 函 数 说 明：从DS18B20读取一个字节
 * 函 数 形 参：无
 * 函 数 返 回：读取到的字节数据
 * 作       者：LC
 * 备       注：无
******************************************************************/
uint8_t DS18B20_Read_Byte(void)
{
    uint8_t i=0,dat=0;

    for (i=0;i<8;i++)
    {
        DQ_OUT();//设置为输入模式
        DQ(0); //拉低
        Delay_us(2);
        DQ(1); //释放总线
        DQ_IN();//设置为输入模式
        Delay_us(12);
        dat>>=1;
        if( DQ_GET() )
        {
            dat=dat|0x80;
        }
        Delay_us(50);
    }
    return dat;
}

/******************************************************************
 * 函 数 名 称：DS18B20_Write_Byte
 * 函 数 说 明：写一个字节到DS18B20
 * 函 数 形 参：dat：要写入的字节
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void DS18B20_Write_Byte(uint8_t dat)
{
    uint8_t i;
    DQ_OUT();//设置输出模式
    for (i=0;i<8;i++)
    {
        if ( (dat&0x01) ) //写1
        {
            DQ(0);
            Delay_us(2);
            DQ(1);
            Delay_us(60);
        }
        else //写0
        {
            DQ(0);//拉低60us
            Delay_us(60);
            DQ(1);//释放总线
            Delay_us(2);
        }
        dat=dat>>1;//传输下一位
    }
}

/******************************************************************
 * 函 数 名 称：DS18B20_Check
 * 函 数 说 明：检测DS18B20是否存在
 * 函 数 形 参：无
 * 函 数 返 回：1:未检测到DS18B20的存在  0:存在
 * 作       者：LC
 * 备       注：无
******************************************************************/
uint8_t DS18B20_Check(void)
{
    uint8_t timeout=0;
    //复位DS18B20
    DQ_OUT(); //设置为输出模式
    DQ(0); //拉低DQ
    Delay_us(750); //拉低750us
    DQ(1); //拉高DQ
    Delay_us(15);  //15us

    //设置为输入模式
    DQ_IN();
    //等待拉低，拉低说明有应答
    while ( DQ_GET() &&timeout<200)
    {
        timeout++;//超时判断
        Delay_us(1);
    };
    //设备未应答
    if(timeout>=200)
        return 1;
    else
        timeout=0;

    //等待18B20释放总线
    while ( !DQ_GET() &&timeout<240)
    {
        timeout++;//超时判断
        Delay_us(1);
    };
    //释放总线失败
    if(timeout>=240)
        return 1;

    return 0;
}

/******************************************************************
 * 函 数 名 称：DS18B20_Start
 * 函 数 说 明：DS18B20开始温度转换
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void DS18B20_Start(void)
{
    DS18B20_Check();                //查询是否有设备应答
    DS18B20_Write_Byte(0xcc);   //对总线上所有设备进行寻址
    DS18B20_Write_Byte(0x44);   //启动温度转换
}

/******************************************************************
 * 函 数 名 称：DS18B20_GetTemperture
 * 函 数 说 明：从ds18b20得到温度值
 * 函 数 形 参：无
 * 函 数 返 回：温度数据
 * 作       者：LC
 * 备       注：无
******************************************************************/
float DS18B20_GetTemperture(void)
{
    uint16_t temp;
    uint8_t dataL=0,dataH=0;
    float value;

    DS18B20_Start();
    DS18B20_Check();
    DS18B20_Write_Byte(0xcc);//对总线上所有设备进行寻址
    DS18B20_Write_Byte(0xbe);// 读取数据命令
    dataL=DS18B20_Read_Byte(); //LSB
    dataH=DS18B20_Read_Byte(); //MSB
    temp=(dataH<<8)+dataL;//整合数据

    if(dataH&0X80)//高位为1，说明是负温度
    {
        temp=(~temp)+1;
        value=temp*(-0.0625);
    }
    else
    {
        value=temp*0.0625;
    }
    return value;
}