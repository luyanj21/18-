/*
 * garage.c
 *
 *  Created on: 2023��7��16��
 *      Author: lenovo
 */
#include "headfile.h"
/*
  * �����߼��
 *
 * */
//�������� �ڰ�������ܺ�
int garage_count;
//�ڰ׵��־λ
int white_black;
//�̶���¼��־λ
int black_white;
//�����������
//��������������Լ��ʮ����
int region;
//�����־λ
int garageout_flag;

int find_zebra (void)
{
    //�����־λ����
    garageout_flag=0;
    //�а�������������
    region=0;
    //��
    //���ϵ��±���  ����Ļ
    for(uint8 i = 45;i<50;i++)
        {
        //�̶��������0
        black_white=0;
        //�����������
            garage_count= 0 ;
            //��������ұ���  ������
            for(uint8 j= 10;j<180;j++)
             {
                //��������ɫ���ʱ���Ϊ1   white-��255
                   if(Pixle[i][j]==255)
                   {
                       white_black=1;
                   }
                   //������ɫ���ʱ���Ϊ0
                   else
                   {
                     white_black=0;
                   }
                   //���ڰױ�־λ��һ��ʱ
                   if(white_black!=black_white)
                   {
                     //�ױ�־λ���ڰ׵��ڱ�־λ
                     black_white = white_black;
                     //������������һ
                     garage_count++;
                   }
                   //���������������ʮһ
                   if(garage_count>14)
                 {
                       //�ܱ�־λ��һ
                   region++;
                 }
               }
          //���ܱ�־λ����2ʱ
         if(region>2)
               {
             //�����־λΪ��
                   garageout_flag=1;
                   //����ѭ��
                   break;
               }
           }
    //������ֵ
    return garageout_flag;
}

/*
 * in_flag=2������ in_flag=1�ҹ����
 * */
void garage_out(int out_flag)
{
    if(out_flag==1)
    {

        //���ҹճ���
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
        //����ճ���

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
/*������ ����Ϲյ������
 * �������Ϲյ�����  ���ǽ���֮��ʼѰ���Ϲյ�
 *
 *Ϊ���ҵ��Ϲյ㿼�Ǹ���ɨ�߷�ʽ 1.������ 2.�Ҵӳ��⿪ʼ���м��� �ҵ���һ������㼴Ϊ����
 *
 * �ж����ҳ��⣿  ���������м�ɨ�߱Ƚ��������������ά����ľ�������ж�
 *
 *ת���־λ=1�ҹ���� =2������
 * */

void garage_in(int in_flag)
{
    if(in_flag==1)
    {
//        ���ҹ����
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

        //�����
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


//����ͣ��
    while(1)
    {car_stop();}

}
