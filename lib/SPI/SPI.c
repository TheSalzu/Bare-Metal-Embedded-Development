#include "SPI.h"

void SPI_transmit(uint8_t data) {
  SPDR = data;
  while (!(SPSR & (1 << SPIF))); // wait until transmission is complete
}

uint8_t SPI_receive(void) {
  SPI_transmit(0x00); // send 8 bits of useless to data to get the 8 bis of their data back
  return SPDR;
}