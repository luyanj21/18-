/*
 * turn.c
 *
 *  Created on: 2023年7月15日
 *      Author: cyl
 */
#include <barrier.h>
/*判断障碍
 *
 * 1.从五十行到一百六十行是否单调
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
    // 从车头往前 左边线是否单调
    if(barrier>10)
    {barrier_flag=1;}
    for(int i = START_H-2; i >=END_H; i--)
    {
        //丢线
        if(l_border[i]==0)
            continue;
        //当左边线每一行的值大于等于下面一行的时候
        if(l_border[i] >= l_border[i+1])    // i是Y坐标值  0 是图像左线X坐标
        {
            //当左边线小于屏幕中间向右找五个点的时候
            if(l_border[i]<MT9V03X_DVP_W/2-10)
                num++;
            else
                num = 0  ;
            //当num》50单调
            if(num == 48)
            {
                num = 0;
                leftState = 1;   // 左单调标志
                break;
            }
        }
        else
        {
            num = 0;
        }
        if(i <= END_H+1)  //   清0
            num = 0;
    }

    // 右边线是否单调
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
