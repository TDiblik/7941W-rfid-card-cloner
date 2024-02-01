#include "Menu.h"
#include "LEDMatrix.h"
#include "debug.h"

void Menu::handle_input(JoystickState action) {
    switch (action) {
    case JoystickState::Centered:
        delay(10);
        return;
    case JoystickState::Pressed:
        this->_matrix_ref.draw(LOADING_BITMAP);
        this->_menu_actions[this->_current_page_index](this);
        break;
    case JoystickState::PointingDown:
        if (this->_current_page_index == 0) {
            break;
        }
        this->_current_page_index--;
        this->_matrix_ref.draw(MENU_BITMAPS[this->_current_page_index]);
        break;
    case JoystickState::PointingUP:
        if (this->_current_page_index == MENU_BITMAPS_LAST_INDEX) {
            break;
        }
        this->_current_page_index++;
        this->_matrix_ref.draw(MENU_BITMAPS[this->_current_page_index]);
        break;
    };
    delay(500);
}

void Menu::ExecuteS1() {
    RFIDReadResult* result_125 = nullptr;
    RFIDReadResult* result_1356 = nullptr;

    bool success_125 = false;
    bool success_1356 = false;
    for (uint8_t i = 1; i <= NUMBER_OF_EXECUTE_RETRIES; i++) {
        if (!success_125) { result_125 = this->_rfid_ref.read_id_125KHz(); }
        if (!success_1356) { result_1356 = this->_rfid_ref.read_id_1356MHz(); }

        if (!success_125 && result_125->status == RFIDResponse::Success) { success_125 = true; }
        if (!success_125 && i != NUMBER_OF_EXECUTE_RETRIES) { delete result_125; }
        if (!success_1356 && result_1356->status == RFIDResponse::Success) { success_1356 = true; }
        if (!success_1356 && i != NUMBER_OF_EXECUTE_RETRIES) { delete result_1356; }

        if (success_125 && success_1356) { break; }
    }

    // Both 125KHz and 13.56MHz got recognized.
    if (success_125 && success_1356) {
        this->_display_rfid_response_to_symbol(RFIDResponse::Success);
        delay(1000);

        delete this->_last_read_125KHz;
        delete this->_last_read_1356MHz;
        this->_last_read_125KHz = result_125;
        this->_last_read_1356MHz = result_1356;

        this->_matrix_ref.blink(NUMBER_23_BITMAP);
        return;
    }

    // Prioritize partial 125KHz findings before 13.56MHz, as those chips tend to be more used
    // for restricted access areas
    if (success_125) {
        goto save_125_into_ram;
    }
    if (success_1356) {
        goto save_1356_into_ram;
    }

    // We can say that 125KHz was recognized, however it was not probably 100% read correctly
    if (result_125 != nullptr && result_125->status != RFIDResponse::Failure) {
    save_125_into_ram:
        this->_display_rfid_response_to_symbol(result_125->status);
        delay(1000);
        delete this->_last_read_125KHz;
        this->_last_read_125KHz = result_125;
        this->_matrix_ref.blink(NUMBER_2_BITMAP);
        return;
    }

    // We can say that 13.56MHz was recognized, however it was not probably 100% read correctly
    if (result_1356 != nullptr && result_1356->status != RFIDResponse::Failure) {
    save_1356_into_ram:
        this->_display_rfid_response_to_symbol(result_1356->status);
        delay(1000);
        delete this->_last_read_1356MHz;
        this->_last_read_1356MHz = result_1356;
        this->_matrix_ref.blink(NUMBER_3_BITMAP);
        return;
    }

    // Nothing got recognized
    this->_display_rfid_response_to_symbol(RFIDResponse::Failure);
}

void Menu::ExecuteS2() {
    RFIDReadResult* result = nullptr;
    for (uint8_t i = 1; i <= NUMBER_OF_EXECUTE_RETRIES; i++) {
        result = this->_rfid_ref.read_id_125KHz();
        if (result->status == RFIDResponse::Success) { break; }
        if (i != NUMBER_OF_EXECUTE_RETRIES) { delete result; }
    }
    this->_display_rfid_response_to_symbol(result->status);

    delete this->_last_read_125KHz;
    this->_last_read_125KHz = result;
}

