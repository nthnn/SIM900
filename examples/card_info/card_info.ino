#include <SoftwareSerial.h>
#include <sim900.h>

SoftwareSerial shieldSerial(7, 8);

void setup() {
  Serial.begin(9600);
  shieldSerial.begin(9600);
  SIM900 sim900(shieldSerial);
  uint8_t phonebookIndex = 1;

  SIM900CardAccount accountInfo;
  accountInfo.name = "Nathanne Isip";
  accountInfo.number = "00000000000";
  accountInfo.numberType = SIM900_PHONEBOOK_INTERNATIONAL;

  Serial.println(F("Storing a phonebook account..."));
  sim900.savePhonebook(phonebookIndex, accountInfo);
  Serial.println(F("Account stored!"));

  SIM900CardAccount retrieved = sim900.retrievePhonebook(phonebookIndex);
  Serial.println(F("Retrieving phonebook..."));
  Serial.println(F("-----------------------"));

  Serial.print(F("Name: "));
  Serial.println(retrieved.name);

  Serial.print(F("Number: "));
  Serial.println(retrieved.number);

  Serial.print(F("Number type: "));
  switch(retrieved.numberType) {
    case 129:
      Serial.println(F("International"));
      break;

    case 145:
      Serial.println(F("National"));
      break;

    default:
      Serial.println(F("Unknown"));
      break;
  }
}

void loop() { }