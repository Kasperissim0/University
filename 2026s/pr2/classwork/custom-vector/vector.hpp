#ifndef CUSTOM_VECTOR
#define CUSTOM_VECTOR
//§ Requisites
  //§ Includes
    #include <concepts>
#include <iostream>
    #include <cstddef>
  #include <optional>
    #include <stdexcept>
    #include <string>
    #include <type_traits>
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
template <typename T = double> 
class Vector {
  friend class ConstIterator;
  //§ Private Variables
    st savedElements    {    0    }, 
       currentCapacity  {    0    };
    T *data             { nullptr };
  //.
  //§ Helper Function(s)
    Vector& resize(const st newSize) { // TODO Update Iterators
      if (newSize == currentCapacity) {} // do nothing
      else if (newSize == 0) this->clear();
      else {
        this->savedElements = ((newSize < savedElements) ? newSize : savedElements);
        T *newData { new T[newSize] }; for (st i { 0 }; i < savedElements; ++i) 
                                        newData[i] = data[i];
        delete[] data, data = newData, currentCapacity = newSize;
      }
      return *this;
    }
    st testValidity(std::ptrdiff_t diff, const st strictlySmallerThan) const {
      st number = 0;
      if (diff < 0 || ((number = static_cast<st>(diff)) && number >= strictlySmallerThan)) 
        throw std::out_of_range("Iterator Is Out Of Bounds");
      return number;
    }
  //.
  public:
    //§ Aliases
      using value_type      = T;
      using size_type       = std::size_t;
      using difference_type = std::ptrdiff_t;
      using reference       = value_type &;
      using const_reference = const value_type &;
      using pointer         = value_type *;
      using const_pointer   = const value_type *;
      // using iterator        = Vector::Iterator;
      // using const_iterator  = Vector::ConstIterator;
    //.
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
      friend class Vector;
      class Iterator {
        template <typename U> friend class Vector;
        protected:
        //§ Private Variables
            T         *element        { nullptr }; // ,
            //          *dataSnapshot   { nullptr };
            Vector<T> *container      { nullptr };
            bool      insideRange     {  false  },
                      dereferencable  {  false  };
            // static st lastID; const st instanceID;
          //.
        //§ Helper Function(s)
          bool isInitialized()                                                 const {
            return (element and container);
          }
          bool isInRange(const std::optional<T*> toTest = std::nullopt)        const {
            return  ((isInitialized()) ? (((((toTest) ? *toTest : element) <= (container->data + container->savedElements)) and (((toTest) ? *toTest : element) >= container->data)) ? true : false) : false);
          }
          bool isDereferencable(const std::optional<T*> toTest = std::nullopt) const {
            return (isInitialized() and isInRange(((toTest) ? *toTest : element)) and (((toTest) ? *toTest : element) != (container->data + container->savedElements)));
          }
          void validateIterator() {
            insideRange = isInRange();
            dereferencable = isDereferencable();
          }
          //.
        public:
        //§ Aliases
            using value_type = typename Vector::value_type;
            using reference = typename Vector::reference;
            using pointer = typename Vector::pointer;
            using difference_type = typename Vector::difference_type;
            using iterator_category = std::forward_iterator_tag;
        //.
        //§ Constructor(s)
            Iterator() {
              std::cerr << "Created Uninitialized Iterator" << std::endl;
            }
            Iterator (T *ptr, Vector<T> *objPtr = nullptr) 
              : element{ptr}, container{objPtr}, // dataSnapshot{((objPtr) ? objPtr->data : nullptr)}, 
                insideRange{isInRange()}, dereferencable{isDereferencable()} { // , instanceID{++lastID} {
                // TODO do something ?
                if (isPrintable<T> && dereferencable) 
                  std::clog << "Element Pointed To By Iterator: " << *element << std::endl;
                else std::clog << "Element Pointed To By Iterator: nullptr" << std::endl;
            }
            template <typename U> Iterator(const U *ptr, const Vector<U> *objPtr = nullptr) requires(std::convertible_to<T, U>)
              : Iterator(reinterpret_cast<T*>(const_cast<std::remove_const_t<U>*>(ptr)), 
                         reinterpret_cast<Vector<T>*>(const_cast<std::remove_const_t<Vector<U>>*>(objPtr))) {
                // TODO do something ?
            }
            Iterator(const Iterator &it) : Iterator(it.element, it.container) {
                // TODO do something ?
            }
        //.
        //§ Operator(s)
          T& operator*() const {
            return ((isDereferencable()) ? *element : throw std::logic_error("Iterator Is Unitialized"));
          }
          T* operator->() const {
            return ((isDereferencable()) ? element : throw std::logic_error("Iterator Is Unitialized"));
          }
          Iterator& operator++() {
            if (isInRange((element + 1))) ++element;
            return *this;
          }
          Iterator operator++(int) {
            return (((isInRange((element + 1))) ? Iterator((++element - static_cast<st>(1)), container) : *this));
          }
          Iterator& operator--() {
            if (isInRange((element - 1))) --element;
            return *this;
          }
          Iterator operator--(int) {
            return (((isInRange((element - 1))) ? Iterator((--element + static_cast<st>(1)), container) : *this));
          }
          bool operator==(const Iterator &it) const {
            return (this->element == it.element && this->container == it.container);
          }
          bool operator!=(const Iterator &it) const {
            return !(*this == it);
          }
          bool operator>(const Iterator &it) const {
            return (element > it.element);
          }
          bool operator>=(const Iterator &it) const {
            return (element >= it.element);
          }
          bool operator<(const Iterator &it) const {
            return (element < it.element);
          }
          bool operator<=(const Iterator &it) const {
            return (element <= it.element);
          }
          Iterator operator+(const st offset) const {
            return Iterator((this->element + offset), container);
          }
          Iterator operator-(const st offset) const {
            return Iterator((this->element - offset), container);
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
        friend class Iterator;
        public:
          //§ Aliases
            using value_type = typename Vector::value_type;
            using reference = typename Vector::const_reference;
            using pointer = typename Vector::const_pointer;
            using difference_type = typename Vector::difference_type;
            using iterator_category = std::forward_iterator_tag;
          //.
          //§ Constructor(s)
            using Iterator::Iterator;
            template <typename U> ConstIterator(const U *ptr, const Vector<U> *objPtr = nullptr) : Iterator(ptr, objPtr) {}
            template <typename EdgCase> ConstIterator(EdgCase it) requires(std::convertible_to<typename EdgCase::value_type, T>)
                 : ConstIterator(it.element, it.container) {} 
              // : ConstIterator(reinterpret_cast<T*>(const_cast<void*>(reinterpret_cast<const void*>(it.operator->()))), nullptr {}
            //.
          const T& operator*() const {
            return ((this->isDereferencable()) ? *(this->element) : throw std::logic_error("Iterator Is Unitialized"));
          }
          const T* operator->() const {
            return ((this->isDereferencable()) ? this->element : throw std::logic_error("Iterator Is Unitialized"));
          }
      };
    //.
    //§ Methods
      bool empty()  const noexcept {
        return (savedElements == 0);
      }
      st size()     const noexcept {
        return savedElements;
      }
      st capacity() const noexcept {
        return currentCapacity;
      }
      Vector& clear()     noexcept {
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
        return ((this->empty()) ? ConstIterator(this->end()) : ConstIterator((this->data), this));
      }
      ConstIterator end()   const noexcept {
        return ConstIterator((this->data + savedElements), this);
      }
      Iterator begin()            noexcept {
        return ((this->empty()) ? Iterator(this->end()) : Iterator((this->data), this));
      }
      Iterator end()              noexcept {
        return Iterator((this->data + savedElements), this);
      }
      Iterator insert(const Iterator position, const T &value) { // TODO Update Iterators
        auto diff { position - this->begin() }; const st index = testValidity(diff, (savedElements + 1));
        
        if (savedElements >= currentCapacity) this->resize((savedElements + 1) * 2);
        for (st i = savedElements; i > index; --i)
          data[i] = data[i - 1]; data[index] = value;
        return ++savedElements, Iterator((data + index), this);
      }
      Iterator erase(const Iterator position) { // TODO Update Iterators
        if (this->empty()) throw std::logic_error("Vector Is Empty, Cannot Erase");
        auto diff { position - this->begin() }; const st index = testValidity(diff, savedElements);

        for (st i = index; i < (savedElements - 1); ++i) 
          data[i] = data[i + 1];
        return --savedElements, Iterator((data + index), this);
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
      friend class ConstIterator;
    //.
}; // template <typename T> Vector<T>::Iterator::lastID = 0;
#endif