#include <Arduino.h>
#include "debug.h"

void debug_print(const char* msg) {
#if DEBUG
    Serial.print(msg);
#endif
}

void debug_print_hex(byte hex_value) {
#if DEBUG
    Serial.print(hex_value, HEX);
#endif
}

void debug_println(const char* msg) {
#if DEBUG
    Serial.println(msg);
#endif
}

void debug_println_double(double value) {
#if DEBUG
    Serial.println(value, 2);
#endif
}

// void debug_println_response_code(RFIDResponseCode response_code) {
// #if DEBUG
//     switch (response_code) {
//     case 0:
//         debug_println("Operation Succeeded");
//         break;
//     case 1:
//         debug_println("Operation Failed");
//         break;
//     case 2:
//         debug_println("Undefined Response");
//         break;
//     case 3:
//         debug_println("Invalid checksum, the ID read is incorrect");
//         break;
//     case 4:
//         debug_println("No id has been read yet");
//         break;
//     }
// #endif
// }
