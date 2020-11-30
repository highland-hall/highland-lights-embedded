#include "Arduino.h"
#include "EEPROM.hpp"
#include "EEPROMI2C.hpp"
#include "LightController.hpp"
#include "SecretUtils.hpp"
#include <cstdint>
#include <WiFiNINA.h>
#include <Wire.h>


highland::EEPROMI2C eeprom_driver;

highland::EEPROM<highland::EEPROMI2C, 128000> eeprom{&eeprom_driver};


void setup() {

}

void loop() {
}
