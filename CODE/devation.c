/*
 * devation.c
 *
 *  Created on: 2023��7��10��
 *      Author: lenovo
 */
#include "headfile.h"

int get_devation(void)
{
    int devation=0;
    //��ȡ����
    //��ȡƫ��ֵ
    for (int i = 0; i < MT9V03X_DVP_H; i++)
    {
        mid_line_list[i] = (l_border[i] + r_border[i])/2;//������
    }
    for (int i = 50; i < MT9V03X_DVP_H; i++)
    {
        devation =devation +(mid_line_list[i]-MT9V03X_DVP_W/2+8);
    }
    devation =devation/MT9V03X_DVP_H;
return devation;
}
