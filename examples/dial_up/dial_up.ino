#include <SoftwareSerial.h>
#include <sim900.h>

SoftwareSerial shieldSerial(7, 8);

void setup() {
  Serial.begin(9600);
  SIM900 sim900(&shieldSerial);

  sim900.dialUp("+XXxxxxxxxxxx");
  delay(20000);
  
  sim900.hangUp();
  delay(3000);

  sim900.redialUp();
  delay(10000);
  sim900.hangUp();
}

void loop() { }