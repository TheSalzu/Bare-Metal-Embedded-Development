// // Includes/Defintions
// #include <avr/io.h>
// #include <util/delay.h>
// #include "SPI.h"

// #define SCK PB5
// #define MOSI PB3
// #define SS PB2

// #define DELAY_BETWEEN_EFFECTS 100

// // Function Declarations
// void initSPI();


// // Main Code
// int main(void) {
//   initSPI();

//   // Constants
//   const uint8_t coolEffect[] = {
//     0b10000001,
//     0b01000010,
//     0b00100100,
//     0b00011000,
//     0b00100100,
//     0b01000010,
//   };

//   while (1) {
//     // EFFECT #1
//     for (uint8_t i = 0; i < 8; i++) { // 0 - 7
//       PORTB &= ~(1 << SS); // Pull it low to talk to it
//       SPI_transmit(1 << i);  // light up i'th pin
//       PORTB |= (1 << SS); // Pull it high to stop talking to it
//       _delay_ms(100);
//     }

//     for (uint8_t i = 6; i > 0; i--) { // 6 - 0
//       PORTB &= ~(1 << SS); // Pull it low to talk to it
//       SPI_transmit(1 << i);  // light up i'th pin
//       PORTB |= (1 << SS); // Pull it high to stop talking to it
//       _delay_ms(100);
//     }

//     _delay_ms(DELAY_BETWEEN_EFFECTS);

//     // EFFECT #2
//     for (uint8_t i = 0; i < 6; i++) {
//       PORTB &= ~(1 << SS); // Pull it low to talk to it
//       SPI_transmit(coolEffect[i]);
//       PORTB |= (1 << SS); // Pull it high to stop talking to it
//       _delay_ms(100);
//     }    

//     _delay_ms(DELAY_BETWEEN_EFFECTS);

//     // EFFECT #3
//     PORTB &= ~(1 << SS); // Pull it low to talk to it
//     SPI_transmit(0b10101010);
//     PORTB |= (1 << SS); // Pull it high to stop talking to it
//     _delay_ms(150);

//     PORTB &= ~(1 << SS); // Pull it low to talk to it
//     SPI_transmit(0b01010101);
//     PORTB |= (1 << SS); // Pull it high to stop talking to it

//     _delay_ms(DELAY_BETWEEN_EFFECTS);
//   }
// }

// // Functions
// void initSPI() {
//   DDRB |= (1 << SCK) | (1 << SS) | (1 << MOSI); // Set all the SPI pins to uput
//   PORTB |= (1 << SS); // Force SS High before enabling SPI Master
//   SPCR |= (1 << MSTR); // AVR is the master
//   SPCR |= (1 << SPR0);
//   SPCR |= (1 << SPE); // Enable SPI
// }