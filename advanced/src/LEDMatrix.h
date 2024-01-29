#pragma once

#include <Arduino.h>
#include <Adafruit_LEDBackpack.h>

class LEDMatrix {
private:
    Adafruit_8x8matrix _matrix;

public:
    LEDMatrix() : _matrix(Adafruit_8x8matrix()) {};
    void Setup();
    void Draw(const uint8_t* bitmap);
};

/* -----------------
    WELCOME BITMAPS
   ----------------- */
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