/****************************************************************************************
* File: main.c
*   Description -   This project interafaces the ZX Distance and Gesture Sensor with the 
*                   PIC24FJ128GA010. This program will be able to chase LEDs based on the
*                   gesture motion and the speed.
*
* Version           Date                  Details
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 1.0.0             11/26/2018            Created the file.
* 1.0.1             12/8/2018             Added Comments
***************************************************************************************/ 
#include "mcc_generated_files/mcc.h"
#include "ZxGesture.h"
#include "i2c1.h"
#include "uart2.h"
#define FCY     16000000
int Delay;
char Direction;
int main(void)
{
    SYSTEM_Initialize();          // initialize the device
    UART2_Initialize(); 
    I2C1_Initialize(400);
    initLEDs();
    while (1)
    {
        __delay32(FCY/10);          // delay of 100 milliseconds
        ZX_XPos();                  // Obtain the gesture
        ZxAction();                 // Pass values global variables
        LEDChaser(Delay,Direction); // Move the LED chaser depending on the gesture
    }
    return -1;
}
