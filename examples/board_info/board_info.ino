#include <SoftwareSerial.h>
#include <sim900.h>

SoftwareSerial shieldSerial(7, 8);

void setup() {
  Serial.begin(9600);
  shieldSerial.begin(9600);
  SIM900 sim900(shieldSerial);

  Serial.println(F("Dumping board informations..."));
  Serial.println(F("-----------------------------------------"));

  Serial.print(F("Manufacturer:\t"));
  Serial.println(sim900.manufacturer());
  
  Serial.print(F("Firmware:\t"));
  Serial.println(sim900.softwareRelease());

  Serial.print(F("Chip Model:\t"));
  Serial.println(sim900.chipModel());

  Serial.print(F("Chip Name:\t"));
  Serial.println(sim900.chipName());

  Serial.print(F("IMEI:\t\t"));
  Serial.println(sim900.imei());
}

void loop() { }