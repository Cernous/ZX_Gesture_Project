/* 
 * File:   zxgesture.h
 * Author: Clarence Zhen
 * Header file for the ZXGesture
 * Created on November 27, 2018, 1:03 PM
 */
#ifndef ZXGESTURE_H
#define	ZXGESTURE_H

#include <xc.h> // include processor files - each processor file is guarded.  

typedef signed short int    INT16;
void ZxAction(void);
int ZxReadSpeed(void);
int ChaserDelay(void);
void ZXGesture_Initialize(void);
void ZXGesture_ReadByte(INT16 regAddr);
void ZXGesture_WriteByte(INT16 regAddr, char WRval);

#endif	/* ZXGESTURE_H */


