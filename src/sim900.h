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

#ifndef SIM900_H
#define SIM900_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "sim900_defs.h"

/**
 * 
 * @class SIM900
 * @brief A class for interfacing with the SIM900 GSM/GPRS module using Arduino and SoftwareSerial.
 *
 * This class provides a wide range of functionalities for working with the SIM900 module, including sending and receiving calls,
 * sending and receiving SMS, updating and extracting real-time clock data, sending HTTP requests, and retrieving various information
 * about the SIM900 module's status and the network it is connected to.
 * 
 */
class SIM900 {
private:
    /// The SoftwareSerial object used for communication with the SIM900 module.
    SoftwareSerial *sim900;

    /// A flag indicating whether Access Point Name (APN) configuration is set.
    bool hasAPN = false;

    /// Send a command to the SIM900 module.
    void sendCommand(String message);

    /// Check if the last command was successful.
    bool isSuccessCommand();

    /// Get the response from the SIM900 module.
    String getResponse();

    /// Get the returned operational mode from the SIM900 module.
    String getReturnedMode();

    /// Perform a raw query operation on a specified line.
    String rawQueryOnLine(uint16_t line);

    /// Retrieve the result of a query operation.
    String queryResult();

public:
    /**
     * 
     * @brief Constructor for the SIM900 class.
     *
     * @param _sim900 A pointer to the SoftwareSerial object for communication with the SIM900 module.
     * 
     */
    SIM900(SoftwareSerial *_sim900);

    /**
     * 
     * @brief Initialize communication with the SIM900 module and perform a handshake.
     *
     * @return True if the handshake is successful, false otherwise.
     * 
     */
    bool handshake();

    /**
     * 
     * @brief Close the communication with the SIM900 module.
     * 
     */
    void close();

    /**
     * 
     * @brief Check if the SIM card is ready.
     *
     * @return True if the SIM card is ready, false otherwise.
     * 
     */
    bool isCardReady();

    /**
     * 
     * @brief Change the PIN code of the SIM card.
     *
     * @param pin The new PIN code to set.
     * @return True if the PIN code change is successful, false otherwise.
     * 
     */
    bool changeCardPin(uint8_t pin);

    /**
     * 
     * @brief Get the signal strength and bit error rate of the network connection.
     *
     * @return A SIM900Signal structure containing signal strength and bit error rate information.
     * 
     */
    SIM900Signal signal();

    /**
     * 
     * @brief Initiate an outgoing call to a phone number.
     *
     * @param number The phone number to call.
     * @return The result of the dialing operation, as a SIM900DialResult.
     * 
     */
    SIM900DialResult dialUp(String number);

    /**
     * 
     * @brief Redial the last outgoing call.
     *
     * This function redials the last outgoing call to the same phone number.
     *
     * @return The result of the redialing operation, as a SIM900DialResult.
     * 
     */
    SIM900DialResult redialUp();

    /**
     * 
     * @brief Accept an incoming call.
     *
     * This function accepts an incoming call from another phone number.
     *
     * @return True if the call acceptance is successful, false otherwise.
     * 
     */
    SIM900DialResult acceptIncomingCall();

    /**
     * 
     * @brief Hang up an active call.
     *
     * This function terminates an ongoing call.
     *
     * @return True if the call is successfully terminated, false otherwise.
     * 
     */
    bool hangUp();

    /**
     * 
     * @brief Send an SMS (Short Message Service).
     *
     * This function sends an SMS message to a specified phone number.
     *
     * @param number The recipient's phone number.
     * @param message The SMS message content.
     * @return True if the SMS is successfully sent, false otherwise.
     * 
     */
    bool sendSMS(String number, String message);

    /**
     * 
     * @brief Connect to an Access Point Name (APN) for mobile data.
     *
     * This function establishes a connection to an APN, enabling mobile data connectivity.
     *
     * @param apn An instance of the SIM900APN structure containing APN, username, and password information.
     * @return True if the APN connection is successful, false otherwise.
     * 
     */
    bool connectAPN(SIM900APN apn);

    /**
     * 
     * @brief Enable the General Packet Radio Service (GPRS) for data communication.
     *
     * This function enables GPRS for data transmission over the mobile network.
     *
     * @return True if GPRS is successfully enabled, false otherwise.
     * 
     */
    bool enableGPRS();

