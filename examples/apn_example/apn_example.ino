#include <SoftwareSerial.h>
#include <sim900.h>

SoftwareSerial shieldSerial(7, 8);

void setup() {
  Serial.begin(9600);
  shieldSerial.begin(9600);
  SIM900 sim900(shieldSerial);

  SIM900APN access;
  access.apn = F("");
  access.username = F("");
  access.password = F("");

  if(!sim900.connectAPN(access)) {
    Serial.println(F("Failed to connect to APN."));
    return;
  }
  Serial.println(F("Connected to APN!"));

  bool gprsEnabled = sim900.enableGPRS();
  Serial.println(gprsEnabled ?
    F("GPRS was successfully enabled.") :
    F("Cannot start GPRS."));

  if(!gprsEnabled)
    return;
  Serial.println("IP Address: " + sim900.ipAddress());
}

void loop() { }