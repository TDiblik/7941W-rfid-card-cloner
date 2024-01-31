#pragma once

#include "Joystick.h"
#include "LEDMatrix.h"
#include "RFID.h"

#define NUMBER_OF_EXECUTE_RETRIES (uint8_t)5

class Menu {
private:
    uint8_t _current_page_index = 0;
    LEDMatrix& _matrix_ref;
    RFID& _rfid_ref;

    RFIDReadResult* _last_read_125KHz = nullptr;
    RFIDReadResult* _last_read_1356MHz = nullptr;

    typedef void(*MenuActions)(Menu*);
    MenuActions _menu_actions[6] = { &Menu::ExecuteS1Wrapper, &Menu::ExecuteS2Wrapper, &Menu::ExecuteS3Wrapper,
                                   &Menu::ExecuteZ1Wrapper, &Menu::ExecuteZ2Wrapper, &Menu::ExecuteZ3Wrapper, };

    void ExecuteS1();
    static void ExecuteS1Wrapper(Menu* menu) { menu->ExecuteS1(); }
    void ExecuteS2();
    static void ExecuteS2Wrapper(Menu* menu) { menu->ExecuteS2(); }
    void ExecuteS3();
    static void ExecuteS3Wrapper(Menu* menu) { menu->ExecuteS3(); }
    void ExecuteZ1();
    static void ExecuteZ1Wrapper(Menu* menu) { menu->ExecuteZ1(); }
    void ExecuteZ2();
    static void ExecuteZ2Wrapper(Menu* menu) { menu->ExecuteZ2(); }
    void ExecuteZ3();
    static void ExecuteZ3Wrapper(Menu* menu) { menu->ExecuteZ3(); }

    void _display_rfid_response_to_symbol(RFIDResponse status);
public:
    Menu(LEDMatrix& matrix_ref, RFID& rfid_ref) : _matrix_ref(matrix_ref), _rfid_ref(rfid_ref) {};
    void handle_input(JoystickState action);
};