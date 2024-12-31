/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "OLED2.h"
#include "MENU.h"
#include "MAX7219.h"
#include "HCSR04.h"
#include "buzzer.h"
//#include "AHT10.h"
#include "SHT20.h"
#include "DS18B20.h"
//#include "MYRTC.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// 传感器数据
float temperature = 0,humidity = 0,temperature_ds18 = 0;
float temperature_1000 = 0,humidity_100 = 0;

// 原始距离与修正距离
float distance[2] = {0};
// 显示补偿
float distance_1000 = 0;
float distance_offset_1000 = 0;

// 报警阈值
uint32_t cnt = 30;

// 八段数码管显示计算用值
int displayValue = 0;
int integerPart = 0;
int decimalPart = 0;

// 温湿度补偿参数
float temperature_compensation = 0.606;
float humidity_compensation = 0.0124;

//距离显示用值
uint16_t Data_Distance = 0;
extern uint8_t c;
extern int get_key;
// flash存储数组
extern uint16_t datatemp[6];

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// 时间存储函数
unsigned char time_data[8] = {0};
char *weekdays[7] = {
        "Sunday",    // 0
        "Monday",    // 1
        "Tuesday",   // 2
        "Wednesday", // 3
        "Thursday",  // 4
        "Friday",    // 5
        "Saturday"   // 6
};
char *weekdays_temp[1];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
    //SHT20_GPIO_INIT();
    //AHT10_Init();
    SHT20_GPIO_INIT();
    DS18B20_GPIO_Init();
    Ultrasonic_Init();
    MAX7219_Init(0XFF,8,8);// 1110 0111
    OLED_Init();

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_IWDG_Init();
  /* USER CODE BEGIN 2 */
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_Base_Start_IT(&htim2);
    //HAL_Delay(1000);
    menu_3();//初始化显示菜单一
    //menu_4();
    //menu_5();
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

      // 传感器数据获取

      temperature = SHT20_Read(T_ADDR);
      humidity = SHT20_Read(PH_ADDR);
      //AHT10_Read_predata(&humidity,&temperature);
      // Hcsr04GetLength_offset();
      // distance[1] = MedianFilter(); // 测量距离且中位值滤波
      distance[1] = GetCompensatedDistance();  // 获取七次距离然后中位值滤波算法，最后进行分区间补偿
      temperature_ds18 = DS18B20_GetTemperture();
      Data_Distance = (uint16_t)distance[1];

      // 打印时钟
      //HALGetDataTime();
//      RtcGetDateTime(time_data,
//                     time_data+1,
//                     time_data+2,
//                     time_data+3,
//                     time_data+4,
//                     time_data+5
//      );
//      weekdays_temp[0] = CalWeek(time_data[0], time_data[1], time_data[2]);
//      printf("%s\n", weekdays_temp[0]);
      printf("20%02d/%02d/%02d\t",time_data[0], time_data[1], time_data[2]);
      printf("%02d:%02d:%02d\r\n",time_data[3], time_data[4], time_data[5]);
      printf("相对湿度: %f %%\n", humidity);
      printf("摄氏温度: %f ℃\n", temperature);
      printf("原始距离: %f cm\n", distance[0]);
      printf("修正距离: %f cm\n", distance[1]);
      printf("整数距离: %d cm\n", Data_Distance);
      printf("温度 = %.2f\r\n\n", temperature_ds18);
        // 八段数码管显示在定时器二的定时周期中
        // 八段数码管实时显示报警阈值

      MAX7219_ShowNum(1, (int)(cnt / 1000),0);
      MAX7219_ShowNum(2, (int)((cnt / 100)%10),0);
      MAX7219_ShowNum(3, (int)((cnt % 100) / 10),0);
      MAX7219_ShowNum(4, (int)(cnt % 10),0);
        // 八段数码管实时显示测量距离，分辨率0.01cm
        displayValue = (int)(distance[1] * 100);
        integerPart = displayValue / 100;
        decimalPart = displayValue % 100;
        if (integerPart > 99)
        {
            integerPart = 99;
            decimalPart = 0;
        }
      MAX7219_ShowNum(5, (integerPart / 10),0);
      MAX7219_ShowNum(6, (integerPart % 10) ,1);
      MAX7219_ShowNum(7, (decimalPart / 10),0);
      MAX7219_ShowNum(8, (decimalPart % 10),0);
      // 报警
      if (displayValue <= cnt*100)
      {
          Buzzer_Alarm((int)distance);
          HAL_IWDG_Refresh(&hiwdg);   //看门狗喂狗
      }

      // OLED显示修正
      temperature_1000 = temperature*1000;
      humidity_100 = humidity*100;
      distance_1000 = distance[0]*1000;
      distance_offset_1000 = distance[1]*1000;

      // OLED显示
      if(c%5==3)
      {
          Display_Array[0]=Display_Array[75];
          Retrude(Display_Array);
          Dotting(Display_Array,1);
          Dotting(Display_Array,0);
          OLED_ShowNum(98,56,Data_Distance,3,8,1);
          OLED_ShowNum(87,56,Display_Array[0],2,8,1);
          OLED_Refresh();
      }

      else if(c%5==4)
      {
          OLED_ShowNum(80,0,Data_Distance,3,16,1);OLED_Refresh();
      }

      else if(c%5==1)
      {
          Updata_menu4();
      }
      else if(c%5 ==2){
          Updata_menu5();
          if (displayValue <= cnt*100)
          {
              OLED_ShowChinese(80,48,25,16,1);
          }else {OLED_ShowChinese(80,48,26,16,1);}
          OLED_Refresh();
      }

      else if(c%5 == 0){
          menu_3();
          OLED_ShowNum(80,48,Data_Distance,3,16,1);
          OLED_Refresh();
      }
      Display_Array[75]=(Data_Distance+1)/10+1;

      HAL_IWDG_Refresh(&hiwdg);   //看门狗喂狗
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
