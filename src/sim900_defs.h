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

typedef struct _SIM900Operator {
    uint16_t mode, format;
    String name;
} SIM900Operator;

typedef struct _SIM900RTC {
    uint8_t day, month, year,
        hour, minute, second;
    int8_t gmt;
} SIM900RTC;

#endif