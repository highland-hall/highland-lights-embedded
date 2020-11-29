#include "Arduino.h"
#include "LightController.hpp"
#include "SecretUtils.hpp"
#include <cstdint>
#include <WiFiNINA.h>


highland::LightController controller;

int status = WL_IDLE_STATUS;

char ssid[] = HIGHLAND_STR(SECRET_SSID);        // your network SSID (name)
char pass[] = HIGHLAND_STR(SECRET_PASS);    // your network password (use for WPA, or use as key for WEP)
unsigned int local_port = 2390;

WiFiUDP Udp;

void setup() {
  delay(2000);
  Serial.begin(9600);
  controller.init();
  controller.addStrip(0,10);

  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    delay(5000);
  }

  Udp.begin(local_port);
}

int i = 0;
void loop() {
  delay(100);
  FastLED.show();
}
