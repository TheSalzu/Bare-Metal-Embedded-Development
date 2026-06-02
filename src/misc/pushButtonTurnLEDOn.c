// // Includes
// #include <avr/io.h>
// #include <util/delay.h>
// #include "USART.h"

  // #define LED_DDR DDRB
  // #define LED_PORT PORTB

// #define BUTTON_DDR DDRD
// #define BUTTON_PORT PORTD
// #define BUTTON_PIN PIND

// // Main Loop
// int main(void) {
//     // Setup
//     BUTTON_DDR &= ~(1 << PD2); // This makes the button into input mode
//     BUTTON_PORT |= (1 << PD2); // This sets the internal pull up resistor
//     LED_DDR |= (1 << PB0); // Set the pinmode to output

//     uint8_t debounceByte = 0xFF;
//     // uint8_t realByte = (uint8_t)(0xFF << BUTTON_CONFIDENCE_LEVEL);
//     // printBinaryByte(realByte);

//     initUSART();

//     // Main Loop
//     while (1) {
//         debounceByte = (debounceByte << 1) | ((BUTTON_PIN >> PD2) & 1);
        
//     if (debounceByte == 0b11100000) {
//             LED_PORT ^= (1 << PB0); // Set the bit to 0
//             printString("Button is held\r\n");
//         } else {
//             // printString("Button is not held\r\n");
//             printBinaryByte(debounceByte);
//             printString("\r\n");
//         }
//     }

//     return 0;
// }