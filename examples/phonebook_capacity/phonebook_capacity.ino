#include <SoftwareSerial.h>
#include <sim900.h>

SoftwareSerial shieldSerial(7, 8);

void setup() {
  Serial.begin(9600);

  SIM900 sim900(&shieldSerial);
  SIM900PhonebookCapacity capacity = sim900.phonebookCapacity();

  Serial.println(F("Phonebook Capacity"));
  Serial.println(F("-------------------"));

  Serial.print(F("Memory Type:\t"));
  Serial.println(capacity.memoryType);

  Serial.print(F("Used:\t\t"));
  Serial.println(capacity.used);

  Serial.print(F("Max:\t\t"));
  Serial.println(capacity.max);
}

void loop() { }