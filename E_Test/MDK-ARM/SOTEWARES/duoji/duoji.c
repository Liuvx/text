#include "duoji.h"


void Duoji_Angle_Set_180(int angle1,int angle2)//180度舵机需要配置32位定时器，该定时器ARR为84000，舵机需要20ms的信号
{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,angle1*13+4000);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,angle2*13+4000);
}
void Duoji_Angle_Set_180_16(int angle1,int angle2)//180度舵机需要配置定时器，该定时器ARR为20000，舵机需要20ms的信号
{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,angle1*11+500);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,angle2*8.+500);
}
void Duoji_Angle_Set_180_Old(int angle1,int angle2)//180度舵机需要配置定时器，该定时器ARR为20000，舵机需要20ms的信号
{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,angle1*8+500);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,angle2*8+500);
}
void Duoji_Angle_Set_360_Stop (void)//360度舵机需要配置定时器，该定时器ARR为20000，舵机需要20ms的信号,停止时的高电平所需要的时间为1.4-1.6
{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,1500);
}
void Duoji_Angle_Set_360_Start (void)//360度舵机需要配置定时器，该定时器ARR为20000，舵机需要20ms的信号,正转时的高电平所需要的时间为0.5-1.5
{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,1000);
}
void Duoji_Angle_Set_360_Fan (void)//360度舵机需要配置定时器，该定时器ARR为20000，舵机需要20ms的信号,反转时的高电平所需要的时间为1.5-2.5
{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2000);
}

