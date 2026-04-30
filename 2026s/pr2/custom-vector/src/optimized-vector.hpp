#ifndef CUSTOM_VECTOR_IMPLEMENTATION
#define CUSTOM_VECTOR_IMPLEMENTATION // TODO add efficient dynamicMemory usage
//§ Requisites
  //§ Includes
    #include <ostream>
    #include <iterator>
    #include <concepts>
    #include <initializer_list>
    #include <cstddef>
    #include <stdexcept>
    #include <format>
    #include <utility>
    #include <memory>
  //.
  //§ Helper Concept / Aliases
    using st   = std::size_t;
    using diff = std::ptrdiff_t;
    constexpr st growthRate(const st &size) { return (size + 1) * 2; }
    template <typename T> concept isPrintable = requires(std::ostream &o, const T &t) { o << t; };
    template <typename T> inline T sc(std::convertible_to<T> auto objToConvert) noexcept { return (static_cast<T>(objToConvert)); }
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
    template <typename T> inline std::ostream& operator<< (std::ostream &o, const Vector<T> &v) requires (isPrintable<T>) {
      o << "[";
      for (st i { 0 }, size { v.size() }; i < size; ++i)
        o << v[i] << ((i == (size - 1)) ? "" : ", ");
      return o << "]";
    }
  //.
