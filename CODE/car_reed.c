/*********************************************************************************************************************
* @file            car_reed.c
* @author          Fantastic Potato
* @Target core     CH32V307VCT6
* @revisions       -2022.09.18
* @modify          none
********************************************************************************************************************/

#include "car_reed.h"

//全局变量
unsigned char g_reed_flag;

//-------------------------------------------------------------------------------------------------------------------
// @brief        智能车干簧管初始化
// @param        void
// @return       void
// Sample usage:        reed_init();
//-------------------------------------------------------------------------------------------------------------------
void reed_init(void)
{
    gpio_init(D10, GPI, 1, IN_PULLUP);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief        智能车磁标检测
// @param        void
// @return       void
// Sample usage:        reed_check();//当干簧管检测到地面磁标时，标志位置1，否则为0。
//-------------------------------------------------------------------------------------------------------------------
void reed_check(void)
{
    if(RESET == gpio_get_input(D10))
    {
        g_reed_flag = 1;
    }
    else
    {
        g_reed_flag = 0;
    }
}

