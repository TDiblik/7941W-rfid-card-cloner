#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "debug.h"
#include "Joystick.h"
#include "LEDMatrix.h"
#include "Menu.h"

static Joystick joystick = Joystick(D0, A1, A2);
static LEDMatrix led_matrix = LEDMatrix();
static Menu menu = Menu(led_matrix);

void setup() {
#if DEBUG
  Serial.begin(9600);
#endif
  debug_println("--- Setting up HW components ---");
  delay(500); // wait for a bit, just to make sure

  joystick.Setup();
  debug_println("Joystick - done");

  led_matrix.Setup();
  debug_println("LED Matrix - done");

  debug_println("--- Finished setup successfully ---");
}

void loop() {
  menu.HandleInput(joystick.GetStatus());
}