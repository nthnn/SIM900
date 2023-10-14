#ifndef SIM900_H
#define SIM900_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#include <sim900_defs.h>

class SIM900 {
private:
    SoftwareSerial *sim900;

    void sendCommand(String message);
    bool isSuccessCommand();

    String getResponse();
    String getReturnedMode();

public:
    SIM900(SoftwareSerial *_sim900);
    bool handshake();
    void close();

    SIM900DialResult dialUp(String number);
    SIM900DialResult redialUp();
    SIM900DialResult acceptIncomingCall();
    bool hangUp();

    bool sendSMS(String number, String message);
};

#endif