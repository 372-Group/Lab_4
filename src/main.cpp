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
#define LONG_DELAY 30000
/*
 * Define a set of states that can be used in the state machine using an enum.
 */

typedef enum stateType{
  wait_press, wait_release, debounce_press, debounce_release
} stateType;

//initializing state
volatile stateType state = wait_press;
volatile bool button = true;

int main(){
  /* for ADC */
  initADC();
  initTimer1();
  initSwitchPB3();
  initPWMTimer3();
  initPWMTimer4();
  sei();
  //Serial.begin(9600);
  //unsigned int result = 0;
  //float voltage = 0;
  //bool On = true;

  //float dutyVolt3 = voltage/5;
  //float dutyVolt4 = 1. - dutyVolt3;
  //changeDutyCycle(dutyVolt3);
  //changeDutyCycle(dutyVolt4);

  int low = 0;
  while(1){
  /*     
        // print out ADC value
        // read in ADCL first then read ADCH
        if(!On){
          turnOff();
          //changeDutyCycle(dutyVolt3);
          //changeDutyCycle(dutyVolt4);
          //changeDutyCycle(voltage);
          Serial.println(On);
        }
        else{
        result = ADCL;
        result += ((unsigned int) ADCH) << 8;
        voltage = result * (5.0/1023.0);
        Serial.println(voltage);
        Serial.println(On);
        changeDutyCycle(voltage);
        }

      switch(state){
      case wait_press:
        delayUs(100000);
        break;
      case debounce_press:
        delayUs(LONG_DELAY);
        state = wait_release;
        break;
      case wait_release:
        delayUs(100000);
        break;
      case debounce_release:
        delayUs(LONG_DELAY);
        if(On){
          On = false;
        }
        else{
          On = true;
        }
        state = wait_press;
        break;
      }*/
    // Switch ISR
    
        switch(state)
        {
            case wait_press:
                low = ADCL;
                low += ((ADCH & 0x3) << 8);
                //voltage = low * (5.0/1023.0);
                //changeDutyCycle(voltage*100);
                changeDutyCycle((int) low/1023.0 * 100.0);
                break;

            case debounce_press:
                delayUs(1);
                state = wait_release;
                break;
            
            case wait_release:
                low = 0;
                OCR3A = 0;
                OCR4A = 0;
                break;
            
            case debounce_release:
                delayUs(1);
                state = wait_press;
                break;
           
            default:
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
    button = ~button;
    Serial.println(button);
    state = debounce_release;
  }
}

