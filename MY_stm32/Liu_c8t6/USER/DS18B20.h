//
// Created by 刘嘉俊 on 24-11-9.
//

#ifndef LIU_C8T6_DS18B20_H
#define LIU_C8T6_DS18B20_H

#include "stm32f1xx_hal.h"

// 端口移植
#define RCC_DQ          __HAL_RCC_GPIOA_CLK_ENABLE() // 使能GPIOB时钟
#define PORT_DQ         GPIOA
#define GPIO_DQ         GPIO_PIN_3

// 设置 DQ 输出模式
#define DQ_OUT()  {\
                        GPIO_InitTypeDef GPIO_InitStruct = {0};\
                        GPIO_InitStruct.Pin = GPIO_DQ;\
                        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; /* 推挽输出模式 */\
                        GPIO_InitStruct.Pull = GPIO_NOPULL; /* 不上拉 */\
                        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; /* 高速 */\
                        HAL_GPIO_Init(PORT_DQ, &GPIO_InitStruct);\
                     }

// 设置 DQ 输入模式
#define DQ_IN()   {\
                        GPIO_InitTypeDef GPIO_InitStruct = {0};\
                        GPIO_InitStruct.Pin = GPIO_DQ;\
                        GPIO_InitStruct.Mode = GPIO_MODE_INPUT; /* 输入模式 */\
                        GPIO_InitStruct.Pull = GPIO_PULLUP; /* 上拉 */\
                        HAL_GPIO_Init(PORT_DQ, &GPIO_InitStruct);\
                   }

// 获取 DQ 引脚的电平变化
#define DQ_GET()        HAL_GPIO_ReadPin(PORT_DQ, GPIO_DQ)

// DQ 输出
#define DQ(x)           HAL_GPIO_WritePin(PORT_DQ, GPIO_DQ, (x ? GPIO_PIN_SET : GPIO_PIN_RESET))



void DS18B20_Reset(void);
uint8_t DS18B20_Check(void);
char DS18B20_GPIO_Init(void);
void DS18B20_Start(void);
float DS18B20_GetTemperture(void);


#endif //LIU_C8T6_DS18B20_H
