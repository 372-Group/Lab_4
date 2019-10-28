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
#include "pwm.h"
#define LONG_DELAY 10000
/*
 * Define a set of states that can be used in the state machine using an enum.
 */

typedef enum stateType{
  wait_press, wait_release, debounce_press, debounce_release
} stateType;

int On = 1;
//initializing state
volatile stateType state = wait_press;

int main(){
  /* for ADC */
  initADC();
  initTimer1();
  initSwitchPB3();
  initPWMTimer3();
  initPWMTimer4();
  sei();
  Serial.begin(9600);
  unsigned int result = 0;
  float voltage = 0;

  while(1){
        // print out ADC value
        // read in ADCL first then read ADCH
        result = ADCL;
        result += ((unsigned int) ADCH) << 8;
        voltage = result * (5.0/1023.0);
        Serial.println(voltage);
        changeDutyCycle(voltage);
      switch(state){
        case wait_press:
        break;
        case debounce_press:
        delayUs(LONG_DELAY);
        break;
        case wait_release:
        break;
        case debounce_release:
        delayUs(LONG_DELAY);
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
    state = debounce_press;
  }
  else if(state == wait_release){
    if(On){
      On = 0;
      turnOff();
    }
    else{
      On = 1;
      initPWMTimer3();
      initPWMTimer4();
    }
    state = debounce_release;
  }
}

