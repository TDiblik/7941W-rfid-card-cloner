#include "Menu.h"
#include "LEDMatrix.h"

void Menu::ExecuteS1() {
    this->_rfid_ref.read_125KHz();
}

void Menu::ExecuteS2() {
    Serial.println("s2");
}

void Menu::ExecuteS3() {
    Serial.println("s3");
}

void Menu::ExecuteZ1() {
    Serial.println("Z1");
}

void Menu::ExecuteZ2() {
    Serial.println("Z2");
}

void Menu::ExecuteZ3() {
    Serial.println("Z3");
}

void Menu::HandleInput(JoystickState action) {
    switch (action) {
    case JoystickState::Centered:
        delay(10);
        return;
    case JoystickState::Pressed:
        this->_menu_actions[this->_current_page_index](this);
        break;
    case JoystickState::PointingDown:
        if (this->_current_page_index == 0) {
            break;
        }
        this->_current_page_index--;
        this->_matrix_ref.Draw(MENU_BITMAPS[this->_current_page_index]);
        break;
    case JoystickState::PointingUP:
        if (this->_current_page_index == MENU_BITMAPS_LAST_INDEX) {
            break;
        }
        this->_current_page_index++;
        this->_matrix_ref.Draw(MENU_BITMAPS[this->_current_page_index]);
        break;
    };
    delay(500);
}