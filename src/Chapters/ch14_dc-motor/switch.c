// // Includes/Definitions
// #include <avr/io.h>
// #include <util/delay.h>

// #define SWITCH PD6
// #define SWITCH_DDR DDRD
// #define SWITCH_PORT PORTD

// // This was more so a hardware thing. I connected up a transitor with a diode to run a motor

// int main(void) {

//   SWITCH_DDR |= (1 << SWITCH); // Output mode

//   while (1) {
//     SWITCH_PORT |= (1 << SWITCH);
//     _delay_ms(1000);
//     SWITCH_PORT &= ~(1 << SWITCH);
//     _delay_ms(1000);
//   }

//   return 0;
// }