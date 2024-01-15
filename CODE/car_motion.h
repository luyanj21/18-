/*********************************************************************************************************************
* @file            car_motion.h
* @author          Andreas HF
* @Target core     CH32V307VCT6
* @revisions       -2022.9.18
* @modify          none
********************************************************************************************************************/

#ifndef __CAR_MOTION_H
#define __CAR_MOTION_H

#include "headfile.h"

//��������
/* С��ֱ�� */
void car_forward(void);
/* С������ */
void car_back(void);
/* ͣ�� */
void car_stop(void);
/* С����ת */
void car_turnleft(void);
/* С����ת */
void car_turnright(void);
/*Բ��ֱ��*/
void circle_forward(void);
#endif
