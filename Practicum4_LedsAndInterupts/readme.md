# Practicum 4 - Leds And Interrupts 
This assignment requires an expansion board containing the dip switches and Leds. This assignment
will use an external interrupt to execute an function that will chance the state of the led. 
So when an user presses an button the current executing program will be saved and the current
instruction pointer will point to the predefined interrupt function that updates the led value.

# Files of this practicum
 - `main.c` The entry point to the program containing the main program loop.
 - `initiateIO.h` This file contains an function for initiating the I/O pins connected to the micro controller.
 
# TODO's 
 - [ ] `Implement` interrupt function to be bound to an interrupt port so we can listen for external interrupt calls.
 - [ ] `Implement` an timer to make the leds blink with different intervals based on the interrupt button pressed.
