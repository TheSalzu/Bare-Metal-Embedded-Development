// // Includes/Defintions
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>

// #define FORWARD 1
// #define BACKWARD -1
// #define STEPS 2048

// #define MAX_DELAY  255
// #define MIN_DELAY 12
// #define ACCELERATION  16          /* lower = smoother but slower accel */

// #define RAMP_STEPS (MAX_DELAY - MIN_DELAY) / ACCELERATION

// // Function Declarations
// void initTimer0();
// void takeSteps(uint16_t amountOfSteps, uint8_t stepSpeed);
// void trapezoidMove(int16_t howManySteps);

// // Global Variables
// const uint8_t stepperMap[] = {
//   (1 << PB0),
//   (1 << PB0) | (1 << PB1),
//   (1 << PB1),
//   (1 << PB1) | (1 << PB2),
//   (1 << PB2),
//   (1 << PB2) | (1 << PB3),
//   (1 << PB3),
//   (1 << PB0) | (1 << PB3),
// };

// volatile uint16_t currentStepCount = 0;
// volatile uint8_t currentStepIndex = 0;
// volatile int8_t direction = FORWARD;

// // Interrupts
// ISR(TIMER0_COMPA_vect) {
//   currentStepIndex = (currentStepIndex + direction) & 0x07;
//   PORTB = stepperMap[currentStepIndex];
//   currentStepCount++;
// }

// // Main Code
// int main(void) {
//   initTimer0();

//   // Port Configuration
//   DDRB = 0b00001111;

//   while (1) {
//     trapezoidMove(2 * STEPS);                         /* two full turns */
//     trapezoidMove(-STEPS / 2);                             /* half turn */
//     trapezoidMove(STEPS / 4);                           /* quarter turn */
//     trapezoidMove(-STEPS / 8);                                /* eighth turn */
//     _delay_ms(500);
//     trapezoidMove(-STEPS / 4);                         /* the other way */
//     trapezoidMove(STEPS / 8);
//     trapezoidMove(STEPS / 2);                /* half turn back to start */
//     trapezoidMove(-2 * STEPS);                         /* two full turns */
//     _delay_ms(1000);
//   }

//   return 0;
// }

// // Functions
// void initTimer0() {
//   TCCR0A |= (1 << WGM01); // CTC Mode
//   TCCR0B |= (1 << CS02) | (1 << CS00); // 1024 prescaler
//   OCR0A = MAX_DELAY; // Default speed to slowest speed
//   sei();
// }

// void takeSteps(uint16_t amountOfSteps, uint8_t stepSpeed) {
//   if (stepSpeed < MIN_DELAY) {
//     stepSpeed = MIN_DELAY;
//   }

//   OCR0A = stepSpeed; // Set Speed
//   TIMSK0 |= (1 << OCIE0A); // Enable interrupt
//   currentStepCount = 0;
//   while (currentStepCount < amountOfSteps); // Wait until stepper takes current steps
//   TIMSK0 &= ~(1 << OCIE0A); // Enable interrupt
// }

// void trapezoidMove(int16_t howManySteps) {
//   uint8_t delay = MAX_DELAY;
//   uint16_t stepsTaken = 0;

//   if (howManySteps > 0) {
//     direction = FORWARD;
//   }
//   else {
//     direction = BACKWARD;
//     howManySteps = -howManySteps;
//   }

//   if (howManySteps > (RAMP_STEPS * 2)) {
//     while (stepsTaken < RAMP_STEPS) {
//       takeSteps(1, delay);
//       delay -= ACCELERATION;
//       stepsTaken++;
//     }

//     // Cruising
//     delay = MIN_DELAY;
//     takeSteps((howManySteps - 2 * RAMP_STEPS), delay);
//     stepsTaken += (howManySteps - 2 * RAMP_STEPS);

//     // Deacceleration
//     while (stepsTaken < howManySteps) {
//       takeSteps(1, delay);
//       delay += ACCELERATION;
//       stepsTaken++;
//     }
//   }
//   else {
//     // Triangle ramp up
//     while (stepsTaken <= howManySteps / 2) {
//       takeSteps(1, delay);
//       delay -= ACCELERATION;
//       stepsTaken++;
//     }
//     delay += ACCELERATION;
//     while (stepsTaken < howManySteps) {
//       takeSteps(1, delay);
//       delay += ACCELERATION;
//       stepsTaken++;
//     }
//   }
// }