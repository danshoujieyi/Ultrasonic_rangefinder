//
// Created by 刘嘉俊 on 24-11-7.
//

#ifndef LIU_C8T6_DELAY_US_H
#define LIU_C8T6_DELAY_US_H

#include "stm32f1xx_hal.h"
#define CPU_FREQUENCY_MHZ    72		// STM32时钟主频

void Delay_us(__IO uint32_t delay);

#endif //LIU_C8T6_DELAY_US_H
