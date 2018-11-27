/**
  @File Name
    uart2.c

  @Description
 * This basic code perform all the necessary operation for UART2, including
 * initialization and transmit single character via async serial I/O
 * 
 * Lab 2 - Introduction to UART
 * Advanced Microprocessor Concepts
 * DY Fong
 * 
 */

#define _ISR_NO_PSV __attribute__((__interrupt__, no_auto_psv))
#define FIFO_SIZE 16

/**
  Section: Included Files
 */

#include "uart2.h"
#include <xc.h>

// Variables
static char fifolist[FIFO_SIZE];
static int fifotail = 0;
static int fifohead = 0;

/*
	Initialize UART2 of PIC24 on Exp16 board
*/
void UART2_Initialize(void) 
{
    // 1000100000000000 -> Low speed mode S=16
    // 1000100000001000 -> High speed mode S=4
    U2MODE = 0x8800;
    
    // 1010010000000000 -> TX enabled
    U2STA = 0xA400;
 
    // Enable U2RXInterrupt while clearing the flag and set the priority to 1
    _U2RXIF = 0;
    _U2RXIP = 0x01;
    _U2RXIE = 1;
    
	// Set up your BRG register for Baud Rate = 19200
    // 0x0033 -> Low speed mode
    // 0x00CF -> High speed mode
    U2BRG = 0x0033;

	// clear transmit buffer 
    U2TXREG = 0x0000;
    
    // clear receiver buffer
    U2RXREG = 0x0000;
	
	// Enable UART2 transmission 
    U2STAbits.UTXEN = 1;
    
}

/*
	Output a single character (byte) via UART2
*/
void outChar(unsigned char c)
{
    while (U2STAbits.UTXBF);
    U2TXREG = c;
}
void outString(const char* psz_s) 
{
	// implement function to transmit a string via UART2
    int i = 0;
    //outChar('\n');
    while(psz_s[i] != '\0')
    {
        outChar(psz_s[i]);
        i++;
    }
}

unsigned int inString(char *psz_buff, unsigned int u16_maxCount) {
    unsigned char u8_c;
    unsigned int u16_i;

    if (!u16_maxCount) 
        return 0;

    for (u16_i = 0; u16_i < u16_maxCount; u16_i++) {
        u8_c = inChar();

        if (u8_c == '\n' ||u8_c == '\r' || u8_c == '\0') break; //terminate loop

        *psz_buff = u8_c; //save character
        psz_buff++;
    }
    //stop reading, terminate, return characters read.
    *psz_buff = 0;

    return(u16_i);
}


unsigned char inChar(void)
{
    char letter;
    while(fifohead == fifotail);
    checkRxErrorUART2();
    fifotail++;
    if(fifotail >= FIFO_SIZE) fifotail = 0;
    letter = fifolist[fifotail];
    return letter;
}

void checkRxErrorUART2(void) 
{
    if(fifohead == fifotail)
    {
        outString("UART2 receive buffer overrun error\n");
    }
	// Implement error checking on receive buffer overrun
    if (U2STAbits.OERR)
    {
        //clear error flag
		U2STAbits.OERR = 0b0;
        outString("UART2 receive buffer overrun error\n");
    }
}

void _ISR_NO_PSV _U2RXInterrupt(void)
{
    fifohead++;
    if(fifohead >= FIFO_SIZE) fifohead = 0;
    checkRxErrorUART2();
    fifolist[fifohead] = U2RXREG; 
    _U2RXIF = 0;
}
