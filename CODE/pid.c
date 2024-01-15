/*
 * pid.c
 *
 *  Created on: 2023��6��27��
 *      Author: lenovo
 */
#include "headfile.h"
//����pid�ṹ��
//struct PID
//{
//    float kp;
//    float ki;
//    float kd;
//};
//typedef struct PID _PID;

_PID PID;

//����ת��pid�����ṹ��
_PID TurnPdate=
{
    .kp=150,        //��ֵ����ֵ60   150
    .ki=0,          //��ֵ����ֵ
    .kd=50        //��ֵ΢��ֵ-45  34
};




/*@brief: λ��ʽPID������
 * @param:
 *        [in] float deviation: ��Ŀ��ֵ��ƫ��
 *        [in] _PID pid: λ��ʽpid�Ĳ���
 * @return: ����ռ�ձȵ�һ��������
 */
int PositionPID(float deviation,_PID pid)
{
    float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;
    static float Bias,Pwm,Integral_bias,Last_Bias;
    Bias=deviation;                                          //����ƫ��
    Integral_bias+=Bias;                                     //���ƫ��Ļ���
    Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias); //λ��ʽPID������
    Last_Bias=Bias;                                          //������һ��ƫ��
    return Pwm;
}

/*@brief: Ϊ�ٶ�pidʹ��λ��ʽPID���������Ի���ֵ�����޷�
 * @param:
 *        [in] float deviation: ��Ŀ��ֵ��ƫ��
 *        [in] _PID pid: λ��ʽpid�Ĳ���
 * @return: ����ռ�ձȵ�һ��������
 */
int PositionPIDToSpd(float deviation,_PID pid)
{
    float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;
    static float Bias,Pwm,Integral_bias,Last_Bias,pwmKI=0;
    Bias=deviation;                                          //����ƫ��
    Integral_bias+=Bias;                                     //���ƫ��Ļ���
    pwmKI=Position_KI*Integral_bias;
    if(pwmKI>PWM_DUTY_MAX) Integral_bias=PWM_DUTY_MAX/Position_KI;//�޷�PWM_DUTY_MAXΪ���pwm
    Pwm=Position_KP*Bias+pwmKI+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
    Last_Bias=Bias;                                          //������һ��ƫ��
    return Pwm;
}
