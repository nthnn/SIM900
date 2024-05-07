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

/**
 * 
 * @file SIM900_Defs.h
 * @author [Nathanne Isip](https://github.com/nthnn)
 * @brief This header defines various data structures and enumerations for the SIM900 GSM/GPRS module interaction.
 * 
 */

#ifndef SIM900_DEFS_H
#define SIM900_DEFS_H

/**
 * 
 * @enum SIM900DialResult
 * @brief An enumeration representing the possible results of a dialing operation with the SIM900 module.
 *
 * This enumeration encapsulates different dialing results, providing detailed information about the outcome of
 * a call initiation process.
 * 
 */
typedef enum _SIM900DialResult {
    /// No dial tone detected, indicating a failed call initiation.
    SIM900_DIAL_RESULT_NO_DIALTONE,

    /// The line is busy, preventing a call from being established.
    SIM900_DIAL_RESULT_BUSY,

    /// No carrier signal detected, resulting in a call failure.
    SIM900_DIAL_RESULT_NO_CARRIER,

    /// No answer from the remote party, signifying an unsuccessful call attempt.
    SIM900_DIAL_RESULT_NO_ANSWER,

    /// An error occurred during the dialing process, causing the call to fail.
    SIM900_DIAL_RESULT_ERROR,

    /// The dialing operation was successful, and a call has been established.
    SIM900_DIAL_RESULT_OK
} SIM900DialResult;

/**
 * 
 * @enum SIM900OperatorFormat
 * @brief An enumeration representing the available operator format options for the SIM900 module.
 *
 * This enumeration defines different ways to manage operator selection, allowing users to control how the SIM900
 * module interacts with mobile network operators.
 * 
 */
typedef enum _SIM900OperatorFormat {
    /// Automatically select the mobile network operator, simplifying the process.
    SIM900_OPERATOR_FORMAT_AUTO,

    /// Manually specify and select the desired mobile network operator.
    SIM900_OPERATOR_FORMAT_MANUAL,

    /// Deregister from the current network, suspending network registration.
    SIM900_OPERATOR_FORMAT_DEREGISTER,

    /// Set operator without network registration, useful in specific scenarios.
    SIM900_OPERATOR_FORMAT_SET_ONLY,

    /// Combine manual and automatic operator selection for flexibility.
    SIM900_OPERATOR_FORMAT_MANUAL_AUTO
} SIM900OperatorFormat;

/**
 * @param i Integer input to be casted.
 * @return A valid SIM900OperatorFormat value.
 * 
 * @brief This function receives an integer value and checks its range. If the value is not in range, the 
 * default value of SIM900OperatorFormat::SIM900_OPERATOR_FORMAT_AUTO is returned other than that a static_cast from
 * the integer value to SIM900OperatorFormat is performed and the result is returned.
 * 
 * @details From C++11 up to newer versions of C++, enumerators are considered as a specific type rather than integer 
 * values. The same is true for newer Arduino compilers, too. So impilicit cast of integer value to an enum type is no longer allowed. For the sake of the safety of an explicit
 * cast is better to first check the range of the input. 
*/
SIM900OperatorFormat intToSIM900OperatorFormat(int i){
    if (i < SIM900OperatorFormat::SIM900_OPERATOR_FORMAT_AUTO || i > SIM900OperatorFormat::SIM900_OPERATOR_FORMAT_MANUAL_AUTO)
        return SIM900OperatorFormat::SIM900_OPERATOR_FORMAT_AUTO;
    else
        return static_cast<SIM900OperatorFormat>(i);
}

/**
 * 
 * @enum SIM900OperatorMode
 * @brief An enumeration representing different operating modes for the SIM900 module.
 *
 * This enumeration provides options for configuring the operational mode of the SIM900 module, allowing
 * users to adapt the module's behavior based on network and connectivity requirements.
 * 
 */
