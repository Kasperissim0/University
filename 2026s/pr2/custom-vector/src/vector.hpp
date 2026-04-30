#ifndef VECTOR_H
#define VECTOR_H
//§ Requisites
  //§ Includes
    #include <ostream>
    #include <iterator>
    #include <initializer_list>
    #include <cstddef>
    #include <stdexcept>
    #include <string>
    #include <utility>
  //.
  //§ Helpers
    using st   = std::size_t;
    using diff = std::ptrdiff_t;
    constexpr st growthRate(const st &size) { return (size == 0 ? 1 : (size * 2)); }
    // template <typename T> concept isPrintable = requires(std::ostream &o, const T &t) { o << t; };
    // template <typename T> inline T sc(std::convertible_to<T> auto objToConvert) noexcept { return (static_cast<T>(objToConvert)); }
    #define ADD_ALIASES(TYPE) \
              using value_type      = TYPE; \
              using size_type       = st; \
              using difference_type = diff; \
              using reference       = TYPE&; \
              using const_reference = const TYPE&; \
              using pointer         = TYPE*; \
              using const_pointer   = const TYPE*;
  //.
  //§ Output Operator
    template <typename T> class Vector;
    template <typename T> 
    inline std::ostream& operator<<(std::ostream &o, const Vector<T> &v) {
        o << "[";
        for (st i { 0 }, size { v.size() }; i < size; ++i)
            o << v[i] << ((i == (size - 1)) ? "" : ", ");
        return o << "]";
    }
    // template <typename T> inline std::ostream& operator<< (std::ostream &o, const Vector<T> &v) requires (isPrintable<T>) {
    //   o << "[";
    //   for (st i { 0 }, size { v.size() }; i < size; ++i)
    //     o << v[i] << ((i == (size - 1)) ? "" : ", ");
    //   return o << "]";
    // }
  //.
//.
template <typename T = double> 
class Vector {  
  template <typename A, typename B, typename C> friend class IteratorBase;
  //§ Private Variables
    // st savedElements    {    0    }, 
    //    currentCapacity  {    0    };
    // T *data             { nullptr };
    st sz                 {    0    }, 
       max_sz             {    0    };
    T *values             { nullptr };
  //.
  //§ Helpers
    Vector& resize (const st newSize) {
      if (newSize == max_sz) {} // do nothing
      else if (newSize == 0) this->clear();
      else {
        this->sz = ((newSize < sz) ? newSize : sz);
        T *newData { new T[newSize] };

        for (st i { 0 }; i < sz; ++i) 
          newData[i] = values[i];
        if (values) 
          delete[] values;

        this->values = newData;
        this->max_sz = newSize;
      }
      return *this;
    }
    auto testValidity(diff pointerDifference, const st strictlySmallerThan) const {
      st number = 0;
      if (pointerDifference < 0 || ((number = static_cast<st>(pointerDifference)) && number >= strictlySmallerThan)) 
        throw std::runtime_error("Iterator Is Out Of Bounds");
      return number;
    }
  //.
  template <typename Derived, typename Target = T, typename Functionality = std::random_access_iterator_tag>
  class IteratorBase { 
    //§ Access To Related Classes
      template <typename A, typename B, typename C> friend class IteratorBase;
      template <typename D>                         friend class Vector;
                                                    friend Derived;
    //.
    protected:
      Target *value              { nullptr };
      const Vector<T> *container { nullptr };
      ~IteratorBase() = default; //* prevent instantiation

