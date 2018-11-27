/****************************************************************************************
* File: ZxGesture.c
*   Description -   
*
* Version           Date                  Details
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 1.0.0             11/26/2018            Created the file.
*
***************************************************************************************/ 

#include "ZxGesture.h"
#define ZXADDR  (0x20)
#define DRCFG   (0x02)
#define DRE     (0x01)

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
