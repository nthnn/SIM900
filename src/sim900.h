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

    String rawQueryOnLine(uint16_t line);
    String queryResult();

public:
    SIM900(SoftwareSerial *_sim900);
    bool handshake();
    void close();

    SIM900DialResult dialUp(String number);
    SIM900DialResult redialUp();
    SIM900DialResult acceptIncomingCall();
    bool hangUp();

    bool sendSMS(String number, String message);

    bool connectAPN(SIM900APN apn);
    bool enableGPRS();
    SIM900HTTPResponse request(SIM900HTTPRequest request);

    SIM900Operator networkOperator();
    SIM900RTC rtc();
    bool updateRtc(SIM900RTC config);

    String manufacturer();
    String softwareRelease();
    String imei();
    String chipModel();
    String chipName();
    String ipAddress();
};

#endif