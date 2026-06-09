// // Definitions & Includes
// #include <avr/io.h>
// #include <util/delay.h>
// #include <avr/interrupt.h>
// #include <stdbool.h>

// #define TIMER0_OVERFLOW_FOR_SECOND ((15625 / 2) / 255)

// #define LED_1 PD4
// #define LED_2 PD5
// #define LED_PORT PORTD
// #define LED_DDR DDRD

// // Function Definitions
// void initTimer0(void);
// void initTimer1(void);
// void initLED(void);

// // Global Variables
// volatile bool timer0Overflown = false;

// // Interrupts
// ISR(TIMER1_COMPA_vect) {
//   LED_PORT ^= (1 << LED_1);
// }

// ISR(TIMER0_OVF_vect) {
//   timer0Overflown = true;
// }

// // Main Code
// int main(void) {
//   initLED();
//   initTimer0();
//   initTimer1();
//   sei();

//   // Variables
//   uint8_t timer0Overflows = 0;

//   // Main Loop

//   while (1) {
//     if (timer0Overflown) {
//       timer0Overflows++;
//       timer0Overflown = false;
//     }

//     if (timer0Overflows / TIMER0_OVERFLOW_FOR_SECOND >= 1) {
//       LED_PORT ^= (1 << LED_2); // Toggle the LED
//       timer0Overflows = 0;
//     }
//   }
//   return 0;
// }

// // Functions
// void initTimer0(void) {
//   // 15,625 ticks per second
//   TCCR0B |= (1 << CS02); // 1024 prescaler
//   TIMSK0 |= (1 << TOIE0); // Enable overflow interrupt
// }

// void initTimer1(void) {
//   TCCR1B |= (1 << WGM12); // CTC Mode
//   TCCR1B |= (1 << CS12); // 256 prescaler
//   OCR1A = 31250; // Toggle every 0.5s = 1Hz blink
//   TIMSK1 |= (1 << OCIE1A); // Enable COMPA interrupt
// }

// void initLED(void) {
//   LED_DDR |= (1 << LED_1); // Output mode
//   LED_DDR |= (1 << LED_2); // Output mode
// }