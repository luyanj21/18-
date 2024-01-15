/*
 * motion.c
 *
 *  Created on: 2023Äê6ÔÂ27ÈÕ
 *      Author: lenovo
 */
#include "headfile.h"
void forward(void)
{
    motor_forward(left,pwml);
    motor_forward(right,pwmr);
}
