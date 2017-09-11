# Practicum 2 - Leds and Dip Switches
This assignment requires an expansion board containing 8 Led's and 4 dip switches. 
The goal is to control the led's using the settings set by the four dip switches. 

 - If the first dip switch is on, activate an single led on the array and shift it from 
 left to right like this pattern:
     ```
    1111 1110	0x7F	127
    1111 1101	0xBF	191
    1111 1011	0xDF	232
    1111 0111	0xEF	239
    1110 1111	0xF7	247
    1101 1111	0xFB	251
    1011 1111	0xFD	253
    0111 1111	0xFE	254
     ```
 - If the second dip switch is on, activate an single led on the array and shift it from 
 the right to the left like this pattern:
    ```
    0111 1111	0x7F	127
    1011 1111	0xBF	191
    1101 1111	0xDF	232
    1110 1111	0xEF	239
    1111 0111	0xF7	247
    1111 1011	0xFB	251
    1111 1101	0xFD	253
    1111 1110	0xFE	254
    ```
 - If the third dip switch is on, activate an single led on the array and shift is from left 
 to right and back like this pattern:
    ```
    1111 1110	0x7F	127
    1111 1101	0xBF	191
    1111 1011	0xDF	232
    1111 0111	0xEF	239
    1110 1111	0xF7	247
    1101 1111	0xFB	251
    1011 1111	0xFD	253
    0111 1111	0xFE	254
    0111 1111	0x7F	127
    1011 1111	0xBF	191
    1101 1111	0xDF	232
    1110 1111	0xEF	239
    1111 0111	0xF7	247
    1111 1011	0xFB	251
    1111 1101	0xFD	253
    1111 1110	0xFE	254
    ```
 - If the fourth dip switch is on, write some awesome led effects of your own. I created several 
 led shows here are some of the patterns they produce:
    - Led Expand, start with 2 leds in the middle expand them to the sides and back to the middle.
        ```
        11111111
        11100111
        11000011
        10000001
        00000000
        10000001
        11000011
        11100111
        11111111
        ```
    - Led Slide, slide leds in from the left and slide them out on the left.
        ```
        1111 1110
        1111 1100
        1111 1000
        1111 0000
        1110 0000
        1100 0000
        1000 0000
        0000 0000
        1000 0000
        1100 0000
        1110 0000
        1111 0000
        1111 1000
        1111 1100
        1111 1110
        1111 1111
        ```
     - Led Slide Out, Slide leds in from the right and slide them out on the left.
        ```
        1111 1110
        1111 1100
        1111 1000
        1111 0000
        1110 0000
        1100 0000
        1000 0000
        0000 0000
        0000 0001
        0000 0011
        0000 0111
        0000 1111
        0001 1111
        0011 1111
        0111 1111
        1111 1111
        ```
     - Led Slide Scan, slide in leds from the left, clear all and slide leds from the right. 
        ```
        0000 0001
        0000 0011
        0000 0111
        0000 1111
        0001 1111
        0011 1111
        0111 1111
        1111 1111
        0000 0000
        1111 1110
        1111 1100
        1111 1000
        1111 0000
        1110 0000
        1100 0000
        1000 0000
        ```
        
# Practicum files
 - `main.c` The entry point to the program containing the main program loop.
 - `initiateIO.h` This file contains an function for initiating the I/O pins connected to the micro controller.
 - `switches.h` This file contains functions to read the dip switches.
 - `ledPrograms.h` This files contains all the led pattern generator functions.
 - `delaySpaceTime.h` This file contains functions to delay `The Fabric Of Space Time` - use with caution, it will make your code unresponsive. 
 
# TODO's 
 - `Replace` delays with an timer and interrupts to make code more responsive.
 
