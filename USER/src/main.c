/*********************************************************************************************************************
* @file            main.c
* @brief           ����ͷͼ����Ļ��ʾ����
* @author          lemon
* @version         1.0
* @Target core     CH32V307VCT6
* @date            2022-3-2
*
********************************************************************************************************************/

/* �û�ͷ�ļ� */
#include "main.h"
#include "headfile.h"
/* ȫ�ֱ������� */

/* ������ */
int main(void)
{
    /* �˴�������Ҫ�õ��ľֲ����� */

    /* ���ܳ���ʼ�� */
    car_init();

    /* �˴���д�������еĴ���(���磺��ʼ�������) */
    ips114_init();     //��ʼ����Ļ
    ips114_show_string(0,0,"CAM-IPS");
    ips114_show_string(0,20,"DEMO");
    mt9v03x_init_dvp();
    Delay_Ms(100);

    //�ȵ�����
    //�ӳ������⿴�����Ϊ2�ҳ�Ϊ1
    //��Ҫͬʱ����find_L�е�garage_in
    //��֤��������һ���������������

    garage_out(2);

    while(1)
    {
        /* �˴���д��Ҫѭ��ִ�еĴ��� */
        if(mt9v03x_finish_flag_dvp)
        {
            mt9v03x_finish_flag_dvp = 0;

            // ����ԭʼͼ���С,��ʾԭʼͼ��
            binaryzation(0);//��򷨶�ֵ��
            //����֮һ
            find_mid_line(Pixle);//�԰����������ߣ�����ֵΪƽ��ֵƫ��ֵ


            find_L(0);//��l�������Ӧ���ж�


            //��ͼ��ʱ��ֻ�ж�ֵ��ͼ�� û����
            int devation=get_devation();

            TraceMove(devation);
            forward();//ע�͵���`pwm���������Ӳ�ת  ����ͼ�񲻿�

            draw_line();
            ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
//            ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
            if(devation<0){devation=-devation;}
            ips114_show_uint(210,20,(uint32)devation,10);
//            if(pwm<0){pwm=-pwm;}
//            ips114_show_uint(210,40,(uint32)pwm,10);


        }
    }
}


