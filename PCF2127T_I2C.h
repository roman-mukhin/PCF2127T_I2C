#ifndef PCF2127T_I2C_H
#define PCF2127T_I2C_H

#include "Arduino.h"
#include "Wire.h"

#define I2C_ADDR 0x51
#define RTC_SECOND_ADDR 0x03
#define RTC_DAY_ADDR 0x06


class PCF2127T_I2C {
public:
  PCF2127T_I2C();
  void begin(TwoWire* wire = NULL);

  void setTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t weekday);
  void readTime(uint8_t& year, uint8_t& month, uint8_t& day, uint8_t& hour, uint8_t& minute, uint8_t& second, uint8_t& weekday);


private:
  TwoWire* _i2c;
  uint8_t decToBcd(uint8_t val);
  uint8_t bcdToDec(uint8_t val);
};
#endif