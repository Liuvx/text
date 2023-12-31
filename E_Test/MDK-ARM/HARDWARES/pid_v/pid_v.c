#include "pid_v.h"
#include "stdio.h"
#include <stdlib.h>
// 轮1
// 定义一个结构体类型变量
tPid PID_Duoji_Shang;           // y轴
tPid PID_Duoji_Xia;             // x轴
tPid PID_X_Wei;                 // x轴
tPid PID_Y_Wei;                 // Y轴
//Point O_Center[1] = {{6, 6}}; // 中心点坐标
Point O_Center[1] = {{74, 77}};
// Point O_Center[1]={{6, 10}};
//   给结构体类型变量赋初值

void PID_init() // PID参数初始化
{
    PID_Duoji_Shang.actual_val = 0.0;
    PID_Duoji_Shang.target_val = O_Center[0].y;
    PID_Duoji_Shang.err = 0.0;
    PID_Duoji_Shang.err_last = 0.0;
    PID_Duoji_Shang.err_sum = 0.0;
    PID_Duoji_Shang.prev_out = 0.0;
    PID_Duoji_Shang.Kp = 1.30;
    PID_Duoji_Shang.Ki = 0; // 0.15
    PID_Duoji_Shang.Kd = 0;

    PID_Duoji_Xia.actual_val = 0.0;
    PID_Duoji_Xia.target_val = O_Center[0].x;
    PID_Duoji_Xia.err = 0.0;
    PID_Duoji_Xia.err_last = 0.0;
    PID_Duoji_Xia.err_sum = 0.0;
    PID_Duoji_Xia.prev_out = 0.0;
    PID_Duoji_Xia.Kp = 1.3;
    PID_Duoji_Xia.Ki = 0; // 0.2
    PID_Duoji_Xia.Kd = 0;

    PID_X_Wei.actual_val = 0.0; // 微分所用PID
    PID_X_Wei.target_val = O_Center[0].x;
    PID_X_Wei.err = 0.0;
    PID_X_Wei.err_last = 0.0;
    PID_X_Wei.err_sum = 0.0;
    PID_X_Wei.prev_out = 0.0;
    PID_X_Wei.Kp = 0;
    PID_X_Wei.Ki = 0; // 0.2
    PID_X_Wei.Kd = 0;

    PID_Y_Wei.actual_val = 0.0; // 微分所用PID
    PID_Y_Wei.target_val = O_Center[0].y;
    PID_Y_Wei.err = 0.0;
    PID_Y_Wei.err_last = 0.0;
    PID_Y_Wei.err_sum = 0.0;
    PID_Y_Wei.prev_out = 0.0;
    PID_Y_Wei.Kp = 1;
    PID_Y_Wei.Ki = 0; // 0.2
    PID_Y_Wei.Kd = 0;
}

int PID_realize_Y(tPid *pid, int actual_val) // Y轴PID调节
{
    int out;
    pid->actual_val = actual_val;                   // 传递真实值
    pid->err = (pid->target_val) - pid->actual_val; ////当前误差=目标值-真实值
    if (pid->err >= -1 && pid->err <= 1)
        pid->err = 0;         // 积分分离
    pid->err_sum += pid->err; // 误差累计值 = 当前误差累计
    if (pid->err_sum > 10)
        pid->err_sum = 10;
    if (pid->err_sum < -10)
        pid->err_sum = -10; // 积分限幅

    // 使用PID控制 输出 = Kp*当前误差  +  Ki*误差累计值 + Kd*(当前误差-上次误差)
    out = pid->Kp * pid->err + pid->Ki * pid->err_sum + pid->Kd * (pid->err - pid->err_last);
    // 保存上次误差: 这次误差赋值给上次误差
    pid->err_last = pid->err;
    // if(out>300)
    // out=300;
    //	if(out<-300)
    // out=-300;

    return out;
}
int PID_realize_X(tPid *pid, int actual_val) // X轴PID调节
{
    int out;
    pid->actual_val = actual_val;                   // 传递真实值
    pid->err = (pid->target_val) - pid->actual_val; ////当前误差=目标值-真实值
    if (pid->err >= -1 && pid->err <= 1)            // 积分分离
        pid->err = 0;
    pid->err_sum += pid->err; // 误差累计值 = 当前误差累计
    if (pid->err_sum > 10)
        pid->err_sum = 10;
    if (pid->err_sum < -10)
        pid->err_sum = -10; // 积分限幅

    // 使用PID控制 输出 = Kp*当前误差  +  Ki*误差累计值 + Kd*(当前误差-上次误差)
    out = pid->Kp * pid->err + pid->Ki * pid->err_sum + pid->Kd * (pid->err - pid->err_last);
    // 保存上次误差: 这次误差赋值给上次误差
    pid->err_last = pid->err;
    // if(out>300)
    // out=300;
    // if(out<-300)
    // out=-300;

    return out;
}
int updateIncrementalPID(tPid *pid, int actual_val) // 增量式PID
{
    int out;
    pid->actual_val = actual_val;

    pid->err = pid->target_val - pid->actual_val;
    if (pid->err >= -1 && pid->err <= 1)
        pid->err = 0; // Integral separation

    pid->err_sum += pid->err;
    if (pid->err_sum > 2)
        pid->err_sum = 2;
    if (pid->err_sum < -3)
        pid->err_sum = -3; // Integral saturation

    out = pid->prev_out + pid->Kp * (pid->err - pid->err_last) + pid->Ki * pid->err_sum + pid->Kd * (pid->err - 2 * pid->err_last + pid->prev_out);

    // Save previous values for the next iteration
    pid->prev_out = out;
    pid->err_last = pid->err;

    return out;
}
