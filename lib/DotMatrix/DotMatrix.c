#include "DotMatrix.h"

// Constants
const uint8_t numbersArray[10][8] PROGMEM = {
  {0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, 0x00}, // 0
  {0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00, 0x00}, // 1
  {0x00, 0x42, 0x61, 0x51, 0x49, 0x46, 0x00, 0x00}, // 2
  {0x00, 0x21, 0x41, 0x45, 0x4B, 0x31, 0x00, 0x00}, // 3
  {0x00, 0x18, 0x14, 0x12, 0x7F, 0x10, 0x00, 0x00}, // 4
  {0x00, 0x27, 0x45, 0x45, 0x45, 0x39, 0x00, 0x00}, // 5
  {0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00, 0x00}, // 6
  {0x00, 0x01, 0x71, 0x09, 0x05, 0x03, 0x00, 0x00}, // 7
  {0x00, 0x36, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00}, // 8
  {0x00, 0x06, 0x49, 0x49, 0x29, 0x1E, 0x00, 0x00}  // 9
};

// Private Functions
void max7219ClearDisplay(void) {
  // Loop through all 8 column registers (0x01 through 0x08)
  for (uint8_t col = 1; col <= 8; col++) {
    spiTransmitMax7219(col, 0x00); // Write 0 to turn off all 8 rows in this column
  }
}

// Public Functions
void spiTransmitMax7219(uint8_t address, uint8_t data) {
  SPI_PORT &= ~(1 << SS); // Pull low
  SPI_transmit(address);
  SPI_transmit(data);
  SPI_PORT |= (1 << SS); // Pullh igh
}

void max7219DisplayNumber(uint8_t number) {
  if (number > 9) {
    return;
  }

  for (uint8_t i = 0; i < 8; i++) {
    const uint8_t address = i + 1;
    const uint8_t* dataAddress = &numbersArray[number][i];
    const uint8_t data = pgm_read_byte(dataAddress);
    spiTransmitMax7219(address, data);
  }
}

void initMax7219() {
  spiTransmitMax7219(DISPLAY_TEST_REGISTER, NORMAL_OPERATION_MODE); // Also enables the device
  spiTransmitMax7219(SCAN_LIMIT_REGISTER, 0x07); // We want all the digits
  spiTransmitMax7219(DECODE_MODE_REGISTER, MATRIX_MODE); // Only use matrix mode on the dot matrix since I don't have seven connected
  spiTransmitMax7219(INTENSITY_REGISTER, 0x00); // Brightness
  spiTransmitMax7219(SHUTDOWN_REGISTER, 0x01); // Enables the device

  max7219ClearDisplay();
}