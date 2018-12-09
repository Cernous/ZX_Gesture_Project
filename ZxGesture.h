/* 
 * File:   zxgesture.h
 * Author: Clarence Zhen
 * Header file for the ZXGesture
 * Created on November 27, 2018, 1:03 PM
 */
#ifndef ZXGESTURE_H
#define	ZXGESTURE_H

#include <xc.h>       // include processor files - each processor file is guarded.  
#include "uart2.h"
#include "i2c1.h"
#include <string.h>

int ZxReadSpeed(void);
void ZxAction(void);
char ZX_ReadGesture(void);
char ZXGesture_ReadByte(char regAddr);
void ZXGesture_WriteByte(char regAddr, char WRval);

#endif	/* ZXGESTURE_H */


