// // Includes
// #include <avr/io.h>
// #include <util/delay.h>
// #include "I2C.h"
// #include "RealTimeClock.h"
// #include "USART.h"

// // Main Code
// int main(void) {
//   // Initalizations
//   initI2C();
//   initUSART();
//   initRTC_SQWE_MODE(ONE_HZ);
//   setHourMode(TWELVE_HOURS);

//   while (1) {
//     printWord(readClockDate());
//     printString("\r\n");
//     _delay_ms(250);
//   }

//   return 0;
// }