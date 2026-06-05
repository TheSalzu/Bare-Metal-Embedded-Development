// Includes/Defintions
#include <avr/io.h>
#include <avr/interrupt.h>
#include "hal.h"
#include <util/delay.h>

#define PWM_PIN PD6
#define PWM_DDR DDRD

#define POT PC0
#define MOTOR_RAMP_TIME 5

#define CONTROL_PIN_1 PB0
#define CONTROL_PIN_2 PB1
#define CONTROL_DDRB DDRB
#define CONTROL_PORT PORTB

// Function Declarations
void changeDirection(uint8_t dir1, uint8_t dir2);
void initPWMTimer();
void initRampTimer();
void initADC();
uint16_t readADC();

// Global Variables
volatile uint8_t targetSpeed = 0;

// Interrupts
ISR(TIMER2_COMPA_vect) {
  if (OCR0A != targetSpeed) {
    OCR0A += (targetSpeed > OCR0A) ? 1 : -1;
  }
}

// Main Code
int main(void) {
  initPWMTimer();
  initRampTimer();
  initADC();
  sei();

  // Pin Configuraition
  PWM_DDR |= (1 << PWM_PIN); // Output Pin
  CONTROL_DDRB |= (1 << CONTROL_PIN_1) | (1 << CONTROL_PIN_2); // Output Pin

  changeDirection(1, 0);

  while (1) {
    const uint16_t potValue = readADC(POT);
    const uint8_t mappedPotValue = map(potValue, 0, 1023, 0, 255);
    targetSpeed = mappedPotValue;    
  }

  return 0;
}

// Functions
void changeDirection(uint8_t dir1, uint8_t dir2) {
  CONTROL_PORT &= ~((1 << CONTROL_PIN_1) | (1 << CONTROL_PIN_2)); // clear both
  CONTROL_PORT |= (dir1 << CONTROL_PIN_1) | (dir2 << CONTROL_PIN_2); // set new
}

void initPWMTimer() {
  // No prescaler because 16mil divided by 256 is 62k hz which is plenty for the motor
  TCCR0A |= (1 << COM0A1); // Non inverting mode
  TCCR0A |= (1 << WGM01) | (1 << WGM00); // Fast PWM
  TCCR0B |= (1 << CS00); // start the prescaler with no divison
}

void initRampTimer() {
  TCCR2A |= (1 << WGM21); // CTC mode
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // 1024 prescaler
  TIMSK2 |= (1 << OCIE2A); // enable interrupt on compare match
  OCR2A = 15; // fires rougly 976 times per second
}

void initADC() {
  ADMUX |= (1 << REFS0); // 5v reference voltage
  ADMUX = (ADMUX & 0xf0) | POT; // Set the multiplexer to our pot pin
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescaler 
  ADCSRA |= (1 << ADEN); // Enable ADC conversions
}

uint16_t readADC() {
  ADCSRA |= (1 << ADSC); // Start the conversion
  while (ADCSRA & (1 << ADSC)) {}; // Yield until the conversion is done
  return ADC;
}