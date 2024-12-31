#ifndef _BSP_ULTRASONIC_H_
#define _BSP_ULTRASONIC_H_

#include "stm32f1xx_hal.h"
#include "Delay_us.h"
#include "tim.h"

#define PORT_SR04             GPIOB

#define GPIO_TRIG             GPIO_PIN_10
#define GPIO_ECHO             GPIO_PIN_11

#define PORT_TIMER            TIM3

#define TIMER_IRQ             TIM3_IRQn
#define TIMER_IRQHandler      TIM3_IRQHandler

#define SR04_TRIG(x)          HAL_GPIO_WritePin(PORT_SR04, GPIO_TRIG, x?GPIO_PIN_SET:GPIO_PIN_RESET)
#define SR04_ECHO()           HAL_GPIO_ReadPin(PORT_SR04, GPIO_ECHO)

void Ultrasonic_Init(void);   // 超声波初始化
//float Hcsr04GetLength(void);  // 获取超声波测距的距离
uint32_t Get_TIMER_Count(void);
float Hcsr04GetLength_offset(void);
float MedianFilter(void); // 中位值滤波算法

float GetCompensatedDistance(void); // 分区间补偿
#endif