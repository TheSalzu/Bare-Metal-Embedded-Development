// // Includes/Refs
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include "USART.h"
// #include <stdbool.h>
// #include "avr/delay.h"

// // Global Variables
// volatile bool movementDetected = false;

// // Interrupts
// ISR(INT0_vect) {
//   if (PIND & (1 << PD2)) {
//     movementDetected = true;
//     PORTB = 0xff;
//   } else {
//     movementDetected = false;
//     PORTB = 0;
//   }
// }

// // Function Definitions
// void initINT0(void);

// // Main Code
// int main(void) {
//   DDRB |= (1 << PB0);

//   DDRD &= ~(1 << PD2);
//   PORTD &= ~(1 << PD2);

//   initINT0();
//   initUSART();


//   // Variables
//   uint8_t previousState = 0;

//   while (1) {
//     const uint8_t currentState = PIND & (1 << PD2);

//     if (currentState != previousState) {
//       previousState = currentState;
//       printString("STATE CHANGED!\r\n");
//     }

//     if (movementDetected) {
//       printString("Movement detected!\r\n");
//     } else {
//       printString("No movement detected!\r\n");
//     }

//     _delay_ms(500);
//   }

//   return 0;
// }

// void initINT0(void) {
//   EICRA |= (1 << ISC00);   // trigger on any change
//   EIMSK |= (1 << INT0);    // enable INT0

//   sei();                   // enable interrupts globally
// }