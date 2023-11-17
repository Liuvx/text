#include "blue.h"
#include "stdio.h"
#include <string.h>
/// @brief ����������
/// @param  ����1λ�ַ���1Ϊǰ����2Ϊ���ˣ�3Ϊ��ת��4Ϊ��ת��5Ϊԭ����ת��6Ϊԭ����ת��7Ϊֹͣ��
int32_t Xunji_N = 0;
extern uint32_t Car_Back_number;
extern uint8_t Usart1_ReadBuf[255]; // ����1 ��������
extern uint8_t Usart1_ReadCount;    // ����1 �����ֽڼ���
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
        if (Usart1_ReadBuf[0] == 0x37) // ֹͣ
        {
            Car_Stop();
            Xunji_N = 0;
            // Car_Back_number = 1;  // ȡ���ж�
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            Beep_DD();
        }
        if (Usart1_ReadBuf[0] == 0x38) // ����Ѱ��
        {
            Xunji_N = 1;          // ����Ѱ��
            Car_Back_number = 1;  // �رյ���
            Stop_Immediately = 0; // ����ֹͣ�ر�
            Car_Go();
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            Beep_DD();
        }
        memset(Usart1_ReadBuf, 0, 255); // ��ս���buf��ע�����ﲻ��ʹ��strlen
    }
}
