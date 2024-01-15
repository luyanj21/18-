/*
 * huandao.c
 *
 *  Created on: 2023年7月6日
 *      Author: cyl
 */

#include <circle.h>

#define START_H     120//从下到上 start较小
#define END_H       0
#define round_size  5

uint32_t imageOut[2][MT9V03X_DVP_W];//0上 1下


uint8_t UpdownSideGet(void)
{

    uint8_t i = 0, j = 0;
    uint8_t last = MT9V03X_DVP_H/2+20;

     //从图像中间行    从中到下     从中到上      扫描
    imageOut[0][MT9V03X_DVP_W/2] =0;
    imageOut[1][MT9V03X_DVP_W/2] =MT9V03X_DVP_H-1;

    //处理中间单独那一列的上下边线
    for(i = last; i > 0; i--)
    {
        //0,h/2
        if(!Pixle[i][MT9V03X_DVP_W/2])
        {
            imageOut[0][MT9V03X_DVP_W/2] = i;
            break;
        }
    }

    for(i = last; i < MT9V03X_DVP_H; i++)
    {
        if(!Pixle[i][MT9V03X_DVP_W/2])
        {
            imageOut[1][MT9V03X_DVP_W/2] = i;
            break;
        }
    }

    //其他列的上下边线
    //从中到左
    for(i = MT9V03X_DVP_W/2-1; i > 0; i--)//遍历每一列
    {
        imageOut[0][i] = 0;
        imageOut[1][i] = MT9V03X_DVP_H-1;

        for(j = imageOut[0][i+1] + 5; j > 0; j--)//一列中的扫描每行  从上列的行数+10开始向上扫描
        {
            //防止出界
            if(imageOut[0][i+1] + 5>MT9V03X_DVP_H)
            {break;}

            if(!Pixle[j][i])
            {
                imageOut[0][i] = j;
                break;
            }
        }
        for(j = imageOut[1][i+1] - 5; j < MT9V03X_DVP_H; j++)
        {

            //防止出界
            if(imageOut[1][i+1] - 5<0)
            {break;}

            if(!Pixle[j][i])
            {
                imageOut[1][i] = j;
                break;
            }
        }
    }

    //从中到右
    for(i = MT9V03X_DVP_W/2+1; i < MT9V03X_DVP_W-1; i++)
        {
            imageOut[0][i] = 0;
            imageOut[1][i] = MT9V03X_DVP_H-1;

            for(j = imageOut[0][i-1] + 5; j > 0; j--)
            {
                //防出界
                if(imageOut[0][i+1] + 5>MT9V03X_DVP_H)
                {break;}

                if(!Pixle[j][i])
                {
                    imageOut[0][i] = j;
                    break;
                }
            }
            for(j = imageOut[1][i-1] - 5; j < MT9V03X_DVP_H; j++)
            {

                //防出界
                if(imageOut[1][i+1] - 5<0)
                {break;}

                if(!Pixle[j][i])
                {
                    imageOut[1][i] = j;
                    break;
                }
            }
        }
    return 0;
}

/*
 * 判断出环的a字形角点用的弧形判断
 * 因为加上了丢线判断之后会无法判断出环的a字形角点 这个判断去除丢线条件
 * status:1左2右    num：A点的差值    start大 end小
 * */
uint16_t RoundaboutGet_A( uint8_t status, uint8_t num,uint8 start,uint8 end )
{

    int i = 0;
    switch(status)
    {
    //左边线
      case 1:
          //从下到上遍历
        for(i =start-2; i >end; i--)
        {
            //
            if(l_border[i]<l_border[i+1]&&(l_border[i+1]-l_border[i]>num))
            {
                return 1;
            }

        }

        break;

      case 2:
        for(i =start-2; i > end; i--)
        {


                /* 有弧线 */
                if(r_border[i]>r_border[i+1]&&(r_border[i]-r_border[i+1]>num))
                {
                    return 1;
                }
        }
        break;
    }

    return 0;
}



