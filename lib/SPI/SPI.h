#ifndef SPI_H
#define SPI_H

#define SPI_DDR DDRB
#define SPI_PORT PORTB 

#define SCK PB5
#define MOSI PB3
#define MISO PB4

#include <avr/io.h>

void initSPI();
void SPI_transmit(uint8_t data);
uint8_t SPI_receive(void);
void SPI_writeRegister(uint8_t address, uint8_t register, uint8_t data);

#endif