/* 
 * File:   LEDChaser.h
 * Author: Clarence Zhen
 * Header file for the LEDChaser
 * Created on December 4, 2018
 */

#ifndef LEDCHASER_H
#define	LEDCHASER_H
#include <xc.h> 
#include "ZxGesture.h"

void initLEDs(void);
void LEDChaser(int delay, int direction);

#endif	/* LEDCHASER_H */

