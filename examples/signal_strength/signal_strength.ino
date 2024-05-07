#include <SoftwareSerial.h>
#include <sim900.h>

SoftwareSerial shieldSerial(7, 8);

void setup() {
  Serial.begin(9600);

  shieldSerial.begin(9600);
  SIM900 sim900(shieldSerial);
  SIM900Signal signal = sim900.signal();

  Serial.println(F("Signal Strength"));
  Serial.println(F("-------------------"));

  Serial.print(F("RSSI:\t\t"));
  Serial.println(signal.rssi);

  Serial.print(F("Bit Error Rate:\t"));
  Serial.println(signal.bit_error_rate);
}

void loop() { }