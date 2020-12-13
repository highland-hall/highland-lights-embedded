#include "EEPROMI2C.hpp"
#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>
#include <stdlib.h>

namespace highland
{
EEPROMI2C::EEPROMI2C(uint16_t wp) :
  m_wp{wp}
{}

void EEPROMI2C::read(uint32_t addr, uint8_t* ptr, size_t size)
{
  generateHeader(addr, WRITE);

  Wire.beginTransmission(m_header[0]);
  Wire.write(m_header+1, 2);
  Wire.endTransmission(false);
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

  digitalWrite(m_wp, LOW);
  for(size_t i=0; i < size; i++)
  {
    generateHeader(addr+i, WRITE);
    Wire.beginTransmission(m_header[0]);
    Wire.write(m_header+1, 2);
    Wire.write(ptr[i]);
    Wire.endTransmission();
    delay(5);
  }
  digitalWrite(m_wp, HIGH);
}
void EEPROMI2C::pageWrite(uint32_t addr, uint8_t* ptr, size_t size)
{
  generateHeader(addr, WRITE);

  digitalWrite(m_wp, LOW);
  
  Wire.beginTransmission(m_header[0]);
  Wire.write(m_header+1, 2); 
  for(size_t i=0; i < size; i++)
  {
    Wire.write(ptr[i]);
  }
  Wire.endTransmission();

  delay(5);
  digitalWrite(m_wp, HIGH);
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
  m_header[0] = 0x50 | (((((uint8_t*) &addr)[2])) & 0x01);
}

}
