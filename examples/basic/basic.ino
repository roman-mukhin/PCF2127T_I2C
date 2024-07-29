#include <Wire.h>
#include <PCF2127T_I2C.h>

// Real Time Clock
PCF2127T_I2C rtc;
uint8_t rtcSeconds, rtcMinutes, rtcHours, rtcWeekDay, rtcDay, rtcMonth, rtcYear;
uint32_t previous_millis = 0;

char buff[100] = "";

// Time setting
void rtcSetTime(uint8_t rtcNewYear, uint8_t rtcNewMonth, uint8_t rtcNewDay, uint8_t rtcNewHour, uint8_t rtcNewMinute, uint8_t rtcNewSecond, uint8_t rtcNewWeekDay) {
  if (rtcNewWeekDay == 7) rtcNewWeekDay = 0;
  if ((rtcNewHour > 23) || (rtcNewMinute > 59) || (rtcNewSecond > 59) || (rtcNewYear > 99) || (rtcNewMonth > 12) || (rtcNewDay > 31) || (rtcNewWeekDay > 6)) Serial.println(F("Wrong time format"));
  else {
    Serial.println(F("Time changed"));
    rtc.setTime(rtcNewYear, rtcNewMonth, rtcNewDay, rtcNewHour, rtcNewMinute, rtcNewSecond, rtcNewWeekDay);
  }
}

// Time reading
void rtcGetTime() {
  rtc.readTime(rtcYear, rtcMonth, rtcDay, rtcHours, rtcMinutes, rtcSeconds, rtcWeekDay);
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("PCF2127T(I2C) test"));
  rtc.begin(&Wire1);

  rtcSetTime(24, 2, 28, 23, 59, 30, 3); // 28 Feb 2024, 23:59:30, Th
  previous_millis = millis();
}

void loop() {
  if ((millis() - previous_millis) >= 1000) {
    rtcGetTime();
    buff[0] = '\0';
    sprintf(buff, "%04d-%02d-%02d %02d:%02d:%02d", 2000 + rtcYear, rtcMonth, rtcDay, rtcHours, rtcMinutes, rtcSeconds);
    Serial.println(buff);
    previous_millis = millis();
  }
}
