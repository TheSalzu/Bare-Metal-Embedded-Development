// Includes
#include <avr/io.h>
#include <avr/delay.h>
#include "SPI.h"
#include "DotMatrix.h"
#include "RealTimeClock.h"
#include "I2C.h"
#include "USART.h"

// Function Definitions
uint8_t getRightmostDigit(uint8_t number);

// Main Code
int main(void) {
  // Pin Configuration
  SPI_DDR |= (1 << SCK) | (1 << MOSI) | (1 << SS);
  SPI_PORT |= (1 << SS); // Force the pin high

  // Initalizations
  initSPI();
  initI2C();
  initUSART();
  initMax7219();
  initRTC();

  while (1) {
    uint8_t seconds = readClockSeconds();
    max7219DisplayNumber(getRightmostDigit(seconds));
    _delay_ms(500);
  }

  return 0;
}

// Functions
uint8_t getRightmostDigit(uint8_t number) {
  if (number == 0) {
    return 0;
  } else if (number <= 9) {
    return number;
  }

  return number % 10;
}