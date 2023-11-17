#include "pid_v.h"
#include "stdio.h"
#include <stdlib.h>
// ��1
// ����һ���ṹ�����ͱ���
tPid PID_Duoji_Shang;           // y��
tPid PID_Duoji_Xia;             // x��
tPid PID_X_Wei;                 // x��
tPid PID_Y_Wei;                 // Y��
//Point O_Center[1] = {{6, 6}}; // ���ĵ�����
Point O_Center[1] = {{74, 77}};
// Point O_Center[1]={{6, 10}};
//   ���ṹ�����ͱ�������ֵ

void PID_init() // PID������ʼ��
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

    PID_X_Wei.actual_val = 0.0; // ΢������PID
    PID_X_Wei.target_val = O_Center[0].x;
    PID_X_Wei.err = 0.0;
    PID_X_Wei.err_last = 0.0;
    PID_X_Wei.err_sum = 0.0;
    PID_X_Wei.prev_out = 0.0;
    PID_X_Wei.Kp = 0;
    PID_X_Wei.Ki = 0; // 0.2
    PID_X_Wei.Kd = 0;

    PID_Y_Wei.actual_val = 0.0; // ΢������PID
    PID_Y_Wei.target_val = O_Center[0].y;
    PID_Y_Wei.err = 0.0;
    PID_Y_Wei.err_last = 0.0;
    PID_Y_Wei.err_sum = 0.0;
    PID_Y_Wei.prev_out = 0.0;
    PID_Y_Wei.Kp = 1;
    PID_Y_Wei.Ki = 0; // 0.2
    PID_Y_Wei.Kd = 0;
}

int PID_realize_Y(tPid *pid, int actual_val) // Y��PID����
{
    int out;
    pid->actual_val = actual_val;                   // ������ʵֵ
    pid->err = (pid->target_val) - pid->actual_val; ////��ǰ���=Ŀ��ֵ-��ʵֵ
    if (pid->err >= -1 && pid->err <= 1)
        pid->err = 0;         // ���ַ���
    pid->err_sum += pid->err; // ����ۼ�ֵ = ��ǰ����ۼ�
    if (pid->err_sum > 10)
        pid->err_sum = 10;
    if (pid->err_sum < -10)
        pid->err_sum = -10; // �����޷�

    // ʹ��PID���� ��� = Kp*��ǰ���  +  Ki*����ۼ�ֵ + Kd*(��ǰ���-�ϴ����)
    out = pid->Kp * pid->err + pid->Ki * pid->err_sum + pid->Kd * (pid->err - pid->err_last);
    // �����ϴ����: �����ֵ���ϴ����
    pid->err_last = pid->err;
    // if(out>300)
    // out=300;
    //	if(out<-300)
    // out=-300;

    return out;
}
int PID_realize_X(tPid *pid, int actual_val) // X��PID����
{
    int out;
    pid->actual_val = actual_val;                   // ������ʵֵ
    pid->err = (pid->target_val) - pid->actual_val; ////��ǰ���=Ŀ��ֵ-��ʵֵ
    if (pid->err >= -1 && pid->err <= 1)            // ���ַ���
        pid->err = 0;
    pid->err_sum += pid->err; // ����ۼ�ֵ = ��ǰ����ۼ�
    if (pid->err_sum > 10)
        pid->err_sum = 10;
    if (pid->err_sum < -10)
        pid->err_sum = -10; // �����޷�

    // ʹ��PID���� ��� = Kp*��ǰ���  +  Ki*����ۼ�ֵ + Kd*(��ǰ���-�ϴ����)
    out = pid->Kp * pid->err + pid->Ki * pid->err_sum + pid->Kd * (pid->err - pid->err_last);
    // �����ϴ����: �����ֵ���ϴ����
    pid->err_last = pid->err;
    // if(out>300)
    // out=300;
    // if(out<-300)
    // out=-300;

    return out;
}
int updateIncrementalPID(tPid *pid, int actual_val) // ����ʽPID
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