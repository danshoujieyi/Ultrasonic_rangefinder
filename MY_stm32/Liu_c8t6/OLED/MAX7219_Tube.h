//
// Created by 刘嘉俊 on 24-10-8.
//

#ifndef INC_1_SHUDIANKESHE_MAX7219_TUBE_H
#define INC_1_SHUDIANKESHE_MAX7219_TUBE_H

#include "stm32f1xx_hal.h"
#include "stdio.h"

#define RCC_MAX7219             RCC_APB2Periph_GPIOB

#define PORT_MAX7219_B            GPIOB
#define PORT_MAX7219_A            GPIOA

#define GPIO_MAX7219_CLK        GPIO_PIN_7 //PA7
#define GPIO_MAX7219_DIN        GPIO_PIN_1 //PB1
#define GPIO_MAX7219_CS         GPIO_PIN_0 //PB0

#define MAX7219_CLK(X) HAL_GPIO_WritePin(PORT_MAX7219_A, GPIO_MAX7219_CLK, (X) ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define MAX7219_DIN(X) HAL_GPIO_WritePin(PORT_MAX7219_B, GPIO_MAX7219_DIN, (X) ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define MAX7219_CS(X)  HAL_GPIO_WritePin(PORT_MAX7219_B, GPIO_MAX7219_CS, (X) ? GPIO_PIN_SET : GPIO_PIN_RESET)

void Write_Max7219(uint8_t address,uint8_t dat);
void Write_Max7219_2(uint8_t address,uint8_t dat);
void Write_Max7219_AllOff(void);
void MAX7219_Init(void);


#endif //INC_1_SHUDIANKESHE_MAX7219_TUBE_H
