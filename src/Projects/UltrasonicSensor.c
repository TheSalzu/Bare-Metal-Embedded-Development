// // Includes
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include "USART.h"
// #include <avr/delay.h>

// // Definitions
// #define TRIGGER PD7
// #define TRIGGER_DDR DDRD
// #define TRIGGER_PORT PORTD

// #define ECHO PD2
// #define ECHO_PIN PIND
// #define ECHO_DDR DDRD

// // Function Definitions
// void initINT0Interrupt();
// void initTimer0();
// void initTimer1();
// void triggerPulse();

// // Enums
// typedef enum {
//   IDLE,
//   TRIGGERING,
//   WAITING_FOR_ECHO,
//   ECHO_RECEIVED
// } SensorState;

// // Global Variables
// volatile uint16_t triggerStartTime = 0;
// volatile uint16_t travelTime = 0;
// volatile SensorState state = IDLE;

// // Main Code
// int main(void) {
//   // Pin Configurations
//   TRIGGER_DDR |= (1 << TRIGGER); // Output mode
//   ECHO_DDR &= ~(1 << ECHO); // Input Mode

//   // Initalizations
//   initINT0Interrupt();
//   initTimer0();
//   initTimer1();
//   initUSART();

//   sei();

//   while (1) {
//     triggerPulse();

//     if (state == ECHO_RECEIVED) {
//       state = IDLE;

//       const uint16_t distanceCM = travelTime / 116;

//       printString("Distance Travelled: ");
//       printWord(distanceCM);
//       printString(" CM");
//       printString("\r\n");
//     }

//     _delay_ms(60);
//   }

//   return 0;
// }

// // Functions
// void initINT0Interrupt() {
//   EICRA |= (1 << ISC00); // Detect any logic chance 
//   EIMSK |= (1 << INT0);
// }

// void initTimer0() {
//   TCCR0A |= (1 << WGM01); // Compare match mode
//   OCR0A = 20; // 10 microsceonds
// }

// // Used to track time between pulses
// void initTimer1() {
//   TCCR1A = 0;
//   TCCR1B |= (1 << CS11); // 8 Prescaler
// }

// void triggerPulse() {
//   if (state != IDLE) {
//     return;
//   }

//   state = TRIGGERING;
//   TRIGGER_PORT |= (1 << TRIGGER); // Set the pin high
//   TCNT0 = 0; // Reset the timer's clock
//   TIMSK0 |= (1 << OCIE0A); // Enable the interrupt
//   TCCR0B |= (1 << CS01); // 8 Prescaler (start the timer)
// }

// // Interrupts

// // Triggers when 10 microseconds have passed
// ISR(TIMER0_COMPA_vect) {
//   TRIGGER_PORT &= ~(1 << TRIGGER); // Set the pin low
//   TIMSK0 &= ~(1 << OCIE0A); // Disable the interrupt
//   TCCR0B &= ~(1 << CS01); // disable the timer
// }

// // Triggers when the pin goes high/low
// ISR(INT0_vect) {
//   // The trigger has started
//   if (PIND & (1 << ECHO)) {
//     triggerStartTime = TCNT1;
//     state = WAITING_FOR_ECHO;
//   } else {
//     // Trigger has ended
//     travelTime = TCNT1 - triggerStartTime;
//     state = ECHO_RECEIVED;
//   }
// }