#ifndef MY_ADC_H
#define MY_ADC_H

#include <avr/io.h>

/*
    ADC Channel Definitions
    These map to the physical analog pins on your Arduino Uno
*/
#define A0 PC0
#define A1 PC1
#define A2 PC2
#define A3 PC3
#define A4 PC4
#define A5 PC5
#define ANALOG_MAX 1023
#define ANALOG_MIN 0

/*
    ADMUX
    - REFS0: sets reference voltage to 5V (AVCC)
    - Bottom 4 bits: channel selection (which pin to read)
    - 0xf0 mask: clears bottom 4 bits without touching top 4

    ADCSRA
    - ADEN:  enables the ADC
    - ADSC:  starts a conversion, hardware clears it when done
    - ADPS2, ADPS1, ADPS0: prescaler set to 128 for 16MHz Uno
                           16MHz / 128 = 125kHz (within 50-200kHz range)

    ADC
    - Read only result register
    - Returns 0 to 1023 after conversion finishes
    - Actually two registers (ADCL + ADCH) combined by compiler
*/

void initADC(void);
uint16_t readADC(uint8_t channel);

#endif