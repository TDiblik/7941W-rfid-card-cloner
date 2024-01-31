#pragma once

#include <Arduino.h>
#include <Adafruit_LEDBackpack.h>

class LEDMatrix {
private:
    Adafruit_8x8matrix _matrix;

public:
    LEDMatrix() : _matrix(Adafruit_8x8matrix()) {};
    void setup();
    void blink(const uint8_t* bitmap, uint8_t number_of_blinks = 3, uint16_t ms_per_blink = 500);
    void draw(const uint8_t* bitmap);
};

/* ----------------
    HELPER BITMAPS
   ---------------- */
static const uint8_t PROGMEM HI_BITMAP[]
{ 0b00000000,
  0b01001010,
  0b01001000,
  0b01111010,
  0b01001010,
  0b01001010,
  0b01001010,
  0b00000000 };

static const uint8_t PROGMEM SMILE_BITMAP[] =
{ 0b00111100,
  0b01000010,
  0b10100101,
  0b10000001,
  0b10100101,
  0b10011001,
  0b01000010,
  0b00111100 };

static const uint8_t PROGMEM CHECKMARK_BITMAP[]
{ 0b00000001,
  0b00000011,
  0b00000111,
  0b00001110,
  0b01011100,
  0b11111000,
  0b01110000,
  0b00100000 };

static const uint8_t PROGMEM X_BITMAP[]
{ 0b11000011,
  0b11100111,
  0b01100110,
  0b00011000,
  0b00011000,
  0b01100110,
  0b11100111,
  0b11000011 };

static const uint8_t PROGMEM QUESTIONMARK_BITMAP[]
{ 0b00011000,
  0b00111100,
  0b00101100,
  0b00001100,
  0b00011000,
  0b00011000,
  0b00000000,
  0b00011000 };

static const uint8_t PROGMEM EXCLAMATIONMARK_BITMAP[]
{ 0b01111110,
  0b00111100,
  0b00111100,
  0b00011000,
  0b00011000,
  0b00000000,
  0b00011000,
  0b00011000 };

static const uint8_t PROGMEM NO_CARD_PROVIDED_BITMAP[]
{ 0b10000000,
  0b01111100,
  0b00100100,
  0b00110100,
  0b00101100,
  0b00100100,
  0b00111110,
  0b00000001 };

static const uint8_t PROGMEM LOADING_BITMAP[]
{ 0b00011010,
  0b00100110,
  0b01001110,
  0b10000000,
  0b00000001,
  0b01110010,
  0b01100100,
  0b01011000 };

/* ---------------
    MENU BITMAPS
   --------------- */
static const uint8_t PROGMEM S1_BITMAP[]
{ 0b01100001,
  0b10010011,
  0b10000101,
  0b01000001,
  0b00100001,
  0b00010001,
  0b10010001,
  0b01100001 };

static const uint8_t PROGMEM S2_BITMAP[]
{ 0b01100111,
  0b10010101,
  0b10000001,
  0b01000011,
  0b00100110,
  0b00010100,
  0b10010101,
  0b01100111 };

static const uint8_t PROGMEM S3_BITMAP[]
{ 0b01100111,
  0b10010101,
  0b10000001,
  0b01000011,
  0b00100011,
  0b00010001,
  0b10010101,
  0b01100111 };

static const uint8_t PROGMEM Z1_BITMAP[]
{ 0b11110001,
  0b00010011,
  0b00010101,
  0b00100001,
  0b01000001,
  0b10000001,
  0b10000001,
  0b11110001 };

static const uint8_t PROGMEM Z2_BITMAP[]
{ 0b11110111,
  0b00010101,
  0b00010001,
  0b00100011,
  0b01000110,
  0b10000100,
  0b10000101,
  0b11110111 };

static const uint8_t PROGMEM Z3_BITMAP[]
{ 0b11110111,
  0b00010101,
  0b00010001,
  0b00100011,
  0b01000011,
  0b10000001,
  0b10000101,
  0b11110111 };

static const uint8_t* const PROGMEM MENU_BITMAPS[]{
    S1_BITMAP,
    S2_BITMAP,
    S3_BITMAP,
    Z1_BITMAP,
    Z2_BITMAP,
    Z3_BITMAP,
};

static const uint8_t MENU_BITMAPS_LAST_INDEX = sizeof(MENU_BITMAPS) / sizeof(MENU_BITMAPS[0]) - 1;