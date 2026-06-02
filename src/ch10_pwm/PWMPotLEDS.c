//                                            /* Quick and dirty PWM Demo */

// // ------- Preamble -------- //
// #include <avr/io.h>                        /* Defines pins, ports, etc */
// #include <util/delay.h>                     /* Functions to waste time */
// #include "analogRead.h"
// #include "USART.h"


// #define LED_MAX_DELAY  50                                  /* microseconds */
// #define LED_MIN_DELAY  5                                  /* microseconds */
// #define LED_PORT PORTB
// #define LED_DDR DDRB

// #define POT_PIN PD0

// // Functions
// void pwmAllPins(uint8_t brightness, uint8_t delay) {
//   LED_PORT = 0xff;                                          /* turn on */
//   for (uint8_t i = 0; i < 255; i++) {
//     if (i >= brightness) {            /* once it's been on long enough */
//       LED_PORT = 0;                                        /* turn off */
//     }

//     for (uint8_t i = 0; i < delay; i++) {
//       _delay_us(1);
//     }

//     // _delay_us(delay);
//   }
// }

// uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
//     if (in_max == in_min) {
//         return out_min; 
//     }
    
//     return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
// }

// int main(void) {
//   initADC();
//   initUSART();

//   uint8_t brightness = 0;
//   int8_t direction = 1;

//   // -------- Inits --------- //

//   // Init all LEDs
//   LED_DDR = 0xff;
//   // ------ Event loop ------ //
//   while (1) {
//     uint16_t potValue = readADC(POT_PIN);
//     uint8_t delay = map(potValue, 0, 1023, LED_MIN_DELAY, LED_MAX_DELAY);
    
//     // Brighten and dim
//     if (brightness == 0) {
//       direction = 1;
//     }
//     if (brightness == 255) {
//       direction = -1;
//     }
//     brightness += direction;
//     pwmAllPins(brightness, delay);


//   }                                                  /* End event loop */
//   return 0;                            /* This line is never reached */
// }
