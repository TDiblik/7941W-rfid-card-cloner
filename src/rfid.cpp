#include <Arduino.h>
#include <SoftwareSerial.h>
#include <constants.h>
#include <debug.h>
#include <rfid.h>

const u16 __utils_response_buf_max_len = 100; // Theoretically, we'll never need more than 20 byte, however I want some leeway
byte __utils_response_buf[__utils_response_buf_max_len];
u16 __utils_response_buf_len;
RFIDResponseCode _rfid_get_response(SoftwareSerial& rfid_serial) {
    u16 i = 0;

    delay(200);
    while ((rfid_serial.available() > 0) && (i < __utils_response_buf_max_len)) {
        __utils_response_buf[i++] = rfid_serial.read();
        delay(100);
    }
    __utils_response_buf_len = i;

    // In theory, this should get optimized away by the compiler (debug function calls will be empty),
    // but I want to make sure that this piece of code never runs in production (empty for loop wastes CPU cycles)
#ifdef DEBUG
    debug_print("Response: ");
    for (i = 0; i < __utils_response_buf_len; i++) {
        debug_print_hex(__utils_response_buf[i]);
        debug_print(" ");
    }
    debug_println("");
#endif

    if (__utils_response_buf_len < 3) {
        return 2;
    }

    switch (__utils_response_buf[3]) { // forth byte is always the response status code
    case 0x80:
        return 1;
    case 0x81:
        return 0;
    default:
        return 2;
    }
}

// reason for the offset
// CD DC               0           81             5           x x x x x       X
//   ^                 ^           ^              ^               ^           ^
// protocol header   address   status code   response len   the id bytes   bytes checksum
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
        byte response_checksum = __utils_response_buf[response_id_end];

        // address ^ status code ^ response_len
        byte calculated_checksum = __utils_response_buf[2] ^ __utils_response_buf[3] ^ response.id_len;

        byte* reponse_id = new byte[response.id_len];
        for (byte i = __read_id_response_offset; i < response_id_end; i++) {
            byte current_byte_of_id = __utils_response_buf[i];
            reponse_id[i - __read_id_response_offset] = current_byte_of_id;
            calculated_checksum ^= current_byte_of_id;
        }
        response.id = reponse_id;

        if (response_checksum != calculated_checksum) {
            response.code = 3;
        }
    }
    return response;
}

IDResponse rfid_read_ID_125KHz(SoftwareSerial& rfid_serial) {
    return _rfid_read_ID(rfid_serial, (byte)0x15);
}

IDResponse rfid_read_ID_13_56MHz(SoftwareSerial& rfid_serial) {
    return _rfid_read_ID(rfid_serial, (byte)0x10);
}

RFIDResponseCode _rfid_write_ID(SoftwareSerial& rfid_serial, IDResponse& id_response, byte command) {
    if (id_response.code != 0 || id_response.id_len < 1) {
        return 4;
    }

    // Prepare checksum
    byte checksum = 0x00 ^ command ^ id_response.id_len;

    // Send the command
    rfid_serial.write((byte)0xAB);                  // protocol header
    rfid_serial.write((byte)0xBA);                  // protocol header
    rfid_serial.write((byte)0x00);                  // address
    rfid_serial.write(command);                     // command
    rfid_serial.write(id_response.id_len);          // data length
    for (byte i = 0; i < id_response.id_len; i++) { // ID data itself
        byte current_byte = id_response.id[i];
        rfid_serial.write(current_byte);
        checksum ^= current_byte;
    }
    rfid_serial.write(checksum);                    // XOR checksum

    return _rfid_get_response(rfid_serial);
}

RFIDResponseCode rfid_write_ID_125KHz(SoftwareSerial& rfid_serial, IDResponse& id_response) {
    return _rfid_write_ID(rfid_serial, id_response, 0x16);
}

RFIDResponseCode rfid_write_ID_13_56MHz(SoftwareSerial& rfid_serial, IDResponse& id_response) {
    return _rfid_write_ID(rfid_serial, id_response, 0x11);
}

void rfid_cleanup_IDResponse(IDResponse& response) {
    if (response.id != nullptr) {
        delete[] response.id;
        response.id = nullptr;
    }
}