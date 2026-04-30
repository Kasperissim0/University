/* Part of ADS1
   University of Vienna
   Author: Sagar Kale.
   Test code generated with the help of an LLM.
   NOTE: THE MAIN PURPOSE OF THIS CODE IS DEMONSTRATION OF DATA STRUCTURE
   CONCEPTS. THIS CODE MAY NOT NECESSARILY SHOW BEST SOFTWARE ENGINEERING
   PRACTICES!
*/

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <sstream>

class my_queue {
  int      *data = nullptr;
  size_t   readIndex = 0, 
           writeIndex = 0, 
           currentCapacity = 0;
  my_queue& resize(const size_t newCapacity) {
    int *newMemory = new int[newCapacity];
    for (size_t i = 0; i < this->currentCapacity; ++i)
      if (i < currentCapacity) newMemory[i] = data[i];
    delete data, this->data = newMemory;
    return *this;
  }
  public:
    my_queue(int n) : currentCapacity{static_cast<size_t>(n)} {
      data = new int[currentCapacity];
    }
    void enqueue(int value) {
      if (((writeIndex + 1) % currentCapacity) == readIndex) this->resize((currentCapacity + 1) * 2);
      data[writeIndex++] = value;
    }
    int dequeue() { // if (!currentCapacity || !data) throw std::runtime_error("Queue Is Empty");
      // if (((readIndex + 1) % currentCapacity) == writeIndex) throw std::runtime_error("Queue Is Empty");
      return data[readIndex++];
    }
    bool is_empty() { 
      return !(writeIndex - readIndex);
    }
    ~my_queue() { 
      delete[] this->data;
    }
};

//§ Tests
  bool test_queue() {
    my_queue mq{100000};
    std::queue<int> q;
    std::srand(std::time(0));
    int num_elements = std::rand() % 100000 + 1;

    // Enqueue elements
    for (int i = 0; i < num_elements; ++i) {
      int value = std::rand();
      mq.enqueue(value);
      q.push(value);
    }

    // Dequeue elements and verify
    size_t count = 0;
    while (!q.empty()) {
      assert(mq.dequeue() == q.front());
      q.pop();
    }
    assert(mq.is_empty() == q.empty());
    return true;
  }

  bool test_queue_mixed() {
    my_queue mq{100000};
    std::queue<int> q;
    std::srand(std::time(0));
    int num_operations = std::rand() % 100000 + 1;

    for (int i = 0; i < num_operations; ++i) {
      int operation = std::rand() % 2; // 0 for enqueue, 1 for dequeue
      if (operation == 0 || q.empty()) {
        int value = std::rand();
        mq.enqueue(value);
        q.push(value);
      } else {
        assert(mq.dequeue() == q.front());
        q.pop();
      }
    }
    assert(mq.is_empty() == q.empty());
    return true;
  }

  int main() {
    if (test_queue() && test_queue_mixed()) std::cout << "Queue tests passed!" << std::endl;
    return 0;
  }
//.