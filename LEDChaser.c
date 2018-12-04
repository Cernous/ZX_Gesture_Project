#include "LEDChaser.h"
#define FCY     16000000
void initLEDs(void){
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISAbits.TRISA6 = 0;
    TRISAbits.TRISA7 = 0;
    LATA = 0b00000001;
}
void LEDChaser(int delay, int direction)
{
    switch(direction){
        case 1:
            if(LATA == 0b10000000) LATA = 0b00000001;
            else LATA = LATA << 1;
            __delay32(delay * (FCY/1000));
            break;
        case 2:
            if(LATA == 0b00000001) LATA = 0b10000000;
            else LATA = LATA >> 1;
            __delay32(delay * (FCY/1000));
            break;
        case 3:
            LATA = 0b11111111;
            break;
    }
}
