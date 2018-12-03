
/****************************************************************************************
* File: ZxGesture.c
*   Description -   
*
* Version   Author          Date            Details
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 1.0.0     Emily Cvejic    11/27/2018      Created the file.
* 1.0.1     Emily Cvejic    11/28/2018      Worked on functions ZxGesture, ZxAction, 
*                                           ZxReadSpeed and ChaserDelay. 
*
***************************************************************************************/ 
#include "ZxGesture.h"
#define ZXADDR  (0x20)
#define DRCFG   (0x02)
#define DRE     (0x01)
#define STATUS  0x00
#define FCY     16000000
#include "uart2.h"
#include "i2c1.h"
#include "xc.h"
#include <string.h>

static enum {ZX_IDLE=0, ZX_R_SWIPE, ZX_L_SWIPE, ZX_UP_SWIPE} state=ZX_L_SWIPE;
static int GestureSpeed, Speed, Delay;
static char Gesture, Xcoor, Zcoor;
char buffer[50];


/*************************************************************
* Function  Name    - char ZxGesture(void)
*           purpose - Polls for the status register to change.
*                     returns the gesture value.
*           author  - Emily Cvejic
**************************************************************/
char ZxGesture(void){
    __delay32(FCY/10);
    Xcoor = ZXGesture_ReadByte(0x00);
//    Zcoor = ZXGesture_ReadByte(0x00);
    sprintf(buffer, "X coordinate: 0x%x\n\r", Xcoor);
    outString(buffer);
//    sprintf(buffer, " Z coordinate: 0x%x\r\r", Zcoor);
//    outString(buffer);
    return Gesture;
}

/*****************
* Function Name     - void ZxAction(void)
*          Purpose  - 
* 
******************/
void ZxAction(void){
    switch(state){
        case ZX_IDLE: 
            outString("No Action Detected \r");
            break;
        case ZX_R_SWIPE:
            Speed=ZxReadSpeed();
            Delay=ChaserDelay();
            sprintf(buffer,"Right Swipe Detected    Speed Value: %d    Delay Chaser: %dms\r", Speed, Delay);
            outString(buffer);
            break; 
        case ZX_L_SWIPE:
            Speed=ZxReadSpeed();
            Delay=ChaserDelay();
            sprintf(buffer,"Left Swipe Detected     Speed Value: %d    Delay Chaser: %dms\r", Speed, Delay);
            outString(buffer);
            break; 
        case ZX_UP_SWIPE:
            Speed=ZxReadSpeed();
            Delay=ChaserDelay();
            sprintf(buffer,"Up Swipe Detected       Speed Value: %d    Delay Chaser: %dms\r", Speed, Delay);
            outString(buffer);
            break;
    }
}

int ZxReadSpeed(){
    GestureSpeed = ZXGesture_ReadByte(0x05);    // Read from the GSPEED register, last gesture speed
    return GestureSpeed;
}

int ChaserDelay(void){
    switch(GestureSpeed){
        case 1: 
            return 500;
        case 2:
            return 450;
        case 3:
            return 400;
        case 4:
            return 350;
        case 5:
            return 300;
        case 6:
            return 250;
        case 7:
            return 200;
        case 8:
            return 150;
        case 9:
            return 100;
        case 10:
            return 50;
    }
    return 0;
}


void ZXGesture_Initialize(void)
{
    //0x01 - DRE
    //00111111 - 0x3F - 
    ZXGesture_WriteByte(DRE, 0x3F);
    //0x02 - DRCFG - Data Ready Config
    //10000001 - 0x81 - 
    ZXGesture_WriteByte(DRCFG, 0x81);
}

void ZXGesture_WriteByte(char regAddr, char WRval)
{
    //Writes a byte to the device
    char data_write[2];
    data_write[0] = regAddr;
    data_write[1] = WRval;
    writeNI2C1(ZXADDR, data_write, 2);
}

char ZXGesture_ReadByte(char regAddr)
{
    //Reads a byte to the device
    char data_read;
    write1I2C1(ZXADDR, regAddr);
    read1I2C1(ZXADDR, data_read);
    return data_read;
}

