#ifndef SPI_H
#define SPI_H
#define SPI_DDR DDRB
#define SPI_PORT PORTB 

#include <avr/io.h>

void initSPI();
void SPI_transmit(uint8_t data);
uint8_t SPI_receive(void);

#endif