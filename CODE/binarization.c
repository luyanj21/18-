
#include "headfile.h"
#include "main.h"
#include "binarization.h"

/************************************
  * @brief    二值化
  * @param    mode  ：  0：大津法阈值    1：平均阈值
  * @return
  * @note     Get_01_Value(0); //使用大津法二值化
  * @date     2021/5/12 WED
 ************************************/
#include "headfile.h"
uint8 Pixle[MT9V03X_DVP_H][MT9V03X_DVP_W];            //存放二值化后图像
void binaryzation(uint8 mode)
{
  int i = 0,j = 0;
  uint32 Threshold=0;
  uint32  tv=0;
  if(mode==1)
  {
      //累加
      for(i = 0; i <MT9V03X_DVP_H; i++)
      {
          for(j = 0; j <MT9V03X_DVP_W; j++)
          {
              tv+=mt9v03x_image_dvp[i][j];         //累加
          }
      }
      Threshold=tv/MT9V03X_DVP_H/MT9V03X_DVP_W;        //求平均值,光线越暗越小，全黑约35，对着屏幕约160，一般情况下大约100
//      Threshold=Threshold*7/10+10;             //此处阈值设置，根据环境的光线来设定
  }
  if(mode==0)
  {
      Threshold = otsu(MT9V03X_DVP_W,MT9V03X_DVP_H);   //大津法阈值
      Threshold = (uint8_t)Threshold+10;
  }
  if(mode==2)
  {
    Threshold=GetOTSU(Pixle);//模糊大津法阈值
    Threshold = (uint8_t)Threshold +20;
  }

  for(i = 0; i < MT9V03X_DVP_H; i++)
  {
    for(j = 0; j < MT9V03X_DVP_W; j++)
    {
      if(mt9v03x_image_dvp[i][j] >Threshold)       //数值越大，显示的内容越多，较浅的图像也能显示出来
        Pixle[i][j] =0xff;
      else
        Pixle[i][j] =0x00;
    }
  }
}

