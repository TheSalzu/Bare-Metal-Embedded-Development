#ifndef BMP_280_I2C
#define BMP_280_I2C

// Defines
#define BMP_ADDRESS          0x76 // Used for talking to i2c
#define CONTROL_REGISTER     0xF4 // Mode, Temp, and Oversampling settings
#define CONFIG_REGISTER      0xF5 // IIR Filter
#define CALIBRATION_REGISTER 0x88

// Temperature Reading Bits
#define TEMP_MSB        0xFA 
#define TEMP_LSB        0xFB
#define TEMP_XLSB       0xFC

// Pressure Reading Bits
#define PRESSURE_MSB    0xF7
#define PRESSURE_LSB    0xF8
#define PRESSURE_XLSB   0xF9

// Mode Settings (Bits 1:0)
#define SLEEP_MODE      0x00
#define FORCED_MODE     0x01
#define NORMAL_MODE     0x03

// Temperature Oversampling Settings (Bits 7:5)
#define TEMPERATURE_OFF 0x20
#define TEMPERATURE_1x  0x20
#define TEMPERATURE_2x  0x40

// Pressure Oversampling settings (Bits 4:2)
#define PRESSURE_OFF    0x04 
#define PRESSURE_1x     0x04 
#define PRESSURE_2x     0x08 
#define PRESSURE_4x     0x0C
#define PRESSURE_8x     0x10
#define PRESSURE_16x    0x14 

// IIR Filter Settings (Bits 4:2)
#define FILTER_OFF      0x00 
#define FILTER_2x       0x04 
#define FILTER_4x       0x08 
#define FILTER_8x       0x0C
#define FILTER_16x      0x10

// Standby Time Settings (Bits 7:5)
#define STANDBY_0_5ms   0x00
#define STANDBY_62_5ms  0x20
#define STANDBY_125ms   0x40
#define STANDBY_250ms   0x60
#define STANDBY_500ms   0x80
#define STANDBY_1000ms  0xC0
#define STANDBY_2000ms  0xE0

// Includes
#include <stdint.h>
#include "I2C.h"

// Functions
void initBmp280I2C();
int8_t readTemperatureCI2C();
uint16_t readBarometricPressureI2C();
int16_t calculateAltitudeI2C(uint16_t pressureHpa);

#endif
