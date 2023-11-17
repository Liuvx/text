#include "json_pid.h"
float p, i, d, a;
int motor = 0;
cJSON *cJsonData, *cJsonVlaue;
extern uint8_t Usart1_ReadBuf[255]; // ����1 ��������
extern uint8_t Usart1_ReadCount;    // ����1 �����ֽڼ���
// jsonָ��Ϊ{"p":30,"i":10,"d":0,"a":25}
void JSON_PD(int motor)
{
    // PID_init();
    if (motor == 1)
    {
        if (Usart_WaitReasFinish() == 0) // �Ƿ�������
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
                cJSON_Delete(cJsonData); // �ͷſռ䡢���ǲ���ɾ��cJsonVlaue��Ȼ�� �����쳣����
            }
            memset(Usart1_ReadBuf, 0, 255); // ��ս���buf��ע�����ﲻ��ʹ��strlen
            printf("P:%.3f  I:%.3f  D:%.3f A:%.3f\r\n", p, i, d, a);
        }
    }
    else if (motor == 2)
    {
        if (Usart_WaitReasFinish() == 0) // �Ƿ�������
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
                cJSON_Delete(cJsonData); // �ͷſռ䡢���ǲ���ɾ��cJsonVlaue��Ȼ�� �����쳣����
            }
            memset(Usart1_ReadBuf, 0, 255); // ��ս���buf��ע�����ﲻ��ʹ��strlen
            printf("P:%.3f  I:%.3f  D:%.3f A:%.3f\r\n", p, i, d, a);
        }
    }
    else if (motor == 3) // ���1�ľ���
    {
        if (Usart_WaitReasFinish() == 0) // �Ƿ�������
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
                cJSON_Delete(cJsonData); // �ͷſռ䡢���ǲ���ɾ��cJsonVlaue��Ȼ�� �����쳣����
            }
            memset(Usart1_ReadBuf, 0, 255); // ��ս���buf��ע�����ﲻ��ʹ��strlen
            printf("P:%.3f  I:%.3f  D:%.3f A:%.3f\r\n", p, i, d, a);
        }
    }
    else if (motor == 4) // ���1�ľ���
    {
        if (Usart_WaitReasFinish() == 0) // �Ƿ�������
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
                cJSON_Delete(cJsonData); // �ͷſռ䡢���ǲ���ɾ��cJsonVlaue��Ȼ�� �����쳣����
            }
            memset(Usart1_ReadBuf, 0, 255); // ��ս���buf��ע�����ﲻ��ʹ��strlen
            printf("P:%.3f  I:%.3f  D:%.3f A:%.3f\r\n", p, i, d, a);
        }
    }

    // printf("Motor:%d  P:%.3f  I:%.3f  D:%.3f A:%.3f\r\n", motor, p, i, d, a);
}
