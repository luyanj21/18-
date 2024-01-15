/*********************************************************************************************************************
* @file            car_light.c
* @author          Andreas HF
* @Target core     CH32V307VCT6
* @revisions       -2022.09.07, V1.0
* @modify          none
 ********************************************************************w************************************************/

#include "car_light.h"

/* rgb��ɫ���� */
static unsigned char rgb_off[3] = {0x00,0x00,0x00};
static unsigned char rgb_blue[3] = {0x00,0x00,0xFF};
static unsigned char rgb_green[3] = {0x00,0xFF,0x00};
static unsigned char rgb_cyan[3] = {0x00,0xFF,0xFF};
static unsigned char rgb_red[3] = {0xFF,0x00,0x00};
static unsigned char rgb_purple[3] = {0xFF,0x00,0xFF};
static unsigned char rgb_yellow[3] = {0xFF,0xFF,0x00};
static unsigned char rgb_white[3] = {0xFF,0xFF,0xFF};

//-------------------------------------------------------------------------------------------------------------------
// @brief        ���ܳ�β��ͬʱ����
// @param        color          β����ɫ
// @param        time           ��ʱʱ��(ms)
// @return       void
// Sample usage:        car_both_rgb_on(red);//β��ͬʱ��ʾ��ɫ����ʱ1s
//-------------------------------------------------------------------------------------------------------------------
void car_both_rgb_on(rgb_color color)
{
    if(color == red)
    {
        ws2812b_write(rgb_red);
        ws2812b_write(rgb_red);
    }
    else if(color == yellow)
    {
        ws2812b_write(rgb_yellow);
        ws2812b_write(rgb_yellow);
    }
    else if(color == white)
    {
        ws2812b_write(rgb_white);
        ws2812b_write(rgb_white);
    }
    else if(color == blue)
    {
        ws2812b_write(rgb_blue);
        ws2812b_write(rgb_blue);
    }
    else if(color == green)
    {
        ws2812b_write(rgb_green);
        ws2812b_write(rgb_green);
    }
    else if(color == cyan)
    {
        ws2812b_write(rgb_cyan);
        ws2812b_write(rgb_cyan);
    }
    else if(color == purple)
    {
        ws2812b_write(rgb_purple);
        ws2812b_write(rgb_purple);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief        ���ܳ�β��Ϩ��
// @param        void
// @return       void
// Sample usage:        car_both_rgb_off();//β��Ϩ��
//-------------------------------------------------------------------------------------------------------------------
void car_both_rgb_off()
{
    ws2812b_write(rgb_off);
    ws2812b_write(rgb_off);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief        ���ܳ�β�������˸
// @param        color          β����ɫ
// @param        flash_count    ��˸����
// @param        time           ���ʱ��(ms)
// @return       void
// Sample usage:        car_left_rgb_flash(red, 3, 500);//�����˸��ɫ���Σ����0.5s
//-------------------------------------------------------------------------------------------------------------------
void car_left_rgb_flash(rgb_color color, uint16_t flash_count, uint16_t time)
{
    unsigned int i;

    if(color == red)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_red);
            ws2812b_write(rgb_off);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == yellow)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_yellow);
            ws2812b_write(rgb_off);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == white)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_white);
            ws2812b_write(rgb_off);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == green)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_green);
            ws2812b_write(rgb_off);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == blue)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_blue);
            ws2812b_write(rgb_off);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == cyan)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_cyan);
            ws2812b_write(rgb_off);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == purple)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_purple);
            ws2812b_write(rgb_off);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }

}

//-------------------------------------------------------------------------------------------------------------------
// @brief        ���ܳ�β���ҵ���˸
// @param        color          β����ɫ
// @param        flash_count    ��˸����
// @param        time           ���ʱ��(ms)
// @return       void
// Sample usage:        car_right_rgb_flash(red, 3, 500);//�ҵ���˸��ɫ���Σ����0.5s
//-------------------------------------------------------------------------------------------------------------------
void car_right_rgb_flash(rgb_color color, uint16_t flash_count, uint16_t time)
{
    unsigned int i;

    if(color == red)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_off);
            ws2812b_write(rgb_red);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == yellow)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_off);
            ws2812b_write(rgb_yellow);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == white)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_off);
            ws2812b_write(rgb_white);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == green)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_off);
            ws2812b_write(rgb_green);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == blue)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_off);
            ws2812b_write(rgb_blue);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == cyan)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_off);
            ws2812b_write(rgb_cyan);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == purple)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_off);
            ws2812b_write(rgb_purple);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief        ���ܳ�β��ͬʱ��˸
// @param        color          β����ɫ
// @param        flash_count    ��˸����
// @param        time           ���ʱ��(ms)
// @return       void
// Sample usage:        car_both_rgb_flash(red, 3, 500);//β��ͬʱ��˸��ɫ���Σ����0.5s
//-------------------------------------------------------------------------------------------------------------------
void car_both_rgb_flash(rgb_color color, uint16_t flash_count, uint16_t time)
{
    unsigned int i;

    if(color == red)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_red);
            ws2812b_write(rgb_red);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == yellow)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_yellow);
            ws2812b_write(rgb_yellow);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == white)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_white);
            ws2812b_write(rgb_white);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == green)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_green);
            ws2812b_write(rgb_green);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == blue)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_blue);
            ws2812b_write(rgb_blue);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == cyan)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_cyan);
            ws2812b_write(rgb_cyan);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else if(color == purple)
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_purple);
            ws2812b_write(rgb_purple);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
    else
    {
        for(i=0; i<flash_count; i++)
        {
            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);

            Delay_Ms(time);

            ws2812b_write(rgb_off);
            ws2812b_write(rgb_off);
            Delay_Ms(time);
        }
    }
}
