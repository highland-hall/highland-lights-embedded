#ifndef HIGHLAND_LIGHT_CONTROLLER_HPP
#define HIGHLAND_LIGHT_CONTROLLER_HPP

#include <FastLED.h>
#include <cstdint>
#include "Vector.hpp"

namespace highland
{
struct __attribute__((packed)) LEDRange
{
  uint8_t  strip_index;
  uint16_t start_index;
  uint16_t end_index;
};

class LightController
{
 public:
  LightController();
  void  init();
  int   addStrip(uint8_t strip_index, uint8_t num_leds);
  int   addRange(LEDRange range);
  CRGB* getStrip(uint8_t idx) {return m_leds[idx];};  
  void setAllInStrip(uint8_t strip_index, CRGB color);

  // Set ranges to different effects/colors

  int clearRange(size_t range_idx);
  int setColorRange(size_t range_idx, CRGB color);
  int setColorRange(size_t range_idx, CHSV color);
  // @todo(apozharski) other solid set colors
  
  void printStrip(uint8_t strip_index);
  void show() { FastLED.show(); };

  static const uint8_t VERSION = 1;
 private:
  CLEDController* m_controllers[4];
  vector<LEDRange, 1> m_ranges;
  CRGB* m_leds[4] = {nullptr, nullptr, nullptr, nullptr};
  uint8_t m_num_leds[4] = {0,0,0,0};
};

} // namespace highland
#endif // HIGHLAND_LIGHT_CONTROLLER_HPP
