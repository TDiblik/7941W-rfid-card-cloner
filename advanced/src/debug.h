#pragma once 

#define DEBUG true

void debug_print(const char* msg);
void debug_print_hex(byte hex_value);
void debug_println(const char* msg);
// void debug_println_response_code(RFIDResponseCode response_code);
void debug_println_number(double value);