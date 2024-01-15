/*
 * draw.c
 *
 *  Created on: 2023年6月28日
 *      Author: lenovo
 */
#include "headfile.h"

//九宫格画点判断
void points(uint8 x,uint8 y,uint16 color)
{
    if(x!=MT9V03X_DVP_W-1)
    {
        ips114_draw_point(x+1,y,color);
        if(y!=MT9V03X_DVP_H-1)
        {
            ips114_draw_point(x,y+1,color);
            ips114_draw_point(x+1,y+1,color);
        }
        if(y!=0)
        {
            ips114_draw_point(x,y-1,color);
            ips114_draw_point(x+1,y-1,color);
        }
    }
    if(x!=0)
    {
        ips114_draw_point(x-1,y,color);
        if(y!=MT9V03X_DVP_H-1)
        {
            ips114_draw_point(x,y+1,color);
            ips114_draw_point(x-1,y+1,color);
        }
        if(y!=0)
        {
            ips114_draw_point(x,y-1,color);
            ips114_draw_point(x-1,y-1,color);
        }

    }
    ips114_draw_point(x,y,color);
}
//绘制边线
void draw_line(void)
{
 for(uint8 i=MT9V03X_DVP_H-1;i>0;i--)
 {
       //全画
    points(l_border[i],i,RGB565_BLUE);
    points(r_border[i],i,RGB565_GREEN);
    points(mid_line_list[i],i,RGB565_RED);
 }
}