void Menu::ExecuteS3() {
    RFIDReadResult* result = nullptr;
    for (uint8_t i = 1; i <= NUMBER_OF_EXECUTE_RETRIES; i++) {
        result = this->_rfid_ref.read_id_1356MHz();
        if (result->status == RFIDResponse::Success) { break; }
        if (i != NUMBER_OF_EXECUTE_RETRIES) { delete result; }
    }
    this->_display_rfid_response_to_symbol(result->status);

    delete this->_last_read_1356MHz;
    this->_last_read_1356MHz = result;
}


/*
 Note 1:
    so, you may be wondering why I'm reading and then instantly deleting a value,
    well, I bought a 7941W clone (!) .... and after debugging for the whole afternoon I found out
    that if you issue a write command, the clone gets confused until you issue (any) read command.
*/

void Menu::ExecuteZ1() {
    // Refer to "Note 1"
    {
        RFIDReadResult* _ = this->_rfid_ref.read_id_125KHz();
        delete _;
        RFIDReadResult* __ = this->_rfid_ref.read_id_1356MHz();
        delete __;
    }

    RFIDResponse response_125;
    RFIDResponse response_1356;

    bool success_125 = false;
    bool success_1356 = false;
    for (uint8_t i = 1; i <= NUMBER_OF_EXECUTE_RETRIES; i++) {
        if (!success_125) { response_125 = this->_rfid_ref.write_id_125KHz(this->_last_read_125KHz); }
        if (!success_1356) { response_1356 = this->_rfid_ref.write_id_1356MHz(this->_last_read_1356MHz); }

        if (!success_125 && response_125 == RFIDResponse::Success) { success_125 = true; }
        if (!success_1356 && response_1356 == RFIDResponse::Success) { success_1356 = true; }

        if (success_125 && success_1356) { break; }
    }

    if (success_125 && success_1356) {
        this->_matrix_ref.blink(NUMBER_23_BITMAP);
        delay(1000);
        this->_display_rfid_response_to_symbol(RFIDResponse::Success);
        return;
    }

    this->_matrix_ref.blink(NUMBER_2_BITMAP);
    this->_display_rfid_response_to_symbol(response_125);
    delay(1000);
    this->_matrix_ref.blink(NUMBER_3_BITMAP);
    this->_display_rfid_response_to_symbol(response_1356);
}

void Menu::ExecuteZ2() {
    // Refer to "Note 1"
    {
        RFIDReadResult* _ = this->_rfid_ref.read_id_125KHz();
        delete _;
    }

    RFIDResponse response;
    for (uint8_t i = 1; i <= NUMBER_OF_EXECUTE_RETRIES; i++) {
        response = this->_rfid_ref.write_id_125KHz(this->_last_read_125KHz);
        if (response == RFIDResponse::Success) { break; }
    }
    this->_display_rfid_response_to_symbol(response);
}

void Menu::ExecuteZ3() {
    // Refer to "Note 1"
    {
        RFIDReadResult* _ = this->_rfid_ref.read_id_1356MHz();
        delete _;
    }

    RFIDResponse response;
    for (uint8_t i = 1; i <= NUMBER_OF_EXECUTE_RETRIES; i++) {
        response = this->_rfid_ref.write_id_1356MHz(this->_last_read_1356MHz);
        if (response == RFIDResponse::Success) { break; }
    }
    this->_display_rfid_response_to_symbol(response);
}

void Menu::_display_rfid_response_to_symbol(RFIDResponse status) {
    switch (status) {
    case RFIDResponse::Success:
        this->_matrix_ref.blink(CHECKMARK_BITMAP);
        break;
    case RFIDResponse::UndefinedResponse:
        this->_matrix_ref.blink(QUESTIONMARK_BITMAP);
        break;
    case RFIDResponse::InvalidChecksum:
        this->_matrix_ref.blink(EXCLAMATIONMARK_BITMAP);
        break;
    case RFIDResponse::Failure:
        this->_matrix_ref.blink(X_BITMAP);
        break;
    case RFIDResponse::NoCardProvidedToWriteFunction:
        this->_matrix_ref.blink(NO_CARD_PROVIDED_BITMAP);
        break;
    }
}