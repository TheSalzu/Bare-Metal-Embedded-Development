// Inlcudes
#include "RealTimeClock.h"
#include "I2C.h"

// Helper Functions
uint8_t bcdToDec(uint8_t bcdByte) {
  return ((bcdByte >> 4) * 10) + (bcdByte & 0x0F);
}

uint8_t decToBcd(uint8_t decByte) {
  return ((decByte / 10) << 4) | (decByte % 10);
}

// Private Functions
void startInternalClock() {
  uint8_t seconds = readRegister(RTC_ADDRESS, SECONDS_ADDRESS);
  seconds &= ~(1 << CH); // TUrn CH off to start counting
  writeRegister(RTC_ADDRESS, SECONDS_ADDRESS, seconds);
}

RTCHour read12HourClockWithRawData(uint8_t rawHours) {
  RTCHour time = {0};

  if (rawHours & (1 << AMPM)) {
    time.isPM = 1; 
  } else {
    time.isPM = 0;
  }

  uint8_t cleanBcdHours = rawHours & 0x1F; // Get the timer only bits
  time.hour = bcdToDec(cleanBcdHours);

  return time;
}

// Public Functions
void setHourMode(HourMode mode) {
  uint8_t currentHours = readRegister(RTC_ADDRESS, HOURS_ADDRESS);
  
  switch (mode) {
    case TWELVE_HOURS:
      currentHours |= (1 << HOUR_MODE_SELECTOR_BIT);
      break;
    case TWENTY_FOUR_HOURS:
      currentHours &= ~(1 << HOUR_MODE_SELECTOR_BIT);
      break;
    default:
      currentHours &= ~(1 << HOUR_MODE_SELECTOR_BIT); // default to 24 hrs
  }

  writeRegister(RTC_ADDRESS, HOURS_ADDRESS, currentHours);
}

// Getters
uint8_t readClockSeconds() {
  uint8_t rawSeconds = readRegister(RTC_ADDRESS, SECONDS_ADDRESS);
  return bcdToDec(rawSeconds & 0x7F);
}

uint8_t readClockMinutes() {
  return bcdToDec(readRegister(RTC_ADDRESS, MINUTES_ADDRESS));
}

uint8_t read24HourClock() {
  uint8_t rawHours = readRegister(RTC_ADDRESS, HOURS_ADDRESS);
  return bcdToDec(rawHours & 0x3F); // Only take the bytes we need
}

RTCHour read12HourClock() {
  RTCHour time = {0};
  uint8_t rawHours = readRegister(RTC_ADDRESS, HOURS_ADDRESS);

  if (rawHours & (1 << AMPM)) {
    time.isPM = 1; 
  } else {
    time.isPM = 0;
  }

  uint8_t cleanBcdHours = rawHours & 0x1F; // Get the timer only bits
  time.hour = bcdToDec(cleanBcdHours);

  return time;
}

uint8_t readClockDayOfWeek() {
  uint8_t rawDayOfWeek = readRegister(RTC_ADDRESS, DAY_OF_WEEK_ADDRESS);
  return bcdToDec(rawDayOfWeek & 0x07);
}

uint8_t readClockDate() {
  uint8_t rawDate = readRegister(RTC_ADDRESS, DATE_ADDRESS);
  return bcdToDec(rawDate & 0x3F);
}

uint8_t readClockMonth() {
  uint8_t rawMonth = readRegister(RTC_ADDRESS, MONTHS_ADDRESS);
  return bcdToDec(rawMonth & 0x1F);
}

uint16_t readClockYear() {
  return bcdToDec(readRegister(RTC_ADDRESS, YEARS_ADDRESS)) + YEAR_OFFSET;
}

