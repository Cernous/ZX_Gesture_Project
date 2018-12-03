/* 
 * File:   zxgesture.h
 * Author: Clarence Zhen
 * Header file for the ZXGesture
 * Created on November 27, 2018, 1:03 PM
 */
#ifndef ZXGESTURE_H
#define	ZXGESTURE_H

#include <xc.h> // include processor files - each processor file is guarded.  

void ZxAction(void);
int ZxReadSpeed(void);
int ChaserDelay(void);
void ZXGesture_Initialize(void);
char ZXGesture_ReadByte(char regAddr);
void ZXGesture_WriteByte(char regAddr, char WRval);

#endif	/* ZXGESTURE_H */


