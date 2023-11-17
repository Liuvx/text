#include "gui.h"
#include "stdio.h"
extern void (*current_operation_index)();
extern uint8_t func_index; // 初始显示欢迎界面
extern uint8_t last_index; // last初始为无效值
extern int angle_xia;
extern int angle_shang;
extern int Angle_Change;
extern int Maichong_Shang;
extern int Maichong_xia;
extern int Stop_Num;
extern int Road_Num;
int PID_Num;
Maichong points[] = {
    {2495, 1057}, // 右上
    {2500, 913},  // 右下
    {2614, 925},  // 左下
    {2614, 1062}, // 左上
    {2497, 1057}};
int Duoji_C = 0; // 0为下，1为上
Menu_table table[60] =
    {
        {0, 0, 0, 1, 1, (*fun_0)},
        ////////UP DOWN
        // 第1层
        {1, 5, 2, 6, 1, (*fun_a1)},  // 复位
        {2, 1, 3, 17, 1, (*fun_b1)}, // 清0
        {3, 2, 4, 8, 1, (*fun_c1)},  // 舵机
        {4, 3, 5, 21, 1, (*fun_d1)}, // 题目
        {5, 4, 1, 19, 1, (*Red)},
        // 第2层
        {6, 7, 7, 6, 1, (*fun_a21)}, // 复位确认
        {7, 6, 6, 1, 1, (*fun_a22)}, // 复位返回

        {8, 10, 9, 32, 1, (*Motor_Set_OLED)},
        {9, 10, 10, 11, 1, (*Motor_xia)},  // 未设置
        {10, 9, 9, 13, 1, (*Motor_shang)}, // 未设置

        // {14, 14, 9, 14, 1, (*Motor_Deg)}, // 寻迹开始
        //  {14, 14, 9, 14, 1, (*Motor_Deg)}, // 返回
        {11, 12, 12, 11, 8, (*X_Add)}, // 下加
        {12, 11, 11, 12, 8, (*X_Deg)}, // 下减
        {13, 14, 14, 13, 8, (*S_Add)}, // 上加
        {14, 13, 13, 14, 8, (*S_Deg)}, // 上减

        {15, 1, 1, 15, 1, (*Add)}, // 减小
        {16, 1, 1, 16, 1, (*Deg)}, // 减小

        {17, 18, 18, 17, 1, (*Qing_Right)},
        {18, 17, 17, 1, 1, (*Qing_back)},

        {19, 20, 20, 19, 1, (*Open)},
        {20, 19, 19, 20, 1, (*Off)},

        {21, 25, 22, 21, 1, {*BianKuang}},
        {22, 21, 23, 22, 1, {*Blank_Road}},
        {23, 22, 24, 26, 1, {*XiaoYan_Right}},
        {24, 23, 25, 32, 1, {*BianKuang_tiaozhen}},
        {25, 24, 21, 37, 1, {*Tiaozheng}},

        {26, 31, 27, 26, 1, {*XiaoYan}},//边线的校正摄像头
        {27, 26, 28, 27, 1, {*XiaoYan_L_UP}},
        {28, 27, 29, 28, 1, {*XiaoYan_R_UP}},
        {29, 28, 30, 29, 1, {*XiaoYan_L_DOWN}},
        {30, 29, 31, 30, 1, {*XiaoYan_R_DOWN}},

        {31, 30, 27, 31, 1, {*Center}},

        {32, 31, 33, 8, 1, {*BK}},//黑色边框的校正
        {33, 32, 34, 33, 1, {*BK_L_UP}},
        {34, 33, 35, 34, 1, {*BK_R_UP}},
        {35, 34, 36, 35, 1, {*BK_L_D}},
        {36, 35, 32, 36, 1, {*BK_R_D}},
		
		{37, 42, 38, 37, 1, {*T_X}},
		{38, 37, 39, 38, 1, {*T_X_A}},
	{39, 38, 40, 39, 1, {*T_Y_A}},
		{40, 39, 41, 40, 1, {*T_X_D}},
		{41, 40, 42, 41, 1, {*T_Y_D}},
		{42, 41, 37, 37, 1, {*STOP}},

        //{14, 1, 1, 1, 1, (*Add_Right)}, // 减小
        //{15, 1, 1, 1, 1, (*Deg_Right)}, // 减小

};
void fun_0(void)
{

    OLED_ShowString(24, 0, "Duoji", 16, 1);
    OLED_ShowString(0, 0, "Menu", 16, 1);
    OLED_ShowString(24, 16, "Reset", 16, 1);
    OLED_ShowString(24, 32, "Qingling", 16, 1);
    OLED_ShowString(24, 48, "Duoji", 16, 1);
}

