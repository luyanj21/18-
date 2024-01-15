
#include "headfile.h"
#include "main.h"
#include "binarization.h"

/************************************
  * @brief    ��ֵ��
  * @param    mode  ��  0�������ֵ    1��ƽ����ֵ
  * @return
  * @note     Get_01_Value(0); //ʹ�ô�򷨶�ֵ��
  * @date     2021/5/12 WED
 ************************************/
#include "headfile.h"
uint8 Pixle[MT9V03X_DVP_H][MT9V03X_DVP_W];            //��Ŷ�ֵ����ͼ��
void binaryzation(uint8 mode)
{
  int i = 0,j = 0;
  uint32 Threshold=0;
  uint32  tv=0;
  if(mode==1)
  {
      //�ۼ�
      for(i = 0; i <MT9V03X_DVP_H; i++)
      {
          for(j = 0; j <MT9V03X_DVP_W; j++)
          {
              tv+=mt9v03x_image_dvp[i][j];         //�ۼ�
          }
      }
      Threshold=tv/MT9V03X_DVP_H/MT9V03X_DVP_W;        //��ƽ��ֵ,����Խ��ԽС��ȫ��Լ35��������ĻԼ160��һ������´�Լ100
//      Threshold=Threshold*7/10+10;             //�˴���ֵ���ã����ݻ����Ĺ������趨
  }
  if(mode==0)
  {
      Threshold = otsu(MT9V03X_DVP_W,MT9V03X_DVP_H);   //�����ֵ
      Threshold = (uint8_t)Threshold+10;
  }
  if(mode==2)
  {
    Threshold=GetOTSU(Pixle);//ģ�������ֵ
    Threshold = (uint8_t)Threshold +20;
  }

  for(i = 0; i < MT9V03X_DVP_H; i++)
  {
    for(j = 0; j < MT9V03X_DVP_W; j++)
    {
      if(mt9v03x_image_dvp[i][j] >Threshold)       //��ֵԽ����ʾ������Խ�࣬��ǳ��ͼ��Ҳ����ʾ����
        Pixle[i][j] =0xff;
      else
        Pixle[i][j] =0x00;
    }
  }
}

