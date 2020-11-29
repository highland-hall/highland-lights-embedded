#pragma once
#include <stdint.h>

namespace highland
{


class EEPROMI2C
{
 public:
  EEPROMI2C();

  void read(uint32_t addr, uint8_t* ptr, size_t size);
  void write(uint32_t addr, uint8_t* ptr, size_t size);
  void pageWrite(uint32_t addr, uint8_t* ptr, size_t size);
  void update(uint32_t addr, uint8_t* ptr, size_t size);
 private:

  void generateHeader(uint32_t addr, uint8_t rw);

  static uint8_t READ = 0;
  static uint8_t WRITE = 1;

  uint8_t m_header[3];
  uint32_t m_curr_addr;
}
}
