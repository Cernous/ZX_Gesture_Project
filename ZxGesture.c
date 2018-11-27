
/****************************************************************************************
* File: ZxGesture.c
*   Description -   
*
* Version           Date                  Details
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 1.0.0             11/27/2018            Created the file.
*
***************************************************************************************/ 
#include "ZxGesture.h"
#define ZXADDR  (0x20)
#define DRCFG   (0x02)
#define DRE     (0x01)
#include "uart2.h"
#include "xc.h"
#include <string.h>

static enum {ZX_IDLE=0, ZX_R_SWIPE, ZX_L_SWIPE, ZX_UP_SWIPE} state=ZX_L_SWIPE;
static int GestureSpeed, Speed, Delay;
char buffer[50];
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

int ChaserDelay(){
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
}


void ZXGesture_Initialize(void)
{
    //0x02 - DRCFG - Data Ready Config
    //10000001 - 0x81 - 
    ZXGesture_WriteByte(DRCFG, 0x81);
    //0x01 - DRE
    //00111111 - 0x3F - 
    ZXGesture_WriteByte(DRE, 0x3F);
    
}

void ZXGesture_WriteByte(INT16 regAddr, char WRval)
{
    //Writes a byte to the device
    char data_write[3];
    data_write[0] = (regAddr >> 8) & 0xFF;; // MSB of register address
    data_write[1] = regAddr & 0xFF;         // LSB of register address
    data_write[2] = WRval & 0xFF;
    writeNI2C1(ZXADDR, data_write, 3);
}

char ZXGesture_ReadByte(INT16 regAddr)
{
    //Reads a byte to the device
    char data_write[2];
    char data_read[1];
    data_write[0] = (regAddr >> 8) & 0xFF; // MSB of register address
    data_write[1] = regAddr & 0xFF;        // LSB of register address
    writeNI2C1(ZXADDR, data_write, 2);
    read1I2C1(ZXADDR, data_read);
    return data_read[0];
}