void fun_a1(void)
{
    OLED_ShowString(0, 16, "-->", 16, 1);
    OLED_ShowString(0, 0, "Menu", 16, 1);
    OLED_ShowChinese(24, 16, 0, 16, 1);
    OLED_ShowChinese(40, 16, 1, 16, 1);
    // OLED_ShowString(24, 16, "Reset", 16, 1);
    // OLED_ShowString(24, 32, "Qingling", 16, 1);
    OLED_ShowChinese(24, 32, 2, 16, 1);
    OLED_ShowChinese(40, 32, 3, 16, 1);
    // OLED_ShowString(24, 48, "Duoji", 16, 1);
    OLED_ShowChinese(24, 48, 4, 16, 1);
    OLED_ShowChinese(40, 48, 5, 16, 1);
    OLED_ShowChinese(56, 48, 6, 16, 1);
    OLED_ShowChinese(72, 48, 7, 16, 1);
}
void fun_b1(void)
{
    OLED_ShowString(0, 16, "-->", 16, 1);
    OLED_ShowString(0, 0, "Menu", 16, 1);
    OLED_ShowChinese(24, 16, 2, 16, 1);
    OLED_ShowChinese(40, 16, 3, 16, 1);
    // OLED_ShowString(24, 48, "Duoji", 16, 1);
    OLED_ShowChinese(24, 32, 4, 16, 1);
    OLED_ShowChinese(40, 32, 5, 16, 1);
    OLED_ShowChinese(56, 32, 6, 16, 1);
    OLED_ShowChinese(72, 32, 7, 16, 1);
    OLED_ShowString(24, 48, "Text", 16, 1);
    // Beep_DD();
}
void fun_c1(void)
{
    OLED_ShowString(0, 32, "-->", 16, 1);
    OLED_ShowString(0, 0, "Menu", 16, 1);
    OLED_ShowChinese(24, 16, 2, 16, 1);
    OLED_ShowChinese(40, 16, 3, 16, 1);
    // OLED_ShowString(24, 48, "Duoji", 16, 1);
    OLED_ShowChinese(24, 32, 4, 16, 1);
    OLED_ShowChinese(40, 32, 5, 16, 1);
    OLED_ShowChinese(56, 32, 6, 16, 1);
    OLED_ShowChinese(72, 32, 7, 16, 1);
    OLED_ShowString(24, 48, "Text", 16, 1);
    // Beep_DD();
}
void fun_d1(void)
{
    OLED_ShowString(0, 32, "-->", 16, 1);
    OLED_ShowString(0, 0, "Menu", 16, 1);
    // OLED_ShowString(24, 48, "Duoji", 16, 1);
    OLED_ShowChinese(24, 16, 4, 16, 1);
    OLED_ShowChinese(40, 16, 5, 16, 1);
    OLED_ShowChinese(56, 16, 6, 16, 1);
    OLED_ShowChinese(72, 16, 7, 16, 1);
    OLED_ShowString(24, 32, "Text", 16, 1);
    OLED_ShowString(24, 48, "Red", 16, 1);
}
void Red(void)
{
    OLED_ShowString(0, 48, "-->", 16, 1);
    OLED_ShowString(0, 0, "Menu", 16, 1);
    // OLED_ShowString(24, 48, "Duoji", 16, 1);
    OLED_ShowChinese(24, 16, 4, 16, 1);
    OLED_ShowChinese(40, 16, 5, 16, 1);
    OLED_ShowChinese(56, 16, 6, 16, 1);
    OLED_ShowChinese(72, 16, 7, 16, 1);
    OLED_ShowString(24, 32, "Text", 16, 1);
    OLED_ShowString(24, 48, "Red", 16, 1);
}

void fun_a21(void) // 复位
{
    OLED_ShowString(0, 16, "-->", 16, 1);
    //  OLED_ShowString(40, 0, "Reste?", 16, 1);
    OLED_ShowChinese(40, 0, 0, 16, 1);
    OLED_ShowChinese(56, 0, 1, 16, 1);
    OLED_ShowString(72, 0, "?", 16, 1);
    OLED_ShowString(24, 16, "Right", 16, 1);
    OLED_ShowString(24, 32, "back", 16, 1);
    // OLED_ShowString(24, 48, "back", 16, 1);
}
void fun_a22(void) // 复位返回
{
    OLED_ShowString(0, 32, "-->", 16, 1);
    // OLED_ShowString(40, 0, "Reste?", 16, 1);
    OLED_ShowChinese(40, 0, 0, 16, 1);
    OLED_ShowChinese(56, 0, 1, 16, 1);
    OLED_ShowString(72, 0, "?", 16, 1);
    OLED_ShowString(24, 16, "Right", 16, 1);
    OLED_ShowString(24, 32, "back", 16, 1);
    // OLED_ShowString(24, 48, "back", 16, 1);
}
void Reset(void) // 复位后
{
    // OLED_ShowString(0, 32, "-->", 16, 1);

    OLED_ShowString(40, 32, "Reste  ok", 16, 1);
    // OLED_ShowString(24, 16, "Right", 16, 1);
    // OLED_ShowString(24, 32, "back", 16, 1);
    // OLED_ShowString(24, 48, "back", 16, 1);
}

