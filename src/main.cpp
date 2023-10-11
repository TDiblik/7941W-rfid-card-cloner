#include <Arduino.h>
#include <SoftwareSerial.h>
#include <constants.h>
#include <debug.h>
#include <rfid.h>

SoftwareSerial rfid_serial = SoftwareSerial(10, 11); // RX,TX POV of the device, meaning you should connect TX to 10 and RX to 11 on an Arduino

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
    rfid_cleanup_IDResponse(response_id_125khz);
    response_id_125khz = rfid_read_ID_125KHz(rfid_serial);
    debug_println_response_code(response_id_125khz.code);
  }

  if (digitalRead(WRITE_125KHz_BUTTON) == HIGH) {
    debug_println("Writing 125KHz...");
    RFIDResponseCode response_code = rfid_write_ID_125KHz(rfid_serial, response_id_125khz);
    debug_println_response_code(response_code);
  }

  if (digitalRead(READ_13_56MHz_BUTTON) == HIGH) {
    debug_println("Reading 13.56MHz...");
    rfid_cleanup_IDResponse(response_id_1356mhz);
    response_id_1356mhz = rfid_read_ID_13_56MHz(rfid_serial);
    debug_println_response_code(response_id_1356mhz.code);
  }

  if (digitalRead(WRITE_13_56MHz_BUTTON) == HIGH) {
    debug_println("Writing 13.56MHz...");
    RFIDResponseCode response_code = rfid_write_ID_13_56MHz(rfid_serial, response_id_1356mhz);
    debug_println_response_code(response_code);
  }
  delay(2500);
}
