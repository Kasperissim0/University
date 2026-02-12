//* create a custom data structore and iterotrs for it

//§ Preamble
  #include <initializer_list>
  #include <iostream>
  using namespace std;
//.

namespace Data {
  template <typename T>
  class Data {
      size_t size = 0;
      vector<T> storage;
    public:
      Data() {

      }
      Data(initializer_list<T> objects) {
        for (auto i = objects.begin(); i != objects.end(); ++i)
          if (i) storage.emplace_back(*i), ++storage;
      }
  };
  class Itetor {
    
  };
}


int main() {

  return 0;
}