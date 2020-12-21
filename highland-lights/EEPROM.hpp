#pragma once
#include <stdint.h>
#include <stdlib.h>

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

  void read(uint32_t address, char* str, size_t length)
  {
    uint8_t* ptr = (uint8_t*) str;
    m_driver->read(address, ptr, length);
  }

  // @todo(apozharski) probably write a null terminated string read and write (possibly needs support in the Driver).

  template<typename T>
  void write(uint32_t address, T op)
  {
    size_t size_of_t = sizeof(T);
    uint32_t last_addr = address + size_of_t - 1;
    // @todo(apozharski) please make this smarter. can do multiple page writes instead of multiple single writes.
    // @todo(apozharski) once microchip gets it shit together and tells me why page writes don't work for the first byte I can try to fix this. 
    if((address & 0x0001ff00U) == (last_addr & 0x0001ff00U))
    {
      m_driver->pageWrite(address, (uint8_t*) (&op), size_of_t);
    }
    else
    {
      m_driver->write(address, (uint8_t*) (&op), size_of_t);
    }
  }

  void write(uint32_t address, char* str, size_t length)
  {
    uint32_t last_addr = address + length - 1;
    // @todo(apozharski) please make this smarter. can do multiple page writes instead of multiple single writes.
    if((address & 0x0001ff00U) == (last_addr & 0x0001ff00U))
    {
      m_driver->pageWrite(address, (uint8_t*) (str), length);
    }
    else
    {
      m_driver->write(address, (uint8_t*) (&str), length);
    }
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
