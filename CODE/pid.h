/*
 * pid.h
 *
 *  Created on: 2023年6月27日
 *      Author: lenovo
 */

#ifndef PID_H_
#define PID_H_

typedef struct
{
    float kp;
    float ki;
    float kd;
}_PID;
extern _PID PID;

extern _PID TurnPdate;

extern _PID SpdPdate;

int PositionPID(float deviation,_PID pid);
//带限制的通过输入偏差值pid输出pmw deviation即为偏差值 pid是三个比例系数
int PositionPIDToSpd(float deviation,_PID pid);

#endif /* PID_H_ */
