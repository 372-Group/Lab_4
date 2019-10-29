// Description:
//----------------------------------------------------------------------//

#include "pwm.h"
#include <avr/io.h>


/* The changeDutyCycle will be changing the amount of
 * voltage that is being sent. If we have 50% duty cycle in a 5v
 * system, 2.5 will be sent out.*/
/*
void changeDutyCycle(double num){
    if (num>2.00 && num<3.00){
        OCR3A = 1023;
        OCR4A = 1023;
    }
    else{
    float percent;
    percent = num / 5;
    OCR3A = percent * 1023;
    OCR4A = (1 - percent) * 1023;
    }
}
*/
void changeDutyCycle(int num){
    OCR3A = (int) (1023/100.0 * num);
    OCR4A = 1023 - (int) (1023/100.0 *num);
}

/*Turns off both motors*/
void turnOff(){
    OCR3A = 0;
    OCR4A = 0;
}

void initPWMTimer3(){
    DDRE |= (1 << DDE3);
    TCCR3A |= (1 << WGM30) | (1 << WGM31) | (1 << COM3A1);
    TCCR3A &= ~(1 << COM3A0);
    TCCR3B |= (1 << WGM32) | (1 << CS30);
    OCR3A = 1023;
}

void initPWMTimer4(){
    DDRH |= (1 << DDH3);
    TCCR4A |= (1 << WGM40) | (1 << WGM41) | (1 << COM4A1);
    TCCR4A &= ~(1 << COM4A0);
    TCCR4B |= (1 << WGM42) | (1 << CS40);
    OCR4A = 1023;
}