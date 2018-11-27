/* 
 * File:   zxgesture.h
 * Author: Clarence Zhen
 * Header file for the ZXGesture
 * Created on November 27, 2018, 1:03 PM
 */

#include "i2c1.h"

#ifndef ZXGESTURE_H
#define	ZXGESTURE_H

typedef signed short int    INT16;

void ZXGesture_Initialize(void);
void ZXGesture_ReadByte(INT16 regAddr);
void ZXGesture_WriteByte(INT16 regAddr, char WRval);

#endif	/* ZXGESTURE_H */

