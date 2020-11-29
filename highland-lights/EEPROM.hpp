#pragma once
#include <stdint.h>

namespace highland
{
///@brief Basic EEPROM
template<typename Driver, uint32_t Size>
class EEPROM
{
 public:
  EEPROM(Driver* driver):
    m_driver{driver}
  {
  }

  template<typename T>
  void read(uint32_t address, T* op)
  {
    uint8_t* ptr = (uint8_t*) op;
    size_t size_of_t = sizeof(T);
    m_driver->read(address, ptr, size_of_t);
  }

  template<>
  void read<String>(uint32_t address, String str, size_t str_len)
  {
    uint8_t* ptr = (uint8_t*) op;
    size_t size_of_t = sizeof(T);
    m_driver->read(address, ptr, size_of_t);
  }

  template<typename T>
  void write(uint32_t address, T op)
  {
    size_t size_of_t = sizeof(T);
    uint32_t last_addr = address + size_of_t;
    if(address & 0x0000ffff == last_addr & 0x0000ffff)
    {
      m_driver->pageWrite(address, &op, size_of_t);
    }
    m_driver->write(address, &op, size_of_t);
  }

  template<typename T>
  void update(uint32_t address, T op)
  {
    size_t size_of_t = sizeof(T);
    m_driver->update(address, &op, size_of_t);
  }  
 private:
  Driver* m_driver;
};
} // namespace highland