void Motor_Set_OLED(void)
{
    // Stop_Num = 0;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Maichong_xia);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Maichong_Shang);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);
    if (Angle_Change == 1)
    {
        OLED_ShowNum(48, 0, angle_xia, 3, 16, 1); // 三位数
        OLED_ShowNum(96, 0, angle_shang, 3, 16, 1);
    }
    else
    {
        OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
        OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
    }

    // OLED_ShowString(0, 0, "Duoji", 16, 1);
    OLED_ShowChinese(0, 0, 4, 16, 1);
    OLED_ShowChinese(16, 0, 5, 16, 1);
    // OLED_ShowChinese(32, 0, 6, 16, 1);
    // OLED_ShowChinese(48, 0, 7, 16, 1);
    //  OLED_ShowString(0, 16, "-->", 16, 1);
    OLED_ShowString(30, 16, "xia", 16, 1);
    OLED_ShowString(90, 16, "Shang", 16, 1);
    OLED_ShowString(24, 32, "Angle_Add", 16, 1);
    OLED_ShowString(24, 48, "Angle_Deg", 16, 1);
}
void Motor_xia(void)
{
    // Stop_Num = 0;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Maichong_xia);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Maichong_Shang);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);
    if (Angle_Change == 1)
    {
        OLED_ShowNum(48, 0, angle_xia, 3, 16, 1); // 三位数
        OLED_ShowNum(96, 0, angle_shang, 3, 16, 1);
    }
    else
    {
        OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
        OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
    }

    // OLED_ShowString(0, 0, "Duoji", 16, 1);
    OLED_ShowChinese(0, 0, 4, 16, 1);
    OLED_ShowChinese(16, 0, 5, 16, 1);
    // OLED_ShowChinese(32, 0, 6, 16, 1);
    // OLED_ShowChinese(48, 0, 7, 16, 1);
    OLED_ShowString(0, 16, "-->", 16, 1);
    OLED_ShowString(30, 16, "xia", 16, 1);
    OLED_ShowString(90, 16, "Shang", 16, 1);
    OLED_ShowString(24, 32, "Angle_Add", 16, 1);
    OLED_ShowString(24, 48, "Angle_Deg", 16, 1);
}
void Motor_shang(void)
{
    // Stop_Num = 0;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Maichong_xia);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Maichong_Shang);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);
    if (Angle_Change == 1)
    {
        OLED_ShowNum(48, 0, angle_xia, 3, 16, 1); // 三位数
        OLED_ShowNum(96, 0, angle_shang, 3, 16, 1);
    }
    else
    {
        OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
        OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
    }

    // OLED_ShowString(0, 0, "Duoji", 16, 1);
    OLED_ShowChinese(0, 0, 4, 16, 1);
    OLED_ShowChinese(16, 0, 5, 16, 1);
    OLED_ShowString(54, 16, "-->", 16, 1);
    OLED_ShowString(30, 16, "xia", 16, 1);
    OLED_ShowString(90, 16, "Shang", 16, 1);
    OLED_ShowString(24, 32, "Angle_Add", 16, 1);
    OLED_ShowString(24, 48, "Angle_Deg", 16, 1);
}
void X_Add(void)
{
    // Stop_Num = 0;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Maichong_xia);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Maichong_Shang);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);
    if (Angle_Change == 1)
    {
        OLED_ShowNum(48, 0, angle_xia, 3, 16, 1); // 三位数
        OLED_ShowNum(96, 0, angle_shang, 3, 16, 1);
    }
    else
    {
        OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
        OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
    }

    // OLED_ShowString(0, 0, "Duoji", 16, 1);
    OLED_ShowChinese(0, 0, 4, 16, 1);
    OLED_ShowChinese(16, 0, 5, 16, 1);
    OLED_ShowString(0, 32, "-->", 16, 1);
    OLED_ShowString(30, 16, "xia", 16, 1);
    // OLED_ShowString(90, 16, "Shang", 16, 1);
    OLED_ShowString(24, 32, "Angle_Add", 16, 1);
    OLED_ShowString(24, 48, "Angle_Deg", 16, 1);
}

void X_Deg(void)
{
    // Stop_Num = 0;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Maichong_xia);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Maichong_Shang);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);
    if (Angle_Change == 1)
    {
        OLED_ShowNum(48, 0, angle_xia, 3, 16, 1); // 三位数
        OLED_ShowNum(96, 0, angle_shang, 3, 16, 1);
    }
    else
    {
        OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
        OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
    }

    // OLED_ShowString(0, 0, "Duoji", 16, 1);
    OLED_ShowChinese(0, 0, 4, 16, 1);
    OLED_ShowChinese(16, 0, 5, 16, 1);
    OLED_ShowString(0, 48, "-->", 16, 1);
    OLED_ShowString(30, 16, "xia", 16, 1);
    // OLED_ShowString(90, 16, "Shang", 16, 1);
    OLED_ShowString(24, 32, "Angle_Add", 16, 1);
    OLED_ShowString(24, 48, "Angle_Deg", 16, 1);
}
void S_Add(void)
{
    // Stop_Num = 0;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Maichong_xia);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Maichong_Shang);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);
    if (Angle_Change == 1)
    {
        OLED_ShowNum(48, 0, angle_xia, 3, 16, 1); // 三位数
        OLED_ShowNum(96, 0, angle_shang, 3, 16, 1);
    }
    else
    {
        OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
        OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
    }

    // OLED_ShowString(0, 0, "Duoji", 16, 1);
    OLED_ShowChinese(0, 0, 4, 16, 1);
    OLED_ShowChinese(16, 0, 5, 16, 1);
    OLED_ShowString(0, 32, "-->", 16, 1);
    // OLED_ShowString(30, 16, "xia", 16, 1);
    OLED_ShowString(90, 16, "Shang", 16, 1);
    OLED_ShowString(24, 32, "Angle_Add", 16, 1);
    OLED_ShowString(24, 48, "Angle_Deg", 16, 1);
}

