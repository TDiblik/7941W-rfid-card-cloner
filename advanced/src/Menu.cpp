#include "Menu.h"
#include "LEDMatrix.h"

void Menu::HandleInput(JoystickState action) {
    switch (action) {
    case JoystickState::Centered:
        break;
    case JoystickState::PointingDown:
        if (this->_current_page_index == MENU_BITMAPS_LAST_INDEX) {
            break;
        }
        this->_current_page_index++;
        this->_matrix_ref.Draw(MENU_BITMAPS[this->_current_page_index]);
        break;
    case JoystickState::PointingUP:
        if (this->_current_page_index == 0) {
            break;
        }
        this->_current_page_index--;
        this->_matrix_ref.Draw(MENU_BITMAPS[this->_current_page_index]);
        break;
    };
}