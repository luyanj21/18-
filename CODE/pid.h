/*
 * pid.h
 *
 *  Created on: 2023��6��27��
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
//�����Ƶ�ͨ������ƫ��ֵpid���pmw deviation��Ϊƫ��ֵ pid����������ϵ��
int PositionPIDToSpd(float deviation,_PID pid);

#endif /* PID_H_ */
