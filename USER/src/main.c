/*********************************************************************************************************************
* @file            main.c
* @brief           摄像头图像屏幕显示例程
* @author          lemon
* @version         1.0
* @Target core     CH32V307VCT6
* @date            2022-3-2
*
********************************************************************************************************************/

/* 用户头文件 */
#include "main.h"
#include "headfile.h"
/* 全局变量声明 */

/* 主函数 */
int main(void)
{
    /* 此处声明需要用到的局部变量 */

    /* 智能车初始化 */
    car_init();

    /* 此处编写单次运行的代码(例如：初始化代码等) */
    ips114_init();     //初始化屏幕
    ips114_show_string(0,0,"CAM-IPS");
    ips114_show_string(0,20,"DEMO");
    mt9v03x_init_dvp();
    Delay_Ms(100);

    //先调焦距
    //从车库向外看从左出为2右出为1
    //需要同时调整find_L中的garage_in
    //保证两个数字一样就能正常出入库

    garage_out(2);

    while(1)
    {
        /* 此处编写需要循环执行的代码 */
        if(mt9v03x_finish_flag_dvp)
        {
            mt9v03x_finish_flag_dvp = 0;

            // 根据原始图像大小,显示原始图像
            binaryzation(0);//大津法二值化
            //二分之一
            find_mid_line(Pixle);//对半找赛道中线，返回值为平均值偏差值


            find_L(0);//找l点进入相应的判断


            //卡图的时候只有二值化图像 没有线
            int devation=get_devation();

            TraceMove(devation);
            forward();//注释掉求`pwm函数后轮子不转  而且图像不卡

            draw_line();
            ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
//            ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
            if(devation<0){devation=-devation;}
            ips114_show_uint(210,20,(uint32)devation,10);
//            if(pwm<0){pwm=-pwm;}
//            ips114_show_uint(210,40,(uint32)pwm,10);


        }
    }
}


