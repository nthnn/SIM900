#include <sim900.h>
#include <SoftwareSerial.h>

void SIM900::sendCommand(String message) {
    this->sim900->println(message);
}

String SIM900::getResponse() {
    delay(500);
    
    if(this->sim900->available() > 0) {
        String response = this->sim900->readString();
        response.trim();

        return response;
    }

    return "";
}

String SIM900::getReturnedMode() {
    String response = this->getResponse();
    return response.substring(response.lastIndexOf('\n') + 1);
}

bool SIM900::isSuccessCommand() {
    return this->getReturnedMode() == "OK";
}

SIM900::SIM900(SoftwareSerial *_sim900):
    sim900(_sim900) {
    this->sim900->begin(9600);
}

bool SIM900::handshake() {
    this->sendCommand("AT");
    return this->isSuccessCommand();
}

SIM900DialResult SIM900::dialUp(String number) {
    this->sendCommand("ATD+ " + number + ";");

    SIM900DialResult result = SIM900_DIAL_RESULT_ERROR;
    String mode = this->getReturnedMode();

    if(mode == "NO DIALTONE")
        result = SIM900_DIAL_RESULT_NO_DIALTONE;
    else if(mode =="BUSY")
        result = SIM900_DIAL_RESULT_BUSY;
    else if(mode == "NO CARRIER")
        result = SIM900_DIAL_RESULT_NO_CARRIER;
    else if(mode == "NO ANSWER")
        result = SIM900_DIAL_RESULT_NO_ANSWER;
    else if(mode == "OK")
        result = SIM900_DIAL_RESULT_OK;

    return result;
}

SIM900DialResult SIM900::redialUp() {
    this->sendCommand("ATDL");

    SIM900DialResult result = SIM900_DIAL_RESULT_ERROR;
    String mode = this->getReturnedMode();

    if(mode == "NO DIALTONE")
        result = SIM900_DIAL_RESULT_NO_DIALTONE;
    else if(mode =="BUSY")
        result = SIM900_DIAL_RESULT_BUSY;
    else if(mode == "NO CARRIER")
        result = SIM900_DIAL_RESULT_NO_CARRIER;
    else if(mode == "NO ANSWER")
        result = SIM900_DIAL_RESULT_NO_ANSWER;
    else if(mode == "OK")
        result = SIM900_DIAL_RESULT_OK;

    return result;
}

SIM900DialResult SIM900::acceptIncomingCall() {
    this->sendCommand("ATA");

    SIM900DialResult result = SIM900_DIAL_RESULT_ERROR;
    String mode = this->getReturnedMode();

    if(mode == "NO CARRIER")
        result = SIM900_DIAL_RESULT_NO_CARRIER;
    else if(mode == "OK")
        result = SIM900_DIAL_RESULT_OK;

    return result;
}

bool SIM900::hangUp() {
    this->sendCommand("ATH");
    return this->isSuccessCommand();
}

bool SIM900::sendSMS(String number, String message) {
    this->handshake();

    this->sendCommand("AT+CMGF=1");
    delay(500);
    this->sendCommand("AT+CMGS=\"" + number + "\"");
    delay(500);
    this->sendCommand(message);
    delay(500);

    this->sim900->write(0x1a);
    return this->getReturnedMode() == ("> " + message);
}

void SIM900::close() {
    this->sim900->end();
}