typedef enum _SIM900OperatorMode {
    /// Standard GSM (2G) operating mode.
    SIM900_OPERATOR_MODE_GSM,

    /// Compact GSM operating mode, optimized for resource-constrained environments.
    SIM900_OPERATOR_MODE_GSM_COMPACT,

    /// UTRAN (3G) operating mode, suitable for 3G network connectivity.
    SIM900_OPERATOR_MODE_UTRAN,

    /// GSM with EGPRS (2.5G) operating mode, offering enhanced data rates.
    SIM900_OPERATOR_MODE_GSM_EGPRS,

    /// UTRAN HSDPA operating mode, enabling high-speed data access.
    SIM900_OPERATOR_MODE_UTRAN_HSDPA,

    /// UTRAN HSUPA operating mode, focused on high-speed uplink data transmission.
    SIM900_OPERATOR_MODE_UTRAN_HSUPA,

    /// UTRAN HSDPA and HSUPA combined mode for versatile 3G connectivity.
    SIM900_OPERATOR_MODE_UTRAN_HSDPA_HSUPA,

    /// E-UTRAN (4G) operating mode, for advanced 4G LTE network connectivity.
    SIM900_OPERATOR_MODE_E_UTRAN
} SIM900OperatorMode;

/**
 * @param i Integer input to be casted.
 * @return A valid SIM900OperatorMode value.
 * 
 * @brief This function receives an integer value and checks its range. If the value is not in range, the 
 * default value of SIM900OperatorMode::SIM900_OPERATOR_MODE_GSM is returned other than that a static_cast from
 * the integer value to SIM900OperatorMode is performed and the result is returned.
 * 
 * @details From C++11 up to newer versions of C++, enumerators are considered as a specific type rather than integer 
 * values. The same is true for newer Arduino compilers, too. So impilicit cast of integer value to an enum type is no longer allowed. For the sake of the safety of an explicit
 * cast is better to first check the range of the input. 
*/
SIM900OperatorMode intToSIM900OperatorMode(int i){
    if (i < SIM900OperatorMode::SIM900_OPERATOR_MODE_GSM || i > SIM900OperatorMode::SIM900_OPERATOR_MODE_E_UTRAN)
        return SIM900OperatorMode::SIM900_OPERATOR_MODE_GSM;
    else
        return static_cast<SIM900OperatorMode>(i);
}

/**
 * 
 * @enum SIM900CardService
 * @brief An enumeration representing the available card service types for the SIM900 module.
 *
 * This enumeration defines various card services, allowing users to configure the module for specific communication needs.
 * 
 */
typedef enum _SIM900CardService {
    /// Asynchronous card service for data communication.
    SIM900_CARD_SERVICE_ASYNC,

    /// Synchronous card service for coordinated data exchange.
    SIM900_CARD_SERVICE_SYNC,

    /// PAD (Packet Assembler/Disassembler) access service.
    SIM900_CARD_SERVICE_PAD_ACCESS,

    /// Packet service for data transmission.
    SIM900_CARD_SERVICE_PACKET,

    /// Voice service for voice calls.
    SIM900_CARD_SERVICE_VOICE,

    /// Fax service for facsimile communication.
    SIM900_CARD_SERVICE_FAX
} SIM900CardService;

/**
 * 
 * @enum SIM900PhonebookType
 * @brief An enumeration representing the phonebook types for storing contacts in the SIM900 module.
 *
 * This enumeration defines different phonebook types, allowing users to manage and organize contact information
 * based on their needs, such as national and international phonebooks.
 * 
 */
typedef enum _SIM900PhonebookType {
    /// National phonebook for storing local contacts.
    SIM900_PHONEBOOK_NATIONAL       = 145,

    /// International phonebook for storing global contacts.
    SIM900_PHONEBOOK_INTERNATIONAL  = 129,

    /// An unspecified or unknown phonebook type.
    SIM900_PHONEBOOK_UNKNOWN        = 0
} SIM900PhonebookType;

/**
 * 
 * @struct SIM900Operator
 * @brief A structure representing mobile network operator information.
 *
 * This structure holds information about the mobile network operator's operating mode, format, and name.
 * 
 */
typedef struct _SIM900Operator {
    /// The operating mode of the mobile network operator.
    SIM900OperatorMode mode;

    /// The operator selection format.
    SIM900OperatorFormat format;

    /// The name of the mobile network operator.
    String name;
} SIM900Operator;

/**
 * 
 * @struct SIM900RTC
 * @brief A structure representing real-time clock (RTC) information.
 *
 * This structure stores date and time information, including day, month, year, hour, minute, second, and GMT offset.
 * 
 */
typedef struct _SIM900RTC {
    /// Date component: day.
    uint8_t day;
    
    /// Date component: month.
    uint8_t month;
    
    /// Date component: year.
    uint8_t year;

    /// Time component: hour.
    uint8_t hour;
    
    /// Time component: minute.
    uint8_t minute;
    
    /// Time component: second.
    uint8_t second;

    /// GMT (Greenwich Mean Time) offset in hours.
    int8_t gmt;
} SIM900RTC;

