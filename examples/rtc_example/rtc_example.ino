#include <SoftwareSerial.h>
#include <sim900.h>

SoftwareSerial shieldSerial(7, 8);

void printRTC(SIM900RTC rtc);

void setup() {
  Serial.begin(9600);
  SIM900 sim900(&shieldSerial);

  SIM900RTC rtc;
  rtc.year = 2;
  rtc.month = 8;
  rtc.day = 8;
  rtc.hour = 8;
  rtc.minute = 0;
  rtc.second = 0;
  rtc.gmt = 8;

  Serial.print(F("Updating RTC to: "));
  printRTC(rtc);
  sim900.updateRtc(rtc);

  Serial.println(F("\n-------------------------------"));
  Serial.print("Current time: ");

  SIM900RTC current = sim900.rtc();
  printRTC(current);
}

void loop() { }

void printRTC(SIM900RTC rtc) {
  Serial.print(rtc.year);
  Serial.print(F("/"));
  Serial.print(rtc.month);
  Serial.print(F("/"));
  Serial.print(rtc.day);
  Serial.print(F(" "));
  Serial.print(rtc.hour);
  Serial.print(F(":"));
  Serial.print(rtc.minute);
  Serial.print(F(":"));
  Serial.print(rtc.second);
  Serial.print(F(" +"));
  Serial.print(rtc.gmt);
}