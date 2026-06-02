// // Includes / Defs
// #include <avr/io.h>
// #include <util/delay.h>
// #include "USART.h"
// #include "analogRead.h"
// #include <stdlib.h>  // add this at the top for itoa

// #define SOUND_ANALOG PC1

// #define LED_PORT PORTB
// #define LED_DDR DDRB
// #define LED_COUNT 3

// // Functions
// void resetPins(void);
// void initADC(void);
// uint16_t readADC(uint8_t channel);

// // Main
// int main(void) {
//   initADC();
//   initUSART();

//   for (uint8_t ledNumber = 0; ledNumber < LED_COUNT; ledNumber++) {
//     LED_DDR |= (1 << ledNumber); // Set all the pins to output
//   }

//   while (1) {
//     const uint16_t soundLevel = readADC(SOUND_ANALOG);
//     const uint8_t numberOfPinsLitUp = (soundLevel >> 8);

//     LED_PORT = 0;
//     for (uint8_t pinNumber = 0; pinNumber < numberOfPinsLitUp; pinNumber++) {
//       LED_PORT |= (1 << pinNumber);
//     }

//     // char buffer[5];
//     // itoa(soundLevel, buffer, 10);
//     // printString(buffer);
//     // printString("\r\n");

//     // _delay_ms(50);
//   }

//   return 0;
// }

// // Functions
// void initADC(void) {
//   ADMUX |= (1 << REFS0); // Set it to option 3, which is the reference voltage.
//   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set 128 divisoon for the prescaler
//   ADCSRA |= (1 << ADEN); // This simply turns the adc on
// }

// uint16_t readADC(uint8_t channel) {
//   // 1. Set the channel so the chip knows where to read from
//   ADMUX = (0xf0 & ADMUX) | channel; // 0xf0 is 1111 0000 so it clears the bottom 4 bits. The bottom 4 bits decide which pin to read from
//   ADCSRA |= (1 << ADSC); // This starts the conversion. ADSC stands for start conversion
//   while ( ADCSRA & (1 << ADSC) ) {};

//   return ADC;
// }