//
// Created by ���ο� on 24-9-19.
//

#include "buzzer.h"
#include "iwdg.h"
// GPIO ��ʼ������

void Buzzer_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // ʹ��GPIOAʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // ����PA11Ϊ�������
    GPIO_InitStruct.Pin = BUZZER_PIN; // ʹ��PA11���Ʒ�����
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // �������ģʽ
    GPIO_InitStruct.Pull = GPIO_PULLUP; // ��������
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // ����
    HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);
}

// �򿪷�����
void Buzzer_On(void)
{
    // ��proteus�������Ǹߵ�ƽ����
    //HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET); // �͵�ƽ����������
    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);
}

// �رշ�����
void Buzzer_Off(void)
{
    //HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET); // �ߵ�ƽ�رշ�����
    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
}

void Buzzer_Alarm(int distance) // distance Ϊ��������
{
    // ���ݾ�������ӳ�ʱ�䣬����Խ�����ӳ�Խ��
    // �趨��С������ӳ�
    int minDelay = 50; // ��С�ӳ�ʱ��
    int maxDelay = 400; // ����ӳ�ʱ��
    int delayTime = (distance * (maxDelay - minDelay)) / 100; // �����ӳ�ʱ��

    // �����ӳ�ʱ���ں���Χ��
    if (delayTime < minDelay) {
        delayTime = minDelay; // ��֤��������С�ӳ�
    }

    for (int i = 0; i < 5; i++) // ��������
    {
        Buzzer_On();            // �򿪷�����
        HAL_Delay(delayTime);   // ��������ӳ�ʱ�䱣��
        Buzzer_Off();          // �رշ�����
        HAL_Delay(delayTime);   // ��������ӳ�ʱ����
    }
    HAL_IWDG_Refresh(&hiwdg);   //���Ź�ι��
}