//.
template <typename T = double> 
class Vector {
  template <typename A, typename B, typename C> friend class IteratorBase;
  //§ Private Variables
    st savedElements    {    0    }, 
       currentCapacity  {    0    };
    T *data             { nullptr };
    std::allocator<T>  dynamicMemory;
  //.
  //§ Helpers
    Vector& resize (const st newSize) {
      if (newSize == 0) this->clear();
      else if (newSize != currentCapacity) {
        auto result = dynamicMemory.allocate_at_least(newSize);
        this->savedElements = ((newSize < savedElements) ? newSize : savedElements);
        this->currentCapacity = result.count; T *newData = result.ptr;
        st previouslySavedElements = this->savedElements;

        if (data) {
          std::uninitialized_move(data, data + previouslySavedElements, newData);
          std::destroy(data, data + previouslySavedElements);
          dynamicMemory.deallocate(data, previouslySavedElements);
        }
        this->data = newData;
        // for (st i = 0; i < savedElements; ++i) {
        //   std::construct_at(newData + i, std::move(data[i]))
        //   std::destroy_at(data + i);
        // }
        // if (data)
        //   dynamicMemory.deallocate(data, previouslySavedElements);
        // data = newData;
      }
      return *this;
    }
    auto testValidity(diff pointerDifference, const st strictlySmallerThan) const {
      st number = 0;
      if (pointerDifference < 0 || ((number = sc<st>(pointerDifference)) && number >= strictlySmallerThan)) 
        throw std::runtime_error("Iterator Is Out Of Bounds");
      return number;
    }
  //.
  template <typename Derived, typename Target = T, typename Functionality = std::random_access_iterator_tag>
  class IteratorBase { // : public Aliases<Target> {
    //§ Access To Related Classes
      template <typename A, typename B, typename C> friend class IteratorBase;
      template <typename D>                         friend class Vector;
                                                    friend Derived;
    //.
    protected:
      Target *value { nullptr };
      ~IteratorBase() = default; //* prevent instantiation
    public:
      ADD_ALIASES(T)
      using iterator_category = Functionality;
      //§ Constructors
        IteratorBase()                                                                        = default;
        IteratorBase(Target *ptr)                                                             : value{ptr} {}
        template<typename DifferentIteratorType, typename NewTarget = Target>
        IteratorBase(const IteratorBase<DifferentIteratorType, NewTarget, Functionality> &it) : value{it.value} {}
      //.
      //§ Operators
        Target&            operator*         ()                                                     const {
          return *value;
          // return (sc<const Derived*>(this)->getValueReference());
        }
        Target*            operator->        ()                                                     const {
          return value;
          // return (sc<const Derived*>(this)->getValuePointer());
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
            return Derived(this->value + offset);
          }
          Derived            operator+         (const int offset)                                     const {
            return Derived(this->value + offset);
          }
          Derived            operator-         (const diff offset)                                    const {
            return Derived(this->value - offset);
          }
          Derived            operator-         (const int offset)                                     const {
            return Derived(this->value - offset);
          }
          Derived&           operator++        ()                                                           {
            // return ();
            return ++value, static_cast<Derived&>(*this);
          }
          Derived            operator++        (int)                                                        {
            // return ();
            return Derived((++value - sc<st>(1)));
          }
          Derived&           operator--        ()                                                           {
            return --value, static_cast<Derived&>(*this);
          }
          Derived            operator--        (int)                                                        {
            return Derived((--value - sc<st>(1)));
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
            return (sc<diff>(this->value - it.value));
          }
          operator           bool              ()                                                           {
            return (this->value != nullptr);
          }
        //.
      //.
  };
  public:
    ADD_ALIASES(T)
    //§ Constructors
      Vector() = default;
      Vector(const st toReserve, const st savedCurrently = 0) : savedElements{savedCurrently}               {
        // if (isPrintable<T>) std::clog << green << "Created" << r <<  " Vector, And Reserved " << blue << currentCapacity << r << " Places" << std::endl;
        auto result = dynamicMemory.allocate_at_least(toReserve);
        this->currentCapacity = result.count;
        this->data = result.ptr;
      }
      Vector(const Vector<T> &v)            : Vector(v.capacity(), v.size())                                {
        for (st i { 0 }; i < v.size(); ++i) 
          data[i] = std::move(v[i]);
        // if (isPrintable<T>) std::clog << green << "Created" << r << " Vector, With The Following Contents: " << *this << std::endl;
      }
      Vector(std::initializer_list<T> v)    : Vector(v.size(), v.size())                                    {
        for (st i { 0 }; i < savedElements; ++i) 
          data[i] = *(v.begin() + i);
        // if (isPrintable<T>) std::clog << green << "Created" << r << " Vector, With The Following Contents: " << *this << std::endl;
      }
      Vector(Vector&& other) noexcept : savedElements{other.savedElements}, 
                                        currentCapacity{other.currentCapacity}, 
                                        data{other.data}                                                    {
        other.data = nullptr; 
        other.savedElements = other.currentCapacity = 0;
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
        return (savedElements == 0);
      }
      st                 size             ()                               const noexcept {
        return savedElements;
      }
      st                 capacity         ()                               const noexcept {
        return currentCapacity;
      }
      ConstIterator      begin            ()                               const noexcept {
        return ConstIterator(this->data);
      }
      ConstIterator      end              ()                               const noexcept {
        return ConstIterator(this->data + savedElements);
      }
      Iterator           begin            ()                                     noexcept {
        return Iterator(this->data );
      }
      Iterator           end              ()                                     noexcept {
        return Iterator(this->data + savedElements);
      }
      Vector&            clear            ()                                     noexcept {
        // if (data) delete[] data, data = nullptr; // , data = new T[currentCapacity];
        // TODO add destruction of items
        return (savedElements = 0, *this); // = currentCapacity = 0, *this);
      }
      Vector&            shrink_to_fit    ()                                              {
        return (this->resize(savedElements), *this);
      }
      Vector&            pop_back         ()                                              {
        // return (((savedElements == 0) ? throw std::runtime_error("Cannot Pop Back, Vector Is Empty") : --savedElements), *this);
        return std::destroy_at(data + savedElements), --savedElements, *this;
      }
      Vector&            push_back        (const T &obj)                                  { 
        if (savedElements >= currentCapacity) this->resize(growthRate(currentCapacity));
        else if (!data) this->resize(growthRate(currentCapacity));
        return (data[savedElements++] = obj, *this);
      }
      Vector&            push_back        (T &&obj)                                       { 
        if (savedElements >= currentCapacity) this->resize(growthRate(currentCapacity));
        else if (!data) this->resize(growthRate(currentCapacity));
        return (data[savedElements++] = std::move(obj), *this);
      }
      Vector&            reserve          (const st newSize)                              {
        return ((newSize <= currentCapacity) ? *this : this->resize(newSize));
      }
      Iterator           erase            (const Iterator position)                       {
        // if (this->empty()) throw std::runtime_error("Vector Is Empty, Cannot Erase");
        const auto index = testValidity((position - this->begin()), savedElements);

        for (st i = index; i < (savedElements - 1); ++i) 
          data[i] = std::move(data[i + 1]);
        return --savedElements, Iterator(data + index);
      }
      Iterator           insert           (const Iterator position, const T &value)       {
        const auto index = testValidity((position - this->begin()), (savedElements + 1));
        
        if (savedElements >= currentCapacity) this->resize(growthRate(currentCapacity));
        for (st i = savedElements; i > index; --i)
          data[i] = std::move(data[i - 1]);

        return data[index] = value, ++savedElements, Iterator(data + index);
      }
    //.
    //§ Operators
      const T&             operator[]      (const st index)                         const {
        if (index >= savedElements) throw std::runtime_error(std::format("Attempted To Access Index {}, But Size Is {}", index, savedElements));
        return data[index];
      }
      T&                   operator[]      (const st index)                               {
        if (index >= savedElements) throw std::runtime_error(std::format("Attempted To Access Index {}, But Size Is {}", index, savedElements));
        return data[index];
      }
      Vector&              operator=       (const Vector &other)                  noexcept { 
        if (this != &other) {
          if (other.savedElements > currentCapacity) this->clear().resize(other.capacity()); 
          savedElements = other.savedElements;
          for (st i = 0; i < savedElements; ++i)  data[i] = other.data[i];
        }
        return *this;
      }
      Vector&              operator=       (Vector &&other)                       noexcept { 
        if (this != other) {
          // TODO add new deallocation logic
          this->currentCapacity = other.currentCapacity;
          this->savedElements = other.savedElements;
          this->data = other.data;
          other.data = nullptr;
          other.currentCapacity = other.savedElements = 0;
        }
        return *this;
      }
      Vector&              operator=       (std::initializer_list<T> list)                { // TODO review this works
        return Vector<T>::operator=((Vector(list)));
      }
    //.
    ~Vector() {
      // if (isPrintable<T>) std::clog << red << "Destroying" << r << " Vector, Current Contents: " << *this << std::endl;
      this->clear(); //* use this or the loop
      if (data)
        for (st i = 0; i < savedElements; ++i)
          std::destroy_at(data + i);
      dynamicMemory.deallocate(data, currentCapacity);
      data = nullptr;
    }
    //§ Aliases
      using iterator       = Iterator;
      using const_iterator = ConstIterator;
    //.
};
#undef ADD_ALIASES
#endif