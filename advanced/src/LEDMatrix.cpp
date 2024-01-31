#include "LEDMatrix.h"
#include <Adafruit_LEDBackpack.h>
#include "debug.h"

void LEDMatrix::setup() {
    this->_matrix.begin(0x70);
    this->_matrix.setBrightness(15);
    this->_matrix.blinkRate(HT16K33_BLINK_DISPLAYON);
    this->_matrix.setDisplayState(true);
    this->_matrix.setCursor(0, 0);
    this->_matrix.clear();
    this->_matrix.writeDisplay();
#if !DEBUG
    delay(250); // wait a bit, just to make sure
    this->draw(HI_BITMAP);
    delay(1500);
    this->draw(SMILE_BITMAP);
    delay(1500);
#endif
#if DEBUG
    delay(250); // wait a bit, just to make sure
#endif
    this->draw(S1_BITMAP);
}

void LEDMatrix::blink(const uint8_t* bitmap, uint8_t number_of_blinks, uint16_t ms_per_blink) {
    const uint16_t delay_per_blink = ms_per_blink / 2;
    for (uint8_t i = 0; i < number_of_blinks; i++) {
        this->_matrix.clear();
        this->_matrix.writeDisplay();
        delay(delay_per_blink);
        this->draw(bitmap);
        delay(delay_per_blink);
    }
}

void LEDMatrix::draw(const uint8_t* bitmap) {
    this->_matrix.clear();
    this->_matrix.drawBitmap(0, 0, bitmap, 8, 8, LED_ON);
    this->_matrix.writeDisplay();
}