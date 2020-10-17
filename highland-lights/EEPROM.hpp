#pragma once
#include "stdint.h"

namespace highland
{
template<typename Driver, uint32_t Size>
class EEPROM
{
 public:
  template<typename T>
  class EEPROMRef
  {
   public:
    //Access/read members.
    T operator*() const                  { return 0; } // TODO
    operator const T() const       { return **this; }

    //Assignment/write members.
    EEPROMRef& operator=( const EEPROMRef &ref ) { return *this = *ref; }
    EEPROMRef& operator=( T in )       { return 0 ,*this;  } // todo

    EEPROMRef& update( uint8_t in )          { return  in != *this ? *this = in : *this; }    

   private:

    uint32_t index;
  }
  
  template<typename T>
  class EEPROMPtr
  {
   public:
    operator const uint32_t() const                 { return address; }
    EEPROMPtr&   operator=( uint32_t in )           { return address = in, *this; }
    bool         operator!=( const EEPROMPtr &ptr ) { return address != ptr.address; }
    bool         operator==( const EEPROMPtr &ptr ) { return address == ptr.address; }
    EEPROMRef<T> operator*()                        { return address; }
    
    EEPROMPtr& operator++()                 { return address += t_size, *this; }
    EEPROMPtr& operator--()                 { return address -= t_size, *this; }
    EEPROMPtr operator++ (int)              { return address += t_size; }
    EEPROMPtr operator-- (int)              { return address -= t_size; }

   private:
    static constexpr AddrSize t_size = sizeof(T);
    
    uint32_t address;
  }

  static uint8_t init()
  {
    
  }
  
  static void read(uint16_t address, T* t)
  {
    uint8_t* ptr = (uint8_t*) t;
    m_driver->read()
  }

  static void write(uint16_t address, uint8_t )
  {
    
  }

  static void update(uint16_t address)
  {
    
  }
};
} // namespace highland
