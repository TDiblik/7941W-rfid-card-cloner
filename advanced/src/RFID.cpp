#include "RFID.h"
#include "debug.h"

void RFID::setup() {
    this->_serial.begin(115200);
}

RFIDReadResult* RFID::read_id_125KHz() { return this->_read_id((uint8_t)0x15); };
RFIDReadResult* RFID::read_id_1356MHz() { return this->_read_id((uint8_t)0x10); };
RFIDResponse RFID::write_id_125KHz(RFIDReadResult* card_info) { return this->_write_id((uint8_t)0x16, card_info); };
RFIDResponse RFID::write_id_1356MHz(RFIDReadResult* card_info) { return this->_write_id((uint8_t)0x11, card_info); };

RFIDResponse RFID::_read_rw_response_into_buf() {
    // Cleanup before reading
    for (uint16_t i = 0; i < MAX_POSSIBLE_RW_RESPONSE_LEN; i++) {
        this->__rw_response_buf[i] = 0;
    }
    this->_serial.flush();

    // Read everything
    delay(200);
    uint16_t i = 0;
    while ((this->_serial.available() > 0) && (i < MAX_POSSIBLE_RW_RESPONSE_LEN)) {
        this->__rw_response_buf[i++] = this->_serial.read();
        delay(100);
    }
    this->__rw_response_buf_len = i;

    // This should get optimized away by the compiler when DEBUG == false
    debug_print("Response: ");
    for (i = 0; i < this->__rw_response_buf_len; i++) {
        debug_print_hex(this->__rw_response_buf[i]);
        debug_print(" ");
    }
    debug_println("");

    if (this->__rw_response_buf_len < 3) {
        return RFIDResponse::UndefinedResponse;
    }

    switch (this->__rw_response_buf[3]) { // forth byte is always the response status code
    case 0x81:
        return RFIDResponse::Success;
    case 0x80:
        return RFIDResponse::Failure;
    default:
        return RFIDResponse::UndefinedResponse;
    }
}

// Format of the RFID reponse
// CD DC               0           81             5           x x x x x       X
//   ^                 ^           ^              ^               ^           ^
// protocol header   address   status code   response len   the id bytes   bytes checksum
RFIDReadResult* RFID::_read_id(uint8_t command) {
    this->_serial.write((uint8_t)0xAB);  // protocol header
    this->_serial.write((uint8_t)0xBA);  // protocol header
    this->_serial.write((uint8_t)0x00);  // address
    this->_serial.write(command);        // command
    this->_serial.write((uint8_t)0x00);  // data length
    this->_serial.write(command);        // XOR checksum (in this case always equal to the command, no need to calculate)

    RFIDReadResult* result = new RFIDReadResult();

    RFIDResponse response = this->_read_rw_response_into_buf();
    result->status = response;
    if (response != RFIDResponse::Success) {
        return result;
    }

    uint8_t response_id_length = this->__rw_response_buf[READ_ID_RESPONSE_OFFSET - 1];
    uint8_t response_id_end_index = READ_ID_RESPONSE_OFFSET + response_id_length - 1;
    uint8_t response_checksum = this->__rw_response_buf[READ_ID_RESPONSE_OFFSET + response_id_length];

    //                                  address           ^       status code       ^ response_len
    uint8_t calculated_checksum = this->__rw_response_buf[2] ^ this->__rw_response_buf[3] ^ response_id_length;

    uint8_t* reponse_id = new uint8_t[response_id_length];
    for (uint8_t i = READ_ID_RESPONSE_OFFSET; i <= response_id_end_index; i++) {
        uint8_t current_id_byte = this->__rw_response_buf[i];
        reponse_id[i - READ_ID_RESPONSE_OFFSET] = current_id_byte;
        calculated_checksum ^= current_id_byte;
    }
    result->id = reponse_id;
    result->id_length = response_id_length;

    if (response_checksum != calculated_checksum) {
        result->status = RFIDResponse::InvalidChecksum;
    }
    return result;
}

RFIDResponse RFID::_write_id(uint8_t command, RFIDReadResult* card_info) {
    if (card_info == nullptr || card_info->status == RFIDResponse::Failure || card_info->id_length < 1) {
        return RFIDResponse::NoCardProvidedToWriteFunction;
    }

    // Prepare checksum
    uint8_t checksum = 0x00 ^ command ^ card_info->id_length;

    // Send the command
    this->_serial.write((uint8_t)0xAB);         // protocol header
    this->_serial.write((uint8_t)0xBA);         // protocol header
    this->_serial.write((uint8_t)0x00);         // address
    this->_serial.write(command);               // command
    this->_serial.write(card_info->id_length);  // data length
    for (uint8_t i = 0; i < card_info->id_length; i++) {
        uint8_t current_byte = card_info->id[i];
        this->_serial.write(current_byte);
        checksum ^= current_byte;
    }
    this->_serial.write(checksum);              // XOR checksum

    return this->_read_rw_response_into_buf();

}