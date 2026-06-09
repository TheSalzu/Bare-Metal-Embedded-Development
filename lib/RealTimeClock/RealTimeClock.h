#ifndef REAL_TIME_CLOCK_H
#define REAL_TIME_CLOCK_H

#include <stdint.h>

// Macros & Device Addresses
#define RTC_ADDRESS 0x68

#define CH                     7 // Turn on the oscillator
#define HOUR_MODE_SELECTOR_BIT 6 // 12hr vs 24hr bit
#define AMPM                   5 // AM or PM indicator bit

#define SECONDS_ADDRESS     0x00
#define MINUTES_ADDRESS     0x01
#define HOURS_ADDRESS       0x02
#define DAY_OF_WEEK_ADDRESS 0x03
#define DATE_ADDRESS        0x04
#define MONTHS_ADDRESS      0x05
#define YEARS_ADDRESS       0x06

#define CONTROL_REGISTER    0x07

#define CONTROL_OUT         0b00000000 
#define CONTROL_OUT_HIGH    0b10000000 
#define CONTROL_OUT_LOW     0b00000000 

#define CONTROL_SQWE_1HZ    0b00010000 
#define CONTROL_SQWE_4kHZ   0b00010001 
#define CONTROL_SQWE_8kHZ   0b00010010 
#define CONTROL_SQWE_32kHZ  0b00010011 

#define YEAR_OFFSET 2000

// Enums & Structs
typedef enum {
  ONE_HZ,
  FOUR_kHZ,
  EIGHT_kHZ,
  THIRTY_TWO_kHZ,
} HZMode;

typedef enum {
  TWELVE_HOURS,
  TWENTY_FOUR_HOURS,
} HourMode;

typedef struct {
  uint8_t hour;
  uint8_t isPM; 
} RTCHour;

typedef struct {
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hour;
  uint8_t dayOfWeek;
  uint8_t date;
  uint8_t month;
  uint8_t year;
  uint8_t isPM;
} RTCTime;

// Initalizations
void initRTC(void);
void initRTC_SQWE_MODE(HZMode mode);
void initRTC_OUT_MODE(void);

// Setters
void writeOutHigh(void);
void writeOutLow(void);
void setHourMode(HourMode mode);

// Getters
uint8_t readClockSeconds(void);
uint8_t readClockMinutes(void);
uint8_t read24HourClock(void);
RTCHour read12HourClock(void);
uint8_t readClockDayOfWeek(void);
uint8_t readClockDate(void);
uint8_t readClockMonth(void);
uint16_t readClockYear(void);

// Mega-getter
RTCTime getTimeValues(HourMode mode);

// One time run functions
void setClockTime(uint8_t sec, uint8_t min, uint8_t hr, uint8_t day, uint8_t date, uint8_t month, uint16_t yr);

#endif // REAL_TIME_CLOCK_H