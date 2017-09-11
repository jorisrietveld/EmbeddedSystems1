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
To write an value to an 7 segment display you will have to know what bit pattern is needed for the
desired effect. The table below shows an list with all possible numbers that can be displayed on the 
displays with there bit pattern, hexadecimal, decimal and octal values.

|  Number   |   Bit Pattern (binary)   |   Hexadecimal  |   Decimal   |   Octal  | Bit Shift sets               |
|:---------:|:------------------------:|:--------------:|:-----------:|:--------:|:----------------------------:|
|        0  |               0b10000010 |           0x82 |         130 |     202  | r \|= (1<<2)\|(1<<7)           |
|        1  |               0b10010000 |           0x90 |         144 |     220  | r \|= (1<<5)\|(1<<7)           |
|        2  |               0b10000101 |           0x85 |         133 |     205  | r \|= (1<<0)\|(1<<2)\|(1<<7)    |
|        3  |               0b10010001 |           0x91 |         145 |     221  | r \|= (1<<0)\|(1<<4)\|(1<<7)    |
|        4  |               0b10111000 |           0xB8 |         184 |     270  | r \|= (1<<4)\|(1<<5)\|(1<<6)\|(1<<7)|
|        5  |               0b11010000 |           0xD0 |         208 |     320  | r \|= (1<<4)\|(1<<6)\|(1<<7)    |
|        6  |               0b11000000 |           0xC0 |         192 |     300  | r \|= (1<<6)\|(1<<7)           |
|        7  |               0b10011011 |           0xE9 |         233 |     233  | r \|= (1<<0)\|(1<<1)\|(1<<3)\|(1<<4)\|(1<<7)|
|        8  |               0b10000000 |           0x80 |         128 |     200  | r \|= (1<<7)                  |
|        9  |               0b10010000 |           0x90 |         144 |     220  | r \|= (1<<4)\|(1<<7)           |

# Practicum files
 - `main.c` The entry point to the program containing the main program loop.
 - `initiateIO.h` This file contains an function for initiating the I/O pins connected to the micro controller.
 - `sevenSegmentDisplay.h` This file contains functions to write to the seven segment displays.
 - `delaySpaceTime.h` This file contains functions to delay `The Fabric Of Space Time` - use with caution, it will make your code unresponsive. 
 
# TODO's 
 - `Replace` delays with an timer and interrupts to make code more responsive.
 
