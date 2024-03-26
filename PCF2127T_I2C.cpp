#include "PCF2127T_I2C.h"

PCF2127T_I2C::PCF2127T_I2C(void) {
  Wire.begin();
}

// PUBLIC
void PCF2127T_I2C::setTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t weekday) {
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(RTC_SECOND_ADDR);
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.endTransmission();

  Wire.beginTransmission(I2C_ADDR);
  Wire.write(RTC_DAY_ADDR);
  Wire.write(decToBcd(day));
  Wire.write(decToBcd(weekday));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));  // 2000 - 00, ..., 2099 - 99
  Wire.endTransmission();
}

void PCF2127T_I2C::readTime(uint8_t& year, uint8_t& month, uint8_t& day, uint8_t& hour, uint8_t& minute, uint8_t& second, uint8_t& weekday) {
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(RTC_SECOND_ADDR);
  Wire.endTransmission();

  Wire.requestFrom(I2C_ADDR, 7);

  while (Wire.available()) {
    second = bcdToDec(Wire.read() & 0x7F);
    minute = bcdToDec(Wire.read() & 0x7F);
    hour = bcdToDec(Wire.read() & 0x3F);
    day = bcdToDec(Wire.read() & 0x3F);
    weekday = bcdToDec(Wire.read() & 0x07);
    month = bcdToDec(Wire.read() & 0x1F);
    year = bcdToDec(Wire.read());
  }
}

// PRIVATE
uint8_t PCF2127T_I2C::decToBcd(uint8_t val) {
  return ((val / 10 * 16) + (val % 10));
}

uint8_t PCF2127T_I2C::bcdToDec(uint8_t val) {
  return ((val / 16 * 10) + (val % 16));
}