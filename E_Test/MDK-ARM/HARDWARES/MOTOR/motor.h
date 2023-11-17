#ifndef __MOTOR_H
#define __MOTOR_H
#include "main.h"
#include "tim.h"

// AIN控制左边，BIN控制右边
// motor1为左边，motor2为右边
#define Motor_L_1_Port GPIOB
#define Motor_L_2_Port GPIOD
#define Motor_L_1_Pin GPIO_PIN_5
#define Motor_L_2_Pin GPIO_PIN_2 // 左边轮子

#define Motor_R_1_Port GPIOB
#define Motor_R_2_Port GPIOB
#define Motor_R_1_Pin GPIO_PIN_4
#define Motor_R_2_Pin GPIO_PIN_3// 右边轮子

#define L1RESET HAL_GPIO_WritePin(Motor_L_1_Port, Motor_L_1_Pin, GPIO_PIN_RESET)
#define L1SET HAL_GPIO_WritePin(Motor_L_1_Port, Motor_L_1_Pin, GPIO_PIN_SET)
#define L2RESET HAL_GPIO_WritePin(Motor_L_2_Port, Motor_L_2_Pin, GPIO_PIN_RESET) // 电机1
#define L2SET HAL_GPIO_WritePin(Motor_L_2_Port, Motor_L_2_Pin, GPIO_PIN_SET)

#define R1RESET HAL_GPIO_WritePin(Motor_R_1_Port, Motor_R_1_Pin, GPIO_PIN_RESET)
#define R1SET HAL_GPIO_WritePin(Motor_R_1_Port, Motor_R_1_Pin, GPIO_PIN_SET)
#define R2RESET HAL_GPIO_WritePin(Motor_R_2_Port, Motor_R_2_Pin, GPIO_PIN_RESET) // 电机2
#define R2SET HAL_GPIO_WritePin(Motor_R_2_Port, Motor_R_2_Pin, GPIO_PIN_SET)
void Motor_Set(int motor1, int motor2);
#endif