/*!
  * @brief    判断左右边线是否存在弧形
      * 输出的 index 圆弧的顶点位置
  * @param    imageInput ： 二值图像信息
  * @param    imageOut   ： 边线数组
  * @param    status     ： 1：左边线  2：右边线
  * @param    num        ： 圆弧的大小 用点数表示  （连续N个增  连续N个减）
  * @return   1 有弧线    0  没弧线

  *
//uint8_t imageSide[MT9V03X_DVP_H][2];
*会将将过弯时的弯道识别成圆弧
 * 原先的方案会导致进不去环
 * 或者在调用的时候放一个标志位放一个标志位进去 如果曾经丢过线就  不行的 这样会照样把
 *
 * 将单调的条件向上压 把圆环的条件的条件向下调  需要让拐弯的外侧线识别成不单调
 * 这时
 *
 * 因为会丢线所以将丢线作为有圆弧的判断条件
 *
 * 丢线作为判断条件并不是很好 因为少了进圆环的第二阶段就会变早
 *
 * 现在将下边弧的个数作为判断条件
 * 在判断上边弧的时候判断下边弧的个数
 * 设置一个决定圆弧的上下边弧的形参
 *
 *
 * 增加一个计数丢线的变量lose 比较丢线的lose_num
 * */
uint16_t RoundaboutGetArc( uint8_t status, uint8_t num,uint8_t* index,uint8 start,uint8 end,uint8 down_num,uint8 lose_num)
{
    int left_flag=0;
    int right_flag=0;
    int i = 0;
    uint8_t inc = 0, dec = 0, n = 0;
    //记录丢线
    int lose=0;
    switch(status)
    {
    //左边线
      case 1:
          //从下到上遍历
        for(i =start-2; i >end; i--)
        {
            //判断是否有丢线
            //如果边线从最右边到
            //如果丢线就会contine到下一次for循环？应该行的吧
            //因为不hi出现最上方有丢线行还会
            //会出现 不行 得加flag判断
            //应该是可以的 因为在金源换阶段中不会出现 会出现 a字形 不会 a字形独立出去了
            //所以使用continue进行跳出
            //使用continue会导致弧线顶点出现误判
//            if(l_border[i]!= 0 && l_border[i+1]== 0)
//            {
//                left_flag=1;
//            }
            if(l_border[i]==0)
            {
                left_flag=1;
                lose++;
//                continue;
            }
            //上下两行没有同时是边框
//            if(l_border[i]!= 1 && l_border[i+1]!= 1)
            if(l_border[i]!= 1 && l_border[i+1]!= 1&&left_flag==1)
            {
                //如果两个相等
                if(l_border[i] == l_border[i+1])
                {
                    n++;
                    continue;
                }
                //如果下边先小于上边线
                //下边弧
                if(l_border[i] > l_border[i+1])
                {
                    //inc是下边弧的数量
                    inc++;
                    inc+=n;
                    n=0;
                }
                //如果下边线小于上边线
                //上边弧
                else
                {
                    dec++;
                    dec+=n;
                    n=0;
                }

                /* 有弧线 */
                //上下弧线都大于上下边线的值
                //并且下边弧不得大于形参 down_num
                if(inc > num && dec > num && inc<down_num && lose>lose_num)
                {
                    *index = i + num;
                    return 1;
                }
            }
            else
            {
                inc = 0;
                dec = 0;n=0;
            }
        }

        break;

      case 2:
        for(i =start-2; i > end; i--)
        {
            ////////////////////////////////////////////////////////////
//            if(r_border[i]!= MT9V03X_DVP_W-1 && r_border[i+1]== MT9V03X_DVP_W-1)
//            {
//                right_flag=1;
//            }
//            if(r_border[i] != MT9V03X_DVP_W-1 && r_border[i+1] != MT9V03X_DVP_W-1)
                ////////////////////////////////////////////////////////////
            if(r_border[i]==MT9V03X_DVP_W-1)
            {
                right_flag=1;
                lose++;
//                continue;
            }
            ////////////////////////////////////////

                if(r_border[i] != MT9V03X_DVP_W-1 && r_border[i+1] != MT9V03X_DVP_W-1&&right_flag==1)
            {

                if(r_border[i] == r_border[i+1])
                {
                    n++;
                    continue;
                }
                if(r_border[i]> r_border[i+1])
                {
                    inc++;
                    inc+=n;
                    n = 0;
                }
                else
                {
                    dec++;
                    dec+=n;
                    n=0;
                }

                /* 有弧线 */
                if(inc > num && dec > num && inc<down_num&&lose>lose_num)
                {
                    *index = i + num;
                    return 1;
                }
            }
            else
            {
                inc = 0;
                dec = 0;n=0;
            }
        }

        break;
    }

    return 0;
}

