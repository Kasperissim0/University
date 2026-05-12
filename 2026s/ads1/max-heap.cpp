#include <iostream>
#include <string>
using namespace std;

class MaxHeap {
  public:
    [[nodiscard]] string print() const {
      // TODO graphical representation
    }
};
ostream& operator<< (ostream& output, const MaxHeap& heap) {
  return output << heap.print();
}
int main() {
  // TODO create tests
  return 0;
}