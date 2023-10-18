#include <SoftwareSerial.h>
#include <sim900.h>

SoftwareSerial shieldSerial(7, 8);

void setup() {
  Serial.begin(9600);
  SIM900 sim900(&shieldSerial);

  SIM900APN access;
  access.apn = "";
  access.username = "";
  access.password = "";

  if(!sim900.connectAPN(access)) {
    Serial.println("Failed to connect to APN.");
    return;
  }
  Serial.println("Connected to APN!");

  bool gprsEnabled = sim900.enableGPRS();
  Serial.println(gprsEnabled ? "GPRS was successfully enabled." : "Cannot start GPRS.");

  if(!gprsEnabled)
    return;
  Serial.println("IP Address: " + sim900.ipAddress());
}

void loop() { }