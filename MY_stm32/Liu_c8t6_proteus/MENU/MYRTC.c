//
// Created by 刘嘉俊 on 24-11-10.
//
#include "MYRTC.h"
/* Includes ------------------------------------------------------------------*/
///*设置系统时间*/
//HAL_StatusTypeDef HAL_RTC_SetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format)
///*读取系统时间*/
//HAL_StatusTypeDef HAL_RTC_GetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format)
///*设置系统日期*/
//HAL_StatusTypeDef HAL_RTC_SetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, uint32_t Format)
///*读取系统日期*/
//HAL_StatusTypeDef HAL_RTC_GetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, uint32_t Format)
///*启动报警功能*/
//HAL_StatusTypeDef HAL_RTC_SetAlarm(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Format)
///*设置报警中断*/
//HAL_StatusTypeDef HAL_RTC_SetAlarm_IT(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Format)
///*报警时间回调函数*/
//__weak void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
///*写入后备储存器*/
//void HAL_RTCEx_BKUPWrite(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister, uint32_t Data)
///*读取后备储存器*/
//uint32_t HAL_RTCEx_BKUPRead(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister

//extern RTC_HandleTypeDef hrtc;  //RTC句柄
//RTC_DateTypeDef HALGetData = {0};  //获取日期结构体
//RTC_TimeTypeDef HALGetTime = {0};   //获取时间结构体
//
//void HALGetDataTime(void)
//{
//    HAL_RTC_GetDate(&hrtc, &HALGetData, RTC_FORMAT_BIN);
//    HAL_RTC_GetTime(&hrtc, &HALGetTime, RTC_FORMAT_BIN);
//    /* Display date Format : yy/mm/dd */
//    printf("%02d/%02d/%02d\r\n",2000 + HALGetData.Year, HALGetData.Month, HALGetData.Date);
//    printf("Weekday : %d\r\n", HALGetData.WeekDay);
//    /* Display time Format : hh:mm:ss */
//    printf("%02d:%02d:%02d\r\n",HALGetTime.Hours, HALGetTime.Minutes, HALGetTime.Seconds);
//
//}
//
//static const unsigned char MONTH_DAY[] = { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//
//// 计算星期函数
//char * CalWeek(int y, int m, int d){
//    if(m==1||m==2)
//    {
//        m+=12;
//        y--;
//    }
//    int week =  (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7+1;
//    switch(week)
//    {
//        case 0 : return weekdays[0]; break;
//        case 1 : return  weekdays[1]; break;
//        case 2 : return  weekdays[2]; break;
//        case 3 : return  weekdays[3]; break;
//        case 4 : return  weekdays[4]; break;
//        case 5 : return  weekdays[5]; break;
//        case 6 : return  weekdays[6]; break;
//        default : return NULL; break;
//    }
//}
//
///**
//  * @brief  Enters the RTC Initialization mode.
//  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
//  *                the configuration information for RTC.
//  * @retval HAL status
//  */
//static HAL_StatusTypeDef RTC_EnterInitMode(RTC_HandleTypeDef* hrtc)
//{
//    uint32_t tickstart = 0U;
//
//    tickstart = HAL_GetTick();
//    /* Wait till RTC is in INIT state and if Time out is reached exit */
//    while((hrtc->Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET)
//    {
//        if((HAL_GetTick() - tickstart) >  RTC_TIMEOUT_VALUE)
//        {
//            return HAL_TIMEOUT;
//        }
//    }
//
//    /* Disable the write protection for RTC registers */
//    __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);
//
//
//    return HAL_OK;
//}
//
///**
//  * @brief  Exit the RTC Initialization mode.
//  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
//  *                the configuration information for RTC.
//  * @retval HAL status
//  */
//static HAL_StatusTypeDef RTC_ExitInitMode(RTC_HandleTypeDef* hrtc)
//{
//    uint32_t tickstart = 0U;
//
//    /* Disable the write protection for RTC registers */
//    __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
//
//    tickstart = HAL_GetTick();
//    /* Wait till RTC is in INIT state and if Time out is reached exit */
//    while((hrtc->Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET)
//    {
//        if((HAL_GetTick() - tickstart) >  RTC_TIMEOUT_VALUE)
//        {
//            return HAL_TIMEOUT;
//        }
//    }
//
//    return HAL_OK;
//}
//
//
///**
//  * @brief  Read the time counter available in RTC_CNT registers.
//  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
//  *                the configuration information for RTC.
//  * @retval Time counter
//  */
//static uint32_t RTC_ReadTimeCounter(RTC_HandleTypeDef* hrtc)
//{
//    uint16_t high1 = 0U, high2 = 0U, low = 0U;
//    uint32_t timecounter = 0U;
//
//    high1 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);
//    low   = READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT);
//    high2 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);
//
//    if (high1 != high2)
//    { /* In this case the counter roll over during reading of CNTL and CNTH registers,
//       read again CNTL register then return the counter value */
//        timecounter = (((uint32_t) high2 << 16U) | READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT));
//    }
//    else
//    { /* No counter roll over during reading of CNTL and CNTH registers, counter
//       value is equal to first value of CNTL and CNTH */
//        timecounter = (((uint32_t) high1 << 16U) | low);
//    }
//
//    return timecounter;
//}
//
///**
//  * @brief  Write the time counter in RTC_CNT registers.
//  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
//  *                the configuration information for RTC.
//  * @param  TimeCounter: Counter to write in RTC_CNT registers
//  * @retval HAL status
//  */
//static HAL_StatusTypeDef RTC_WriteTimeCounter(RTC_HandleTypeDef* hrtc, uint32_t TimeCounter)
//{
//    HAL_StatusTypeDef status = HAL_OK;
//
//    /* Set Initialization mode */
//    if(RTC_EnterInitMode(hrtc) != HAL_OK)
//    {
//        status = HAL_ERROR;
//    }
//    else
//    {
//        /* Set RTC COUNTER MSB word */
//        WRITE_REG(hrtc->Instance->CNTH, (TimeCounter >> 16U));
//        /* Set RTC COUNTER LSB word */
//        WRITE_REG(hrtc->Instance->CNTL, (TimeCounter & RTC_CNTL_RTC_CNT));
//
//        /* Wait for synchro */
//        if(RTC_ExitInitMode(hrtc) != HAL_OK)
//        {
//            status = HAL_ERROR;
//        }
//    }
//
//    return status;
//}


