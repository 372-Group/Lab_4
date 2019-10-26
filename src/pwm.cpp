// Description:
//----------------------------------------------------------------------//

#include "pwm.h"
#include <avr/io.h>

void changeDutyCycle(){

}

void initPWMTimer3(){
    DDRE |= (1 << DDE3);
    TCCR3A |= (1 << WGM30) | (1 << WGM31) | (1 << COM3A1);
    TCCR3A &= ~(1 << COM3A0);
    TCCR3B |= (1 << WGM32) | (1 << CS30);
    OCR3A = 255;
}

void initPWMTimer4(){
    DDRH |= (1 << DDH4);
    TCCR4A |= (1 << WGM40) | (1 << WGM41) | (1 << COM4A1);
    TCCR4A &= ~(1 << COM4A0);
    TCCR4B |= (1 << WGM42) | (1 << CS40);
    OCR4A = 255;
}