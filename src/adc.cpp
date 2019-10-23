// Description:
//----------------------------------------------------------------------//

#include "adc.h"
#include <avr/io.h>

// initSwitch returns void and takes no parameters
void initADC(){
    // Set switch 22 as pull-up enabled input (Pin A0)
    PORTA |= (1 << PORTA0);
    DDRA &= ~(1 << DDA0);
}
