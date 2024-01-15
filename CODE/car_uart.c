/*********************************************************************************************************************
* @file            car_uart.c
* @author          GX
* @Target core     CH32V307VCT6
* @revisions       20220908
* @modify          none
********************************************************************************************************************/

#include "car_uart.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief        Debug���ڳ�ʼ��
// @return       void
// Sample usage:        Debug_uart_init();//����1��ʼ��
//-------------------------------------------------------------------------------------------------------------------
void Debug_uart_init()
{
    uart_init(UART_3, 115200, UART3_TX_B10, UART3_RX_B11);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief        ���ߴ��ڳ�ʼ��
// @return       void
// Sample usage:        wireless_uart2_init();//���ߴ��ڳ�ʼ��
//-------------------------------------------------------------------------------------------------------------------
void wireless_uart2_init(unsigned int uart_periph)
{
    wireless_uart_init();
}

//-------------------------------------------------------------------------------------------------------------------
// @brief        ���ڽ�����
// @param        uart_periph            ����ģ��ţ�USARTx(x = 1,2)�����У�UART2Ϊ���ߴ��ڣ�
// @return       rec_dat
// Sample usage:        rx_char = uart_receive(UART1);//����1������
//-------------------------------------------------------------------------------------------------------------------
unsigned char uart_receive(unsigned int uart_periph)
{
    unsigned char rec_dat;

    rec_dat = uart_getchar(uart_periph);

    return rec_dat;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief        ���ڷ����ַ�
// @param        uart_periph              ����ģ��ţ�USARTx(x = 1,2)�����У�UART2Ϊ���ߴ��ڣ�
// @param        dat                      ��Ҫ���͵��ֽ�
// @return       void
// Sample usage:        uart_send_char(UART_1,0xA5);// ����UART1����0xA5
//-------------------------------------------------------------------------------------------------------------------
void uart_send_char(unsigned int uart_periph, unsigned char dat)
{
    uart_putchar(uart_periph, dat);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief        ���ڷ���ascii��
// @param        uart_periph              ����ģ��ţ�USARTx(x = 1,2)�����У�UART2Ϊ���ߴ��ڣ�
// @param        ascii_value              ASCII������
// @return       void
// Sample usage:        uart_send_ascii(UART_1,ascii_value);
//-------------------------------------------------------------------------------------------------------------------
void uart_send_ascii(unsigned int uart_periph, unsigned char *ascii_value)
{
    unsigned char i;

    for(i=0; i<5; i++)
    {
        uart_send_char(uart_periph, ascii_value[i]);
    }                                    //�Ӹ�λ����λ����ascii��

    uart_send_char(uart_periph, 0x20);        //����
}
