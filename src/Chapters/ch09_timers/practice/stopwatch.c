// // Definitions & Includes
// #include <avr/io.h>
// #include <util/delay.h>
// #include <avr/interrupt.h>
// #include "USART.h"
// #include <stdbool.h>
// #include <stdlib.h>

// #define TICKS_PER_OVERFLOW 65536 // 16 bit integer
// #define TICKS_PER_SECOND (16000000 / 1024) // 1024 prescaler at 16MHz

// #define BUTTON PD2
// #define BUTTON_DDR DDRD

// // Function Definitions
// void initTimer(void);
// void initButton(void);
// uint32_t getSecondsPassed(void);
// void printTimePassed(void);

// // Global Variables
// volatile uint8_t timerOverflows = 0;
// volatile bool buttonPressed = false;
// volatile uint16_t lastPressTime = 0;

// // Interrupts
// ISR(TIMER1_OVF_vect) {
//   timerOverflows++;
// }

// ISR(INT0_vect) {
//   const uint16_t now = TCNT1;
//   uint16_t timeSinceLastPress = now - lastPressTime;
//   if (timeSinceLastPress < TICKS_PER_SECOND) { // debounce - ignore within 1 second
//     return;
//   }

//   lastPressTime = now;
//   buttonPressed = true;
// }

// // Main Code
// int main(void) {
//   initTimer();
//   initUSART();
//   initButton();
//   sei();

//   // Variables
//   bool isCounting = false;

//   // Main Loop
//   while (1) {
//     if (!buttonPressed) {
//       continue;
//     }

//     printString("\r\n");
//     isCounting = !isCounting;
//     buttonPressed = false;

//     if (isCounting) {
//       TCNT1 = 0;          // clear current tick count
//       timerOverflows = 0; // clear overflow count
//       printString("---STOPWATCH STARTING---\r\n");
//     } else {
//       printTimePassed();
//     }
//   }
//   return 0;
// }

// // Functions
// void initButton(void) {
//   BUTTON_DDR &= ~(1 << BUTTON);  // Input mode
//   PORTD |= (1 << BUTTON);        // Enable pull up resistor

//   EICRA |= (1 << ISC01);         // Falling edge (on button press)
//   EIMSK |= (1 << INT0);          // Enable INT0 interrupt
// }

// void initTimer(void) {
//   TCCR1B |= (1 << CS12) | (1 << CS10); // 1024 prescaler
//   TIMSK1 |= (1 << TOIE1);              // Enable overflow interrupt
// }

// uint32_t getSecondsPassed(void) {
//   const uint16_t currentTickCount = TCNT1;
//   const uint32_t totalTicks = ((uint32_t)timerOverflows * TICKS_PER_OVERFLOW) + currentTickCount;
//   return totalTicks / TICKS_PER_SECOND;
// }

// void printTimePassed(void) {
//   const uint8_t secondsPassed = getSecondsPassed();
//   char secondsBuffer[4] = {0};
//   itoa(secondsPassed, secondsBuffer, 10); // convert int to string
//   printString(secondsBuffer);
//   printString(" seconds\r\n");
// }