#include "blue.h"
#include "stdio.h"
#include <string.h>
/// @brief 蓝牙处理部分
/// @param  接收1位字符，1为前进，2为后退，3为左转，4为右转，5为原地左转，6为原地右转，7为停止。
int32_t Xunji_N = 0;
extern uint32_t Car_Back_number;
extern uint8_t Usart1_ReadBuf[255]; // 串口1 缓冲数组
extern uint8_t Usart1_ReadCount;    // 串口1 接收字节计数
extern uint32_t Stop_Immediately;

void BLUE_TR(void)
{
    if (Usart_WaitReasFinish() == 0)
    {
        // printf("%c", Usart1_ReadBuf[0]);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        //  if (strncmp((const char *)Usart1_ReadBuf, "{}", 1) == 0)
        if (Usart1_ReadBuf[0] == 0x31)
        {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            Car_Go();
            Beep_DD();
        }
        if (Usart1_ReadBuf[0] == 0x32)
        {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            Car_Back();
            Beep_DD();
        }
        if (Usart1_ReadBuf[0] == 0x33)
        {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            Car_Left();
            Beep_DD();
        }
        if (Usart1_ReadBuf[0] == 0x35)
        {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            Car_Left_Inplace();
            Beep_DD();
        }
        if (Usart1_ReadBuf[0] == 0x34)
        {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            Car_Right();
            Beep_DD();
        }
        if (Usart1_ReadBuf[0] == 0x36)
        {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            Car_Right_Inplace();
            Beep_DD();
        }
        if (Usart1_ReadBuf[0] == 0x37) // 停止
        {
            Car_Stop();
            Xunji_N = 0;
            // Car_Back_number = 1;  // 取消判断
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            Beep_DD();
        }
        if (Usart1_ReadBuf[0] == 0x38) // 开启寻迹
        {
            Xunji_N = 1;          // 开启寻迹
            Car_Back_number = 1;  // 关闭倒回
            Stop_Immediately = 0; // 紧急停止关闭
            Car_Go();
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            Beep_DD();
        }
        memset(Usart1_ReadBuf, 0, 255); // 清空接收buf，注意这里不能使用strlen
    }
}
