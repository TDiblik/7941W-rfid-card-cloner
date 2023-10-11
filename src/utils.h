typedef struct IDResponse {
    u8 code;
    byte id_len;
    byte id_checksum;
    byte* id;
} IDResponse;

IDResponse rfid_read_ID_125KHz(SoftwareSerial& rfid_serial);
IDResponse rfid_read_ID_13_56MHz(SoftwareSerial& rfid_serial);
void cleanup_IDResponse(IDResponse& response);