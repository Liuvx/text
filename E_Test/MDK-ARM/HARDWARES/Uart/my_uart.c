#include "my_uart.h"
#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "stdarg.h"
// #include "control.h"

uint8_t USART3_RX_Data;
uint8_t USART3_TX_BUF[USART3_MAX_SEND_LEN];
uint8_t USART3_RX_BUF[USART3_MAX_Receive_LEN];
uint16_t USART3_RX_STA;

uint8_t USART2_RX_Data;
uint8_t USART2_TX_BUF[USART2_MAX_SEND_LEN];
uint8_t USART2_RX_BUF[USART2_MAX_Receive_LEN];
uint16_t USART2_RX_STA;

// �����жϺ���
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1) // ����ͷ����
    {
        if ((USART3_RX_STA & 0x8000) == 0) // ����δ���
        {
            if ((USART3_RX_STA & 0x4000)) // ���յ���0xfe
            {
                if (USART3_RX_Data != 0x0c)
                {
                    USART3_RX_STA &= 0x3fff;
                    USART3_RX_BUF[USART3_RX_STA++] = 0x0c;
                    USART3_RX_BUF[USART3_RX_STA++] = USART3_RX_Data; // ��ֹ�����г���0xfe��ʱ��ʧ����
                }
                else
                {
                    // HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
                    USART3_RX_STA |= 0x8000; // �������
                }
            }
            else
            {
                if (USART3_RX_Data == 0x0b)
                {
                    USART3_RX_STA |= 0x4000; // ���ܵ���0xfe
                }
                else
                {
                    USART3_RX_BUF[USART3_RX_STA & 0x3fff] = USART3_RX_Data;
                    USART3_RX_STA++;
                    if (USART3_RX_STA > (USART3_MAX_Receive_LEN - 1)) // �������ݳ���
                    {
                        USART3_RX_STA = 0;
                    }
                }
            }
            // u3_printf("%c",USART3_RX_BUF[0]);
        }
         HAL_UART_Receive_IT(&huart1, &USART3_RX_Data, 1);
    }
    else if (huart->Instance == USART3) // ����1
    {
        LED_text;
        //        if (USART2_RX_Data > 0x30 && USART2_RX_Data < 0x39)
        //        {
        //            if (back_flag == 0) // ����ҩ;��ʶ�����֣�����ʱ����ʶ��
        //            {
        //                if (shuzi_flag == 0) // δʶ����ɣ�ͣ��
        //                {
        //                    USART2_RX_STA = 1;
        //                    shuzi[shuzi_count] = USART2_RX_Data;
        //                    shuzi_count++;
        //                    if (shuzi_count > 22) // ʶ�����
        //                    {
        //                        shuzi_count = 22;
        //                        shuzi_flag = 1;
        //                    }
        //                }
        //            }
        //        }
        //        //HAL_UART_Receive_IT(&huart2, &USART2_RX_Data, 1);
        //    }
        //}
        if ((USART2_RX_STA & 0x8000) == 0) // ����δ���
        {
            if ((USART2_RX_STA & 0x4000)) // ���յ���0xfe
            {
                if (USART2_RX_Data != 0x0c)
                {
                    USART2_RX_STA &= 0x3fff;
                    USART2_RX_BUF[USART2_RX_STA++] = 0x0c;
                    USART2_RX_BUF[USART2_RX_STA++] = USART2_RX_Data; // ��ֹ�����г���0xfe��ʱ��ʧ����
                }
                else
                {
                    // HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
                    USART2_RX_STA |= 0x8000; // �������
                }
            }
            else
            {
                if (USART2_RX_Data == 0x0b)
                {
                    USART2_RX_STA |= 0x4000; // ���ܵ���0xfe
                }
                else
                {
                    USART2_RX_BUF[USART2_RX_STA & 0x3fff] = USART2_RX_Data;
                    USART2_RX_STA++;
                    if (USART2_RX_STA > (USART2_MAX_Receive_LEN - 1)) // �������ݳ���
                    {
                        USART2_RX_STA = 0;
                    }
                }
            }
            // u3_printf("%c",USART3_RX_BUF[0]);
        }
        HAL_UART_Receive_IT(&huart3, &USART2_RX_Data, 1);
    }
}
    void u3_printf(char *fmt, ...)//����ͷ
    {
        va_list ap;
        va_start(ap, fmt);
        vsprintf((char *)USART3_TX_BUF, fmt, ap);
        va_end(ap);
        HAL_UART_Transmit(&huart1, USART3_TX_BUF, strlen((const char *)USART3_TX_BUF), HAL_MAX_DELAY);
    }
    void u2_printf(char *fmt, ...)//������
    {
        va_list ap;
        va_start(ap, fmt);
        vsprintf((char *)USART2_TX_BUF, fmt, ap);
        va_end(ap);
        HAL_UART_Transmit(&huart3, USART2_TX_BUF, strlen((const char *)USART2_TX_BUF), HAL_MAX_DELAY);
    }
