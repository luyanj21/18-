/*
 * oust.c
 *
 *  Created on: 2023年6月26日
 *      Author: 傻逼安工大
 */
#include "oust.h"
#include "main.h"
#include "headfile.h"


/************************************
* 函数名称：otsu(uint16 column, uint16 row)
* 功能说明：求阈值大小
* 参数说明：
* 函数返回：阈值大小
* 修改时间：2021/5/12 Wed
************************************/
uint16 otsu(uint16 column, uint16 row)
{
    uint16 i,j;
    uint32 Amount = 0;
    uint32 PixelBack = 0;
    uint32 PixelIntegralBack = 0;
    uint32 PixelIntegral = 0;
    int32 PixelIntegralFore = 0;
    int32 PixelFore = 0;
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; //类间方差;
    uint16 MinValue, MaxValue;
    uint16 Threshold = 0;
    uint16 HistoGram[256];

    for (j = 0; j < 256; j++)  HistoGram[j] = 0; //初始化灰度直方图

    for (j = 0; j < row; j++)
    {
        for (i = 0; i < column; i++)
        {
            HistoGram[mt9v03x_image_dvp[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++) ;        //获取最小灰度的值
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--) ; //获取最大灰度的值

    for (j = MinValue; j <= MaxValue; j++)    Amount += HistoGram[j];                   //像素总数

    PixelIntegral = 0;
    for (j = MinValue; j <= MaxValue; j++)
    {
        PixelIntegral += HistoGram[j] * j; //灰度值总数
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++)
    {
        PixelBack = PixelBack + HistoGram[j];                   //前景像素点数
        PixelFore = Amount - PixelBack;                         //背景像素点数
        OmegaBack = (float)PixelBack / Amount;                  //前景像素百分比
        OmegaFore = (float)PixelFore / Amount;                  //背景像素百分比
        PixelIntegralBack += HistoGram[j] * j;                  //前景灰度值
        PixelIntegralFore = PixelIntegral - PixelIntegralBack;  //背景灰度值
        MicroBack = (float)PixelIntegralBack / PixelBack;       //前景灰度百分比
        MicroFore = (float)PixelIntegralFore / PixelFore;       //背景灰度百分比
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore); //计算类间方差
        if (Sigma > SigmaB) //找出最大类间方差以及对应的阈值
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //返回最佳阈值;
}
