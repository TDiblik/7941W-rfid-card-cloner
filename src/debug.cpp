#include <Arduino.h>
#include <constants.h>
#include <rfid.h>

void debug_print(const char* msg) {
#ifdef DEBUG
    Serial.print(msg);
#endif
}

void debug_print_hex(byte hex_value) {
#ifdef DEBUG
    Serial.print(hex_value, HEX);
#endif
}

void debug_println(const char* msg) {
#ifdef DEBUG
    Serial.println(msg);
#endif
}

void debug_println_response_code(RFIDResponseCode response_code) {
#ifdef DEBUG
    switch (response_code) {
    case 0:
        debug_println("Operation Succeeded");
        break;
    case 1:
        debug_println("Operation Failed");
        break;
    case 2:
        debug_println("Undefined Response");
        break;
    case 3:
        debug_println("Invalid checksum, the ID read is incorrect");
        break;
    case 4:
        debug_println("No id has been read yet");
        break;
    }
#endif
}
