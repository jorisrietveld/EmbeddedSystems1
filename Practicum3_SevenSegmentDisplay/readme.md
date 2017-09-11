# Practicum 2 - Seven Segment Display
This assignment requires an expansion board containing four seven segment displays. The
board has 2 connections, one to write data on the A, B, C, D, E, F, G ports to light the
segments. And one to control the NPN transistors used to power the displays and to choose.
what display can be written to. 

Because you can only write one number at a time (Or write the same number on multiple displays) 
you have to use multiplexing to write multi digit numbers. To achieve this the ports connected to
the transistors have to be switched quickly so it seems like all four displays are on on the same 
time. The assignment is writing the number 8765 to the seven segment display.

## The seven segment display
Below is an list of the bit patterns for an certain number
|  Number   |   Bit Pattern (binary)   |   Hexdecimal   |   Decimal   |   Octal  |
|:---------:|:------------------------:|:--------------:|:-----------:|:--------:|
|        0  |               0b10000010 |           0x82 |         130 |     202  |
|        1  |               0b10010000 |           0x90 |         144 |     220  |
|        2  |               0b10000101 |           0x85 |         133 |     205  |
|        3  |               0b10010001 |           0x91 |         145 |     221  |
|        4  |               0b10111000 |           0xB8 |         184 |     270  |
|        5  |               0b11010000 |           0xD0 |         208 |     320  |
|        6  |               0b11000000 |           0xC0 |         192 |     300  |
|        7  |               0b10011011 |           0xE9 |         233 |     233  |
|        8  |               0b10000000 |           0x80 |         128 |     200  |
|        9  |               0b10010000 |           0x90 |         144 |     220  |

        
# Practicum files
 - `main.c` The entry point to the program containing the main program loop.
 - `initiateIO.h` This file contains an function for initiating the I/O pins connected to the micro controller.
 - `sevenSegmentDisplay.h` This file contains functions to write to the seven segment displays.
 - `delaySpaceTime.h` This file contains functions to delay `The Fabric Of Space Time` - use with caution, it will make your code unresponsive. 
 
# TODO's 
 - `Replace` delays with an timer and interrupts to make code more responsive.
 
