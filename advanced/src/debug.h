#pragma once 

#define DEBUG true
// #include <rfid.h>

void debug_print(const char* msg);
// void debug_print_hex(byte hex_value);
void debug_println(const char* msg);
// void debug_println_response_code(RFIDResponseCode response_code);
void debug_println_double(double value);