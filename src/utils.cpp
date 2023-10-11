#include <Arduino.h>
#include <SoftwareSerial.h>
#include <utils.h>

const u16 __utils_response_buf_max__len = 500;
byte __utils_response_buf[__utils_response_buf_max__len];
u16 __utils_response_buf_len;

// 0 => success
// 1 => fail
// 2 => undefined response
u8 _rfid_get_response(SoftwareSerial& rfid_serial) {
    u16 i = 0;

    delay(100);
    while ((rfid_serial.available() > 0) && (i < __utils_response_buf_max__len)) {
        __utils_response_buf[i++] = rfid_serial.read();
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

// reason for the offset
// CD DC             0           81      5              x x x x x       X
//   ^               ^           ^       ^                  ^           ^
// protocol header  address   success   response len    the id bytes  id bytes checksum
const byte __read_id_response_offset = 5;
IDResponse _rfid_read_ID(SoftwareSerial& rfid_serial, byte command) {
    rfid_serial.write((byte)0xAB);  // protocol header
    rfid_serial.write((byte)0xBA);  // protocol header
    rfid_serial.write((byte)0x00);  // address
    rfid_serial.write(command);     // command
    rfid_serial.write((byte)0x00);  // data length
    rfid_serial.write(command);     // XOR checksum (ironically, in this case, always equal to the command)

    IDResponse response;
    response.code = _rfid_get_response(rfid_serial);
    if (response.code == 0) {
        response.id_len = __utils_response_buf[__read_id_response_offset - 1];

        byte response_id_end = response.id_len + __read_id_response_offset;
        response.id_checksum = __utils_response_buf[response_id_end];

        byte* reponse_id = new byte[response.id_len];
        for (byte i = __read_id_response_offset; i < response_id_end; i++) {
            reponse_id[i - __read_id_response_offset] = __utils_response_buf[i];
        }
        response.id = reponse_id;
    }
    return response;
}

IDResponse rfid_read_ID_125KHz(SoftwareSerial& rfid_serial) {
    return _rfid_read_ID(rfid_serial, (byte)0x15);
}

IDResponse rfid_read_ID_13_56MHz(SoftwareSerial& rfid_serial) {
    return _rfid_read_ID(rfid_serial, (byte)0x10);
}

void cleanup_IDResponse(IDResponse& response) {
    if (response.id != nullptr) {
        delete[] response.id;
        response.id = nullptr;
    }
}