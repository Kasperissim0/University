#ifndef CUSTOM_VECTOR
#define CUSTOM_VECTOR
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <string>

template <typename T>
class Vector {
    size_t currentSize { 0 }, 
           currentCapacity { 0 }, 
           maxCapacity { 0 };
    T const* data = nullptr;
  public:
    Vector() {

    }
    bool isEmpty() const noexcept {
      return (this->currentSize == 0);
    }
    size_t size() const noexcept {
      return this->currentSize;
    }
    size_t capacity() const noexcept {
      return this->currentCapacity;
    }
    Vector& clear() const noexcept {
      if (data) delete data;

      return data = nullptr, *this;
    }
    Vector& reserve(const size_t amountToReserve) {

      return *this;
    }


    T& operator[](const size_t index) {
      if (index >= this->currentSize) return this->data[index];
      else                            throw std::runtime_error("Attempted To Access Index " + std::to_string(index) 
                                                                                            + ", But Vector Size Is - "
                                                                                            + std::to_string(this->currentSize));
    }
    ~Vector() {
      std::clog << "Destroying Vector: " << *data << std::endl;
      this->clear();
    }
};

template <typename T>
std::ostream& operator<< (std::ostream &o, const Vector<T> &v) {
  for (size_t i = 0, size = v.size(); i < size; ++i)
    o << "#" << i << " " << v[i] << std::endl;
  return o;
}

#endif