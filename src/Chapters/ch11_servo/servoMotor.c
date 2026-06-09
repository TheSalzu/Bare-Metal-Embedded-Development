// /* Quick interactive demo running servo with Timer 1 */
// // ------- Preamble -------- //
// #include <avr/io.h>
// #include <util/delay.h>
// #include <avr/interrupt.h>
// #include "pinDefines.h"
// #include "analogRead.h"
// #include "USART.h"
// #include "stdlib.h"

// #define PULSE_MIN  2000   // 2000 * 0.5us = 1ms
// #define PULSE_MAX  4000   // 4000 * 0.5us = 2ms
// #define PULSE_MID  3000   // 3000 * 0.5us = 1.5ms

// static inline void initTimer1Servo(void) {
//                    /* Set up Timer1 (16bit) to give a pulse every 20ms */
//                              /* Use Fast PWM mode, counter max in ICR1 */
//   TCCR1A |= (1 << WGM11);
//   TCCR1B |= (1 << WGM12) | (1 << WGM13);
//   TCCR1B |= (1 << CS11);               /* /8 prescaling -- 0.5us per tick at 16MHz */
//   ICR1 = 40000;                                          /* TOP value = 20ms */
//   TCCR1A |= (1 << COM1A1);                   /* Direct output on PB1 / OC1A */
//   DDRB |= (1 << PB1);                                 /* set pin for output */
// }

// uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max) {
//     if (in_max == in_min) {
//         return out_min; 
//     }
    
//     return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
// }

// int main(void) {
//   // -------- Inits --------- //
//   OCR1A = PULSE_MID;                       /* set it to middle position initially */
//   initTimer1Servo();
//   initADC();  
//   initUSART();
  

//   // ------ Event loop ------ //
//   while (1) {
//     const uint32_t potValue = readADC(PC0);
//     OCR1A = map(potValue, 0, 1023, PULSE_MIN, PULSE_MAX);
//   }                                                       /* End event loop */
//   return 0;                                   /* This line is never reached */
// }