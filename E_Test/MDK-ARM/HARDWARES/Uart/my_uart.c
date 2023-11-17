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

// 串口中断函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1) // 摄像头串口
    {
        if ((USART3_RX_STA & 0x8000) == 0) // 接收未完成
        {
            if ((USART3_RX_STA & 0x4000)) // 接收到了0xfe
            {
                if (USART3_RX_Data != 0x0c)
                {
                    USART3_RX_STA &= 0x3fff;
                    USART3_RX_BUF[USART3_RX_STA++] = 0x0c;
                    USART3_RX_BUF[USART3_RX_STA++] = USART3_RX_Data; // 防止数据中出现0xfe到时丢失数据
                }
                else
                {
                    // HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
                    USART3_RX_STA |= 0x8000; // 接收完成
                }
            }
            else
            {
                if (USART3_RX_Data == 0x0b)
                {
                    USART3_RX_STA |= 0x4000; // 接受到了0xfe
                }
                else
                {
                    USART3_RX_BUF[USART3_RX_STA & 0x3fff] = USART3_RX_Data;
                    USART3_RX_STA++;
                    if (USART3_RX_STA > (USART3_MAX_Receive_LEN - 1)) // 超出数据长度
                    {
                        USART3_RX_STA = 0;
                    }
                }
            }
            // u3_printf("%c",USART3_RX_BUF[0]);
        }
         HAL_UART_Receive_IT(&huart1, &USART3_RX_Data, 1);
    }
    else if (huart->Instance == USART3) // 串口1
    {
        LED_text;
        //        if (USART2_RX_Data > 0x30 && USART2_RX_Data < 0x39)
        //        {
        //            if (back_flag == 0) // 在送药途中识别数字，返回时不用识别
        //            {
        //                if (shuzi_flag == 0) // 未识别完成，停车
        //                {
        //                    USART2_RX_STA = 1;
        //                    shuzi[shuzi_count] = USART2_RX_Data;
        //                    shuzi_count++;
        //                    if (shuzi_count > 22) // 识别完成
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
        if ((USART2_RX_STA & 0x8000) == 0) // 接收未完成
        {
            if ((USART2_RX_STA & 0x4000)) // 接收到了0xfe
            {
                if (USART2_RX_Data != 0x0c)
                {
                    USART2_RX_STA &= 0x3fff;
                    USART2_RX_BUF[USART2_RX_STA++] = 0x0c;
                    USART2_RX_BUF[USART2_RX_STA++] = USART2_RX_Data; // 防止数据中出现0xfe到时丢失数据
                }
                else
                {
                    // HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
                    USART2_RX_STA |= 0x8000; // 接收完成
                }
            }
            else
            {
                if (USART2_RX_Data == 0x0b)
                {
                    USART2_RX_STA |= 0x4000; // 接受到了0xfe
                }
                else
                {
                    USART2_RX_BUF[USART2_RX_STA & 0x3fff] = USART2_RX_Data;
                    USART2_RX_STA++;
                    if (USART2_RX_STA > (USART2_MAX_Receive_LEN - 1)) // 超出数据长度
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
    void u3_printf(char *fmt, ...)//摄像头
    {
        va_list ap;
        va_start(ap, fmt);
        vsprintf((char *)USART3_TX_BUF, fmt, ap);
        va_end(ap);
        HAL_UART_Transmit(&huart1, USART3_TX_BUF, strlen((const char *)USART3_TX_BUF), HAL_MAX_DELAY);
    }
    void u2_printf(char *fmt, ...)//串口屏
    {
        va_list ap;
        va_start(ap, fmt);
        vsprintf((char *)USART2_TX_BUF, fmt, ap);
        va_end(ap);
        HAL_UART_Transmit(&huart3, USART2_TX_BUF, strlen((const char *)USART2_TX_BUF), HAL_MAX_DELAY);
    }
