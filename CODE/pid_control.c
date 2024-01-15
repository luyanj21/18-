/*
 * pid_control.c
 *
 *  Created on: 2023��6��27��
 *      Author: lenovo
 */


/*@brief:����ѭ��������pid����С��ת��ʹС�����ں����м�
 * @param:
 *        [in]int TraceDate: ѭ�������������ֵ
 *        [in]float TarSpdL:�ұߵ��Ŀ���ٶ�,����ٶ�Խ1.27m/s
 * @return: ���ص��ڵ���ٶȵ�ת��pwm
 */
#include "headfile.h"
int fixed_pwml=5000;
int fixed_pwmr=5000;

int pwml;
int pwmr;
int pwm;

int ChangeTraceTurn(int TraceDate)
{
//    int pwm=0;
    int bias;
    bias=TraceDate;
    pwm=PositionPID(bias,TurnPdate);
//    if(pwm>2500)        pwm=2500;//�޷�
//    else if(pwm<-2500)  pwm=-2500;
    return pwm;
}


/*@brief: ��С������ѭ��������
 *@param:����pwm��ȫ�ֱ��� ������Ϊ����ƫ��ֵ�ı�����pwm��ֵ
 *        [in]TraceDate: ѭ�������������ֵ
 *        [in]TarSpeed:ѭ����Ŀ���ٶ�
 *@return: ����Ŀ��㷵��1�����򷵻�0
 */
//void TraceMove(int TraceDate,float TarSpeed)
void TraceMove(int TraceDate)

{
    int turnpwm=0;
    turnpwm= ChangeTraceTurn (TraceDate);
    pwmr=fixed_pwmr-turnpwm;
    if(pwmr>10000)       pwmr=10000;//�޷�
    else if(pwmr<0)  pwmr=0;
    pwml=fixed_pwml+turnpwm;
    if(pwml>10000)       pwml=10000;//�޷�
    else if(pwml<0)  pwml=0;
}
