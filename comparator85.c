/*
 * comparator85.c
 *  Created on:     04.06.2018
 *  Last modified:  
 *  Author:         Andrew Jason Bishop
 */

#define F_CPU 16000000UL
#include <avr/io.h>

#define BIT(x) (0x01 << (x))

#define setBit(reg, bit) ( (reg) |=  (1 << (bit)) )
#define clrBit(reg, bit) ( (reg) &= ~(1 << (bit)) )

#define flpBit(reg,bit) ( (reg) ^= (1 << (bit)) )
#define getBit(reg,bit) ( (reg) &  (1 << (bit)) )

#define setWithMask(reg, mask) ( (reg) |=  (mask) )
#define clrWithMask(reg, mask) ( (reg) &= ~(mask) )




int main(void) {

    DDRB |= (1 << PB4);     // PB4 as LED out
    PORTB = 0x00;

    ADCSRA &= ~(1 << ADEN); // disable ADC (clr bit)
    ADCSRB |=  (1 << ACME); // enable comparator multiplexed input (set bit)
    ADMUX &= ~0x03;         // clr MUX[1:0]
    ADMUX |=  3;            // set MUX[1:0], select ADC3 as AIN1 

    while(1) {

        if ( getBit(ACSR,ACO) )
            setBit( PORTB, PB4 );

        else
            clrBit( PORTB, PB4 );
        }

    } // main


/* END */

