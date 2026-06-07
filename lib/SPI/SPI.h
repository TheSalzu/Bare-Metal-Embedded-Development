#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

void SPI_transmit(uint8_t data);
uint8_t SPI_receive(void);

#endif