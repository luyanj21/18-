/*
 * find..c
 *
 *  Created on: 2023��6��27��
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

//��������������  �ж�1/4 3/4
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
           //�������֮һ���ǰ׵㣬�Ӷ���֮һ����
         if(index[i][MT9V03X_DVP_W/2]==255)
         {
             //Ѱ����ߵ�
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
             //Ѱ���ұߵ�
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
         //��� �ķ�֮һ���ǰ׵㣬���ķ�֮һ����
         else if(index[i][MT9V03X_DVP_W/4]==255)
         {

             //Ѱ����ߵ�
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
             //Ѱ���ұߵ�
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
         //�ķ�֮�����ɫ
         else if(index[i][MT9V03X_DVP_W/4*3]==255)
         {
             flag_line[i]=1;
             //Ѱ����ߵ�
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
             //Ѱ���ұߵ�
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
             //���䷢������Բ��� ���ԸĻ�0��w�������ڱ����ж�

             //Ϊ��ֹ�յ㷢�� ����ûѰ���ĵط��ڴ����ĵط�Ӧ�õ�����һ��
//             left_point=l_border[i+1];//���µ���ɨ����һ�о���������һ�� ��һ
//             right_point=r_border[i+1];
              left_point=0;//���µ���ɨ����һ�о���������һ�� ��һ
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
//Ϊ�˾����ж��ǲ��ܵ���·Ӱ����Խ�startH�ʵ����߷�ֹ��·�����ܵ�Ӱ�� ��ͬʱ�ֲ�������ɨ�����Ӱ��
#define END_H 0//����С�������
/*
 *  �������뱣֤���϶˵�������ֱ��  �·������ؿ�����Ϊ����ͷ���͵��µ����������Ҳ�������ɷǵ���
 *  ��ö��϶˵������ؽ����ж�
 *  �����﷢��i�����uint���͵Ļᵼ��ֻ��whileѭ����Ĵ���ִ�� �г�ʼ��������û��ͼ��������ʾ
 *  ������int���͵ı���֮���ֿ���������ʾ
 *  ����i���Ե���0
 *
 *
 *��Ϊfind�����Ѱ�������ֵĵط�����ֵ��Ϊ��һ�е���ֵ �����ͻ�Ӱ�쵽�����Ƿ񵥵����ж����ϰ��жϵ�ʱ��ֱ�Ӳ��������ϵĳ���
 *����������ѱ��ʻ�ȥ�ĵط��ĳ��ڻ�ȡ������ɫ���ʱ��ͻ�ȡΪ��һ����������
 *
 *�����������ǿ�˻����ȥԲ�� �����˻�Ϲ��Բ��
 *���Խ������ٴμ�ǿ ��Ӷ��ߵ��ж� �ٴμ����β� lose_num
 *�������жϵ�ʱ��ʹ�ö���������Ѱ�ɵ�ʱ����� �ܱ��ֽ�����������ͬʱ����Ϲ��Բ��
 *
 */
void find_L(int mode)
{
    int i = 0;
    //���ұ����Ƿ񵥵�
    uint8_t leftState = 0;
    uint8_t rightState = 0;

//    uint8_t count = 0;
    uint8_t num = 0, py;


    //���ұ߻��жϱ�־λ
    int errL=0;
    int errR=0;
    //�����жϱ�־λ
    int garage_flag=0;
    int barrier_flag=0;


    // �ӳ�ͷ��ǰ ������Ƿ񵥵�
    for(i = START_H-2; i >=END_H; i--)
    {
        //����
        if(l_border[i]== 0)
            continue;
        //�������ÿһ�е�ֵ���ڵ�������һ�е�ʱ��
        if(l_border[i] >= l_border[i+1])    // i��Y����ֵ  0 ��ͼ������X����
        {
            //�������С����Ļ�м�������������ʱ��
            if(l_border[i]<MT9V03X_DVP_W/2)
                num++;
            else
                num = 0  ;
            //��num��50����
            if(num == 78)
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




    //�ж�Ԫ��
    //һ�ߵ���һ�߲���������Բ��
    if(rightState==1&&leftState==0)
    {
        //�ӻ����ж� ��Ȼ��ֱ�ӽ��뻷��
        //�����ж�
        errL = RoundaboutGetArc( 1, 3, &py,120,0,60,30);//round_sizeԲ���Ĵ�С      Բ���Ĵ�С �õ�����ʾ  ������N����  ����N������
        //��Բ��
        if(errL==1)
        {

            RoundaboutProcess(2);//��Բ��

        }

    }if(leftState==1&&rightState==0)
    {
        errR = RoundaboutGetArc( 2, 3, &py,120,0,60,30);//1�������   2���ұ���
        //��Բ��
        if(errR==1)
        {

            RoundaboutProcess(1);//��Բ��

        }

    }

    //���߾������� ��������� ���� �������ϰ�
    if(rightState==0&&leftState==0)
    {

        //�жϰ�����
        garage_flag=find_zebra();
        //�жϱ�־λ
        if(garage_flag)
        {
            garage_in(2);

        }



        ///////////////////////////////////////////////////////////
        //�ж��ϰ�
        barrier_flag=find_barrier();
        if(barrier_flag==1)
        {
            barrier_turn();
        }
        ////////////////////////////////////////////////////////////
    }
}
