/*********************************************************************************************************************
* @file            car_uart.c
* @author          GX
* @Target core     CH32V307VCT6
* @revisions       20220908
* @modify          none
********************************************************************************************************************/

#include "car_uart.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief        Debug串口初始化
// @return       void
// Sample usage:        Debug_uart_init();//串口1初始化
//-------------------------------------------------------------------------------------------------------------------
void Debug_uart_init()
{
    uart_init(UART_3, 115200, UART3_TX_B10, UART3_RX_B11);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief        无线串口初始化
// @return       void
// Sample usage:        wireless_uart2_init();//无线串口初始化
//-------------------------------------------------------------------------------------------------------------------
void wireless_uart2_init(unsigned int uart_periph)
{
    wireless_uart_init();
}

//-------------------------------------------------------------------------------------------------------------------
// @brief        串口接收数
// @param        uart_periph            串口模块号：USARTx(x = 1,2)（其中，UART2为无线串口）
// @return       rec_dat
// Sample usage:        rx_char = uart_receive(UART1);//串口1接收数
//-------------------------------------------------------------------------------------------------------------------
unsigned char uart_receive(unsigned int uart_periph)
{
    unsigned char rec_dat;

    rec_dat = uart_getchar(uart_periph);

    return rec_dat;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief        串口发送字符
// @param        uart_periph              串口模块号：USARTx(x = 1,2)（其中，UART2为无线串口）
// @param        dat                      需要发送的字节
// @return       void
// Sample usage:        uart_send_char(UART_1,0xA5);// 串口UART1发送0xA5
//-------------------------------------------------------------------------------------------------------------------
void uart_send_char(unsigned int uart_periph, unsigned char dat)
{
    uart_putchar(uart_periph, dat);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief        串口发送ascii码
// @param        uart_periph              串口模块号：USARTx(x = 1,2)（其中，UART2为无线串口）
// @param        ascii_value              ASCII码数组
// @return       void
// Sample usage:        uart_send_ascii(UART_1,ascii_value);
//-------------------------------------------------------------------------------------------------------------------
void uart_send_ascii(unsigned int uart_periph, unsigned char *ascii_value)
{
    unsigned char i;

    for(i=0; i<5; i++)
    {
        uart_send_char(uart_periph, ascii_value[i]);
    }                                    //从高位到低位发送ascii码

    uart_send_char(uart_periph, 0x20);        //换行
}
