// Authors:
// Net ID's:
// Date:
// Assignment: 
//----------------------------------------------------------------------//

#include "timer.h"

/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
void initTimer1(){
    TCCR1A&=~(1<<WGM10);
    TCCR1A&=~(1<<WGM11);
    TCCR1B|=(1<<WGM12);
    TCCR1B&=~(1<<WGM13);
    
    // Here we are setting our prescaler to 1.
    TCCR1B&=~(1<<CS12);
    TCCR1B&=~(1<<CS11);
    TCCR1B|=(1<<CS10);
    // This sets our output compare register to 16, thus allowing us to have 1 microsecond delay
    OCR1A = 16;
    
}

/* This delays the program an amount specified by unsigned int delay.
 */

// THIS SHOULD BE WORKING, I CHECKED IT, BUT CHECK WITH ARDUINO
void delayUs(unsigned int delay){
    //setthecounterto0
    TIFR1|=(1<<OCF1A);
    TCNT1=0;
    
    unsigned int count = 0;
    while(count<delay){
        if((TIFR1&(1<<OCF1A))){//incrementeverytimethetimerraisesaflag(counting10msflags)
            count++;
            TIFR1|=(1<<OCF1A);//settimertostartcountingagain
        }
    }
    
}

