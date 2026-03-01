//* create a custom data structore and iterotrs for it

//§ Preamble
  #include <initializer_list>
  #include <iostream>
  using namespace std;
//.

//? Source(s):  https://moodle.univie.ac.at/mod/extserver/view.php?id=19368923
/* 
  Iterators are used to traverse lists of objects in a given order. 
  They are often used to formulate algorithms (e.g. sorting algorithms) independently of the internal representation of the objects or the list.
  Write three classes, Object, List, and Iterator, to provide the following functionality: Object is a proxy for any class. 
  For test purposes, this class should have at least one print method that enables the objects to be uniquely identified. 
  List is to manage objects in a dynamic array. 
  The list should have add and insert methods, which can insert an object at the end and at the beginning of the list, respectively. 
  Iterator should contain the ++ and -- operators, which are used to move forward and backward in the list, respectively, and the * (dereferencing) operator, which returns the current object. 
  An iterator that refers to the first element of a list is returned by calling the begin() method of the List class. 
  Assuming that the list l is filled with the four objects 'a', 'b', 'c' and 'd', e.g. B. the following piece of program will deliver the listed results:
      Iterator it{l.begin()};
      (*it).print(); //Output of 'a';
      it++;
      (*it).print(); //Output of 'b';
      it--;
      (*it).print(); //Output of 'a';
*/

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