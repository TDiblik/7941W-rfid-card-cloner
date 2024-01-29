#pragma once

#include <cstdint>
#include <api/Common.h>

enum JoystickState {
    Centered,
    Pressed,
    PointingUP,
    PointingDown,
};

class Joystick {
private:
    static const uint16_t DOWN_TRIGGER_THRESHOLD = 10; // 0 to DOWN_TRIGGER_THRESHOLD -> press triggered
    static const uint16_t Y_UP_THRESHOLD = 300; // 0 to Y_UP_THRESHOLD -> Pointing UP
    static const uint16_t Y_DOWN_THRESHOLD = 700; // Y_DOWN_THRESHOLD to 1024 -> Pointing DOWN

    const uint8_t POWER_PIN;
    const uint8_t D_PIN;
    const uint8_t X_PIN;

public:
    Joystick(uint8_t power_pin, uint8_t d_pin, uint8_t x_pin) : POWER_PIN(power_pin), D_PIN(d_pin), X_PIN(x_pin) {};
    void Setup();
    JoystickState GetStatus();
};