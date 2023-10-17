#include <SoftwareSerial.h>
#include <sim900.h>

SoftwareSerial shieldSerial(7, 8);

void setup() {
  Serial.begin(9600);

  SIM900 sim900(&shieldSerial);
  SIM900Operator network = sim900.networkOperator();

  Serial.println(F("SIM900 Current Network Operator"));
  Serial.println(F("-------------------------------"));
  Serial.print(F("Name:\t"));
  Serial.println(network.name);
  Serial.print(F("Mode:\t"));
  Serial.println(network.mode);
  Serial.print(F("Format:\t"));
  Serial.println(network.format);
}

void loop() { }
