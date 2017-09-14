;
; Author: Joris Rietveld <jorisrietveld@gmail.com>
; Created: 09-09-2017 05:26
; Licence: GPLv3 - General Public Licence version 3
;
; My quick reference for memory addresses.

;============[ TWI - Two wire interface ]
;0x00	TWBR        Two wire interface Bit Rate Register
;0x01	TWSR        Two wire interface Status Register
;0x02	TWAR        Two wire interface Address Register
;0x03	TWDR        Two wire interface Data Register

;============[ ADC -Analog Digital Conversion ]
;0x04	ADC         Analog Digital Conversion
;0x04	ADC         Analog Digital Conversion
;0x04	ADCL        Analog Digital Conversion Low
;0x05	ADCH        Analog Digital Conversion High
;0x06	ADCSRA      Analog Digital Conversion Control and Sta
;0x07	ADMUX		Analog Digital Multiplexer

;============[ ACSR - Analog Comparator ]
;0x08	ACSR        Analog Comparator Status Register

;============[ USART - Universal Synchronous and Asynchronous Receiver Transmitter ]
;0x09   UBRRL       Universal Synchronous and Asynchronous Receiver Transmitter - Baud Rate Register Low
;0x0A   UCSRB       Universal Synchronous and Asynchronous Receiver Transmitter - Control and Status Register B
;0x0B   UCSRA       Universal Synchronous and Asynchronous Receiver Transmitter - Control and Status Register A
;0x0C   UDR         Universal Synchronous and Asynchronous Receiver Transmitter - I/O Data Register

;============[ SPI - Serial Peripheral Interface ]
;0x0D   SPCR        Serial Peripheral Interface Control register
;0x0E   SPSR        Serial Peripheral Interface Status register
;0x0    SPDR        Serial Peripheral Interface Data Register

============[ Output Port D  ]
;0x10   PIND        Pin Output D
;0x11   DDRD        Data Direction Register D
;0x12   PORTD       Pin Output D

;============[ Output Port C  ]
;0x13   PINC        Pin input C
;0x14   DDRC        Data Direction Register C
;0x15   PORTC       Pin Output C

;============[ Output Port B  ]
;0x16   PINB        Pin input B
;0x17   DDRB        Data Direction Register B
;0x18   PORTB       Pin Output B

;============[ Output Port A  ]
;0x19   PINA        Pin input A
;0x1A   DDRA        Data Direction Register A
;0x1B   PORTA       Pin Output A

;============[ EEPROM ]
;0x1C   EECR        Electrical Erasable Read Only Memory Control Register
;0x1D   EEDR        Electrical Erasable Read Only Memory Data Register
;0x1E   EEAR        Electrical Erasable Read Only Memory Address Register
;0x1E   EEARL       Electrical Erasable Read Only Memory Address Register Low
;0x1F   EEARH       Electrical Erasable Read Only Memory Address Register High

;0x20   UBRRH       Universal Synchronous and Asynchronous Receiver Transmitter - Baud Rate Register High
;0x21   WDTCR       Watchdog Timer Control Register
;0x22   ASSR        Asynchronous Status Register

;============[  Timer 2  ]
;0x23   OCR2         Output Compare Register 2
;0x24   TCNT2       Timer/Counter1 Control Register 2 B
;0x25   TCCR2       Timer/Counter1 Control Register 2 A
;============[  Timer 1  ]
;0x26   ICR1L       Input Capture Register Low
;0x27   ICR1H       Input Capture Register High
;0x28   OCR1BL      Output Compare Register 1B LOW
;0x29   OCR1BH      Output Compare Register 1B High
;0x2A   OCR1AL      Output Compare Register 1A LOW
;0x2B   OCR1AH      Output Compare Register 1A High
;0x2C   TCNT1L      Timer/Counter 1 Low
;0x2D   TCNT1H      Timer/Counter 1 High
;0x2E   TCCR1B      Timer/Counter1 Control Register 1 B
;0x2F   TCCR1A      Timer/Counter1 Control Register 1 A
;0x30   SFIOR       Special Function I/O Register
;0x31   OSCCAL      Oscillator Calibration Register
;OCDR   OSCCAL      Oscillator Calibration Register
;============[  Timer 0  ]
;0x32    TCNT0      Timer/Counter 0
;0x33    TCCR0      Timer/Counter1 Control Register 0
;0x34    MCUSR      MCU Control and Status Register
;MCUCSR  MCUS
;0x35    MCUCR      MCU Control Register
;0x36    TWCR       Timer/Counter1 Control Register
;0x37    SPMCR      Store Program Memory Control Register
;0x38    TIFR       Timer/Counter Interrupt Flag Register
;0x39    TIMSK      Timer/Counter Interrupt Mask Register
;0x3A    GIFR       General Interrupt Flag Register
;0x3B    GIMSK      General Interrupt Control Register
;GICR    GIMSK      General Interrupt Control Register
;0x3C    OCR0       Timer/Counter0 Output Compare Register 0