void S_Deg(void)
{
    // Stop_Num = 0;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Maichong_xia);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Maichong_Shang);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);
    if (Angle_Change == 1)
    {
        OLED_ShowNum(48, 0, angle_xia, 3, 16, 1); // 三位数
        OLED_ShowNum(96, 0, angle_shang, 3, 16, 1);
    }
    else
    {
        OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
        OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
    }

    // OLED_ShowString(0, 0, "Duoji", 16, 1);
    OLED_ShowChinese(0, 0, 4, 16, 1);
    OLED_ShowChinese(16, 0, 5, 16, 1);
    OLED_ShowString(0, 48, "-->", 16, 1);
    // OLED_ShowString(30, 16, "xia", 16, 1);
    OLED_ShowString(90, 16, "Shang", 16, 1);
    OLED_ShowString(24, 32, "Angle_Add", 16, 1);
    OLED_ShowString(24, 48, "Angle_Deg", 16, 1);
}

void Add(void)
{

    OLED_ShowString(48, 0, "X:", 16, 1);
    OLED_ShowNum(62, 0, angle_xia, 2, 16, 1);
    OLED_ShowNum(100, 0, angle_shang, 2, 16, 1);
    OLED_ShowString(84, 0, "S:", 16, 1);
}
void Deg(void)
{

    OLED_ShowString(48, 0, "X:", 16, 1);
    OLED_ShowNum(62, 0, angle_xia, 2, 16, 1);
    OLED_ShowNum(100, 0, angle_shang, 2, 16, 1);
    OLED_ShowString(84, 0, "S:", 16, 1);
    OLED_ShowString(0, 0, "Duoji", 16, 1);
    OLED_ShowString(0, 48, "-->", 16, 1);
    OLED_ShowString(30, 16, "xia", 16, 1);
    OLED_ShowString(90, 16, "Shang", 16, 1);
    OLED_ShowString(24, 32, "Angle_Add", 16, 1);
    OLED_ShowString(24, 48, "Angle_Deg", 16, 1);
}
void Qing_Right(void) // 清0
{
    OLED_ShowString(0, 16, "-->", 16, 1);
    // OLED_ShowString(40, 0, "Qingling?", 16, 1);
    OLED_ShowChinese(40, 0, 2, 16, 1);
    OLED_ShowChinese(56, 0, 3, 16, 1);
    OLED_ShowString(72, 0, "?", 16, 1);
    OLED_ShowString(24, 16, "Right", 16, 1);
    OLED_ShowString(24, 32, "back", 16, 1);
    // OLED_ShowString(24, 48, "back", 16, 1);
}
void Qing_back(void) // 复位返回
{
    OLED_ShowString(0, 32, "-->", 16, 1);
    // OLED_ShowString(40, 0, "Qingling?", 16, 1);
    OLED_ShowChinese(40, 0, 2, 16, 1);
    OLED_ShowChinese(56, 0, 3, 16, 1);
    OLED_ShowString(72, 0, "?", 16, 1);
    // OLED_ShowString(24, 16, "Right", 16, 1);
    OLED_ShowString(24, 32, "back", 16, 1);
    // OLED_ShowString(24, 48, "back", 16, 1);
}
void Open(void) // 开启
{
    OLED_ShowString(0, 16, "-->", 16, 1);
    OLED_ShowString(40, 0, "Red open?", 16, 1);
    // OLED_ShowChinese(40, 0, 2, 16, 1);
    // OLED_ShowChinese(56, 0, 3, 16, 1);
    // OLED_ShowString(72, 0, "?", 16, 1);
    OLED_ShowString(24, 16, "Right", 16, 1);
    OLED_ShowString(24, 32, "off", 16, 1);
    // OLED_ShowString(24, 48, "back", 16, 1);
}
void Off(void) // 关闭
{
    OLED_ShowString(0, 32, "-->", 16, 1);
    OLED_ShowString(40, 0, "Red open?", 16, 1);
    // OLED_ShowChinese(40, 0, 2, 16, 1);
    // OLED_ShowChinese(56, 0, 3, 16, 1);
    // OLED_ShowString(72, 0, "?", 16, 1);
    OLED_ShowString(24, 16, "Right", 16, 1);
    OLED_ShowString(24, 32, "off", 16, 1);
    // OLED_ShowString(24, 48, "back", 16, 1);
}
void BianKuang(void)
{
    OLED_ShowString(0, 0, "Test", 16, 1);
    OLED_ShowString(0, 16, "-->", 16, 1);
    OLED_ShowString(40, 16, "BianKuang_Road", 16, 1);
    OLED_ShowString(40, 32, "Blank_Road", 16, 1);
    OLED_ShowString(40, 48, "XIAO_Yan", 16, 1);
}

