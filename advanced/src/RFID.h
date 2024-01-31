#pragma once

#include <cstdint>
#include <Arduino.h>

#define MAX_POSSIBLE_RESPONSE_LEN 100 // Theoretically, we'll never need more than 20 byte, however I want some leeway
#define READ_ID_RESPONSE_OFFSET 5 // Index of the first byte of the ID in the response. More info in RFID.cpp

enum RFIDResponse {
    Success,
    Failure,
    UndefinedResponse,
    InvalidChecksum,
    NoCardProvidedToWriteFunction
};

struct RFIDReadResult {
    RFIDResponse status;
    uint8_t* id;
    uint8_t id_length;

    ~RFIDReadResult() {
        delete[] id;
    }
};

// For more information about the device/protocols used, refer to
// https://www.icstation.com/dual-frequency-rfid-reader-writer-wireless-module-uart-1356mhz-125khz-icid-card-p-12444.html
class RFID {
private:
    arduino::UART& _serial;

    uint8_t __response_buf[MAX_POSSIBLE_RESPONSE_LEN];
    uint8_t __response_buf_len;
    RFIDResponse _read_response_into_buf();

    RFIDReadResult* _read_id(uint8_t command);
    RFIDResponse _write_id(uint8_t command, RFIDReadResult* card_info);

public:
    RFID(arduino::UART& serial) : _serial(serial) {};
    void setup();
    RFIDReadResult* read_id_125KHz();
    RFIDReadResult* read_id_1356MHz();
    RFIDResponse write_id_125KHz(RFIDReadResult* card_info);
    RFIDResponse write_id_1356MHz(RFIDReadResult* card_info);
};