#include "I2C.h"

#define SDA PC4
#define SCL PC5
#define I2C_PORT PORTC

void initI2C() {
  I2C_PORT |= ((1 << SDA) | (1 << SCL)); // internal pull-up resitors
  TWBR = 72; // 100khz speed
  TWCR |= (1 << TWEN);
}

void i2cWaitForComplete(void) {
  while ( !(TWCR & (1 << TWINT)) ) {}; // Waits until TWINT flag is one
}

void i2cStart(void) {
  // TWEN keeps it enabled, TWSTA is start bit, TWINT clears the flag
  TWCR = (1 << TWEN) | (1 << TWSTA) | (1 << TWINT);
  i2cWaitForComplete();
}

void i2cStop(void) {
  // TWEN keeps it enabled, TWST0 is start bit, TWINT clears the flag
  TWCR = (1 << TWEN) | (1 << TWSTO) | (1 << TWINT);
}

void i2cSend(uint8_t data) {
  TWDR = data; // dump our data
  TWCR = (1 << TWINT) | (1 << TWEN); // Enable and clear flag
  i2cWaitForComplete();
}

// Read and continue
uint8_t i2cReadAck(void) {
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // Enable and clear flag and make sure we sent a continue bit
  i2cWaitForComplete();
  return (TWDR); // return the data
}

// Read and stop
uint8_t i2cReadNoAck(void) {
  TWCR = (1 << TWINT) | (1 << TWEN); // Enable and clear flag
  i2cWaitForComplete();
  return (TWDR); // return the data
}

// Helper Functions to reduce code amount
uint8_t readRegister(uint8_t deviceAddress, uint8_t registerAddress) {
  i2cStart();
  i2cSend(deviceAddress << 1); // Write mode
  i2cSend(registerAddress); // Write to the address we're talking to

  i2cStart(); // Start again in read mode
  i2cSend((deviceAddress << 1) | 1); // Tell i2c we're reading this time
  uint8_t data = i2cReadNoAck(); // Read data and stop
  i2cStop();

  return data;
}

void writeRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data) {
  i2cStart();
  i2cSend(deviceAddress << 1); // Write mode
  i2cSend(registerAddress); // Write to the address we're talking to
  i2cSend(data);// Send Data
  i2cStop();
}