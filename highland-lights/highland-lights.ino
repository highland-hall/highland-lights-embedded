#include "Arduino.h"
#include "LightController.hpp"
#include <cstdint>
highland::LightController controller;
// CLEDController* c;
// CLEDController* c2;
// CRGB* l = nullptr;
// CRGB* l2 = nullptr;


void setup() {
  delay(2000);
  Serial.begin(9600);
  //pinMode(DATA_PIN, OUTPUT);
  controller.init();
  // Serial.println("Inited controller");
  controller.addStrip(0,10);
  //controller.addStrip(1,1);
  //controller.addStrip(2,1);
  //controller.addStrip(3,1);
  // Serial.println("Added strip");
  controller.setAllInStrip(0, CRGB::White);
  //controller.setAllInStrip(1, CRGB::White);
  // Serial.println("set all to white");
  // c = &(FastLED.addLeds<WS2813, 5, RGB>(l, 0));
  // uint8_t n = 10;
  // l = (CRGB*) calloc(n, sizeof(CRGB));
  // c->setLeds(l, n);
  // c2 = &(FastLED.addLeds<WS2813, 5, RGB>(l2, 0));
  // l2 = (CRGB*) calloc(n, sizeof(CRGB));
  // c2->setLeds(l2, n);
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
  Serial.println("Alive");
  //FastLED.show();
  controller.printStrip(0);
  controller.printStrip(1);
  controller.printStrip(2);
  controller.printStrip(3);
  FastLED.show();
  // Serial.println(i);
  // i++;
  // Serial.println((uint32_t) controller.getStrip(0), HEX);
}
