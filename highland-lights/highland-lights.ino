#include "Arduino.h"
#include "EEPROM.hpp"
#include "EEPROMI2C.hpp"
#include "LightController.hpp"
#include "LightsInterface.hpp"
#include "SecretUtils.hpp"
#include <cstdint>
#include <WiFiNINA.h>
#include <Wire.h>

#define WP 20

highland::EEPROMI2C eeprom_driver{WP};

highland::EEPROM<highland::EEPROMI2C, 128000> eeprom{&eeprom_driver};

highland::LightController controller;
highland::LightsInterface interface(&controller, &eeprom);

void setup() {
  WiFi.disconnect();
  pinMode(WP, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  delay(5000);
  // uint32_t test = 0x00000A0B;
  // eeprom.write<uint32_t>(0, test);
  controller.init();
  //controller.addStrip(0,10);
  //controller.setAllInStrip(0, CRGB::White);
  //controller.show();
  
  interface.initialize();
}

void loop() {
  interface.handleConnection();
}
