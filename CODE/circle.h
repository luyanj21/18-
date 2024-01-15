/*
 * huandao.h
 *
 *  Created on: 2023Äê7ÔÂ6ÈÕ
 *      Author: cyl
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_
#include "headfile.h"
void RoundaboutProcess(uint8_t state);
uint16_t RoadIsRoundabout(void);
uint8_t UpdownSideGet(void);
uint16_t RoadUpSide_Mono(uint8_t X1, uint8_t X2,uint8 down_max);
uint16_t RoundaboutGetArc( uint8_t status, uint8_t num,uint8_t* index,uint8 start,uint8 end,uint8 down_num,uint8 lose_num);
#endif /* CIRCLE_H_ */
