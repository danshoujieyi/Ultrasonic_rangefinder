//
// Created by 刘嘉俊 on 24-11-7.
//

#ifndef LIU_C8T6_SHT20_H
#define LIU_C8T6_SHT20_H

#include "stm32f1xx_hal.h"
#include "I2C.h"

#define T_ADDR     0xf3   // 温度
#define PH_ADDR    0xf5   // 湿度

// 端口移植
#define RCC_SHT20         __HAL_RCC_GPIOA_CLK_ENABLE() // 使能GPIOB时钟
#define PORT_SHT20        GPIOA

#define GPIO_SDA           GPIO_PIN_12
#define GPIO_SCL           GPIO_PIN_11

// 设置SDA输出模式
#define SDA_OUT()   {\
                        GPIO_InitTypeDef GPIO_InitStruct = {0};\
                        GPIO_InitStruct.Pin = GPIO_SDA;\
                        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;\
                        GPIO_InitStruct.Pull = GPIO_NOPULL;\
                        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;\
                        HAL_GPIO_Init(PORT_SHT20, &GPIO_InitStruct);\
                     }

// 设置SDA输入模式
#define SDA_IN()    {\
                        GPIO_InitTypeDef GPIO_InitStruct = {0};\
                        GPIO_InitStruct.Pin = GPIO_SDA;\
                        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;\
                        GPIO_InitStruct.Pull = GPIO_PULLUP;\
                        HAL_GPIO_Init(PORT_SHT20, &GPIO_InitStruct);\
                    }

// 获取SDA引脚的电平变化
#define SDA_GET()       HAL_GPIO_ReadPin(PORT_SHT20, GPIO_SDA)

// SDA与SCL输出
#define SDA(x)          HAL_GPIO_WritePin(PORT_SHT20, GPIO_SDA, (x ? GPIO_PIN_SET : GPIO_PIN_RESET))
#define SCL(x)          HAL_GPIO_WritePin(PORT_SHT20, GPIO_SCL, (x ? GPIO_PIN_SET : GPIO_PIN_RESET))

void SHT20_GPIO_INIT(void);
float SHT20_Read(unsigned char regaddr);


#endif //LIU_C8T6_SHT20_H
