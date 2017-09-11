# Practicum 5 - Pulse Counter 
This assignment requires an expansion board containing the dip switches and Leds, an board with the 
seven segment displays and an function generator for generation pulses. This assignment
will use an external interrupt chance the program mode for the handling of incoming pulses generated
by the function generator. What data is shown to the user on the four seven segments displays is depended 
on the current program mode set by the buttons.

 - If the program mode is set to 00 the counter will increment on the value shown on the seven segment
 displays by each pulse it receives.
 - If the program mode is set to 01 the counter will decrement on the value shown on the seven segment
 displays by each pulse it receives.
 - If the program mode is set to 10 the counter will increment on the value shown on the seven segment
 displays by each pulse it receives until the value 100 is reached. When 100 is reached the counter will
 start to decrement the value until 0 and start over from the beginning.
 - If the program mode is set to 11 the counter will increment but the seven segment display will only 
 show prime numbers.

# Files of this practicum
 - `main.c` The entry point to the program containing the main program loop.
 - `initiateIO.h` This file contains an function for initiating the I/O pins connected to the micro controller.
 
# TODO's 
 - []
