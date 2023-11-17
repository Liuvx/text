#include "json_pid.h"
float p, i, d, a;
int motor = 0;
cJSON *cJsonData, *cJsonVlaue;
extern uint8_t Usart1_ReadBuf[255]; // 串口1 缓冲数组
extern uint8_t Usart1_ReadCount;    // 串口1 接收字节计数
// json指令为{"p":30,"i":10,"d":0,"a":25}
void JSON_PD(int motor)
{
    // PID_init();
    if (motor == 1)
    {
        if (Usart_WaitReasFinish() == 0) // 是否接收完毕
        {
            cJsonData = cJSON_Parse((const char *)Usart1_ReadBuf);
            if (cJSON_GetObjectItem(cJsonData, "p") != NULL)
            {
                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "p");
                p = cJsonVlaue->valuedouble;
                pidMotor1Speed.Kp = p;
            }
            if (cJSON_GetObjectItem(cJsonData, "i") != NULL)
            {
                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "i");
                i = cJsonVlaue->valuedouble;
                pidMotor1Speed.Ki = i;
            }
            if (cJSON_GetObjectItem(cJsonData, "d") != NULL)
            {
                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "d");
                d = cJsonVlaue->valuedouble;
                pidMotor1Speed.Kd = d;
            }
            if (cJSON_GetObjectItem(cJsonData, "a") != NULL)
            {

                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "a");
                a = cJsonVlaue->valuedouble;
                pidMotor1Speed.target_val = a;
            }
            if (cJsonData != NULL)
            {
                cJSON_Delete(cJsonData); // 释放空间、但是不能删除cJsonVlaue不然会 出现异常错误
            }
            memset(Usart1_ReadBuf, 0, 255); // 清空接收buf，注意这里不能使用strlen
            printf("P:%.3f  I:%.3f  D:%.3f A:%.3f\r\n", p, i, d, a);
        }
    }
    else if (motor == 2)
    {
        if (Usart_WaitReasFinish() == 0) // 是否接收完毕
        {
            cJsonData = cJSON_Parse((const char *)Usart1_ReadBuf);
            if (cJSON_GetObjectItem(cJsonData, "p") != NULL)
            {
                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "p");
                p = cJsonVlaue->valuedouble;
                pidMotor2Speed.Kp = p;
            }
            if (cJSON_GetObjectItem(cJsonData, "i") != NULL)
            {
                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "i");
                i = cJsonVlaue->valuedouble;
                pidMotor2Speed.Ki = i;
            }
            if (cJSON_GetObjectItem(cJsonData, "d") != NULL)
            {
                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "d");
                d = cJsonVlaue->valuedouble;
                pidMotor2Speed.Kd = d;
            }
            if (cJSON_GetObjectItem(cJsonData, "a") != NULL)
            {

                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "a");
                a = cJsonVlaue->valuedouble;
                pidMotor2Speed.target_val = a;
            }
            if (cJsonData != NULL)
            {
                cJSON_Delete(cJsonData); // 释放空间、但是不能删除cJsonVlaue不然会 出现异常错误
            }
            memset(Usart1_ReadBuf, 0, 255); // 清空接收buf，注意这里不能使用strlen
            printf("P:%.3f  I:%.3f  D:%.3f A:%.3f\r\n", p, i, d, a);
        }
    }
    else if (motor == 3) // 电机1的距离
    {
        if (Usart_WaitReasFinish() == 0) // 是否接收完毕
        {
            cJsonData = cJSON_Parse((const char *)Usart1_ReadBuf);
            if (cJSON_GetObjectItem(cJsonData, "p") != NULL)
            {
                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "p");
                p = cJsonVlaue->valuedouble;
                Motor1_Distance.Kp = p;
            }
            if (cJSON_GetObjectItem(cJsonData, "i") != NULL)
            {
                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "i");
                i = cJsonVlaue->valuedouble;
                Motor1_Distance.Ki = i;
            }
            if (cJSON_GetObjectItem(cJsonData, "d") != NULL)
            {
                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "d");
                d = cJsonVlaue->valuedouble;
                Motor1_Distance.Kd = d;
            }
            if (cJSON_GetObjectItem(cJsonData, "a") != NULL)
            {

                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "a");
                a = cJsonVlaue->valuedouble;
                Motor1_Distance.target_val = a;
            }
            if (cJsonData != NULL)
            {
                cJSON_Delete(cJsonData); // 释放空间、但是不能删除cJsonVlaue不然会 出现异常错误
            }
            memset(Usart1_ReadBuf, 0, 255); // 清空接收buf，注意这里不能使用strlen
            printf("P:%.3f  I:%.3f  D:%.3f A:%.3f\r\n", p, i, d, a);
        }
    }
    else if (motor == 4) // 电机1的距离
    {
        if (Usart_WaitReasFinish() == 0) // 是否接收完毕
        {
            cJsonData = cJSON_Parse((const char *)Usart1_ReadBuf);
            if (cJSON_GetObjectItem(cJsonData, "p") != NULL)
            {
                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "p");
                p = cJsonVlaue->valuedouble;
                Motor2_Distance.Kp = p;
            }
            if (cJSON_GetObjectItem(cJsonData, "i") != NULL)
            {
                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "i");
                i = cJsonVlaue->valuedouble;
                Motor2_Distance.Ki = i;
            }
            if (cJSON_GetObjectItem(cJsonData, "d") != NULL)
            {
                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "d");
                d = cJsonVlaue->valuedouble;
                Motor2_Distance.Kd = d;
            }
            if (cJSON_GetObjectItem(cJsonData, "a") != NULL)
            {

                cJsonVlaue = cJSON_GetObjectItem(cJsonData, "a");
                a = cJsonVlaue->valuedouble;
                Motor2_Distance.target_val = a;
            }
            if (cJsonData != NULL)
            {
                cJSON_Delete(cJsonData); // 释放空间、但是不能删除cJsonVlaue不然会 出现异常错误
            }
            memset(Usart1_ReadBuf, 0, 255); // 清空接收buf，注意这里不能使用strlen
            printf("P:%.3f  I:%.3f  D:%.3f A:%.3f\r\n", p, i, d, a);
        }
    }

    // printf("Motor:%d  P:%.3f  I:%.3f  D:%.3f A:%.3f\r\n", motor, p, i, d, a);
}
