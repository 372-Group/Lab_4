// Author:
// Net ID:         
// Date:           
// Assignment:     Lab 4
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
#include <Arduino.h>
#include <avr/io.h>
#include "adc.h"
#include "switch.h"
#include "timer.h"
#define SHORT_DELAY 100
#define LONG_DELAY 200
/*
 * Define a set of states that can be used in the state machine using an enum.
 */
typedef enum stateType_enum{
  //wait_press, debounce_press, wait_release, debounce_release
  wait_press, wait_release
} stateType;

//initializing state
volatile stateType state = wait_press;

int main(){
  int test = 1;

  while(1){
      switch(state){
        case wait_press: //flip = 2
          //delayMs(SHORT_DELAY);
          //turnOnLEDWithChar(i);
        break;
        case wait_release: //flip = 1
          //delayMs(LONG_DELAY);
          //turnOnLEDWithChar(i);
        break;
      }
  }

  return 0;
}

/* This is currently setup for interrupts on pin 22. Will need to be setup for deboucing,
 * which it currently does not do
 */
ISR(PCINT0_vect){
  //use this function for the PCINT0 flag when it goes up
  //handle the switch press
  if(state == wait_press){
    state = wait_release;
    delayUs(LONG_DELAY);
  }
  else{
    state = wait_press;
    delayUs(SHORT_DELAY);
  }
}

