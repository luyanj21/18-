/*
 * huandao.c
 *
 *  Created on: 2023��7��6��
 *      Author: cyl
 */

#include <circle.h>

#define START_H     120//���µ��� start��С
#define END_H       0
#define round_size  5

uint32_t imageOut[2][MT9V03X_DVP_W];//0�� 1��


uint8_t UpdownSideGet(void)
{

    uint8_t i = 0, j = 0;
    uint8_t last = MT9V03X_DVP_H/2+20;

     //��ͼ���м���    ���е���     ���е���      ɨ��
    imageOut[0][MT9V03X_DVP_W/2] =0;
    imageOut[1][MT9V03X_DVP_W/2] =MT9V03X_DVP_H-1;

    //�����м䵥����һ�е����±���
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

    //�����е����±���
    //���е���
    for(i = MT9V03X_DVP_W/2-1; i > 0; i--)//����ÿһ��
    {
        imageOut[0][i] = 0;
        imageOut[1][i] = MT9V03X_DVP_H-1;

        for(j = imageOut[0][i+1] + 5; j > 0; j--)//һ���е�ɨ��ÿ��  �����е�����+10��ʼ����ɨ��
        {
            //��ֹ����
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

            //��ֹ����
            if(imageOut[1][i+1] - 5<0)
            {break;}

            if(!Pixle[j][i])
            {
                imageOut[1][i] = j;
                break;
            }
        }
    }

    //���е���
    for(i = MT9V03X_DVP_W/2+1; i < MT9V03X_DVP_W-1; i++)
        {
            imageOut[0][i] = 0;
            imageOut[1][i] = MT9V03X_DVP_H-1;

            for(j = imageOut[0][i-1] + 5; j > 0; j--)
            {
                //������
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

                //������
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
 * �жϳ�����a���νǵ��õĻ����ж�
 * ��Ϊ�����˶����ж�֮����޷��жϳ�����a���νǵ� ����ж�ȥ����������
 * status:1��2��    num��A��Ĳ�ֵ    start�� endС
 * */
uint16_t RoundaboutGet_A( uint8_t status, uint8_t num,uint8 start,uint8 end )
{

    int i = 0;
    switch(status)
    {
    //�����
      case 1:
          //���µ��ϱ���
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


                /* �л��� */
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
  * @brief    �ж����ұ����Ƿ���ڻ���
      * ����� index Բ���Ķ���λ��
  * @param    imageInput �� ��ֵͼ����Ϣ
  * @param    imageOut   �� ��������
  * @param    status     �� 1�������  2���ұ���
  * @param    num        �� Բ���Ĵ�С �õ�����ʾ  ������N����  ����N������
  * @return   1 �л���    0  û����

  *
//uint8_t imageSide[MT9V03X_DVP_H][2];
*�Ὣ������ʱ�����ʶ���Բ��
 * ԭ�ȵķ����ᵼ�½���ȥ��
 * �����ڵ��õ�ʱ���һ����־λ��һ����־λ��ȥ ������������߾�  ���е� ������������
 *
 * ����������������ѹ ��Բ�����������������µ�  ��Ҫ�ù���������ʶ��ɲ�����
 * ��ʱ
 *
 * ��Ϊ�ᶪ�����Խ�������Ϊ��Բ�����ж�����
 *
 * ������Ϊ�ж����������Ǻܺ� ��Ϊ���˽�Բ���ĵڶ��׶ξͻ����
 *
 * ���ڽ��±߻��ĸ�����Ϊ�ж�����
 * ���ж��ϱ߻���ʱ���ж��±߻��ĸ���
 * ����һ������Բ�������±߻����β�
 *
 *
 * ����һ���������ߵı���lose �Ƚ϶��ߵ�lose_num
 * */
uint16_t RoundaboutGetArc( uint8_t status, uint8_t num,uint8_t* index,uint8 start,uint8 end,uint8 down_num,uint8 lose_num)
{
    int left_flag=0;
    int right_flag=0;
    int i = 0;
    uint8_t inc = 0, dec = 0, n = 0;
    //��¼����
    int lose=0;
    switch(status)
    {
    //�����
      case 1:
          //���µ��ϱ���
        for(i =start-2; i >end; i--)
        {
            //�ж��Ƿ��ж���
            //������ߴ����ұߵ�
            //������߾ͻ�contine����һ��forѭ����Ӧ���еİ�
            //��Ϊ��hi�������Ϸ��ж����л���
            //����� ���� �ü�flag�ж�
            //Ӧ���ǿ��Ե� ��Ϊ�ڽ�Դ���׶��в������ ����� a���� ���� a���ζ�����ȥ��
            //����ʹ��continue��������
            //ʹ��continue�ᵼ�»��߶����������
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
            //��������û��ͬʱ�Ǳ߿�
//            if(l_border[i]!= 1 && l_border[i+1]!= 1)
            if(l_border[i]!= 1 && l_border[i+1]!= 1&&left_flag==1)
            {
                //����������
                if(l_border[i] == l_border[i+1])
                {
                    n++;
                    continue;
                }
                //����±���С���ϱ���
                //�±߻�
                if(l_border[i] > l_border[i+1])
                {
                    //inc���±߻�������
                    inc++;
                    inc+=n;
                    n=0;
                }
                //����±���С���ϱ���
                //�ϱ߻�
                else
                {
                    dec++;
                    dec+=n;
                    n=0;
                }

                /* �л��� */
                //���»��߶��������±��ߵ�ֵ
                //�����±߻����ô����β� down_num
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

                /* �л��� */
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
   * @brief    ���ߴ���
   *
   * @param    imageSide  : ����
   * @param    status     : 1������߲���   2���ұ��߲���
   * @param    startX     : ��ʼ�� ����
   * @param    startY     : ��ʼ�� ����
   * @param    endX       : ������ ����
   * @param    endY       : ������ ����
   *
   * @return
   *
   * @note     endY һ��Ҫ���� startY
   *
   */
 void ImageAddingLine( uint8_t status, uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY)
 {
     int i = 0;

     // ֱ�� x = ky + b
     float k = 0.0f, b = 0.0f;
//     switch(status)
//     {
//       case 1://����
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
//       case 2://�Ҳ���
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
           if(status==1)//����
             {
                 k = (float)((float)endX - (float)startX) / (float)((float)endY - (float)startY);
                 b = (float)startX - (float)startY * k;

                 for(i = startY; i < endY; i++)
                 {
                     l_border[i] = (uint8_t)(k * i + b);
                 }
                 break;
             }

           if(status==2)//�Ҳ���
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
   * @brief    �ж��ϱ����Ƿ񵥵�
   * @param    X1 :��ʼX��
   * @param    X2 :��ֹX��              X1 < X2
   * @param    imageIn �� ��������
   *
   * @return   0��������or���� 1������������ 2�������ݼ�
   *
   * @note downΪ�����±������µ��õ�
   *
   * @see
   *
   * @date     2021/11/30 ���ڶ�
   */
 uint16_t RoadUpSide_Mono(uint8_t X1, uint8_t X2,uint8 down_max)
 {
     //�����±���
     UpdownSideGet();

     uint8_t i = 0, num = 0;

     for(i = X1; i < X2-1; i++)
     {
        //����
         if(imageOut[0][i] >= imageOut[0][i+1]&&imageOut[0][i]!=0&&imageOut[0][i]<down_max)
             num++;
         else
             num = 0;
         if (num >= (X2-X1)*4/5)
             return 1;
     }
     //����
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
//�Ƿ�ΪԲ��
 uint16_t RoadIsRoundabout(void)
 {
     uint8_t i = 0;
     uint8_t errL=0;
     uint8_t errR=0;
     uint8_t leftState = 0;
     uint8_t rightState = 0;
     uint8_t count = 0;
     uint8_t num = 0, py;


     // �ӳ�ͷ��ǰ ������Ƿ񵥵�
     for(i = START_H-2; i > END_H; i--)
     {
         if(l_border[i]== 1)
             continue;
         if(l_border[i] >= l_border[i+1])    // i��Y����ֵ  0 ��ͼ������X����
         {
             if(l_border[i]<MT9V03X_DVP_W/2 - 5)
                    num++;
             else
                    num = 0;

             if(num == 50)
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


     errL = RoundaboutGetArc( 1, round_size, &py,120,0,120,0);//round_sizeԲ���Ĵ�С      Բ���Ĵ�С �õ�����ʾ  ������N����  ����N������
     errR = RoundaboutGetArc( 2, round_size, &py,120,0,120,0);//1�������   2���ұ���

     // �ұ����Ƿ񵥵�
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

     // ��ߵ����� ����Ҳ��Ƿ��ǻ���
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
     /* �ұߵ����� �������Ƿ��ǻ��� */
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
 //����
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
      //����Ϊ����Բ��   ż��������Բ��
          if(state==1)
          {
              if(mt9v03x_finish_flag_dvp)
              {
                  mt9v03x_finish_flag_dvp = 0;
                  binaryzation(0);//��򷨶�ֵ��
                  find_mid_line(Pixle);//�԰����������ߣ�����ֵΪƽ��ֵƫ��ֵ


                  // ��黡��
                  err1 = RoundaboutGetArc(2, 3, &pointY,120,0,120,0);

                  // �л��� ���в��� ���ӻ������ҵ� �� ͼ�����½�
                  if(err1)
                  {
                      pointX = r_border[pointY];
                      ImageAddingLine(2, pointX, pointY, MT9V03X_DVP_W-1, 120);
                      finderr = 1;
                  }
                  else
                  {
                      if(finderr)
                          state = 3;//׼�����뻷��
                  }

                  //��ȡƫ��ֵ
                  int devation=get_devation();
                  TraceMove(devation); //�������ת��
                  forward();
                  draw_line();
                  ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
                  //ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
                  if(devation<0){devation=-devation;}
                  ips114_show_uint(210,20,(uint32)devation,10);
                  if(state<0){state=-state;}
                  ips114_show_uint(210,40,state,10);

              }
          }
          /* �����󻷵� �������ڴ����� */


          if(state==3)
          {

              if(mt9v03x_finish_flag_dvp)
              {
                  mt9v03x_finish_flag_dvp = 0;
                  binaryzation(0);//��򷨶�ֵ��
                  find_mid_line(Pixle);//�԰����������ߣ�����ֵΪƽ��ֵƫ��ֵ


                  for(i=1;i<MT9V03X_DVP_H-1;i++)
                     {
                           l_border[i]=  l_border[i]+30;

                     }

                  if(RoadUpSide_Mono(0, MT9V03X_DVP_W-31,120) == 1)//���ߵ�����������һ��
                        state = 5;
                  //��ȡƫ��ֵ
                  int devation=get_devation();
                  TraceMove(devation);
                  forward();
                  draw_line();
                  ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
       //            ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
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
                  binaryzation(0);//��򷨶�ֵ��
                  find_mid_line(Pixle);//�԰����������ߣ�����ֵΪƽ��ֵƫ��ֵ


                  err5 = RoundaboutGet_A( 1, 5,120,70);

                  flag = RoadUpSide_Mono(20, MT9V03X_DVP_W,60);
                  //�������
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
                  //��ȡƫ��ֵ
                  int devation=get_devation();
                  TraceMove(devation);
                  draw_line();
                  forward();
                  ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
       //            ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
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
                       binaryzation(0);//��򷨶�ֵ��
                       find_mid_line(Pixle);//�԰����������ߣ�����ֵΪƽ��ֵƫ��ֵ

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
                       //��ȡƫ��ֵ
                       int devation=get_devation();
                       TraceMove(devation);
                       forward();
                       draw_line();
                       ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
     //                ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
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
                          binaryzation(0);//��򷨶�ֵ��
                          find_mid_line(Pixle);//�԰����������ߣ�����ֵΪƽ��ֵƫ��ֵ

                          // ��黡��
                          err2 = RoundaboutGetArc( 1, 3, &pointY,120,0,120,0);

                          // �л��� ���в��� ���ӻ�������� �� ͼ�����½�
                          if(err2)
                          {
                              pointX = l_border[pointY];
                              ImageAddingLine(1, pointX, pointY, 0, 120);
                              finderr = 1;
                          }
                          else
                          {
                              if(finderr)//�ж���Ҫ��
                              {state = 4;}//׼�����뻷��
                          }

                          //��ȡƫ��ֵ
                          int devation=get_devation();

                               //�������ת��
                          TraceMove(devation);
                          forward();
                          draw_line();
                          ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
                          if(devation<0){devation=-devation;}
                          ips114_show_uint(210,20,(uint32)devation,10);

                      }
                  }


                       /* �����һ��� �������ڴ����� */

                  //�ϱ��ߵ���
                  if(state==4)
                  {
                       if(mt9v03x_finish_flag_dvp)
                       {
                           mt9v03x_finish_flag_dvp = 0;
                           binaryzation(0);//��򷨶�ֵ��
                           find_mid_line(Pixle);//�԰����������ߣ�����ֵΪƽ��ֵƫ��ֵ

                           for(i=1;i<MT9V03X_DVP_H-1;i++)
                              {
                                    r_border[i]= r_border[i]-30;
                              }

                           if(RoadUpSide_Mono(30,MT9V03X_DVP_W-1,120) == 2)//���ߵ�����������һ��
                                 {state = 6;}


                           //��ȡƫ��ֵ
                           int devation=get_devation();

                                //�������ת��
                           TraceMove(devation);
                           forward();
                           draw_line();
                           ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
                //            ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��

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
                         binaryzation(0);//��򷨶�ֵ��
                         find_mid_line(Pixle);//�԰����������ߣ�����ֵΪƽ��ֵƫ��ֵ

                         //������ʶ��Ĺյ�     ���û����б� �յ��ܿ����ϱ��ȵ�ʱ���Ѿ������A��ͻ��� ʹ�ùյ��б�ķ�ʽ
                         err6 = RoundaboutGet_A( 2, 5,120,50);
                         //�ϱ��ߵ�����
                         flag = RoadUpSide_Mono(0,MT9V03X_DVP_W-20,60);
                         //�������
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
                         //��ȡƫ��ֵ
                         int devation=get_devation();

                              //�������ת��
                         TraceMove(devation);
                         forward();
                         draw_line();
                         ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
              //            ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
                         if(devation<0){devation=-devation;}
                         ips114_show_uint(210,20,(uint32)devation,10);


                     }

                  }
//���ĳ������� ������߲����ݾͻ�ֱ�е�����֮����һ�������devation����ת��ͷ�ص�Բ����
                  //�������̫���ֻᵼ��ѹ���м价��
                  //�������������ת���ʱ��
                  //ת����õķ���������ת���ʱ��
                 //������ǿ���������� ����һ�� ��Ӧ���ߵ���Ϊ����Ϊ�������ж�

                  if(state==8)
                  {

                      if(mt9v03x_finish_flag_dvp)
                      {
                          mt9v03x_finish_flag_dvp = 0;
                          binaryzation(0);//��򷨶�ֵ��
                          find_mid_line(Pixle);//�԰����������ߣ�����ֵΪƽ��ֵƫ��ֵ

                          //�ж�Ԫ��
                          //����
                          ImageAddingLine( 2,86,0,86, 120);
                          //�ϱ���
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
                          //��ȡƫ��ֵ
                          int devation =get_devation();

                               //�������ת��
                          TraceMove(devation);
                          forward();
                          draw_line();
                          ips114_displayimage032(Pixle[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
               //            ips114_displayimage032(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);//��ʾ��ֵ��ͼ��
                          if(devation<0){devation=-devation;}
                          ips114_show_uint(210,20,(uint32)devation,10);
                      }

                  }
               }
      }
