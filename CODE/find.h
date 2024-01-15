/*
 * find.h
 *
 *  Created on: 2023Äê6ÔÂ27ÈÕ
 *      Author: lenovo
 */

#ifndef FIND_H_
#define FIND_H_

void find_mid_line(uint8 index[MT9V03X_DVP_H][MT9V03X_DVP_W]);

void find_L (int mode);

extern uint8 l_border[MT9V03X_DVP_H];
extern uint8 r_border[MT9V03X_DVP_H];
extern uint8 mid_line_list[MT9V03X_DVP_H];

extern uint8 right_flag[MT9V03X_DVP_H];
extern uint8 left_flag[MT9V03X_DVP_H];

extern uint8 flag_line[MT9V03X_DVP_H];

extern int barrier;
#endif /* FIND_H_ */
