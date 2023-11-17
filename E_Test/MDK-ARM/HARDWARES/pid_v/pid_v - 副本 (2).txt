#ifndef __PID_V_H
#define __PID_V_H
// #include "main.h"
#include "tim.h"
#include "openmv.h"
typedef struct
{
  int target_val; // 目标值
  int actual_val; // 实际值
  int err;        // 当前偏差
  int err_last;   // 上次偏差
  int err_sum;    // 误差累计值
  int prev_out;
  float Kp, Ki, Kd; // 比例，积分，微分系数

} tPid; // 定义的PID的结构体

extern tPid PID_Duoji_Shang;
extern tPid PID_Duoji_Xia;
extern tPid PID_X_Wei;
extern tPid PID_Y_Wei;

// 声明函数
void PID_init(void);
int PID_realize_Y(tPid *pid, int actual_val);
int PID_realize_X(tPid *pid, int actual_val);
int updateIncrementalPID(tPid *pid, int actual_val);

#endif
