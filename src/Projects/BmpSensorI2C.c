// // Includes
// #include <avr/io.h>
// #include <util/delay.h>
// #include "Bmp280I2C.h"
// #include "I2C.h"
// #include "USART.h"

// // Global Variables
// int8_t celsius = 0;
// int8_t fahrenheit = 0;
// int16_t pressure = 0;

// // Function Definitions
// void updateReadings(); // Only call once a second

// int main() {
//   // Initalizations
//   initI2C();
//   initUSART();
//   initBmp280I2C();


//   while (1) {
//     updateReadings();

//     printString("Celsius: ");
//     printWord(celsius);
//     printString("\r\n");

//     printString("Fahrenheit: ");
//     printWord(fahrenheit);
//     printString("\r\n");

//     printString("Pressure: ");
//     printWord(pressure);
//     printString("\r\n");

//     _delay_ms(1000);
//   }

//   return 0;
// }

// // Functions
// void updateReadings() {  
//   const uint8_t newCelsius = readTemperatureCI2C();
//   pressure = readBarometricPressureI2C();
//   celsius = newCelsius;
//   fahrenheit = (((newCelsius * 9) + 2) / 5) + 32;
// }