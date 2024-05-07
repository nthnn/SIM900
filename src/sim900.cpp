/*
 * This file is part of the SIM900 Arduino Shield library.
 * Copyright (c) 2023 Nathanne Isip
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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

bool SIM900::isCardReady() {
    this->sendCommand(F("AT+CPIN?"));
    return this->isSuccessCommand();
}

bool SIM900::changeCardPin(uint8_t pin) {
    if(pin > 9999)
        return false;

    this->sendCommand("AT+CPIN=\"" + String(pin) + "\"");
    return this->isSuccessCommand();
}

SIM900Signal SIM900::signal() {
    SIM900Signal signal;
    signal.rssi = signal.bit_error_rate = 0;
    this->sendCommand("AT+CSQ");

    String response = this->queryResult();
    uint8_t delim = response.indexOf(',');

    if(delim == -1)
        return signal;

    signal.rssi = (uint8_t) response.substring(0, delim).toInt();
    signal.bit_error_rate = (uint8_t) response.substring(delim + 1).toInt();

    return signal;
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

SIM900Operator SIM900::networkOperator() {
    SIM900Operator simOperator;
    simOperator.mode = static_cast<SIM900OperatorMode>(0);
    simOperator.format = static_cast<SIM900OperatorFormat>(0);
    simOperator.name = "";

    this->sendCommand(F("AT+COPS?"));

    String response = this->queryResult();
    uint8_t delim1 = response.indexOf(','),
        delim2 = response.indexOf(',', delim1 + 1);

    simOperator.mode = intToSIM900OperatorMode((uint8_t) response.substring(0, delim1).toInt());
    simOperator.format = intToSIM900OperatorFormat((uint8_t) response.substring(delim1 + 1, delim2).toInt());
    simOperator.name = response.substring(delim2 + 2, response.length() - 2);

    return simOperator;
}

bool SIM900::connectAPN(SIM900APN apn) {
    this->sendCommand(F("AT+CMGF=1"));
    if(!this->isSuccessCommand())
        return false;

    this->sendCommand(F("AT+CGATT=1"));
    if(!this->isSuccessCommand())
        return false;
    
    this->sendCommand(
        "AT+CSTT=\"" + apn.apn +
        "\",\"" + apn.username +
        "\",\"" + apn.password + "\""
    );

    return (this->hasAPN = this->isSuccessCommand());
}

bool SIM900::enableGPRS() {
    if(!this->hasAPN)
        return false;

    this->sendCommand(F("AT+CIICR"));
    delay(1000);

    return this->isSuccessCommand();
}

SIM900HTTPResponse SIM900::request(SIM900HTTPRequest request) {
    SIM900HTTPResponse response;
    response.status = -1;

    if(!this->hasAPN)
        return response;

    this->sendCommand(
        "AT+CIPSTART=\"TCP\",\"" + request.domain +
        "\"," + String(request.port)
    );
    
    String resp = this->getResponse();
    resp.trim();

    delay(1500);
    if(!resp.endsWith(F("CONNECT OK")))
        return response;

    String requestStr = request.method + " " +
        request.resource + " HTTP/1.0\r\nHost: " +
        request.domain + "\r\n";

    for(int i = 0; i < request.header_count; i++)
        requestStr += request.headers[i].key + ": " +
            request.headers[i].value + "\r\n";

    if(request.data != "" || request.data != NULL)
        requestStr += request.data + "\r\n";

    requestStr += F("\r\n");
    this->sendCommand(requestStr);

    // TODO
    return response;
}

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

bool SIM900::savePhonebook(uint8_t index, SIM900CardAccount account) {
    this->sendCommand(
        "AT+CPBW=" + String(index) +
        ",\"" + account.number +
        "\"," + account.numberType +
        ",\"" + account.name + "\""
    );
    return this->isSuccessCommand();
}

SIM900CardAccount SIM900::retrievePhonebook(uint8_t index) {
    this->sendCommand("AT+CPBR=" + String(index));

    SIM900CardAccount accountInfo;
    accountInfo.numberType = static_cast<SIM900PhonebookType>(0);

    String response = this->queryResult();
    response = response.substring(response.indexOf(',') + 1);

    uint8_t delim1 = response.indexOf(','),
        delim2 = response.indexOf(',', delim1 + 1);

    accountInfo.number = response.substring(1, delim1 - 1);
    
    uint8_t type = (uint8_t) response.substring(delim1 + 1, delim2).toInt();
    if(type == 129 || type == 145)
        accountInfo.numberType = static_cast<SIM900PhonebookType>(type);
    else accountInfo.numberType = static_cast<SIM900PhonebookType>(0);

    accountInfo.name = response.substring(delim2 + 2, response.length() - 2);
    return accountInfo;
}

bool SIM900::deletePhonebook(uint8_t index) {
    this->sendCommand("AT+CPBW=" + String(index));
    return this->isSuccessCommand();
}

SIM900PhonebookCapacity SIM900::phonebookCapacity() {
    SIM900PhonebookCapacity capacity;
    capacity.used = capacity.max = 0;
    capacity.memoryType = F("");

    this->sendCommand("AT+CPBS?");

    String response = this->queryResult();
    uint8_t delim1 = response.indexOf(','),
        delim2 = response.indexOf(',', delim1 + 1);

    capacity.memoryType = response.substring(1, delim1 - 1);
    capacity.used = (uint8_t) response.substring(delim1 + 1, delim2).toInt();
    capacity.max = (uint8_t) response.substring(delim2 + 1).toInt();

    return capacity;
}

SIM900CardAccount SIM900::cardNumber() {
    this->sendCommand(F("AT+CNUM"));

    SIM900CardAccount account;
    account.name = F("");

    String response = this->queryResult();
    if(response == F(""))
        return account;

    uint8_t delim1 = response.indexOf(','),
        delim2 = response.indexOf(',', delim1 + 1),
        delim3 = response.indexOf(',', delim2 + 1),
        delim4 = response.indexOf(',', delim3 + 1);

    account.name = response.substring(1, delim1 - 1);
    account.number = response.substring(delim1 + 2, delim2 - 1);
    account.type = (uint8_t) response.substring(delim2 + 1, delim3).toInt();
    account.speed = (uint8_t) response.substring(delim3 + 1, delim4).toInt();
    account.service = (uint8_t) response.substring(delim4 + 1).toInt();
    account.numberType = static_cast<SIM900PhonebookType>(0);

    return account;
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

String SIM900::ipAddress() {
    this->sendCommand(F("AT+CIFSR"));
    return this->rawQueryOnLine(2);
}