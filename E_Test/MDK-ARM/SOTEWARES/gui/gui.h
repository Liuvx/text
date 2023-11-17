#ifndef __GUI_H
#define __GUI_H
#include "main.h"
#include "oled.h"
#include "beep.h"
#include "key.h"
#include "pid_v.h"
#include "openmv.h"
typedef uint8_t uchar;

typedef struct
{
    uchar current;
    uchar up;    // 向上翻索引号
    uchar next;  // 向下翻索引号
    uchar enter; // 确认索引号
    uchar back;
    void (*current_operation)(void); // 当前状态应该执行的操作
} Menu_table;

extern Menu_table table[60];
extern void fun_0(void);
extern void fun_a1(void);
extern void fun_b1(void);
extern void fun_c1(void);
extern void fun_d1(void);
extern void fun_a21(void);
extern Point Bian_Point[5];
extern Point O_Center[1];
void fun_a22(void); // 寻迹返回;
void Motor_Set_OLED(void);
void Motor_xia(void);
void Motor_shang(void);
void X_Add(void);
void X_Deg(void);
void S_Add(void);
void S_Deg(void);
void Add(void);
void Deg(void);
void Reset(void);
void Menu_OLED(void);
void Qing_Right(void);
void Qing_back(void);
void Red(void);
void Off(void);
void Open(void);
void BianKuang(void);
void Blank_Road(void);
void XiaoYan_Right(void);
void XiaoYan(void);
void XiaoYan_L_UP(void);
void XiaoYan_R_UP(void);
void XiaoYan_R_DOWN(void);
void XiaoYan_L_DOWN(void);
void Center(void);
void BK(void);
void BK_L_UP(void);
void BK_R_UP(void);
void BK_L_D(void);
void BK_R_D(void);
void BianKuang_tiaozhen(void);
void Tiaozheng(void);
void T_X(void);
void T_X_A(void);
void T_Y_A(void);
void T_X_D(void);
void T_Y_D(void);
void STOP(void);
#endif
