// Includes
#include <avr/io.h>
#include <util/delay.h>
#include "Bmp280SPI.h"
#include "SPI.h"
#include "USART.h"

// Defines
#define SS PB2
#define SS_PORT PORTB
#define SS_DDR DDRB

// Global Variables
int8_t celsius = 0;
int8_t fahrenheit = 0;
int16_t pressure = 0;

// Function Definitions
void updateReadings(); // Only call once a second

int main() {
  SPI_DDR |= (1 << SCK) | (1 << MOSI); // All outputs
  SPI_DDR &= ~(1 << MISO); // Input
  
  SS_DDR |= (1 << SS); // Output
  SS_PORT |= (1 << SS); // Pull the pin high

  // Initalizations
  initSPI();
  initUSART();
  initBmp280SPI(SS, &SS_PORT);

  while (1) {
    updateReadings();

    printString("Celsius: ");
    printWord(celsius);
    printString("\r\n");

    printString("Fahrenheit: ");
    printWord(fahrenheit);
    printString("\r\n");

    printString("Pressure: ");
    printWord(pressure);
    printString("\r\n");

    _delay_ms(1000);
  }

  return 0;
}

// Functions
void updateReadings() {  
  const uint8_t newCelsius = readTemperatureCSPI();
  pressure = readBarometricPressureSPI();
  celsius = newCelsius;
  fahrenheit = (((newCelsius * 9) + 2) / 5) + 32;
}