#ifndef HIGHLAND_VECTOR_HPP
#define HIGHLAND_VECTOR_HPP

#include <cstdint>
#include <stdlib.h>

namespace highland
{
// @brief "true" vector implementation for arduino. Hard limited compile time size for size safety.
// @tparam T          Type of data stored in vector
// @tparam START_SIZE initial size of vector
// @tparam MAX_SIZE   max size of vector. generally small as this is intended for embedded use.
template <typename T, size_t START_SIZE=1, size_t MAX_SIZE=32>
class vector
{
 public:
  vector()
  {
    // TODO: check for success. honestly don't know what to do if we fail but :shrug:
    m_data = (T*) calloc(START_SIZE, sizeof(T));
    m_size = 0;
    m_max_size = START_SIZE;
  }

  int push_back(T e)
  {
    if(m_size == m_max_size)
    {
      if(m_size*2 > MAX_SIZE)
      {
        return -1;
      }
      T* new_data = (T*) calloc(m_max_size*2, sizeof(T));
      memcpy(new_data, m_data, m_size*sizeof(T));
      m_data = new_data;
      m_max_size = m_max_size*2;
    }

    m_data[m_size] = e;
    m_size++;
  }

  uint8_t size()
  {
    return m_size;
  }

  T& operator[](size_t idx)
  {
    return m_data[idx];
  }

  const T& operator[](size_t idx) const
  {
    return m_data[idx];
  }
  
 private:
  T* m_data;
  uint8_t m_size;
  uint8_t m_max_size;
};
} // namespace highland
#endif // HIGHLAND_LIGHT_CONTROLLER_HPP
