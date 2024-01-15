/*********************************************************************************************************************
* @file            car_reed.h
* @author          Fantastic Potato
* @Target core     CH32V307VCT6
* @revisions       -2022.09.18
* @modify          none
********************************************************************************************************************/

#ifndef CAR_REED_H_
#define CAR_REED_H_

#include "headfile.h"


//��������
/* ���ܳ��ɻɹܳ�ʼ�� */
void reed_init(void);
/* ���ܳ��ű��� */
void reed_check(void);


//ȫ�ֱ�������
extern unsigned char g_reed_flag;

#endif /* CAR_REED_H_ */
