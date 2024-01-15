/*
 * pid.c
 *
 *  Created on: 2023年6月27日
 *      Author: lenovo
 */
#include "headfile.h"
//定义pid结构体
//struct PID
//{
//    float kp;
//    float ki;
//    float kd;
//};
//typedef struct PID _PID;

_PID PID;

//定义转向pid参数结构体
_PID TurnPdate=
{
    .kp=150,        //赋值比例值60   150
    .ki=0,          //赋值积分值
    .kd=50        //赋值微分值-45  34
};




/*@brief: 位置式PID控制器
 * @param:
 *        [in] float deviation: 和目标值得偏差
 *        [in] _PID pid: 位置式pid的参数
 * @return: 调节占空比的一个整形数
 */
int PositionPID(float deviation,_PID pid)
{
    float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;
    static float Bias,Pwm,Integral_bias,Last_Bias;
    Bias=deviation;                                          //计算偏差
    Integral_bias+=Bias;                                     //求出偏差的积分
    Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias); //位置式PID控制器
    Last_Bias=Bias;                                          //保存上一次偏差
    return Pwm;
}

/*@brief: 为速度pid使用位置式PID控制器，对积分值进行限幅
 * @param:
 *        [in] float deviation: 和目标值得偏差
 *        [in] _PID pid: 位置式pid的参数
 * @return: 调节占空比的一个整形数
 */
int PositionPIDToSpd(float deviation,_PID pid)
{
    float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;
    static float Bias,Pwm,Integral_bias,Last_Bias,pwmKI=0;
    Bias=deviation;                                          //计算偏差
    Integral_bias+=Bias;                                     //求出偏差的积分
    pwmKI=Position_KI*Integral_bias;
    if(pwmKI>PWM_DUTY_MAX) Integral_bias=PWM_DUTY_MAX/Position_KI;//限幅PWM_DUTY_MAX为最大pwm
    Pwm=Position_KP*Bias+pwmKI+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
    Last_Bias=Bias;                                          //保存上一次偏差
    return Pwm;
}
