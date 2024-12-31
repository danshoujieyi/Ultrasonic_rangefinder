//
// Created by 刘嘉俊 on 24-11-10.
//

#ifndef LIU_C8T6_MYRTC_H
#define LIU_C8T6_MYRTC_H
#include "stm32f1xx_hal.h"
//#include "rtc.h"
#include "stdio.h"

#define  RTC_unique_ID	(0x5A52)
extern unsigned char time_data[8];
extern char* weekdays[7];
void HALGetDataTime(void);


char * CalWeek(int y, int m, int d);
void RtcGetDateTime(unsigned char* year, unsigned char* month, unsigned char* day, unsigned char* hour, unsigned char* minute, unsigned char* sec);
void RtcSetDateTime(unsigned char year, unsigned char month, unsigned char day, unsigned char hour, unsigned char minute, unsigned char sec);
unsigned int   GetDiffDay(unsigned int dateBegin, unsigned int dateEnd);
unsigned int   CalculateDate(unsigned int fromDate, unsigned int diffDay);
unsigned int   RtcGetDate(void);
#endif //LIU_C8T6_MYRTC_H
