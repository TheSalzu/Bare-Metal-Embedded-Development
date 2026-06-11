#include "Bmp280SPI.h"

// Definitions
#define BIT_7 (1 << 7)

// Macros
#define COMBINE_U16(h, l) ((uint16_t)(((uint16_t)(h) << 8) | (uint8_t)(l)))
#define COMBINE_I16(h, l) ((int16_t) (((uint16_t)(h) << 8) | (uint8_t)(l)))

// Global Variables
static uint16_t spiDigT1 = 0;
static int16_t spiDigT2 = 0;
static int16_t spiDigT3 = 0;
static int32_t spiTFine = 0;

static uint16_t spiDigP1 = 0;
static int16_t spiDigP2 = 0;
static int16_t spiDigP3 = 0;
static int16_t spiDigP4 = 0;
static int16_t spiDigP5 = 0;
static int16_t spiDigP6 = 0;
static int16_t spiDigP7 = 0;
static int16_t spiDigP8 = 0;
static int16_t spiDigP9 = 0;

static uint8_t spiClockSelect = 0;
static volatile uint8_t *spiClockPort = 0;

// SPI Helpers
static void bmp280SPITransmit(uint8_t registerAddress, uint8_t data) {
  *spiClockPort &= ~(1 << spiClockSelect);

  SPI_transmit(registerAddress & ~(BIT_7)); 
  SPI_transmit(data);

  *spiClockPort |= (1 << spiClockSelect);
}

static uint8_t bmp280SPIRead(uint8_t registerAddress) {
  *spiClockPort &= ~(1 << spiClockSelect);
  SPI_transmit(registerAddress | BIT_7); 
  const uint8_t data = SPI_receive();

  *spiClockPort |= (1 << spiClockSelect);
  return data;
}


// Private Functions

// I have no fucking clue how these work I just I just plug in a ADC  value
// This gets barometic pressure (divide by 256)
static uint32_t bmp280SPICompensateP(int32_t adcP) {
  int64_t var1, var2, p;
  
  var1 = ((int64_t)spiTFine) - 128000;
  var2 = var1 * var1 * (int64_t)spiDigP6;
  var2 = var2 + ((var1 * (int64_t)spiDigP5) << 17);
  var2 = var2 + (((int64_t)spiDigP4) << 35);
  var1 = ((var1 * var1 * (int64_t)spiDigP3) >> 8) + ((var1 * (int64_t)spiDigP2) << 12);
  var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)spiDigP1) >> 33;
  
  if (var1 == 0) {
      return 0; // avoid exception caused by division by zero
  }
  
  p = 1048576 - adcP;
  p = (((p << 31) - var2) * 3125) / var1;
  var1 = (((int64_t)spiDigP9) * (p >> 13) * (p >> 13)) >> 25;
  var2 = (((int64_t)spiDigP8) * p) >> 19;
  p = ((p + var1 + var2) >> 8) + (((int64_t)spiDigP7) << 4);
  
  return (uint32_t)p; // Returns pressure in Pascals
}

// T is temperature in celcius (divide by 100)
static int32_t bmp280SPICompensateT(int32_t adcT) {
  int32_t var1, var2, T;
  
  var1 = ((((adcT >> 3) - ((int32_t)spiDigT1 << 1))) * ((int32_t)spiDigT2)) >> 11;
  var2 = (((((adcT >> 4) - ((int32_t)spiDigT1)) * ((adcT >> 4) - ((int32_t)spiDigT1))) >> 12) * ((int32_t)spiDigT3)) >> 14;  
  spiTFine = var1 + var2;
  T = (spiTFine * 5 + 128) >> 8;
  
  return T; 
}

static int32_t bmp280SPIReadADCTemperature() {
  *spiClockPort &= ~(1 << spiClockSelect); // Pull pin low to signal we're talking to them
  SPI_transmit(TEMP_MSB | BIT_7); // We're reading these bits

  // Burst read cos the datasheet reccomends that
  const uint8_t tempMSB = SPI_receive();
  const uint8_t tempLSB = SPI_receive();
  const uint8_t tempXLSB = SPI_receive();
  *spiClockPort |= (1 << spiClockSelect); // Pull pin high to signal we're done talking to them

  const int32_t finalTemperature = (((int32_t)tempMSB << 12) |
                                   ((int32_t)tempLSB << 4)   |
                                   ((int32_t)tempXLSB >> 4));
  

  return finalTemperature;
}

