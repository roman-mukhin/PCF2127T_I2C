#include "PCF2127T_I2C.h"

PCF2127T_I2C::PCF2127T_I2C() {
  _i2c = NULL;
}


// PUBLIC
void PCF2127T_I2C::begin(TwoWire* wire) {
  // setup I2C bus
  if (wire) {
    _i2c = wire;
  } else {
    _i2c = &Wire;
  }
  _i2c->begin();
}

void PCF2127T_I2C::setTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t weekday) {
  _i2c->beginTransmission(I2C_ADDR);
  _i2c->write(RTC_SECOND_ADDR);
  _i2c->write(decToBcd(second));
  _i2c->write(decToBcd(minute));
  _i2c->write(decToBcd(hour));
  _i2c->endTransmission();

  _i2c->beginTransmission(I2C_ADDR);
  _i2c->write(RTC_DAY_ADDR);
  _i2c->write(decToBcd(day));
  _i2c->write(decToBcd(weekday));
  _i2c->write(decToBcd(month));
  _i2c->write(decToBcd(year));  // 2000 - 00, ..., 2099 - 99
  _i2c->endTransmission();
}

void PCF2127T_I2C::readTime(uint8_t& year, uint8_t& month, uint8_t& day, uint8_t& hour, uint8_t& minute, uint8_t& second, uint8_t& weekday) {
  _i2c->beginTransmission(I2C_ADDR);
  _i2c->write(RTC_SECOND_ADDR);
  _i2c->endTransmission();

  _i2c->requestFrom(I2C_ADDR, 7);

  while (_i2c->available()) {
    second = bcdToDec(_i2c->read() & 0x7F);
    minute = bcdToDec(_i2c->read() & 0x7F);
    hour = bcdToDec(_i2c->read() & 0x3F);
    day = bcdToDec(_i2c->read() & 0x3F);
    weekday = bcdToDec(_i2c->read() & 0x07);
    month = bcdToDec(_i2c->read() & 0x1F);
    year = bcdToDec(_i2c->read());
  }
}

// PRIVATE
uint8_t PCF2127T_I2C::decToBcd(uint8_t val) {
  return ((val / 10 * 16) + (val % 10));
}

uint8_t PCF2127T_I2C::bcdToDec(uint8_t val) {
  return ((val / 16 * 10) + (val % 16));
}