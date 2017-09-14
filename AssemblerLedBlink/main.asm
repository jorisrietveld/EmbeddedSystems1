;
; Author: Joris Rietveld <jorisrietveld@gmail.com>
; Created: 14-09-2017 05:26
; Licence: GPLv3 - General Public Licence version 3
;
; This project blinks an LED

; LABEL	Instuct	Arg1	Arg2	Instruction name                    Description                                     What is actualy going on?
        ldi     r24,    0xFF    ; Load Immediate                    Load value 255 to register 24                   Amount of iterations in for loop
        out     0x1a,   r24     ; Port Out                          Store value of register 24 To DRRA              Set port A as output
        ldi     r18,    0x08    ; Load Immediate                    Load value 8 to register 18                     Amount of iterations in for loop
        ldi     r19,    0x00    ; Load Immediate                    Load value 0 to register 19                     Not sure what this is doing.
        ldi     r20,    0xFF    ; Load Immediate                    Load value 255 to register 20                   Default LED on value.
WHILE:  out     0x1b,   r1      ; Port Out                          Store value of register 1 to PORTA              Switch off leds.
        movw    r24,    r18     ; Copy Register Word                Copy the value of register 18 to register 24    Reset the for loop iteration counters.
DELAY1: sbiw    r24,    0x01    ; Substract Immidiate from word     Substract 1 from register 24                    Substract 1 from the iteration counter
        brne    DELAY1          ; Brance if not equal               go to DELEY1 register 24 equals 0               continue looping DELAY1 if counter not equals 0
        out     0x1b,   r20     ; Port out                          Store value of register 20 to PORTA             Set the leds high.
        movw    r24,    r18     ; Copy Register Word                Copy the value of register 18 to register 24    Reset the for loop iteration counters.
DELAY2: sbiw    r24,    0x01    ; Substract Immidiate from word     Substract 1 from register 23                    Substract 1 from the iteration counter
        brne    DELAY2          ; Brance if not equal               Brence if register 24 equals 0                  continue looping DELAY2 if counter not equals 0
        rjmp    WHILE           ; Direct jump                       Jump back to the WHILE:                         Endless loop WHILE:
