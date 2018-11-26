/**
  UART2 Generated Driver API Header File 

  @Company
    Microchip Technology Inc.

  @File Name
    uart2.h

  @Description
 * Lab 4 - Interrupt Driven UART
 * Advanced Microprocessor Concepts
 * DY Fong
 */



#ifndef _UART2_H
#define _UART2_H


void UART2_Initialize(void);

unsigned char inChar(void);  
unsigned int inString(char *psz_buff, unsigned int u16_maxCount);

void outChar(unsigned char u8_c);
void outString(const char* psz_s);

void checkRxErrorUART2(void);

#endif  // _UART2_H

/*
  End of File
 */
