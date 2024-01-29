#include "LEDMatrix.h"
#include <Adafruit_LEDBackpack.h>
#include "debug.h"

void LEDMatrix::Setup() {
    this->_matrix.begin(0x70);
    this->_matrix.setBrightness(15);
    this->_matrix.blinkRate(HT16K33_BLINK_DISPLAYON);
    this->_matrix.setDisplayState(true);
    this->_matrix.setCursor(0, 0);
    this->_matrix.clear();
    this->_matrix.writeDisplay();
#if !DEBUG
    delay(250); // wait a bit, just to make sure
    this->Draw(HI_BITMAP);
    delay(1500);
    this->Draw(SMILE_BITMAP);
    delay(1500);
#endif
#if DEBUG
    delay(250); // wait a bit, just to make sure
#endif
    this->Draw(S1_BITMAP);
}

// TODO: Blinking X/checkmark
// void LEDMatrix::BlinkBitmap(const uint8_t* bitmap) {
// }

void LEDMatrix::Draw(const uint8_t* bitmap) {
    this->_matrix.clear();
    this->_matrix.drawBitmap(0, 0, bitmap, 8, 8, LED_ON);
    this->_matrix.writeDisplay();
}