#ifndef DOT_MATRIX_H
#define DOT_MATRIX_H

#define SCK PB5
#define MOSI PB3
#define SS PB2

#include <avr/pgmspace.h>
#include <avr/io.h>
#include "SPI.h"

#define NORMAL_OPERATION_MODE    0x00
#define MATRIX_MODE              0x00
#define ALL_DIGITS               0x00
#define LOWEST_BRIGHTNESS_MODE    0x00

#define DECODE_MODE_REGISTER     0x09
#define INTENSITY_REGISTER       0x0A
#define SCAN_LIMIT_REGISTER      0x0B
#define SHUTDOWN_REGISTER        0x0C
#define DISPLAY_TEST_REGISTER    0x0F

// Functions
void initMax7219();
void spiTransmitMax7219(uint8_t address, uint8_t data);
void max7219DisplayNumber(uint8_t number);
#endif