//
//void RtcSetDateTime(unsigned char year, unsigned char month, unsigned char date,
//                    unsigned char hour, unsigned char minute, unsigned char second)
//{
//    unsigned int temp = (unsigned int)hour * 3600 +
//                        (unsigned int)minute * 60 + second +
//                        GetDiffDay(101, (unsigned int)year * 10000 +
//                                        (unsigned int)month * 100 + date) * 3600 * 24;
//
//    RTC_WriteTimeCounter(&hrtc, temp);
//}
//
//void RtcGetDateTime(unsigned char* year, unsigned char* month, unsigned char* day,
//                    unsigned char* hour, unsigned char* minute, unsigned char* sec)
//{
//    unsigned int timecounter = RTC_ReadTimeCounter(&hrtc);
//    unsigned int date = timecounter / (3600 * 24);
//    if (hour != NULL && minute != NULL && sec != NULL)
//    {
//        *hour = timecounter / 3600 % 24;
//        *minute = timecounter / 60 % 60;
//        *sec = timecounter % 60;
//    }
//    if (year != NULL && month != NULL && day != NULL)
//    {
//        date = CalculateDate(101, date);
//        *year = date / 10000 % 100;
//        *month = date / 100 % 100;
//        *day = date % 100;
//    }
//}
//static unsigned char getMonthDay(unsigned char year, unsigned char month)
//{
//    if (month == 2) {
//        if (((2000 + year) % 4 == 0 && (2000 + year) % 100 != 0) || (2000 + year) % 400 == 0)
//        {
//            return 29;
//        }
//        else
//        {
//            return 28;
//        }
//    } else
//        return MONTH_DAY[month - 1];
//}
//
//unsigned int GetDiffDay(unsigned int dateBegin, unsigned int dateEnd)
//{
//    unsigned int sum = 0;
//    unsigned char year1, year2, month1, month2, day1, day2 = 0;
//
//    year1 = dateBegin / 10000;
//    year2 = dateEnd / 10000;
//    month1 = (dateBegin % 10000) / 100;
//    month2 = (dateEnd % 10000) / 100;
//    day1 = dateBegin % 100;
//    day2 = dateEnd % 100;
//
//    if(dateBegin > dateEnd)
//        return 0;
//
//    while (1)
//    {
//        if (year2 == year1 && month2 == month1)
//        {
//            sum += day2 - day1;
//            break;
//        }
//        else
//        {
//            sum += day2;
//            month2--;
//            if (month2 < 1 || month2 > 12)
//            {
//                month2 = 12;
//                year2--;
//            }
//            day2 = getMonthDay(year2, month2);
//        }
//    }
//    return sum;
//}
//
///* calculate date from 2000-01-01 */
//unsigned int CalculateDate(unsigned int fromDate, unsigned int diffDay)
//{
//    unsigned char year1, month1, day1, day2 = 0;
//
//    year1 = fromDate / 10000 % 100;
//    month1 = fromDate / 100 % 100;
//    day1 = fromDate % 100;
//
//    do {
//        if (month1 > 12) {
//            month1 = month1 - 12;
//            year1 = year1 + 1;
//        }
//
//        day2 = getMonthDay(year1, month1);
//
//        if (diffDay + day1 > day2) { /* next month */
//            diffDay = diffDay - (day2 - day1);
//            month1++;
//            day1 = 0;
//        } else { /* current month */
//            day1 += diffDay;
//            break;
//        }
//    } while (1);
//    return (unsigned int) year1 * 10000 + (unsigned int) month1 * 100 + (unsigned int) day1;
//}