void Blank_Road(void)
{
    OLED_ShowString(0, 0, "Test", 16, 1);
    OLED_ShowString(0, 32, "-->", 16, 1);
    OLED_ShowString(40, 16, "BianKuang_Road", 16, 1);
    OLED_ShowString(40, 32, "Blank_Road", 16, 1);
    OLED_ShowString(40, 48, "XIAO_Yan", 16, 1);
}
void XiaoYan_Right(void)
{
    OLED_ShowString(0, 0, "Test", 16, 1);
    OLED_ShowString(0, 48, "-->", 16, 1);
    OLED_ShowString(40, 16, "BianKuang_Road", 16, 1);
    OLED_ShowString(40, 32, "Blank_Road", 16, 1);
    OLED_ShowString(40, 48, "XIAO_Yan", 16, 1);
}
void BianKuang_tiaozhen(void)
{
    OLED_ShowString(0, 0, "Test", 16, 1);
    OLED_ShowString(0, 48, "-->", 16, 1);
    // OLED_ShowString(40, 16, "BianKuang_Road", 16, 1);
    OLED_ShowString(40, 16, "Blank_Road", 16, 1);
    OLED_ShowString(40, 32, "XIAO_Yan", 16, 1);
    OLED_ShowString(40, 48, "BK_TIAO", 16, 1);
}
void XiaoYan(void) // 要求停止
{
    // HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_RESET);
    OLED_ShowString(0, 0, "Red_C", 16, 1);
    OLED_ShowString(48, 0, "X:", 16, 1);
    OLED_ShowNum(62, 0, Red_center[0].x, 2, 16, 1);
    OLED_ShowNum(100, 0, Red_center[0].y, 2, 16, 1);
    OLED_ShowString(84, 0, "Y:", 16, 1);
    // OLED_ShowString(0, 16, "-->", 16, 1);
    OLED_ShowString(30, 16, "L_UP", 16, 1);
    OLED_ShowString(90, 16, "R_UP", 16, 1);
    OLED_ShowString(30, 32, "L_D", 16, 1);
    OLED_ShowString(90, 32, "R_D", 16, 1);
    OLED_ShowString(30, 48, "Center", 16, 1);
    Stop_Num = 1;
}
void Tiaozheng(void)
{
	    OLED_ShowString(0, 0, "Test", 16, 1);
    OLED_ShowString(0, 48, "-->", 16, 1);
    // OLED_ShowString(40, 16, "BianKuang_Road", 16, 1);
    //OLED_ShowString(40, 16, "Blank_Road", 16, 1);
    OLED_ShowString(40, 16, "XIAO_Yan", 16, 1);
    OLED_ShowString(40, 32, "BK_TIAO", 16, 1);
	 OLED_ShowString(40, 48, "TIAO_Zheng", 16, 1);
}
void XiaoYan_L_UP(void) // 要求停止
{
    OLED_ShowString(0, 0, "Red_C", 16, 1);
    OLED_ShowString(48, 0, "X:", 16, 1);
    OLED_ShowNum(62, 0, Red_center[0].x, 2, 16, 1);
    OLED_ShowNum(100, 0, Red_center[0].y, 2, 16, 1);
    OLED_ShowString(84, 0, "Y:", 16, 1);
    OLED_ShowString(0, 16, "-->", 16, 1);
    OLED_ShowString(30, 16, "L_UP", 16, 1);
    OLED_ShowString(90, 16, "R_UP", 16, 1);
    OLED_ShowString(30, 32, "L_D", 16, 1);
    OLED_ShowString(90, 32, "R_D", 16, 1);
    OLED_ShowString(30, 48, "Center", 16, 1);
}
void XiaoYan_R_UP(void) // 要求停止
{
    OLED_ShowString(0, 0, "Red_C", 16, 1);
    OLED_ShowString(48, 0, "X:", 16, 1);
    OLED_ShowNum(62, 0, Red_center[0].x, 2, 16, 1);
    OLED_ShowNum(100, 0, Red_center[0].y, 2, 16, 1);
    OLED_ShowString(84, 0, "Y:", 16, 1);
    OLED_ShowString(54, 16, "-->", 16, 1);
    OLED_ShowString(30, 16, "L_UP", 16, 1);
    OLED_ShowString(90, 16, "R_UP", 16, 1);
    OLED_ShowString(30, 32, "L_D", 16, 1);
    OLED_ShowString(90, 32, "R_D", 16, 1);
    OLED_ShowString(30, 48, "Center", 16, 1);
}
void XiaoYan_L_DOWN(void) // 要求停止
{
    OLED_ShowString(0, 0, "Red_C", 16, 1);
    OLED_ShowString(48, 0, "X:", 16, 1);
    OLED_ShowNum(62, 0, Red_center[0].x, 2, 16, 1);
    OLED_ShowNum(100, 0, Red_center[0].y, 2, 16, 1);
    OLED_ShowString(84, 0, "Y:", 16, 1);
    OLED_ShowString(0, 32, "-->", 16, 1);
    OLED_ShowString(30, 16, "L_UP", 16, 1);
    OLED_ShowString(90, 16, "R_UP", 16, 1);
    OLED_ShowString(30, 32, "L_D", 16, 1);
    OLED_ShowString(90, 32, "R_D", 16, 1);
    OLED_ShowString(30, 48, "Center", 16, 1);
}
void XiaoYan_R_DOWN(void) // 要求停止
{
    OLED_ShowString(0, 0, "Red_C", 16, 1);
    OLED_ShowString(48, 0, "X:", 16, 1);
    OLED_ShowNum(62, 0, Red_center[0].x, 2, 16, 1);
    OLED_ShowNum(100, 0, Red_center[0].y, 2, 16, 1);
    OLED_ShowString(84, 0, "Y:", 16, 1);
    OLED_ShowString(54, 32, "-->", 16, 1);
    OLED_ShowString(30, 16, "L_UP", 16, 1);
    OLED_ShowString(90, 16, "R_UP", 16, 1);
    OLED_ShowString(30, 32, "L_D", 16, 1);
    OLED_ShowString(90, 32, "R_D", 16, 1);
    OLED_ShowString(30, 48, "Center", 16, 1);
}
void Center(void)
{
    OLED_ShowString(0, 0, "Red_C", 16, 1);
    OLED_ShowString(48, 0, "X:", 16, 1);
    OLED_ShowNum(62, 0, Red_center[0].x, 2, 16, 1);
    OLED_ShowNum(100, 0, Red_center[0].y, 2, 16, 1);
    OLED_ShowString(84, 0, "Y:", 16, 1);
    OLED_ShowString(0, 48, "-->", 16, 1);
    OLED_ShowString(30, 16, "L_UP", 16, 1);
    OLED_ShowString(90, 16, "R_UP", 16, 1);
    OLED_ShowString(30, 32, "L_D", 16, 1);
    OLED_ShowString(90, 32, "R_D", 16, 1);
    OLED_ShowString(30, 48, "Center", 16, 1);
}
void BK_L_UP(void)
{
    OLED_ShowString(0, 0, "Maic", 16, 1);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);

    OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
    OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
    OLED_ShowString(0, 16, "-->", 16, 1);
    OLED_ShowString(30, 16, "L_UP", 16, 1);
    OLED_ShowString(90, 16, "R_UP", 16, 1);
    OLED_ShowString(30, 32, "L_D", 16, 1);
    OLED_ShowString(90, 32, "R_D", 16, 1);
}
   
