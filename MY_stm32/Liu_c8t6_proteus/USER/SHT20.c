//
// Created by 刘嘉俊 on 24-11-7.
//

#include "SHT20.h"
#include "Delay_us.h"
#include "stdio.h"
void SHT20_GPIO_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 使能 GPIOB 时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // 配置 SDA 和 SCL 引脚
    GPIO_InitStruct.Pin = GPIO_SDA | GPIO_SCL;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // 推挽输出模式  开漏或推挽
    GPIO_InitStruct.Pull = GPIO_NOPULL; // 不用上拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // 高速
    HAL_GPIO_Init(PORT_SHT20, &GPIO_InitStruct);

    // 将 SDA 和 SCL 引脚设置为高
    HAL_GPIO_WritePin(PORT_SHT20, GPIO_SDA | GPIO_SCL, GPIO_PIN_SET);
}

/******************************************************************
 * 函 数 名 称：IIC_Start
 * 函 数 说 明：IIC起始信号
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void IIC_Start(void)
{
    SDA_OUT();

    SCL(0);
    SDA(1);
    SCL(1);

    Delay_us(5);

    SDA(0);
    Delay_us(5);
    SCL(0);
    Delay_us(5);

}

/******************************************************************
 * 函 数 名 称：IIC_Stop
 * 函 数 说 明：IIC停止信号
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void IIC_Stop(void)
{
    SDA_OUT();

    SCL(0);
    SDA(0);

    SCL(1);
    Delay_us(5);
    SDA(1);
    Delay_us(5);

}

/******************************************************************
 * 函 数 名 称：IIC_Send_Ack
 * 函 数 说 明：主机发送应答
 * 函 数 形 参：0应答  1非应答
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void IIC_Send_Ack(uint8_t ack)
{
    SDA_OUT();
    SCL(0);
    SDA(0);
    Delay_us(5);
    if(!ack) SDA(0);
    else     SDA(1);
    SCL(1);
    Delay_us(5);
    SCL(0);
    SDA(1);
}

/******************************************************************
 * 函 数 名 称：IIC_Wait_Ack
 * 函 数 说 明：等待从机应答
 * 函 数 形 参：无
 * 函 数 返 回：1=无应答   0=有应答
 * 作       者：LC
 * 备       注：无
******************************************************************/
uint8_t IIC_Wait_Ack(void)
{
    char ack = 0;
    unsigned char ack_flag = 10;
    SDA_IN();
    SDA(1);
    Delay_us(5);
    SCL(1);
    Delay_us(5);
    while( (SDA_GET()==1) && ( ack_flag ) )
    {
        ack_flag--;
        Delay_us(5);
    }

    if( ack_flag <= 0 )
    {
        IIC_Stop();
        return 1;
    }
    else
    {
        SCL(0);
        SDA_OUT();
    }
    return ack;
}
/******************************************************************
 * 函 数 名 称：IIC_Write
 * 函 数 说 明：IIC写一个字节
 * 函 数 形 参：dat写入的数据
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void IIC_Write(uint8_t data)
{
    int i = 0;
    SDA_OUT();
    SCL(0);//拉低时钟开始数据传输

    for( i = 0; i < 8; i++ )
    {
        SDA( (data & 0x80) >> 7 );
        Delay_us(2);
        data<<=1;
        Delay_us(6);
        SCL(1);
        Delay_us(4);
        SCL(0);
        Delay_us(4);

    }
}

/******************************************************************
 * 函 数 名 称：IIC_Read
 * 函 数 说 明：IIC读1个字节
 * 函 数 形 参：无
 * 函 数 返 回：读出的1个字节数据
 * 作       者：LC
 * 备       注：无
******************************************************************/
uint8_t IIC_Read(void)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
    {
        SCL(0);
        Delay_us(5);
        SCL(1);
        Delay_us(5);
        receive<<=1;
        if( SDA_GET() )
        {
            receive|=1;
        }
        Delay_us(5);
    }
    return receive;
}

/******************************************************************
 * 函 数 名 称：SHT20_Read
 * 函 数 说 明：测量温湿度
 * 函 数 形 参：regaddr寄存器地址 regaddr=0xE3测量温度 =0xE5测量湿度
 * 函 数 返 回：regaddr=0xE3时返回温度，regaddr=0xE5时返回湿度
 * 作       者：LC
 * 备       注：无
******************************************************************/
float SHT20_Read(uint8_t regaddr)
{
    unsigned char data_H = 0;
    unsigned char data_L = 0;
    float temp = 0;
    IIC_Start();
    IIC_Write(0x80|0);
    if( IIC_Wait_Ack() == 1 ) printf("error -1\r\n");
    IIC_Write(regaddr);
    if( IIC_Wait_Ack() == 1 ) printf("error -2\r\n");

    do{
        Delay_us(10);
        IIC_Start();
        IIC_Write(0x80|1);

    }while( IIC_Wait_Ack() == 1 );

    Delay_us(20);

    data_H = IIC_Read();
    IIC_Send_Ack(0);
    data_L = IIC_Read();
    IIC_Send_Ack(1);
    IIC_Stop();

    if( regaddr == 0xf3 )
    {
        temp = ((data_H<<8)|data_L) / 65536.0 * 175.72 - 46.85;
    }
    if( regaddr == 0xf5 )
    {
        temp = ((data_H<<8)|data_L) / 65536.0 * 125.0 - 6;
    }
    return temp;

}