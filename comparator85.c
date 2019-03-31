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


void
setup(void) {
    crlPortRegAndSetAsOutPB4();
    disable_ADC();
    enable_comparator_multiplexed_input();
    select_ADC_input_channel( _ADCpin ); }//


void
crlPortRegAndSetAsOutPB4(void) {
    PORTB = 0x00;
    DDRB |= (1 << PB4); }// PB4 as LED out


void
disable_ADC(void) {
    clrBit(ADCSRA, ADEN); }//


void
enable_comparator_multiplexed_input(void) {
    setBit(ADCSRB, ACME); }//


void
select_ADC_input_channel(unsigned char _ADCpin) {
    clrWithMask( ADMUX, 0x03 );     // clr MUX[1:0]
    setWithMask( ADMUX, _ADCpin ); }// set MUX[1:0]


unsigned char
isComparatorHigh(void) {
    return getBit(ACSR,ACO); }//


int main(void) {

    setup();

    while(1) {

        if ( isComparatorHigh() )
            setBit( PORTB, PB4 );

        else
            clrBit( PORTB, PB4 );
        }

    }// main


/* END */