RTCTime getTimeValues(HourMode mode) {
  RTCTime timeValues = {0};

  i2cStart();
  i2cSend(RTC_ADDRESS << 1);
  i2cSend(SECONDS_ADDRESS);

  i2cStart();
  i2cSend((RTC_ADDRESS << 1) | 1);

  uint8_t rawSeconds = i2cReadAck();
  uint8_t rawMinutes = i2cReadAck();
  uint8_t rawHours = i2cReadAck();
  uint8_t rawDayOfWeek = i2cReadAck();
  uint8_t rawDate = i2cReadAck();
  uint8_t rawMonth = i2cReadAck();
  uint8_t rawYear = i2cReadNoAck();

  timeValues.seconds = bcdToDec(rawSeconds & 0x7F);
  timeValues.minutes = bcdToDec(rawMinutes);
  timeValues.dayOfWeek = bcdToDec(rawDayOfWeek & 0x07);
  timeValues.month = bcdToDec(rawMonth & 0x1F);
  timeValues.year = bcdToDec(rawYear) + YEAR_OFFSET;

  // For hours:
  if (mode == TWELVE_HOURS) {
    const RTCHour tweleveHourStruct = read12HourClockWithRawData(rawHours);
    timeValues.isPM = tweleveHourStruct.isPM;
    timeValues.hour = tweleveHourStruct.hour;
  }
  else if (mode == TWENTY_FOUR_HOURS) {
    timeValues.hour = bcdToDec(rawHours & 0x3F);
  }

  i2cStop();

  return timeValues;
}

// Initalization modes
void initRTC() {
  startInternalClock();
}
void initRTC_SQWE_MODE(HZMode mode) {
  startInternalClock();
  
  uint8_t hzRate = 0;

  switch (mode) {
    case ONE_HZ:
      hzRate = CONTROL_SQWE_1HZ;
      break;
    case FOUR_kHZ:
      hzRate = CONTROL_SQWE_4kHZ;
      break;
    case EIGHT_kHZ:
      hzRate = CONTROL_SQWE_8kHZ;
      break;
    case THIRTY_TWO_kHZ:
      hzRate = CONTROL_SQWE_32kHZ;
      break;
    default:
      hzRate = CONTROL_SQWE_1HZ; // default to 1hz
  }

  writeRegister(RTC_ADDRESS, CONTROL_REGISTER, hzRate);
}

// Out Mode
void initRTC_OUT_MODE() {
  startInternalClock();
  writeRegister(RTC_ADDRESS, CONTROL_REGISTER, CONTROL_OUT);
}

void writeOutHigh() {
  writeRegister(RTC_ADDRESS, CONTROL_REGISTER, CONTROL_OUT_HIGH);
}

void writeOutLow() {
  writeRegister(RTC_ADDRESS, CONTROL_REGISTER, CONTROL_OUT_LOW);
}

// One time setup
void setClockTime(uint8_t sec, uint8_t min, uint8_t hr, uint8_t day, uint8_t date, uint8_t month, uint16_t yr) {
  uint8_t bcdSec = decToBcd(sec);
  uint8_t bcdMin = decToBcd(min);
  uint8_t bcdHr = decToBcd(hr); // Assumes 24-hour format for easy setting
  uint8_t bcdDay = decToBcd(day);
  uint8_t bcdDate = decToBcd(date);
  uint8_t bcdMonth = decToBcd(month);
  uint8_t bcdYear  = decToBcd((uint8_t)(yr % 100)); 

  bcdSec &= ~(1 << CH);

  writeRegister(RTC_ADDRESS, SECONDS_ADDRESS, bcdSec);
  writeRegister(RTC_ADDRESS, MINUTES_ADDRESS, bcdMin);
  writeRegister(RTC_ADDRESS, HOURS_ADDRESS, bcdHr);
  writeRegister(RTC_ADDRESS, DAY_OF_WEEK_ADDRESS, bcdDay);
  writeRegister(RTC_ADDRESS, DATE_ADDRESS, bcdDate);
  writeRegister(RTC_ADDRESS, MONTHS_ADDRESS, bcdMonth);
  writeRegister(RTC_ADDRESS, YEARS_ADDRESS, bcdYear);
}