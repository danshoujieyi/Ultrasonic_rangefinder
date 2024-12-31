/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "OLED2.h"
#include "STMflash.h"
#include "MENU.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
// 定义按键返回值
#define KEY0_Y  1  // PB12
#define KEY1_UP     2  // PB14
#define KEY2_DOWN  3  // PA11
#define KEY3_CLOSE  4
#define KEY4_USELESS	5

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern uint32_t cnt;
extern unsigned char msHcCount;
extern uint16_t Data_Distance;

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t c=5;
uint8_t get_key = 0;
uint8_t count = 1;
//要写入到STM32 FLASH的字符串数组
uint16_t my_Buffer[6]={0,0,0,0,0,0}; // 末尾用来存储报警阈值


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_4) != RESET)
    {
        if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)==0)
        cnt++;
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
    }
  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(CNT__Pin);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5) != RESET)
    {

        if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==0)
            cnt--;
        // 濞撳懘娅庢稉顓熸焽閺嶅洤绻?
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
    }
  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(CNT_B5_Pin);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt.
  */
void TIM1_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_IRQn 0 */
    if (__HAL_TIM_GET_FLAG(&htim1, TIM_FLAG_UPDATE) != RESET)  // 妫?鏌ュ畾鏃跺櫒涓柇鍙戠敓
    {
        if (__HAL_TIM_GET_IT_SOURCE(&htim1, TIM_IT_UPDATE) != RESET)
        {
            msHcCount++;
            __HAL_TIM_CLEAR_IT(&htim1, TIM_IT_UPDATE);  // 娓呴櫎涓柇鏍囧織
        }
    }
  /* USER CODE END TIM1_UP_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_IRQn 1 */

  /* USER CODE END TIM1_UP_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
    if (__HAL_TIM_GET_FLAG(&htim2, TIM_FLAG_UPDATE) != RESET)  // 妫?鏌ュ畾鏃跺櫒涓柇鍙戠敓
    {
        if (__HAL_TIM_GET_IT_SOURCE(&htim2, TIM_IT_UPDATE) != RESET)
        {


            __HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);  // 娓呴櫎涓柇鏍囧織
        }
    }
  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) != RESET)
    {
        if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)==0)
        {
            get_key=KEY0_Y;
            if(c%5==0&&(get_key==KEY0_Y)) {
                get_key=0;
                c++;
                OLED_Clear();
                menu_4();
            }

            if(c%5==1&&(get_key==KEY0_Y)) {
                get_key=0;
                c++;
                OLED_Clear();
                menu_5();
            }

            if(c%5==2&&(get_key==KEY0_Y)) {
                get_key=0;
                c++;
                OLED_Clear();
                menu_1();
                OLED_Refresh();
            }

            if(c%5==3&&(get_key==KEY0_Y)) {get_key=0;c++;OLED_Clear();menu_2();
                STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
                for(int i=0;i<6;i++){
                    my_Buffer[i]=datatemp[i];
                }
                Updata_menu2();
                count=1;
                Select_menu(1);
            }//选择初始位置OLED_Refresh();
            if(c%5==4&&(get_key==KEY0_Y)&&(count >= 1))
            {
                get_key = 0;
                count++;
                Select_menu(count);//选择位置
                if(count>=8)
                {	count=1;OLED_Clear();c++;}
            }
        }
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12);
    }

    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_14) != RESET)
    {
        if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)==0)
        {
            get_key=KEY1_UP;
            if(c%5==1&&(get_key==KEY1_UP)) {
                get_key=0;
                c--;
                OLED_Clear();
            }
            if(c%5==2&&(get_key==KEY1_UP)) {
                get_key=0;
                c--;
                OLED_Clear();
                menu_4();
            }
            if(c%5==3&&(get_key==KEY1_UP)) {
                get_key=0;
                c--;
                OLED_Clear();
                menu_5();
            }
            if(c%5==4&&(get_key==KEY1_UP)&&(count <= 8))
            {
                get_key = 0;
                count--;
                Select_menu(count);//选择位置
                if(count==0)
                {
                    c--;
                    OLED_Clear();
                    menu_1();
                }
            }
            if(c%5==4&&(get_key==KEY1_UP)&&(count == 0)) {
                get_key=0;
                c--;
                OLED_Clear();
                menu_1();
            }
        }
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_14);
    }

    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11) != RESET) {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == 0) {
            get_key = KEY2_DOWN;
            if (c % 5 == 4 && (get_key == KEY2_DOWN)) {
                get_key = 0;
                if (count == 1) {
                    for (int i = 6; i >= 1; i--) {
                        my_Buffer[i] = my_Buffer[i - 1];
                    }
                    my_Buffer[0] = Data_Distance;
                } else if (count != 1) {
                    Delete_select(count - 2, (u16 *) my_Buffer);
                }
                STMFLASH_Write(FLASH_SAVE_ADDR, (u16 *) my_Buffer, SIZE);
                Updata_menu2();//更新数据
            }
        }
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);
    }
  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
