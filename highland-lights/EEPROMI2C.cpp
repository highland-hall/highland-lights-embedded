#include "EEPROMI2C.hpp"
#include <Wire.h>
namespace highland
{
EEPROMI2C::EEPROMI2C()
{
  
}
void read(uint32_t addr, uint8_t* ptr, size_t size)
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
void write(uint32_t addr, uint8_t* ptr, size_t size)
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
void pageWrite(uint32_t addr, uint8_t* ptr, size_t size)
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
void update(uint32_t addr, uint8_t* ptr, size_t size)
{
  generateHeader(addr, READ);
}
}
