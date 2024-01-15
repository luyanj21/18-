/*********************************************************************************************************************
* @file            board_led.h
* @author          Davis Klay HF
* @Target core     CH32V307VCT6
* @revisions       -2022.10.7, V1.0
* @modify          none
********************************************************************************************************************/

#ifndef BOARD_LED_H_
#define BOARD_LED_H_

#include "headfile.h"

//�궨��
#define LED1    1
#define LED2    2

#define LED1_PIN     E2
#define LED1_MODE    OUT_PP


#define LED2_PIN     E3
#define LED2_MODE    OUT_PP

#define ON      0
#define OFF     1


//��������
/* ����LED��ʼ�� */
void board_led_init(unsigned char led_num);
/* ����LED���� */
void board_led_on(unsigned char led_num);
/* ����LEDϨ�� */
void board_led_off(unsigned char led_num);
/* ����LED��ƽ��ת */
void board_led_toggle(unsigned char led_num);

//ȫ�ֱ�������

#endif
