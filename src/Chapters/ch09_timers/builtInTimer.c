// // Includes
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>
// #include "scale8.h"

// // Definitions
// #define SPEAKER_DDR DDRD
// #define SPEAKER_PORT PORTD
// #define SPEAKER PD6

// // Function Defintions
// static inline void initTimer0(void);
// static inline void playNote(uint8_t waveLength, uint16_t duration);

// // Interrupts
// ISR(TIMER1_OVF_vect) {

// }

// // Main Code
// int main(void) {
//   // Toggle speaker on output mode
//   SPEAKER_DDR |= (1 << SPEAKER);

//   // Initalizaions
//   initTimer0();

//   // Main loop
//   while (1) {
//     playNote(C2, 200);
//     playNote(D2, 200);
//     playNote(E2, 200);
//        (C3, 200);

//     _delay_ms(1000);
//     _delay_ms(1000);
//     _delay_ms(1000);
//   }

//   return 0;
// }

// static inline void initTimer0(void) {
//   TCCR0A |= (1 << WGM01); // CTC Mode
//   TCCR0A |= (1 << COM0A0); // Set the mode to toggle
//   TCCR0B |= (1 << CS01 | CS00); // Set the mode to 64 and enable the timer
// }

// static inline void playNote(uint8_t waveLength, uint16_t duration) {
//   OCR0A = waveLength; // Set our target value
//   SPEAKER_DDR |= (1 << SPEAKER);

//   while (duration) {
//     _delay_ms(1);
//     duration--;
//   }  

//   SPEAKER_DDR &= ~(1 << SPEAKER);
// }