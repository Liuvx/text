#ifndef __KEY_H
#define __KEY_H
#include "main.h"

#define Read_Key1 HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)
#define Read_Key2 HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)
#define Read_Key3 HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)
#define Read_Key4 HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)
#define Read_Key6 HAL_GPIO_ReadPin(KEY6_GPIO_Port,KEY6_Pin)

int Read_Key(void);

#endif
