#include <SoftwareSerial.h>
#include <sim900.h>

SoftwareSerial shieldSerial(7, 8);

void setup() {
  Serial.begin(9600);

  shieldSerial.begin(9600);
  SIM900 sim900(shieldSerial);
  Serial.println(
    sim900.sendSMS("+XXxxxxxxxxxx", "Hello, world!!")
      ? "Sent!" : "Not sent."
  );
  sim900.close();
}

void loop() { }