/*!
   * @brief    补线处理
   *
   * @param    imageSide  : 边线
   * @param    status     : 1：左边线补线   2：右边线补线
   * @param    startX     : 起始点 列数
   * @param    startY     : 起始点 行数
   * @param    endX       : 结束点 列数
   * @param    endY       : 结束点 行数
   *
   * @return
   *
   * @note     endY 一定要大于 startY
   *
   */
 void ImageAddingLine( uint8_t status, uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY)
 {
     int i = 0;

     // 直线 x = ky + b
     float k = 0.0f, b = 0.0f;
//     switch(status)
//     {
//       case 1://左补线
//         {
//             k = (float)((float)endX - (float)startX) / (float)((float)endY - (float)startY);
//             b = (float)startX - (float)startY * k;
//
//             for(i = startY; i < endY; i++)
//             {
//                 l_border[i] = (uint8_t)(k * i + b);
//             }
//             break;
//         }
//
//       case 2://右补线
//         {
//             while(1)
//             {car_stop();}
//             k = (float)((float)endX - (float)startX) / (float)((float)endY - (float)startY);
//             b = (float)startX - (float)startY * k;
//
//             for(i = startY; i < endY; i++)
//             {
//                 r_border[i] = (uint8_t)(k * i + b);
//             }
//             break;
//         }
//
//     }
     while(1)
         {
           if(status==1)//左补线
             {
                 k = (float)((float)endX - (float)startX) / (float)((float)endY - (float)startY);
                 b = (float)startX - (float)startY * k;

                 for(i = startY; i < endY; i++)
                 {
                     l_border[i] = (uint8_t)(k * i + b);
                 }
                 break;
             }

           if(status==2)//右补线
             {
                 k = (float)((float)endX - (float)startX) / (float)((float)endY - (float)startY);
                 b = (float)startX - (float)startY * k;

                 for(i = startY; i < endY; i++)
                 {
                     r_border[i] = (uint8_t)(k * i + b);
                 }
                 break;
             }

         }
 }


 /*!
   * @brief    判断上边线是否单调
   * @param    X1 :起始X点
   * @param    X2 :终止X点              X1 < X2
   * @param    imageIn ： 边线数组
   *
   * @return   0：不单调or错误， 1：单调递增， 2：单调递减
   *
   * @note down为限制下边线最下点用的
   *
   * @see
   *
   * @date     2021/11/30 星期二
   */
 uint16_t RoadUpSide_Mono(uint8_t X1, uint8_t X2,uint8 down_max)
 {
     //找上下边线
     UpdownSideGet();

     uint8_t i = 0, num = 0;

     for(i = X1; i < X2-1; i++)
     {
        //向上
         if(imageOut[0][i] >= imageOut[0][i+1]&&imageOut[0][i]!=0&&imageOut[0][i]<down_max)
             num++;
         else
             num = 0;
         if (num >= (X2-X1)*4/5)
             return 1;
     }
     //向下
     for(i = X1; i < X2-1; i++)
     {
         if(imageOut[0][i] <= imageOut[0][i+1]&&imageOut[0][i]!=0&&imageOut[0][i]<down_max)
             num++;
         else
             num = 0;
         if (num >= (X2-X1)*4/5)
             return 2;
     }
     return 0;
 }
