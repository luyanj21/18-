/*
 * motion.c
 *
 *  Created on: 2023��6��27��
 *      Author: lenovo
 */
#include "headfile.h"
void forward(void)
{
    motor_forward(left,pwml);
    motor_forward(right,pwmr);
}
