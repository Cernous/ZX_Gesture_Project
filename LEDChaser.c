/****************************************************************************************
* File: LEDChaser.c
*   Description -   Contains functions necessary for a functioning LED chaser on the
*                   Explorer 16 Development Board.
*
* Version   Author          Date            Details
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 1.0.0     Clarence Zhen    12/4/2018      Created the file.
* 1.0.1     Clarence Zhen    12/8/2018      Commented Code.
****************************************************************************************/

#include "LEDChaser.h"

/* Macros */
#define FCY     16000000

/*******************************************************************************
* Function Name: void initLEDs(void)
* Author: Clarence Zhen 
*   Purpose - Initializes the 8 on-board Explorer 16 LEDs for the chaser.
*******************************************************************************/
void initLEDs(void){
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISAbits.TRISA6 = 0;
    TRISAbits.TRISA7 = 0;
    LATA = 0b00000001;                                  // Initial State of the LED chaser
}

/*******************************************************************************
* Function Name: void LEDChaser(int delay, int direction)
* Author: Clarence Zhen 
*   Purpose - LED Chaser Function. Shifts the light depending on the last gesture
*             and the last gesture speed.
*******************************************************************************/
void LEDChaser(int delay, int direction)
{
    switch(direction){
        case 1:                                         //Left Swipe was detected
            if(LATA == 0b10000000) LATA = 0b00000001;
            else LATA = LATA << 1;
            __delay32(delay * (FCY/1000));              //Delay in Milliseconds
            break;
        case 2:                                         //Right Swipe was detected
            if(LATA == 0b00000001) LATA = 0b10000000;
            else LATA = LATA >> 1;
            __delay32(delay * (FCY/1000));              //Delay in Milliseconds
            break;
        case 3:                                         //Swipe Up or Hover Up was detected
            LATA = 0b11111111;
            break;
    }
}
