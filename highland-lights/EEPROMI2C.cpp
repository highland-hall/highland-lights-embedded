#include "EEPROMI2C.hpp"
#include <Wire.h>
namespace highland
{
EEPROMI2C::EEPROMI2C()
{}

void EEPROMI2C::read(uint32_t addr, uint8_t* ptr, size_t size)
{
  generateHeader(addr, WRITE);

  Wire.beginTransmission();
  Wire.write(m_header, 3);
  Wire.endTransmission();
  generateHeader(addr, READ);
  Wire.requestFrom(m_header[0], size);
  if(Wire.available())
  {
    for(size_t i = 0; i < size; i++)
    {
      ptr[i] = Wire.read();
    }
  }
}

// This is really dumb. please make this auto page write :(
void EEPROMI2C::write(uint32_t addr, uint8_t* ptr, size_t size)
{
  generateHeader(addr, WRITE);

  for(size_t i=0; i < size; i++)
  {
    Wire.beginTransmission();
    Wire.write(m_header, 3);
    Wire.write(ptr[i]);
    Wire.endTransmission();
  }
  
}
void EEPROMI2C::pageWrite(uint32_t addr, uint8_t* ptr, size_t size)
{
  generateHeader(addr, WRITE);

  Wire.beginTransmission();
  Wire.write(m_header, 3); 
  for(size_t i=0; i < size; i++)
  {
    Wire.write(ptr[i]);
  }
  Wire.endTransmission();
}

/// update is dumb but probably necessary for feature completeness.
void EEPROMI2C::update(uint32_t addr, uint8_t* ptr, size_t size)
{
  generateHeader(addr, READ);
}

void EEPROMI2C::generateHeader(uint32_t addr, uint8_t rw)
{
  m_header[2] = ((uint8_t*) &addr)[0];
  m_header[1] = ((uint8_t*) &addr)[1];
  //TODO make first element.
}

}
