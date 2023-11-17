#include "motor.h"

void Motor_Set(int motor1, int motor2) // 大于0为正转，小于0为反转，等于0为停止
{
    if (motor1 < 0)
    {
        L1RESET;
        L2SET;
    }
    if (motor1 > 0)
    {
        L1SET;
        L2RESET;
    }
    if (motor1 == 0)
    {
        L1RESET;
        L2RESET;
    }
    if (motor2 > 0)
    {
        R1RESET;
        R2SET;
    }
    if (motor2 < 0)
    {
        R1SET;
        R2RESET;
    }
    if (motor2 == 0)
    {
        R1RESET;
        R2RESET;
    }
    if (motor1 < 0)
    {
        if (motor1 < -7000)
        motor1 = -7000;
        //__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, -motor1);
    }
    if (motor1 > 0)
    {
        if (motor1 > 7000)
        motor1 = 7000;
       // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, motor1);
    }
    if (motor2 < 0)
    {
        if (motor2 < -7000)
        motor2 = -7000;
       // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, -motor2);
    }
    if (motor2 > 0)
    {
        if (motor2 > 7000)
        motor2 = 7000;
        //__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, motor2);
    }
}
