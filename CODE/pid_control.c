/*
 * pid_control.c
 *
 *  Created on: 2023年6月27日
 *      Author: lenovo
 */


/*@brief:根据循迹传感器pid调节小车转向使小车处于黑线中间
 * @param:
 *        [in]int TraceDate: 循迹传感器输出的值
 *        [in]float TarSpdL:右边电机目标速度,最大速度越1.27m/s
 * @return: 返回调节电机速度的转向pwm
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
//    if(pwm>2500)        pwm=2500;//限幅
//    else if(pwm<-2500)  pwm=-2500;
    return pwm;
}


/*@brief: 让小车根据循迹黑线走
 *@param:左右pwm是全局变量 本函数为根据偏差值改变左右pwm的值
 *        [in]TraceDate: 循迹传感器输出的值
 *        [in]TarSpeed:循迹的目标速度
 *@return: 到达目标点返回1，否则返回0
 */
//void TraceMove(int TraceDate,float TarSpeed)
void TraceMove(int TraceDate)

{
    int turnpwm=0;
    turnpwm= ChangeTraceTurn (TraceDate);
    pwmr=fixed_pwmr-turnpwm;
    if(pwmr>10000)       pwmr=10000;//限幅
    else if(pwmr<0)  pwmr=0;
    pwml=fixed_pwml+turnpwm;
    if(pwml>10000)       pwml=10000;//限幅
    else if(pwml<0)  pwml=0;
}
