/*********************************************************************************************************************
* @file            car_adc.h
* @author          Andreas HF
* @Target core     CH32V307VCT6
* @revisions        -2022.09.07, V1.0
* @modify          none
********************************************************************************************************************/

#ifndef CAR_ADC_H_
#define CAR_ADC_H_

#include "headfile.h"

//�궨��
#define ADC_CH_1     ADC_IN2_A2
#define ADC_CH_2     ADC_IN3_A3
#define ADC_CH_3     ADC_IN4_A4
#define ADC_CH_4     ADC_IN5_A5
#define ADC_CH_5     ADC_IN6_A6

//��������
/* adc��ʼ�� */
void adc_channel_init(uint32_t adc_ch);
/* adcת��һ�� */
unsigned int adc_get(uint32_t adc_ch);

//ȫ�ֱ�������

#endif /* CAR_ADC_H_ */
