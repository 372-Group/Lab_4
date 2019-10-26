// Description:
//----------------------------------------------------------------------//

#include "adc.h"
#include <avr/io.h>

//a 8-level ADC has a bit-depth of 3. 
//Arduino has a bit-depth of 10.

/* steps to set up the adc
1. configure ADCSRA
- Choose input channel, mode (single-ended or differential), and gain (if applicable) using ADMUX bits 3-0.
- Choose VREF(AREF,AVCC, or internal 2.56 Vref) using ADMUX bits 7-6
- Choose left or right alignment of conversion result in ADC Data Register using ADMUX bit 5
- Choose to enable or disable ADC auto-trigger using ADCSRA bit 5. If enabled, you then need to set bits 7-5 in SFIOR to 
select the auto-trigger source
- Choose to enable or disable ADC interrupt using ADCSRA bit 3. 
    If enabled, you will alos need to enable Global interrupt in order for the ADC Interrupt to be acted upon
    (SREG |= (1 << SREG_l);). You will also need an ISR to service the interrupt <=""="">
- Choose the clock prescaller using ADCSRA bits 2-0
- Turn on the ADC using ADCSRA bit 7:
    1 to turn on; 0 to turn off.
2. start a Conversion: 
    write a 1 to bit-6 of ADCSRA to start a conversion
3. COnversion Complete Check
- Either by ADC Interrupt or by checking bit 6 of ADCSRA (conversion is complete when this bit is 0)
or by checking bit 4 of ADCSRA (conversion is complete when this bit is 1)
*/

// initSwitch returns void and takes no parameters
void initADC(){
    // Set switch 22 as pull-up enabled input (Pin A0)
    PORTA |= (1 << PORTA0);
    DDRA &= ~(1 << DDA0);

    /* Special Function Registers
     * ADMUX
     * ADCSRA
     * ADCSRB
     * ADCH
     * ADCL
     * DIDR0
     * DIDR2
     * */


    //ADLAR determines how the 10-bit result is stored.
    //set ADLAR to 0.
    ADCSRA &= ~(1 << ADLAR);

    /*REFS refers to reference voltage that is used. In our case we will be using
     * VCC which is 5 volts. It is because of this that I believe we should use 'b01 for 
     * REFS [1:0]*/
    ADMUX &= ~(1 << REFS1);
    ADMUX |= (1 << REFS0);

    /*This is to turn on the ADC, this is usually the last thing to be done. 
     * So maybe put this at the bottom of the function.*/
    ADCSRA |=(1 << ADEN);

    /*This is to start the conversion process. 
    */

    //read from ADCL first and then read from ADCH
    //right justified

}
