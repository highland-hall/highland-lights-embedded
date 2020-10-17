#pragma once
#include "stdint.h"

namespace highland
{
namespace lights
{
template<typename T>
class EEPROMPtr
{
 public:

  operator const AddrSize() const     { return address; }
  EEPtr &operator=( AddrSize in )     { return address = in, *this; }

  bool operator!=( const EEPtr &ptr ) { return address != ptr.address; }
  bool operator==( const EEPtr &ptr ) { return address == ptr.address; }
  T&   operator*()                    { return address; }

  EEPtr& operator++()                 { return ++address, *this; }
  EEPtr& operator--()                 { return --address, *this; }
  EEPtr operator++ (int)              { return address++; }
  EEPtr operator-- (int)              { return address--; }  

 private:
  static constexpr AddrSize t_size = sizeof(T);

  AddrSize address;
}
} // namespace lights
} // namespace highland
