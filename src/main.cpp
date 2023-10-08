#include <Arduino.h>
#include <SoftwareSerial.h>
#include "utils.h"

#define DEBUG true
#define READ_125KHz_BUTTON 2
#define READ_13_56MHz_BUTTON 4
SoftwareSerial rfid_serial = SoftwareSerial(10, 11); // RX,TX POV of the device, meaning you should connect TX to 10 and RX to 11 on an Arduino

void debug_println(const char* msg) {
#ifdef DEBUG
  Serial.println(msg);
#endif
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

void loop() {
  if (digitalRead(READ_125KHz_BUTTON) == HIGH) {
    debug_println("Reading 125KHz...");
    rfid_read_ID_125KHz(&rfid_serial);
  }
  if (digitalRead(READ_13_56MHz_BUTTON) == HIGH) {
    debug_println("Reading 13.56MHz...");
    // rfid_get_response(&rfid_serial);
  }
  delay(5000);
}
