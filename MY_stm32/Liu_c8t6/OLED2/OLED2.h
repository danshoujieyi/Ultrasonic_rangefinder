//
// Created by 刘嘉俊 on 24-11-9.
//

#ifndef LIU_C8T6_OLED2_H
#define LIU_C8T6_OLED2_H

#include "stm32f1xx_hal.h"
#include "stdlib.h"

extern uint8_t OLED_GRAM[144][8];
#define Brightness 0xFF

//-----------------OLED端口定义----------------

#define OLED_SCL_Clr() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET) // SCL
#define OLED_SCL_Set() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET)

#define OLED_SDA_Clr() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET) // DIN
#define OLED_SDA_Set() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET)

#define OLED_CMD  0 // 写命令
#define OLED_DATA 1 // 写数据


void OLED2_ClearPoint(uint8_t x, uint8_t y);
void OLED2_ColorTurn(uint8_t i);
void OLED2_DisplayTurn(uint8_t i);
void OLED2_I2C_Start(void);
void OLED2_I2C_Stop(void);
void OLED2_I2C_WaitAck(void);
void OLED_Send_Byte(uint8_t dat);
void OLED_WR_Byte(uint8_t dat, uint8_t mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t);
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode);
void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r);
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size1, uint8_t mode);
void OLED_ShowChar6x8(uint8_t x, uint8_t y, uint8_t chr, uint8_t mode);
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t size1, uint8_t mode);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size1, uint8_t mode);
void OLED_ShowChinese(uint8_t x, uint8_t y, uint8_t num, uint8_t size1, uint8_t mode);
void OLED_ScrollDisplay(uint8_t num, uint8_t space, uint8_t mode);
void OLED_ShowPicture(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, uint8_t BMP[], uint8_t mode);
void OLED_Init(void);

#endif //LIU_C8T6_OLED2_H
