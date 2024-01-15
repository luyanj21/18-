/*
 * turn.c
 *
 *  Created on: 2023��7��15��
 *      Author: cyl
 */
#include <barrier.h>
/*�ж��ϰ�
 *
 * 1.����ʮ�е�һ����ʮ���Ƿ񵥵�
 *
 * */
#define START_H 110
#define END_H 60
int find_barrier(void)
{
    int barrier_flag=0;
    int leftState=0;
    int rightState=0;
    int num=0;
    // �ӳ�ͷ��ǰ ������Ƿ񵥵�
    if(barrier>10)
    {barrier_flag=1;}
    for(int i = START_H-2; i >=END_H; i--)
    {
        //����
        if(l_border[i]==0)
            continue;
        //�������ÿһ�е�ֵ���ڵ�������һ�е�ʱ��
        if(l_border[i] >= l_border[i+1])    // i��Y����ֵ  0 ��ͼ������X����
        {
            //�������С����Ļ�м�������������ʱ��
            if(l_border[i]<MT9V03X_DVP_W/2-10)
                num++;
            else
                num = 0  ;
            //��num��50����
            if(num == 48)
            {
                num = 0;
                leftState = 1;   // �󵥵���־
                break;
            }
        }
        else
        {
            num = 0;
        }
        if(i <= END_H+1)  //   ��0
            num = 0;
    }

    // �ұ����Ƿ񵥵�
    for(int i = START_H-2; i >=END_H; i--)
    {
        if(r_border[i] == MT9V03X_DVP_W-1)
            continue;

        if(r_border[i]<= r_border[i+1])
        {
            if(r_border[i]>MT9V03X_DVP_W/2+10)
                    num++;
            else
                    num = 0;


            if(num ==48)
            {
                num = 0;
                rightState = 1;
                break;
            }
        }
        else
        {
              num = 0;
        }

        if(i <= END_H+1)
            num = 0;
    }


    ips114_show_uint(210,40,(uint32)rightState,10);
    ips114_show_uint(210,60,(uint32)leftState,10);

    if(barrier_flag==1&&rightState==1&&leftState==1)
    {
        return 1;
    }
    return 0;
}
void barrier_turn(void)
{

//    if(barrier>8)
//    {

                car_turnright();
                Delay_Ms(350);



                car_stop();
                Delay_Ms(1);

                car_forward();
                Delay_Ms(500);
//

                car_stop();
                Delay_Ms(1);

                car_turnleft();
                Delay_Ms(500);
//
                car_stop();
                Delay_Ms(1);

                car_forward();
                Delay_Ms(1000);
//
                car_stop();
                Delay_Ms(1);

                car_turnright();
                 Delay_Ms(100);
    }