    /**
     * 
     * @brief Send an HTTP request to a remote server.
     *
     * This function sends an HTTP request to a specified server with the provided request parameters.
     *
     * @param request An instance of the SIM900HTTPRequest structure representing the HTTP request.
     * @return A SIM900HTTPResponse structure containing the HTTP response from the server.
     * 
     */
    SIM900HTTPResponse request(SIM900HTTPRequest request);

    /**
     * 
     * @brief Get information about the current network operator.
     *
     * This function retrieves information about the mobile network operator, including its operating mode, format, and name.
     *
     * @return A SIM900Operator structure containing network operator information.
     * 
     */
    SIM900Operator networkOperator();

    /**
     * 
     * @brief Get the SIM card number.
     *
     * This function retrieves information about the SIM card, including the card's name, number, type, speed,
     * the type of phonebook where the number is stored, and the card service.
     *
     * @return A SIM900CardAccount structure containing SIM card information.
     * 
     */
    SIM900CardAccount cardNumber();

    /**
     * 
     * @brief Get the real-time clock (RTC) information.
     *
     * This function retrieves the current date and time from the SIM900 module, including day, month, year, hour,
     * minute, second, and the GMT offset.
     *
     * @return A SIM900RTC structure containing RTC information.
     * 
     */
    SIM900RTC rtc();

    /**
     * 
     * @brief Update the SIM900 module's real-time clock (RTC).
     *
     * This function allows you to configure the SIM900 module's RTC with a new date, time, and GMT offset.
     *
     * @param config An instance of the SIM900RTC structure containing the new RTC configuration.
     * @return True if the RTC update is successful, false otherwise.
     * 
     */
    bool updateRtc(SIM900RTC config);

    /**
     * 
     * @brief Save a contact in the SIM card's phonebook.
     *
     * This function saves a contact entry in the SIM card's phonebook at the specified index.
     *
     * @param index The index at which to save the contact entry.
     * @param account An instance of the SIM900CardAccount structure containing the contact's information.
     * @return True if the contact is successfully saved, false otherwise.
     * 
     */
    bool savePhonebook(uint8_t index, SIM900CardAccount account);

    /**
     * 
     * @brief Delete a contact from the SIM card's phonebook.
     *
     * This function deletes a contact entry from the SIM card's phonebook at the specified index.
     *
     * @param index The index of the contact entry to delete.
     * @return True if the contact is successfully deleted, false otherwise.
     * 
     */
    bool deletePhonebook(uint8_t index);

    /**
     * 
     * @brief Retrieve a contact from the SIM card's phonebook.
     *
     * This function retrieves a contact entry from the SIM card's phonebook at the specified index.
     *
     * @param index The index of the contact entry to retrieve.
     * @return A SIM900CardAccount structure containing the contact's information.
     * 
     */
    SIM900CardAccount retrievePhonebook(uint8_t index);

    /**
     * 
     * @brief Get information about the capacity of the SIM card's phonebook.
     *
     * This function provides information about the capacity of the SIM card's phonebook memory type,
     * including the memory type, used entries, and the maximum number of entries.
     *
     * @return A SIM900PhonebookCapacity structure containing phonebook capacity information.
     * 
     */
    SIM900PhonebookCapacity phonebookCapacity();

    /**
     * 
     * @brief Get the manufacturer name of the SIM900 module.
     *
     * @return The manufacturer name as a String.
     * 
     */
    String manufacturer();

    /**
     * 
     * @brief Get the software release version of the SIM900 module.
     *
     * @return The software release version as a String.
     * 
     */
    String softwareRelease();

    /**
     * 
     * @brief Get the International Mobile Equipment Identity (IMEI) number of the SIM900 module.
     *
     * @return The IMEI number as a String.
     * 
     */
    String imei();

    /**
     * 
     * @brief Get the chip model of the SIM900 module.
     *
     * @return The chip model as a String.
     * 
     */
    String chipModel();

    /**
     * 
     * @brief Get the chip name of the SIM900 module.
     *
     * @return The chip name as a String.
     * 
     */
    String chipName();

    /**
     * 
     * @brief Get the IP address assigned to the SIM900 module.
     *
     * @return The assigned IP address as a String.
     * 
     */
    String ipAddress();
};

#endif