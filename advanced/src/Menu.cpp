#include "Menu.h"
#include "LEDMatrix.h"

void Menu::ExecuteS1() {
    delete this->_last_read_125KHz;
    delete this->_last_read_1356MHz;

    RFIDReadResult* result_1356 = this->_rfid_ref.read_id_1356MHz();
    RFIDReadResult* result_125 = this->_rfid_ref.read_id_125KHz();

    // todo: handle
}

void Menu::ExecuteS2() {
    delete this->_last_read_125KHz;

    RFIDReadResult* result = nullptr;
    for (uint8_t i = 0; i < NUMBER_OF_EXECUTE_RETRIES; i++) {
        result = this->_rfid_ref.read_id_125KHz();
        if (result->status == RFIDResponse::Success) { break; }
    }
    this->_display_rfid_response_to_symbol(result->status);
    this->_last_read_125KHz = result;
}

void Menu::ExecuteS3() {
    delete this->_last_read_1356MHz;

    RFIDReadResult* result = nullptr;
    for (uint8_t i = 0; i < NUMBER_OF_EXECUTE_RETRIES; i++) {
        result = this->_rfid_ref.read_id_1356MHz();
        if (result->status == RFIDResponse::Success) { break; }
    }
    this->_display_rfid_response_to_symbol(result->status);
    this->_last_read_1356MHz = result;
}

void Menu::ExecuteZ1() {
    // todo: try to write into both
}

void Menu::ExecuteZ2() {
    RFIDResponse response;
    for (uint8_t i = 0; i < NUMBER_OF_EXECUTE_RETRIES; i++) {
        response = this->_rfid_ref.write_id_125KHz(this->_last_read_125KHz);
        if (response == RFIDResponse::Success) { break; }
        delay(WRITE_RETRY_DELAY_MS); // Give the device some time to process possible previous commands (when write fails, it takes longer for the device to recover)
    }
    this->_display_rfid_response_to_symbol(response);
}

void Menu::ExecuteZ3() {
    RFIDResponse response;
    for (uint8_t i = 0; i < NUMBER_OF_EXECUTE_RETRIES; i++) {
        response = this->_rfid_ref.write_id_1356MHz(this->_last_read_125KHz);
        if (response == RFIDResponse::Success) { break; }
        delay(WRITE_RETRY_DELAY_MS); // Give the device some time to process possible previous commands (when write fails, it takes longer for the device to recover)
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
    case RFIDResponse::Fail:
        this->_matrix_ref.blink(X_BITMAP);
        break;
    case RFIDResponse::NoCardProvidedToWriteFunction:
        this->_matrix_ref.blink(NO_CARD_PROVIDED_BITMAP);
        break;
    }
}

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