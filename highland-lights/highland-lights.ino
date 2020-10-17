#include "Arduino.h"
#include <FastLED.h>
#include "LightController.hpp"
#include <cstdint>
highland::LightController controller;

void setup() {
  delay(200);
  //pinMode(DATA_PIN, OUTPUT);
  controller.init();
  controller.addStrip(0,10);
  Serial.begin(9600);
}

int i = 0;
void loop() {
  // digitalWrite(DATA_PIN, HIGH);
  // delay(100);
  // digitalWrite(DATA_PIN, LOW);
  // delay(100);
  
  // for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
  //     // Turn our current led on to white, then show the leds
  //     leds[whiteLed] = CRGB::White;

  //     // Show the leds (only one of which is set to white, from above)
  //     FastLED.show();

  //     // Wait a little bit
  //     delay(100);

  //     // Turn our current led back to black for the next loop around
  //     leds[whiteLed] = CRGB::Black;
  //  }
  delay(100);
  //FastLED.show();
  Serial.println(i);
  i++;
  Serial.println((uint32_t) controller.getStrip(0), HEX);
}
