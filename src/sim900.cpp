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
    return this->getReturnedMode() == F("OK");
}

String SIM900::rawQueryOnLine(uint16_t line) {
    String response = this->getResponse();
    String result = "";

    uint16_t currentLine = 0;
    for(int i = 0; i < response.length(); i++)
        if(currentLine == line && response[i] != '\n')
            result += response[i];
        else if(response[i] == '\n') {
            currentLine++;

            if(currentLine > line)
                break;
        }

    return result;
}

String SIM900::queryResult() {
    String response = this->getResponse();
    String result = F("");

    int idx = response.indexOf(": ");
    if(idx != -1)
        result = response.substring(
            idx + 2,
            response.indexOf('\n', idx)
        );

    return result;
}

SIM900::SIM900(SoftwareSerial *_sim900):
    sim900(_sim900) {
    this->sim900->begin(9600);
}

bool SIM900::handshake() {
    this->sendCommand(F("AT"));
    return this->isSuccessCommand();
}

void SIM900::close() {
    this->sim900->end();
}

SIM900DialResult SIM900::dialUp(String number) {
    this->sendCommand("ATD+ " + number + ";");

    SIM900DialResult result = SIM900_DIAL_RESULT_ERROR;
    String mode = this->getReturnedMode();

    if(mode == F("NO DIALTONE"))
        result = SIM900_DIAL_RESULT_NO_DIALTONE;
    else if(mode == F("BUSY"))
        result = SIM900_DIAL_RESULT_BUSY;
    else if(mode == F("NO CARRIER"))
        result = SIM900_DIAL_RESULT_NO_CARRIER;
    else if(mode == F("NO ANSWER"))
        result = SIM900_DIAL_RESULT_NO_ANSWER;
    else if(mode == F("OK"))
        result = SIM900_DIAL_RESULT_OK;

    return result;
}

SIM900DialResult SIM900::redialUp() {
    this->sendCommand(F("ATDL"));

    SIM900DialResult result = SIM900_DIAL_RESULT_ERROR;
    String mode = this->getReturnedMode();

    if(mode == F("NO DIALTONE"))
        result = SIM900_DIAL_RESULT_NO_DIALTONE;
    else if(mode == F("BUSY"))
        result = SIM900_DIAL_RESULT_BUSY;
    else if(mode == F("NO CARRIER"))
        result = SIM900_DIAL_RESULT_NO_CARRIER;
    else if(mode == F("NO ANSWER"))
        result = SIM900_DIAL_RESULT_NO_ANSWER;
    else if(mode == F("OK"))
        result = SIM900_DIAL_RESULT_OK;

    return result;
}

SIM900DialResult SIM900::acceptIncomingCall() {
    this->sendCommand(F("ATA"));

    SIM900DialResult result = SIM900_DIAL_RESULT_ERROR;
    String mode = this->getReturnedMode();

    if(mode == F("NO CARRIER"))
        result = SIM900_DIAL_RESULT_NO_CARRIER;
    else if(mode == F("OK"))
        result = SIM900_DIAL_RESULT_OK;

    return result;
}

bool SIM900::hangUp() {
    this->sendCommand(F("ATH"));
    return this->isSuccessCommand();
}

bool SIM900::sendSMS(String number, String message) {
    this->handshake();

    this->sendCommand(F("AT+CMGF=1"));
    delay(500);
    this->sendCommand("AT+CMGS=\"" + number + "\"");
    delay(500);
    this->sendCommand(message);
    delay(500);
    this->sim900->write(0x1a);

    return this->getReturnedMode().startsWith(">");
}

//SIM900Operator SIM900::networkOperator();

bool SIM900::updateRtc(SIM900RTC config) {
    this->sendCommand(
        "AT+CCLK=\"" + String(config.year <= 9 ? "0" : "") + String(config.year) +
        "/" + String(config.month <= 9 ? "0" : "") + String(config.month) +
        "/" + String(config.day <= 9 ? "0" : "") + String(config.day) +
        "," + String(config.hour <= 9 ? "0" : "") + String(config.hour) +
        ":" + String(config.minute <= 9 ? "0" : "") + String(config.minute) +
        ":" + String(config.second <= 9 ? "0" : "") + String(config.second) +
        "+" + String(config.gmt <= 9 ? "0" : "") + String(config.gmt) + "\""
    );

    return this->isSuccessCommand();
}

SIM900RTC SIM900::rtc() {
    SIM900RTC rtc;
    rtc.year = rtc.month = rtc.day =
        rtc.hour = rtc.minute = rtc.second = 
        rtc.gmt = 0;

    this->sendCommand(F("AT+CMGF=1"));
    if(!this->isSuccessCommand())
        return rtc;

    this->sendCommand(F("AT+CENG=3"));
    if(!this->isSuccessCommand())
        return rtc;
    this->sendCommand(F("AT+CCLK?"));
    
    String time = this->queryResult();
    time = time.substring(1, time.length() - 2);

    uint8_t delim1 = time.indexOf('/'),
        delim2 = time.indexOf('/', delim1 + 1),
        delim3 = time.indexOf(',', delim2),
        delim4 = time.indexOf(':', delim3),
        delim5 = time.indexOf(':', delim4 + 1),
        delim6 = time.indexOf('+', delim5);

    rtc.year =  (uint8_t) time.substring(0, delim1).toInt();
    rtc.month = (uint8_t) time.substring(delim1 + 1, delim2).toInt();
    rtc.day = (uint8_t) time.substring(delim2 + 1, delim3).toInt();
    rtc.hour = (uint8_t) time.substring(delim3 + 1, delim4).toInt();
    rtc.minute = (uint8_t) time.substring(delim4 + 1, delim5).toInt();
    rtc.second = (uint8_t) time.substring(delim5 + 1, delim6).toInt();
    rtc.gmt = (uint8_t) time.substring(delim6 + 1).toInt();

    return rtc; 
}

String SIM900::manufacturer() {
    this->sendCommand(F("AT+GMI"));
    return this->rawQueryOnLine(2);
}

String SIM900::softwareRelease() {
    this->sendCommand(F("AT+GMR"));

    String result = this->rawQueryOnLine(2);
    result = result.substring(result.lastIndexOf(F(":")) + 1);

    return result;
}

String SIM900::imei() {
    this->sendCommand(F("AT+GSN"));
    return this->rawQueryOnLine(2);
}

String SIM900::chipModel() {
    this->sendCommand(F("AT+GMM"));
    return this->rawQueryOnLine(2);
}

String SIM900::chipName() {
    this->sendCommand(F("AT+GOI"));
    return this->rawQueryOnLine(2);
}
