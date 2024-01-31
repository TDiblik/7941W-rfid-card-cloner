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

void debug_println_number(double value) {
#if DEBUG
    Serial.println(value, 2);
#endif
}