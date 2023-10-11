#include <Arduino.h>
#include <SoftwareSerial.h>
#include "utils.h"

#define DEBUG true
#define READ_125KHz_BUTTON 2
#define WRITE_125KHz_BUTTON 3
#define READ_13_56MHz_BUTTON 4
#define WRITE_13_56MHz_BUTTON 5
SoftwareSerial rfid_serial = SoftwareSerial(10, 11); // RX,TX POV of the device, meaning you should connect TX to 10 and RX to 11 on an Arduino

void debug_println(const char* msg) {
#ifdef DEBUG
  Serial.println(msg);
#endif
}

void debug_println_response_code(u8 response_code) {
  switch (response_code) {
  case 0:
    debug_println("Operation Succeeded");
    break;
  case 1:
    debug_println("Operation Failed");
    break;
  case 2:
    debug_println("Undefined response");
    break;
  }
}

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  debug_println("Starting...");
#endif
  rfid_serial.begin(115000);

  pinMode(READ_125KHz_BUTTON, INPUT);
  pinMode(READ_13_56MHz_BUTTON, INPUT);
}

IDResponse response_id_125khz;
IDResponse response_id_1356mhz;
void loop() {
  if (digitalRead(READ_125KHz_BUTTON) == HIGH) {
    debug_println("Reading 125KHz...");
    cleanup_IDResponse(response_id_125khz);
    response_id_125khz = rfid_read_ID_125KHz(rfid_serial);
    debug_println_response_code(response_id_125khz.code);
  }

  if (digitalRead(WRITE_125KHz_BUTTON) == HIGH) {
  }

  if (digitalRead(READ_13_56MHz_BUTTON) == HIGH) {
    debug_println("Reading 13.56MHz...");
    cleanup_IDResponse(response_id_1356mhz);
    response_id_1356mhz = rfid_read_ID_13_56MHz(rfid_serial);
    debug_println_response_code(response_id_1356mhz.code);
  }

  if (digitalRead(WRITE_13_56MHz_BUTTON) == HIGH) {
  }
  delay(2500);
}
