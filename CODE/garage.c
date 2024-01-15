/*
 * garage.c
 *
 *  Created on: 2023年7月16日
 *      Author: lenovo
 */
#include "headfile.h"
/*
  * 斑马线检测
 *
 * */
//跳变点个数 黑白跳变点总和
int garage_count;
//黑白点标志位
int white_black;
//固定记录标志位
int black_white;
//单条线跳变点
//单行跳变点最多可以检出十七行
int region;
//车库标志位
int garageout_flag;

int find_zebra (void)
{
    //车库标志位置零
    garageout_flag=0;
    //行斑马线数量置零
    region=0;
    //行
    //从上到下遍历  上屏幕
    for(uint8 i = 45;i<50;i++)
        {
        //固定跳变点置0
        black_white=0;
        //斑马线跳变点
            garage_count= 0 ;
            //横向便利找边线  从左到右
            for(uint8 j= 10;j<180;j++)
             {
                //当碰到白色点的时候记为1   white-》255
                   if(Pixle[i][j]==255)
                   {
                       white_black=1;
                   }
                   //遇到黑色点的时候记为0
                   else
                   {
                     white_black=0;
                   }
                   //当黑白标志位不一致时
                   if(white_black!=black_white)
                   {
                     //白标志位等于白到黑标志位
                     black_white = white_black;
                     //斑马线数量加一
                     garage_count++;
                   }
                   //如果斑马线数大于十一
                   if(garage_count>14)
                 {
                       //总标志位加一
                   region++;
                 }
               }
          //当总标志位大于2时
         if(region>2)
               {
             //车库标志位为真
                   garageout_flag=1;
                   //跳出循环
                   break;
               }
           }
    //返回数值
    return garageout_flag;
}

/*
 * in_flag=2左拐入库 in_flag=1右拐入库
 * */
void garage_out(int out_flag)
{
    if(out_flag==1)
    {

        //向右拐出库
        car_forward();
        Delay_Ms(350);

        car_stop();
        Delay_Ms(1);

        car_turnright();
        Delay_Ms(400);
//        while(1)
//        {car_stop();}


    }
    if(out_flag==2)
    {
        //向左拐出库

        car_forward();
        Delay_Ms(350);


        car_stop();
        Delay_Ms(1);



        car_turnleft();
        Delay_Ms(400);

//  while(1)
//        {car_stop();}

    }

}
/*进车库 获得上拐点的坐标
 * 不传入上拐点坐标  而是进入之后开始寻找上拐点
 *
 *为了找到上拐点考虑更换扫线方式 1.八邻域 2.找从车库开始向中间找 找到第一个跳变点即为边线
 *
 * 判断左右车库？  从左右向中间扫线比较左右跳变点距离二维数组的距离进行判断
 *
 *转向标志位=1右拐入库 =2左拐入库
 * */

void garage_in(int in_flag)
{
    if(in_flag==1)
    {
//        向右拐入库
        car_forward();
        Delay_Ms(250);

        car_stop();
        Delay_Ms(1);

        car_turnright();
        Delay_Ms(450);

        car_stop();
        Delay_Ms(1);

        car_forward();
        Delay_Ms(200);
    }


    if(in_flag==2)
    {

        //左入库
        car_forward();
        Delay_Ms(300);



        car_stop();
        Delay_Ms(1);

        car_turnleft();
        Delay_Ms(450);

        car_stop();
        Delay_Ms(1);

        car_forward();
        Delay_Ms(200);

    }


//进库停车
    while(1)
    {car_stop();}

}
