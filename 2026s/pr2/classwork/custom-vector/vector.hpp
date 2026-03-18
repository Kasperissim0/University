#ifndef CUSTOM_VECTOR
#define CUSTOM_VECTOR
//§ Includes
  #include <iostream>
  #include <cstddef>
  #include <stdexcept>
  #include <string>
  #include "colors.hpp"
//.
//§ Helper Concept
  template <typename T>
  concept isPrintable = requires(std::ostream &o, const T &t) { o << t; };
//.

template <typename T>
class Vector {
  //§ Private Variables
    size_t savedElements { 0 }, 
           currentCapacity { 0 };
    T *data { nullptr };
  //.
  //§ Helper Function(s)
    Vector& resize(const size_t newSize) {
      if (newSize == currentCapacity) {} // do nothing
      else if (newSize == 0) this->clear();
      else {
        this->savedElements = ((newSize < this->size()) ? newSize : this->size());
        T *newData { new T[newSize] }; for (size_t i { 0 }; i < this->size(); ++i) 
                                        newData[i] = data[i];
        delete[] data, data = newData, currentCapacity = newSize;
      }
      return *this;
    }
  //.
  public:
    //§ Constructors
      Vector() {}
      Vector(const size_t toReserve, const size_t savedCurrently = 0)
            : savedElements{savedCurrently}, 
              currentCapacity{toReserve}, 
              data{((currentCapacity > 0) ? new T[currentCapacity] : nullptr)} {
        // if (isPrintable<T>) std::clog << green << "Created" << r <<  " Vector, And Reserved " << blue << currentCapacity << r << " Places" << std::endl;
      }
      Vector(const Vector<T> &v) : Vector(v.capacity(), v.size()) {
        for (size_t i { 0 }; i < v.size(); ++i) 
          data[i] = v[i];
        // if (isPrintable<T>) std::clog << green << "Created" << r << " Vector, With The Following Contents: " << *this << std::endl;
      }
      Vector(std::initializer_list<T> v) : Vector(v.size(), v.size()) {
        for (size_t i { 0 }; i < savedElements; ++i) 
          data[i] = *(v.begin() + i);
        // if (isPrintable<T>) std::clog << green << "Created" << r << " Vector, With The Following Contents: " << *this << std::endl;
      }
    //.
    //§ Iterators
      class iterator {

      };
      class const_iterator {

      };
    //.
    //§ Methods
      bool empty() const noexcept {
        return (savedElements == 0);
      }
      size_t size() const noexcept {
        return savedElements;
      }
      size_t capacity() const noexcept {
        return currentCapacity;
      }
      Vector& clear() noexcept {
        if (data) delete[] data, data = nullptr;
        return (savedElements = 0, *this); // = currentCapacity = 0, *this);
      }
      Vector& reserve(const size_t newSize) {
        return ((newSize <= currentCapacity) ? *this : this->resize(newSize));
      }
      Vector& shrink_to_fit() {
        return (this->resize(savedElements), *this);
      }
      Vector& push_back(const T &obj) {
        if ((savedElements + 1) >= currentCapacity) this->resize((savedElements + 1) * 2);
        return (data[savedElements++] = obj, *this);
      } 
      Vector& pop_back() {
      return (((savedElements == 0) ? throw std::out_of_range("Cannot Pop Back, Vector Is Empty") : --savedElements), *this);
    }
    //.
    //§ Operators
      Vector& operator=(const Vector &other) { 
        if (this == &other) goto end;
        this->clear().reserve(other.capacity()); savedElements = other.savedElements;
        for (size_t i = 0; i < savedElements; ++i) data[i] = other.data[i];
        end: return *this;
      }
      T& operator[](const size_t index) {
        if (index >= savedElements) throw std::out_of_range("Attempted To Access Index " 
                                                              + std::to_string(index) 
                                                              + ", But Vector Size Is - "
                                                              + std::to_string(savedElements));
        else return data[index];
      }
      const T& operator[](const size_t index) const {
      if (index >= savedElements) throw std::out_of_range("Attempted To Access Index " 
                                                            + std::to_string(index) 
                                                            + ", But Vector Size Is - "
                                                            + std::to_string(savedElements));
      else return data[index];
    }
    //.
    ~Vector() {
      // if (isPrintable<T>) std::clog << red << "Destroying" << r << " Vector, Current Contents: " << *this << std::endl;
      this->clear();
    }
};

//§ Output
  template <typename T>
  std::ostream& operator<< (std::ostream &o, const Vector<T> &v) requires (isPrintable<T>) {
  o << "[";
  for (size_t i { 0 }, size { v.size() }; i < size; ++i)
    o << v[i] << ((i == (size - 1)) ? "" : ", ");
  return o << "]";
}
//.

#endif