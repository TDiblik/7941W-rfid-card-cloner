#pragma once

#include <SoftwareSerial.h>

/* Possible response codes:
  0 => success
  1 => fail
  2 => undefined response
  3 => invalid checksum, probably error while reading (always calculated from all the bytes sent/received, without the protocol header)
  4 => no id provided to a write function
*/
typedef byte RFIDResponseCode;

typedef struct IDResponse {
  RFIDResponseCode code;
  byte id_len;
  byte* id;
} IDResponse;
IDResponse rfid_read_ID_125KHz(SoftwareSerial& rfid_serial);
IDResponse rfid_read_ID_13_56MHz(SoftwareSerial& rfid_serial);

RFIDResponseCode rfid_write_ID_125KHz(SoftwareSerial& rfid_serial, IDResponse& id_response);
RFIDResponseCode rfid_write_ID_13_56MHz(SoftwareSerial& rfid_serial, IDResponse& id_response);

void rfid_cleanup_IDResponse(IDResponse& response);