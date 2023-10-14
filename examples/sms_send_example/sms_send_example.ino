#include <SoftwareSerial.h>
#include <sim900.h>

void setup() {
  Serial.begin(9600);
  SIM900 sim900(&SoftwareSerial(7, 8));

  Serial.println(sim900.sendSMS("+XXxxxxxxxxxx", "Hello, world!"));
  sim900.close();
}

void loop() { }