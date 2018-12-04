/****************************************************************************************
* File: main.c
*   Description -   This project interafaces the ZX Distance and Gesture Sensor with the 
*                   PIC24FJ128GA010. This program will be able to chase LEDs based on the
*                   gesture motion and the speed.
*
* Version           Date                  Details
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 1.0.0             11/26/2018            Created the file.
*
***************************************************************************************/ 
#include "mcc_generated_files/mcc.h"
#include "ZxGesture.h"
#include "i2c1.h"
#include "uart2.h"
#define FCY     16000000
int main(void)
{
    SYSTEM_Initialize();          // initialize the device
    UART2_Initialize(); 
    I2C1_Initialize(400);
    while (1)
    {
        __delay32(FCY/10);
        ZX_XPos();
        ZxAction(); 
    }
    return -1;
}
