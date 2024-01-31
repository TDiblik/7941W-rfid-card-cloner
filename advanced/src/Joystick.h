#pragma once

#include <cstdint>

enum JoystickState {
    Centered,
    Pressed,
    PointingUP,
    PointingDown,
};

class Joystick {
private:
    const uint8_t _power_pin;
    const uint8_t _d_pin;
    const uint8_t _x_pin;

public:
    static const uint16_t DOWN_TRIGGER_THRESHOLD = 10; // 0 to DOWN_TRIGGER_THRESHOLD -> press triggered
    static const uint16_t Y_UP_THRESHOLD = 300; // 0 to Y_UP_THRESHOLD -> Pointing UP
    static const uint16_t Y_DOWN_THRESHOLD = 700; // Y_DOWN_THRESHOLD to 1024 -> Pointing DOWN

    Joystick(uint8_t power_pin, uint8_t d_pin, uint8_t x_pin) : _power_pin(power_pin), _d_pin(d_pin), _x_pin(x_pin) {};
    void setup();
    JoystickState get_status();
};