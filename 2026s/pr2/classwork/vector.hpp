#ifndef CUSTOM_VECTOR
#define CUSTOM_VECTOR
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <string>

template <typename T>
class Vector {
    size_t size { 0 }, capacity { 0 };
    T data = nullptr;
  public:
    Vector() {}
    Vector(const size_t amountToReserve) : size{amountToReserve} {}
    Vector(const Vector<T>& v) : size{v.getSize()}, capacity{v.getCapacity()}, data{new T[capacity]} {
      if (!v.isEmpty())
        for (size_t i = 0; i < this->size; ++i) 
          this->data[i] = *(new T(v[i]));
    }
    Vector(std::initializer_list<T> v) : size{v.getSize()}, capacity{v.size()}, data{new T[capacity]} {
      if (!v.isEmpty())
        for (size_t i = 0; i < this->size; ++i) 
          this->data[i] = *(new T(*(v.begin() + i)));
    }
    bool isEmpty() const noexcept {
      return (this->size == 0);
    }
    size_t getSize() const noexcept {
      return this->size;
    }
    size_t getCapacity() const noexcept {
      return this->capacity;
    }
    Vector& clear() noexcept {
      if (data) delete[] data;
      this->size = 0, data = nullptr;

      return *this;
    }
    Vector& reserve(const size_t amountToReserve) noexcept {
      this->capacity = amountToReserve;

      return *this;
    }


    T& operator[](const size_t index) {
      if (index >= this->size) return this->data[index];
      else                            throw  std::runtime_error("Attempted To Access Index " + std::to_string(index) 
                                                                                             + ", But Vector Size Is - "
                                                                                             + std::to_string(this->size));
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
