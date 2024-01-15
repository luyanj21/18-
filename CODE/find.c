/*
 * find..c
 *
 *  Created on: 2023年6月27日
 *      Author: lenovo
 */


#include"headfile.h"


uint8 l_border[MT9V03X_DVP_H];

uint8 r_border[MT9V03X_DVP_H];

uint8 mid_line_list[MT9V03X_DVP_H];


uint8 right_flag[MT9V03X_DVP_H];
uint8 left_flag[MT9V03X_DVP_H];
uint8 flag_line[MT9V03X_DVP_H];
int barrier;

//从中线往两边找  判断1/4 3/4
void find_mid_line(uint8 index[MT9V03X_DVP_H][MT9V03X_DVP_W])
{
     uint8 left_point=1;
     uint8 right_point=MT9V03X_DVP_W-1;

     uint8 l_flag=1;
     uint8 r_flag=1;

     barrier=0;
////////////////////////////////////////////
     l_border[0]=1;
     r_border[0]=MT9V03X_DVP_W-1;
     mid_line_list[0]=(left_point+right_point)/2;


     for(uint8 i=MT9V03X_DVP_H-1;i>0;i--)
     {
         l_flag=1;
         r_flag=1;
           //如果二分之一点是白点，从二分之一点找
         if(index[i][MT9V03X_DVP_W/2]==255)
         {
             //寻找左边点
             for(uint8 j=MT9V03X_DVP_W/2-1;j>0;j--)
             {
                 if(index[i][j]==0&&index[i][j+1]==255)
                 {
                     left_point=j;
                     break;
                 }
                 else
                 {
                     left_point=0;
                     l_flag=0;
                 }

             }
             //寻找右边点
             for(uint8 j=MT9V03X_DVP_W/2;j<MT9V03X_DVP_W;j++)
             {
                 if(index[i][j]==0&&index[i][j-1]==255)
                 {
                     right_point=j;
                     break;

                 }
                 else
                 {
                     right_point=MT9V03X_DVP_W-1;
                     r_flag=0;
                 }
             }

         }
         //如果 四分之一点是白点，从四分之一点找
         else if(index[i][MT9V03X_DVP_W/4]==255)
         {

             //寻找左边点
             for(uint8 j=MT9V03X_DVP_W/4-1;j>0;j--)
             {
                 if(index[i][j]==0&&index[i][j+1]==255)
                 {
                     left_point=j;
                     break;

                 }
                 else
                 {
                     left_point=0;
                     l_flag=0;
                 }
             }
             //寻找右边点
             for(uint8 j=MT9V03X_DVP_W/4+1;j<MT9V03X_DVP_W;j++)
             {
                 if(index[i][j]==0&&index[i][j-1]==255)
                 {
                     right_point=j;
                     break;

                 }
                 else
                 {
                     right_point=MT9V03X_DVP_W-1;
                     r_flag=0;
                 }
             }
         }
         //四分之三点黑色
         else if(index[i][MT9V03X_DVP_W/4*3]==255)
         {
             flag_line[i]=1;
             //寻找左边点
             for(uint8 j=MT9V03X_DVP_W/4*3-1;j>0;j--)
             {
                 if(index[i][j]==0&&index[i][j+1]==255)
                 {
                     left_point=j;
                     break;

                 }
                 else
                 {
                     left_point=0;
                     l_flag=0;
                 }

             }
             //寻找右边点
             for(uint8 j=MT9V03X_DVP_W/4*3+1;j<MT9V03X_DVP_W;j++)
             {
                 if(index[i][j]==0&&index[i][j-1]==255)
                 {
                     right_point=j;
                     break;

                 }
                 else
                 {
                     right_point=MT9V03X_DVP_W-1;
                     r_flag=0;
                 }

             }

         }
         else
         {
             //拐弯发电可能性不大 所以改回0，w这样便于避障判断

             //为防止拐点发电 这里没寻到的地方在大拐弯的地方应该等于上一行
//             left_point=l_border[i+1];//从下到上扫线上一行就是往下数一行 加一
//             right_point=r_border[i+1];
              left_point=0;//从下到上扫线上一行就是往下数一行 加一
              right_point=MT9V03X_DVP_W-1;
             r_flag=0;
             l_flag=0;
             if(i>20)
             {barrier++;}
         }

         l_border[i]=left_point;
         r_border[i]=right_point;

         left_flag[i]=l_flag;
         right_flag[i]=r_flag;

     }


}





#define START_H MT9V03X_DVP_H-40
//为了尽量判断是不受到道路影响可以将startH适当调高防止道路边线受到影响 的同时又不对正常扫弦造成影响
#define END_H 0//不能小于这个数
/*
 *  单调必须保证最上端的像素是直的  下方的像素可能因为摄像头过低导致的赛道边线找不到而变成非单调
 *  最好对上端单个像素进行判断
 *  在这里发现i如果是uint类型的会导致只有while循环外的代码执行 有初始化字样而没有图像或边线显示
 *  而换成int类型的变量之后又可以正常显示
 *  其中i可以等于0
 *
 *
 *因为find里面把寻不到变现的地方给赋值成为上一行的数值 这样就会影响到边线是否单调的判断在障碍判断的时候直接不会进入避障的程序
 *所以在这里把便鲜花去的地方改成在获取不到白色点的时候就划取为那一个最左最右
 *
 *上面的条件加强了会进不去圆环 减弱了会瞎进圆环
 *可以将条件再次加强 添加丢线的判断 再次加入形参 lose_num
 *并且在判断的时候使用而不在正常寻仙的时候加入 能保持进条件正常的同时不会瞎进圆环
 *
 */
void find_L(int mode)
{
    int i = 0;
    //做右边线是否单调
    uint8_t leftState = 0;
    uint8_t rightState = 0;

//    uint8_t count = 0;
    uint8_t num = 0, py;


    //左右边弧判断标志位
    int errL=0;
    int errR=0;
    //车库判断标志位
    int garage_flag=0;
    int barrier_flag=0;


    // 从车头往前 左边线是否单调
    for(i = START_H-2; i >=END_H; i--)
    {
        //丢线
        if(l_border[i]== 0)
            continue;
        //当左边线每一行的值大于等于下面一行的时候
        if(l_border[i] >= l_border[i+1])    // i是Y坐标值  0 是图像左线X坐标
        {
            //当左边线小于屏幕中间向右找五个点的时候
            if(l_border[i]<MT9V03X_DVP_W/2)
                num++;
            else
                num = 0  ;
            //当num》50单调
            if(num == 78)
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
    for(i = START_H-2; i >=END_H; i--)
    {
        if(r_border[i] == MT9V03X_DVP_W-1)
            continue;

        if(r_border[i]<= r_border[i+1])
        {
            if(r_border[i]>MT9V03X_DVP_W/2)
                    num++;
            else
                    num = 0;


            if(num ==78)
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




    //判断元素
    //一边单调一边不单调进入圆环
    if(rightState==1&&leftState==0)
    {
        //加弧线判断 不然会直接进入环岛
        //左弧线判断
        errL = RoundaboutGetArc( 1, 3, &py,120,0,60,30);//round_size圆弧的大小      圆弧的大小 用点数表示  （连续N个增  连续N个减）
        //左圆环
        if(errL==1)
        {

            RoundaboutProcess(2);//左圆环

        }

    }if(leftState==1&&rightState==0)
    {
        errR = RoundaboutGetArc( 2, 3, &py,120,0,60,30);//1是左边线   2是右边线
        //右圆环
        if(errR==1)
        {

            RoundaboutProcess(1);//右圆环

        }

    }

    //两边均不单调 是弯道或者 车库 或者是障碍
    if(rightState==0&&leftState==0)
    {

        //判断斑马线
        garage_flag=find_zebra();
        //判断标志位
        if(garage_flag)
        {
            garage_in(2);

        }



        ///////////////////////////////////////////////////////////
        //判断障碍
        barrier_flag=find_barrier();
        if(barrier_flag==1)
        {
            barrier_turn();
        }
        ////////////////////////////////////////////////////////////
    }
}
