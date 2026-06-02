// Definitions & Includes
#include <avr/io.h>
#include "analogRead.h"
#include "hal.h"

#define PULSE_MIN 2000 
#define PULSE_MID 3000
#define PULSE_MAX 4000

#define SERVO PB1
#define SERVO_DDR DDRB

#define POT PC0

// Function Definitions
void initTimer(void);

// Main Code
int main(void) {
  initTimer();
  initADC();

  OCR1A = PULSE_MID; // start at center position

  // Main Loop
  while (1) {
    const uint16_t potValue = readADC(POT);
    OCR1A = map(potValue, ANALOG_MIN, ANALOG_MAX, PULSE_MIN, PULSE_MAX);
  }

  return 0;
}

// Functions
void initTimer(void) {
  TCCR1A |= (1 << COM1A1);               // Non-inverting PWM
  TCCR1A |= (1 << WGM11);                // Fast PWM part (1st bit needed)
  TCCR1B |= (1 << WGM13) | (1 << WGM12); // Fast PWM with ICR1 as TOP (last 2 bits needed)
  TCCR1B |= (1 << CS11);                 // /8 prescaler for the most definition
  ICR1 = 40000;                          // 20ms, 50hz per cycle

  SERVO_DDR |= (1 << SERVO); // Set servo pin to output
}