#ifndef SIM900_DEFS_H
#define SIM900_DEFS_H

typedef enum _SIM900DialResult {
    SIM900_DIAL_RESULT_NO_DIALTONE,
    SIM900_DIAL_RESULT_BUSY,
    SIM900_DIAL_RESULT_NO_CARRIER,
    SIM900_DIAL_RESULT_NO_ANSWER,
    SIM900_DIAL_RESULT_ERROR,
    SIM900_DIAL_RESULT_OK
} SIM900DialResult;

typedef enum _SIM900OperatorFormat {
    SIM900_OPERATOR_FORMAT_AUTO,
    SIM900_OPERATOR_FORMAT_MANUAL,
    SIM900_OPERATOR_FORMAT_DEREGISTER,
    SIM900_OPERATOR_FORMAT_SET_ONLY,
    SIM900_OPERATOR_FORMAT_MANUAL_AUTO
} SIM900OperatorFormat;

typedef enum _SIM900OperatorMode {
    SIM900_OPERATOR_MODE_GSM,
    SIM900_OPERATOR_MODE_GSM_COMPACT,
    SIM900_OPERATOR_MODE_UTRAN,
    SIM900_OPERATOR_MODE_GSM_EGPRS,
    SIM900_OPERATOR_MODE_UTRAN_HSDPA,
    SIM900_OPERATOR_MODE_UTRAN_HSUPA,
    SIM900_OPERATOR_MODE_UTRAN_HSDPA_HSUPA,
    SIM900_OPERATOR_MODE_E_UTRAN
} SIM900OperatorMode;

typedef enum _SIM900CardService {
    SIM900_CARD_SERVICE_ASYNC,
    SIM900_CARD_SERVICE_SYNC,
    SIM900_CARD_SERVICE_PAD_ACCESS,
    SIM900_CARD_SERVICE_PACKET,
    SIM900_CARD_SERVICE_VOICE,
    SIM900_CARD_SERVICE_FAX
} SIM900CardService;

typedef enum _SIM900PhonebookType {
    SIM900_PHONEBOOK_NATIONAL       = 145,
    SIM900_PHONEBOOK_INTERNATIONAL  = 129,
    SIM900_PHONEBOOK_UNKNOWN        = 0
} SIM900PhonebookType;

typedef struct _SIM900Operator {
    SIM900OperatorMode mode;
    SIM900OperatorFormat format;
    String name;
} SIM900Operator;

typedef struct _SIM900RTC {
    uint8_t day, month, year,
        hour, minute, second;
    int8_t gmt;
} SIM900RTC;

typedef struct _SIM900APN {
    String apn, username, password;
} SIM900APN;

typedef struct _SIM900HTTPHeader {
    String key, value;
} SIM900HTTPHeader;

typedef struct _SIM900HTTPRequest {
    String method, data;
    String domain, resource;
    uint8_t status;
    uint16_t port;
    SIM900HTTPHeader *headers;
    uint16_t header_count;
} SIM900HTTPRequest;

typedef struct _SIM900HTTPResponse {
    uint16_t status;
    SIM900HTTPHeader *headers;
    uint16_t header_count;
    String data;
} SIM900HTTPResponse;

typedef struct _SIM900CardAccount {
    String name, number;
    uint8_t type, speed;
    SIM900PhonebookType numberType;
    SIM900CardService service;
} SIM900CardAccount;

#endif