static int32_t bmp280SPIReadADCPressure() {
  *spiClockPort &= ~(1 << spiClockSelect); // Pull pin low to signal we're talking to them
  SPI_transmit(PRESSURE_MSB | BIT_7); // We're reading these bits

  // Burst read cos the datasheet reccomends that
  const uint8_t pressureMSB = SPI_receive();
  const uint8_t pressureLSB = SPI_receive();
  const uint8_t pressureXLSB = SPI_receive();
  *spiClockPort |= (1 << spiClockSelect); // Pull pin high to signal we're done talking to them

  const int32_t finalPressure = (((int32_t)pressureMSB << 12) |
                                   ((int32_t)pressureLSB << 4)   |
                                   ((int32_t)pressureXLSB >> 4));
  

  return finalPressure;
}

static void bmp280SPIReadAllCalibrationData() {
  uint8_t buffer[24]; // 24 bytes total (6 for Temp, 18 for Pressure)

  // Pull pin low
  *spiClockPort &= ~(1 << spiClockSelect); // Pull pin low to signal we're talking to them
  SPI_transmit(CALIBRATION_REGISTER | BIT_7); // Read mode

  for (uint8_t i = 0; i < 24; i++) {
    buffer[i] = SPI_receive();
  }

  *spiClockPort |= (1 << spiClockSelect); // Pull pin high to signal we're done talking to them

  // Temperature Constants
  spiDigT1 = COMBINE_U16(buffer[1], buffer[0]);
  spiDigT2 = COMBINE_I16(buffer[3], buffer[2]);
  spiDigT3 = COMBINE_I16(buffer[5], buffer[4]);
  
  // Pressure Constants (Starts at 6)
  spiDigP1 = COMBINE_U16(buffer[7],  buffer[6]);
  spiDigP2 = COMBINE_I16(buffer[9],  buffer[8]);
  spiDigP3 = COMBINE_I16(buffer[11], buffer[10]);
  spiDigP4 = COMBINE_I16(buffer[13], buffer[12]);
  spiDigP5 = COMBINE_I16(buffer[15], buffer[14]);
  spiDigP6 = COMBINE_I16(buffer[17], buffer[16]);
  spiDigP7 = COMBINE_I16(buffer[19], buffer[18]);
  spiDigP8 = COMBINE_I16(buffer[21], buffer[20]);
  spiDigP9 = COMBINE_I16(buffer[23], buffer[22]);
}

// Public Functions
void initBmp280SPI(uint8_t clockSelectPin, volatile uint8_t *clockSelectPort) {
  spiClockSelect = clockSelectPin;
  spiClockPort = clockSelectPort;
  
  const uint8_t controlRegister = PRESSURE_16x | TEMPERATURE_2x | NORMAL_MODE; // 2x temp oversampling, 16x pressure
  const uint8_t configRegister = STANDBY_1000ms | FILTER_4x; // 1 second delay in reads, 4x filter

  bmp280SPITransmit(CONFIG_REGISTER, configRegister);
  bmp280SPITransmit(CONTROL_REGISTER, controlRegister);

  bmp280SPIReadAllCalibrationData();
}

// No floats
int8_t readTemperatureCSPI() {
  const int32_t rawTemperature = bmp280SPIReadADCTemperature();
  const int32_t convertedTemp = bmp280SPICompensateT(rawTemperature); // Only like 12 bits are used
  return (int8_t)(convertedTemp / 100); // Drop the decimal
}

uint16_t readBarometricPressureSPI() {
  const int32_t rawPressure = bmp280SPIReadADCPressure();
  const int32_t convertedPressure = bmp280SPICompensateP(rawPressure);
  return (uint16_t)(convertedPressure / 25600);
}

// In meters
int16_t calculateAltitudeSPI(uint16_t pressureHpa) {
  int32_t currentPressurePa = (uint32_t)pressureHpa * 100;
  int32_t seaLevelPressurePa = 101325; 
  return  ((seaLevelPressurePa - currentPressurePa) * 843) / 10000;
}
