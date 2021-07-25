#include "LightController.hpp"

#include "Vector.hpp"

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
  if(num_leds == 0) num_leds = 1; // @todo(apozharski) please please please figure out why FASTLED crashes with 0 leds
  if(m_leds[strip_index] != nullptr)
  {
    // @todo this might actually be really dangerous. Maybe stop interrupt handling?
    m_num_leds[strip_index] = 0;
    free(m_leds[strip_index]);
  }
  m_leds[strip_index] = (CRGB* ) calloc(num_leds, sizeof(CRGB));
  m_num_leds[strip_index] = num_leds;
  (m_controllers[strip_index])->setLeds(m_leds[strip_index], num_leds);
  return 0;
}

int LightController::addRange(LEDRange range)
{
  return m_ranges.push_back(range);
}

int LightController::clearRange(size_t range_idx)
{
  if(range_idx >= m_ranges.size())
  {
    return -1;
  }

  const LEDRange& range = m_ranges[range_idx];

  for(uint8_t i = range.start_index; i <= range.end_index; i++)
  {
    m_leds[range.strip_index][i] = CRGB::Black;
  }

  return 0;
}

int LightController::setColorRange(size_t range_idx, CRGB color)
{
  if(range_idx >= m_ranges.size())
  {
    return -1;
  }

  const LEDRange& range = m_ranges[range_idx];

  for(uint8_t i = range.start_index; i <= range.end_index; i++)
  {
    m_leds[range.strip_index][i] = color;
  }

  return 0;
}

int LightController::setColorRange(size_t range_idx, CHSV color)
{
  if(range_idx >= m_ranges.size())
  {
    return -1;
  }

  const LEDRange& range = m_ranges[range_idx];
  CRGB rgb_color;
  hsv2rgb_rainbow(color, rgb_color);
  
  for(uint8_t i = range.start_index; i <= range.end_index; i++)
  {
    m_leds[range.strip_index][i] = rgb_color;
  }

  return 0;
}

void LightController::setAllInStripRGB(uint8_t strip_index, CRGB color)
{
  for(uint8_t i = 0; i < m_num_leds[strip_index]; i++)
  {
    m_leds[strip_index][i] = color;
  }
}

void LightController::setAllInStripHSV(uint8_t strip_index, CHSV color)
{
  CRGB rgb_color;
  hsv2rgb_rainbow(color, rgb_color);
  for(uint8_t i = 0; i < m_num_leds[strip_index]; i++)
  {
    m_leds[strip_index][i] = rgb_color;
  }
}

void LightController::printStrip(uint8_t strip_index)
{
  Serial.print(strip_index);Serial.println("------------------------------------------------------");
  Serial.println((uint32_t) (m_controllers[strip_index]->leds()), HEX);
  Serial.println((uint32_t) (m_leds[strip_index]), HEX);
  for(uint8_t i = 0; i < m_num_leds[strip_index]; i++)
  {
    Serial.print(i);Serial.print("|");
    Serial.print(m_leds[strip_index][i].r);Serial.print(" ");
    Serial.print(m_leds[strip_index][i].g);Serial.print(" ");
    Serial.print(m_leds[strip_index][i].b);Serial.print("|");
  }
  Serial.println("Done Printing Strip");
}
} // namespace highland
