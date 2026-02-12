#include <iostream>
#include <ostream>
#include <stdexcept>
#include <optional>
#include <vector>

using namespace std;

template <typename T>
class SafePtr {
    const T* p;
  public:
    SafePtr(optional<T>& value = nullopt) {
      p = value ? new T(*value) : nullptr;
    }
    SafePtr(optional<T>&& value = nullopt) {
      p = value ? new T(*value) : nullptr;
    }
    SafePtr(optional<T>* value = nullopt) {
      p = value ? *value : nullptr;
    }
    ~SafePtr() {
      cout << "Deleting p -> " << *p << endl;
      delete p;
    }
    T operator*() const {
      if (p)        return *p;
      else          throw runtime_error("\n❌ ERROR: No Value Assigned To Object");
    }
};

template <typename T>
ostream& operator<< (ostream& o, const SafePtr<T>& p) {
  o << "Attempting To Dereference Internal Pointer 🚧" << endl
    << "Value Stored: " << *p << endl;
  return o;
}
template <typename T>
ostream& operator<< (ostream& o, const vector<SafePtr<T>>& v) {
  for (size_t i = 0; i < v.size(); ++i)
    o << "Entry #" << (i + 1) << endl
      << "- " << v.at(i);
  return o;
}


int main() {
  vector<SafePtr<int>> values;
    values.emplace_back(5);
    // values.emplace_back(10);
    // values.emplace_back(51);
    // values.emplace_back(3);
    // values.emplace_back(5);
    values.emplace_back(nullopt);

  try { cout << values << endl;}
  catch (...) {}
  return 0;
}