#include "Bmp280I2C.h"

// Macros
#define COMBINE_U16(h, l) ((uint16_t)(((uint16_t)(h) << 8) | (uint8_t)(l)))
#define COMBINE_I16(h, l) ((int16_t) (((uint16_t)(h) << 8) | (uint8_t)(l)))

// Global Variables
static uint16_t i2cDigT1 = 0;
static int16_t i2cDigT2 = 0;
static int16_t i2cDigT3 = 0;
static int32_t i2cTFine = 0;

static uint16_t i2cDigP1 = 0;
static int16_t i2cDigP2 = 0;
static int16_t i2cDigP3 = 0;
static int16_t i2cDigP4 = 0;
static int16_t i2cDigP5 = 0;
static int16_t i2cDigP6 = 0;
static int16_t i2cDigP7 = 0;
static int16_t i2cDigP8 = 0;
static int16_t i2cDigP9 = 0;

// Private Functions

// I have no fucking clue how these work I just I just plug in a ADC  value
// This gets barometic pressure (divide by 256)
static uint32_t bmp280I2CCompensateP(int32_t adcP) {
  int64_t var1, var2, p;
  
  var1 = ((int64_t)i2cTFine) - 128000;
  var2 = var1 * var1 * (int64_t)i2cDigP6;
  var2 = var2 + ((var1 * (int64_t)i2cDigP5) << 17);
  var2 = var2 + (((int64_t)i2cDigP4) << 35);
  var1 = ((var1 * var1 * (int64_t)i2cDigP3) >> 8) + ((var1 * (int64_t)i2cDigP2) << 12);
  var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)i2cDigP1) >> 33;
  
  if (var1 == 0) {
      return 0; // avoid exception caused by division by zero
  }
  
  p = 1048576 - adcP;
  p = (((p << 31) - var2) * 3125) / var1;
  var1 = (((int64_t)i2cDigP9) * (p >> 13) * (p >> 13)) >> 25;
  var2 = (((int64_t)i2cDigP8) * p) >> 19;
  p = ((p + var1 + var2) >> 8) + (((int64_t)i2cDigP7) << 4);
  
  return (uint32_t)p; // Returns pressure in Pascals
}

// T is temperature in celcius (divide by 100)
static int32_t bmp280I2CCompensateT(int32_t adcT) {
  int32_t var1, var2, T;
  
  var1 = ((((adcT >> 3) - ((int32_t)i2cDigT1 << 1))) * ((int32_t)i2cDigT2)) >> 11;
  var2 = (((((adcT >> 4) - ((int32_t)i2cDigT1)) * ((adcT >> 4) - ((int32_t)i2cDigT1))) >> 12) * ((int32_t)i2cDigT3)) >> 14;  
  i2cTFine = var1 + var2;
  T = (i2cTFine * 5 + 128) >> 8;
  
  return T; 
}

static int32_t bmp280I2CReadADCTemperature() {
  i2cStart();
  i2cSend(BMP_ADDRESS << 1); // Write mode
  i2cSend(TEMP_MSB); // Reading this register

  i2cStart(); // Repeated start for read mode
  i2cSend((BMP_ADDRESS << 1) | 1); // read mode

  // Burst read cos the datasheet reccomends that
  const uint8_t tempMSB = i2cReadAck();
  const uint8_t tempLSB = i2cReadAck();
  const uint8_t tempXLSB = i2cReadNoAck();
  i2cStop();

  const int32_t finalTemperature = (((int32_t)tempMSB << 12) |
                                   ((int32_t)tempLSB << 4)   |
                                   ((int32_t)tempXLSB >> 4));
  

  return finalTemperature;
}

static int32_t bmp280I2CReadADCPressure() {
  i2cStart();
  i2cSend(BMP_ADDRESS << 1); // Write mode
  i2cSend(PRESSURE_MSB); // Reading this register

  i2cStart(); // Repeated start for read mode
  i2cSend((BMP_ADDRESS << 1) | 1); // read mode

  // Burst read cos the datasheet reccomends that
  const uint8_t pressureMSB = i2cReadAck();
  const uint8_t pressureLSB = i2cReadAck();
  const uint8_t pressureXLSB = i2cReadNoAck();
  i2cStop();

  const int32_t finalPressure = (((int32_t)pressureMSB << 12) |
                                   ((int32_t)pressureLSB << 4)   |
                                   ((int32_t)pressureXLSB >> 4));
  

  return finalPressure;
}

static void bmp280I2CReadAllCalibrationData() {
  uint8_t buffer[24]; // 24 bytes total (6 for Temp, 18 for Pressure)

  i2cStart();
  i2cSend(BMP_ADDRESS << 1); // Write mode
  i2cSend(CALIBRATION_REGISTER);
  
  i2cStart(); // Repeated start for read mode
  i2cSend((BMP_ADDRESS << 1) | 1);

  for (uint8_t i = 0; i < 23; i++) {
    buffer[i] = i2cReadAck();
  }

  // Read last byte with no ack
  buffer[23] = i2cReadNoAck();
  i2cStop();

  // Temperature Constants
  i2cDigT1 = COMBINE_U16(buffer[1], buffer[0]);
  i2cDigT2 = COMBINE_I16(buffer[3], buffer[2]);
  i2cDigT3 = COMBINE_I16(buffer[5], buffer[4]);
  
  // Pressure Constants (Starts at 6)
  i2cDigP1 = COMBINE_U16(buffer[7],  buffer[6]);
  i2cDigP2 = COMBINE_I16(buffer[9],  buffer[8]);
  i2cDigP3 = COMBINE_I16(buffer[11], buffer[10]);
  i2cDigP4 = COMBINE_I16(buffer[13], buffer[12]);
  i2cDigP5 = COMBINE_I16(buffer[15], buffer[14]);
  i2cDigP6 = COMBINE_I16(buffer[17], buffer[16]);
  i2cDigP7 = COMBINE_I16(buffer[19], buffer[18]);
  i2cDigP8 = COMBINE_I16(buffer[21], buffer[20]);
  i2cDigP9 = COMBINE_I16(buffer[23], buffer[22]);
}

// Public Functions
void initBmp280I2C() {
  const uint8_t controlRegister = PRESSURE_16x | TEMPERATURE_2x | NORMAL_MODE; // 2x temp oversampling, 16x pressure
  const uint8_t configRegister = STANDBY_1000ms | FILTER_4x; // 1 second delay in reads, 4x filter

  writeRegister(BMP_ADDRESS, CONTROL_REGISTER, controlRegister);
  writeRegister(BMP_ADDRESS, CONFIG_REGISTER, configRegister);
  bmp280I2CReadAllCalibrationData();
}

// No floats
int8_t readTemperatureCI2C() {
  const int32_t rawTemperature = bmp280I2CReadADCTemperature();
  const int32_t convertedTemp = bmp280I2CCompensateT(rawTemperature); // Only like 12 bits are used
  return (int8_t)(convertedTemp / 100); // Drop the decimal
}

uint16_t readBarometricPressureI2C() {
  const int32_t rawPressure = bmp280I2CReadADCPressure();
  const int32_t convertedPressure = bmp280I2CCompensateP(rawPressure);
  return (uint16_t)(convertedPressure / 25600);
}

// In meters
int16_t calculateAltitudeI2C(uint16_t pressureHpa) {
  int32_t currentPressurePa = (uint32_t)pressureHpa * 100;
  int32_t seaLevelPressurePa = 101325; 
  return  ((seaLevelPressurePa - currentPressurePa) * 843) / 10000;
}
