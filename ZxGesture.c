
/****************************************************************************************
* File: ZxGesture.c
*   Description -   contains all the functions used to control the sensor and interpret 
*                   the values. This file was used to read the gestures and the speed, and 
*                   also to change the state depending on the gesture detected.
*
* Version   Author          Date            Details
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 1.0.0     Emily Cvejic    11/27/2018      Created the file.
* 1.0.1     Emily Cvejic    11/28/2018      Worked on functions ZxGesture, ZxAction, 
*                                           ZxReadSpeed and ChaserDelay. 
* 1.0.2     ____________    12/3/2018       Broke system
* 1.0.3     ____________    12/4/2018       Fixed hardware component blocking system. 
*                                           Receiving correct values. Displaying speed and delay
* 1.0.4     Emily Cvejic    12/7/2018       Commented code and added macros
* 1.0.5     Clarence Zhen   12/8/2018       Commented Code
***************************************************************************************/ 
#include "ZxGesture.h"

/* Register and Address Macros */
#define ZXADDR  (0x20)
#define DRCFG   (0x02)
#define DRE     (0x01)
#define GESTURE (0x04)
#define GSPEED  (0x05)
#define STATUS  (0x00)
/* Macros */
#define MULTIPLIER  (20)
#define FCY         (16000000)

/* Local Variables */
static enum {ZX_IDLE=0, ZX_R_SWIPE, ZX_L_SWIPE, ZX_UP_SWIPE, ZX_HOVER, ZX_HL, ZX_HR, ZX_HU};
static int GestureSpeed, Speed, SpeedReturn;
static unsigned char Gesture = ZX_IDLE;
static char buffer[50];
/* Global Variables */
extern int Delay;
extern char Direction;

/*******************************************************************************
* Function Name: char ZX_ReadGesture(void)
* Author: Clarence Zhen 
*   Purpose - Reads from GESTURE Register of the ZX Gesture Sensor and returns
*             a byte value that is specific to the last used gesture.
*******************************************************************************/
char ZX_ReadGesture(void){
    Gesture = ZXGesture_ReadByte(GESTURE);
    return Gesture;
}

/*******************************************************************************
* Function Name: void ZxAction(void)
* Author: Emily Cvejic 
*   Purpose - Prints to the serial terminal a message based on the gesture read.
*             The message includes the speed and the delay of the chaser. 
*           ZX_IDLE:        State that does not do anything, goes there when the 
*                           gesture value is 0x00, meaning no gesture detected
*           ZX_R_SWIPE:     State for the right swipe. Sets the direction to 2,
*                           prints to the serial terminal.
*           ZX_L_SWIPE:     State for the left swipe. Sets the direction to 1, 
*                           prints to the serial terminal.
*           ZX_UP_SWIPE:    State for the up swipe. Sets the direction to 3.
*******************************************************************************/
void ZxAction(void){
    switch(Gesture){
        case ZX_IDLE: 
            //outString("No Action Detected \r");       // Did not implement this 
            break;
        case ZX_R_SWIPE:
            Direction = 2;                              // Direction set to 2, for the chaser
            Speed=ZxReadSpeed();                        // Read and record the speed
            Delay=ChaserDelay();                        // Record the delay by ChaserDelay() function
            sprintf(buffer,"Right Swipe Detected    Speed Value: %d    Delay Chaser: %d ms\n\r", Speed, Delay);
            outString(buffer);
            break; 
        case ZX_L_SWIPE:
            Direction = 1;      
            Speed=ZxReadSpeed();
            Delay=ChaserDelay();
            sprintf(buffer,"Left Swipe Detected     Speed Value: %d    Delay Chaser: %d ms\n\r", Speed, Delay);
            outString(buffer);
            break; 
        case ZX_UP_SWIPE:
            Direction = 3;
            Speed=ZxReadSpeed();
            Delay=ChaserDelay();
            sprintf(buffer,"Up Swipe Detected       Speed Value: %d    Delay Chaser: %d ms\n\r", Speed, Delay);
            outString(buffer);
            break;
        case ZX_HOVER:
            outString("Hover Detected \n\r");
            break;
        case ZX_HL:
            outString("Hover Left Detected \n\r");
            break;
        case ZX_HR:
            outString("Hover Right Detected \n\r");
            break;
        case ZX_HU:
            Direction = 3;
            outString("Hover Up Detected \n\r");
            break;
    }
}
/*******************************************************************************
* Function Name: int ZxReadSpeed(void)
* Author: Emily Cvejic 
*   Purpose - Reads from the speed (GSPEED) register. The value is returned by an
*             integer. The larger the integer, the slower the speed of the gesture.
*   Returns - SpeedReturn: integer of value 1-7 that represents the speed. 7 is 
*             slowest, 1 is fastest.   
*******************************************************************************/
int ZxReadSpeed(){
    GestureSpeed = ZXGesture_ReadByte(GSPEED);    // Read from the GSPEED register, last gesture speed
    if(GestureSpeed>=1  && GestureSpeed<=5)  SpeedReturn=1;
    if(GestureSpeed>=6  && GestureSpeed<=10) SpeedReturn=2;
    if(GestureSpeed>=11 && GestureSpeed<=15) SpeedReturn=3;
    if(GestureSpeed>=16 && GestureSpeed<=20) SpeedReturn=4;
    if(GestureSpeed>=21 && GestureSpeed<=25) SpeedReturn=5;
    if(GestureSpeed>=26 && GestureSpeed<=30) SpeedReturn=6;
    if(GestureSpeed>=31)                     SpeedReturn=7;
    return SpeedReturn;
}

/*******************************************************************************
* Function Name: int ChaserDelay(void)
* Author: Clarence Zhen & Emily Cvejic
*   Purpose - Sets the delay of the LED chaser. 
*******************************************************************************/
int ChaserDelay(void){
    return SpeedReturn*MULTIPLIER;
}

/*******************************************************************************
* Function Name: void ZX_Gesture_WriteByte(char regAddr, char WRval)
* Author: Clarence Zhen 
*   Purpose - An I2C Write function specific to the ZX Gesture Sensor.
*             Writes a byte to the selected register of the I2C device.
*******************************************************************************/
void ZXGesture_WriteByte(char regAddr, char WRval)
{
    //Writes a byte to the device
    char data_write[2];
    data_write[0] = regAddr;
    data_write[1] = WRval;
    writeNI2C1(ZXADDR, data_write, 2);
}

/*******************************************************************************
* Function Name: void ZX_Gesture_ReadByte(char regAddr, char WRval)
* Author: Clarence Zhen 
*   Purpose - An I2C Read function specific to the ZX Gesture Sensor.
*             Reads a byte from the selected register of the I2C device.
*******************************************************************************/
char ZXGesture_ReadByte(char regAddr)
{
    //Reads a byte to the device
    char data_read[1];
    write1I2C1(ZXADDR, regAddr);
    read1I2C1(ZXADDR, data_read);
    return data_read[0];
}

