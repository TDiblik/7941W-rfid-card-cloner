#include <Arduino.h>
#include <SoftwareSerial.h>

const u16 __utils_response_buf_max__len = 500;
byte __utils_response_buf[__utils_response_buf_max__len];
u16 __utils_response_buf_len;

// 0 => success
// 1 => fail
// 2 => undefined response
u8 _rfid_get_response(SoftwareSerial* rfid_serial) {
    u16 i = 0;

    delay(100);
    while ((rfid_serial->available() > 0) && (i < __utils_response_buf_max__len)) {
        __utils_response_buf[i++] = rfid_serial->read();
        delay(50);
    }
    __utils_response_buf_len = i;

    Serial.print("Response: ");
    for (i = 0; i < __utils_response_buf_len; i++) {
        Serial.print(__utils_response_buf[i], HEX);
        Serial.print(" ");
    }
    Serial.println("");

    if (__utils_response_buf_len < 3) {
        return 2;
    }

    switch (__utils_response_buf[3]) {
    case 0x80:
        return 1;
    case 0x81:
        return 0;
    default:
        return 2;
    }
}

void rfid_read_ID_125KHz(SoftwareSerial* rfid_serial) {
    rfid_serial->write((byte)0xAB);
    rfid_serial->write((byte)0xBA);
    rfid_serial->write((byte)0x00);  // address
    rfid_serial->write((byte)0x15);  // command
    rfid_serial->write((byte)0x00);  // data length
    rfid_serial->write((byte)0x15);  // XOR checksum

    u8 response_code = _rfid_get_response(rfid_serial);
    switch (response_code) {
    case 0:
        Serial.println("Operation Succeeded");
        break;
    case 1:
        Serial.println("Operation Failed");
        break;
    case 2:
        Serial.println("Undefined response");
        break;
    }
}

void rfid_read_ID_13_56MHz(SoftwareSerial* rfid_serial) {
    rfid_serial->write((byte)0xAB);
    rfid_serial->write((byte)0xBA);
    rfid_serial->write((byte)0x00);  // address
    rfid_serial->write((byte)0x10);  // command
    rfid_serial->write((byte)0x00);  // data length
    rfid_serial->write((byte)0x15);  // XOR checksum

    u8 response_code = _rfid_get_response(rfid_serial);
    switch (response_code) {
    case 0:
        Serial.println("Operation Succeeded");
        break;
    case 1:
        Serial.println("Operation Failed");
        break;
    case 2:
        Serial.println("Undefined response");
        break;
    }
}