#include "control.h" //用来写死路线

void Duoji_Control(int duoji_shang,int duoji_xia)
{
	PID_Duoji_Shang.target_val=duoji_shang;
	PID_Duoji_Xia.target_val=duoji_xia;
}
