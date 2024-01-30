#pragma once

#include "Joystick.h"
#include "LEDMatrix.h"

class Menu {
private:
    uint8_t _current_page_index = 0;
    LEDMatrix& _matrix_ref;
    // void ExecuteSelectedAction(JoystickState action);
public:
    Menu(LEDMatrix& matrix_ref) : _matrix_ref(matrix_ref) {};
    void HandleInput(JoystickState action);
};