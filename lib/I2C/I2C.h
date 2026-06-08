// Functions for i2c communication
#include <avr/io.h>
#include "pinDefines.h"

void initI2C(void);

void i2cWaitForComplete(void);

void i2cStart(void);

void i2cStop(void);

void i2cSend(uint8_t data);

uint8_t i2cReadAck(void);

uint8_t i2cReadNoAck(void);

uint8_t readRegister(uint8_t deviceAddress, uint8_t registerAddress);

void writeRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data);