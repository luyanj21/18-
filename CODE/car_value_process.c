/*********************************************************************************************************************
* @file            car_value_process.c
* @author          GX
* @Target core     CH32V307VCT6
* @revisions       20220908
* @modify          none
********************************************************************************************************************/

#include "car_value_process.h"



//-------------------------------------------------------------------------------------------------------------------
//@brief        32λ�޷�������ת��ΪASCII��
//@param        int_value:            32λ�޷�������
//@param        ascii_value:          ASCII������
//@return       void
//Sample usage:        int_to_ascii(adc_value, ascii_value_array);   //32λ�޷�������ת��ΪASCII��
//-------------------------------------------------------------------------------------------------------------------
void int_to_ascii(unsigned int dat, unsigned char *ascii_value)
{
    ascii_value[4] = dat % 10 + 0x30;
    ascii_value[3] = dat / 10 % 10 + 0x30;
    ascii_value[2] = dat / 100 % 10 + 0x30;
    ascii_value[1] = dat / 1000 % 10 + 0x30;
    ascii_value[0] = dat / 10000 % 10 + 0x30;
}
