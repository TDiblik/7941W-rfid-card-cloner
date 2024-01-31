#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "debug.h"
#include "Joystick.h"
#include "LEDMatrix.h"
#include "Menu.h"
#include "RFID.h"

static Joystick joystick = Joystick(D0, A1, A2);
static LEDMatrix led_matrix = LEDMatrix();
static RFID rfid = RFID(Serial1); // Connect RFID-RX->Board-D6 ; RFID-TX->Board-D7, refers to https://files.seeedstudio.com/wiki/XIAO-BLE/pinout2.png
static Menu menu = Menu(led_matrix, rfid);

void setup() {
#if DEBUG
  Serial.begin(9600);
#endif
  debug_println("--- Setting up HW components ---");
  delay(500); // wait for a bit, just to make sure

  joystick.setup();
  debug_println("Joystick - done");

  led_matrix.setup();
  debug_println("LED Matrix - done");

  rfid.setup();
  debug_println("Communication with the cloner - done");

  debug_println("--- Finished setup successfully ---");
}

void loop() {
  menu.handle_input(joystick.get_status());
}