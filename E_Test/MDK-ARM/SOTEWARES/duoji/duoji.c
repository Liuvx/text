#include "duoji.h"


void Duoji_Angle_Set_180(int angle1,int angle2)//180�ȶ����Ҫ����32λ��ʱ�����ö�ʱ��ARRΪ84000�������Ҫ20ms���ź�
{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,angle1*13+4000);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,angle2*13+4000);
}
void Duoji_Angle_Set_180_16(int angle1,int angle2)//180�ȶ����Ҫ���ö�ʱ�����ö�ʱ��ARRΪ20000�������Ҫ20ms���ź�
{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,angle1*11+500);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,angle2*8.+500);
}
void Duoji_Angle_Set_180_Old(int angle1,int angle2)//180�ȶ����Ҫ���ö�ʱ�����ö�ʱ��ARRΪ20000�������Ҫ20ms���ź�
{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,angle1*8+500);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,angle2*8+500);
}
void Duoji_Angle_Set_360_Stop (void)//360�ȶ����Ҫ���ö�ʱ�����ö�ʱ��ARRΪ20000�������Ҫ20ms���ź�,ֹͣʱ�ĸߵ�ƽ����Ҫ��ʱ��Ϊ1.4-1.6
{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,1500);
}
void Duoji_Angle_Set_360_Start (void)//360�ȶ����Ҫ���ö�ʱ�����ö�ʱ��ARRΪ20000�������Ҫ20ms���ź�,��תʱ�ĸߵ�ƽ����Ҫ��ʱ��Ϊ0.5-1.5
{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,1000);
}
void Duoji_Angle_Set_360_Fan (void)//360�ȶ����Ҫ���ö�ʱ�����ö�ʱ��ARRΪ20000�������Ҫ20ms���ź�,��תʱ�ĸߵ�ƽ����Ҫ��ʱ��Ϊ1.5-2.5
{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2000);
}