    public:
      ADD_ALIASES(T)
      using iterator_category = Functionality;
      //§ Constructors
        IteratorBase()                                                                        = default;
        IteratorBase(Target *ptr)                                                             : value{ptr} {}
        IteratorBase(Target *ptr, const Vector<T>* p)                                         : value{ptr}, container{p}                 {}
        template<typename DifferentIteratorType, typename NewTarget = Target>
        IteratorBase(const IteratorBase<DifferentIteratorType, NewTarget, Functionality> &it) : value{it.value}, container{it.container} {}
      //.
      //§ Operators
        Target&            operator* ()                                                     const {
          if (!container or (value < container->values) or (value >= (container->values + container->sz)))
            throw std::runtime_error("Iterator out of bounds");
          return *value;
        }
        Target* operator->        ()                                                     const {
          if (!container or (value < container->values) or (value >= (container->values + container->sz)))
            throw std::runtime_error("Iterator out of bounds");
          return value;
        }
        //§ Comparisons
          template<typename OtherIterator, typename OtherTarget>
          bool               operator==        (const IteratorBase<OtherIterator,OtherTarget> &it)  const {
            return (this->value == it.value);
          }
            template<typename OtherIterator, typename OtherTarget>
          bool               operator!=        (const IteratorBase<OtherIterator,OtherTarget> &it)  const {
            return !(this->value == it.value);
          }
            template<typename OtherIterator, typename OtherTarget>
          bool               operator>         (const IteratorBase<OtherIterator,OtherTarget> &it)  const {
            return (this->value > it.value);
          }
            template<typename OtherIterator, typename OtherTarget>
          bool               operator>=        (const IteratorBase<OtherIterator,OtherTarget> &it)  const {
            return (this->value >= it.value);
          }
            template<typename OtherIterator, typename OtherTarget>
          bool               operator<         (const IteratorBase<OtherIterator,OtherTarget> &it)  const {
            return (this->value < it.value);
          }
            template<typename OtherIterator, typename OtherTarget>
          bool               operator<=        (const IteratorBase<OtherIterator,OtherTarget> &it)  const {
            return (this->value <= it.value);
          }
        //.
        //§ Movement
          Derived            operator+         (const diff offset)                                    const {
            return Derived((this->value + offset), this->container);
          }
          Derived            operator+         (const int offset)                                     const {
            return Derived((this->value + offset), this->container);
          }
          Derived            operator-         (const diff offset)                                    const {
            return Derived((this->value - offset), this->container);
          }
          Derived            operator-         (const int offset)                                     const {
            return Derived((this->value - offset), this->container);
          }
          Derived&           operator++        ()                                                           {
            if (container and value >= container->values and value < (container->values + container->sz)) ++value; 
            return static_cast<Derived&>(*this);
          }
          Derived            operator++        (int)                                                        {
            auto temp = static_cast<Derived&>(*this); 
            if (container and value >= container->values and value < (container->values + container->sz)) ++value; 
            return temp;
          }
          Derived&           operator--        ()                                                           {
            if (container and value > container->values and value <= (container->values + container->sz)) --value; 
            return static_cast<Derived&>(*this);
          }
          Derived            operator--        (int)                                                        {
            auto temp = static_cast<Derived&>(*this); 
            if (container and value > container->values and value <= (container->values + container->sz)) --value; 
            return temp;
          }
          Derived&           operator+=        (const int offset)                                           {
            return (this->value += offset), static_cast<Derived&>(*this);
          }
          Derived&           operator-=        (const int offset)                                           {
            return (this->value -= offset), static_cast<Derived&>(*this);
          }
        //.
        //§ Other
          diff               operator-         (const IteratorBase &it)                               const {
            return (static_cast<diff>(this->value - it.value));
          }
          explicit operator           bool              ()                                                           {
            return (this->value != nullptr);
          }
        //.
      //.
  };
  public:
    ADD_ALIASES(T)
    //§ Constructors
      Vector() = default;
      Vector(const st toReserve, const st savedCurrently = 0) 
            : sz{savedCurrently}, max_sz{toReserve}, 
              values{((max_sz > 0) ? new T[max_sz] : nullptr)}               {
      }
      Vector(const Vector<T> &v)            : Vector(v.capacity(), v.size())                                {
        for (st i { 0 }; i < v.size(); ++i) 
          values[i] = v[i];
      }
      Vector(std::initializer_list<T> v)    : Vector(v.size(), v.size())                                    {
        for (st i { 0 }; i < sz; ++i) 
          values[i] = *(v.begin() + i);
      }
      Vector(Vector&& other) noexcept : sz{other.sz}, 
                                        max_sz{other.max_sz}, 
                                        values{other.values}                                                    {
        other.values = nullptr; 
        other.sz = other.max_sz = 0;
      }
    //.
    //§ Iterators
      struct Iterator       :  public IteratorBase<Iterator>       {
        using IteratorBase<Iterator>::IteratorBase;
      };
      struct ConstIterator  :  public IteratorBase<ConstIterator, const T>  {
        using IteratorBase<ConstIterator, const T>::IteratorBase;
      };
    //.
    //§ Methods
      bool               empty            ()                               const noexcept {
        return (sz == 0);
      }
      st                 size             ()                               const noexcept {
        return sz;
      }
      st                 capacity         ()                               const noexcept {
        return max_sz;
      }
      ConstIterator      begin            ()                               const noexcept {
        return ConstIterator(this->values, this);
      }
      ConstIterator      end              ()                               const noexcept {
        return ConstIterator(this->values + sz, this);
      }
      Iterator           begin            ()                                     noexcept {
        return Iterator(this->values, this);
      }
      Iterator           end              ()                                     noexcept {
        return Iterator(this->values + sz, this);
      }
      Vector&            clear            ()                                     noexcept {
        return (sz = 0, *this); 
      }
      Vector&            shrink_to_fit    ()                                              {
        return (this->resize(sz), *this);
      }
      Vector&            pop_back         ()                                              {
        return (((sz == 0) ? throw std::runtime_error("Cannot Pop Back, Vector Is Empty") : --sz), *this);
      }
      Vector&            push_back        (const T &obj)                                  { 
        if (sz >= max_sz) this->resize(growthRate(max_sz));
        else if (!values) this->resize(growthRate(max_sz));
        return (values[sz++] = obj, *this);
      }
      Vector&            push_back        (T &&obj)                                       { 
        if (sz >= max_sz) this->resize(growthRate(max_sz));
        else if (!values) this->resize(growthRate(max_sz));
        return (values[sz++] = std::move(obj), *this);
      }
      Vector&            reserve          (const st newSize)                              {
        return ((newSize <= max_sz) ? *this : this->resize(newSize));
      }
      Iterator           erase            (const Iterator position)                       {
        const auto index = testValidity((position - this->begin()), sz);

        for (st i = index; i < (sz - 1); ++i) 
          values[i] = values[i + 1];
        return --sz, Iterator((values + index), this);
      }
      Iterator           insert           (const Iterator position, const T &value)       {
        const auto index = testValidity((position - this->begin()), (sz + 1));
        
        if (sz >= max_sz) this->resize(growthRate(max_sz));
        for (st i = sz; i > index; --i)
          values[i] = values[i - 1];

        return values[index] = value, ++sz, Iterator((values + index), this);
      }
    //.
    //§ Operators
      const T&             operator[]      (const st index)                         const {
        if (index >= sz) throw std::runtime_error("Attempted To Access Index " + std::to_string(index) + ", But Size Is " + std::to_string(sz));
        return values[index];
      }
      T&                   operator[]      (const st index)                               {
        if (index >= sz) throw std::runtime_error("Attempted To Access Index " + std::to_string(index) + ", But Size Is " + std::to_string(sz));
        return values[index];
      }
      Vector&              operator=       (const Vector &other)                          { 
        if (this != &other) {
          if (other.sz > max_sz) {
              if (values) delete[] values;
              max_sz = other.capacity();
              values = new T[max_sz];
          }
          sz = other.sz;
          for (st i = 0; i < sz; ++i)  values[i] = other.values[i];
        }
        return *this;
      }
      Vector&              operator=       (Vector &&other)                       noexcept { 
        if (this != &other) {
          if (values) delete[] values;
          this->max_sz = other.max_sz;
          this->sz = other.sz;
          this->values = other.values;
          other.values = nullptr;
          other.max_sz = other.sz = 0;
        }
        return *this;
      }
      Vector&              operator=       (std::initializer_list<T> list)                { 
        return Vector<T>::operator=((Vector(list)));
      }
    //.
    ~Vector() {
      if (values) delete[] values;
      values = nullptr;
    }
    //§ Aliases
      using iterator       = Iterator;
      using const_iterator = ConstIterator;
    //.
    friend difference_type operator-(const ConstIterator& lop, const ConstIterator& rop) {
    return lop.operator->() - rop.operator->();
}
};
#undef ADD_ALIASES
#endif