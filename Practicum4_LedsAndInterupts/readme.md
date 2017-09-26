# Practicum 4 - Leds And Interrupts 
This assignment requires an expansion board containing the dip switches and Leds. This assignment
will use an external interrupt to execute an function that will chance the state of the led. 
So when an user presses an button the current executing program will be saved and the current
instruction pointer will point to the predefined interrupt function that updates the led value.

## Initiating 
To start using interrupts on the micro controller, you have to include the interrupt header file.
The header defines some compiler preprocessor macro's that help with configuring interrupts,
enabling/disabling, setting an handler and some constants that can be passed as flags. 
```c
/**
 * Include the AVR Interrupt interface.
 * Remember to use sharp brackets instead of double quotes when you include non local files. 
 */
#include <avr/interrupt.h>

```
### The ports
To 

### The 

## The Interrupt function ISR
The project has to use an interrupt to update the led state. Below I will explain every code 
bit.

First we have to define the an `ISR()`(Interrupt Service Routine)[http://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html#gad28590624d422cdf30d626e0a506255f]
for interrupt 0 (Port D5). 
```c
ISR (INT0_vect)
{
```
    PORTC = ~( state ^ ( state >> 1 )); // Encode the state to led output signals.
    state++; // Increase state by 1
    state %= 4; // Limit the state to 3
}
```

## Files of this practicum
 - `main.c` The entry point to the program containing the main program loop.
 
## TODO's 
 - [ ] `Implement` interrupt function to be bound to an interrupt port so we can listen for external interrupt calls.
 - [ ] `Implement` an timer to make the leds blink with different intervals based on the interrupt button pressed.
