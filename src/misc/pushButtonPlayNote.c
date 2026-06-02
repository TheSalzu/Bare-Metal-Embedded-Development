// // Includes
// #include <avr/io.h>
// #include <util/delay.h>
// #include "USART.h"
// #include <organ.h>
// #include "scale16.h"
// #include "pinDefines.h"

// #define BUTTON_DDR DDRD
// #define BUTTON_PORT PORTD
// #define BUTTON_PIN PIND

// #define LED_DDR DDRB
// #define LED_PORT PORTB

// // #define SPEAKER_DDR DDRB

// // Main Loop
// int main(void) {
//     // Setup
//     BUTTON_DDR &= ~(1 << PD2); // This makes the button into input mode
//     BUTTON_PORT |= (1 << PD2); // This sets the internal pull up resistor
//     SPEAKER_DDR |= (1 << SPEAKER); // Output
//     LED_DDR |= (1 << PB0);

//     // Variables
//     const uint16_t song[] = {
//         E6, E6, E6, C6, E6, G6, G5,
//         C6, G5, E5, A5, B5, Ax5, A5,
//         G5, E6, G6, A6, F6, G6, E6, C6, D6, B5,
//         C6, G5, E5, A5, B5, Ax5, A5,
//         G5, E6, G6, A6, F6, G6, E6, C6, D6, B5,
//                                                                     /* etc */
//     };

//     const uint8_t SONG_LENGTH = sizeof(song) / sizeof(song[1]);
//     uint8_t noteToPlay = 0;
//     uint8_t debounceByte = 0xFF;
//     initUSART();

//     // Main Loop
//     while (1) {
//         debounceByte = (debounceByte << 1) | ((BUTTON_PIN >> PD2) & 1);

//         if (debounceByte == 0b11100000) {
//             // debounceByte = 0xFF;
//             playNote(song[noteToPlay], 1600);

//             // Toggle LED
//             LED_PORT ^= (1 << PB0);

//             noteToPlay++;
//             if (noteToPlay == SONG_LENGTH) {
//                 noteToPlay = 0;
//             }
//         }
//     }

//     _delay_ms(5);

//     return 0;
// }