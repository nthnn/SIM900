#include <SoftwareSerial.h>
#include <sim900.h>

SoftwareSerial shieldSerial(7, 8);

void setup() {
  Serial.begin(9600);
  shieldSerial.begin(9600);
  SIM900 sim900(shieldSerial);
  uint8_t index = 1;

  SIM900CardAccount account;
  account.name = "Nathanne Isip";
  account.number = "00000000000";
  account.numberType = SIM900_PHONEBOOK_NATIONAL;

  Serial.println(F("Storing to phonebook..."));
  if(!sim900.savePhonebook(index, account)) {
    Serial.println(F("Error saving to phonebook."));
    return;
  }

  Serial.println(F("Stored!"));
  Serial.println(F("--------------------------"));
  Serial.println(F("Retrieving..."));

  SIM900CardAccount retrieved = sim900.retrievePhonebook(index);
  Serial.print(F("Name:\t"));
  Serial.println(retrieved.name);

  Serial.print(F("Number:\t"));
  Serial.println(retrieved.number);

  Serial.print(F("Type:\t"));
  switch(retrieved.numberType) {
    case SIM900_PHONEBOOK_INTERNATIONAL:
      Serial.println("International");
      break;

    case SIM900_PHONEBOOK_NATIONAL:
      Serial.println("National");
      break;

    default:
      Serial.println("Unknown");
      break;
  }
}

void loop() { }