void BK_R_UP(void)
{
    OLED_ShowString(0, 0, "Maic", 16, 1);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);

    OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
    OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
    OLED_ShowString(54, 16, "-->", 16, 1);
    OLED_ShowString(30, 16, "L_UP", 16, 1);
    OLED_ShowString(90, 16, "R_UP", 16, 1);
    OLED_ShowString(30, 32, "L_D", 16, 1);
    OLED_ShowString(90, 32, "R_D", 16, 1);
   
}
void BK_L_D(void)
{
    OLED_ShowString(0, 0, "Maic", 16, 1);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);

    OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
    OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
    OLED_ShowString(0, 32, "-->", 16, 1);
    OLED_ShowString(30, 16, "L_UP", 16, 1);
    OLED_ShowString(90, 16, "R_UP", 16, 1);
    OLED_ShowString(30, 32, "L_D", 16, 1);
    OLED_ShowString(90, 32, "R_D", 16, 1);
   
}
void BK_R_D(void)
{
    OLED_ShowString(0, 0, "Maic", 16, 1);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);

    OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
    OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
    OLED_ShowString(54, 32, "-->", 16, 1);
    OLED_ShowString(30, 16, "L_UP", 16, 1);
    OLED_ShowString(90, 16, "R_UP", 16, 1);
    OLED_ShowString(30, 32, "L_D", 16, 1);
    OLED_ShowString(90, 32, "R_D", 16, 1);
   
}
void BK(void)
{
    OLED_ShowString(0, 0, "Maic", 16, 1);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);

    OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
    OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
    //  OLED_ShowString(54, 16, "-->", 16, 1);
    OLED_ShowString(30, 16, "L_UP", 16, 1);
    OLED_ShowString(90, 16, "R_UP", 16, 1);
    OLED_ShowString(30, 32, "L_D", 16, 1);
    OLED_ShowString(90, 32, "R_D", 16, 1);
    
}
void T_X(void)
{
    OLED_ShowString(0, 0, "T_C", 16, 1);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);

    OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
    OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
    //  OLED_ShowString(54, 16, "-->", 16, 1);
    OLED_ShowString(30, 16, "X_UP", 16, 1);
    OLED_ShowString(90, 16, "Y_UP", 16, 1);
    OLED_ShowString(30, 32, "X_D", 16, 1);
    OLED_ShowString(90, 32, "Y_D", 16, 1);
    OLED_ShowString(30, 48, "STOP", 16, 1);
}
void T_X_A(void)
{
    OLED_ShowString(0, 0, "T_C", 16, 1);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);

    OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
    OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
     OLED_ShowString(0, 16, "-->", 16, 1);
    OLED_ShowString(30, 16, "X_UP", 16, 1);
    OLED_ShowString(90, 16, "Y_UP", 16, 1);
    OLED_ShowString(30, 32, "X_D", 16, 1);
    OLED_ShowString(90, 32, "Y_D", 16, 1);
    OLED_ShowString(30, 48, "STOP", 16, 1);
}
void T_Y_A(void)
{
    OLED_ShowString(0, 0, "T_C", 16, 1);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);

    OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
    OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
     OLED_ShowString(54, 16, "-->", 16, 1);
    OLED_ShowString(30, 16, "X_UP", 16, 1);
    OLED_ShowString(90, 16, "Y_UP", 16, 1);
    OLED_ShowString(30, 32, "X_D", 16, 1);
    OLED_ShowString(90, 32, "Y_D", 16, 1);
    OLED_ShowString(30, 48, "STOP", 16, 1);
}
void T_X_D(void)
{
    OLED_ShowString(0, 0, "T_C", 16, 1);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);

    OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
    OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
     OLED_ShowString(0, 32, "-->", 16, 1);
    OLED_ShowString(30, 16, "X_UP", 16, 1);
    OLED_ShowString(90, 16, "Y_UP", 16, 1);
    OLED_ShowString(30, 32, "X_D", 16, 1);
    OLED_ShowString(90, 32, "Y_D", 16, 1);
    OLED_ShowString(30, 48, "STOP", 16, 1);
}
void T_Y_D(void)
{
    OLED_ShowString(0, 0, "T_C", 16, 1);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);

    OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
    OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
     OLED_ShowString(54, 32, "-->", 16, 1);
    OLED_ShowString(30, 16, "X_UP", 16, 1);
    OLED_ShowString(90, 16, "Y_UP", 16, 1);
    OLED_ShowString(30, 32, "X_D", 16, 1);
    OLED_ShowString(90, 32, "Y_D", 16, 1);
    OLED_ShowString(30, 48, "STOP", 16, 1);
}
void STOP(void)
{
    OLED_ShowString(0, 0, "T_C", 16, 1);
    OLED_ShowString(32, 0, "X:", 16, 1);
    OLED_ShowString(78, 0, "S:", 16, 1);

    OLED_ShowNum(48, 0, Maichong_xia, 4, 16, 1); // 四位数
    OLED_ShowNum(96, 0, Maichong_Shang, 4, 16, 1);
     OLED_ShowString(0, 48, "-->", 16, 1);
    OLED_ShowString(30, 16, "X_UP", 16, 1);
    OLED_ShowString(90, 16, "Y_UP", 16, 1);
    OLED_ShowString(30, 32, "X_D", 16, 1);
    OLED_ShowString(90, 32, "Y_D", 16, 1);
    OLED_ShowString(30, 48, "STOP", 16, 1);
}
void Menu_OLED(void)
{
    int Road = 0;
    OLED_Refresh();
    if (Read_Key1 == 0 || Read_Key2 == 0 || Read_Key3 == 0 || Read_Key4 == 0||Read_Key6 == 0)
    {
        if (Read_Key1 == 0)
        {
            func_index = table[func_index].up; // 向下
            // Beep_DD();
            while (!Read_Key1)
                ;         // 松手检测
            OLED_Clear(); // 清屏只能放这里，放在其他地方会导致屏幕不亮
        }
        if (Read_Key2 == 0)
        {
            func_index = table[func_index].next; // 向下翻
                                                 // Beep_DD();
            while (!Read_Key2)
                ;         // 松手检测
            OLED_Clear(); // 清屏只能放这里，放在其他地方会导致屏幕不亮
        }
        if (Read_Key3 == 0)
        {
            if (func_index != 1)
            {
                func_index = table[func_index].back; // 返回
                while (!Read_Key3)
                    ;         // 松手检测
                OLED_Clear(); // 清屏只能放这里，放在其他地方会导致屏幕不亮
            }
            else
                Beep_DD();
        }
        if (Read_Key4 == 0)
        {
            while (!Read_Key4)
                ; // 松手检测
                  // if (func_index == 6 || func_index == 11 || func_index == 12 || func_index == 13 || func_index == 14 || func_index == 17 || func_index == 19 || func_index == 20 || func_index == 21|| func_index == 23|| func_index == 27|| func_index == 28|| func_index == 29|| func_index == 30)
                  // {
            switch (func_index)
            {
            case 6:
				PID_Num=0;
                Stop_Num = 0;
                PID_Duoji_Shang.target_val = O_Center[0].y;
                PID_Duoji_Xia.target_val = O_Center[0].x;
                Beep_DD();
                OLED_Clear();
                func_index = 1;
                break;
            case 11:

                if (Angle_Change == 1)
                    angle_xia++;
                else
                    Maichong_xia = Maichong_xia + 1;
                (*current_operation_index)();
                break;
            case 12:
                if (Angle_Change == 1)
                    angle_xia--;
                else
                    Maichong_xia = Maichong_xia - 1;
                (*current_operation_index)();
                break;
            case 13:
                if (Angle_Change == 1)
                    angle_shang++;
                else
                    Maichong_Shang = Maichong_Shang + 1;
                (*current_operation_index)();
                break;
            case 14:
                if (Angle_Change == 1)
                    angle_shang--;
                else
                    Maichong_Shang = Maichong_Shang - 1;
                (*current_operation_index)();
                break;
            case 17:
                OLED_Clear();
                func_index = 1;
                break;
            case 19:
                HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_SET);
                Beep_DD();
                break;
            case 20:
                HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_RESET);
                Beep_DD();
                Off();

                break;
            case 21:
                HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, GPIO_PIN_SET);
                Stop_Num = 0;
                Road = 0;
                while (1)
                {
                    // printf()
					PID_Num=0;
                    PID_Duoji_Xia.target_val = Bian_Point[Road].x;
                    PID_Duoji_Shang.target_val = Bian_Point[Road].y;
                    printf("%d,%d\n", Red_center[0].x, PID_Duoji_Xia.target_val);
                    // printf("%d,%d,%d,%d,%d,%d,%d,%d,%d\n", PID_Duoji_Shang.actual_val, PID_Duoji_Shang.target_val, PID_Duoji_Xia.actual_val, PID_Duoji_Xia.target_val, X, Y, Maichong_Shang, Maichong_xia, Stop_Num);
                    if (abs(Red_center[0].x - Bian_Point[Road].x) <= 2 && abs(Red_center[0].y - Bian_Point[Road].y) <= 2)
                    // while (abs(PID_Duoji_Shang.err) >= 2 || abs(PID_Duoji_Xia.err) >= 2)
                    {
                        Road++;
                        // Stop_Num = 0;
                    }
                    if (Road == 5)
                    {
                        break;
                    }
                }
                break;
            case 22:
            {
				Road_Num=1;
				Stop_Num=0;
				PID_Num=1;
                int numPoints = sizeof(points) / sizeof(points[0]);
                Maichong currentPos = points[0];

                {

                    for (int i = 1; i < numPoints; i++)
                    {
                        Maichong targetPos = points[i];

                        while (currentPos.x != targetPos.x || currentPos.y != targetPos.y)
                        {
                            if (Stop_Num == 0)
                            {
                                moveToPoint(targetPos, &currentPos);
                                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, currentPos.x);
                                __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, currentPos.y);
                            }

                            // printf("Moving to (%d, %d)\n", currentPos.x, currentPos.y);
                            HAL_Delay(25); // 暂停20毫秒
                        }
                    }
					Road_Num=0;
					Stop_Num=1;
                }
            }
            break;
            case 27:
            {
                Bian_Point[3].x = Red_center[0].x;
                Bian_Point[3].y = Red_center[0].y;
                OLED_Clear();
                func_index = 26;
            }
            break;
            case 28:
            {

                Bian_Point[0].x = Red_center[0].x;
                Bian_Point[0].y = Red_center[0].y;
                Bian_Point[4].x = Red_center[0].x;
                Bian_Point[4].y = Red_center[0].y;
                OLED_Clear();
                func_index = 26;
            }
            break;
            case 29:
            {
                Bian_Point[2].x = Red_center[0].x;
                Bian_Point[2].y = Red_center[0].y;
                OLED_Clear();
                func_index = 26;
            }
            break;
            case 30:
            {
                Bian_Point[1].x = Red_center[0].x;
                Bian_Point[1].y = Red_center[0].y;
                OLED_Clear();
                func_index = 26;
            }
            break;

            case 31:
            {
                O_Center[0].x = Red_center[0].x;
                O_Center[0].y = Red_center[0].y;
                OLED_Clear();
                func_index = 26;
            }
            break;
			 case 33:
            {
               points[3].x=Maichong_xia;
				points[3].y=Maichong_Shang;
                OLED_Clear();
                func_index = 32;
            }
            break;
			case 34:
            {
               points[0].x=Maichong_xia;
				points[0].y=Maichong_Shang;
                OLED_Clear();
                func_index = 32;
            }
            break;
			case 35:
            {
               points[2].x=Maichong_xia;
				points[2].y=Maichong_Shang;
                OLED_Clear();
                func_index = 32;
            }
            break;
			case 36:
            {
               points[1].x=Maichong_xia;//右下
				points[1].y=Maichong_Shang;
                OLED_Clear();
                func_index = 32;
            }
            break;
			case 38:
            {
				Stop_Num=0;
				PID_Num=1;
               if (Stop_Num == 0)
				   Maichong_xia--;
			   HAL_Delay(20);
                OLED_Clear();
                func_index = 42;
            }
            break;
			case 39:
            {
				Stop_Num=0;
				PID_Num=1;
               if (Stop_Num == 0)
			   {
				    Maichong_Shang++;
			   HAL_Delay(20);
			   }
				   
                OLED_Clear();
                func_index = 42;
            }
            break;
			case 40:
            {
				Stop_Num=0;
				PID_Num=1;
               if (Stop_Num == 0)
			   {
				    Maichong_xia++;
			   HAL_Delay(20);
			   }
				  
                OLED_Clear();
                func_index = 42;
            }
			case 41:
            {
				Stop_Num=0;
				PID_Num=1;
               if (Stop_Num == 0)
			   {
				    Maichong_Shang--;
			   HAL_Delay(20);
			   }
				   
                OLED_Clear();
                func_index = 42;
            }
			case 42:
			{
				Stop_Num =1;
				//PID_Num=1;
			}
            break;

            default:
                func_index = table[func_index].enter; // 确认
                                                      // Beep_DD();
                OLED_Clear();
                break;
            }
		
            //  }
            // else
            //   {

            //  }
            // OLED_Refresh();
            // OLED_Clear(); // 清屏只能放这里，放在其他地方会导致屏幕不亮
        }
		
    }

    if (func_index != last_index)
    {
        // printf("%c", func_index);
        current_operation_index = table[func_index].current_operation;

        (*current_operation_index)(); // 执行当前操作函数

        last_index = func_index;
    }
    if (func_index == 26 || func_index == 27 || func_index == 28 || func_index == 29 || func_index == 30|| func_index == 32|| func_index == 33|| func_index == 34|| func_index == 35|| func_index == 36|| func_index == 37|| func_index == 38|| func_index == 39|| func_index == 40|| func_index == 41|| func_index == 42)
    {
        current_operation_index = table[func_index].current_operation;
		OLED_Refresh();
        (*current_operation_index)(); // 执行当前操作函数
    }
}
