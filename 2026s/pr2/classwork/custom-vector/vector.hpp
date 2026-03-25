#ifndef CUSTOM_VECTOR
#define CUSTOM_VECTOR
//§ Requisites
  //§ Includes
    #include <iostream>
    #include <cstddef>
    #include <stdexcept>
    #include <string>
    // #include "colors.hpp"
  //.
  //§ Helper Concept / Alias(es)
  template <typename T> concept isPrintable = requires(std::ostream &o, const T &t) { o << t; };
  using st = std::size_t;
//.
  //§ Output Operator
    template <typename T> class Vector; 
    template <typename T>
    std::ostream& operator<< (std::ostream &o, const Vector<T> &v) requires (isPrintable<T>) {
    o << "[";
    for (st i { 0 }, size { v.size() }; i < size; ++i)
      o << v[i] << ((i == (size - 1)) ? "" : ", ");
    return o << "]";
  }
  //.
//.
template <typename T> 
class Vector {
  //§ Private Variables
    st savedElements { 0 }, 
       currentCapacity { 0 };
    T *data { nullptr };
  //.
  //§ Helper Function(s)
    Vector& resize(const st newSize) {
      if (newSize == currentCapacity) {} // do nothing
      else if (newSize == 0) this->clear();
      else {
        this->savedElements = ((newSize < this->size()) ? newSize : this->size());
        T *newData { new T[newSize] }; for (st i { 0 }; i < savedElements; ++i) 
                                        newData[i] = data[i];
        delete[] data, data = newData, currentCapacity = newSize;
      }
      return *this;
    }
    void testValidity(std::ptrdiff_t diff, const size_t strictlySmallerThan) {
      if (diff < 0 || static_cast<st>(diff) > strictlySmallerThan) 
        throw std::out_of_range("Iterator Is Out Of Bounds");
    }
  //.
  public:
    //§ Constructor(s)
      Vector() {}
      Vector(const st toReserve, const st savedCurrently = 0)
            : savedElements{savedCurrently}, 
              currentCapacity{toReserve}, 
              data{((currentCapacity > 0) ? new T[currentCapacity] : nullptr)} {
        // if (isPrintable<T>) std::clog << green << "Created" << r <<  " Vector, And Reserved " << blue << currentCapacity << r << " Places" << std::endl;
      }
      Vector(const Vector<T> &v) : Vector(v.capacity(), v.size()) {
        for (st i { 0 }; i < v.size(); ++i) 
          data[i] = v[i];
        // if (isPrintable<T>) std::clog << green << "Created" << r << " Vector, With The Following Contents: " << *this << std::endl;
      }
      Vector(std::initializer_list<T> v) : Vector(v.size(), v.size()) {
        for (st i { 0 }; i < savedElements; ++i) 
          data[i] = *(v.begin() + i);
        // if (isPrintable<T>) std::clog << green << "Created" << r << " Vector, With The Following Contents: " << *this << std::endl;
      }
    //.
    //§ Iterators
      class ConstIterator;
      class Iterator {
          friend class Vector;
        protected:
          T *element { nullptr }; // static st lastID; st instanceID;
        public:
          Iterator() {
            std::clog << "Created Uninitialized Iterator" << std::endl;
          }
          Iterator(T *ptr) : element{ptr} { // , instanceID{++lastID} {
              // if (isPrintable<T> && element) std::clog << "Element Pointed To By Iterator: " << *element << std::endl;
          }
        //§ Operator(s)
          T& operator*() {
            return ((element) ? *element : throw std::logic_error("Iterator Is Unitialized"));
          }
          T* operator->() {
            return ((element) ? element : throw std::logic_error("Iterator Is Unitialized"));
          }
          Iterator& operator++() {
            return ++element, *this;
          }
          Iterator operator++(int) {
            return ++element, (*this - static_cast<st>(1));
          }
          bool operator==(const Iterator &it) const {
            return (this->element == it.element);
          }
          bool operator!=(const Iterator &it) const {
            return !(*this == it);
          }
          Iterator operator+(const st offset) const {
            return Iterator(this->element + offset);
          }
          Iterator operator-(const st offset) const {
            return Iterator(this->element - offset);
          }
          std::ptrdiff_t operator-(const Iterator &it) const {
            return (this->element - it.element);
          }
          operator bool() {
              return (element ? true : false);
            }
        //.
      };
      class ConstIterator : public Iterator {
        public:
          using Iterator::Iterator;
          ConstIterator(const Iterator &it) : Iterator(it) {}
          const T& operator*() const {
            return ((this->element) ? *this->element : throw std::logic_error("Iterator Is Unitialized"));
          }
          const T* operator->() const {
            return ((this->element) ? this->element : throw std::logic_error("Iterator Is Unitialized"));
          }
      };
    //.
    //§ Methods
      bool empty() const noexcept {
        return (savedElements == 0);
      }
      st size() const noexcept {
        return savedElements;
      }
      st capacity() const noexcept {
        return currentCapacity;
      }
      Vector& clear() noexcept {
        if (data) delete[] data, data = nullptr;
        return (savedElements = 0, *this); // = currentCapacity = 0, *this);
      }
      Vector& reserve(const st newSize) {
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
      ConstIterator begin() const noexcept {
        return ((this->empty()) ? this->end() : this->data);
      }
      ConstIterator end() const noexcept {
        return (this->data + savedElements);
      }
      Iterator begin() noexcept {
        return ((this->empty()) ? this->end() : this->data);
      }
      Iterator end() noexcept {
        return (this->data + savedElements);
      }
      Iterator insert(const ConstIterator position, const T value) {
        auto diff { position - this->begin() }; testValidity(diff, savedElements);
        // TODO Finish this
      }
      Iterator erase(const ConstIterator position) {
        if (this->empty()) throw std::logic_error("Vector Is Empty, Cannot Erase");
        auto diff { position - this->begin() }; testValidity(diff, (savedElements + 1));
        st index = static_cast<st>(diff);
        for (st i = index; i < (savedElements - 1); ++i) 
          data[i] = data[(i + 1)];
        return --savedElements, Iterator(data + index);
      }
    //.
    //§ Operators
      Vector& operator=(const Vector &other) { 
        if (this == &other) goto end;
        this->clear().reserve(other.capacity()); savedElements = other.savedElements;
        for (st i = 0; i < savedElements; ++i) data[i] = other.data[i];
        end: return *this;
      }
      T& operator[](const st index) {
        if (index >= savedElements) throw std::out_of_range("Attempted To Access Index " 
                                                              + std::to_string(index) 
                                                              + ", But Vector Size Is - "
                                                              + std::to_string(savedElements));
        else return data[index];
      }
      const T& operator[](const st index) const {
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
    //§ Aliases
      using iterator       = Iterator;
      using const_iterator = ConstIterator;
    //.
}; // template <typename T> Vector<T>::Iterator::lastID = 0;
#endif