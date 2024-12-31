#ifndef __MAX7219__H__
#define __MAX7219__H__
#include "stm32f1xx_hal.h"                  // Device header
#include "math.h"
#define clk GPIO_PIN_7
#define load GPIO_PIN_0
#define din GPIO_PIN_1

#define LOAD(x)  HAL_GPIO_WritePin(GPIOB, load, (GPIO_PinState)x)
#define CLK(x)   HAL_GPIO_WritePin(GPIOA, clk, (GPIO_PinState)x)
#define DIN(x)   HAL_GPIO_WritePin(GPIOB, din, (GPIO_PinState)x)

#define LINE  0x0A
#define E     0x0B
#define H     0x0C
#define L     0x0D
#define P     0x0E
#define blank 0x0F

void MAX7219_Init(uint8_t BCD,uint8_t Intensity,uint8_t DisplayNum);
void MAX7219_ShowNum(uint8_t location,uint8_t num,uint8_t dot);
void MAX7219_Clear(void);
void MAX7219_Stopwatch(uint16_t time);
#endif
