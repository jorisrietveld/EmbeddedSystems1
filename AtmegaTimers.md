# Timers And Interupts on the Atmega32

### F_CPU 1000000UL
- 0.001 GHz
- 1 MHz
- 1000 KHz
- 1 000 000 hertz
### This table show the amount of clock ticks for an given time and prescaler

| **Time unit**     | Normal        |**Prescaler 8**|**Prescaler 64**|**Prescaler 256**|**Prescaler 1024**|
|:-----------------:|:-------------:|:-------------:|:-------------:|:-------------:|:-------------:|
|**Hour**           |3 600 000 000  | 450 000 000   | 56.250.000    | 14 062.500    | 3.515.625     |
|**minute**         |60 000 000     |7 500 000      | 937 500       | 234 375       | 58593.75      |
|**second**         |1 000 000      |125 000        | 15 625        | 3906.25       | 976.5625      |
|**100 millisecond**|100 000        |12 500         | 1 562.5       | 390.625       | 97.65625      |
|**10 millisecond** |10 000         |1 250          | 156.25        | 39.0625       | 9.765625      |
|**1 millisecond**  |1000           |125            | 15.625        | 3.90625       | 0.9765625     |
|**microsecond**    |1              | 0.125         | 0.015625      | 0.00390625    | 0.0009765625  |


## Timer/Counter 0 Registers - 8 Bit Register - Range( 0, 255 )
This are the registers that are associated with TIMER0, so you need them for configuration and to access the values.

| **Address**   |**Macro**  | **Full name**                                 | **Description**                                                                 |
|:-------------:|:------:   |:---------------------------------------------:|:-------------------------------------------------------------------------------:|
|0x32           |`TCNT0 `   |     Timer/Counter 0                           | This register holds counted clock circles, increments until if overflows at 255 |
|0x33           |`TCCR0 `   |     Timer/Counter1 Control Register 0         | This register configures the clock source (internal/external/off)               |
|0x34           |`MCUSR `   |     MCU Control and Status Register           |                                                                                 |
|**MCUS**       |`MCUCSR`   |     Alias                                     |                                                                                 |
|0x35           |`MCUCR `   |     MCU Control Register                      |                                                                                 |
|0x36           |`TWCR  `   |     Timer/Counter1 Control Register           |                                                                                 |
|0x37           |`SPMCR `   |     Store Program Memory Control Register     |                                                                                 |
|0x38           |`TIFR  `   |     Timer/Counter Interrupt Flag Register     |                                                                                 |
|0x39           |`TIMSK `   |     Timer/Counter Interrupt Mask Register     |                                                                                 |
|0x3A           |`GIFR  `   |     General Interrupt Flag Register           |                                                                                 |
|0x3B           |`GIMSK `   |     General Interrupt Control Register        |                                                                                 |
|**GICR****     |`GIMSK `   |     Alias                                     |                                                                                 |
|0x3C           |`OCR0  `   |     Timer/Counter0 Output Compare Register 0  |                                                                                 |

#### Clock Source Settings - Register TCCR0
 For configuring the the the prescaler, clock source and enable timer 1.

|**Mode**|**Binary**|**Hex**|**Bit Shift (with empty values)** | **Bit Shift (Use this)**   |**Description**        |**Source**          |
|:--:|:--------:|:----:|:-------------------------------------:|:--------------------------:|:---------------------:|:------------------:|
|0 | 0b00000000 | 0x00 | `(0<<CS02) \| (0<<CS01) \| (0<<CS00)` | `                        ` | Timer off             |                    |
|1 | 0b00000001 | 0x01 | `(0<<CS02) \| (0<<CS01) \| (1<<CS00)` | `(1<<CS00)               ` | Internal Clock / 0    | Prescaler disapled |
|2 | 0b00000010 | 0x02 | `(0<<CS02) \| (1<<CS01) \| (0<<CS00)` | `(1<<CS01)               ` | Internal Clock / 8    | From Prescaler     |
|3 | 0b00000011 | 0x03 | `(0<<CS02) \| (1<<CS01) \| (1<<CS00)` | `(0<<CS01)\|(0<<CS01)    ` | Internal Clock / 64   | From Prescaler     |
|4 | 0b00000100 | 0x04 | `(1<<CS02) \| (0<<CS01) \| (0<<CS00)` | `(1<<CS02)               ` | Internal Clock / 256  | From Prescaler     |
|5 | 0b00000101 | 0x05 | `(1<<CS02) \| (0<<CS01) \| (1<<CS00)` | `(1<<CS02) \| (1 << CS00)` | Internal Clock / 1024 | From Prescaler     |
|5 | 0b00000110 | 0x06 | `(1<<CS02) \| (1<<CS01) \| (0<<CS00)` | `(1<<CS02) \| (1 << CS01)` | External clock on pin |                    |

## Timer/Counter 1 Registers - 16 Bit Register - Range( 0, 65535 )
This are the registers that are associated with TIMER1, so you need them for configuration and to access the values.

| **Address**   |**Macro**  | **Full name**                                   | **Description**                                             |
|:-------------:|:---------:|:-----------------------------------------------:|:-----------------------------------------------------------:|
|0x26           | `ICR1L `    | Input Capture Register Low                    |                                                             |
|0x27           | `ICR1H `    | Input Capture Register High                   |                                                             |
|0x28           | `OCR1BL`    | Output Compare Register 1B LOW                |                                                             |
|0x29           | `OCR1BH`    | Output Compare Register 1B High               |                                                             |
|0x2A           | `OCR1AL`    | Output Compare Register 1A LOW                |                                                             |
|0x2B           | `OCR1AH`    | Output Compare Register 1A High               |                                                             |
|0x2C           | `TCNT1L`    | Timer/Counter 1 Low                           |                                                             |
|0x2D           | `TCNT1H`    | Timer/Counter 1 High                          |                                                             |
|0x2E           | `TCCR1B`    | Timer/Counter1 Control Register 1 B           |                                                             |
|0x2F           | `TCCR1A`    | Timer/Counter1 Control Register 1 A           |                                                             |
|0x30           | `SFIOR `    | Special Function I/O Register                 |                                                             |
|0x31           | `OSCCAL`    | Oscillator Calibration Register               |                                                             |
|OCDR           | `OSCCAL`    | Oscillator Calibration Register               |                                                             |


## Timer/Counter 1 Registers - 8 Bit Register - Range( 0, 255 )
This are the registers that are associated with TIMER2, so you need them for configuration and to access the values.

| **Address**   |**Macro**  | **Full name**                                 | **Description**                                               |
|:-------------:|:---------:|:---------------------------------------------:|:-------------------------------------------------------------:|
|0x23           | `OCR2 `   | Output Compare Register 2                     |                                                               |
|0x24           | `TCNT2`   | Timer/Counter 2 Control Register 2 B          |                                                               |
|0x25           | `TCCR2`   | Timer/Counter 2 Control Register 2 A          |                                                               |