//是否为圆环
 uint16_t RoadIsRoundabout(void)
 {
     uint8_t i = 0;
     uint8_t errL=0;
     uint8_t errR=0;
     uint8_t leftState = 0;
     uint8_t rightState = 0;
     uint8_t count = 0;
     uint8_t num = 0, py;


     // 从车头往前 左边线是否单调
     for(i = START_H-2; i > END_H; i--)
     {
         if(l_border[i]== 1)
             continue;
         if(l_border[i] >= l_border[i+1])    // i是Y坐标值  0 是图像左线X坐标
         {
             if(l_border[i]<MT9V03X_DVP_W/2 - 5)
                    num++;
             else
                    num = 0;

             if(num == 50)
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


     errL = RoundaboutGetArc( 1, round_size, &py,120,0,120,0);//round_size圆弧的大小      圆弧的大小 用点数表示  （连续N个增  连续N个减）
     errR = RoundaboutGetArc( 2, round_size, &py,120,0,120,0);//1是左边线   2是右边线

     // 右边线是否单调
     for(i = START_H-2; i > END_H; i--)
     {
         if(r_border[i] == MT9V03X_DVP_W-1)
             continue;

         if(r_border[i]<= r_border[i+1])
         {
             if(r_border[i]>MT9V03X_DVP_W/2 + 5)
                            num++;
             else
                     num = 0  ;


             if(num == 50)
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

     // 左边单调， 检测右侧是否是环岛
     if(leftState == 1 && rightState == 0 && errL == 0)
     {
         count = 0;

         if(RoundaboutGetArc( 2, round_size, &count,120,0,120,0))
         {
             return 1;
         }
         else
         {
             return 0;
         }
     }
     /* 右边单调， 检测左侧是否是环岛 */
       if(rightState == 1 && leftState == 0&& errR == 0)
       {
           count = 0;
           if(RoundaboutGetArc( 1, round_size, &count,120,0,120,0))
           {

               return 2;
           }
       }
       return 0;
   }
 //化线
  void RoundaboutProcess( uint8_t state_1)
  {

      uint8_t i = 0, err5 = 0,err6 = 0;
      uint8_t pointX = 0, pointY = 0, inc = 0, dec = 0;
      uint8_t flag= 0, Down_flag = 0;
      static uint8_t finderr = 0;
      static uint8_t err1 = 0;
      static uint8_t err2 = 0;
      int state=state_1;
      int up_flag=0;
      while(1)
      {
      //奇数为入右圆环   偶数进入左圆环
          if(state==1)
          {
              if(mt9v03x_finish_flag_dvp)
              {
                  mt9v03x_finish_flag_dvp = 0;
                  binaryzation(0);//大津法二值化
                  find_mid_line(Pixle);//对半找赛道中线，返回值为平均值偏差值


                  // 检查弧线
                  err1 = RoundaboutGetArc(2, 3, &pointY,120,0,120,0);

                  // 有弧线 进行补线 连接弧线最右点 和 图像右下角
                  if(err1)
                  {
                      pointX = r_border[pointY];
                      ImageAddingLine(2, pointX, pointY, MT9V03X_DVP_W-1, 120);
                      finderr = 1;
                  }
                  else
                  {
                      if(finderr)
                          state = 3;//准备进入环岛
                  }

                  //获取偏差值
                  int devation=get_devation();
                  TraceMove(devation); //输出轮子转速
                  forward();
                  draw_line();
                  ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
                  //ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
                  if(devation<0){devation=-devation;}
                  ips114_show_uint(210,20,(uint32)devation,10);
                  if(state<0){state=-state;}
                  ips114_show_uint(210,40,state,10);

              }
          }
          /* 发现左环岛 环岛出口处补线 */


          if(state==3)
          {

              if(mt9v03x_finish_flag_dvp)
              {
                  mt9v03x_finish_flag_dvp = 0;
                  binaryzation(0);//大津法二值化
                  find_mid_line(Pixle);//对半找赛道中线，返回值为平均值偏差值


                  for(i=1;i<MT9V03X_DVP_H-1;i++)
                     {
                           l_border[i]=  l_border[i]+30;

                     }

                  if(RoadUpSide_Mono(0, MT9V03X_DVP_W-31,120) == 1)//上线单调增进入下一步
                        state = 5;
                  //获取偏差值
                  int devation=get_devation();
                  TraceMove(devation);
                  forward();
                  draw_line();
                  ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
       //            ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
                  if(devation<0){devation=-devation;}
                  ips114_show_uint(210,20,(uint32)devation,10);

                  ips114_show_uint(210,40,state,10);
              }


          }
          if(state==5)
          {
              if(mt9v03x_finish_flag_dvp)
              {
                  mt9v03x_finish_flag_dvp = 0;
                  binaryzation(0);//大津法二值化
                  find_mid_line(Pixle);//对半找赛道中线，返回值为平均值偏差值


                  err5 = RoundaboutGet_A( 1, 5,120,70);

                  flag = RoadUpSide_Mono(20, MT9V03X_DVP_W,60);
                  //检查下线
                  for(i = MT9V03X_DVP_W-1; i > 0; i--)
                  {
                      if(imageOut[1][i] == 119)
                            inc++;
                      else
                           dec++;
                      if( dec <= 15)
                      {
                          Down_flag = 1;
                          break;
                      }
                   }


//                  if(err5 && Down_flag&&flag!=0)

                  if(err5 && Down_flag)
                  {
                       state = 7;
                  }
                  //获取偏差值
                  int devation=get_devation();
                  TraceMove(devation);
                  draw_line();
                  forward();
                  ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
       //            ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
                  if(devation<0){devation=-devation;}
                  ips114_show_uint(210,20,(uint32)devation,10);
                  if(state<0){state=-state;}
                  ips114_show_uint(210,40,state,10);
              }

          }


                  if(state==7)
                  {

                      if(mt9v03x_finish_flag_dvp)
                   {
                       mt9v03x_finish_flag_dvp = 0;
                       binaryzation(0);//大津法二值化
                       find_mid_line(Pixle);//对半找赛道中线，返回值为平均值偏差值

                       ImageAddingLine( 1, 96, 0, 96, 120);
                       flag = RoadUpSide_Mono(50, MT9V03X_DVP_W,120);

                       if(flag==1)
                       {
                           up_flag=1;
                       }
                       if(flag==0&&up_flag)
                       {
                           state = 0;
                           finderr = 0;
                           err1 = 0;
                           circle_forward();
                           Delay_Ms(500);
                           break;
                       }
                       //获取偏差值
                       int devation=get_devation();
                       TraceMove(devation);
                       forward();
                       draw_line();
                       ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
     //                ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
                       if(devation<0){devation=-devation;}
                       ips114_show_uint(210,20,(uint32)devation,10);
                       if(state<0){state=-state;}
                       ips114_show_uint(210,40,state,10);
                   }

                  }


                  if(state==2)
                  {

                      if(mt9v03x_finish_flag_dvp)
                      {
                          mt9v03x_finish_flag_dvp = 0;
                          binaryzation(0);//大津法二值化
                          find_mid_line(Pixle);//对半找赛道中线，返回值为平均值偏差值

                          // 检查弧线
                          err2 = RoundaboutGetArc( 1, 3, &pointY,120,0,120,0);

                          // 有弧线 进行补线 连接弧线最左点 和 图像左下角
                          if(err2)
                          {
                              pointX = l_border[pointY];
                              ImageAddingLine(1, pointX, pointY, 0, 120);
                              finderr = 1;
                          }
                          else
                          {
                              if(finderr)//判断需要加
                              {state = 4;}//准备进入环岛
                          }

                          //获取偏差值
                          int devation=get_devation();

                               //输出轮子转速
                          TraceMove(devation);
                          forward();
                          draw_line();
                          ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
                          if(devation<0){devation=-devation;}
                          ips114_show_uint(210,20,(uint32)devation,10);

                      }
                  }


                       /* 发现右环岛 环岛出口处补线 */

                  //上边线单调
                  if(state==4)
                  {
                       if(mt9v03x_finish_flag_dvp)
                       {
                           mt9v03x_finish_flag_dvp = 0;
                           binaryzation(0);//大津法二值化
                           find_mid_line(Pixle);//对半找赛道中线，返回值为平均值偏差值

                           for(i=1;i<MT9V03X_DVP_H-1;i++)
                              {
                                    r_border[i]= r_border[i]-30;
                              }

                           if(RoadUpSide_Mono(30,MT9V03X_DVP_W-1,120) == 2)//上线单调增进入下一步
                                 {state = 6;}


                           //获取偏差值
                           int devation=get_devation();

                                //输出轮子转速
                           TraceMove(devation);
                           forward();
                           draw_line();
                           ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
                //            ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像

                           if(devation<0){devation=-devation;}
                           ips114_show_uint(210,20,(uint32)devation,10);

                       }
                  }
                  //
                  if(state==6)
                  {
                      if(mt9v03x_finish_flag_dvp)
                     {
                         mt9v03x_finish_flag_dvp = 0;
                         binaryzation(0);//大津法二值化
                         find_mid_line(Pixle);//对半找赛道中线，返回值为平均值偏差值

                         //出赛道识别的拐点     不用弧线判别 拐到能看见上边先的时候已经变成了A字突变点 使用拐点判别的方式
                         err6 = RoundaboutGet_A( 2, 5,120,50);
                         //上边线单调？
                         flag = RoadUpSide_Mono(0,MT9V03X_DVP_W-20,60);
                         //检查下线
                         for(i = MT9V03X_DVP_W-1; i > 0; i--)
                         {
                             if(imageOut[1][i] == 119)
                                   inc++;
                             else
                                  dec++;
                             if( dec <= 15)
                             {
                                 Down_flag = 1;
                                 break;
                             }
                          }
//                         if((flag==1||flag==2)&& err6&& Down_flag)
//                         if(err6 && Down_flag && flag!=0)
                         if(err6 && Down_flag)
                         {

                              state = 8;
                         }
                         //获取偏差值
                         int devation=get_devation();

                              //输出轮子转速
                         TraceMove(devation);
                         forward();
                         draw_line();
                         ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
              //            ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
                         if(devation<0){devation=-devation;}
                         ips114_show_uint(210,20,(uint32)devation,10);


                     }

                  }
//最后的出环补线 如果补线不够狠就会直行到边线之后获得一个极大的devation导致转过头回到圆环中
                  //如果补的太狠又会导致压倒中间环岛
                  //所以最好是增加转向的时间
                  //转向最好的方法是增加转向的时间
                 //所以增强出环的条件 增加一个 对应边线单调为单调为单调的判断

                  if(state==8)
                  {

                      if(mt9v03x_finish_flag_dvp)
                      {
                          mt9v03x_finish_flag_dvp = 0;
                          binaryzation(0);//大津法二值化
                          find_mid_line(Pixle);//对半找赛道中线，返回值为平均值偏差值

                          //判断元素
                          //补线
                          ImageAddingLine( 2,86,0,86, 120);
                          //上边线
                          flag = RoadUpSide_Mono(0,MT9V03X_DVP_W-50,120);

                          if(flag==2)
                          {
                              up_flag=1;
                          }
                          if(flag==0&&up_flag==1)
                          {
                              state = 0;
                              finderr = 0;
                              err2 = 0;
                              circle_forward();
                              Delay_Ms(500);
                              break;

                          }
                          //获取偏差值
                          int devation =get_devation();

                               //输出轮子转速
                          TraceMove(devation);
                          forward();
                          draw_line();
                          ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
               //            ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//显示二值化图像
                          if(devation<0){devation=-devation;}
                          ips114_show_uint(210,20,(uint32)devation,10);
                      }

                  }
               }
      }