/**
 * 
 * @struct SIM900APN
 * @brief A structure representing Access Point Name (APN) configuration for mobile data.
 *
 * This structure holds information about the APN, username, and password required for mobile data connectivity.
 * 
 */
typedef struct _SIM900APN {
    /// The Access Point Name (APN) for data connectivity.
    String apn;

    /// The username for APN authentication.
    String username;

    /// The password for APN authentication.
    String password;
} SIM900APN;

/**
 * 
 * @struct SIM900HTTPHeader
 * @brief A structure representing an HTTP header key-value pair.
 *
 * This structure stores an HTTP header field as a key-value pair, facilitating the construction of HTTP requests.
 * 
 */
typedef struct _SIM900HTTPHeader {
    /// The header field key.
    String key;

    /// The header field value.
    String value;
} SIM900HTTPHeader;

/**
 * 
 * @struct SIM900HTTPRequest
 * @brief A structure representing an HTTP request.
 *
 * This structure holds information about an HTTP request, including the HTTP method, data, domain, resource, status,
 * port, and an array of HTTP headers.
 * 
 */
typedef struct _SIM900HTTPRequest {
    /// The HTTP method for the request (e.g., GET, POST).
    String method;

    /// The data to be included in the request (e.g., POST data).
    String data;

    /// The domain or server to which the request is sent.
    String domain;

    /// The resource or URL path to access on the server.
    String resource;

    /// The status of the HTTP request.
    uint8_t status;

    /// The port on which the server is listening (e.g., 80 for HTTP).
    uint16_t port;

    /// An array of HTTP headers associated with the request.
    SIM900HTTPHeader *headers;

    /// The number of HTTP headers in the array.
    uint16_t header_count;
} SIM900HTTPRequest;

/**
 * 
 * @struct SIM900HTTPResponse
 * @brief A structure representing an HTTP response.
 *
 * This structure contains information about an HTTP response, including the HTTP status code, an array of HTTP headers,
 * and the response data.
 * 
 */
typedef struct _SIM900HTTPResponse {
    /// The HTTP status code of the response.
    uint16_t status;

    /// An array of HTTP headers included in the response.
    SIM900HTTPHeader *headers;

    /// The number of HTTP headers in the array.
    uint16_t header_count;

    /// The data received in the HTTP response, such as HTML content or JSON data.
    String data;
} SIM900HTTPResponse;

/**
 * 
 * @struct SIM900CardAccount
 * @brief A structure representing a card account, including name, number, type, and service information.
 *
 * This structure stores information related to a card account, making it useful for managing and accessing
 * card-based services and communication.
 * 
 */
typedef struct _SIM900CardAccount {
    /// The name associated with the card account.
    String name;
    
    /// The card's phone number.
    String number;

    /// The card's type (e.g., SIM card).
    uint8_t type;
    
    /// The card's speed or data rate.
    uint8_t speed;

    /// The type of phonebook (national, international) where the number is stored.
    SIM900PhonebookType numberType;

    /// The type of card service (e.g., voice, data) associated with the card account.
    SIM900CardService service;
} SIM900CardAccount;

/**
 * 
 * @struct SIM900PhonebookCapacity
 * @brief A structure representing the capacity of a phonebook memory type.
 *
 * This structure provides information about the capacity of a specific phonebook memory type, including the type of
 * memory, the number of entries used, and the maximum number of entries that can be stored.
 * 
 */
typedef struct _SIM900PhonebookCapacity {
    /// The type of phonebook memory (e.g., "SM" for SIM memory).
    String memoryType;

    /// The number of entries used in the phonebook memory.
    uint8_t used;

    /// The maximum number of entries that can be stored in the phonebook memory.
    uint8_t max;
} SIM900PhonebookCapacity;

/**
 * 
 * @struct SIM900Signal
 * @brief A structure representing signal strength and bit error rate information.
 *
 * This structure stores information about the signal strength (RSSI) and bit error rate (BER) of the SIM900 module's
 * network connection, which is crucial for assessing the quality of the cellular signal.
 * 
 */
typedef struct _SIM900Signal {
    /// Received Signal Strength Indication (RSSI) in decibels (dBm).
    uint8_t rssi;

    /// Bit Error Rate (BER) as a unitless ratio.
    uint8_t bit_error_rate;
} SIM900Signal;

#endif