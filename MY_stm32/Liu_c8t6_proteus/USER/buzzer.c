//
// Created by 刘嘉俊 on 24-9-19.
//

#include "buzzer.h"
#include "iwdg.h"
// GPIO 初始化函数

void Buzzer_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 使能GPIOA时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 配置PA11为推挽输出
    GPIO_InitStruct.Pin = BUZZER_PIN; // 使用PA11控制蜂鸣器
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // 推挽输出模式
    GPIO_InitStruct.Pull = GPIO_PULLUP; // 上拉电阻
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // 高速
    HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);
}

// 打开蜂鸣器
void Buzzer_On(void)
{
    // 在proteus仿真中是高电平触发
    //HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET); // 低电平驱动蜂鸣器
    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);
}

// 关闭蜂鸣器
void Buzzer_Off(void)
{
    //HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET); // 高电平关闭蜂鸣器
    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
}

void Buzzer_Alarm(int distance) // distance 为报警距离
{
    // 根据距离调整延迟时间，距离越近，延迟越短
    // 设定最小和最大延迟
    int minDelay = 50; // 最小延迟时间
    int maxDelay = 400; // 最大延迟时间
    int delayTime = (distance * (maxDelay - minDelay)) / 100; // 计算延迟时间

    // 限制延迟时间在合理范围内
    if (delayTime < minDelay) {
        delayTime = minDelay; // 保证不低于最小延迟
    }

    for (int i = 0; i < 5; i++) // 产生五声
    {
        Buzzer_On();            // 打开蜂鸣器
        HAL_Delay(delayTime);   // 按计算的延迟时间保持
        Buzzer_Off();          // 关闭蜂鸣器
        HAL_Delay(delayTime);   // 按计算的延迟时间间隔
    }
    HAL_IWDG_Refresh(&hiwdg);   //看门狗喂狗
}