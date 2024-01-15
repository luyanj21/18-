/*
 * oust.c
 *
 *  Created on: 2023��6��26��
 *      Author: ɵ�ư�����
 */
#include "oust.h"
#include "main.h"
#include "headfile.h"


/************************************
* �������ƣ�otsu(uint16 column, uint16 row)
* ����˵��������ֵ��С
* ����˵����
* �������أ���ֵ��С
* �޸�ʱ�䣺2021/5/12 Wed
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
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; //��䷽��;
    uint16 MinValue, MaxValue;
    uint16 Threshold = 0;
    uint16 HistoGram[256];

    for (j = 0; j < 256; j++)  HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ

    for (j = 0; j < row; j++)
    {
        for (i = 0; i < column; i++)
        {
            HistoGram[mt9v03x_image_dvp[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++) ;        //��ȡ��С�Ҷȵ�ֵ
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--) ; //��ȡ���Ҷȵ�ֵ

    for (j = MinValue; j <= MaxValue; j++)    Amount += HistoGram[j];                   //��������

    PixelIntegral = 0;
    for (j = MinValue; j <= MaxValue; j++)
    {
        PixelIntegral += HistoGram[j] * j; //�Ҷ�ֵ����
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++)
    {
        PixelBack = PixelBack + HistoGram[j];                   //ǰ�����ص���
        PixelFore = Amount - PixelBack;                         //�������ص���
        OmegaBack = (float)PixelBack / Amount;                  //ǰ�����ذٷֱ�
        OmegaFore = (float)PixelFore / Amount;                  //�������ذٷֱ�
        PixelIntegralBack += HistoGram[j] * j;                  //ǰ���Ҷ�ֵ
        PixelIntegralFore = PixelIntegral - PixelIntegralBack;  //�����Ҷ�ֵ
        MicroBack = (float)PixelIntegralBack / PixelBack;       //ǰ���ҶȰٷֱ�
        MicroFore = (float)PixelIntegralFore / PixelFore;       //�����ҶȰٷֱ�
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore); //������䷽��
        if (Sigma > SigmaB) //�ҳ������䷽���Լ���Ӧ����ֵ
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //���������ֵ;
}
