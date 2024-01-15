/*********************************************************************************************************************
* @file            car_init.c
* @author          Andreas HF
* @Target core     CH32V307VCT6
* @revisions       2022.09.07, V1.0
* @modify          none
********************************************************************************************************************/

#include "car_init.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief        ������pwm��ʼ��
// @param        void
// @return       void
// Sample usage:        car_init();
                        //���ܳ���ʼ��
//-------------------------------------------------------------------------------------------------------------------

void car_init()
{
//    DisableGlobalIRQ();                                         //Ĭ�Ϲ������ж�
//    interrupt_global_disable();
    board_init();
    Delay_Init();

    /* ��ʼ����� */
    motor_init(left);
    motor_init(right);

    /* ��ʼ������ */
    key_init(K1);
    key_init(K2);
    key_init(K3);
    key_init(K4);
    key_init(K5);
    key_init(K6);

    adc_init(ADC_IN2_A2);
    adc_init(ADC_IN3_A3);
    adc_init(ADC_IN4_A4);
    adc_init(ADC_IN5_A5);
    adc_init(ADC_IN6_A6);

    /* ��ʼ������LED */
    board_led_init(LED1);
    board_led_init(LED2);

    /* ��ʼ��RGB���� */
    ws2812b_init();

    /* ��ʼ���ɻɹ� */
    reed_init();

    /* ��ʼ���ж� */
    int_init();
    interrupt_global_enable();
}

//-------------------------------------------------------------------------------------------------------------------
// @brief        �жϳ�ʼ��
// @param        void
// @return       void
// Sample usage:        int_init();//�жϳ�ʼ��
//-------------------------------------------------------------------------------------------------------------------
void int_init(void)
{
}



