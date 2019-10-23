// Author:
// Net ID:         
// Date:           
// Assignment:     Lab 4
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//

/*
 * Define a set of states that can be used in the state machine using an enum.
 */
typedef enum{
    WAIT_PRESS,
    WAIT_RELEASE
} states;

volatile states state = WAIT_PRESS;

int main(){
  int test = 1;

  while(1){
      switch(state){
          case WAIT_PRESS:
              break;
          case WAIT_RELEASE:

              break;
      }
  }

  return 0;
}

/* This is currently setup for interrupts on pin 22. Will need to be setup for deboucing,
 * which it currently does not do
 */
ISR(PCINT0_vect){
    if(state == WAIT_PRESS){
        state = WAIT_RELEASE;
    }
    else if( state == WAIT_RELEASE ){
        state = WAIT_PRESS;
        if( initial_delay == 200){
            initial_delay = 100;
        }
        else{
            initial_delay = 200;
        }
        delayMs(initial_delay);
    }
}
