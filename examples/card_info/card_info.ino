#include <SoftwareSerial.h>
#include <sim900.h>

SoftwareSerial shieldSerial(7, 8);

void setup() {
  Serial.begin(9600);
  SIM900 sim900(&shieldSerial);

  Serial.println(F("Dumping SIM card informations..."));
  Serial.println(F("-----------------------------------------"));

  SIM900CardAccount accountInfo = sim900.cardNumber();

  Serial.print(F("Name:\t\t"));
  Serial.println(accountInfo.name);

  Serial.print(F("Number:\t\t"));
  Serial.println(accountInfo.number);

  Serial.print(F("Type:\t\t"));
  Serial.println(accountInfo.type);

  Serial.print(F("Speed:\t\t"));
  Serial.println(accountInfo.speed);

  Serial.print(F("Service:\t"));
  Serial.println(accountInfo.service);
}

void loop() { }