#include <Arduino.h>
#include <cstdint>
#include <api/Common.h>
#include <api/String.h>

#include "debug.h"
#include "Joystick.h"

void Joystick::setup() {
    pinMode(this->_power_pin, OUTPUT);
    digitalWrite(this->_power_pin, HIGH);
}

JoystickState Joystick::get_status() {
    if (analogRead(this->_d_pin) < this->DOWN_TRIGGER_THRESHOLD) {
        debug_println("Joystick status: pressed");
        return JoystickState::Pressed;
    }

    // We pretend that X is Y because the component is rotated by 90° 
    // Also, because of this, the value is inverted (1024 == DOWN ; 0 == UP)
    int y_value = analogRead(this->_x_pin);
    if (y_value < this->Y_UP_THRESHOLD) {
        debug_println("Joystick status: UP");
        debug_print("   value: ");
        debug_println_number(y_value);
        return JoystickState::PointingUP;
    }
    if (y_value > this->Y_DOWN_THRESHOLD) {
        debug_println("Joystick status: DOWN");
        debug_print("   value: ");
        debug_println_number(y_value);
        return JoystickState::PointingDown;
    }
    return JoystickState::Centered;
};