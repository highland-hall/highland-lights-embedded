#include "LightController.hpp"

#include "Vector.hpp"

#include <FastLED.h>

#include <cstdint>
#include <stdlib.h>

namespace highland
{

LightController::LightController()
{
  
}

void LightController::init()
{
  // @todo consolidated config.
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  m_controllers[0] = &(FastLED.addLeds<WS2813, 5, RGB>(m_leds[0], m_num_leds[0]));
  m_controllers[1] = &(FastLED.addLeds<WS2813, 6, RGB>(m_leds[1], m_num_leds[1]));
  m_controllers[2] = &(FastLED.addLeds<WS2813, 7, RGB>(m_leds[2], m_num_leds[2]));
  m_controllers[3] = &(FastLED.addLeds<WS2813, 8, RGB>(m_leds[3], m_num_leds[3]));
}

int LightController::addStrip(uint8_t strip_index, uint8_t num_leds)
{
  // @todo make sure num_leds > 0 or make special behavior such that num_leds == 0 only frees
  if(m_leds[strip_index] != nullptr)
  {
    // @todo this might actually be really dangerous. Maybe stop interrupt handling?
    m_num_leds[strip_index] = 0;
    free(m_leds[strip_index]);
  }
  m_num_leds[strip_index] = num_leds;
  m_leds[strip_index] = (CRGB*) calloc(num_leds, sizeof(CRGB));
  m_leds[0][0] = CRGB::White;
  m_controllers[strip_index]->setLeds(m_leds[strip_index], num_leds);
  return 0;
}

int LightController::addRange(LEDRange range)
{
  return m_ranges.push_back(range);
}

} // namespace highland
