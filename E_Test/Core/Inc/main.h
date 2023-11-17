/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define Red_Num 20 // ��������ͷ�������ݵĴ���


#define LED_text HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin)
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define KEY5_Pin GPIO_PIN_4
#define KEY5_GPIO_Port GPIOA
#define KEY5_EXTI_IRQn EXTI4_IRQn
#define KEY6_Pin GPIO_PIN_5
#define KEY6_GPIO_Port GPIOA
#define KEY6_EXTI_IRQn EXTI9_5_IRQn
#define BEEP_Pin GPIO_PIN_5
#define BEEP_GPIO_Port GPIOC
#define OLED_SCL_Pin GPIO_PIN_0
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_1
#define OLED_SDA_GPIO_Port GPIOB
#define RED_Pin GPIO_PIN_15
#define RED_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_10
#define KEY1_GPIO_Port GPIOC
#define KEY2_Pin GPIO_PIN_11
#define KEY2_GPIO_Port GPIOC
#define KEY3_Pin GPIO_PIN_12
#define KEY3_GPIO_Port GPIOC
#define KEY4_Pin GPIO_PIN_2
#define KEY4_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */