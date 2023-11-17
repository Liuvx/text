/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "oled.h"
#include "openmv.h"
#include "beep.h"
#include "key.h"
#include "gui.h"
#include "duoji.h"
#include "stdio.h"
#include "stm32f4xx_it.h"
#include "my_uart.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define Wide 144 // Black
#define Long 114
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern uint8_t Usart1_ReadBuf[255]; // 串口1 缓冲数组
extern uint8_t Usart1_ReadCount;    // 串口1 接收字节计数
extern uint8_t uart3_rxbuff;
extern Point Red_center[1];
extern int AVer_Num;
extern int X;
extern int Y;
extern int Stop_Num;
extern int Road_Num;
// extern Point Black_Point[4];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
// int Open_Num = 0;
int angle_shang = 30;
int angle_xia = 30;
int Angle_Change = 0; // 1为角度设置，0为脉冲设置
int Maichong_Shang = 910;
int Maichong_xia = 2500; // 右上
void (*current_operation_index)();
uint32_t func_index = 1;  // 初始显示欢迎界面
uint8_t last_index = 127; // last初始为无效值
int i;
int Road = 0;
extern int PID_Num;
// int Maichong_Shang = Shang_Min;
// int Maichong_xia = Xia_Min;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// int Road = 0;
//  Point Center_Point[1]={{51, 48}};//中心点坐标
Point Bian_Point[5] = {
    {139, 12},  // 右上
    {134, 131}, // 右下
    {12, 134},  // 左下
    {12, 16},   // 左上
    {139, 12},  // 右上
};              // 铅笔痕迹的四点坐标
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  int numPoints = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM2_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */
  OLED_Init(); // 初始化OLED

  PID_init(); // PID参数初始化

  HAL_UART_Receive_IT(&huart1, &USART3_RX_Data, 1); // 打开串口接收中断
  HAL_UART_Receive_IT(&huart2, &USART2_RX_Data, 1); // 打开串口接收中断;
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);         //***定时器初始化
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);         //***定时器初始化
  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);         //***定时器初始化
  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);         //***定时器初始化
  HAL_TIM_Base_Start_IT(&htim2);                    // 定时器2的定时功能开，1ms
  HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    Menu_OLED(); // 执行菜单命令

    // }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
// void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
//{
//  EXTI line interrupt detected
//  if(__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != RESET)
//  {
//   // __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
//    HAL_GPIO_EXTI_Callback(GPIO_Pin);
//		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
//  }
//

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == KEY5_Pin)
  {
    if (HAL_GPIO_ReadPin(KEY5_GPIO_Port, KEY5_Pin) == 0)
    {
      LED_text;
      if (Stop_Num == 0)
        Stop_Num = 1;
      else
        Stop_Num = 0;
      while (!HAL_GPIO_ReadPin(KEY5_GPIO_Port, KEY5_Pin))
        ; // 松手检测
    }
   // __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
  }
  if (GPIO_Pin == KEY6_Pin)
  {
    if (HAL_GPIO_ReadPin(KEY6_GPIO_Port, KEY6_Pin) == 0)
    {
		LED_text;
				PID_Num=0;
                Stop_Num = 0;
                PID_Duoji_Shang.target_val = O_Center[0].y;
                PID_Duoji_Xia.target_val = O_Center[0].x;
               // Beep_DD();
               // OLED_Clear();
                //func_index = 1;
      while (!HAL_GPIO_ReadPin(KEY6_GPIO_Port, KEY6_Pin)); // 松手检测
    }
    
  }
  __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
  
}
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
