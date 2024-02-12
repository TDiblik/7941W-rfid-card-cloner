# Showcase

<!-- todo: add a video where I showcase the advanced version -->

[![Showcase gif](./resources/showcase.gif)](./resources/showcase.mp4)

# Advanced version

## Dictionary before starting

- Whenever the docs call something "a/the display", it means the 8x8 LED matrix
- Whenever the docs say "input", it means the Joystick, or selecting something with the Joystick

## How does it work?

## How to setup?

## Bitmap generator

You might notice, in the root of the project, there is a python script called `bitmap_generator.py`. You can use this to generate bitmaps to draw onto the display. All you have to do is start the program `python bitmap_generator.py`. A following window will pop up: <br/>
![Example usage of the bitmap generator to draw S1](./resources/how_to_draw_S_8x8.png) <br/>
Here, you can draw something that you want to get displayed on the screen. After you're done, hit the "Generate" button. This will output "C code" that you can put into the project. The output will look like this:

```cpp
static const uint8_t PROGMEM NAME_BITMAP[]
{ 0b01100001,
  0b10010011,
  0b10000101,
  0b01000001,
  0b00100001,
  0b00010001,
  0b10010001,
  0b01100001 };
```

If you pass this as an argument into the `LEDMatrix.draw` or `LEDMatrix.blink` functions, it will get drawn. You can quickly test it out by changing the `main.cpp` to the following:

```cpp
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "debug.h"
#include "LEDMatrix.h"

static LEDMatrix led_matrix = LEDMatrix();

// REPLACE THIS WITH YOUR GENERATED BITMAP
static const uint8_t PROGMEM YOUR_GENERATED_BITMAP[]
{ 0b00000000,
  0b01001010,
  0b01001000,
  0b01111010,
  0b01001010,
  0b01001010,
  0b01001010,
  0b00000000 };

void setup() {
  Serial.begin(9600);
  led_matrix.setup();
  debug_println("LED Matrix - done");
}

void loop() {
  led_matrix.draw(YOUR_GENERATED_BITMAP);
  delay(500); // we don't want to spam it... Tbh, the `.draw` could be in the setup function and the loop could be empty
}
```

## Development notes

# Simple version

## How does it work?

## How to setup?

## Development notes
